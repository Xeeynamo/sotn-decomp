// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno4/rno4.h"

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1A988", EntityBreakable);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1A988", func_us_801C123C_from_no4);

extern s32 g_ExplosionVariantVelocity[];
extern u8 g_ExplosionVariantFrames[];
extern u16 g_ExplosionVariantDurations[];

void EntityExplosionVariants(Entity* self) {
    if (!self->step) {
        self->velocityY =
            g_ExplosionVariantVelocity[self->ext.destructAnim.index];
        self->flags =
            FLAG_UNK_2000 | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_POS_CAMERA_LOCKED;
        self->palette = PAL_FLAG(PAL_UNK_195);
        self->animSet = ANIMSET_DRA(2);
        self->animCurFrame = g_ExplosionVariantFrames[self->params];
        self->blendMode = BLEND_TRANSP;
        self->step++;
        return;
    }

    self->posY.val -= self->velocityY;
    ++self->poseTimer;
    if ((self->poseTimer % 2) == 0) {
        self->animCurFrame++;
    }
    if (self->poseTimer > g_ExplosionVariantDurations[self->params]) {
        DestroyEntity(self);
    }
}

void EntityGreyPuff(Entity* self) {
    extern s16 g_GreyPuffScale[];
    extern s32 g_GreyPuffVelocity[];

    if (!self->step) {
        self->flags =
            FLAG_UNK_2000 | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_POS_CAMERA_LOCKED;
        self->palette = PAL_FLAG(PAL_UNK_195);
        self->animSet = ANIMSET_DRA(5);
        self->animCurFrame = 1;
        self->blendMode = BLEND_TRANSP;
        self->drawFlags = ENTITY_SCALEX | ENTITY_SCALEY;
        self->scaleX = g_GreyPuffScale[self->params];
        self->scaleY = self->scaleX;
        self->velocityY = g_GreyPuffVelocity[self->params];
        self->step++;
    } else {
        self->posY.val -= self->velocityY;
        self->poseTimer++;
        if ((self->poseTimer % 2) == 0) {
            self->animCurFrame++;
        }
        if (self->poseTimer > 36) {
            DestroyEntity(self);
        }
    }
}

void EntityIntenseExplosion(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitParticle);
        self->palette = PAL_FLAG(PAL_UNK_170);
        self->animSet = 5;
        self->animCurFrame = 1;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        if (self->params & 0xF0) {
            self->palette = PAL_FLAG(PAL_UNK_195);
            self->blendMode = BLEND_TRANSP;
        }
        if (self->params & 0xFF00) {
            self->zPriority = (u16)((self->params & 0xFF00) >> 8);
        }
        self->zPriority += 8;
        return;
    }

    self->poseTimer++;
    self->posY.val -= FIX(0.25);

    if (((s16)self->poseTimer % 2) == 0) {
        self->animCurFrame++;
    }

    if ((s16)self->poseTimer <= 0x24) {
        return;
    } else {
        DestroyEntity(self);
    }
}

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1A988", PlaySfxPositional);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1A988", func_pspeu_09246618_from_bo3);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1A988", func_us_801A07CC_from_bo3);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1A988", func_us_801C5518_from_no4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1A988", func_pspeu_09252F98);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1A988", func_us_801C909C);

extern ObjInit2 BackgroundBlockInit[];

void EntityBackgroundBlock(Entity* self) {
    ObjInit2* objInit = &BackgroundBlockInit[self->params];

    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = objInit->animSet;
        self->zPriority = objInit->zPriority;
        self->unk5A = LOHU(objInit->facingLeft);
        self->palette = objInit->palette;
        self->drawFlags = objInit->drawFlags;
        self->blendMode = objInit->blendMode;
        if (objInit->flags) {
            self->flags = objInit->flags;
        }
    }

    AnimateEntity(objInit->animFrames, self);
}
