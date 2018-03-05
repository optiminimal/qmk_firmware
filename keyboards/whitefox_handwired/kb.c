#include "kb.h"

void matrix_init_kb(void) {
    rgblight_mode(1);
    rgblight_setrgb(0x00,0xff,0x00);

	matrix_init_user();
}

