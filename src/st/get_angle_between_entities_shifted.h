// SPDX-License-Identifier: AGPL-3.0-only
u8 GetAngleBetweenEntitiesShifted(Entity* a, Entity* b) {
    s32 diffX = (u16)b->posX.i.hi - (u16)a->posX.i.hi;
    s32 diffY = (u16)b->posY.i.hi - (u16)a->posY.i.hi;
    return Ratan2Shifted(diffX, diffY);
}
