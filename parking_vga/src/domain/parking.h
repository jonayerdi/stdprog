/*
 * parking.h
 *
 *  Created on: 15 Nov 2017
 *      Author: Jon Ayerdi
 */

#ifndef SRC_DOMAIN_PARKING_H_
#define SRC_DOMAIN_PARKING_H_

#include <stddef.h> /* size_t */

#include "io/graphics.h" /* graphics_t */
#include "io/gpio.h" /* gpio_input_t */
#include "lib/clock.h" /* clock_t */
#include "lib/image.h" /* image_t */

#define GPIO_VALUE_FREE ((gpio_value_t)0)
#define GPIO_VALUE_TAKEN ((gpio_value_t)1)

typedef enum parking_state
{
	parking_state_unknown,
	parking_state_free,
	parking_state_freeing,
	parking_state_taken,
	parking_state_taking
} parking_state_t;

typedef enum parking_state_mode
{
	parking_state_mode_normal,
	parking_state_mode_forced
} parking_state_mode_t;

typedef struct parking_spot
{
	unsigned int id;
	parking_state_t state;
	parking_state_mode_t state_mode;
	timestamp_t timestamp;
	gpio_input_t input_source;
	size_t x1;
	size_t x2;
	size_t y1;
	size_t y2;
} parking_spot_t;

typedef struct parking
{
	parking_spot_t *spots;
	size_t count;
	timestamp_t time;
	graphics_t graphics;
	image_t background_image;
} parking_t;

int parking_init(parking_t *output);
int parking_step(parking_t input, timestamp_t time_diff);
void parking_render(parking_t input);
void parking_destroy(parking_t *input);

#endif /* SRC_DOMAIN_PARKING_H_ */
