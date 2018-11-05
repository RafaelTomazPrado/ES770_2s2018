/* ***************************************************************** */
/* File name:        adc.c                                           */
/* File description: configures and manipulates the Analogic-Digital */
/*                   converter.                                      */
/* Author name:      Rafael Tomaz Prado                              */
/* Creation date:    04nov2018                                       */
/* Revision date:    04nov2018                                       */
/* ***************************************************************** */

#include "ADC/adc.h"
#include "KL25Z/board.h"

/* Defines a shortcut for the COCO register section */
#define ADC0_SC1A_COCO (ADC0_SC1A >> 7)

/* ************************************************** */
/* Method name: 	   adc_initADCModule          */
/* Method description: configure ADC module           */
/* Input params:	   n/a 			      */
/* Outpu params:	   n/a 			      */
/* ************************************************** */
void adc_initADCModule(void)
{
   /* un-gate port clock*/
   SIM_SCGC6 |= SIM_SCGC6_ADC0(CGC_CLOCK_ENABLED);	//Enable clock for ADC

   ADC0_CFG1 |= (ADC_CFG1_ADICLK(0b01) | ADC_CFG1_MODE(0b00) | ADC_CFG1_ADLSMP(0b0) | ADC_CFG1_ADIV(0b00) | ADC_CFG1_ADLPC(0b0));

   /*
   ADC_CFG1_ADICLK(x)// bus/2 clock selection
   ADC_CFG1_MODE(x)  // 8-bit conversion mode selection
   ADC_CFG1_ADLSMP(x)// Short sample time configuration
   ADC_CFG1_ADIV(x)  // Clock Divide Select (Divide by 1)
   ADC_CFG1_ADLPC(x) // Normal power Configuration
   */

   ADC0_SC2 |= (ADC_SC2_REFSEL(0b00) | ADC_SC2_DMAEN(0b0) | ADC_SC2_ACFE(0b0) | ADC_SC2_ADTRG(0b0));

   /*
   ADC_SC2_REFSEL(x)// reference voltage selection - external pins
   ADC_SC2_DMAEN(x) // dma disabled
   ADC_SC2_ACREN(x) // dont care - range function
   ADC_SC2_ACFGT(x) // dont care - 0 -> Less than, 1 -> Greater Than
   ADC_SC2_ACFE(x)  // compare function disabled
   ADC_SC2_ADTRG(x) // When software trigger is selected, a conversion is initiated following a write to SC1A
   ADC_SC2_ADACT(x) // HW-set indicates if a conversion is being held, is cleared when conversion is done
   */

   ADC0_CFG2 |= (ADC_CFG2_ADLSTS(0b00) | ADC_CFG2_ADHSC(0b0) | ADC_CFG2_ADACKEN(0b0) | ADC_CFG2_MUXSEL(0b0));

   /*
   ADC_CFG2_ADLSTS(x)  // default time
   ADC_CFG2_ADHSC(x)   // normal conversion sequence
   ADC_CFG2_ADACKEN(x) // disable adack clock
   ADC_CFG2_MUXSEL(x)  // select 'a' channels
   */

}

/* ************************************************** */
/* Method name: 	   adc_initConversion             */
/* Method description: init a conversion from D to A  */
/* Input params:	   n/a 							  */
/* Outpu params:	   n/a 							  */
/* ************************************************** */
void adc_initConversion(sensor s)
{
   ADC0_SC1A &= (ADC_SC1_ADCH(s) | ADC_SC1_DIFF(0b0) | ADC_SC1_AIEN(0b0));

   /*
   ADC_SC1_COCO(x) // conversion complete flag HW-set
   ADC_SC1_AIEN(x) // conversion complete interrupt disables
   ADC_SC1_DIFF(x) // selects single-ended conversion
   ADC_SC1_ADCH(x) // selects channel, view 3.7.1.3.1 ADC0 Channel Assignment ADC0_SE4a from datasheet
   */
}

/* ************************************************** */
/* Method name: 	   adc_isAdcDone              */
/* Method description: check if conversion is done    */
/* Input params:	   n/a 		              */
/* Outpu params:	   n/a 			      */
/* ************************************************** */
int adc_isAdcDone(void)
{
   if(ADC0_SC1A_COCO) // watch complete conversion flag
      return 1; // if the conversion is complete, return 1
   else
      return 0; // if the conversion is still taking place, return 0
}

/* ************************************************** */
/* Method name: 	   adc_getConversionValue     */
/* Method description: retrieve converted value       */
/* Input params:	   n/a 			      */
/* Outpu params:	   n/a 			      */
/* ************************************************** */
int adc_getConversionValue(void)
{
   return ADC0_RA; // return the register value that keeps the result of conversion
}
