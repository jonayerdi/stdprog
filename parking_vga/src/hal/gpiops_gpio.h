/*****************************************************************************************
*                                      gpiops_gpio.h
******************************************************************************************
* AUTHOR: Jon Ayerdi
*
* DESCRIPTION: Implementation of MIO/EMIO GPIOs for the ZYBO 7000 board
*
*****************************************************************************************/
#ifndef SRC_HAL_GPIOPS_GPIO_H_
#define SRC_HAL_GPIOPS_GPIO_H_

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/

#include "io/gpio.h"

#include <xil_types.h>
#include <xgpiops.h>
#include <xparameters.h>

/*--------------------------------------------------------------------------------------*/
/*                                        TYPES                                         */
/*--------------------------------------------------------------------------------------*/

typedef struct gpiops_id
{
	u16 device_id;
	u32 pin;
} gpiops_id_t;

typedef struct gpiops_gpio
{
	XGpioPs gpio;
	u32 pin;
} gpiops_gpio_t;

/*--------------------------------------------------------------------------------------*/
/*                            PUBLIC FUNCTION DECLARATIONS                              */
/*--------------------------------------------------------------------------------------*/

/** @brief initializes an input gpiops gpio.
 *  @param out the gpio.
 *  @param id id of the gpio.
 *  @return 0 (OK) or nonzero (error).
 */
int gpiops_input_init(gpio_input_t *out, gpiops_id_t id);
/** @brief initializes an output gpiops gpio.
 *  @param out the gpio.
 *  @param id id of the gpio.
 *  @return 0 (OK) or nonzero (error).
 */
int gpiops_output_init(gpio_output_t *out, gpiops_id_t id);

#endif /* SRC_HAL_GPIOPS_GPIO_H_ */

/*****************************************************************************************
*                                      gpiops_gpio.h
*****************************************************************************************/
