/*************************************************************************************//**
* @file lwip_tcp_stream.h
* @brief Implementation of TCP streams with lwIP RAW API
* @author Jon Ayerdi
*****************************************************************************************/
#ifndef SRC_HAL_LWIP_TCP_STREAM_H_
#define SRC_HAL_LWIP_TCP_STREAM_H_

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/

#include "io/stream.h"

#include "lwip/tcp.h"

#include <stdlib.h>

/*--------------------------------------------------------------------------------------*/
/*                                        TYPES                                         */
/*--------------------------------------------------------------------------------------*/

typedef struct lwip_tcp_stream
{
	volatile struct tcp_pcb *socket;
	volatile int closed;
	volatile size_t received;
	volatile char buffer[512];
} lwip_tcp_stream_t;

/*--------------------------------------------------------------------------------------*/
/*                            PUBLIC FUNCTION DECLARATIONS                              */
/*--------------------------------------------------------------------------------------*/

/** @brief initializes a lwIP TCP connection.
 *  @param istream the input stream.
 *  @param ostream the output stream.
 *  @param address destination address.
 *  @param port destination port.
 *  @return 0 (OK) or nonzero (error).
 */
int lwip_tcp_stream(input_stream_t *istream, output_stream_t *ostream, const char *address, const char *port);

#endif /* SRC_HAL_LWIP_TCP_STREAM_H_ */

/*****************************************************************************************
*                                   lwip_tcp_stream.h
*****************************************************************************************/
