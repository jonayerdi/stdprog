/*
 * bmp.c
 *
 *  Created on: 17 Nov 2017
 *      Author: Jon Ayerdi
 */

#include "lib/bmp.h"

#include "io/memory.h"

#define BMP_FILE_HEADER_SIGNATURE 0x4D42
#define BMP_INFO_HEADER_COLOR_PLANES 1
#define BMP_INFO_HEADER_BITS_PER_PIXEL 24
#define BMP_INFO_HEADER_COMPRESSION 0

int _check_header(bmp_header_t header);

int _check_header(bmp_header_t header)
{
	if(header.file_header.signature != BMP_FILE_HEADER_SIGNATURE)
		return BMP_STATE_ERROR_HEADER;
	if(header.info_header.color_planes != BMP_INFO_HEADER_COLOR_PLANES)
		return BMP_STATE_ERROR_HEADER;
	if(header.info_header.bits_per_pixel != BMP_INFO_HEADER_BITS_PER_PIXEL)
		return BMP_STATE_ERROR_HEADER;
	if(header.info_header.compression != BMP_INFO_HEADER_COMPRESSION)
		return BMP_STATE_ERROR_HEADER;
	return BMP_STATE_OK;
}

int bmp_load(input_stream_t input, image_t *output)
{
	//Declare local variables
	int state;
	bmp_header_t header;
	size_t read;
	//Read and check BMP header
	read = stream_read(input, (char *)&header, sizeof(bmp_header_t));
	if(read != sizeof(bmp_header_t))
		return BMP_STATE_ERROR_STREAM;
	state = _check_header(header);
	if(state != BMP_STATE_OK)
		return state;
	//Set image parameters and allocate pixel buffer
	output->x = header.info_header.image_width;
	output->y = header.info_header.image_height;
	output->stride = header.info_header.image_width;
	output->pixels = (pixel_t *)memory_allocate(sizeof(pixel_t) * header.info_header.image_width * header.info_header.image_height);
	//Read pixel buffer
	for(size_t y = 0 ; y < output->y ; y++)
	{
		for(size_t x = 0 ; x < output->x ; x++)
		{
			read = stream_read(input, (char *)&output->pixels[((output->y - y - 1) * output->x) + (output->x - x - 1)], header.info_header.bits_per_pixel / 8);
			if(read != (header.info_header.bits_per_pixel / 8))
				return BMP_STATE_ERROR_STREAM;
		}
		size_t remain = (output->x * header.info_header.bits_per_pixel / 8) % 4;
		if(remain)
		{
			char buffer[3];
			size_t to_read = 4 - remain;
			read = stream_read(input, buffer, to_read);
			if(read != to_read)
				return BMP_STATE_ERROR_STREAM;
		}
	}
	return BMP_STATE_OK;
}
