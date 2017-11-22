/***********************************************************************
*                              gpio.h
************************************************************************
* AUTHOR: Jon Ayerdi
*
* DESCRIPTION: Interfaces for input and output GPIOs.
*
***********************************************************************/

#ifndef SRC_IO_GPIO_H_
#define SRC_IO_GPIO_H_

/*--------------------------------------------------------------------*/
/*                              INCLUDES                              */
/*--------------------------------------------------------------------*/

/* External dependencies */
#include <xil_types.h>

/*--------------------------------------------------------------------*/
/*                               TYPES                                */
/*--------------------------------------------------------------------*/

typedef u32 gpio_value_t;

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

/*---------------------------------------------------------------------*/
/*                  PUBLIC FUNCTION DECLARATIONS                       */
/*---------------------------------------------------------------------*/

gpio_value_t gpio_get(gpio_input_t gpio);
void gpio_set(gpio_output_t gpio, gpio_value_t value);

void gpio_input_destroy(gpio_input_t gpio);
void gpio_output_destroy(gpio_output_t gpio);

#endif /* SRC_IO_GPIO_H_ */
/**********************************************************************/
/*                                  gpio.h                            */
/**********************************************************************/
