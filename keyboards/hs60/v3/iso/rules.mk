# Do not put the microcontroller into power saving mode
# when we get USB suspend event. We want it to keep updating
# backlight effects.
OPT_DEFS += -DNO_SUSPEND_POWER_DOWN

# Build Options
#   change yes to no to disable
#
BACKLIGHT_ENABLE = no              # Enable keyboard backlight functionality
NO_USB_STARTUP_CHECK = no          # Disable initialization only when usb is plugged in
SERIAL_LINK_ENABLE = no
TAP_DANCE_ENABLE = no
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = yes

RGB_MATRIX_DRIVER = IS31FL3733

SRC += v3.c
