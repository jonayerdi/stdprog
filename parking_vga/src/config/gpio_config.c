/*
 * gpio_config.c
 *
 *  Created on: 19 Dec 2017
 *      Author: Jon Ayerdi
 */

#include "config/gpio_config.h"

#include <string.h>

#define GPIO_CONFIG_MAP(NAME,VALUE) { if(!strcmp(gpio_name, NAME)) { return VALUE; } }

int gpio_config_get_input(gpio_input_t *out, const char *gpio_name)
{
	//Buttons
	GPIO_CONFIG_MAP("button0", axi_gpio_input_init(out, axi_gpio_button0));
	GPIO_CONFIG_MAP("button1", axi_gpio_input_init(out, axi_gpio_button1));
	GPIO_CONFIG_MAP("button2", axi_gpio_input_init(out, axi_gpio_button2));
	GPIO_CONFIG_MAP("button3", axi_gpio_input_init(out, axi_gpio_button3));
	GPIO_CONFIG_MAP("button4", gpiops_input_init(out, gpiops_button4));
	GPIO_CONFIG_MAP("button5", gpiops_input_init(out, gpiops_button5));
	//Switches
	GPIO_CONFIG_MAP("switch0", axi_gpio_input_init(out, axi_gpio_switch0));
	GPIO_CONFIG_MAP("switch1", axi_gpio_input_init(out, axi_gpio_switch1));
	GPIO_CONFIG_MAP("switch2", axi_gpio_input_init(out, axi_gpio_switch2));
	GPIO_CONFIG_MAP("switch3", axi_gpio_input_init(out, axi_gpio_switch3));
	return GPIO_CONFIG_NOT_FOUND;
}

int gpio_config_get_output(gpio_output_t *out, const char *gpio_name)
{
	//LEDs
	GPIO_CONFIG_MAP("led0", axi_gpio_output_init(out, axi_gpio_led0));
	GPIO_CONFIG_MAP("led1", axi_gpio_output_init(out, axi_gpio_led1));
	GPIO_CONFIG_MAP("led2", axi_gpio_output_init(out, axi_gpio_led2));
	GPIO_CONFIG_MAP("led3", axi_gpio_output_init(out, axi_gpio_led3));
	GPIO_CONFIG_MAP("led4", gpiops_output_init(out, gpiops_led4));
	return GPIO_CONFIG_NOT_FOUND;
}
