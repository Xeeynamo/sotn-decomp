// SPDX-License-Identifier: AGPL-3.0-or-later
#include "top.h"

extern EInit g_EInitInteractable;
extern u32 g_CutsceneFlags;

// Alucard walks to the Warp platform
void func_us_801AD11C(Entity* self) {
    Tilemap* tilemap;
    Entity* player;
    s16 offsetX;
    s16 offsetY;

    tilemap = &g_Tilemap;
    player = &PLAYER;
    offsetX = player->posX.i.hi + g_Tilemap.scrollX.i.hi;
    offsetY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        g_PauseAllowed = false;
        g_unkGraphicsStruct.pauseEnemies = true;
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
        break;

    case 1:
        if (g_CutsceneFlags & 0x40) {
            g_Player.padSim = PAD_RIGHT;
            self->step++;
        }
        g_Player.demo_timer = 1;
        break;

    case 2:
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
        player->posX.i.hi = 0x380 - tilemap->scrollX.i.hi;
        if (g_CutsceneFlags & 0x20) {
            self->step++;
        }
        break;

    case 3:
        g_Player.padSim = PAD_LEFT;
        g_Player.demo_timer = 1;
        if (offsetX < 0x270) {
            g_Player.padSim |= PAD_CROSS;
            if (offsetX < 0x141) {
                g_Player.padSim = PAD_NONE;
                self->step++;
            }
            if ((g_Status.wornEquipment[1] == 0x19) &&
                (g_Player.vram_flag & 1)) {
                self->step += 2;
            }
        }
        break;

    case 4:
        g_Player.padSim = PAD_UP;
        g_Player.demo_timer = 1;
        break;

    case 5:
        g_PauseAllowed = true;
        if (g_unkGraphicsStruct.pauseEnemies) {
            g_unkGraphicsStruct.pauseEnemies = false;
        }
        DestroyEntity(self);
        break;
    }
}

INCLUDE_ASM("st/top/nonmatchings/post_richter_cutscene", func_us_801AD320);

INCLUDE_ASM("st/top/nonmatchings/post_richter_cutscene", func_us_801AD400);
