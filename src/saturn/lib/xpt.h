// SPDX-License-Identifier: AGPL-3.0-only
#ifndef XPT_H
#define XPT_H
typedef unsigned char Uint8;
typedef signed char Sint8;
typedef unsigned short Uint16;
typedef signed short Sint16;
typedef unsigned long Uint32;
typedef signed long Sint32;
typedef float Float32;
typedef double Float64;

typedef int Int;

typedef int Bool;

enum BooleanLogic { FALSE = 0, TRUE = 1 };

enum BooleanSwitch { OFF = 0, ON = 1 };

enum Judgement { OK = 0, NG = -1 };

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define ABS(x) ((x) < 0 ? -(x) : (x))

#endif
