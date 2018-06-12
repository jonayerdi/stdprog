/*************************************************************************************//**
* @file hcsr04_gpio.c
* @brief Implementation of HCSR04 sensor GPIOs for the ZYBO 7000 board
* @author Jon Ayerdi
*****************************************************************************************/

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/
#include "hcsr04_gpio.h"

#include "io/memory.h"

#include <xstatus.h>

/*--------------------------------------------------------------------------------------*/
/*                                        MACROS                                        */
/*--------------------------------------------------------------------------------------*/

#define AXI_IN 1
#define AXI_OUT 0

//AXI pins
#define RESET_PIN 0
#define ENABLE_PIN 1
#define READY_PIN 0
#define PRESENCE_PIN 1
#define DATA_PIN 2
//AXI channels
#define WRITE_CHANNEL 1
#define READ_CHANNEL 2

//Util
#define XGpio_SetDataDirectionPin(axi, cha, pin, dir) \
	dir ? XGpio_SetDataDirection(axi, cha, XGpio_GetDataDirection(axi, cha) | 1<<pin) \
		: XGpio_SetDataDirection(axi, cha, XGpio_GetDataDirection(axi, cha) & ~(1<<pin))
#define XGpio_WritePin(axi, cha, pin, val) \
	val ? XGpio_DiscreteSet(axi, cha, 1<<pin) \
		: XGpio_DiscreteClear(axi, cha, 1<<pin)

/*--------------------------------------------------------------------------------------*/
/*                            		 PRIVATE FUNCTIONS                                  */
/*--------------------------------------------------------------------------------------*/

static gpio_value_t _get(void *context);
static void _destroy(void *context);
static void _reset(void *context);

static gpio_value_t _get(void *context)
{
	hcsr04_gpio_t *gpio = (hcsr04_gpio_t *)context;
	XGpio axi = gpio->gpio;
	volatile u32 reg0;
	volatile u32 count;
	volatile u32 reset;
	do
	{
		//Reset variables
		reg0 = 0;
		count = 0;
		reset = 0;
		//Set enable pin
		XGpio_WritePin(&axi, WRITE_CHANNEL, ENABLE_PIN, 1);
		while(!(reg0 & (1<<READY_PIN)))
		{
			//Read register
			reg0 = XGpio_DiscreteRead(&axi, READ_CHANNEL);
			if(count++ > 1000000)
			{
				//Reset HC_SR04 via AXI
				_reset(context);
				reset = 1;
				break;
			}
		}
		//Reset enable pin
		XGpio_WritePin(&axi, WRITE_CHANNEL, ENABLE_PIN, 0);
	} while(reset);
	return (gpio_value_t)!!(reg0 & (1<<PRESENCE_PIN));
}

static void _destroy(void *context)
{
	hcsr04_gpio_t *gpio = (hcsr04_gpio_t *)context;
	memory_free(gpio);
}

static void _reset(void *context)
{
	hcsr04_gpio_t *gpio = (hcsr04_gpio_t *)context;
	XGpio_WritePin(&gpio->gpio, WRITE_CHANNEL, RESET_PIN, 1);
	for(volatile int i = 0 ; i < 1000 ; i++) {i=i;};
	XGpio_WritePin(&gpio->gpio, WRITE_CHANNEL, RESET_PIN, 0);
}

/*--------------------------------------------------------------------------------------*/
/*                             PUBLIC FUNCTION DEFINITIONS                              */
/*--------------------------------------------------------------------------------------*/

int hcsr04_gpio_init(gpio_input_t *out, hcsr04_gpio_id_t id)
{
	//Variables
	XGpio axi;
	s32 status;
	hcsr04_gpio_t *context = memory_allocate(sizeof(hcsr04_gpio_t));
	if(context == NULL)
		return MEMORY_ERROR;
	//Configure AXI
	status = XGpio_Initialize(&axi, id.device_id);
	if(status != XST_SUCCESS)
	{
		memory_free(context);
		return status;
	}
	XGpio_SetDataDirection(&axi, WRITE_CHANNEL, 0x00000000);
	XGpio_SetDataDirection(&axi, READ_CHANNEL, 0xFFFFFFFF);
	//Reset HC_SR04 via AXI
	context->gpio = axi;
	_reset(context);
	//Implement gpio_input_t
	out->get = _get;
	out->destroy = _destroy;
	out->context = context;
	return XST_SUCCESS;
}

/*****************************************************************************************
*                                      hcsr04_gpio.c
*****************************************************************************************/
