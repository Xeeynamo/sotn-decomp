// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo3.h"

AnimateEntityFrame D_us_80180FCC[] = {
    POSE(4, 0x49, 0), POSE(8, 0x4C, 0), POSE(8, 0x49, 0),
    POSE(8, 0x4D, 0), POSE(4, 0x49, 0), POSE_END};
AnimateEntityFrame D_us_80180FD8[] = {
    POSE(8, 0x49, 0), POSE(8, 0x4E, 0), POSE(8, 0x4F, 0), POSE_END};
AnimateEntityFrame D_us_80180FE0[] = {
    POSE(4, 0x4F, 0), POSE(8, 0x4E, 0), POSE(8, 0x49, 0), POSE_END};

// static once func_us_801A5338 is C
void func_us_801A4FB8(void) {
    Primitive* prim;
    Entity* entity;
    s32 posX;
    s32 posY;
    s16 angle;
    s32 offsetX;
    s32 offsetY;
    s32 i;

    posX = g_CurrentEntity->posX.val;
    posY = g_CurrentEntity->posY.val;
    prim = g_CurrentEntity->ext.scyllaWyrm.prim;
    prim->x1 = prim->x3 = posX;
    prim->y1 = prim->y3 = posY;
    prim->drawMode = DRAW_HIDE;
    entity = g_CurrentEntity + 1;
    for (i = 0; i < 12; i++, entity++) {
        offsetX = entity->posX.val - posX;
        offsetY = entity->posY.val - posY;
        angle = ratan2(offsetY, offsetX);
        if (!g_CurrentEntity->params) {
            angle += 0x400;
        } else {
            angle -= 0x400;
        }
        posX = (entity->posX.val + posX) / 2 >> 16;
        posY = (entity->posY.val + posY) / 2 >> 16;
        offsetX = (rcos(angle) << 4) >> 12;
        offsetY = (rsin(angle) << 4) >> 12;
        prim->x0 = posX + offsetX;
        prim->y0 = posY + offsetY;
        prim->x2 = posX - offsetX;
        prim->y2 = posY - offsetY;
        if (g_CurrentEntity->flags & 0xF) {
            prim->clut = g_CurrentEntity->palette & 0xFFF;
        } else {
            prim->clut = 0x205;
        }
        prim = prim->next;
        prim->x1 = posX + offsetX;
        prim->y1 = posY + offsetY;
        prim->x3 = posX - offsetX;
        prim->y3 = posY - offsetY;
        posX = entity->posX.val;
        posY = entity->posY.val;
    }
    prim->drawMode = DRAW_HIDE;
}

// static once func_us_801A5338 is C
void func_us_801A516C(void) {
    Entity* entity;
    s32 posX;
    s32 posY;
    s32 newX;
    s32 newY;
    Entity* next;
    s32 i;

    posX = g_CurrentEntity->posX.val;
    posY = g_CurrentEntity->posY.val;
    entity = g_CurrentEntity + 1;
    for (i = 0; i < 11; i++) {
        next = entity + 1;
        posX = (posX + next->posX.val) >> 1;
        posY = (posY + next->posY.val) >> 1;
        newX = posX - entity->posX.val;
        newY = posY - entity->posY.val;
        newX = (newX >> 2) + posX;
        newY = (newY >> 2) + posY;
        entity->posX.val = newX;
        entity->posY.val = newY;
        posX = newX;
        posY = newY;
        entity = next;
    }
}

INCLUDE_ASM("boss/bo3/nonmatchings/e_scylla_wyrm", func_us_801A51E4);

INCLUDE_ASM("boss/bo3/nonmatchings/e_scylla_wyrm", func_us_801A5338);

INCLUDE_ASM("boss/bo3/nonmatchings/e_scylla_wyrm", func_us_801A57A4);

INCLUDE_ASM("boss/bo3/nonmatchings/e_scylla_wyrm", func_us_801A5948);
