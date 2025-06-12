// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"

// BSS
// This could have been BUTTON_COUNT * PAD_COUNT but nope, 16 on psp
u8 g_PadsRepeatTimer[16];

static void ResetPadsRepeat(void) {
    u8* ptr;
    s32 i;

    g_pads[0].repeat = 0;
    ptr = g_PadsRepeatTimer;

    for (i = 0; i < LEN(g_PadsRepeatTimer); i++) {
        *ptr++ = 0x10;
    }
}

static void UpdatePadsRepeat(void) {
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

void InitializePads(void) {
    Pad* pad;
    s32 i;

    PadInit(0);
    for (pad = g_pads, i = 0; i < PAD_COUNT; i++, pad++) {
        pad->pressed = pad->previous = pad->tapped = 0;
    }
    ResetPadsRepeat();
}

void ReadPads(void) {
    u32 padData;
    u32 rawPadRead;
    Pad* pad;
    s32 i;

    for (pad = g_pads, i = 0; i < PAD_COUNT; i++, pad++) {
        pad->previous = pad->pressed;
#ifdef VERSION_PSP
        if (i == 0) {
            rawPadRead = PadRead_PSP();
        } else {
            rawPadRead = 0;
        }
        padData = rawPadRead;
#else
        padData = PadRead(i >> 1);
#endif
        if (!(i & 1)) {
            pad->pressed = padData & 0xFFFF;
        } else {
            pad->pressed = padData >> 0x10;
        }

        pad->tapped = (pad->pressed ^ pad->previous) & pad->pressed;
    }
    UpdatePadsRepeat();
}
