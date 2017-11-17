/*
 * time.h
 *
 *  Created on: 18 Oct 2017
 *      Author: Jon Ayerdi
 */

#ifndef SRC_DOMAIN_TIME_H_
#define SRC_DOMAIN_TIME_H_

#include <stdint.h> /* uint32_t */
#include <stdio.h> /* sprintf */

static char _hours_24_to_12[] = {12,1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11};
static char *_am_pm[] = {"AM", "PM"};

#define TIME_MINUTE_SECONDS (60)
#define TIME_HOUR_SECONDS (60 * 60)
#define TIME_DAY_SECONDS (60 * 60 * 24)

#define TIME_SET(T,HOUR,MINUTE,SECOND) ((T) = (((HOUR) * TIME_HOUR_SECONDS) + ((MINUTE) * TIME_MINUTE_SECONDS) + (SECOND)))

#define TIME_INCREASE(T,HOURS,MINUTES,SECONDS) ((T) += (((HOURS) * TIME_HOUR_SECONDS) + ((MINUTES) * TIME_MINUTE_SECONDS) + (SECONDS)))
#define TIME_DECREASE(T,HOURS,MINUTES,SECONDS) ((T) -= (((HOURS) * TIME_HOUR_SECONDS) + ((MINUTES) * TIME_MINUTE_SECONDS) + (SECONDS)))

#define TIME_GET_SECOND(T) ((T)%(TIME_MINUTE_SECONDS))
#define TIME_GET_MINUTE(T) (((T)%(TIME_HOUR_SECONDS)) / TIME_MINUTE_SECONDS)
#define TIME_GET_HOUR_24(T) (((T)%(TIME_DAY_SECONDS)) / TIME_HOUR_SECONDS)
#define TIME_GET_HOUR_12(T) _hours_24_to_12[TIME_GET_HOUR_24(T)]
#define TIME_GET_AM_PM(T) _am_pm[(TIME_GET_HOUR_24(T) - 1) >= 12]

/**
 * char str[9];
 */
#define time_to_string_24(time,str) \
	sprintf(str, "%02d:%02d:%02d", TIME_GET_HOUR_24(time), TIME_GET_MINUTE(time), TIME_GET_SECOND(time))

/**
 * char str[12];
 */
#define time_to_string_12(time,str) \
	sprintf(str, "%02d:%02d:%02d %s", TIME_GET_HOUR_12(time), TIME_GET_MINUTE(time), TIME_GET_SECOND(time), TIME_GET_AM_PM(time))

#endif /* SRC_DOMAIN_TIME_H_ */
