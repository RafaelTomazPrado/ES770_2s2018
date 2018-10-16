/* ***************************************************************** */
/* File name:        main.c                                          */
/* File description: main execution routine. Contains the ECC.       */
/* Author name:      Rafael Tomaz Prado                              */
/* Creation date:    02out2018                                       */
/* Revision date:    02out2018                                       */
/* ***************************************************************** */

/* Includes headers */
#include "fsl_device_registers.h"
#include "KL25Z/board.h"
#include "MCG/mcg_hal.h"
/* Peripheral includes */
#include "Timer/ecc_irc.h"
#include "Infrared/infrared.h"
#include "PWM/pwmController.h"
#include "Tachometer/tachometer.h"


/* constant definitions */
#define TIME_IN_MILISECONDS				30
#define ECC_PERIOD   TIME_IN_MILISECONDS * 1000 /* micro seconds */

/* Variables */
volatile unsigned int eccLock = 1;

/* Method signatures */
void ecc_interruptionRoutine(void);
void systemSetup(void);

int main(void)
{
	/* System setup */
	systemSetup();

	/* ECC Loop */
    while(1) {

    	/* ECC lock */
    	while(eccLock);
    	eccLock = 1;
    }
    /* Never leave main */
    return 0;
}

void systemSetup(void){
		/* Install the ECC interruption routine */
		ecc_installISR(ECC_PERIOD, ecc_interruptionRoutine);
		/* Configures the system clock */
		mcg_clockInit();
		/* Setup the PWM generator */
		pwm_setup();
		/* Setup the Infrared sensors */
		infrared_setup();
		/* Setup the tachometers */
		tachometer_setup();
}

/* Method to unlock the ECC and allow the cycle to reset */
void ecc_interruptionRoutine(void){
	eccLock = 0;
}
