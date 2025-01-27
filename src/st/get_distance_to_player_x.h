// SPDX-License-Identifier: AGPL-3.0-or-later
// Absolute distance from g_CurrentEntity to the player in the X Axis
s16 GetDistanceToPlayerX(void) {
    Entity* player = &PLAYER;
    s16 xDistance = g_CurrentEntity->posX.i.hi - player->posX.i.hi;

    if (xDistance < 0) {
        xDistance = -xDistance;
    }
    return xDistance;
}
