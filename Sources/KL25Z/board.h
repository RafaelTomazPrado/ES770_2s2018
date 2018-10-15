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


#endif /* KL25Z_BOARD_H */
