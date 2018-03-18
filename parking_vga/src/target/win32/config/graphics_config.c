/*************************************************************************************//**
* @file graphics_config.c
* @brief Mapping of graphics implementations to their names
* @author Jon Ayerdi
*****************************************************************************************/

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/
#include "config/graphics_config.h"

#include "hal/window_graphics.h"

#include <string.h>

/*--------------------------------------------------------------------------------------*/
/*                                        MACROS                                        */
/*--------------------------------------------------------------------------------------*/

/* Utils */
#define GRAPHICS_CONFIG_MAP_MODE(NAME,X,Y) { if(!strcmp(mode_name, NAME)) { config.x = X; config.y = Y; } }

/*--------------------------------------------------------------------------------------*/
/*                            PUBLIC FUNCTION DECLARATIONS                              */
/*--------------------------------------------------------------------------------------*/

int graphics_config_get(graphics_t *output, const char *device_name, const char *mode_name)
{
	window_graphics_config_t config = { .title = "", .x = 0, .y = 0 };
	GRAPHICS_CONFIG_MAP_MODE("640x480", 640, 480);
	GRAPHICS_CONFIG_MAP_MODE("800x600", 800, 600);
	GRAPHICS_CONFIG_MAP_MODE("1280x720", 1280, 720);
	GRAPHICS_CONFIG_MAP_MODE("1280x1024", 1280, 1024);
	GRAPHICS_CONFIG_MAP_MODE("1920x1080", 1920, 1080);
	if(config.x != 0)
	{
		return window_graphics_init(output, config);
	}
	return GRAPHICS_CONFIG_MODE_NOT_FOUND;
}

/*****************************************************************************************
*                                   graphics_config.c
*****************************************************************************************/
