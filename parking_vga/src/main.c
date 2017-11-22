/*
 * main.c
 *
 *  Created on: 15 Nov 2017
 *      Author: Jon Ayerdi
 */

#include "io/logger.h"
#include "io/graphics.h"
#include "hal/stdio_stream.h"
#include "hal/vga_graphics.h"
#include "hal/file_stream.h"

#define FILE_BUFFER_SIZE 512

#define BLACK 0xFF000000
#define RED 0x88FF0000
#define GREEN 0x8800FF00
#define YELLOW 0x88F2EE02
#define BLUE 0xFF0000FF
#define WHITE 0xFFFFFFFF

static output_stream_t logger;
static input_stream_t stdin;

void filesTest(void);
void vgaTest(void);

void filesTest(void)
{
	/* Declare variables */
	int error;
	input_stream_t fileIn;
	output_stream_t fileOut;
	char file_contents[FILE_BUFFER_SIZE];
	size_t file_read;

	/* File write test */
	stream_write_string(logger, "[calling] file_output_stream()\n");
	error = file_output_stream(&fileOut, "Test.txt");
	if(error)
		stream_write_string(logger, "[error] file_output_stream()");
	else
	{
		stream_write_string(logger, "[done] file_output_stream()\n");
		stream_write_string(fileOut, "This text was written into the file");
		stream_flush(fileOut);
		stream_close_output(fileOut);
	}

	/* File read test */
	stream_write_string(logger, "[calling] file_input_stream()\n");
	error = file_input_stream(&fileIn, "Test.txt");
	if(error)
		stream_write_string(logger, "[error] file_input_stream()");
	else
	{
		stream_write_string(logger, "[done] file_input_stream()\n");
		stream_write_string(logger, "[file dump begin]:\n");
		while(file_read = stream_read(fileIn, file_contents, FILE_BUFFER_SIZE))
			stream_write(logger, file_contents, file_read);
		stream_close_input(fileIn);
		stream_write_string(logger, "\n[file dump end]:\n");
	}
	stream_flush(logger);
}

void vgaTest(void)
{
	/* Declare variables */
	int error;
	graphics_t gfx;
	vga_graphics_config_t config = VGA_GRAPHICS_VGA_CONFIG(VMODE_800x600);//VGA_GRAPHICS_HDMI_CONFIG(VMODE_800x600);

	/* VGA test */
	stream_write_string(logger, "[calling] vga_graphics_init()\n");
	error = vga_graphics_init(config, &gfx);
	if(error)
		stream_write_string(logger, "[error] vga_graphics_init()\n");
	else
	{
		stream_write_string(logger, "[done] vga_graphics_init()\n");
		graphics_draw_rect(gfx, BLACK, 0, 0, 800, 600);
		graphics_draw_rect(gfx, GREEN, 500, 100, 700, 400);
		graphics_draw_circle(gfx, RED, 300, 250, 150);
		graphics_draw_circle(gfx, YELLOW, 0, 0, 200);
		graphics_draw_string8x8(gfx, "Texto", BLUE, 200, 200);
		graphics_draw_string8x8(gfx, "de", WHITE, 248, 200);
		graphics_draw_string8x8(gfx, "prueba", BLACK, 272, 200);
		while(1)
			graphics_render(gfx);
		graphics_destroy(gfx);
	}
}

int main(void)
{
	/* Init logger */
	logger_init();
	logger = logger_get();

	/* Init stdin */
	stdio_input_stream(&stdin);

	/* Start the demo */
	stream_write_string(logger, "Starting application\n");

	/* File test */
	filesTest();

	/* VGA test */
	vgaTest();

	stream_write_string(logger, "Application terminated\n");
}
