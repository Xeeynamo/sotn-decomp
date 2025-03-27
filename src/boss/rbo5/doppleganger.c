// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo5.h"

INCLUDE_ASM("boss/rbo5/nonmatchings/doppleganger", func_us_801C096C);

INCLUDE_ASM("boss/rbo5/nonmatchings/doppleganger", func_us_801C0C00);

INCLUDE_ASM("boss/rbo5/nonmatchings/doppleganger", func_us_801C11D4);

INCLUDE_ASM("boss/rbo5/nonmatchings/doppleganger", MemCardSetPort);

INCLUDE_ASM("boss/rbo5/nonmatchings/doppleganger", func_us_801C1DC8);

INCLUDE_ASM("boss/rbo5/nonmatchings/doppleganger", func_us_801C2D90);

INCLUDE_ASM("boss/rbo5/nonmatchings/doppleganger", func_us_801C2EC0);

INCLUDE_ASM("boss/rbo5/nonmatchings/doppleganger", func_us_801C34EC);

extern Point16 D_us_80181338[];

void func_us_801C3AC8(void) {
    Collider collider;

    s16* dopY;
    s16* dopX;
    s32 effects;
    s32 i;
    u32* pVramFlag;

    s16 offsetX, offsetY;

    dopY = &DOPPLEGANGER.posY.i.hi;
    dopX = &DOPPLEGANGER.posX.i.hi;

    pVramFlag = &g_Dop.vram_flag;
    effects =
        g_Dop.unk04 & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                       EFFECT_UNK_0400 | EFFECT_UNK_0002 | EFFECT_SOLID);
    if (effects == (EFFECT_UNK_8000 | EFFECT_UNK_0002 | EFFECT_SOLID) ||
        effects == (EFFECT_UNK_0800 | EFFECT_UNK_0002 | EFFECT_SOLID) ||
        effects == (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                    EFFECT_SOLID)) {
        *pVramFlag |= 4;
        return;
    }

    for (i = 0; i < 7; i++) {
        effects = g_Dop.colWall[i].effects &
                  (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                   EFFECT_UNK_0002 | EFFECT_SOLID);
        if ((effects == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_SOLID)) ||
            (effects == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0002 |
                         EFFECT_SOLID)) ||
            (effects == (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_SOLID)) ||
            (effects == (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                         EFFECT_SOLID)) ||
            (effects == (EFFECT_UNK_8000 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
            (effects == (EFFECT_UNK_0800 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
            (effects == (EFFECT_UNK_0002 | EFFECT_SOLID))) {

            offsetX = *dopX + D_us_80181338[i].x + g_Dop.colWall[i].unk4 - 1;
            offsetY = *dopY + D_us_80181338[i].y;
            g_api.CheckCollision(offsetX, offsetY, &collider, 0);

            if (!(collider.effects & EFFECT_SOLID)) {
                *pVramFlag |= 4;
                *dopX += g_Dop.colWall[i].unk4;
                return;
            }
        }

        if ((effects & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
                EFFECT_UNK_8000 &&
            i != 0 &&
            ((g_Dop.colWall[0].effects & EFFECT_UNK_0800) ||
             !(g_Dop.colWall[0].effects &
               (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
            *pVramFlag |= 4;
            *dopX += g_Dop.colWall[i].unk4;
            return;
        }

        if ((effects & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
                EFFECT_UNK_0800 &&
            i != 6 &&
            ((g_Dop.colWall[6].effects & EFFECT_UNK_8000) ||
             !(g_Dop.colWall[6].effects &
               (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
            *pVramFlag |= 4;
            *dopX += g_Dop.colWall[i].unk4;
            return;
        }
    }
}

void func_us_801C3D10(void) {
    Collider collider;

    s16* dopY;
    s16* dopX;
    s32 effects;
    s32 i;
    u32* pVramFlag;

    s16 offsetX, offsetY;
    dopY = &DOPPLEGANGER.posY.i.hi;
    dopX = &DOPPLEGANGER.posX.i.hi;

    pVramFlag = &g_Dop.vram_flag;
    effects =
        g_Dop.unk04 &
        (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_UNK_0800 |
         EFFECT_UNK_0400 | EFFECT_UNK_0002 | EFFECT_SOLID);
    if (effects == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0002 |
                    EFFECT_SOLID) ||
        effects == (EFFECT_UNK_0800 | EFFECT_UNK_0400 | EFFECT_UNK_0002 |
                    EFFECT_SOLID) ||
        effects == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                    EFFECT_UNK_0400 | EFFECT_UNK_0002 | EFFECT_SOLID)) {
        *pVramFlag |= 8;
        return;
    }

    for (i = 7; i < 14; i++) {
        effects = g_Dop.colWall[i].effects &
                  (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                   EFFECT_UNK_0002 | EFFECT_SOLID);
        if (effects == (EFFECT_UNK_8000 | EFFECT_SOLID) ||
            effects == (EFFECT_UNK_8000 | EFFECT_UNK_0002 | EFFECT_SOLID) ||
            effects == (EFFECT_UNK_0800 | EFFECT_SOLID) ||
            effects == (EFFECT_UNK_0800 | EFFECT_UNK_0002 | EFFECT_SOLID) ||
            effects == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0002 |
                        EFFECT_SOLID) ||
            effects == (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                        EFFECT_SOLID) ||
            effects == (EFFECT_UNK_0002 | EFFECT_SOLID)) {

            offsetX = *dopX + D_us_80181338[i].x + g_Dop.colWall[i].unkC + 1;
            offsetY = *dopY + D_us_80181338[i].y;
            g_api.CheckCollision(offsetX, offsetY, &collider, 0);

            if (!(collider.effects & EFFECT_SOLID)) {
                *pVramFlag |= 8;
                *dopX += g_Dop.colWall[i].unkC;
                return;
            }
        }

        if ((effects & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
                (EFFECT_UNK_8000 | EFFECT_UNK_4000) &&
            i != 7 &&
            ((g_Dop.colWall[7].effects & EFFECT_UNK_0800) ||
             !(g_Dop.colWall[7].effects &
               (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
            *pVramFlag |= 8;
            *dopX += g_Dop.colWall[i].unkC;
            return;
        }

        if (((effects &
              (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
             (EFFECT_UNK_4000 | EFFECT_UNK_0800)) &&
            i != 13 &&
            ((g_Dop.colWall[13].effects & EFFECT_UNK_8000) ||
             !(g_Dop.colWall[13].effects &
               (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
            *pVramFlag |= 8;
            *dopX += g_Dop.colWall[i].unkC;
            return;
        }
    }
}
