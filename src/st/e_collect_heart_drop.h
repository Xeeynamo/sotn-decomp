// SPDX-License-Identifier: AGPL-3.0-or-later

// defined in d_prize_drops.c
extern u16 OVL_EXPORT(PrizeDrops)[];

// params: Local index of this drop
void EntityHeartDrop(Entity* self) {
    u16 index;
    u8 value;
    PfnEntityUpdate update;

    if (!self->step) {
        index = self->ext.heartDrop.unkB4 =
            self->params + HEART_DROP_CASTLE_FLAG;
        value = g_CastleFlags[(index >> 3) + CASTLE_COLLECTIBLES_100] >>
                (index & 7);
        if (value & 1) {
            DestroyEntity(self);
            return;
        }

        index -= HEART_DROP_CASTLE_FLAG;
        index = OVL_EXPORT(PrizeDrops)[index];
        if (index < 128) {
            self->unkB8 = (Entity*)EntityPrizeDrop;
        } else {
            self->unkB8 = (Entity*)EntityEquipItemDrop;
            index -= 128;
        }
        self->params = index + 0x8000;
    } else {
        index = self->ext.heartDrop.unkB4;
        if (self->step < 5) {
            if (self->hitFlags) {
                g_CastleFlags[(index >> 3) + CASTLE_COLLECTIBLES_100] |=
                    1 << (index & 7);
                self->step = 5;
            }
        }
    }
    update = (PfnEntityUpdate)self->unkB8;
    update(self);
}
