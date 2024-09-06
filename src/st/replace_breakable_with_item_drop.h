// SPDX-License-Identifier: AGPL-3.0-or-later
void ReplaceBreakableWithItemDrop(Entity* self) {
    u16 params;

    PreventEntityFromRespawning(self);

#if STAGE != STAGE_ST0
    if (!(g_Status.relics[RELIC_CUBE_OF_ZOE] & 2)) {
        DestroyEntity(self);
        return;
    }
#endif

    params = self->params &= 0xFFF;

    if (params < 0x80) {
        self->entityId = E_PRIZE_DROP;
        self->pfnUpdate = (PfnEntityUpdate)EntityPrizeDrop;
        self->animFrameDuration = 0;
        self->animFrameIdx = 0;
    } else {
        self->entityId = E_EQUIP_ITEM_DROP;
        self->pfnUpdate = (PfnEntityUpdate)EntityEquipItemDrop;
        params -= 0x80;
    }

    self->params = params;
    self->unk6D[0] = 0x10;
    self->step = 0;
}
