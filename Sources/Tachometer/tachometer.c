/* ***************************************************************** */
/* File name:        tachometer.c                                    */
/* File description: controls the tachometer speed sensor.           */
/* Author name:      Rafael Tomaz Prado                              */
/* Creation date:    15out2018                                       */
/* Revision date:    15out2018                                       */
/* ***************************************************************** */

#include "Tachometer/tachometer.h"
#include "KL25Z/board.h"

/* ************************************************ */
/* Method name:        tachometer_setup             */
/* Method description: configures the tachometer    */
/*                     counter                      */
/* Input params:       n/a                          */
/* Output params:       n/a                         */
/* ************************************************ */
void tachometer_setup(void){
    /* Un-gate tachometer port clock*/
    SIM_SCGC5 |= SIM_SCGC5_PORTE(CGC_CLOCK_ENABLED);

// Setup do TPM0 como contador - faz assim mesmo configurando os 2 e depois pergunta pro Bonna como faz a frequencia fixa
  // /* Set port as FTM_CLKIN0 */
	// PORTE_PCR29 = PORT_PCR_MUX(TACOMETER_ALT_COUNT);
	// /* Puts a zero to the SOPT4 register on the 24th bit, setting TMP0 using CLKIN0. */
	// SIM_SOPT4 &= SOPT4_TPM0_CLKIN0_SEL;
	// /* Sets the TPM source as OSCERCLK (0x02u on bits 25 and 24) */
	// SIM_SOPT2 |= SIM_SOPT2_TPMSRC(SOPT2_TPMSRC_OSCERCLK);
	// /* Un-gate TPM0 port clock */
	// SIM_SCGC6 |= SIM_SCGC6_TPM0(CGC_CLOCK_ENABLED);
	// /* Sets timer with source as External Clock*/
	// TPM0_SC |= TPM_SC_CMOD(TPM_CMOD_ALT_EXTERNAL);
	// /* Sets 1:1 prescaler */
	// TPM0_SC |= TPM_SC_PS(TPM_PS_ALT_DIV1);

}
