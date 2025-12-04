// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dre/dre.h"

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

#ifdef VERSION_PSP
extern u8* D_801816C4; // defined in st_init_psp
extern s32 E_ID(SUCCUBUS_PETAL);
extern s32 E_ID(SUCCUBUS_WING_OVERLAY);
extern s32 E_ID(SUCCUBUS_CLONE);
extern s32 E_ID(SUCCUBUS_PINK_BALL_PROJECTILE);
extern s32 E_ID(SUCCUBUS_WING_SPIKE);
extern s32 E_ID(SUCCUBUS_WING_SPIKE_TIP);
extern s32 E_ID(SUCCUBUS_CUTSCENE);
#endif

extern EInit g_EInitSuccubus;
extern EInit D_801804DC;
extern EInit D_801804E8;
extern EInit D_801804F4;
extern EInit D_80180500;
extern EInit D_8018050C;

// bss on pspeu
#ifndef VERSION_PSP
static s32 multiple_count = 0; // clones counter
static s32 D_80180664 = 0;
static s32 D_80180668 = 0;
#endif

// This data comes at the beginning for pspeu, but the end for us
#ifdef VERSION_PSP
static s8 D_801807F8[] = {
    0,  0,  0,   0,   -68, -62, 0, 0, 0,   6,  4,   20,  0,   4,
    4,  18, 0,   -2,  4,   12,  0, 0, 3,   3,  -4,  0,   4,   4,
    -4, -4, 4,   4,   -4,  4,   4, 4, -20, -7, 0,   0,   -12, -20,
    0,  0,  -20, -12, 0,   0,   0, 0, 4,   4,  -20, -32, 0,   0};
static u8 D_80180830[] = {
    0, 1, 1,  1,  1, 1, 1, 1, 1, 1, 1, 1,  1,  1,  1,  1,  1, 1, 1, 1, 1, 1, 1,
    2, 2, 2,  2,  2, 2, 2, 2, 2, 2, 2, 2,  2,  2,  3,  3,  2, 2, 2, 2, 3, 3, 4,
    2, 3, 3,  3,  3, 3, 2, 2, 2, 2, 2, 2,  2,  2,  2,  1,  3, 3, 5, 5, 5, 6, 7,
    8, 9, 10, 11, 1, 1, 1, 1, 2, 2, 2, 12, 12, 13, 13, 13, 0, 0, 0, 0, 0, 0, 0};
#endif
/* *** EntitySuccubus animations START *** */
static AnimateEntityFrame D_8018066C[] = {{8, 2}, {8, 3}, POSE_LOOP(0)};
static AnimateEntityFrame D_80180674[] = {
    {2, 4}, {10, 5}, {10, 6}, {10, 7}, POSE_END};
static AnimateEntityFrame D_80180680[] = {
    {12, 7}, {12, 8}, {12, 7}, {12, 8}, {12, 7},
    {12, 8}, {12, 7}, {12, 8}, POSE_END};
static AnimateEntityFrame D_80180694[] = {
    {10, 8}, {10, 9}, {64, 10}, {8, 11}, {16, 12}, POSE_END};
static AnimateEntityFrame D_801806A0[] = {
    {24, 13}, {8, 14}, {8, 15}, {8, 16}, {8, 17},  {24, 18},
    {2, 19},  {2, 20}, {2, 21}, {2, 22}, {2, 23},  {2, 24},
    {40, 23}, {8, 25}, {8, 26}, {8, 27}, {16, 28}, POSE_END};
static AnimateEntityFrame D_801806C4[] = {
    {8, 28}, {8, 29}, {8, 30}, {8, 31},
    {8, 32}, {8, 33}, {8, 34}, POSE_LOOP(0)};
static AnimateEntityFrame D_801806D4[] = {
    {4, 28}, {10, 35}, {6, 36}, {6, 37}, {6, 38},
    {6, 39}, {6, 40},  {6, 41}, {4, 42}, POSE_END};
static AnimateEntityFrame D_801806E8[] = {
    {8, 36}, {8, 37}, {8, 38}, {8, 39},
    {8, 40}, {8, 41}, {8, 42}, POSE_LOOP(0)};
static AnimateEntityFrame D_801806F8[] = {
    {4, 36}, {10, 35}, {6, 28}, {6, 29}, {6, 30},
    {6, 31}, {6, 32},  {6, 33}, {4, 34}, POSE_END};
static AnimateEntityFrame D_8018070C[] = {
    {8, 36}, {8, 43}, {8, 44}, {32, 45}, {1, 46}, {2, 47}, {4, 48}, POSE_END};
static AnimateEntityFrame D_8018071C[] = {
    {2, 36}, {8, 43}, {8, 44}, {8, 46}, {8, 49}, {8, 50}, {32, 51}, POSE_END};
static AnimateEntityFrame D_8018072C[] = {{8, 52}, {8, 53}, POSE_LOOP(0)};
static AnimateEntityFrame D_80180734[] = {
    {12, 28}, {8, 27}, {8, 54}, {24, 55}, {1, 26},
    {2, 25},  {2, 23}, {2, 24}, {40, 23}, POSE_END};
static AnimateEntityFrame D_80180748[] = {
    {4, 28}, {8, 56}, {8, 57}, {8, 58}, {32, 59}, {1, 26},
    {2, 25}, {2, 23}, {2, 24}, {4, 60}, POSE_END};
static AnimateEntityFrame D_80180760[] = {{8, 23}, {8, 25}, {12, 26}, POSE_END};
static AnimateEntityFrame D_80180768[] = {{8, 61}, {8, 44}, POSE_LOOP(0)};
static AnimateEntityFrame D_80180770[] = {
    {8, 73}, {32, 74}, {128, 75}, POSE_END};
static AnimateEntityFrame D_80180778[] = {{1, 75}, {128, 76}, POSE_END};
static AnimateEntityFrame D_80180780[] = {
    {16, 26}, {8, 25}, {8, 23},  {8, 77}, {72, 78},
    {1, 79},  {2, 26}, {16, 28}, POSE_END};
static AnimateEntityFrame D_80180794[] = {{1, 80}, {1, 81}, POSE_LOOP(0)};
static AnimateEntityFrame D_8018079C[] = {{8, 82}, {8, 83}, {8, 84}, POSE_END};
static AnimateEntityFrame __unused_801807A4[] = {
    {8, 84}, {8, 83}, {8, 82}, POSE_END};
static AnimateEntityFrame D_801807AC[] = {
    {8, 83}, {8, 87}, {8, 83}, {8, 88}, POSE_LOOP(0)};
static u8 __unused_801807B8[] = {
    0, 0, 0,   0,  128, 91, 8, 90, 8, 89, 32,  88, 128, 28,
    0, 0, 128, 28, 32,  88, 8, 89, 8, 90, 128, 91, 0,   0};
/* *** EntitySuccubus animations END *** */
// 0x801807D4
static u8 g_CloneShootOrder[4][7] = {
    {0, 1, 2, 3, 4, 5, 6},
    {1, 5, 4, 3, 6, 2, 0},
    {3, 6, 1, 0, 5, 4, 2},
    {4, 1, 3, 2, 6, 0, 5}};
static s16 D_801807F0[] = {168, 744, -312, -768};

// This data comes at the beginning for pspeu, but the end for us
#ifndef VERSION_PSP
static s8 D_801807F8[] = {
    0,  0,  0,   0,   -68, -62, 0, 0, 0,   6,  4,   20,  0,   4,
    4,  18, 0,   -2,  4,   12,  0, 0, 3,   3,  -4,  0,   4,   4,
    -4, -4, 4,   4,   -4,  4,   4, 4, -20, -7, 0,   0,   -12, -20,
    0,  0,  -20, -12, 0,   0,   0, 0, 4,   4,  -20, -32, 0,   0};
static u8 D_80180830[] = {
    0, 1, 1,  1,  1, 1, 1, 1, 1, 1, 1, 1,  1,  1,  1,  1,  1, 1, 1, 1, 1, 1, 1,
    2, 2, 2,  2,  2, 2, 2, 2, 2, 2, 2, 2,  2,  2,  3,  3,  2, 2, 2, 2, 3, 3, 4,
    2, 3, 3,  3,  3, 3, 2, 2, 2, 2, 2, 2,  2,  2,  2,  1,  3, 3, 5, 5, 5, 6, 7,
    8, 9, 10, 11, 1, 1, 1, 1, 2, 2, 2, 12, 12, 13, 13, 13, 0, 0, 0, 0, 0, 0, 0};
#endif

#ifdef VERSION_PSP
static s32 D_80180668;
static s32 D_80180664;
static s32 multiple_count = 0; // clones counter
#endif

#ifndef VERSION_PSP
// defined in cutscene_data
extern u8 D_801816C4[]; // Succubus facing assigned to it
#endif

// bss
extern s32 g_SkipCutscene;
extern u32 g_CutsceneFlags;

void EntitySuccubus(Entity* self) {
    u8* clonesShootOrder;
    s32 sideToPlayer;
    Entity* entity;
    s32 posX, posY;
    s8* hitbox;
    s32 facingLeft;
    s16 angle;
    s32 temp;
    s32 i;

    FntPrint("multiple_count %x\n", multiple_count);

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
        InitializeEntity(g_EInitSuccubus);
        self->animCurFrame = 82;
        SetStep(SUCCUBUS_CS_1);
        entity = self + 1;
        CreateEntityFromCurrentEntity(E_ID(SUCCUBUS_WING_OVERLAY), entity);

    case SUCCUBUS_CS_1: // Disguised as Lisa
        if (g_CastleFlags[SUCCUBUS_CS] || (g_DemoMode != Demo_None)) {
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
        if (g_SkipCutscene) {
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
        if (g_SkipCutscene && self->step_s) {
            SetStep(SUCCUBUS_CS_4);
        } else {
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
                if (!AnimateEntity(D_80180680, self)) {
                    SetStep(SUCCUBUS_CS_4);
                }
                break;
            }
        }
        break;

    // Ascends Succubus into the air
    case SUCCUBUS_CS_4:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_80180694, self)) {
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
            if (!AnimateEntity(D_801806A0, self)) {
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
            PlaySfxPositional(SFX_SUCCUBUS_DEFEAT);
            entity = &g_Entities[200];
            CreateEntityFromCurrentEntity(E_ID(SUCCUBUS_CUTSCENE), entity);
            entity->params = 1;
            multiple_count = 0;
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
            if (posY > 175) {
                PlaySfxPositional(SFX_STOMP_HARD_A);
                self->posY.i.hi = 175 - g_Tilemap.scrollY.i.hi;
                SetSubStep(SUCCUBUS_DYING_ANIM_1);
                posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
                if (posX < 80) {
                    *D_801816C4 = self->facingLeft = 1;
                } else if (posX > 432) {
                    *D_801816C4 = self->facingLeft = 0;
                } else {
                    *D_801816C4 = self->facingLeft =
                        (GetSideToPlayer() & 1) ^ 1;
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
        if (!self->step_s) {
            self->ext.succubus.timer = 64;
            self->step_s++;
        }

        AnimateEntity(D_801806C4, self);
        if (!self->poseTimer && self->pose == 3) {
            PlaySfxPositional(SFX_BOSS_WING_FLAP);
        }

        posY = self->posY.i.hi - self->ext.succubus.yOffset;
        if (posY > 8) {
            self->velocityY = FIX(-0.75);
        }

        if (!--self->ext.succubus.timer) {
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
            if (!(Random() & 3)) {
                if (Random() & 1) {
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
            if (!self->poseTimer && self->pose == 3) {
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

            if (self->facingLeft ^ self->ext.succubus.facingLeft) {
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
            if (!self->ext.succubus.facingLeft && temp < posX) {
                self->ext.succubus.facingLeft ^= 1;
            }
            if (self->ext.succubus.facingLeft && posX < temp) {
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
            if (self->facingLeft) {
                posX = 512 - posX;
            }
            if (posX > 416) {
                self->ext.succubus.facingLeft = 0;
                self->ext.succubus.timer = 96;
                self->step_s++;
            }

            if (!self->ext.succubus.timer) {
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
            if (self->facingLeft ^ self->ext.succubus.facingLeft) {
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
            if (!self->poseTimer && self->pose == 3) {
                PlaySfxPositional(SFX_BOSS_WING_FLAP);
            }
            MoveEntity();
            if (!--self->ext.succubus.timer) {
                self->step_s = 0;
            }
            break;
        }
        break;

    case SUCCUBUS_FACE_PLAYER:
        if (!self->step_s) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;
        }

        if (!AnimateEntity(D_801806D4, self)) {
            if (self->ext.succubus.nextStep) {
                SetStep(self->ext.succubus.nextStep);
                self->ext.succubus.nextStep = 0;
            } else {
                SetStep(SUCCUBUS_FLY);
            }
        }
        break;

    case SUCCUBUS_NEXT_ACTION_CHECK:
        if (!AnimateEntity(D_801806F8, self)) {
            if (self->ext.succubus.nextStep) {
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
            if (g_Player.status & PLAYER_STATUS_CURSE) {
                self->ext.succubus.unk87 = false;
            } else {
                self->ext.succubus.unk87 = true;
            }
            D_80180668 = 0;
            self->step_s++;

        case SUCCUBUS_PETAL_ATTACK_ANIM:
            if (!AnimateEntity(D_8018070C, self)) {
                self->ext.succubus.timer = 128;
                PlaySfxPositional(SFX_SUCCUBUS_LAUGH);
                self->step_s++;
            }
            break;

        case SUCCUBUS_PETAL_ATTACK_CREATE_PETALS:
            if (!(self->ext.succubus.timer & 1)) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_ID(SUCCUBUS_PETAL), self, entity);
                    entity->facingLeft = self->facingLeft;
                    entity->zPriority = self->zPriority - 1;
                }
            }
            if (!(self->ext.succubus.timer & 0x3F)) {
                PlaySfxPositional(SFX_GLASS_SHARDS);
            }
            if (!--self->ext.succubus.timer) {
                SetStep(SUCCUBUS_FLY);
            }
            if (self->ext.succubus.unk87) {
                if (g_Player.status & PLAYER_STATUS_CURSE) {
                    SetStep(SUCCUBUS_CHARGE);
                }
            } else if (D_80180668) {
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
            PlaySfxPositional(SFX_UNK_SUCCUBUS_86F);
            self->step_s++;

        case SUCCUBUS_CHARGE_FLY_TOWARDS_PLAYER:
            entity = &PLAYER;
            posX = entity->posX.i.hi - self->posX.i.hi;
            if (self->facingLeft) {
                posX -= 16;
            } else {
                posX += 16;
            }
            posY = entity->posY.i.hi - self->posY.i.hi;

            angle = ratan2(posY, posX);
            self->velocityX = (rcos(angle) << 0x11) >> 0xC;
            self->velocityY = (rsin(angle) << 0x11) >> 0xC;
            posX = self->velocityX;

            if (self->facingLeft) {
                posX = -posX;
            }
            if (posX > 0) {
                self->velocityX = 0;
            }

            MoveEntity();

            entity = &PLAYER;
            posX = entity->posX.i.hi - self->posX.i.hi;
            if (!self->facingLeft) {
                posX = -posX;
            }
            posX -= 4;
            if (posX < 0) {
                posX = 512;
            }
            posY = entity->posY.i.hi - self->posY.i.hi;
            if (posY < 0) {
                posY = -posY;
            }

            if (!(g_Player.status &
                  (PLAYER_STATUS_AXEARMOR | PLAYER_STATUS_DEAD |
                   PLAYER_STATUS_UNK100 | PLAYER_STATUS_STONE |
                   PLAYER_STATUS_CROUCH | PLAYER_STATUS_MIST_FORM))) {
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

            if (!g_Player.unk60) {
                if (!--self->ext.succubus.timer) {
                    self->ext.succubus.unk87 = false;
                    SetStep(SUCCUBUS_FLY);
                }
            }
            break;

        case SUCCUBUS_CHARGE_AT_PLAYER_POSITION:
            entity = &PLAYER;
            posX = entity->posX.i.hi;
            if (self->facingLeft) {
                posX -= 16;
            } else {
                posX += 16;
            }
            posY = entity->posY.i.hi;
            self->posX.i.hi = posX;
            self->posY.i.hi = posY;
            PlaySfxPositional(SFX_SUCCUBUS_ILL_SUCK_YOU_DRY);
            self->step_s++;

        case SUCCUBUS_CHARGE_DEAL_DAMAGE:
            if (!AnimateEntity(D_8018071C, self)) {
                g_Player.unk64 = g_api.enemyDefs[347].attack;
                g_Player.unk60 = 3;
                self->ext.succubus.timer = 48;
                self->step_s++;
            }
            break;

        case SUCCUBUS_CHARGE_FLY_AWAY:
            if (!--self->ext.succubus.timer) {
                g_Player.unk60 = 0;
                self->hitboxState = 3;
                if (self->facingLeft) {
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
            if (!--self->ext.succubus.timer) {
                SetStep(SUCCUBUS_TAUNT);
            }
            break;
        }
        break;

    case SUCCUBUS_TAUNT:
        if (!self->step_s) {
            self->ext.succubus.timer = 80;
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;
            if (self->ext.succubus.unk87) {
                PlaySfxPositional(SFX_SUCCUBUS_DELICIOUS);
            } else {
                PlaySfxPositional(SFX_SUCCUBUS_LAUGH);
            }
            self->ext.succubus.unk87 = false;
        }
        AnimateEntity(D_8018072C, self);
        if (!--self->ext.succubus.timer || GetDistanceToPlayerX() < 32) {
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
                temp = ((temp - 480) % 64) + 416;
                posX = temp - 384;
            }

            clonesShootOrder = *g_CloneShootOrder;
            temp = Random() & 3;
            clonesShootOrder += temp * 7;

            entity = &g_Entities[112];
            temp = self->posX.i.hi + g_Tilemap.scrollX.i.hi;

            for (i = 0; i < 6; i++, entity++, clonesShootOrder++, posX += 64) {
                CreateEntityFromEntity(E_ID(SUCCUBUS_CLONE), self, entity);
                // Giving each clone a pointer to the real Succubus
                entity->ext.succubus.real = self;
                if (posX == temp) {
                    posX += 64;
                }
                entity->ext.succubus.clonePosX = posX;
                entity->params = *clonesShootOrder;
            }
            self->params = *clonesShootOrder;
            self->hitboxState = 0;
            self->ext.succubus.timer = 64;
            multiple_count = 6;
            PlaySfxPositional(SFX_SUCCUBUS_DUPLICATES);
            PlaySfxPositional(SFX_PSWORD_TWIRL);
            self->step_s++;

        case SUCCUBUS_CLONE_ATTACK_WAIT:
            if (!--self->ext.succubus.timer) {
                self->step_s = 3;
            }

        case SUCCUBUS_CLONE_ATTACK_ANIM_1:
            self->ext.succubus.unk85 = false;
            AnimateEntity(D_80180734, self);
            if (!self->poseTimer && self->pose == 4) {
                self->step_s++;
            }
            break;

        case SUCCUBUS_CLONE_ATTACK_PLACE_REAL:
            temp = Random() % 6;
            entity = &g_Entities[112];
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
            if (!AnimateEntity(D_80180734, self)) {
                SetSubStep(SUCCUBUS_CLONE_ATTACK_SET_SHOOTING);
            }
            break;

        case SUCCUBUS_CLONE_ATTACK_SET_SHOOTING:
            if (!AnimateEntity(D_80180760, self)) {
                // PinkBall attack delay set
                self->ext.succubus.timer = (self->params * 48) + 1;
                self->ext.succubus.unk85 = true;
                SetSubStep(SUCCUBUS_CLONE_ATTACK_STOP_SHOOTING);
            }
            break;

        case SUCCUBUS_CLONE_ATTACK_STOP_SHOOTING:
            self->animCurFrame = 26;
            if (!--self->ext.succubus.timer) {
                self->ext.succubus.unk85 = false;
                /*! @bug: Likely a typo meant to be
                 * SetSubStep(SUCCUBUS_CLONE_ATTACK_SHOOT_PINKBALLS);
                 * case SUCCUBUS_CLONE_ATTACK_SHOOT_PINKBALLS is
                 * inaccessible causing the real Succubus to be
                 * unable to do the PinkBall attack.
                 */
                SetSubStep(SUCCUBUS_CLONE_ATTACK_STOP_SHOOTING);
            }
            if (!multiple_count) {
                SetStep(SUCCUBUS_IDLE);
            }
            break;

        /* Unused: see @bug in previous case.
         * The real Succubus was supposed to shoot last, hinting
         * the player her real position, but the end result is
         * she doesn't shoot at all.
         */
        case SUCCUBUS_CLONE_ATTACK_SHOOT_PINKBALLS:
            if (!AnimateEntity(D_80180780, self)) {
                self->ext.succubus.timer = 288;
                SetSubStep(SUCCUBUS_CLONE_ATTACK_ANIM_2);
            }
            if (!self->poseTimer && self->pose == 4) {
                PlaySfxPositional(SFX_RIC_SUC_REVIVE);

                for (i = 0; i < 2; i++) {
                    entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                    if (entity != NULL) {
                        CreateEntityFromEntity(
                            E_ID(SUCCUBUS_PINK_BALL_PROJECTILE), self, entity);
                        entity->params = i;
                        if (i != 0) {
                            entity->posX.i.hi -= 2;
                        } else {
                            entity->posX.i.hi += 2;
                        }
                        entity->posY.i.hi -= 13;
                        entity->ext.succubus.real = self;
                        entity->zPriority = self->zPriority + 1;
                    }
                }
            }
            if (!self->poseTimer && self->pose == 5) {
#ifdef VERSION_PSP
                PlaySfxPositional(SFX_UNUSED_SUCCUBUS_ATTACK_A);
                PlaySfxPositional(SFX_RNO2_ANIME_SWORD);
#else
                PlaySfxPositional(SFX_SUCCUBUS_HOMING_ORB_ATTACK);
                PlaySfxPositional(SFX_SUCCUBUS_HOMING_ORB);
                PlaySfxPositional(SFX_FIRE_SHOT);
#endif
                self->ext.succubus.unk85 = true;
            }
            break;
        }
        break;

    case SUCCUBUS_SPIKE_ATTACK:
        switch (self->step_s) {
        case SUCCUBUS_SPIKE_ATTACK_CREATE_SPIKES:
            self->facingLeft = 0;
            self->ext.succubus.unk85 = false;
            D_80180668 = 0;
            entity = &g_Entities[96];
            for (facingLeft = 0; facingLeft < 2; facingLeft++) {
                for (i = 0; i < 4; i++, entity += 2) {
                    CreateEntityFromEntity(
                        E_ID(SUCCUBUS_WING_SPIKE), self, entity);
                    entity->params = i;
                    entity->zPriority = self->zPriority;
                    entity->ext.succubus.real = self;
                    if (!facingLeft) {
                        entity->posX.i.hi -= 5;
                    } else {
                        entity->posX.i.hi += 4;
                    }
                    entity->posY.i.hi -= 27;
                    entity->facingLeft = facingLeft;
                }
            }
            self->step_s++;

        case SUCCUBUS_SPIKE_ATTACK_1:
            if (!AnimateEntity(D_80180748, self)) {
                self->ext.succubus.unk85 = true;
                PlaySfxPositional(SFX_GUARD_TINK);
                PlaySfxPositional(SFX_SUCCUBUS_WING_ATTACK);
                self->ext.succubus.timer = 64;
                SetSubStep(2);
            }
            break;

        case SUCCUBUS_SPIKE_ATTACK_2:
            if (!--self->ext.succubus.timer) {
                self->ext.succubus.unk85 = false;
                self->ext.succubus.timer = 64;
                self->step_s++;
            }
            break;

        case SUCCUBUS_SPIKE_ATTACK_3:
            if (!--self->ext.succubus.timer) {
                self->step_s++;
            }
            break;

        case SUCCUBUS_SPIKE_ATTACK_4:
            if (!AnimateEntity(D_80180760, self)) {
                SetStep(SUCCUBUS_IDLE);
            }
            if (D_80180668) {
                if (GetDistanceToPlayerX() > 64) {
                    self->ext.succubus.nextStep = SUCCUBUS_TAUNT;
                    SetStep(SUCCUBUS_FACE_PLAYER);
                }
            }
            break;
        }
        break;

    case SUCCUBUS_GET_HIT:
        if (!self->step_s) {
            if (Random() & 1) {
                PlaySfxPositional(SFX_SUCCUBUS_PAIN_A);
            } else {
                PlaySfxPositional(SFX_SUCCUBUS_PAIN_B);
            }

            self->ext.succubus.timer = 32;
            multiple_count = 0;
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
        if (!--self->ext.succubus.timer) {
            if (Random() & 1) {
                self->ext.succubus.nextStep = SUCCUBUS_SPIKE_ATTACK;
            } else {
                self->ext.succubus.nextStep = SUCCUBUS_CLONE_ATTACK;
            }
            SetStep(SUCCUBUS_NEXT_ACTION_CHECK);
        }
        break;

    case SUCCUBUS_DEBUG:
#include "../pad2_anim_debug.h"
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
    hitbox = D_801807F8;
    hitbox += 4 * D_80180830[self->animCurFrame];
    self->hitboxOffX = *hitbox++;
    self->hitboxOffY = *hitbox++;
    self->hitboxWidth = *hitbox++;
    self->hitboxHeight = *hitbox++;
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
        self->drawFlags = FLAG_DRAW_ROTATE;
        self->rotate = rand() & 0xFFF;
        temp_s2 = Random() & 3;
        if (temp_s2 > 2) {
            temp_s2 = 0;
        }
        self->animCurFrame = temp_s2 + 64;

        angle = ((Random() & 0x1F) * 16) + 0xC0;
        if (!self->facingLeft) {
            angle = 0x800 - angle;
        }
#ifdef VERSION_PSP
        temp_s2 = (((rand() & 0x7fff) * 4) + 0x38000) >> 0xC;
#else
        temp_s2 = ((rand() * 4) + 0x38000) >> 0xC;
#endif
        self->velocityX = temp_s2 * rcos(angle);
        self->velocityY = temp_s2 * rsin(angle);
        self->ext.succubus.timer = (Random() & 31) + 16;

    case 1:
        self->velocityX -= self->velocityX >> 6;
        self->velocityY -= self->velocityY >> 6;
        MoveEntity();
        if (!--self->ext.succubus.timer) {
            self->ext.succubus.timer = (Random() & 31) + 32;
            self->step++;
        }
        break;

    case 2:
        MoveEntity();
        self->rotate += self->ext.succubus.timer;
        break;
    }
}

// Wings that appear over the player when the succubus does her charge attack
void EntitySuccubusWingOverlay(Entity* self) {
    Entity* entity;

    if (!self->step) {
        InitializeEntity(D_801804E8);
    }

    entity = self - 1;
    self->posX.i.hi = entity->posX.i.hi;
    self->posY.i.hi = entity->posY.i.hi;
    self->facingLeft = entity->facingLeft;
    self->animCurFrame = 0;

    if (entity->animCurFrame == 50) {
        self->animCurFrame = 62;
    }

    if (entity->animCurFrame == 51) {
        self->animCurFrame = 63;
    }

    entity = &PLAYER;
    self->zPriority = entity->zPriority + 4;
}

void EntitySuccubusClone(Entity* self) {
    Entity* newEntity;
    s8* hitbox;
    s32 velX;
    s32 i;

    if (multiple_count == 0) {
        self->flags |= FLAG_DEAD;
    }

    if (self->flags & FLAG_DEAD) {
        if (self->step != 5) {
            if (multiple_count != 0) {
                multiple_count--;
            }
            self->hitboxState = 0;
            self->flags |= FLAG_DEAD;
            g_api.PlaySfxVolPan(SFX_BOSS_CLONE_DISAPPEAR, 0x54, 0);
            SetStep(5);
        }
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_801804F4);
        self->hitboxState = 0;
        velX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        velX = (self->ext.succubus.clonePosX - velX) << 0x10;
        self->velocityX = velX / 0x40;
        self->ext.succubus.timer = 64;

    case 1:
        MoveEntity();
        newEntity = self->ext.succubus.real;
        self->animCurFrame = newEntity->animCurFrame;
        self->facingLeft = newEntity->facingLeft;
        if (!--self->ext.succubus.timer) {
            self->hitboxState = 3;
            SetStep(2);
        }
        break;

    case 2:
        newEntity = self->ext.succubus.real;
        self->animCurFrame = newEntity->animCurFrame;
        self->facingLeft = newEntity->facingLeft;
        if (newEntity->ext.succubus.unk85) {
            self->ext.succubus.timer = (self->params * 48) + 1;
            SetStep(3);
        }
        break;

    case 3:
        self->animCurFrame = 26;
        if (!--self->ext.succubus.timer) {
            SetStep(4);
        }
        break;

    case 4:
        if (!self->step_s) {
            self->ext.succubus.unk85 = 0;
            self->step_s++;
        }

        if (!AnimateEntity(D_80180780, self)) {
            self->ext.succubus.timer = 288;
            SetStep(3);
        }

        if (!self->poseTimer && self->pose == 4) {
            PlaySfxPositional(SFX_RIC_SUC_REVIVE);
            for (i = 0; i < 2; i++) {
                newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(SUCCUBUS_PINK_BALL_PROJECTILE), self, newEntity);
                    newEntity->params = i;
                    if (i != 0) {
                        newEntity->posX.i.hi -= 2;
                    } else {
                        newEntity->posX.i.hi += 2;
                    }
                    newEntity->posY.i.hi -= 10;
                    newEntity->ext.succubus.real = self;
                    newEntity->zPriority = self->zPriority + 1;
                }
            }
        }
        if (!self->poseTimer && self->pose == 5) {
            PlaySfxPositional(SFX_SUCCUBUS_HOMING_ORB_ATTACK);
#ifdef VERSION_PSP
            PlaySfxPositional(SFX_RNO2_ANIME_SWORD);
#else
            PlaySfxPositional(SFX_SUCCUBUS_HOMING_ORB);
#endif
            PlaySfxPositional(SFX_FIRE_SHOT);
            self->ext.succubus.unk85 = 1;
        }
        break;

    case 5:
        if (!self->step_s) {
            self->ext.succubus.timer = 32;
            self->step_s++;
        }
        if (self->ext.succubus.timer & 1) {
            self->animSet = ANIMSET_DRA(0);
        } else {
            self->animSet = ANIMSET_OVL(1);
        }
        if (!--self->ext.succubus.timer) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    hitbox = D_801807F8;
    hitbox += D_80180830[self->animCurFrame] * 4;
    self->hitboxOffX = *hitbox++;
    self->hitboxOffY = *hitbox++;
    self->hitboxWidth = *hitbox++;
    self->hitboxHeight = *hitbox++;
}

// Pink ball projectile shot by succubus duplicates ID 0x1D
void EntityPinkBallProjectile(Entity* self) {
    Entity* entity;
    s16 temp_s0;

    if (D_80180664 & 2) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180500);
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->drawFlags = FLAG_DRAW_SCALEX | FLAG_DRAW_SCALEY;
        self->scaleX = self->scaleY = 0;

    case 1:
        self->scaleX = self->scaleY += 4;
        if (self->scaleX > 256) {
            self->drawFlags = FLAG_DRAW_DEFAULT;
        }
        AnimateEntity(D_80180794, self);

        entity = self->ext.succubus.real;
        if (entity->ext.succubus.unk85) {
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
        entity = &PLAYER;
        temp_s0 = GetAngleBetweenEntities(self, entity);
        temp_s0 = GetNormalizedAngle(0x10, self->ext.succubus.unkA2, temp_s0);
        self->velocityX = rcos(temp_s0) * 0x38;
        self->velocityY = rsin(temp_s0) * 0x38;
        self->ext.succubus.unkA2 = temp_s0;

        if (self->hitFlags & 0x80) {
            self->step = 4;
        }

        if (!--self->ext.succubus.timer) {
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
    Entity* entity;
    s32 temp_s2;
    s16 var_s0;

    if (D_80180664 & 2) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_801804E8);
        self->drawFlags = FLAG_DRAW_ROTATE;
        self->animCurFrame = 0;
        var_s0 = D_801807F0[self->params];
        self->rotate = var_s0;
        self->drawFlags |= FLAG_DRAW_SCALEX;
        self->scaleX = 0x100;
        entity = self + 1;
        CreateEntityFromEntity(E_ID(SUCCUBUS_WING_SPIKE_TIP), self, entity);
        entity->facingLeft = self->facingLeft;
        entity->params = self->params;
        entity->rotate = self->rotate;

    case 1:
        entity = self->ext.succubus.real;
        if (entity->ext.succubus.unk85) {
            self->step++;
        }
        break;

    case 2:
        self->animCurFrame = 85;
        self->scaleX += 0x40;
        if (self->scaleX > 0x600) {
            self->scaleX = 0x600;
        }

        entity = self->ext.succubus.real;
        if (!entity->ext.succubus.unk85) {
            self->step++;
        }
        break;

    case 3:
        self->scaleX -= 0x40;
        if (self->scaleX < 0x100) {
            DestroyEntity(self);
            return;
        }
    }

    temp_s2 = (self->scaleX * 0xB) << 2 >> 8;
    var_s0 = self->rotate;
    if (!self->facingLeft) {
        var_s0 = 0x800 - var_s0;
    }

    entity = self + 1;
    entity->posX.i.hi = self->posX.i.hi;
    entity->posY.i.hi = self->posY.i.hi;
    entity->posX.i.hi += temp_s2 * rcos(var_s0) >> 0xC;
    entity->posY.i.hi -= temp_s2 * rsin(var_s0) >> 0xC;
}

void EntitySuccubusWingSpikeTip(Entity* self) {
    Entity* entity;

    switch (self->step) {
    case 0:
        InitializeEntity(D_8018050C);
        self->animCurFrame = 0;
        self->drawFlags = FLAG_DRAW_ROTATE;
        self->hitboxState = 0;

    case 1:
        entity = self - 1;
        if (entity->animCurFrame) {
            self->hitboxState = 1;
            self->animCurFrame = 86;
        }
        if (self->hitFlags) {
            D_80180668 = 1;
        }
        if (entity->entityId != E_ID(SUCCUBUS_WING_SPIKE)) {
            DestroyEntity(self);
        }
    }
}
