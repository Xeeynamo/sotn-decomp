// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rlib.h"

INCLUDE_ASM("st/rlib/nonmatchings/unk_2DBE8", func_us_801ADBE8);

extern EInit D_us_8018064C;
extern s8 g_HarpyKickHitboxes[];
extern u8 g_HarpyKickHitboxIdx[];

void EntityHarpyKick(Entity* self) {
    s32 animFrame;
    s8* hitbox;
    Entity* harpy;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_8018064C);
        /* fall through */
    case 1:
        harpy = self - 1;
        self->facingLeft = harpy->facingLeft;
        self->posX.val = harpy->posX.val;
        self->posY.val = harpy->posY.val;
        animFrame = harpy->animCurFrame;
        hitbox = g_HarpyKickHitboxes;
        animFrame = g_HarpyKickHitboxIdx[animFrame];
        hitbox += animFrame * 4;
        self->hitboxOffX = *hitbox++;
        self->hitboxOffY = *hitbox++;
        self->hitboxWidth = *hitbox++;
        self->hitboxHeight = *hitbox++;
        if (harpy->entityId != E_UNK_1C) {
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit D_us_80180658;
extern s32 D_us_801817CC[];

void func_us_801AE414(Entity* self) {
    switch (self->step_s) {
    case 0:
        InitializeEntity(D_us_80180658);
        self->animCurFrame = self->params + 0x1C;
        /* fall through */
    case 1:
        MoveEntity();
        self->velocityY += (u32)self->ext.et_801AE414.accelY;
        self->ext.et_801AE414.accelY += D_us_801817CC[self->params];
    }
}

INCLUDE_ASM("st/rlib/nonmatchings/unk_2DBE8", func_us_801AE4B4);

INCLUDE_ASM("st/rlib/nonmatchings/unk_2DBE8", func_us_801AE534);

INCLUDE_ASM("st/rlib/nonmatchings/unk_2DBE8", func_us_801AED4C);

extern EInit D_us_80180688;
extern AnimationFrame D_us_80181888;

void func_us_801AEFE0(Entity* self) {
    Entity* parent;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180688);
        self->blendMode = BLEND_TRANSP;
        PlaySfxPositional(SFX_NOISE_SWEEP_DOWN_B);
        /* fall through */
    case 1:
        parent = self->ext.et_801AEFE0.parent;
        self->posX.val = parent->posX.val;
        self->posY.val = parent->posY.val;
        if (AnimateEntity(&D_us_80181888, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit D_us_8018067C;
extern AnimationFrame D_us_8018189C;

void func_us_801D8D44_from_no4(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_8018067C);
        if (self->facingLeft) {
            self->velocityX = FIX(6);
        } else {
            self->velocityX = FIX(-6);
        }
        /* fall through */
    case 1:
        MoveEntity();
        AnimateEntity(&D_us_8018189C, self);
        if (self->flags & FLAG_DEAD) {
            DestroyEntity(self);
        }
        break;
    }
}

INCLUDE_ASM("st/rlib/nonmatchings/unk_2DBE8", func_us_801AF11C);

INCLUDE_ASM("st/rlib/nonmatchings/unk_2DBE8", func_us_801AF3C8);

INCLUDE_ASM("st/rlib/nonmatchings/unk_2DBE8", func_us_801AF448);

INCLUDE_ASM("st/rlib/nonmatchings/unk_2DBE8", func_us_801AF9E8);

extern EInit g_EInitSchmoo;
extern AnimationFrame D_us_8018198C;
extern AnimationFrame D_us_80181998;

void func_us_801AFC88(Entity* self) {
    Entity* entity;
    s32 sideToPlayer;
    s32 distanceToPlayer;

    if (self->flags & FLAG_DEAD) {
        PlaySfxPositional(SFX_EXPLODE_B);
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 1;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSchmoo);
        self->drawFlags = ENTITY_ROTATE;
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        /* fall through */
    case 1:
        AnimateEntity(&D_us_8018198C, self);
        MoveEntity();
        sideToPlayer = GetSideToPlayer();

        if (self->facingLeft) {
            self->velocityX += FIX(0.046875);
            if (self->velocityX > FIX(3)) {
                self->velocityX = FIX(3);
            }
        } else {
            self->velocityX -= FIX(0.046875);
            if (self->velocityX < FIX(-3)) {
                self->velocityX = FIX(-3);
            }
        }

        if (sideToPlayer & 2) {
            self->velocityY -= FIX(0.046875);
            if (self->velocityY < FIX(-1.5)) {
                self->velocityY = FIX(-1.5);
            }
        } else {
            self->velocityY += FIX(0.046875);
            if (self->velocityY > FIX(1.5)) {
                self->velocityY = FIX(1.5);
            }
        }

        sideToPlayer = (sideToPlayer & 1) ^ 1;
        distanceToPlayer = GetDistanceToPlayerX();
        if (sideToPlayer != self->facingLeft && distanceToPlayer >= 0x59) {
            SetStep(2);
        }
        break;

    case 2:
        MoveEntity();
        switch (self->step_s) {
        case 0:
            self->velocityX -= self->velocityX >> 4;
            self->velocityY -= self->velocityY >> 4;
            if (abs(self->velocityX) < FIX(0.25)) {
                self->step_s++;
            }
            break;

        case 1:
            self->velocityX -= self->velocityX >> 8;
            self->velocityY -= self->velocityY >> 8;
            if (AnimateEntity(&D_us_80181998, self) == 0) {
                SetStep(1);
            }
            if (!self->poseTimer && self->pose == 2) {
                self->facingLeft ^= 1;
            }
            break;
        }
        break;
    }

    self->rotate = -abs(self->velocityX >> 8);
}
