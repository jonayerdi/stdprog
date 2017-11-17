/*
 * parking.h
 *
 *  Created on: 15 Nov 2017
 *      Author: Jon Ayerdi
 */

#ifndef SRC_DOMAIN_PARKING_H_
#define SRC_DOMAIN_PARKING_H_

#include <stddef.h> /* size_t */

#include "lib/clock.h" /* clock_t */
#include "lib/image.h" /* image_t */
#include "io/graphics.h" /* graphics_t */

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
	parking_state state;
	parking_state_mode_t state_mode;
	clock_t timestamp;
	size_t x;
	size_t y;
} parking_spot_t;

typedef struct parking
{
	parking_spot_t *spots;
	size_t count;
	graphics_t graphics;
	image_t background;
} parking_t;

int parking_init(char *config, parking_t *output);
int parking_maintain(parking_t input);
int parking_render(parking_t input);
int parking_destroy(parking_t *input);

#endif /* SRC_DOMAIN_PARKING_H_ */
