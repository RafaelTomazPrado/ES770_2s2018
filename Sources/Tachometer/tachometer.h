/* ***************************************************************** */
/* File name:        tachometer.h                                    */
/* File description: headers for the tachometer speed sensor.        */
/* Author name:      Rafael Tomaz Prado                              */
/* Creation date:    15out2018                                       */
/* Revision date:    15out2018                                       */
/* ***************************************************************** */

#ifndef TACHOMETER_H
#define TACHOMETER_H

#include "KL25Z/board.h"

/* ************************************************ */
/* Method name:        tachometer_setup             */
/* Method description: configures the tachometer    */
/*                     counter                      */
/* Input params:       n/a                          */
/* Output params:       n/a                         */
/* ************************************************ */
void tachometer_setup(void);

/* ************************************************ */
/* Method name:        tachometer_getEngineSpeed    */
/* Method description: returns the engine speed     */
/* Input params:       engine                       */
/* Output params:      amount of turns              */
/* ************************************************ */
double tachometer_getEngineSpeed(engine e);

#endif /* TACHOMETER_H */
