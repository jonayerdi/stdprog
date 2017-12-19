/*
 * gpio_config.h
 *
 *  Created on: 19 Dec 2017
 *      Author: Jon Ayerdi
 */

#ifndef SRC_CONFIG_GPIO_CONFIG_H_
#define SRC_CONFIG_GPIO_CONFIG_H_

#include "hal/gpiops_gpio.h"
#include "hal/axi_gpio.h"

#define GPIO_CONFIG_NOT_FOUND -69

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

int gpio_config_get_input(gpio_input_t *out, const char *gpio_name);
int gpio_config_get_output(gpio_output_t *out, const char *gpio_name);

#endif /* SRC_CONFIG_GPIO_CONFIG_H_ */
