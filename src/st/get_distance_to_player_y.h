// SPDX-License-Identifier: AGPL-3.0-or-later
// Absolute distance from g_CurrentEntity to the player in the Y Axis
s32 GetDistanceToPlayerY(void) {
    Entity* player = &PLAYER;
    s32 yDistance = g_CurrentEntity->posY.i.hi - player->posY.i.hi;

    if (yDistance < 0) {
        yDistance = -yDistance;
    }
    return yDistance;
}
