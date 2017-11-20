/*
 * stdio_stream.h
 *
 *  Created on: 17 Nov 2017
 *      Author: Jon Ayerdi
 */

#ifndef SRC_HAL_STDIO_STREAM_H_
#define SRC_HAL_STDIO_STREAM_H_

#include "io/stream.h"

int stdio_input_stream(input_stream_t *stream);
int stdio_output_stream(output_stream_t *stream);

#endif /* SRC_HAL_STDIO_STREAM_H_ */
