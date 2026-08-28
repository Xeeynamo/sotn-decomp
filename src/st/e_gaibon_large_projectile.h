// SPDX-License-Identifier: AGPL-3.0-or-later

extern EInit g_EInitGaibonLargeProjectile;

static u8 anim_large_fireball1[] = {
    2, 13, 2, 14, 2, 15, 2, 16, 2, 15, 2, 14, 0, 0};
static u8 anim_large_fireball2[] = {
    1, 1, 1, 2, 1, 3,  1, 4,  1, 5,  1, 6,  1,  7,
    1, 8, 1, 9, 1, 10, 1, 11, 1, 12, 1, 13, -1, 0};

void EntityLargeGaibonProjectile(Entity* self) {
    Entity* newEntity;

    if (self->flags & FLAG_DEAD) {
        self->drawFlags = ENTITY_DEFAULT;
        self->step = 0;
        self->pfnUpdate = EntityExplosion;
        self->entityId = 2;
        self->params = 1;
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGaibonLargeProjectile);
        if (!self->params) {
            self->animSet = ANIMSET_DRA(2);
            self->drawFlags = ENTITY_ROTATE;
            self->velocityX = (rcos(self->rotate) * FIX(3.5)) >> 0xC;
            self->velocityY = (rsin(self->rotate) * FIX(3.5)) >> 0xC;
            self->rotate -= 0x400;
            self->palette = PAL_FLAG(PAL_UNK_1B6);
        } else {
            self->animSet = ANIMSET_DRA(14);
            self->unk5A = 0x79;
            self->drawFlags = ENTITY_SCALEX | ENTITY_ROTATE | ENTITY_OPACITY;
            self->scaleX = 0x100;
            self->opacity = 0x80;
            self->palette = PAL_FLAG(PAL_UNK_1F3);
            self->blendMode = BLEND_TRANSP | BLEND_ADD;
            self->step = 2;
            self->hitboxState = 0;
            self->flags |= FLAG_UNK_2000;
        }
        break;

    case 1:
        MoveEntity();
        AnimateEntity(anim_large_fireball1, self);
        if (!(g_Timer & 3)) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(
                    E_ID(GAIBON_BIG_FIREBALL), self, newEntity);
                newEntity->params = 1;
                newEntity->rotate = self->rotate;
                newEntity->zPriority = self->zPriority + 1;
            }
        }
        break;

    case 2:
        self->opacity -= 2;
        self->scaleX -= 4;
        if (AnimateEntity(anim_large_fireball2, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}
