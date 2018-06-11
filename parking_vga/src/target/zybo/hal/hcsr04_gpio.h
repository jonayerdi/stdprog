/*************************************************************************************//**
* @file hcsr04_gpio.c
* @brief Implementation of HCSR04 sensor GPIOs for the ZYBO 7000 board
* @author Jon Ayerdi
*****************************************************************************************/
#ifndef SRC_HAL_HCSR04_GPIO_H_
#define SRC_HAL_HCSR04_GPIO_H_

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/

#include "io/gpio.h"

#include <xil_types.h>
#include <xgpio.h>
#include <xparameters.h>

/*--------------------------------------------------------------------------------------*/
/*                                        TYPES                                         */
/*--------------------------------------------------------------------------------------*/

typedef struct hcsr04_gpio_id
{
	u16 device_id;
} hcsr04_gpio_id_t;

typedef struct hcsr04_gpio
{
	XGpio gpio;
} hcsr04_gpio_t;

/*--------------------------------------------------------------------------------------*/
/*                            PUBLIC FUNCTION DECLARATIONS                              */
/*--------------------------------------------------------------------------------------*/

/** @brief initializes an input axi gpio.
 *  @param out the gpio.
 *  @param id id of the gpio.
 *  @return 0 (OK) or nonzero (error).
 */
int hcsr04_gpio_init(gpio_input_t *out, hcsr04_gpio_id_t id);

#endif /* SRC_HAL_HCSR04_GPIO_H_ */

/*****************************************************************************************
*                                      hcsr04_gpio.h
*****************************************************************************************/
