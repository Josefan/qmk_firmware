
# If you want to change the display of OLED, you need to change here
#SRC +=  ./lib/glcdfont.c \
        #./lib/rgb_state_reader.c \
        #./lib/layer_state_reader.c \
        #./lib/logo_reader.c \
        #./lib/keylogger.c \
        # ./lib/mode_icon_reader.c \
        # ./lib/host_led_state_reader.c \
        # ./lib/timelogger.c \


# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = atmel-dfu


EXTRAKEY_ENABLE = yes       # Audio control and System control
UNICODEMAP_ENABLE = yes
OLED_DRIVER_ENABLE = yes
WPM_ENABLE = yes

# RGB Matrix
RGB_MATRIX_ENABLE = no

# Enable WS2812 RGB underlight.
RGBLIGHT_ENABLE = yes

# if firmware size over limit, try this option
LTO_ENABLE = yes
