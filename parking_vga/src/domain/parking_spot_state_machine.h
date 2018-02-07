/*****************************************************************************************
*                             parking_spot_state_machine.h
******************************************************************************************
* AUTHOR: Jon Ayerdi
*
* DESCRIPTION: State machine of a parking spot.
*
*****************************************************************************************/
#ifndef SRC_DOMAIN_PARKING_SPOT_STATE_MACHINE_H_
#define SRC_DOMAIN_PARKING_SPOT_STATE_MACHINE_H_

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/

#include "lib/state_machine.h"

#include "domain/parking.h"

/*--------------------------------------------------------------------------------------*/
/*                                        MACROS                                        */
/*--------------------------------------------------------------------------------------*/

#define GPIO_VALUE_FREE ((gpio_value_t)0)
#define GPIO_VALUE_TAKEN ((gpio_value_t)1)

#define TIMEOUT_TRANSITION 4

/*--------------------------------------------------------------------------------------*/
/*                                        TYPES                                         */
/*--------------------------------------------------------------------------------------*/

typedef enum parking_spot_state
{
	parking_state_unknown = 0,
	parking_state_free = 1,
	parking_state_freeing = 2,
	parking_state_taken = 3,
	parking_state_taking = 4
} parking_spot_state_t;

typedef struct parking_spot_state_machine_context
{
	parking_t *parking;
	parking_spot_t * spot;
} parking_spot_state_machine_context_t;

/*--------------------------------------------------------------------------------------*/
/*                            PUBLIC FUNCTION DECLARATIONS                              */
/*--------------------------------------------------------------------------------------*/

BOOLEAN parking_spot_state_machine_stop_condition(void *context);
void parking_spot_state_machine_transition_action(void *context);
BOOLEAN parking_spot_state_machine_is_free(void *context);
BOOLEAN parking_spot_state_machine_is_taken(void *context);
BOOLEAN parking_spot_state_machine_timeout_elapsed(void *context);

/** @brief initializes the state_machine for the given spot of the parking.
 *  @param state_machine the state machine.
 *  @param parking the parking.
 *  @param spot the parking spot.
 *  @return 0 (OK) or nonzero (error).
 */
int parking_spot_init_state_machine(TS_MACHINE *state_machine, parking_t *parking, parking_spot_t * spot);
/** @brief destroys the parking state_machine instance.
 *  @param state_machine the state_machine.
 */
void parking_spot_destroy_state_machine(TS_MACHINE state_machine);

#endif /* SRC_DOMAIN_PARKING_SPOT_STATE_MACHINE_H_ */

/*****************************************************************************************
*                             parking_spot_state_machine.h
*****************************************************************************************/
