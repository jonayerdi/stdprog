/*****************************************************************************************
*                             parking_spot_state_machine.c
******************************************************************************************
* AUTHOR: Jon Ayerdi
*
* DESCRIPTION: State machine of a parking spot.
*
*****************************************************************************************/

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/

#include "domain/parking_spot_state_machine.h"

#include <string.h> /* memcpy */

#include "io/memory.h"
#include "io/gpio.h"

#include "lib/clock.h"

/*--------------------------------------------------------------------------------------*/
/*                                      CONSTANTS                                       */
/*--------------------------------------------------------------------------------------*/

static TS_TRANS _unknown_state_transitions[] =
{
	{
		.evento = parking_spot_state_machine_is_free,
		.accion = parking_spot_state_machine_transition_action,
		.estado_destino = parking_state_free
	},
	{
		.evento = parking_spot_state_machine_is_taken,
		.accion = parking_spot_state_machine_transition_action,
		.estado_destino = parking_state_taken
	}
};
static TS_TRANS _free_state_transitions[] =
{
	{
		.evento = parking_spot_state_machine_is_taken,
		.accion = parking_spot_state_machine_transition_action,
		.estado_destino = parking_state_taking
	}
};
static TS_TRANS _freeing_state_transitions[] =
{
	{
		.evento = parking_spot_state_machine_is_taken,
		.accion = parking_spot_state_machine_transition_action,
		.estado_destino = parking_state_taken
	},
	{
		.evento = parking_spot_state_machine_timeout_elapsed,
		.accion = parking_spot_state_machine_transition_action,
		.estado_destino = parking_state_free
	}
};
static TS_TRANS _taken_state_transitions[] =
{
	{
		.evento = parking_spot_state_machine_is_free,
		.accion = parking_spot_state_machine_transition_action,
		.estado_destino = parking_state_freeing
	}
};
static TS_TRANS _taking_state_transitions[] =
{
	{
		.evento = parking_spot_state_machine_is_free,
		.accion = parking_spot_state_machine_transition_action,
		.estado_destino = parking_state_free
	},
	{
		.evento = parking_spot_state_machine_timeout_elapsed,
		.accion = parking_spot_state_machine_transition_action,
		.estado_destino = parking_state_taken
	}
};

static TS_ESTADO _estados[] =
{
	{
		.controles = NULL,
		.transiciones = _unknown_state_transitions,
		.transiciones_count = 2
	},
	{
		.controles = NULL,
		.transiciones = _free_state_transitions,
		.transiciones_count = 1
	},
	{
		.controles = NULL,
		.transiciones = _freeing_state_transitions,
		.transiciones_count = 2
	},
	{
		.controles = NULL,
		.transiciones = _taken_state_transitions,
		.transiciones_count = 1
	},
	{
		.controles = NULL,
		.transiciones = _taking_state_transitions,
		.transiciones_count = 2
	}
};

/*--------------------------------------------------------------------------------------*/
/*                             PUBLIC FUNCTION DEFINITIONS                              */
/*--------------------------------------------------------------------------------------*/

BOOLEAN parking_spot_state_machine_stop_condition(void *context)
{
	parking_spot_state_machine_context_t *parking_context = (parking_spot_state_machine_context_t *)context;
	return parking_context->spot->mode == parking_spot_mode_forced ? TRUE : FALSE;
}
void parking_spot_state_machine_transition_action(void *context)
{
	parking_spot_state_machine_context_t *parking_context = (parking_spot_state_machine_context_t *)context;
	parking_context->spot->timestamp = parking_context->parking->time;
}
BOOLEAN parking_spot_state_machine_is_free(void *context)
{
	parking_spot_state_machine_context_t *parking_context = (parking_spot_state_machine_context_t *)context;
	return (gpio_get(parking_context->spot->input_source) == GPIO_VALUE_FREE) ? TRUE : FALSE;
}
BOOLEAN parking_spot_state_machine_is_taken(void *context)
{
	parking_spot_state_machine_context_t *parking_context = (parking_spot_state_machine_context_t *)context;
	return (gpio_get(parking_context->spot->input_source) == GPIO_VALUE_TAKEN) ? TRUE : FALSE;
}
BOOLEAN parking_spot_state_machine_timeout_elapsed(void *context)
{
	parking_spot_state_machine_context_t *parking_context = (parking_spot_state_machine_context_t *)context;
	return (CLOCK_DIFF_SECONDS(parking_context->spot->timestamp, parking_context->parking->time) > TIMEOUT_TRANSITION) ? TRUE : FALSE;
}

int parking_spot_init_state_machine(TS_MACHINE *state_machine, parking_t *parking, parking_spot_t * spot)
{
	//Allocate state machine
	parking_spot_state_machine_context_t *parking_context = (parking_spot_state_machine_context_t *)memory_allocate(sizeof(parking_spot_state_machine_context_t));
	if(parking_context == NULL)
		return MEMORY_ERROR;
	//Define state machine
	parking_context->parking = parking;
	parking_context->spot = spot;
	state_machine->StopCond = parking_spot_state_machine_stop_condition;
	state_machine->contexto = parking_context;
	state_machine->estado_actual = parking_state_unknown;
	state_machine->estados = _estados;
	state_machine->estados_count = 5;
	return 0;
}

void parking_spot_destroy_state_machine(TS_MACHINE state_machine)
{
	memory_free(state_machine.contexto);
}

/*****************************************************************************************
*                             parking_spot_state_machine.c
*****************************************************************************************/
