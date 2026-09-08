// SPDX-License-Identifier: AGPL-3.0-or-later
void func_us_8019C610(Entity* self) {
    Entity* entity;
    s16 angle;

    if (g_RcenShaftFlags & 4) {
        DestroyEntity(self);
        return;
    }

    if (!self->step) {
        InitializeEntity(D_us_80180588);
        self->palette = 0x2E4;
        self->drawFlags = ENTITY_OPACITY | ENTITY_ROTATE;
        self->rotate = (s16)(self->ext.rcenShaftProjectile.angle + 0x400);
        angle = self->ext.rcenShaftProjectile.angle;
        self->velocityX = (rcos(angle) * 0x30000) >> 0xC;
        self->velocityY = (rsin(angle) * 0x30000) >> 0xC;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
    }

    MoveEntity();
    angle = self->ext.rcenShaftProjectile.angle;
    self->velocityX += (rcos(angle) << 0xA) >> 0xC;
    self->velocityY += (rsin(angle) << 0xA) >> 0xC;

    if (self->params && self->pose == 7 && !self->poseTimer) {
        entity = AllocEntity(&g_Entities[112], &g_Entities[192]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_ID(UNK_1C), self, entity);
            entity->zPriority = self->zPriority;
            entity->params = self->params - 1;
            entity->ext.rcenShaftProjectile.angle =
                self->ext.rcenShaftProjectile.angle;
        }
    }

    self->opacity -= 2;
    if (!self->opacity) {
        DestroyEntity(self);
        return;
    }
    if (!AnimateEntity(D_us_80180874, self)) {
        DestroyEntity(self);
    }
}
