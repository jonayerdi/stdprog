/*****************************************************************************************
*                                      vga_graphics.h
******************************************************************************************
* AUTHOR: Jon Ayerdi
*
* DESCRIPTION: Implementation of VGA graphics for the ZYBO 7000 board
*
*****************************************************************************************/
#ifndef SRC_HAL_VGA_GRAPHICS_H_
#define SRC_HAL_VGA_GRAPHICS_H_

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/

#include <xparameters.h>

#include "hal/vga/vga_modes.h"
#include "hal/vga/display_ctrl.h"

#include "io/graphics.h"

/*--------------------------------------------------------------------------------------*/
/*                                        TYPES                                         */
/*--------------------------------------------------------------------------------------*/

typedef struct vga_graphics_config
{
	VideoMode mode;
	int hdmi;
	u16 vdma_id;
	u32 display_ctrl_address;
} vga_graphics_config_t;

typedef struct vga_graphics
{
	DisplayCtrl driver;
	VideoMode mode;
	pixel_t *vbuffer;
	pixel_t **framebuffers;
	char current_frame;
} vga_graphics_t;

/*--------------------------------------------------------------------------------------*/
/*                            PUBLIC FUNCTION DECLARATIONS                              */
/*--------------------------------------------------------------------------------------*/

/** @brief initializes the graphics.
 *  @param output the graphics.
 *  @param config the configuration for the graphics
 *  @return 0 (OK) or nonzero (error).
 */
int vga_graphics_init(graphics_t *output, vga_graphics_config_t config);

#endif /* SRC_HAL_VGA_GRAPHICS_H_ */

/*****************************************************************************************
*                                      vga_graphics.h
*****************************************************************************************/
