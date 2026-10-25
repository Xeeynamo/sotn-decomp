// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rdai.h"

// EntitySpectralSword primarily uses this as a method to smoothly rotate, but
// also to retract it's outer ring after an attack by decreasing the radius.
static bool StepTowards(s16* val, s32 target, s32 step) {
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

INCLUDE_ASM("st/rdai/nonmatchings/e_spectral_sword", func_us_801C0C44);

void EntitySpectralSwordAura(Entity* self) {
    Entity* parent;

    if (!self->step) {
        InitializeEntity(g_EInitSpectralSwordAura);
        self->animCurFrame = 1;
#if defined(STAGE_IS_RDAI)
        self->palette += 14;
#else
        self->palette += 2;
#endif
        self->drawFlags |= ENTITY_OPACITY | ENTITY_SCALEY | ENTITY_SCALEX;
        self->blendMode = BLEND_TRANSP | BLEND_ADD;
        self->scaleX = self->scaleY = 0x100;
        self->opacity = 0x80;
    }
    parent = self->ext.et_801CEB08.unk80;
    self->posX.val = parent->posX.val;
    self->posY.val = parent->posY.val;
    self->scaleX += 6;
    self->scaleY += 6;
    self->opacity -= 4;
    if (self->opacity < 0x20) {
        DestroyEntity(self);
    }
}

INCLUDE_ASM("st/rdai/nonmatchings/e_spectral_sword", func_us_801C17E8);

INCLUDE_ASM("st/rdai/nonmatchings/e_spectral_sword", func_us_801C1DE8);
