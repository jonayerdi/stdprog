/*
 * gpio.c
 *
 *  Created on: 29 Oct 2017
 *      Author: Jon Ayerdi
 */

#include "gpio.h"

static XGpioPs _gpio0;

static void (**_handlers)(void);
static size_t _handlers_count = 0;

static void _interrupt_handler(void *arg, u32 bank, u32 status)
{
	for(size_t i = 0 ; i < _handlers_count ; i++)
		_handlers[i]();
}

s32 gpio_init(void)
{
	//Variables
	XGpioPs_Config *config0;
	s32 status = XST_SUCCESS;
	//Configure GPIO device
	config0 = XGpioPs_LookupConfig(XPAR_PS7_GPIO_0_DEVICE_ID);
	XGpioPs_CfgInitialize(&_gpio0, config0, config0->BaseAddr);
	//Run a self-test on the GPIO device
	status = XGpioPs_SelfTest(&_gpio0);
	return status;
}

s32 gpio_init_interrupts(void (**handlers)(void), size_t handlers_count)
{
	//Variables
	s32 status;
	XScuGic_Config *interruptConfig;
	XScuGic interrupt;
	//Initialize
	Xil_ExceptionInit();
	interruptConfig = XScuGic_LookupConfig(XPAR_SCUGIC_SINGLE_DEVICE_ID);
	status = XScuGic_CfgInitialize(&interrupt, interruptConfig, interruptConfig->CpuBaseAddress);
	if(status != XST_SUCCESS)
		return status;
	/*
	 * Connect the interrupt controller interrupt handler to the hardware
	 * interrupt handling logic in the processor.
	 */
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XScuGic_InterruptHandler, &interrupt);
	/*
	 * Connect the device driver handler that will be called when an
	 * interrupt for the device occurs, the handler defined above performs
	 * the specific interrupt processing for the device.
	 */
	status = XScuGic_Connect(&interrupt, XPAR_XGPIOPS_0_INTR, (Xil_ExceptionHandler)XGpioPs_IntrHandler, &_gpio0);
	if (status != XST_SUCCESS)
		return status;
	/* Enable falling edge interrupts for all the pins in banks 0 1 2 3. */
	XGpioPs_SetIntrType(&_gpio0, XGPIOPS_BANK0, 0x00, 0xFFFFFFFF, 0x00);
	XGpioPs_SetIntrType(&_gpio0, XGPIOPS_BANK1, 0x00, 0xFFFFFFFF, 0x00);
	XGpioPs_SetIntrType(&_gpio0, XGPIOPS_BANK2, 0x00, 0xFFFFFFFF, 0x00);
	XGpioPs_SetIntrType(&_gpio0, XGPIOPS_BANK3, 0x00, 0xFFFFFFFF, 0x00);
	/* Set the handler for gpio interrupts. */
	XGpioPs_SetCallbackHandler(&_gpio0, (void *)&_gpio0, _interrupt_handler);
	/* Enable the GPIO interrupts of Banks 0 1 2 3. */
	XGpioPs_IntrEnable(&_gpio0, XGPIOPS_BANK0, 0xFFFFFFFF);
	XGpioPs_IntrEnable(&_gpio0, XGPIOPS_BANK1, 0xFFFFFFFF);
	XGpioPs_IntrEnable(&_gpio0, XGPIOPS_BANK2, 0xFFFFFFFF);
	XGpioPs_IntrEnable(&_gpio0, XGPIOPS_BANK3, 0xFFFFFFFF);
	/* Enable the interrupt for the GPIO device. */
	XScuGic_Enable(&interrupt, XPAR_XGPIOPS_0_INTR);
	/* Enable interrupts in the Processor. */
	Xil_ExceptionEnableMask(XIL_EXCEPTION_IRQ);
	//Setup handlers
	_handlers = handlers;
	_handlers_count = handlers_count;
	//Return
	return XST_SUCCESS;
}

void gpio_set_direction(u32 pin, u32 direction)
{
	XGpioPs_SetDirectionPin(&_gpio0, pin, direction);
	if(direction == GPIO_OUT)
		XGpioPs_SetOutputEnablePin(&_gpio0, pin, 1);
}

u32 inline gpio_read(u32 pin)
{
	return XGpioPs_ReadPin(&_gpio0, pin);
}

void inline gpio_write(u32 pin, u32 data)
{
	XGpioPs_WritePin(&_gpio0, pin, data);
}
