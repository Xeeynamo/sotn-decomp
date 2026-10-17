// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rlib/rlib.h"

INCLUDE_ASM("st/rlib_psp/nonmatchings/rlib_psp/unk_10548", EntityLion);

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
        if (harpy->entityId != E_LION) {
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
