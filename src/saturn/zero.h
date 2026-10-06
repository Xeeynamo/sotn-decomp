// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef ZERO_BIN_H
#define ZERO_BIN_H
#include "sattypes.h"
#include "stage_data.h"
#include "lib/scl.h"
#include "lib/per.h"
#include "lib/bup.h"
#include "lib/cdc.h"
#include "lib/snd.h"
#include "inc_asm.h"
#include <saturn_sprite.h>

// func_06023394
void DMA_CpuMemCopy2(s32*, s32*, u32);

// func_06023484
s32 DMA_CpuResult();

// func_060234F4
void DMA_ScuInit();

void InitPrimBuf();
void func_06004D84(void);
void func_06004DE8(void);
void func_06004E50(void);
void func_06004E94(void);
void INT_SetScuFunc(u32 vector, void (*handler)(void));

// DAT_0605C120, DAT_060645EC, DAT_060645e4, DAT_060645f8 and SpGourTbl
// are deliberately absent: zero and its dependents access them at
// different types, and a shared declaration changes codegen.
// Each user declares its own.
extern s32 DAT_060DC004[];
extern s32 DAT_060DC008[];
extern s32 DAT_060DC00C[];
extern s32 DAT_0605D910[];
struct ShakeState {
    s16 id;
    s16 index;
    s16* offsets;
    s16 offset;
};
extern struct ShakeState DAT_06057A10;
extern s32 DAT_00252000;
extern s32 DAT_00258000;

extern SaturnSpriteResource** DAT_060645D0;

extern s32 DAT_060485E0[];
extern Unk0605DB60 d_0605DB60[32];

typedef struct {
    s32 dst0;
    s32 dst4;
    u16* unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s16 unk24;
    u16 flags;
    u16 width;
    u16 height;
    u16 divisorX;
    u16 divisorY;
} Unk0605CD90;

void func_0600871C(Unk0605CD90*, UNK_0605c680*, s32);

void BuildSubDispTilemap(Unk0605CD90* arg0);
s32 DAT_060086e4;
s32 DecompressLZSS(u8*, u8*, u32);
void DmaScroll(u16* src, u16* dest, u32 cnt);

typedef struct {
    u32 tileFlags;
    u32 src;
    u32 dest;
    u32 cnt;
} BgTransfer;

extern Unk0605CD90 DAT_0605CD90[];
extern BgTransfer DAT_0605D6C0[8];

#define DMA_SRC_ADDR 0x002E0000

extern s16 DAT_06062224[];
extern s32 DAT_06039214;
void ClearDebugPrintTilemap();

#define SH2_REG_M_FRT_IC 0x21000000

extern void* g_BatResourceDescriptorList;

extern s32* DAT_060a5000;

extern SaturnStageDataTables g_StageOverlayData;

extern s32* DAT_06066000;

void func_06006FA8(void);

extern s32 DAT_060476a0;
extern s32 DAT_060476a4;
extern s32 DAT_06038a44;

void func_060082E8(void);
void func_0600841C(void);

void InitPaletteRemapLuts(void);
void func_0600B254(void);

extern u32 DAT_0605C658;
void func_06030df0();
void InitBackupRam(void);
s32 func_0600D028(u32 device, s8 arg1);
s8 func_0600D264(u32 device, s8 arg1);
s8 func_0600D47C(u32 device, s8 arg1);
void InitSystem();
void func_060040D8();

/* Declarations moved here by tools/saturn/move_declarations.py */
extern s32 DAT_0605CD5C;
void func_0600971C(void);
void func_06005208(s32);
extern bool DAT_0605D7F0;
extern s32 DAT_0605c6e4;
extern s32 DAT_0605c664;
extern s16 DAT_0605c110;
extern u16 DAT_0605becc;
extern u8 DAT_06057f68;
extern u8* DAT_060645b8;
void func_06009510(u16);
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
extern Unk0605cd70 DAT_0605cea0;
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
extern MthXy DAT_06061DE0;
extern XyInt DAT_06061DE8;
extern BupConfig DAT_0605DD90;
extern u16 DAT_0605DD94;
extern s8 DAT_0605DD60;
extern s8 DAT_0605DD61;
extern u32 DAT_0605DDD0[BUP_LIB_SIZE4];
extern u32 DAT_06002000[BUP_WORK_SIZE4];

void func_0600C818();
void ResetLayerColorCalc();
extern u16 DAT_0605CDB8;
void DestroySpriteObject(SpriteObject*);
extern u32 g_randomNext;
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
s32 func_06006574(struct Unk0600654C*);
extern s32 DAT_0605d7f8;
extern s32 DAT_06057f34;
void SPR_WaitDrawEnd();
void func_06012fb4();
void func_0600D8BC();
void func_06009838();
void UpdateScrollForRoom();
void TransferAllBgLayers();
void func_06008264();
void CloseSpriteList();
void func_06007d54();
void func_0600652C();
void func_06005310();
void func_06004F50();
void ReturnToGame();
void SetVblank(s32);
void func_0600456c();
void ClearDebugPrintTilemap(void);
extern s32 SpMstCmdPos;
void CSH_Init(Uint16 sw);
s32 ReadFileToAddr(char* path, s32 addr);
extern s16 d_0605AEA8;
extern s16 d_0605AEB0;
extern s32 DAT_060645AC;
void FlushVramTransfers(void);
void func_06008464(void);
void func_06008488(void);
extern s32 DAT_06050668;
extern s32 DAT_0605AE80;
extern s32* DAT_0605AE8C;
extern s32 DAT_0605064C;
s32 func_06006170(void);
s32 func_060062F8(s32, s32*);
extern s32 DAT_0605C100;
extern s32 DAT_0605CD80;
extern s32 DAT_0605C65C;
extern void (*DAT_0606465C)(void);
extern void (*DAT_060645C4)(void);
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
typedef struct {
    s8 r;
    s8 g;
    s8 b;
    s16 a;
} Unk0605C6D8;
extern Unk0605C6D8 DAT_0605C6D8;
extern Unk0605D770 DAT_0605D770;
extern s32 DAT_0605D764;

extern PerGetSys* DAT_060505E0;
extern PerGetSys* DAT_060505E4;
typedef struct {
    u8 id;
    u8 size;
    u16 buttons;
} PerData;
extern PerData* DAT_060505F8;
extern PerMulInfo* DAT_060505FC;
extern u8* DAT_06050600;

void func_06004A10(void);
void func_0600456C(void);
void func_0600460C(void);
void func_060046E8(void);
void func_060047E8(void);
void func_06004878(void);
void UpdatePads(void);
void UpdatePadsRepeat(void);
s32 func_06006470(void);
void SetVDP2Vram(void);
void func_060082C8(void);
void func_06009D30(void);
void func_0600B234(void);
void func_0600DAB4(void);
extern void SPR_2OpenCommand(Uint16);
extern MthMatrix DAT_060579A8;
extern Point16 DAT_0605BEC0;
extern s32 DAT_060576B0[];
extern s32 DAT_06057770;
extern void func_06008AB4(void);
extern void func_0600BD68(void);
void SetCurrentMatrixBinAngle(MthXyz* rot, MthXyz* pos);
void TransformAndProjectPoints(MthXyz* src, XyInt* dst, s32 count);
extern void func_0600DE38(void);
extern void func_0600E164(void);
extern void func_06008B20(void);
extern void func_06008EE8(void);
extern void SignalSlaveSh2(void);
extern void ResetPadsRepeat(void);
extern void func_06008C2C(void);
extern void (*DAT_06064624)(s32);
extern void (*DAT_0606461C)(s32);
extern u16 DAT_06038D70[];
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
extern u16* func_0600CB04(s32, s32);
extern s32 func_0600C880(s32, s32, s32);
extern u8 DAT_06057F60[];
extern s16 DAT_06038FD6;
extern s16 DAT_06038FD8;
void func_0601AF44(void);
extern char* DAT_06038FE0;
s32 sprintf(char* str, const char* format, ...);
extern void (*DAT_0603908C[])(Primitive* prim, s16 x, s16 y);
extern s32 DAT_06061DD4;
extern MthMatrixTbl DAT_06061DF0;
extern Point16 DAT_06057A08;
extern Point16 DAT_06057A0C;
bool CdSoundCommandQueueEmpty(void);
/* End moved declarations */

#endif
