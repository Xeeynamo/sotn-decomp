// SPDX-License-Identifier: AGPL-3.0-or-later

#include "rbo3.h"

extern EInit g_EInitParticle;

static u8 D_us_801806C4[] = {
    3, 1, 3, 2, 3, 3,  3, 4,  3, 5,  3, 6,  3,   7,
    3, 8, 3, 9, 3, 10, 3, 11, 3, 12, 3, 13, 255, 0,
};
static u8 unused_anim_1[] = {
    3, 1, 3, 2, 3, 3,  3, 4,  3, 5,  3, 6,  3, 7,
    3, 8, 3, 9, 3, 10, 3, 11, 3, 12, 3, 13, 0, 0,
};
static u8 unused_anim_2[] = {
    2, 1, 2, 2, 2,  3, 2,  4, 2,  5, 2,  6, 2,  7, 2,
    8, 2, 9, 2, 10, 2, 11, 2, 12, 2, 13, 2, 14, 0, 0,
};
static EntityConfig D_us_8018071C[] = {
    {0x8004, 0x50, 0x000D, 0x0030, D_us_801806C4},
};

// Entity ID 0x1B
void func_us_80192998(Entity *self) {
  s32 params;
  EntityConfig *obj;

  switch (self->step) {
  case 0:
    InitializeEntity(g_EInitParticle);
    params = self->params & 0xF;
    obj = &D_us_8018071C[params];
    self->palette = obj->palette + 0x2E0;
    self->blendMode = obj->blendMode;
    self->animSet = obj->animSet;
    self->unk5A = obj->unk5A;
    self->ext.e_80192998.anim = obj->animData;
    self->step = params + 1;
    if (self->params & 0xFF00) {
      self->zPriority = (self->params & 0xFF00) >> 8;
    }

    if (self->params & 0xF0) {
      self->palette = PAL_FLAG(PAL_UNK_19F);
      self->blendMode = BLEND_TRANSP;
      self->facingLeft = 1;
    }
    break;

  case 1:
    if (!self->step_s) {
      self->drawFlags = ENTITY_OPACITY;
      self->opacity = 0xC0;
      self->facingLeft = Random() & 1;
      self->velocityX = (Random() << 8) - FIX(1.0 / 2.0);
      self->velocityY = FIX(-0.75);
      self->ext.e_80192998.accelY = -(Random() * 16) - FIX(1.0 / 4.0);
      self->step_s++;
    }
    MoveEntity();
    self->velocityY += (s32)self->ext.e_80192998.accelY;
    self->opacity -= 1;
    if (!AnimateEntity(self->ext.e_80192998.anim, self)) {
      DestroyEntity(self);
    }
    break;
  }
}
