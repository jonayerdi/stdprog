/*
 * image.h
 *
 *  Created on: 17 Nov 2017
 *      Author: Jon Ayerdi
 */

#ifndef SRC_LIB_IMAGE_H_
#define SRC_LIB_IMAGE_H_

#include <stddef.h> /* size_t */
#include <stdint.h> /* uint32_t */

typedef uint32_t pixel_t; /* ARGB format */

#define PIXEL_ALPHA ((pixel_t) 0xFF000000)
#define PIXEL_INVISIBLE ((pixel_t) 0x00000000)
#define PIXEL_RED ((pixel_t) 0x00FF0000)
#define PIXEL_GREEN ((pixel_t) 0x0000FF00)
#define PIXEL_BLUE ((pixel_t) 0x000000FF)

typedef struct image
{
	size_t x;
	size_t y;
	size_t stride;
	pixel_t *pixels;
} image_t;

void pixel_alpha_compositing(pixel_t *target, pixel_t value);

image_t *image_alloc(size_t x, size_t y);
void image_free(image_t *image);

#endif /* SRC_LIB_IMAGE_H_ */
