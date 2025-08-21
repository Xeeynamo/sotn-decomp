// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

#ifdef VERSION_PSP
extern s32 E_ID(PRIEST);
#endif

static AnimationFrame anim_1[] = {{8, 8}, {8, 9}, {8, 10}, {8, 11}, {-1, 0}};

// Matches e_chair/func_us_801BEDD8
static bool func_us_801C3104(Entity* self) {
    s16 offsetX, offsetY;

    if (g_pads[0].pressed != PAD_UP) {
        return false;
    }

    offsetX = self->posX.i.hi - PLAYER.posX.i.hi;
    offsetY = self->posY.i.hi - PLAYER.posY.i.hi;

    if (offsetY > 4 || offsetY < -4) {
        return false;
    }

    if (offsetX > 4 || offsetX < -4) {
        return false;
    }

    return true;
}

// Shares some chunks of code with EntityChair, but appears to have some
// different sections Is likely the chair in the priest's room
void EntityChair(Entity* self) {
    s16 offsetX;
    Entity* entity;

    FntPrint("x:%02x,y:%02x\n", self->posX.i.hi, self->posY.i.hi);
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        if (self->params & 0xFF00) {
            entity = self + 1;
            if (self->params & 0x100) {
                CreateEntityFromCurrentEntity(E_ID(PRIEST), entity);
                entity->posX.i.hi = 176;
                entity->posY.i.hi = 128;
                entity->params = 0;
                if (Random() & 1) {
                    entity->params |= 0x100;
                }
                break;
            }
            if (self->params & 0x200) {
                CreateEntityFromCurrentEntity(E_ID(PRIEST), entity);
                entity->posX.i.hi = 64;
                entity->posY.i.hi = 128;
                entity->params = 1;
                if (Random() & 1) {
                    entity->params |= 0x100;
                }
            }
        }
        break;
    case 1:
        if (func_us_801C3104(self)) {
            g_Player.demo_timer = 10;
            g_Player.padSim = PAD_UP;
            g_Player.unk14 = self->params & 0xFF;
            self->step++;
        }
        break;
    case 2:
        g_Player.unk14 = self->params & 0xFF;
        offsetX = self->posX.i.hi - PLAYER.posX.i.hi;
        if (offsetX > 0) {
            PLAYER.posX.i.hi++;
        }
        if (offsetX < 0) {
            PLAYER.posX.i.hi--;
        }
        if (offsetX == 0) {
            self->step++;
        }
        break;
    case 3:
        g_Player.unk14 = self->params & 0xFF;
        if (PLAYER.poseTimer < 0) {
            if (self->params & 0xFF00) {
                entity = self + 1;
                if (entity->step == 1) {
                    entity->step++;
                }
            }
            self->step++;
        }
        if (PLAYER.step != 0 || PLAYER.step_s != 4) {
            self->step = 1;
        }
        break;
    case 4:
        g_Player.unk14 = self->params & 0xFF;
        if (PLAYER.step != 0 || PLAYER.step_s != 4) {
            self->step = 1;
        }
        break;
    }
    g_api.UpdateAnim(NULL, NULL);
}

// Matches e_chair/func_us_801B81E8
static void func_us_801B81E8(Entity* self) {
    if (self->ext.chair.unkEntity->step != 4) {
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(3);
        self->velocityY = FIX(-3.0 / 8.0);
        self->velocityX = FIX(0.25);
        if (self->facingLeft) {
            self->velocityX = -self->velocityX;
        }
        self->unk5A = 32;
        self->palette = PAL_OVL(PAL_STAGE_NAME_19F);
        self->anim = anim_1;
        self->pose = 0;
        self->poseTimer = 0;
        self->facingLeft = false;
        self->posY.i.hi -= 16;
        self->posX.val += self->velocityX << 5;
        break;

    case 1:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (self->poseTimer < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    g_api.UpdateAnim(NULL, NULL);
}
