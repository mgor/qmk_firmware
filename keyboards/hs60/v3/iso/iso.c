#include "iso.h"

#ifdef RGB_MATRIX_ENABLE
const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, B_1,   A_1,   C_1}, //LA1
    {0, E_1,   D_1,   F_1}, //LA2
    {0, H_1,   G_1,   I_1}, //LA3
    {0, K_1,   J_1,   L_1}, //LA4
    {0, B_2,   A_2,   C_2}, //LA5
    {0, E_2,   D_2,   F_2}, //LA6
    {0, H_2,   G_2,   I_2}, //LA7
    {0, K_2,   J_2,   L_2}, //LA8
    {0, B_3,   A_3,   C_3}, //LA9
    {0, E_3,   D_3,   F_3}, //LA10
    {0, H_3,   G_3,   I_3}, //LA11
    {0, K_3,   J_3,   L_3}, //LA12
    {0, B_4,   A_4,   C_4}, //LA13
    {0, E_4,   D_4,   F_4}, //LA14
    {0, H_4,   G_4,   I_4}, //LA15
    {0, K_4,   J_4,   L_4}, //LA16
    {0, B_5,   A_5,   C_5}, //LA17
    {0, E_5,   D_5,   F_5}, //LA18
    {0, H_5,   G_5,   I_5}, //LA19
    {0, K_5,   J_5,   L_5}, //LA20
    {0, B_6,   A_6,   C_6}, //LA21
    {0, E_6,   D_6,   F_6}, //LA22
    {0, H_6,   G_6,   I_6}, //LA23
    {0, K_6,   J_6,   L_6}, //LA24
    {0, B_7,   A_7,   C_7}, //LA25
    {0, E_7,   D_7,   F_7}, //LA26
    {0, H_7,   G_7,   I_7}, //LA27
    {0, K_7,   J_7,   L_7}, //LA28
    {0, B_8,   A_8,   C_8}, //LA29
    {0, E_8,   D_8,   F_8}, //LA30
    {0, H_8,   G_8,   I_8}, //LA31
    {0, K_8,   J_8,   L_8}, //LA32
    {0, B_9,   A_9,   C_9}, //LA33
    {0, E_9,   D_9,   F_9}, //LA34
    {0, H_9,   G_9,   I_9}, //LA35
    {0, K_9,   J_9,   L_9}, //LA36
    {0, B_10,  A_10,  C_10}, //LA37
    {0, E_10,  D_10,  F_10}, //LA38
    {0, H_10,  G_10,  I_10}, //LA39
    {0, K_10,  J_10,  L_10}, //LA40
    {0, B_11,  A_11,  C_11}, //LA41
    {0, E_11,  D_11,  F_11}, //LA42
    {0, H_11,  G_11,  I_11}, //LA43
    {0, K_11,  J_11,  L_11}, //LA44
    {0, B_12,  A_12,  C_12}, //LA45
    {0, E_12,  D_12,  F_12}, //LA46
    {0, H_12,  G_12,  I_12}, //LA47
    {0, K_12,  J_12,  L_12}, //LA48
    {0, B_13,  A_13,  C_13}, //LA49
    {0, E_13,  D_13,  F_13}, //LA50
    {0, H_13,  G_13,  I_13}, //LA51
    {0, K_13,  J_13,  L_13}, //LA52
    {0, B_14,  A_14,  C_14}, //LA53
    {0, E_14,  D_14,  F_14}, //LA54
    {0, H_14,  G_14,  I_14}, //LA55
    {0, K_14,  J_14,  L_14}, //LA56
    {0, B_15,  A_15,  C_15}, //LA57
    {0, E_15,  D_15,  F_15}, //LA58
    {0, H_15,  G_15,  I_15}, //LA59
    {0, K_15,  J_15,  L_15}, //LA60
    {0, B_16,  A_16,  C_16}, //LA61
    {0, E_16,  D_16,  F_16}, //LA62
    {0, H_16,  G_16,  I_16}, //LA63
    {0, K_16,  J_16,  L_16}, //LA64
};

led_config_t g_led_config = { {
    // Key Matrix to LED index
    // LA1,  LA5,   LA9, LA13, LA17, LA21, LA25, LA29, LA33, LA37, LA41, LA45, LA49, LA53,
    // LA2,  LA6,  LA10, LA14, LA18, LA22, LA26, LA30, LA34, LA38, LA42, LA46, LA50,  ---,
    // LA3,  LA7,  LA11, LA15, LA19, LA23, LA27, LA31, LA35, LA39, LA43, LA47, LA54, LA55,
    // LA4,  LA48,  LA8, LA12, LA16, LA20, LA24, LA28, LA32, LA36, LA40, LA44,  ---, LA52,
    // LA57, LA58, LA59,  ---,  ---,  ---, LA60,  ---,  ---,  ---, LA62, LA63, LA64, LA56
    {   0,   4,  8,     12,     16,     20,  24,     28,     32,     36,  40,  44,     48,     52 },
    {   1,   5,  9,     13,     17,     21,  25,     29,     33,     37,  41,  45,     49, NO_LED },
    {   2,   6, 10,     14,     18,     22,  26,     30,     34,     38,  42,  46,     53,     54 },
    {   3,  47,  7,     11,     15,     19,  23,     27,     31,     35,  39,  43, NO_LED,     51 },
    {  56,  57, 58, NO_LED, NO_LED, NO_LED,  59, NO_LED, NO_LED, NO_LED,  61,  62,     63,     55 }
}, {
    // LED Index to Physical position
    // LA1..LA13
    {0, 0}    , {0, 16}  , {0, 32} ,  {0, 48}  , {17, 0}  , {17, 16} , {17, 32}, {34, 48} , {34, 0}  , {34, 16} , {34, 32} , {52, 48} , {52, 0}  , \
    // LA14..LA26
    {52, 16}  , {52, 32} , {69, 48} , {69, 0}  , {69, 16} , {69, 32} , {86, 48}, {86, 0}  , {86, 16} , {86, 32} , {103, 48}, {103, 0} , {103, 16}, \
    // LA27..LA38
    {103, 32} , {103, 48}, {121, 0},  {121, 16}, {121, 32}, {138, 48}, {138, 0}, {138, 16}, {138, 32}, {155, 48}, {155, 0} , {155, 16},            \
    // LAA39..LA50
    {155, 32} , {172, 48}, {172, 0},  {172, 16}, {172, 32}, {190, 48}, {190, 0}, {190, 16}, {190, 32}, {17, 48} , {207, 0} , {207, 16},            \
    // LA51 -- not used
    {255, 255},                                                                                                                                    \
    // LA52..LA60
    {224, 48} , {224, 0} , {207, 32}, {224, 32}, {224, 64}, {0, 64}  , {17, 64}, {24, 64} , {103, 64},                                             \
    // LA61 -- not used
    {255, 255},                                                                                                                                    \
    // LA62..LA64
    {172, 64} , {190, 64}, {207, 64}
}, {
    // LED Index to Flag
    // LA1-LA4
    LED_FLAG_MODIFIER, LED_FLAG_MODIFIER, LED_FLAG_INDICATOR, LED_FLAG_MODIFIER, \
    // LA5-LA8
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,  LED_FLAG_KEYLIGHT, \
    // LA9-LA12
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,  LED_FLAG_KEYLIGHT, \
    // LA13-LA16
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,  LED_FLAG_KEYLIGHT, \
    // LA17-LA20
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,  LED_FLAG_KEYLIGHT, \
    // LA21-LA24
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,  LED_FLAG_KEYLIGHT, \
    // LA25-LA28
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,  LED_FLAG_KEYLIGHT, \
    // LA29-LA32
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,  LED_FLAG_KEYLIGHT, \
    // LA33-LA36
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,  LED_FLAG_KEYLIGHT, \
    // LA37-LA40
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,  LED_FLAG_KEYLIGHT, \
    // LA41-LA44
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,  LED_FLAG_KEYLIGHT, \
    // LA45-LA48
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,  LED_FLAG_KEYLIGHT, \
    // LA49-LA52
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_NONE,      LED_FLAG_MODIFIER, \
    // LA53-LA56
    LED_FLAG_MODIFIER, LED_FLAG_KEYLIGHT, LED_FLAG_MODIFIER,  LED_FLAG_MODIFIER, \
    // LA57-LA64
    LED_FLAG_MODIFIER, LED_FLAG_MODIFIER, LED_FLAG_MODIFIER,  LED_FLAG_MODIFIER, LED_FLAG_NONE, LED_FLAG_MODIFIER, LED_FLAG_MODIFIER, LED_FLAG_MODIFIER
} };
#endif

#if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
static uint16_t idle_timer = 0;
static bool rgb_idle = false;
static uint8_t halfmin_counter = 0;
#endif

void keyboard_post_init_kb(void) {
    #ifdef RGB_MATRIX_ENABLE
    // disable non existing LED's, keyboards/wilba_tech/wt_rgb_backlight.c#L3186-L3203
    IS31FL3733_set_led_control_register(51-1, false, false, false);
    IS31FL3733_set_led_control_register(61-1, false, false, false);
    IS31FL3733_update_led_control_registers(DRIVER_ADDR_1, 0);

    rgb_matrix_enable();
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv(HSV_CYAN);
    #endif

    #ifdef RGBLIGHT_ENABLE
    rgblight_enable();
    rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_sethsv(HSV_CYAN);
    #endif

    keyboard_post_init_user();
}

void matrix_init_kb(void) {
    #ifdef CONSOLE_ENABLE
    debug_enable=true;
    debug_matrix=true;
    debug_keyboard=true;
    uint8_t sleep_timer = timer_read();

    while (timer_elapsed(sleep_timer) < 2000); // sleep for 2 seconds...
    #endif

    matrix_init_user();
}

void matrix_scan_kb(void) {
    #if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
    if (idle_timer == 0) {
        idle_timer = timer_read();
    }

    if (!rgb_idle && timer_elapsed(idle_timer) > 30000) {
        halfmin_counter++;
        idle_timer = timer_read();
    } else if (!rgb_idle && RGB_DISABLE_AFTER_IDLE > 0 && halfmin_counter >= RGB_DISABLE_AFTER_IDLE * 2) {
        #ifdef RGB_MATRIX_ENABLE
        rgb_matrix_disable_noeeprom();
        #endif
        #ifdef RGBLIGHT_ENABLE
        rgblight_disable_noeeprom();
        #endif
        rgb_idle = true;
        halfmin_counter = 0;
    }
    #endif
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    #if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
    if (record->event.pressed) {
        if (rgb_idle) {
            #ifdef RGB_MATRIX_ENABLE
            rgb_matrix_enable_noeeprom();
            #endif
            #ifdef RGBLIGHT_ENABLE
            rgblight_enable_noeeprom();
            #endif
            rgb_idle = false;
        }
        idle_timer = timer_read();
        halfmin_counter = 0;
    }
    #endif

    return process_record_user(keycode, record);
}

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }

    return true;
}

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    #ifdef RGB_MATRIX_ENABLE
    if (host_keyboard_led_state().caps_lock) {
        for (uint8_t i = led_min; i < led_max; i++) {
            if (g_led_config.flags[i] & LED_FLAG_KEYLIGHT) {
                rgb_matrix_set_color(i, RGB_RED);
            }
        }
    }
    #endif

    return rgb_matrix_indicators_advanced_user(led_min, led_max);
}
