/* ***************************************************************** */
/* File name:        adc_stateMachine.h                              */
/* File description: state machine that controls the AD conversion   */
/* Author name:      Rafael Tomaz Prado                              */
/* Creation date:    05nov2018                                       */
/* Revision date:    05nov2018                                       */
/* ***************************************************************** */

#idndef ADC_STATEMACHINE_H
#define ADC_STATEMACHINE_H

/* *************************************************** */
/* Method name: 	   adcStateMachine_update            */
/* Method description:  updates the current state      */
/*                      based on the conversion status.*/
/* Input params:	   n/a 			                         */
/* Output params:	   n/a 			                         */
/* *************************************************** */
void adcStateMachine_update(void);

/* *************************************************** */
/* Method name: 	   adcStateMachine_setSensor         */
/* Method description: sets the input sensor           */
/* Input params:	   n/a 			                         */
/* Output params:	   n/a 			                         */
/* *************************************************** */
void adc_setInputSensor(sensor s);

#endif /* ADC_STATEMACHINE_H */
