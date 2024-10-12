// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "game.h"

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801CF4A8);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801CF670);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801CF910);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801CFBE8);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D0718);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D0898);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D0990);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D0E7C);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D191C);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D20A4);

extern u16 g_EInitInteractable[];

void func_us_801D2318(Entity* entity) {
    if (entity->step == 0) {
        InitializeEntity(g_EInitInteractable);
    }
    if ((entity - 1)->entityId != 0x2E) {
        DestroyEntity(entity);
    }
}

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_801CD78C);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D2424);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D26CC);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D274C);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D27C4);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D29F8);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D2A64);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D4324);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D44A0);

INCLUDE_RODATA("st/no0/nonmatchings/unk_4F4A8", D_us_801C1684);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D4AA4);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D4CAC);

void func_us_801D4E30(void) {
    Primitive* prim;
    s32 i;

    prim = g_CurrentEntity->ext.prim;
    for (i = 0; i < 10; i++) {
        prim->x0 = (prim->x0 + prim->x1) / 2;
        prim->y0 = (prim->y0 + prim->y2) / 2;
        prim = prim->next;
    }
}

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D4E94);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D4FCC);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D5074);

void func_us_801D51EC(void) {
    Primitive* prim;
    s32 i;

    prim = g_CurrentEntity->ext.prim;
    for (i = 0; i < 10; i++) {
        prim->x0 = prim->x2 = prim->x0 - 3;
        prim->x1 = prim->x3 = prim->x0 + 6;
        prim->y0 = prim->y1 = prim->y0 - 3;
        prim->y2 = prim->y3 = prim->y0 + 6;

        prim = prim->next;
    }
}

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D5250);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D52E0);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D5384);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D542C);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D5E4C);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D606C);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D6254);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D6474);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D66F8);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D75E4);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", EntitySkeleton);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", EntitySkeletonPieces);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D7C20);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D7D00);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D7DAC);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D8150);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D8DF0);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D8FFC);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D91C4);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D9264);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801DA488);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801DA6B4);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801DADD0);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_801C3F9C);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_801C4198);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_801C4550);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", EntityAxeKnight);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", EntityAxeKnightRotateAxe);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", EntityAxeKnightThrowingAxe);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801DBDCC);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801DC194);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801DC64C);

void func_us_801DC754(void) {
    g_CurrentEntity->facingLeft = (GetSideToPlayer() & 1) ^ 1;
}

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801DC788);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", SkeletonAttackCheck);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801DCB48);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801DD018);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", EntitySkeletonThrownBone);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_801C6678);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801DD2B0);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", EntityMagicallySealedDoor);
