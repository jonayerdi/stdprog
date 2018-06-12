/*************************************************************************************//**
* @file bmp.c
* @brief Defines the BMP image file format and provides an interface to parse a BMP file from a stream
* @author Jon Ayerdi
*****************************************************************************************/

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/
#include "lib/bmp.h"

#include "io/memory.h"

/*--------------------------------------------------------------------------------------*/
/*                                        MACROS                                        */
/*--------------------------------------------------------------------------------------*/
#define BMP_FILE_HEADER_SIGNATURE 0x4D42
#define BMP_INFO_HEADER_COLOR_PLANES 1
#define BMP_INFO_HEADER_BITS_PER_PIXEL 24
#define BMP_INFO_HEADER_COMPRESSION 0

#define _BMP_READ(TARGET) { read = stream_read(input, (char *)(&(TARGET)), sizeof(TARGET)); if (read != sizeof(TARGET)) { return BMP_STATE_ERROR_STREAM; } }

/*--------------------------------------------------------------------------------------*/
/*                            		 PRIVATE FUNCTIONS                                  */
/*--------------------------------------------------------------------------------------*/

int _read_header(input_stream_t input, bmp_header_t *output);
int _check_header(bmp_header_t header);

int _read_header(input_stream_t input, bmp_header_t *output)
{
	size_t read;
	//BMP file header
	_BMP_READ(output->file_header.signature);
	_BMP_READ(output->file_header.file_size);
	_BMP_READ(output->file_header.reserved1);
	_BMP_READ(output->file_header.reserved2);
	_BMP_READ(output->file_header.data_offset);
	//BMP info header
	_BMP_READ(output->info_header.header_size);
	_BMP_READ(output->info_header.image_width);
	_BMP_READ(output->info_header.image_height);
	_BMP_READ(output->info_header.color_planes);
	_BMP_READ(output->info_header.bits_per_pixel);
	_BMP_READ(output->info_header.compression);
	_BMP_READ(output->info_header.image_size);
	_BMP_READ(output->info_header.horizontal_resolution);
	_BMP_READ(output->info_header.vertical_resolution);
	_BMP_READ(output->info_header.palette_colors);
	_BMP_READ(output->info_header.important_colors);
	return BMP_STATE_OK;
}

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

/*--------------------------------------------------------------------------------------*/
/*                             PUBLIC FUNCTION DEFINITIONS                              */
/*--------------------------------------------------------------------------------------*/

int bmp_load(input_stream_t input, image_t *output)
{
	//Declare local variables
	int state;
	bmp_header_t header;
	size_t read;
	//Read and check BMP header
	state = _read_header(input, &header);
	if(state != BMP_STATE_OK)
		return state;
	state = _check_header(header);
	if(state != BMP_STATE_OK)
		return state;
	//Set image parameters and allocate pixel buffer
	image_alloc(output, header.info_header.image_width, header.info_header.image_height);
	//Read pixel buffer
	for(size_t y = 0 ; y < output->y ; y++)
	{
		//Read row pixel bytes
		for(size_t x = 0 ; x < output->x ; x++)
		{
			read = stream_read(input, (char *)&output->pixels[((output->y - y - 1) * output->x) + (x)], header.info_header.bits_per_pixel / 8);
			if(read != (header.info_header.bits_per_pixel / 8))
				return BMP_STATE_ERROR_STREAM;
			//Make pixel opaque
			output->pixels[((output->y - y - 1) * output->x) + (x)] |= PIXEL_ALPHA;
		}
		//Read row alignment bytes
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

/****************************************************************************************
*                                       bmp.c
****************************************************************************************/
