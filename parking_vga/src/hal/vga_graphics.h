/*
 * vga_graphics.h
 *
 *  Created on: 17 Nov 2017
 *      Author: Jon Ayerdi
 */

#ifndef SRC_HAL_VGA_GRAPHICS_H_
#define SRC_HAL_VGA_GRAPHICS_H_

#include <xparameters.h>

#include "hal/vga/vga_modes.h"
#include "hal/vga/display_ctrl.h"

#include "io/graphics.h"

#define VGA_GRAPHICS_DISPLAY_NOT_HDMI DISPLAY_NOT_HDMI
#define VGA_GRAPHICS_DISPLAY_HDMI DISPLAY_HDMI

#define VGA_GRAPHICS_VDMA_0_ID XPAR_AXIVDMA_0_DEVICE_ID
#define VGA_GRAPHICS_VDMA_1_ID XPAR_AXIVDMA_1_DEVICE_ID

#define VGA_GRAPHICS_DISPCTRL_0_BASEADDR XPAR_AXI_DISPCTRL_0_S_AXI_BASEADDR
#define VGA_GRAPHICS_DISPCTRL_1_BASEADDR XPAR_AXI_DISPCTRL_1_S_AXI_BASEADDR

#define VGA_GRAPHICS_VGA_CONFIG(MODE) \
{ \
	.mode = MODE, \
	.hdmi = VGA_GRAPHICS_DISPLAY_NOT_HDMI, \
	.vdma_id = VGA_GRAPHICS_VDMA_0_ID, \
	.display_ctrl_address = VGA_GRAPHICS_DISPCTRL_0_BASEADDR \
}

#define VGA_GRAPHICS_HDMI_CONFIG(MODE) \
{ \
	.mode = MODE, \
	.hdmi = VGA_GRAPHICS_DISPLAY_HDMI, \
	.vdma_id = VGA_GRAPHICS_VDMA_1_ID, \
	.display_ctrl_address = VGA_GRAPHICS_DISPCTRL_1_BASEADDR \
}

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

int vga_graphics_init(vga_graphics_config_t config, graphics_t *output);

#endif /* SRC_HAL_VGA_GRAPHICS_H_ */
