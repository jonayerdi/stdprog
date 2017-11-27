/*
 * bmp.h
 *
 *  Created on: 15 Nov 2017
 *      Author: Jon Ayerdi
 */

#ifndef SRC_LIB_BMP_H_
#define SRC_LIB_BMP_H_

#include <stddef.h> /* size_t */
#include <stdint.h> /* uint8_t, uint16_t, uint32_t */

#include "lib/image.h"
#include "io/stream.h"

#define BMP_STATE_OK 0
#define BMP_STATE_ERROR_HEADER 1
#define BMP_STATE_ERROR_STREAM 2

typedef struct bmp_file_header
{
	uint16_t signature;
	uint32_t file_size;
	uint16_t reserved1;
	uint16_t reserved2;
	uint32_t data_offset;
} __attribute__((packed)) bmp_file_header_t;

typedef struct bmp_info_header
{
	uint32_t header_size;
	uint32_t image_width;
	uint32_t image_height;
	uint16_t color_planes;
	uint16_t bits_per_pixel;
	uint32_t compression;
	uint32_t image_size;
	uint32_t horizontal_resolution;
	uint32_t vertical_resolution;
	uint32_t palette_colors;
	uint32_t important_colors;
} __attribute__((packed)) bmp_info_header_t;

typedef struct bmp_header
{
	bmp_file_header_t file_header;
	bmp_info_header_t info_header;
} __attribute__((packed)) bmp_header_t;

int bmp_load(input_stream_t input, image_t *output);

#endif /* SRC_LIB_BMP_H_ */
