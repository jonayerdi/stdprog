/*************************************************************************************//**
* @file stream_config.h
* @brief Mapping of stream implementations to their names
* @author Jon Ayerdi
*****************************************************************************************/
#ifndef SRC_CONFIG_STREAM_CONFIG_H_
#define SRC_CONFIG_STREAM_CONFIG_H_

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/
#include "io/stream.h"

/*--------------------------------------------------------------------------------------*/
/*                            PUBLIC FUNCTION DECLARATIONS                              */
/*--------------------------------------------------------------------------------------*/

/** @brief gets an input stream by name.
 *  @param out the stream.
 *  @param filename name of the stream.
 *  @return 0 (OK) or nonzero (error).
 */
int stream_config_get_input(input_stream_t *out, const char *filename);
/** @brief gets an output stream by name.
 *  @param out the stream.
 *  @param filename name of the stream.
 *  @return 0 (OK) or nonzero (error).
 */
int stream_config_get_output(output_stream_t *out, const char *filename);

#endif /* SRC_CONFIG_STREAM_CONFIG_H_ */

/*****************************************************************************************
*                                   stream_config.h
*****************************************************************************************/
