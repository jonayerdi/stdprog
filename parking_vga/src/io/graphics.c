/*****************************************************************************************
*                                      graphics.c
******************************************************************************************
* AUTHOR: Jon Ayerdi
*
* DESCRIPTION: Interfaces for graphics output
*
*****************************************************************************************/

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/
#include "io/graphics.h"

#include "lib/font8x8.h"

#include <string.h> /* strlen */

/*--------------------------------------------------------------------------------------*/
/*                             PUBLIC FUNCTION DEFINITIONS                              */
/*--------------------------------------------------------------------------------------*/

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

	/* Get vbuffer */
	pixel_t *vbuffer = graphics.get_vbuffer(graphics.context);

	/* Set pixel color*/
	for(size_t pixel_y = 0 ; pixel_y < 8 ; pixel_y++)
		for(size_t character = 0 ; character < string_length ; character++)
			for(size_t pixel_x = 0 ; pixel_x < 8 ; pixel_x++)
			{
				size_t pos_x = x + (8 * character) + pixel_x;
				if(pos_x >= graphics.x) /* Check horizontal out of bounds */
				{
					character = string_length; /* Skip to next vertical position (outer loop) */
					break;
				}
				size_t pos_y = y + pixel_y;
				if(pos_y >= graphics.y) /* Check vertical out of bounds */
					return; /* Everything else is out of bounds */
				pixel_alpha_compositing(&vbuffer[(pos_y * graphics.x) + pos_x]
					,(font8x8[(size_t)string[character]][pixel_y] & (1 << pixel_x)) ? color : PIXEL_INVISIBLE);
			}
}

void graphics_draw_rect(graphics_t graphics, pixel_t color, size_t x1, size_t y1, size_t x2, size_t y2)
{
	/* Get vbuffer */
	pixel_t *vbuffer = graphics.get_vbuffer(graphics.context);

	/* Compute bounds */
	size_t end_x = x2 > graphics.x ? graphics.x : x2;
	size_t end_y = y2 > graphics.y ? graphics.y : y2;

	/* Set pixel color */
	for(size_t pixel_y = y1 ; pixel_y < end_y ; pixel_y++)
		for(size_t pixel_x = x1 ; pixel_x < end_x ; pixel_x++)
			pixel_alpha_compositing(&vbuffer[(pixel_y * graphics.x) + (pixel_x)], color);
}

void graphics_draw_circle(graphics_t graphics, pixel_t color, size_t x, size_t y, size_t radius)
{
	/* Precompute constants */
	size_t diameter = (radius * 2) + 1;
	int sradius = (int)radius;
	int radius2 = ((int)radius * (int)radius);

	/* Get vbuffer */
	pixel_t *vbuffer = graphics.get_vbuffer(graphics.context);

	/* Set pixel color */
	for(int pixel_y = 0 ; pixel_y < (int)diameter ; pixel_y++)
		for(int pixel_x = 0 ; pixel_x < (int)diameter ; pixel_x++)
		{
			int dist_x2 = ((pixel_x - sradius) * (pixel_x - sradius));
			int dist_y2 = ((pixel_y - sradius) * (pixel_y - sradius));
			pixel_alpha_compositing(&vbuffer[((y + pixel_y) * graphics.x) + (x + pixel_x)]
				, ((dist_x2 + dist_y2) <= radius2) ? color : PIXEL_INVISIBLE);
		}
}

inline void graphics_draw_image(graphics_t graphics, image_t image, size_t x, size_t y)
{
	/* Get vbuffer */
	pixel_t *vbuffer = graphics.get_vbuffer(graphics.context);

	/* Compute bounds */
	size_t end_x = (x + image.x) > graphics.x ? graphics.x - x : image.x;
	size_t end_y = (y + image.y) > graphics.y ? graphics.y - y : image.y;

	/* Set pixel color */
	for(size_t pixel_y = 0 ; pixel_y < end_y ; pixel_y++)
		for(size_t pixel_x = 0 ; pixel_x < end_x ; pixel_x++)
			vbuffer[((y + pixel_y) * graphics.x) + (x + pixel_x)] = image.pixels[((pixel_y) * image.stride) + (pixel_x)];
}

inline void graphics_render(graphics_t graphics)
{
	graphics.flush_vbuffer(graphics.context);
}

inline void graphics_destroy(graphics_t graphics)
{
	graphics.destroy(graphics.context);
}

/*****************************************************************************************
*                                      graphics.c
*****************************************************************************************/
