/*
 * timer.h
 *
 *  Created on: 18 Oct 2017
 *      Author: Jon Ayerdi
 */

#ifndef SRC_HW_ABSTRACTION_TIMER_H_
#define SRC_HW_ABSTRACTION_TIMER_H_

#include <xscutimer.h>
#include <xscugic.h>
#include <stdint.h>

s32 timer_init(int msecs, void (**callbacks)(void), size_t callback_count);
void timer_halt(void);
uint32_t timer_get_ticks(void);

#endif /* SRC_HW_ABSTRACTION_TIMER_H_ */
