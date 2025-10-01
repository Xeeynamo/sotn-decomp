// SPDX-License-Identifier: AGPL-3.0-or-later

#ifdef STAGE_HAS_CONFESSIONAL
#define PARAMS params & 0xFF
#else
#define PARAMS params
#endif

enum ChairSteps {
    CHAIR_INIT = 0,
    CHAIR_DESTROY = 1,
    CHAIR_CHECK_SIT = 1,
    CHAIR_POSITION_PLAYER = 2,
    CHAIR_SEAT_PLAYER = 3,
    CHAIR_PLAYER_SITTING = 4,
};

#if defined(VERSION_PSP) && defined(STAGE_HAS_CONFESSIONAL)
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
#ifdef STAGE_HAS_CONFESSIONAL
    Entity* confessionalGhost;

    FntPrint("x:%02x,y:%02x\n", self->posX.i.hi, self->posY.i.hi);
#endif

    switch (self->step) {
    case CHAIR_INIT:
        InitializeEntity(g_EInitCommon);
#ifdef STAGE_HAS_CONFESSIONAL
        if (self->params & 0xFF00) {
            confessionalGhost = self + 1;
            // Left chair, params 0x513, spawns right curtain
            if (self->params & 0x100) {
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
            // Right chair, params 0x260, spawns left curtain
            if (self->params & 0x200) {
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
#endif
        break;
    case CHAIR_CHECK_SIT:
        if (ChairSitCheck(self)) {
            g_Player.demo_timer = 10;
            g_Player.padSim = PAD_UP;
            g_Player.unk14 = self->PARAMS;
            self->step++;
        }
        break;
    case CHAIR_POSITION_PLAYER:
        g_Player.unk14 = self->PARAMS;
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
        g_Player.unk14 = self->PARAMS;
        if (PLAYER.poseTimer < 0) {
#ifdef STAGE_HAS_CONFESSIONAL
            if (self->params & 0xFF00) {
                confessionalGhost = self + 1;
                // Increments EntityConfessionalGhost to begin the seqence if it
                // hasn't run yet
                if (confessionalGhost->step == CONFESSIONAL_GHOST_READY) {
                    confessionalGhost->step++;
                }
            }
#else
            self->ext.chair.unk0 = FLT(0.625);
#endif
            self->step++;
        }
        if (PLAYER.step != Player_Stand ||
            PLAYER.step_s != Player_Stand_ChairSit) {
            self->step = CHAIR_CHECK_SIT;
        }
        break;
    case CHAIR_PLAYER_SITTING:
        g_Player.unk14 = self->PARAMS;
        if (PLAYER.step != Player_Stand ||
            PLAYER.step_s != Player_Stand_ChairSit) {
            self->step = CHAIR_CHECK_SIT;
        }
        break;
    }
    g_api.UpdateAnim(NULL, NULL);

#ifdef CHAIR_DEBUG
    FntPrint("obj_step:%02x\n", self->step);
    FntPrint("pl_step:%02x,pl_step_s:%02x\n", PLAYER.step, PLAYER.step_s);
#endif
}

// This function exists in dai, lib, and no1, but is completely unused
// Best guess is that it applies to the destroyable table in BO0
void func_us_801B81E8(Entity* self) {
    if (self->ext.chair.unkEntity->step != 4) {
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case CHAIR_INIT:
        InitializeEntity(g_EInitCommon);
#ifdef STAGE_HAS_CONFESSIONAL
        self->animSet = ANIMSET_OVL(3);
#else
        self->animSet = ANIMSET_OVL(2);
#endif
        self->velocityY = FIX(-0.375);
        self->velocityX = FIX(0.25);
        if (self->facingLeft) {
            self->velocityX = -self->velocityX;
        }
        self->unk5A = 32;
        self->palette = PAL_OVL(0x19F);
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
