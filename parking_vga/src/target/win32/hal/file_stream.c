/*************************************************************************************//**
* @file file_stream.c
* @brief Implementation of file streams via stdin
* @author Jon Ayerdi
*****************************************************************************************/

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/

#include "hal/file_stream.h"

#include <stdio.h>

/*--------------------------------------------------------------------------------------*/
/*                            		 PRIVATE FUNCTIONS                                  */
/*--------------------------------------------------------------------------------------*/

static size_t _read(char *str, size_t size, void *context);
static size_t _write(const char *str, size_t size, void *context);
static void _discard(void *context);
static void _flush(void *context);
static void _close(void *context);

static size_t _read(char *str, size_t size, void *context)
{
	FILE *file = (FILE *)context;
	return fread(str, 1, size, file);
}

static size_t _write(const char *str, size_t size, void *context)
{
	FILE *file = (FILE *)context;
	return fwrite(str, 1, size, file);
}

static void _discard(void *context)
{
	/* Hopefully unused */
}

static void _flush(void *context)
{
	FILE *file = (FILE *)context;
	fflush(file);
}

static void _close(void *context)
{
	FILE *file = (FILE *)context;
	fclose(file);
}

/*--------------------------------------------------------------------------------------*/
/*                             PUBLIC FUNCTION DEFINITIONS                              */
/*--------------------------------------------------------------------------------------*/

int file_input_stream(input_stream_t *stream, const char *filename)
{
	FILE *file = fopen(filename, "rb");
	if(file == NULL)
		return 1;
	/* Implement input_stream_t */
	stream->read = _read;
	stream->discard = _discard;
	stream->close = _close;
	stream->context = file;
	return 0;
}

int file_output_stream(output_stream_t *stream, const char *filename)
{
	FILE *file = fopen(filename, "wb");
	if(file == NULL)
		return 1;
	/* Implement input_stream_t */
	stream->read = _read;
	stream->discard = _discard;
	stream->close = _close;
	stream->context = file;
	return 0;
}

/*****************************************************************************************
*                                      file_stream.c
*****************************************************************************************/
