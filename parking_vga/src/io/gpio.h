/*
 * gpio.h
 *
 *  Created on: 15 Nov 2017
 *      Author: Jon Ayerdi
 */

#ifndef SRC_IO_GPIO_H_
#define SRC_IO_GPIO_H_

#include <xil_types.h>

typedef u32 gpio_value_t;

typedef struct gpio_input
{
	gpio_value_t(*get)(void *context);
	void *context;
} gpio_input_t;

typedef struct gpio_output
{
	void(*set)(gpio_value_t value, void *context);
	void *context;
} gpio_output_t;

gpio_value_t gpio_get(gpio_input_t gpio);
void gpio_set(gpio_output_t gpio, gpio_value_t value);

#endif /* SRC_IO_GPIO_H_ */
