/*****************************************************************************************
*                                      scu_timer.h
******************************************************************************************
* AUTHOR: Jon Ayerdi
*
* DESCRIPTION: Implementation of SCU timer for the ZYBO 7000 board
*
*****************************************************************************************/
#ifndef SRC_HAL_SCU_TIMER_H_
#define SRC_HAL_SCU_TIMER_H_

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/

#include "io/timer.h"

#include <xscutimer.h>

/*--------------------------------------------------------------------------------------*/
/*                                        TYPES                                         */
/*--------------------------------------------------------------------------------------*/

typedef struct scu_timer
{
	XScuTimer driver;
	ttimer_t *timer;
	void (*timer_handler)(ttimer_t *timer);
} scu_timer_t;

/*--------------------------------------------------------------------------------------*/
/*                            PUBLIC FUNCTION DECLARATIONS                              */
/*--------------------------------------------------------------------------------------*/

/** @brief initializes the scu timer.
 *  @param output the timer.
 *  @return 0 (OK) or nonzero (error).
 */
int scu_timer_init(ttimer_t *output);

#endif /* SRC_HAL_SCU_TIMER_H_ */

/*****************************************************************************************
*                                      scu_timer.h
*****************************************************************************************/
