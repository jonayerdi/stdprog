/*
 * image.c
 *
 *  Created on: 17 Nov 2017
 *      Author: Jon Ayerdi
 */

#include "lib/image.h"

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
