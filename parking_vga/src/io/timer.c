/*
 * timer.c
 *
 *  Created on: 15 Nov 2017
 *      Author: Jon Ayerdi
 */

#include "io/timer.h"

static void _timer_callback(timer_t timer);

static void _timer_callback(timer_t timer)
{
	if(timer.callback)
		timer.callback(timer);
	timer.ticks++;
}

inline int timer_start(timer_t timer, timer_tick_t period_msecs, void(*callback)(timer_t timer))
{
	timer.callback = callback;
	timer.period_msecs = period_msecs;
	timer.ticks = 0;
	return timer.start(msecs, _timer_callback, timer.context);
}

inline int timer_stop(timer_t timer)
{
	return timer.stop(timer.context);
}

inline timer_tick_t timer_get_ticks(timer_t timer)
{
	return timer.ticks;
}

inline void timer_destroy(timer_t timer)
{
	timer.destroy(timer.context);
}
