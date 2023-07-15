#include "stage.h"

void Update(void);
void TestCollisions(void);
void CreateEntityWhenInHorizontalRange(LayoutEntity*);
void func_8018A520(s16);
void func_8018A7AC(void);
void func_8018CAB0(void);
void InitRoomEntities(s32 objLayoutId);
void func_801916C4(u16);
void func_80192F40(u8*, u8);

RoomHeader g_Rooms[];
s16** g_SpriteBanks[];
void* g_Cluts[];
RoomDef g_TileLayers[];
void* g_EntityGfxs[];
void func_80188514(void);

Overlay g_StageOverlay = {
    /* 0x00 */ Update,
    /* 0x04 */ TestCollisions,
    /* 0x08 */ func_8018A7AC,
    /* 0x0C */ InitRoomEntities,
    /* 0x10 */ g_Rooms,
    /* 0x14 */ g_SpriteBanks,
    /* 0x18 */ g_Cluts,
    /* 0x1C */ NULL,
    /* 0x20 */ g_TileLayers,
    /* 0x24 */ g_EntityGfxs,
    /* 0x28 */ func_80188514,
    /* 0x2C */ 0x00000000,
    /* 0x30 */ 0x00000000,
    /* 0x34 */ 0x00000000,
    /* 0x38 */ 0x00000000,
    /* 0x3C */ 0x00000000,
};

SpriteParts* D_80186D88[];
s16** g_SpriteBanks[] = {
    /* 0x040 */ 0x00000000,
    /* 0x044 */ D_80186D88,
    /* 0x048 */ 0x00000000,
    /* 0x04C */ 0x00000000,
    /* 0x050 */ 0x00000000,
    /* 0x054 */ 0x00000000,
    /* 0x058 */ 0x00000000,
    /* 0x05C */ 0x00000000,
    /* 0x060 */ 0x00000000,
    /* 0x064 */ 0x00000000,
    /* 0x068 */ 0x00000000,
    /* 0x06C */ 0x00000000,
    /* 0x070 */ 0x00000000,
    /* 0x074 */ 0x00000000,
    /* 0x078 */ 0x00000000,
    /* 0x07C */ 0x00000000,
    /* 0x080 */ 0x00000000,
    /* 0x084 */ 0x00000000,
    /* 0x088 */ 0x00000000,
    /* 0x08C */ 0x00000000,
    /* 0x090 */ 0x00000000,
    /* 0x094 */ 0x00000000,
    /* 0x098 */ 0x00000000,
    /* 0x09C */ 0x00000000,
};

u32 D_80181D08[];
void* D_801800A0[] = {
    /* 0x0A0 */ (void*)0x00000005,
    /* 0x0A4 */ (void*)0x00002000,
    /* 0x0A8 */ (void*)0x00000010,
    /* 0x0AC */ (void*)D_80181D08,
    /* 0x0B0 */ (void*)0xFFFFFFFF,
};
void* g_Cluts[] = {
    /* 0x0B4 */ D_801800A0,
};

// TileDefinition D_80182D68[];
// TileDefinition D_80186D78;
// u16 D_80181D68[];
// u16 D_80181F68[];
// u16 D_80182168[];
// u16 D_80182368[];
// u16 D_80182568[];
// u16 D_80182768[];
// LayerDef D_801800B8 = {0, 0, 0, 0, 0, 0};
// LayerDef D_801800C8 = {D_80181D68, &D_80186D78, 0x01328328, 0x60, 3, 0};
// LayerDef D_801800D8 = {D_80181F68, &D_80186D78, 0x01565565, 0x60, 3, 0};
// LayerDef D_801800E8 = {D_80182168, &D_80186D78, 0x0147B47B, 0x60, 3, 0};
// LayerDef D_801800F8 = {D_80182368, &D_80186D78, 0x0198F98F, 0x60, 3, 0};
// LayerDef D_80180108 = {D_80182568, &D_80186D78, 0x01B23B23, 0x60, 3, 0};
// LayerDef D_80180118 = {D_80182768, &D_80182D68, 0x40B22B22, 0x20, 3, 2};
// LayerDef D_80180128 = {D_80182768, &D_80182D68, 0x41990990, 0x1F, 3, 2};
// LayerDef D_80180138 = {D_80182768, &D_80182D68, 0x40564564, 0x1E, 3, 2};
// LayerDef D_80180148 = {D_80182768, &D_80182D68, 0x4147C47C, 0x1D, 3, 2};
// LayerDef D_80180158 = {D_80182768, &D_80182D68, 0x40327327, 0x1C, 3, 2};
// RoomDef g_TileLayers[] = {
//     /* 0x168 */ {&D_801800C8, &D_801800B8},
//     /* 0x170 */ {&D_801800D8, &D_801800B8},
//     /* 0x178 */ {&D_801800E8, &D_801800B8},
//     /* 0x180 */ {&D_801800F8, &D_801800B8},
//     /* 0x188 */ {&D_80180108, &D_801800B8},
//     /* 0x190 */ {&D_80180118, &D_801800B8},
//     /* 0x198 */ {&D_80180128, &D_801800B8},
//     /* 0x1A0 */ {&D_80180138, &D_801800B8},
//     /* 0x1A8 */ {&D_80180148, &D_801800B8},
//     /* 0x1B0 */ {&D_80180158, &D_801800B8},
// };
