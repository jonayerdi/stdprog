/*************************************************************************************//**
* @file image.h
* @brief Defines an image format and basic functions to manipulate it
* @author Jon Ayerdi
*****************************************************************************************/
#ifndef SRC_LIB_IMAGE_H_
#define SRC_LIB_IMAGE_H_

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/
#include <stddef.h> /* size_t, NULL */
#include <stdint.h> /* uint32_t */

/*--------------------------------------------------------------------------------------*/
/*                                        TYPES                                         */
/*--------------------------------------------------------------------------------------*/
typedef uint32_t pixel_t; /* ARGB format */

typedef struct image
{
	size_t x;
	size_t y;
	size_t stride;
	pixel_t *pixels;
} image_t;

typedef enum compositing_mode
{
	compositing_mode_binary,
	compositing_mode_alpha
} compositing_mode_t;


/*--------------------------------------------------------------------------------------*/
/*                                        MACROS                                        */
/*--------------------------------------------------------------------------------------*/
#define PIXEL_ALPHA ((pixel_t) 0xFF000000)
#define PIXEL_INVISIBLE ((pixel_t) 0x00000000)
#define PIXEL_RED ((pixel_t) 0x00FF0000)
#define PIXEL_GREEN ((pixel_t) 0x0000FF00)
#define PIXEL_BLUE ((pixel_t) 0x000000FF)

/*--------------------------------------------------------------------------------------*/
/*                            PUBLIC FUNCTION DECLARATIONS                              */
/*--------------------------------------------------------------------------------------*/

/** @brief performs the selected compositing function of value into target.
 *  @param target pixel over which the compositing is performed.
 *  @param value the pixel that will be composited into the target.
 *  @param compositing mode (binary or alpha).
 */
void pixel_compositing(pixel_t *target, pixel_t value, compositing_mode_t mode);

/** @brief performs the binary compositing of value into target (invisible if alpha is 0, opaque otherwise).
 *  @param target pixel over which the binary compositing is performed.
 *  @param value the pixel that will be composited into the target.
 */
void pixel_binary_compositing(pixel_t *target, pixel_t value);

/** @brief performs the alpha compositing of value into target.
 *  @param target pixel over which the alpha compositing is performed.
 *  @param value the pixel that will be composited into the target.
 */
void pixel_alpha_compositing(pixel_t *target, pixel_t value);

/** @brief allocates a pixel buffer for the given image.
 *  @param image the image where the pixel buffer needs to be allocated.
 *  @param x width of the image.
 *  @param y height of the image.
 *  @return either 0 (OK) or MEMORY_ERROR
 */
int image_alloc(image_t *image, size_t x, size_t y);

/** @brief frees the allocated memory of an image previously initializad with image_alloc.
 *  @param image an image previously initializad with image_alloc.
 */
void image_free(image_t *image);

/*--------------------------------------------------------------------------------------*/
/*                             PUBLIC FUNCTION DEFINITIONS                              */
/*--------------------------------------------------------------------------------------*/

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

#endif /* SRC_LIB_IMAGE_H_ */
/****************************************************************************************
*                                       image.h
****************************************************************************************/
