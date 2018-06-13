/*************************************************************************************//**
* @file lwip_tcp_stream.c
* @brief Implementation of TCP streams with lwIP RAW API
* @author Jon Ayerdi
*****************************************************************************************/

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/

#include "hal/lwip_tcp_stream.h"

#include "io/memory.h"
#include "config/logger.h"

#include <stdint.h>
#include <string.h>

#include "xscutimer.h"
#include "xparameters.h"
#include "xil_exception.h"
#include "lwip/init.h"
#include "lwip/err.h"

/*--------------------------------------------------------------------------------------*/
/*                            		 	  GLOBALS                                       */
/*--------------------------------------------------------------------------------------*/

/* the MAC address of the board.
	* This should be unique per board/PHY */
static unsigned char mac_ethernet_address[6] =
	{ 0x00, 0x0a, 0x35, 0x00, 0x01, 0x02 };
static struct ip_addr ipaddr, netmask, gw;
struct netif *netif, server_netif;
static volatile int connected;
static volatile struct tcp_pcb *sock;
static volatile int initialized = 0;

/*--------------------------------------------------------------------------------------*/
/*                            		 PRIVATE FUNCTIONS                                  */
/*--------------------------------------------------------------------------------------*/

char _str_err(err_t e);
uint32_t _ip_addr_from_str(const char *str);
uint32_t _u32_from_str(const char *str, size_t len);
int _lwip_init(void);
void _tcp_connect(const char *address, const char *port);
err_t _tcp_connected(void *arg, struct tcp_pcb *tpcb, err_t err);
void _tcp_error_connect(void *arg, err_t err);
err_t recv_callback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
err_t sent_callback(void *arg, struct tcp_pcb *tpcb, u16_t len);

static size_t _read(char *str, size_t size, void *context);
static size_t _write(const char *str, size_t size, void *context);
static void _discard(void *context);
static void _flush(void *context);
static void _close(void *context);

char _str_err(err_t e)
{
	switch(e)
	{
	case 0:
		return '0';
	case -1:
		return '1';
	case -2:
		return '2';
	case -3:
		return '3';
	case -4:
		return '4';
	case -5:
		return '5';
	case -6:
		return '6';
	case -7:
		return '7';
	case -8:
		return '8';
	case -9:
		return '9';
	case -10:
		return 'A';
	case -11:
		return 'B';
	case -12:
		return 'C';
	case -13:
		return 'D';
	case -14:
		return 'E';
	case -15:
		return 'F';
	default:
		return 'U';
	}
}

uint32_t _ip_addr_from_str(const char *str)
{
	uint32_t value = 0;
	int digit = 0;
	char nums[3];
	int i, index = 0;
	for(digit = 0 ; digit < 4 ; digit++)
	{
		for(i = 0 ; str[index] != '.' ; i++, index++)
		{
			if(str[index] == '\0')
			{
				index--;
				break;
			}
			nums[i] = str[index];
		}
		index++;
		value |= (_u32_from_str(nums, i) << (8*digit));
	}
	return value;
}
uint32_t _u32_from_str(const char *str, size_t len)
{
	uint32_t value = 0;
	for(size_t i = 0 ; i < len ; i++)
	{
		value *= 10;
		value += (str[i] - '0');
	}
	return value;
}

int _lwip_tcp_is_initialized(void)
{
	return initialized;
}
struct netif *_lwip_tcp_get_netif(void)
{
	return netif;
}

int _lwip_init(void)
{
	if(!initialized)
	{
		/* Netif */
		netif = &server_netif;
		/* IP */
		IP4_ADDR(&ipaddr,  192, 168,   0, 222);
		IP4_ADDR(&netmask, 255, 255, 255,  0);
		IP4_ADDR(&gw,      192, 168,   0,  1);
		/* lwip_init */
		lwip_init();
		/* Add network interface to the netif_list,
		* and set it as default */
		if (!xemac_add(netif, &ipaddr, &netmask, &gw, mac_ethernet_address, XPAR_XEMACPS_0_BASEADDR))
			return -1;
		netif_set_default(netif);
		/* specify that the network if is up */
		netif_set_up(netif);
		/* done */
		initialized = 1;
	}
	return 0;
}

void _tcp_connect(const char *address, const char *port)
{
	struct tcp_pcb *socket;
	struct ip_addr ip;
	err_t err;

	ip.addr = _ip_addr_from_str(address);
	uint16_t prt = (uint16_t)_u32_from_str(port, strlen(port));

	while(1)
	{
		connected = 0;
		LOG("Connecting to "); LOG(address); LOG(":"); LOG(port); LOG("\n");
		socket = tcp_new();
		tcp_err(socket, _tcp_error_connect);
		sock = NULL;
		err = tcp_bind(socket, IP_ADDR_ANY, 0);
		if(err == ERR_OK)
		{
			LOG("Socket bound\n");
			err = tcp_connect(socket, &ip, prt, _tcp_connected);
			if(err == ERR_OK)
			{
				while(!connected);
				if(sock) break;
			}
			else
			{
				char e[2] = {_str_err(err), '\0'};
				LOG("Error connecting: "); LOG(e); LOG("\n");
			}
		}
		else
		{
			LOG("Socket bind failed\n");
		}
		tcp_close(socket);
	}
	LOG("Connected to "); LOG(address); LOG(":"); LOG(port); LOG("\n");
	tcp_nagle_enable (sock);
}

err_t _tcp_connected(void *arg, struct tcp_pcb *tpcb, err_t err)
{
	if(err == ERR_OK)
		sock = tpcb;
	connected = 1;
	return ERR_OK;
}

void _tcp_error_connect(void *arg, err_t err)
{
	connected = 1;
}

err_t recv_callback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
	lwip_tcp_stream_t *conn = (lwip_tcp_stream_t *)arg;
	if(err != ERR_OK || !p)
	{
		conn->closed = 1;
		tcp_close(conn->socket);
		tcp_recv(conn->socket, NULL);
	}
	else
	{
		memcpy(conn->buffer + conn->received, p->payload, p->len);
		conn->received += p->len;
		tcp_recved(conn->socket, p->len);
	}
	return ERR_OK;
}

err_t sent_callback(void *arg, struct tcp_pcb *tpcb, u16_t len)
{
	lwip_tcp_stream_t *conn = (lwip_tcp_stream_t *)arg;
	conn->sending = 0;
	return ERR_OK;
}

static size_t _read(char *str, size_t size, void *context)
{
	lwip_tcp_stream_t *conn = (lwip_tcp_stream_t *)context;
	while(conn->received < size);
	memcpy(str, conn->buffer, size);
	memmove(conn->buffer, conn->buffer+size, size);
	conn->received -= size;
	return size;
}

static size_t _write(const char *str, size_t size, void *context)
{
	lwip_tcp_stream_t *conn = (lwip_tcp_stream_t *)context;
	while (tcp_sndbuf(conn->socket) < size);
	conn->sending = 1;
	err_t err = tcp_write(conn->socket, str, size, 1);
	if(err == ERR_OK)
		err = tcp_output(conn->socket);
	if(err == ERR_OK)
	{
		//while(conn->sending);
	}
	return err == ERR_OK ? size : 0;
}

static void _discard(void *context)
{
	lwip_tcp_stream_t *conn = (lwip_tcp_stream_t *)context;
	conn->received = 0;
}

static void _flush(void *context)
{
	lwip_tcp_stream_t *conn = (lwip_tcp_stream_t *)context;
	tcp_output(conn->socket);
}

static void _close(void *context)
{
	lwip_tcp_stream_t *conn = (lwip_tcp_stream_t *)context;
	tcp_close(conn->socket);
	tcp_recv(conn->socket, NULL);
	memory_free(conn);
}

/*--------------------------------------------------------------------------------------*/
/*                             PUBLIC FUNCTION DEFINITIONS                              */
/*--------------------------------------------------------------------------------------*/

int lwip_tcp_stream(input_stream_t *istream, output_stream_t *ostream, const char *address, const char *port)
{
	int error;
	/* Init lwIP */
	error = _lwip_init();
	if(error) return error;
	/* Init lwIP TCP block */
	_tcp_connect(address, port);
	/* Setup context */
	lwip_tcp_stream_t *conn = memory_allocate(sizeof(lwip_tcp_stream_t));
	conn->socket = sock;
	conn->closed = 0;
	conn->received = 0;
	tcp_arg(conn->socket, (void*)conn);
	tcp_recv(conn->socket, recv_callback);
	tcp_sent(conn->socket, sent_callback);
	/* Implement input_stream_t */
	istream->read = _read;
	istream->discard = _discard;
	istream->close = _close;
	istream->context = conn;
	/* Implement output_stream_t */
	ostream->write = _write;
	ostream->flush = _flush;
	ostream->close = _close;
	ostream->context = conn;
	return 0;
}

/*****************************************************************************************
*                                   lwip_tcp_stream.c
*****************************************************************************************/
