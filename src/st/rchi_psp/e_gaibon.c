// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rchi/rchi.h"

/* PSP RCHI's Gaibon is 1658 instructions versus NZ0's 1756. Only the
 * 90-instruction small projectile is structurally exact; leg and large
 * projectile still differ, and all four functions share stage-owned data. */
INCLUDE_ASM("st/rchi_psp/nonmatchings/rchi_psp/e_gaibon", EntityGaibon);

#include "../rchi/e_rchi_gaibon_leg.h"

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

INCLUDE_ASM("st/rchi_psp/nonmatchings/rchi_psp/e_gaibon", EntityLargeGaibonProjectile);
