// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo5.h"

void CutsceneCameraPan(s16 target) {
    s16 pan;
    s16 delta;

    pan = 128 - (target - 256);
    delta = pan - g_unkGraphicsStruct.unk14;
    if (delta > 1) {
        g_unkGraphicsStruct.unk14++;
    } else if (delta < -1) {
        g_unkGraphicsStruct.unk14--;
    } else {
        g_unkGraphicsStruct.unk14 = pan;
    }
}

extern EInit g_EInitSpawner;
extern u32 g_CutsceneFlags;

#ifdef VERSION_PSP
INCLUDE_ASM("boss/bo5/nonmatchings/e_cutscene_actors", EntityCutsceneStage);
#else
void EntityCutsceneStage(Entity* self) {
    Entity* entity;
    s16 posScrollX;
    Tilemap* tilemap;

    tilemap = &g_Tilemap;
    entity = &PLAYER;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpawner);
        break;
    case 1:
        switch (self->step_s) {
        case 0:
            for (entity = &g_Entities[160]; entity < &g_Entities[192];
                 entity++) {
                if (entity->entityId == E_PRIZE_DROP) {
                    self->ext.cutsceneStage.target = entity;
                    self->step_s++;
                }
            }
            break;
        case 1:
            entity = self->ext.cutsceneStage.target;
            if (entity->entityId != E_PRIZE_DROP) {
                self->step_s++;
                D_us_801806DC = 0;
                g_CutsceneFlags |= 0x8000;
            }
            break;
        case 2:
            SetStep(2);
            break;
        }
        break;
    case 2:
        g_PauseAllowed = false;
        g_unkGraphicsStruct.pauseEnemies = true;
        g_Player.padSim = PAD_RIGHT;
        if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
            g_Player.padSim = PAD_WOLF;
        }
        g_Player.demo_timer = 1;
        self->step++;
        break;
    case 3:
        g_Player.padSim = PAD_NONE;
        if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
            if (g_Timer & 1) {
                g_Player.padSim = PAD_R2;
            }
        } else {
            g_Player.padSim = PAD_RIGHT;
            posScrollX = entity->posX.i.hi + tilemap->scrollX.i.hi;
            if (posScrollX > 288 && !(g_CutsceneFlags & 1)) {
                g_CutsceneFlags |= 1;
            }
            if (posScrollX > 320) {
                g_Player.padSim = PAD_NONE;
                entity->posX.i.hi = 320 - tilemap->scrollX.i.hi;
                self->step++;
            }
            if (posScrollX < 256) {
                posScrollX = 256;
            }
            CutsceneCameraPan(posScrollX);
        }
        g_Player.demo_timer = 1;
        break;
    case 4:
        CutsceneCameraPan(320);
        if (g_CutsceneFlags & 2) {
            self->step++;
        }
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
        break;
    case 5:
        CutsceneCameraPan(256);
        if (g_unkGraphicsStruct.unk14 == 128) {
            g_PauseAllowed = true;
            if (g_unkGraphicsStruct.pauseEnemies) {
                g_unkGraphicsStruct.pauseEnemies = false;
            }
            DestroyEntity(self);
        }
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
        break;
    }
}
#endif

#ifndef VERSION_PC
INCLUDE_ASM("boss/bo5/nonmatchings/e_cutscene_actors", func_us_801A62B4);
#else
void func_us_801A62B4(Entity* self) { NOT_IMPLEMENTED; }
#endif

void func_us_801A666C(Primitive* prim, s16 arg1) {
    prim->x0 = prim->x2 -= arg1;
    prim->x1 = prim->x3 += arg1;
    prim->y0 = prim->y1 -= arg1;
    prim->y2 = prim->y3 += arg1;
}

#ifndef VERSION_PC
INCLUDE_ASM("boss/bo5/nonmatchings/e_cutscene_actors", func_us_801A66B0);
#else
void func_us_801A66B0(Entity* self, s32 arg1) { NOT_IMPLEMENTED; }
#endif

void func_801B1D68(Entity* self) { func_us_801A66B0(self, 0); }

void BO5_RicSetDeadPrologue(Entity* self) { func_us_801A66B0(self, 1); }
