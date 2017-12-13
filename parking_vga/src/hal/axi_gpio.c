/*
 * axi_gpio.c
 *
 *  Created on: 13 Dec 2017
 *      Author: Jon Ayerdi
 */

#include "axi_gpio.h"

#include "io/memory.h"

#include <xstatus.h>

#define AXI_IN 1
#define AXI_OUT 0

#define XGpio_SetDataDirectionPin(axi, cha, pin, dir) \
	dir ? XGpio_SetDataDirection(axi, cha, XGpio_GetDataDirection(axi, cha) | 1 << pin) \
		: XGpio_SetDataDirection(axi, cha, XGpio_GetDataDirection(axi, cha) & ~(1 << pin))
#define XGpio_ReadPin(axi, cha, pin) (!!(XGpio_DiscreteRead(axi, cha) & (1 << pin)))
#define XGpio_WritePin(axi, cha, pin, val) \
	val ? XGpio_DiscreteSet(axi, cha, 1 << pin) \
		: XGpio_DiscreteClear(axi, cha, 1 << pin)

static gpio_value_t _get(void *context);
static void _set(gpio_value_t value, void *context);

static gpio_value_t _get(void *context)
{
	axi_gpio_t *gpio = (axi_gpio_t *)context;
	return (gpio_value_t)XGpio_ReadPin(&gpio->gpio, gpio->channel, gpio->pin);
}

static void _set(gpio_value_t value, void *context)
{
	axi_gpio_t *gpio = (axi_gpio_t *)context;
	XGpio_WritePin(&gpio->gpio, gpio->channel, gpio->pin, value);
}

static void _destroy(void *context)
{
	axi_gpio_t *gpio = (axi_gpio_t *)context;
	memory_free(gpio);
}

int axi_gpio_input_init(gpio_input_t *out, axi_gpio_id_t id)
{
	//Variables
	XGpio axi;
	s32 status;
	axi_gpio_t *context = (axi_gpio_t *)memory_allocate(sizeof(axi_gpio_t));
	//Configure AXI
	status = XGpio_Initialize(&axi, id.device_id);
	if(status != XST_SUCCESS)
		return status;
	XGpio_SetDataDirectionPin(&axi, id.channel, id.pin, AXI_IN);
	//Implement gpio_input_t
	context->gpio = axi;
	context->channel = id.channel;
	context->pin = id.pin;
	out->get = _get;
	out->destroy = _destroy;
	out->context = context;
	return XST_SUCCESS;
}

int axi_gpio_output_init(gpio_output_t *out, axi_gpio_id_t id)
{
	//Variables
	XGpio axi;
	s32 status;
	axi_gpio_t *context = (axi_gpio_t *)memory_allocate(sizeof(axi_gpio_t));
	//Configure AXI
	status = XGpio_Initialize(&axi, id.device_id);
	if(status != XST_SUCCESS)
		return status;
	XGpio_SetDataDirectionPin(&axi, id.channel, id.pin, AXI_OUT);
	//Implement gpio_input_t
	context->gpio = axi;
	context->channel = id.channel;
	context->pin = id.pin;
	out->set = _set;
	out->destroy = _destroy;
	out->context = context;
	return XST_SUCCESS;
}
