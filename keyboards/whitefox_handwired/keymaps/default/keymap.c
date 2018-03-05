#include "kb.h"

#define _QWERTY 0
#define _ADJUST 1
#define _MOUSE 2

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  ADJUST,
  MOUSE,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO


//Tap Dance Declarations
enum {
  TD_ESC_CAPS = 0,
  CT_EGG = 1
};

void dance_egg(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 10) {
    SEND_STRING("Safety dance!");
    reset_tap_dance(state);
  }
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [CT_EGG] = ACTION_TAP_DANCE_FN(dance_egg),
  [TD_ESC_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_0, KC_1)
};

// make whitefox_handwired:default:teensy
const uint16_t PROGMEM keymaps[3][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = KEYMAP(
 /*|--------+--------+--------+--------+---------+--------+---------+---------+----------+---------+---------+---------+--------+--------+--------+--------+ */
    KC_GESC,   KC_1,    KC_2,    KC_3,    KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,    KC_MINS,   KC_EQL,  RESET,  KC_NO,  KC_BSPC,
 /*|--------+--------+--------+--------+---------+--------+---------+---------+----------+---------+---------+---------+--------+--------+--------+--------+ */
      KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,    KC_LBRC,   KC_RBRC,  KC_BSLS,     KC_GRV,
 /*|------------+--------+--------+--------+---------+--------+---------+---------+----------+---------+---------+---------+--------+-----------+----------+ */
    LT(2,KC_NO),   KC_A,    KC_S,    KC_D,    KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN, KC_QUOT,   KC_ENT,              TD(CT_EGG),
 /*|--------------+--------+--------+--------+---------+--------+---------+---------+----------+---------+---------+---------+------------------+----------+ */
      KC_LSFT,       KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,      KC_RSFT,         KC_UP,  TD(TD_ESC_CAPS),
 /*|------------------+--------+--------+--------+---------+--------+---------+---------+----------+---------+---------+---------------+----------+--------+ */
      KC_LCTL,   KC_LGUI,  KC_LALT,                      KC_SPC,                                LT(1, KC_NO), KC_NO,             KC_LEFT, KC_DOWN, KC_RGHT
 /*|----------+----------+----------+----------------------------------------------------------+-----------+----------+--------+--------+--------+--------+ */
  ),

 /*|esc-`-1--`-2--`-3--`-4--`-5--`-6--`-7--`-8--`-9--`-0--`mnus`plus`--bksp--|  |ins-`pgup| */
    [_ADJUST] = KEYMAP(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, RGB_TOG, RGB_SMOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, KC_VOLU, _______,
        _______, _______, _______, KC_MPLY, _______, _______, KC_MPRV, KC_VOLD, KC_MNXT
    ),

    [_MOUSE] = KEYMAP(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MS_UP, _______,
        _______, _______, _______, _______, _______, KC_MS_BTN1, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT
    )

};
/*
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) // this is the function signature -- just copy/paste it into your keymap file as it is.
{
  switch(id) {
    case 0: // this would trigger when you hit a key mapped as M(0)
      if (record->event.pressed) {
        SEND_STRING("none");
        #ifdef RGBLIGHT_ENABLE
            rgblight_setrgb(0xff,0x00,0xff);
        #endif
        return false; // This is false because it has to return something.
      }
      break;
    case 1:
      if (record->event.pressed) {
        SEND_STRING("My friend Louisa got straight A's all the way from kindergarten to her PhD. One day while we were out biking in Europe we ran into John Nash knife fighting with Sifu. I was busy fighting a student of mine with my Aikido, or else I would have hypnotized both John Nash and Sifu. I HATE A WHITE SAUCE.");
        return false;
      }
      break;
  }
  return MACRO_NONE;
};
*/

void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);
    switch (layer) {
        case _QWERTY:
           break;
        case _ADJUST:
            //SEND_STRING("Hello!");
            //rgblight_mode(1);
            //rgblight_setrgb(0x00,0xff,0x00);
            break;
    }
};
