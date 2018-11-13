/* ***************************************************************** */
/* File name:        pid.c                                           */
/* File description: Implements the PID controller                   */
/* Author name:      Rafael Tomaz Prado                              */
/* Creation date:    13nov2018                                       */
/* Revision date:    13nov2018                                       */
/* ***************************************************************** */

#include "PID/pid.h"

/* PID sampling time */
const double sampling = 0.03;

/* Variables for the position controller */
const double posK = 30.0, posTd = 0.05, posTi = 999999999999;
/* 0- current, 1- past, 2- past-1*/
static double posError[3] = {0.0, 0.0, 0.0};
/* Saves last output command */
static double posLastOutput = 0.0;

/* Variables for the speed controller */
const double spdK = 0.0, spdTd = 0.0, spdTi = 0.0;
/* 0- current, 1- past, 2- past-1*/
static double spdError[3] = {0.0, 0.0, 0.0};
/* Saves last output command */
static double spdLastOutput = 0.0;

double pid_posUpdate(double sensorReading){
  /* If the line is detected by the middle sensor */
  const double reference = 0.0;
  /* determines the current error */
  posError[0] = reference - sensorReading;
  /* Constant calculations */
  double q0 = posK * (1 + sampling/(2*posTi) + posTd/sampling);
  double q1 = -1*posK*(1 + (2*posTd)/sampling - sampling/(2*posTi));
  double q2 = posK*posTd/sampling;
  /* Calculates the actuator signal */
  double uk = posLastOutput+q0*posError[0]+q1*posError[1]+q2*posError[2];
  /* Updates the errors and the last output */
  posLastOutput = uk;
  posError[2] = posError[1];
  posError[1] = posError[0];

  return uk;
}

/* Should verify which engine is being controlled and generate an opposed signal to the other*/

double pid_spdUpdate(double sensorReading){
  /* Changes the reference for the speed */
  const double reference = 100.0;
  /* determines the current error */
  spdError[0] = sensorReading - reference;
  /* Constant calculations */
  double q0 = spdK * (1 + sampling/(2*spdTi) + spdTd/sampling);
  double q1 = -1*spdK*(1 + (2*spdTd)/sampling - sampling/(2*spdTi));
  double q2 = spdK*spdTd/sampling;
  /* Calculates the actuator signal */
  double uk = spdLastOutput+q0*spdError[0]+q1*spdError[1]+q2*spdError[2];
  /* Updates the errors and the last output */
  spdLastOutput = uk;
  spdError[2] = spdError[1];
  spdError[1] = spdError[0];

  return uk;
}
