// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

// This could have been BUTTON_COUNT * PAD_COUNT but nope, 16 on psp
extern u8 g_PadsRepeatTimer[16];

void ResetPadsRepeat(void) {
    u8* ptr;
    s32 i;

    g_pads[0].repeat = 0;
    ptr = g_PadsRepeatTimer;

    for (i = 0; i < LEN(g_PadsRepeatTimer); i++) {
        *ptr++ = 0x10;
    }
}

void UpdatePadsRepeat(void) {
    u16 button = 1;
    u16 unk = g_pads[0].tapped;
    u16 pressed = g_pads[0].pressed;
    u16 repeat = 0;
    u8* timers = g_PadsRepeatTimer;
    s32 i = 0;

    while (i < 0x10) {
        if (pressed & button) {
            if (unk & button) {
                repeat |= button;
                timers[0] = 0x10;
            } else {
                if (!timers[0]--) {
                    repeat |= button;
                    timers[0] = 5;
                }
            }
        }
        i++;
        timers++;
        button <<= 1;
    }
    g_pads[0].repeat = repeat;
}

INCLUDE_ASM("dra_psp/psp/dra_psp/61B78", func_psp_0913E658);

INCLUDE_ASM("dra_psp/psp/dra_psp/61B78", func_psp_0913E6D0);
