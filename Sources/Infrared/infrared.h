/* ***************************************************************** */
/* File name:        infrared.h                                      */
/* File description: controls the infrared sensor.                   */
/* Author name:      Rafael Tomaz Prado                              */
/* Creation date:    02out2018                                       */
/* Revision date:    02out2018                                       */
/* ***************************************************************** */

#ifndef INFRARED_H
#define INFRARED_H

/* ************************************************ */
/* Method name:        infrared_setup               */
/* Method description: setups the sensors pins      */
/* Input params:       n/a                          */
/* Output params:       n/a                         */
/* ************************************************ */
void infrared_setup(void);

/* ************************************************ */
/* Method name:        infrared_updatePosition      */
/* Method description: reads sensors and calculates */
/*                     line position                */
/* Input params:       n/a                          */
/* Output params:  line position relative to center */
/* ************************************************ */
double infrared_updatePosition(void);

/* ************************************************ */
/* Method name:        useSingleCalibration         */
/* Method description: decides if will use multi    */
/*                     sensor calibration           */
/* Input params:       decision: (yes/no) - (>1/0)  */
/* Output params:      n/a                          */
/* ************************************************ */
void infrared_useSingleCalibration(int decision);

#endif /* INFRARED_H */
