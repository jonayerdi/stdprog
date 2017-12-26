/*
 * scu_timer.c
 *
 *  Created on: 8 Dec 2017
 *      Author: Jon Ayerdi
 */

#include "hal/scu_timer.h"

#include "io/memory.h"

#include <xscugic.h>
#include <stdint.h>

static int _start(uint32_t freq, void(*timer_handler)(ttimer_t *timer), void *context);
static void _stop(void *context);
static void _destroy(void *context);
static void _scu_timer_handler(scu_timer_t *timer);

static int _start(uint32_t freq, void(*timer_handler)(ttimer_t *timer), void *context)
{
	scu_timer_t *scu_timer = (scu_timer_t *)context;
	scu_timer->timer_handler = timer_handler;
	XScuTimer *timer = &scu_timer->driver;
	//Variables
	XScuTimer_Config *timer_config;
	s32 status;
	u32 load_value;
	//Configure timer
	timer_config = XScuTimer_LookupConfig(XPAR_SCUTIMER_DEVICE_ID);
	status = XScuTimer_CfgInitialize(timer, timer_config, timer_config->BaseAddr);
	if(status != XST_SUCCESS)
	{
		//Stop the timer if needed
		if(status == XST_DEVICE_IS_STARTED)
		{
			_stop(scu_timer);
			status = XScuTimer_CfgInitialize(timer, timer_config, timer_config->BaseAddr);
			if(status != XST_SUCCESS)
				return status;
		}
		else
			return status;
	}
	status = XScuTimer_SelfTest(timer);
	if(status != XST_SUCCESS)
		return status;
	XScuTimer_EnableAutoReload(timer);
	load_value = XPAR_CPU_CORTEXA9_0_CPU_CLK_FREQ_HZ / (freq*2);
	XScuTimer_LoadTimer(timer, load_value);
	//Setup timer interrupts
	Xil_ExceptionInit();
	XScuGic_DeviceInitialize(XPAR_SCUGIC_SINGLE_DEVICE_ID);
	//Connect the interrupt controller interrupt handler to the hardware interrupt handling logic in the processor
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_IRQ_INT, (Xil_ExceptionHandler)XScuGic_DeviceInterruptHandler, (void *)XPAR_SCUGIC_SINGLE_DEVICE_ID);
	//Connect the device driver handler that will be called when an interrupt for the device occurs
	XScuGic_RegisterHandler(XPAR_SCUGIC_CPU_BASEADDR, XPAR_SCUTIMER_INTR, (Xil_ExceptionHandler)_scu_timer_handler, (void *)scu_timer);
	//Enable the interrupt for scu timer.
	XScuGic_EnableIntr(XPAR_SCUGIC_DIST_BASEADDR, XPAR_SCUTIMER_INTR);
	//Enable timer interrupts
	Xil_ExceptionEnableMask(XIL_EXCEPTION_IRQ);
	XScuTimer_EnableInterrupt(timer);
	//Start the timer
	XScuTimer_Start(timer);
	return status;
}

static void _stop(void *context)
{
	scu_timer_t *scu_timer = (scu_timer_t *)context;
	XScuTimer *timer = &scu_timer->driver;
	XScuTimer_Stop(timer);
	XScuTimer_DisableInterrupt(timer);
	Xil_ExceptionDisableMask(XIL_EXCEPTION_IRQ);
	XScuGic_DisableIntr(XPAR_SCUGIC_DIST_BASEADDR, XPAR_SCUTIMER_INTR);
	Xil_ExceptionRemoveHandler(XIL_EXCEPTION_ID_IRQ_INT);
}

static void _destroy(void *context)
{
	scu_timer_t *scu_timer = (scu_timer_t *)context;
	memory_free(scu_timer);
}

static void _scu_timer_handler(scu_timer_t *scu_timer)
{
	scu_timer->timer_handler(scu_timer->timer);
	XScuTimer_ClearInterruptStatus(&scu_timer->driver);
}

int scu_timer_init(ttimer_t *output)
{
	//Allocate and init scu_timer_t instance
	scu_timer_t *scu_timer = (scu_timer_t *)memory_allocate(sizeof(scu_timer_t));
	if(scu_timer == NULL)
		return MEMORY_ERROR;
	scu_timer->timer = output;
	//Implement timer interface
	output->context = (void *)scu_timer;
	output->start = _start;
	output->stop = _stop;
	output->destroy = _destroy;
	return 0;
}
