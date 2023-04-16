# Do not put the microcontroller into power saving mode
# when we get USB suspend event. We want it to keep updating
# backlight effects.
OPT_DEFS += -DNO_SUSPEND_POWER_DOWN

NO_USB_STARTUP_CHECK = no          # Disable initialization only when usb is plugged in

RGB_MATRIX_DRIVER = IS31FL3733
