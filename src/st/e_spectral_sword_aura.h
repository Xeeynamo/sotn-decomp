// SPDX-License-Identifier: AGPL-3.0-or-later

void EntitySpectralSwordAura(Entity* self) {
    Entity* parent;

    if (!self->step) {
        InitializeEntity(g_EInitSpectralSwordAura);
        self->animCurFrame = 1;
#if defined(STAGE_IS_RDAI)
        self->palette += 14;
#else
        self->palette += 2;
#endif
        self->drawFlags |= ENTITY_OPACITY | ENTITY_SCALEY | ENTITY_SCALEX;
        self->blendMode = BLEND_TRANSP | BLEND_ADD;
        self->scaleX = self->scaleY = 0x100;
        self->opacity = 0x80;
    }
    parent = self->ext.et_801CEB08.unk80;
    self->posX.val = parent->posX.val;
    self->posY.val = parent->posY.val;
    self->scaleX += 6;
    self->scaleY += 6;
    self->opacity -= 4;
    if (self->opacity < 0x20) {
        DestroyEntity(self);
    }
}
