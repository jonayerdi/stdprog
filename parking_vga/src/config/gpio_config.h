/*****************************************************************************************
*                                    gpio_config.h
******************************************************************************************
* AUTHOR: Jon Ayerdi
*
* DESCRIPTION: Mapping of gpio implementations to their names
*
*****************************************************************************************/
#ifndef SRC_CONFIG_GPIO_CONFIG_H_
#define SRC_CONFIG_GPIO_CONFIG_H_

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/
#include "io/gpio.h"

/*--------------------------------------------------------------------------------------*/
/*                                        MACROS                                        */
/*--------------------------------------------------------------------------------------*/
#define GPIO_CONFIG_NOT_FOUND -69

/*--------------------------------------------------------------------------------------*/
/*                            PUBLIC FUNCTION DECLARATIONS                              */
/*--------------------------------------------------------------------------------------*/

/** @brief gets an input gpio by name.
 *  @param out the gpio.
 *  @param gpio_name name of the gpio.
 *  @return 0 (OK) or nonzero (error).
 */
int gpio_config_get_input(gpio_input_t *out, const char *gpio_name);
/** @brief gets an output gpio by name.
 *  @param out the gpio.
 *  @param gpio_name name of the gpio.
 *  @return 0 (OK) or nonzero (error).
 */
int gpio_config_get_output(gpio_output_t *out, const char *gpio_name);

#endif /* SRC_CONFIG_GPIO_CONFIG_H_ */

/*****************************************************************************************
*                                    gpio_config.h
*****************************************************************************************/
