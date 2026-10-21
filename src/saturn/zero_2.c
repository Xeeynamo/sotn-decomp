// SPDX-License-Identifier: AGPL-3.0-or-later
#include "zero.h"
#include "zero/fontmap.h"
#include "zero/text.h"
#include "inc_asm.h"
#include "sattypes.h"

void func_06019058(Entity* self) {
    if (self->step == 0) {
        self->step++;
    }
}

const s16 DAT_6019072 = 0;

void func_06019074(s8* arg0, u8 arg1) {
    BottomCornerText text;

    func_06019560(arg0, text.data, &text.unk40, &text.primitiveCount);
    g_unkGraphicsStruct.BottomCornerTextPrims =
        AllocPrimitives(0, text.primitiveCount + 4);
    if (g_unkGraphicsStruct.BottomCornerTextPrims != -1) {
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

extern u16 DAT_06064500[];
extern u16 DAT_06064520[];

#define ExtractBit(x)                                                          \
    x & 1;                                                                     \
    x >>= 1

// very similar to func_80106A28
u16* func_0601972C(u16 ch) {
    u16* srcPtr;
    u16 row;
    u16* bitmap;
    u16* temp_r0;
    u16 val0, val1, val2;
    u16 b0, b1, b2, b3;
    s32 i;

    if ((DAT_0605C6E4 != 0) || (DAT_060476a4 != 0)) {
        temp_r0 = func_060199F8(ch);
    } else {
        temp_r0 = func_0601992C(ch);
    }
    if (temp_r0 == NULL) {
        return NULL;
    }
    DMA_CpuMemCopy2(DAT_06064500, temp_r0, 0x10);
    while (DMA_CpuResult() == 2) {
    }
    bitmap = DAT_06064500;
    srcPtr = DAT_06064520;
    for (i = 16; i > 0; --i) {
        val0 = val2 = val1 = 0;

        row = *bitmap;

        if (row & 0xF) {
            b0 = ExtractBit(row);
            b1 = ExtractBit(row);
            b2 = ExtractBit(row);
            b3 = ExtractBit(row);

            val2 |= (b0 * 3 + b1);
            val2 |= (b1 * 2 + b2 * 2) << 4;
            val2 |= (b2 + b3 * 3) << 8;
        } else {
            row >>= 4;
        }
        if (row & 0xF) {
            b0 = ExtractBit(row);
            b1 = ExtractBit(row);
            b2 = ExtractBit(row);
            b3 = ExtractBit(row);

            val2 |= (b0 * 3 + b1) << 12;
            val1 |= (b1 * 2 + b2 * 2);
            val1 |= (b2 + b3 * 3) << 4;
        } else {
            row >>= 4;
        }
        if (row & 0xF) {
            b0 = ExtractBit(row);
            b1 = ExtractBit(row);
            b2 = ExtractBit(row);
            b3 = ExtractBit(row);

            val1 |= (b0 * 3 + b1) << 8;
            val1 |= (b1 * 2 + b2 * 2) << 12;
            val0 |= (b2 + b3 * 3);
        } else {
            row >>= 4;
        }
        if (row & 0xF) {
            b0 = ExtractBit(row);
            b1 = ExtractBit(row);
            b2 = ExtractBit(row);
            b3 = ExtractBit(row);

            val0 |= (b0 * 3 + b1) << 4;
            val0 |= (b1 * 2 + b2 * 2) << 8;
            val0 |= (b2 + b3 * 3) << 12;
        } else {
            row >>= 4;
        }
        *srcPtr++ = val0;
        *srcPtr++ = val1;
        *srcPtr++ = val2;
        bitmap++;
    }
    return DAT_06064520;
}

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

// original name: INIT_NOW_LOADING
void func_06019FA0(s32 arg0) {
    func_0600C6E4(arg0);
    SetVdp2BackgroundColorRgb(0, 0, 0);
    if (arg0 == 0) {
        DAT_06057C90 = arg0;
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
