/*************************************************************************************//**
* @file gpio.h
* @brief Interfaces for input and output GPIOs
* @author Jon Ayerdi
*****************************************************************************************/
#ifndef SRC_IO_GPIO_H_
#define SRC_IO_GPIO_H_

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/

#include <stdint.h> /* uint32_t */

/*--------------------------------------------------------------------------------------*/
/*                                        TYPES                                         */
/*--------------------------------------------------------------------------------------*/

typedef uint32_t gpio_value_t;

typedef struct gpio_input
{
	gpio_value_t(*get)(void *context);
	void(*destroy)(void *context);
	void *context;
} gpio_input_t;

typedef struct gpio_output
{
	void(*set)(gpio_value_t value, void *context);
	void(*destroy)(void *context);
	void *context;
} gpio_output_t;

/*--------------------------------------------------------------------------------------*/
/*                           PUBLIC FUNCTION DECLARATIONS                               */
/*--------------------------------------------------------------------------------------*/

/** @brief reads a value from the given gpio.
 *  @param gpio the source gpio.
 *  @return the value read from the source gpio.
 */
gpio_value_t gpio_get(gpio_input_t gpio);
/** @brief writes a value to the given gpio.
 *  @param gpio the target gpio.
 *  @param value the value to write to the gpio
 */
void gpio_set(gpio_output_t gpio, gpio_value_t value);

/** @brief destroys the given gpio.
 *  @param gpio the target gpio.
 */
void gpio_input_destroy(gpio_input_t gpio);
/** @brief destroys the given gpio.
 *  @param gpio the target gpio.
 */
void gpio_output_destroy(gpio_output_t gpio);

#endif /* SRC_IO_GPIO_H_ */

/****************************************************************************************
*                                      gpio.h
****************************************************************************************/
