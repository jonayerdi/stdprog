/*
 * main.c
 *
 *  Created on: 15 Nov 2017
 *      Author: Jon Ayerdi
 */

#include "io/logger.h"
#include "io/graphics.h"
#include "hal/vga_graphics.h"
#include "hal/file_stream.h"

#define FILE_BUFFER_SIZE 512

#define BLACK 0xFFFFFFFF
#define RED 0xAAFF0000
#define GREEN 0xAA00FF00
#define BLUE 0xAA0000FF

int main(void)
{
	/* Declare variables */
	int error;
	output_stream_t logger;
	input_stream_t file;
	char file_contents[FILE_BUFFER_SIZE];
	size_t file_read;
	graphics_t gfx;
	vga_graphics_config_t config = VGA_GRAPHICS_HDMI_CONFIG(VMODE_1280x1024);

	/* Init logger */
	logger_init();
	logger = logger_get();
	/* Start the demo */
	stream_write_string(logger, "Starting application\n");
	/* File test */
	stream_write_string(logger, "[calling] file_input_stream()\n");
	error = file_input_stream(&file, "Test.txt");
	if(error)
		stream_write_string(logger, "[error] file_input_stream()");
	else
	{
		stream_write_string(logger, "[done] file_input_stream()\n");
		stream_write_string(logger, "[file dump begin]:\n");
		while(file_read = stream_read(file, file_contents, FILE_BUFFER_SIZE))
			stream_write(logger, file_contents, file_read);
		stream_write_string(logger, "\n[file dump end]:\n");
	}
	stream_flush(logger);
	/* VGA test */
	stream_write_string(logger, "[calling] vga_graphics_init()\n");
	error = vga_graphics_init(config, &gfx);
	if(error)
		stream_write_string(logger, "[error] vga_graphics_init()");
	else
		stream_write_string(logger, "[done] vga_graphics_init()\n");
	graphics_draw_rect(gfx, BLACK, 0, 0, 1280, 1024);
	graphics_draw_circle(gfx, RED, 50, 50, 100);
	graphics_draw_circle(gfx, GREEN, 150, 150, 200);
	graphics_draw_string8x8(gfx, "HOLA", BLUE, 200, 200);
	while(1)
		graphics_render(gfx);
	graphics_destroy(gfx);
	stream_write_string(logger, "Application terminated");
}
