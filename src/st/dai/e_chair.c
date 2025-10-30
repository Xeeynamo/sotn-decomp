// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

#define LEFT_CHAIR 0x100
#define RIGHT_CHAIR 0x200

enum ChairSteps {
    CHAIR_INIT = 0,
    CHAIR_DESTROY = 1,
    CHAIR_CHECK_SIT = 1,
    CHAIR_POSITION_PLAYER = 2,
    CHAIR_SEAT_PLAYER = 3,
    CHAIR_PLAYER_SITTING = 4,
};

#if defined(VERSION_PSP)
extern s32 E_ID(CONFESSIONAL_GHOST);
#endif

static AnimationFrame anim[] = {{8, 8}, {8, 9}, {8, 10}, {8, 11}, POSE_END};

static bool ChairSitCheck(Entity* self) {
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

void EntityChair(Entity* self) {
    s16 offsetX;
    Entity* confessionalGhost;

    FntPrint("x:%02x,y:%02x\n", self->posX.i.hi, self->posY.i.hi);

    switch (self->step) {
    case CHAIR_INIT:
        InitializeEntity(g_EInitCommon);
        // Each chair spawns the curtain on the opposing side, which anchors the
        // ghost
        if (self->params & 0xFF00) {
            confessionalGhost = self + 1;
            if (self->params & LEFT_CHAIR) {
                CreateEntityFromCurrentEntity(
                    E_ID(CONFESSIONAL_GHOST), confessionalGhost);
                confessionalGhost->posX.i.hi = 176;
                confessionalGhost->posY.i.hi = 128;
                confessionalGhost->params = CONFESSIONAL_GHOST_PRIEST;
                if (Random() & 1) {
                    confessionalGhost->params |= CONFESSIONAL_GHOST_BAD;
                }
                break;
            }
            if (self->params & RIGHT_CHAIR) {
                CreateEntityFromCurrentEntity(
                    E_ID(CONFESSIONAL_GHOST), confessionalGhost);
                confessionalGhost->posX.i.hi = 64;
                confessionalGhost->posY.i.hi = 128;
                confessionalGhost->params = CONFESSIONAL_GHOST_PARISHIONER;
                if (Random() & 1) {
                    confessionalGhost->params |= CONFESSIONAL_GHOST_BAD;
                }
            }
        }
        break;
    case CHAIR_CHECK_SIT:
        if (ChairSitCheck(self)) {
            g_Player.demo_timer = 10;
            g_Player.padSim = PAD_UP;
            g_Player.unk14 = self->params & 0xFF;
            self->step++;
        }
        break;
    case CHAIR_POSITION_PLAYER:
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
    case CHAIR_SEAT_PLAYER:
        g_Player.unk14 = self->params & 0xFF;
        if (PLAYER.poseTimer < 0) {
            if (self->params & 0xFF00) {
                confessionalGhost = self + 1;
                // Increments EntityConfessionalGhost to begin the seqence if it
                // hasn't run yet
                if (confessionalGhost->step == CONFESSIONAL_GHOST_READY) {
                    confessionalGhost->step++;
                }
            }
            self->step++;
        }
        if (PLAYER.step != Player_Stand ||
            PLAYER.step_s != Player_Stand_ChairSit) {
            self->step = CHAIR_CHECK_SIT;
        }
        break;
    case CHAIR_PLAYER_SITTING:
        g_Player.unk14 = self->params & 0xFF;
        if (PLAYER.step != Player_Stand ||
            PLAYER.step_s != Player_Stand_ChairSit) {
            self->step = CHAIR_CHECK_SIT;
        }
        break;
    }
    g_api.UpdateAnim(NULL, NULL);
}

// This function exists in dai, lib, and no1, but is completely unused
void func_us_801B81E8(Entity* self) {
    if (self->ext.chair.unkEntity->step != 4) {
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case CHAIR_INIT:
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(3);
        self->velocityY = FIX(-0.375);
        self->velocityX = FIX(0.25);
        if (self->facingLeft) {
            self->velocityX = -self->velocityX;
        }
        self->unk5A = 32;
        self->palette = PAL_FLAG(0x19F);
        self->anim = anim;
        self->pose = NULL;
        self->poseTimer = NULL;
        self->facingLeft = false;
        self->posY.i.hi -= 16;
        self->posX.val += self->velocityX << 5;
        break;

    case CHAIR_DESTROY:
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
