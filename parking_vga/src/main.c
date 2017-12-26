/*
 * main.c
 *
 *  Created on: 15 Nov 2017
 *      Author: Jon Ayerdi
 */

#include "config/logger.h"
#include "config/timer_config.h"

#include "domain/parking.h"

#define TIMER_FREQ 60

static ttimer_t timer;
static parking_t parking;

static void _timer_callback(ttimer_t _timer);

static void _timer_callback(ttimer_t _timer)
{
	parking_step(&parking, 60);
	parking_render(parking);
}

int main(void)
{
	int result;

	/* Init logger */
	logger_init();

	/* Start the demo */
	LOG("[start] Starting application\n");

	/* Init parking */
	result = parking_init(&parking);
	if(result != 0)
	{
		LOG("[error] Parking init");
		return 0;
	}

	/* Init timer */
	result = timer_config_get_default(&timer);
	if(result != 0)
	{
		LOG("[error] SCU Timer init");
		return 0;
	}

	/* Start timer */
	result = timer_start(&timer, TIMER_FREQ, _timer_callback);
	if(result != 0)
	{
		LOG("[error] Starting timer");
		return 0;
	}

	/* Demo started */
	LOG("[done] Starting application\n");
	for(;;);
}
