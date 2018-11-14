/* ***************************************************************** */
/* File name:        infrared.c                                      */
/* File description: controls the infrared sensor.                   */
/* Author name:      Rafael Tomaz Prado                              */
/* Creation date:    02out2018                                       */
/* Revision date:    02out2018                                       */
/* ***************************************************************** */

#include "KL25Z/board.h"
#include "KL25Z/delay.h"
#include "KL25Z/rgbLED.h"
#include "Infrared/infrared.h"
#include "ADC/adc.h"

/* Holds the minimum and maximum value after the calibration */
static double sensorMaxValue[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
static double sensorMinValue[5] = {999999999.0,999999999.0, 999999999.0, 999999999.0, 999999999.0};

/* Used in single calibration method */
static int isUsingSingleCalibration = 0;
static double overallMax = 0.0;
static double overallMin = 999999999.0;

/* Defines which sensor is being used as input */
const sensor infraredArray[5] = {FAR_LEFT,LEFT,CENTER,RIGHT,FAR_RIGHT};
/* Define the weight each sensor has on the position calculation */
const int sensorWeights[5] = {-2,-1,0,1,2};
/* Holds the latest reading for each sensor */
static double sensorValues[5] = {0.0, 0.0, 0.0, 0.0, 0.0};

/* Callibration method signature */
void infrared_calibrateAll(void);
void infrared_calibrateSingle(void);

/* ************************************************ */
/* Method name:        useSingleCalibration         */
/* Method description: decides if will use multi    */
/*                     sensor calibration           */
/* Input params:       decision: (yes/no) - (>1/0)  */
/* Output params:      n/a                          */
/* ************************************************ */
void infrared_useSingleCalibration(int decision){
  isUsingSingleCalibration = decision;
}

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
    if(isUsingSingleCalibration)
      infrared_calibrateSingle();
    else
      infrared_calibrateAll();
}

/* ************************************************ */
/* Method name:        infrared_calibrateAll        */
/* Method description: measures the maxium and min  */
/*                     values for each sensor       */
/* Input params:       n/a                          */
/* Output params:       n/a                         */
/* ************************************************ */
void infrared_calibrateAll(void){
  double conversionResult;

  /* Turns on Blue LED*/
  rgbLED_setRGBLED(0,0,1);
  /* Generates a delay of 2s before it starts callibrating */
  util_genDelayOf(3000);
  /* calibrates the white (line) values */
  for(int i=0;i<5;i++){
      /*  Measures 300 times for each sensor */
      int j = 300;
      while(j--){
        /* Initializes the conversion */
        adc_initConversion(infraredArray[i]);
        /* wait until it's done*/
        while(!adc_isAdcDone());
        /* Gets the result */
        conversionResult = adc_getConversionValue();
        /* If its value is higher than the highest for that sensor */
        if(conversionResult > sensorMaxValue[i]){
          /* Updates the maximum value */
          sensorMaxValue[i] = conversionResult;
        }
      }
    }
    /* Turn on Red LED */
    rgbLED_setRGBLED(1,0,0);
    /* Generates a 5s delay to change callibration position */
    util_genDelayOf(3000);
    /* calibrates the black (out of the line) values */
    for(int i=0;i<5;i++){
        /*  Measures 300 times for each sensor */
        int j = 300;
        while(j--){
          /* Initializes the conversion */
          adc_initConversion(infraredArray[i]);
          /* wait until it's done*/
          while(!adc_isAdcDone());
          /* Gets the result */
          conversionResult = adc_getConversionValue();
          /* If its value is higher than the highest for that sensor */
          if(conversionResult < sensorMinValue[i]){
            /* Updates the maximum value */
            sensorMinValue[i] = conversionResult;
          }
        }
      }
      /* Turn on Green LED */
      rgbLED_setRGBLED(0,1,0);
      /* Generates a delay to place the robot on the line to start*/
      util_genDelayOf(4000);
      /* Turn off LED */
      rgbLED_setRGBLED(0,0,0);
}

/* ************************************************ */
/* Method name:        infrared_calibrateSingle     */
/* Method description: measures the maxium and min  */
/*                     values for each sensor       */
/* Input params:       n/a                          */
/* Output params:       n/a                         */
/* ************************************************ */
void infrared_calibrateSingle(void){
  double conversionResult;

  /* calibrates the white (line) values */
  for(int i=0;i<5;i++){
      /*  Measures 300 times for each sensor */
      int j = 300;
      while(j--){
        /* Initializes the conversion */
        adc_initConversion(infraredArray[i]);
        /* wait until it's done*/
        while(!adc_isAdcDone());
        /* Gets the result */
        conversionResult = adc_getConversionValue();
        /* If its value is higher than the highest */
        if(conversionResult > overallMax){
          /* Updates the maximum value */
          overallMax = conversionResult;
        }
        if(conversionResult < overallMin){
          /* Updates the maximum value */
          overallMin = conversionResult;
        }
      }
    }
}


/* ************************************************ */
/* Method name:        infrared_updatePosition      */
/* Method description: reads sensors and calculates */
/*                     line position                */
/* Input params:       n/a                          */
/* Output params:  line position relative to center */
/* ************************************************ */
double infrared_updatePosition(void){
  double conversionResult;

  double pos = 0.0;
  double sum = 0.0;

  for(int i=0; i<5; i++){
    /* Start conversion for sensor i */
    adc_initConversion(infraredArray[i]);
    /* Wait until conversion is done */
    while(!adc_isAdcDone());
    /* gets the conversion result */
    conversionResult = adc_getConversionValue();
    /* Saturates the upper and lower readings to calibration values */
    if(isUsingSingleCalibration){
      if(conversionResult > overallMax){
        conversionResult = overallMax;
      }
      if(conversionResult < overallMin){
        conversionResult = overallMin;
      }
    }else{
      if(conversionResult > sensorMaxValue[i]){
        conversionResult = sensorMaxValue[i];
      }
      if(conversionResult < sensorMinValue[i]){
        conversionResult = sensorMinValue[i];
      }
    }
    sensorValues[i] = conversionResult;

    pos += sensorValues[i]*sensorWeights[i];
    sum += sensorValues[i];
  }

  return pos/sum;
}
