#include "dz60.h"
#include "keymap_german.h"

#define _DEFAULT 0
#define _FN 1
#define _AUX 2

#define ____ KC_TRNS
#define XXXX KC_NO
#define X__X KC_NUBS
#define USB_LED_BL 5

#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

// MO(2) MO(1)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty gui/alt/space/alt/guiISO 7u layout layer 0
* ,-----------------------------------------------------------------------------------------.
* | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  ß  |  ´  |   BSPC    |
* |-----------------------------------------------------------------------------------------+
* | Tab    |  Q  |  W  |  E  |  R  |  T  |  Z  |  U  |  I  |  O  |  P  |  P  |  Ü  | *  |   |
* |-------------------------------------------------------------------------------------|   +
* | LCtrl   |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  Ö  |  Ä |  # |Enter    |
* |-----------------------------------------------------------------------------------------+
* | Shift|  < |  Y  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  .  | RShift    | FN  |
* |-----------------------------------------------------------------------------------------+
* |LAlt |      | LGUI   |              Space                       | RGUI   |       | RAlt  |
* `-----'      '------------------------------------------------------------'       '-------'
*/
/*

åß∂ƒ©˙∆åß∂ƒ≈ç√\\dsf
*/
  [_DEFAULT] = 	KEYMAP(
    KC_ESC,  KC_1,  KC_2,  KC_3,  KC_4,  KC_5,  KC_6,  KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, XXXX, KC_BSPC,
    KC_TAB,   KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,  KC_Y,  KC_U, KC_I, KC_O,	KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
    KC_LCTRL,  KC_A,  KC_S,  KC_D,  KC_F,  KC_G,  KC_H,  KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
    KC_LSFT, X__X, KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  KC_N, KC_M, KC_COMM, 	KC_DOT, KC_SLSH, KC_RSFT, MO(_FN),
    KC_LALT,  XXXX,  KC_LGUI,   XXXX, KC_SPC,   XXXX,     XXXX,  KC_RGUI,  XXXX, XXXX, KC_RALT
  ),

  [_FN] = 	KEYMAP(
    ____,   KC_F1,    KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7, KC_F8, KC_F9, KC_F10, 	KC_F12, XXXX, XXXX, RESET,
    ____,   RGB_TOG, RGB_SMOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, XXXX,	XXXX, KC_UP, XXXX, KC_RIGHT,
    ____,      BL_DEC, BL_TOGG, BL_INC, BL_STEP,  ____,  ____,  ____, ____, ____, KC_LEFT, KC_DOWN, KC_ENT,
    ____, ____, KC_MPRV, KC_MPLY, KC_MNXT, ____, ____, ____, ____, ____, ____, ____, ____, ____,
    KC_LALT,    XXXX,  KC_LGUI,   XXXX, KC_MPLY,   XXXX,     XXXX,  MO(_AUX),  XXXX, XXXX, KC_RALT
  ),


  [_AUX] = 	KEYMAP(
    ____,   XXXX,    XXXX,  XXXX,  XXXX,  XXXX,  XXXX,  XXXX, XXXX, XXXX, XXXX, 	XXXX, XXXX, XXXX, RESET,
    ____,   RGB_TOG, RGB_SMOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, XXXX,	XXXX, KC_VOLU, XXXX, KC_MNXT,
    ____,      BL_DEC, BL_TOGG, BL_INC, BL_STEP,  ____,  ____,  ____, ____, ____, KC_MPRV, KC_VOLD, KC_ENT,
    ____, ____, KC_MPRV, KC_MPLY, KC_MNXT, ____, ____, ____, ____, ____, ____, ____, ____, ____,
    KC_LALT,    XXXX,  KC_LGUI,   XXXX, KC_MPLY,   XXXX,     XXXX,  KC_RGUI,  XXXX, XXXX, KC_RALT
  ),

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

void matrix_init_user(void) {
  // * Set our LED pins as output
  DDRB |= (1<<2);
#ifdef BACKLIGHT_CAPS
  // register the required ISRs
  TIMSK1 |= _BV(OCIE1B) | _BV(TOIE1);
#endif
}

void led_set_user(uint8_t usb_led) {
    if ((usb_led & (1 << USB_LED_BL)) || (layer_state == 2)) {
        // Turn capslock on
        PORTB &= ~(1<<2);
    } else {
        // Turn capslock off
        PORTB |= (1<<2);
    }
}

#ifdef BACKLIGHT_CAPS
  ISR(TIMER1_COMPB_vect) {
    led_set_user(~(1 << USB_LED_BL));
  }

  ISR(TIMER1_OVF_vect) {
    if (OCR1B != 0) {
      led_set_user(1 << USB_LED_BL);
    }
  }
#endif
