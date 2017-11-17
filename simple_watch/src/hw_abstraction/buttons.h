/*
 * buttons.h
 *
 *  Created on: 23 Oct 2017
 *      Author: Jon Ayerdi
 */

#ifndef SRC_HW_ABSTRACTION_BUTTONS_H_
#define SRC_HW_ABSTRACTION_BUTTONS_H_

#include "gpio.h"

void buttons_init(void);
u32 buttons_get(u32 pin);

#define hw_abstraction_button_1 50
#define hw_abstraction_button_2 51

#endif /* SRC_HW_ABSTRACTION_BUTTONS_H_ */
