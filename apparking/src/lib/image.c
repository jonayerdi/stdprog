/*************************************************************************************//**
* @file image.c
* @brief Defines an image format and basic functions to manipulate it
* @author Jon Ayerdi
*****************************************************************************************/

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/
#include "lib/image.h"

#include "io/memory.h"

/*--------------------------------------------------------------------------------------*/
/*                             PUBLIC FUNCTION DEFINITIONS                              */
/*--------------------------------------------------------------------------------------*/

#ifndef _MSC_VER

inline void pixel_compositing(pixel_t *target, pixel_t value, compositing_mode_t mode)
{
	switch(mode)
	{
		case compositing_mode_binary:
			pixel_binary_compositing(target, value);
			break;
		case compositing_mode_alpha:
			pixel_alpha_compositing(target, value);
			break;
	}
}

inline void pixel_binary_compositing(pixel_t *target, pixel_t value)
{
	if(value & PIXEL_ALPHA)
		*target = value;
}

inline void pixel_alpha_compositing(pixel_t *target, pixel_t value)
{
	pixel_t oldvalue = *target;
	double alpha = ((double)((value & PIXEL_ALPHA)>>24)) / 255.0; /* 0.0 to 1.0 */
	double oldalpha = 1 - alpha;
	char r = (char)((((double)((oldvalue & PIXEL_RED)>>16)) * oldalpha) + (((double)((value & PIXEL_RED)>>16)) * alpha));
	char g = (char)((((double)((oldvalue & PIXEL_GREEN)>>8)) * oldalpha) + (((double)((value & PIXEL_GREEN)>>8)) * alpha));
	char b = (char)((((double)((oldvalue & PIXEL_BLUE))) * oldalpha) + (((double)((value & PIXEL_BLUE))) * alpha));
	*target = (((pixel_t)r<<16) + ((pixel_t)g<<8) + ((pixel_t)b));
}

#endif /* _MSC_VER */

int image_alloc(image_t *image, size_t x, size_t y)
{
	image->x = x;
	image->y = y;
	image->stride = x;
	image->pixels = (pixel_t *)memory_allocate(sizeof(pixel_t) * x * y);
	if(image->pixels == NULL)
		return MEMORY_ERROR;
	return 0;
}

void image_free(image_t *image)
{
	memory_free(image->pixels);
}

/****************************************************************************************
*                                       image.c
****************************************************************************************/
