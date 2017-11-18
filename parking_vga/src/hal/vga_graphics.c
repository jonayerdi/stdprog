/*
 * vga_graphics.c
 *
 *  Created on: 17 Nov 2017
 *      Author: Jon Ayerdi
 */

#include "hal/vga_graphics.h"

static pixel_t *_get_vbuffer(void *context);
static void _flush_vbuffer(void *context);
static void _destroy(void *context);

static pixel_t *_get_vbuffer(void *context)
{
	vga_graphics_t *vga = ((vga_graphics_t *)context);
	return vga->vbuffer;
}

static void _flush_vbuffer(void *context)
{
	vga_graphics_t *vga = ((vga_graphics_t *)context);

}

static void _destroy(void *context)
{

}

int vga_graphics_init(vga_graphics_config_t config, graphics_t *output)
{
	vga_graphics_t context;

}
