/*
 * Overlay: DRE
 * Enemy: Succubus Boss
 * ID: 0x19
 * BOSS ID: 9
 */

#include "dre.h"

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
extern s32 D_80180660; // clones counter

void EntitySuccubus(Entity* self) {
    const int SeenCutscene = 212;
    u8* clonesShootOrder;
    s32 sideToPlayer;
    Entity* entity;
    s32 posX, posY;
    s8* hitbox;
    s32 facing;
    s16 angle;
    s32 temp;
    s32 i;

    FntPrint("multiple_count %x\n", D_80180660);

    if ((self->hitFlags & 3) && (self->step & SUCCUBUS_CS_1)) {
        SetStep(SUCCUBUS_GET_HIT);
    }

    if (self->flags & 0x100) {
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
        if (D_8003BDEC[SeenCutscene] || (g_DemoMode != Demo_None)) {
            self->facing = 0;
            self->posX.i.hi = 416 - g_Camera.posX.i.hi;
            self->posY.i.hi = 175 - g_Camera.posY.i.hi;
            SetStep(SUCCUBUS_CS_4);
            self->step_s = 3;
        }
        self->animCurFrame = 82;
        if (D_801A3F84 & 4) {
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
            if (D_801A3F84 & 0x400) {
                SetSubStep(1);
            }
            break;

        case 1:
            AnimateEntity(D_801807AC, self);
            if (D_801A3F84 & 0x800) {
                self->animCurFrame = 84;
                SetSubStep(2);
            }
            break;

        case 2:
            if (D_801A3F84 & 0x1000) {
                SetSubStep(3);
            }
            break;

        case 3:
            self->animCurFrame = 83;
            if (D_801A3F84 & 0x2000) {
                SetSubStep(4);
            }
            break;

        case 4:
            self->animCurFrame = 84;
            if (D_801A3F84 & 0x20) {
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
                self->facing = 0;
                self->posX.i.hi = 416 - g_Camera.posX.i.hi;
                self->posY.i.hi = 175 - g_Camera.posY.i.hi;
                self->step_s++;

            case 1:
                AnimateEntity(D_8018066C, self);
                if (D_801A3F84 & 0x40) {
                    SetSubStep(2);
                }
                break;

            case 2:
                self->animCurFrame = 4;
                if (D_801A3F84 & 0x80) {
                    SetSubStep(3);
                }
                break;

            case 3:
                AnimateEntity(D_80180674, self);
                if (D_801A3F84 & 0x100) {
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
            func_801A046C(NA_VO_SU_NO_SCREAM);
            CreateEntityFromCurrentEntity(
                E_SUCCUBUS_CUTSCENE, &g_Entities[200]);
            g_Entities[200].params = 1;
            D_80180660 = 0;
            D_80180664 |= 2;
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_SUCCUBUS_DEFEAT, TIMEATTACK_SET_RECORD);
            self->velocityX = 0;
            self->velocityY = 0;
            posY = self->posY.i.hi + g_Camera.posY.i.hi;
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
            posY = self->posY.i.hi + g_Camera.posY.i.hi;
            if (posY >= 176) {
                func_801A046C(NA_SE_SU_LANDING);
                self->posY.i.hi = 175 - g_Camera.posY.i.hi;
                SetSubStep(SUCCUBUS_DYING_ANIM_1);
                posX = self->posX.i.hi + g_Camera.posX.i.hi;
                if (posX < 80) {
                    D_801816C4 = self->facing = 1;
                } else if (posX > 432) {
                    D_801816C4 = self->facing = 0;
                } else {
                    D_801816C4 = self->facing = (GetSideToPlayer() & 1) ^ 1;
                }
                D_801A3F84 |= 2;
            }
            break;

        case SUCCUBUS_DYING_ANIM_1:
            AnimateEntity(D_80180770, self);
            if (D_801A3F84 & 0x10) {
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
            func_801A046C(NA_SE_SU_FLAPPING_WINGS);
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
            self->ext.succubus.facing = 0;
            self->step_s++;

        case SUCCUBUS_FLY_1:
            AnimateEntity(D_801806E8, self);
            if ((self->animFrameIdx == 3) && (self->animFrameDuration == 0)) {
                func_801A046C(NA_SE_SU_FLAPPING_WINGS);
            }

            MoveEntity();
            posY = self->posY.i.hi - self->ext.succubus.yOffset;
            if (posY > 8) {
                self->velocityY = FIX(-0.75);
            }
            if (posY < -8) {
                self->velocityY = FIX(0.75);
            }

            if (self->facing != self->ext.succubus.facing) {
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
            if (self->ext.succubus.facing == 0) {
                if (temp < posX) {
                    self->ext.succubus.facing ^= 1;
                }
                if (self->ext.succubus.facing != 0) {
                    if (posX < temp) {
                        self->ext.succubus.facing ^= 1;
                    }
                }
            } else if (posX < temp) {
                self->ext.succubus.facing ^= 1;
            }

            sideToPlayer = ((GetSideToPlayer() & 1) ^ 1);
            if (self->facing != sideToPlayer) {
                if (temp > 16) {
                    self->ext.succubus.nextStep = SUCCUBUS_CLONE_ATTACK;
                    SetStep(SUCCUBUS_NEXT_ACTION_CHECK);
                }
            }

            posX = self->posX.i.hi + g_Camera.posX.i.hi;
            if (self->facing != 0) {
                posX = 512 - posX;
            }
            if (posX > 416) {
                self->ext.succubus.facing = 0;
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
            if (self->facing != self->ext.succubus.facing) {
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
                func_801A046C(NA_SE_SU_FLAPPING_WINGS);
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
            self->facing = (GetSideToPlayer() & 1) ^ 1;
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
            self->facing = (GetSideToPlayer() & 1) ^ 1;
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
                func_801A046C(NA_VO_SU_LAUGH);
                self->step_s++;
            }
            break;

        case SUCCUBUS_PETAL_ATTACK_CREATE_PETALS:
            if (!(self->ext.succubus.timer & 1)) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_SUCCUBUS_PETAL, self, entity);
                    entity->facing = self->facing;
                    entity->zPriority = self->zPriority - 1;
                }
            }
            if ((self->ext.succubus.timer % 64) == 0) {
                func_801A046C(NA_SE_SU_PETAL_ATTACK);
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
            func_801A046C(NA_VO_SU_BLANK);
            self->step_s++;

        case SUCCUBUS_CHARGE_FLY_TOWARDS_PLAYER:
            entity = &PLAYER;
            posX = entity->posX.i.hi - self->posX.i.hi;
            if (self->facing != 0) {
                posX -= 16;
            } else {
                posX += 16;
            }
            posY = entity->posY.i.hi - self->posY.i.hi;

            angle = ratan2(posY, posX);
            self->velocityX = (rcos(angle) << 0x11) >> 0xC;
            self->velocityY = (rsin(angle) << 0x11) >> 0xC;
            posX = self->velocityX;

            if (self->facing != 0) {
                posX = -posX;
            }
            if (posX > 0) {
                self->velocityX = 0;
            }

            MoveEntity();

            posX = PLAYER.posX.i.hi - self->posX.i.hi;
            if (self->facing == 0) {
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

            posY = self->posY.i.hi + g_Camera.posY.i.hi;
            if (posY > 176) {
                self->posY.i.hi = 176 - g_Camera.posY.i.hi;
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
            if (self->facing != 0) {
                posX -= 16;
            } else {
                posX += 16;
            }
            self->posY.i.hi = posY = entity->posY.i.hi;
            self->posX.i.hi = posX;
            func_801A046C(NA_VO_SU_SUCK_YOU_DRY);
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
                if (self->facing != 0) {
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
            self->facing = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;
            if (self->ext.succubus.unk87) {
                func_801A046C(NA_VO_SU_DELICIOUS);
            } else {
                func_801A046C(NA_VO_SU_LAUGH);
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
            posX = self->posX.i.hi + g_Camera.posX.i.hi;
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
            temp = self->posX.i.hi + g_Camera.posX.i.hi;

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
            D_80180660 = 6;
            func_801A046C(NA_VO_SU_GRUNT_1);
            func_801A046C(NA_SE_SU_CREATE_CLONES);
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
            if (D_80180660 == 0) {
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
                func_801A046C(NA_SE_SU_CHARGE_PINKBALLS);

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
                func_801A046C(NA_VO_SU_GRUNT_2);
                func_801A046C(NA_VO_SU_CRYSTAL_1);
                func_801A046C(NA_SE_SU_SHOOT_PINKBALLS);
                self->ext.succubus.unk85 = true;
            }
            break;
        }
        break;

    case SUCCUBUS_SPIKE_ATTACK:
        switch (self->step_s) {
        case SUCCUBUS_SPIKE_ATTACK_CREATE_SPIKES:
            entity = &g_Entities[96];
            self->facing = 0;
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
                    entity->facing = facing;
                }
            }
            self->step_s++;

        case SUCCUBUS_SPIKE_ATTACK_1:
            if (AnimateEntity(D_80180748, self) == 0) {
                self->ext.succubus.unk85 = true;
                func_801A046C(NA_VO_SU_CRYSTAL_2);
                func_801A046C(NA_VO_SU_GRUNT_3);
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
                func_801A046C(NA_VO_SU_HURT_1);
            } else {
                func_801A046C(NA_VO_SU_HURT_2);
            }

            self->ext.succubus.timer = 32;
            D_80180660 = 0;
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
    posX = self->posX.i.hi + g_Camera.posX.i.hi;
    posY = self->posY.i.hi + g_Camera.posY.i.hi;

    if (self->velocityX < 0) {
        if (posX < 40) {
            self->posX.i.hi = 40 - g_Camera.posX.i.hi;
        }
    } else if (posX > 480) {
        self->posX.i.hi = 480 - g_Camera.posX.i.hi;
    }
    if ((self->velocityY < 0) && (posY < 48)) {
        self->posY.i.hi = 48 - g_Camera.posY.i.hi;
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

const u32 rodataPadding = 0;
