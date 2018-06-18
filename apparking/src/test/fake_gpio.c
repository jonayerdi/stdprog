/*************************************************************************************//**
* @file fake_gpio.h
* @brief Implementation of fake GPIOs
* @author Jon Ayerdi
*****************************************************************************************/

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/

#include "fake_gpio.h"

#include "io/memory.h"

/*--------------------------------------------------------------------------------------*/
/*                            		 PRIVATE FUNCTIONS                                  */
/*--------------------------------------------------------------------------------------*/

static gpio_value_t _get(void *context);
static void _set(gpio_value_t value, void *context);
static void _destroy(void *context);

static gpio_value_t _get(void *context)
{
	fake_gpio_t *gpio = (fake_gpio_t *)context;
	return gpio->value;
}

static void _set(gpio_value_t value, void *context)
{
	fake_gpio_t *gpio = (fake_gpio_t *)context;
	gpio->value = value;
}

static void _destroy(void *context)
{
	fake_gpio_t *gpio = (fake_gpio_t *)context;
	memory_free(gpio);
}

/*--------------------------------------------------------------------------------------*/
/*                             PUBLIC FUNCTION DEFINITIONS                              */
/*--------------------------------------------------------------------------------------*/

int fake_gpio_input_init(gpio_input_t *out)
{
	//Configure GPIO
	fake_gpio_t *context = (fake_gpio_t *)memory_allocate(sizeof(fake_gpio_t));
	if(context == NULL)
		return MEMORY_ERROR;
	context->value = 0;
	//Implement gpio_input_t
	out->get = _get;
	out->destroy = _destroy;
	out->context = context;
	return 0;
}

int fake_gpio_output_init(gpio_output_t *out)
{
    //Configure GPIO
	fake_gpio_t *context = (fake_gpio_t *)memory_allocate(sizeof(fake_gpio_t));
	if(context == NULL)
		return MEMORY_ERROR;
	context->value = 0;
	//Implement gpio_input_t
	out->set = _set;
	out->destroy = _destroy;
	out->context = context;
	return 0;
}

void fake_gpio_set_value(gpio_input_t *gpio, gpio_value_t value)
{
    ((fake_gpio_t *)gpio->context)->value = value;
}

gpio_value_t fake_gpio_get_value(gpio_output_t *gpio)
{
    return ((fake_gpio_t *)gpio->context)->value;
}

/*****************************************************************************************
*                                      fake_gpio.c
*****************************************************************************************/
