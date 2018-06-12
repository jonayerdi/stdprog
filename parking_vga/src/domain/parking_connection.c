/*************************************************************************************//**
* @file parking_connection.c
* @brief Handles connection of parking application server
* @author Jon Ayerdi
*****************************************************************************************/

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/
#include "domain/parking_connection.h"
#include "domain/parking_spot_state_machine.h"

#include "config/stream_config.h"

#include <stdint.h>

/*--------------------------------------------------------------------------------------*/
/*                                        MACROS                                        */
/*--------------------------------------------------------------------------------------*/
#define MESSAGE_PARKING_ID 0x11111111
#define MESSAGE_PARKING_SPOT_UPDATE 0x12121212
#define MESSAGE_CAMERA_IMAGE_UPDATE 0x13131313

#define PARKING_SPOT_STATE_UNKNOWN 0
#define PARKING_SPOT_STATE_FREEING 1
#define PARKING_SPOT_STATE_FREE 2
#define PARKING_SPOT_STATE_TAKING 3
#define PARKING_SPOT_STATE_TAKEN 4

#define PARKING_SPOT_MODE_NORMAL 0
#define PARKING_SPOT_MODE_FORCED 1

/*--------------------------------------------------------------------------------------*/
/*                             PUBLIC FUNCTION DEFINITIONS                              */
/*--------------------------------------------------------------------------------------*/
void parking_connection_init(output_stream_t ostream, parking_t parking)
{
    stream_write32(ostream, MESSAGE_PARKING_ID);
    stream_write32(ostream, parking.id);
}

void parking_connection_spot_update(output_stream_t ostream, parking_spot_t parking_spot)
{
    stream_write32(ostream, MESSAGE_PARKING_SPOT_UPDATE);
    stream_write32(ostream, parking_spot.id);
    switch((parking_spot_state_t)parking_spot.state_machine.estado_actual)
	{
		case parking_state_free:
			stream_write32(ostream, PARKING_SPOT_STATE_FREE);
			break;
		case parking_state_freeing:
			stream_write32(ostream, PARKING_SPOT_STATE_FREEING);
			break;
		case parking_state_taken:
			stream_write32(ostream, PARKING_SPOT_STATE_TAKEN);
			break;
		case parking_state_taking:
			stream_write32(ostream, PARKING_SPOT_STATE_TAKING);
			break;
		default:
			stream_write32(ostream, PARKING_SPOT_STATE_UNKNOWN);
			break;
	}
    switch(parking_spot.mode)
    {
        case parking_spot_mode_forced:
            stream_write32(ostream, PARKING_SPOT_MODE_FORCED);
            break;
        default:
            stream_write32(ostream, PARKING_SPOT_MODE_NORMAL);
            break;
    }
}

void parking_connection_image_update(output_stream_t ostream, parking_camera_t *camera)
{
	//Read image (MAX SIZE 100 KB)
	uint8_t buffer[1024*100];
	size_t imageSize;
	input_stream_t imageStream;
	int result = stream_config_get_input(&imageStream, camera->imageFiles[camera->imageFilesIndex]);
	camera->imageFilesIndex = (camera->imageFilesIndex + 1) % camera->imageFilesCount;
	if(!result)
	{
		imageSize = stream_read(imageStream, buffer, 1024*100);
		stream_close_input(imageStream);
	}
	else imageSize = 0;
	//Send message
	stream_write32(ostream, MESSAGE_CAMERA_IMAGE_UPDATE);
	stream_write32(ostream, camera->id);
	stream_write32(ostream, imageSize);
	for(size_t i = 0 ; i < imageSize ; i++)
		stream_write(ostream, &buffer[i], sizeof(uint8_t));
}

/*****************************************************************************************
*                                        parking_connection.c
*****************************************************************************************/
