#include <stage.h>

extern u_long* g_SpriteBanks[];
extern void* g_Cluts[];
extern void* g_EntityGfxs[];
extern MyRoomDef rooms[];
extern unsigned char g_Rooms[];

void Update();
void HitDetection();
void UpdateRoomPosition();
void InitRoomEntities();
void UpdateStageEntities();

u_long* NZ0_Header[] = {
    Update,
    HitDetection,
    UpdateRoomPosition,
    InitRoomEntities,
    g_Rooms,
    g_SpriteBanks,
    g_Cluts,
    g_pStObjLayoutHorizontal,
    rooms,
    g_EntityGfxs,
    UpdateStageEntities,
};

extern u_long* D_801A6E8C;
extern u_long* D_801A6FCC;
extern u_long* D_801A7304;
extern u_long* D_801A79E4;
extern u_long* D_801A9448;
extern u_long* D_801AA340;
extern u_long* D_801AA87C;
extern u_long* D_801AB778;
extern u_long* D_801ABC48;
extern u_long* D_801AC474;
extern u_long* D_801ACC30;
extern u_long* D_801ACDF4;
extern u_long* D_801ACF58;
extern u_long* D_801AE910;
extern u_long* D_801AFB90;
static u_long* g_SpriteBanks[] = {
    0x00000000,  &D_801A6E8C, &D_801A6FCC, &D_801A7304, &D_801A79E4,
    &D_801A9448, &D_801AA340, &D_801AA87C, &D_801AB778, &D_801ABC48,
    &D_801AC474, &D_801ACC30, &D_801ACDF4, &D_801ACF58, &D_801AE910,
    &D_801AFB90, 0x00000000,  0x00000000,  0x00000000,  0x00000000,
    0x00000000,  0x00000000,  0x00000000,  0x00000000,
};

extern u_long* D_80195C3C;
extern u_long* D_80195CDC;
extern u_long* D_80195D3C;
extern u_long* D_80195DBC;
extern u_long* D_80195E1C;
extern u_long* D_80195E3C;
extern u_long* D_80195E9C;
extern u_long* D_80195F1C;
extern u_long* D_80195F9C;
extern u_long* D_8019601C;
extern u_long* D_801962DC;
extern u_long* D_8019641C;
extern u_long* D_8019647C;
extern u_long* D_8019657C;
extern u_long* D_8019663C;
extern u_long* D_8019665C;
extern u_long* D_8019685C;
static u_long* D_8018008C[] = {
    0x00000005,  0x00002000, 0x00000040, &D_80195C3C, 0x00002040, 0x00000010,
    &D_80195CDC, 0x00002050, 0x00000040, &D_80195D3C, 0x00002090, 0x00000030,
    &D_80195DBC, 0x000020C0, 0x00000010, &D_80195E1C, 0x000020D0, 0x00000030,
    &D_80195E3C, 0x00002110, 0x00000040, &D_80195F1C, 0x00002150, 0x00000040,
    &D_80195F9C, 0x00002190, 0x00000040, &D_80195E9C, 0x000021D0, 0x000000A0,
    &D_801962DC, 0x00002270, 0x00000030, &D_8019641C, 0x000022A0, 0x00000080,
    &D_8019647C, 0x00002320, 0x00000050, &D_8019657C, 0x00002370, 0x00000010,
    &D_8019663C, 0x00002380, 0x00000080, &D_8019665C, 0x00002400, 0x00000080,
    &D_8019685C, 0x00002E00, 0x00000100, &D_8019601C, 0xFFFFFFFF,
};

static void* g_Cluts[] = {
    &D_8018008C,
};

#include "layers.h"