/* ***************************************************************** */
/* File name:        infrared.c                                      */
/* File description: controls the infrared sensor.                   */
/* Author name:      Rafael Tomaz Prado                              */
/* Creation date:    02out2018                                       */
/* Revision date:    02out2018                                       */
/* ***************************************************************** */

#include "Infrared/infrared.h"
#include "KL25Z/board.h"

/* ************************************************ */
/* Method name:        infrared_setup               */
/* Method description: setups the sensors pins      */
/* Input params:       n/a                          */
/* Output params:       n/a                         */
/* ************************************************ */
void infrared_setup(void){
    /* Un-gate port clock*/
    SIM_SCGC5 |= SIM_SCGC5_PORTC(CGC_CLOCK_ENABLED);

    /* Sets all ports with ADC alternative */
    PORTE_PCR20 = PORT_PCR_MUX(INFRARED_MUX_ALT);
    PORTE_PCR21 = PORT_PCR_MUX(INFRARED_MUX_ALT);
    PORTE_PCR22 = PORT_PCR_MUX(INFRARED_MUX_ALT);
    PORTE_PCR23 = PORT_PCR_MUX(INFRARED_MUX_ALT);
    PORTC_PCR2 = PORT_PCR_MUX(INFRARED_MUX_ALT);
}
