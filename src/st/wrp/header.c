#include "wrp.h"

void Update(void);
void HitDetection(void);
void CreateEntityWhenInHorizontalRange(LayoutEntity*);
void func_8018A520(s16);
void UpdateRoomPosition(void);
void func_8018CAB0(void);
void InitRoomEntities(s32 objLayoutId);
void func_801916C4(u16);
void BottomCornerText(u8*, u8);

extern MyRoomDef rooms[];

extern RoomHeader g_Rooms[];
extern signed short* spriteBanks[];
extern void* g_Cluts[];
extern RoomDef g_TileLayers[];
extern void* OVL_EXPORT(g_EntityGfxs)[];
void UpdateStageEntities(void);

Overlay g_StageOverlay = {
    /* 0x00 */ Update,
    /* 0x04 */ HitDetection,
    /* 0x08 */ UpdateRoomPosition,
    /* 0x0C */ InitRoomEntities,
    /* 0x10 */ g_Rooms,
    /* 0x14 */ spriteBanks,
    /* 0x18 */ g_Cluts,
    /* 0x1C */ NULL,
    /* 0x20 */ rooms,
    /* 0x24 */ OVL_EXPORT(g_EntityGfxs),
    /* 0x28 */ UpdateStageEntities,
    /* 0x2C */ 0x00000000,
    /* 0x30 */ 0x00000000,
    /* 0x34 */ 0x00000000,
    /* 0x38 */ 0x00000000,
    /* 0x3C */ 0x00000000,
};

#include "sprite_banks.h"

extern u16 D_80181D08[16];
void* D_801800A0[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x2000, D_80181D08),
    PAL_TERMINATE(),
};
void* g_Cluts[] = {
    /* 0x0B4 */ D_801800A0,
};

#include "layers.h"
