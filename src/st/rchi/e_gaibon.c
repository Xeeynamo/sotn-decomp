// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rchi.h"

INCLUDE_ASM("st/rchi/nonmatchings/e_gaibon", EntityGaibon);

#include "../e_rchi_gaibon_leg.h"

INCLUDE_ASM("st/rchi/nonmatchings/e_gaibon", EntitySmallGaibonProjectile);

extern u16 D_us_80180630;
extern u8 D_us_80181754;
extern u8 D_us_80181764;

void EntityLargeGaibonProjectile(Entity* self) {
    Entity* entity;

    if (self->flags & FLAG_DEAD) {
        self->pfnUpdate = EntityExplosion;
        self->entityId = 2;
        self->drawFlags = ENTITY_DEFAULT;
        self->step = 0;
        self->params = 1;
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(&D_us_80180630);
        if (self->params == 0) {
            self->animSet = 2;
            self->drawFlags = ENTITY_ROTATE;
            self->velocityX = (rcos((s32)self->rotate) * 0x38000) >> 0xC;
            self->velocityY = (rsin((s32)self->rotate) * 0x38000) >> 0xC;
            self->palette = 0x81B6;
            self->rotate = (u16)self->rotate - 0x400;
            return;
        }

        self->animSet = 0xE;
        self->unk5A = 0x79;
        self->drawFlags = ENTITY_OPACITY | ENTITY_ROTATE | ENTITY_SCALEX;
        self->scaleX = 0x100;
        self->opacity = 0x80;
        self->palette = 0x81F3;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        self->step = 2;
        self->hitboxState = 0;
        self->flags |= FLAG_UNK_2000;
        return;

    case 1:
        MoveEntity();
        AnimateEntity(&D_us_80181754, self);
        if (!(g_Timer & 3)) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_LARGE_GAIBON_PROJECTILE, self, entity);
                entity->params = 1;
                entity->rotate = (s16)(u16)self->rotate;
                entity->zPriority = self->zPriority + 1;
                return;
            }
        }
        return;

    case 2:
        self->opacity += 0xFE;
        self->scaleX = (u16)self->scaleX - 4;
        if (AnimateEntity(&D_us_80181764, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}
