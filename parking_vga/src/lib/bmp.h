/*
 * bmp.h
 *
 *  Created on: 15 Nov 2017
 *      Author: Jon Ayerdi
 */

#ifndef SRC_LIB_BMP_H_
#define SRC_LIB_BMP_H_

#include <stddef.h> /* size_t */
#include <stdint.h> /* uint32_t */

#include "image.h"
#include "io/stream.h"

#define BMP_STATE_OK 0
#define BMP_STATE_ERROR_HEADER 1
#define BMP_STATE_ERROR_STREAM 2

int bmp_load(input_stream_t input, image_t *output);

#endif /* SRC_LIB_BMP_H_ */
