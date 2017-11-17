/*
 * image.h
 *
 *  Created on: 17 Nov 2017
 *      Author: Jon Ayerdi
 */

#ifndef SRC_LIB_IMAGE_H_
#define SRC_LIB_IMAGE_H_

#include <stdint.h> /* uint32_t */

typedef uint32_t pixel_t;

#define PIXEL_BLACK ((pixel_t) 0x000000)
#define PIXEL_WHITE ((pixel_t) 0xFFFFFF)
#define PIXEL_RED ((pixel_t) 0xFF0000)
#define PIXEL_GREEN ((pixel_t) 0x00FF00)
#define PIXEL_BLUE ((pixel_t) 0x0000FF)

typedef struct image
{
	size_t x;
	size_t y;
	pixel_t *pixels;
} image_t;

image_t *image_alloc(size_t x, size_t y);
void image_free(image_t *image);

#endif /* SRC_LIB_IMAGE_H_ */
