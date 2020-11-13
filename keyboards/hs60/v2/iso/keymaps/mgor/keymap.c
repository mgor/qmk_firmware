/* Copyright 2018 Yiancar
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

enum keyboard_layers {
  _BASE = 0, // Base Layer
  _FUNC,     // Function Layer
  _CAPS,     // Caps Layer
  _MENU      // Menu Layer
};

#define MG_CAPS LT(_CAPS, KC_CAPS)
#define MG_UP RSFT_T(KC_UP)
#define MG_LEFT LT(_FUNC, KC_LEFT)
#define MG_DOWN LT(_MENU, KC_DOWN)
#define MG_RIGHT RCTL_T(KC_RIGHT)

// https://beta.docs.qmk.fm/using-qmk/hardware-features/lighting/feature_rgblight
#ifdef RGBLIGHT_ENABLE
    #define MG_RGB_TOG RGB_TOG
    #define MG_RGB_RMOD RGB_RMOD
    #define MG_RGB_MOD RGB_MOD
#else
    #define MG_RGB_TOG KC_TRNS
    #define MG_RGB_RMOD KC_TRNS
    #define MG_RGB_MOD KC_TRNS
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT_60_iso( /* Base */
    KC_GESC,     KC_1,       KC_2,         KC_3,         KC_4,     KC_5,     KC_6,    KC_7,     KC_8,      KC_9,     KC_0,        KC_MINS,  KC_EQL,   KC_BSPC, \
    KC_TAB,      KC_Q,       KC_W,         KC_E,         KC_R,     KC_T,     KC_Y,    KC_U,     KC_I,      KC_O,     KC_P,        KC_LBRC,  KC_RBRC,           \
    MG_CAPS,     KC_A,       KC_S,         KC_D,         KC_F,     KC_G,     KC_H,    KC_J,     KC_K,      KC_L,     KC_SCLN,     KC_QUOT,  KC_NUHS,  KC_ENT,  \
    KC_LSFT,     KC_NUBS,    KC_Z,         KC_X,         KC_C,     KC_V,     KC_B,    KC_N,     KC_M,      KC_COMM,  KC_DOT,      KC_SLSH,            MG_UP,   \
    KC_LCTL,     KC_LGUI,    KC_LALT,                                        KC_SPC,                                 KC_RALT,     MG_LEFT,  MG_DOWN,  MG_RIGHT),

[_FUNC] = LAYOUT_60_iso( /* FN */
    KC_GRV,      KC_F1,      KC_F2,        KC_F3,        KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,      KC_F11,   KC_F12,   KC_DEL ,\
    KC_TRNS,     KC_TRNS,    KC_UP,        KC_TRNS,      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,     KC_TRNS,  KC_TRNS,          \
    KC_TRNS,     KC_LEFT,    KC_DOWN,      KC_RGHT,      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,     KC_TRNS,  KC_TRNS,  KC_TRNS,\
    KC_TRNS,     KC_TRNS,    KC_TRNS,      KC_TRNS,      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,     KC_TRNS,            KC_TRNS,\
    KC_TRNS,     KC_TRNS,    KC_TRNS,                                        KC_TRNS,                                KC_TRNS,     KC_TRNS,  KC_TRNS,  KC_TRNS),

[_CAPS] = LAYOUT_60_iso( /* CAPS */
    KC_TRNS,     KC_F1,      KC_F2,        KC_F3,        KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,      KC_F11,   KC_F12,   KC_DEL, \
    KC_TRNS,     KC_PGUP,    KC_HOME,      KC_END,       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_INS,   KC_MUTE,  KC_VOLD,     KC_VOLU,  KC_TRNS,          \
    KC_TRNS,     KC_PGDN,    KC_TRNS,      KC_TRNS,      KC_TRNS,  KC_TRNS,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_MPRV,     KC_MPLY,  KC_MNXT,  KC_TRNS,\
    KC_TRNS,     KC_TRNS,    KC_INS,       KC_TRNS,      KC_CALC,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,     KC_TRNS,            KC_UP,  \
    KC_TRNS,     KC_TRNS,    KC_TRNS,                                        KC_TRNS,                                KC_TRNS,     KC_LEFT,  KC_DOWN,  KC_RIGHT),

[_MENU] = LAYOUT_60_iso( /* MENU */
    KC_TRNS,     KC_TRNS,    KC_TRNS,      KC_TRNS,     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,     KC_TRNS,  KC_TRNS,  KC_TRNS,\
    KC_TRNS,     MG_RGB_TOG, MG_RGB_RMOD,  MG_RGB_MOD,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  EEP_RST,     KC_TRNS,  RESET,            \
    KC_TRNS,     KC_TRNS,    KC_TRNS,      KC_TRNS,     S1_DEC,   S1_INC,   S2_DEC,   S2_INC,   KC_TRNS,  KC_TRNS,  KC_TRNS,     KC_TRNS,  KC_TRNS,  KC_TRNS,\
    KC_TRNS,     KC_TRNS,    EF_DEC,       EF_INC,      H1_DEC,   H1_INC,   H2_DEC,   H2_INC,   BR_DEC,   BR_INC,   ES_DEC,      ES_INC,             KC_TRNS,\
    KC_TRNS,     KC_TRNS,    KC_TRNS,                                       KC_TRNS,                                KC_TRNS,     KC_TRNS,  KC_TRNS,  KC_TRNS),
};

void matrix_init_user(void) {
  //user initialization
}

void matrix_scan_user(void) {
  //user matrix
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

#ifdef RGBLIGHT_LAYERS
// https://docs.splitkb.com/hc/en-us/articles/360011243659-How-can-I-set-the-default-RGB-underglow-color-of-my-keyboard-

const rgblight_segment_t PROGMEM mg_capslock_active_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, MG_LAYER_CAPSLOCK_COLOR}
);

const rgblight_segment_t PROGMEM mg_func_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, MG_LAYER_1_COLOR}
);

const rgblight_segment_t PROGMEM mg_caps_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, MG_LAYER_2_COLOR}
);

const rgblight_segment_t PROGMEM mg_menu_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM, MG_LAYER_3_COLOR}
);

const rgblight_segment_t* const PROGMEM mg_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    mg_capslock_active_layer,
    mg_func_layer,
    mg_caps_layer,
    mg_menu_layer
);

void keyboard_post_init_user(void) {
    rgblight_layers = mg_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _FUNC));
    rgblight_set_layer_state(2, layer_state_cmp(state, _CAPS));
    rgblight_set_layer_state(3, layer_state_cmp(state, _MENU));
    return state;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(_BASE, led_state.caps_lock);
    return true;
}
#endif

