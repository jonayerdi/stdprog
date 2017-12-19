/*
 * graphics_config.h
 *
 *  Created on: 19 Dec 2017
 *      Author: Jon Ayerdi
 */

#ifndef SRC_CONFIG_GRAPHICS_CONFIG_H_
#define SRC_CONFIG_GRAPHICS_CONFIG_H_

#include "hal/vga_graphics.h"

#define GRAPHICS_CONFIG_DEVICE_NOT_FOUND -70
#define GRAPHICS_CONFIG_MODE_NOT_FOUND -71

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

int graphics_config_get(graphics_t *output, const char *device_name, const char *mode_name);

#endif /* SRC_CONFIG_GRAPHICS_CONFIG_H_ */
