// SPDX-License-Identifier: AGPL-3.0-only
/**
 * Returns the player's side position relative to g_CurrentEntity
 * 0 = Player is on the right side
 * 1 = Player is on the left side
 * 2 = Player is above
 */
u8 GetSideToPlayer() {
    u8 side = 0;
    Entity* player = &PLAYER;

    if (g_CurrentEntity->posX.i.hi > player->posX.i.hi) {
        side |= 1;
    }

    if (g_CurrentEntity->posY.i.hi > player->posY.i.hi) {
        side |= 2;
    }
    return side;
}
