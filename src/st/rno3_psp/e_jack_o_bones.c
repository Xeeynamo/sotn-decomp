// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno3/rno3.h"

extern u16 D_pspeu_09259110[];
extern u16 D_pspeu_09259118[];

void func_pspeu_0923DEB0(void) {
    s32 temp_s1;
    u16 temp_s0;

    temp_s1 = UnkCollisionFunc2(&D_pspeu_09259110);
    temp_s0 = UnkCollisionFunc(&D_pspeu_09259118, 3);
    if ((temp_s1 == 0x80) || (temp_s0 & 2)) {
        SetStep(5);
        return;
    }
    if (!g_CurrentEntity->ext.ILLEGAL.u8[0]) {
        SetStep(4);
        return;
    }
    g_CurrentEntity->ext.ILLEGAL.u8[0] -= 1;
}


INCLUDE_ASM("st/rno3_psp/nonmatchings/rno3_psp/e_jack_o_bones", EntityJackOBones);

INCLUDE_ASM("st/rno3_psp/nonmatchings/rno3_psp/e_jack_o_bones", func_us_801C2380);

INCLUDE_ASM("st/rno3_psp/nonmatchings/rno3_psp/e_jack_o_bones", func_us_801C247C);
