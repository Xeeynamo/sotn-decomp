#include <game.h>
#include <psxsdk/libsnd.h>
#include "disk.h"

// TODO dra.h
#define SEQ_TABLE_S_MAX 0x10
#define SEQ_TABLE_T_MAX 1
#define MAX_SND_COUNT 0x100

// 42398.c
s32 g_DebugFreeze;
s32 g_DebugHitboxViewMode;
u32 D_801362B4;
s32 D_801362B8;
s32 D_801362BC;
s32 g_DebugPalIdx;
u32 g_DebugColorChannel; // TODO DebugColorChannel
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
u32 g_NowLoadingModel[14]; // TODO NowLoadingModel

// 47BB8.c
void* g_SimFile;      // TODO SimFile*
u32 D_80136450[4];    // TODO SimFile
s16 D_80136460[1024]; // TODO VSYNC_UNK_LEN
s16 D_80136C60[1024]; // TODO VSYNC_UNK_LEN

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
static s32 D_80137588; // unused
static s32 D_8013758C; // unused

// demo.c
u8* g_DemoPtr;
s32 g_DemoKeyIdx;

// 5087C.c
s32 D_80137598;
s32 D_8013759C;
s32 D_801375A0;
u16 D_801375A4;               // TODO overlaps with D_801375A6
u16 D_801375A6;               // TODO this might be f32
u16 D_801375A8;               // TODO overlaps with D_801375AA
u16 D_801375AA;               // TODO this might be f32
s32 D_801375AC;               // TODO might be f32
s32 D_801375B0;               // TODO might be f32
s32 D_801375B4;               // TODO might be f32
s32 D_801375B8;               // TODO might be f32
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
MenuContext g_MenuData[16]; // TODO MenuData, TODO NUM_MENU
s32 D_801377FC[16];         // TODO NUM_MENU
s32 D_8013783C;
s32 D_80137840;
s32 D_80137844[1];
s32 D_80137848[1];
#if defined(VERSION_US)
s32 D_8013784C;
#endif
s16 g_RelicMenuFadeTimer;
static s16 g_RelicMenuFadeTimer_;
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
u8 g_PlayerHud[0x2C];      // TODO PlayerHud
s32 g_HealingMailTimer[1]; // maybe part of g_PlayerHud

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
static u8 D_80137EF8[0x60]; // unused

// cd.c
CdCallbacks g_CdCallback;
CdlLOC g_CdLoc;
u8 g_Cd[0x34]; // TODO CdThing
s16 g_VabId;
u8 D_80137F96;
static u8 D_80137F97[5]; // unused
s32 D_80137F9C;
s32 D_80137FA0;
static u32 D_80137FA4; // unused
s16 D_80137FA8;
static s16 D_80137FAA; // unused
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
static s16 g_WasFacingLeft_; // alignment padding
s16 g_WasFacingLeft2;
static s16 g_WasFacingLeft2_; // alignment padding
s32 g_WasFacingLeft3;
s32 g_WasFacingLeft4;
s16 g_WasFacingLeft5;
static s16 g_WasFacingLeft5_; // alignment padding
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
static u8 D_8013803C_[3]; // alignment padding
u8 D_80138040;
static u8 D_80138040_[3]; // alignment padding
u8 D_80138044;
static u8 D_80138044_[3]; // alignment padding
u8 D_80138048;
static u8 D_80138048_[3]; // alignment padding

// 78D0C.c
Point16 D_8013804C[16];

// 7E4BC.c
s32 D_8013808C;
s32 D_80138090;
u8 D_80138094[16][0x14]; // TODO mistStruct
s16 D_801381D4;
static s16 D_801381D4_; // alignment padding
s16 D_801381D8;
static s16 D_801381D8_; // alignment padding
s16 D_801381DC;
static s16 D_801381DC_; // alignment padding
s16 D_801381E0;
static s16 D_801381E0_; // alignment padding
s16 D_801381E4;
static s16 D_801381E4_; // alignment padding
s16 D_801381E8;
static s16 D_801381E8_; // alignment padding
s16 D_801381EC;
static s16 D_801381EC_; // alignment padding
s16 D_801381F0;
static s16 D_801381F0_; // alignment padding
Primitive D_801381F4[8];
s32 D_80138394;
s32 D_80138398;

// 843B0.c
Point16 D_8013839C[32];
s32 D_8013841C;
static s32 D_80138420; // unused
RECT D_80138424;

// 8A0A4.c, 8D3E8.c
s32 D_8013842C;
s32 D_80138430;
static u32 D_80138434; // unused
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
static s16 g_CurrentXaConfigId_;
s16 D_8013845C;
static s16 D_8013845E; // alignment padding
#if defined(VERSION_PC)
u8 g_SeqTable[SS_SEQ_TABSIZ * SEQ_TABLE_S_MAX * SEQ_TABLE_T_MAX];
u_long* D_80138784[0x700];
#else
u8 g_SeqTable[800];
u_long* D_80138784[488];
#endif
s32 g_CurCdPos;
u8 g_CdMode[2];
static u8 D_80138F26[2]; // alignment padding
s32 g_KeyOffChannels;
u8 g_CdCommandResult[56];
s8 D_80138F64[SPU_VOICE_NUM];
s32 D_80138F7C;
s16 D_80138F80;
static s16 D_80138F82; // align padding
s32 g_SeqPointers[10];
s16 g_SfxRingBufferReadPos;
static s16 D_80138FAE; // align padding
u32 g_DebugMode;       // TODO DebugMode
#ifdef VERSION_PC
SpuVoiceAttr D_80138FB4_;
SpuVoiceAttr* D_80138FB4 = &D_80138FB4_;
#else
SpuVoiceAttr* D_80138FB4; // on PSX it points to 0x80000000
#endif
s16 g_VolL;
static u16 D_80138FBA; // padding
s16 D_80138FBC;
static s16 D_80138FBE;              // padding
ButtonComboState g_ButtonCombo[16]; // TODO COMBO_NUM
s16 g_sfxRingBufferWritePos;
static s16 D_80139002; // padding
s16 g_VolR;
static u16 D_80139006; // padding
s32 D_80139008;
u32 g_DebugCurPal;
s16 D_80139010;
static s16 D_80139012_; // padding
u8 D_80139014;
static u8 D_80139015[3]; // padding
u8 D_80139018[4];
s16 D_8013901C;
static s16 D_8013901C_; // padding
u8 g_MuteCd;
static u8 D_80139021[55]; // padding
s8 D_80139058[4];
s32 g_PrevEquippedWeapons[2];
s16 g_CurrentXaSoundId;
static u16 g_CurrentXaSoundId_[27]; // padding
s16 g_SeqVolume1;
static u16 g_SeqVolume1_; // padding
u8 D_801390A0;
static u8 D_801390A1[3]; // padding
u16 D_801390A4;
static u16 D_801390A4_; // padding
u8 D_801390A8;
static u8 D_801390A9[3]; // padding
s16 D_801390AC[4];
s32 D_801390B4[4];
u8 D_801390C4;
static u8 D_801390C5[3]; // padding
SpuVoiceAttr* D_801390C8;
SpuVoiceAttr* D_801390CC;
static u32 D_801390D0; // unused
GpuBuffer* g_BackBuffer;
u8 D_801390D8;
static u8 D_801390D9[3]; // padding
SfxRingBufferItem g_SfxRingBuffer[MAX_SND_COUNT];

u16 D_801396DC[2];               // TODO type
u16 D_801396E0[2];               // TODO type
u16 D_801396E4;                  // TODO type
u16 D_801396E6;                  // TODO type
u16 D_801396E8;                  // TODO type
u16 D_801396EA;                  // TODO type
u16 D_801396EC[2];               // TODO type
u32 g_CdCommandStatus;           // TODO type
u16 g_CdSoundCommandQueuePos[2]; // TODO type
u32 D_801396F8[32];              // TODO type
u32 D_80139778[32];              // TODO type
u32 D_801397F8;                  // TODO type
u32 D_801397FC;                  // TODO type
u16 D_80139800[2];               // TODO type
u16 D_80139804[4];               // TODO type
u32 D_8013980C;                  // TODO type
u8 g_SeqPlayingId[4];            // TODO type
u16 D_80139814[6];               // TODO type
u16 g_XaMusicVolume[2];          // TODO type
u32 D_80139824;                  // TODO type
s32 D_80139828[16];
u16 g_CdSoundCommandQueue[256];          // TODO type
u16 g_SoundCommandRingBufferReadPos[2];  // TODO type
u16 D_80139A6C[2];                       // TODO type
u16 g_SoundCommandRingBufferWritePos[2]; // TODO type
u16 D_80139A74[2];                       // TODO type
u32 D_80139A78;                          // TODO type
u32 D_80139A7C[1280];                    // TODO unused?
u16 D_8013AE7C[2];                       // TODO type
u8 g_CdSoundCommandStep[4];              // TODO type
s16 g_CurrentSfxScriptSfxId[4];
u16 g_volumeL[2];                  // TODO type
u32 D_8013AE90;                    // TODO type
u16 D_8013AE94[2];                 // TODO type
u8 g_ReverbDepth[4];               // TODO type
u32 D_8013AE9C;                    // TODO type
u16 D_8013AEA0[4];                 // TODO type
static u16 D_8013AEA8[10];         // unused
u32 D_8013AEBC;                    // TODO type
u16 D_8013AEC0[2];                 // TODO type
u32 D_8013AEC4;                    // TODO type
u32 D_8013AEC8;                    // TODO type
u32 D_8013AECC;                    // TODO type
u32 D_8013AED0;                    // TODO type
u16 D_8013AED4[4];                 // TODO type
u32 D_8013AEDC;                    // TODO type
u16 D_8013AEE0[2];                 // TODO type
u32 D_8013AEE4;                    // TODO type
u8 D_8013AEE8[4];                  // TODO type
u8 g_SoundInitialized[4];          // TODO type
u16 g_SeqVolume2[2];               // TODO type
u32 D_8013AEF4;                    // TODO type
u32 g_MemcardInfo[152];            // TODO type
u32 D_8013B158;                    // TODO type
u32 D_8013B15C;                    // TODO type
u8 D_8013B160[624];                // TODO type
u32 D_8013B3D0[6];                 // TODO type
u16 g_SoundCommandRingBuffer[256]; // TODO type
u32 D_8013B5E8;                    // TODO type
u8 D_8013B5EC[4];                  // TODO type
u32 g_MemcardBlockRead;            // TODO type
u8 D_8013B5F4[2];                  // TODO type
u8 D_8013B5F6[6];                  // TODO type
u32 D_8013B5FC;                    // TODO unused?
u16 D_8013B600[10];                // TODO unused?
s8 g_UnkChannelSetting1[4];
u8 D_8013B618[4]; // TODO type
u32 D_8013B61C;   // TODO type
u16 g_SfxScriptVolume[4];
s8* g_CurrentSfxScript[4];
static u32 D_8013B638[2]; // unused
u32 D_8013B640[2];        // TODO type
s16 D_8013B648[4];
s16 D_8013B650[4];
u16 g_SeqAccessNum[2]; // TODO type
u32 D_8013B65C;        // TODO type
u32 g_MemcardStep;     // TODO type
u16 D_8013B664[2];     // TODO type
u16 g_CdVolume[2];     // TODO type
s16 g_SfxScriptTimer[4];
u16 D_8013B674[2];        // TODO type
u16 D_8013B678[3];        // TODO type
u16 D_8013B67E;           // TODO type
u8 D_8013B680[4];         // TODO type
u8 g_CdSoundCommand16[4]; // TODO type
u8 D_8013B688[8];         // TODO type
u8 D_8013B690[4];         // TODO type
u32 D_8013B694;           // TODO type
u16 g_volumeR[2];         // TODO type
u32 D_8013B69C;           // TODO type
#if defined(VERSION_HD)
u32 D_8013B6A0; // TODO type
#endif
