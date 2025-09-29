// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <psxsdk/libsnd.h>
#include "disk.h"
#include "dra.h"

// 63ED4.c
s32 D_80137E6C;
SVECTOR D_80137E70[14];
s32 D_80137EE0;
s32 D_80137EE4;
s32 D_80137EE8;
s32 D_80137EEC;
s32 D_80137EF0;
s32 D_80137EF4;
u8 D_80137EF8[0x60];

// cd.c
CdCallbacks g_CdCallback;
CdlLOC g_CdLoc;
CdThing g_Cd;
s16 g_VabId;
u8 D_80137F96;
STATIC_PAD_BSS(5);
s32 D_80137F9C;
s32 D_80137FA0;
STATIC_PAD_BSS(4);
s16 D_80137FA8;
STATIC_PAD_BSS(2);
s32 D_80137FAC;
s32 D_80137FB0;

// 692E8.c
s32 D_80137FB4;
s32 D_80137FB8;
#if defined(VERSION_US)
s32 D_80137FBC;
#endif

// 6D59C.c, 704D0.c
s16 g_WasFacingLeft;
STATIC_PAD_BSS(2);
s16 g_WasFacingLeft2;
STATIC_PAD_BSS(2);
s32 g_WasFacingLeft3;
s32 g_WasFacingLeft4;
s16 g_WasFacingLeft5;
STATIC_PAD_BSS(2);
s32 g_WasFacingLeft6;
s32 g_WasFacingLeft7;

// 71830.c
#if defined(VERSION_US)
s32 D_80137FDC;
#endif

// 72BB0.c, 75F54.c
s32 D_80137FE0;
s32 D_80137FE4;
s32 D_80137FE8;
s32 D_80137FEC;
s32 D_80137FF0;

// 75F54.c
s32 g_WingSmashButtonCounter;
s32 g_WingSmashButtonTimer;
s32 g_WingSmashTimer;
s32 g_BatScreechDone;
s32 g_MistTimer; // remaining time in mist transformation
s32 D_80138008;
s32 D_8013800C[11];
s32 D_80138038;

// 75F54.c, 7A4D0.c
u8 D_8013803C;
STATIC_PAD_BSS(3);
u8 D_80138040;
STATIC_PAD_BSS(3);
u8 D_80138044;
STATIC_PAD_BSS(3);
u8 D_80138048;
STATIC_PAD_BSS(3);

// 78D0C.c
Point16 D_8013804C[16];

// 7E4BC.c
s32 D_8013808C;
s32 D_80138090;
mistStruct D_80138094[16];
s16 D_801381D4;
STATIC_PAD_BSS(2);
s16 D_801381D8;
STATIC_PAD_BSS(2);
s16 D_801381DC;
STATIC_PAD_BSS(2);
s16 D_801381E0;
STATIC_PAD_BSS(2);
s16 D_801381E4;
STATIC_PAD_BSS(2);
s16 D_801381E8;
STATIC_PAD_BSS(2);
s16 D_801381EC;
STATIC_PAD_BSS(2);
s16 D_801381F0;
STATIC_PAD_BSS(2);
Primitive D_801381F4[8];
s32 D_80138394;
s32 D_80138398;

// 843B0.c
Point16 D_8013839C[32];
s32 D_8013841C;
STATIC_PAD_BSS(4);
RECT D_80138424;

// 8A0A4.c, 8D3E8.c
s32 D_8013842C;
s32 D_80138430;
STATIC_PAD_BSS(4);
s32 D_80138438;
s32 D_8013843C;
s32 D_80138440;
s32 D_80138444;
s32 D_80138448;
s32 D_8013844C;
s32 D_80138450;

// sound.c
s32 D_80138454;
s16 g_CurrentXaConfigId;
STATIC_PAD_BSS(2);
s16 D_8013845C;
STATIC_PAD_BSS(2);
#if defined(VERSION_PC)
u8 g_SeqTable[SS_SEQ_TABSIZ * SEQ_TABLE_S_MAX * SEQ_TABLE_T_MAX];
u_long* D_80138784[0x700];
#else
u8 g_SeqTable[800];
u_long* D_80138784[488];
#endif
s32 g_CurCdPos;
u8 g_CdMode[2];
STATIC_PAD_BSS(2);
s32 g_KeyOffChannels;
u8 g_CdCommandResult[8];
STATIC_PAD_BSS(48);
s8 g_KeyStatus[SPU_VOICE_NUM];
s32 D_80138F7C;
s16 D_80138F80;
STATIC_PAD_BSS(2);
s32 g_SeqPointers[10];
s16 g_SfxRingBufferReadPos;
STATIC_PAD_BSS(2);
DebugMode g_DebugMode;
#ifdef VERSION_PC
SpuVoiceAttr D_80138FB4_;
SpuVoiceAttr* D_80138FB4 = &D_80138FB4_;
#else
SpuVoiceAttr* D_80138FB4; // on PSX it points to 0x80000000
#endif
s16 g_VolL;
STATIC_PAD_BSS(2);
s16 D_80138FBC;
STATIC_PAD_BSS(2);
ButtonComboState g_ButtonCombo[COMBO_NUM];
s16 g_sfxRingBufferWritePos;
STATIC_PAD_BSS(2);
s16 g_VolR;
STATIC_PAD_BSS(2);
s32 D_80139008;
u32 g_DebugCurPal;
u16 g_CurSfxDistance20_21;
STATIC_PAD_BSS(2);
u8 D_80139014;
STATIC_PAD_BSS(3);
u8 g_SfxScriptModeCopy[NUM_CH];
s16 D_8013901C;
STATIC_PAD_BSS(2);
u8 g_MuteCd;
STATIC_PAD_BSS(55);
s8 g_SfxScriptDistanceCopy[NUM_CH];
s32 g_PrevEquippedWeapons[2];
s16 g_CurrentXaSoundId;
STATIC_PAD_BSS(54);
s16 g_SeqVolume1;
STATIC_PAD_BSS(2);
u8 D_801390A0;
STATIC_PAD_BSS(3);
u16 g_CurSfxVol20_21;
STATIC_PAD_BSS(2);
u8 D_801390A8;
STATIC_PAD_BSS(3);
u16 g_SfxScriptVolumeCopy[NUM_CH];
s8* g_CurrentSfxScriptCopy[NUM_CH];
u8 g_SeqIsPlaying;
STATIC_PAD_BSS(3);
SpuVoiceAttr* D_801390C8;
SpuVoiceAttr* D_801390CC;
STATIC_PAD_BSS(4);
GpuBuffer* g_BackBuffer;
u8 D_801390D8;
STATIC_PAD_BSS(3);
SfxRingBufferItem g_SfxRingBuffer[MAX_SND_COUNT];
u16 g_CurSfxDistance12_19;
STATIC_PAD_BSS(2);
s16 D_801396E0;
STATIC_PAD_BSS(2);
u16 D_801396E4;
u16 D_801396E6;
u16 D_801396E8;
s16 D_801396EA;
s16 D_801396EC;
STATIC_PAD_BSS(2);
s32 g_CdCommandStatus;
s16 g_CdSoundCommandQueuePos;
STATIC_PAD_BSS(2);
s32 D_801396F8[32];
s32 D_80139778[32];
u16 g_CurSfxVol12_19;
STATIC_PAD_BSS(2);
s32 D_801397FC;
s16 D_80139800;
STATIC_PAD_BSS(2);
s16 g_CurSfxId22_23;
STATIC_PAD_BSS(6);
s32 D_8013980C;
u8 g_SeqPlayingId;
STATIC_PAD_BSS(3);
s16 g_SfxScriptTimerCopy[NUM_CH];
STATIC_PAD_BSS(4);
s16 g_XaMusicVolume;
STATIC_PAD_BSS(2);
s32 D_80139824;
s32 g_StatBuffTimers[16];
s16 g_CdSoundCommandQueue[MAX_SND_COUNT];
s16 g_SoundCommandRingBufferReadPos;
STATIC_PAD_BSS(2);
s16 g_XaVolumeMultiplier;
STATIC_PAD_BSS(2);
s16 g_SoundCommandRingBufferWritePos;
STATIC_PAD_BSS(2);
s16 D_80139A74;
STATIC_PAD_BSS(2);
s16 g_XaFadeCounter;
STATIC_PAD_BSS(2);
u16 D_80139A7C[32 * 80];
u16 g_SfxVolumeMultiplier;
STATIC_PAD_BSS(2);

volatile u8 g_CdSoundCommandStep;
STATIC_PAD_BSS(3);
s16 g_CurrentSfxScriptSfxId[NUM_CH];
s16 g_volumeL;
STATIC_PAD_BSS(2);
s32 D_8013AE90;
s16 g_CurSfxDistance22_23;
STATIC_PAD_BSS(2);
u8 g_ReverbDepth;
STATIC_PAD_BSS(3);
s32 D_8013AE9C;
s16 g_SfxScriptUnk6[NUM_CH];
STATIC_PAD_BSS(20);
s32 D_8013AEBC[4];
s32 D_8013AECC;
bool g_canRevealMap;
s16 D_8013AED4[NUM_CH_2];
u8 D_8013AEDC;
u8 D_8013AEDD[3];
u16 g_CurSfxVol22_23;
STATIC_PAD_BSS(2);
s32 D_8013AEE4;
u8 D_8013AEE8;
STATIC_PAD_BSS(3);
volatile u8 g_SoundInitialized;
STATIC_PAD_BSS(3);
s16 g_SeqVolume2;
STATIC_PAD_BSS(2);
s32 D_8013AEF4;
MemcardInfo g_MemcardInfo[2];
s16 g_SoundCommandRingBuffer[MAX_SND_COUNT];
s32 D_8013B5E8;
u8 g_SfxScriptMode[NUM_CH];
s32 g_MemcardBlockRead;
Cmd14 D_8013B5F4[2];
s8 g_SfxScriptDistance[NUM_CH];
s8 D_8013B618;
STATIC_PAD_BSS(3);
s32 D_8013B61C;
u16 g_SfxScriptVolume[NUM_CH];
s8* g_CurrentSfxScript[NUM_CH];
STATIC_PAD_BSS(8);
CdlLOC D_8013B640;
STATIC_PAD_BSS(4);
s16 g_CurrentSfxScriptSfxId2[NUM_CH];
s16 g_CurrentSfxId12_19[NUM_CH_2];
s16 g_SeqAccessNum;
STATIC_PAD_BSS(2);
s32 D_8013B65C;
s32 g_MemcardStep;
s16 g_CurSfxId20_21;
STATIC_PAD_BSS(2);
s16 g_CdVolume;
STATIC_PAD_BSS(2);
s16 g_SfxScriptTimer[NUM_CH];
STATIC_PAD_BSS(4);
s16 g_CurrentSfxScriptSfxIdCopy[NUM_CH];
u8 D_8013B680;
STATIC_PAD_BSS(3);
u8 g_CdSoundCommand16;
STATIC_PAD_BSS(3);
u8 D_8013B688[8];
s8 D_8013B690;
STATIC_PAD_BSS(3);
s32 D_8013B694;
s16 g_volumeR;
STATIC_PAD_BSS(2);
s32 D_8013B69C;
#if defined(VERSION_HD)
u32 D_8013B6A0; // TODO VAB from BSS, fake symbol
#endif
