/*
 * timer_config.c
 *
 *  Created on: 19 Dec 2017
 *      Author: Jon Ayerdi
 */

#include "config/timer_config.h"

#include "hal/scu_timer.h"

inline int timer_config_get_default(ttimer_t *out)
{
	return scu_timer_init(out);
}
