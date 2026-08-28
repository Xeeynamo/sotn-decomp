// SPDX-License-Identifier: AGPL-3.0-or-later
void EntityGaibonLeg(Entity* self) {
    Entity* parent;
    s32 frame;

    if (!self->step) {
        InitializeEntity(g_EInitGaibon);
        self->hitboxState = 0;
    }

    parent = self - 1;
    self->facingLeft = parent->facingLeft;
    self->palette = parent->palette;
    self->posX.i.hi = parent->posX.i.hi;
    self->posY.i.hi = parent->posY.i.hi;
    self->animCurFrame = 0;
    frame = parent->animCurFrame;

    if (0x1F < frame && frame < 0x23) {
        self->animCurFrame = 0x26;
    } else if (frame == 0x23) {
        self->animCurFrame = 0x27;
    } else if (0x23 < frame && frame < 0x26) {
        self->animCurFrame = 0x28;
    }

    if (parent->entityId != 0x19) {
        DestroyEntity(self);
    }
}
