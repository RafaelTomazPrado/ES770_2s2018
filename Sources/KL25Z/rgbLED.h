/* ***************************************************************** */
/* File name:        rgbLED.h		                                 */
/* File description: Header file containing the functions/methods    */
/*                   interfaces for handling the RGB LED from KL25Z  */
/* Authors names:    Lucas Pagan, Antonio Ruette, Bruna Mattos       */
/* Creation date:    16oct2018                                       */
/* Revision date:    16oct2018                                       */
/* ***************************************************************** */

#ifndef SOURCES_RGBLED_H_
#define SOURCES_RGBLED_H_

/* ************************************************  */
/* Method name:        rgbLED_initRGBLED	         */
/* Method description: Initialize RGB LED device 	 */
/* Input params:       n/a                           */
/* Output params:      n/a                           */
/* ************************************************  */
void rgbLED_initRGBLED(void);

/* ************************************************ */
/* Method name:        rgbLED_setRGBLED		        */
/* Method description: set the RGB LED ON	        */
/* Input params:       cR, cG, cB: char             */
/* Output params:      n/a                          */
/* ************************************************ */
void rgbLED_setRGBLED(char cR, char cG, char cB);

#endif /* SOURCES_RGBLED_H_ */
