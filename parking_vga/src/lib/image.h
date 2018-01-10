/*****************************************************************************************
*                                         image.h
******************************************************************************************
* AUTHOR: Jon Ayerdi
*
* DESCRIPTION: Defines an image format and basic functions to manipulate it
*
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

/*--------------------------------------------------------------------------------------*/
/*                                        MACROS                                        */
/*--------------------------------------------------------------------------------------*/
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

/*--------------------------------------------------------------------------------------*/
/*                                  PUBLIC FUNCTIONS                                    */
/*--------------------------------------------------------------------------------------*/

/** @brief performs the alpha compositing of value into target.
 *  @param target pixel over which the alpha compositing is performed.
 *  @param value the pixel that will be composited into the target.
 */
void pixel_alpha_compositing(pixel_t *target, pixel_t value);

/** @brief allocates a pixel buffer for the given image.
 *  @param image the image where the pixel buffer needs to be allocated.
 *  @param x width of the image.
 *  @param y height of the image.
 */
int image_alloc(image_t *image, size_t x, size_t y);
/** @brief frees the allocated memory of an image previously initializad with image_alloc.
 *  @param image an image previously initializad with image_alloc.
 */
void image_free(image_t *image);

#endif /* SRC_LIB_IMAGE_H_ */
/****************************************************************************************/
/*                                       image.h
/****************************************************************************************/
