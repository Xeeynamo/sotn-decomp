// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz1.h"

extern EInit g_EInitInteractable;

// This is the entity that transitions the player out of the large secret area
// behind the breakable wall and the left side of the room with the pendulums
void EntityRoomExit(Entity* self) {
    Entity* player;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->hitboxWidth = 16;
        self->hitboxHeight = 32;
        self->hitboxState = 1;
        // fallthrough

    case 1:
        if (g_PlayerX < 256 && GetDistanceToPlayerX() < self->hitboxWidth &&
            GetDistanceToPlayerY() < self->hitboxHeight) {
            g_Tilemap.x = 256;
            g_Tilemap.left++;
            g_PlayerX -= 256;
            self->step = 16;
        }
        break;
    case 2:
        if (!self->hitFlags) {
            self->step--;
        }
        player = &PLAYER;
        if (player->posX.i.hi < self->posX.i.hi) {
            g_Tilemap.x = 256;
            g_PlayerX = DISP_ALL_H;
            g_Tilemap.left++;
            PLAYER.posX.i.hi = 112;
            PLAYER.zPriority = 0x5F;
        }
        break;
    }
}
