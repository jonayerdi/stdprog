/*
 * gpio.c
 *
 *  Created on: 15 Nov 2017
 *      Author: Jon Ayerdi
 */

#include "io/gpio.h"

inline gpio_value_t gpio_get(gpio_input_t gpio)
{
	return gpio.get(gpio.context);
}

inline void gpio_set(gpio_output_t gpio, gpio_value_t value)
{
	gpio.set(value, gpio.context);
}
