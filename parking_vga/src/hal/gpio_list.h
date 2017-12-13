/*
 * gpio_list.h
 *
 *  Created on: 13 Dec 2017
 *      Author: Jon Ayerdi
 */

#ifndef SRC_HAL_GPIO_LIST_H_
#define SRC_HAL_GPIO_LIST_H_

#include "gpiops_gpio.h"
#include "axi_gpio.h"

/* MIO */
/* Buttons */
const gpiops_id_t gpiops_button4 = { .device_id = XPAR_PS7_GPIO_0_DEVICE_ID, .pin = 50 };
const gpiops_id_t gpiops_button5 = { .device_id = XPAR_PS7_GPIO_0_DEVICE_ID, .pin = 51 };
/* LEDs */
const gpiops_id_t gpiops_led4 = { .device_id = XPAR_PS7_GPIO_0_DEVICE_ID, .pin = 7 };

/* AXI GPIO */
/* Buttons */
const axi_gpio_id_t axi_gpio_button0 = { .device_id = XPAR_BTNS_4BITS_DEVICE_ID, .channel = 1, .pin = 0 };
const axi_gpio_id_t axi_gpio_button1 = { .device_id = XPAR_BTNS_4BITS_DEVICE_ID, .channel = 1, .pin = 1 };
const axi_gpio_id_t axi_gpio_button2 = { .device_id = XPAR_BTNS_4BITS_DEVICE_ID, .channel = 1, .pin = 2 };
const axi_gpio_id_t axi_gpio_button3 = { .device_id = XPAR_BTNS_4BITS_DEVICE_ID, .channel = 1, .pin = 3 };
/* Switches */
const axi_gpio_id_t axi_gpio_switch0 = { .device_id = XPAR_SWS_4BITS_DEVICE_ID, .channel = 1, .pin = 0 };
const axi_gpio_id_t axi_gpio_switch1 = { .device_id = XPAR_SWS_4BITS_DEVICE_ID, .channel = 1, .pin = 1 };
const axi_gpio_id_t axi_gpio_switch2 = { .device_id = XPAR_SWS_4BITS_DEVICE_ID, .channel = 1, .pin = 2 };
const axi_gpio_id_t axi_gpio_switch3 = { .device_id = XPAR_SWS_4BITS_DEVICE_ID, .channel = 1, .pin = 3 };
/* LEDs */
const axi_gpio_id_t axi_gpio_led0 = { .device_id = XPAR_LEDS_4BITS_DEVICE_ID, .channel = 1, .pin = 0 };
const axi_gpio_id_t axi_gpio_led1 = { .device_id = XPAR_LEDS_4BITS_DEVICE_ID, .channel = 1, .pin = 1 };
const axi_gpio_id_t axi_gpio_led2 = { .device_id = XPAR_LEDS_4BITS_DEVICE_ID, .channel = 1, .pin = 2 };
const axi_gpio_id_t axi_gpio_led3 = { .device_id = XPAR_LEDS_4BITS_DEVICE_ID, .channel = 1, .pin = 3 };

int gpio_list_get_input(gpio_input_t *out, const char *name);
int gpio_list_get_output(gpio_output_t *out, const char *name);

#endif /* SRC_HAL_GPIO_LIST_H_ */
