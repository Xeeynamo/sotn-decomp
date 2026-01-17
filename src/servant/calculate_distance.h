// SPDX-License-Identifier: AGPL-3.0-or-later
s32 CalculateDistance(Entity* entity, s32 targetX, s32 targetY) {
    s32 dx = targetX - entity->posX.i.hi;
    s32 dy = targetY - entity->posY.i.hi;
    s32 distance = SquareRoot12((dx * dx + dy * dy) << 12) >> 12;
    return distance;
}
