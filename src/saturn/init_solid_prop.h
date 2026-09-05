// SPDX-License-Identifier: AGPL-3.0-or-later
void InitSolidProp(Entity* self) {
    s32 spriteFlags;
    s16 params;
    s32 flags;
    s32 frameType;
    s32 spriteSize;
    SpriteObject* sprite;
    SaturnSpriteFrameHeader** frame;
    s32 offset;
    s32 i;
    s32 count;

    if (self->step == 0) {
        params = self->params;
        flags = 3;
        spriteFlags = -0x100 & params;
        flags &= params;
        frameType = 2 & flags;
        spriteSize = 6;
        if (frameType != 0) {
            spriteSize = 18;
        }

        sprite = CreateSpriteObject(
            g_EntitySpriteBank08.allocationIndex, g_EntitySpriteBank08.flags,
            g_EntitySpriteBank08.images, spriteSize);
        self->unk0 = sprite;
        TekiInit(self, 3);

        frame = DAT_06046CD0;
        self->step++;
        if (frameType != 0) {
            frame += 2;
        } else {
            frame += 1;
        }
        func_0600AFA8(sprite, *frame);

        if (spriteFlags != 0) {
            sprite->flags |= 0x30;
        }
        sprite->flags = (sprite->flags & ~7) | 3;
        sprite->posX = self->posX.val;
        offset = 0xB0;
        sprite->posY = self->posY.val;
        if (1 & flags) {
            offset = 0xBD;
        }
        if (flags & 2) {
            count = 6;
        } else {
            count = 2;
        }

        for (i = 0; i < count; i++) {
            DAT_0608FFF8[offset] = 3;
            DAT_0608FFF8[offset + 1] = 3;
            DAT_0608FFF8[offset + 2] = 3;
            offset -= 0x10;
        }
    }
}
