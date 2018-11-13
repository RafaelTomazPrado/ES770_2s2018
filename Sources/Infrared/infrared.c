/* ***************************************************************** */
/* File name:        infrared.c                                      */
/* File description: controls the infrared sensor.                   */
/* Author name:      Rafael Tomaz Prado                              */
/* Creation date:    02out2018                                       */
/* Revision date:    02out2018                                       */
/* ***************************************************************** */

#include "Infrared/infrared.h"
#include "KL25Z/board.h"
#include "ADC/adc.h"

/* Holds the minimum and maximum value after the calibration */
static double sensorMaxValue[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
static double sensorMinValue[5] = {999999999,999999999, 999999999, 999999999, 999999999};

/* Defines which sensor is being used as input */
const sensor infraredArray[5] = {FAR_LEFT,LEFT,CENTER,RIGHT,FAR_RIGHT};
/* Define the weight each sensor has on the position calculation */
const int sensorWeights[5] = {-2,-1,0,1,2};
/* Holds the latest reading for each sensor */
static double sensorValues[5] = {0.0, 0.0, 0.0, 0.0, 0.0};

/* Callibration method signature */
void infrared_callibrate(void);

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

    /* After each pin has been setup, calibrates the sensors */
    infrared_callibrate();
}

void infrared_callibrate(void){
  double conversionResult;
  int currentState = 0;

  for(int i=0;i<5;i++){
      int j = 300;
      while(j--){
        /* Verifies current state */
        switch (currentState) {
          case 0:
            /* Initializes the conversion */
            adc_initConversion(infraredArray[i]);
            /* Updates to next state */
            currentState = 1;
            break;
          case 1:
            /* Verifies if conversion is done */
            if(adc_isAdcDone()){
              conversionResult = adc_getConversionValue();

              if(conversionResult > sensorMaxValue[i]){
                sensorMaxValue[i] = conversionResult;
              }
              if (conversionResult < sensorMinValue[i]){
                sensorMinValue[i] = conversionResult;
              }
              /* Goes back to initial state to start another measurement */
              currentState = 0;
            }
            break;
        }/* end switch(currentState) */
      }

    }
}

double infrared_updatePosition(void){
  double conversionResult;

  double pos = 0.0;
  double sum = 0.0;

  for(int i=0; i<5; i++){
    adc_initConversion(infraredArray[i]);
    /* Wait until conversion is done */
    while(!adc_isAdcDone());
    conversionResult = adc_getConversionValue();

    /* TODO: Tratar resultado da conversão */
    if(conversionResult > sensorMaxValue[i]){
      conversionResult = sensorMaxValue[i];
    }
    if(conversionResult < sensorMinValue[i]){
      conversionResult = sensorMinValue[i];
    }
    sensorValues[i] = conversionResult;

    pos += sensorValues[i]*sensorWeights[i];
    sum += sensorValues[i];
  }

  return pos/sum;
}
