#include "macrokrs.h"
#include "joy_input.h"

#define CTL_DEL  CTL_T(KC_DEL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	LAYOUT(
		KC_LSFT, KC_LCTL, KC_LALT, KC_P, KC_E, 
		KC_LSFT, LCTL(KC_Z), KC_V, KC_A, KC_Q, 
		CTL_DEL, KC_F5, KC_F6, KC_F7, 
		         MO(1), MO(2)),

	LAYOUT(
		QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, 
		KC_TRNS, KC_TRNS),

	LAYOUT(
		KC_TRNS, KC_INS, KC_HOME, KC_PGUP, KC_TRNS, 
		KC_TRNS, KC_DEL, KC_END, KC_PGDN, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS),

	LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS),

};


void pointing_device_driver_init(void) {
	joy_input_init();
}
report_mouse_t pointing_device_driver_get_report(report_mouse_t mouse_report) { 
	report_joy_t data = joy_input_read();
	mouse_report.x = data.x2;
	mouse_report.y = data.y2;

	//-- start mouse middle click and drag --
    if(data.x2 == 0 && data.y2 == 0)
        mouse_report.buttons = pointing_device_handle_buttons(mouse_report.buttons, false, POINTING_DEVICE_BUTTON3);
    else
        mouse_report.buttons = pointing_device_handle_buttons(mouse_report.buttons, true, POINTING_DEVICE_BUTTON3);
    //-- end mouse middle click and drag --

	joy_state.dir = joy_input_direction(data);

	joy_update_keycode(KC_PMNS, joy_state.lastDir.up, joy_state.dir.up);
	joy_update_keycode(KC_PPLS, joy_state.lastDir.down, joy_state.dir.down);
    joy_update_keycode(KC_P4, joy_state.lastDir.left, joy_state.dir.left);
    joy_update_keycode(KC_P6, joy_state.lastDir.right, joy_state.dir.right);
    joy_state.lastDir = joy_state.dir;


	return mouse_report; 
}
uint16_t       pointing_device_driver_get_cpi(void) { return 0; }
void           pointing_device_driver_set_cpi(uint16_t cpi) {}


// void matrix_init_user(void) {

// }