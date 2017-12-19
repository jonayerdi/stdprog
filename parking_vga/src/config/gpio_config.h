/*
 * gpio_config.h
 *
 *  Created on: 19 Dec 2017
 *      Author: Jon Ayerdi
 */

#ifndef SRC_CONFIG_GPIO_CONFIG_H_
#define SRC_CONFIG_GPIO_CONFIG_H_

#include "io/gpio.h"

#define GPIO_CONFIG_NOT_FOUND -69

int gpio_config_get_input(gpio_input_t *out, const char *gpio_name);
int gpio_config_get_output(gpio_output_t *out, const char *gpio_name);

#endif /* SRC_CONFIG_GPIO_CONFIG_H_ */
