// SPDX-License-Identifier: AGPL-3.0-or-later
/*
 * Overlay: DRE
 * Enemy: Succubus Boss
 * ID: 0x19
 * BOSS ID: 9
 */

#include "dre.h"
#include "sfx.h"

typedef enum {
    /* 0 */ SUCCUBUS_INIT,
    /* 1 */ SUCCUBUS_CS_1,
    /* 2 */ SUCCUBUS_CS_2,
    /* 3 */ SUCCUBUS_CS_3,
    /* 4 */ SUCCUBUS_CS_4,
    /* 5 */ SUCCUBUS_IDLE,
    /* 7 */ SUCCUBUS_FLY = 7,
    /* 8 */ SUCCUBUS_PETAL_ATTACK,
    /* 9 */ SUCCUBUS_CHARGE,
    /* 11 */ SUCCUBUS_CLONE_ATTACK = 11,
    /* 12 */ SUCCUBUS_SPIKE_ATTACK,
    /* 13 */ SUCCUBUS_TAUNT,
    /* 14 */ SUCCUBUS_GET_HIT,
    /* 15 */ SUCCUBUS_FACE_PLAYER,
    /* 16 */ SUCCUBUS_NEXT_ACTION_CHECK,
    /* 18 */ SUCCUBUS_DYING = 18,
    /* 255 */ SUCCUBUS_DEBUG = 255,
} SuccubusSteps;

typedef enum {
    /* 0 */ SUCCUBUS_FLY_0,
    /* 1 */ SUCCUBUS_FLY_1,
    /* 2 */ SUCCUBUS_FLY_2,
} SuccubusFlySubSteps;

typedef enum {
    /* 0 */ SUCCUBUS_PETAL_ATTACK_SETUP,
    /* 1 */ SUCCUBUS_PETAL_ATTACK_ANIM,
    /* 2 */ SUCCUBUS_PETAL_ATTACK_CREATE_PETALS,
} SuccubusPetalAttackSubSteps;

typedef enum {
    /* 0 */ SUCCUBUS_CHARGE_SETUP,
    /* 1 */ SUCCUBUS_CHARGE_FLY_TOWARDS_PLAYER,
    /* 2 */ SUCCUBUS_CHARGE_AT_PLAYER_POSITION,
    /* 3 */ SUCCUBUS_CHARGE_DEAL_DAMAGE,
    /* 4 */ SUCCUBUS_CHARGE_FLY_AWAY,
    /* 5 */ SUCCUBUS_CHARGE_DECELERATE,
} SuccubusChargeSubSteps;

typedef enum {
    /* 0 */ SUCCUBUS_CLONE_ATTACK_ANIM_1,
    /* 1 */ SUCCUBUS_CLONE_ATTACK_CREATE_CLONES,
    /* 2 */ SUCCUBUS_CLONE_ATTACK_WAIT,
    /* 3 */ SUCCUBUS_CLONE_ATTACK_PLACE_REAL,
    /* 4 */ SUCCUBUS_CLONE_ATTACK_ANIM_2,
    /* 5 */ SUCCUBUS_CLONE_ATTACK_SET_SHOOTING,
    /* 6 */ SUCCUBUS_CLONE_ATTACK_STOP_SHOOTING,
    /* 7 */ SUCCUBUS_CLONE_ATTACK_SHOOT_PINKBALLS, // unused
} SuccubusCloneAttackSubSteps;

typedef enum {
    /* 0 */ SUCCUBUS_SPIKE_ATTACK_CREATE_SPIKES,
    /* 1 */ SUCCUBUS_SPIKE_ATTACK_1,
    /* 2 */ SUCCUBUS_SPIKE_ATTACK_2,
    /* 3 */ SUCCUBUS_SPIKE_ATTACK_3,
    /* 4 */ SUCCUBUS_SPIKE_ATTACK_4,
} SuccubusSpikeAttackSubSteps;

typedef enum {
    /* 0 */ SUCCUBUS_DYING_SETUP,
    /* 1 */ SUCCUBUS_DYING_FALL,
    /* 2 */ SUCCUBUS_DYING_LAND,
    /* 3 */ SUCCUBUS_DYING_ANIM_1,
    /* 4 */ SUCCUBUS_DYING_ANIM_2,
} SuccubusDyingSubSteps;

// Original name: multiple_count
extern s32 g_HeartDropArray; // clones counter

void EntitySuccubus(Entity* self) {
    u8* clonesShootOrder;
    s32 sideToPlayer;
    Entity* entity;
    s32 posX, posY;
    s8* hitbox;
    s32 facing;
    s16 angle;
    s32 temp;
    s32 i;

    FntPrint("multiple_count %x\n", g_HeartDropArray);

    if ((self->hitFlags & 3) && (self->step & SUCCUBUS_CS_1)) {
        SetStep(SUCCUBUS_GET_HIT);
    }

    if (self->flags & FLAG_DEAD) {
        if (self->step != SUCCUBUS_DYING) {
            self->hitboxState = 0;
            SetStep(SUCCUBUS_DYING);
        }
    }

    switch (self->step) {
    case SUCCUBUS_INIT:
        InitializeEntity(D_801804D0);
        self->animCurFrame = 82;
        SetStep(SUCCUBUS_CS_1);
        CreateEntityFromCurrentEntity(E_SUCCUBUS_WING_OVERLAY, &self[1]);

    case SUCCUBUS_CS_1: // Disguised as Lisa
        if (g_CastleFlags[SUCC_CS_DONE] || (g_DemoMode != Demo_None)) {
            self->facingLeft = 0;
            self->posX.i.hi = 416 - g_Tilemap.scrollX.i.hi;
            self->posY.i.hi = 175 - g_Tilemap.scrollY.i.hi;
            SetStep(SUCCUBUS_CS_4);
            self->step_s = 3;
        }
        self->animCurFrame = 82;
        if (g_CutsceneFlags & 4) {
            SetStep(SUCCUBUS_CS_2);
        }
        break;

    case SUCCUBUS_CS_2: // Disguised as Lisa
        if (D_801A3ED4 != 0) {
            SetSubStep(4);
        }
        switch (self->step_s) {
        case 0:
            AnimateEntity(D_8018079C, self);
            if (g_CutsceneFlags & 0x400) {
                SetSubStep(1);
            }
            break;

        case 1:
            AnimateEntity(D_801807AC, self);
            if (g_CutsceneFlags & 0x800) {
                self->animCurFrame = 84;
                SetSubStep(2);
            }
            break;

        case 2:
            if (g_CutsceneFlags & 0x1000) {
                SetSubStep(3);
            }
            break;

        case 3:
            self->animCurFrame = 83;
            if (g_CutsceneFlags & 0x2000) {
                SetSubStep(4);
            }
            break;

        case 4:
            self->animCurFrame = 84;
            if (g_CutsceneFlags & 0x20) {
                SetStep(SUCCUBUS_CS_3);
            }
            break;
        }
        break;

    // Sets Succubus in position
    case SUCCUBUS_CS_3:
        if ((D_801A3ED4 == 0) || (self->step_s == 0)) {
            switch (self->step_s) {
            case 0:
                self->facingLeft = 0;
                self->posX.i.hi = 416 - g_Tilemap.scrollX.i.hi;
                self->posY.i.hi = 175 - g_Tilemap.scrollY.i.hi;
                self->step_s++;

            case 1:
                AnimateEntity(D_8018066C, self);
                if (g_CutsceneFlags & 0x40) {
                    SetSubStep(2);
                }
                break;

            case 2:
                self->animCurFrame = 4;
                if (g_CutsceneFlags & 0x80) {
                    SetSubStep(3);
                }
                break;

            case 3:
                AnimateEntity(D_80180674, self);
                if (g_CutsceneFlags & 0x100) {
                    SetSubStep(4);
                }
                break;

            case 4:
                if (AnimateEntity(D_80180680, self) == 0) {
                    SetStep(SUCCUBUS_CS_4);
                }
                break;
            }
        } else {
            SetStep(SUCCUBUS_CS_4);
        }
        break;

    // Ascends Succubus into the air
    case SUCCUBUS_CS_4:
        switch (self->step_s) {
        case 0:
            if (AnimateEntity(D_80180694, self) == 0) {
                SetSubStep(1);
            }
            break;

        case 1:
            g_api.PlaySfx(MU_ENCHANTED_BANQUET);
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_SUCCUBUS_DEFEAT, TIMEATTACK_SET_VISITED);
            self->velocityX = 0;
            self->velocityY = FIX(-4);
            self->step_s++;

        case 2:
            MoveEntity();
            self->velocityY += FIX(0.125);
            if (self->velocityY > 0) {
                self->velocityY = 0;
            }
            if (AnimateEntity(D_801806A0, self) == 0) {
                SetStep(SUCCUBUS_IDLE);
            }
            break;

        case 3:
            AnimateEntity(D_80180694, self);
            if (GetDistanceToPlayerX() < 96) {
                SetSubStep(1);
            }
            break;
        }
        break;

    case SUCCUBUS_DYING:
        switch (self->step_s) {
        case SUCCUBUS_DYING_SETUP:
            PlaySfxPositional(NA_VO_SU_NO_SCREAM);
            CreateEntityFromCurrentEntity(
                E_SUCCUBUS_CUTSCENE, &g_Entities[200]);
            g_Entities[200].params = 1;
            g_HeartDropArray = 0;
            D_80180664 |= 2;
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_SUCCUBUS_DEFEAT, TIMEATTACK_SET_RECORD);
            self->velocityX = 0;
            self->velocityY = 0;
            posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            if (posY > 160) {
                self->velocityY = FIX(-2);
                self->step_s = 1;
            } else {
                self->step_s = 2;
            }
            break;

        case SUCCUBUS_DYING_FALL:
            AnimateEntity(D_80180768, self);
            MoveEntity();
            self->velocityY += FIX(0.125);
            if (self->velocityY > 0) {
                self->step_s = 2;
            }
            break;

        case SUCCUBUS_DYING_LAND:
            AnimateEntity(D_80180768, self);
            MoveEntity();
            self->velocityY += FIX(0.125);
            posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            if (posY >= 176) {
                PlaySfxPositional(SFX_STOMP_HARD_A);
                self->posY.i.hi = 175 - g_Tilemap.scrollY.i.hi;
                SetSubStep(SUCCUBUS_DYING_ANIM_1);
                posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
                if (posX < 80) {
                    D_801816C4 = self->facingLeft = 1;
                } else if (posX > 432) {
                    D_801816C4 = self->facingLeft = 0;
                } else {
                    D_801816C4 = self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                }
                g_CutsceneFlags |= 2;
            }
            break;

        case SUCCUBUS_DYING_ANIM_1:
            AnimateEntity(D_80180770, self);
            if (g_CutsceneFlags & 0x10) {
                SetSubStep(SUCCUBUS_DYING_ANIM_2);
            }
            break;

        case SUCCUBUS_DYING_ANIM_2:
            AnimateEntity(D_80180778, self);
        }
        break;

    case SUCCUBUS_IDLE:
        if (self->step_s == 0) {
            self->ext.succubus.timer = 64;
            self->step_s++;
        }

        AnimateEntity(D_801806C4, self);
        if ((self->animFrameIdx == 3) && (self->animFrameDuration == 0)) {
            PlaySfxPositional(SFX_BOSS_WING_FLAP);
        }

        posY = self->posY.i.hi - self->ext.succubus.yOffset;
        if (posY > 8) {
            self->velocityY = FIX(-0.75);
        }

        if (--self->ext.succubus.timer == 0) {
            self->ext.succubus.nextStep = SUCCUBUS_FLY;
            SetStep(SUCCUBUS_FACE_PLAYER);
        }
        if ((self->ext.succubus.timer < 80) && (GetDistanceToPlayerX() < 80)) {
            self->ext.succubus.nextStep = SUCCUBUS_FLY;
            SetStep(SUCCUBUS_FACE_PLAYER);
        }
        break;

    case SUCCUBUS_FLY:
        switch (self->step_s) {
        case SUCCUBUS_FLY_0:
            self->velocityY = 0;
            self->ext.succubus.timer = (Random() & 31) + 32;
            self->ext.succubus.nextAttack = SUCCUBUS_PETAL_ATTACK;
            self->ext.succubus.yOffset = 88;
            if (!(Random() % 4)) {
                if (Random() % 2) {
                    self->ext.succubus.nextAttack = SUCCUBUS_SPIKE_ATTACK;
                    self->ext.succubus.yOffset = 120;
                } else {
                    self->ext.succubus.nextAttack = SUCCUBUS_CLONE_ATTACK;
                }
            }
            self->ext.succubus.facingLeft = 0;
            self->step_s++;

        case SUCCUBUS_FLY_1:
            AnimateEntity(D_801806E8, self);
            if ((self->animFrameIdx == 3) && (self->animFrameDuration == 0)) {
                PlaySfxPositional(SFX_BOSS_WING_FLAP);
            }

            MoveEntity();
            posY = self->posY.i.hi - self->ext.succubus.yOffset;
            if (posY > 8) {
                self->velocityY = FIX(-0.75);
            }
            if (posY < -8) {
                self->velocityY = FIX(0.75);
            }

            if (self->facingLeft != self->ext.succubus.facingLeft) {
                self->velocityX += FIX(0.09375);
                if (self->velocityX >= FIX(1.375)) {
                    self->velocityX = FIX(1.375);
                }
            } else {
                self->velocityX -= FIX(0.09375);
                if (self->velocityX <= FIX(-1.375)) {
                    self->velocityX = FIX(-1.375);
                }
            }

            if (self->ext.succubus.nextAttack == SUCCUBUS_CLONE_ATTACK) {
                posX = 64;
            } else {
                posX = 96;
            }

            temp = GetDistanceToPlayerX();
            if (self->ext.succubus.facingLeft == 0) {
                if (temp < posX) {
                    self->ext.succubus.facingLeft ^= 1;
                }
                if (self->ext.succubus.facingLeft != 0) {
                    if (posX < temp) {
                        self->ext.succubus.facingLeft ^= 1;
                    }
                }
            } else if (posX < temp) {
                self->ext.succubus.facingLeft ^= 1;
            }

            sideToPlayer = ((GetSideToPlayer() & 1) ^ 1);
            if (self->facingLeft != sideToPlayer) {
                if (temp > 16) {
                    self->ext.succubus.nextStep = SUCCUBUS_CLONE_ATTACK;
                    SetStep(SUCCUBUS_NEXT_ACTION_CHECK);
                }
            }

            posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            if (self->facingLeft != 0) {
                posX = 512 - posX;
            }
            if (posX > 416) {
                self->ext.succubus.facingLeft = 0;
                self->ext.succubus.timer = 96;
                self->step_s++;
            }

            if (self->ext.succubus.timer == 0) {
                if (GetDistanceToPlayerX() < 96) {
                    if (self->ext.succubus.nextAttack ==
                        SUCCUBUS_PETAL_ATTACK) {
                        SetStep(SUCCUBUS_PETAL_ATTACK);
                    } else {
                        self->ext.succubus.nextStep =
                            self->ext.succubus.nextAttack;
                        SetStep(SUCCUBUS_NEXT_ACTION_CHECK);
                    }
                }
            } else {
                self->ext.succubus.timer--;
            }
            break;

        case SUCCUBUS_FLY_2:
            if (self->facingLeft != self->ext.succubus.facingLeft) {
                self->velocityX += FIX(0.09375);
                if (self->velocityX >= FIX(1.375)) {
                    self->velocityX = FIX(1.375);
                }
            } else {
                self->velocityX -= FIX(0.09375);
                if (self->velocityX <= FIX(-1.375)) {
                    self->velocityX = FIX(-1.375);
                }
            }
            AnimateEntity(D_801806E8, self);
            if ((self->animFrameIdx == 3) && (self->animFrameDuration == 0)) {
                PlaySfxPositional(SFX_BOSS_WING_FLAP);
            }
            MoveEntity();
            if (--self->ext.succubus.timer == 0) {
                self->step_s = 0;
            }
            break;
        }
        break;

    case SUCCUBUS_FACE_PLAYER:
        if (self->step_s == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;
        }

        if (AnimateEntity(D_801806D4, self) == 0) {
            if (self->ext.succubus.nextStep != 0) {
                SetStep(self->ext.succubus.nextStep);
                self->ext.succubus.nextStep = 0;
            } else {
                SetStep(SUCCUBUS_FLY);
            }
        }
        break;

    case SUCCUBUS_NEXT_ACTION_CHECK:
        if (AnimateEntity(D_801806F8, self) == 0) {
            if (self->ext.succubus.nextStep != 0) {
                SetStep(self->ext.succubus.nextStep);
                self->ext.succubus.nextStep = 0;
            } else {
                SetStep(SUCCUBUS_IDLE);
            }
        }
        break;

    case SUCCUBUS_PETAL_ATTACK:
        switch (self->step_s) {
        case SUCCUBUS_PETAL_ATTACK_SETUP:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (g_Player.unk0C & PLAYER_STATUS_CURSE) {
                self->ext.succubus.unk87 = false;
            } else {
                self->ext.succubus.unk87 = true;
            }
            D_80180668 = 0;
            self->step_s++;

        case SUCCUBUS_PETAL_ATTACK_ANIM:
            if (AnimateEntity(D_8018070C, self) == 0) {
                self->ext.succubus.timer = 128;
                PlaySfxPositional(NA_VO_SU_LAUGH);
                self->step_s++;
            }
            break;

        case SUCCUBUS_PETAL_ATTACK_CREATE_PETALS:
            if (!(self->ext.succubus.timer & 1)) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_SUCCUBUS_PETAL, self, entity);
                    entity->facingLeft = self->facingLeft;
                    entity->zPriority = self->zPriority - 1;
                }
            }
            if ((self->ext.succubus.timer % 64) == 0) {
                PlaySfxPositional(SFX_GLASS_SHARDS);
            }
            if (--self->ext.succubus.timer == 0) {
                SetStep(SUCCUBUS_FLY);
            }
            if (self->ext.succubus.unk87) {
                if (g_Player.unk0C & PLAYER_STATUS_CURSE) {
                    SetStep(SUCCUBUS_CHARGE);
                }
            } else if (D_80180668 != 0) {
                if (GetDistanceToPlayerX() > 72) {
                    self->ext.succubus.nextStep = SUCCUBUS_TAUNT;
                    SetStep(SUCCUBUS_FACE_PLAYER);
                }
            }
            break;
        }
        break;

    case SUCCUBUS_CHARGE:
        switch (self->step_s) {
        case SUCCUBUS_CHARGE_SETUP:
            self->ext.succubus.timer = 112;
            self->animCurFrame = 36;
            PlaySfxPositional(NA_VO_SU_BLANK);
            self->step_s++;

        case SUCCUBUS_CHARGE_FLY_TOWARDS_PLAYER:
            entity = &PLAYER;
            posX = entity->posX.i.hi - self->posX.i.hi;
            if (self->facingLeft != 0) {
                posX -= 16;
            } else {
                posX += 16;
            }
            posY = entity->posY.i.hi - self->posY.i.hi;

            angle = ratan2(posY, posX);
            self->velocityX = (rcos(angle) << 0x11) >> 0xC;
            self->velocityY = (rsin(angle) << 0x11) >> 0xC;
            posX = self->velocityX;

            if (self->facingLeft != 0) {
                posX = -posX;
            }
            if (posX > 0) {
                self->velocityX = 0;
            }

            MoveEntity();

            posX = PLAYER.posX.i.hi - self->posX.i.hi;
            if (self->facingLeft == 0) {
                posX = -posX;
            }
            posX -= 4;
            if (posX < 0) {
                posX = 512;
            }
            posY = PLAYER.posY.i.hi - self->posY.i.hi;
            if (posY < 0) {
                posY = -posY;
            }

            if (!(g_Player.unk0C & 0x010401A2)) {
                if ((posY < 12) && (posX < 24)) {
                    g_Player.unk60 = 1;
                    g_Player.unk64 = 0;
                    g_Player.unk62 = 0;
                    self->hitboxState = 0;
                    self->step_s++;
                }
            } else {
                FntPrint("ng status\n");
            }

            posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            if (posY > 176) {
                self->posY.i.hi = 176 - g_Tilemap.scrollY.i.hi;
            }

            if (g_Player.unk60 == 0) {
                if (--self->ext.succubus.timer == 0) {
                    self->ext.succubus.unk87 = false;
                    SetStep(SUCCUBUS_FLY);
                }
            }
            break;

        case SUCCUBUS_CHARGE_AT_PLAYER_POSITION:
            entity = &PLAYER;
            posX = entity->posX.i.hi;
            if (self->facingLeft != 0) {
                posX -= 16;
            } else {
                posX += 16;
            }
            self->posY.i.hi = posY = entity->posY.i.hi;
            self->posX.i.hi = posX;
            PlaySfxPositional(NA_VO_SU_SUCK_YOU_DRY);
            self->step_s++;

        case SUCCUBUS_CHARGE_DEAL_DAMAGE:
            if (AnimateEntity(D_8018071C, self) == 0) {
                g_Player.unk64 = g_api.enemyDefs[347].attack;
                g_Player.unk60 = 3;
                self->ext.succubus.timer = 48;
                self->step_s++;
            }
            break;

        case SUCCUBUS_CHARGE_FLY_AWAY:
            if (--self->ext.succubus.timer == 0) {
                g_Player.unk60 = 0;
                self->hitboxState = 3;
                if (self->facingLeft != 0) {
                    self->velocityX = FIX(-4);
                } else {
                    self->velocityX = FIX(4);
                }
                self->velocityY = FIX(-4);
                self->animCurFrame = 47;
                self->ext.succubus.timer = 24;
                self->step_s++;
            }
            break;

        case SUCCUBUS_CHARGE_DECELERATE:
            MoveEntity();
            self->velocityX -= self->velocityX >> 5;
            self->velocityY -= self->velocityY >> 5;
            if (--self->ext.succubus.timer == 0) {
                SetStep(SUCCUBUS_TAUNT);
            }
            break;
        }
        break;

    case SUCCUBUS_TAUNT:
        if (self->step_s == 0) {
            self->ext.succubus.timer = 80;
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;
            if (self->ext.succubus.unk87) {
                PlaySfxPositional(NA_VO_SU_DELICIOUS);
            } else {
                PlaySfxPositional(NA_VO_SU_LAUGH);
            }
            self->ext.succubus.unk87 = false;
        }
        AnimateEntity(D_8018072C, self);
        if ((--self->ext.succubus.timer == 0) ||
            (GetDistanceToPlayerX() < 32)) {
            SetStep(SUCCUBUS_FLY);
        }
        break;

    case SUCCUBUS_CLONE_ATTACK:
        switch (self->step_s) {
        case SUCCUBUS_CLONE_ATTACK_CREATE_CLONES:
            posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            posX -= 192;

            // left bound limit
            if (posX < 32) {
                posX = 96 - ((32 - posX) % 64);
            }

            // right bound limit
            temp = posX + 384;
            if (temp > 480) {
                posX = ((posX - 96) % 64) + 32;
            }

            clonesShootOrder = *g_CloneShootOrder;
            temp = Random() & 3;
            clonesShootOrder += temp * 7;

            entity = &g_Entities[112];
            temp = self->posX.i.hi + g_Tilemap.scrollX.i.hi;

            for (i = 0; i < 6; i++, entity++, clonesShootOrder++, posX += 64) {
                CreateEntityFromEntity(E_SUCCUBUS_CLONE, self, entity);
                // Giving each clone a pointer to the real Succubus
                entity->ext.succubus.real = self;
                if (posX == temp) {
                    posX += 64;
                }
                entity->ext.succubus.clonePosX = posX;
                entity->params = *clonesShootOrder;
            }
            self->params = *clonesShootOrder;
            self->ext.succubus.timer = 64;
            self->hitboxState = 0;
            g_HeartDropArray = 6;
            PlaySfxPositional(NA_VO_SU_GRUNT_1);
            PlaySfxPositional(NA_SE_SU_CREATE_CLONES);
            self->step_s++;

        case SUCCUBUS_CLONE_ATTACK_WAIT:
            if (--self->ext.succubus.timer == 0) {
                self->step_s = 3;
            }

        case SUCCUBUS_CLONE_ATTACK_ANIM_1:
            self->ext.succubus.unk85 = false;
            AnimateEntity(D_80180734, self);
            if ((self->animFrameIdx == 4) && (self->animFrameDuration == 0)) {
                self->step_s++;
            }
            break;

        case SUCCUBUS_CLONE_ATTACK_PLACE_REAL:
            entity = &g_Entities[112];
            temp = Random() % 6;
            entity += temp;

            posX = entity->posX.i.hi;
            posY = entity->posY.i.hi;
            entity->posX.i.hi = self->posX.i.hi;
            entity->posY.i.hi = self->posY.i.hi;
            self->posX.i.hi = posX;
            self->posY.i.hi = posY;
            self->hitboxState = 3;
            self->step_s++;

        case SUCCUBUS_CLONE_ATTACK_ANIM_2:
            if (AnimateEntity(D_80180734, self) == 0) {
                SetSubStep(SUCCUBUS_CLONE_ATTACK_SET_SHOOTING);
            }
            break;

        case SUCCUBUS_CLONE_ATTACK_SET_SHOOTING:
            if (AnimateEntity(D_80180760, self) == 0) {
                self->ext.succubus.unk85 = true;
                // PinkBall attack delay set
                self->ext.succubus.timer = (self->params * 48) + 1;
                SetSubStep(SUCCUBUS_CLONE_ATTACK_STOP_SHOOTING);
            }
            break;

        case SUCCUBUS_CLONE_ATTACK_STOP_SHOOTING:
            self->animCurFrame = 26;
            if (--self->ext.succubus.timer == 0) {
                self->ext.succubus.unk85 = false;
                /*! @bug: Likely a typo meant to be
                 * SetSubStep(SUCCUBUS_CLONE_ATTACK_SHOOT_PINKBALLS);
                 * case SUCCUBUS_CLONE_ATTACK_SHOOT_PINKBALLS is
                 * inaccessible causing the real Succubus to be
                 * unable to do the PinkBall attack.
                 */
                SetSubStep(SUCCUBUS_CLONE_ATTACK_STOP_SHOOTING);
            }
            if (g_HeartDropArray == 0) {
                SetStep(SUCCUBUS_IDLE);
            }
            break;

        /* Unused: see @bug in previous case.
         * The real Succubus was supposed to shoot last, hinting
         * the player her real position, but the end result is
         * she doesn't shoot at all.
         */
        case SUCCUBUS_CLONE_ATTACK_SHOOT_PINKBALLS:
            if (AnimateEntity(D_80180780, self) == 0) {
                self->ext.succubus.timer = 288;
                SetSubStep(SUCCUBUS_CLONE_ATTACK_ANIM_2);
            }
            if ((self->animFrameIdx == 4) && (self->animFrameDuration == 0)) {
                PlaySfxPositional(NA_SE_SU_CHARGE_PINKBALLS);

                for (i = 0; i < 2; i++) {
                    entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                    if (entity != NULL) {
                        CreateEntityFromEntity(
                            E_SUCCUBUS_PINK_BALL_PROJECTILE, self, entity);
                        entity->params = i;
                        if (i != 0) {
                            entity->posX.i.hi -= 2;
                        } else {
                            entity->posX.i.hi += 2;
                        }
                        entity->ext.succubus.real = self;
                        entity->posY.i.hi -= 13;
                        entity->zPriority = self->zPriority + 1;
                    }
                }
            }
            if ((self->animFrameIdx == 5) && (self->animFrameDuration == 0)) {
                PlaySfxPositional(NA_VO_SU_GRUNT_2);
                PlaySfxPositional(NA_VO_SU_CRYSTAL_1);
                PlaySfxPositional(SFX_FIRE_SHOT);
                self->ext.succubus.unk85 = true;
            }
            break;
        }
        break;

    case SUCCUBUS_SPIKE_ATTACK:
        switch (self->step_s) {
        case SUCCUBUS_SPIKE_ATTACK_CREATE_SPIKES:
            entity = &g_Entities[96];
            self->facingLeft = 0;
            self->ext.succubus.unk85 = false;
            D_80180668 = 0;
            for (facing = 0; facing < 2; facing++) {
                for (i = 0; i < 4; i++, entity += 2) {
                    CreateEntityFromEntity(E_SUCCUBUS_WING_SPIKE, self, entity);
                    entity->params = i;
                    entity->zPriority = self->zPriority;
                    entity->ext.succubus.real = self;
                    if (facing == 0) {
                        entity->posX.i.hi -= 5;
                    } else {
                        entity->posX.i.hi += 4;
                    }
                    entity->posY.i.hi -= 27;
                    entity->facingLeft = facing;
                }
            }
            self->step_s++;

        case SUCCUBUS_SPIKE_ATTACK_1:
            if (AnimateEntity(D_80180748, self) == 0) {
                self->ext.succubus.unk85 = true;
                PlaySfxPositional(SFX_GUARD_TINK);
                PlaySfxPositional(NA_VO_SU_GRUNT_3);
                self->ext.succubus.timer = 64;
                SetSubStep(2);
            }
            break;

        case SUCCUBUS_SPIKE_ATTACK_2:
            if (--self->ext.succubus.timer == 0) {
                self->ext.succubus.unk85 = false;
                self->ext.succubus.timer = 64;
                self->step_s++;
            }
            break;

        case SUCCUBUS_SPIKE_ATTACK_3:
            if (--self->ext.succubus.timer == 0) {
                self->step_s++;
            }
            break;

        case SUCCUBUS_SPIKE_ATTACK_4:
            if (AnimateEntity(D_80180760, self) == 0) {
                SetStep(SUCCUBUS_IDLE);
            }
            if (D_80180668 != 0) {
                if (GetDistanceToPlayerX() > 64) {
                    self->ext.succubus.nextStep = SUCCUBUS_TAUNT;
                    SetStep(SUCCUBUS_FACE_PLAYER);
                }
            }
            break;
        }
        break;

    case SUCCUBUS_GET_HIT:
        if (self->step_s == 0) {
            if (Random() % 2) {
                PlaySfxPositional(NA_VO_SU_HURT_1);
            } else {
                PlaySfxPositional(NA_VO_SU_HURT_2);
            }

            self->ext.succubus.timer = 32;
            g_HeartDropArray = 0;
            if (GetSideToPlayer() & 1) {
                self->velocityX = FIX(2);
            } else {
                self->velocityX = FIX(-2);
            }
            self->velocityY = FIX(-2);
            self->step_s++;
        }
        AnimateEntity(D_80180768, self);
        MoveEntity();
        self->velocityX -= self->velocityX >> 5;
        self->velocityY -= self->velocityY >> 5;
        self->velocityY += FIX(0.0625);
        if (--self->ext.succubus.timer == 0) {
            if (Random() % 2) {
                self->ext.succubus.nextStep = SUCCUBUS_SPIKE_ATTACK;
            } else {
                self->ext.succubus.nextStep = SUCCUBUS_CLONE_ATTACK;
            }
            SetStep(SUCCUBUS_NEXT_ACTION_CHECK);
        }
        break;

    case SUCCUBUS_DEBUG:
        /**
         * Debug: Press SQUARE / CIRCLE on the second controller
         * to advance/rewind current animation frame
         */
        FntPrint("charal %x\n", self->animCurFrame);
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (self->params == 0) {
                self->animCurFrame++;
                self->params |= 1;
            } else {
                break;
            }
        } else {
            self->params = 0;
        }
        if (g_pads[1].pressed & PAD_CIRCLE) {
            if (self->step_s == 0) {
                self->animCurFrame--;
                self->step_s |= 1;
            }
        } else {
            self->step_s = 0;
        }
        break;
    }
    posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
    posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;

    if (self->velocityX < 0) {
        if (posX < 40) {
            self->posX.i.hi = 40 - g_Tilemap.scrollX.i.hi;
        }
    } else if (posX > 480) {
        self->posX.i.hi = 480 - g_Tilemap.scrollX.i.hi;
    }
    if ((self->velocityY < 0) && (posY < 48)) {
        self->posY.i.hi = 48 - g_Tilemap.scrollY.i.hi;
    }
    // TODO: !FAKE
    hitbox = (s8*)&D_80180830[self->animCurFrame][D_801807F8];
    hitbox--;
    hitbox++;
    self->hitboxOffX = *hitbox++;
    self->hitboxOffY = *hitbox++;
    self->hitboxWidth = hitbox[0];
    self->hitboxHeight = hitbox[1];
}

void EntitySuccubusPetal(Entity* self) {
    Entity* newEntity;
    s32 temp_s2;
    s16 angle;

    if (D_80180664 & 2) {
        self->flags |= FLAG_DEAD;
    }
    if (self->hitFlags & 0x80) {
        D_80180668 = 1;
    }

    if (self->flags & FLAG_DEAD) {
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->params = 0;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_801804DC);
        self->drawFlags = FLAG_DRAW_ROTZ;
        self->rotZ = rand() & 0xFFF;
        temp_s2 = Random() & 3;
        if (temp_s2 >= 3) {
            temp_s2 = 0;
        }
        self->animCurFrame = temp_s2 + 64;

        angle = ((Random() & 0x1F) * 16) + 0xC0;
        if (self->facingLeft == 0) {
            angle = 0x800 - angle;
        } else {
            angle = angle;
        }
        temp_s2 = ((rand() * 4) + 0x38000) >> 0xC;
        self->velocityX = temp_s2 * rcos(angle);
        self->velocityY = temp_s2 * rsin(angle);
        self->ext.succubus.timer = (Random() & 31) + 16;

    case 1:
        self->velocityX = self->velocityX - (self->velocityX >> 6);
        self->velocityY = self->velocityY - (self->velocityY >> 6);
        MoveEntity();
        if (--self->ext.succubus.timer == 0) {
            self->ext.succubus.timer = (Random() & 31) + 32;
            self->step++;
        }
        break;

    case 2:
        MoveEntity();
        self->rotZ += self->ext.succubus.timer;
        break;
    }
}

// Wings that appear over the player when the succubus does her charge attack
void EntitySuccubusWingOverlay(Entity* entity) {
    if (entity->step == 0) {
        InitializeEntity(D_801804E8);
    }

    entity->posX.i.hi = entity[-1].posX.i.hi;
    entity->animCurFrame = 0;
    entity->posY.i.hi = entity[-1].posY.i.hi;
    entity->facingLeft = entity[-1].facingLeft;

    if (entity[-1].animCurFrame == 50) {
        entity->animCurFrame = 62;
    }

    if (entity[-1].animCurFrame == 51) {
        entity->animCurFrame = 63;
    }

    entity->zPriority = PLAYER.zPriority + 4;
}

extern s32 g_HeartDropArray; // clones counter

void EntitySuccubusClone(Entity* self) {
    Entity* newEntity;
    s8* hitbox;
    s32 velX;
    s32 i;

    if (g_HeartDropArray == 0) {
        self->flags |= FLAG_DEAD;
    }

    if (self->flags & FLAG_DEAD) {
        if (self->step != 5) {
            if (g_HeartDropArray != 0) {
                g_HeartDropArray--;
            }
            self->hitboxState = 0;
            self->flags |= FLAG_DEAD;
            g_api.PlaySfxVolPan(0x6D9, 0x54, 0);
            SetStep(5);
        }
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_801804F4);
        self->hitboxState = 0;
        velX = self->ext.succubus.clonePosX -
                   (self->posX.i.hi + g_Tilemap.scrollX.i.hi)
               << 0x10;
        if (velX < 0) {
            velX += 0x3F;
        }
        self->velocityX = velX >> 6;
        self->ext.succubus.timer = 64;

    case 1:
        MoveEntity();
        newEntity = self->ext.succubus.real;
        self->animCurFrame = newEntity->animCurFrame;
        self->facingLeft = newEntity->facingLeft;
        if (--self->ext.succubus.timer == 0) {
            self->hitboxState = 3;
            SetStep(2);
        }
        break;

    case 2:
        newEntity = self->ext.succubus.real;
        self->animCurFrame = newEntity->animCurFrame;
        self->facingLeft = newEntity->facingLeft;
        if (newEntity->ext.succubus.unk85 != 0) {
            self->ext.succubus.timer = (self->params * 48) + 1;
            SetStep(3);
        }
        break;

    case 3:
        self->animCurFrame = 26;
        if (--self->ext.succubus.timer == 0) {
            SetStep(4);
        }
        break;

    case 4:
        if (self->step_s == 0) {
            self->ext.succubus.unk85 = 0;
            self->step_s++;
        }

        if (AnimateEntity(D_80180780, self) == 0) {
            self->ext.succubus.timer = 288;
            SetStep(3);
        }

        if (self->animFrameIdx == 4 && self->animFrameDuration == 0) {
            PlaySfxPositional(0x6E2);
            for (i = 0; i < 2; i++) {
                newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(
                        E_SUCCUBUS_PINK_BALL_PROJECTILE, self, newEntity);
                    newEntity->params = i;
                    if (i != 0) {
                        newEntity->posX.i.hi -= 2;
                    } else {
                        newEntity->posX.i.hi += 2;
                    }
                    newEntity->ext.succubus.real = self;
                    newEntity->posY.i.hi -= 10;
                    newEntity->zPriority = self->zPriority + 1;
                }
            }
        }
        if (self->animFrameIdx == 5 && self->animFrameDuration == 0) {
            PlaySfxPositional(NA_VO_SU_GRUNT_2);
            PlaySfxPositional(NA_VO_SU_CRYSTAL_1);
            PlaySfxPositional(SFX_FIRE_SHOT);
            self->ext.succubus.unk85 = 1;
        }
        break;

    case 5:
        if (self->step_s == 0) {
            self->ext.succubus.timer = 32;
            self->step_s++;
        }
        if (self->ext.succubus.timer & 1) {
            self->animSet = ANIMSET_DRA(0);
        } else {
            self->animSet = ANIMSET_OVL(1);
        }
        if (--self->ext.succubus.timer == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    hitbox = &D_80180830[self->animCurFrame][D_801807F8];
    hitbox--;
    hitbox++;
    self->hitboxOffX = *hitbox++;
    self->hitboxOffY = *hitbox++;
    self->hitboxWidth = hitbox[0];
    self->hitboxHeight = hitbox[1];
}

// Pink ball projectile shot by succubus duplicates ID 0x1D
void EntityPinkBallProjectile(Entity* self) {
    Entity* entity;
    s16 temp_s0;
    s16 temp_v0;

    if (D_80180664 & 2) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180500);
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
        self->rotY = 0;
        self->rotX = 0;

    case 1:
        self->rotX = self->rotY += 4;
        if (self->rotX > 256) {
            self->drawFlags = FLAG_DRAW_DEFAULT;
        }
        AnimateEntity(D_80180794, self);

        entity = self->ext.succubus.real;
        if (entity->ext.succubus.unk85 != 0) {
            self->drawFlags = FLAG_DRAW_DEFAULT;
            self->step++;
        }
        if (entity->flags & FLAG_DEAD) {
            DestroyEntity(self);
        }
        break;

    case 2:
        temp_s0 = (self->params << 10) + 0x200;
        self->velocityX = rcos(temp_s0) * 0x38;
        self->velocityY = rsin(temp_s0) * 0x38;
        self->ext.succubus.unkA2 = temp_s0;
        self->ext.succubus.timer = 128;
        self->step++;

    case 3:
        AnimateEntity(D_80180794, self);
        MoveEntity();
        temp_v0 = GetAngleBetweenEntities(self, g_Entities);
        temp_s0 = GetNormalizedAngle(0x10, self->ext.succubus.unkA2, temp_v0);
        self->velocityX = rcos(temp_s0) * 0x38;
        self->velocityY = rsin(temp_s0) * 0x38;
        self->ext.succubus.unkA2 = temp_s0;

        if (self->hitFlags & 0x80) {
            self->step = 4;
        }

        if (--self->ext.succubus.timer == 0) {
            self->step = 4;
        }
        break;

    case 4:
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
        AnimateEntity(D_80180794, self);
        MoveEntity();
        break;
    }
}

// Extending wing spike from succubus ID 0x1E
void EntitySuccubusWingSpike(Entity* self) {
    s32 temp_s2;
    s16 var_s0;

    if (D_80180664 & 2) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_801804E8);
        self->drawFlags = FLAG_DRAW_ROTZ;
        self->animCurFrame = 0;
        var_s0 = D_801807F0[self->params];
        self->rotZ = var_s0;
        self->drawFlags |= FLAG_DRAW_ROTX;
        self->rotX = 0x100;
        CreateEntityFromEntity(E_SUCCUBUS_WING_SPIKE_TIP, self, &self[1]);
        self[1].facingLeft = self->facingLeft;
        self[1].params = self->params;
        self[1].rotZ = self->rotZ;

    case 1:
        if (self->ext.succubus.real->ext.succubus.unk85 != 0) {
            self->step++;
        }
        break;

    case 2:
        self->animCurFrame = 85;
        self->rotX += 0x40;
        if (self->rotX > 0x600) {
            self->rotX = 0x600;
        }

        if (self->ext.succubus.real->ext.succubus.unk85 == 0) {
            self->step++;
        }
        break;

    case 3:
        self->rotX -= 0x40;
        if (self->rotX < 0x100) {
            DestroyEntity(self);
            return;
        }
    }

    var_s0 = self->rotZ;
    temp_s2 = (self->rotX * 0xB) >> 6;
    if (self->facingLeft == 0) {
        var_s0 = 0x800 - var_s0;
    }

    self[1].posX.i.hi = self->posX.i.hi;
    self[1].posY.i.hi = self->posY.i.hi;
    self[1].posX.i.hi += temp_s2 * rcos(var_s0) >> 0xC;
    self[1].posY.i.hi -= temp_s2 * rsin(var_s0) >> 0xC;
}

void EntitySuccubusWingSpikeTip(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(D_8018050C);
        self->animCurFrame = 0;
        self->drawFlags = FLAG_DRAW_ROTZ;
        self->hitboxState = 0;

    case 1:
        if (self[-1].animCurFrame != 0) {
            self->hitboxState = 1;
            self->animCurFrame = 86;
        }
        if (self->hitFlags != 0) {
            D_80180668 = 1;
        }
        if (self[-1].entityId != 0x1E) {
            DestroyEntity(self);
        }
    }
}
