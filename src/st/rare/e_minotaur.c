// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rare.h"

extern EInit g_EInitMinotaur;
extern EInit g_EInitMinotaurAttackHitbox;
extern EInit g_EInitMinotaurFireball;
extern EInit g_EInitMinotaurSpitLiquid;
extern EInit g_EInitParticle;

static s16 sensors[] = {0, 40, 16, 0};
static s16 sensors_ground[] = {0, 40, 0, 4, 16, -4, -32, 0};

static AnimateEntityFrame anim_move[] = {
    {.duration = 6, .pose = 0x01}, {.duration = 14, .pose = 0x30},
    {.duration = 9, .pose = 0x02}, {.duration = 10, .pose = 0x03},
    {.duration = 9, .pose = 0x04}, {.duration = 6, .pose = 0x2D},
    {.duration = 6, .pose = 0x04}, {.duration = 8, .pose = 0x03},
    {.duration = 7, .pose = 0x02}, POSE_LOOP(0),
};
static AnimateEntityFrame anim_idle[] = {
    {.duration = 10, .pose = 0x05},
    {.duration = 9, .pose = 0x06},
    {.duration = 7, .pose = 0x07},
    {.duration = 10, .pose = 0x08},
    {.duration = 9, .pose = 0x07},
    {.duration = 7, .pose = 0x06},
    POSE_LOOP(0),
};
static AnimateEntityFrame anim_axe_swing_windup[] = {
    {.duration = 7, .pose = 0x0A},  {.duration = 5, .pose = 0x0B},
    {.duration = 6, .pose = 0x0C},  {.duration = 5, .pose = 0x2E},
    {.duration = 26, .pose = 0x2F}, {.duration = 3, .pose = 0x34},
    {.duration = 4, .pose = 0x0D},  POSE_END,
};
static AnimateEntityFrame anim_axe_swing_down[] = {
    {.duration = 6, .pose = 0x0E},
    {.duration = 2, .pose = 0x0F},
    {.duration = 2, .pose = 0x10},
    {.duration = 3, .pose = 0x11},
    {.duration = 3, .pose = 0x35},
    {.duration = 48, .pose = 0x11},
    POSE_END,
};
static AnimateEntityFrame anim_spit_attack[] = {
    {.duration = 1, .pose = 0x01},
    {.duration = 6, .pose = 0x13},
    {.duration = 5, .pose = 0x14},
    {.duration = 1, .pose = 0x31},
    {.duration = 28, .pose = 0x38},
    {.duration = 3, .pose = 0x32},
    {.duration = 3, .pose = 0x15},
    {.duration = 1, .pose = 0x33},
    POSE_END,
};
static AnimateEntityFrame anim_throw_fireballs[] = {
    {.duration = 1, .pose = 0x01},
    {.duration = 6, .pose = 0x16},
    {.duration = 21, .pose = 0x17},
    {.duration = 4, .pose = 0x18},
    {.duration = 3, .pose = 0x19},
    {.duration = 12, .pose = 0x1A},
    {.duration = 6, .pose = 0x1B},
    {.duration = 4, .pose = 0x1C},
    {.duration = 3, .pose = 0x1D},
    {.duration = 1, .pose = 0x36},
    {.duration = 22, .pose = 0x1D},
    {.duration = 6, .pose = 0x1C},
    {.duration = 5, .pose = 0x1E},
    {.duration = 4, .pose = 0x09},
    POSE_END,
};
static AnimateEntityFrame anim_block[] = {
    {.duration = 1, .pose = 0x01},
    {.duration = 5, .pose = 0x1F},
    {.duration = 22, .pose = 0x20},
    {.duration = 6, .pose = 0x1F},
    POSE_END,
};
static AnimateEntityFrame anim_axe_charge_attack[] = {
    {.duration = 1, .pose = 0x01},
    {.duration = 24, .pose = 0x11},
    {.duration = 8, .pose = 0x35},
    {.duration = 4, .pose = 0x06},
    {.duration = 4, .pose = 0x05},
    {.duration = 3, .pose = 0x12},
    {.duration = 3, .pose = 0x37},
    {.duration = 49, .pose = 0x12},
    POSE_END,
};
static AnimateEntityFrame anim_hit[] = {
    {.duration = 2, .pose = 0x21},
    {.duration = 6, .pose = 0x22},
    {.duration = 6, .pose = 0x21},
    POSE_LOOP(0),
};
static AnimateEntityFrame anim_death[] = {
    {.duration = 6, .pose = 0x39},  {.duration = 6, .pose = 0x3A},
    {.duration = 6, .pose = 0x25},  {.duration = 8, .pose = 0x27},
    {.duration = 8, .pose = 0x28},  {.duration = 8, .pose = 0x29},
    {.duration = 8, .pose = 0x2A},  {.duration = 8, .pose = 0x2B},
    {.duration = 24, .pose = 0x2C}, POSE_END,
};
static AnimateEntityFrame anim_spit[] = {
    {.duration = 1, .pose = 0x09},
    {.duration = 1, .pose = 0x0A},
    {.duration = 1, .pose = 0x0B},
    {.duration = 1, .pose = 0x0C},
    {.duration = 1, .pose = 0x0D},
    {.duration = 1, .pose = 0x0E},
    {.duration = 1, .pose = 0x0F},
    {.duration = 1, .pose = 0x10},
    {.duration = 1, .pose = 0x11},
    {.duration = 1, .pose = 0x12},
    {.duration = 1, .pose = 0x13},
    {.duration = 1, .pose = 0x14},
    POSE_END,
};
static AnimateEntityFrame anim_death_puff[] = {
    {.duration = 3, .pose = 0x01}, {.duration = 3, .pose = 0x02},
    {.duration = 3, .pose = 0x03}, {.duration = 3, .pose = 0x04},
    {.duration = 3, .pose = 0x05}, {.duration = 3, .pose = 0x06},
    {.duration = 3, .pose = 0x07}, {.duration = 3, .pose = 0x08},
    {.duration = 3, .pose = 0x09}, {.duration = 3, .pose = 0x0A},
    {.duration = 3, .pose = 0x0B}, {.duration = 3, .pose = 0x0C},
    {.duration = 3, .pose = 0x0D}, POSE_END,
};

// { hitboxOffX, hitboxOffY, hitboxWidth, hitboxHeight }
static s8 base_hitboxes[][4] = {
    {0, 0, 0, 0},      {0, 4, 16, 33},    {0, 8, 16, 28},  {-4, 3, 15, 33},
    {1, 4, 15, 33},    {12, 8, 12, 28},   {0, 0, 16, 29},  {-2, -4, 13, 33},
    {-3, 3, 13, 32},   {0, -3, 16, 31},   {-5, 6, 14, 31}, {1, 4, 17, 33},
    {3, 1, 16, 35},    {-1, 6, 17, 30},   {0, 10, 16, 25}, {-3, 14, 16, 25},
    {-13, 15, 15, 21}, {-12, 14, 16, 23}, {0, 3, 16, 31},  {-1, 9, 18, 27},
    {0, -1, 16, 33},   {-64, -88, 0, 0},  {4, 1, 16, 35},
};
// Indexed based off animCurFrame
static u8 base_hitbox_indices[] = {
    0,  1, 1,  1,  1,  1,  1,  1,  1,  2,  3,  4,  5,  6,  7,
    8,  9, 1,  10, 11, 12, 13, 1,  1,  14, 15, 16, 17, 18, 1,
    19, 1, 20, 1,  1,  1,  1,  21, 21, 21, 21, 21, 21, 21, 21,
    1,  5, 5,  1,  12, 11, 13, 6,  1,  1,  10, 22, 21, 21, 0,
};

// { hitboxOffX, hitboxOffY, hitboxWidth, hitboxHeight }
static s8 attack_hitboxes[][4] = {
    {0, 0, 0, 0},       {-38, -18, 17, 12}, {-34, -16, 17, 12},
    {-35, -15, 17, 10}, {-37, -15, 17, 10}, {-39, -16, 17, 12},
    {-36, -17, 17, 10}, {-8, -52, 11, 21},  {33, -31, 12, 11},
    {50, 7, 10, 11},    {33, -8, 14, 12},   {27, -36, 14, 12},
    {-5, -56, 10, 26},  {-44, -25, 24, 40}, {-34, 30, 17, 11},
    {-46, 11, 28, 10},  {-36, -5, 17, 11},  {-33, -14, 13, 13},
    {-40, -26, 12, 11}, {-30, -30, 11, 11}, {-23, -31, 12, 13},
    {-8, -29, 12, 16},  {-9, -25, 11, 18},  {-7, -27, 11, 17},
    {13, -21, 11, 11},  {20, -22, 11, 11},  {-21, -31, 11, 13},
    {-35, -6, 17, 11},  {-19, 20, 12, 12},  {-64, -88, 0, 0},
    {-26, -30, 13, 13}, {-38, -17, 13, 13}, {-25, -30, 13, 13},
};
// Indexed based off animCurFrame
static u8 attack_hitbox_indices[] = {
    0,  1,  1,  1,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11,
    12, 13, 14, 15, 16, 17, 17, 18, 19, 20, 21, 22, 23, 24, 25,
    26, 27, 28, 29, 29, 3,  29, 29, 29, 29, 29, 29, 29, 29, 29,
    1,  9,  9,  1,  30, 31, 17, 10, 14, 25, 15, 32, 29, 29, 0,
};

// { velocity, angle }
// There is data here for 10 fireballs but only the first 8 are released
static s32 fireball_config[][2] = {
    {FIX(6), ROT(22.5)},   {FIX(6), ROT(33.75)},  {FIX(6), ROT(45)},
    {FIX(6), ROT(56.25)},  {FIX(6), ROT(67.5)},   {FIX(6), ROT(78.75)},
    {FIX(6), ROT(90)},     {FIX(6), ROT(101.25)}, {FIX(6), ROT(112.5)},
    {FIX(6), ROT(123.75)},
};

// Present in PSX but stripped on PSP
// This looks like it might be unused sensor data
static s16 unused[] = {0, 64, 4, 0};

void EntityMinotaur(Entity* self) {
    enum MinotaurStep {
        INIT = 0,
        FALL_TO_GROUND = 1,
        IDLE_WAIT = 2,
        PLAYER_AGGRO = 3,
        MOVE = 5,
        CHOOSE_ATTACK = 6,
        AXE_SWING = 8,
        SPIT_LIQUID = 10,
        THROW_FIREBALLS = 12,
        BLOCK = 14,
        AXE_CHARGE = 16,
        UNK_UNUSED = 18,
        HIT_BY_PLAYER = 24,
        DEATH = 32,
    };

    Entity* entity;
    s32 i;
    s8* ptr;
    s32 playerVelocityX;

    if (self->step & 1 && self->hitFlags & 3) {
        SetStep(HIT_BY_PLAYER);
    }

    if (self->flags & FLAG_DEAD && self->step < DEATH) {
        SetStep(DEATH);
    }

    FntPrint("mino_step %x\n", self->step);
    switch (self->step) {
    case INIT:
        InitializeEntity(g_EInitMinotaur);
        entity = self + 1;
        CreateEntityFromCurrentEntity(E_MINOTAUR_ATTACK_HITBOX, entity);
        // fallthrough
    case FALL_TO_GROUND:
        if (UnkCollisionFunc3(sensors_ground) & 1) {
            SetStep(IDLE_WAIT);
        }
        break;
    case IDLE_WAIT:
        AnimateEntity(anim_idle, self);
        if (GetDistanceToPlayerX() < 0x68) {
            SetStep(PLAYER_AGGRO);
        }
        break;
    case PLAYER_AGGRO:
        if (!self->step_s) {
            if (!self->ext.minotaur.moveTimer) {
                self->ext.minotaur.moveTimer = 0x20;
            }
            self->step_s++;
        }

        AnimateEntity(anim_idle, self);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        if (self->ext.minotaur.moveTimer) {
            self->ext.minotaur.moveTimer--;
        }

        if (!self->ext.minotaur.moveTimer) {
            SetStep(MOVE);
        }

        entity = &PLAYER;
        playerVelocityX = entity->velocityX;
        if (self->facingLeft) {
            playerVelocityX = -playerVelocityX;
        }

        if (self->facingLeft == entity->facingLeft &&
            GetDistanceToPlayerX() > 0x48 && GetDistanceToPlayerX() < 0x60 &&
            g_Player.status & PLAYER_STATUS_UNK400 && playerVelocityX > 0) {
            SetStep(AXE_CHARGE);
        }

        // Looks to be triggered by player throwing a subweapon at the Minotaur
        if (self->facingLeft == entity->facingLeft &&
            g_Player.status & PLAYER_STATUS_UNK800) {
            SetStep(BLOCK);
        }

        break;
    case MOVE:
        if (!self->step_s) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.minotaur.moveAway = false;
            self->ext.minotaur.timer = 0x20;
            self->step_s++;
        }

        if (!AnimateEntity(anim_move, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }

        if (self->facingLeft ^ self->ext.minotaur.moveAway) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }

        UnkCollisionFunc2(sensors);
        if (GetDistanceToPlayerX() > 0x70) {
            self->ext.minotaur.moveAway = false;
        }

        if (GetDistanceToPlayerX() < 0x30) {
            self->ext.minotaur.moveAway = true;
        }

        if (!--self->ext.minotaur.timer) {
            SetStep(CHOOSE_ATTACK);
        }
        break;
    case CHOOSE_ATTACK:
        switch (self->step_s) {
        case 0:
            self->ext.minotaur.timer = 0x20;
            self->animCurFrame = 1;
            self->step_s++;
            break;
        case 1:
            if (!--self->ext.minotaur.timer) {
                self->step_s++;
            }
            break;
        case 2:
            entity = &PLAYER;
            if (GetDistanceToPlayerX() < 0x48) {
                if (self->facingLeft == entity->facingLeft) {
                    if (Random() & 3) {
                        SetStep(SPIT_LIQUID);
                    } else {
                        SetStep(AXE_CHARGE);
                    }
                } else if (Random() & 3) {
                    SetStep(AXE_CHARGE);
                } else {
                    SetStep(AXE_SWING);
                }
            } else if (Random() & 7) {
                SetStep(AXE_SWING);
            } else {
                SetStep(AXE_CHARGE);
            }
        }
        break;
    case SPIT_LIQUID:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(anim_spit_attack, self)) {
                self->step_s++;
            }
            break;
        case 1:
            self->ext.minotaur.timer = 0x40;
            PlaySfxPositional(SFX_MINOTAUR_BREATH_ATTACK);
            self->step_s++;
            // fallthrough
        case 2:
            if (!(g_Timer & 3)) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_MINOTAUR_SPIT_LIQUID, self, entity);
                    if (self->facingLeft) {
                        entity->posX.i.hi += 0x20;
                    } else {
                        entity->posX.i.hi -= 0x20;
                    }
                    entity->posY.i.hi -= 4;
                    entity->facingLeft = self->facingLeft;
                    entity->rotate = ROT(-112.5);
                    entity->zPriority = self->zPriority + 1;
                }
            }

            if (!--self->ext.minotaur.timer) {
                SetStep(PLAYER_AGGRO);
            }
        }
        break;
    case THROW_FIREBALLS:
        // This attack appears to be unused in game as this case is never called
        if (!AnimateEntity(anim_throw_fireballs, self)) {
            SetStep(PLAYER_AGGRO);
        }

        if (!self->poseTimer && self->pose == 8) {
            // nb. there is data present for 10 fireballs but only 8 are
            // released
            for (i = 0; i < 8; i++) {
                entity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_MINOTAUR_FIREBALL, self, entity);
                    entity->posY.i.hi += 0x28;
                    entity->facingLeft = self->facingLeft;
                    entity->params = i;
                }
            }
        }

        break;
    case BLOCK:
        if (!AnimateEntity(anim_block, self)) {
            SetStep(PLAYER_AGGRO);
        }
        break;
    case AXE_CHARGE:
        if (!self->step_s) {
            self->velocityX = 0;
            self->velocityY = 0;
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;
        }

        UnkCollisionFunc2(sensors);
        if (!AnimateEntity(anim_axe_charge_attack, self)) {
            SetStep(PLAYER_AGGRO);
        }

        self->velocityX -= self->velocityX / 16;
        if (!self->poseTimer && self->pose == 7) {
            PlaySfxPositional(SFX_MINOTAUR_ATTACK);
            if (self->facingLeft) {
                self->velocityX = FIX(4.0);
            } else {
                self->velocityX = FIX(-4.0);
            }
        }
        break;
    case AXE_SWING:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(anim_axe_swing_windup, self)) {
                self->velocityY = 0;
                if (self->facingLeft) {
                    self->velocityX = FIX(4.0);
                } else {
                    self->velocityX = FIX(-4.0);
                }
                self->step_s++;
                PlaySfxPositional(SFX_BOSS_WING_FLAP);
                SetSubStep(1);
            }
            break;
        case 1:
            UnkCollisionFunc2(sensors);
            self->velocityX -= self->velocityX / 16;
            if (!AnimateEntity(anim_axe_swing_down, self)) {
                SetStep(PLAYER_AGGRO);
            }
            break;
        }
        break;
    case HIT_BY_PLAYER:
        if (!AnimateEntity(anim_hit, self)) {
            SetStep(PLAYER_AGGRO);
        }
        break;
    case UNK_UNUSED:
        // This state appears unused and displays one of the death frames of the
        // Minotaur which flips directions.
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 0x2B;
            self->step_s++;
            break;
        case 1:
            self->facingLeft ^= 1;
            self->step_s++;
            break;
        case 2:
            self->animCurFrame = 1;
            SetStep(PLAYER_AGGRO);
            break;
        }
        break;
    case DEATH:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s++;
            // fallthrough
        case 1:
            if (UnkCollisionFunc3(sensors_ground) & 1) {
                self->ext.minotaur.deathPuffPosX = -0x10;
                self->ext.minotaur.timer = 0;
                self->step_s++;
            }
            break;
        case 2:
            if (!AnimateEntity(anim_death, self)) {
                self->step_s = 3;
            }
            self->ext.minotaur.timer &= 1;
            // fallthrough
        case 3:
            if (self->ext.minotaur.timer & 1) {
                entity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_MINOTAUR_DEATH_PUFF, self, entity);
                    entity->posX.i.hi += self->ext.minotaur.deathPuffPosX;
                    entity->posY.i.hi += 0x20;
                    entity->zPriority = self->zPriority + 1;
                    entity->params = abs(self->ext.minotaur.deathPuffPosX) +
                                     (self->ext.minotaur.timer >> 1);
                }

                // Puff position moves left to right as the death plays out
                // Once it hits a rightmost position it loops back around to the
                // starting position on the left again.
                self->ext.minotaur.deathPuffPosX += 8;
                if (self->ext.minotaur.deathPuffPosX > 0x10) {
                    self->ext.minotaur.deathPuffPosX = -0x10;
                }
            }

            if (!(g_Timer & 7)) {
                PlaySfxPositional(SFX_OUIJA_TABLE_DEATH);
            }

            if (self->ext.minotaur.timer++ > 0x20) {
                self->step_s++;
            }
            break;
        case 4:
            DestroyEntity(self);
            DestroyEntity(self + 1);
            return;
        }
        break;
    case 0xFF:
#include "../pad2_anim_debug.h"
    }

    ptr = *base_hitboxes;
    ptr += base_hitbox_indices[self->animCurFrame] * 4;
    self->hitboxOffX = *ptr++;
    self->hitboxOffY = *ptr++;
    self->hitboxWidth = *ptr++;
    self->hitboxHeight = *ptr++;
}

void EntityMinotaurAttackHitbox(Entity* self) {
    s8* ptr;
    Entity* parent;
    s32 animCurFrame;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitMinotaurAttackHitbox);
        self->animCurFrame = 0;
        // fallthrough
    case 1:
        parent = self - 1;
        if (parent->entityId != E_MINOTAUR) {
            DestroyEntity(self);
            return;
        }

        animCurFrame = parent->animCurFrame;
        self->facingLeft = parent->facingLeft;
        self->posX.val = parent->posX.val;
        self->posY.val = parent->posY.val;
        self->hitboxState = 1;

        ptr = *attack_hitboxes;
        ptr += attack_hitbox_indices[animCurFrame] * 4;
        self->hitboxOffX = *ptr++;
        self->hitboxOffY = *ptr++;
        self->hitboxWidth = *ptr++;
        self->hitboxHeight = *ptr++;
        break;
    }
}

// This entity appears unused in game as the entity step
// which triggers it to spawn is never called.
void EntityMinotaurFireball(Entity* self) {
    s32 angle;
    s32 speed;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitMinotaurFireball);
        // Fireballs fly out in a sort of clock hands arrangement
        speed = fireball_config[self->params][0];
        angle = fireball_config[self->params][1];
        self->velocityX = (-speed * rcos(angle)) >> 0xC;
        self->velocityY = (-speed * rsin(angle)) >> 0xC;
        if (self->facingLeft) {
            self->velocityX = -self->velocityX;
        }
        // fallthrough
    case 1:
        MoveEntity();
        // Fireballs slowly fall over time
        self->velocityY += FIX(0.125);
        break;
    }
}

void EntityMinotaurSpitLiquid(Entity* self) {
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitMinotaurSpitLiquid);
        self->palette = PAL_FLAG(PAL_MINOTAUR_SPIT);
        if (self->facingLeft) {
            self->rotate = -self->rotate;
        }
        self->facingLeft = 0;
        // Spit flies slightly up and down randomly
        self->rotate += ROT(11.25) - Random();
        angle = self->rotate;
        self->velocityX = rsin(angle) * 0x24;
        self->velocityY = rcos(angle) * -0x24;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->drawFlags = FLAG_DRAW_OPACITY | FLAG_DRAW_ROTATE |
                          FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
        self->scaleX = 0x40;
        self->scaleY = 0x80;
        self->opacity = 0x80;
        break;
    case 1:
        MoveEntity();
        self->scaleX += 0x10;
        self->scaleY += 0xE;
        self->opacity -= 1;
        if (!AnimateEntity(anim_spit, self)) {
            DestroyEntity(self);
        }
        break;
    }
}

// A purple cloud which rises and fades away over time
void EntityMinotaurDeathPuff(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        self->animSet = 0xE;
        self->palette = PAL_MINOTAUR_DEATH_PUFF;
        self->unk5A = 0x79;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->drawFlags =
            FLAG_DRAW_OPACITY | FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
        self->scaleY = 0x180;
        self->scaleX = 0xA0;
        self->opacity = 0x60 - (self->params * 2);
        self->velocityY = FIX(-3.0);
        self->facingLeft = Random() & 1;
        // fallthrough
    case 1:
        MoveEntity();
        self->velocityY -= FIX(0.0625);
        self->opacity -= 2;
        self->scaleX += 8;
        self->scaleY -= 4;

        if (!self->opacity) {
            DestroyEntity(self);
        } else if (!AnimateEntity(anim_death_puff, self)) {
            DestroyEntity(self);
        }
        break;
    }
}
