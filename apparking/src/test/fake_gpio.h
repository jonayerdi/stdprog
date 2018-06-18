/*************************************************************************************//**
* @file fake_gpio.h
* @brief Implementation of fake GPIOs
* @author Jon Ayerdi
*****************************************************************************************/
#ifndef SRC_TEST_FAKE_GPIO_H_
#define SRC_TEST_FAKE_GPIO_H_

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/

#include "io/gpio.h"

/*--------------------------------------------------------------------------------------*/
/*                                        TYPES                                         */
/*--------------------------------------------------------------------------------------*/
typedef struct fake_gpio
{
	gpio_value_t value;
} fake_gpio_t;

/*--------------------------------------------------------------------------------------*/
/*                            PUBLIC FUNCTION DECLARATIONS                              */
/*--------------------------------------------------------------------------------------*/

/** @brief initializes an input fake gpio.
 *  @param out the gpio.
 *  @return 0 (OK) or nonzero (error).
 */
int fake_gpio_input_init(gpio_input_t *out);
/** @brief initializes an output fake gpio.
 *  @param out the gpio.
 *  @return 0 (OK) or nonzero (error).
 */
int fake_gpio_output_init(gpio_output_t *out);

void fake_gpio_set_value(gpio_input_t *gpio, gpio_value_t value);

gpio_value_t fake_gpio_get_value(gpio_output_t *gpio);

#endif /* SRC_TEST_FAKE_GPIO_H_ */

/*****************************************************************************************
*                                      fake_gpio.h
*****************************************************************************************/
