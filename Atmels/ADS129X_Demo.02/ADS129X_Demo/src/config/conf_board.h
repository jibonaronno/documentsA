/**
 * \file
 *
 * \brief Board configuration.
 *
 * Copyright (c) 2012-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef CONF_BOARD_H_INCLUDED
#define CONF_BOARD_H_INCLUDED

/** Enable Com Port. */
#define CONF_BOARD_UART_CONSOLE

#define WITH_BLUETOOTH_MODULE
#ifdef WITH_BLUETOOTH_MODULE
#define WITHOUT_PARALLEL_DISPLAY
#endif

//! [TMOUT config]
/* Use TC Peripheral 0. */
#define TC_TMOUT TC0
#define TC_TMOUT_CHN 0
#define TC_TMOUT_Handler TC0_Handler
#define ID_TC_TMOUT ID_TC0
#define TMOUT_BASE_FREQ_HZ  (100)
//! [TMOUT config]

//! [tc_define_ch1]
/* Configure TC0 channel 1 as waveform output. */
#define TC_CHANNEL_WAVEFORM 1
#define ID_TC_WAVEFORM      ID_TC1
#define PIN_TC_WAVEFORM     PIN_TC0_TIOA1
#define PIN_TC_WAVEFORM_MUX PIN_TC0_TIOA1_MUX
//! [tc_define_ch1]

//! [tc_define_ch2]
/* Configure TC0 channel 2 as capture input. */
#define TC_CHANNEL_CAPTURE 2
#define ID_TC_CAPTURE ID_TC2
#define PIN_TC_CAPTURE PIN_TC0_TIOA2
#define PIN_TC_CAPTURE_MUX PIN_TC0_TIOA2_MUX
//! [tc_define_ch2]

//! [tc_define_irq_handler]
/* Use TC2_Handler for TC capture interrupt. */
#define TC_Handler  TC2_Handler
#define TC_IRQn     TC2_IRQn
//! [tc_define_irq_handler]

//! [board clock configuration]
#define BOARD_FREQ_SLCK_XTAL        (32768U)
#define BOARD_FREQ_SLCK_BYPASS      (32768U)
#define BOARD_FREQ_MAINCK_XTAL      (48000000U)/*(12000000U)*/
#define BOARD_FREQ_MAINCK_BYPASS    (48000000U)/*(12000000U)*/
#define BOARD_MCK                   (48000000U)/*CHIP_FREQ_CPU_MAX*/
#define BOARD_OSC_STARTUP_US        15625
//! [board clock configuration]

//! [MicroSD card configuration]
#define ACCESS_MEM_TO_RAM_ENABLED
#define CONF_BOARD_SD_MMC_HSMCI     1
//#define SD_MMC_ENABLE               1
#define SD_MMC_HSMCI_MEM_CNT        1
#define SD_MMC_HSMCI_SLOT_0_SIZE    4 // 4-bits connector pin
#define PINS_HSMCI   {0x3fUL << 26, PIOA, ID_PIOA, PIO_PERIPH_C, PIO_PULLUP}

/* Card detect pin */
#if 1
#define SD_MMC_0_CD_PIN             IOPORT_CREATE_PIN(PIOB, 10)
#define SD_MMC_0_CD_GPIO            (PIO_PB10_IDX)
#define SD_MMC_0_CD_PIO_ID          ID_PIOB
#define SD_MMC_0_CD_FLAGS           (PIO_INPUT | PIO_PULLUP | PIO_OPENDRAIN)

#define SD_MMC_0_CD_DETECT_VALUE    0

#define SD_MMC_0_CD    {PIO_PB10, PIOB, ID_PIOB, PIO_INPUT, PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE}
#define SD_MMC_0_CD_MASK PIO_PB10
#define SD_MMC_0_CD_PIO PIOB
#define SD_MMC_0_CD_ID ID_PIOB
#define SD_MMC_0_CD_TYPE PIO_INPUT
#define SD_MMC_0_CD_ATTR (PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_EDGE)
#endif

#define PIN_HSMCI_MCCDA_GPIO        (PIO_PA28_IDX)
#define PIN_HSMCI_MCCDA_FLAGS       (PIO_PERIPH_C | PIO_DEFAULT | PIO_PULLUP)
#define PIN_HSMCI_MCCK_GPIO         (PIO_PA29_IDX)
#define PIN_HSMCI_MCCK_FLAGS        (PIO_PERIPH_C | PIO_DEFAULT | PIO_PULLUP)
#define PIN_HSMCI_MCDA0_GPIO        (PIO_PA30_IDX)
#define PIN_HSMCI_MCDA0_FLAGS       (PIO_PERIPH_C | PIO_DEFAULT | PIO_PULLUP)
#define PIN_HSMCI_MCDA1_GPIO        (PIO_PA31_IDX)
#define PIN_HSMCI_MCDA1_FLAGS       (PIO_PERIPH_C | PIO_DEFAULT | PIO_PULLUP)
#define PIN_HSMCI_MCDA2_GPIO        (PIO_PA26_IDX)
#define PIN_HSMCI_MCDA2_FLAGS       (PIO_PERIPH_C | PIO_DEFAULT | PIO_PULLUP)
#define PIN_HSMCI_MCDA3_GPIO        (PIO_PA27_IDX)
#define PIN_HSMCI_MCDA3_FLAGS       (PIO_PERIPH_C | PIO_DEFAULT | PIO_PULLUP)

#define RELEASE_HSMCI_PINS() do {\
    gpio_configure_pin(PIN_HSMCI_MCCDA_GPIO, (PIO_INPUT | PIO_PULLUP | PIO_OPENDRAIN)); \
    gpio_configure_pin(PIN_HSMCI_MCCK_GPIO, (PIO_INPUT | PIO_PULLUP | PIO_OPENDRAIN)); \
    gpio_configure_pin(PIN_HSMCI_MCDA0_GPIO, (PIO_INPUT | PIO_PULLUP | PIO_OPENDRAIN)); \
    gpio_configure_pin(PIN_HSMCI_MCDA1_GPIO, (PIO_INPUT | PIO_PULLUP | PIO_OPENDRAIN)); \
    gpio_configure_pin(PIN_HSMCI_MCDA2_GPIO, (PIO_INPUT | PIO_PULLUP | PIO_OPENDRAIN)); \
    gpio_configure_pin(PIN_HSMCI_MCDA3_GPIO, (PIO_INPUT | PIO_PULLUP | PIO_OPENDRAIN)); \
} while(0)

#define ASSIGN_HSMCI_PINS() do {\
    pio_configure_pin(PIN_HSMCI_MCCDA_GPIO, PIN_HSMCI_MCCDA_FLAGS); \
    pio_configure_pin(PIN_HSMCI_MCCK_GPIO, PIN_HSMCI_MCCK_FLAGS); \
    pio_configure_pin(PIN_HSMCI_MCDA0_GPIO, PIN_HSMCI_MCDA0_FLAGS); \
    pio_configure_pin(PIN_HSMCI_MCDA1_GPIO, PIN_HSMCI_MCDA1_FLAGS); \
    pio_configure_pin(PIN_HSMCI_MCDA2_GPIO, PIN_HSMCI_MCDA2_FLAGS); \
    pio_configure_pin(PIN_HSMCI_MCDA3_GPIO, PIN_HSMCI_MCDA3_FLAGS); \
} while(0)

#define SD_ON_IDX   (PIO_PB8_IDX)
#define SD_ON_PIN   IOPORT_CREATE_PIN(PIOB, 8)
#define SD_ON_PIO   ( PIO_PB8 )
#define SET_SD_OFF()   ( REG_PIOB_CODR |= SD_ON_PIO )
#define SET_SD_ON()  do { \
    REG_PIOB_SODR |= SD_ON_PIO; \
} while(0);
//! [MicroSD card configuration]

//! [ADS1298 configuration]
#define ADS129X_CASCADED_DEVS   2
#define SPI_MODULE     SPI

#define PINS_ADS_SPI_TYPE     PIO_PERIPH_A
#if ADS129X_CASCADED_DEVS == 2
#define PINS_ADS_SPI_PA_MASK     (PIO_PA14A_SPCK | PIO_PA13A_MOSI | PIO_PA12A_MISO | PIO_PA11A_NPCS0)
#else
#define PINS_ADS_SPI_PA_MASK     (PIO_PA14A_SPCK | PIO_PA13A_MOSI | PIO_PA12A_MISO)
#endif
#define PINS_ADS_SPI_PB_MASK     (PIO_PB14A_NPCS1)
#define PINS_ADS_SPI_PA_ATTR     PIO_DEFAULT
#define PINS_ADS_SPI_PB_ATTR     PIO_DEFAULT

#define SPI_CLOCK   (16000000UL)
#define SPI_CS_COUNT    ADS129X_CASCADED_DEVS
#if ADS129X_CASCADED_DEVS == 2
#define SPI_CHIP_ID_0 0  /* Master PIO_PA11A_NPCS0 */
#define SPI_CHIP_ID_1 1   /* PIO_PB14A_NPCS1 */
#else
#define SPI_CHIP_ID_0 1   /* Master PIO_PA11A_NPCS1 */
#endif

#if SPI_CLOCK == (16000000UL)
#define SPI_DLYBS         1  /* < Delay before SPCK */
#define SPI_DLYBCT        6  /* < Delay between consecutive transfers */
#elif SPI_CLOCK == (4000000UL)
#define SPI_DLYBS         1 /* < Delay before SPCK */
#define SPI_DLYBCT        4 /* < Delay between consecutive transfers */
#elif SPI_CLOCK == (20000000UL)
#define SPI_DLYBS         1 /* < Delay before SPCK */
#define SPI_DLYBCT        5 /* < Delay between consecutive transfers */
#warning "this is too fast and it does not work reliably"
#else
#error SPI_DLYBS and SPI_DLYBCT must be determined!!!
#endif

//GPIOs
#define ADS_START_PORT  (PIOB)
#define ADS_START_PIO   (PIO_PB3)
#define ADS_READY_PORT  (PIOA)
#define ADS_DRDY_PIO    (PIO_PA1)
#define ADS_PD_PORT     (PIOA)
#define ADS_PD_PIO      (PIO_PA6)
#define ADS_RESET_PORT  (PIOA)
#define ADS_RESET_PIO   (PIO_PA16)

#define PACE_RESET_PORT (PIOA)
#define PACE_RESET_PIO  (PIO_PA11)

#define CLR_PACE_RESET   ( REG_PIOA_CODR |= PACE_RESET_PIO )
#define SET_PACE_RESET   ( REG_PIOA_SODR |= PACE_RESET_PIO )

#define CLR_ADS1298_START   ( REG_PIOB_CODR |= ADS_START_PIO )
#define SET_ADS1298_START   ( REG_PIOB_SODR |= ADS_START_PIO )

#define CLR_ADS1298_PWD     ( REG_PIOA_CODR |= ADS_PD_PIO )
#define SET_ADS1298_PWD     ( REG_PIOA_SODR |= ADS_PD_PIO )

#define CLR_ADS1298_RESET   ( REG_PIOA_CODR |= ADS_RESET_PIO )
#define SET_ADS1298_RESET   ( REG_PIOA_SODR |= ADS_RESET_PIO )

#define GET_ADS1298_DRDY    (!(REG_PIOA_PDSR & (ADS_DRDY_PIO)))
//! [ADS1298 configuration]
#define PACEMAKER_PORT  (PIOA)
#define PACEMAKER_PIO   (PIO_PA2)
#if ADS129X_CASCADED_DEVS == 1
#define PACEMAKER_SPIKE (REG_PIOA_PDSR & PACEMAKER_PIO)
#else
#define PACEMAKER_SPIKE (!(REG_PIOA_PDSR & PACEMAKER_PIO))
#endif
//! [PACEMAKER DIGITAL SIGNAL]

//! [PACEMAKER DIGITAL SIGNAL]

//! [PWM pin definition]
#define PIN_BACKLIGHT_PGIO (PIO_PA0_IDX)
#define BACKLIGHT_PORT  (PIOA)
#define BACKLIGHT_PIO   (PIO_PA0)
#define BACKLIGHT_GPIO_OFF   ( REG_PIOA_CODR |= BACKLIGHT_PIO )

/** PWM Backlight LED pin definitions. */
#define PIN_PWM_BACKLIGHT_GPIO_IDX  PIO_PA0_IDX
#define PIN_PWM_BACKLIGHT_FLAGS     (PIO_PERIPH_A | PIO_DEFAULT)
#define PIN_PWM_BACKLIGHT_CHANNEL   PWM_CHANNEL_0

/** PWM frequency in Hz */
#define PWM_FREQUENCY      1000
/** Period value of PWM output waveform */
#define PERIOD_VALUE       100
/** Initial duty cycle value */
#define INIT_DUTY_VALUE    0
//! [PWM pin definition]

//! [Battery ADC]
#define ADC_CHANNELS_IN_USE (1)

#define BATTERY_ADC_PIO   (PIO_PB0X1_AD4)
#define BATTERY_ADC_CH    (ADC_CHANNEL_4)
//! [Battery ADC]

//! [LED (green)]
#define LED_PIN    IOPORT_CREATE_PIN(PIOB, 12)
#define LED_PIO     (PIO_PB12)
#define LED_OFF()   ( REG_PIOB_CODR |= LED_PIO )
#define LED_ON()    ( REG_PIOB_SODR |= LED_PIO )
#define LED_TOGGLE()( REG_PIOB_PDSR & LED_PIO ? (LED_OFF()) : (LED_ON()))
//! [LED (green)]

//! [Buttons]
// ENTER/ON (PB2/WKOUP12)
#define BUTTON_ENTER_PIN IOPORT_CREATE_PIN(PIOB, 2)
#define BUTTON_ENTER_ACTIVE (LOW)
#define WAKEUP_WAIT_INPUT_ID    (SUPC_WUIR_WKUPEN12)
#define WAKEUP_BACKUP_INPUT_ID  (SUPC_WUIR_WKUPEN12)
// UP
#define BUTTON_UP_PIN IOPORT_CREATE_PIN(PIOB, 4)
// DOWN
#define BUTTON_DOWN_PIN IOPORT_CREATE_PIN(PIOA, 15)
// EVENT/BACK
#define BUTTON_EVENT_PIN IOPORT_CREATE_PIN(PIOB, 13)

// Usage macros
#define KEY_UP_PRESSED      (!(REG_PIOB_PDSR & PIO_PB4))
#define KEY_DOWN_PRESSED    (!(REG_PIOA_PDSR & PIO_PA15))
#define KEY_ACTION_PRESSED  (!(REG_PIOB_PDSR & PIO_PB2))
#define KEY_EVENT_PRESSED   (!(REG_PIOB_PDSR & PIO_PB13))

//! [Buttons]

//!  [TWI I2C]
//@{
/** TWI0 pin definitions */
#define TWI0_DATA_GPIO   PIO_PA3_IDX
#define TWI0_DATA_FLAGS  (PIO_PERIPH_A)
#define TWI0_CLK_GPIO    PIO_PA4_IDX
#define TWI0_CLK_FLAGS   (PIO_PERIPH_A)

#define TWI_BUS_CLK_SPEED   (400000) /*50000 (50kHz)*/
//!  [TWI I2C]

//!  [LCD Power pin]
#define LCD_PWR_PIN IOPORT_CREATE_PIN(PIOB, 1)
#define LCD_PWR_PIO     (PIO_PB1)
#define LCD_PWR_OFF()   ( REG_PIOB_SODR |= LCD_PWR_PIO )
#define LCD_PWR_ON()    ( REG_PIOB_CODR |= LCD_PWR_PIO )
//!  [LCD Power pin]


//!  [LCD (parallel interface)]
// D0-7 -> PA18-25
#define PDATA_AND_MASK (0x03fC0000)
#define parallelLcdWriteByte(data)   (REG_PIOA_CODR = PDATA_AND_MASK, REG_PIOA_SODR = (((uint32_t)data) << 18) & PDATA_AND_MASK)

#define parallelLcdReadByte()        ((REG_PIOA_PDSR & PDATA_AND_MASK) >> 18)

#define parallelLcdSetInput()        do { \
    REG_PIOA_PER &= ~PDATA_AND_MASK; \
    REG_PIOA_ODR |= PDATA_AND_MASK; \
    REG_PIOA_PUER |= PDATA_AND_MASK; \
    REG_PIOA_PPDDR |= PDATA_AND_MASK; \
} while(0)

#define parallelLcdSetOutput()       do { \
    REG_PIOA_PER |= PDATA_AND_MASK; \
    REG_PIOA_OER |= PDATA_AND_MASK; \
    REG_PIOA_PUDR |= PDATA_AND_MASK; \
    REG_PIOA_PPDER |= PDATA_AND_MASK; \
} while(0)

#define LCD_RDB_PIN     IOPORT_CREATE_PIN(PIOA, 17)
#define LCD_RDB_PIO     ( PIO_PA17 )
#define SET_LCD_RDB     ( REG_PIOA_SODR |= LCD_RDB_PIO )
#define CLR_LCD_RDB     ( REG_PIOA_CODR |= LCD_RDB_PIO )

#define LCD_WRB_PIN     IOPORT_CREATE_PIN(PIOA, 9)
#define LCD_WRB_PIO     ( PIO_PA9 )
#define SET_LCD_WRB     ( REG_PIOA_SODR |= LCD_WRB_PIO )
#define CLR_LCD_WRB     ( REG_PIOA_CODR |= LCD_WRB_PIO )

#define LCD_CS_PIN      IOPORT_CREATE_PIN(PIOA, 5)
#define LCD_CS_PIO      ( PIO_PA5 )
#define SET_LCD_CS      ( REG_PIOA_SODR |= LCD_CS_PIO )
#define CLR_LCD_CS      ( REG_PIOA_CODR |= LCD_CS_PIO )

#define LCD_RS_PIN      IOPORT_CREATE_PIN(PIOB, 8)
#define LCD_RS_PIO      ( PIO_PB8 )
#define SET_LCD_RS      ( REG_PIOB_SODR |= LCD_RS_PIO )
#define CLR_LCD_RS      ( REG_PIOB_CODR |= LCD_RS_PIO )
//!  [LCD (parallel interface)]


//!  [LCD (spi-gpio interface)]
#define LCD_SPI_CS_IDX (PIO_PA24_IDX)
#define LCD_SPI_CS_PIN  IOPORT_CREATE_PIN(PIOA, PIO_PA24)
#define CLR_LCD_SPI_CS  REG_PIOA_CODR |= (PIO_PA24)
#define SET_LCD_SPI_CS  REG_PIOA_SODR |= (PIO_PA24)

#define LCD_SPI_SCK_IDX (PIO_PA23_IDX)
#define LCD_SPI_SCK_PIN  IOPORT_CREATE_PIN(PIOA, PIO_PA23)
#define CLR_LCD_SPI_SCK  REG_PIOA_CODR |= (PIO_PA23)
#define SET_LCD_SPI_SCK  REG_PIOA_SODR |= (PIO_PA23)

#define LCD_SPI_SDA_IDX (PIO_PA22_IDX)
#define LCD_SPI_SDA_PIN  IOPORT_CREATE_PIN(PIOA, PIO_PA22)
#define CLR_LCD_SPI_SDA  REG_PIOA_CODR |= (PIO_PA22)
#define SET_LCD_SPI_SDA  REG_PIOA_SODR |= (PIO_PA22)
#define GET_LCD_SPI_SDA  (REG_PIOA_PDSR & PIO_PA22)

#define LCD_SPI_SDA_AS_INPUT  do { \
    REG_PIOA_PER |= PIO_PA22; \
    REG_PIOA_ODR |= PIO_PA22; \
} while (0)

#define LCD_SPI_SDA_AS_OUTPUT  do { \
    REG_PIOA_PER |= PIO_PA22; \
    REG_PIOA_OER |= PIO_PA22; \
} while (0)
//!  [LCD (spi-gpio interface)]

//!  [LCD (spi-usart interface)]
#define LCD_MISO_PIO    PIO_PA21_IDX
#define LCD_MISO_FLAGS  (PIO_PERIPH_A)

#define LCD_MOSI_PIO    PIO_PA22_IDX
#define LCD_MOSI_FLAGS  (PIO_PERIPH_A)

#define LCD_SCK_PIO    PIO_PA23_IDX
#define LCD_SCK_FLAGS  (PIO_PERIPH_A)

#define LCD_NSS_PIO    PIO_PA24_IDX
#define LCD_NSS_FLAGS  (PIO_PERIPH_A)
//!  [LCD (spi-usart interface)]

#define LCD_SPI_A0_IDX (PIO_PA19_IDX)
#define LCD_SPI_A0_PIN  IOPORT_CREATE_PIN(PIOA, PIO_PA19)
#define CLR_LCD_SPI_A0  REG_PIOA_CODR |= (PIO_PA19)
#define SET_LCD_SPI_A0  REG_PIOA_SODR |= (PIO_PA19)

#define LCD_SPI_RESET_IDX (PIO_PA20_IDX)
#define LCD_SPI_RESET_PIN  IOPORT_CREATE_PIN(PIOA, PIO_PA20)
#define CLR_LCD_SPI_RESET  REG_PIOA_CODR |= (PIO_PA20)
#define SET_LCD_SPI_RESET  REG_PIOA_SODR |= (PIO_PA20)


//!  [Other GPIOs]
#define USB_CONNECTED_PIN   IOPORT_CREATE_PIN(PIOB, 9)
#define USB_CONNECTED_PIO   ( PIO_PB9 )
#define GET_USB_CONNECTED   ((REG_PIOB_PDSR & USB_CONNECTED_PIO) != 0)

#define SD_TO_USB_PIN       IOPORT_CREATE_PIN(PIOB, 11)
#define SD_TO_USB_PIO       ( PIO_PB11 )
#define SET_SD_TO_USB()     REG_PIOB_SODR |= SD_TO_USB_PIO
#define SET_SD_TO_CPU()     REG_PIOB_CODR |= SD_TO_USB_PIO
//!  [Other GPIOs]

#ifdef WITH_BLUETOOTH_MODULE

// UART config
#define PINS_UART0_MASK     (PIO_PA9A_URXD0 | PIO_PA10A_UTXD0)
#define PINS_UART0_PIO      PIOA
#define PINS_UART0_TYPE     PIO_PERIPH_A
#define PINS_UART0_ATTR     PIO_DEFAULT

// uart_dma driver config ->
#define CONF_BOARD_UART0
#define RX_UART_BUF0_SIZE 1024
#define TX_UART_BUF0_SIZE 1024
// <- uart_dma driver config

#define BT_RX_PIN_IDX (PIO_PA9_IDX)
#define BT_TX_PIN_IDX (PIO_PA10_IDX)

//#define USE_OLD_BT_ON_PIN
#ifdef USE_OLD_BT_ON_PIN
#define BT_ON_IDX   (PIO_PB8_IDX)
#define BT_ON_PIN   IOPORT_CREATE_PIN(PIOB, 8)
#define BT_ON_PIO   ( PIO_PB8 )
#define SET_BT_ON()   ( REG_PIOB_CODR |= BT_ON_PIO )
#define SET_BT_OFF()  do { \
        REG_PIOB_SODR |= BT_ON_PIO; \
        gpio_configure_pin(BT_RX_PIN_IDX, PIO_OUTPUT_0); \
        gpio_configure_pin(BT_TX_PIN_IDX, PIO_OUTPUT_0); \
    } while(0);
     
#else
#define BT_ON_IDX   (PIO_PA25_IDX)
#define BT_ON_PIN   IOPORT_CREATE_PIN(PIOA, 25)
#define BT_ON_PIO   ( PIO_PA25 )
#define SET_BT_ON()   ( REG_PIOA_SODR |= BT_ON_PIO )
#define SET_BT_OFF()  do { \
        REG_PIOA_CODR |= BT_ON_PIO; \
        gpio_configure_pin(BT_RX_PIN_IDX, PIO_OUTPUT_0); \
        gpio_configure_pin(BT_TX_PIN_IDX, PIO_OUTPUT_0); \
    } while(0);
#endif

#define BT_STATUS_IDX   (PIO_PA5_IDX)
#define BT_STATUS_PIN   IOPORT_CREATE_PIN(PIOA, 5)
#define BT_STATUS_PIO   ( PIO_PA5 )
#define BT_CONNECTED    (REG_PIOA_PDSR & BT_STATUS_PIO)

#endif

#define RESUME_LOCATION_REGISTER (GPBR0)
#define READ_RESUME_LOCATION() gpbr_read(RESUME_LOCATION_REGISTER)
#define WRITE_RESUME_LOCATION(location) gpbr_write(RESUME_LOCATION_REGISTER, location)

#define ON_POWERUP_STATUS_REGISTER (GPBR1)
typedef enum { opu_On, opu_Off, opu_Invalid } onPwrStatus_t;
#define READ_ON_POWERUP_STATUS() ((onPwrStatus_t) ((gpbr_read(ON_POWERUP_STATUS_REGISTER)) > opu_Invalid ? opu_Off : gpbr_read(ON_POWERUP_STATUS_REGISTER)))
#define WRITE_ON_POWERUP_STATUS(status) gpbr_write(ON_POWERUP_STATUS_REGISTER, status)

#define FW_MODULE_NAME  "CC300H-ATSAM4S\0"

/* Do not change this structure never ever -> */
struct firmwareData {
    char signature[16];
    char fwVersion[16];
    char buildDate[16];
};
/* <- Do not change this structure never ever */

extern volatile const struct firmwareData fwData;

#define KEEP_FIRMWARE_INFO if(fwData.signature[0]) { nop(); }  /* required to prevent the compiler from optimizing 'fwData' */

#define ENCODED_FW_VERSION (((fwData.fwVersion[0] - '0') << 4) | ((fwData.fwVersion[2] - '0') << 2) | (fwData.fwVersion[4] - '0'))

#endif /* CONF_BOARD_H_INCLUDED */
