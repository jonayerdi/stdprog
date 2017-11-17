/*
 * leds.c
 *
 *  Created on: 29 Oct 2017
 *      Author: Jon Ayerdi
 */

#include "leds.h"

void leds_init(void)
{
	gpio_init();
	gpio_set_direction(hw_abstraction_led_4, GPIO_OUT);
}

void leds_set(u32 pin, u32 value)
{
	gpio_write(pin, value);
}
