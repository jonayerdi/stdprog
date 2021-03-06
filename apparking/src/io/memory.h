#pragma once
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

#endif /* SRC_IO_MEMORY_H_ */

/*****************************************************************************************
*                                      memory.h
*****************************************************************************************/
