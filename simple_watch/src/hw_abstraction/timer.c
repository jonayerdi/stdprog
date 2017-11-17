/*
 * timer.c
 *
 *  Created on: 18 Oct 2017
 *      Author: Jon Ayerdi
 */

#include "timer.h"

static uint32_t _count;
static XScuTimer _timer;

static void (**_callbacks)(void);
static size_t _callback_count;

static void _timer_callback(XScuTimer *timer);

static void _timer_callback(XScuTimer *timer)
{
	_count++;
	for(size_t i = 0 ; i < _callback_count ; i++)
		_callbacks[i]();
	XScuTimer_ClearInterruptStatus(&_timer);
}

s32 timer_init(int msecs, void (**callbacks)(void), size_t callback_count)
{
	//Variables
	XScuTimer_Config *timer_config;
	s32 status;
	u32 load_value;
	u32 step = 1000/msecs;
	//Reset count
	_count = 0;
	//Setup callbacks
	_callbacks = callbacks;
	_callback_count = callback_count;
	//Configure timer
	timer_config = XScuTimer_LookupConfig(XPAR_SCUTIMER_DEVICE_ID);
	status = XScuTimer_CfgInitialize(&_timer, timer_config, timer_config->BaseAddr);
	if(status != XST_SUCCESS)
		return status;
	status = XScuTimer_SelfTest(&_timer);
	if(status != XST_SUCCESS)
		return status;
	XScuTimer_EnableAutoReload(&_timer);
	load_value = XPAR_CPU_CORTEXA9_0_CPU_CLK_FREQ_HZ / (step*2);
	XScuTimer_LoadTimer(&_timer, load_value);
	//Setup timer interrupts
	Xil_ExceptionInit();
	XScuGic_DeviceInitialize(XPAR_SCUGIC_SINGLE_DEVICE_ID);
	/*Connect the interrupt controller interrupt handler to the hardware interrupt handling logic in the processor*/
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_IRQ_INT, (Xil_ExceptionHandler)XScuGic_DeviceInterruptHandler, (void *)XPAR_SCUGIC_SINGLE_DEVICE_ID);
	/*Connect the device driver handler that will be called when an interrupt for the device occurs, the handler defined above performs
		the specific interrupt processing for the device.*/
	XScuGic_RegisterHandler(XPAR_SCUGIC_CPU_BASEADDR, XPAR_SCUTIMER_INTR, (Xil_ExceptionHandler)_timer_callback, (void *)&_timer);
	/*Enable the interrupt for scu timer.*/
	XScuGic_EnableIntr(XPAR_SCUGIC_DIST_BASEADDR, XPAR_SCUTIMER_INTR);
	//Enable timer interrupts
	Xil_ExceptionEnableMask(XIL_EXCEPTION_IRQ);
	XScuTimer_EnableInterrupt(&_timer);
	XScuTimer_Start(&_timer);
	return status;
}

void timer_halt(void)
{
	XScuTimer_Stop(&_timer);
	XScuTimer_DisableInterrupt(&_timer);
	Xil_ExceptionEnableMask(XIL_EXCEPTION_IRQ);
}

uint32_t timer_get_ticks(void)
{
	return _count;
}
