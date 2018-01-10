/*
 * parking_spot_state_machine.h
 *
 *  Created on: 9 Jan 2018
 *      Author: Jon Ayerdi
 */

#ifndef SRC_DOMAIN_PARKING_SPOT_STATE_MACHINE_H_
#define SRC_DOMAIN_PARKING_SPOT_STATE_MACHINE_H_

#include "lib/state_machine.h"

#include "domain/parking.h"

#define GPIO_VALUE_FREE ((gpio_value_t)0)
#define GPIO_VALUE_TAKEN ((gpio_value_t)1)

#define TIMEOUT_TRANSITION 4

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

BOOLEAN parking_spot_state_machine_stop_condition(void *context);
void parking_spot_state_machine_transition_action(void *context);
BOOLEAN parking_spot_state_machine_is_free(void *context);
BOOLEAN parking_spot_state_machine_is_taken(void *context);
BOOLEAN parking_spot_state_machine_timeout_elapsed(void *context);

int parking_spot_init_state_machine(TS_MACHINE *state_machine, parking_t *parking, parking_spot_t * spot);
void parking_spot_destroy_state_machine(TS_MACHINE state_machine);

#endif /* SRC_DOMAIN_PARKING_SPOT_STATE_MACHINE_H_ */
