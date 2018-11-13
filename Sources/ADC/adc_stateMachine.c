/* ***************************************************************** */
/* File name:        adc_stateMachine.c                              */
/* File description: state machine that controls the AD conversion   */
/* Author name:      Rafael Tomaz Prado                              */
/* Creation date:    05nov2018                                       */
/* Revision date:    05nov2018                                       */
/* ***************************************************************** */

#include "ADC/adc_stateMachine.h"
#include "Infrared/infrared.h"

/* This enumeration defines all states that are covered by the state machine into a custom type. */
typedef enum
{
    START,
    RESULT
} conversion_state;

/* Defines the current state of the machine. */
static conversion_state currentState = START;
/* Defines which sensor is being used as input */
const sensor infraredArray[5] = {FAR_LEFT,LEFT,CENTER,RIGHT,FAR_RIGHT};
static sensor inputSensor = FAR_LEFT;
static unsigned int pureIndex = 1;

const int sensorWeights[5] = {-2,-1,0,1,2};
static double sensorValues[5] = {0.0, 0.0, 0.0, 0.0, 0.0};

/* *************************************************** */
/* Method name: 	   adcStateMachine_setSensor         */
/* Method description: sets the input sensor           */
/* Input params:	   n/a 			                         */
/* Output params:	   n/a 			                         */
/* *************************************************** */
void updateInputSensor(){
    inputSensor = infraredArray[pureIndex%5];
    pureIndex++;
}

/* *************************************************** */
/* Method name: 	   adcStateMachine_update            */
/* Method description:  updates the current state      */
/*                      based on the conversion status.*/
/* Input params:	   n/a 			                         */
/* Output params:	   n/a 			                         */
/* *************************************************** */
void adcStateMachine_update(void){
  double conversionResult;
  /* Verifies current state */
  switch (currentState) {
    case START:
      /* Initializes the conversion */
      adc_initConversion(inputSensor);
      /* Updates to next state */
      currentState = RESULT;
      break;
    case RESULT:
      /* Verifies if conversion is done */
      if(adc_isAdcDone()){
        conversionResult = adc_getConversionValue();

        /* TODO: Tratar resultado da conversão */
        if(conversionResult > getSensorMax()){
          conversionResult = getSensorMax();
        }
        if(conversionResult < getSensorMin()){
          conversionResult = getSensorMin();
        }

        sensorValues[pureIndex%5] = conversionResult;

        /* Updates the sensor being used as input automatically */
        updateInputSensor();
        /* Goes back to initial state to start another measurement */
        currentState = START;
      }
      break;
  }/* end switch(currentState) */
}

double getLinePosition(){
    double pos = 0.0;
    /* Calculates position using the sensorWeights */
    for(int i=0;i<5;i++){
      pos += sensorValues[i]*sensorWeights[i];
    }
    return pos;
}
