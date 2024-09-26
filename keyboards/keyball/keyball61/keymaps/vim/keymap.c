/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/
*/

#include QMK_KEYBOARD_H

#include "quantum.h"
#include "qmk-vim/src/vim.h"
#include "qmk-vim/src/modes.h"


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Process case modes
    if (!process_vim_mode(keycode, record)) {
        return false;
    }

    // Regular user keycode case statement
    switch (keycode) {
        case PB_1:
            if (record->event.pressed) {
                toggle_vim_mode();
            }
            return false;
		case PB_2:
			if (record->event.pressed) {
	            if (get_vim_mode() == INSERT_MODE) {
			    	tap_code16(KC_SPC);
			    } else {
			    	tap_code16(KC_BTN1);
			    }
			}
		    return false;
		case KC_BTN1:
			if (record->event.pressed) {
	            if (get_vim_mode() == INSERT_MODE) {
			    	tap_code16(KC_SPC);
					return false;
			    } 
			}
		    return true;
        default:
            return true;
    }
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_universal(
    KC_ESC   , KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,                                  KC_6     , KC_7     , KC_8     , KC_9     , KC_0      , KC_BSPC  ,
    KC_TAB   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                  KC_Y     , KC_U     , KC_I     , KC_O     , KC_P      , KC_ENT  ,
    KC_BSLS   , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                  KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , KC_QUOT ,
    MO(1)    , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     , KC_LBRC  ,              KC_RBRC, KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH   , MO(1)    ,
    KC_LCTL  , KC_LCTL  , KC_LGUI  , KC_LALT   , KC_BTN1 ,LT(2,KC_SPC),LT(3,KC_BTN2)  ,           KC_BTN1  , LT(2,KC_SPC)   ,_______   ,_______   , _______  , KC_MINS  , KC_EQL
  ),


  [1] = LAYOUT_universal(
    KC_ESC   , S(KC_1)  , S(KC_2)  , S(KC_3)  , S(KC_4)  , S(KC_5)  ,                                  S(KC_6)  , S(KC_7)  ,S(KC_8), S(KC_9)  , S(KC_0)  ,KC_DEL,
    S(KC_TAB), S(KC_Q)  , S(KC_W)  , S(KC_E)  , S(KC_R)  , S(KC_T)  ,                                  S(KC_Y)  , S(KC_U)  , S(KC_I)  , S(KC_O)  , S(KC_P)  ,S(KC_ENT),
    S(KC_BSLS), S(KC_A)  , S(KC_S)  , S(KC_D)  , S(KC_F)  , S(KC_G)  ,                                  S(KC_H)  , S(KC_J)  , S(KC_K)  , S(KC_L) ,S(KC_SCLN),S(KC_QUOT),
    _______  , S(KC_Z)  , S(KC_X)  , S(KC_C)  , S(KC_V)  , S(KC_B)  ,S(KC_LBRC),           S(KC_RBRC), S(KC_N)  , S(KC_M)  ,S(KC_COMM), S(KC_DOT),S(KC_SLSH) , _______,
    PB_1     ,S(KC_LCTL), S(KC_INS),KC_PSCR  , LT(3,KC_BTN1)  , _______  , LT(3,KC_BTN3),        LT(3,KC_BTN1)  , LT(3,KC_BTN2)    , _______  ,S(KC_RGUI), _______  , S(KC_MINS), S(KC_EQL)
  ),

  [2] = LAYOUT_universal(
    KC_GRV , KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                                  KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
    SSNP_VRT , _______  , KC_UP     , RALT(KC_5)    , KC_9     , _______  ,                                  _______  , A(KC_UP)  , KC_UP    , KC_MINS  , KC_EQL  , KC_F12   ,
    SSNP_HOR , KC_LEFT  , KC_DOWN  , KC_RGHT     , SSNP_FRE   ,KC_VOLD   ,                                  KC_PGUP  , A(KC_DOWN)  , A(KC_UP)  , KC_BTN2  , KC_BTN3  , _______  ,
    KC_LSFT   , _______  , KC_1     , KC_2     , KC_3     ,S(KC_MINS), S(KC_8)  ,            S(KC_9)  , KC_PGDN  , KC_MUTE  , _______  , _______  , RALT(KC_S) , KC_RSFT     ,
    TG(2)    , KC_LCTL  , KC_LGUI  , KC_LALT    , A(KC_LEFT) , _______  , A(KC_RGHT)  ,             _______  , _______  , _______  , _______  , _______  , KC_VOLD  , KC_VOLU
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  , AML_TO   , KC_UP    , AML_D50  , AML_I50  , AML_TO   ,                                  RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN , RGB_M_K  ,
    RGB_MOD  , KC_LEFT  , KC_DOWN  , KC_RGHT  , _______  , _______  ,                                  RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , _______  , _______  ,                                  CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE , KBC_RST  ,
    _______  , _______  , SCRL_DVD , SCRL_DVI , SCRL_MO  , SCRL_TO  , EE_CLR   ,            EE_CLR   , KC_HOME  , KC_PGDN  , KC_PGUP  , KC_END   , _______  , _______  ,
    QK_BOOT  , _______  , KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT  , _______  ,            _______  , KC_BSPC  , _______  , _______  , _______  , _______  , QK_BOOT
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 2 or greater
    keyball_set_scroll_mode(get_highest_layer(state) > 1);
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
	if (vim_mode_enabled()) {
        switch (get_vim_mode()) {
            case NORMAL_MODE:
                oled_write_P(PSTR("-- NORMAL --\n"), false);
                break;
            case INSERT_MODE:
                oled_write_P(PSTR("-- INSERT --!!SPC!!\n"), false);
                break;
            case VISUAL_MODE:
                oled_write_P(PSTR("-- VISUAL --\n"), false);
                break;
            case VISUAL_LINE_MODE:
                oled_write_P(PSTR("-- V-LINE --\n"), false);
                break;
            default:
                oled_write_P(PSTR("-- ?????? --\n"), false);
                break;
        }
	} else {
		keyball_oled_render_keyinfo();
	}
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif
