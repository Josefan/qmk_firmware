/* Copyright 2021 Josef Andersson
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
 * You should thave received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "analog.h"
#include "qmk_midi.h"
#include "print.h"

uint8_t midi2vol = 0x3E;
extern MidiDevice midi_device;

#ifdef AUDIO_ENABLE
  float base[][2]     = SONG(QWERTY_SOUND);
  float music[][2]  = SONG(PLANCK_SOUND);
  float numpad[][2]  = SONG(PREONIC_SOUND);
#endif

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _MUSIC,
    _NUMPAD
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    BASE = SAFE_RANGE,
    SPOTIFY,
    DISCORD
};
/*
 * ,-----------------------------|
 * | KC_ | KC_ | KC_ | KC_ | KC_ |
 * |-----+-----+-----+-----+-----|
 * |  |  | KC_ | KC_ | KC_ | KC_ |
 * |  |  +-----+-----+-----+-----|
 * |  |  | KC_ | KC_ | KC_ | KC_ |
 * | --- +-----+-----+-----+-----|
 * |  |  | KC_ | KC_ | KC_ |     |
 * |  |  +-----+-----+-----+ KC_ |
 * |  |  | KC_ | KC_ | KC_ |     |
 * |-----------------------------|
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
    KC_T,   KC_A,   KC_B,   KC_C,   SPOTIFY,\
            KC_E,   KC_F,   KC_G,   DISCORD,\
            KC_I,   KC_J,   KC_K,   DEBUG,\
            KC_M,   KC_N,   KC_O,\
            KC_P,   KC_Q,   KC_R,   RESET\

    ),
    [_MUSIC] = LAYOUT(
    KC_T,   KC_A,   KC_B,   KC_C,   SPOTIFY,\
            KC_MPLY,KC_MPRV,KC_MNXT,DISCORD,\
            KC_VOLU,KC_BRIU,KC_MUTE,DEBUG,\
            KC_VOLD,KC_BRID,KC_O,\
            KC_P,   KC_Q,   KC_R,   RESET\

    ),
    [_NUMPAD] = LAYOUT(
    KC_PENT,KC_NLCK, KC_PAST, KC_PSLS, KC_PMNS,\
            KC_P7,   KC_P8,   KC_P9,   KC_PMNS,\
            KC_P4,   KC_P5,   KC_P6,   KC_PPLS,\
            KC_P1,   KC_P2,   KC_P3,\
            KC_P0,   KC_P0,   KC_PDOT, KC_ENT\

    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case BASE:
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING("QMK is the best thing ever!");
            } else {
                // when keycode QMKBEST is released
            }
            break;
        case SPOTIFY:
            if (record->event.pressed) {
                // when keycode SPOTIFY is pressed
                midi2vol= 0x3F;
            } else {
                midi2vol= 0x3E;
                // when keycode SPOTIFY is released
            }
            break;
        case DISCORD:
            if (record->event.pressed) {
                // when keycode DISCORD is pressed
                midi2vol= 0x40;
            } else {
                midi2vol= 0x3E;
                // when keycode DISCORD is released
            }
            break;
    }
    #ifdef CONSOLE_ENABLE
        //uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    #endif
    return true;
}

uint16_t divisor =  60000;
void slider(void) {
    if (divisor++) { // only run the slider function 1/256 times it's called
        return;
    }
    divisor = 60000;
    //uint8_t volume = 127 - (analogReadPin(SLIDER_PIN) >> 3);
    //dprintf("%d \n",volume);
    //midi_send_cc(&midi_device, 0, midi2vol, 127 - volume);
}

void matrix_scan_user(void) {
    slider();
}

uint8_t current_layer_mask = 1;
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise && (current_layer_mask != 4)) {
            current_layer_mask = current_layer_mask << 1;
            layer_state_set(current_layer_mask);
        } else if (!clockwise && (current_layer_mask != 1)){
            current_layer_mask = current_layer_mask >> 1;
            layer_state_set(current_layer_mask);
        }
    }
    return true;
}

#ifdef AUDIO_ENABLE
layer_state_t layer_state_set_user(layer_state_t state) {
    dprintf("layer_mask %d \n",state);
    switch (get_highest_layer(state)) {
    case _BASE:
        PLAY_SONG(base);
        break;
    case _MUSIC:
        PLAY_SONG(music);
        break;
    case _NUMPAD:
        PLAY_SONG(numpad);
        if (!host_keyboard_led_state().num_lock) {
             tap_code16(KC_NLCK);
        }
        break;
    default: //  for any other layers, or the default layer
        break;
    }
  return state;
}
#endif


/*
votid matrix_init_user(void) {

}
*/
