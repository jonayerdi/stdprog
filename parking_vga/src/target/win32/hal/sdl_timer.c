/*************************************************************************************//**
* @file sdl_timer.c
* @brief Implementation of SDL timer
* @author Jon Ayerdi
*****************************************************************************************/

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/

#include "hal/sdl_timer.h"

#include "io/memory.h"

#include "hal/sdl_global.h"

/*--------------------------------------------------------------------------------------*/
/*                            		 PRIVATE FUNCTIONS                                  */
/*--------------------------------------------------------------------------------------*/

static int _start(uint32_t freq, void(*timer_handler)(ttimer_t *timer), void *context);
static void _stop(void *context);
static void _destroy(void *context);
static int _sdl_timer_thread(void *context);

static int _start(uint32_t freq, void(*timer_handler)(ttimer_t *timer), void *context)
{
    sdl_timer_t *sdl_timer = (sdl_timer_t *)context;
    sdl_timer->stop = 0;
    sdl_timer->timer->freq = freq;
    sdl_timer->timer_handler = timer_handler;
    sdl_timer->thread = SDL_CreateThread(_sdl_timer_thread, "sdl_timer_thread", context);
    if(sdl_timer->thread == NULL)
        return (int)SDL_GetError();
	return 0;
}

static void _stop(void *context)
{
    volatile sdl_timer_t *sdl_timer = (sdl_timer_t *)context;
    sdl_timer->stop = 1;
	SDL_WaitThread(sdl_timer->thread, NULL);
}

static void _destroy(void *context)
{
    _stop(context);
    memory_free(context);
}

static int _sdl_timer_thread(void *context)
{
    volatile sdl_timer_t *sdl_timer = (sdl_timer_t *)context;
    uint32_t step = 1000/sdl_timer->timer->freq;
    while(!sdl_timer->stop)
    {
        sdl_timer->timer_handler(sdl_timer->timer);
        SDL_Delay(step);
    }
    return 0;
}

/*--------------------------------------------------------------------------------------*/
/*                             PUBLIC FUNCTION DEFINITIONS                              */
/*--------------------------------------------------------------------------------------*/

int sdl_timer_init(ttimer_t *output)
{
    //Init SDL if needed
    int status = sdl_init_if_needed();
	if(status)
        return status;
    //Allocate and init sdl_timer_t instance
    sdl_timer_t *sdl_timer = (sdl_timer_t *)memory_allocate(sizeof(sdl_timer_t));
	if(sdl_timer == NULL)
		return MEMORY_ERROR;
    sdl_timer->timer = output;
	//Implement timer interface
	output->context = (void *)sdl_timer;
	output->start = _start;
	output->stop = _stop;
	output->destroy = _destroy;
	return 0;
}

/*****************************************************************************************
*                                      sdl_timer.c
*****************************************************************************************/
