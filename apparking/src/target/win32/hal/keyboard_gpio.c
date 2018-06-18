/*************************************************************************************//**
* @file keyboard_gpio.c
* @brief Implementation of keyboard key GPIOs with SDL
* @author Jon Ayerdi
*****************************************************************************************/

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/

#include "hal/keyboard_gpio.h"

#include "hal/sdl_global.h"

#include "io/memory.h"

#include <stdio.h>

/*--------------------------------------------------------------------------------------*/
/*                            		 PRIVATE FUNCTIONS                                  */
/*--------------------------------------------------------------------------------------*/

static gpio_value_t _get(void *context);
static void _destroy(void *context);

static gpio_value_t _get(void *context)
{
	SDL_Scancode *scancode = (SDL_Scancode *)context;
	const Uint8 *keyboard = SDL_GetKeyboardState(NULL);
	return (gpio_value_t)keyboard[*scancode];
}

static void _destroy(void *context)
{
	memory_free(context);
}

/*--------------------------------------------------------------------------------------*/
/*                             PUBLIC FUNCTION DEFINITIONS                              */
/*--------------------------------------------------------------------------------------*/

int keyboard_gpio_init(gpio_input_t *out, SDL_Scancode scancode)
{
	//Init SDL if needed
    int status = sdl_init_if_needed();
	if(status)
        return status;
    //Configure GPIO
	SDL_Scancode *context = (SDL_Scancode *)memory_allocate(sizeof(SDL_Scancode));
	if(context == NULL)
		return MEMORY_ERROR;
	*context = scancode;
	//Implement gpio_input_t
	out->get = _get;
	out->destroy = _destroy;
	out->context = context;
	return 0;
}

/*****************************************************************************************
*                                      keyboard_gpio.c
*****************************************************************************************/