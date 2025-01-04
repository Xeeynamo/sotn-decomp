// SPDX-License-Identifier: AGPL-3.0-or-later
bool PlayerIsWithinHitbox(Entity* self) {
    s16 posXAbs;
    s16 posXDiff;
    s16 posYAbs;
    s16 posYDiff;

    posXDiff = PLAYER.posX.i.hi - self->posX.i.hi;
    posXAbs = abs(posXDiff);
    if (posXAbs > self->hitboxWidth) {
        return false;
    }

    posYDiff = PLAYER.posY.i.hi - self->posY.i.hi;
    posYAbs = abs(posYDiff);
    if (posYAbs > self->hitboxHeight) {
        return false;
    }
    return true;
}
