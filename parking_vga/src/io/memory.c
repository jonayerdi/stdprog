/*
 * memory.c
 *
 *  Created on: 20 Nov 2017
 *      Author: Jon Ayerdi
 */

#include "io/memory.h"

//#include <stdlib.h> /* malloc, free */

static char _memory[1280*1024*4*5];
void *current = _memory;

inline void *memory_allocate(size_t size)
{
	void *ptr = current;
	current += size;
	return ptr;
	//return malloc(size);
}

inline void memory_free(void *ptr)
{
	//return free(ptr);
}
