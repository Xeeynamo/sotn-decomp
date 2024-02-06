#ifndef STAGE_LOADER_H
#define STAGE_LOADER_H

#include "../pc.h"

// load a rooms.layers.json file and all its dependencies to the returned
// pre-allocated RoomDef array. Returns NULL in case of a failure.
RoomDef* LoadRooms(const char* filePath);

#endif
