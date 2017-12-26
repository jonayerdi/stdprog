/*
 * fixed_gpio.h
 *
 *  Created on: 26 Dec 2017
 *      Author: Jon Ayerdi
 */

#ifndef SRC_HAL_FIXED_GPIO_H_
#define SRC_HAL_FIXED_GPIO_H_

#include "io/gpio.h"

typedef struct fixed_gpio
{
	gpio_value_t value;
} fixed_gpio_t;

int fixed_gpio_input_init(gpio_input_t *out, gpio_value_t value);

#endif /* SRC_HAL_FIXED_GPIO_H_ */
