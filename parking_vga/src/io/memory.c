/*
 * memory.c
 *
 *  Created on: 20 Nov 2017
 *      Author: Jon Ayerdi
 */

#include "io/memory.h"

#ifdef MEMORY_NO_HEAP

#define MEMORY_SIZE ((size_t)0x10000000ul)

static char _memory[MEMORY_SIZE];
static size_t _current = 0;

inline void *memory_allocate(size_t size)
{
	if(_current + size > MEMORY_SIZE)
		return NULL; /* Out of memory */
	void *ptr = &_memory[_current];
	_current += size;
	return ptr;
}

inline void memory_free(void *ptr)
{

}

#else /* MEMORY_NO_HEAP */

#include <stdlib.h> /* malloc, free */

inline void *memory_allocate(size_t size)
{
	return malloc(size);
}

inline void memory_free(void *ptr)
{
	return free(ptr);
}

#endif /* MEMORY_NO_HEAP */
