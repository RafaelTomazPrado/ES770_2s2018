/* ***************************************************************** */
/* File name:        pwmController.c                                 */
/* File description: generates a PWM signal to control engines.      */
/* Author name:      Rafael Tomaz Prado                              */
/* Creation date:    15out2018                                       */
/* Revision date:    15out2018                                       */
/* ***************************************************************** */

#include "PWM/pwmController.h"
#include "KL25Z/boarh.h"

/* Parameters */
#define TPM_SRC_FREQ		4000000
#define PWM_FREQ				400
#define TPM_PRESCALE		1
#define TPM_MOD_VAL 		(TPM_SRC_FREQ/(PWM_FREQ*TPM_PRESCALE))

/* ************************************************ */
/* Method name:        pwm_setup        				    */
/* Method description: configures the TPM2 to work  */
/*                     as PWM with 2 channels       */
/* Input params:       n/a                          */
/* Output params:       n/a                         */
/* ************************************************ */
void pwm_setup(void){
  /* un-gate port clock*/
	SIM_SCGC6 |= SIM_SCGC6_TPM2(CGC_CLOCK_ENABLED); //Enable clock for TPM2

	TPM2_SC |= TPM_SC_CPWMS(TPM_CPWMS_UP);   //up counting mode
	TPM2_SC |= TPM_SC_CMOD(TPM_CMOD_ALT_LPTMR);   //LPTPM Counter increments on every LPTPM counter clock
	TPM2_SC |= TPM_SC_PS(TPM_PS_ALT_DIV1);   //Prescale 1:1

	/* This portion of code configures the Channel 0*/
	TPM2_C0SC |= (TPM_CnSC_MSB(0b1) | TPM_CnSC_MSA(0b0) | TPM_CnSC_ELSB(0b1) | TPM_CnSC_ELSA(0b0));
	/* This portion of code configures the Channel 0*/
	TPM2_C1SC |= (TPM_CnSC_MSB(0b1) | TPM_CnSC_MSA(0b0) | TPM_CnSC_ELSB(0b1) | TPM_CnSC_ELSA(0b0));

	/* Sets the Timer MOD */
	TPM2_MOD = TPM_MOD_VAL;
	/* Resets the counter*/
	TPM2_CNT = 0x00u;
	/* Sets the initial Duty Cycle as 0% */
	TPM2_C0V = 0x00;
	TPM2_C1V = 0x00;
}
