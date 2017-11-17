/*
 * stream.h
 *
 *  Created on: 15 Nov 2017
 *      Author: Jon Ayerdi
 */

#ifndef SRC_IO_STREAM_H_
#define SRC_IO_STREAM_H_

#include <stddef.h> /* size_t */

typedef struct input_stream
{
	size_t (*read)(char *str, size_t size, void *context);
	void (*discard)(void *context);
	void (*close)(void *context);
	void *context;
} input_stream_t;

typedef struct output_stream
{
	size_t (*write)(const char *str, size_t size, void *context);
	void (*flush)(void *context);
	void (*close)(void *context);
	void *context;
} output_stream_t;

void stream_close_input(input_stream_t stream);
void stream_close_output(output_stream_t stream);

void stream_discard(input_stream_t stream);
void stream_flush(output_stream_t stream);

size_t stream_read(input_stream_t stream, char *output, size_t length);
size_t stream_write(output_stream_t stream, const char *input, size_t length);

size_t stream_read_line(input_stream_t stream, char *output, size_t length);
size_t stream_write_string(output_stream_t stream, const char *input);

#endif /* SRC_IO_STREAM_H_ */
