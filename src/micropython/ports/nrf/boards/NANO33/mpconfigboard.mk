MCU_SERIES = m4
MCU_VARIANT = nrf52
MCU_SUB_VARIANT = nrf52840
SD=s140
SOFTDEV_VERSION = 6.1.1
LD_FILES += boards/arduino_nano_33_ble/nano_bootloader.ld boards/nrf52840_1M_256k.ld

NRF_DEFINES += -DNRF52840_XXAA
