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

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)

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


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[BASE] = LAYOUT_moonlander(
    	KC_GRAVE,	KC_1,		KC_2,		KC_3,       KC_4,       KC_5,		KC_MINUS,			KC_EQUAL,	KC_6,		KC_7,       KC_8,		KC_9,		KC_0,    	KC_MINUS,       
    	KC_TAB,		KC_Q,    	KC_W,       KC_E,       KC_R,       KC_T,       KC_LBRC,        	KC_RBRC,	KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,    	KC_BSLASH,      
		ALL_T(KC_ESCAPE),CTL_A, ALT_S,      GUI_D,      SFT_F,      KC_G,       _______,            _______,	KC_H,       SFT_J,      GUI_K,      ALT_L,      CTL_SCLN,	KC_QUOTE,       
		KC_LSHIFT,	KC_Z,    	KC_X,       KC_C,       KC_V,       KC_B,                                       KC_N,       KC_M,       KC_COMMA,   KC_DOT,     KC_SLASH,	KC_RSHIFT,      
		KC_LCTRL,	KC_LALT, 	KC_LGUI,    _______,	MO(MOVE),   _______,                                    _______,    MO(SYMB),	_______,	KC_RGUI,    KC_RALT, 	KC_RCTRL,       
                                            			KC_BSPACE,  MO(NUMP),   MO(MDIA),          	MO(WNDW),  	KC_ENTER,   KC_SPACE
	),
	[MOVE] = LAYOUT_moonlander(
		TO(BASE),          _______, _______, _______, _______, _______, _______,                                 _______, _______, _______, _______, _______, _______, _______, 
		_______, _______, _______, _______, _______, _______, _______,                                 _______, LCTL(KC_LEFT),  LGUI(KC_LBRACKET),LGUI(KC_RBRACKET),RCTL(KC_RIGHT), _______, _______, 
		_______, KC_LCTRL,       KC_LALT,        KC_LGUI,        KC_LSHIFT,      _______, _______,                                                                 _______, KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,       _______, _______, 
		_______, KC_MAC_UNDO,    KC_MAC_CUT,     KC_MAC_COPY,    KC_MAC_PASTE,   _______,                                 KC_HOME,        KC_PGDOWN,      KC_PGUP,        KC_END,         _______, _______, 
		_______, _______, _______, _______, _______, _______,                                                                                                 _______, _______, _______, _______, _______, _______, 
		_______, _______, _______,                 _______, _______, _______
	),
	[MDIA] = LAYOUT_moonlander(
		TO(BASE),          _______, _______, _______, _______, _______, _______,                                 KC_AUDIO_MUTE,  _______, _______, _______, _______, WEBUSB_PAIR,    RESET,          
		_______, _______, _______, _______, _______, _______, _______,                                 KC_AUDIO_VOL_UP,_______, _______, _______, _______, _______, _______, 
		_______, _______, _______, _______, _______, _______, _______,                                                                 KC_AUDIO_VOL_DOWN,_______, _______, _______, RGB_MOD,        RGB_TOG,        _______, 
		_______, _______, _______, _______, _______, _______,                                 _______, _______, RGB_HUD,        RGB_VAD,        RGB_VAI,        RGB_HUI,        
		LGUI(LSFT(KC_4)),_______, LGUI(LCTL(LSFT(KC_4))),_______, LGUI(LSFT(KC_5)),LGUI(LCTL(KC_Q)),                                                                                                _______, KC_MEDIA_PLAY_PAUSE,KC_MEDIA_PREV_TRACK,KC_BRIGHTNESS_DOWN,KC_BRIGHTNESS_UP,KC_MEDIA_NEXT_TRACK,
		_______, _______, _______,                 _______, _______, _______
	),
	[WNDW] = LAYOUT_moonlander(
		_______, _______, _______, _______, _______, _______, _______,                                 _______, _______, _______, _______, _______, _______, _______, 
		_______, _______, _______, LALT(LGUI(LCTL(LSFT(KC_UP)))),_______, _______, _______,                                 _______, _______, _______, _______, _______, _______, _______, 
		_______, _______, LALT(LGUI(LCTL(LSFT(KC_LEFT)))),LALT(LCTL(KC_C)),LALT(LGUI(LCTL(LSFT(KC_RIGHT)))),LALT(LGUI(LCTL(KC_RIGHT))),_______,                                                                 _______, _______, _______, _______, _______, _______, _______, 
		_______, _______, _______, LALT(LGUI(LCTL(LSFT(KC_DOWN)))),_______, _______,                                 _______, _______, _______, _______, _______, _______, 
		_______, _______, _______, _______, _______, _______,                                                                                                 _______, _______, _______, _______, _______, _______, 
		_______, _______, _______,                 _______, _______, _______
	),
	[SYMB] = LAYOUT_moonlander(
		_______, _______, _______, _______, _______, _______, _______,                                 _______, _______, _______, _______, _______, _______, _______, 
		_______, KC_TILD,        KC_GRAVE,       KC_LCBR,        KC_RCBR,        KC_PERC,        _______,                                 _______, KC_CIRC,        _______, _______, _______, _______, _______, 
		_______, KC_EQUAL,       KC_MINUS,       KC_LPRN,        KC_RPRN,        KC_PLUS,        _______,                                                                 _______, KC_DLR,         KC_EXLM,        _______, _______, KC_COLN,        _______, 
		_______, _______, KC_UNDS,        KC_LBRACKET,    KC_RBRACKET,    _______,                                 _______, _______, _______, _______, _______, _______, 
		_______, _______, _______, _______, _______, _______,                                                                                                 _______, _______, _______, _______, _______, _______, 
		_______, _______, _______,                 _______, _______, _______
	),
	[NUMP] = LAYOUT_moonlander(
		_______, _______, _______, _______, _______, _______, _______,                                 _______, _______, _______, KC_EQUAL,       KC_KP_SLASH,    KC_KP_ASTERISK, _______, 
		_______, _______, _______, _______, _______, _______, _______,                                 _______, _______, KC_KP_7,        KC_KP_8,        KC_KP_9,        KC_KP_MINUS,    _______, 
		_______, _______, _______, _______, _______, _______, _______,                                                                 _______, _______, KC_KP_4,        KC_KP_5,        KC_KP_6,        KC_KP_PLUS,     _______, 
		_______, _______, _______, _______, _______, _______,                                 _______, KC_KP_1,        KC_KP_2,        KC_KP_3,        KC_KP_ENTER,    _______, 
		_______, _______, _______, _______, _______, _______,                                                                                                 _______, KC_KP_0,        KC_BSPACE,      KC_KP_DOT,      _______, _______, 
		_______, _______, _______,                 _______, _______, _______
	),
};

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
