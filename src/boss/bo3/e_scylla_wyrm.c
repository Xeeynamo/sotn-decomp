// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo3.h"

AnimateEntityFrame D_us_80180FCC[] = {
    POSE(4, 0x49, 0), POSE(8, 0x4C, 0), POSE(8, 0x49, 0),
    POSE(8, 0x4D, 0), POSE(4, 0x49, 0), POSE_END};
AnimateEntityFrame D_us_80180FD8[] = {
    POSE(8, 0x49, 0), POSE(8, 0x4E, 0), POSE(8, 0x4F, 0), POSE_END};
AnimateEntityFrame D_us_80180FE0[] = {
    POSE(4, 0x4F, 0), POSE(8, 0x4E, 0), POSE(8, 0x49, 0), POSE_END};

INCLUDE_ASM("boss/bo3/nonmatchings/e_scylla_wyrm", func_us_801A4FB8);

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
