/*****************************************************************************************
*                                      file_stream.c
******************************************************************************************
* AUTHOR: Jon Ayerdi
*
* DESCRIPTION: Implementation of file streams for the ZYBO 7000 board
*
*****************************************************************************************/

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/

#include "hal/file_stream.h"

#include "io/memory.h"

#include <ff.h>

/*--------------------------------------------------------------------------------------*/
/*                            		 	 CONSTANTS                                      */
/*--------------------------------------------------------------------------------------*/

static FATFS filesystem = {.fs_type = 0};

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
	FIL *file = (FIL *)context;
	size_t read;
	f_read(file, str, size, &read);
	return read;
}

static size_t _write(const char *str, size_t size, void *context)
{
	FIL *file = (FIL *)context;
	size_t written;
	f_write(file, str, size, &written);
	return written;
}

static void _discard(void *context)
{
	/* Hopefully unused */
}

static void _flush(void *context)
{
	FIL *file = (FIL *)context;
	f_sync(file);
}

static void _close(void *context)
{
	FIL *file = (FIL *)context;
	f_close(file);
	memory_free(file);
}

/*--------------------------------------------------------------------------------------*/
/*                             PUBLIC FUNCTION DEFINITIONS                              */
/*--------------------------------------------------------------------------------------*/

int file_input_stream(input_stream_t *stream, const char *filename)
{
	FIL *file = (FIL *)memory_allocate(sizeof(FIL));
	if(file == NULL)
		return MEMORY_ERROR;
	FRESULT result;
	/* Mount filesystem if needed */
	if(filesystem.fs_type == 0)
	{
		result = f_mount(&filesystem, "", 0);
		if(result != FR_OK)
		{
			memory_free(file);
			return result;
		}
	}
	/* Open file */
	result = f_open(file, filename, FA_READ | FA_OPEN_EXISTING);
	if(result != FR_OK)
	{
		memory_free(file);
		return result;
	}
	/* Implement input_stream_t */
	stream->read = _read;
	stream->discard = _discard;
	stream->close = _close;
	stream->context = file;
	return 0;
}

int file_output_stream(output_stream_t *stream, const char *filename)
{
	FIL *file = (FIL *)memory_allocate(sizeof(FIL));
	if(file == NULL)
		return MEMORY_ERROR;
	FRESULT result;
	/* Mount filesystem if needed */
	if(filesystem.fs_type == 0)
	{
		result = f_mount(&filesystem, "", 0);
		if(result != FR_OK)
		{
			memory_free(file);
			return result;
		}
	}
	/* Open file */
	result = f_open(file, filename, FA_WRITE | FA_CREATE_ALWAYS);
	if(result != FR_OK)
	{
		memory_free(file);
		return result;
	}
	/* Implement output_stream_t */
	stream->write = _write;
	stream->flush = _flush;
	stream->close = _close;
	stream->context = file;
	return 0;
}

/*****************************************************************************************
*                                      file_stream.c
*****************************************************************************************/
