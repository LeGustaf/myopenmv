#define MICROPY_HW_BOARD_NAME       "OPENMV2"
#define MICROPY_HW_MCU_NAME         "STM32F427"
#define MICROPY_PY_SYS_PLATFORM     "OpenMV2"

#define MICROPY_FATFS_EXFAT         (1)
#define MICROPY_HW_HAS_SWITCH       (0)
#define MICROPY_HW_HAS_MMA7660      (0)
#define MICROPY_HW_HAS_LIS3DSH      (0)
#define MICROPY_HW_HAS_LCD          (0)
#define MICROPY_HW_ENABLE_RNG       (1)
#define MICROPY_HW_ENABLE_RTC       (1)
#define MICROPY_HW_ENABLE_TIMER     (1)
#define MICROPY_HW_ENABLE_SERVO     (1)
#define MICROPY_HW_ENABLE_DAC       (1)
#define MICROPY_HW_ENABLE_SPI1      (0)
#define MICROPY_HW_ENABLE_SPI2      (1)
#define MICROPY_HW_ENABLE_SPI3      (0)
#define MICROPY_HW_ENABLE_USB       (1)
#define MICROPY_HW_ENABLE_SDCARD    (1)
// Reserved DMA streams
#define MICROPY_HW_DMA2S1_IS_RESERVED
#define MICROPY_HW_TIM_IS_RESERVED(id) (id == 1 || id == 6)

#define MICROPY_HW_CLK_PLLM (6)
#define MICROPY_HW_CLK_PLLN (360)
#define MICROPY_HW_CLK_PLLQ (15)
#define MICROPY_HW_CLK_PLLP (RCC_PLLP_DIV4)

#define USBD_VID                      0x1209
#define USBD_PID                      0xabd1
#define USBD_LANGID_STRING            0x409
#define USBD_MANUFACTURER_STRING      "OpenMV"
#define USBD_PRODUCT_FS_STRING        "OpenMV Virtual Comm Port in FS Mode"
#define USBD_PRODUCT_HS_STRING        "OpenMV Virtual Comm Port in HS Mode"
#define USBD_SERIALNUMBER_FS_STRING   "000000000011"
#define USBD_SERIALNUMBER_HS_STRING   "000000000010"
#define USBD_INTERFACE_FS_STRING      "VCP Interface"
#define USBD_INTERFACE_HS_STRING      "VCP Interface"
#define USBD_CONFIGURATION_FS_STRING  "VCP Config"
#define USBD_CONFIGURATION_HS_STRING  "VCP Config"

// UART config
#define MICROPY_HW_UART3_TX  (pin_B10)
#define MICROPY_HW_UART3_RX  (pin_B11)
#define MICROPY_HW_UART3_RTS (pin_B14)
#define MICROPY_HW_UART3_CTS (pin_B13)

// I2C busses
#define MICROPY_HW_I2C2_SCL (pin_B10)
#define MICROPY_HW_I2C2_SDA (pin_B11)

// SPI busses
#define MICROPY_HW_SPI2_NSS  (pin_B12)
#define MICROPY_HW_SPI2_SCK  (pin_B13)
#define MICROPY_HW_SPI2_MISO (pin_B14)
#define MICROPY_HW_SPI2_MOSI (pin_B15)

// CAN busses
#define MICROPY_HW_CAN2_NAME "CAN2" // CAN2 on RX,TX = P3,P2 = PB12,PB13
#define MICROPY_HW_CAN2_TX          (pin_B13)
#define MICROPY_HW_CAN2_RX          (pin_B12)

// SD card detect switch
#define MICROPY_HW_SDCARD_DETECT_PIN        (pin_A15)
#define MICROPY_HW_SDCARD_DETECT_PULL       (GPIO_PULLUP)
#define MICROPY_HW_SDCARD_DETECT_PRESENT    (GPIO_PIN_RESET)

// USB config
#define MICROPY_HW_USB_FS                   (1)
#define MICROPY_HW_USB_VBUS_DETECT_PIN      (pin_A9)
//#define MICROPY_HW_USB_OTG_ID_PIN         (pin_A10)

// USRSW is pulled low. Pressing the button makes the input go high.
#define MICROPY_HW_USRSW_PIN        (pin_A0)
#define MICROPY_HW_USRSW_PULL       (GPIO_NOPULL)
#define MICROPY_HW_USRSW_EXTI_MODE  (GPIO_MODE_IT_RISING)
#define MICROPY_HW_USRSW_PRESSED    (1)

// LEDs
#define MICROPY_HW_LED1             (pin_C0) // red
#define MICROPY_HW_LED2             (pin_C2) // green
#define MICROPY_HW_LED3             (pin_C1) // blue
#define MICROPY_HW_LED4             (pin_E2) // IR 
#define MICROPY_HW_LED_OTYPE        (GPIO_MODE_OUTPUT_PP)
#define MICROPY_HW_LED_ON(pin)      (pin->gpio->BSRR = (pin->pin_mask << 16))
#define MICROPY_HW_LED_OFF(pin)     (pin->gpio->BSRR = pin->pin_mask)

// Servos
#define PYB_SERVO_NUM (2)
