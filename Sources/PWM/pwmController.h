/* ***************************************************************** */
/* File name:        pwmController.c                                 */
/* File description: generates a PWM signal to control engines.      */
/* Author name:      Rafael Tomaz Prado                              */
/* Creation date:    15out2018                                       */
/* Revision date:    15out2018                                       */
/* ***************************************************************** */

#ifndef PWMCONTROLLER_H
#define PWMCONTROLLER_H

/* ************************************************ */
/* Method name:        pwm_setup        				    */
/* Method description: configures the TPM2 to work  */
/*                     as PWM with 2 channels       */
/* Input params:       n/a                          */
/* Output params:       n/a                         */
/* ************************************************ */
void pwm_setup(void);

#endif /*PWMCONTROLLER_H*/
