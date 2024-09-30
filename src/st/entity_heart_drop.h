// SPDX-License-Identifier: AGPL-3.0-or-later
extern u16 g_HeartDropArray[];

#if defined(VERSION_BETA)
static u16 g_HeartDropArray[] = {
    0x000C, 0x0017, 0x00D8, 0x012F, 0x000C, 0x0085, 0x0017, 0x00E5,
    0x014A, 0x00EE, 0x013A, 0x0017, 0x000C, 0x00C9, 0x008B, 0x00C8,
    0x0098, 0x0099, 0x0142, 0x0161, 0x008F, 0x011A, 0x011F, 0x0099,
    0x00C9, 0x00F2, 0x0133, 0x0103, 0x0150, 0x013E, 0x000C, 0x0017,
    0x0103, 0x00D6, 0x00E6, 0x0017, 0x0017, 0x0089, 0x0139, 0x0000};
#endif

void EntityHeartDrop(Entity* self) {
    u16 index;
    u8 value;
    PfnEntityUpdate update;

    if (!self->step) {
        index = self->ext.heartDrop.unkB4 =
            self->params + HEART_DROP_CASTLE_FLAG;
        value = g_CastleFlags[(index >> 3) + HEART_FLAGS_START] >> (index & 7);
        if (value & 1) {
            DestroyEntity(self);
            return;
        }

        index -= HEART_DROP_CASTLE_FLAG;
        index = g_HeartDropArray[index];
        if (index < 128) {
            self->unkB8 = EntityPrizeDrop;
        } else {
            self->unkB8 = EntityEquipItemDrop;
            index -= 128;
        }
        self->params = index + 0x8000;
    } else {
        index = self->ext.heartDrop.unkB4;
        if (self->step < 5) {
            if (self->hitFlags) {
                g_CastleFlags[(index >> 3) + HEART_FLAGS_START] |=
                    1 << (index & 7);
                self->step = 5;
            }
        }
    }
    update = self->unkB8;
    update(self);
}
