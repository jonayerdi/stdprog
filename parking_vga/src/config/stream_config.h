/*
 * stream_config.h
 *
 *  Created on: 19 Dec 2017
 *      Author: Jon Ayerdi
 */

#ifndef SRC_CONFIG_STREAM_CONFIG_H_
#define SRC_CONFIG_STREAM_CONFIG_H_

#include "io/stream.h"

int stream_config_get_input(input_stream_t *out, const char *filename);
int stream_config_get_output(output_stream_t *out, const char *filename);

#endif /* SRC_CONFIG_STREAM_CONFIG_H_ */
