/*****************************************************************************************
*                                      axi_gpio.h
******************************************************************************************
* AUTHOR: Jon Ayerdi
*
* DESCRIPTION: Implementation of AXI GPIOs for the ZYBO 7000 board
*
*****************************************************************************************/
#ifndef SRC_HAL_AXI_GPIO_H_
#define SRC_HAL_AXI_GPIO_H_

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

typedef struct axi_gpio_id
{
	u16 device_id;
	u16 channel;
	u32 pin;
} axi_gpio_id_t;

typedef struct axi_gpio
{
	XGpio gpio;
	u16 channel;
	u32 pin;
} axi_gpio_t;

/*--------------------------------------------------------------------------------------*/
/*                            PUBLIC FUNCTION DECLARATIONS                              */
/*--------------------------------------------------------------------------------------*/

/** @brief initializes an input axi gpio.
 *  @param out the gpio.
 *  @param id id of the gpio.
 *  @return 0 (OK) or nonzero (error).
 */
int axi_gpio_input_init(gpio_input_t *out, axi_gpio_id_t id);
/** @brief initializes an output axi gpio.
 *  @param out the gpio.
 *  @param id id of the gpio.
 *  @return 0 (OK) or nonzero (error).
 */
int axi_gpio_output_init(gpio_output_t *out, axi_gpio_id_t id);

#endif /* SRC_HAL_AXI_GPIO_H_ */

/*****************************************************************************************
*                                      axi_gpio.h
*****************************************************************************************/
