/*************************************************************************************//**
* @file graphics.h
* @brief Interfaces for graphics output
* @author Jon Ayerdi
*****************************************************************************************/
#ifndef SRC_IO_GRAPHICS_H_
#define SRC_IO_GRAPHICS_H_

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/
#include <stddef.h> /* size_t */

#include "lib/image.h"

/*--------------------------------------------------------------------------------------*/
/*                                        MACROS                                        */
/*--------------------------------------------------------------------------------------*/
#define GRAPHICS_OK 0x00
#define GRAPHICS_ERROR_OUT_OF_BOUNDS 0x01

/*--------------------------------------------------------------------------------------*/
/*                                        TYPES                                         */
/*--------------------------------------------------------------------------------------*/
typedef struct graphics
{
	size_t x;
	size_t y;
	int (*get_surface)(void *context, image_t *surface, size_t x1, size_t y1, size_t x2, size_t y2);
	void (*update)(void *context, size_t x1, size_t y1, size_t x2, size_t y2);
	void (*render)(void *context);
	void (*destroy)(void *context);
	void *context;
} graphics_t;

/*--------------------------------------------------------------------------------------*/
/*                            PUBLIC FUNCTION DECLARATIONS                              */
/*--------------------------------------------------------------------------------------*/

/** @brief draws the given character into the given graphics.
 *  @param graphics the target graphics.
 *  @param character character to draw
 *  @param color color of the character
 *  @param x x position of the character
 *  @param y y position of the character
 *  @param mode compositing_mode of the renderer
 */
void graphics_draw_char8x8(graphics_t graphics, char character, pixel_t color, size_t x, size_t y, compositing_mode_t mode);
/** @brief draws the given string into the given graphics.
 *  @param graphics the target graphics.
 *  @param string string to draw
 *  @param color color of the string
 *  @param x x position of the string
 *  @param y y position of the string
 *  @param mode compositing_mode of the renderer
 */
void graphics_draw_string8x8(graphics_t graphics, char *string, pixel_t color, size_t x, size_t y, compositing_mode_t mode);
/** @brief draws a rectangle into the given graphics.
 *  @param graphics the target graphics.
 *  @param color color of the rectangle
 *  @param x1 starting x position of the rectangle
 *  @param y1 starting y position of the rectangle
 *  @param x2 ending x position of the rectangle
 *  @param y2 ending y position of the rectangle
 *  @param mode compositing_mode of the renderer
 */
void graphics_draw_rect(graphics_t graphics, pixel_t color, size_t x1, size_t y1, size_t x2, size_t y2, compositing_mode_t mode);
/** @brief draws a circle into the given graphics.
 *  @param graphics the target graphics.
 *  @param color color of the circle
 *  @param x x position of the circle
 *  @param y y position of the circle
 *  @param radius radius of the circle
 *  @param mode compositing_mode of the renderer
 */
void graphics_draw_circle(graphics_t graphics, pixel_t color, size_t x, size_t y, size_t radius, compositing_mode_t mode);
/** @brief draws the given image into the given graphics.
 *  @param graphics the target graphics.
 *  @param image image to draw
 *  @param x x position of the image
 *  @param y y position of the image
 *  @param mode compositing_mode of the renderer
 */
void graphics_draw_image(graphics_t graphics, image_t image, size_t x, size_t y, compositing_mode_t mode);
/** @brief updates the specified rectangular area of the graphics.
 *  @param x1 starting x position of the rectangle
 *  @param y1 starting y position of the rectangle
 *  @param x2 ending x position of the rectangle
 *  @param y2 ending y position of the rectangle
 *  @param graphics the target graphics.
 */
void graphics_update(graphics_t graphics, size_t x1, size_t y1, size_t x2, size_t y2);
/** @brief renders the given graphics to the screen.
 *  @param graphics the target graphics.
 */
void graphics_render(graphics_t graphics);
/** @brief destroys the given graphics.
 *  @param graphics the target graphics.
 */
void graphics_destroy(graphics_t graphics);

#endif /* SRC_IO_GRAPHICS_H_ */

/*****************************************************************************************
*                                      graphics.h
*****************************************************************************************/
