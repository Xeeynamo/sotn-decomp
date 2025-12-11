// SPDX-License-Identifier: AGPL-3.0-or-later
#include "stage.h"

#ifdef VERSION_PSP
extern s32 E_ID(EXPLODE_PUFF_OPAQUE);
#endif

extern EInit g_EInitParticle;

static u8 puff_anim_one[] = {
    0x03, 0x01, 0x03, 0x02, 0x03, 0x03, 0x03, 0x04, 0x03, 0x05,
    0x03, 0x06, 0x03, 0x07, 0x03, 0x08, 0x03, 0x09, 0x03, 0x0A,
    0x03, 0x0B, 0x03, 0x0C, 0x03, 0x0D, 0xFF, 0x00,
};
static u8 puff_anim_two[] = {
    0x02, 0x01, 0x02, 0x02, 0x02, 0x03, 0x02, 0x04, 0x02, 0x05,
    0x02, 0x06, 0x02, 0x07, 0x02, 0x08, 0x02, 0x09, 0x02, 0x0A,
    0x02, 0x0B, 0x02, 0x0C, 0x02, 0x0D, 0x02, 0x0E, 0xFF, 0x00,
};
static EntityConfig puff_config[] = {
    PUFF_PARAMS_0,
    PUFF_PARAMS_1,
    PUFF_PARAMS_2,
    PUFF_PARAMS_3,
};

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

void EntityExplosionPuffOpaque(Entity* self) {
    EntityConfig* obj;
#ifdef STAGE_IS_NZ1
    s16 rotate;
#endif
    s32 params;
    s32 speed;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        params = self->params & 0xF;
        obj = &puff_config[params];
        self->palette = obj->palette + PAL_PUFF_OPAQUE_OFFSET;
        self->drawMode = obj->drawMode;
        self->animSet = obj->animSet;
        self->unk5A = obj->unk5A;
        self->ext.opaquePuff.anim = obj->animData;
        self->step = params + 1;

        if (self->params & 0xFF00) {
            self->zPriority = (self->params & 0xFF00) >> 8;
        }

        if (self->params & 0xF0) {
            self->palette = PAL_FLAG(PAL_UNK_19F);
            self->drawMode = DRAW_TPAGE;
            self->facingLeft = 1;
        }
        break;

    case 1:
#if defined(STAGE_IS_ARE) || defined(STAGE_IS_NZ1)
        if (!self->step_s) {
            self->velocityY = FIX(-0.875);
            self->step_s++;
        }
#endif
        MoveEntity();
#if defined(STAGE_IS_ARE) || defined(STAGE_IS_NZ1)
#elif defined(STAGE_IS_NZ0)
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
#ifdef STAGE_IS_NZ1
        if (!self->step_s) {
            self->drawFlags = FLAG_DRAW_OPACITY;
            self->drawFlags |= FLAG_DRAW_ROTATE;
            self->opacity = 0x80;
            self->facingLeft = Random() & 1;
            self->rotate = (Random() & 0x1F) * 0x10;
            rotate = self->rotate;
            if (self->facingLeft) {
                rotate = -rotate;
            }
            self->velocityX = rsin(rotate) * 0x18;
            self->velocityY = rcos(rotate) * -0x18;
            self->ext.opaquePuff.unk8C = Random() * 0x10 + 0x4000;
            self->step_s++;
        }
        MoveEntity();
        self->opacity -= 1;
        rotate = self->rotate;
        if (self->facingLeft) {
            rotate = -rotate;
        }
        self->velocityX += self->ext.opaquePuff.unk8C * rsin(rotate) >> 0xC;
        self->velocityY += -self->ext.opaquePuff.unk8C * rcos(rotate) >> 0xC;

#else
        if (!self->step_s) {
            self->facingLeft = Random() & 1;
            self->drawFlags |= FLAG_DRAW_SCALEX;
            self->scaleX = 0xC0;
            self->step_s++;
            self->velocityY = FIX(-0.75);
        }
        MoveEntity();
#endif
        if (AnimateEntity(self->ext.opaquePuff.anim, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}
