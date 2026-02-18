// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../chi/chi.h"

void EntityBreakableWallDebris(Entity* self) {
    typedef enum Step {
        INIT = 0,
        CHECK_FLAG = 1,
        MOVEMENT = 2,
    };

    Collider col;
    Entity* entity;
    s16 posX, posY;
    s32 i;

    switch (self->step) {
    case INIT:
        InitializeEntity(g_EInitSecret);
        self->animCurFrame = self->params & 0xFF;
        self->drawFlags = ENTITY_ROTATE;
        self->zPriority = 0x69;
        if (self->rotate & 1) {
            self->facingLeft = true;
            self->rotate &= 0xFFF0;
        }

        self->velocityX = (Random() & 0xF) << 0xC;
        if (self->animCurFrame == 0xD) {
            self->velocityX += FIX(0.25);
        }
        self->velocityY = ((Random() & 7) << 0xB) - FIX(0.25);
        if (self->animCurFrame < 0xB) {
            self->velocityY -= FIX(1);
        }
        self->ext.breakableDebris.rotSpeed = ((Random() & 3) + 1) * 0x20;
        break;

    case CHECK_FLAG:
        if (self->params & 0x100) {
            self->params &= 0xFF;
            self->step++;
        }
        break;

    case MOVEMENT:
        self->rotate += self->ext.breakableDebris.rotSpeed;
        MoveEntity();
        self->velocityY += FIX(0.125);
        posX = self->posX.i.hi;
        posY = self->posY.i.hi + 6;
        g_api.CheckCollision(posX, posY, &col, 0);
        if (col.effects & EFFECT_SOLID) {
            self->posY.i.hi += col.unk18;
            if (self->animCurFrame > 0xB) {
                // Break into a couple pieces
                for (i = 0; i < 2; i++) {
                    entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (entity != NULL) {
                        CreateEntityFromEntity(E_ID(ID_19), self, entity);
                        entity->params = (Random() & 3) + 9;
                        entity->params |= 0x100;
                    }
                }
                DestroyEntity(self);
                return;
            }
            if (self->velocityY < FIX(0.5)) {
                // Poof, gone
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, entity);
                    entity->params = 0x10;
                    entity->params |= 0xC000;
                }
                DestroyEntity(self);
                return;
            }

            // Bounce
            self->velocityY = -self->velocityY * 2 / 3;
        }
        break;
    }
}

INCLUDE_ASM("st/chi_psp/nonmatchings/chi_psp/en_breakable_wall", EntityBreakableWall);
