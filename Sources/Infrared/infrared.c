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

    /* Sets all ports with GPIO alternative */
    PORTC_PCR1 = PORT_PCR_MUX(INFRARED_MUX_ALT);
    PORTC_PCR2 = PORT_PCR_MUX(INFRARED_MUX_ALT);
    PORTC_PCR3 = PORT_PCR_MUX(INFRARED_MUX_ALT);
    PORTC_PCR4 = PORT_PCR_MUX(INFRARED_MUX_ALT);
    PORTC_PCR5 = PORT_PCR_MUX(INFRARED_MUX_ALT);

    /* Set pins as digital inputs */
    GPIOC_PDDR |= GPIO_PDDR_PDD(INFRARED1_DIR | INFRARED2_DIR | INFRARED3_DIR | INFRARED4_DIR | INFRARED5_DIR);
}
