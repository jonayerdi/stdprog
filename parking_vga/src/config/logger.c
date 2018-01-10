/*****************************************************************************************
*                                        logger.c
******************************************************************************************
* AUTHOR: Jon Ayerdi
*
* DESCRIPTION: Mapping of the default logger stream
*
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

inline void logger_init(void)
{
	stdio_output_stream(&_logger);
}

inline output_stream_t logger_get(void)
{
	return _logger;
}

/*****************************************************************************************
*                                        logger.c
*****************************************************************************************/
