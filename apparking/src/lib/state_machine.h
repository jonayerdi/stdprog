 /*
                                        *******************
 ***************************************** C HEADER FILE ****************************************
 **                                     *******************                                    **
 **                                                                                            **
 ** project    : General template                                                              **
 ** filename   : TPL.H                                                                         **
 ** version    : 1                                                                             **
 ** date       : 19/11/2015                                                                    **
 **                                                                                            **
 ************************************************************************************************
 **                                                                                            **
 ** Copyright (c) 2015, Sainz Oruna, Markel                                                    **
 ** All rights reserved.                                                                       **
 **                                                                                            **
 ************************************************************************************************

 VERSION HISTORY:
 -- -- -- -- -- --

 Version     : 1
 Date        : 19/11/2015
 Revised by  : Sainz Oruna, Markel
 Description : Original version.

 */
 #ifndef STATE_MACHINE_H_
 #define STATE_MACHINE_H_

 /**********************************************************************************************/
 /**                                                                                          **/
 /**                                MODULES USED                                              **/
 /**                                                                                          **/
 /**********************************************************************************************/

#include <stddef.h> /* size_t */

 /**********************************************************************************************/
 /**                                                                                          **/
 /**                                DEFINITIONS AND MACROS                                    **/
 /**                                                                                          **/
 /**********************************************************************************************/

 /**********************************************************************************************/
 /**                                                                                          **/
 /**                                TYPEDEFS AND STRUCTURES                                   **/
 /**                                                                                          **/
 /**********************************************************************************************/

 typedef enum
 {
	 FALSE = 0,
	 TRUE = 1
 } BOOLEAN;

 typedef void            (*TPFN_ACC)(void *contexto); /* Puntero a una funci�n acci�n */
 typedef BOOLEAN         (*TPFN_EVE)(void *contexto); /* Puntero a una funci�n evento */

 typedef struct {
 	  TPFN_EVE      evento;       			/* Puntero a la funci�n evento */
 	  TPFN_ACC      accion;        		 	/* Puntero a la funci�n acci�n */
 	  size_t		estado_destino;			/* Estado de destino */
 } TS_TRANS;

 typedef struct {
 	  TPFN_ACC      controles;      		/* Funci�n de control del estado */
 	  TS_TRANS    * transiciones;   		/* Punteros las funciones del estado */
 	  size_t		transiciones_count;		/* Número de funciones */
 } TS_ESTADO;

 typedef struct {
 	  size_t		estado_actual;
 	  TPFN_EVE      StopCond;       		/* Condici�n necesaria para la ejecuci�n */
 	  TS_ESTADO   * estados;        		/* Matriz de punteros a los ESTADOS */
 	  size_t		estados_count;			/* Número de ESTADOS */
 	  void 		  * contexto;				/* Parámetro para pasar a las funciones de acción y evento */
 } TS_MACHINE;

 /**********************************************************************************************/
 /**                                                                                          **/
 /**                                EXPORTED VARIABLES                                        **/
 /**                                                                                          **/
 /**********************************************************************************************/

 /**********************************************************************************************/
 /**                                                                                          **/
 /**                                EXPORTED FUNCTIONS                                        **/
 /**                                                                                          **/
 /**********************************************************************************************/

 void STATE_MACHINE_ejecutar(TS_MACHINE *la_maquina);
 void STATE_MACHINE_ejecuta_estado(TS_ESTADO *el_estado, TS_MACHINE *la_maquina);

 #endif /* STATE_MACHINE_H_ */

 /**********************************************************************************************/
 /**                                                                                          **/
 /**                                       EOF                                                **/
 /**                                                                                          **/
 /**********************************************************************************************/
