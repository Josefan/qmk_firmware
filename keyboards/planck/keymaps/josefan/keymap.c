/* Copyright 2015-2021 Jack Humbert
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
#include "muse.h"
#include "keymap_swedish.h"

enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _GAMING,
  _ADJUST,
  _NUMPAD
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE
};

// Adds supprot for unicode characters
const uint32_t PROGMEM unicode_map[] = {
    0x00E5,  // å
    0x00C5,  // Å
    0x00E4,  // ä
    0x00C4,  // Ä
    0x00F6,  // ö
    0x00D6,  // Ö
    0x00B0   // °
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  Å   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Ctl/ESC|  A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Esc | LAlt  | GUI  | Space/Lower | Bksp/Raise  | ENT  |Gaming| Left | Right|
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_TAB,        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                       KC_Y,      KC_U,    KC_I,    KC_O,         KC_P,       SE_ARNG,
    LCTL_T(KC_ESC),KC_A   KC_S,    KC_D,    KC_F,    KC_G,                       KC_H,      KC_J,    KC_K,    KC_L,         KC_SCLN,    KC_QUOT,
    KC_LSFT,       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                       KC_N,      KC_M,    KC_COMM, KC_DOT,       KC_SLSH,    KC_DEL,
    TG(_NUMPAD),   KC_ESC,  KC_LALT, KC_LGUI, _______, LT(_LOWER, KC_SPC),_______, LT(_RAISE, KC_BSPC),KC_ENT,  TG(_GAMING),  KC_LEFT,    KC_RGHT
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |  ?   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |  F1  |  F2  |  F3  |  F4  |  F5  |  -   |   =  |      |   [  |   ]  |  `   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|  F6  |  F7  |  F8  |  F9  |  F10 |  F11 | F12  |      |      |   \  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |             |             | GUI  | RAlt | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_ESC,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR,  KC_LPRN, KC_RPRN, SE_QUES,
    KC_LCTL,KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_MINS, KC_EQL,  _______,  KC_LBRC, KC_RBRC, KC_GRV,
    KC_LSFT, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,  _______, KC_BSLS, KC_DEL,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_RGUI,  KC_RALT, KC_VOLU, KC_MPLY
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  å   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Mute | Prev | Next | Play | Vol+ | Left | Down |  Up  | Right|   ö  |  ä   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift| Bri- | Bri+ | PGDN | PGUP | Vol- | Home | End  |   ,  |   .  |      | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |             |             | GUI  | RAlt | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    XP(0,1),
    KC_LCTL,KC_MUTE, KC_MPRV, KC_MNXT, KC_MPLY, KC_VOLU, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XP(4,5), XP(2,3),
    KC_LSFT, KC_BRID, KC_BRIU, KC_PGDN, KC_PGUP, KC_VOLD, KC_HOME, KC_END,  KC_COMM, KC_DOT,  _______, KC_DEL,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_RGUI, KC_RALT, KC_VOLU, KC_MPLY
),

/* Gaming
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Esc | LAlt  | GUI  |    Space    | Enter/Adjust| GUI  |Gaming| Left | Right|
 * `-----------------------------------------------------------------------------------'
 */
[_GAMING] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                       KC_Y,      KC_U,    KC_I,        KC_O,    KC_P,    KC_BSPC,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                       KC_H,      KC_J,    KC_K,        KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                       KC_N,      KC_M,    KC_COMM,     KC_DOT,  KC_SLSH, KC_DEL,
    _______, KC_ESC,  KC_LALT, KC_LGUI, _______, KC_SPC,_______, LT(_ADJUST, KC_ENT), KC_RGUI,   TG(_GAMING), KC_LEFT, KC_RGHT
),

/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|      |      |Qwerty|      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |             |             |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
*/
[_ADJUST] = LAYOUT_planck_grid(
    _______, QK_BOOT, DB_TOGG, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, KC_DEL ,
    _______, _______, _______,  AU_ON,   AU_OFF,  _______, _______, QWERTY,  _______, _______, _______,  _______,
    _______, _______, _______,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* NUMPAD
 *
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |   /  |   7  |   8  |   9  |   -  | NumLK|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |   *  |   4  |   5  |   6  |   +  | Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |   0  |   1  |   2  |   3  |   ,  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |    Space    |    Bksp     | Enter|      |      |      |
 * `-----------------------------------------------------------------------------------'
*/
[_NUMPAD] = LAYOUT_planck_grid(
    _______,     _______, _______, _______, _______, _______, KC_PSLS, KC_P7, KC_P8, KC_P9, KC_PMNS, KC_NUM,
    _______,     _______, _______, _______, _______, _______, KC_PAST, KC_P4, KC_P5, KC_P6, KC_PPLS, KC_PENT,
    _______,     _______, _______, _______, _______, _______, KC_P0,   KC_P1, KC_P2, KC_P3, KC_PDOT, _______,
    TG(_NUMPAD), _______, _______, _______, _______, KC_SPC,  _______, KC_BSPC, KC_ENT, _______, _______, _______
)

/* LAYER
 *
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |             |             |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
[_LAYER] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)
*/

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;


bool encoder_update_user(uint8_t index, bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_DOWN);
      #else
        tap_code(KC_DOWN);
      #endif
    } else {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_UP);
      #else
        tap_code(KC_UP);
      #endif
    }
  }
    return false;
}

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
#ifdef AUDIO_ENABLE
            static bool play_sound = false;
#endif
            if (active) {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_song); }
#endif
                layer_on(_LOWER);
            } else {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_gb_song); }
#endif
                layer_off(_RAISE);
            }
#ifdef AUDIO_ENABLE
            play_sound = true;
#endif
            break;
        }
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
    return true;
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
