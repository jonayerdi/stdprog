/*************************************************************************************//**
* @file gpio_config.c
* @brief Mapping of gpio implementations to their names
* @author Jon Ayerdi
*****************************************************************************************/

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/
#include "config/gpio_config.h"

#include "hal/fixed_gpio.h"
#include "hal/keyboard_gpio.h"

#include <string.h>

/*--------------------------------------------------------------------------------------*/
/*                                      CONSTANTS                                       */
/*--------------------------------------------------------------------------------------*/


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
	GPIO_CONFIG_MAP("button0", keyboard_gpio_init(out, SDL_SCANCODE_0));
	GPIO_CONFIG_MAP("button1", keyboard_gpio_init(out, SDL_SCANCODE_1));
	GPIO_CONFIG_MAP("button2", keyboard_gpio_init(out, SDL_SCANCODE_2));
	GPIO_CONFIG_MAP("button3", keyboard_gpio_init(out, SDL_SCANCODE_3));
	GPIO_CONFIG_MAP("button4", keyboard_gpio_init(out, SDL_SCANCODE_4));
	GPIO_CONFIG_MAP("button5", keyboard_gpio_init(out, SDL_SCANCODE_5));
	//Switches
	GPIO_CONFIG_MAP("switch0", keyboard_gpio_init(out, SDL_SCANCODE_KP_0));
	GPIO_CONFIG_MAP("switch1", keyboard_gpio_init(out, SDL_SCANCODE_KP_1));
	GPIO_CONFIG_MAP("switch2", keyboard_gpio_init(out, SDL_SCANCODE_KP_2));
	GPIO_CONFIG_MAP("switch3", keyboard_gpio_init(out, SDL_SCANCODE_KP_3));
	return GPIO_CONFIG_NOT_FOUND;
}

int gpio_config_get_output(gpio_output_t *out, const char *gpio_name)
{
	return GPIO_CONFIG_NOT_FOUND;
}

/*****************************************************************************************
*                                    gpio_config.c
*****************************************************************************************/
