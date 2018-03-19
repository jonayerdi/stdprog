/*************************************************************************************//**
* @file sdl_timer.h
* @brief Implementation of SDL timer
* @author Jon Ayerdi
*****************************************************************************************/
#ifndef SRC_HAL_SDL_TIMER_H_
#define SRC_HAL_SDL_TIMER_H_

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/

#include "io/timer.h"

#include "SDL.h"

/*--------------------------------------------------------------------------------------*/
/*                                        TYPES                                         */
/*--------------------------------------------------------------------------------------*/

typedef struct sdl_timer
{
    char stop;
    void(*timer_handler)(ttimer_t *timer);
    ttimer_t *timer;
	SDL_Thread *thread;
} sdl_timer_t;

/*--------------------------------------------------------------------------------------*/
/*                            PUBLIC FUNCTION DECLARATIONS                              */
/*--------------------------------------------------------------------------------------*/

/** @brief initializes the SDL timer.
 *  @param output the timer.
 *  @return 0 (OK) or nonzero (error).
 */
int sdl_timer_init(ttimer_t *output);

/** @brief stops all sdl_timer instances. This prevents new sdl_timer instances from working. Use on application exit.
 */
void sdl_timer_stop_all(void);

#endif /* SRC_HAL_SDL_TIMER_H_ */

/*****************************************************************************************
*                                      sdl_timer.h
*****************************************************************************************/
