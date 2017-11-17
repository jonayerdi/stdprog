/*
 * time.h
 *
 *  Created on: 18 Oct 2017
 *      Author: Jon Ayerdi
 */

#ifndef SRC_LIB_CLOCK_H_
#define SRC_LIB_CLOCK_H_

#include <stdint.h> /* uint32_t */
#include <stdio.h> /* sprintf */

typedef uint32_t clock_t;

static char _hours_24_to_12[] = {12,1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11};
static char *_am_pm[] = {"AM", "PM"};

#define CLOCK_MINUTE_SECONDS (60)
#define CLOCK_HOUR_SECONDS (60 * 60)
#define CLOCK_DAY_SECONDS (60 * 60 * 24)

#define CLOCK_SET(T,HOUR,MINUTE,SECOND) ((T) = (((HOUR) * CLOCK_HOUR_SECONDS) + ((MINUTE) * CLOCK_MINUTE_SECONDS) + (SECOND)))

#define CLOCK_INCREASE(T,HOURS,MINUTES,SECONDS) ((T) += (((HOURS) * CLOCK_HOUR_SECONDS) + ((MINUTES) * CLOCK_MINUTE_SECONDS) + (SECONDS)))
#define CLOCK_DECREASE(T,HOURS,MINUTES,SECONDS) ((T) -= (((HOURS) * CLOCK_HOUR_SECONDS) + ((MINUTES) * CLOCK_MINUTE_SECONDS) + (SECONDS)))

#define CLOCK_GET_SECOND(T) ((T)%(CLOCK_MINUTE_SECONDS))
#define CLOCK_GET_MINUTE(T) (((T)%(CLOCK_HOUR_SECONDS)) / CLOCK_MINUTE_SECONDS)
#define CLOCK_GET_HOUR_24(T) (((T)%(CLOCK_DAY_SECONDS)) / CLOCK_HOUR_SECONDS)
#define CLOCK_GET_HOUR_12(T) _hours_24_to_12[CLOCK_GET_HOUR_24(T)]
#define CLOCK_GET_AM_PM(T) _am_pm[(CLOCK_GET_HOUR_24(T) - 1) >= 12]

#define CLOCK_DIFF_SECONDS(T1, T2) ((T2) - (T1))

/**
 * char str[9];
 */
#define time_to_string_24(clock,str) \
	sprintf(str, "%02d:%02d:%02d", CLOCK_GET_HOUR_24(clock), CLOCK_GET_MINUTE(clock), CLOCK_GET_SECOND(clock))

/**
 * char str[12];
 */
#define time_to_string_12(clock,str) \
	sprintf(str, "%02d:%02d:%02d %s", CLOCK_GET_HOUR_12(clock), CLOCK_GET_MINUTE(clock), CLOCK_GET_SECOND(clock), CLOCK_GET_AM_PM(clock))

#endif /* SRC_LIB_CLOCK_H_ */
