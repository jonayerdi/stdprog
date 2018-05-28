/*************************************************************************************//**
* @file socket_stream.h
* @brief Implementation of TCP socket streams
* @author Jon Ayerdi
*****************************************************************************************/
#ifndef SRC_HAL_SOCKET_STREAM_H_
#define SRC_HAL_SOCKET_STREAM_H_

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/
#include "io/stream.h"

/*--------------------------------------------------------------------------------------*/
/*                            PUBLIC FUNCTION DECLARATIONS                              */
/*--------------------------------------------------------------------------------------*/

/** @brief initializes a socket iostream.
 *  @param istream the input stream.
 *  @param ostream the output stream.
 *  @param address the destination IP address.
 *  @param port the destination port.
 *  @return 0 (OK) or nonzero (error).
 */
int socket_stream(input_stream_t *istream, output_stream_t *ostream, const char *address, const char *port);

#endif /* SRC_HAL_SOCKET_STREAM_H_ */

/*****************************************************************************************
*                                      socket_stream.h
*****************************************************************************************/
