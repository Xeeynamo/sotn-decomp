// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef STAGE_LOADER_H
#define STAGE_LOADER_H

#include "../pc.h"
#include <stage.h>

#define LOAD_ASSET(path, dst) FileReadToBuf(path, dst, 0, sizeof(dst))
#define LOAD_ASSET_GFX(bpath, dst) LOAD_ASSET(bpath "/" #dst ".gfxbin", dst)
#define LOAD_ASSET_PAL(bpath, dst) LOAD_ASSET(bpath "/" #dst ".palbin", dst)

extern u8 stage_placeholder[1444];
extern u8 stage_title_jp[836];

// load a rooms.layers.json file and all its dependencies to the returned
// pre-allocated RoomDef array. Returns NULL in case of a failure.
RoomDef* LoadRoomsLayers(const char* filePath);

// load a g_Rooms.roomdef.json file into the pre-allocated returning pointer.
// Returns NULL in case of a failure.
RoomHeader* LoadRoomDefs(const char* filePath);

// load a *.layoutobj.json file into the returning pre-allocated array.
// Returns NULL in case of a failure.
LayoutEntity* LoadObjLayout(const char* filePath);

// load an *.animset.json file into the returning pre-allocated array.
// Returns NULL in case of a failure.
SpritePart* LoadSpriteParts(const char* filePath);

// reset all the pre-allocated arrays, useful when loading a new stage
void LoadReset();

#endif
