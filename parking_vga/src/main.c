/*
 * main.c
 *
 *  Created on: 15 Nov 2017
 *      Author: Jon Ayerdi
 */

#include "io/logger.h"
#include "io/timer.h"

#include "hal/scu_timer.h"

#include "domain/parking.h"

#define TIMER_PERIOD 10

static ttimer_t timer;
static parking_t parking;

static void _timer_callback(ttimer_t _timer);

static void _timer_callback(ttimer_t _timer)
{
	parking_step(parking, _timer.period_msecs);
	if(!(timer_get_ticks(_timer) % (100 / _timer.period_msecs)))
		parking_render(parking);
}

int main(void)
{
	/* Init logger */
	logger_init();

	/* Start the demo */
	LOG("[start] Starting application\n");

	/* Init parking */
	parking_init(&parking);

	/* Init timer */
	scu_timer_init(&timer);

	/* Start timer */
	timer_start(timer, TIMER_PERIOD, _timer_callback);

	/* Demo started */
	LOG("[done] Starting application\n");
}
