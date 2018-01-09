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
#include "lib/json.h"

#include "config/gpio_config.h"
#include "config/graphics_config.h"
#include "config/stream_config.h"

#define CONFIG_FILE_MAX_BYTES 8000

#define GPIO_VALUE_FREE ((gpio_value_t)0)
#define GPIO_VALUE_TAKEN ((gpio_value_t)1)

#define TIMEOUT_TAKE_SPOT 4
#define TIMEOUT_FREE_SPOT 4

#define COLOR_PARKING_STATE_UNKNOWN 0xCCAAAAAA
#define COLOR_PARKING_STATE_FREE 0xCC00DD11
#define COLOR_PARKING_STATE_FREEING 0xCCBB00BB
#define COLOR_PARKING_STATE_TAKEN 0xCCDD0011
#define COLOR_PARKING_STATE_TAKING 0xCCFCF94E

static int _parking_spot_init(parking_spot_t *output, json_object config);
static int _parking_spot_step(parking_spot_t *input, timestamp_t time);
static void _parking_spot_render(graphics_t graphics, parking_spot_t input);
static void _parking_spot_destroy(parking_spot_t *input);

static int _parking_spot_init(parking_spot_t *output, json_object config)
{
	int error;
	output->id = (unsigned int)(*((json_integer *)json_object_find_key(config, "id", 0).value));
	output->state = parking_state_unknown;
	output->mode = parking_spot_mode_normal;
	CLOCK_SET(output->timestamp, 0, 0, 0, 0);
	output->x1 = (size_t)(*((json_integer *)json_object_find_key(config, "x1", 0).value));
	output->x2 = (size_t)(*((json_integer *)json_object_find_key(config, "x2", 0).value));
	output->y1 = (size_t)(*((json_integer *)json_object_find_key(config, "y1", 0).value));
	output->y2 = (size_t)(*((json_integer *)json_object_find_key(config, "y2", 0).value));
	error = gpio_config_get_input(&output->input_source, (json_string)json_object_find_key(config, "input_source", 0).value);
	if(error)
		return error;
	error = gpio_config_get_input(&output->forced_source, (json_string)json_object_find_key(config, "forced_source", 0).value);
	return error;
}

static int _parking_spot_step(parking_spot_t *input, timestamp_t time)
{
	//Only for demo purposes, parking mode and state would be set via remote commands
	if(gpio_get(input->forced_source) == GPIO_VALUE_TAKEN)
	{
		input->mode = parking_spot_mode_forced;
		input->state = parking_state_taken;
	}
	else if(input->mode == parking_spot_mode_forced)
	{
		input->mode = parking_spot_mode_normal;
		input->state = parking_state_unknown;
	}
	//State machine
	if(input->mode == parking_spot_mode_normal)
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
				else if(CLOCK_DIFF_SECONDS(input->timestamp, time) > TIMEOUT_FREE_SPOT)
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
				else if(CLOCK_DIFF_SECONDS(input->timestamp, time) > TIMEOUT_TAKE_SPOT)
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
	gpio_input_destroy(input->forced_source);
}

int parking_init(parking_t *output, const char *config_filename)
{
	int result;
	input_stream_t config_file;
	char config[CONFIG_FILE_MAX_BYTES];
	size_t config_length;
	json_object parking, graphics, layout;
	json_array spots;
	json_allocator allocator = { .malloc = memory_allocate, .free = memory_free };
	//Read config file
	result = stream_config_get_input(&config_file, config_filename);
	if(result)
		return PARKING_ERROR_CONFIG_STREAM;
	config_length = stream_read(config_file, config, CONFIG_FILE_MAX_BYTES);
	//Parse configuration
	result = (int)json_read_object(config, config_length, &allocator, &parking, &config_length);
	if(result)
		return PARKING_ERROR_CONFIG_PARSE;
	graphics = *((json_object *)json_object_find_key(parking, "graphics", 0).value);
	layout = *((json_object *)json_object_find_key(parking, "layout", 0).value);
	spots = *((json_array *)json_object_find_key(layout, "spots", 0).value);
	//Time
	CLOCK_SET(output->time, 0, 0, 0, 0);
	//Graphics
	result = graphics_config_get(&output->graphics
			, (json_string)json_object_find_key(graphics, "device", 0).value
			, (json_string)json_object_find_key(graphics, "mode", 0).value);
	if(result)
		return PARKING_ERROR_INIT_GRAPHICS;
	//Background image
	input_stream_t image_input;
	result = stream_config_get_input(&image_input, (json_string)json_object_find_key(layout, "background", 0).value);
	if(result)
		return PARKING_ERROR_IMAGE_STREAM;
	result = bmp_load(image_input, &output->background_image);
	stream_close_input(image_input);
	if(result)
		return PARKING_ERROR_IMAGE_PARSE;
	//Parking spots
	output->count = spots.count;
	output->spots = (parking_spot_t *)memory_allocate(sizeof(parking_spot_t) * spots.count);
	for(size_t i = 0 ; i < output->count ; i++)
	{
		result = _parking_spot_init(&output->spots[i], *((json_object *)spots.values[i].value));
		if(result)
			return PARKING_ERROR_CONFIG_SPOT;
	}
	//Destroy json object
	json_free_object(&allocator, parking);
	//Destroy config input stream
	stream_close_input(config_file);
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
