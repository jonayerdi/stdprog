/*
 * main.c
 *
 *  Created on: 18 Oct 2017
 *      Author: Jon Ayerdi
 */

#include "platform.h"

#include "domain/time.h"
#include "io/stream.h"
#include "hw_abstraction/stdio.h"
#include "hw_abstraction/gpio.h"
#include "hw_abstraction/buttons.h"
#include "hw_abstraction/leds.h"
#include "hw_abstraction/timer.h"
#include "hw_abstraction/vga_textmode.h"

input_stream in = hw_abstraction_stdin;
output_stream out = hw_abstraction_vga_textmode; //hw_abstraction_stdout;
unsigned int time;
void (*gpio_callbacks[1])(void);
void (*timer_callbacks[2])(void);
int status;
char time_str[12];
volatile int mode;

void gpio_change()
{
	//Change between 12h and 24h modes with buttons
	static char buttonState = 0;
	if(buttons_get(hw_abstraction_button_1) != buttonState)
	{
		if(buttonState)
			mode = !mode;
		buttonState = !buttonState;
	}
}

void timer_tick(void);

void timer_tick(void)
{
	TIME_INCREASE(time,0,0,1);
	if(mode%2)
		time_to_string_12(time,time_str);
	else
		time_to_string_24(time,time_str);
	stream_write_str(&out, time_str);
	stream_write_str(&out, "\n");
	out.flush();
}

void timer_tick2(void);

void timer_tick2(void)
{
	static int a = 0;
	if(a)
	{
		a = 0;
		leds_set(hw_abstraction_led_4, 0);
	}
	else
	{
		a = 1;
		leds_set(hw_abstraction_led_4, 1);
	}
}

int main(void)
{
	//Setup initial time
	TIME_SET(time,0,0,0);

	//Mode 0 = 24h clock, else 12h clock
	mode = 0;

	//Setup buttons
	buttons_init();
	//gpio_callbacks[0] = gpio_change;
	//gpio_init_interrupts(gpio_callbacks, 1);
	//Setup LEDs
	leds_init();
	//Setup timer
	timer_callbacks[0] = timer_tick;
	timer_callbacks[1] = timer_tick2;
	timer_init(100, timer_callbacks, 2);
	//Setup VGA
	vga_textmode_init();
	vga_textmode_clear();

	//Endless loop
	for(;;)
		gpio_change();

    return 0;
}
