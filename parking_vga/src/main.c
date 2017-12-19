/*
 * main.c
 *
 *  Created on: 15 Nov 2017
 *      Author: Jon Ayerdi
 */

#include "config/logger.h"
#include "config/timer_config.h"

#include "domain/parking.h"

#define TIMER_PERIOD 10

static ttimer_t timer;
static parking_t parking;

static void _timer_callback(ttimer_t _timer);

static void _timer_callback(ttimer_t _timer)
{
	parking_step(&parking, _timer.period_msecs);
	if(!(timer_get_ticks(_timer) % (100 / _timer.period_msecs)))
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
	result = timer_start(&timer, TIMER_PERIOD, _timer_callback);
	if(result != 0)
	{
		LOG("[error] Starting timer");
		return 0;
	}

	/* Demo started */
	LOG("[done] Starting application\n");
	for(;;);
}
