// SPDX-License-Identifier: AGPL-3.0-or-later
#include "zero.h"
#include "zero/fontmap.h"
#include "zero/text.h"
#include "inc_asm.h"
#include "sattypes.h"

void func_06019074(s8* arg0, u8 arg1) {
    BottomCornerText text;
    s32 prims;

    func_06019560(arg0, text.data, &text.unk40, &text.primitiveCount);
    prims = AllocPrimitives(0, text.primitiveCount + 4);
    g_unkGraphicsStruct.BottomCornerTextPrims = prims;
    if (prims != -1) {
        func_060190D8(text.unk40, text.data, arg1);
        g_unkGraphicsStruct.BottomCornerTextTimer = 0x130;
    }
}
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60190D8, func_060190D8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6019560, func_06019560);

void func_060195F0(void) {
    DAT_060476a4 = 0;
    DAT_060476a0 = 0;
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601960C, func_0601960C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601972C, func_0601972C);
u16 func_060198F4(u16 arg0) {
    SaturnFontGlyphMapping* glyph;
    u16* mapped;
    u16 key;
    u16 result;

    glyph = g_SaturnFontGlyphMappings;
    key = glyph->shiftJis;
    result = 0x1800;
    if (key != 0) {
        mapped = &glyph->characterOffset;
        do {
            if (key == arg0) {
                return *mapped;
            }
            glyph++;
            key = glyph->shiftJis;
            mapped += 2;
        } while (key != 0);
    }
    return result;
}
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601992C, func_0601992C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60199F8, func_060199F8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6019A7C, func_06019A7C);

// _INIT_NOW_LOADING
void func_06019FA0(s32 param_1) {
    func_0600C6E4(param_1);
    SetVdp2BackgroundColorRgb(0, 0, 0);
    if (param_1 == 0) {
        DAT_06057C90 = param_1;
        func_06019A7C(&DAT_06057C90, 80, 112, 0);
    }
}
void func_06019FE4(s32 arg0) {
    if (arg0 == 0) {
        func_06019A7C(&DAT_06057C90, 80, 112, 0);
    } else if (arg0 == 1) {
        func_0601A020();
    }
}
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601A020, func_0601A020);
