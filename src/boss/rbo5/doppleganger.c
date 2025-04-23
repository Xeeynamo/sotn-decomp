// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo5.h"

extern s32 D_us_801D36E8[];
extern s32 D_us_801D3768[];
extern s32 D_us_801D4344;

void func_us_801C096C(void) {
    Entity* entity;
    Primitive* prim;
    s16 primIndex;
    s32 angle;
    s32 scale;
    s32 i;
    s32 colliderSize;
    s32* colliders;

    g_CurrentEntity = &DOPPLEGANGER;
    DOPPLEGANGER.animSet = ANIMSET_OVL(1);
    DOPPLEGANGER.unk5A = 8;
    g_PlayerDraw[8].enableColorBlend = 0;
    DOPPLEGANGER.zPriority = g_unkGraphicsStruct.g_zEntityCenter + 8;
    if (DOPPLEGANGER.posX.i.hi < PLAYER.posX.i.hi) {
        DOPPLEGANGER.facingLeft = false;
    } else {
        DOPPLEGANGER.facingLeft = true;
    }

    DOPPLEGANGER.palette = PAL_OVL(0x200);
    DOPPLEGANGER.rotX = 0x100;
    DOPPLEGANGER.rotY = 0x100;
    DOPPLEGANGER.drawMode = DRAW_DEFAULT;
    DOPPLEGANGER.flags =
        FLAG_UNK_10000000 | FLAG_POS_CAMERA_LOCKED | FLAG_UNK_400000;

    // BUG: this loop seems to be clearing parts of the floor
    //      ceiling colliders, but not all of them
    colliderSize = (sizeof(Collider) * 6) + 0x1C;
    colliders = (s32*)g_Dop.colFloor;
    for (i = 0; i < colliderSize; i++, colliders++) {
        *colliders = 0;
    }

    D_us_801D4344 = 1;
    g_Dop.vram_flag = 1;
    func_8010E570(0);
    entity = &g_Entities[E_ID_41];

    for (i = 0; i < 3; i++, entity++) {
        DestroyEntity(entity);
        entity->animSet = ANIMSET_OVL(1);
        entity->unk5A = i + 9;
        entity->palette = PAL_OVL(0x200);
        entity->flags = FLAG_POS_CAMERA_LOCKED;
    }
    primIndex = g_api.AllocPrimitives(PRIM_TILE, 6);
    prim = &g_PrimBuf[primIndex];
    g_Entities[E_ID_41].primIndex = primIndex;
    g_Entities[E_ID_41].flags |= FLAG_HAS_PRIMS;

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE | DRAW_UNK02;
        prim = prim->next;
    }

    for (i = 0; i < 32; i++) {
        angle = (rand() & 0x3FF) + 0x100;
        scale = (rand() & 0xFF) + 0x100;
        D_us_801D36E8[i] = ((rcos(angle) << 4) * scale) >> 8;
        D_us_801D3768[i] = -(((rsin(angle) << 4) * scale) >> 7);
    }

    g_api.TimeAttackController(
        TIMEATTACK_EVENT_DOPPLEGANGER_40_DEFEAT, TIMEATTACK_SET_VISITED);
}

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
