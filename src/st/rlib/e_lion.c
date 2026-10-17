// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rlib.h"

extern EInit g_EInitLion;

static s16 sensors1[] = {0, 30, 0, 4, 24, -4, -48, 0};
static s16 sensors2[] = {0, 30, 24, 0};
// Not a proper walk cycle, lion kind of just shuffles his feet moonwalking
static AnimateEntityFrame anim_walk[] = {
    {10, 1}, {7, 2}, {6, 3}, {9, 4}, {6, 3}, {7, 2}, POSE_LOOP(0)};
static AnimateEntityFrame anim_overhead_attack[] = {
    {28, 1}, {8, 5},  {8, 6},  {8, 7},  {8, 8},  {31, 7}, {3, 9},      {3, 10},
    {2, 11}, {2, 12}, {2, 13}, {1, 14}, {2, 15}, {1, 16}, {2, 17},     {8, 18},
    {8, 19}, {8, 10}, {8, 9},  {8, 6},  {8, 5},  {8, 1},  POSE_LOOP(0)};
static AnimateEntityFrame anim_dying[] = {
    {40, 1}, {5, 5},  {5, 6},  {5, 7},   {5, 20}, {7, 23},
    {7, 24}, {7, 25}, {7, 26}, {49, 27}, POSE_END};
static AnimateEntityFrame anim_grab_crotch[] = {
    {16, 1}, {5, 21}, {13, 22}, {7, 21}, {7, 1}, POSE_LOOP(0)};

static s32 D_us_801817CC[] = {
    FIX(8.0 / 1024), FIX(7.0 / 1024),  FIX(4.0 / 1024),
    FIX(6.0 / 1024), FIX(12.0 / 1024), FIX(14.0 / 1024),
};
static s8 g_AttackHitboxes[][4] = {
    {0, 0, 0, 0},     {-61, -98, 0, 0}, {20, -21, 16, 31}, {25, -4, 15, 14},
    {53, -1, 33, 26}, {82, -9, 4, 17},  {45, -10, 33, 26}, {74, -3, 4, 17}};
static u8 g_AttackHitboxIdx[] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4,
                                 5, 6, 7, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

typedef enum {
    LION_INIT,
    LION_GROUND,
    LION_IDLE,
    LION_RETREAT,
    LION_ADVANCE,
    LION_ATTACK,
    LION_DEAD
} LionSteps;

void EntityLion(Entity* self) {
    Entity* other;
    s32 coll;
    s32 i;

    if (self->flags & FLAG_DEAD && self->step != LION_DEAD) {
        PlaySfxPositional(SFX_UNK_RLIB_732);
        self->hitboxState = 0;
        PlaySfxPositional(SFX_FM_STUTTER_EXPLODE);
        SetStep(LION_DEAD);
    }
    switch (self->step) {
    case LION_INIT:
        InitializeEntity(g_EInitLion);
        other = self + 1;
        CreateEntityFromCurrentEntity(E_LION_ATTACK, other);
        /* fallthrough */
    case LION_GROUND:
        if (UnkCollisionFunc3(sensors1) & 1) {
            SetStep(LION_IDLE);
        }
        break;
    case LION_IDLE:
        AnimateEntity(anim_grab_crotch, self);
        self->facingLeft = GetSideToPlayer() & 1;
        if (GetDistanceToPlayerX() < 0x60) {
            SetStep(LION_RETREAT);
        }
        break;
    case LION_RETREAT:
        AnimateEntity(anim_walk, self);
        coll = UnkCollisionFunc2(sensors2);
        if (coll & 0x60) {
            self->posX.val -= self->velocityX;
        }
        if (self->facingLeft ^ self->ext.lion.facingbool) {
            self->velocityX = FIX(-0.75);
        } else {
            self->velocityX = FIX(0.75);
        }
        if (self->ext.lion.facingbool) {
            self->velocityX -= self->velocityX / 4;
        }
        switch (self->step_s) {
        case 0:
            self->facingLeft = GetSideToPlayer() & 1;
            self->ext.lion.facingbool = true;
            self->ext.lion.timer = 0x60;
            self->step_s++;
            /* fallthrough */
        case 1:
            self->facingLeft = GetSideToPlayer() & 1;
            other = &PLAYER;
            if (other->facingLeft != self->facingLeft) {
                self->ext.lion.timer--;
            }
            if ((GetDistanceToPlayerX() > 0x60) &&
                other->facingLeft == self->facingLeft) {
                SetStep(LION_ADVANCE);
            } else {
                if (!self->ext.lion.timer) {
                    self->step_s++;
                }
                if (GetDistanceToPlayerX() < 0x28) {
                    SetStep(LION_ATTACK);
                }
            }
            break;
        case 2:
            self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
            self->ext.lion.facingbool = false;
            if (GetDistanceToPlayerX() > 0xA0) {
                SetStep(LION_IDLE);
            }
            break;
        }
        if (self->hitFlags & 3) {
            self->facingLeft = GetSideToPlayer() & 1;
            SetStep(LION_ATTACK);
        }
        break;
    case LION_ADVANCE:
        AnimateEntity(anim_walk, self);
        coll = UnkCollisionFunc2(sensors2);
        if (coll & 0x60) {
            self->posX.val -= self->velocityX;
        }
        self->facingLeft = GetSideToPlayer() & 1;
        other = &PLAYER;
        if (other->facingLeft != self->facingLeft) {
            self->ext.lion.timer--;
            self->ext.lion.facingbool = true;
            if (!self->ext.lion.timer) {
                SetStep(LION_RETREAT);
                return;
            }
        } else {
            self->ext.lion.timer = 0x20;
            self->ext.lion.facingbool = false;
        }
        if (self->facingLeft ^ self->ext.lion.facingbool) {
            self->velocityX = FIX(-0.75);
        } else {
            self->velocityX = FIX(0.75);
        }
        if (self->ext.lion.facingbool) {
            self->velocityX -= self->velocityX / 4;
        }
        switch (self->step_s) {
        case 0:
            self->facingLeft = GetSideToPlayer() & 1;
            self->ext.lion.timer; // Need a line here to touch self.
            self->ext.lion.attackDelay = 0x30;
            self->step_s++;
            /* fallthrough */
        case 1:
            self->velocityX -= self->velocityX / 2;
            if (g_Timer & 1) {
                self->poseTimer++;
            }
            if (!--self->ext.lion.attackDelay) {
                self->step_s++;
            }
            /* fallthrough */
        case 2:
            if (GetDistanceToPlayerX() < 0x40) {
                SetStep(LION_ATTACK);
            }
            break;
        }
        if (self->hitFlags & 3) {
            self->facingLeft = GetSideToPlayer() & 1;
            SetStep(LION_ATTACK);
        }
        break;
    case LION_ATTACK:
        if (!self->poseTimer && (self->pose == 6)) {
            PlaySfxPositional(SFX_BOSS_WING_FLAP);
        }
        if (AnimateEntity(anim_overhead_attack, self) == 0) {
            SetStep(LION_RETREAT);
        }
        break;
    case LION_DEAD:
        switch (self->step_s) {
        case 0:
            if (!(g_Timer & 3)) {
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != 0) {
                    CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, other);
                    other->posX.i.hi += (0x20 - (Random() & 0x2F));
                    other->posY.i.hi += (0x20 - (Random() & 0x3F));
                }
            }
            if (!(g_Timer & 7)) {
                PlaySfxPositional(SFX_SMALL_FLAME_IGNITE);
            }
            if (AnimateEntity(anim_dying, self) == 0) {
                self->step_s++;
            }
            break;
        case 1:
            PlaySfxPositional(SFX_FLEA_ARMOR_EXPLODE);
            for (i = 0; i < 6; i++) {
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_LION_DEATH_PARTS, self, other);
                    other->params = i;
                    other->facingLeft = self->facingLeft;
                }
            }
            DestroyEntity(self);
            return;
        }
        break;
    case 0xFF:
#include "../pad2_anim_debug.h"
    }
}

extern EInit g_EInitLionAttack;

void EntityLionAttack(Entity* self) {
    s32 animFrame;
    s8* hitbox;
    Entity* lion;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitLionAttack);
        /* fall through */
    case 1:
        lion = self - 1;
        self->facingLeft = lion->facingLeft;
        self->posX.val = lion->posX.val;
        self->posY.val = lion->posY.val;
        animFrame = lion->animCurFrame;
        hitbox = (s8*)g_AttackHitboxes;
        animFrame = g_AttackHitboxIdx[animFrame];
        hitbox += animFrame * 4;
        self->hitboxOffX = *hitbox++;
        self->hitboxOffY = *hitbox++;
        self->hitboxWidth = *hitbox++;
        self->hitboxHeight = *hitbox++;
        if (lion->entityId != E_LION) {
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit g_EInitLionDeathParts;

void EntityLionDeathParts(Entity* self) {
    switch (self->step_s) {
    case 0:
        InitializeEntity(g_EInitLionDeathParts);
        self->animCurFrame = self->params + 28;
        /* fall through */
    case 1:
        MoveEntity();
        self->velocityY += (u32)self->ext.lion.accelY;
        self->ext.lion.accelY += D_us_801817CC[self->params];
    }
}
