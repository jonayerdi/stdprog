/*****************************************************************************************
*                                         timer.h
******************************************************************************************
* AUTHOR: Jon Ayerdi
*
* DESCRIPTION: Interfaces for timer manipulation.
*
*****************************************************************************************/
#ifndef SRC_IO_TIMER_H_
#define SRC_IO_TIMER_H_

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/
#include <stdint.h> /* uint32_t, uint64_t */

/*--------------------------------------------------------------------------------------*/
/*                                        TYPES                                         */
/*--------------------------------------------------------------------------------------*/

typedef uint64_t timer_tick_t;

typedef struct ttimer
{
	int(*start)(uint32_t freq, void(*callback)(struct ttimer *ttimer), void *context);
	void(*stop)(void *context);
	void(*destroy)(void *context);
	void(*callback)(struct ttimer ttimer);
	timer_tick_t period;
	uint32_t freq;
	volatile timer_tick_t ticks;
	void *context;
} ttimer_t;

/*--------------------------------------------------------------------------------------*/
/*                           PUBLIC FUNCTION DECLARATIONS                               */
/*--------------------------------------------------------------------------------------*/

/** @brief starts the timer.
 *  @param timer the timer.
 *  @param freq timer frequence in HZ.
 *  @param callback callback function to call every timer interval.
 *  @return 0 (OK) or nonzero (error).
 */
int timer_start(ttimer_t *timer, uint32_t freq, void(*callback)(ttimer_t timer));
/** @brief stops the timer.
 *  @param timer the timer.
 */
void timer_stop(ttimer_t timer);

/** @brief returns the tick count of the timer.
 *  @param timer the timer.
 *  @return count of intervals passed since the timer was started.
 */
timer_tick_t timer_get_ticks(ttimer_t timer);

/** @brief destroys the timer.
 *  @param timer the timer.
 */
void timer_destroy(ttimer_t timer);

#endif /* SRC_IO_TIMER_H_ */

/*****************************************************************************************
*                                         timer.h
*****************************************************************************************/
