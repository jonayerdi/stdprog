/*************************************************************************************//**
* @file main.c
* @brief Entry point for the parking application
* @author Jon Ayerdi
*****************************************************************************************/

#include "config/logger.h"
#include "config/timer_config.h"
#include "config/idle_loop.h"

#include "domain/parking.h"

#define TIMER_FREQ 60

ttimer_t timer;
parking_t parking;

static void _timer_callback(ttimer_t _timer);

static void _timer_callback(ttimer_t _timer)
{
	parking_step(&parking, 125);
	parking_render(parking);
}

int main(void)
{
	int result;

	/* Init logger */
	logger_init();

	/* Init timer */
	result = timer_config_get_default(&timer);
	if(result != 0)
	{
		LOG("[error] SCU Timer init\n");
		return 0;
	}

	/* Start timer */
	result = timer_start(&timer, TIMER_FREQ);
	if(result != 0)
	{
		LOG("[error] Starting timer\n");
		return 0;
	}

	/* Start the demo */
	LOG("[start] Starting application\n");

	/* Init parking */
	result = parking_init(&parking, "parking.txt");
	if(result != 0)
	{
		LOG("[error] Parking init: ");
		switch(result)
		{
			case PARKING_ERROR_CONFIG_STREAM:
				LOG("Error opening parking.txt\n");
				break;
			case PARKING_ERROR_CONFIG_PARSE:
				LOG("Error parsing parking.txt\n");
				break;
			case PARKING_ERROR_INIT_CONNECTION:
				LOG("Error initializing connection\n");
				break;
			case PARKING_ERROR_INIT_GRAPHICS:
				LOG("Error initializing graphics\n");
				break;
			case PARKING_ERROR_IMAGE_STREAM:
				LOG("Error opening background image file\n");
				break;
			case PARKING_ERROR_IMAGE_PARSE:
				LOG("Error parsing background image file\n");
				break;
			case PARKING_ERROR_CONFIG_SPOT:
				LOG("Error initializing one or more parking spots\n");
				break;
			default:
				LOG("Unknown error\n");
				break;
		}
		return 0;
	}

	/* Set timer callback */
	timer_set_callback(&timer, _timer_callback);

	/* Demo started */
	LOG("[done] Starting application\n");
	idle_loop();
}
