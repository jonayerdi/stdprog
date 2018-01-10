/*****************************************************************************************
*                                         timer.c
******************************************************************************************
* AUTHOR: Jon Ayerdi
*
* DESCRIPTION: Interfaces for timer manipulation.
*
*****************************************************************************************/

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/
#include "io/timer.h"

/*--------------------------------------------------------------------------------------*/
/*                            		 PRIVATE FUNCTIONS                                  */
/*--------------------------------------------------------------------------------------*/

static void _timer_handler(ttimer_t *timer);

static void _timer_handler(ttimer_t *timer)
{
	timer->ticks++;
	if(timer->callback)
		timer->callback(*timer);
}

/*--------------------------------------------------------------------------------------*/
/*                             PUBLIC FUNCTION DEFINITIONS                              */
/*--------------------------------------------------------------------------------------*/

inline int timer_start(ttimer_t *timer, uint32_t freq, void(*callback)(ttimer_t timer))
{
	timer->callback = callback;
	timer->freq = freq;
	timer->period = (1000 / freq) + 1;
	timer->ticks = 0;
	return timer->start(freq, _timer_handler, timer->context);
}

inline void timer_stop(ttimer_t timer)
{
	timer.stop(timer.context);
}

inline timer_tick_t timer_get_ticks(ttimer_t timer)
{
	return timer.ticks;
}

inline void timer_destroy(ttimer_t timer)
{
	timer.destroy(timer.context);
}

/*****************************************************************************************
*                                         timer.c
*****************************************************************************************/
