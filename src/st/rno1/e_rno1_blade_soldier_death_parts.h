// SPDX-License-Identifier: AGPL-3.0-or-later

extern EInit g_EInitNovaSkeleton;
extern u16 D_us_80181DE0[];

void EntityBladeSoldierDeathParts(Entity* self) {
    if (self->step) {
        if (--self->ext.nova.deathPartLife) {
            self->rotate += D_us_80181DE0[self->params];
            FallEntity();
            MoveEntity();
            return;
        }

        self->entityId = E_EXPLOSION;
        self->pfnUpdate = EntityExplosion;
        self->params = 0;
        self->step = 0;
        return;
    }

    InitializeEntity(g_EInitNovaSkeleton);
    self->hitboxState = 0;
    self->flags |=
        FLAG_DESTROY_IF_OUT_OF_CAMERA | FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
        FLAG_UNK_00200000 | FLAG_UNK_2000;
    self->animCurFrame = self->params + 0x1D;
    self->drawFlags = ENTITY_ROTATE;

    if (self->facingLeft) {
        self->velocityX = -self->velocityX;
    }
}
