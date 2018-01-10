/*****************************************************************************************
*                                   graphics_config.c
******************************************************************************************
* AUTHOR: Jon Ayerdi
*
* DESCRIPTION: Mapping of graphics implementations to their names
*
*****************************************************************************************/

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/
#include "config/graphics_config.h"

#include "hal/vga_graphics.h"
#include "hal/vga/vga_modes.h"

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
	//Variables
	VideoMode mode = { .label = 0 };
	vga_graphics_config_t config = { .display_ctrl_address = 0 };
	//Modes
	GRAPHICS_CONFIG_MAP_MODE("640x480", VMODE_640x480);
	GRAPHICS_CONFIG_MAP_MODE("800x600", VMODE_800x600);
	GRAPHICS_CONFIG_MAP_MODE("1280x720", VMODE_1280x720);
	GRAPHICS_CONFIG_MAP_MODE("1280x1024", VMODE_1280x1024);
	GRAPHICS_CONFIG_MAP_MODE("1920x1080", VMODE_1920x1080);
	if(mode.label != 0)
	{
		//Devices
		GRAPHICS_CONFIG_MAP_DEVICE("vga", VGA_GRAPHICS_VGA_CONFIG(mode));
		GRAPHICS_CONFIG_MAP_DEVICE("hdmi", VGA_GRAPHICS_HDMI_CONFIG(mode));
		if(config.display_ctrl_address != 0)
		{
			return vga_graphics_init(output, config);
		}
		return GRAPHICS_CONFIG_DEVICE_NOT_FOUND;
	}
	return GRAPHICS_CONFIG_MODE_NOT_FOUND;
}

/*****************************************************************************************
*                                   graphics_config.c
*****************************************************************************************/
