/*
 * scu_timer.h
 *
 *  Created on: 8 Dec 2017
 *      Author: Jon Ayerdi
 */

#ifndef SRC_HAL_SCU_TIMER_H_
#define SRC_HAL_SCU_TIMER_H_

#include "io/timer.h"

#include <xscutimer.h>

typedef struct scu_timer
{
	XScuTimer driver;
	ttimer_t *timer;
	void (*timer_handler)(ttimer_t *timer);
} scu_timer_t;

int scu_timer_init(ttimer_t *output);

#endif /* SRC_HAL_SCU_TIMER_H_ */
