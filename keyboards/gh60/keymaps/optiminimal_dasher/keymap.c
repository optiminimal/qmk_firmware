#include "gh60.h"
#include "action_layer.h"

extern keymap_config_t keymap_config;

#define _QW 0
#define _FL 1

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Used for SHIFT_ESC
#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     *  _QW: Qwerty Layer
     * ,-----------------------------------------------------------.
     * |ESC | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =| Backsp|
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|
     * |-----------------------------------------------------------|
     * |Ctrl   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '| Return|
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|     Shift|
     * |-----------------------------------------------------------|
     * |Ctrl|Alt |Gui |      Space             |Gui |Alt |Ctrl|  Fn|
     * `-----------------------------------------------------------'
     */
[_QW] = { /* Layer 0: Qwerty */
    {F(0),    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC},
    {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS},
    {KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, XXXXXXX, KC_ENT },
    {KC_LSFT, XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, XXXXXXX, MO(_FL)},
    {KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX, XXXXXXX, KC_SPC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RGUI, KC_RALT, KC_RCTL, MO(_FL)}
  },
    /*
     *  _FL: Function Layer
     * ,-----------------------------------------------------------.
     * |    |F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|    Del|
     * |-----------------------------------------------------------|
     * |     |   |   |   |   |   |   |PgU| Up|PgD|PSc|SLk|Pau|     |
     * |-----------------------------------------------------------|
     * |       |   |MPr|MPl|MNx|   |Hom| Lt| Dn| Rt|   |   |       |
     * |-----------------------------------------------------------|
     * |CAPS    |   |Mut|VlD|VlU|   |End|   |   |   |   |          |
     * |-----------------------------------------------------------|
     * |_QW |    |    |                        |    |    |    |    |
     * `-----------------------------------------------------------'
     */
[_FL] = { /* Layer 3: Functions */
    {KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL },
    {_______, _______, KC_VOLU, _______, _______, _______, _______, _______, _______, _______, KC_UP,   _______, _______, RESET  },
    {_______, KC_MPRV, KC_VOLD, KC_MNXT, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, _______},
    {KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, _______},
    {_______, _______, _______, XXXXXXX, XXXXXXX, KC_MPLY, XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______, _______}
  }

};

enum function_id {
    SHIFT_ESC,
};

const uint16_t PROGMEM fn_actions[] = {
  [0]  = ACTION_FUNCTION(SHIFT_ESC),
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  static uint8_t shift_esc_shift_mask;
  switch (id) {
    case SHIFT_ESC:
      shift_esc_shift_mask = get_mods()&MODS_CTRL_MASK;
      if (record->event.pressed) {
        if (shift_esc_shift_mask) {
          add_key(KC_GRV);
          send_keyboard_report();
        } else {
          add_key(KC_ESC);
          send_keyboard_report();
        }
      } else {
        if (shift_esc_shift_mask) {
          del_key(KC_GRV);
          send_keyboard_report();
        } else {
          del_key(KC_ESC);
          send_keyboard_report();
        }
      }
      break;
  }
}
