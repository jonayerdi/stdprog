/*
 * stdio.c
 *
 *  Created on: 18 Oct 2017
 *      Author: Jon Ayerdi
 */

#include "stdio.h"

size_t stdin_read(char *str, size_t size)
{
	return fread(str, 1, size, stdout);
}

void stdin_discard(void)
{
	while(stdin->_r) getchar(); //empty stdin
	//while((getchar()) != '\n');
}

size_t stdout_write(const char *str, size_t size)
{
	return fwrite(str, 1, size, stdout);
}

void stdout_flush(void)
{
	fflush(stdout);
}
