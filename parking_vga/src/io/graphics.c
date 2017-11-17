/*
 * graphics.c
 *
 *  Created on: 15 Nov 2017
 *      Author: Jon Ayerdi
 */

#include "io/graphics.h"

#include "lib/font8x8.h"

#include <string.h> /* strlen */

static pixel_t _bigrect[GRAPHICS_MAX_RECT];

inline void graphics_draw_char8x8(graphics_t graphics, char character, pixel_t color, size_t x, size_t y)
{
	char string[2];
	string[0] = character;
	string[1] = '\0';
	graphics_draw_string8x8(graphics, string, color, x, y);
}

void graphics_draw_string8x8(graphics_t graphics, char *string, pixel_t color, size_t x, size_t y)
{
	/* Declare variables */
	size_t string_length = strlen(string);
	char *bitmask;

	/* Create image for string */
	image_t image;
	image.x = 8 * string_length;
	image.y = 8;
	image.pixels = &_bigrect;

	/* Set string pixel color and bitmask*/
	for(size_t i = 0 ; i < 8 * 8 * string_length ; i++)
	{
		_bigrect[i] = color;
		//TODO bitmask
	}

	/* Bitblt string into graphics */
	graphics.bitblt(graphics.context, image, bitmask, x, y);
}

void graphics_draw_rect(graphics_t graphics, pixel_t color, size_t x1, size_t x2, size_t y1, size_t y2)
{
	/* Create image for rect */
	image_t rect;
	rect.x = x2 - x1;
	rect.y = y2 - y1;
	rect.pixels = &_bigrect;

	/* Set rect pixel color */
	for(size_t i = 0 ; i < x * y ; i++)
		_bigrect[i] = color;

	/* Bitblt rect into graphics */
	graphics.bitblt(graphics.context, rect, GRAPHICS_BITMASK_NONE, x1, y1);
}

inline void graphics_draw_image(graphics_t graphics, image_t image, size_t x, size_t y)
{
	graphics.bitblt(graphics.context, image, GRAPHICS_BITMASK_NONE, x, y);
}

inline void graphics_render(graphics_t graphics)
{
	graphics.flush(graphics.context);
}
