// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rlib.h"

static bool ApproachTarget(s16* val, s16 target, s16 step) {
    if (abs(*val - target) < step) {
        *val = target;
        return true;
    }
    if (*val > target) {
        *val -= step;
    }
    if (*val < target) {
        *val += step;
    }
    return false;
}

static s16 sensors1[] = {0, 34, 0, 4, 24, -4, -48, 0};
static s16 sensors2[] = {0, 34, 24, 0};
static AnimateEntityFrame anim_tinman_idle[] = {
    {3, 1}, {3, 2}, {3, 3}, {3, 4}, POSE_LOOP(0)};
static AnimateEntityFrame anim_tinman_transform[] = {
    {32, 1}, {4, 6},  {3, 7},  {2, 8},  {2, 9},   {8, 10}, {2, 11}, {2, 12},
    {2, 13}, {2, 14}, {2, 15}, {2, 16}, {2, 17},  {2, 18}, {8, 17}, {2, 19},
    {2, 21}, {2, 20}, {8, 21}, {3, 22}, {3, 23},  {3, 24}, {3, 25}, {3, 26},
    {3, 27}, {3, 28}, {3, 29}, {3, 30}, {32, 21}, POSE_END};
static AnimateEntityFrame anim_tinman_transformed_idle[] = {
    {2, 21}, {2, 31}, POSE_LOOP(0)};
static AnimateEntityFrame anim_smokepuff[] = {
    {3, 32}, {3, 33}, {3, 34}, {3, 35}, {3, 36},
    {3, 37}, {3, 38}, {3, 39}, {3, 40}, POSE_END};
static AnimateEntityFrame anim_fire_bullet[] = {
    {2, 42}, {2, 43}, {2, 44}, {2, 45}, {2, 46}, POSE_LOOP(0)};
static AnimateEntityFrame anim_debris_spin[] = {
    {2, 47}, {2, 48}, {2, 49}, {2, 50}, {2, 51}, {2, 52}, POSE_LOOP(0)};
static AnimateEntityFrame anim_tinman_turnaround[] = {
    {17, 53}, {3, 54}, {3, 55}, {3, 56}, {3, 57}, {17, 58},
    {3, 57},  {3, 56}, {3, 55}, {3, 54}, POSE_END};

typedef struct {
    u16 delay;
    u16 gravity;
    s32 velX;
    s32 velY;
} deathPartsParam;

static deathPartsParam deathPartsParams[] = {
    {52, false, FIX(-1.5), 0},
    {28, true, FIX(0.75), FIX(-1.25)},
    {16, true, FIX(1), FIX(-4)},
    {24, true, FIX(0.5), FIX(-1.5)},
    {48, true, FIX(3.0 / 8), FIX(-1)},
    {32, true, FIX(7.0 / 8), FIX(-1)},
    {40, false, FIX(3), 0},
    {40, true, 0, FIX(-3)},
    {52, false, FIX(-0.75), 0},
    {8, true, FIX(0.5), FIX(-2)},
    {4, true, FIX(-0.25), FIX(-1)},
};

extern EInit g_EInitTinman;

typedef enum {
    TM_INIT,
    TM_COLL,
    TM_WAIT,
    TM_NORMAL,
    TM_TURNAROUND,
    TM_TRANSFORM,
    TM_TRANSFORMED,
    TM_DEAD
} TinmanSteps;

void EntityTinMan(Entity* self) {
    s32 var_s2;
    s32 var_s1;
    Entity* other;

    if (self->step) {
        if ((self->hitPoints < g_api.enemyDefs[ENEMY_TIN_MAN].hitPoints / 4) &&
            (self->step < TM_TRANSFORM)) {
            SetStep(TM_TRANSFORM);
        }
    }
    if (self->hitFlags & 3) {
        PlaySfxPositional(SFX_UNK_RLIB_73D);
    }
    if ((self->flags & FLAG_DEAD) && (self->step != TM_DEAD)) {
        SetStep(TM_DEAD);
    }
    switch (self->step) {
    case TM_INIT:
        InitializeEntity(g_EInitTinman);
        self->hitboxOffY = 9;
        other = self + 1;
        CreateEntityFromCurrentEntity(E_TINMAN_ARM, other);
        other->zPriority = self->zPriority + 1;
        /* fallthrough */
    case TM_COLL:
        if (UnkCollisionFunc3(&sensors1) & 1) {
            SetStep(TM_WAIT);
        }
        break;
    case TM_WAIT:
        if (GetDistanceToPlayerX() < 0x60) {
            SetStep(TM_NORMAL);
        }
        break;
    case TM_NORMAL:
        AnimateEntity(&anim_tinman_idle, self);
        self->ext.tinman.turningAround = false;
        var_s2 = 0;
        if (self->facingLeft) {
            self->velocityX += FIX(0.03125);
            if (self->velocityX > FIX(1.5)) {
                self->velocityX = FIX(1.5);
                var_s2 = 1;
            }
        } else {
            self->velocityX -= FIX(0.03125);
            if (self->velocityX < FIX(-1.5)) {
                self->velocityX = FIX(-1.5);
                var_s2 = 1;
            }
        }
        if (var_s2 != 0) {
            if (Random() & 0x1F) {
                var_s2 = 0;
            } else {
                var_s2 = 1;
            }
            if (self->poseTimer) {
                self->poseTimer -= 1;
            }
        } else if (g_Timer & 0xF) {
            var_s2 = 0;
        } else {
            var_s2 = 1;
        }
        if (var_s2 != 0) {
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(E_TINMAN_SMOKE, self, other);
                other->ext.tinman.parent = self;
                other->facingLeft = self->facingLeft;
                other->zPriority = ((self->zPriority) + 1);
            }
        }
        if (UnkCollisionFunc2(sensors2) & 0x60) {
            self->posX.val -= self->velocityX;
            self->velocityX = -self->velocityX;
        }
        if (GetDistanceToPlayerX() < 0x50) {
            self->ext.tinman.armAngle -= 0x100;
            self->ext.tinman.armAngle &= 0xFFF;
        } else {
            ApproachTarget(&self->ext.tinman.armAngle, 0, 0x80);
        }
        var_s2 = GetSideToPlayer() & 1;
        if ((var_s2 == self->facingLeft) && (GetDistanceToPlayerX() > 0x30)) {
            SetStep(TM_TURNAROUND);
        }
        break;
    case TM_TURNAROUND:
        self->velocityX -= self->velocityX / 32;
        if (UnkCollisionFunc2(sensors2) & 0x60) {
            self->posX.val -= self->velocityX;
            self->velocityX = -self->velocityX;
        }
        switch (self->step_s) {
        case 0:
            self->ext.tinman.turningAround = false;
            if (ApproachTarget(&self->ext.tinman.armAngle, 0, 0x80) != 0) {
                self->step_s++;
            }
            break;
        case 1:
            self->ext.tinman.turningAround = true;
            if (AnimateEntity(&anim_tinman_turnaround, self) == 0) {
                self->ext.tinman.turningAround = false;
                self->animCurFrame = 1;
                self->facingLeft ^= 1;
                SetStep(TM_NORMAL);
            }
            break;
        }
        break;
    case TM_TRANSFORM:
        switch (self->step_s) {
        case 0:
            if (GetSideToPlayer() & 1) {
                self->velocityX = FIX(1.0);
            } else {
                self->velocityX = FIX(-1.0);
            }
            self->velocityY = FIX(-2.0);
            self->drawFlags = ENTITY_ROTATE;
            self->step_s++;
            /* fallthrough */
        case 1:
            ApproachTarget(&self->rotate, 0x80, 0x10);
            if (UnkCollisionFunc3(&sensors1) & 1) {
                self->step_s++;
            }
            break;
        case 2:
            if (ApproachTarget(&self->rotate, 0, 0x10) != 0) {
                self->ext.tinman.transformed = true;
                self->drawFlags = ENTITY_DEFAULT;
                self->rotate = 0;
                self->step_s++;
            }
            break;
        case 3:
            if (AnimateEntity(&anim_tinman_transform, self) == 0) {
                self->hitboxWidth = 0xF;
                self->hitboxHeight = 0x11;
                self->hitboxOffX = 2;
                self->hitboxOffY = 0xF;
                self->ext.tinman.timer = Random() & 0xF;
                SetStep(TM_TRANSFORMED);
            }
            break;
        }
        break;
    case TM_TRANSFORMED:
        AnimateEntity(&anim_tinman_transformed_idle, self);
        if (!(self->ext.tinman.timer & 7)) {
            PlaySfxPositional(SFX_EXPLODE_E);
        }
        self->ext.tinman.timer++;
        if (!(self->ext.tinman.timer & 3)) {
            other = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (other != NULL) {
                CreateEntityFromEntity(E_TINMAN_PROJECTILE, self, other);
                other->facingLeft = self->facingLeft;
                other->posY.i.hi -= (((self->ext.tinman.timer & 7) >> 1) + 7);
                if (self->facingLeft) {
                    other->posX.i.hi -= 2;
                } else {
                    other->posX.i.hi += 2;
                }
            }
        }
        break;
    case TM_DEAD:
        // Useless empty block!
        if (UnkCollisionFunc3(&sensors1) & 1) {
        }
        ApproachTarget(&self->rotate, 0, 0x20);
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            if (self->ext.tinman.transformed) {
                self->step_s = 2;
            } else {
                self->step_s = 1;
            }
            break;
        case 1:
            if (AnimateEntity(&anim_tinman_transform, self) == 0) {
                self->step_s++;
            }
            break;
        case 2:
            for (var_s1 = 0; var_s1 < 11; var_s1++) {
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_TINMAN_DEATH_PARTS, self, other);
                    other->facingLeft = self->facingLeft;
                    other->params = (var_s1 + 0x3B);
                }
            }
            PlaySfxPositional(SFX_FLEA_ARMOR_EXPLODE);
            DestroyEntity(self);
        }
        break;
    case 0xFF:
#include "../pad2_anim_debug.h"
    }
}

extern EInit g_EInitTinManArm;

void EntityTinManArm(Entity* self) {
    Entity* other;
    s16 angle;
    s32 var_s1;

    other = self - 1;
    self->facingLeft = other->facingLeft;
    self->posX.val = other->posX.val;
    self->posY.val = other->posY.val;
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitTinManArm);
        self->drawFlags = ENTITY_ROTATE;
        /* fallthrough */
    case 1:
        other = self - 1;
        if (other->ext.tinman.turningAround == true) {
            self->hitboxState = 0;
            self->animCurFrame = 0;
        } else {
            self->animCurFrame = 5;
            self->rotate = other->ext.tinman.armAngle;
            self->hitboxState = 1;
            angle = self->rotate + 0x200;
            self->hitboxOffX = ((rcos(angle) * 0x1C) >> 0xC);
            self->hitboxOffY = ((rsin(angle) * 0x1C) >> 0xC);
            if (self->rotate >= ROT(337.5)) {
                PlaySfxPositional(SFX_WHIP_TWIRL_SWISH);
            }
        }
        if (other->ext.tinman.transformed || (other->flags & FLAG_DEAD)) {
            self->hitboxState = 0;
            self->step++;
        }
        break;
    case 2:
        other = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (other != NULL) {
            CreateEntityFromEntity(E_TINMAN_DEATH_PARTS, self, other);
            other->facingLeft = self->facingLeft;
            other->rotate = self->rotate;
            other->zPriority = self->zPriority;
            other->params = 5;
        }
        for (var_s1 = 0; var_s1 < 8; var_s1++) {
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(E_TINMAN_DEATH_PARTS, self, other);
                other->params = 0;
                other->zPriority = self->zPriority;
            }
        }
        PlaySfxPositional(SFX_WALL_DEBRIS_C);
        other = self - 1;
        self->hitboxState = other->hitboxState;
        self->attackElement = other->attackElement;
        self->attack = other->attack;
        self->parent = self - 1;
        self->animCurFrame = 0;
        self->hitboxWidth = 0xF;
        self->hitboxHeight = 0xB;
        self->hitboxOffX = 0x17;
        self->hitboxOffY = -5;
        self->step++;
        break;
    case 3:
        other = self - 1;
        if ((other->entityId != 0x1F) || (other->flags & FLAG_DEAD)) {
            DestroyEntity(self);
        }
        break;
    }
}
extern EInit g_EInitTinMan2;

void EntityTinManSmoke(Entity* self) {
    Entity* parent;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitTinMan2);
        self->blendMode = BLEND_TRANSP;
        PlaySfxPositional(SFX_NOISE_SWEEP_DOWN_B);
        /* fall through */
    case 1:
        parent = self->ext.tinman.parent;
        self->posX.val = parent->posX.val;
        self->posY.val = parent->posY.val;
        if (AnimateEntity(&anim_smokepuff, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit g_EInitTinManProjectile;
// Created at rapid-fire after transforming
void EntityTinManProjectile(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitTinManProjectile);
        if (self->facingLeft) {
            self->velocityX = FIX(6);
        } else {
            self->velocityX = FIX(-6);
        }
        /* fall through */
    case 1:
        MoveEntity();
        AnimateEntity(&anim_fire_bullet, self);
        if (self->flags & FLAG_DEAD) {
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit g_EInitTinMan2;

void EntityTinManDeathParts(Entity* self) {
    Entity* other;
    s16 angle;
    s32 temp_s2;
    deathPartsParam* temp_s0;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitTinMan2);
        if (!self->params) {
            self->step = 1;
            temp_s2 = (Random() & 0x1F) + 0x10;
            angle = (Random() * 6) + 0x900;
            self->velocityX = temp_s2 * rcos(angle);
            self->velocityY = temp_s2 * rsin(angle);
            return;
        }
        self->animCurFrame = self->params;
        if (self->params > 0x3A) {
            temp_s2 = self->params - 0x3B;
            temp_s0 = &deathPartsParams[temp_s2];
            self->velocityX = temp_s0->velX;
            if (self->facingLeft) {
                self->velocityX = -self->velocityX;
            }
            self->velocityY = temp_s0->velY;
            self->ext.tinman.timer = temp_s0->delay;
            self->ext.tinman.hasGravity = temp_s0->gravity;
            self->step = 3;
        } else {
            self->drawFlags = ENTITY_ROTATE;
            self->step = 2;
        }
        break;
    case 1:
        AnimateEntity(&anim_debris_spin, self);
        MoveEntity();
        self->velocityY += FIX(0.09375);
        break;
    case 2:
        MoveEntity();
        self->velocityY += FIX(0.09375);
        self->rotate += ROT(11.25);
        break;
    case 3:
        switch (self->step_s) {
        case 0:
            if (!--self->ext.tinman.timer) {
                self->ext.tinman.timer = 0x20;
                self->step_s++;
            }
            break;
        case 1:
            MoveEntity();
            if (self->ext.tinman.hasGravity) {
                self->velocityY += FIX(0.125);
            }
            if (!--self->ext.tinman.timer) {
                PlaySfxPositional(SFX_EXPLODE_B);
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, other);
                    other->posY.i.hi += 0x10;
                    other->params = 1;
                }
                DestroyEntity(self);
            }
            break;
        }
        break;
    }
}
