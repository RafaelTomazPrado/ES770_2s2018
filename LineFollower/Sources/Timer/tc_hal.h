/* ***************************************************************** */
/* File name:        tc_hal.c                                        */
/* File description: Header file containing the functions/methods    */
/*                   interfaces for handling timers and counter      */
/*                   from the FRDM-KL25Z board                       */
/* Author name:      dloubach                                        */
/* Creation date:    23out2015                                       */
/* Revision date:    25fev2016                                   s    */
/* ***************************************************************** */

#ifndef TIMER_TC_HAL_H
#define TIMER_TC_HAL_H

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
void tc_installLptmr0(uint32_t uiTimeInUs, lptmr_callback_t tUserCallback);


#endif /* TIMER_TC_HAL_H */
