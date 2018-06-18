/*************************************************************************************//**
* @file window_graphics.h
* @brief Implementation of graphics with SDL windows
* @author Jon Ayerdi
*****************************************************************************************/
#ifndef SRC_HAL_WINDOW_GRAPHICS_H_
#define SRC_HAL_WINDOW_GRAPHICS_H_

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/

#include "io/graphics.h"

#include "SDL.h"

/*--------------------------------------------------------------------------------------*/
/*                                        TYPES                                         */
/*--------------------------------------------------------------------------------------*/

typedef struct window_graphics_config
{
    char *title;
    size_t x;
	size_t y;
} window_graphics_config_t;

typedef struct window_graphics
{
	window_graphics_config_t config;
    SDL_Window *window;
    pixel_t *vbuffer;
} window_graphics_t;

/*--------------------------------------------------------------------------------------*/
/*                            PUBLIC FUNCTION DECLARATIONS                              */
/*--------------------------------------------------------------------------------------*/

/** @brief initializes the graphics.
 *  @param output the graphics.
 *  @param config the configuration for the graphics
 *  @return 0 (OK) or nonzero (error).
 */
int window_graphics_init(graphics_t *output, window_graphics_config_t config);

#endif /* SRC_HAL_WINDOW_GRAPHICS_H_ */

/*****************************************************************************************
*                                      window_graphics.h
*****************************************************************************************/
