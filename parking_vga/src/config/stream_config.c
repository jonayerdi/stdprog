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

#include <string.h>

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

/*****************************************************************************************
*                                   stream_config.c
*****************************************************************************************/
