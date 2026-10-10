// SPDX-License-Identifier: AGPL-3.0-or-later

#include "rbo3.h"

extern EInit g_EInitParticle;
extern EntityConfig D_us_8018071C[];

// Entity ID 0x1B
void func_us_80192998(Entity* self) {
    s32 params;
    u32 priorityParams;
    EntityConfig* obj;

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
        priorityParams = self->params & 0xFF00;
        if (priorityParams) {
            self->zPriority = priorityParams >> 8;
        }

        if (self->params & 0xF0) {
            self->palette = PAL_FLAG(PAL_UNK_19F);
            self->blendMode = BLEND_TRANSP;
            self->facingLeft = 1;
        }
        break;

    case 1:
        if (self->step_s == 0) {
            self->drawFlags = ENTITY_OPACITY;
            self->opacity = 0xC0;
            self->facingLeft = Random() & 1;
            self->velocityX = (Random() << 8) - FIX(1.0 / 2.0);
            self->velocityY = FIX(-0.75);
            self->ext.e_80192998.accelY = -(Random() * 16) - FIX(1.0 / 4.0);
            self->step_s++;
        }
        MoveEntity();
        self->velocityY += self->ext.e_80192998.accelY;
        self->opacity += 255;
        if (AnimateEntity(self->ext.e_80192998.anim, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}
