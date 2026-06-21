// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno3/rno3.h"

extern EInit D_us_80180A34;

INCLUDE_ASM("st/rno3_psp/nonmatchings/rno3_psp/e_stairway", EntityStairwayPiece);

// falling rock with puff of smoke when it disappears. I think part of the
// merman room breakable rock
void EntityFallingRock(Entity* self) {
    Collider collider;
    Entity* newEntity;
    s32 rnd;
    s32 x, y;
    s32 animFrame = self->params & 0xF;
    s16 rndAngle;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180A34);
        self->animCurFrame = animFrame + 31;
        self->drawFlags |= ENTITY_ROTATE | ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleX = self->scaleY = 0x60;
        rnd = (Random() & 0x1F) + 16;
        rndAngle = (Random() * 6) + 0x900;
        self->velocityX = rnd * rcos(rndAngle);
        self->velocityY = rnd * rsin(rndAngle);
        if (self->velocityX > 0) {
            self->facingLeft = 1;
        }
        break;

    case 1:
        MoveEntity();
        self->velocityY += FIX(0.125);
        self->rotate -= 0x20;
        x = self->posX.i.hi;
        y = self->posY.i.hi + 8;
        g_api.CheckCollision(x, y, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, newEntity);
                newEntity->params = 0x10;
                if (animFrame == 0) {
                    newEntity->params = 0x13;
                }
            }
            DestroyEntity(self);
        }
        break;
    }
}
