/*
 * stdio.h
 *
 *  Created on: 18 Oct 2017
 *      Author: Jon Ayerdi
 */

#ifndef SRC_HW_ABSTRACTION_STDIO_H_
#define SRC_HW_ABSTRACTION_STDIO_H_

#include <stdio.h>
#include "../io/stream.h"

size_t stdin_read(char *str, size_t size);
void stdin_discard(void);

size_t stdout_write(const char *str, size_t size);
void stdout_flush(void);

#define hw_abstraction_stdin { stdin_read, stdin_discard }
#define hw_abstraction_stdout { stdout_write, stdout_flush }

#endif /* SRC_HW_ABSTRACTION_STDIO_H_ */
