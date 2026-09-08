// SPDX-License-Identifier: AGPL-3.0-or-later
void UpdateEntitySprite(Entity* self) {
    s16** parts;
    s16* frame;
    SpriteObject* sprite;
    s32 count;
    s32 posX;
    s32 posY;

    parts = (s16**)self->ext.spriteEntity.frames;
    sprite = self->unk0;
    if (parts != NULL && sprite != NULL) {
        frame = parts[self->animCurFrame];
        sprite->flags = (sprite->flags & ~0x3F08) | (frame[0] & 0x3F08);
        sprite->slotAndStreamId =
            (sprite->slotAndStreamId & ~0x7F) | (frame[1] & 0x7F);
        func_0600B0B8(
            sprite->parts, &frame[2], (sprite->flags & 0x3F00) >> 0x8);
        if (self != &PLAYER) {
            posX = self->posX.val;
            posY = self->posY.val;
            sprite->posX = posX;
            sprite->posY = posY;
        }
        if (self->facingLeft != 0) {
            sprite->flags |= 0x10;
        } else {
            sprite->flags &= ~0x10;
        }
        count = 0;
        if (self->drawFlags & ENTITY_ROTATE) {
            sprite->rotate = self->rotate & 0x0FFF;
            count = 1;
        }
        if (self->drawFlags & ENTITY_SCALEX) {
            sprite->scaleX = self->scaleX >> 2;
            count++;
        }
        if (self->drawFlags & ENTITY_SCALEY) {
            sprite->scaleY = self->scaleY >> 2;
            count++;
        }
        if (count != 0) {
            sprite->flags |= 0x40;
        } else {
            sprite->flags &= ~0x40;
        }
    }
}
