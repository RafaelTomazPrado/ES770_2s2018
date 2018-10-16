/* ***************************************************************** */
/* File name:        pwmController.c                                 */
/* File description: generates a PWM signal to control engines.      */
/* Author name:      Rafael Tomaz Prado                              */
/* Creation date:    15out2018                                       */
/* Revision date:    15out2018                                       */
/* ***************************************************************** */

#include "PWM/pwmController.h"
#include "KL25Z/board.h"

/* Parameters */
#define TPM_SRC_FREQ		8000000
#define PWM_FREQ				400
#define TPM_PRESCALE		1
#define TPM_MOD_VAL 		(TPM_SRC_FREQ/(PWM_FREQ*TPM_PRESCALE))

/* ************************************************ */
/* Method name:        pwm_setup        				    */
/* Method description: configures the TPM1 to work  */
/*                     as PWM with 2 channels       */
/* Input params:       n/a                          */
/* Output params:       n/a                         */
/* ************************************************ */
void pwm_setup(void){
  /* un-gate port clock*/
	SIM_SCGC6 |= SIM_SCGC6_TPM1(CGC_CLOCK_ENABLED); //Enable clock for TPM1
	/* un-gate portA clock*/
	 SIM_SCGC5 |= SIM_SCGC5_PORTA(CGC_CLOCK_ENABLED);

	/* Configures both ports as PWM*/
  PORTA_PCR12 |= PORT_PCR_MUX(TPM_PWM_MUX_ALT);
	PORTA_PCR13 |= PORT_PCR_MUX(TPM_PWM_MUX_ALT);

	/* Configures the TPM1 */
	TPM1_SC &= ~TPM_SC_CPWMS(1);
	TPM1_SC |= TPM_SC_CMOD(TPM_CMOD_ALT_LPTMR);   //LPTPM Counter increments on every LPTPM counter clock
	TPM1_SC |= TPM_SC_PS(TPM_PS_ALT_DIV1);   //Prescale 1:1

	/* This line configures the Channel 0*/
	TPM1_C0SC &= ~(TPM_CnSC_MSA(0b0) | TPM_CnSC_ELSA(0b0));
	TPM1_C0SC |= (TPM_CnSC_MSB(0b1) | TPM_CnSC_ELSB(0b1));
	/* This line configures the Channel 1*/
	TPM1_C1SC &= ~(TPM_CnSC_MSA(0b0) | TPM_CnSC_ELSA(0b0));
	TPM1_C1SC |= (TPM_CnSC_MSB(0b1) | TPM_CnSC_ELSB(0b1));

	/* Sets the Timer MOD */
	TPM1_MOD = TPM_MOD_VAL;
	/* Resets the counter*/
	TPM1_CNT = 0x00u;
	/* Sets the initial Duty Cycle as 0% */
	TPM1_C0V = 0x00;
	TPM1_C1V = 0x00;
}

/* ************************************************ */
/* Method name:        pwm_setDutyCycle  				    */
/* Method description: sets the DC for engine       */
/* Input params:       e - desired engine           */
/*                     percentage - DC %            */
/* Output params:       n/a                         */
/* ************************************************ */
void pwm_setDutyCycle(engine e, unsigned int percentage){
		// Calculates the proper value based on the MOD value
		unsigned int dutyCycle = (percentage * TPM_MOD_VAL)/100;
		// Sets the DC value to the designated engine
		if(e == RIGHT)	TPM1_C0V = TPM_CnV_VAL(dutyCycle);
		else TPM1_C1V = TPM_CnV_VAL(dutyCycle);
}
