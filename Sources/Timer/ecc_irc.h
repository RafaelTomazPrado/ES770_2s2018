/* ***************************************************************** */
/* File name:        ecc_irc.c                                        */
/* File description: Header file containing the functions/methods    */
/*                   interfaces for handling timers and counter      */
/*                   from the FRDM-KL25Z board                       */
/* Author name:      dloubach                                        */
/* Creation date:    23out2015                                       */
/* Revision date:    25fev2016                                   s    */
/* ***************************************************************** */

#ifndef ECC_IRC_H
#define ECC_IRC_H

#include "fsl_lptmr_driver.h"

/* ************************************************ */
/* Method name:        tc_installLptmr              */
/* Method description: Low power timer 0            */
/*                    initialization and start      */
/* Input params:      uiTimeInUs:                   */
/*                    time in micro seconds         */
/*                    tUserCallback                 */
/*                    function pointer to be called */
/*                    when counter achieves         */
/*                    uiTimeInUs                    */
/* Output params:     n/a                           */
/* ************************************************ */
void ecc_installISR(uint32_t uiTimeInUs, lptmr_callback_t tUserCallback);


#endif /* ECC_IRC_H */
