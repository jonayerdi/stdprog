/*
 * main.c
 *
 *  Created on: 15 Nov 2017
 *      Author: Jon Ayerdi
 */

#include "io/graphics.h"
#include "hal/vga_graphics.h"

int main(void)
{
	graphics_t gfx;
	vga_graphics_config_t config = VGA_GRAPHICS_VGA_CONFIG(VMODE_1280x1024);
	pixel_t black = 0xFFFFFFFF;
	pixel_t red = 0xAAFF0000;
	pixel_t green = 0xAA00FF00;
	pixel_t blue = 0xAA0000FF;
	vga_graphics_init(config, &gfx);
	graphics_draw_rect(gfx, black, 0, 0, 1280, 1024);
	graphics_draw_circle(gfx, red, 50, 50, 100);
	graphics_draw_circle(gfx, green, 150, 150, 200);
	graphics_draw_string8x8(gfx, "HOLA", blue, 200, 200);
	while(1)
		graphics_render(gfx);
	graphics_destroy(gfx);
}
