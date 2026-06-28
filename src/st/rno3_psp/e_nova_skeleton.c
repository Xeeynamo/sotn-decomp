// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno3/rno3.h"

extern s16 D_pspeu_0925A550[];

void func_pspeu_0924EB18(void) {
    // return value not used, but function has side effects
    s32 unused = UnkCollisionFunc2(&D_pspeu_0925A550);
    // if cooldown has expired...
    if (!g_CurrentEntity->ext.ILLEGAL.u8[5]) {
        if (GetDistanceToPlayerX() >= 0x80){
            return;
        }
        if((g_CurrentEntity->facingLeft) ^ (GetSideToPlayer() & 1)) {
            SetStep(6);
        }
    } else {
        g_CurrentEntity->ext.ILLEGAL.u8[5]--;
    }
}

INCLUDE_ASM("st/rno3_psp/nonmatchings/rno3_psp/e_nova_skeleton", func_pspeu_0924EBC8);

INCLUDE_ASM("st/rno3_psp/nonmatchings/rno3_psp/e_nova_skeleton", EntityNovaSkeleton);

INCLUDE_ASM("st/rno3_psp/nonmatchings/rno3_psp/e_nova_skeleton", EntityBladeSoldierDeathParts);

INCLUDE_ASM("st/rno3_psp/nonmatchings/rno3_psp/e_nova_skeleton", func_us_801C2FF0);

INCLUDE_ASM("st/rno3_psp/nonmatchings/rno3_psp/e_nova_skeleton", func_us_801C34A0);
