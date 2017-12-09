/*
 * timer.h
 *
 *  Created on: 15 Nov 2017
 *      Author: Jon Ayerdi
 */

#ifndef SRC_IO_TIMER_H_
#define SRC_IO_TIMER_H_

#include <stdint.h> /* uint64_t */

typedef uint64_t timer_tick_t;

typedef struct ttimer
{
	int(*start)(timer_tick_t period_msecs, void(*callback)(struct ttimer ttimer), void *context);
	void(*stop)(void *context);
	void(*destroy)(void *context);
	void(*callback)(struct ttimer ttimer);
	timer_tick_t period_msecs;
	volatile timer_tick_t ticks;
	void *context;
} ttimer_t;

int timer_start(ttimer_t timer, timer_tick_t period_msecs, void(*callback)(ttimer_t timer));
void timer_stop(ttimer_t timer);

timer_tick_t timer_get_ticks(ttimer_t timer);

void timer_destroy(ttimer_t timer);

#endif /* SRC_IO_TIMER_H_ */
