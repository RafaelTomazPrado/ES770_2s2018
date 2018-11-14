/* ***************************************************************** */
/* File name:        rgbLED.c		                                 */
/* File description: File dedicated to the hardware abstraction layer*/
/*                   related to the KL25Z RGB LED				     */
/* Author name:      Lucas Pagan, Antonio Ruette, Bruna Mattos		 */
/* Creation date:    16oct2018                                       */
/* Revision date:    16oct2018                                       */
/* ***************************************************************** */

#include "KL25Z/board.h"
#include "rgbLED.h"

/* ************************************************  */
/* Method name:        rgbLED_initRGBLED	         */
/* Method description: Initialize RGB LED device 	 */
/* Input params:       n/a                           */
/* Output params:      n/a                           */
/* ************************************************  */
void rgbLED_initRGBLED(void){
	/* un-gate port clock */
	SIM_SCGC5 |= SIM_SCGC5_PORTB(CGC_CLOCK_ENABLED);
	SIM_SCGC5 |= SIM_SCGC5_PORTD(CGC_CLOCK_ENABLED);

	/* set RGB LED pins as gpio  	*/
	/* PCR - Pin Control Register  	*/
	PORTB_PCR18 |= PORT_PCR_MUX(1);
	PORTB_PCR19 |= PORT_PCR_MUX(1);
	PORTD_PCR1  |= PORT_PCR_MUX(1);

	/* set right motor pin as a digital output */
	/* PDDR - Pin Data Direction Register      */
	GPIOB_PDDR |= GPIO_PDDR_PDD(1 << 18);
	GPIOB_PDDR |= GPIO_PDDR_PDD(1 << 19);
	GPIOD_PDDR |= GPIO_PDDR_PDD(1);
}

/* ************************************************ */
/* Method name:        rgbLED_setRGBLED		        */
/* Method description: set the RGB LED ON	        */
/* Input params:       cR, cG, cB: char             */
/* Output params:      n/a                          */
/* ************************************************ */
void rgbLED_setRGBLED(char cR, char cG, char cB)
{
	/* set RGB LED pins to high if the correspondent variable is 1 	*/
	/* PSOR - Pin Set Output Register    					 		*/
	/* PCOR - Pin Clear Output Register								*/

	if(cR == '1'){
		GPIOB_PSOR = GPIO_PSOR_PTSO( (0x01U << 18) );
	}
	else{
		GPIOB_PCOR = GPIO_PCOR_PTCO( (0x01U << 18) );
	}

	if(cG == '1'){
		GPIOB_PSOR = GPIO_PSOR_PTSO( (0x01U << 19) );
	}
	else{
		GPIOB_PCOR = GPIO_PCOR_PTCO( (0x01U << 19) );
	}

	if(cB == '1'){
		GPIOD_PSOR = GPIO_PSOR_PTSO( (0x01U << 1) );
	}
	else{
		GPIOD_PCOR = GPIO_PCOR_PTCO( (0x01U << 1) );
	}
}
