// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <psxsdk/libsnd.h>
#include "disk.h"
#include "dra.h"

#define padding static

// 42398.c
s32 g_DebugFreeze;
s32 g_DebugHitboxViewMode;
u32 D_801362B4;
s32 D_801362B8;
s32 D_801362BC;
s32 g_DebugPalIdx;
DebugColorChannel g_DebugColorChannel;
u32 D_801362C8;
OT_TYPE* g_CurrentOT;
s32 D_801362D0;
s32 D_801362D4;
s32 g_DebugIsRecordingVideo;
GpuUsage g_GpuMaxUsage;
s32 g_DebugWaitInfoTimer;
s32 g_DebugRecordVideoFid;
s16 D_80136308[128];
#if defined(VERSION_US)
s32 g_softResetTimer;
#endif

// play.c
s32 D_8013640C;
s32 D_80136410;

// loading.c
NowLoadingModel g_NowLoadingModel;

// 47BB8.c
SimFile* g_SimFile;
SimFile D_80136450;
s16 D_80136460[VSYNC_UNK_LEN];
s16 D_80136C60[VSYNC_UNK_LEN];

// pads.c
u8 g_PadsRepeatTimer[BUTTON_COUNT * PAD_COUNT];

// save_mgr.c
s32 g_MemcardRetryCount;
s32 g_MemcardFd;

// 4A538.c
u16 D_80137478[ICON_SLOT_NUM];
u16 D_801374B8[ICON_SLOT_NUM];
u16 D_801374F8[ICON_SLOT_NUM];
u16 D_80137538[ICON_SLOT_NUM];
u8* g_DecSrcPtr;
u8* g_DecDstPtr;
s32 g_DecReadNibbleFlag;
s32 g_DecWriteNibbleFlag;
padding s32 D_80137588;
padding s32 D_8013758C;

// demo.c
u8* g_DemoPtr;
s32 g_DemoKeyIdx;

// 5087C.c
s32 D_80137598;
s32 D_8013759C;
s32 D_801375A0;
s32 D_801375A4;
s32 D_801375A8;
s32 D_801375AC;
s32 D_801375B0;
s32 D_801375B4;
s32 D_801375B8;
RoomLoadDefHolder D_801375BC; // fake struct?
s32 D_801375C0;
s32 D_801375C4;
s32 D_801375C8;

// menu.c
EquipKind D_801375CC;
s32 D_801375D0;
s32 D_801375D4;
s32* D_801375D8;
s32 D_801375DC;
s32 D_801375E0[NUM_FAMILIARS + 1];
s32 g_IsCloakLiningUnlocked;
s32 g_IsCloakColorUnlocked;
s32 D_80137608;
s32 g_IsSelectingEquipment;
s32 g_EquipmentCursor;
s32 D_80137614;
s32 g_EquipOrderType;
MenuData g_MenuData;
s32 D_801377FC[NUM_MENU];
s32 D_8013783C;
s32 D_80137840;
s32 D_80137844[1];
s32 D_80137848[1];
#if defined(VERSION_US)
s32 D_8013784C;
#endif
s16 g_RelicMenuFadeTimer;
padding s16 g_RelicMenuFadeTimer_;
s32 g_TimeAttackEntryTimes[NUM_TIMEATTACK_EVENTS];
s32 c_strTimeAttackEntry[NUM_TIMEATTACK_EVENTS];
s32 g_NewAttackRightHand;
s32 g_NewAttackLeftHand;
s32 g_NewDefenseEquip;
s32 g_NewPlayerStatsTotal[4];
s32 D_80137948;
s8* D_8013794C;
s32 D_80137950;
s32 D_80137954;
s32 D_80137958;
s32 g_ServantPrevious;

// 5D5BC.c
s32 D_80137960;
s32 D_80137964;
s32 D_80137968;
PlayerHud g_PlayerHud;
s32 g_HealingMailTimer[1];

// both 5D5BC.c and 627C4.c, maybe need another C file in between
u32 D_8013799C;
s32 D_801379A0;
s32 D_801379A4;
s32 D_801379A8;

// 627C4.c, 63ED4.c
Unkstruct_80102CD8 D_801379AC;

// 63ED4.c
s32 D_801379B8;
s32 D_801379BC;
SVECTOR D_801379C0;
SVECTOR D_801379C8;
VECTOR D_801379D0;
VECTOR D_801379E0[20];
VECTOR D_80137B20[24];
SVECTOR D_80137CA0[20];
SVECTOR D_80137D40[24];
MATRIX D_80137E00;
MATRIX D_80137E20;
s32 D_80137E40;
s32 D_80137E44;
s32 D_80137E48;
s32 D_80137E4C;
s32 g_MemCardRetryCount;
s32 D_80137E54;
s32 D_80137E58;
s32 D_80137E5C;
s32 D_80137E60;
s32 g_MemCardRStep;
s32 g_MemCardRStepSub;
s32 D_80137E6C;
SVECTOR D_80137E70[14];
s32 D_80137EE0;
s32 D_80137EE4;
s32 D_80137EE8;
s32 D_80137EEC;
s32 D_80137EF0;
s32 D_80137EF4;
padding u8 D_80137EF8[0x60];

// cd.c
CdCallbacks g_CdCallback;
CdlLOC g_CdLoc;
CdThing g_Cd;
s16 g_VabId;
u8 D_80137F96;
padding u8 D_80137F97[5];
s32 D_80137F9C;
s32 D_80137FA0;
padding u32 D_80137FA4;
s16 D_80137FA8;
padding s16 D_80137FAA;
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
padding s16 g_WasFacingLeft_;
s16 g_WasFacingLeft2;
padding s16 g_WasFacingLeft2_;
s32 g_WasFacingLeft3;
s32 g_WasFacingLeft4;
s16 g_WasFacingLeft5;
padding s16 g_WasFacingLeft5_;
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
padding u8 D_8013803C_[3];
u8 D_80138040;
padding u8 D_80138040_[3];
u8 D_80138044;
padding u8 D_80138044_[3];
u8 D_80138048;
padding u8 D_80138048_[3];

// 78D0C.c
Point16 D_8013804C[16];

// 7E4BC.c
s32 D_8013808C;
s32 D_80138090;
mistStruct D_80138094[16];
s16 D_801381D4;
padding s16 D_801381D4_;
s16 D_801381D8;
padding s16 D_801381D8_;
s16 D_801381DC;
padding s16 D_801381DC_;
s16 D_801381E0;
padding s16 D_801381E0_;
s16 D_801381E4;
padding s16 D_801381E4_;
s16 D_801381E8;
padding s16 D_801381E8_;
s16 D_801381EC;
padding s16 D_801381EC_;
s16 D_801381F0;
padding s16 D_801381F0_;
Primitive D_801381F4[8];
s32 D_80138394;
s32 D_80138398;

// 843B0.c
Point16 D_8013839C[32];
s32 D_8013841C;
padding s32 D_80138420;
RECT D_80138424;

// 8A0A4.c, 8D3E8.c
s32 D_8013842C;
s32 D_80138430;
padding u32 D_80138434;
s32 D_80138438;
s32 D_8013843C;
s32 D_80138440;
s32 D_80138444;
s32 D_80138448;
s32 D_8013844C;
s32 D_80138450;

// 91EBC.c, 92F60.c, 93290.c, 93BDC.c, 94F50.c, 953A0.c
s32 D_80138454;
s16 g_CurrentXaConfigId;
padding s16 g_CurrentXaConfigId_;
s16 D_8013845C;
padding s16 D_8013845E;
#if defined(VERSION_PC)
u8 g_SeqTable[SS_SEQ_TABSIZ * SEQ_TABLE_S_MAX * SEQ_TABLE_T_MAX];
u_long* D_80138784[0x700];
#else
u8 g_SeqTable[800];
u_long* D_80138784[488];
#endif
s32 g_CurCdPos;
u8 g_CdMode[2];
padding u8 D_80138F26[2];
s32 g_KeyOffChannels;
u8 g_CdCommandResult[8];
static u8 D_80138F38[48];
s8 g_KeyStatus[SPU_VOICE_NUM];
s32 D_80138F7C;
s16 D_80138F80;
padding s16 D_80138F82;
s32 g_SeqPointers[10];
s16 g_SfxRingBufferReadPos;
padding s16 D_80138FAE;
DebugMode g_DebugMode;
#ifdef VERSION_PC
SpuVoiceAttr D_80138FB4_;
SpuVoiceAttr* D_80138FB4 = &D_80138FB4_;
#else
SpuVoiceAttr* D_80138FB4; // on PSX it points to 0x80000000
#endif
s16 g_VolL;
padding u16 D_80138FBA;
s16 D_80138FBC;
padding s16 D_80138FBE;
ButtonComboState g_ButtonCombo[COMBO_NUM];
s16 g_sfxRingBufferWritePos;
padding s16 D_80139002;
s16 g_VolR;
padding u16 D_80139006;
s32 D_80139008;
u32 g_DebugCurPal;
s16 g_CurSfxDistance20_21;
padding s16 D_80139012_;
u8 D_80139014;
padding u8 D_80139015[3];
s8 g_SfxScriptModeCopy[NUM_CH];
s16 D_8013901C;
padding s16 D_8013901C_;
u8 g_MuteCd;
padding u8 D_80139021[55];
s8 g_SfxScriptDistanceCopy[NUM_CH];
s32 g_PrevEquippedWeapons[2];
s16 g_CurrentXaSoundId;
padding u16 g_CurrentXaSoundId_[27];
s16 g_SeqVolume1;
padding u16 g_SeqVolume1_;
u8 D_801390A0;
padding u8 D_801390A1[3];
s16 g_CurSfxVol20_21;
padding u16 D_801390A4_;
u8 D_801390A8;
padding u8 D_801390A9[3];
s16 g_SfxScriptVolumeCopy[NUM_CH];
s32 D_801390B4[NUM_CH];
u8 g_SeqIsPlaying;
padding u8 D_801390C5[3];
SpuVoiceAttr* D_801390C8;
SpuVoiceAttr* D_801390CC;
padding u32 D_801390D0;
GpuBuffer* g_BackBuffer;
u8 D_801390D8;
padding u8 D_801390D9[3];
SfxRingBufferItem g_SfxRingBuffer[MAX_SND_COUNT];
s16 g_CurSfxDistance12_19;
padding s16 D_801396DE;
s16 D_801396E0;
padding s16 D_801396E2;
u16 D_801396E4;
u16 D_801396E6;
u16 D_801396E8;
s16 D_801396EA;
u16 D_801396EC;
padding u16 D_801396EE;
s32 g_CdCommandStatus;
s16 g_CdSoundCommandQueuePos;
padding u16 g_CdSoundCommandQueuePos_;
s32 D_801396F8[32];
s32 D_80139778[32];
u16 g_CurSfxVol12_19;
padding s16 D_801397FA;
s32 D_801397FC;
s16 D_80139800;
padding s16 D_80139800_;
s16 g_CurSfxId22_23;
padding s16 D_80139806;
padding s32 D_80139808;
s32 D_8013980C;
u8 g_SeqPlayingId;
padding u8 g_SeqPlayingId_[3];
s16 g_SfxScriptTimerCopy[NUM_CH];
padding s32 D_80139814_;
s16 g_XaMusicVolume;
padding u16 g_XaMusicVolume_;
s32 D_80139824;
s32 D_80139828[16];
s16 g_CdSoundCommandQueue[MAX_SND_COUNT];
s16 g_SoundCommandRingBufferReadPos;
padding s16 g_SoundCommandRingBufferReadPos_;
s16 g_XaVolumeMultiplier;
padding s16 D_80139A6E;
s16 g_SoundCommandRingBufferWritePos;
padding s16 g_SoundCommandRingBufferWritePos_;
s16 D_80139A74;
padding s16 D_80139A76;
s16 g_XaFadeCounter;
padding s16 D_80139A7A;
u16 D_80139A7C[32 * 80];
u16 g_SfxVolumeMultiplier;
padding u16 D_8013AE7E;

volatile u8 g_CdSoundCommandStep;
padding u8 g_CdSoundCommandStep_[3];
s16 g_CurrentSfxScriptSfxId[NUM_CH];
s16 g_volumeL;
padding s16 g_volumeL_;
s32 D_8013AE90;
s16 g_CurSfxDistance22_23;
padding u16 D_8013AE96;
u8 g_ReverbDepth;
padding u8 g_ReverbDepth_[3];
s32 D_8013AE9C;
s16 g_SfxScriptUnk6[NUM_CH];
padding u16 D_8013AEA8[10];
s32 D_8013AEBC[4];
s32 D_8013AECC;
bool g_canRevealMap;
s16 D_8013AED4[NUM_CH_2];
u8 D_8013AEDC;
u8 D_8013AEDD[3];
u16 g_CurSfxVol22_23;
padding u16 D_8013AEE2;
s32 D_8013AEE4;
s8 D_8013AEE8;
padding u8 D_8013AEE9[3];
u8 g_SoundInitialized;
padding u8 D_8013AEED[3];
s16 g_SeqVolume2;
padding s16 D_8013AEF2;
s32 D_8013AEF4;
MemcardInfo g_MemcardInfo[2];
s16 g_SoundCommandRingBuffer[MAX_SND_COUNT];
s32 D_8013B5E8;
u8 g_SfxScriptMode[NUM_CH];
s32 g_MemcardBlockRead;
Cmd14 D_8013B5F4[2];
s8 g_SfxScriptDistance[NUM_CH];
s8 D_8013B618;
padding u8 D_8013B619[3];
s32 D_8013B61C;
u16 g_SfxScriptVolume[NUM_CH];
s8* g_CurrentSfxScript[NUM_CH];
padding u32 D_8013B638[2];
CdlLOC D_8013B640;
padding u32 D_8013B644;
s16 g_CurrentSfxScriptSfxId2[NUM_CH];
s16 g_CurrentSfxId12_19[NUM_CH_2];
s16 g_SeqAccessNum;
padding u16 D_8013B65A;
s32 D_8013B65C;
s32 g_MemcardStep;
s16 g_CurSfxId20_21;
padding u16 D_8013B666;
s16 g_CdVolume;
padding u16 D_8013B66A;
s16 g_SfxScriptTimer[NUM_CH];
padding u32 D_8013B674;
s16 g_CurrentSfxScriptSfxIdCopy[NUM_CH];
u8 D_8013B680;
padding u8 D_8013B681[3];
u8 g_CdSoundCommand16;
padding u8 D_8013B685[3];
u8 D_8013B688[8];
s8 D_8013B690;
static u8 D_8013B693[3];
s32 D_8013B694;
s16 g_volumeR;
static s16 D_8013B69A;
s32 D_8013B69C;
#if defined(VERSION_HD)
u32 D_8013B6A0; // TODO VAB from BSS, fake symbol
#endif
