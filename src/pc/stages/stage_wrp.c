#include <game.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stage_loader.h"
#include "sfx.h"

void Update(void);
void HitDetection(void);
void UpdateRoomPosition(void);
void UpdateStageEntities(void);
static void MyInitRoomEntities(s32 objLayoutId);

// TODO populate from assets/st/wrp/D_80186D88.animset.json
static SpriteParts* D_80186D88[] = {NULL, NULL, NULL, NULL};
static u_long* sprite_banks[] = {
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

static u16 D_80181D08[16];
static void* D_801800A0[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK(0x2000, D_80181D08),
    PAL_TERMINATE(),
};

static void* clut_anims[] = {
    /* 0x0B4 */ D_801800A0,
};

extern void* WRP_g_EntityGfxs[];

// BSS SECTION START
s32 D_80193AA0 = 0;
s32 D_80193AA4 = 0;
s32 D_80193AA8 = 0;
s32 D_80193AAC = 0;
u16* g_LayoutObjHorizontal = NULL;
u16* g_LayoutObjVertical = NULL;
u8 g_LayoutObjPosHorizontal = 0;
u8 g_LayoutObjPosVertical = 0;
u16 g_ItemIconSlots[32] = {0};
// BSS SECTION END

static Overlay g_StageDesc = {
    Update,
    HitDetection,
    UpdateRoomPosition,
    MyInitRoomEntities,
    NULL, // set in InitStageWrp
    sprite_banks,
    clut_anims,
    NULL,
    NULL, // set in InitStageWrp
    WRP_g_EntityGfxs,
    UpdateStageEntities,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

static LayoutEntity* g_Stub_80181228;
static LayoutEntity* g_Stub_80181250;
static LayoutEntity* g_Stub_801812A0;
static LayoutEntity* g_Stub_801812C8;
static LayoutEntity* g_Stub_80181278;
static LayoutEntity* g_Stub_801812F0;
static LayoutEntity* g_Stub_80181304;

static LayoutEntity* g_Stub_80181324;
static LayoutEntity* g_Stub_8018134C;
static LayoutEntity* g_Stub_80181374;
static LayoutEntity* g_Stub_8018139C;
static LayoutEntity* g_Stub_801813C4;
static LayoutEntity* g_Stub_801813EC;
static LayoutEntity* g_Stub_80181400;

void InitStageWrp(Overlay* o) {
    LoadReset();

    FILE* f = fopen("assets/st/wrp/D_80181D08.dec", "rb");
    if (f) {
        fseek(f, 0, SEEK_END);
        size_t len = ftell(f);
        fseek(f, 0, SEEK_SET);
        fread(D_80181D08, MIN(len, sizeof(D_80181D08)), 1, f);
        fclose(f);
    }

    g_Stub_80181228 = LoadObjLayout("assets/st/wrp/D_80181228.layoutobj.json");
    g_Stub_80181250 = LoadObjLayout("assets/st/wrp/D_80181250.layoutobj.json");
    g_Stub_801812A0 = LoadObjLayout("assets/st/wrp/D_801812A0.layoutobj.json");
    g_Stub_801812C8 = LoadObjLayout("assets/st/wrp/D_801812C8.layoutobj.json");
    g_Stub_80181278 = LoadObjLayout("assets/st/wrp/D_80181278.layoutobj.json");
    g_Stub_801812F0 = LoadObjLayout("assets/st/wrp/D_801812F0.layoutobj.json");
    g_Stub_80181304 = LoadObjLayout("assets/st/wrp/D_80181304.layoutobj.json");

    g_Stub_80181324 = LoadObjLayout("assets/st/wrp/D_80181324.layoutobj.json");
    g_Stub_8018134C = LoadObjLayout("assets/st/wrp/D_8018134C.layoutobj.json");
    g_Stub_80181374 = LoadObjLayout("assets/st/wrp/D_80181374.layoutobj.json");
    g_Stub_8018139C = LoadObjLayout("assets/st/wrp/D_8018139C.layoutobj.json");
    g_Stub_801813C4 = LoadObjLayout("assets/st/wrp/D_801813C4.layoutobj.json");
    g_Stub_801813EC = LoadObjLayout("assets/st/wrp/D_801813EC.layoutobj.json");
    g_Stub_80181400 = LoadObjLayout("assets/st/wrp/D_80181400.layoutobj.json");

    int layoutId = 0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_80181228;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_80181250;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812A0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812C8;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_80181278;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_801812F0;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_80181304;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_80181304;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_80181304;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_80181304;
    g_pStObjLayoutHorizontal[layoutId++] = g_Stub_80181304;

    layoutId = 0;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_80181324;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_8018134C;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_8018139C;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813C4;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_80181374;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_801813EC;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_80181400;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_80181400;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_80181400;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_80181400;
    g_pStObjLayoutVertical[layoutId++] = g_Stub_80181400;

    sprite_banks[1] = LoadSpriteParts("assets/st/wrp/D_80186D88.animset.json");

    g_StageDesc.tileLayers = LoadRoomsLayers("assets/st/wrp/rooms.layers.json");
    g_StageDesc.rooms = LoadRoomDefs("assets/st/wrp/g_Rooms.roomdef.json");
    memcpy(o, &g_StageDesc, sizeof(Overlay));
}

void SetGameState(GameState gameState);
void PlaySfx(s32 sfxId);
void InitRoomEntities(s32 objLayoutId);

static void MyInitRoomEntities(s32 objLayoutId) {
    INFOF("Stage: %02X, objLayoutId: %i", g_StageId, objLayoutId);
    InitRoomEntities(objLayoutId);
}
