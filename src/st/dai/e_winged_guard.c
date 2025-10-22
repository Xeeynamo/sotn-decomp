// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

enum WingedGuardSteps {
    WINGED_GUARD_INIT,
    WINGED_GUARD_MOVE,
    WINGED_GUARD_DEBUG = 255,
};

enum WingedGuardPartsSteps {
    WINGED_GUARD_PARTS_INIT,
    WINGED_GUARD_PARTS_MOVE,
};

static AnimateEntityFrame anim_move[] = {
    {6, 1}, {4, 2}, {4, 3}, {6, 4}, {4, 3}, {4, 2}, POSE_LOOP(0),
};
static u32 velocity_intervals[][2] = {
    {FIX(0), FIX(-0.5)},    {FIX(0.25), FIX(-1.125)}, {FIX(0.1875), FIX(0)},
    {FIX(-0.1875), FIX(0)}, {FIX(0), FIX(-0.75)},     {FIX(-0.25), FIX(-1.125)},
    {FIX(0.125), FIX(-1)},  {FIX(0), FIX(0)},
};

// static s16 min_max_positions[] defined before EntityWingedGuardSpawner
// because of const string in EntityWingedGuard

void EntityWingedGuard(Entity* self) {
    Entity* entity;
    s32 guardPart;

    if (self->flags & FLAG_DEAD) {
        PlaySfxPositional(SFX_SKELETON_DEATH_C);
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = EXPLOSION_SMALL_MULTIPLE;
        }
        for (guardPart = 0; guardPart < 8; guardPart++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_WINGED_GUARD_PARTS, self, entity);
                entity->velocityX = self->velocityX;
                entity->velocityY = self->velocityY;
                entity->params = guardPart;
                entity->facingLeft = self->facingLeft;
                entity->zPriority = self->zPriority;
            }
        }
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case WINGED_GUARD_INIT:
        InitializeEntity(g_EInitWingedGuard);
        self->hitboxOffY = 2;
        self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
        if (self->facingLeft) {
            self->velocityX = FIX(1.0);
        } else {
            self->velocityX = FIX(-1.0);
        }
        // fallthrough
    case WINGED_GUARD_PARTS_MOVE:
        AnimateEntity(anim_move, self);
        if (!self->poseTimer && self->pose == 2) {
            PlaySfxPositional(SFX_WING_FLAP_A);
        }
        MoveEntity();
        self->velocityY = (rsin(self->rotate) << 14) >> 12;
        self->rotate += 16;
        return;
    case WINGED_GUARD_DEBUG:
#include "../pad2_anim_debug.h"
    }
}

void EntityWingedGuardParts(Entity* self) {
    Entity* explosion;

    switch (self->step) {
    case WINGED_GUARD_PARTS_INIT:
        InitializeEntity(g_EInitWingedGuardParts);
        self->flags |= FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
        self->animCurFrame = self->params + 5;
        if (!self->params) {
            self->drawFlags |= FLAG_DRAW_ROTATE;
        }
        if (self->facingLeft) {
            self->velocityX += velocity_intervals[self->params][0];
        } else {
            self->velocityX -= velocity_intervals[self->params][0];
        }
        if (GetSideToPlayer() & 1) {
            self->velocityX += FIX(0.5);
        } else {
            self->velocityX -= FIX(0.5);
        }
        self->velocityY += velocity_intervals[self->params][1];
        return;
    case WINGED_GUARD_PARTS_MOVE:
        MoveEntity();
        self->rotate += 128;
        self->velocityY += FIX(0.1875);
        if (!(Random() & 0x3F)) {
            explosion = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (explosion != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, explosion);
                explosion->params = EXPLOSION_SMALL;
            }
        }
        return;
    }
}

static s16 min_max_positions[] = {384, 640, 416, 1664, 384, 640, 416, 944};

void EntityWingedGuardSpawner(Entity* self) {
    Entity* entity;
    s32 posX, posY;
    s16* minMaxPositions;

    if (!self->step) {
        InitializeEntity(g_EInitSpawner);
        // This is not a mistake, Winged Guard and Ghost use the same spawner
        self->ext.ghostEnemySpawner.timer = 1;
    }
    if (!--self->ext.ghostEnemySpawner.timer) {
        self->ext.ghostEnemySpawner.timer = (Random() & 47) + 192;
        entity = &PLAYER;
        posX = g_Tilemap.scrollX.i.hi + entity->posX.i.hi;
        posY = g_Tilemap.scrollY.i.hi + entity->posY.i.hi;
        if (self->params) {
            minMaxPositions = &min_max_positions[(self->params - 1) * 4];
            if (posX < minMaxPositions[0] || posX > minMaxPositions[1] ||
                posY < minMaxPositions[2] || posY > minMaxPositions[3]) {
                return;
            }
        }

        entity = AllocEntity(&g_Entities[168], &g_Entities[172]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_WINGED_GUARD, self, entity);
            entity->zPriority = 176;
            entity->posX.i.hi = posX - g_Tilemap.scrollX.i.hi;
            entity->posY.i.hi = posY - g_Tilemap.scrollY.i.hi;
            if (Random() & 1) {
                entity->posX.i.hi = 288;
            } else {
                entity->posX.i.hi = -32;
            }
            posY = ((Random() & 127) - 64);
            entity->posY.i.hi += posY;
        }
    }
}
