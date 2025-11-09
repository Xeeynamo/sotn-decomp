// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no4.h"

static u8 anim_throat_inflate[] = {
    0x05, 0x10, 0x03, 0x11, 0x05, 0x12, 0x03, 0x12, 0x00, 0x00, 0x00, 0x00};
static u8 anim_tongue[] = {
    0x04, 0x10, 0x08, 0x13, 0x01, 0x11, 0x02, 0x12, 0x01, 0x11, 0x01,
    0x14, 0x01, 0x15, 0x01, 0x16, 0x01, 0x17, 0x02, 0x18, 0x03, 0x19,
    0x0C, 0x18, 0x04, 0x17, 0x04, 0x16, 0x04, 0x15, 0x02, 0x14, 0x08,
    0x10, 0x01, 0x11, 0x04, 0x12, 0x01, 0x11, 0x10, 0x10, 0xFF, 0x00};
static u8 anim_jump[] = {0x03, 0x10, 0x0C, 0x13, 0x03, 0x10, 0xFF, 0x00};
static s16 sensors_ground[4][2] = {{0, 8}, {0, 4}, {3, -4}, {-6, 0}};
static Point32 jumpVelocities[] = {
    {.x = FIX(2), .y = FIX(-1.5)},
    {.x = FIX(1), .y = FIX(-2)},
    {.x = FIX(2), .y = FIX(-3)},
    {.x = FIX(3), .y = FIX(-4.5)},
};
// { step_s / jumpCount }
static u8 jumpType[][2] = {
    // 9 tiny jumps
    {1, 0},
    // 1 small, 1 medium, 1 big jump
    {2, 1},
    // 1 big, 1 medium, 1 small jump
    {3, 3},
    // 2 small jumps, 1 big jump
    {4, 0},
};

static s32 FrogJump(s32 index) {
    Collider collider;
    s32 posX;
    s32 posY;

    switch (g_CurrentEntity->ext.frogToad.jumpStep) {
    case 0:
        if (!AnimateEntity(anim_jump, g_CurrentEntity)) {
            g_CurrentEntity->velocityX = jumpVelocities[index].x;
            if (!g_CurrentEntity->facingLeft) {
                g_CurrentEntity->velocityX = -g_CurrentEntity->velocityX;
            }
            g_CurrentEntity->velocityY = jumpVelocities[index].y;
            g_CurrentEntity->ext.frogToad.jumpStep++;
            PlaySfxPositional(SFX_BLIPS_C);
            g_CurrentEntity->ext.frogToad.jumpTimer = 4;
        }
        break;
    case 1:
        posX = g_CurrentEntity->posX.i.hi;
        if (g_CurrentEntity->velocityX > 0) {
            posX += 0xC;
        }
        if (g_CurrentEntity->velocityX < 0) {
            posX -= 0xC;
        }
        posY = g_CurrentEntity->posY.i.hi;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            g_CurrentEntity->velocityX = 0;
        }
        if (UnkCollisionFunc3(sensors_ground) & 1) {
            g_CurrentEntity->poseTimer = 0;
            g_CurrentEntity->pose = 0;
            g_CurrentEntity->ext.frogToad.jumpStep = 2;
        }
        if (abs(g_CurrentEntity->velocityY) < FIX(2)) {
            g_CurrentEntity->animCurFrame = 0x1B;
        } else {
            g_CurrentEntity->animCurFrame = 0x1A;
        }
        if (g_CurrentEntity->ext.frogToad.jumpTimer) {
            g_CurrentEntity->animCurFrame = 0x1B;
            g_CurrentEntity->ext.frogToad.jumpTimer--;
        }
        break;
    case 2:
        if (!AnimateEntity(anim_jump, g_CurrentEntity)) {
            return 1;
        }
        break;
    }

    return 0;
}

void EntityFrog(Entity* self) {
    Entity* entity;
    s32 index;

    if (self->flags & FLAG_DEAD) {
        PlaySfxPositional(SFX_FROG_CROAK);
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 0;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitFrog);
        self->animCurFrame = 16;
        self->hitboxOffX = 1;
        self->hitboxOffY = 1;
        self->hitboxWidth = 8;
        self->hitboxHeight = 7;
        self->ext.frogToad.lickTimer = 0x80;
        break;
    case 1:
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        if (UnkCollisionFunc3(sensors_ground) & 1) {
            self->step++;
        }
        break;
    case 2:
        if (!AnimateEntity(anim_throat_inflate, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            PlaySfxPositional(SFX_FROG_CROAK);
        }

        if (self->ext.frogToad.lickTimer) {
            self->ext.frogToad.lickTimer--;
        } else if (GetDistanceToPlayerX() < 0x40 &&
                   (GetSideToPlayer() & 1) ^ self->facingLeft) {
            SetStep(4);
        }

        if (!(Random() & 0x7F)) {
            SetStep(3);
        }

        break;
    // Lick
    case 4:
        if (!AnimateEntity(anim_tongue, self)) {
            self->ext.frogToad.lickTimer = 0x80;
            SetStep(2);
        }

        if (!self->poseTimer && self->pose == 9) {
            PlaySfxPositional(SFX_FROG_TOAD_TONGUE);
        }

        switch (self->animCurFrame) {
        case 23:
            self->hitboxOffX = -0xF;
            self->hitboxOffY = 0;
            self->hitboxWidth = 0x14;
            self->hitboxHeight = 4;
            break;
        case 24:
            self->hitboxOffX = -0x15;
            self->hitboxOffY = 0;
            self->hitboxWidth = 0x1B;
            self->hitboxHeight = 4;
            break;
        case 25:
            self->hitboxOffX = -0x20;
            self->hitboxOffY = 0;
            self->hitboxWidth = 0x20;
            self->hitboxHeight = 4;
            break;
        default:
            self->hitboxOffX = 1;
            self->hitboxOffY = 1;
            self->hitboxWidth = 8;
            self->hitboxHeight = 7;
            break;
        }
        break;
    // Jump
    case 3:
        switch (self->step_s) {
        case 0:
            index = Random() & 3;
            self->ext.frogToad.jumpStep = 0;
            self->step_s = jumpType[index][0];
            self->ext.frogToad.jumpCount = jumpType[index][1];
            break;
        case 1:
            // Do 9 tiny jumps
            // Jump velocity index 0
            if (FrogJump(0) != 0) {
                self->ext.frogToad.jumpStep = 0;
                self->ext.frogToad.jumpCount++;
            }

            if (self->ext.frogToad.jumpCount > 8) {
                SetStep(2);
            }
            break;
        case 2:
            // Do 1 small, 1 medium, 1 big jump
            // Jump velocity index 1, 2, 3
            if (FrogJump(self->ext.frogToad.jumpCount) != 0) {
                self->ext.frogToad.jumpStep = 0;
                self->ext.frogToad.jumpCount++;
            }

            if (self->ext.frogToad.jumpCount > 3) {
                SetStep(2);
            }
            break;
        case 3:
            // Do 1 big, 1 medium, 1 small jump
            // Jump velocity index 3, 2, 1
            if (FrogJump(self->ext.frogToad.jumpCount) != 0) {
                self->ext.frogToad.jumpStep = 0;
                self->ext.frogToad.jumpCount--;
            }

            if (!self->ext.frogToad.jumpCount) {
                SetStep(2);
            }
            break;
        case 4:
            // Do 2 short jumps, followed by 1 big jump
            // Jump velocity index 1, 1, 3
            if (self->ext.frogToad.jumpCount < 2) {
                index = 1;
            } else {
                index = 3;
            }

            if (FrogJump(index) != 0) {
                self->ext.frogToad.jumpStep = 0;
                self->ext.frogToad.jumpCount++;
                if (self->ext.frogToad.jumpCount > 2) {
                    SetStep(2);
                }
            }
            break;
        }
        break;
    }
}
