// SPDX-License-Identifier: AGPL-3.0-or-later
u8 GetAngleBetweenEntitiesShifted(Entity* a, Entity* b) {
    s16 diffX = b->posX.i.hi - a->posX.i.hi;
    s16 diffY = b->posY.i.hi - a->posY.i.hi;
    return Ratan2Shifted(diffX, diffY);
}
