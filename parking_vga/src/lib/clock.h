/*****************************************************************************************
*                                         clock.h
******************************************************************************************
* AUTHOR: Jon Ayerdi
*
* DESCRIPTION: Defines macros for time conversion and manipulation
*
*****************************************************************************************/
#ifndef SRC_LIB_CLOCK_H_
#define SRC_LIB_CLOCK_H_

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/
#include <stdint.h> /* uint64_t */
#include <stdio.h> /* sprintf */

/*--------------------------------------------------------------------------------------*/
/*                                        TYPES                                         */
/*--------------------------------------------------------------------------------------*/
typedef uint64_t timestamp_t;

/*--------------------------------------------------------------------------------------*/
/*                                      CONSTANTS                                       */
/*--------------------------------------------------------------------------------------*/
static char const _hours_24_to_12[] = {12,1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11};
static char const * const _am_pm[] = {"AM", "PM"};

/*--------------------------------------------------------------------------------------*/
/*                                        MACROS                                        */
/*--------------------------------------------------------------------------------------*/
#define CLOCK_SECOND_MILLIS (1000)
#define CLOCK_MINUTE_MILLIS (1000 * 60)
#define CLOCK_HOUR_MILLIS (1000 * 60 * 60)
#define CLOCK_DAY_MILLIS (1000 * 60 * 60 * 24)

#define CLOCK_SET(T,HOUR,MINUTE,SECOND,MILLIS) ((T) = (((HOUR) * CLOCK_HOUR_MILLIS) + ((MINUTE) * CLOCK_MINUTE_MILLIS) + ((SECOND) * CLOCK_SECOND_MILLIS) + (MILLIS)))

#define CLOCK_INCREASE(T,HOURS,MINUTES,SECONDS,MILLIS) ((T) += (((HOURS) * CLOCK_HOUR_MILLIS) + ((MINUTES) * CLOCK_MINUTE_MILLIS) + ((SECONDS) * CLOCK_SECOND_MILLIS) + (MILLIS)))
#define CLOCK_DECREASE(T,HOURS,MINUTES,SECONDS,MILLIS) ((T) -= (((HOURS) * CLOCK_HOUR_MILLIS) + ((MINUTES) * CLOCK_MINUTE_MILLIS) + ((SECONDS) * CLOCK_SECOND_MILLIS) + (MILLIS)))

#define CLOCK_GET_MILLIS(T) ((T)%(CLOCK_SECOND_MILLIS))
#define CLOCK_GET_SECOND(T) (((T)%(CLOCK_MINUTE_MILLIS)) / CLOCK_SECOND_MILLIS)
#define CLOCK_GET_MINUTE(T) (((T)%(CLOCK_HOUR_MILLIS)) / CLOCK_MINUTE_MILLIS)
#define CLOCK_GET_HOUR_24(T) (((T)%(CLOCK_DAY_MILLIS)) / CLOCK_HOUR_MILLIS)
#define CLOCK_GET_HOUR_12(T) _hours_24_to_12[CLOCK_GET_HOUR_24(T)]
#define CLOCK_GET_AM_PM(T) _am_pm[(CLOCK_GET_HOUR_24(T) - 1) >= 12]

#define CLOCK_ADD(T1, T2) ((T2) + (T1))
#define CLOCK_DIFF_MILLIS(T1, T2) ((T2) - (T1))
#define CLOCK_DIFF_SECONDS(T1, T2) (CLOCK_DIFF_MILLIS(T1, T2) / CLOCK_SECOND_MILLIS)

/**
 * char str[9];
 */
#define CLOCK_TO_STRING_24(clock,str) \
	sprintf(str, "%02d:%02d:%02d", CLOCK_GET_HOUR_24(clock), CLOCK_GET_MINUTE(clock), CLOCK_GET_SECOND(clock))

/**
 * char str[12];
 */
#define CLOCK_TO_STRING_12(clock,str) \
	sprintf(str, "%02d:%02d:%02d %s", CLOCK_GET_HOUR_12(clock), CLOCK_GET_MINUTE(clock), CLOCK_GET_SECOND(clock), CLOCK_GET_AM_PM(clock))

#endif /* SRC_LIB_CLOCK_H_ */
/****************************************************************************************/
/*                                       clock.h
/****************************************************************************************/
