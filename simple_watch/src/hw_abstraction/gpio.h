/*
 * gpio.h
 *
 *  Created on: 29 Oct 2017
 *      Author: Jon Ayerdi
 */

#ifndef SRC_HW_ABSTRACTION_GPIO_H_
#define SRC_HW_ABSTRACTION_GPIO_H_

#define GPIO_IN 0
#define GPIO_OUT 1

#include <xstatus.h>
#include <xgpiops.h>
#include <xparameters.h>
#include <xil_exception.h>
#include <xscugic.h>

s32 gpio_init(void);
s32 gpio_init_interrupts(void (**handlers)(void), size_t handlers_count);
void gpio_set_direction(u32 pin, u32 direction);
u32 gpio_read(u32 pin);
void gpio_write(u32 pin, u32 value);

#endif /* SRC_HW_ABSTRACTION_GPIO_H_ */
