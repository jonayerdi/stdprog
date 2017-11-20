/*
 * stdio_stream.c
 *
 *  Created on: 17 Nov 2017
 *      Author: Jon Ayerdi
 */

#include "io/stream.h"

#include <stdio.h>

static size_t _read(char *str, size_t size, void *context);
static size_t _write(const char *str, size_t size, void *context);
static void _discard(void *context);
static void _flush(void *context);
static void _close(void *context);

static size_t _read(char *str, size_t size, void *context)
{
	return fread(str, 1, size, stdin);
}

static size_t _write(const char *str, size_t size, void *context)
{
	return fwrite(str, 1, size, stdout);
}

static void _discard(void *context)
{
	while(stdin->_r)
		getchar();
}

static void _flush(void *context)
{
	fflush(stdin);
}

static void _close(void *context)
{
	/* Nothing to do */
}

int stdio_input_stream(input_stream_t *stream)
{
	stream->read = _read;
	stream->discard = _discard;
	stream->close = _close;
	return 0;
}

int stdio_output_stream(output_stream_t *stream)
{
	stream->write = _write;
	stream->flush = _flush;
	stream->close = _close;
	return 0;
}
