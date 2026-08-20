// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef ZERO_BIN_H
#define ZERO_BIN_H
#include "sattypes.h"
#include "stage_data.h"
#include "lib/scl.h"
#include "inc_asm.h"
#include <saturn_sprite.h>

// func_06023394
void DMA_CpuMemCopy2(s32*, s32*, u32);

// func_06023484
s32 DMA_CpuResult();

// func_060234F4
void DMA_ScuInit();

// void SPR_2SetGourTbl(u16 arg0);

void InitPrimBuf();

// DAT_0605c120, DAT_060645EC, DAT_060645e4, DAT_060645f8 and SpGourTbl
// are deliberately absent: zero and its dependents access them at
// different types, and a shared declaration changes codegen.
// Each user declares its own.
extern s32 DAT_0601ac30[];
extern s32 DAT_0601ac38[];
extern s32 DAT_0601ac40[];
extern s32 DAT_0605D910[];
extern s16 DAT_0605AEA8;
extern s16 DAT_06057A10[];
extern s32 DAT_00252000;
extern s32 DAT_00258000;

struct Unk060645D0_1 {
    struct Unk060645D0_2* unk0;
};
struct Unk060645D0_2 {
    u8 pad[0x8];
    s16 unk8;
};
extern struct Unk060645D0_1* DAT_060645D0;

extern u8 SYS_buf_060485E0[];
struct Unk0605d6c0* DAT_0605d6c0[];
void func_0600871C(s32, UNK_0605c680*, s32);

struct Unk0605CD90 {
    s32 dst0;
    s32 dst4;
    u16* unk8;
    s32 unkc;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1c;
    s32 unk20;
    s16 unk24;
    u8 pad[10];
};

void BuildSubDispTilemap(struct Unk0605CD90* param_1);
s32 DAT_060086e4;
s32 DecompressLZSS(u8*, u8*, u32);
// func_060086E8
void DmaScroll(s32* src, s32* dest, u32 cnt);

struct Unk0605d6c0 {
    u32 tileFlags;
    u32 src;
    u32 dest;
    u32 cnt;
    u8 unk[0x20];
    s32 unk30;
    u32 unk34;
    u32 unk38;
    u32 unk3c;
};

struct Unk0605CD90 DAT_0605CD90[];

#define DMA_SRC_ADDR 0x002E0000

#define VDP2_DEBUG_TILEMAP_OFFSET (SCL_VDP2_VRAM + 0x58000)
#define VDP2_25F00600 SCL_VDP2_VRAM + 0x100600

extern s16 DAT_06062224[];
extern s32 DAT_06039214;
void ClearDebugPrintTilemap();

#define SH2_REG_M_FRT_IC 0x21000000

extern s32 DAT_060645d0;
extern void* g_BatResourceDescriptorList;

extern s32* DAT_060a5000;

extern SaturnStageDataTables g_StageOverlayData;

extern s32* DAT_06066000;

void func_06006FA8(void);

extern u8 g_MuteCd;
extern u8 DAT_060644dc;

extern s32 DAT_060476a4;
extern s32 DAT_060476a0;
extern s32 DAT_06064354;
extern s32 DAT_060644AC;

struct Unk0600E050 {
    u8 pad[0x4];
    s16 unk4;
    s16 pad6;
    s16 unk8;
    u8 pada[2];
    s16 unkc;
    s16 unke;
};

void func_0601B600();
extern s32 DAT_06038a44;

s32 func_06017FA4(s32 param_1, s32 param_2, s32 param_3);

void func_060082E8(void);
void func_0600841C(void);

void InitPaletteRemapLuts(void);
void func_0600B254(void);

extern s32 D_8013B61C;
extern s32 g_PlayingXaBgmId;
extern s8 DAT_060644C0;

extern u16 DAT_0605cea2;
extern u32 DAT_0605C658;
void func_06030df0();
void InitSystem();
void func_060040D8();

/* Declarations moved here by tools/saturn/move_declarations.py */
extern u16 DAT_06065470;
extern s16 DAT_0605d772;
void func_0600971C(void);
void StartColorOffsetFade(s32, s32);
void func_06005208(s32);
extern s32 DAT_0605d7f0;
extern s32 DAT_0605c6e4;
extern s32 DAT_0605c664;
extern s16 DAT_0605c110;
extern u16 DAT_0605becc;
extern u8 DAT_06057f68;
extern u8* DAT_060645b8;
void func_06009510(s32);
void SetCanRevealMap(void);
extern s32 DAT_0605d7dc;
extern s32 DAT_0605ceb0;
extern Unk0605cd70 DAT_0605cd70;
extern s32 g_PlayerX;
extern s32 DAT_0605cd54;
extern s32 DAT_0605C668;
extern s32 D_80097C98;
extern s32 g_PlayerY;
extern u32 g_RoomCount;
void func_0601960C(char*, u8*, s16*, s16*, s32);
extern u8 DAT_0604E5E0[];
extern void* memset(void* dest, int value, unsigned long size);
extern SaturnSpriteResource g_SaturnSharedSpriteBank13Resource;
extern SaturnSpriteResource g_SaturnSharedSpriteBank12Resource;
extern SaturnSpriteResource g_SaturnSharedSpriteBank4Resource;
extern SaturnSpriteResource g_SaturnSharedSpriteBank0Resource;
extern s32 g_GameClearFlag;
extern u8 g_CastleMap[];
extern u16 D_8003C730;
extern s32 D_8013AEE4;
extern u8 DAT_06057f62;
extern s32 DAT_0606459c;
extern s32 DAT_0605c108;
extern s32 D_8006C374;
void func_060195F0(void);
void func_0600FB34(void);
extern s32 g_CutsceneHasControl;
extern s32 DAT_06061dd0;
extern s32 DAT_0605c10c;
extern SaturnStageFileRecord g_StageFileRecords[];
extern s32 DAT_0605c11a;
extern u16 DAT_0605cea0;
extern SaturnSpriteResource g_EntitySpriteBank14;
extern EntityEntry g_EntityNoopEntry;
extern SaturnSpriteFrameHeader* g_SaturnSharedOpaquePuffFrames1[15];
extern SaturnSpriteFrameHeader* g_SaturnSharedOpaquePuffFrames0[14];
extern SaturnSpriteFrameHeader* g_SaturnSharedBreakableFrames[202];
extern SaturnSpriteResource g_SaturnSharedSpriteBank14Resource;
extern SaturnSpriteResource g_SaturnSharedSpriteBank11Resource;
extern SaturnSpriteResource g_SaturnSharedSpriteBank10Resource;
extern SaturnSpriteResource g_SaturnSharedSpriteBank9Resource;
extern SaturnSpriteResource g_SaturnSharedSpriteBank8Resource;
extern SaturnSpriteResource g_SaturnSharedSpriteBank7Resource;
extern SaturnSpriteResource g_SaturnSharedSpriteBank6Resource;
extern SaturnSpriteResource g_SaturnSharedSpriteBank5Resource;
extern SaturnSpriteResource g_SaturnSharedSpriteBank3Resource;
extern SaturnSpriteResource g_SaturnSharedSpriteBank2Resource;
extern SaturnSpriteResource g_SaturnSharedSpriteBank1Resource;
extern UNK_0605c680 DAT_0605c680;
extern Tilemap g_Tilemap;
extern Pad g_pads[];
extern MenuNavigation g_MenuNavigation;
extern s32 g_PlayableCharacter;
extern u8 g_CastleFlags[];
extern s32 currentMusicId;
extern s32 g_Servant;
extern s32 D_8006BB00;
extern FgLayer D_8003C708;
extern u32 g_Timer;
extern u32 g_GameTimer;
extern unkGraphicsStruct g_unkGraphicsStruct;
extern PlayerStatus g_Status;
extern Entity* g_CurrentEntity;
extern PlayerState g_Player;
extern Unk0605D750 g_CurrentRoom;
extern EntityEntry** PfnEntityUpdates[];
extern GameApi g_api;
extern GameSettings g_Settings;
extern int rand(void);
extern u16 DAT_06061DE8[2];
extern s32 DAT_06061DE0[2];
extern u16 DAT_0605DD94;
extern s8 DAT_0605DD60;
void func_0601B724();
int func_0601B75C(int param_1, int param_2, int param_3);
int func_0601B8B4(int param_1, int param_2);
s32 func_06017F5C(u8*);
void code2name(u32 code, u8* name);
extern u8 DAT_0606423a;
extern u8 DAT_06064414;
extern s32 DAT_06064250;
void StopPcm(s32 param);
extern s32 d_0605AEAC;
void func_0600C818();
void ResetLayerColorCalc();
extern u16 DAT_0605cdb8;
void DestroySpriteObject(SpriteObject*);
extern u32 g_randomNext;
extern u8 DAT_060644c4;
extern s16 DAT_060643c4;
extern s32 DAT_06064230;
s32 func_0602A778(s32, s32, s32);
extern s32 DAT_06039128[];
void func_0600C18C();
void func_0600BF08();
void func_0600BEA8();
SpriteObject* AllocSpriteObject(void);
extern s32 g_SpritePartsInUse;               /* 0x06038DB8 */
extern s32 g_SpriteObjectsInUse;             /* 0x06038DB4 */
extern s32 g_SpriteListCount;                /* 0x06038DB0 */
extern SpriteObject* g_SpriteListTail;       /* 0x06057794 */
extern SpriteObject* g_SpriteListHead;       /* 0x06057790 */
extern SpritePart* g_SpritePartFreeList;     /* 0x0605779C */
extern SpriteObject* g_SpriteObjectFreeList; /* 0x06057798 */
void SetVdp2BackgroundColor();
void SPR_2FrameEraseData(Uint16);
void SPR_SetEraseData(
    Uint16 eraseData, Uint16 leftX, Uint16 topY, Uint16 rightX, Uint16 botY);
void SPR_2CloseCommand();
void SPR_2ClrAllChar(void);
extern s32 g_FileLoadEnabled;
s32 func_0601AE5C(s32, s32);
void func_0600C298(s32);
void func_0600C0C4(s32);
void func_0601AE2C(s32);
s32 func_0602DCFC();
s32 func_06006574(struct Unk0600654C*);
extern s32 DAT_0605d7f8;
extern s32 DAT_06057f34;
void SPR_WaitDrawEnd();
void func_06012fb4();
void func_0600d8bc();
void func_06009838();
void UpdateScrollForRoom();
void TransferAllBgLayers();
void func_06008264();
void CloseSpriteList();
void func_06007d54();
void func_0600652C();
void func_06005310();
void func_06004f50();
void ReturnToGame();
void SetVblank();
void func_0600456c();
void func_060100B8(void);
extern s32 SpMstCmdPos;
void func_06024444(s32 arg0);
void func_06024474(void);
void func_06024494(s32 arg0, s32 arg1, s32 arg2);
double func_06031F88(s32 arg0);
double func_060319E8(double arg0, s32 arg1, s32 arg2);
s32 func_06032014(double arg0);
/* End moved declarations */

#endif
