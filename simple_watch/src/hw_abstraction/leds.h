/*
 * leds.h
 *
 *  Created on: 29 Oct 2017
 *      Author: Jon Ayerdi
 */

#ifndef SRC_HW_ABSTRACTION_LEDS_H_
#define SRC_HW_ABSTRACTION_LEDS_H_

#include "gpio.h"

void leds_init(void);
void leds_set(u32 pin, u32 value);

#define hw_abstraction_led_4 7

#endif /* SRC_HW_ABSTRACTION_LEDS_H_ */
