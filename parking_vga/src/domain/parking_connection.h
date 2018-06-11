/*************************************************************************************//**
* @file parking_connection.h
* @brief Handles connection of parking application server
* @author Jon Ayerdi
*****************************************************************************************/

#ifndef SRC_DOMAIN_PARKING_CONNECTION_H_
#define SRC_DOMAIN_PARKING_CONNECTION_H_

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/

#include "domain/parking.h"

/*--------------------------------------------------------------------------------------*/
/*                            PUBLIC FUNCTION DECLARATIONS                              */
/*--------------------------------------------------------------------------------------*/

void parking_connection_init(output_stream_t ostream, parking_t parking);
void parking_connection_spot_update(output_stream_t ostream, parking_spot_t parking_spot);
void parking_connection_image_update(output_stream_t ostream, parking_camera_t *camera);

#endif /* SRC_DOMAIN_PARKING_CONNECTION_H_ */

/*****************************************************************************************
*                                        parking_connection.h
*****************************************************************************************/
