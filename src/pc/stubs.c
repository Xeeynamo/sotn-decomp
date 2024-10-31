// SPDX-License-Identifier: AGPL-3.0-or-later
#include "pc.h"
#include "dra.h"
#include "memcard.h"

// game.h
GameApi g_api;
u32 g_GameStep;
Pad g_pads[PAD_COUNT];
Stages g_StageId;
s32 g_UseDisk;
u32 g_MenuStep;
DemoMode g_DemoMode;
s32 g_LoadOvlIdx;
s32 g_LoadFile;
s32 D_8006BB00;
u32 g_CdStep;
GameState g_GameState;
Entity g_Entities[TOTAL_ENTITY_COUNT];
unkGraphicsStruct g_unkGraphicsStruct;
s32 g_entityDestroyed[18] = {0};
Primitive g_PrimBuf[MAX_PRIM_COUNT];
FgLayer D_8003C708;
s16 D_8003C710;
s16 D_8003C712;
s32 D_8003C728;
s32 D_8003C730;
bool g_PauseAllowed;
s32 g_IsUsingCd;
Entity* g_CurrentEntity;
GpuUsage g_GpuUsage;
PlayerStatus g_Status;
u32 g_randomNext;
s32 g_PlayerX;
s32 g_PlayerY;
PlayerState g_Player;
u32 g_GameTimer;
GpuBuffer g_GpuBuffers[2];
s16 g_GpuBuffers_1_buf_draw_clip_y; // member of D_800542FC, TODO
                                    // overlap, hard to remove
GpuBuffer* g_CurrentBuffer;
u32 g_GameEngineStep;
s32 D_8003C0F8;
s32 D_800973EC;
s32 g_CutsceneHasControl;
s32 D_800973EC;
s32 D_8003C73C;
s32 g_MapCursorTimer;
s32 g_PlayableCharacter;
s32 g_backbufferX;
s32 g_backbufferY;
u32 g_Timer;
s32 D_80097904;
s32 g_ScrollDeltaX;
s32 g_ScrollDeltaY;
s32 D_80097910;
s32 g_LoadOvlIdx;
s32 D_8009791C;
s32 D_80097920;
s32 D_80097924;
s32 D_80097928;
s32 D_8006C3AC;
s32 D_800978C4;
s32 D_80097C98;
s8 D_80097B98;
s8 D_80097B99;
u16 g_Clut[0x3000];
u16 D_8006EBCC[0x1000]; // part of g_Clut?
u16 D_8006EBE0;
Point32 D_8006C384;
MenuNavigation g_MenuNavigation;
GameSettings g_Settings;
Point32 D_8006C38C;
s32 g_CurrentStream;
u16 g_ClutIds[0x400];
s32 D_8003C738;
u8 g_CastleFlags[0x300];
s32 D_8006C374;
s32 D_8006C378;
u32 D_80070BCC;
s32 g_Servant;
s32 g_ServantLoaded;
Event g_EvHwCardEnd;
Event g_EvHwCardErr;
Event g_EvHwCardTmo;
Event g_EvHwCardNew;
Event g_EvSwCardEnd;
Event g_EvSwCardErr;
Event g_EvSwCardTmo;
Event g_EvSwCardNew;
s32 g_PrevScrollX;
s32 g_PrevScrollY;
s32 D_80073080;
s32 g_IsTimeAttackUnlocked;
bool D_8003C908;
s32 D_8003C100;
s32 D_800978B4;
u32 g_RoomCount;
char D_80097902[] = "dummy";
s32 g_EquippedWeaponIds[2] = {0};
u8 g_SaveName[12];
Tilemap g_Tilemap;
BgLayer g_BgLayers[MAX_BG_LAYER_COUNT];
u8 g_CastleMap[0x800];
u8 g_saveIcon0[0x180];
u8 g_saveIcon1[0x180];
u8 g_saveIcon2[0x180];
u8 g_saveIcon3[0x180];
u8 g_saveIcon4[0x180];
u8 g_saveIcon5[0x180];
u8 g_saveIcon6[0x180];
u8 g_saveIcon7[0x180];
u8 g_saveIcon8[0x180];
u8 g_saveIcon9[0x180];
u8 g_saveIcon10[0x180];
u8 g_saveIcon11[0x180];
u8 g_saveIcon12[0x180];
u8 g_saveIcon13[0x180];
u8 g_saveIcon14[0x180];
u8 g_saveIcon15[0x180];
u16 g_saveIconPal0[0x10][0x10];
s32 D_8003C0EC[4] = {0};
Unkstruct_8006C3C4 D_8006C3C4[32] = {0};
GfxLoad g_GfxLoad[0x10] = {0};
s16 D_800705CC[0x200];
s32 D_8007F208 = 0;
PlayerDraw g_PlayerDraw[0x10];
DR_ENV D_800974AC[16];
u32 D_8003C744 = 0;
s32 D_80097448[2];
s32 D_80097450;
Pos D_80097488;

// dra.h
u16 D_800AC958[] = {
    0x0200, 0x0220, 0x0200, 0x0220, 0x0240, 0x0260, 0x0240, 0x0260,
    0x0280, 0x02A0, 0x0280, 0x02A0, 0x02C0, 0x02E0, 0x02C0, 0x02E0,
    0x0300, 0x0320, 0x0300, 0x0320, 0x0340, 0x0360, 0x0340, 0x0360,
    0x0380, 0x03A0, 0x0380, 0x03A0, 0x03C0, 0x03E0, 0x03C0, 0x03E0,
};
struct XaMusicConfig g_XaMusicConfigs[563] = {0};

// other stubs
s32 D_800974A4;
s32 g_DebugPlayer;
u8 D_8013B6A0[269488] = {0}; // VB file
u8 D_8017D350[57744] = {0};  // VB file
u8 D_8018B4E0[108048] = {0}; // VB file
u8 D_801A9C80[64496] = {0};  // VB file
u8 aPbav[0x3000] = {0};      // VH file
u8 aPbav_0[0x2000] = {0};    // VH file
u8 aPbav_1[0x2000] = {0};    // VH file
u8 aPbav_2[0x2000] = {0};    // VH file
u8 aPqes[] = {0};            // SEQ file
u8 aPqes_0[] = {0};          // SEQ file
u8 aPqes_1[] = {0};          // SEQ file
s32 D_800987B4;
u8 g_GfxEquipIcon[320][16 * 16 / 2];
s16 g_PalEquipIcon[320 * 16];
u16 D_8006ED0C[0x10] = {0};
u16 D_8006ED2C[0x10] = {0};
u16 D_8006ED4C[0x10] = {0};

u8 g_Pix[4][128 * 128 / 2];
ImgSrc g_imgUnk8013C200_impl = {
    0,
    0,
    0,
};
ImgSrc* g_imgUnk8013C200 = &g_imgUnk8013C200_impl;
ImgSrc* g_imgUnk8013C270 = &g_imgUnk8013C200_impl;
PlayerOvl g_PlOvl = {0};
u8** g_PlOvlAluBatSpritesheet[1] = {0};
Unkstruct_800BF554 g_SfxData[737];

// sound stubs

void SpuGetAllKeysStatus(char* status) { NOT_IMPLEMENTED; }

void func_801073C0(void) { NOT_IMPLEMENTED; }

void UpdateCd(void) { NOT_IMPLEMENTED; }

int CdInit(void) {
    NOT_IMPLEMENTED;
    return 0;
}

void func_801083BC(void) { NOT_IMPLEMENTED; }

u16 g_FontCharData[0x60] = {1, 1, 1, 0, 0, 0};
u16* func_80106A28(u32 arg0, u16 kind) {
    NOT_IMPLEMENTED;
    return g_FontCharData;
}
