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
void func_06004D84(void);
void func_06004DE8(void);
void func_06004E50(void);
void func_06004E94(void);
void INT_SetScuFunc(u32 vector, void (*handler)(void));
extern void (*DAT_06000344)(u32 clearMask, u32 setMask);
extern s32 DAT_06064320;

// DAT_0605c120, DAT_060645EC, DAT_060645e4, DAT_060645f8 and SpGourTbl
// are deliberately absent: zero and its dependents access them at
// different types, and a shared declaration changes codegen.
// Each user declares its own.
extern s32 DAT_0601ac30[];
extern s32 DAT_0601ac38[];
extern s32 DAT_0601ac40[];
extern s32 DAT_0605D910[];
extern s16 DAT_0605AEA8;
struct ShakeState {
    s16 id;
    s16 index;
    s16* offsets;
    s16 offset;
};
extern struct ShakeState DAT_06057A10;
extern s32 DAT_00252000;
extern s32 DAT_00258000;
extern u16 DAT_06065470;

extern SaturnSpriteResource** DAT_060645D0;

extern u8 SYS_buf_060485E0[];
extern Unk0605DB60 d_0605DB60[32];
extern struct BgTransfer DAT_0605d6c0[8];
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

struct BgTransfer {
    u32 tileFlags;
    u32 src;
    u32 dest;
    u32 cnt;
};

struct Unk0605CD90 DAT_0605CD90[];

#define DMA_SRC_ADDR 0x002E0000

#define VDP2_DEBUG_TILEMAP_OFFSET (SCL_VDP2_VRAM + 0x58000)
#define VDP2_25F00600 SCL_VDP2_VRAM + 0x100600

extern s16 DAT_06062224[];
extern s32 DAT_06039214;
void ClearDebugPrintTilemap();

#define SH2_REG_M_FRT_IC 0x21000000

#define BCD_TO_DEC(x) ((((u8)(x) >> 4) * 10) + ((x) & 0x0F))

#define SMPC_SF (*(volatile s8*)0x20100063)
#define SMPC_COMREG (*(volatile s8*)0x2010001F)
#define SMPC_SNDON 0x19
#define SMPC_SNDOFF 0x1A

#define SMPC_ISSUE(cmd)                                                        \
    do {                                                                       \
        do {                                                                   \
        } while (SMPC_SF & 1);                                                 \
        SMPC_SF = 1;                                                           \
        SMPC_COMREG = (cmd);                                                   \
        if (SMPC_SF & 1) {                                                     \
            do {                                                               \
            } while (SMPC_SF & 1);                                             \
        }                                                                      \
    } while (0)

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
void InitBackupRam(void);
s32 func_06030690(s8 arg0, s32 arg1, void* arg2);
s32 func_0600D028(s32 arg0, s8 arg1);
s8 func_0600D264(s8 arg0, s8 arg1);
s8 func_0600D47C(s32 arg0, s8 arg1);
extern s8 DAT_0605DD61;
extern s16 DAT_0605DD90;
void InitSystem();
void func_060040D8();

/* Declarations moved here by tools/saturn/move_declarations.py */
extern s16 DAT_0605d772;
extern s16 DAT_0605AEA2;
extern s16 DAT_0605BEC2;
extern s32 DAT_0605CD5C;
void func_0600971C(void);
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
extern s32 DAT_0605D7DC;
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
extern SaturnSpriteResource g_EntitySpriteBank01;
extern SaturnSpriteFrameHeader* DAT_06045E14[];
extern s16 DAT_06045FA8;
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
extern s32 DAT_06064250[];
void StopPcm(s32 param);
void func_06011F40(s32 param);
s32 func_0601BDD0(s32);
extern s32 DAT_060641F4;
extern s32 DAT_06062258;
extern s32 DAT_06062268;
extern s32 DAT_06062290[];
extern s32 DAT_06063BD4;
extern s32 DAT_06063C1C;
extern s32 DAT_06063EB4;
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
extern SaturnSpriteResource g_EntitySpriteBank08;
extern SaturnSpriteFrameHeader* DAT_06046CD0[];
void func_0600AFA8(SpriteObject* sprite, SaturnSpriteFrameHeader* frame);
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
void CSH_Init(Uint16 sw);
s32 ReadFileToAddr(char* path, s32 addr);
extern s16 d_0605AEA8;
extern s16 d_0605AEB0;
extern s32 DAT_060645AC;
void FlushVramTransfers(void);
void func_06008464(void);
void func_06008488(void);
s32 func_0602D754(void*);
void func_0601B910(s32, s32*, s32*, s32*);
extern s32 DAT_06050668;
extern s32 DAT_0605AE80;
extern s32* DAT_0605AE8C;
extern s32 DAT_0605064C;
extern void (*DAT_0600026C)(void);
s32 func_06006170(void);
s32 func_060062F8(s32, s32*);
extern s32 DAT_0605C100;
extern s32 DAT_0605CD80;
extern s32 DAT_0605C65C;
extern void (*DAT_0606465C)(void);
extern void (*DAT_060645C4)(void);
extern s32 DAT_060054D8;
extern s32 DAT_060054E4;
extern s32 DAT_060054F0;
extern s32 DAT_060054FC;
extern s32 DAT_06005810;
extern s32 DAT_0600581C;
extern s32 DAT_0600582C;
extern s32 DAT_060059DC;
extern s32 DAT_060059E8;
extern char* DAT_06038A14[][2];
void func_06009F10(void);
void func_060100DC(void);
void func_0601AEF4(void);
void func_0601AF2C(void);
void func_0601B184(void);
void func_0601B19C(void);
void CSH_AllClr(void);
void InitSpriteEngine(s32 arg0);
void InitVdp2Display(void);
void InitDebugPrint(void);
extern u8 DAT_06057F40;
extern s32 DAT_0605C118;
extern s32 DAT_0605CE90;
extern s32 DAT_0605C6D4;
extern s16 DAT_0605C6DC;
extern Unk0605D770 DAT_0605D770;
extern s32 DAT_0605D764;
struct Unk060505E0 {
    s32 unk0;
    s32 unk4;
};
extern struct Unk060505E0* DAT_060505E0;
extern struct Unk060505E0 DAT_06065D40;
extern volatile u8 DAT_06065D32;
struct Unk060505F8 {
    u16 idSize;
    u16 buttons;
};
extern struct Unk060505F8* DAT_060505F8;
s32 func_0602BB98(s32, s32, s32, s32, s32);
void func_06004A10(void);
void func_0600456C(void);
void func_0600460C(void);
void func_060046E8(void);
void func_060047E8(void);
void func_06004878(void);
void func_06004C14(void);
s32 func_06006470(void);
void func_06007F6C(void);
void func_060082C8(void);
void func_06009D30(void);
void func_0600B234(void);
void func_0600DAB4(void);
extern void SPR_2OpenCommand(Uint16);
extern s32 DAT_0600E23C;
extern MthMatrix DAT_060579A8;
extern s32 DAT_0605BEC0;
extern s32 DAT_060576B0[];
extern s32 DAT_06057770;
extern void func_06008AB4();
extern void func_0600BD68(s32 arg0, s32 arg1, s32 arg2, Unk0605cd70* arg3);
extern void func_0600DE38(void);
extern void func_0600E164(void);
extern void func_06008B20(void);
extern void func_06008EE8(void);
extern void SignalSlaveSh2(void);
extern void ResetPadsRepeat(void);
extern s8 DAT_06057F50;
extern void func_06008C2C(void);
extern void SCL_SetColOffset(
    Uint32 OffsetReg, Uint32 Surfaces, Sint16 red, Sint16 green, Sint16 blue);
extern void (*DAT_06064624)(s32);
extern void (*DAT_0606461C)(s32);
void SCL_SetDisplayMode(u8, u8, u8);
void SCL_SetCycleTable(u16*);
extern u16 DAT_06038D70[];
extern void SCL_Open(Uint32 sclnum);
extern void SCL_MoveTo(Fixed32 x, Fixed32 y, Fixed32 z);
extern void SCL_Close(void);
extern void func_06009D60(u32);
extern u8 DAT_060577A0[];
void rsincos(s32 angle, s32* sinOut, s32* cosOut);
void func_0600BF38();
void func_0600BF8C();
void func_0600BFD8();
void func_0600AB60(void);
extern SaturnSpriteResource** DAT_06064650;
extern s16 DAT_06038FD4;
extern s16 func_0600AE30(s32, SaturnSpriteImage*, s32);
extern SaturnSpriteResource** DAT_060645D4;
extern SaturnSpriteResource** DAT_06064670;
s16 func_0600AEE4(u16*);
extern s32* func_0600CB04(s32, s32);
extern s32 func_0600C880(s32, s32, s32);
struct Unk06057F60 {
    s8 unk0;
    s8 unk1;
    s8 unk2;
    s8 unk3;
    s8 unk4;
    s8 unk5;
    s8 unk6;
};
extern struct Unk06057F60 DAT_06057F60;
extern s32 func_06030968(void*, s32, s32, void*);
extern s32 SYS_state_060485C4;
extern s32 SYS_state_060485C0;
extern s32 DAT_060058C0;
extern s16 DAT_06038FD6;
extern s16 DAT_06038FD8;
void func_0601AF44(void);
extern s32 DAT_06038FE0;
s32 func_06032F50(void* dst, const void* fmt, s32 arg0, s8 arg1);
s32 func_06030768(s32 arg0, void* arg1, void* arg2);
s8 func_06030898(s32 arg0, void* arg1, void* arg2);
s8 func_060307C4(s32 arg0, void* arg1);
extern s32 Crc32(s32, s32*);
extern void (*DAT_0603908C[])(Primitive* prim, s16 x, s16 y);
extern s32 DAT_06061DD4;
extern MthMatrixTbl DAT_06061DF0;
extern Point16 DAT_06057A08;
extern Point16 DAT_06057A0C;
bool CdSoundCommandQueueEmpty(void);
extern void MarkRoomVisited(s32, s32, s32, Tilemap*);
extern Entity DAT_060997F8[];
struct Unk060643E0 {
    u8 unk00[0x1C];
    s32 unk1C;
};
extern struct Unk060643E0 DAT_060643E0;
extern s16 DAT_0606436E;
extern s32 DAT_060644B0;
extern s32 func_06011B28(s32);
extern s32 func_06018B8C(s32, u8, s32);
extern s32 func_06018C00(s32, s32, u8);
/* End moved declarations */

#endif
