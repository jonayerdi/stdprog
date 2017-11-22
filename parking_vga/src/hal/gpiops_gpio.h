/*
 * gpiops_gpio.h
 *
 *  Created on: 17 Nov 2017
 *      Author: Jon Ayerdi
 */

#ifndef SRC_HAL_GPIOPS_GPIO_H_
#define SRC_HAL_GPIOPS_GPIO_H_

#include "io/gpio.h"

#include <xil_types.h>
#include <xgpiops.h>

typedef struct gpiops_id
{
	u16 device_id;
	u32 pin;
}gpiops_id_t;

typedef struct gpiops_gpio
{
	XGpioPs gpio;
	u32 pin;
} gpiops_gpio_t;

int gpiops_input_init(gpio_input_t *out, gpiops_id_t id);
int gpiops_output_init(gpio_output_t *out, gpiops_id_t id);

#endif /* SRC_HAL_GPIOPS_GPIO_H_ */
