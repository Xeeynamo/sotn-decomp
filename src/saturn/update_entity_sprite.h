// SPDX-License-Identifier: AGPL-3.0-or-later
void UpdateEntitySprite(Entity* arg0) {
    s16** parts;
    s16* frame;
    s16* framePtr;
    SpriteObject* sprite;
    s32 count;
    s32 posX;
    s32 posY;

    parts = (s16**)arg0->ext.spriteEntity.frames;
    sprite = arg0->unk0;
    if (parts != NULL && sprite != NULL) {
        frame = parts[arg0->animCurFrame];
        framePtr = frame;
        sprite->flags =
            (sprite->flags & ~0x3F08) | (*(volatile s16*)framePtr++ & 0x3F08);
        sprite->slotAndStreamId = (sprite->slotAndStreamId & ~0x7F) |
                                  (*(volatile s16*)framePtr & 0x7F);
        func_0600B0B8(
            sprite->parts, frame + 2,
            ((u32) * (volatile u16*)&sprite->flags >> 8) & 0x3F, framePtr);
        if (arg0 != g_Entities) {
            posX = arg0->posX.val;
            posY = arg0->posY.val;
            sprite->posX = posX;
            sprite->posY = posY;
        }
        if (arg0->facingLeft != 0) {
            sprite->flags |= 0x10;
        } else {
            sprite->flags &= ~0x10;
        }
        count = 0;
        if (arg0->drawFlags & 4) {
            sprite->rotate = arg0->rotate & 0x0FFF;
            count = 1;
        }
        if (arg0->drawFlags & 1) {
            sprite->scaleX = arg0->scaleX >> 2;
            count += 1;
        }
        if (arg0->drawFlags & 2) {
            sprite->scaleY = arg0->scaleY >> 2;
            count += 1;
        }
        if (count != 0) {
            sprite->flags |= 0x40;
        } else {
            sprite->flags &= ~0x40;
        }
    }
}
