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
#define INFRARED_GPIO_BASE_PNT      PTC

#define INFRARED_MUX_ALT            0x01u

/* Individual sensor pins and directions */
#define INFRARED1_PIN               1U
#define INFRARED1_DIR               (GPIO_INPUT << INFRARED1_PIN)

#define INFRARED2_PIN               2U
#define INFRARED2_DIR               (GPIO_INPUT << INFRARED2_PIN)

#define INFRARED3_PIN               3U
#define INFRARED3_DIR               (GPIO_INPUT << INFRARED3_PIN)

#define INFRARED4_PIN               4U
#define INFRARED4_DIR               (GPIO_INPUT << INFRARED4_PIN)

#define INFRARED5_PIN               5U
#define INFRARED5_DIR               (GPIO_INPUT << INFRARED5_PIN)

/*         End of Infrared sensors definitions          */

/*            Tachometers definitions          */
#define TACHOMETER_PORT_BASE_PNT     PORTE
#define TACHOMETER_CNT_BASE_PNT      PTE

#define TACHOMETER_RIGHT_PIN         29U
#define TACHOMETER_LEFT_PIN          30U

#define TACHOMETER_ALT_COUNT         0x04u
/*         End of Tachometers definitions        */

/*            TPM definitions          */
#define TPM_CMOD_ALT_EXTERNAL     0x02u          /* Select the TPM operation with external clock */
#define TPM_CMOD_ALT_LPTMR        0x01u          /* Select the TPM operation with LPTMR */
#define TPM_CPWMS_UP              0x00u          /* Select Up counting mode */
#define TPM_CPWMS_DOWN            0x01u          /* Select Up-down counting mode */
#define TPM_PS_ALT_DIV1           0x00u          /* Select pre-scaler division by 1 */
#define TPM_PWM_MUX_ALT           0x03u          /* Selects the PWM alternative for port */
// Defines the external clock source for TPM0
#define SOPT4_TPM0_CLKIN0_SEL 		~SIM_SOPT4_TPM0CLKSEL(0x01u)
#define SOPT4_TPM1_CLKIN1_SEL 		SIM_SOPT4_TPM1CLKSEL(0x01u)

/*         End of TPM definitions        */

/* Defines a type to map which engine is being manipulated */
typedef enum{
    RIGHT,
    LEFT
} engine;


#endif /* KL25Z_BOARD_H */
