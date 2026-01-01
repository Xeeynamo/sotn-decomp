// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rare.h"

extern EInit g_EInitWerewolf;
extern EInit g_EInitWerewolfAttackHitbox;
extern EInit g_EInitWerewolfEnergyWave;
extern EInit g_EInitInteractable;
extern s16* sprites_rare_4[];

static s16 sensors[] = {0, 27, 4, 0};
static s16 sensors_ground[] = {0, 27, 0, 4, 4, -4, -8, 0};

static AnimateEntityFrame anim_idle[] = {
    {.duration = 6, .pose = 0x01},
    {.duration = 6, .pose = 0x02},
    {.duration = 6, .pose = 0x03},
    {.duration = 6, .pose = 0x02},
    POSE_LOOP(0),
};
static AnimateEntityFrame anim_head_tilt[] = {
    {.duration = 4, .pose = 0x04}, {.duration = 4, .pose = 0x05},
    {.duration = 6, .pose = 0x06}, {.duration = 4, .pose = 0x05},
    {.duration = 6, .pose = 0x04}, {.duration = 16, .pose = 0x02},
    {.duration = 2, .pose = 0x04}, POSE_LOOP(0),
};
static AnimateEntityFrame anim_punch[] = {
    {.duration = 8, .pose = 0x0B}, {.duration = 4, .pose = 0x0D},
    {.duration = 6, .pose = 0x0F}, {.duration = 4, .pose = 0x0D},
    {.duration = 6, .pose = 0x0F}, {.duration = 7, .pose = 0x0D},
    {.duration = 8, .pose = 0x0B}, {.duration = 3, .pose = 0x0C},
    {.duration = 2, .pose = 0x0E}, {.duration = 2, .pose = 0x10},
    {.duration = 1, .pose = 0x11}, {.duration = 1, .pose = 0x12},
    {.duration = 1, .pose = 0x13}, {.duration = 2, .pose = 0x14},
    {.duration = 2, .pose = 0x0B}, POSE_END,
};
static AnimateEntityFrame anim_energy_wave_jump[] = {
    {.duration = 1, .pose = 0x01},
    {.duration = 4, .pose = 0x24},
    {.duration = 6, .pose = 0x25},
    POSE_END,
};
static AnimateEntityFrame anim_energy_wave[] = {
    {.duration = 8, .pose = 0x1A},
    {.duration = 6, .pose = 0x1B},
    {.duration = 7, .pose = 0x1C},
    {.duration = 6, .pose = 0x1D},
    {.duration = 9, .pose = 0x1E},
    {.duration = 12, .pose = 0x1F},
    POSE_END,
};
static AnimateEntityFrame anim_slide_attack[] = {
    {.duration = 3, .pose = 0x0A},
    {.duration = 3, .pose = 0x22},
    {.duration = 3, .pose = 0x21},
    {.duration = 17, .pose = 0x20},
    {.duration = 9, .pose = 0x21},
    {.duration = 9, .pose = 0x22},
    {.duration = 9, .pose = 0x23},
    {.duration = 5, .pose = 0x0A},
    POSE_END,
};
static AnimateEntityFrame anim_charge_init[] = {
    {.duration = 12, .pose = 0x02},
    {.duration = 6, .pose = 0x24},
    {.duration = 1, .pose = 0x3F},
    {.duration = 1, .pose = 0x25},
    {.duration = 1, .pose = 0x3F},
    {.duration = 1, .pose = 0x25},
    {.duration = 1, .pose = 0x3F},
    {.duration = 1, .pose = 0x25},
    {.duration = 1, .pose = 0x3F},
    {.duration = 1, .pose = 0x25},
    {.duration = 1, .pose = 0x3F},
    {.duration = 1, .pose = 0x25},
    POSE_END,
};
static AnimateEntityFrame anim_charge_attack[] = {
    {.duration = 3, .pose = 0x26},  {.duration = 3, .pose = 0x27},
    {.duration = 2, .pose = 0x28},  {.duration = 8, .pose = 0x29},
    {.duration = 4, .pose = 0x28},  {.duration = 4, .pose = 0x27},
    {.duration = 3, .pose = 0x2A},  {.duration = 4, .pose = 0x2B},
    {.duration = 5, .pose = 0x2C},  {.duration = 4, .pose = 0x2D},
    {.duration = 27, .pose = 0x0A}, POSE_END,
};
static AnimateEntityFrame anim_death_pain[] = {
    {.duration = 15, .pose = 0x0A}, {.duration = 5, .pose = 0x25},
    {.duration = 5, .pose = 0x24},  {.duration = 4, .pose = 0x0B},
    {.duration = 42, .pose = 0x2E}, POSE_END,
};
static AnimateEntityFrame anim_death_melt[] = {
    {.duration = 7, .pose = 0x2E},
    {.duration = 3, .pose = 0x2F},
    {.duration = 5, .pose = 0x2E},
    {.duration = 6, .pose = 0x2F},
    {.duration = 10, .pose = 0x30},
    {.duration = 10, .pose = 0x35},
    {.duration = 4, .pose = 0x31},
    {.duration = 24, .pose = 0x35},
    {.duration = 9, .pose = 0x31},
    {.duration = 8, .pose = 0x32},
    {.duration = 6, .pose = 0x33},
    {.duration = 77, .pose = 0x34},
    POSE_END,
};
static AnimateEntityFrame anim_spin_attack[] = {
    {.duration = 4, .pose = 0x0C},
    {.duration = 2, .pose = 0x0B},
    {.duration = 2, .pose = 0x0A},
    {.duration = 1, .pose = 0x09},
    POSE_END,
};

// Most of these are frames from the animations above and thus not particularly
// interesting Of note are pose frames 0x07 and 0x08 which appear unused and
// look to represent perhaps a scared or cowering Werewolf.
static AnimateEntityFrame anim_werewolf_unused[] = {
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
    {0, 0, 0, 0},     {0, 7, 10, 18},   {0, 6, 7, 18},    {0, 6, 6, 19},
    {0, 5, 6, 20},    {-1, 4, 5, 20},   {0, 3, 4, 21},    {0, -1, 7, 16},
    {2, 12, 9, 12},   {1, 7, 8, 17},    {0, 8, 8, 17},    {-1, 8, 8, 17},
    {0, 1, 7, 8},     {0, 3, 13, 12},   {0, 2, 12, 15},   {0, 5, 8, 22},
    {6, 8, 10, 16},   {7, 14, 7, 17},   {-7, 13, 7, 16},  {-4, 2, 10, 11},
    {-4, 4, 9, 11},   {10, 15, 10, 13}, {7, 14, 7, 12},   {5, 13, 9, 12},
    {1, 12, 9, 12},   {3, 6, 7, 18},    {2, 11, 7, 15},   {2, 1, 11, 14},
    {1, -4, 14, 8},   {6, 0, 18, 10},   {5, -5, 19, 10},  {5, 0, 13, 7},
    {0, 0, 8, 9},     {-1, 2, 6, 13},   {-16, -21, 0, 0}, {-17, -10, 0, 0},
    {-16, -15, 0, 0},
};
// Indexed based off animCurFrame
static u8 base_hitbox_indices[] = {
    0,  1,  1,  1,  2,  3,  4,  5,  6,  7,  8,  9,  9,  9,  9,  10,
    11, 11, 11, 11, 11, 12, 12, 12, 13, 14, 15, 16, 17, 18, 19, 20,
    21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 32, 33, 34, 34,
    34, 34, 34, 34, 34, 34, 35, 35, 35, 35, 35, 36, 36, 36, 36, 26};

// { hitboxOffX, hitboxOffY, hitboxWidth, hitboxHeight }
static s8 attack_hitboxes[][4] = {
    {0, 0, 0, 0},     {-16, -21, 0, 0}, {-19, -3, 7, 4},  {-19, -3, 6, 9},
    {-20, -3, 10, 7}, {-28, -3, 12, 4}, {-32, -3, 18, 4}, {-48, -3, 7, 4},
    {25, 8, 6, 9},    {20, -6, 8, 8},   {-25, 14, 4, 7},  {10, 22, 4, 5},
    {10, 23, 4, 6},   {1, 23, 24, 4},   {-8, 23, 21, 4},  {-17, -10, 0, 0},
    {-16, -15, 0, 0},
};
// Indexed based off animCurFrame
static u8 attack_hitbox_indices[] = {
    0,  1,  1, 1, 1, 1, 1,  1,  1,  1,  1,  1,  1,  1,  1,  2,
    3,  4,  5, 6, 7, 1, 1,  1,  1,  1,  1,  8,  9,  10, 11, 12,
    13, 14, 1, 1, 1, 1, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    1,  1,  1, 1, 1, 1, 15, 15, 15, 15, 15, 16, 16, 16, 16, 1,
};

void EntityWerewolf(Entity* self) {
    enum WerewolfStep {
        INIT = 0,
        FALL_TO_GROUND = 1,
        IDLE_WAIT = 2,
        PLAYER_AGGRO = 3,
        CHOOSE_ATTACK = 4,
        MOVE = 5,
        PUNCH_ATTACK = 6,
        ENERGY_WAVE_ATTACK = 8,
        SLIDE_ATTACK = 10,
        CHARGE_ATTACK = 12,
        SPIN_ATTACK = 14,
        DEATH = 24,
    };

    Entity* entity;
    s8* ptr;
    s32 velocityX;

    if (self->flags & FLAG_DEAD && self->step < DEATH) {
        SetStep(DEATH);
    }

    switch (self->step) {
    case INIT:
        InitializeEntity(g_EInitWerewolf);
        entity = self + 1;
        CreateEntityFromCurrentEntity(E_WEREWOLF_ATTACK_HITBOX, entity);
        // fallthrough
    case FALL_TO_GROUND:
        if (UnkCollisionFunc3(sensors_ground) & 1) {
            SetStep(IDLE_WAIT);
        }
        break;
    case IDLE_WAIT:
        AnimateEntity(anim_idle, self);
        if (GetDistanceToPlayerX() < 0x60) {
            SetStep(PLAYER_AGGRO);
        }
        break;
    case PLAYER_AGGRO:
        if (!self->step_s) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (!self->ext.werewolf.moveTimer) {
                self->ext.werewolf.moveTimer = 0x20;
            }
            self->step_s++;
        }

        if (!AnimateEntity(anim_idle, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }

        if (self->ext.werewolf.moveTimer) {
            self->ext.werewolf.moveTimer--;
        } else {
            SetStep(MOVE);
        }

        entity = &PLAYER;
        velocityX = entity->velocityX;
        if (self->facingLeft) {
            velocityX = -velocityX;
        }

        // If the player is already close enough, we can punch right away
        if (self->facingLeft == entity->facingLeft &&
            GetDistanceToPlayerX() < 0x38 && velocityX > 0) {
            SetStep(PUNCH_ATTACK);
        }
        break;
    case MOVE:
        if (!self->step_s) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.werewolf.moveAway = false;
            self->ext.werewolf.timer = 0x20;
            self->step_s++;
        }

        if (!AnimateEntity(anim_head_tilt, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }

        if (self->facingLeft ^ self->ext.werewolf.moveAway) {
            self->velocityX = FIX(1.0);
        } else {
            self->velocityX = FIX(-1.0);
        }

        UnkCollisionFunc2(sensors);
        if (GetDistanceToPlayerX() > 0x70) {
            self->ext.werewolf.moveAway = false;
        }

        if (GetDistanceToPlayerX() < 0x30) {
            self->ext.werewolf.moveAway = true;
        }

        if (!--self->ext.werewolf.timer) {
            SetStep(CHOOSE_ATTACK);
        }
        break;
    case CHOOSE_ATTACK:
        if (!AnimateEntity(anim_idle, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }

        switch (self->step_s) {
        case 0:
            self->ext.werewolf.timer = 0x20;
            self->step_s++;
            break;
        case 1:
            if (!--self->ext.werewolf.timer) {
                self->step_s++;
            }
            break;
        case 2:
            entity = &PLAYER;
            if (self->facingLeft == entity->facingLeft) {
                if (GetDistanceToPlayerX() < 0x40) {
                    if (Random() & 3) {
                        SetStep(SLIDE_ATTACK);
                    } else {
                        SetStep(PUNCH_ATTACK);
                    }
                } else if (Random() & 1) {
                    SetStep(CHARGE_ATTACK);
                } else {
                    SetStep(ENERGY_WAVE_ATTACK);
                }
            } else if (GetDistanceToPlayerX() < 0x38) {
                if (Random() & 1) {
                    SetStep(SLIDE_ATTACK);
                } else {
                    SetStep(ENERGY_WAVE_ATTACK);
                }
            } else if (Random() & 1) {
                SetStep(CHARGE_ATTACK);
            } else {
                SetStep(SPIN_ATTACK);
            }
            break;
        }
        break;
    case PUNCH_ATTACK:
        if (!AnimateEntity(anim_punch, self)) {
            SetStep(PLAYER_AGGRO);
        }

        if (!self->poseTimer && self->pose == 8) {
            PlaySfxPositional(SFX_WHIP_TWIRL_SWISH);
        }

        break;
    case ENERGY_WAVE_ATTACK:
        switch (self->step_s) {
        case 0:
            // Jump into the air
            if (!AnimateEntity(anim_energy_wave_jump, self)) {
                self->animCurFrame = 0x2D;
                self->velocityX = FIX(-2.0);
                if (self->facingLeft) {
                    self->velocityX = -self->velocityX;
                }
                self->velocityY = FIX(-2.0);
                SetSubStep(1);
            }
            break;
        case 1:
            if (UnkCollisionFunc3(&sensors_ground) & 1) {
                self->step_s++;
            }
            break;
        case 2:
            // After we've landed on the ground, spawn an energy wave projectile
            if (!AnimateEntity(anim_energy_wave, self)) {
                SetStep(PLAYER_AGGRO);
            }

            if (!self->poseTimer && self->pose == 4) {
                PlaySfxPositional(SFX_OUIJA_TABLE_DEATH);
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_WEREWOLF_ENERGY_WAVE, self, entity);
                    entity->facingLeft = self->facingLeft;
                    entity->posY.i.hi -= 0x10;
                }
            }
            break;
        }
        break;
    case SLIDE_ATTACK:
        if (!self->step_s) {
            self->velocityX = 0;
            self->velocityY = 0;
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;
        }

        UnkCollisionFunc2(sensors);
        if (!AnimateEntity(anim_slide_attack, self)) {
            SetStep(PLAYER_AGGRO);
        }

        self->velocityX -= self->velocityX / 16;
        if (!self->poseTimer && self->pose == 3) {
            PlaySfxPositional(SFX_SCRAPE_B);
            if (self->facingLeft) {
                self->velocityX = FIX(4.0);
            } else {
                self->velocityX = FIX(-4.0);
            }
        }
        break;
    case CHARGE_ATTACK:
        switch (self->step_s) {
        case 0:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;
            // fallthrough
        case 1:
            if (!AnimateEntity(anim_charge_init, self)) {
                SetSubStep(2);
            }
            break;
        case 2:
            if (self->facingLeft) {
                self->velocityX = FIX(6.0);
            } else {
                self->velocityX = FIX(-6.0);
            }

            PlaySfxPositional(SFX_ARROW_SHOT_A);
            self->step_s++;
            // fallthrough
        case 3:
            UnkCollisionFunc2(sensors);
            self->velocityX -= self->velocityX / 32;
            if (!AnimateEntity(anim_charge_attack, self)) {
                SetStep(PLAYER_AGGRO);
            }
            break;
        }
        break;
    case SPIN_ATTACK:
        switch (self->step_s) {
        case 0:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (self->facingLeft) {
                self->velocityX = FIX(4.5);
            } else {
                self->velocityX = FIX(-4.5);
            }
            self->velocityY = 0;
            self->step_s++;
            // fallthrough
        case 1:
            if (!AnimateEntity(anim_spin_attack, self)) {
                self->ext.werewolf.timer = 0x20;
                self->animCurFrame = 0x15;
                self->drawFlags |= FLAG_DRAW_ROTATE;
                self->step_s++;
                self->velocityY = FIX(-4.0);
                self->step_s = 3;
            }
            break;
        case 2:
            UnkCollisionFunc2(sensors);
            self->rotate -= ROT(22.5);
            if (!(g_Timer & 8)) {
                PlaySfxPositional(SFX_WEREWOLF_SPIN_ATTACK);
            }

            if (!(self->ext.werewolf.timer & 3)) {
                entity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_WEREWOLF_AFTERIMAGE, self, entity);
                    entity->facingLeft = self->facingLeft;
                    entity->rotate = self->rotate;
                    entity->params = self->animCurFrame;
                }
            }

            if (!--self->ext.werewolf.timer) {
                self->drawFlags = FLAG_DRAW_DEFAULT;
                self->animCurFrame = 0xA;
                self->ext.werewolf.timer = 0x10;
                self->step_s = 4;
            }
            break;
        case 3:
            self->rotate -= ROT(22.5);
            if (!(g_Timer & 8)) {
                PlaySfxPositional(SFX_WEREWOLF_SPIN_ATTACK);
            }

            if (!(g_Timer & 3)) {
                entity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_WEREWOLF_AFTERIMAGE, self, entity);
                    entity->facingLeft = self->facingLeft;
                    entity->rotate = self->rotate;
                    entity->params = self->animCurFrame;
                }
            }

            if (UnkCollisionFunc3(sensors_ground) & 1) {
                self->drawFlags = FLAG_DRAW_DEFAULT;
                self->animCurFrame = 0xA;
                self->ext.werewolf.timer = 0x10;
                self->step_s = 4;
            }
            break;
        case 4:
            if (!--self->ext.werewolf.timer) {
                SetStep(PLAYER_AGGRO);
            }
            break;
        }
        break;
    case DEATH:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            self->velocityX = FIX(2.0);
            if (self->facingLeft) {
                self->velocityX = -self->velocityX;
            }
            self->velocityY = FIX(-2.0);
            self->rotate = 0;
            self->animCurFrame = 7;
            self->step_s++;
            // fallthrough
        case 1:
            if (UnkCollisionFunc3(sensors_ground) & 1) {
                self->step_s++;
            }
            break;
        case 2:
            if (!AnimateEntity(anim_death_pain, self)) {
                entity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_WEREWOLF_DEATH_FLAMES, self, entity);
                    entity->posY.i.hi += 0x1B;
                    entity->zPriority = self->zPriority;
                }
                SetSubStep(3);
            }
            break;
        case 3:
            if (!AnimateEntity(anim_death_melt, self)) {
                SetSubStep(4);
            }
            break;
        case 4:
            self->animCurFrame = 0;
            DestroyEntity(self);
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

void EntityWerewolfAttackHitbox(Entity* self) {
    s32 animCurFrame;
    s8* hitboxPtr;
    Entity* werewolf;

    if (!self->step) {
        InitializeEntity(g_EInitWerewolfAttackHitbox);
        self->animCurFrame = 0;
    }

    werewolf = self - 1;
    if (werewolf->entityId != E_WEREWOLF) {
        DestroyEntity(self);
        return;
    }

    animCurFrame = werewolf->animCurFrame;
    self->facingLeft = werewolf->facingLeft;
    self->posX.val = werewolf->posX.val;
    self->posY.val = werewolf->posY.val;

    hitboxPtr = *attack_hitboxes;
    hitboxPtr += attack_hitbox_indices[animCurFrame] * 4;
    self->hitboxOffX = *hitboxPtr++;
    self->hitboxOffY = *hitboxPtr++;
    self->hitboxWidth = *hitboxPtr++;
    self->hitboxHeight = *hitboxPtr++;
}

void EntityWerewolfEnergyWave(Entity* self) {
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitWerewolfEnergyWave);
        self->animCurFrame = 0x39;
        if (self->facingLeft) {
            self->velocityX = FIX(4.5);
        } else {
            self->velocityX = FIX(-4.5);
        }
        self->velocityY = 0;
        // fallthrough
    case 1:
        MoveEntity();
        self->velocityY -= FIX(5.0 / 64.0);
        angle = ratan2(-self->velocityY, abs(self->velocityX));

        // Change the displayed sprite as the energy wave angles up
        self->animCurFrame = 0x36;
        if (angle > 0x80) {
            self->animCurFrame = 0x37;
        }
        if (angle > 0x140) {
            self->animCurFrame = 0x38;
        }
        if (angle > 0x180) {
            self->animCurFrame = 0x39;
        }
        break;
    }
}

// Displays a trailing opaque effect behind the arcing spin jump attack
// Params here is the animCurFrame of the main Werewolf entity
void EntityWerewolfSpinAttackAfterImage(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitWerewolf);
        self->palette = g_EInitWerewolf[3] + PAL_FLAG(9);
        self->hitboxState = 0;
        self->flags |= FLAG_UNK_00200000 | FLAG_UNK_2000;
        self->drawFlags = FLAG_DRAW_OPACITY | FLAG_DRAW_ROTATE;
        self->animCurFrame = self->params;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->opacity = 0x60;
    }

    self->ext.werewolf.timer++;
    if ((!self->ext.werewolf.timer) & 1) {
        self->animCurFrame = 0;
    } else {
        self->animCurFrame = self->params;
    }

    self->opacity -= 8;
    if (!self->opacity) {
        DestroyEntity(self);
    }
}

static SVECTOR death_flame_vector[] = {
    {.vx = -16, .vy = -24, .vz = -18, .pad = 0},
    {.vx = 16, .vy = -24, .vz = -18, .pad = 0},
    {.vx = -16, .vy = 24, .vz = -18, .pad = 0},
    {.vx = 16, .vy = 24, .vz = -18, .pad = 0}};

Primitive* FindFirstUnkPrim2(Primitive* prim, u8 index);
void EntityWerewolfDeathFlames(Entity* self) {
    long otz;
    SVECTOR svecTwo;
    VECTOR vec;
    MATRIX matrix;

    Primitive* prim;
    s16* ptr;
    s32 posY;
    s32 i;
    SVECTOR* sVec;
    s32 color;
    s32 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x80);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.werewolf.prim = prim;
        while (prim != NULL) {
            prim->tpage = 0x17;
            // BUG: this is immediately overwritten
            prim->clut = PAL_WEREWOLF_DEATH_FLAMES_A;
            prim->clut = PAL_WEREWOLF_DEATH_FLAMES_B;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->ext.werewolf.timer = 0x100;
    case 1:
        if (!(self->ext.werewolf.timer & 0x1F)) {
            PlaySfxPositional(SFX_FIREBALL_SHOT_B);
        }

        if (!--self->ext.werewolf.timer) {
            DestroyEntity(self);
            return;
        }

        if (!(self->ext.werewolf.timer & 3)) {
            self->ext.werewolf.unk9C -= 0x20;
            color = self->ext.werewolf.timer;
            if (color > 0x60) {
                color = 0x40;
            }

            for (i = 0; i < 3; i++) {
                prim = self->ext.werewolf.prim;
                prim = FindFirstUnkPrim2(prim, 2);
                if (prim != NULL) {
                    UnkPolyFunc2(prim);
                    prim->next->x2 = 0;
                    prim->next->y2 = 0;
                    prim->next->x1 =
                        self->ext.werewolf.unk9C + (i * 0x555) + Random();
                    prim->next->y1 = 0;
                    PGREY(prim, 0) = PGREY(prim, 1) = PGREY(prim, 2) =
                        PGREY(prim, 3) = color;

                    prim = prim->next;
                    prim->drawMode = DRAW_HIDE;
                }
            }
        }

        SetGeomScreen(0x200);
        SetGeomOffset(self->posX.i.hi, self->posY.i.hi);
        prim = self->ext.werewolf.prim;
        sVec = death_flame_vector;
        posY = self->posY.i.hi + 8;
        while (prim != NULL) {
            if (prim->p3 == 8) {
                vec.vx = 0;
                vec.vy = prim->next->y1;
                vec.vz = 0x200;
                TransMatrix(&matrix, &vec);
                SetTransMatrix(&matrix);
                svecTwo.vx = 0;
                svecTwo.vy = prim->next->x1;
                svecTwo.vz = 0x180;
                RotMatrix(&svecTwo, &matrix);
                SetRotMatrix(&matrix);
                gte_ldv3c(sVec);
                gte_rtpt();
                gte_stsxy3_gt3(prim);
                gte_ldv0(&sVec[3]);
                gte_rtps();
                gte_stsxy((long*)&prim->x3);
                gte_avsz4();
#ifdef VERSION_US
                gte_stszotz(otz);
#else
                gte_stszotz(&otz);
#endif

                if (otz > 0x80) {
                    prim->priority = self->zPriority - 1;
                } else {
                    prim->priority = self->zPriority + 1;
                }

                if (posY < prim->y2) {
                    prim->y2 = posY;
                }

                if (posY < prim->y3) {
                    prim->y3 = posY;
                }
                prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                 DRAW_UNK02 | DRAW_TRANSP;
            }
            prim = prim->next;
        }

        prim = self->ext.werewolf.prim;
        while (prim != NULL) {
            if (prim->p3 == 8) {
                prim->next->y1 -= 3;
                prim->next->x1 += 0x30;
                prim->r0 -= 1;
                if (!prim->r0) {
                    UnkPolyFunc0(prim);
                    continue;
                }

                prim->g0 = prim->b0 = prim->r0;
                PGREY(prim, 1) = PGREY(prim, 2) = PGREY(prim, 3) = prim->r0;
                if (!prim->next->y2) {
                    prim->next->x2++;
                    if (prim->next->x2 > 0xD) {
                        UnkPolyFunc0(prim);
                        continue;
                    }

                    ptr = sprites_rare_4[prim->next->x2];
                    ptr += 8;
                    prim->u0 = prim->u2 = *ptr++;
                    prim->v0 = prim->v1 = *ptr++;
                    prim->u1 = prim->u3 = *ptr++;
                    prim->v2 = prim->v3 = *ptr++;
                    prim->next->y2 = 2;
                } else {
                    prim->next->y2--;
                }
            }
            prim = prim->next;
        }
        break;
    }
}
