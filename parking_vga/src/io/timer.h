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

typedef struct timer
{
	int(*start)(timer_tick_t period_msecs, void(*callback)(timer_t timer), void *context);
	int(*stop)(void *context);
	void(*destroy)(void *context);
	void(*callback)(timer_t timer);
	timer_tick_t period_msecs;
	volatile timer_tick_t ticks;
	void *context;
} timer_t;

int timer_start(timer_t timer, timer_tick_t period_msecs, void(*callback)(timer_t timer));
int timer_stop(timer_t timer);

timer_tick_t timer_get_ticks(timer_t timer);

void timer_destroy(timer_t timer);

#endif /* SRC_IO_TIMER_H_ */
