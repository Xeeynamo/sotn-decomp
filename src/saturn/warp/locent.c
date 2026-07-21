// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

void func_060DC040(Entity* self);
void func_060DCAFC(Entity* self);

extern struct SpriteParts* g_WarpSpriteBank16[];

EntityEntry g_WarpRoomEntry = {
    g_WarpSpriteBank16,
    func_060DC040,
};

EntityEntry g_WarpSmallRocksEntry = {
    g_WarpSpriteBank16,
    func_060DCAFC,
};
