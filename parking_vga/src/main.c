/*************************************************************************************//**
* @file main.c
* @brief Entry point for the parking application
* @author Jon Ayerdi
*****************************************************************************************/

#include "config/logger.h"
#include "config/timer_config.h"

#include "domain/parking.h"

#define TIMER_FREQ 60

static ttimer_t timer;
static parking_t parking;

static void _timer_callback(ttimer_t _timer);

static void _timer_callback(ttimer_t _timer)
{
	parking_step(&parking, 80);
	parking_render(parking);
}

int main(void)
{
	int result;

	/* Init logger */
	logger_init();

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

	/* Init timer */
	result = timer_config_get_default(&timer);
	if(result != 0)
	{
		LOG("[error] SCU Timer init\n");
		return 0;
	}

	/* Start timer */
	result = timer_start(&timer, TIMER_FREQ, _timer_callback);
	if(result != 0)
	{
		LOG("[error] Starting timer\n");
		return 0;
	}

	/* Demo started */
	LOG("[done] Starting application\n");
	for(;;);
}
