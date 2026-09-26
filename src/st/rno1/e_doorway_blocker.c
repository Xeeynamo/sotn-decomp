// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno1.h"

static u16 wallTiles[] = {
    0x002B, 0x002C, 0x0023, 0x01BC, 0x0001, 0x0002, 0x0023, 0x001C,
    0x0003, 0x0004, 0x0023, 0x0024, 0x0029, 0x002A, 0x0023, 0x001C,
    0x002B, 0x002C, 0x0023, 0x0024, 0x0001, 0x0002, 0x0023, 0x00A2};
static u16 unusedWallTiles[] = {
    0x002B, 0x002C, 0x00FA, 0x01BC, 0x01D8, 0x01D9, 0x01DA, 0x01DB,
    0x01DC, 0x01DD, 0x01DE, 0x01DF, 0x01E7, 0x01E8, 0x01E9, 0x01EA,
    0x01EB, 0x01EC, 0x01ED, 0x01EE, 0x0001, 0x0002, 0x009E, 0x00A2};
extern EInit g_EinitDoorwayBlocker;

// Strange discovery! This function places wall block tiles over a path to
// another room which does not exist! On the map, we can see two rooms: The
// "exit" from the boss room, and the CD room leading to the Library. There
// is an empty space in between the two of these. The map tile data for the
// largest, tallest room in Outer Wall contains an open doorway leading into
// this room. But since there is no such room there, this entity blocks that
// doorway and makes it a solid, nondescript wall. This likely relates to some
// kind of cut content. As far as I know, there is no other data in the RNO1
// overlay corresponding to this "lost room".

void EntityDoorwayBlocker(Entity* self) {
    u8 srcIdx;
    s32 dstBase;
    s32 i, j;

    switch (self->step) {
    case 0: // only one case so this is a static entity
        InitializeEntity(g_EinitDoorwayBlocker);
        self->animCurFrame = 0;
        dstBase = 0x50F;
        srcIdx = 0;
        for (i = 0; i < 6; i++) {
            for (j = 0; j < 4; j++) {
                g_Tilemap.fg[dstBase - j] = wallTiles[srcIdx];
                srcIdx++;
            }
            dstBase -= 0x30;
        }
        self->step = 3;
    }
}
