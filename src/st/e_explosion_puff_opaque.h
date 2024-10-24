// SPDX-License-Identifier: AGPL-3.0-or-later
#include "stage.h"

void CreateExplosionPuff() {
    Entity* entity;
    s8 temp_s4 = Random() & 3;
    s16 temp_s3 = ((Random() & 0xF) << 8) - 0x800;
    s32 i;

    for (i = 0; i < 6; i++) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_WARG_EXP_OPAQUE, g_CurrentEntity, entity);
            entity->params = 2;
            entity->ext.opaquePuff.unk89 = 6 - i;
            entity->ext.opaquePuff.unk84 = temp_s3;
            entity->ext.opaquePuff.unk88 = temp_s4;
        }
    }
}

extern Unkstruct_80180FE0 D_80180FE0[];

void EntityExplosionPuffOpaque(Entity* self) {
    Unkstruct_80180FE0* obj;
    s32 velocityX;
    s32 velocityY;
    s32 params;
    s32 temp_s0;
    s32 adjVelocityX;
    s32 adjVelocityY;
    u32 temp_v0;
    s32 rnd;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        params = self->params & 0xF;
        obj = &D_80180FE0[params];
        self->palette = obj->palette + E_PUFF_OPAQUE_PALETTE_OFFSET;
        self->drawMode = obj->drawMode;
        self->animSet = obj->animSet;
        self->unk5A = obj->unk2;
        self->ext.opaquePuff.anim = obj->anim;
        self->step = params + 1;

        temp_v0 = self->params & 0xFF00;
        if (temp_v0 != 0) {
            self->zPriority = temp_v0 >> 8;
        }

        if (self->params & 0xF0) {
            self->palette = 0x819F;
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
        if (AnimateEntity(self->ext.opaquePuff.anim, self) != 0) {
            switch (self->step_s) {
            case 0:
                self->drawFlags = FLAG_DRAW_UNK8;
                self->unk6C = 0x80;
                self->step_s++;
                break;

            case 1:
                if (self->animFrameIdx == 5) {
                    self->step_s++;
                }
                break;

            case 2:
                self->unk6C += 0xFC;
                break;
            }
        } else {
            DestroyEntity(self);
        }
        break;

    case 3:
        if (self->step_s == 0) {
            self->drawFlags |= FLAG_DRAW_ROTZ;
            switch (self->ext.opaquePuff.unk88) {
            case 1:
                if (self->ext.opaquePuff.unk89 >= 0x4) {
                    self->ext.opaquePuff.unk89 += 0xFD;
                    self->ext.opaquePuff.unk84 -= 0x800;
                }
                break;

            case 2:
                self->ext.opaquePuff.unk84 =
                    (u16)self->ext.opaquePuff.unk84 +
                    ((u8)self->ext.opaquePuff.unk89 * 0xC0);
                break;
            }
            self->ext.opaquePuff.unk84 = self->ext.opaquePuff.unk84 & 0xFFF;
            self->rotZ = self->ext.opaquePuff.unk84 & 0xFFF;
            temp_s0 = self->ext.opaquePuff.unk89 * 0x140;
            temp_s0 /= 28;
            self->velocityX = temp_s0 * rsin(self->ext.opaquePuff.unk84);
            self->velocityY = -(temp_s0 * rcos(self->ext.opaquePuff.unk84));
            self->step_s++;
        }

        if (self->animFrameIdx >= 13) {
            velocityX = self->velocityX;
            if (velocityX < 0) {
                adjVelocityX = velocityX + 3;
            } else {
                adjVelocityX = velocityX;
            }
            self->velocityX = velocityX - (adjVelocityX >> 2);

            velocityY = self->velocityY;
            if (velocityY < 0) {
                adjVelocityY = velocityY + 3;
            } else {
                adjVelocityY = velocityY;
            }
            self->velocityY = velocityY - (adjVelocityY >> 2);
        }
        MoveEntity();
        if (AnimateEntity(self->ext.opaquePuff.anim, self) == 0) {
            DestroyEntity(self);
        }
        break;

    case 4:
        if (self->step_s == 0) {
            rnd = Random();
            self->velocityY = FIX(-0.75);
            self->facingLeft = rnd & 1;
            self->rotX = 0xC0;
            self->drawFlags |= FLAG_DRAW_ROTX;
            self->step_s++;
        }
        MoveEntity();
        if (AnimateEntity(self->ext.opaquePuff.anim, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}
