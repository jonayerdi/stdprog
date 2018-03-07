/*************************************************************************************//**
* @file graphics.c
* @brief Interfaces for graphics output
* @author Jon Ayerdi
*****************************************************************************************/

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/
#include "io/graphics.h"

#include "lib/font8x8.h"

#include <string.h> /* strlen */
#include <stdlib.h>

/*--------------------------------------------------------------------------------------*/
/*                             PUBLIC FUNCTION DEFINITIONS                              */
/*--------------------------------------------------------------------------------------*/

inline void graphics_draw_char8x8(graphics_t graphics, char character, pixel_t color, size_t x, size_t y, compositing_mode_t mode)
{
	char string[2];
	string[0] = character;
	string[1] = '\0';
	graphics_draw_string8x8(graphics, string, color, x, y, mode);
}

void graphics_draw_string8x8(graphics_t graphics, char *string, pixel_t color, size_t x, size_t y, compositing_mode_t mode)
{
	/* Precompute constants */
	size_t string_length = strlen(string);

	/* Get surface */
	image_t surface;
	if(graphics.get_surface(graphics.context, &surface, x, y, x + (8 * string_length) - 1, y + 8 - 1) != GRAPHICS_OK)
		return;

	/* Render into surface */
	for(size_t pixel_y = 0 ; pixel_y < 8 ; pixel_y++)
	{
		for(size_t character = 0 ; character < string_length ; character++)
		{
			for(size_t pixel_x = 0 ; pixel_x < 8 ; pixel_x++)
			{
				size_t pos_x = (8 * character) + pixel_x;
				size_t pos_y = pixel_y;
				pixel_compositing(
					&surface.pixels[(pos_y * surface.stride) + pos_x]
					, (font8x8[(size_t)string[character]][pixel_y] & (1 << pixel_x)) ? color : PIXEL_INVISIBLE
					, mode);
			}
		}
	}
}

void graphics_draw_rect(graphics_t graphics, pixel_t color, size_t x1, size_t y1, size_t x2, size_t y2, compositing_mode_t mode)
{
	/* Precompute constants */
	size_t len_x = x2 - x1;
	size_t len_y = y2 - y1;

	/* Get surface */
	image_t surface;
	if(graphics.get_surface(graphics.context, &surface, x1, y1, x2, y2) != GRAPHICS_OK)
		return;

	/* Render into surface */
	for(size_t pos_y = 0 ; pos_y < len_y ; pos_y++)
		for(size_t pos_x = 0 ; pos_x < len_x ; pos_x++)
			pixel_compositing(
					&surface.pixels[(pos_y * surface.stride) + pos_x]
					, color
					, mode);
}

void graphics_draw_circle(graphics_t graphics, pixel_t color, size_t x, size_t y, size_t radius, compositing_mode_t mode)
{
	/* Precompute constants */
	int sradius = (int)radius;
	int radius2 = ((int)radius * (int)radius);
	int diameter = (sradius * 2) + 1;

	/* Get surface */
	image_t surface;
	if(graphics.get_surface(graphics.context, &surface, x, y, x + diameter - 1, y + diameter - 1) != GRAPHICS_OK)
		return;

	/* Render into surface */
	for(int pos_y = 0 ; pos_y < diameter ; pos_y++)
	{
		for(int pos_x = 0 ; pos_x < diameter ; pos_x++)
		{
			int dist_x2 = ((pos_x - sradius) * (pos_x - sradius));
			int dist_y2 = ((pos_y - sradius) * (pos_y - sradius));
			pixel_compositing(
					&surface.pixels[(pos_y * surface.stride) + pos_x]
					, ((dist_x2 + dist_y2) <= radius2) ? color : PIXEL_INVISIBLE
					, mode);
		}
	}
}

inline void graphics_draw_image(graphics_t graphics, image_t image, size_t x, size_t y, compositing_mode_t mode)
{
	/* Get surface */
	image_t surface;
	if(graphics.get_surface(graphics.context, &surface, x, y, x + image.x - 1, y + image.y - 1) != GRAPHICS_OK)
		return;

	/* Render into surface */
	for(size_t pos_y = 0 ; pos_y < image.y ; pos_y++)
		for(size_t pos_x = 0 ; pos_x < image.x ; pos_x++)
			pixel_compositing(
					&surface.pixels[(pos_y * surface.stride) + pos_x]
					, image.pixels[((pos_y) * image.stride) + (pos_x)]
					, mode);
}

inline void graphics_update(graphics_t graphics, size_t x1, size_t y1, size_t x2, size_t y2)
{
	graphics.update(graphics.context, x1, y1, x2, y2);
}

inline void graphics_render(graphics_t graphics)
{
	graphics.render(graphics.context);
}

inline void graphics_destroy(graphics_t graphics)
{
	graphics.destroy(graphics.context);
}

/*****************************************************************************************
*                                      graphics.c
*****************************************************************************************/
