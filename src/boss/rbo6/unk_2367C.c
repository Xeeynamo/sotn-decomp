// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo6.h"

extern s32 g_CutsceneFlags;
extern EInit g_EInitInteractable;

void func_us_801A367C(Entity* self) {
    Tilemap* unusedTilemap = &g_Tilemap;
    Entity* player = &PLAYER;
    s16 unusedX = player->posX.i.hi + g_Tilemap.scrollX.i.hi;
    s16 unusedY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        g_PauseAllowed = 0;
        g_unkGraphicsStruct.pauseEnemies = 1;
        player->facingLeft = 0;
        if (g_Status.wornEquipment[1] != ITEM_AXE_LORD_ARMOR) {
            player->animCurFrame = 0xBF;
        }
        player->posX.i.hi = 0x70;
        g_Player.padSim = 0;
        g_Player.demo_timer = 1;
        break;
    case 1:
        if (g_Status.wornEquipment[1] != ITEM_AXE_LORD_ARMOR) {
            player->animCurFrame = 0xBF;
        }
        player->posX.i.hi = 0x70;
        if (g_CutsceneFlags & 2) {
            self->step += 1;
        }
        g_Player.padSim = 0;
        g_Player.demo_timer = 1;
        break;
    case 2:
        g_PauseAllowed = 1;
        g_unkGraphicsStruct.pauseEnemies = 0;
        g_Entities[E_AFTERIMAGE_1].ext.afterImage.disableFlag = 1;
        DestroyEntity(self);
        break;
    }
}

INCLUDE_ASM("boss/rbo6/nonmatchings/unk_2367C", func_us_801A37B4);

INCLUDE_ASM("boss/rbo6/nonmatchings/unk_2367C", func_us_801A399C);

INCLUDE_ASM("boss/rbo6/nonmatchings/unk_2367C", func_us_801A3BE0);

INCLUDE_ASM("boss/rbo6/nonmatchings/unk_2367C", func_us_801A4028);

INCLUDE_ASM("boss/rbo6/nonmatchings/unk_2367C", func_us_801A9208_from_bo6);
