/* ***************************************************************** */
/* File name:        tachometer.c                                    */
/* File description: controls the tachometer speed sensor.           */
/* Author name:      Rafael Tomaz Prado                              */
/* Creation date:    15out2018                                       */
/* Revision date:    16out2018                                       */
/* ***************************************************************** */

#include "Tachometer/tachometer.h"
#include "KL25Z/board.h"

// Number of steps on one full encoder disk turn
#define ENCODER_STEPS   20
// Reset counter
#define RESET_COUNTER   0

/* ************************************************ */
/* Method name:        tachometer_setup             */
/* Method description: configures the tachometer    */
/*                     counter                      */
/* Input params:       n/a                          */
/* Output params:       n/a                         */
/* ************************************************ */
void tachometer_setup(void){
    /* Un-gate TPM0 port clock */
    SIM_SCGC6 |= SIM_SCGC6_TPM0(CGC_CLOCK_ENABLED);
    /* Un-gate tachometer port clock*/
    SIM_SCGC5 |= SIM_SCGC5_PORTE(CGC_CLOCK_ENABLED);
    /* Sets the TPM source as OSCERCLK (0x02u on bits 25 and 24) */
    SIM_SOPT2 |= SIM_SOPT2_TPMSRC(SOPT2_TPMSRC_OSCERCLK);

    /* Configures both ports to work with channels 2 and 3 */
    PORTE_PCR29 = PORT_PCR_MUX(TACHOMETER_ALT_COUNT);
    PORTE_PCR30 = PORT_PCR_MUX(TACHOMETER_ALT_COUNT);

    /* Sets counter to count up */
    /* ANDs the sdk mask negated to ensure the CPWMS bit is zero */
    TPM0_SC &= ~TPM_SC_CPWMS(1);
  	/* Sets timer with source as External Clock*/
  	TPM0_SC |= TPM_SC_CMOD(TPM_CMOD_ALT_LPTMR);
  	/* Sets 1:1 prescaler */
  	TPM0_SC |= TPM_SC_PS(TPM_PS_ALT_DIV128);
    /* Resets the count */
    TPM0_CNT = RESET_COUNTER;

    /* Configures channel 2 to capture inputs on rising edges only */
    /* Also enables the interruption for channel */
    TPM0_C2SC &= ~(TPM_CnSC_MSB(1) | TPM_CnSC_ELSB(1));
  	TPM0_C2SC |= (TPM_CnSC_MSA(0) | TPM_CnSC_ELSA(1) | TPM_CnSC_CHIE(1));

    /* Configures channel 3 to capture inputs on rising edges only */
    /* Also enables the interruption for channel */
    TPM0_C3SC &= ~(TPM_CnSC_MSB(1) | TPM_CnSC_ELSB(1));
  	TPM0_C3SC |= (TPM_CnSC_MSA(0) | TPM_CnSC_ELSA(1) | TPM_CnSC_CHIE(1));
}

/* ************************************************ */
/* Method name:        tachometer_getEngineSpeed    */
/* Method description: returns the engine speed     */
/* Input params:       n/a                          */
/* Output params:      amount of turns              */
/* ************************************************ */
double tachometer_getEngineSpeed(engine e){
    // Get the number of pulses on the entrance according to the engine
    int numberOfPulses = 0;
    if(e == RIGHT){
      numberOfPulses = TPM0_CNT;
      // Resets the counter
      TPM0_CNT = RESET_COUNTER;
    }
    else{
      numberOfPulses = TPM2_CNT;
      // Resets the counter
      TPM2_CNT = RESET_COUNTER;
    }
    // Returns the number of full turns
    return numberOfPulses/ENCODER_STEPS;
}
