/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

#pragma once

#include <stdbool.h>
#include <stdint.h>

#define ANALOG_JOYSTICK_X_AXIS_PIN F4
#define ANALOG_JOYSTICK_Y_AXIS_PIN F5
#define ANALOG_JOYSTICK_X2_AXIS_PIN F7
#define ANALOG_JOYSTICK_Y2_AXIS_PIN F6
#define ANALOG_JOYSTICK_AXIS_MIN 0
#define ANALOG_JOYSTICK_AXIS_MAX 1023
#define ANALOG_JOYSTICK_SPEED_REGULATOR 10
#define ANALOG_JOYSTICK_READ_INTERVAL 100
#define ANALOG_JOYSTICK_SPEED_MAX 1

typedef struct {
    int8_t x;
    int8_t y;
    int8_t x2;
    int8_t y2;
    bool   button;
} report_joy_t;

typedef struct {
    bool up;
    bool right;
    bool down;
    bool left;
} joy_direction_t;

typedef struct {
    joy_direction_t dir;
    joy_direction_t lastDir;
} joy_state_t;

joy_state_t joy_state;

uint16_t joy_speed_read;

report_joy_t joy_input_read(void);
void         joy_input_init(void);

void joy_update_keycode(uint16_t keycode, bool last, bool current);
joy_direction_t joy_input_direction(report_joy_t report);
