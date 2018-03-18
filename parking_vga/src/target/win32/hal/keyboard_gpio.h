/*************************************************************************************//**
* @file keyboard_gpio.h
* @brief Implementation of keyboard key GPIOs with SDL
* @author Jon Ayerdi
*****************************************************************************************/
#ifndef SRC_HAL_KEYBOARD_GPIO_H_
#define SRC_HAL_KEYBOARD_GPIO_H_

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/

#include "io/gpio.h"

#include "SDL.h"

/*--------------------------------------------------------------------------------------*/
/*                            PUBLIC FUNCTION DECLARATIONS                              */
/*--------------------------------------------------------------------------------------*/

/** @brief initializes an input gpio that returns the state of the key.
 *  @param out the gpio.
 *  @param scancode the scancode of the key.
 *  @return 0 (OK) or nonzero (error).
 */
int keyboard_gpio_init(gpio_input_t *out, SDL_Scancode scancode);

#endif /* SRC_HAL_KEYBOARD_GPIO_H_ */

/*****************************************************************************************
*                                      keyboard_gpio.h
*****************************************************************************************/
