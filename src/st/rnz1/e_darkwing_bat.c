// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rnz1.h"

#ifdef VERSION_PSP
extern s32 E_ID(BAT_WINGS);
extern s32 E_ID(DARKWING_WIND_DUST);
extern s32 E_ID(FADING_FIREBALL);
#endif

typedef enum {
    DB_INIT,
    DB_UNUSED,
    DB_IDLE,
    DB_WAKEUP,
    DB_FLYING,
    DB_TORPEDO,
    DB_WIND_ATTACK,
    DB_HUG_ATTACK,
    DB_8,
    DB_DEAD
} DB_steps;

static AnimateEntityFrame anim_breathing[] = {
    {16, 1}, {8, 2}, {8, 3}, {8, 4}, {24, 5}, POSE_END};
static AnimateEntityFrame anim_flapping[] = {
    {2, 14}, {2, 8}, {2, 9}, {2, 10}, {15, 11}, POSE_END};
static AnimateEntityFrame anim_torpedo_twist[] = {
    {3, 14}, {3, 15}, {8, 19}, POSE_END};
static AnimateEntityFrame anim_torpedo_twirl[] = {
    {3, 16}, {3, 17}, {3, 18}, {3, 19}, POSE_LOOP(0)};
static AnimateEntityFrame anim_torpedo_crush[] = {
    {2, 16}, {2, 15}, {2, 14}, POSE_END};
static AnimateEntityFrame anim_prepare_wind_attack[] = {
    {2, 9}, {2, 22}, {2, 21}, {2, 20}, POSE_END};
static AnimateEntityFrame anim_wind_attack[] = {
    {7, 20}, {5, 21}, {1, 22}, {1, 23}, {1, 24}, {1, 25}, {5, 26},     {7, 27},
    {5, 26}, {5, 25}, {5, 24}, {5, 23}, {5, 22}, {5, 21}, POSE_LOOP(0)};
static AnimateEntityFrame anim_spinning_halfopen[] = {
    {4, 29}, {4, 30}, {4, 31}, {4, 32},     {4, 33},
    {4, 34}, {4, 35}, {4, 36}, POSE_LOOP(0)};
// Grab alucard
static AnimateEntityFrame anim_hug[] = {
    {1, 20}, {1, 21}, {1, 22}, {1, 23}, {1, 24},
    {1, 25}, {2, 26}, {8, 27}, POSE_END};
// Alucard is being held, wings bulge to show him within
static AnimateEntityFrame anim_hugging[] = {
    {6, 28}, {5, 44}, {6, 45}, {6, 44}, POSE_LOOP(0)};
// No more hug
static AnimateEntityFrame anim_hug_release[] = {
    {2, 27}, {2, 26}, {1, 25}, {1, 24}, {1, 23},
    {1, 22}, {1, 21}, {1, 20}, POSE_END};
// Appears to show the hugging animation (with Alucard's bulge) but wings
// are pointed straight down - hug as we know it is sideways
static AnimateEntityFrame anim_unused[] = {
    {6, 41}, {6, 42}, {5, 43}, {6, 42}, POSE_LOOP(0)};
static AnimateEntityFrame anim_body_idle[] = {
    {2, 37}, {10, 38}, {16, 39}, POSE_END};

static s8 hitboxes[] = {
    0,  0,   0,  0,  4,  -12, 4,  28, 4,  -8, 4,  32, 4,  -4, 4,  28,
    4,  -12, 20, 12, 8,  -12, 16, 12, 4,  -4, 20, 4,  0,  -4, 16, 4,
    -8, -60, 16, 4,  -8, 52,  16, 4,  12, 0,  28, 8,  12, -4, 36, 4,
    8,  -4,  40, 4,  4,  4,   12, 12, 4,  0,  12, 8,  0,  0,  8,  16,
    -4, 4,   12, 12, 0,  4,   8,  12, 4,  4,  20, 12, 12, 0,  20, 8,
    0,  0,   24, 8,  4,  8,   28, 8,  0,  8,  24, 8,  8,  8,  24, 8};
static u8 hitboxOffsets[] = {
    0,  1,  2,  2,  1,  2,  0,  3,  4,  5,  6,  7,  8,  9,  10, 11,
    12, 12, 12, 12, 13, 14, 14, 14, 15, 13, 13, 16, 17, 18, 19, 20,
    18, 21, 22, 22, 23, 7,  7,  7,  0,  0,  0,  0,  0,  0,  0,  0};
static s16 yOffsets[] = {0, -72, -96, -96};
static u8 stepOptions[] = {
    DB_TORPEDO, DB_HUG_ATTACK, DB_WIND_ATTACK, DB_WIND_ATTACK};
extern s32 g_BossFlag;
extern EInit g_EInitDarkwingBat;

// Move a rotation angle toward the target, but only by an
// amount "increment". Return true if we reached the target.
static bool WakeupRotateHelper(s16* rot, s16 target, s16 increment) {
    if (abs(*rot - target) < increment) {
        *rot = target;
        return true;
    }
    if (*rot > target) {
        *rot -= increment;
    }
    if (*rot < target) {
        *rot += increment;
    }
    return false;
}

static s32 WindAttackHelper(s32 arg0) {
#ifdef VERSION_PSP
    Collider sp2C;
#endif
    Entity* other;
    s32 var_s5;
    s32 xVar, yVar;
    s32 var_s2;
    s32 i;

    for (i = 0; i < 0x10; i++) {
        if (!(Random() & 7) && (arg0 || !(g_Timer & 7))) {
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(
                    E_ID(DARKWING_WIND_DUST), g_CurrentEntity, other);
                other->posY.i.hi = 200; // Dust spawns on the ground
                if (g_CurrentEntity->facingLeft) {
                    other->posX.i.hi += (i * 8);
                } else {
                    other->posX.i.hi -= (i * 8);
                }
                other->scaleX = other->scaleY = 320 - (i * 8);
                other->facingLeft = g_CurrentEntity->facingLeft;
            }
        }
    }
    FntPrint("damage:%x\n", g_CurrentEntity->ext.darkwing.damage);
    if ((g_Player.unk60) == 2) {
        other = &PLAYER;
        other->velocityY -= FIX(1.0 / 8);
        if (g_CurrentEntity->facingLeft) {
            other->velocityX += FIX(1.0 / 8);
        } else {
            other->velocityX -= FIX(1.0 / 8);
        }
        var_s5 = g_Player.vram_flag & ~TOUCHING_GROUND;
#ifdef VERSION_PSP
        xVar = other->posX.i.hi;
        yVar = F(other->posY).i.hi + F(other->velocityY).i.hi;
        g_api.CheckCollision(xVar, yVar, &sp2C, 0);
        if (sp2C.effects & (EFFECT_UNK_0002 | EFFECT_SOLID)) {
            var_s5 = 1;
        }
        xVar = F(other->posX).i.hi + F(other->velocityX).i.hi;
        yVar = other->posY.i.hi;
        g_api.CheckCollision(xVar, yVar, &sp2C, 0);
        if (sp2C.effects & (EFFECT_UNK_0002 | EFFECT_SOLID)) {
            var_s5 = 1;
        }
        if (var_s5 == 0) {
#else
        if (var_s5 == 0 && g_PlayableCharacter == PLAYER_ALUCARD) {
#endif
            other->posX.val += other->velocityX;
            other->posY.val += other->velocityY;
        }
        if (other->velocityY > FIX(-4)) {
            return 1;
        }
        var_s2 = g_CurrentEntity->ext.darkwing.damage;
        g_Player.unk64 = (g_api.enemyDefs[275].attack / var_s2);
        g_Player.unk60 = 4;
        if (var_s2 > 2) {
            g_Player.unk60 = 0;
        }
        if (g_CurrentEntity->facingLeft) {
            other->velocityX = FIX(10) / var_s2;
        } else {
            other->velocityX = FIX(-10) / var_s2;
        }
        other->velocityY = FIX(-3) / var_s2;
        return 1;
    }
    if ((g_Player.unk60) || (arg0 == 0)) {
        return 0;
    }
    other = &PLAYER;
    var_s2 = g_CurrentEntity->posX.i.hi - other->posX.i.hi;
    if (g_CurrentEntity->facingLeft) {
        var_s2 = -var_s2;
    }
    if (var_s2 > 0x80U) {
        return 0;
    }
    var_s2 = other->velocityX;
    if (g_CurrentEntity->facingLeft) {
        var_s2 = -var_s2;
    }
    if ((g_Player.status & PLAYER_STATUS_UNK4000000) && (var_s2 > 0)) {
        other->posX.val -= other->velocityX / 2;
        return 0;
    }
    if (!(g_Player.status & (PLAYER_STATUS_AXEARMOR | PLAYER_STATUS_DEAD |
                             PLAYER_STATUS_UNK10000 | PLAYER_STATUS_INVINCIBLE |
                             PLAYER_STATUS_STONE | PLAYER_STATUS_CROUCH |
                             PLAYER_STATUS_MIST_FORM))) {
        g_Player.unk60 = 1;
        g_Player.unk64 = 0;
        g_Player.unk62 = 0;
        var_s2 = GetDistanceToPlayerX();
        var_s2 = (var_s2 - 48) / 24;
        if (var_s2 <= 0) {
            var_s2 = 1;
        }
        g_CurrentEntity->ext.darkwing.damage = var_s2;
        return 1;
    }
    return 0;
}

void EntityDarkwingBat(Entity* self) {
    s32 var_s4;
    Entity* other;
    s16 angle;
    s8* ptr_s3;

    s32 xVar;
    s32 yVar;

    if ((self->flags & FLAG_DEAD) && (self->step != DB_DEAD)) {
        SetStep(DB_DEAD);
    }
    switch (self->step) {
    case DB_INIT:
        InitializeEntity(g_EInitDarkwingBat);
        self->zPriority = (g_unkGraphicsStruct.g_zEntityCenter + 4);
        self->hitboxState = 0;
        other = self + 1;
        CreateEntityFromEntity(E_ID(BAT_WINGS), self, other);
        other->zPriority = ((self->zPriority) + 1);
        SetStep(DB_IDLE);
        break;
    case DB_IDLE:
        if (g_BossFlag & 1) {
            SetStep(DB_WAKEUP);
        }
        break;
    case DB_WAKEUP:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(anim_breathing, self)) {
                self->velocityY = FIX(3.0);
                self->drawFlags |= ENTITY_ROTATE;
                self->rotate = 0;
                self->animCurFrame = 7;
                self->step_s++;
            }
            break;
        case 1:
            MoveEntity();
            self->velocityY -= self->velocityY / 16;
            if (self->facingLeft) {
                self->velocityX += FIX(0.0625);
            } else {
                self->velocityX -= FIX(0.0625);
            }
            if (WakeupRotateHelper(&self->rotate, ROT(90), 0x20)) {
                self->velocityY = 0;
                self->drawFlags = ENTITY_DEFAULT;
                self->rotate = 0;
                self->animCurFrame = 0xE;
                SetSubStep(2);
            }
            break;
        case 2:
            MoveEntity();
            if (!AnimateEntity(anim_flapping, self)) {
                self->hitboxState = 3;
                self->ext.darkwing.unk85 = 1;
                SetStep(DB_FLYING);
            }
            break;
        }
        break;
    case DB_FLYING:
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 0x25;
            self->ext.darkwing.unk84 = 1;
            self->ext.darkwing.unk85 = 0;
            self->ext.darkwing.unk86 = 0;
            self->ext.darkwing.wasHit = 0;
            self->ext.darkwing.timer = 0xE0;
            self->velocityY = FIX(1.0);
            self->ext.darkwing.randTo3 = Random() & 3;
            self->step_s++;
            /* fallthrough */
        case 1:
            MoveEntity();
            if (self->hitFlags & 3) {
                self->ext.darkwing.wasHit = 1;
            }
            if ((self->ext.darkwing.wasHit) &&
                !(AnimateEntity(anim_body_idle, self))) {
                self->ext.darkwing.wasHit = 0;
                self->pose = 0;
                self->poseTimer = 0;
                self->animCurFrame = 0x25;
            }
            if (self->facingLeft) {
                self->velocityX += FIX(3.0 / 64);
                if (self->velocityX >= FIX(1.25)) {
                    self->velocityX = FIX(1.25);
                }
            } else {
                self->velocityX -= FIX(3.0 / 64);
                if (self->velocityX <= FIX(-1.25)) {
                    self->velocityX = FIX(-1.25);
                }
            }
            other = &PLAYER;
            yVar = other->posY.i.hi - self->posY.i.hi;
            yVar += yOffsets[self->ext.darkwing.randTo3];
            if (yVar < -8) {
                self->velocityY -= FIX(3.0 / 128);
                if (self->velocityY <= FIX(-5.0 / 8)) {
                    self->velocityY = FIX(-0.625);
                }
            }
            if (yVar > 8) {
                self->velocityY += FIX(3.0 / 64);
                if (self->velocityY >= FIX(0.625)) {
                    self->velocityY = FIX(0.625);
                }
            }
            xVar = other->posX.i.hi - self->posX.i.hi;
            if (self->facingLeft) {
                xVar = -xVar;
            }
            if (xVar > 0x60) {
                self->facingLeft ^= 1;
            }
            if (self->ext.darkwing.timer) {
                self->ext.darkwing.timer--;
            } else if (xVar > -0x58U) {
                SetStep(stepOptions[self->ext.darkwing.randTo3]);
                break;
            }
            if (self->facingLeft) {
                if (self->posX.i.hi > 0xC0) {
                    self->facingLeft = 0;
                }
            } else if (self->posX.i.hi < 0x40) {
                self->facingLeft = 1;
            }
            break;
        }
        break;
    case DB_TORPEDO:
        switch (self->step_s) {
        case 0:
            self->ext.darkwing.unk84 = 0;
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s++;
            /* fallthrough */
        case 1:
            if (!AnimateEntity(anim_torpedo_twist, self)) {
                self->attack = g_api.enemyDefs[274].attack;
                self->ext.darkwing.timer = 0;
                SetSubStep(2);
            }
            break;
        case 2:
            if (self->facingLeft) {
                self->velocityX = FIX(3.5);
            } else {
                self->velocityX = FIX(-3.5);
            }
            if (!(g_Timer & 3)) {
                PlaySfxPositional(SFX_UNK_RNZ1_SWISH_823);
            }
            if (self->ext.darkwing.timer) {
                if (!--self->ext.darkwing.timer) {
                    self->pose = 0;
                    self->poseTimer = 0;
                }
            } else if (self->hitFlags & 3) {
                self->ext.darkwing.timer = 0x20;
                self->pose = 0;
                self->poseTimer = 0;
            }
            if (self->ext.darkwing.timer) {
                self->velocityX /= 4;
                AnimateEntity(anim_spinning_halfopen, self);
            } else {
                AnimateEntity(anim_torpedo_twirl, self);
            }
            MoveEntity();
            other = &PLAYER;
            xVar = other->posX.i.hi - self->posX.i.hi;
            if (self->facingLeft) {
                xVar = -xVar;
            }
            if (xVar > 0x40) {
                self->attack = g_api.enemyDefs[273].attack;
                SetSubStep(3);
            }
            break;
        case 3:
            if (!AnimateEntity(anim_torpedo_crush, self)) {
                self->ext.darkwing.unk85 = 1;
                SetStep(DB_FLYING);
            }
            break;
        }
        break;
    case DB_WIND_ATTACK:
        switch (self->step_s) {
        case 0:
            self->ext.darkwing.unk85 = 1;
            self->ext.darkwing.unk84 = 1;
            self->ext.darkwing.timer = 0x20;
            self->step_s++;
            /* fallthrough */
        case 1:
            if (!--self->ext.darkwing.timer) {
                self->ext.darkwing.unk84 = 0;
                self->velocityX = 0;
                self->velocityY = 0;
                self->step_s++;
            case 2:
                if (!AnimateEntity(anim_prepare_wind_attack, self)) {
                    self->ext.darkwing.attackCycles = 0;
                    self->ext.darkwing.timer = 0;
                    SetSubStep(3);
                }
            }
            break;
        case 3:
            var_s4 = AnimateEntity(anim_wind_attack, self);
            if (!var_s4) {
                self->ext.darkwing.attackCycles += 1;
            }
            if ((!self->poseTimer) && (self->pose == 3)) {
                PlaySfxPositional(SFX_UNK_RNZ1_WIND_824);
            }
            var_s4 = 0;
            if ((self->pose > 3) && (self->pose < 8)) {
                var_s4 = 1;
            }
            if (self->ext.darkwing.timer) {
                self->ext.darkwing.timer--;
                var_s4 = 0;
            }
            var_s4 = WindAttackHelper(var_s4);
            if (var_s4) {
                self->ext.darkwing.timer = 0x40;
            }
            if ((self->ext.darkwing.attackCycles) > 3) {
                self->ext.darkwing.timer = 8;
                self->step_s++;
            }
            break;
        case 4:
            WindAttackHelper(0);
            if (!--self->ext.darkwing.timer) {
                self->ext.darkwing.unk85 = 1;
                SetStep(DB_FLYING);
            }
            break;
        }
        break;
    case DB_HUG_ATTACK:
        switch (self->step_s) {
        case 0:
            self->ext.darkwing.unk85 = 1;
            self->ext.darkwing.timer = 0x20;
            self->step_s++;
            /* fallthrough */
        case 1:
            if (!--self->ext.darkwing.timer) {
                self->ext.darkwing.unk84 = 0;
                self->animCurFrame = 0xB;
                other = &PLAYER;
                xVar = other->posX.i.hi - self->posX.i.hi;
                yVar = other->posY.i.hi - self->posY.i.hi;
                angle = ratan2(yVar, xVar);
                self->velocityX = (rcos(angle) * FIX(2.5)) >> 0xC;
                self->velocityY = (rsin(angle) * FIX(2.5)) >> 0xC;
                xVar = self->velocityX;
                if (self->facingLeft) {
                    xVar = -xVar;
                }
                if (xVar > 0) {
                    self->velocityX = 0;
                }
                self->step_s++;
            }
            break;
        case 2:
            MoveEntity();
            self->velocityY += FIX(0.03125);
            other = &PLAYER;
            yVar = other->posY.i.hi - self->posY.i.hi;
            if (yVar < 0x24) {
                self->step_s++;
            }
            break;
        case 3:
            if (!AnimateEntity(anim_hug, self)) {
                SetSubStep(6);
            }
            if ((self->pose) == 8) {
                other = &PLAYER;
                xVar = self->posX.i.hi;
                if (self->facingLeft) {
                    xVar += 0x20;
                } else {
                    xVar -= 0x20;
                }
                yVar = self->posY.i.hi + 0x28;
                xVar = other->posX.i.hi - xVar;
                yVar = other->posY.i.hi - yVar;
                if ((abs(xVar) < 0x10) && (abs(yVar) < 0x10) &&
                    !(g_Player.status &
                      (PLAYER_STATUS_AXEARMOR | PLAYER_STATUS_DEAD |
                       PLAYER_STATUS_UNK10000 | PLAYER_STATUS_INVINCIBLE |
                       PLAYER_STATUS_STONE | PLAYER_STATUS_CROUCH |
                       PLAYER_STATUS_MIST_FORM))) {
                    g_Player.unk60 = 1;
                    g_Player.unk64 = g_api.enemyDefs[276].attack;
                    g_Player.unk62 = 0;
                    SetSubStep(4);
                }
            }
            break;
        case 4:
            other = &PLAYER;
            xVar = other->posX.i.hi;
            if (self->facingLeft) {
                xVar -= 0x20;
            } else {
                xVar += 0x20;
            }
            yVar = other->posY.i.hi - 0x24;
            self->posX.i.hi = xVar;
            self->posY.i.hi = yVar;
            self->ext.darkwing.attackCycles = 0;
            self->step_s++;
            break;
        case 5:
            if (!AnimateEntity(anim_hugging, self)) {
                self->ext.darkwing.attackCycles += 1;
                g_Player.unk64 = g_api.enemyDefs[276].attack;
                g_Player.unk60 = 3;
            }
            self->ext.darkwing.timer++;
            if (self->ext.darkwing.timer & 1) {
                self->posY.i.hi += 1;
            } else {
                self->posY.i.hi -= 1;
            }
            if ((self->ext.darkwing.attackCycles) > 3) {
                g_Player.unk60 = 0;
                SetSubStep(6);
            }
            break;
        case 6:
            if (!AnimateEntity(anim_hug_release, self)) {
                self->step_s++;
            }
            break;
        case 7:
            self->animCurFrame = 0x25;
            self->ext.darkwing.unk84 = 1;
            self->ext.darkwing.unk85 = 1;
            self->ext.darkwing.unk86 = 1;
            self->drawFlags = ENTITY_ROTATE;
            // Strange value, potentially a mistake that should be 180 degrees
            self->rotate = 0x180;
            if (self->facingLeft) {
                self->velocityX = FIX(-0.1875);
            } else {
                self->velocityX = FIX(0.1875);
            }
            self->velocityY = FIX(-0.4375);
            self->ext.darkwing.timer = 0xC0;
            self->step_s++;
            /* fallthrough */
        case 8:
            MoveEntity();
            if (!--self->ext.darkwing.timer) {
                self->rotate = 0;
                self->drawFlags = ENTITY_DEFAULT;
                SetStep(DB_FLYING);
            }
            break;
        }
        break;
    // This step is possibly unreachable? Not certain. Could be related to
    // the unused animation.
    case DB_8:
        switch (self->step_s) {
        case 0:
            self->ext.darkwing.unk84 = 0;
            self->ext.darkwing.unk87 = 1;
            self->animCurFrame = 0x25;
            other = &PLAYER;
            xVar = other->posX.i.hi;
            if (self->facingLeft) {
                xVar += 0x10;
            } else {
                xVar -= 0x10;
            }
            yVar = other->posY.i.hi - 0x30;
            self->posX.i.hi = xVar;
            self->posY.i.hi = yVar;
            self->ext.darkwing.attackCycles = 0;
            self->ext.darkwing.timer = 0x18;
            self->step_s++;
            /* fallthrough */
        case 1:
            if (!--self->ext.darkwing.timer) {
                self->ext.darkwing.timer = 0x18;
                self->ext.darkwing.attackCycles += 1;
                g_Player.unk64 = g_api.enemyDefs[276].attack;
                g_Player.unk60 = 3;
            }
            if (self->ext.darkwing.timer & 1) {
                self->posY.i.hi += 1;
            } else {
                self->posY.i.hi -= 1;
            }
            if ((self->ext.darkwing.attackCycles) > 3) {
                g_Player.unk60 = 0;
                self->step_s++;
            }
            break;
        case 2:
            self->animCurFrame = 0x25;
            self->ext.darkwing.unk84 = 1;
            self->ext.darkwing.unk85 = 1;
            self->ext.darkwing.unk86 = 1;
            self->ext.darkwing.unk87 = 0;
            self->drawFlags = ENTITY_ROTATE;
            self->rotate = 0x180;
            if (self->facingLeft) {
                self->velocityX = FIX(-0.1875);
            } else {
                self->velocityX = FIX(0.1875);
            }
            self->velocityY = FIX(-0.4375);
            self->ext.darkwing.timer = 0x80;
            self->step_s++;
            /* fallthrough */
        case 3:
            MoveEntity();
            if (!--self->ext.darkwing.timer) {
                self->rotate = 0;
                self->drawFlags = ENTITY_DEFAULT;
                SetStep(DB_FLYING);
            }
            break;
        }
        break;
    case DB_DEAD:
        switch (self->step_s) {
        case 0:
            g_BossFlag |= 2;
#ifdef VERSION_US
            self->flags |= FLAG_UNK_00200000;
            self->hitboxState = 0;
#endif
            self->animCurFrame = 0x25;
            self->rotate = 0;
            self->drawFlags = ENTITY_DEFAULT;
            self->ext.darkwing.unk84 = 1;
            self->ext.darkwing.unk85 = 1;
            self->ext.darkwing.unk86 = 0;
            self->ext.darkwing.unk87 = 0;
            self->velocityX = 0;
            self->velocityY = FIX(-0.5);
            if (g_Player.unk60) {
                g_Player.unk60 = 0;
            }
            self->step_s++;
            /* fallthrough */
        case 1:
            MoveEntity();
            if (!AnimateEntity(anim_body_idle, self)) {
                SetSubStep(2);
            }
            break;
        case 2:
            MoveEntity();
            self->velocityY += FIX(0.0625);
            if (self->posY.i.hi > 0xC8) {
                PlaySfxPositional(SFX_UNK_RNZ1_EXPLODE_821);
                self->posY.i.hi = 0xC8;
                self->step_s++;
            }
            break;
        case 3:
            other = self + 1;
            if (!other->entityId) {
                self->step_s++;
                self->ext.darkwing.timer = 0x100;
                g_api.PlaySfx(SFX_FIREBALL_SHOT_A);
            }
            break;
        case 4:
            other = AllocEntity(&g_Entities[64], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(E_ID(FADING_FIREBALL), self, other);
                other->posX.i.hi += ((Random() & 0x3F) - 0x20);
                other->posY.i.hi += 8;
                other->zPriority = ((self->zPriority) + 1);
            }
            if (!(self->ext.darkwing.timer & 7)) {
                PlaySfxPositional(SFX_FIREBALL_SHOT_B);
            }
            if (!--self->ext.darkwing.timer) {
                self->animCurFrame = 0;
                g_BossFlag |= 4;
                self->step_s++;
            }
            break;
        case 5:
            break;
        }
        break;
    case 0xFF:
#include "../pad2_anim_debug.h"
    }
    ptr_s3 = &hitboxes[0];
    ptr_s3 += hitboxOffsets[self->animCurFrame] * 4;
    self->hitboxOffX = *ptr_s3++;
    self->hitboxOffY = *ptr_s3++;
    self->hitboxWidth = *ptr_s3++;
    self->hitboxHeight = *ptr_s3++;
}

extern EInit g_EInitDarkwingBat2;
// When you first walk into the room, Darkwing Bat is hanging from a golden
// perch at the top of the screen. It sticks out, compared to the large
// structure in the center. When DB is idle before the fight, the perch is
// part of its sprite, but once the fight starts, we create a static entity
// that sits there to keep showing the perch.
void EntityDarkwingBatPerch(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitDarkwingBat2);
        self->animCurFrame = 6;
    }
}

extern EInit g_EInitParticle;

// The many little puffs of dust that come from the ground during wind attack
void EntityDarkwingWindDust(Entity* self) {
    s32 yShift;

    if (!self->step) {
        InitializeEntity(g_EInitParticle);
        self->drawFlags = ENTITY_ROTATE | ENTITY_SCALEY | ENTITY_SCALEX;
        self->palette = PAL_FLAG(PAL_UNK_170);
        self->animSet = 5;
        self->animCurFrame = 1;
        self->palette = PAL_FLAG(PAL_UNK_195);
        self->blendMode = BLEND_TRANSP;
        self->zPriority += 8;
        yShift = (0x100 - self->scaleY) >> 4;
        self->posY.i.hi += yShift;
        // This looks more like an if-else but psp doesn't match that
        if (self->facingLeft) {
            self->velocityX = FIX(4.0);
            return;
        }
        self->velocityX = FIX(-4.0);
        return;
    }
    self->poseTimer += 1;
    MoveEntity();
    if (self->facingLeft) {
        self->velocityX -= FIX(0.125);
    } else {
        self->velocityX += FIX(0.125);
    }
    self->velocityY = FIX(-1.5);
    self->rotate -= 0x40;
    if (!(self->poseTimer & 1)) {
        self->animCurFrame += 1;
    }
    if (self->poseTimer > 36) {
        DestroyEntity(self);
    }
}

static AnimateEntityFrame anim_fireball[] = {
    {3, 1}, {3, 2}, {3, 3},  {3, 4},  {3, 5},  {3, 6},  {3, 7},
    {3, 8}, {3, 9}, {3, 10}, {3, 11}, {3, 12}, {3, 13}, POSE_END};

void EntityFadingFireball(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        self->animSet = 0xE;
        self->unk5A = 0x79;
        self->drawFlags = ENTITY_OPACITY;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        self->palette = 0x2E4;
        self->facingLeft = Random() & 1;
        self->velocityX = (Random() << 8) - FIX(0.5);
        self->velocityY = FIX(-2.0);
        self->ext.darkwing.fireballAccel = -(Random() * 0x10) - 0x100;
        /* fallthrough */
    case 1:
        MoveEntity();
        self->velocityY += self->ext.darkwing.fireballAccel;
        self->opacity -= 4;
        if (AnimateEntity(anim_fireball, self) == 0) {
            DestroyEntity(self);
        }
    }
}
