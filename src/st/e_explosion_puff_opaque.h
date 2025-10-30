// SPDX-License-Identifier: AGPL-3.0-or-later
#include "stage.h"

#ifdef VERSION_PSP
extern s32 E_ID(EXPLODE_PUFF_OPAQUE);
#endif

void CreateExplosionPuff() {
    Entity* puff;
    s32 rand3 = Random() & 3; // Random puff style 0, 1, 2
    s16 initAngle = ((Random() & 0xF) << 8) - 0x800;
    s32 i;

    for (i = 0; i < 6; i++) {
        puff = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (puff != NULL) {
            CreateEntityFromEntity(
                E_ID(EXPLODE_PUFF_OPAQUE), g_CurrentEntity, puff);
            puff->params = 2;
            puff->ext.opaquePuff.speed = 6 - i;
            puff->ext.opaquePuff.angle = initAngle;
            puff->ext.opaquePuff.puffStyle = rand3;
        }
    }
}

extern EntityConfig D_80180FE0[];

void EntityExplosionPuffOpaque(Entity* self) {
    EntityConfig* obj;
    s32 params;
    s32 speed;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        params = self->params & 0xF;
        obj = &D_80180FE0[params];
        self->palette = obj->palette + E_PUFF_OPAQUE_PALETTE_OFFSET;
        self->drawMode = obj->drawMode;
        self->animSet = obj->animSet;
        self->unk5A = obj->unk5A;
        self->ext.opaquePuff.anim = obj->animData;
        self->step = params + 1;

        if (self->params & 0xFF00) {
            self->zPriority = (self->params & 0xFF00) >> 8;
        }

        if (self->params & 0xF0) {
            self->palette = PAL_FLAG(0x19F);
            self->drawMode = DRAW_TPAGE;
            self->facingLeft = 1;
        }
        break;

    case 1:
        MoveEntity();
#if defined(STAGE_IS_NZ0)
        self->velocityY = FIX(-1);
#else
        self->velocityY = FIX(1);
#endif
        if (AnimateEntity(self->ext.opaquePuff.anim, self) == 0) {
            DestroyEntity(self);
        }
        break;

    case 2:
        if (AnimateEntity(self->ext.opaquePuff.anim, self) == 0) {
            DestroyEntity(self);
            break;
        }
        switch (self->step_s) {
        case 0:
            self->drawFlags = FLAG_DRAW_OPACITY;
            self->opacity = 0x80;
            self->step_s++;
            break;

        case 1:
            if (self->pose == 5) {
                self->step_s++;
            }
            break;

        case 2:
            self->opacity -= 4;
            break;
        }

        break;

    case 3:
        if (!self->step_s) {
            self->drawFlags |= FLAG_DRAW_ROTATE;
            switch (self->ext.opaquePuff.puffStyle) {
            case 1:
                if (self->ext.opaquePuff.speed > 3) {
                    self->ext.opaquePuff.speed -= 3;
                    self->ext.opaquePuff.angle =
                        self->ext.opaquePuff.angle - 0x800;
                }
                break;

            case 2:
                self->ext.opaquePuff.angle +=
                    (self->ext.opaquePuff.speed * 0xC0);
                break;
            }
            self->ext.opaquePuff.angle &= 0xFFF;
            self->rotate = self->ext.opaquePuff.angle;
            speed = self->ext.opaquePuff.speed * 0x140 / 28;
            self->velocityX = speed * rsin(self->ext.opaquePuff.angle);
            self->velocityY = -(speed * rcos(self->ext.opaquePuff.angle));
            self->step_s++;
        }

        if (self->pose > 12) {
            self->velocityX -= self->velocityX / 4;
            self->velocityY -= self->velocityY / 4;
        }
        MoveEntity();
        if (AnimateEntity(self->ext.opaquePuff.anim, self) == 0) {
            DestroyEntity(self);
        }
        break;

    case 4:
        if (!self->step_s) {
            self->facingLeft = Random() & 1;
            self->drawFlags |= FLAG_DRAW_SCALEX;
            self->scaleX = 0xC0;
            self->step_s++;
            self->velocityY = FIX(-0.75);
        }
        MoveEntity();
        if (AnimateEntity(self->ext.opaquePuff.anim, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}
