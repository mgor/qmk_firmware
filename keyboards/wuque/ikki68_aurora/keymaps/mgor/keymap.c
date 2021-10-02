/* Copyright 2021 wuquestudio
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
#include "config.h"

enum keyboard_layers {
    _BASE = 0,
    _FUNC = 1,
    _CAPS = 2,
};

#define MG_CAPS LT(_CAPS, KC_CAPS)
#define MG_FUNC MO(_FUNC)

#ifdef RGBLIGHT_ENABLE
static uint16_t idle_timer = 0;
static uint8_t halfmin_counter = 0;
static bool rgblight_idle = false;

const rgblight_segment_t PROGMEM mg_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, RGBLED_NUM, HSV_RED}
);

const rgblight_segment_t PROGMEM mg_func_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, RGBLED_NUM, HSV_GREEN}
);

const rgblight_segment_t PROGMEM mg_caps_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, RGBLED_NUM, HSV_CYAN}
);

const rgblight_segment_t* const PROGMEM mg_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    mg_capslock_layer,
    mg_func_layer,
    mg_caps_layer
);
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_68_iso_split_rshift(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,    KC_INS, KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,             KC_DEL, KC_PGDN,
        MG_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_BSLS,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RSFT,    KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MG_FUNC, KC_RCTL,    KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_FUNC] = LAYOUT_68_iso_split_rshift(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,     _______, _______,
        _______, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, EEP_RST, _______, RESET,               _______, _______,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,
        _______, _______, _______,                            _______,                            _______, _______, _______,    _______, _______, _______
    ),
    [_CAPS] = LAYOUT_68_iso_split_rshift(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,     _______, _______,
        _______, KC_PGUP, KC_HOME, KC_END,  _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______, _______,
        _______, _______, KC_PGDN, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,
        _______, _______, _______, _______, KC_CALC, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,
        _______, _______, _______,                            _______,                            _______, _______, _______,    KC_HOME, _______, KC_END
    ),
};

void matrix_scan_user(void) {
#ifdef RGBLIGHT_ENABLE
    if (idle_timer == 0) {
        idle_timer = timer_read();
    }

    if (!rgblight_idle && timer_elapsed(idle_timer) > 30000) {
        halfmin_counter++;
        idle_timer = timer_read();
    }

    if (!rgblight_idle && RGBLIGHT_DISABLE_AFTER_TIMEOUT > 0 && halfmin_counter >= RGBLIGHT_DISABLE_AFTER_TIMEOUT * 2) {
        rgblight_disable_noeeprom();
        rgblight_idle = true;
        halfmin_counter = 0;
    }
#endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef RGBLIGHT_ENABLE
    if (record->event.pressed) {
        if (rgblight_idle == true) {
            rgblight_enable_noeeprom();
            rgblight_idle = false;
        }
        idle_timer = timer_read();
        halfmin_counter = 0;
    }
#endif
    return true;
}

void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_layers = mg_rgb_layers;
#endif
}

#ifdef RGBLIGHT_ENABLE
void matrix_init_user(void) {
    // set default color and mode, do not use rgblight layer for _BASE...
    rgblight_enable();
    rgblight_mode(1);
    rgblight_sethsv(HSV_BLUE);
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}

uint32_t layer_state_set_user(uint32_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _FUNC));
    rgblight_set_layer_state(2, layer_state_cmp(state, _CAPS));

    return state;
}
#endif
