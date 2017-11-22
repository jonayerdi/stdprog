/*****************************************************************************************
*                                        gpio.c                                          *
******************************************************************************************
* AUTHOR: Jon Ayerdi
*
* DESCRIPTION: Interfaces for input and output GPIOs.
*
*****************************************************************************************/

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/

/* Module declarations */
#include "io/gpio.h"

/*--------------------------------------------------------------------------------------*/
/*                             PUBLIC FUNCTION DEFINITIONS                              */
/*--------------------------------------------------------------------------------------*/

inline gpio_value_t gpio_get(gpio_input_t gpio)
{
	return gpio.get(gpio.context);
}

inline void gpio_set(gpio_output_t gpio, gpio_value_t value)
{
	gpio.set(value, gpio.context);
}

inline void gpio_input_destroy(gpio_input_t gpio)
{
	gpio.destroy(gpio.context);
}

inline void gpio_output_destroy(gpio_output_t gpio)
{
	gpio.destroy(gpio.context);
}


/****************************************************************************************/
/*                                       gpio.c                                         */
/****************************************************************************************/
