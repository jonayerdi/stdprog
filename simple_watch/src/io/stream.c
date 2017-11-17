/*
 * stream.c
 *
 *  Created on: 16 Oct 2017
 *      Author: Jon Ayerdi
 */

#include "stream.h"

uint64_t stream_str_to_uint(const char *str)
{
	uint64_t result = 0;
	while(*str)
	{
		result *= 10;
		result += CHAR_TO_INT(*str);
		str++;
	}
	return result;
}

uint64_t stream_read_uint(input_stream *in)
{
	char buffer[21];
	char *bufferIndex = buffer;
	size_t read = 0;
	while(bufferIndex == buffer) //Repeat until we get a number
	{
		for(size_t i = 0 ; i < 20 ; i++) //64 bits = max 20 decimal digits
		{
			read = in->read(bufferIndex, 1);
			if(read == 0)
				break; //Break on read failure
			if(*bufferIndex == '\r' || *bufferIndex == '\n' || *bufferIndex == EOF)
				break; //Break on newline or end of stream
			if(!IS_DIGIT(*bufferIndex))
				break; //Break on non numeric char
			bufferIndex++;
		}
	}
	*bufferIndex = '\0';
	return stream_str_to_uint(buffer);
}

void stream_write_str(output_stream *out, char *str)
{
	out->write(str, strlen(str));
}
