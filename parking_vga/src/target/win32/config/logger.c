/*************************************************************************************//**
* @file logger.c
* @brief Mapping of the default logger stream
* @author Jon Ayerdi
*****************************************************************************************/

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/
#include "config/logger.h"

#include "hal/stdio_stream.h"

/*--------------------------------------------------------------------------------------*/
/*                            			CONSTANTS               	                    */
/*--------------------------------------------------------------------------------------*/

static output_stream_t _logger;

/*--------------------------------------------------------------------------------------*/
/*                            PUBLIC FUNCTION DECLARATIONS                              */
/*--------------------------------------------------------------------------------------*/

void logger_init(void)
{
	stdio_output_stream(&_logger);
}

output_stream_t logger_get(void)
{
	return _logger;
}

/*****************************************************************************************
*                                        logger.c
*****************************************************************************************/
