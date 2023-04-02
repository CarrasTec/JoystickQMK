#ifndef MACROKRS_H
#define MACROKRS_H

#include "quantum.h"

#define LAYOUT( \
	K00, K01, K02, K03, K04, \
	K10, K11, K12, K13, K14, \
	K20, K21, K22, K23,      \
	     K31, K32  \
) { \
	{ K00,   K01,   K02,   K03,   K04 }, \
	{ K10,   K11,   K12,   K13,   K14 }, \
	{ K20,   K21,   K22,   K23,   KC_NO }, \
	{ KC_NO, K31,   K32,   KC_NO, KC_NO }  \
}

#endif