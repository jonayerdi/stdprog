/*****************************************************************************************
*                                    gpio_config.c
******************************************************************************************
* AUTHOR: Jon Ayerdi
*
* DESCRIPTION: Mapping of gpio implementations to their names
*
*****************************************************************************************/

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/
#include "config/gpio_config.h"

#include "hal/fixed_gpio.h"
#include "hal/gpiops_gpio.h"
#include "hal/axi_gpio.h"

#include <string.h>

/*--------------------------------------------------------------------------------------*/
/*                                      CONSTANTS                                       */
/*--------------------------------------------------------------------------------------*/

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

/*--------------------------------------------------------------------------------------*/
/*                                        MACROS                                        */
/*--------------------------------------------------------------------------------------*/

/* Utils */
#define GPIO_CONFIG_MAP(NAME,VALUE) { if(!strcmp(gpio_name, NAME)) { return VALUE; } }

/*--------------------------------------------------------------------------------------*/
/*                            PUBLIC FUNCTION DECLARATIONS                              */
/*--------------------------------------------------------------------------------------*/

int gpio_config_get_input(gpio_input_t *out, const char *gpio_name)
{
	//Fixed
	GPIO_CONFIG_MAP("fixed0", fixed_gpio_input_init(out, 0));
	GPIO_CONFIG_MAP("fixed1", fixed_gpio_input_init(out, 1));
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

/*****************************************************************************************
*                                    gpio_config.c
*****************************************************************************************/
