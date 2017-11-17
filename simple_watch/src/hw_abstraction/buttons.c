/*
 * buttons.c
 *
 *  Created on: 23 Oct 2017
 *      Author: Jon Ayerdi
 */

#include "buttons.h"

void buttons_init(void)
{
	gpio_init();
	gpio_set_direction(hw_abstraction_button_1, GPIO_IN);
	gpio_set_direction(hw_abstraction_button_2, GPIO_IN);
}

u32 buttons_get(u32 pin)
{
	return gpio_read(pin);
}
