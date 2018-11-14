/* ***************************************************************** */
/* File name:        adc.h                                           */
/* File description: configures and manipulates the Analogic-Digital */
/*                   converter.                                      */
/* Author name:      Rafael Tomaz Prado                              */
/* Creation date:    04nov2018                                       */
/* Revision date:    04nov2018                                       */
/* ***************************************************************** */

#ifndef ADC_H
#define ADC_H

#include "KL25Z/board.h"

/* ************************************************** */
/* Method name: 	   adc_initADCModule          */
/* Method description: configure ADC module           */
/* Input params:	   n/a 			      */
/* Outpu params:	   n/a 			      */
/* ************************************************** */
void adc_initADCModule(void);

/* ************************************************** */
/* Method name: 	   adc_initConversion             */
/* Method description: init a conversion from D to A  */
/* Input params:	   n/a 							  */
/* Outpu params:	   n/a 							  */
/* ************************************************** */
void adc_initConversion(sensor s);

/* ************************************************** */
/* Method name: 	   adc_isAdcDone              */
/* Method description: check if conversion is done    */
/* Input params:	   n/a 		              */
/* Outpu params:	   n/a 			      */
/* ************************************************** */
int adc_isAdcDone(void);

/* ************************************************** */
/* Method name: 	   adc_getConversionValue     */
/* Method description: retrieve converted value       */
/* Input params:	   n/a 			      */
/* Outpu params:	   n/a 			      */
/* ************************************************** */
int adc_getConversionValue(void);

#endif /* ADC_H */
