// SPDX-License-Identifier: AGPL-3.0-or-later
void func_us_8019C4EC(Entity* self) {
    Entity* parent;
    s16 angle;

    if (g_RcenShaftFlags & 4) {
        DestroyEntity(self);
        return;
    }

    if (!self->step) {
        InitializeEntity(D_us_80180588);
        self->palette = 0x2E7;
        self->velocityX = 0;
        self->drawFlags = ENTITY_ROTATE;
        self->rotate = (s16)(self->ext.rcenShaftProjectile.angle + 0x400);
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
    }

    self->velocityX += FIX(1.0);
    parent = self->ext.rcenShaftProjectile.parent;
    angle = self->ext.rcenShaftProjectile.angle;
    self->posX.i.hi = parent->posX.i.hi;
    self->posY.i.hi = parent->posY.i.hi;
    self->posX.val += (self->velocityX >> 12) * rcos(angle);
    self->posY.val += (self->velocityX >> 12) * rsin(angle);

    if (AnimateEntity(D_us_80180890, self) == 0) {
        DestroyEntity(self);
    }
}
