/*****************************************************************************************
*                                      stdio_stream.h
******************************************************************************************
* AUTHOR: Jon Ayerdi
*
* DESCRIPTION: Implementation of stdio stream
*
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
 *  @param out the stream.
 *  @return 0 (OK) or nonzero (error).
 */
int stdio_input_stream(input_stream_t *stream);
/** @brief initializes a stdio output stream.
 *  @param out the stream.
 *  @return 0 (OK) or nonzero (error).
 */
int stdio_output_stream(output_stream_t *stream);

#endif /* SRC_HAL_STDIO_STREAM_H_ */

/*****************************************************************************************
*                                      stdio_stream.h
*****************************************************************************************/
