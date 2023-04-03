#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _FN1,
    _FN2
};

#define CTL_DEL  CTL_T(KC_DEL)
#define FN1 MO(_FN1)
#define FN2 MO(_FN2)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_LSFT, KC_LCTL, KC_LALT, KC_P, KC_E,
        KC_LSFT, C(KC_Z), KC_V,    KC_A, KC_Q,
        CTL_DEL, KC_F5,   KC_F6,   KC_F7,
                 FN1,     FN2
    ),

    [_FN1] = LAYOUT(
        QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS, KC_TRNS,
        KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT,
                 KC_TRNS, KC_TRNS
    ),

    [_FN2] = LAYOUT(
        KC_TRNS, KC_INS,  KC_HOME, KC_PGUP, KC_TRNS,
        KC_TRNS, KC_DEL,  KC_END,  KC_PGDN, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS
    ),
};
