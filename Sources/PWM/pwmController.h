/* ***************************************************************** */
/* File name:        pwmController.c                                 */
/* File description: generates a PWM signal to control engines.      */
/* Author name:      Rafael Tomaz Prado                              */
/* Creation date:    15out2018                                       */
/* Revision date:    15out2018                                       */
/* ***************************************************************** */

#ifndef PWMCONTROLLER_H
#define PWMCONTROLLER_H

#include "KL25Z/board.h"

/* ************************************************ */
/* Method name:        pwm_setup        				    */
/* Method description: configures the TPM2 to work  */
/*                     as PWM with 2 channels       */
/* Input params:       n/a                          */
/* Output params:       n/a                         */
/* ************************************************ */
void pwm_setup(void);

/* ************************************************ */
/* Method name:        pwm_setDutyCycle  				    */
/* Method description: sets the DC for engine       */
/* Input params:       e - desired engine           */
/*                     percentage - DC %            */
/* Output params:       n/a                         */
/* ************************************************ */
void pwm_setDutyCycle(engine e, unsigned int percentage);

#endif /*PWMCONTROLLER_H*/
