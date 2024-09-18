#ifndef CASTLE_FLAG_BANK
#define CASTLE_FLAG_BANK 0
#endif

extern u16 D_80180608[];

void EntityHeartDrop(Entity* self) {
    u16 index;
    u8 value;
    PfnEntityUpdate update;

    if (!self->step) {
        index = self->ext.heartDrop.unkB4 =
            self->params + 0x118 + CASTLE_FLAG_BANK;
        value = g_CastleFlags[(index >> 3) + HEART_FLAGS_START] >> (index & 7);
        if (value & 1) {
            DestroyEntity(self);
            return;
        }

        index -= 0x118 + CASTLE_FLAG_BANK;
        index = D_80180608[index];
        if (index < 128) {
            self->ext.heartDrop.update = EntityPrizeDrop;
        } else {
            self->ext.heartDrop.update = EntityEquipItemDrop;
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
    update = self->ext.heartDrop.update;
    update(self);
}