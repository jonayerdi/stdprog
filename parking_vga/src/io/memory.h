/*************************************************************************************//**
* @file memory.h
* @brief Interfaces for memory allocation
* @author Jon Ayerdi
*****************************************************************************************/
#ifndef SRC_IO_MEMORY_H_
#define SRC_IO_MEMORY_H_

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/
#include <stddef.h> /* size_t */

/*--------------------------------------------------------------------------------------*/
/*                                        MACROS                                        */
/*--------------------------------------------------------------------------------------*/
#define MEMORY_ERROR 0xDEAD

/*--------------------------------------------------------------------------------------*/
/*                            PUBLIC FUNCTION DECLARATIONS                              */
/*--------------------------------------------------------------------------------------*/

/** @brief allocates memory on request.
 *  @param size number of bytes to allocate.
 *  @return pointer to the allocated memory or NULL if failed.
 */
void *memory_allocate(size_t size);
/** @brief frees the memory previously allocated with memory_allocate.
 *  @param ptr pointer returned by memory_allocate.
 */
void memory_free(void *ptr);

/*--------------------------------------------------------------------------------------*/
/*                             PUBLIC FUNCTION DEFINITIONS                              */
/*--------------------------------------------------------------------------------------*/

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
	free(ptr);
}

#endif /* MEMORY_NO_HEAP */

#endif /* SRC_IO_MEMORY_H_ */

/*****************************************************************************************
*                                      memory.h
*****************************************************************************************/
