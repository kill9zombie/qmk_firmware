/* Copyright 2015-2017 Jack Humbert
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

#include "preonic.h"
#include "action_layer.h"

enum custom_keycodes {
    M_LAYER1 = SAFE_RANGE
    M_LAYER2
    M_CAPS
    TMUX_1
    TMUX_2
    TMUX_3
    TMUX_4
    TMUX_5
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// To keep track of the state of caps lock
bool capslock_enabled;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


/* Dvorak base layer
 * ,-----------------------------------------------------------------------------------.
 * |   [  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   ]  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  |  /   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  -   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Layer1|   `  | Alt  | Del  | Esc  |    Space    |Enter |Bksp  |   \  |   =  |Layer2|
 * `-----------------------------------------------------------------------------------'
 *
 * Mod Tap keys:
 *
 * [ - CTRL + shift when held, [ when tapped
 * ` - Left GUI when held, ` when tapped
 * \ - CTRL when held, \ when tapped
 *
 */
[0] = {
  {MT(MOD_LCTL | MOD_LSFT, KC_LBRC),  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_RBRC},
  {KC_TAB,   KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH},
  {KC_CTRL,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS},
  {KC_LSFT,  KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT },
  {M_LAYER1, GUI_T(KC_GRV),  KC_LALT, KC_DEL,  KC_ESC,  KC_SPC,  KC_SPC,  KC_ENT,  KC_BSPC, CTL_T(KC_BSLS), KC_EQL,   M_LAYER2}
},

/* Right hand layer 1
 * ,-----------------------------------------------------------------------------------.
 * |   `  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | CAPS |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |      |      |      |      |      |      |      |  up  |      |      |  /   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl |      |      |      |      |      |      | left | down | right|      |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|      |      |      |      |  x   |      |      |      |      |      | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Layer1| GUI  | Alt  | Del  | Esc  |    Space    |Enter |Bksp  |      |      |Layer2|
 * `-----------------------------------------------------------------------------------'
 *
 *
 */
[1] = {
  {KC_GRV,  KC_F1,   KC_F2,    KC_F3,   KC_F4,    KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  M_CAPS},
  {_______, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX,  XXXXXXX, _______},
  {_______, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, KC_PIPE},
  {_______, XXXXXXX, XXXXXXX,  XXXXXXX, _______,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, _______},
  {_______, KC_LGUI, _______,  _______, _______,  _______, _______, _______, _______, XXXXXXX,  XXXXXXX, _______}
},

/* Left hand layer 2
 * ,-----------------------------------------------------------------------------------.
 * |      |tmux 1|tmux 2|tmux 3|tmux 4|tmux 5|      |      |m acc1|m acc2|m acc0|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |      |      | m up |      |      |      |      |      |      |      |RESET |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl |      |m left|m down|m righ|scrl u|      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|      |      |      |      |scrl d|      |      |      |      |      |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Layer1| GUI  | Alt  |PRTSC | Esc  |    m left   |m righ|Bksp  | ALT  |      |Layer2|
 * `-----------------------------------------------------------------------------------'
 *
 *
 */
[2] = {
  {XXXXXXX, TMUX_1,  TMUX_2,  TMUX_3,  TMUX_4,  TMUX_5,  XXXXXXX, XXXXXXX, KC_ACL1, KC_ACL2, KC_ACL0, XXXXXXX},
  {_______, XXXXXXX, XXXXXXX, KC_MS_U, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET},
  {_______, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX},
  {_______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_WH_D, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX},
  {_______, KC_LGUI, _______, KC_PSCR, _______, KC_BTN1, KC_BTN1, KC_BTN2, _______, _______, XXXXXXX, _______}
}


};


void matrix_init_user(void) {
  capslock_enabled = false;
}


/*
 * MACROS:
 *
 * M_LAYER1 - set backlight level 1 and momentary layer 1
 * M_LAYER2 - set backlight level 2 and momentary layer 2
 *
 * M_CAPS - set backlight level 3 and enable caps lock
 *
 * TMUX_1 - send CTRL+B 1
 * TMUX_2 - send CTRL+B 2
 * TMUX_3
 * TMUX_4
 * TMUX_5
 *
 */


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case M_LAYER1:
      if (record->event.pressed) {
        #ifdef BACKLIGHT_ENABLE
          backlight_set(1);
        #endif
        layer_on(1);
        // update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef BACKLIGHT_ENABLE
          backlight_set(0);
        #endif
        layer_off(1);
        // update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case M_LAYER2:
      if (record->event.pressed) {
        #ifdef BACKLIGHT_ENABLE
          backlight_set(2);
        #endif
        layer_on(2);
        // update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef BACKLIGHT_ENABLE
          backlight_set(0);
        #endif
        layer_off(2);
        // update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case M_CAPS:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_LCAP));
        capslock_enabled = !capslock_enabled;
        #ifdef BACKLIGHT_ENABLE
          if (capslock_enabled) {
            backlight_set(3);
          } else {
            backlight_set(0);
          }
        #endif
      }
      return false;
      break;
    case TMUX_1:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("b")"1");
      }
      return false;
      break;
    case TMUX_2:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("b")"2");
      }
      return false;
      break;
    case TMUX_3:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("b")"3");
      }
      return false;
      break;
    case TMUX_4:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("b")"4");
      }
      return false;
      break;
    case TMUX_5:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("b")"5");
      }
      return false;
      break;
    }
    return true;
};
