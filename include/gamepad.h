#ifndef GAMEPAD_H
#define GAMEPAD_H

#include "types.h"

#define BUTTON_COUNT 8
#define PAD_COUNT 2

#if !defined(VERSION_PSP)
#define PAD_L2 0x0001
#define PAD_R2 0x0002
#define PAD_L1 0x0004
#define PAD_R1 0x0008
#define PAD_TRIANGLE 0x0010
#define PAD_CIRCLE 0x0020
#define PAD_CROSS 0x0040
#define PAD_SQUARE 0x0080
#define PAD_SELECT 0x0100
#define PAD_L3 0x0200
#define PAD_R3 0x0400
#define PAD_START 0x0800
#define PAD_UP 0x1000
#define PAD_RIGHT 0x2000
#define PAD_DOWN 0x4000
#define PAD_LEFT 0x8000

#else
#define PAD_L1 0x0100
#define PAD_R1 0x0200
#define PAD_TRIANGLE 0x1000
#define PAD_CIRCLE 0x2000
#define PAD_CROSS 0x4000
#define PAD_SQUARE 0x8000
#define PAD_SELECT 0x0001
#define PAD_START 0x0008
#define PAD_UP 0x0010
#define PAD_RIGHT 0x0020
#define PAD_DOWN 0x0040
#define PAD_LEFT 0x0080
#endif

// Game Buttons unofficially refers to buttons used in playing the game.
// Direction, action and shoulder buttons. Any button except start or select.
#define GAMEBUTTONS (~(PAD_START | PAD_SELECT))

typedef struct {
    /* 0x0 */ u16 pressed;
    /* 0x2 */ s16 previous;
    /* 0x4 */ u16 tapped;
    /* 0x6 */ u16 repeat;
} Pad; // size = 0x8

extern Pad g_pads[PAD_COUNT];


// Used to track the state of moves the player does with a sequence of buttons.
// This includes spells, some of Richter's moves, etc.
typedef struct {
    s16 buttonsCorrect;
    s16 timer;
} ButtonComboState;

#endif // GAMEPAD_H
