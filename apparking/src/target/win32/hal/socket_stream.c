/*************************************************************************************//**
* @file file_stream.c
* @brief Implementation of file streams via stdin
* @author Jon Ayerdi
*****************************************************************************************/

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#include "hal/socket_stream.h"
#include "io/memory.h"

/*--------------------------------------------------------------------------------------*/
/*                            		 PRIVATE FUNCTIONS                                  */
/*--------------------------------------------------------------------------------------*/

static int _winsock_initialized = 0;

static int _winsock_init(void);
static void _winsock_destroy(void);
static size_t _read(char *str, size_t size, void *context);
static size_t _write(const char *str, size_t size, void *context);
static void _discard(void *context);
static void _flush(void *context);
static void _close(void *context);

static int _winsock_init(void)
{
    int error;
    WSADATA wsaData;
    if(!_winsock_initialized)
    {
        error = WSAStartup(MAKEWORD(2,2), &wsaData);
        if (error) return error;
    }
    _winsock_initialized++;
    return 0;
}

static void _winsock_destroy(void)
{
    _winsock_initialized--;
    if(!_winsock_initialized)
        WSACleanup();
}

static size_t _read(char *str, size_t size, void *context)
{
	SOCKET *socket = (SOCKET *)context;
    int iResult = recv(*socket, str, size, 0);
	return iResult;
}

static size_t _write(const char *str, size_t size, void *context)
{
	SOCKET *socket = (SOCKET *)context;
    int iResult = send(*socket, str, (int)size, 0);
    if (iResult == SOCKET_ERROR) return 0;
	return iResult;
}

static void _discard(void *context)
{
	/* Hopefully unused */
}

static void _flush(void *context)
{
	/* Hopefully unused */
}

static void _close(void *context)
{
    SOCKET *socket = (SOCKET *)context;
	closesocket(*socket);
    _winsock_destroy();
    memory_free(socket);
}

/*--------------------------------------------------------------------------------------*/
/*                             PUBLIC FUNCTION DEFINITIONS                              */
/*--------------------------------------------------------------------------------------*/

int socket_stream(input_stream_t *istream, output_stream_t *ostream, const char *address, const char *port)
{
	/* Init winsock */
    SOCKET *ConnectSocket = memory_allocate(sizeof(SOCKET));
    if(!ConnectSocket) return MEMORY_ERROR;
    struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;
    int error;

    // Initialize Winsock
    *ConnectSocket = INVALID_SOCKET;
    error = _winsock_init();
    if (error) return error;

    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    error = getaddrinfo(address, port, &hints, &result);
    if (error) 
    {
        _winsock_destroy();
        memory_free(ConnectSocket);
        return error;
    }

    // Attempt to connect to an address until one succeeds
    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {

        // Create a SOCKET for connecting to server
        *ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, 
            ptr->ai_protocol);
        if (*ConnectSocket == INVALID_SOCKET) {
            _winsock_destroy();
            memory_free(ConnectSocket);
            return 1;
        }

        // Connect to server.
        error = connect(*ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (error == SOCKET_ERROR) {
            closesocket(*ConnectSocket);
            *ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if ((*ConnectSocket) == INVALID_SOCKET) {
        _winsock_destroy();
        memory_free(ConnectSocket);
        return 1;
    }

	/* Implement input_stream_t */
	istream->read = _read;
	istream->discard = _discard;
	istream->close = _close;
	istream->context = ConnectSocket;
    /* Implement output_stream_t */
	ostream->write = _write;
	ostream->flush = _flush;
	ostream->close = _close;
	ostream->context = ConnectSocket;
	return 0;
}

/*****************************************************************************************
*                                      file_stream.c
*****************************************************************************************/
