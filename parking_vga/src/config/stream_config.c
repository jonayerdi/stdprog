/*
 * stream_config.c
 *
 *  Created on: 19 Dec 2017
 *      Author: Jon Ayerdi
 */

#include "config/stream_config.h"

#include "hal/stdio_stream.h"
#include "hal/file_stream.h"

#include <string.h>

int stream_config_get_input(input_stream_t *out, const char *filename)
{
	if(!strcmp(filename, "*"))
	{
		return stdio_input_stream(out);
	}
	else
	{
		return file_input_stream(out, filename);
	}
}

int stream_config_get_output(output_stream_t *out, const char *filename)
{
	if(!strcmp(filename, "*"))
	{
		return stdio_output_stream(out);
	}
	else
	{
		return file_output_stream(out, filename);
	}
}
