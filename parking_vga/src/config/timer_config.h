/*************************************************************************************//**
* @file timer_config.h
* @brief Mapping of timer implementations
* @author Jon Ayerdi
*****************************************************************************************/
#ifndef SRC_CONFIG_TIMER_CONFIG_H_
#define SRC_CONFIG_TIMER_CONFIG_H_

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/
#include "io/timer.h"

/** @brief gets the default timer.
 *  @param out the timer.
 *  @return 0 (OK) or nonzero (error).
 */
int timer_config_get_default(ttimer_t *out);

#endif /* SRC_CONFIG_TIMER_CONFIG_H_ */

/*****************************************************************************************
*                                   timer_config.h
*****************************************************************************************/
