/*************************************************************************************//**
* @file stdio_stream.h
* @brief Implementation of stdio stream
* @author Jon Ayerdi
*****************************************************************************************/
#ifndef SRC_HAL_STDIO_STREAM_H_
#define SRC_HAL_STDIO_STREAM_H_

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/
#include "io/stream.h"

/*--------------------------------------------------------------------------------------*/
/*                            PUBLIC FUNCTION DECLARATIONS                              */
/*--------------------------------------------------------------------------------------*/

/** @brief initializes a stdio input stream.
 *  @param stream the stream.
 *  @return 0 (OK) or nonzero (error).
 */
int stdio_input_stream(input_stream_t *stream);
/** @brief initializes a stdio output stream.
 *  @param stream the stream.
 *  @return 0 (OK) or nonzero (error).
 */
int stdio_output_stream(output_stream_t *stream);

#endif /* SRC_HAL_STDIO_STREAM_H_ */

/*****************************************************************************************
*                                      stdio_stream.h
*****************************************************************************************/
