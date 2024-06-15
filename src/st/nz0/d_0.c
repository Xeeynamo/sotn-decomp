#include "nz0.h"

void Update(void);
void HitDetection(void);
void UpdateRoomPosition(void);
void InitRoomEntities(s32 objLayoutId);
extern RoomHeader g_Rooms[];
extern s16** g_SpriteBanks[];
extern void* g_Cluts[];
extern RoomDef g_TileLayers[];
extern void* g_EntityGfxs[];
void UpdateStageEntities(void);

extern u8** D_801A6E8C;
extern s32* D_801A6FCC;
extern s32* D_801A7304;
extern void*(D_801A79E4)(void);

Overlay g_StageOverlay = {
    /* 0x00 */ Update,
    /* 0x04 */ HitDetection,
    /* 0x08 */ UpdateRoomPosition,
    /* 0x0C */ InitRoomEntities,
    /* 0x10 */ g_Rooms,
    /* 0x14 */ 0x8018002C,
    /* 0x18 */ g_Cluts,
    /* 0x1C */ g_pStObjLayoutHorizontal,
    /* 0x20 */ g_TileLayers,
    /* 0x24 */ g_EntityGfxs,
    /* 0x28 */ UpdateStageEntities,
    /* 0x2C */ NULL,
    /* 0x30 */ &D_801A6E8C,
    /* 0x34 */ &D_801A6FCC,
    /* 0x38 */ &D_801A7304,
    /* 0x3C */ D_801A79E4,
};
