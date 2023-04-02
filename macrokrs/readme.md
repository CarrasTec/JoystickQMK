## Joystick  
En rules.mk:
JOYSTICK_ENABLE = yes
By default, two axes and eight buttons are defined, with a reported resolution of 8 bits (-127 to +127). or change in config.h

// Min 0, max 32
#define JOYSTICK_BUTTON_COUNT 16
// Min 0, max 6: X, Y, Z, Rx, Ry, Rz
#define JOYSTICK_AXIS_COUNT 3
// Min 8, max 16
#define JOYSTICK_AXIS_RESOLUTION 10


