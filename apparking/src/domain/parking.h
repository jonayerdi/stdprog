/*************************************************************************************//**
* @file parking.h
* @brief Parking monitoring application
* @author Jon Ayerdi
*****************************************************************************************/
#ifndef SRC_DOMAIN_PARKING_H_
#define SRC_DOMAIN_PARKING_H_

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/

#include <stddef.h> /* size_t */

#include "io/graphics.h" /* graphics_t */
#include "io/gpio.h" /* gpio_input_t */
#include "io/stream.h" /* input_stream_t, output_stream_t */

#include "lib/clock.h" /* clock_t */
#include "lib/image.h" /* image_t */
#include "lib/state_machine.h" /* TS_MACHINE */

/*--------------------------------------------------------------------------------------*/
/*                                        MACROS                                        */
/*--------------------------------------------------------------------------------------*/

#define PARKING_ERROR_CONFIG_STREAM	 	0x01
#define PARKING_ERROR_CONFIG_PARSE 		0x02
#define PARKING_ERROR_INIT_CONNECTION 	0x03
#define PARKING_ERROR_INIT_GRAPHICS 	0x04
#define PARKING_ERROR_IMAGE_STREAM 		0x05
#define PARKING_ERROR_IMAGE_PARSE 		0x06
#define PARKING_ERROR_CONFIG_SPOT		0x07

/*--------------------------------------------------------------------------------------*/
/*                                        TYPES                                         */
/*--------------------------------------------------------------------------------------*/

typedef enum parking_spot_mode
{
	parking_spot_mode_normal,
	parking_spot_mode_forced
} parking_spot_mode_t;

typedef struct parking_camera
{
	uint32_t id;
	char **imageFiles;
	size_t imageFilesCount;
	size_t imageFilesIndex;
} parking_camera_t;

typedef struct parking_spot
{
	unsigned int id;
	TS_MACHINE state_machine;
	parking_spot_mode_t mode;
	timestamp_t timestamp;
	gpio_input_t input_source;
	gpio_input_t forced_source;
	size_t x1;
	size_t x2;
	size_t y1;
	size_t y2;
} parking_spot_t;

typedef struct parking
{
	unsigned int id;
	parking_camera_t *cameras;
	size_t cameraCount;
	parking_spot_t *spots;
	size_t count;
	timestamp_t time;
	input_stream_t connection_in;
	output_stream_t connection_out;
	graphics_t graphics;
	char has_graphics;
	image_t background_image;
} parking_t;

/*--------------------------------------------------------------------------------------*/
/*                            PUBLIC FUNCTION DECLARATIONS                              */
/*--------------------------------------------------------------------------------------*/

/** @brief initializes the parking structure.
 *  @param output the parking.
 *  @param config_filename filename of the configuration file.
 *  @return 0 (OK) or nonzero (error).
 */
int parking_init(parking_t *output, const char *config_filename);
/** @brief executes a step of the parking state machines.
 *  @param input the parking.
 *  @param time_diff elapsed milliseconds since previous call to parking_step.
 *  @return 0 (OK) or nonzero (error).
 */
int parking_step(parking_t *input, timestamp_t time_diff);
/** @brief renders the parking state into the configured graphics device.
 *  @param input the parking.
 */
void parking_render(parking_t input);
/** @brief destroys the parking instance.
 *  @param input the parking.
 */
void parking_destroy(parking_t *input);

#endif /* SRC_DOMAIN_PARKING_H_ */

/*****************************************************************************************
*                                        parking.h
*****************************************************************************************/
