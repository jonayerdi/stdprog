/*************************************************************************************//**
* @file stream.h
* @brief Interfaces for input and output data streams
* @author Jon Ayerdi
*****************************************************************************************/
#ifndef SRC_IO_STREAM_H_
#define SRC_IO_STREAM_H_

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/
#include <stddef.h> /* size_t */

/*--------------------------------------------------------------------------------------*/
/*                                        TYPES                                         */
/*--------------------------------------------------------------------------------------*/

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

/*--------------------------------------------------------------------------------------*/
/*                           PUBLIC FUNCTION DECLARATIONS                               */
/*--------------------------------------------------------------------------------------*/

/** @brief closes the given stream.
 *  @param stream the stream to close.
 */
void stream_close_input(input_stream_t stream);
/** @brief closes the given stream.
 *  @param stream the stream to close.
 */
void stream_close_output(output_stream_t stream);

/** @brief discards all input from the given stream.
 *  @param stream the stream to discard.
 */
void stream_discard(input_stream_t stream);
/** @brief flushes all the output of the given stream.
 *  @param stream the stream to flush.
 */
void stream_flush(output_stream_t stream);

/** @brief reads bytes from the given stream.
 *  @param stream the stream to read.
 *  @param output buffer to write the data.
 *  @param length number of bytes to read.
 *  @return number of bytes read.
 */
size_t stream_read(input_stream_t stream, char *output, size_t length);
/** @brief writes bytes to the given stream.
 *  @param stream the stream to write.
 *  @param input buffer to read the data.
 *  @param length number of bytes to write.
 *  @return number of bytes written.
 */
size_t stream_write(output_stream_t stream, const char *input, size_t length);

/** @brief reads a line from the given stream.
 *  @param stream the stream to read.
 *  @param output buffer to write the data.
 *  @param length max number of bytes to read.
 *  @return number of bytes read.
 */
size_t stream_read_line(input_stream_t stream, char *output, size_t length);
/** @brief writes a string to the given stream.
 *  @param stream the stream to write.
 *  @param input buffer to read the data.
 *  @return number of bytes written.
 */
size_t stream_write_string(output_stream_t stream, const char *input);

#endif /* SRC_IO_STREAM_H_ */

/*****************************************************************************************
*                                         stream.h
*****************************************************************************************/
