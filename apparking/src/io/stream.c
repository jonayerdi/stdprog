/*************************************************************************************//**
* @file stream.c
* @brief Interfaces for input and output data streams
* @author Jon Ayerdi
*****************************************************************************************/

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/
#include "io/stream.h"

#include <string.h> /* strlen */

/*--------------------------------------------------------------------------------------*/
/*                             PUBLIC FUNCTION DEFINITIONS                              */
/*--------------------------------------------------------------------------------------*/

void stream_close_input(input_stream_t stream)
{
	stream.close(stream.context);
}

void stream_close_output(output_stream_t stream)
{
	stream.close(stream.context);
}

void stream_discard(input_stream_t stream)
{
	stream.discard(stream.context);
}

void stream_flush(output_stream_t stream)
{
	stream.flush(stream.context);
}

size_t stream_read(input_stream_t stream, char *output, size_t length)
{
	return stream.read(output, length, stream.context);
}

size_t stream_write(output_stream_t stream, const char *input, size_t length)
{
	return stream.write(input, length, stream.context);
}

size_t stream_read_line(input_stream_t stream, char *output, size_t length)
{
	char data = 0;
	size_t read = 0;

	while(data != '\n' && read < length)
	{
		if(stream_read(stream, &data, 1))
			read++;
		else
			break;
	}

	return read;
}

size_t stream_write_string(output_stream_t stream, const char *input)
{
	return stream_write(stream, input, strlen(input));
}

size_t stream_write32(output_stream_t stream, uint32_t input)
{
	return stream_write(stream, (const char *)&input, sizeof(uint32_t));
}

/*****************************************************************************************
*                                         stream.c
*****************************************************************************************/
