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

INCLUDE_ASM("dra_psp/psp/dra_psp/61B78", func_psp_0913E558);

INCLUDE_ASM("dra_psp/psp/dra_psp/61B78", func_psp_0913E658);

INCLUDE_ASM("dra_psp/psp/dra_psp/61B78", func_psp_0913E6D0);
