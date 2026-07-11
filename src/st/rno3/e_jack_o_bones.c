// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno3.h"

extern EInit g_EInitJackOBones2;
extern EInit g_EInitJackOBones3;
extern EInit g_EInitJackOBones;

static u8 anim_walk_fwd[] = {6, 1, 4, 2, 4, 3, 6, 4, 5, 5, 5, 6, 0};
static u8 anim_walk_back[] = {6, 1, 5, 6, 5, 5, 6, 4, 4, 3, 4, 2, 0};
static u8 anim_throw[] = {5, 1,  5,  2,  5, 7, 6, 8, 5, 9, 5,   10,
                          5, 11, 31, 12, 4, 4, 4, 5, 4, 6, 255, 0};
static u8 anim_jump_windup[] = {1, 1, 4, 13, 4, 14, 1, 1, 255, 0};
static u8 anim_jump_landing[] = {1, 1, 4, 13, 6, 14, 4, 13, 1, 1, 255, 0};
static u16 death_parts_rotspeeds[] = {
    0x100, 0x80, 0x48, 0x20, 0x40, 0x10, 0x18, 0};
static u8 death_parts_lifetimes[] = {48, 32, 20, 12, 24, 16, 20, 0};
static s32 death_parts_xVels[] = {
    FIX(0.75), FIX(1.75), FIX(1.5), FIX(1), FIX(2), FIX(1.75), FIX(0.75)};
static s32 death_parts_yVels[] = {
    FIX(-5), FIX(-3), FIX(-2), FIX(-3), FIX(-4), FIX(-0.875), FIX(-4)};
static s16 death_parts_xPos[] = {
    -4, 0, 4, -4, -4, 4, 0, 0,
};
static s16 death_parts_yPos[] = {-16, -8, -4, -4, 9, 9, 0, 0};
// Select throw speed table with self->params & 1.
static u8 throw_timers[][4] = {{96, 8, 8, 64}, {128, 64, 32, 48}};
static s16 sensors1[] = {0, 20, 0, 4, 8, -4, -16, 0};
static u16 sensors2[] = {0, 20, 12, 0};
static s16 sensors3[] = {-12, 16, 0, -16, 0, -16};

typedef enum {
    JACKO_INIT,
    JACKO_1,
    JACKO_WALK_FWD,
    JACKO_WALK_BACK,
    JACKO_THROW,
    JACKO_JUMP,
    JACKO_DEAD
} JackOBonesSteps;

typedef enum {
    JACKO_JUMP_WINDUP,
    JACKO_JUMP_MIDAIR,
    JACKO_JUMP_LANDING
} JumpSubsteps;

static void TryThrow(void) {
    s32 temp_s1;
    u16 temp_s0;

    temp_s1 = UnkCollisionFunc2(sensors2);
    temp_s0 = UnkCollisionFunc(sensors3, 3);
    if ((temp_s1 == 0x80) || (temp_s0 & 2)) {
        SetStep(JACKO_JUMP);
        return;
    }
    if (!g_CurrentEntity->ext.jackoBones.throwTimer) {
        SetStep(JACKO_THROW);
        return;
    }
    g_CurrentEntity->ext.jackoBones.throwTimer--;
}

void EntityJackOBones(Entity* self) {
    s32 xShift;
    u8 var_s2;
    s32 i;
    Entity* other;

    if (self->flags & FLAG_DEAD) {
        self->step = JACKO_DEAD;
    }
    switch (self->step) {
    case JACKO_INIT:
        InitializeEntity(g_EInitJackOBones);
        if (self->params) {
            self->palette++;
        }
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        // Cooldown for throwing jacks
        self->ext.jackoBones.throwTimer = 0x50;
        // When walking forward, this tells us if facing left. When walking
        // back, this is the inverse of whether we are facing left.
        self->ext.jackoBones.movingLeft = 0;
        self->ext.jackoBones.throwTimerIndex = 0;
        break;
    case JACKO_1:
        if (UnkCollisionFunc3(sensors1) == 0) {
            break;
        }
        self->step++;
        break;
    case JACKO_WALK_FWD:
        if (AnimateEntity(anim_walk_fwd, self) == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        self->ext.jackoBones.movingLeft = self->facingLeft;
        if (self->ext.jackoBones.movingLeft) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }
        if (GetDistanceToPlayerX() < 76) {
            self->step = JACKO_WALK_BACK;
        }
        TryThrow();
        break;
    case JACKO_WALK_BACK:
        if (AnimateEntity(anim_walk_back, self) == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        self->ext.jackoBones.movingLeft = self->facingLeft ^ 1;
        if (self->ext.jackoBones.movingLeft) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }
        if (GetDistanceToPlayerX() > 92) {
            self->step = JACKO_WALK_FWD;
        }
        TryThrow();
        break;
    case JACKO_THROW:
        var_s2 = AnimateEntity(anim_throw, self);
        // We set a value here but it is never used.
        if (self->params) {
            i = 11;
        } else {
            i = 10;
        }
        // Animation done. walk backward and set the timer for next throw.
        if (!var_s2) {
            SetStep(JACKO_WALK_BACK);
            var_s2 = ++self->ext.jackoBones.throwTimerIndex & 3;
            self->ext.jackoBones.throwTimer =
                throw_timers[self->params & 1][var_s2];
            break;
        }
        if ((var_s2 & 0x80) && (self->animCurFrame == 0xB)) {
            other = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (other != NULL) {
                PlaySfxPositional(SFX_BONE_THROW);
                CreateEntityFromCurrentEntity(E_JACKO_JACK, other);
                if (self->params) {
                    xShift = -16;
                } else {
                    xShift = 8;
                }
                if (self->facingLeft) {
                    other->posX.i.hi -= xShift;
                } else {
                    other->posX.i.hi += xShift;
                }
                other->posY.i.hi -= 16;
                other->params = self->params;
                other->facingLeft = self->facingLeft;
            }
        }
        break;
    case JACKO_JUMP:
        switch (self->step_s) {
        case JACKO_JUMP_WINDUP:
            if (!(AnimateEntity(anim_jump_windup, self) & 1)) {
                var_s2 = self->ext.jackoBones.movingLeft;
                if (!(Random() & 3)) {
                    var_s2 ^= 1;
                }
                if (var_s2) {
                    self->velocityX = FIX(2);
                } else {
                    self->velocityX = FIX(-2);
                }
                self->velocityY = FIX(-3);
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s++;
            }
            break;
        case JACKO_JUMP_MIDAIR:
            if (UnkCollisionFunc3(sensors1)) {
                self->step_s++;
            }
            CheckFieldCollision(sensors3, 2);
            break;
        case JACKO_JUMP_LANDING:
            if (AnimateEntity(anim_jump_landing, self) == 0) {
                SetStep(JACKO_WALK_BACK);
            }
        }
        break;
    case JACKO_DEAD:
        PlaySfxPositional(SFX_SKELETON_DEATH_B);
        for (i = 0; i < 6; i++) {
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other == NULL) {
                break;
            }
            CreateEntityFromCurrentEntity(E_JACKO_DEATH_PARTS, other);
            other->facingLeft = self->facingLeft;
            other->params = i;
            other->params |= (self->params << 8);
            other->ext.jackoBones.deathPartLife = death_parts_lifetimes[i];
            if (self->facingLeft) {
                other->posX.i.hi -= death_parts_xPos[i];
            } else {
                other->posX.i.hi += death_parts_xPos[i];
            }
            other->posY.i.hi += death_parts_yPos[i];
            other->velocityX = death_parts_xVels[i];
            other->velocityY = death_parts_yVels[i];
        }
        DestroyEntity(self);
        break;
    }
}

void EntityJackOBonesDeathParts(Entity* self) {
    if (self->step) {
        if (--self->ext.jackoBones.deathPartLife) {
            self->rotate += death_parts_rotspeeds[self->params];
            FallEntity();
            MoveEntity();
            return;
        }
        self->entityId = E_EXPLOSION;
        self->pfnUpdate = EntityExplosion;
        self->params = 0;
        self->step = 0;
        return;
    }
    InitializeEntity(g_EInitJackOBones2);
    self->animCurFrame = (self->params & 0xFF) + 15;
    if (self->params & 0x100) {
        self->palette += 1;
    }
    self->drawFlags = ENTITY_ROTATE;
    if (self->facingLeft) {
        self->velocityX = -self->velocityX;
    }
}

void EntityJackOBonesJack(Entity* self) {
    Collider sp10;
    s32 temp;
    s32 yVar;
    s32 xVar;

    if (!self->step) {
        InitializeEntity(g_EInitJackOBones3);
        if (self->params) {
            self->palette += 1;
        }
        self->animCurFrame = 0x15;
        self->drawFlags |= ENTITY_ROTATE;
        if (self->params) {
            yVar = FIX(4);
            xVar = FIX(1);
        } else {
            yVar = FIX(-1);
            xVar = FIX(2.5);
        }
        if (self->facingLeft) {
            self->velocityX = xVar;
        } else {
            self->velocityX = -xVar;
        }
        self->velocityY = yVar;
    }
    MoveEntity();
    self->velocityY += FIX(0.1875);
    self->rotate -= 0x40;
    xVar = self->posX.i.hi;
    yVar = self->posY.i.hi + 5;
    g_api.CheckCollision(xVar, yVar, &sp10, 0);
    if (sp10.effects & EFFECT_SOLID) {
        PlaySfxPositional(SFX_SKULL_KNOCK_A);
        self->ext.jackoBones.bouncesDone += 1;
        temp = sp10.unk18;
#if defined(VERSION_PSP)
        xVar = self->posX.i.hi;
        yVar = self->posY.i.hi - 3;
        g_api.CheckCollision(xVar, yVar, &sp10, 0);
        if (sp10.effects & EFFECT_SOLID) {
            self->velocityX = -self->velocityX;
        } else {
#else
        if (1) {
#endif
            self->posY.i.hi += temp;
#if defined(VERSION_PSP)
            self->velocityY = -self->velocityY;
#else
            self->velocityY =
                -((self->velocityY < 0) ? -self->velocityY : self->velocityY);
#endif
            if (self->params) {
                self->velocityY = FIX(-7) / self->ext.jackoBones.bouncesDone;
            } else {
                self->velocityY -= self->velocityY / 16;
            }
        }
        xVar = self->posX.i.hi + self->velocityX;
        yVar = self->posY.i.hi;
    }
#if defined(VERSION_PSP)
    if (self->params) {
#else
    if (1) {
#endif
        xVar = self->posX.i.hi;
        yVar = self->posY.i.hi - 5;
        g_api.CheckCollision(xVar, yVar, &sp10, 0);
        if (sp10.effects & EFFECT_SOLID) {
            self->posY.i.hi += sp10.unk20;
            self->velocityY = abs(self->velocityY);
        }
#if !defined(VERSION_PSP)
        xVar = self->posX.i.hi;
        yVar = self->posY.i.hi;
        if (self->velocityX > 0) {
            xVar += 5;
        } else {
            xVar -= 5;
        }
        g_api.CheckCollision(xVar, yVar, &sp10, 0);
        if (sp10.effects & EFFECT_SOLID) {
            self->velocityX = -self->velocityX;
        }
        if (self->params)
#endif
            if (self->ext.jackoBones.bouncesDone > 8) {
                self->flags |= FLAG_DEAD;
            }
    }

    if (self->flags & FLAG_DEAD) {
        self->drawFlags = ENTITY_DEFAULT;
        self->entityId = E_EXPLOSION;
        self->pfnUpdate = EntityExplosion;
        self->params = 0;
        self->step = 0;
    }
}
