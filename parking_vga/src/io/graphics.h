/*
 * graphics.h
 *
 *  Created on: 15 Nov 2017
 *      Author: Jon Ayerdi
 */

#ifndef SRC_IO_GRAPHICS_H_
#define SRC_IO_GRAPHICS_H_

#include <stddef.h> /* size_t */

#include "lib/image.h"

typedef struct graphics
{
	size_t x;
	size_t y;
	pixel_t *(*get_vbuffer)(void *context);
	void (*flush_vbuffer)(void *context);
	void (*destroy)(void *context);
	void *context;
} graphics_t;

#endif /* SRC_IO_GRAPHICS_H_ */

void graphics_draw_char8x8(graphics_t graphics, char character, pixel_t color, size_t x, size_t y);
void graphics_draw_string8x8(graphics_t graphics, char *string, pixel_t color, size_t x, size_t y);
void graphics_draw_rect(graphics_t graphics, pixel_t color, size_t x1, size_t y1, size_t x2, size_t y2);
void graphics_draw_circle(graphics_t graphics, pixel_t color, size_t x, size_t y, size_t radius);
void graphics_draw_image(graphics_t graphics, image_t image, size_t x, size_t y);
void graphics_render(graphics_t graphics);
void graphics_destroy(graphics_t graphics);
