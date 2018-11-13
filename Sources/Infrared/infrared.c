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

static double sensorMaxValue = 0;
static double sensorMinValue = 999999999;

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

void infrared_callibrate(void){
  double conversionResult;
  int currentState = 0;
  /* Defines which sensor is being used as input */
  sensor array[5] = {FAR_LEFT,LEFT,CENTER,RIGHT,FAR_RIGHT};

  for(int i=0;i<5;i++){
      int j = 300;
      while(j--){
        /* Verifies current state */
        switch (currentState) {
          case 0:
            /* Initializes the conversion */
            adc_initConversion(array[i]);
            /* Updates to next state */
            currentState = 1;
            break;
          case 1:
            /* Verifies if conversion is done */
            if(adc_isAdcDone()){
              conversionResult = adc_getConversionValue();

              if(conversionResult > sensorMaxValue){
                sensorMaxValue = conversionResult;
              }
              if (conversionResult < sensorMinValue){
                sensorMinValue = conversionResult;
              }
              /* Goes back to initial state to start another measurement */
              currentState = 0;
            }
            break;
        }/* end switch(currentState) */
      }

    }
}


double getSensorMax(){
  return sensorMaxValue;
}

double getSensorMin(){
  return sensorMinValue;
}
