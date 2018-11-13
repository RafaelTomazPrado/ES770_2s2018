/* ***************************************************************** */
/* File name:        adc_stateMachine.c                              */
/* File description: state machine that controls the AD conversion   */
/* Author name:      Rafael Tomaz Prado                              */
/* Creation date:    05nov2018                                       */
/* Revision date:    05nov2018                                       */
/* ***************************************************************** */

#include "ADC/adc_stateMachine.h"
#include "Infrared/infrared.h"

/* Defines which sensor is being used as input */
const sensor infraredArray[5] = {FAR_LEFT,LEFT,CENTER,RIGHT,FAR_RIGHT};

const int sensorWeights[5] = {-2,-1,0,1,2};
static double sensorValues[5] = {0.0, 0.0, 0.0, 0.0, 0.0};

/* *************************************************** */
/* Method name: 	   adcStateMachine_update            */
/* Method description:  updates the current state      */
/*                      based on the conversion status.*/
/* Input params:	   n/a 			                         */
/* Output params:	   n/a 			                         */
/* *************************************************** */
void adcStateMachine_update(void){
  double conversionResult;

  for(int i=0; i<5; i++){
    adc_initConversion(infraredArray[i]);
    /* Wait until conversion is done */
    while(!adc_isAdcDone());
    conversionResult = adc_getConversionValue();

    /* TODO: Tratar resultado da conversão */
    if(conversionResult > getSensorMax()){
      conversionResult = getSensorMax();
    }
    if(conversionResult < getSensorMin()){
      conversionResult = getSensorMin();
    }
    sensorValues[i] = conversionResult;
  }
}

double getLinePosition(){
    double pos = 0.0;
    /* Calculates position using the sensorWeights */
    for(int i=0;i<5;i++){
      pos += sensorValues[i]*sensorWeights[i];
    }
    return pos;
}
