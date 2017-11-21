/*
 * memory.h
 *
 *  Created on: 20 Nov 2017
 *      Author: Jon Ayerdi
 */

#ifndef SRC_IO_MEMORY_H_
#define SRC_IO_MEMORY_H_

#include <stddef.h> /* size_t */

#define MEMORY_ERROR 0xDEAD

void *memory_allocate(size_t size);
void memory_free(void *ptr);

#endif /* SRC_IO_MEMORY_H_ */
