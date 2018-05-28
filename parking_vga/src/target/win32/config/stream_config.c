/*************************************************************************************//**
* @file stream_config.c
* @brief Mapping of stream implementations to their names
* @author Jon Ayerdi
*****************************************************************************************/

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/
#include "config/stream_config.h"

#include "hal/stdio_stream.h"
#include "hal/file_stream.h"
#include "hal/socket_stream.h"

#include <string.h>
#include <stddef.h>

/*--------------------------------------------------------------------------------------*/
/*                            PUBLIC FUNCTION DECLARATIONS                              */
/*--------------------------------------------------------------------------------------*/

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

int stream_config_get_iostream(input_stream_t *istream, output_stream_t *ostream, const char *filename)
{
	char address[64] = {0};
	char port[16] = {0};
	const char *separator = strchr(filename, ':');
	if(separator)
	{
		size_t pos = (size_t)(separator - filename);
		memcpy(address, filename, pos);
		memcpy(port, filename + pos + 1, strlen(filename) - (pos + 1));
		return socket_stream(istream, ostream, address, port);
	}
	else return -13;
}

/*****************************************************************************************
*                                   stream_config.c
*****************************************************************************************/
