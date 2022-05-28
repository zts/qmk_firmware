/* Copyright 2020 ZSA Technology Labs, Inc <@zsa>
 * Copyright 2020 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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
#include "version.h"
#include "keycode.h"
#include "quantum_keycodes.h"
#include "color.h"

enum layers {
    BASE,  // default layer
    MOVE,  // cursor movement
    MDIA,  // media keys
	WNDW,  // window management
	SYMB,  // symbols
	NUMP,  // numpad
};

enum custom_keycodes {
    VRSN = ML_SAFE_RANGE,
};

#define KC_UNDO LGUI(KC_Z)
#define KC_CUT LGUI(KC_X)
#define KC_COPY LGUI(KC_C)
#define KC_PASTE LGUI(KC_V)

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

// Hyper Escape
#define HYP_ESC ALL_T(KC_ESCAPE)

// Media layer shortcuts
#define SS_FSEL  LGUI(LSFT(KC_4)) // Grab region to file
#define SS_CSEL  LGUI(LCTL(LSFT(KC_4))) // Grab region to clipboard
#define SS_OPTS  LGUI(LSFT(KC_5)) // Grab with options
#define MAC_LOCK LGUI(LCTL(KC_Q)) // Lock screen

// Movement layer shortcuts
#define MAC_PREV LGUI(KC_LBRC) // back / previous
#define MAC_NEXT LGUI(KC_RBRC) // forward / next

// Window mgmt layer shortcuts
#define WM_PSPC LCTL(KC_LEFT)  // previous space
#define WM_NSPC LCTL(KC_RIGHT) // next space

// helpful defines from drashna/wrappers.h
#define _________________QWERTY_L1_________________       KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _________________QWERTY_L2_________________       KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define _________________QWERTY_L3_________________       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________QWERTY_R1_________________       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _________________QWERTY_R2_________________       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT
#define _________________QWERTY_R3_________________       KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH

#define ________________NUMBER_LEFT________________       KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define ________________NUMBER_RIGHT_______________       KC_6,    KC_7,    KC_8,    KC_9,    KC_0
#define _________________FUNC_LEFT_________________       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define _________________FUNC_RIGHT________________       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10

#define ___________________BLANK___________________       _______, _______, _______, _______, _______

// END defines from drashna/wrappers.h


// LAYOUT
//
// This trick allows vscode to recognise the core keycodes
#define LAYOUT_moonlander_wrapper(...) LAYOUT_moonlander(__VA_ARGS__)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[BASE] = LAYOUT_moonlander_wrapper(
		KC_GRV,  ________________NUMBER_LEFT________________, KC_MINS,         KC_EQL,  ________________NUMBER_RIGHT_______________, KC_MINUS,
		KC_TAB,  _________________QWERTY_L1_________________, KC_LBRC,         KC_RBRC, _________________QWERTY_R1_________________, KC_BSLASH,
		HYP_ESC, CTL_A,   ALT_S,   GUI_D,   SFT_F,   KC_G,    _______,         _______, KC_H,   SFT_J,   GUI_K,   ALT_L,   CTL_SCLN, KC_QUOTE,
		KC_LSFT, _________________QWERTY_L3_________________,                           _________________QWERTY_R3_________________, KC_RSHIFT,
		KC_LCTL, KC_LALT, KC_LGUI, _______, MO(MOVE),       _______,              _______,      MO(SYMB), _______, KC_RGUI, KC_RALT, KC_RCTRL,
												KC_BSPC,MO(NUMP),MO(MDIA),  MO(WNDW),KC_ENT,KC_SPC
	),
	[MOVE] = LAYOUT_moonlander_wrapper(
		TO(BASE),_______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______,         _______, _______, MAC_PREV,MAC_NEXT,_______, _______, _______,
		_______, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, _______, _______,         _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
		_______, KC_UNDO, KC_CUT,  KC_COPY, KC_PASTE,_______,                           KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,
		_______, _______, _______, _______, _______,        _______,              _______,       _______, _______, _______, _______, _______,
												_______, _______, _______,   _______, _______, _______
	),
	[MDIA] = LAYOUT_moonlander_wrapper(
		TO(BASE),_______, _______, _______, _______, _______, _______,         KC_MUTE, _______, _______, _______, _______, _______, RESET,
		DT_PRNT, DT_DOWN, DT_UP,   _______, _______, _______, _______,         KC_VOLU, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______,         KC_VOLD, _______, _______, _______, RGB_MOD, RGB_TOG, _______,
		_______, _______, _______, _______, _______, _______,                           _______, _______, RGB_HUD, RGB_VAD, RGB_VAI, RGB_HUI,
		SS_FSEL, _______, SS_CSEL, _______, SS_OPTS,        MAC_LOCK,            _______,        KC_MPLY, KC_MPRV, _______, _______, KC_MNXT,
												_______, _______, _______,   _______, _______, _______
	),
	[WNDW] = LAYOUT_moonlander_wrapper(
		_______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______,      _______,                  _______,     _______, _______, _______, _______, _______,
												_______, _______, _______,   _______, _______, _______
	),
	[SYMB] = LAYOUT_moonlander_wrapper(
		_______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
		_______, KC_TILD, KC_GRV,  KC_LCBR, KC_RCBR, KC_PERC, _______,         _______, KC_CIRC, _______, _______, _______, _______, _______,
		_______, KC_EQL,  KC_MINS, KC_LPRN, KC_RPRN, KC_PLUS, _______,         _______, KC_DLR,  KC_EXLM, _______, _______, KC_COLN, _______,
		_______, _______, KC_UNDS, KC_LBRC, KC_RBRC, _______,                           _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______,      _______,                  _______,     _______, _______, _______, _______, _______,
												_______, _______, _______,   _______, _______, _______
	),
	[NUMP] = LAYOUT_moonlander_wrapper(
		_______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, KC_EQL,  KC_PSLS, KC_PAST, _______,
		_______, _______, _______, _______, _______, _______, _______,         _______, _______, KC_KP_7, KC_KP_8, KC_KP_9, KC_PMNS, _______,
		_______, _______, _______, _______, _______, _______, _______,         _______, _______, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS, _______,
		_______, _______, _______, _______, _______, _______,                           _______, KC_KP_1, KC_KP_2, KC_KP_3, KC_PENT, _______,
		_______, _______, _______, _______, _______,      _______,                  _______,     KC_KP_0, KC_BSPC, KC_PDOT, _______, _______,
												_______, _______, _______,   _______, _______, _______
	),
};

	// [template] = LAYOUT_moonlander_wrapper(
	// 	_______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
	// 	_______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
	// 	_______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
	// 	_______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
	// 	_______, _______, _______, _______, _______,      _______,                  _______,     _______, _______, _______, _______, _______,
	// 											_______, _______, _______,   _______, _______, _______
	// ),

extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

#define ___off___ {HSV_OFF}
#define H_BLUE {HSV_BLUE}
#define H_RED {HSV_RED}
#define H_GREEN {HSV_GREEN}
#define H_PURPLE {HSV_PURPLE}
#define H_GOLD {HSV_GOLD}
#define H_ORANGE {HSV_ORANGE}
#define BLANK_LAYER { \
	___off___, ___off___, ___off___, ___off___, ___off___, ___off___, ___off___,         ___off___, ___off___, ___off___, ___off___, ___off___, ___off___, ___off___, \
	___off___, ___off___, ___off___, ___off___, ___off___, ___off___, ___off___,         ___off___, ___off___, ___off___, ___off___, ___off___, ___off___, ___off___, \
	___off___, ___off___, ___off___, ___off___, ___off___, ___off___, ___off___,         ___off___, ___off___, ___off___, ___off___, ___off___, ___off___, ___off___, \
	___off___, ___off___, ___off___, ___off___, ___off___, ___off___,                               ___off___, ___off___, ___off___, ___off___, ___off___, ___off___, \
	___off___, ___off___, ___off___, ___off___, ___off___,      ___off___,                  ___off___,         ___off___, ___off___, ___off___, ___off___, ___off___, \
												   ___off___, ___off___, ___off___,   ___off___, ___off___, ___off___ \
}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [BASE] - BLANK_LAYER,
    [MOVE] - BLANK_LAYER,
    [MDIA] - BLANK_LAYER,
	[WNDW] - BLANK_LAYER,
	[SYMB] - BLANK_LAYER,
	[NUMP] - BLANK_LAYER,
};

// Note: Needs rotation - driver led numbering runs top to bottom, then left to right.
//  [x] = {
//  	___off___, ___off___, ___off___, ___off___, ___off___, ___off___, ___off___,         ___off___, ___off___, ___off___, ___off___, ___off___, ___off___, ___off___,
//  	___off___, ___off___, ___off___, ___off___, ___off___, ___off___, ___off___,         ___off___, ___off___, ___off___, ___off___, ___off___, ___off___, ___off___,
//  	___off___, ___off___, ___off___, ___off___, ___off___, ___off___, ___off___,         ___off___, ___off___, ___off___, ___off___, ___off___, ___off___, ___off___,
//  	___off___, ___off___, ___off___, ___off___, ___off___, ___off___,                               ___off___, ___off___, ___off___, ___off___, ___off___, ___off___,
//  	___off___, ___off___, ___off___, ___off___, ___off___,      ___off___,                  ___off___,         ___off___, ___off___, ___off___, ___off___, ___off___,
//												       ___off___, ___off___, ___off___,   ___off___, ___off___, ___off___,
//  }

void set_layer_color(int layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

void rgb_matrix_indicators_user(void) {
  if (keyboard_config.disable_layer_led) { return; }
  switch (biton32(layer_state)) {
    case 0:
      set_layer_color(0);
      break;
    case 1:
      set_layer_color(1);
      break;
    case 2:
      set_layer_color(2);
      break;
    case 3:
      set_layer_color(3);
      break;
    case 4:
      set_layer_color(4);
      break;
    case 5:
      set_layer_color(5);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
        case VRSN:
            SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
            return false;
        }
    }
    return true;
}
