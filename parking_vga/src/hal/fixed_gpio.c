/*************************************************************************************//**
* @file fixed_gpio.c
* @brief Implementation of constant value GPIOs
* @author Jon Ayerdi
*****************************************************************************************/

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/

#include "hal/fixed_gpio.h"

#include "io/memory.h"

/*--------------------------------------------------------------------------------------*/
/*                            		 PRIVATE FUNCTIONS                                  */
/*--------------------------------------------------------------------------------------*/

static gpio_value_t _get(void *context);
static void _destroy(void *context);

static gpio_value_t _get(void *context)
{
	fixed_gpio_t *gpio = (fixed_gpio_t *)context;
	return gpio->value;
}

static void _destroy(void *context)
{
	fixed_gpio_t *gpio = (fixed_gpio_t *)context;
	memory_free(gpio);
}

/*--------------------------------------------------------------------------------------*/
/*                             PUBLIC FUNCTION DEFINITIONS                              */
/*--------------------------------------------------------------------------------------*/

int fixed_gpio_input_init(gpio_input_t *out, gpio_value_t value)
{
	//Configure GPIO
	fixed_gpio_t *context = (fixed_gpio_t *)memory_allocate(sizeof(fixed_gpio_t));
	if(context == NULL)
		return MEMORY_ERROR;
	context->value = value;
	//Implement gpio_input_t
	out->get = _get;
	out->destroy = _destroy;
	out->context = context;
	return 0;
}

/*****************************************************************************************
*                                      fixed_gpio.c
*****************************************************************************************/
