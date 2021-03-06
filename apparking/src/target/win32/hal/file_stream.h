/*************************************************************************************//**
* @file file_stream.h
* @brief Implementation of file streams via stdin
* @author Jon Ayerdi
*****************************************************************************************/
#ifndef SRC_HAL_FILE_STREAM_H_
#define SRC_HAL_FILE_STREAM_H_

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/
#include "io/stream.h"

/*--------------------------------------------------------------------------------------*/
/*                            PUBLIC FUNCTION DECLARATIONS                              */
/*--------------------------------------------------------------------------------------*/

/** @brief initializes a file input stream.
 *  @param stream the stream.
 *  @param filename name of the file.
 *  @return 0 (OK) or nonzero (error).
 */
int file_input_stream(input_stream_t *stream, const char *filename);
/** @brief initializes a file output stream.
 *  @param stream the stream.
 *  @param filename name of the file.
 *  @return 0 (OK) or nonzero (error).
 */
int file_output_stream(output_stream_t *stream, const char *filename);

#endif /* SRC_HAL_FILE_STREAM_H_ */

/*****************************************************************************************
*                                      file_stream.h
*****************************************************************************************/
