/*************************************************************************************//**
* @file graphics_config.c
* @brief Mapping of graphics implementations to their names
* @author Jon Ayerdi
*****************************************************************************************/

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/
#include "config/graphics_config.h"

#include <string.h>

/*--------------------------------------------------------------------------------------*/
/*                                        MACROS                                        */
/*--------------------------------------------------------------------------------------*/

/* Utils */
#define GRAPHICS_CONFIG_MAP_MODE(NAME,VALUE) { if(!strcmp(mode_name, NAME)) { mode = VALUE; } }
#define GRAPHICS_CONFIG_MAP_DEVICE(NAME,VALUE) { if(!strcmp(device_name, NAME)) { vga_graphics_config_t _config = VALUE; config = _config; } }

/*--------------------------------------------------------------------------------------*/
/*                            PUBLIC FUNCTION DECLARATIONS                              */
/*--------------------------------------------------------------------------------------*/

int graphics_config_get(graphics_t *output, const char *device_name, const char *mode_name)
{
	return GRAPHICS_CONFIG_MODE_NOT_FOUND;
}

/*****************************************************************************************
*                                   graphics_config.c
*****************************************************************************************/
