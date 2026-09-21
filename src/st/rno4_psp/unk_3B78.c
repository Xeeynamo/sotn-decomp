// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno4/rno4.h"

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", EntityRdaiUnk33);

#include "../e_imp_death_particle.h"

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_us_801BBE58_from_rnz1);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_us_801BC650_from_rnz1);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_us_801BCA5C_from_rnz1);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_us_801BCB9C_from_rnz1);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_us_801BCD80_from_rnz1);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_us_801BCE4C_from_rnz1);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_us_801BCFC8_from_rnz1);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", StepTowards);

void func_us_801D5DC8(Primitive* prim) {
    s32 yPos;
    switch (prim->p2) {
    case 0:
        LOW(prim->x2) = Random() * 8;
        prim->x3 = (Random() & 0x1F) + 0x10;
        prim->drawMode = DRAW_UNK02;
        prim->p2 += 1;

    case 1:
        yPos = (prim->y0 << 0x10) + prim->y1;
        yPos = yPos + LOW(prim->x2);
        LOW(prim->x2) -= 0x1000;
        prim->y0 = yPos >> 0x10;
        prim->y1 = yPos & 0xffff;
        if (!(prim->x3 -= 1)) {
            prim->p2 = 0;
            prim->drawMode = DRAW_HIDE;
            prim->p3 = 0;
        }
        return;
    }
}

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_us_801D5E90);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_us_801D68E0);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_us_801D6B8C);
