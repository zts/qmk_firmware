/*
 * Copyright 2022 Kevin Gee <info@controller.works>
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
// oled functions
#include "quantum.h"

// Left-hand home row mods
#define CTL_A LCTL_T(KC_A)
#define ALT_S LALT_T(KC_S)
#define GUI_D LGUI_T(KC_D)
#define SFT_F LSFT_T(KC_F)

// Right-hand home row mods
#define SFT_J RSFT_T(KC_J)
#define GUI_K RGUI_T(KC_K)
#define ALT_L LALT_T(KC_L)
#define CTL_SCLN RCTL_T(KC_SCLN)

// MacOS clipboard shortcuts
#define KC_UNDO LGUI(KC_Z)
#define KC_CUT LGUI(KC_X)
#define KC_COPY LGUI(KC_C)
#define KC_PASTE LGUI(KC_V)

enum layers {
    BASE,  // default layer
    LOWER, // lower layer
    RAISE, // raise layer
    ADJUST, // adjustments layer
    MOVE,  // cursor movement
	WNDW,  // window management
	SYMB,  // symbols
	NUMP,  // numpad
};

const char * const layers_as_strings[] = {
    [BASE] = "BASE",
    [LOWER] = "__ LoWer __",
    [RAISE] = "^^ Raise ^^",
    [ADJUST] = "> ADJust <",
    [MOVE] = "=> MoVe <=",
    [WNDW] = ":> Window <:",
    [SYMB] = "%% Symbol %%",
    [NUMP] = "Num Pad",
};

bool oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    int layer = get_highest_layer(layer_state);
    oled_write_ln_P(PSTR(layers_as_strings[layer]), false);

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);

    return false;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_split_3x5_3(
  //,--------------------------------------------.                    ,--------------------------------------------.
         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
        CTL_A,   ALT_S,   GUI_D,   SFT_F,    KC_G,                         KC_H,   SFT_J,   GUI_K,   ALT_L, CTL_SCLN,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
         KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                MO(MOVE),   MO(LOWER),  KC_BSPC,  KC_SPC, LT(SYMB, KC_ENT), LT(RAISE, KC_ESC)
                            //`--------------------------'  `--------------------------'

  ),

  [LOWER] = LAYOUT_split_3x5_3(
  //,--------------------------------------------.                    ,--------------------------------------------.
         KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
       KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_QUOT,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                 _______, _______,  KC_ESC,     KC_ENT,   MO(ADJUST), _______
                             //`--------------------------'  `--------------------------'
  ),

  [RAISE] = LAYOUT_split_3x5_3(
  //,--------------------------------------------.                    ,--------------------------------------------.
      KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                 _______,   MO(ADJUST),  KC_ESC,     KC_DEL, _______, _______
                             //`--------------------------'  `--------------------------'
  ),

  [ADJUST] = LAYOUT_split_3x5_3(
  //,--------------------------------------------.                    ,--------------------------------------------.
      QK_BOOT, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                 _______, _______, _______,    _______, _______, _______
                             //`--------------------------'  `--------------------------'
  ),

  [MOVE] = LAYOUT_split_3x5_3(
  //,--------------------------------------------.                    ,--------------------------------------------.
      _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, _______,                      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_UNDO, KC_CUT,  KC_COPY, KC_PASTE, _______,                     KC_END,  KC_PGDN, KC_PGUP, KC_HOME, _______,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                 _______, _______, _______,    _______, MO(WNDW), _______
                             //`--------------------------'  `--------------------------'
  ),

  [WNDW] = LAYOUT_split_3x5_3(
  //,--------------------------------------------.                    ,--------------------------------------------.
      _______, _______, _______, _______, _______,                      _______, KC_KP_7, _______, KC_KP_9, _______,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______,                      KC_KP_4, KC_KP_2, KC_KP_8, KC_KP_6, KC_KP_5,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______,                      _______, KC_KP_1, _______, KC_KP_3, _______,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                 _______, _______, _______,    _______, _______, _______
                             //`--------------------------'  `--------------------------'
  ),

  [SYMB] = LAYOUT_split_3x5_3(
  //,--------------------------------------------.                    ,--------------------------------------------.
      KC_TILD,  KC_GRV, KC_LCBR, KC_RCBR, KC_PERC,                      KC_CIRC, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_EQL,  KC_MINS, KC_LPRN, KC_RPRN, KC_PLUS,                      KC_DLR,  KC_EXLM, _______, _______, _______,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      _______, KC_UNDS, KC_LBRC, KC_RBRC, _______,                      _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                 _______, MO(NUMP), _______,    _______, _______, _______
                             //`--------------------------'  `--------------------------'
  ),

  [NUMP] = LAYOUT_split_3x5_3(
  //,--------------------------------------------.                    ,--------------------------------------------.
      _______, _______, _______, _______, _______,                      _______, KC_KP_7, KC_KP_8, KC_KP_9, _______,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, _______,                      _______, KC_KP_4, KC_KP_5, KC_KP_6, _______,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______,                      _______, KC_KP_1, KC_KP_2, KC_KP_3, _______,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                 _______, _______, _______,    _______, KC_KP_0, KC_PDOT
                             //`--------------------------'  `--------------------------'
  ),

};


//   [XXX] = LAYOUT_split_3x5_3(
//   //,--------------------------------------------.                    ,--------------------------------------------.
//       _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______,
//   //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
//       _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______,
//   //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
//       _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______,
//   //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
//                                  _______, _______, _______,    _______, _______, _______
//                              //`--------------------------'  `--------------------------'
//   ),
