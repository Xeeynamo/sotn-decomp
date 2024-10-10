// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../wrp/wrp.h"

void HitDetection(void);

extern RoomHeader g_Rooms[];
extern SpriteParts* g_SpriteBanks;
extern u_long* g_Cluts;
extern MyRoomDef OVL_EXPORT(rooms_layers)[];
extern GfxBank* g_EntityGfxs;
void UpdateStageEntities(void);

Overlay g_StageOverlay = {
    /* 0x00 */ Update,
    /* 0x04 */ HitDetection,
    /* 0x08 */ UpdateRoomPosition,
    /* 0x0C */ InitRoomEntities,
    /* 0x10 */ g_Rooms,
    /* 0x14 */ &g_SpriteBanks,
    /* 0x18 */ &g_Cluts,
    /* 0x1C */ NULL,
    /* 0x20 */ (RoomDef*)OVL_EXPORT(rooms_layers),
    /* 0x24 */ &g_EntityGfxs,
    /* 0x28 */ UpdateStageEntities,
    /* 0x2C */ 0x00000000,
    /* 0x30 */ 0x00000000,
    /* 0x34 */ 0x00000000,
    /* 0x38 */ 0x00000000,
    /* 0x3C */ 0x00000000,
};
