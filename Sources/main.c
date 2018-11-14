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
#include "ADC/adc.h"
#include "PID/pid.h"
#include "KL25Z/rgbLED.h"

/* constant definitions */
#define TIME_IN_MILISECONDS				30
#define ECC_PERIOD   TIME_IN_MILISECONDS * 1000 /* micro seconds */
#define PWM_REFERENCE 60

/* Variables */
volatile unsigned int eccLock = 1;

/* Method signatures */
void ecc_interruptionRoutine(void);
void systemSetup(void);
void sensorTest(double currentPosition);
void eccTimeTest(int on);

int main(void){
	/* Selects type of callibration to be performed by the sensors */
	infrared_useSingleCalibration(0);
	/* System setup */
	systemSetup();

	double currentPosition, posControl;
	pwm_setDutyCycle(RIGHT_ENGINE, PWM_REFERENCE);
	pwm_setDutyCycle(LEFT_ENGINE, PWM_REFERENCE);

	/* ECC Loop */
    while(1) {
			/* Sets test port */
			// eccTimeTest(1);
			/* Acquires current position from sensors */
			currentPosition = infrared_updatePosition();
			// sensorTest(currentPosition);

			/* Inputs on PID controller and gets control signal */
			posControl = pid_posUpdate(currentPosition);

			/* Applies control signal to PWMs */
			int rightPWM = PWM_REFERENCE+posControl;
			int leftPWM = PWM_REFERENCE-posControl;

			/* Limits the signal between 0 and 100 */
			if(rightPWM > 100){
				rightPWM = 100;
			}
			if(leftPWM > 100){
				leftPWM = 100;
			}
			if(rightPWM < 0){
				rightPWM = 0;
			}
			if(leftPWM < 0){
				leftPWM = 0;
			}

			/* Sets the new duty cycle after control */
			pwm_setDutyCycle(RIGHT_ENGINE, rightPWM);
			pwm_setDutyCycle(LEFT_ENGINE, leftPWM);

			/* ECC lock */
    	while(eccLock);
			/* Clears test port*/
			// eccTimeTest(0);
    	eccLock = 1;
    }
    /* Never leave main */
    return 0;
}

void systemSetup(void){
		/* Configures the system clock */
		mcg_clockInit();
		/* Initializes the ADC module -- MUST BE INITIALIZED BEFORE INFRARED */
		adc_initADCModule();
		/* Setup the PWM generator */
		pwm_setup();
		/* Setup the Infrared sensors */
		infrared_setup();
		/* Setup the tachometers */
		tachometer_setup();
		/* Install the ECC interruption routine */
		ecc_installISR(ECC_PERIOD, ecc_interruptionRoutine);
		/* Initializes the RGB Led module */
		rgbLED_initRGBLED();
		/* Configures a port to be used to measure ECC time */
		PORTC_PCR1 = PORT_PCR_MUX(1);
		GPIOC_PDDR |= (1 << 1);
}

/* Method to unlock the ECC and allow the cycle to reset */
void ecc_interruptionRoutine(void){
	eccLock = 0;
}

/* Method to test if sensors are working properly */
void sensorTest(double currentPosition){
	int test = 0;
	if(currentPosition >-2 && currentPosition < -1){
		/* FAR_LEFT - LEFT */
		test = 0;
	}
	if(currentPosition >-1 && currentPosition < 0){
		/* LEFT - CENTER */
		test = 0;
	}
	if(currentPosition > 0 && currentPosition < 1){
		/* CENTER - RIGHT */
		test = 0;
	}
	if(currentPosition >1 && currentPosition < 2){
		/* RIGHT - FAR_RIGHT */
		test = 0;
	}
	if(currentPosition > -0.1 && currentPosition < 0.1){
		/* CENTER */
		test = 0;
	}
}

/* Method to test ECC time */
void eccTimeTest(int on){
	if(on){
		/* Sets signal */
		GPIOC_PSOR = GPIO_PSOR_PTSO( (0x01U << 1) );
	}else{
		/* Clears signal */
		GPIOC_PCOR = GPIO_PCOR_PTCO( (0x01U << 1) );
	}
}
