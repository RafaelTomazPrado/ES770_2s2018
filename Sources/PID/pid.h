/* ***************************************************************** */
/* File name:        pid.h                                           */
/* File description: headers for the PID controller                  */
/* Author name:      Rafael Tomaz Prado                              */
/* Creation date:    13nov2018                                       */
/* Revision date:    13nov2018                                       */
/* ***************************************************************** */

#ifndef PID_H
#define PID_H

double pid_posUpdate(double sensorReading);
double pid_spdUpdate(double sensorReading);

#endif /* PID_H */
