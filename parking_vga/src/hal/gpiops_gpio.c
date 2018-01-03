/*
 * gpiops_gpio.c
 *
 *  Created on: 17 Nov 2017
 *      Author: Jon Ayerdi
 */

#include "hal/gpiops_gpio.h"

#include "io/memory.h"

#include <xstatus.h>

#define GPIO_IN 0
#define GPIO_OUT 1

static gpio_value_t _get(void *context);
static void _set(gpio_value_t value, void *context);
static void _destroy(void *context);

static int gpiops_init(XGpioPs *gpio, gpiops_id_t id, u32 direction);

static gpio_value_t _get(void *context)
{
	gpiops_gpio_t *gpio = (gpiops_gpio_t *)context;
	return (gpio_value_t)XGpioPs_ReadPin(&gpio->gpio, gpio->pin);
}

static void _set(gpio_value_t value, void *context)
{
	gpiops_gpio_t *gpio = (gpiops_gpio_t *)context;
	XGpioPs_WritePin(&gpio->gpio, gpio->pin, (u32)value);
}

static void _destroy(void *context)
{
	gpiops_gpio_t *gpio = (gpiops_gpio_t *)context;
	memory_free(gpio);
}

static int gpiops_init(XGpioPs *gpio, gpiops_id_t id, u32 direction)
{
	//Variables
	XGpioPs_Config *config;
	s32 status;
	//Configure GPIO device
	config = XGpioPs_LookupConfig(id.device_id);
	XGpioPs_CfgInitialize(gpio, config, config->BaseAddr);
	//Run a self-test on the GPIO device
	status = XGpioPs_SelfTest(gpio);
	if(status != XST_SUCCESS)
		return status;
	XGpioPs_SetDirectionPin(gpio, id.pin, direction);
	if(direction == GPIO_OUT)
		XGpioPs_SetOutputEnablePin(gpio, id.pin, 1);
	return XST_SUCCESS;
}

int gpiops_input_init(gpio_input_t *out, gpiops_id_t id)
{
	//Variables
	XGpioPs gpio;
	s32 status;
	gpiops_gpio_t *context = (gpiops_gpio_t *)memory_allocate(sizeof(gpiops_gpio_t));
	if(context == NULL)
		return MEMORY_ERROR;
	//Configure GPIO device
	status = gpiops_init(&gpio, id, GPIO_IN);
	if(status != XST_SUCCESS)
	{
		memory_free(context);
		return status;
	}
	//Implement gpio_input_t
	context->gpio = gpio;
	context->pin = id.pin;
	out->get = _get;
	out->destroy = _destroy;
	out->context = context;
	return XST_SUCCESS;
}

int gpiops_output_init(gpio_output_t *out, gpiops_id_t id)
{
	//Variables
	XGpioPs gpio;
	s32 status;
	gpiops_gpio_t *context = (gpiops_gpio_t *)memory_allocate(sizeof(gpiops_gpio_t));
	if(context == NULL)
		return MEMORY_ERROR;
	//Configure GPIO device
	status = gpiops_init(&gpio, id, GPIO_OUT);
	if(status != XST_SUCCESS)
	{
		memory_free(context);
		return status;
	}
	//Implement gpio_input_t
	context->gpio = gpio;
	context->pin = id.pin;
	out->set = _set;
	out->destroy = _destroy;
	out->context = context;
	return XST_SUCCESS;
}
