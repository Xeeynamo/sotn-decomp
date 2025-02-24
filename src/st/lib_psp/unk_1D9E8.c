// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../../st/lib/lib.h"

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09255068);

// func_us_801BB8DC code is shared with PSX and is ready for merge
// Seems to be related to the iframes of the ectoplasm and the skeleton spawns
// Mudman spawn animation causes iframes for it
void func_us_801BB8DC(s16* unkArg) {
    switch (g_CurrentEntity->step_s) {
    case 0:
        g_CurrentEntity->animCurFrame = 0;
        g_CurrentEntity->hitboxState = 0;
        g_CurrentEntity->zPriority -= 0x10;
        g_CurrentEntity->ext.lesserDemon.unkB2 = g_CurrentEntity->palette;
        g_CurrentEntity->drawFlags |= FLAG_DRAW_UNK8;
        g_CurrentEntity->unk6C = 2;
        g_CurrentEntity->step_s++;
        g_CurrentEntity->flags |= FLAG_UNK_2000;
        g_CurrentEntity->flags &= ~(FLAG_UNK_800 | FLAG_UNK_400);
        if (!unkArg) {
            g_CurrentEntity->step_s = 2;
        }
        break;
    case 1:
        if (UnkCollisionFunc3(unkArg) & 1) {
            g_CurrentEntity->animCurFrame = 1;
            g_CurrentEntity->step_s++;
        }
        break;
    case 2:
        g_CurrentEntity->unk6C += 4;
        if (g_CurrentEntity->unk6C > 0xA0) {
            g_CurrentEntity->drawFlags = FLAG_DRAW_DEFAULT;
            g_CurrentEntity->drawMode = DRAW_DEFAULT;
            g_CurrentEntity->ext.lesserDemon.unkB0 = 0x20;
            g_CurrentEntity->step_s++;
        }
        break;
    case 3:
        if (g_CurrentEntity->ext.lesserDemon.unkB0 % 2) {
            g_CurrentEntity->palette = g_CurrentEntity->ext.lesserDemon.unkB2;
        } else {
            g_CurrentEntity->palette = 0x819F;
        }

#ifdef VERSION_PSP
        if (!(--g_CurrentEntity->ext.lesserDemon.unkB0)) {
#else
        if (!(--g_CurrentEntity->ext.lesserDemon.unkB0 << 16)) {
#endif

            g_CurrentEntity->palette = g_CurrentEntity->ext.lesserDemon.unkB2;
            g_CurrentEntity->hitboxState = 3;
            SetStep(1);
        }
        break;
    }
}

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09256018);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_092564B8);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09256AC0);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09256E08);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09257100);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_092576C8);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09257BF8);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09258100);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09258A38);

// Lesser Demon
INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09258B50);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_0925A798);
