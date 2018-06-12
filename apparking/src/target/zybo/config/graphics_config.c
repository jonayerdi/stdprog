/*************************************************************************************//**
* @file graphics_config.c
* @brief Mapping of graphics implementations to their names
* @author Jon Ayerdi
*****************************************************************************************/

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/
#include "config/graphics_config.h"


#include <string.h>

/*--------------------------------------------------------------------------------------*/
/*                                        MACROS                                        */
/*--------------------------------------------------------------------------------------*/

/* VGA or HDMI */
#define VGA_GRAPHICS_DISPLAY_NOT_HDMI DISPLAY_NOT_HDMI
#define VGA_GRAPHICS_DISPLAY_HDMI DISPLAY_HDMI

/* VDMA */
#define VGA_GRAPHICS_VDMA_0_ID XPAR_AXIVDMA_0_DEVICE_ID
#define VGA_GRAPHICS_VDMA_1_ID XPAR_AXIVDMA_1_DEVICE_ID

#define VGA_GRAPHICS_DISPCTRL_0_BASEADDR XPAR_AXI_DISPCTRL_0_S_AXI_BASEADDR
#define VGA_GRAPHICS_DISPCTRL_1_BASEADDR XPAR_AXI_DISPCTRL_1_S_AXI_BASEADDR

/* VideoMode macros */
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

/* Utils */
#define GRAPHICS_CONFIG_MAP_MODE(NAME,VALUE) { if(!strcmp(mode_name, NAME)) { mode = VALUE; } }
#define GRAPHICS_CONFIG_MAP_DEVICE(NAME,VALUE) { if(!strcmp(device_name, NAME)) { vga_graphics_config_t _config = VALUE; config = _config; } }

/*--------------------------------------------------------------------------------------*/
/*                            PUBLIC FUNCTION DECLARATIONS                              */
/*--------------------------------------------------------------------------------------*/

int graphics_config_get(graphics_t *output, const char *device_name, const char *mode_name)
{
	return GRAPHICS_CONFIG_MODE_NOT_FOUND;
}

/*****************************************************************************************
*                                   graphics_config.c
*****************************************************************************************/
