// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rchi.h"

INCLUDE_ASM("st/rchi/nonmatchings/e_gaibon", EntityGaibon);

#include "e_rchi_gaibon_leg.h"

extern EInit g_EInitGaibonProjectile;
extern u8 g_AnimSmallGaibonProjectile[];

void EntitySmallGaibonProjectile(Entity* self) {
    if (self->flags & FLAG_DEAD) {
        self->drawFlags = ENTITY_DEFAULT;
        self->step = 0;
        self->pfnUpdate = EntityExplosion;
        self->entityId = E_EXPLOSION;
        self->params = 0;
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGaibonProjectile);
        self->animSet = ANIMSET_DRA(2);
        self->animCurFrame = 1;
        self->drawFlags = ENTITY_SCALEX | ENTITY_ROTATE;
        self->scaleX = 0xC0;
        self->velocityX = (rcos(self->rotate) * FIX(2.5)) >> 0xC;
        self->velocityY = (rsin(self->rotate) * FIX(2.5)) >> 0xC;
        self->rotate -= ROT(90);
        self->palette = PAL_FLAG(PAL_UNK_1B6);

    case 1:
        MoveEntity();
        AnimateEntity(g_AnimSmallGaibonProjectile, self);
        return;
    }
}

#include "../e_gaibon_large_projectile.h"
