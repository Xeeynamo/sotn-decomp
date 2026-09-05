// SPDX-License-Identifier: AGPL-3.0-or-later

extern EInit g_EInitWerewolfARE;

void EntityWerewolfSpinAttackAfterImage(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitWerewolfARE);
        self->palette = g_EInitWerewolfARE[3] + PAL_FLAG(9);
        self->blendMode = BLEND_TRANSP | BLEND_ADD;
        self->hitboxState = 0;
        self->drawFlags = ENTITY_OPACITY | ENTITY_ROTATE;
        self->animCurFrame = self->params;
        self->flags |= FLAG_UNK_00200000 | FLAG_UNK_2000;
        self->opacity = 0x60;
    }

    self->ext.werewolf.timer++;
    if ((!self->ext.werewolf.timer) & 1) {
        self->animCurFrame = 0;
    } else {
        self->animCurFrame = self->params;
    }

    self->opacity -= 8;
    if (!self->opacity) {
        DestroyEntity(self);
    }
}
