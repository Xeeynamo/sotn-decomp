// SPDX-License-Identifier: AGPL-3.0-or-later
s32 CalculateDistance(Entity* entity, s32 targetX, s32 targetY) {
    s32 deltaX = targetX - entity->posX.i.hi;
    s32 deltaY = targetY - entity->posY.i.hi;

    return SquareRoot12((SQ(deltaX) + SQ(deltaY)) << 12) >> 12;
}
