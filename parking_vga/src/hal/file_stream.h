/*
 * file_stream.h
 *
 *  Created on: 17 Nov 2017
 *      Author: Jon Ayerdi
 */

#ifndef SRC_HAL_FILE_STREAM_H_
#define SRC_HAL_FILE_STREAM_H_

#include "io/stream.h"

int file_input_stream(input_stream_t *stream, const char *filename);
int file_output_stream(output_stream_t *stream, const char *filename);

#endif /* SRC_HAL_FILE_STREAM_H_ */
