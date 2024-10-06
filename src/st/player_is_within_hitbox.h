// SPDX-License-Identifier: AGPL-3.0-or-later
bool PlayerIsWithinHitbox(Entity* self) {
    s16 diffX = PLAYER.posX.i.hi - self->posX.i.hi;

    diffX = abs(diffX);
    if (self->hitboxWidth >= diffX) {
        diffX = PLAYER.posY.i.hi - self->posY.i.hi;
        diffX = abs(diffX);
        return self->hitboxHeight >= diffX;
    } else {
        return false;
    }
}
