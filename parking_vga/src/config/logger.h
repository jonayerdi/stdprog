/*
 * logger.h
 *
 *  Created on: 20 Nov 2017
 *      Author: Jon Ayerdi
 */

#ifndef SRC_CONFIG_LOGGER_H_
#define SRC_CONFIG_LOGGER_H_

#include "io/stream.h"

#define LOG(STR) stream_write_string(logger_get(), STR)

void logger_init(void);
output_stream_t logger_get(void);

#endif /* SRC_CONFIG_LOGGER_H_ */
