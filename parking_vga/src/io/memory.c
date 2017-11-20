/*
 * memory.c
 *
 *  Created on: 20 Nov 2017
 *      Author: Jon Ayerdi
 */

#include "io/memory.h"

inline void *memory_allocate(size_t size)
{
	return malloc(size);
}

inline void memory_free(void *ptr)
{
	return free(ptr);
}
