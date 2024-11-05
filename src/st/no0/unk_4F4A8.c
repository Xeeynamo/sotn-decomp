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

void func_801CD78C(Point32* src, s32 speed, s16 angle, Point32* dst) {
    if (g_CurrentEntity->facingLeft) {
        angle = -angle;
    }
    *dst = *src;

    dst->x -= speed * rsin(angle) * 16;
    dst->y += speed * rcos(angle) * 16;
}

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D2424);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D26CC);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D274C);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D27C4);

bool func_us_801D29F8(s16* arg0, s32 arg1, s32 arg2) {
    if (abs(*arg0 - arg1) < arg2) {
        *arg0 = arg1;
        return true;
    }

    if (arg1 < *arg0) {
        *arg0 -= arg2;
    }

    if (*arg0 < arg1) {
        *arg0 += arg2;
    }

    return false;
}

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

void func_us_801D5250(void) {
    Primitive* prim = g_CurrentEntity->ext.prim;
    Collider collider;
    s32 i;

    for (i = 0; i < 10; i++) {
        g_api.CheckCollision(prim->x0, prim->y0 + 3, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            prim->y0 += collider.unk18;
        }
        prim = prim->next;
    }
}

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D52E0);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D5384);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D542C);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D5E4C);

INCLUDE_ASM("st/no0/nonmatchings/unk_4F4A8", func_us_801D606C);
