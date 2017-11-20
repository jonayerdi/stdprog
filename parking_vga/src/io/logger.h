/*
 * logger.h
 *
 *  Created on: 20 Nov 2017
 *      Author: Jon Ayerdi
 */

#ifndef SRC_IO_LOGGER_H_
#define SRC_IO_LOGGER_H_

#include "io/stream.h"

void logger_init(void);
output_stream_t logger_get(void);

#endif /* SRC_IO_LOGGER_H_ */
