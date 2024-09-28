// SPDX-License-Identifier: AGPL-3.0-or-later
s16 CalculateAngleToEntity(Entity* entity, s16 targetX, s16 targetY) {
    s16 angle;
    s16 deltaY;
    s16 deltaX;

    deltaX = targetX - entity->posX.i.hi;
    deltaY = targetY - entity->posY.i.hi;
    angle = ratan2(-deltaY, deltaX) & 0xFFF;
    return angle;
}
