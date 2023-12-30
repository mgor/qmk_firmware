/* Copyright 2021 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

#ifdef CONSOLE_ENABLE
#include "print.h"
#endif

#define CLICK_PERIOD_MS 60


enum keyboard_layers {
    _BASE = 0,
    _CAPS = 1,
    _FUNC = 2,
};

enum mg_keycodes {
    MG_RESET = SAFE_RANGE,
    MG_EEPS,
    MG_VAI,
    MG_VAD,
    MG_HUI,
    MG_HUD,
    MG_SAI,
    MG_SAD,
    MG_SPI,
    MG_SPD,
    WASD,
    AUTOCLK,
    MG_RGB_N,
    MG_RGB_P,
};

#define LT_CAPS LT(_CAPS, KC_CAPS)
#define MO_FUNC MO(_FUNC)
#ifndef ENCODER_ENABLE
#define RGB_P KC_TRNS
#define RGB_N KC_TRNS
#else
#define RGB_P MG_RGB_P
#define RGB_N MG_RGB_N
#endif

static uint16_t idle_timer = 0;
static uint16_t delay_timer = 0;
static uint8_t halfmin_counter = 0;
static bool rgb_matrix_idle = false;
static bool dip_switch_active;
static bool wasd_active = false;
static uint16_t wasd_timer = 0;
static deferred_token click_token = INVALID_DEFERRED_TOKEN;
static bool click_registered = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT_iso_83(
     KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_INS,   KC_MUTE,
     AUTOCLK,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_HOME,
     KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,                      KC_PGUP,
     LT_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,  KC_ENT,             KC_PGDN,
     KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,
     KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO_FUNC,  KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

[_FUNC] = LAYOUT_iso_83(
     WASD,               KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_MPRV,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  MG_RGB_P, MG_RGB_N, RGB_TOG,
     AUTOCLK,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_DEL,             KC_TRNS,
     KC_TRNS,  KC_TRNS,  MG_VAI,   MG_HUI,   MG_SAI,   MG_SPI,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  MG_RESET,                     KC_TRNS,
     KC_TRNS,  KC_TRNS,  MG_VAD,   MG_HUD,   MG_SAD,   MG_SPD,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  MG_EEPS,            KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),

[_CAPS] = LAYOUT_iso_83(
     KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_HOME,
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                      KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_CALC,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS)

};

void keyboard_post_init_user(void) {
#ifdef CONSOLE_ENABLE
    debug_enable=true;
#endif
}

static void mg_rgb(bool reverse) {
    delay_timer = timer_read();
    if (!reverse) {
        dip_switch_active ? rgb_matrix_step() : rgb_matrix_step_noeeprom();
    } else {
        dip_switch_active ? rgb_matrix_step_reverse() : rgb_matrix_step_reverse_noeeprom();
    }
}

static void mg_vai(void) {
    dip_switch_active ? rgb_matrix_increase_val() : rgb_matrix_increase_val_noeeprom();
}

static void mg_vad(void) {
    dip_switch_active ? rgb_matrix_decrease_val() : rgb_matrix_decrease_val_noeeprom();
}

static void mg_hui(void) {
    dip_switch_active ? rgb_matrix_increase_hue() : rgb_matrix_increase_hue_noeeprom();
}

static void mg_hud(void) {
    dip_switch_active ? rgb_matrix_decrease_hue() : rgb_matrix_decrease_hue_noeeprom();
}

static void mg_sai(void) {
    dip_switch_active ? rgb_matrix_increase_sat() : rgb_matrix_increase_sat_noeeprom();
}

static void mg_sad(void) {
    dip_switch_active ? rgb_matrix_decrease_sat() : rgb_matrix_decrease_sat_noeeprom();
}

static void mg_spi(void) {
    dip_switch_active ? rgb_matrix_increase_speed() : rgb_matrix_increase_speed_noeeprom();
}

static void mg_spd(void) {
    dip_switch_active ? rgb_matrix_decrease_speed() : rgb_matrix_decrease_speed_noeeprom();
}

static uint32_t auto_click_callback(uint32_t trigger_time, void* cb_arg) {
    if (click_registered) {
        unregister_code(KC_MS_BTN1);
        click_registered = false;
    } else {
        click_registered = true;
        register_code(KC_MS_BTN1);
    }

    return CLICK_PERIOD_MS / 2;
}

bool dip_switch_update_user(uint8_t index, bool active) {
    if (index == 0) {
        // if caps lock is enabled in "admin" mode, tap it turn caps off
        if (host_keyboard_led_state().caps_lock && dip_switch_active && !active) {
            tap_code(KC_CAPS);
        }
        dip_switch_active = active;
    }

    return false;
}

void matrix_init_user(void) {
    rgb_matrix_enable();
}

void matrix_scan_user(void) {
    if (idle_timer == 0) {
        idle_timer = timer_read();
    }

    if (!rgb_matrix_idle && timer_elapsed(idle_timer) > 30000) {
        halfmin_counter++;
        idle_timer = timer_read();
    }

    if (!rgb_matrix_idle && RGB_MATRIX_DISABLE_AFTER_TIMEOUT > 0 && halfmin_counter >= RGB_MATRIX_DISABLE_AFTER_TIMEOUT * 2) {
        rgb_matrix_disable_noeeprom();
        rgb_matrix_idle = true;
        halfmin_counter = 0;
    }

    if (wasd_active && timer_elapsed(wasd_timer) > (rand() % 30001) + 15000) {
        uint8_t key = rand() % 4;

        switch (key) {
            case 0:
                tap_code(KC_W);
                break;
            case 1:
                tap_code(KC_S);
                break;
            case 2:
                tap_code(KC_A);
                break;
            case 3:
                tap_code(KC_D);
                break;
        }

        wasd_timer = timer_read();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        if (rgb_matrix_idle) {
            rgb_matrix_enable_noeeprom();
            rgb_matrix_idle = false;
        }
        idle_timer = timer_read();
        halfmin_counter = 0;
    }

    // keycodes that should be handled both up and down
    switch (keycode & 0xFF) { // KC_ value in the first 8 bits, if wrapped with MO, LT etc.
        case KC_CAPS:
            if (!dip_switch_active) {
                return false;
            }
            break;
    }

    // keycodes that should be handled only down
    if (record->event.pressed) {
        // changing rgb settings, delay RGB indicators so we can se the changes
        if (keycode >= MG_VAI && keycode <= MG_SPD) {
            delay_timer = timer_read();
        }

        switch (keycode) {
            case MG_RESET:
                if (dip_switch_active) {
                    reset_keyboard();
                    return false;
                }
                break;
            case MG_EEPS:
                if (dip_switch_active) {
                    eeconfig_update_rgb_matrix();
                    return false;
                }
                break;
            case MG_VAI:
                mg_vai();
                return false;
            case MG_VAD:
                mg_vad();
                return false;
            case MG_HUI:
                mg_hui();
                return false;
            case MG_HUD:
                mg_hud();
                return false;
            case MG_SAI:
                mg_sai();
                return false;
            case MG_SAD:
                mg_sad();
                return false;
            case MG_SPI:
                mg_spi();
                return false;
            case MG_SPD:
                mg_spd();
                return false;
            case WASD:
                wasd_active = !wasd_active;
                if (!wasd_active) {
                    wasd_timer = 0;
                } else {
                    wasd_timer = timer_read();
                }
                return false;
            case AUTOCLK:
                if (click_token != INVALID_DEFERRED_TOKEN) {
                    cancel_deferred_exec(click_token);
                    click_token = INVALID_DEFERRED_TOKEN;
                    if (click_registered) {
                        unregister_code(KC_MS_BTN1);
                        click_registered = false;
                    }
                } else {
                    uint32_t next_delay_ms = auto_click_callback(next_delay_ms, NULL);
                    click_token = defer_exec(next_delay_ms, auto_click_callback, NULL);
                }
                return false;
            case MG_RGB_N:
                mg_rgb(false);
                return false;
            case MG_RGB_P:
                mg_rgb(true);
                return false;
            default:
                break;
        }
    }

    return true;
}

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index != 0) {
        return true;
    }

    if (layer_state_is(_FUNC)) {
        mg_rgb(clockwise);
    } else if (layer_state_is(_CAPS)) {
        clockwise ? tap_code(KC_PGUP) : tap_code(KC_PGDN);
    } else { // _BASE
        clockwise ? tap_code(KC_VOLU) : tap_code(KC_VOLD);
    }

    return false; // do not run encoder_update_kb
}
#endif

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    RGB color = { .r = -1, .g = -1, .b = -1};
    if (wasd_active && click_token != INVALID_DEFERRED_TOKEN) { // RGB_GOLDENROD
        color.r = 0xD9;
        color.g = 0xA5;
        color.b = 0x21;
    } else if (wasd_active) { // RGB_CHARTREUSE
        color.r = 0x80;
        color.g = 0xFF;
        color.b = 0x00;
    } else if (click_token != INVALID_DEFERRED_TOKEN) { // RGB_MAGENTA
        color.r = 0xFF;
        color.g = 0x00;
        color.b = 0xFF;
    } else if (layer_state_is(_BASE) && host_keyboard_led_state().caps_lock && dip_switch_active) {
        color.r = 0xFF;
        color.g = 0x80;
        color.b = 0x00;
    } else {
        HSV hsv = {0, 0, 0};

        if (layer_state_is(_FUNC)) {
            if (dip_switch_active) {
                hsv.v = 0;
            } else {
                hsv.h = 85;
            }

            // rgb_matrix_mode has been changed, want to see a preview of it
            if (delay_timer > 0 && timer_elapsed(delay_timer) < 3000) {
                return false;
            }

            delay_timer = 0;
        } else if (layer_state_is(_CAPS)) {
            hsv.h = 128;
        } else {
            return false;
        }

        hsv.s = 255;
        hsv.v = rgb_matrix_get_val();

        color = hsv_to_rgb(hsv);
    }


    if (color.r > -1 && color.g > -1 && color.b > -1) {
        for (uint8_t i = led_min; i <= led_max; i++) {
            rgb_matrix_set_color(i, color.r, color.g, color.b);
        }
    }

    return false;
}
