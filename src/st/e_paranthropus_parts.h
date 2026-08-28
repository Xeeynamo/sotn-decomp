// SPDX-License-Identifier: AGPL-3.0-or-later

void EntityParanthropusThrownBone(Entity* self) {
    if (self->flags & FLAG_DEAD) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParanthropusThrownBone);
        self->drawFlags |= ENTITY_ROTATE;
        if (self->facingLeft) {
            self->velocityX = FIX(2.0);
        } else {
            self->velocityX = FIX(-2.0);
        }
        self->velocityY = FIX(-6.0);
        break;
    case 1:
        MoveEntity();
        self->rotate -= ROT(22.5);
        self->velocityY += FIX(0.25);
        break;
    }
}

void EntityParanthropusBoneHitbox(Entity* self) {
    Entity* paranthropus;
    u8 paranthropusAnimCurFrame;

    if (!self->step) {
        InitializeEntity(g_EInitParanthropusBoneHitbox);
    }

    paranthropus = self - 1;

    paranthropusAnimCurFrame = paranthropus->animCurFrame;
    if (paranthropusAnimCurFrame > 0x1D) {
        paranthropusAnimCurFrame = 0;
    }

    self->hitboxOffX = bone_hitbox_offsets[paranthropusAnimCurFrame].x;
    self->hitboxOffY = bone_hitbox_offsets[paranthropusAnimCurFrame].y;
    self->hitboxWidth =
        bone_hitbox_dimensions[paranthropusAnimCurFrame].width / 2;
    self->hitboxHeight =
        bone_hitbox_dimensions[paranthropusAnimCurFrame].height / 2;
    self->facingLeft = paranthropus->facingLeft;
    self->hitboxState = paranthropus->hitboxState;
    self->posX.i.hi = paranthropus->posX.i.hi;
    self->posY.i.hi = paranthropus->posY.i.hi;

    if (paranthropus->entityId != E_PARANTHROPUS) {
        DestroyEntity(self);
    }
}

void EntityParanthropusSkull(Entity* self) {
    u8 i;
    Entity* entity;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->attack = 0;
        self->attackElement = ELEMENT_NONE;
    }

    // Main Paranthropus entity
    entity = self - 2;
    i = entity->animCurFrame;
    if (i >= 0x21) {
        i = 0;
    }

    if (entity->facingLeft) {
        self->posX.i.hi = (self - 2)->posX.i.hi - skull_positions[i].x;
    } else {
        self->posX.i.hi = (self - 2)->posX.i.hi + skull_positions[i].x;
    }
    self->posY.i.hi = (self - 2)->posY.i.hi + skull_positions[i].y;

    // Player can stand on top of the skull as a platform
#ifdef VERSION_US
    i = 0;
#endif
    if (entity->step < DEATH) {
        i = GetPlayerCollisionWith(self, 8, 10, 4);
    }

    entity = &PLAYER;
    if (i) {
        entity->posY.val += FIX(2.0);
    }

    if ((self - 2)->entityId != E_PARANTHROPUS) {
        DestroyEntity(self);
    }
}
