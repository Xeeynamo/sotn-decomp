// SPDX-License-Identifier: AGPL-3.0-or-later

extern EInit g_EInitParticle;
extern u8 anim_torch_puff[];

void func_us_801A4BA4(Entity* self) {
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        self->animSet = 0xE;
        self->unk5A = 0x79;
        self->palette = 0x227;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        self->drawFlags = ENTITY_OPACITY | ENTITY_ROTATE;
        self->opacity = 0x80;
        self->facingLeft = Random() & 1;
        self->drawFlags |= ENTITY_SCALEY;
        self->scaleY = 0x180;

        angle = self->rotate;
        if (self->facingLeft) {
            angle = -angle;
        }
        self->velocityX = rsin(angle) * 0x28;
        self->velocityY = rcos(angle) * -0x28;
        self->ext.opaquePuff.unk8C = (Random() * 0x10) + 0x1000;

    case 1:
        MoveEntity();
        self->opacity -= 2;
        angle = self->rotate;
        if (self->facingLeft) {
            angle = -angle;
        }
        self->velocityX += (rsin(angle) * self->ext.opaquePuff.unk8C) >> 0xC;
        self->velocityY += (-self->ext.opaquePuff.unk8C * rcos(angle)) >> 0xC;
        if (AnimateEntity(anim_torch_puff, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}
