/*************************************************************************************//**
* @file graphics_config.h
* @brief Mapping of graphics implementations to their names
* @author Jon Ayerdi
*****************************************************************************************/
#ifndef SRC_CONFIG_GRAPHICS_CONFIG_H_
#define SRC_CONFIG_GRAPHICS_CONFIG_H_

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/
#include "io/graphics.h"

/*--------------------------------------------------------------------------------------*/
/*                                        MACROS                                        */
/*--------------------------------------------------------------------------------------*/
#define GRAPHICS_CONFIG_DEVICE_NOT_FOUND -70
#define GRAPHICS_CONFIG_MODE_NOT_FOUND -71

/*--------------------------------------------------------------------------------------*/
/*                            PUBLIC FUNCTION DECLARATIONS                              */
/*--------------------------------------------------------------------------------------*/

/** @brief gets a graphics instance by name.
 *  @param output the graphics.
 *  @param device_name name of the graphics device.
 *  @param mode_name name of the graphics mode.
 *  @return 0 (OK) or nonzero (error).
 */
int graphics_config_get(graphics_t *output, const char *device_name, const char *mode_name);

#endif /* SRC_CONFIG_GRAPHICS_CONFIG_H_ */

/*****************************************************************************************
*                                   graphics_config.h
*****************************************************************************************/
