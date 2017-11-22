/*
 * main.c
 *
 *  Created on: 15 Nov 2017
 *      Author: Jon Ayerdi
 */

#include "io/stream.h"
#include "io/gpio.h"
#include "io/logger.h"
#include "io/graphics.h"

#include "hal/stdio_stream.h"
#include "hal/file_stream.h"
#include "hal/gpiops_gpio.h"
#include "hal/vga_graphics.h"

#define FILE_BUFFER_SIZE 512

#define BLACK 0xFF000000
#define RED 0x88FF0000
#define GREEN 0x8800FF00
#define YELLOW 0x88F2EE02
#define BLUE 0xFF0000FF
#define WHITE 0xFFFFFFFF

static output_stream_t logger;

void files_test(void);
void vga_gpio_test(void);

void files_test(void)
{
	/* Declare variables */
	int error;
	input_stream_t fileIn;
	output_stream_t fileOut;
	char file_contents[FILE_BUFFER_SIZE];
	size_t file_read;

	/* File write test */
	stream_write_string(logger, "[start] Opening file for writing...\n");
	error = file_output_stream(&fileOut, "Test.txt");
	if(error)
		stream_write_string(logger, "[error] Opening file for writing\n");
	else
	{
		stream_write_string(logger, "[start] File open, writing...\n");
		stream_write_string(fileOut, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam eu nisl eget elit varius iaculis.\n");
		stream_write_string(fileOut, "Mauris et magna quis diam dapibus egestas. Nam ac quam euismod, suscipit nisi ac, viverra lectus.\n");
		stream_write_string(fileOut, "Sed fermentum tellus enim, eget sollicitudin sapien efficitur eu.\n");
		stream_write_string(fileOut, "Curabitur eleifend est sed odio condimentum. Ut lacinia eros imperdiet, gravida lectus ac, maximus nullam.\n");
		stream_close_output(fileOut);
		stream_write_string(logger, "[done] File written\n");
	}

	/* File read test */
	stream_write_string(logger, "[start] Opening file for reading...\n");
	error = file_input_stream(&fileIn, "Test.txt");
	if(error)
		stream_write_string(logger, "[error] Opening file for reading\n");
	else
	{
		stream_write_string(logger, "[done] File open, reading...\n");
		stream_write_string(logger, "[file dump begin]\n");
		while(file_read = stream_read(fileIn, file_contents, FILE_BUFFER_SIZE))
			stream_write(logger, file_contents, file_read);
		stream_close_input(fileIn);
		stream_write_string(logger, "\n[file dump end]\n");
	}
	stream_flush(logger);
}

void vga_gpio_test(void)
{
	/* Declare variables */
	int error;
	gpio_input_t button;
	graphics_t gfx;
	vga_graphics_config_t config = VGA_GRAPHICS_VGA_CONFIG(VMODE_800x600);//VGA_GRAPHICS_HDMI_CONFIG(VMODE_800x600);

	/* Init GPIO */
	gpiops_id_t gpio_id = GPIOPS_BUTTON5;
	gpiops_input_init(&button, gpio_id);

	/* VGA test */
	stream_write_string(logger, "[start] Initializing VGA\n");
	error = vga_graphics_init(config, &gfx);
	if(error)
		stream_write_string(logger, "[error] Initializing VGA\n");
	else
	{
		stream_write_string(logger, "[done] Initialized VGA\n");
		graphics_draw_rect(gfx, BLACK, 0, 0, 800, 600);
		graphics_draw_rect(gfx, GREEN, 500, 100, 700, 400);
		graphics_draw_circle(gfx, RED, 300, 250, 150);
		graphics_draw_circle(gfx, YELLOW, 0, 0, 200);
		graphics_draw_string8x8(gfx, "Texto", BLUE, 200, 200);
		graphics_draw_string8x8(gfx, "de", WHITE, 248, 200);
		graphics_draw_string8x8(gfx, "prueba", BLACK, 272, 200);
		stream_write_string(logger, "[start] Rendering stuff...Press button5 to terminate\n");
		while(gpio_get(button) == 0)
			graphics_render(gfx);
		gpio_input_destroy(button);
		graphics_destroy(gfx);
	}
}

int main(void)
{
	/* Init logger */
	logger_init();
	logger = logger_get();

	/* Start the demo */
	stream_write_string(logger, "[start] Starting application\n");

	/* File test */
	stream_write_string(logger, "[start] files_test()\n");
	files_test();
	stream_write_string(logger, "[done] files_test()\n");

	/* VGA test */
	stream_write_string(logger, "[start] vga_gpio_test()\n");
	vga_gpio_test();
	stream_write_string(logger, "[done] vga_gpio_test()\n");

	stream_write_string(logger, "[done] Application terminated\n");
}
