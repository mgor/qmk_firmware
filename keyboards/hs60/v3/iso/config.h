// Copyright 2023 Mikael Göransson (@github@mgor.se)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef RGB_MATRIX_ENABLE
    #define RGB_MATRIX_LED_COUNT 64
    #define DRIVER_COUNT 1
    #define DRIVER_ADDR_1 0b1010000
    #define RGB_DISABLE_WHEN_USB_SUSPENDED
    #define RGB_MATRIX_DISABLE_AFTER_TIMEOUT 3
    #ifndef CONSOLE_ENABLE
        #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
        #define RGB_MATRIX_KEYPRESSES
        //#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
        #define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_TYPING_HEATMAP
    #else
        #define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_COLOR
        #undef RGBLIGHT_ANIMATIONS
    #endif
#endif
