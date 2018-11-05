/* ***************************************************************** */
/* File name:        adc_stateMachine.c                              */
/* File description: state machine that controls the AD conversion   */
/* Author name:      Rafael Tomaz Prado                              */
/* Creation date:    05nov2018                                       */
/* Revision date:    05nov2018                                       */
/* ***************************************************************** */

#include "ADC/adc_stateMachine.h"

/* This enumeration defines all states that are covered by the state machine into a custom type. */
typedef enum
{
    START,
    CHECK,
    RESULT
} conversion_state;

/* Defines the current state of the machine. */
static conversion_state currentState = START;
/* Defines which sensor is being used as input */
static sensor inputSensor = CENTER;

/* *************************************************** */
/* Method name: 	   adcStateMachine_update            */
/* Method description:  updates the current state      */
/*                      based on the conversion status.*/
/* Input params:	   n/a 			                         */
/* Output params:	   n/a 			                         */
/* *************************************************** */
void adcStateMachine_update(void){
  int iConversionResult;
  /* Verifies current state */
  switch (currentState) {
    case START:
      /* Initializes the conversion */
      adc_initConversion(inputSensor);
      /* Updates to next state */
      currentState = CHECK;
      break;
    case CHECK:
      /* Verifies if conversion is done */
      if(adc_isAdcDone()){
        /* Updates to next state */
        currentState = RESULT;
      }
      /* Stays on this state until conversion is finished. */
      break;
    case RESULT:
      iConversionResult = adc_getConversionValue();
      iConversionResult &= 0xFF;
      /* Goes back to initial state to start another measurement */
      currentState = START;
      break;
  }/* end switch(currentState) */
}

/* *************************************************** */
/* Method name: 	   adcStateMachine_setSensor         */
/* Method description: sets the input sensor           */
/* Input params:	   n/a 			                         */
/* Output params:	   n/a 			                         */
/* *************************************************** */
void adc_setInputSensor(sensor s){
  inputSensor = s;
}
