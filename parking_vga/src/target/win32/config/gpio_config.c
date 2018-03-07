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
	
	return GPIO_CONFIG_NOT_FOUND;
}

int gpio_config_get_output(gpio_output_t *out, const char *gpio_name)
{
	return GPIO_CONFIG_NOT_FOUND;
}

/*****************************************************************************************
*                                    gpio_config.c
*****************************************************************************************/