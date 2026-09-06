// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno4.h"

extern Entity g_Entities_224;

void EntityBreakableWallDebris(Entity* self) {
    Collider collider;
    Entity* debris;
#ifdef VERSION_PSP
    s32 collX;
    s32 collY;
#endif

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        self->drawFlags = ENTITY_ROTATE;
        self->animSet = ANIMSET_OVL(1);
        if (Random() & 1) {
            self->animCurFrame = 0x26;
        } else {
            self->animCurFrame = 0x27;
        }
        if (self->velocityX < 0) {
            self->facingLeft = 1;
        }
        /* fall through */
    case 1:
        MoveEntity();
#ifdef VERSION_PSP
        self->rotate += ROT(2.8125);
        if (self->params) {
            self->rotate += ROT(2.8125);
        }
#else
        {
            u16 rotation = self->rotate;
            self->rotate = rotation + 0x20;
            if (self->params != 0) {
                self->rotate = rotation + 0x40;
            }
        }
#endif
        self->velocityY += FIX(0.125);
#ifdef VERSION_PSP
        collX = self->posX.i.hi;
        collY = self->posY.i.hi + 6;
        g_api.CheckCollision(collX, collY, &collider, 0);
#else
        g_api.CheckCollision(
            self->posX.i.hi, self->posY.i.hi + 6, &collider, 0);
#endif
        if (collider.effects & EFFECT_SOLID) {
#ifdef VERSION_PSP
            self->posY.i.hi += collider.unk18;
            if (self->velocityY < FIX(0.5)) {
                debris = AllocEntity(&g_Entities[224], &g_Entities[256]);
#else
            self->posY.i.hi = (u16)self->posY.i.hi + (u16)collider.unk18;
            if (self->velocityY <= 0x7FFF) {
                debris = AllocEntity(&g_Entities[224], &g_Entities[256]);
#endif
                if (debris != 0) {
                    CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, debris);
                    debris->params = 0x10;
                }
                DestroyEntity(self);
                return;
            }
            self->velocityY = (-self->velocityY * 2) / 3;
        }
        break;
    }
}
