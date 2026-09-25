// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno1.h"

// This file holds decorations in the 2-tall room that connects to the boss
// room and the save room. In NO1, it leads to the boss fight. These are all
// background decorations and it is not clear why they need to be entities
// since it seems like they might as well be part of the background. There are
// 9 of these decorative entities, selected by their params. The animation
// frame is params + 1; I will give the values for frame numbers here:
// Frame 1: Chair and desk
// Frame 2: Door with a ladder and 2 papers on the wall
// Frame 3: A small lantern (it is hidden by a breakable candle thing in-game)
// Frame 4: A dead body hanging from a chain, with a green cloak
// Frame 5: Next to 4, some kind of rope with gold balls on each side of it?
// Frame 6: Two bowls, made of silver and gold?
// Frame 7: Looks like destroyed metal bars leading to the boss room
// Frame 8: A bell with a pull-chain
// Frame 9: An empty bottle on its side, and a little green pyramid

// It is unclear what the purpose of the different Z priorities are - Almost
// all are the same, except for 4 and 5 which have higher values. Might be 
// interesting to see if there is any object in-game with a priority between.

extern EInit g_EInitBossNextDecor;

static u16 zPris[] = {0x68,0x68,0x68,
                      0x6C,0x6A,0x68,
                      0x68,0x68,0x68};
static u16 opacs[] = {0x80,0x80,0x60,
                      0x80,0x80,0x40,
                      0x80,0x80,0x80};

void EntityBossAnteRoomDecoration(Entity* self) {
    switch (self->step) {
    case 0: {
        InitializeEntity(g_EInitBossNextDecor);
        self->animCurFrame = self->params + 1;
        self->zPriority = zPris[self->params];
        self->drawFlags = ENTITY_OPACITY;
        self->opacity = opacs[self->params];
        break;
    }

    case 1:
        break;

    case 2:
#include "../pad2_anim_debug.h"
    }
}
