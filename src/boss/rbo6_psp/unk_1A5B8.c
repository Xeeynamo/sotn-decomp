// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rbo6/rbo6.h"

void func_us_8019D330_from_rcen(Entity* self) {
    typedef struct {
        u16 animSet;
        u16 unk2;
        u16 palette;
        u16 blendMode;
        u32 animation;
    } Borbo6ParticleData;
    extern Borbo6ParticleData D_pspeu_0926BC10[];
    extern u16 g_EInitParticle;

    u32 index;
    Borbo6ParticleData* particle;
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(&g_EInitParticle);
        index = self->params & 0xF;
        particle = &D_pspeu_0926BC10[index];
        self->palette = particle->palette + 0x2E0;
        self->blendMode = (u8)particle->blendMode;
        self->animSet = particle->animSet;
        self->unk5A = particle->unk2;
        self->ext.et_801A518C.anim = (u8*)particle->animation;
        self->step = index + 1;
        if (self->params & 0xFF00) {
            self->zPriority = (self->params & 0xFF00) >> 8;
        }
        if (!(self->params & 0xF0)) {
            return;
        }
        self->palette = PAL_FLAG(PAL_UNK_19F);
        self->blendMode = BLEND_TRANSP;
        self->facingLeft = 1;
        return;

    case 1:
        if (AnimateEntity(self->ext.et_801A518C.anim, self) == 0) {
            DestroyEntity(self);
        }
        break;

    case 2:
        MoveEntity();
        self->velocityY = FIX(-1.0);
        if (AnimateEntity(self->ext.et_801A518C.anim, self) == 0) {
            DestroyEntity(self);
        }
        break;

    case 3:
        if (!self->step_s) {
            self->drawFlags = ENTITY_OPACITY;
            self->drawFlags |= ENTITY_ROTATE;
            self->opacity = 0x80;
            self->facingLeft = Random() & 1;
            self->rotate = rand() & 0xFFF;
            angle = self->rotate;
            if (self->facingLeft) {
                angle = -angle;
            }
            self->velocityX = rsin(angle) * 0x28;
            self->velocityY = rcos(angle) * -0x28;
            self->ext.et_801A518C.acceleration = (Random() << 4) + 0x1000;
            self->step_s++;
        }
        MoveEntity();
        self->opacity--;
        angle = self->rotate;
        if (self->facingLeft) {
            angle = -angle;
        }
        self->velocityX +=
            (rsin(angle) * (s32)self->ext.et_801A518C.acceleration) >> 12;
        self->velocityY +=
            (-(s32)self->ext.et_801A518C.acceleration * rcos(angle)) >> 12;
        if (AnimateEntity(self->ext.et_801A518C.anim, self) == 0) {
            DestroyEntity(self);
        }
        break;

    case 4:
        if (!self->step_s) {
            self->drawFlags = ENTITY_OPACITY;
            self->opacity = 0x80;
            self->facingLeft = Random() & 1;
            self->velocityX = ((Random() << 9) - 0x8000) - 0x8000;
            self->velocityY = FIX(-2.5);
            self->ext.et_801A518C.accelerationY = -(Random() << 4) - 0x1000;
            self->step_s++;
        }
        MoveEntity();
        self->velocityY += (s32)self->ext.et_801A518C.accelerationY;
        self->opacity--;
        if (AnimateEntity(self->ext.et_801A518C.anim, self) == 0) {
            DestroyEntity(self);
        }

    default:
        return;
    }
}

INCLUDE_ASM("boss/rbo6_psp/nonmatchings/rbo6_psp/unk_1A5B8", EntityBackgroundVortex);
