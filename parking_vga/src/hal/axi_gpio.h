/*
 * axi_gpio.h
 *
 *  Created on: 13 Dec 2017
 *      Author: Jon Ayerdi
 */

#ifndef SRC_HAL_AXI_GPIO_H_
#define SRC_HAL_AXI_GPIO_H_

#include "io/gpio.h"

#include <xil_types.h>
#include <xgpio.h>
#include <xparameters.h>

typedef struct axi_gpio_id
{
	u16 device_id;
	u16 channel;
	u32 pin;
} axi_gpio_id_t;

typedef struct axi_gpio
{
	XGpio gpio;
	u16 channel;
	u32 pin;
} axi_gpio_t;

int axi_gpio_input_init(gpio_input_t *out, axi_gpio_id_t id);
int axi_gpio_output_init(gpio_output_t *out, axi_gpio_id_t id);

#endif /* SRC_HAL_AXI_GPIO_H_ */
