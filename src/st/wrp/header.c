#include "wrp.h"

void Update(void);
void HitDetection(void);
void CreateEntityWhenInHorizontalRange(LayoutEntity*);
void func_8018A520(s16);
void UpdateRoomPosition(void);
void func_8018CAB0(void);
void InitRoomEntities(s32 objLayoutId);
void PlaySfxPositional(u16);
void BottomCornerText(u8*, u8);

extern MyRoomDef rooms_layers[];

extern RoomHeader OVL_EXPORT(rooms)[];
static signed short* spriteBanks[];
extern void* g_Cluts[];
extern RoomDef g_TileLayers[];
extern void* OVL_EXPORT(g_EntityGfxs)[];
void UpdateStageEntities(void);

static Overlay OVL_EXPORT(Overlay) = {
    .Update = Update,
    .HitDetection = HitDetection,
    .UpdateRoomPosition = UpdateRoomPosition,
    .InitRoomEntities = InitRoomEntities,
    .rooms = OVL_EXPORT(rooms),
    .spriteBanks = spriteBanks,
    .cluts = g_Cluts,
    .objLayoutHorizontal = NULL,
    .tileLayers = rooms_layers,
    .gfxBanks = OVL_EXPORT(g_EntityGfxs),
    .UpdateStageEntities = UpdateStageEntities,
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
