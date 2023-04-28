// Copyright 2023 Mikael Göransson (@github@mgor.se)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define RGB_MATRIX_LED_COUNT 64
#define RGB_MATRIX_CENTER { 94, 16 }
#define DRIVER_COUNT 1
#define DRIVER_ADDR_1 0b1010000
#define RGB_DISABLE_WHEN_USB_SUSPENDED
#define RGB_DISABLE_AFTER_IDLE 3
#ifndef CONSOLE_ENABLE
    #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
    #define RGB_MATRIX_KEYPRESSES
    #define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#else
    #undef RGBLIGHT_ANIMATIONS
#endif

// https://mechboards.co.uk/blogs/news/adding-underglow-to-the-hs60
#ifdef RGBLIGHT_ENABLE
    #define RGB_DI_PIN A6
    #define RGBLED_NUM 16
#endif
