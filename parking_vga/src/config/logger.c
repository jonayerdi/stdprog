/*
 * logger.c
 *
 *  Created on: 20 Nov 2017
 *      Author: Jon Ayerdi
 */

#include "config/logger.h"

#include "hal/stdio_stream.h"

static output_stream_t _logger;

inline void logger_init(void)
{
	stdio_output_stream(&_logger);
}

inline output_stream_t logger_get(void)
{
	return _logger;
}
