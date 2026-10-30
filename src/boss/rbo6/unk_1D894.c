// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo6.h"

#ifdef VERSION_PSP
u16 PrizeDrops[ZERO_LEN] = {};
#else
u16 PrizeDrops[] = {
    ITEMDROP_STAR_FLAIL,
    0x0203,
    0x0303,
    0x0403,
    0x0503,
    0x0603,
    0x0703,
    0x0803,
    0x0903,
    0x0A03,
    0x0B03,
    0x0C03,
    0x0D03,
    ITEMDROP_GREAT_SWORD,
};
#endif

typedef struct {
    u16 animSet;
    u16 unk2;
    u16 palette;
    u16 blendMode;
    AnimateEntityFrame* animation;
} Borbo6ParticleData;
extern Borbo6ParticleData D_us_801806B4[];
extern u16 g_EInitParticle;

void func_us_8019D330_from_rcen(Entity* self) {
    u32 index;
    Borbo6ParticleData* particle;
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(&g_EInitParticle);
        index = self->params & 0xF;
        particle = &D_us_801806B4[index];
        self->palette = particle->palette + 0x2E0;
        self->blendMode = particle->blendMode;
        self->animSet = particle->animSet;
        self->unk5A = particle->unk2;
        self->ext.et_801A518C.anim = particle->animation;
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
            self->velocityX = rsin(angle) * 40;
            self->velocityY = rcos(angle) * -40;
            self->ext.et_801A518C.acceleration = (Random() << 4) + 0x1000;
            self->step_s++;
        }
        MoveEntity();
        self->opacity -= 1;
        angle = self->rotate;
        if (self->facingLeft) {
            angle = -angle;
        }
        self->velocityX +=
            (rsin(angle) * self->ext.et_801A518C.acceleration) >> 12;
        self->velocityY +=
            (-self->ext.et_801A518C.acceleration * rcos(angle)) >> 12;
        if (AnimateEntity(self->ext.et_801A518C.anim, self) == 0) {
            DestroyEntity(self);
        }
        break;

    case 4:
        if (!self->step_s) {
            self->drawFlags = ENTITY_OPACITY;
            self->opacity = 0x80;
            self->facingLeft = Random() & 1;
            self->velocityX = ((Random() * FIX(1.0/128)) - FIX(0.5)) - FIX(0.5);
            self->velocityY = FIX(-2.5);
            self->ext.et_801A518C.accelerationY = -(Random() << 4) - 0x1000;
            self->step_s++;
        }
        MoveEntity();
        self->velocityY += (s32)self->ext.et_801A518C.accelerationY;
        self->opacity -= 1;
        if (AnimateEntity(self->ext.et_801A518C.anim, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}
