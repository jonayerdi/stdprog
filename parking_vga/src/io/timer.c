/*
 * timer.c
 *
 *  Created on: 15 Nov 2017
 *      Author: Jon Ayerdi
 */

#include "io/timer.h"

static void _timer_handler(ttimer_t timer);

static void _timer_handler(ttimer_t timer)
{
	timer.ticks++;
	if(timer.callback)
		timer.callback(timer);
}

inline int timer_start(ttimer_t timer, timer_tick_t period_msecs, void(*callback)(ttimer_t timer))
{
	timer.callback = callback;
	timer.period_msecs = period_msecs;
	timer.ticks = 0;
	return timer.start(period_msecs, _timer_handler, timer.context);
}

inline void timer_stop(ttimer_t timer)
{
	timer.stop(timer.context);
}

inline timer_tick_t timer_get_ticks(ttimer_t timer)
{
	return timer.ticks;
}

inline void timer_destroy(ttimer_t timer)
{
	timer.destroy(timer.context);
}
