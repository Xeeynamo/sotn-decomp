// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

extern struct SpriteParts g_WarpRoomSpriteParts;
extern struct SpriteParts g_WarpSmallRocksSpriteParts;

struct SpriteParts* g_WarpSpriteBank16[] = {
    &g_WarpRoomSpriteParts,
    &g_WarpSmallRocksSpriteParts,
    (struct SpriteParts*)-1,
};
