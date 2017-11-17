/*
 * stream.h
 *
 *  Created on: 16 Oct 2017
 *      Author: Jon Ayerdi
 */

#ifndef SRC_IO_STREAM_H_
#define SRC_IO_STREAM_H_

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define IS_DIGIT(N) ((N) >= '0' && (N) <= '9')
#define CHAR_TO_INT(C) ((C) - '0')

typedef struct _input_stream
{
	size_t (*read)(char *str, size_t size);
	void (*discard)(void);
} input_stream;

typedef struct _output_stream
{
	size_t (*write)(const char *str, size_t size);
	void (*flush)(void);
} output_stream;

uint64_t stream_str_to_uint(const char *str);
uint64_t stream_read_uint(input_stream *in);

void stream_write_str(output_stream *out, char *str);

#endif /* SRC_IO_STREAM_H_ */
