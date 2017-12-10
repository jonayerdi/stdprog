/*
 * parking.c
 *
 *  Created on: 15 Nov 2017
 *      Author: Jon Ayerdi
 */

#include "domain/parking.h"

#include "io/memory.h"
#include "io/stream.h"
#include "io/gpio.h"
#include "io/graphics.h"

#include "lib/image.h"
#include "lib/bmp.h"

#include "hal/file_stream.h"
#include "hal/gpiops_gpio.h"
#include "hal/vga_graphics.h"

#define COLOR_PARKING_STATE_UNKNOWN 0xCCAAAAAA
#define COLOR_PARKING_STATE_FREE 0xCC00DD11
#define COLOR_PARKING_STATE_FREEING 0xCCBB00BB
#define COLOR_PARKING_STATE_TAKEN 0xCCDD0011
#define COLOR_PARKING_STATE_TAKING 0xCCFCF94E

static int _parking_spot_init(parking_spot_t *output);
static int _parking_spot_step(parking_spot_t *input, timestamp_t time);
static void _parking_spot_render(graphics_t graphics, parking_spot_t input);
static void _parking_spot_destroy(parking_spot_t *input);

static int _parking_spot_init(parking_spot_t *output)
{
	//TODO
	return 0;
}

static int _parking_spot_step(parking_spot_t *input, timestamp_t time)
{
	if(input->state_mode == parking_state_mode_normal)
	{
		gpio_value_t value = gpio_get(input->input_source);
		switch(input->state)
		{
			case parking_state_free:
				if(value == GPIO_VALUE_TAKEN)
				{
					input->state = parking_state_taking;
					input->timestamp = time;
				}
				break;
			case parking_state_freeing:
				if(value == GPIO_VALUE_TAKEN)
				{
					input->state = parking_state_taken;
					input->timestamp = time;
				}
				else if(CLOCK_DIFF_SECONDS(input->timestamp, time) > 5)
				{
					input->state = parking_state_free;
					input->timestamp = time;
				}
				break;
			case parking_state_taken:
				if(value == GPIO_VALUE_FREE)
				{
					input->state = parking_state_freeing;
					input->timestamp = time;
				}
				break;
			case parking_state_taking:
				if(value == GPIO_VALUE_FREE)
				{
					input->state = parking_state_free;
					input->timestamp = time;
				}
				else if(CLOCK_DIFF_SECONDS(input->timestamp, time) > 5)
				{
					input->state = parking_state_taken;
					input->timestamp = time;
				}
				break;
			default:
				input->state = (value == GPIO_VALUE_FREE) ? parking_state_free : parking_state_taken;
				break;
		}
	}
	return 0;
}

static void _parking_spot_render(graphics_t graphics, parking_spot_t input)
{
	pixel_t color;
	switch(input.state)
	{
		case parking_state_free:
			color = COLOR_PARKING_STATE_FREE;
			break;
		case parking_state_freeing:
			color = COLOR_PARKING_STATE_FREEING;
			break;
		case parking_state_taken:
			color = COLOR_PARKING_STATE_TAKEN;
			break;
		case parking_state_taking:
			color = COLOR_PARKING_STATE_TAKING;
			break;
		default:
			color = COLOR_PARKING_STATE_UNKNOWN;
			break;
	}
	graphics_draw_rect(graphics, color, input.x1, input.y1, input.x2, input.y2);
}

static void _parking_spot_destroy(parking_spot_t *input)
{
	gpio_input_destroy(input->input_source);
}

int parking_init(parking_t *output)
{
	int result = 0;
	//Parking spots
	output->spots = (parking_spot_t *)memory_allocate(2 * sizeof(parking_spot_t));
	output->count = 2;
	for(size_t i = 0 ; i < output->count ; i++)
	{
		output->spots[i].id = i + 1;
		output->spots[i].state = parking_state_unknown;
		output->spots[i].state_mode = parking_state_mode_normal;
		CLOCK_SET(output->spots[i].timestamp, 0, 0, 0, 0);
	}
	gpiops_id_t gpio0 = GPIOPS_BUTTON4;
	result = gpiops_input_init(&output->spots[0].input_source, gpio0);
	output->spots[0].x1 = 34;
	output->spots[0].x2 = 147;
	output->spots[0].y1 = 45;
	output->spots[0].y2 = 184;
	gpiops_id_t gpio1 = GPIOPS_BUTTON5;
	result = gpiops_input_init(&output->spots[1].input_source, gpio1);
	output->spots[1].x1 = 194;
	output->spots[1].x2 = 298;
	output->spots[1].y1 = 45;
	output->spots[1].y2 = 184;
	//Time
	CLOCK_SET(output->time, 0, 0, 0, 0);
	//Graphics
	vga_graphics_config_t vga_config = VGA_GRAPHICS_HDMI_CONFIG(VMODE_800x600);
	result = vga_graphics_init(vga_config, &output->graphics);
	//Background image
	input_stream_t image_input;
	result = file_input_stream(&image_input, "parking.bmp");
	result = bmp_load(image_input, &output->background_image);
	return 0;
}

int parking_step(parking_t *input, timestamp_t time_diff)
{
	CLOCK_INCREASE(input->time, 0, 0, 0, time_diff);
	for(size_t i = 0 ; i < input->count ; i++)
		_parking_spot_step(&input->spots[i], input->time);
	return 0;
}

void parking_render(parking_t input)
{
	graphics_draw_image(input.graphics, input.background_image, 0, 0);
	for(size_t i = 0 ; i < input.count ; i++)
		_parking_spot_render(input.graphics, input.spots[i]);
	graphics_render(input.graphics);
}

void parking_destroy(parking_t *input)
{
	//Parking spots
	for(size_t i = 0 ; i < input->count ; i++)
		_parking_spot_destroy(&input->spots[i]);
	memory_free(input->spots);
	//Graphics
	graphics_destroy(input->graphics);
	//Background image
	image_free(&input->background_image);
}
