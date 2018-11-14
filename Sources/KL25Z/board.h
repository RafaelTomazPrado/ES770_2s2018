#ifndef KL25Z_BOARD_H
#define KL25Z_BOARD_H

#include <MKL25Z4.h>

/* Clock gate control */
#define  CGC_CLOCK_DISABLED         0x00U
#define  CGC_CLOCK_ENABLED          0x01U

/* GPIO input / output */
#define GPIO_INPUT                  0x00U
#define GPIO_OUTPUT                 0x01U

/*            Infrared sensors definitions          */
#define INFRARED_PORT_BASE_PNT      PORTC
#define INFRARED_MUX_ALT            0x00u /* ADC alternative */

/*         End of Infrared sensors definitions          */

/*            Tachometers definitions          */
#define TACHOMETER_PORT_BASE_PNT     PORTE
#define TACHOMETER_CNT_BASE_PNT      PTE

#define TACHOMETER_RIGHT_PIN         29U
#define TACHOMETER_LEFT_PIN          30U

#define TACHOMETER_ALT_COUNT         0x03u
/*         End of Tachometers definitions        */

/*            TPM definitions          */
#define SOPT2_TPMSRC_OSCERCLK     0x02u         // Selects TPM clock source

#define TPM_CMOD_ALT_EXTERNAL     0x02u          /* Select the TPM operation with external clock */
#define TPM_CMOD_ALT_LPTMR        0x01u          /* Select the TPM operation with LPTMR */
#define TPM_CPWMS_DOWN            0x01u          /* Select Up-down counting mode */
#define TPM_PS_ALT_DIV1           0x00u          /* Select pre-scaler division by 1 */
#define TPM_PS_ALT_DIV128         0x08u          /* Select pre-scaler division by 128 */
#define TPM_PWM_MUX_ALT           0x03u          /* Selects the PWM alternative for port */

/*         End of TPM definitions        */

/* Defines a type to map which engine is being manipulated */
typedef enum{
    RIGHT_ENGINE,
    LEFT_ENGINE
} engine;

/* Define a sensor type */
typedef enum{
  FAR_LEFT,
  LEFT,
  CENTER,
  RIGHT,
  FAR_RIGHT
}sensor;

#endif /* KL25Z_BOARD_H */
