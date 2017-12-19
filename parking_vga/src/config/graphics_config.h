/*
 * graphics_config.h
 *
 *  Created on: 19 Dec 2017
 *      Author: Jon Ayerdi
 */

#ifndef SRC_CONFIG_GRAPHICS_CONFIG_H_
#define SRC_CONFIG_GRAPHICS_CONFIG_H_

#include "io/graphics.h"

#define GRAPHICS_CONFIG_DEVICE_NOT_FOUND -70
#define GRAPHICS_CONFIG_MODE_NOT_FOUND -71

int graphics_config_get(graphics_t *output, const char *device_name, const char *mode_name);

#endif /* SRC_CONFIG_GRAPHICS_CONFIG_H_ */
