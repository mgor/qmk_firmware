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
};

#define LT_CAPS LT(_CAPS, KC_CAPS)
#define MO_FUNC MO(_FUNC)
static uint16_t idle_timer = 0;
static uint16_t delay_timer = 0;
static uint8_t halfmin_counter = 0;
static bool rgb_matrix_idle = false;
static bool dip_switch_active;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT_iso_83(
     KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_INS,   KC_MUTE,
     KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_HOME,
     KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,                      KC_PGUP,
     LT_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,  KC_ENT,             KC_PGDN,
     KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,
     KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO_FUNC,  KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

[_FUNC] = LAYOUT_iso_83(
     KC_TRNS,            KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,   RGB_TOG,
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
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
    switch (keycode & 0xFF) { // KC_ value in the first 8 bytes, if wrapped with MO, LT etc.
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
                dip_switch_active ? rgb_matrix_increase_val() : rgb_matrix_increase_val_noeeprom();
                return false;
            case MG_VAD:
                dip_switch_active ? rgb_matrix_decrease_val() : rgb_matrix_decrease_val_noeeprom();
                return false;
            case MG_HUI:
                dip_switch_active ? rgb_matrix_increase_hue() : rgb_matrix_increase_hue_noeeprom();
                return false;
            case MG_HUD:
                dip_switch_active ? rgb_matrix_decrease_hue() : rgb_matrix_decrease_hue_noeeprom();
                return false;
            case MG_SAI:
                dip_switch_active ? rgb_matrix_increase_sat() : rgb_matrix_increase_sat_noeeprom();
                return false;
            case MG_SAD:
                dip_switch_active ? rgb_matrix_decrease_sat() : rgb_matrix_decrease_sat_noeeprom();
                return false;
            case MG_SPI:
                dip_switch_active ? rgb_matrix_increase_speed() : rgb_matrix_increase_speed_noeeprom();
                return false;
            case MG_SPD:
                dip_switch_active ? rgb_matrix_decrease_speed() : rgb_matrix_decrease_speed_noeeprom();
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
        delay_timer = timer_read();
        if (dip_switch_active) {
            clockwise ? rgb_matrix_step() : rgb_matrix_step_reverse();
        } else {
            clockwise ? rgb_matrix_step_noeeprom() : rgb_matrix_step_reverse_noeeprom();
        }
    } else if (layer_state_is(_CAPS)) {
        clockwise ? tap_code(KC_PGUP) : tap_code(KC_PGDN);
    } else { // _BASE
        clockwise ? tap_code(KC_VOLU) : tap_code(KC_VOLD);
    }

    return false; // do not run encoder_update_kb
}
#endif

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (layer_state_is(_BASE) && host_keyboard_led_state().caps_lock) {
        for (uint8_t i = led_min; i <= led_max; i++) {
            if (g_led_config.flags[i] & LED_FLAG_KEYLIGHT) {
                rgb_matrix_set_color(i, RGB_ORANGE);
            }
        }
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
                return;
            }

            delay_timer = 0;
        } else if (layer_state_is(_CAPS)) {
            hsv.h = 128;
        } else {
            return;
        }

        hsv.s = 255;
        hsv.v = rgb_matrix_get_val();

        RGB rgb = hsv_to_rgb(hsv);

        for (uint8_t i = led_min; i <= led_max; i++) {
            if (g_led_config.flags[i] & LED_FLAG_KEYLIGHT) {
                rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
            }
        }
    }
}
