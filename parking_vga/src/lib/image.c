/*
 * image.c
 *
 *  Created on: 17 Nov 2017
 *      Author: Jon Ayerdi
 */

#include "lib/image.h"

inline void pixel_alpha_compositing(pixel_t *target, pixel_t value)
{
	pixel_t oldvalue = *target;
	double alpha = ((double)(value & PIXEL_ALPHA)) / 255.0; /* 0.0 to 1.0 */
	double oldalpha = 1 - alpha;
	char r = (char)((((double)((oldvalue & PIXEL_RED)>>16)) * oldalpha) + (((double)((value & PIXEL_RED)>>16)) * alpha));
	char g = (char)((((double)((oldvalue & PIXEL_GREEN)>>8)) * oldalpha) + (((double)((value & PIXEL_GREEN)>>8)) * alpha));
	char b = (char)((((double)((oldvalue & PIXEL_BLUE))) * oldalpha) + (((double)((value & PIXEL_BLUE))) * alpha));
	*target = (((pixel_t)r<<16) + ((pixel_t)g<<8) + ((pixel_t)b));
}

inline image_t *image_alloc(size_t x, size_t y)
{
	image_t * image = (image_t *)malloc(sizeof(image_t));
	image->pixels = (pixel_t *)malloc(sizeof(pixel_t) * x * y);
}

inline void image_free(image_t *image)
{
	free(image->pixels);
	free(image);
}
