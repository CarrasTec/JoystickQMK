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

#include "joy_input.h"
#include "analog.h"
#include "gpio.h"
#include "wait.h"
#include "timer.h"
#include <stdlib.h>
#include "quantum.h"

// Set Parameters
uint16_t minAxisValue = ANALOG_JOYSTICK_AXIS_MIN;
uint16_t maxAxisValue = ANALOG_JOYSTICK_AXIS_MAX;

uint8_t maxCursorSpeed = ANALOG_JOYSTICK_SPEED_MAX;
uint8_t speedRegulator = ANALOG_JOYSTICK_SPEED_REGULATOR; // Lower Values Create Faster Movement

int16_t xOrigin, yOrigin;
int16_t xOrigin2, yOrigin2;

uint16_t lastCursor = 0;

int16_t axisCoordinate(pin_t pin, uint16_t origin) {
    int8_t  direction;
    int16_t distanceFromOrigin;
    int16_t range;

    int16_t position = analogReadPin(pin);

    if (origin == position) {
        return 0;
    } else if (origin > position) {
        distanceFromOrigin = origin - position;
        range              = origin - minAxisValue;
        direction          = -1;
    } else {
        distanceFromOrigin = position - origin;
        range              = maxAxisValue - origin;
        direction          = 1;
    }

    float   percent    = (float)distanceFromOrigin / range;
    int16_t coordinate = (int16_t)(percent * 100);
    if (coordinate < 0) {
        return 0;
    } else if (coordinate > 100) {
        return 100 * direction;
    } else {
        return coordinate * direction;
    }
}

int8_t axisToMouseComponent(pin_t pin, int16_t origin, uint8_t maxSpeed) {
    int16_t coordinate = axisCoordinate(pin, origin);
    if (coordinate != 0) {
        float percent = (float)coordinate / 100;
        return percent * maxCursorSpeed * (abs(coordinate) / speedRegulator);
    } else {
        return 0;
    }
}

report_joy_t joy_input_read(void) {
    report_joy_t report = {0};
    if (timer_elapsed(lastCursor) > joy_speed_read) {
        lastCursor = timer_read();
        report.x   = axisToMouseComponent(ANALOG_JOYSTICK_X_AXIS_PIN, xOrigin, maxCursorSpeed);
        report.y   = axisToMouseComponent(ANALOG_JOYSTICK_Y_AXIS_PIN, yOrigin, maxCursorSpeed);
        report.x2   = axisToMouseComponent(ANALOG_JOYSTICK_X2_AXIS_PIN, xOrigin2, maxCursorSpeed);
        report.y2   = axisToMouseComponent(ANALOG_JOYSTICK_Y2_AXIS_PIN, yOrigin2, maxCursorSpeed);
    }
#ifdef ANALOG_JOYSTICK_CLICK_PIN
    report.button = !readPin(ANALOG_JOYSTICK_CLICK_PIN);
#endif
    return report;
}

void joy_input_init(void) {
#ifdef ANALOG_JOYSTICK_CLICK_PIN
    setPinInputHigh(ANALOG_JOYSTICK_CLICK_PIN);
#endif
    // Account for drift
    xOrigin = analogReadPin(ANALOG_JOYSTICK_X_AXIS_PIN);
    yOrigin = analogReadPin(ANALOG_JOYSTICK_Y_AXIS_PIN);
    xOrigin2 = analogReadPin(ANALOG_JOYSTICK_X2_AXIS_PIN);
    yOrigin2 = analogReadPin(ANALOG_JOYSTICK_Y2_AXIS_PIN);
    joy_speed_read = 100;
}

joy_direction_t joy_input_direction(report_joy_t report){
    joy_direction_t direction;
    int8_t x=report.x*speedRegulator;
    int8_t y=report.y*speedRegulator;
    
    direction.left = (x > 5);
    direction.right = (x < -5);
    direction.up = (y > 5);
    direction.down = (y < -5);
    if (abs(x)>0)
        joy_speed_read = 100 - (int16_t)abs(x);
    else if (abs(y)>0)
        joy_speed_read = 100 - (int16_t)abs(y);
    if (joy_speed_read <=0)
        joy_speed_read=1;
    return direction;
}

void joy_update_keycode(uint16_t keycode, bool last, bool current){
    if (last != current) {
        if (current) {
            register_code16(keycode);
        } else {
            unregister_code16(keycode);
        }
    } 
}
