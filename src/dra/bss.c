#include "common.h"
#include <game.h>

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
// 5D5BC.c
// 627C4.c
// 63ED4.c
// cd.c
// 692E8.c
// 6D59C.c
// 704D0.c
// 71830.c
// 72BB0.c
// 75F54.c
// 78D0C.c
// 7A4D0.c
// 7E4BC.c
// 843B0.c
// 8A0A4.c
// 8D3E8.c
// 91EBC.c
// 92F60.c
// 93290.c
// 93BDC.c
// 94F50.c
// 953A0.c

u32 D_801375CC;                 // TODO type
u32 D_801375D0;                 // TODO type
u32 D_801375D4;                 // TODO type
u32 D_801375D8;                 // TODO type
u32 D_801375DC;                 // TODO type
u32 D_801375E0[7];              // TODO type
u32 D_801375FC;                 // TODO type
u32 g_IsCloakLiningUnlocked;    // TODO type
u32 g_IsCloakColorUnlocked;     // TODO type
u32 D_80137608;                 // TODO type
u32 g_IsSelectingEquipment;     // TODO type
u32 g_EquipmentCursor;          // TODO type
u32 D_80137614;                 // TODO type
u32 g_EquipOrderType;           // TODO type
u16 g_MenuData[12];             // TODO type
u16 D_80137634[2];              // TODO unused?
u8 D_80137638;                  // TODO type
u8 D_80137639;                  // TODO unused?
u8 D_8013763A[60];              // TODO unused?
u16 D_80137676;                 // TODO unused?
u16 D_80137678[2];              // TODO unused?
u16 D_8013767C[6];              // TODO type
u16 D_80137688[2];              // TODO type
u16 D_80137692[18];             // TODO unused?
u8 D_801376B0[20];              // TODO type
u16 D_801376C4[2];              // TODO type
u16 D_801376C8[19];             // TODO type
u16 g_JosephsCloakContext[135]; // TODO type
u32 D_801377FC[16];             // TODO type
u32 D_8013783C;                 // TODO type
u32 D_80137840;                 // TODO type
u32 D_80137844;                 // TODO type
u32 D_80137848;                 // TODO type
#if defined(VERSION_US)
u32 D_8013784C; // TODO type
#endif
u32 g_RelicMenuFadeTimer;       // TODO type
u32 g_TimeAttackEntryTimes[27]; // TODO type
u32 c_strTimeAttackEntry[27];   // TODO type
u32 g_NewAttackRightHand;       // TODO type
u32 g_NewAttackLeftHand;        // TODO type
u32 g_NewDefenseEquip;          // TODO type
u32 g_NewPlayerStatsTotal[4];   // TODO type
u32 D_80137948;                 // TODO type
u32 D_8013794C;                 // TODO type
u32 D_80137950;                 // TODO type
u32 D_80137954;                 // TODO type
u32 D_80137958;                 // TODO type
u32 g_ServantPrevious;          // TODO type
u32 D_80137960;                 // TODO type
u32 D_80137964;                 // TODO type
u32 D_80137968;                 // TODO type
u32 g_PlayerHud;                // TODO type
u32 D_80137970;                 // TODO type
u32 D_80137974;                 // TODO type
u32 D_80137978;                 // TODO type
u32 D_8013797C;                 // TODO type
u32 D_80137980;                 // TODO type
u32 D_80137984;                 // TODO type
u32 D_80137988;                 // TODO type
u32 D_8013798C;                 // TODO type
u32 D_80137990;                 // TODO type
u32 D_80137994;                 // TODO type
u32 g_HealingMailTimer;         // TODO type
u32 D_8013799C;                 // TODO type
u32 D_801379A0;                 // TODO type
u32 D_801379A4;                 // TODO type
u32 D_801379A8;                 // TODO type
u16 D_801379AC;                 // TODO type
u16 D_801379AE;                 // TODO unused?
u32 D_801379B0;                 // TODO type
u16 D_801379B4[2];              // TODO unused?
u32 D_801379B8;                 // TODO type
u32 D_801379BC;                 // TODO type
u16 D_801379C0;                 // TODO type
u16 D_801379C2;                 // TODO unused?
u16 D_801379C4[2];              // TODO type
u16 D_801379C8;                 // TODO type
u16 D_801379CA;                 // TODO unused?
u16 D_801379CC[2];              // TODO unused?
u32 D_801379D0;                 // TODO type
u32 D_801379D4;                 // TODO unused?
u32 D_801379D8[2];              // TODO unused?
u32 D_801379E0[80];             // TODO type
u32 D_80137B20[96];             // TODO type
u32 D_80137CA0[40];             // TODO type
u32 D_80137D40[48];             // TODO type
u32 D_80137E00[8];              // TODO type
u32 D_80137E20[8];              // TODO type
u32 D_80137E40;                 // TODO type
u32 D_80137E44;                 // TODO type
u32 D_80137E48;                 // TODO type
u32 D_80137E4C;                 // TODO type
u32 g_MemCardRetryCount;        // TODO type
u32 D_80137E54;                 // TODO type
u32 D_80137E58;                 // TODO type
u32 D_80137E5C;                 // TODO type
u32 D_80137E60;                 // TODO type
u32 g_MemCardRStep;             // TODO type
u32 g_MemCardRStepSub;          // TODO type
u32 D_80137E6C;                 // TODO type
u16 D_80137E70;                 // TODO type
u16 D_80137E72;                 // TODO unused?
u16 D_80137E74;                 // TODO unused?
u16 D_80137E76;                 // TODO unused?
u32 D_80137E78[2];              // TODO unused?
u32 D_80137E80[2];              // TODO unused?
u32 D_80137E88[2];              // TODO unused?
u32 D_80137E90[2];              // TODO unused?
u32 D_80137E98[2];              // TODO unused?
u32 D_80137EA0[2];              // TODO unused?
u32 D_80137EA8[2];              // TODO unused?
u32 D_80137EB0[2];              // TODO unused?
u32 D_80137EB8[2];              // TODO unused?
u32 D_80137EC0[2];              // TODO unused?
u32 D_80137EC8[2];              // TODO unused?
u32 D_80137ED0[2];              // TODO unused?
u32 D_80137ED8[2];              // TODO unused?
u32 D_80137EE0;                 // TODO type
u32 D_80137EE4;                 // TODO type
u32 D_80137EE8;                 // TODO type
u32 D_80137EEC;                 // TODO type
u32 D_80137EF0;                 // TODO type
u32 D_80137EF4;                 // TODO type
u32 D_80137EF8[24];             // TODO type
u32 g_CdCallback;               // TODO type
u32 g_CdLoc;                    // TODO type
u16 g_Cd;                       // TODO type
u16 D_80137F62;                 // TODO unused?
u16 D_80137F64;                 // TODO unused?
u16 D_80137F66;                 // TODO unused?
u32 g_Cd_D_80137F68;            // TODO unused?
u32 D_80137F6C;                 // TODO type
u32 g_Cd_D_80137F70;            // TODO unused?
u32 g_Cd_D_80137F74;            // TODO unused?
u32 g_Cd_D_80137F78;            // TODO unused?
u32 g_Cd_D_80137F7C;            // TODO unused?
u32 g_Cd_overlayCopySrc;        // TODO unused?
u32 g_Cd_overlayCopyDst;        // TODO unused?
u32 g_Cd_addr;                  // TODO unused?
u32 g_Cd_overlayBlockCount;     // TODO unused?
u32 g_Cd_overlayLastBlockSize;  // TODO unused?
u8 g_VabId[2];                  // TODO unused?
u8 D_80137F96[6];               // TODO unused?
u32 D_80137F9C;                 // TODO type
u32 D_80137FA0[2];              // TODO type
u16 D_80137FA8[2];              // TODO type
u32 D_80137FAC;                 // TODO type
u32 D_80137FB0;                 // TODO type
u32 D_80137FB4;                 // TODO type
u32 D_80137FB8;                 // TODO type
#if defined(VERSION_US)
u32 D_80137FBC; // TODO type
#endif
u16 g_WasFacingLeft[2];  // TODO type
u16 g_WasFacingLeft2[2]; // TODO type
u32 g_WasFacingLeft3;    // TODO type
u32 g_WasFacingLeft4;    // TODO type
u16 g_WasFacingLeft5[2]; // TODO type
u32 g_WasFacingLeft6;    // TODO type
u32 g_WasFacingLeft7;    // TODO type
#if defined(VERSION_US)
u32 D_80137FDC; // TODO type
#endif
u32 D_80137FE0;                          // TODO type
u32 D_80137FE4;                          // TODO type
u32 D_80137FE8;                          // TODO type
u32 D_80137FEC;                          // TODO type
u32 D_80137FF0;                          // TODO type
u32 g_WingSmashButtonCounter;            // TODO type
u32 g_WingSmashButtonTimer;              // TODO type
u32 g_WingSmashTimer;                    // TODO type
u32 g_BatScreechDone;                    // TODO type
u32 g_MistTimer;                         // TODO type
u32 D_80138008;                          // TODO type
u32 D_8013800C;                          // TODO type
u32 D_80138010;                          // TODO type
u32 D_80138014;                          // TODO type
u32 D_80138018[8];                       // TODO type
u32 D_80138038;                          // TODO type
u8 D_8013803C[4];                        // TODO type
u8 D_80138040[4];                        // TODO type
u8 D_80138044[4];                        // TODO type
u8 D_80138048[4];                        // TODO type
u16 D_8013804C;                          // TODO type
u16 D_8013804E[31];                      // TODO unused?
u32 D_8013808C;                          // TODO type
u32 D_80138090;                          // TODO type
u16 D_80138094;                          // TODO type
u16 D_80138096[2];                       // TODO unused?
u16 D_8013809A;                          // TODO unused?
u32 D_8013809C;                          // TODO unused?
u32 D_801380A0;                          // TODO unused?
u32 D_801380A4[76];                      // TODO unused?
u32 D_801381D4;                          // TODO type
u32 D_801381D8;                          // TODO type
u32 D_801381DC;                          // TODO type
u32 D_801381E0;                          // TODO type
u32 D_801381E4;                          // TODO type
u32 D_801381E8;                          // TODO type
u32 D_801381EC;                          // TODO type
u32 D_801381F0;                          // TODO type
u8 D_801381F4[416];                      // TODO type
u32 D_80138394;                          // TODO type
u32 D_80138398;                          // TODO type
u16 D_8013839C;                          // TODO type
u16 D_8013839E[63];                      // TODO unused?
u32 D_8013841C;                          // TODO type
u32 D_80138420;                          // TODO unused?
u16 D_80138424;                          // TODO type
u16 D_80138426;                          // TODO unused?
u16 D_80138428;                          // TODO unused?
u16 D_8013842A;                          // TODO unused?
u32 D_8013842C;                          // TODO type
u32 D_80138430[2];                       // TODO type
u32 D_80138438;                          // TODO type
u32 D_8013843C;                          // TODO type
u32 D_80138440;                          // TODO type
u32 D_80138444;                          // TODO type
u32 D_80138448;                          // TODO type
u32 D_8013844C;                          // TODO type
u32 D_80138450;                          // TODO type
u32 D_80138454;                          // TODO type
u32 g_CurrentXaConfigId;                 // TODO type
u32 D_8013845C;                          // TODO type
u8 g_SeqTable[804];                      // TODO type
u32 D_80138784[487];                     // TODO type
u32 g_CurCdPos;                          // TODO type
u8 g_CdMode;                             // TODO type
u8 D_80138F25[3];                        // TODO type
u32 g_KeyOffChannels;                    // TODO type
u8 g_CdCommandResult[54];                // TODO type
u8 D_80138F62[2];                        // TODO unused?
u8 D_80138F64[14];                       // TODO type
u8 D_80138F72;                           // TODO unused?
u8 D_80138F73;                           // TODO unused?
u8 D_80138F74;                           // TODO unused?
u8 D_80138F75;                           // TODO unused?
u8 D_80138F76;                           // TODO unused?
u8 D_80138F77[5];                        // TODO unused?
u32 D_80138F7C;                          // TODO type
u16 D_80138F80[2];                       // TODO type
u32 g_SeqPointers[10];                   // TODO type
u16 g_SfxRingBufferReadPos[2];           // TODO type
u32 g_DebugMode;                         // TODO type
u32 D_80138FB4;                          // TODO type
u16 g_VolL[2];                           // TODO type
u16 D_80138FBC[2];                       // TODO type
u16 g_ButtonCombo;                       // TODO type
u16 D_80138FC2;                          // TODO unused?
u16 D_80138FC4;                          // TODO type
u16 D_80138FC6;                          // TODO unused?
u16 D_80138FC8;                          // TODO type
u16 D_80138FCA;                          // TODO type
u32 D_80138FCC;                          // TODO unused?
u32 D_80138FD0[2];                       // TODO unused?
u32 D_80138FD8[3];                       // TODO unused?
u32 D_80138FE4[5];                       // TODO unused?
u32 D_80138FF8;                          // TODO unused?
u32 D_80138FFC;                          // TODO unused?
u16 g_sfxRingBufferWritePos[2];          // TODO type
u16 g_VolR[2];                           // TODO type
u32 D_80139008;                          // TODO type
u32 g_DebugCurPal;                       // TODO type
u16 D_80139010[2];                       // TODO type
u8 D_80139014[4];                        // TODO type
u8 D_80139018[4];                        // TODO type
u16 D_8013901C[2];                       // TODO type
u8 g_MuteCd[56];                         // TODO type
u8 D_80139058[4];                        // TODO type
u32 g_PrevEquippedWeapons;               // TODO type
u32 D_80139060;                          // TODO type
u16 g_CurrentXaSoundId[28];              // TODO type
u16 g_SeqVolume1[2];                     // TODO type
u8 D_801390A0[4];                        // TODO type
u16 D_801390A4[2];                       // TODO type
u32 D_801390A8;                          // TODO type
u16 D_801390AC[4];                       // TODO type
u32 D_801390B4[4];                       // TODO type
u8 D_801390C4[4];                        // TODO type
u32 D_801390C8;                          // TODO type
u32 D_801390CC[2];                       // TODO type
u32 g_BackBuffer;                        // TODO type
u8 D_801390D8[4];                        // TODO type
u16 g_SfxRingBuffer;                     // TODO type
u16 D_801390DE;                          // TODO type
u16 D_801390E0[766];                     // TODO type
u16 D_801396DC[2];                       // TODO type
u16 D_801396E0[2];                       // TODO type
u16 D_801396E4;                          // TODO type
u16 D_801396E6;                          // TODO type
u16 D_801396E8;                          // TODO type
u16 D_801396EA;                          // TODO type
u16 D_801396EC[2];                       // TODO type
u32 g_CdCommandStatus;                   // TODO type
u16 g_CdSoundCommandQueuePos[2];         // TODO type
u32 D_801396F8[32];                      // TODO type
u32 D_80139778[32];                      // TODO type
u32 D_801397F8;                          // TODO type
u32 D_801397FC;                          // TODO type
u16 D_80139800[2];                       // TODO type
u16 D_80139804[4];                       // TODO type
u32 D_8013980C;                          // TODO type
u8 g_SeqPlayingId[4];                    // TODO type
u16 D_80139814[6];                       // TODO type
u16 g_XaMusicVolume[2];                  // TODO type
u32 D_80139824;                          // TODO type
u32 D_80139828;                          // TODO type
u32 D_8013982C;                          // TODO type
u32 D_80139830;                          // TODO type
u32 D_80139834;                          // TODO unused?
u32 D_80139838;                          // TODO unused?
u32 D_8013983C;                          // TODO type
u32 D_80139840;                          // TODO type
u32 D_80139844;                          // TODO type
u32 D_80139848;                          // TODO type
u32 D_8013984C;                          // TODO type
u32 D_80139850;                          // TODO type
u32 D_80139854[5];                       // TODO type
u16 g_CdSoundCommandQueue[256];          // TODO type
u16 g_SoundCommandRingBufferReadPos[2];  // TODO type
u16 D_80139A6C[2];                       // TODO type
u16 g_SoundCommandRingBufferWritePos[2]; // TODO type
u16 D_80139A74[2];                       // TODO type
u32 D_80139A78;                          // TODO type
u32 D_80139A7C[1280];                    // TODO unused?
u16 D_8013AE7C[2];                       // TODO type
u8 g_CdSoundCommandStep[4];              // TODO type
u16 g_CurrentSfxScriptSfxId[3];          // TODO type
u16 D_8013AE8A;                          // TODO type
u16 g_volumeL[2];                        // TODO type
u32 D_8013AE90;                          // TODO type
u16 D_8013AE94[2];                       // TODO type
u8 g_ReverbDepth[4];                     // TODO type
u32 D_8013AE9C;                          // TODO type
u16 D_8013AEA0[3];                       // TODO type
u16 D_8013AEA6[11];                      // TODO type
u32 D_8013AEBC;                          // TODO type
u16 D_8013AEC0[2];                       // TODO type
u32 D_8013AEC4;                          // TODO type
u32 D_8013AEC8;                          // TODO type
u32 D_8013AECC;                          // TODO type
u32 D_8013AED0;                          // TODO type
u16 D_8013AED4[3];                       // TODO type
u16 D_8013AEDA;                          // TODO unused?
u32 D_8013AEDC;                          // TODO type
u16 D_8013AEE0[2];                       // TODO type
u32 D_8013AEE4;                          // TODO type
u8 D_8013AEE8[4];                        // TODO type
u8 g_SoundInitialized[4];                // TODO type
u16 g_SeqVolume2[2];                     // TODO type
u32 D_8013AEF4;                          // TODO type
u32 g_MemcardInfo[152];                  // TODO type
u32 D_8013B158;                          // TODO type
u32 D_8013B15C;                          // TODO type
u8 D_8013B160[624];                      // TODO type
u32 D_8013B3D0[6];                       // TODO type
u16 g_SoundCommandRingBuffer[256];       // TODO type
u32 D_8013B5E8;                          // TODO type
u8 D_8013B5EC[4];                        // TODO type
u32 g_MemcardBlockRead;                  // TODO type
u8 D_8013B5F4[2];                        // TODO type
u8 D_8013B5F6[6];                        // TODO type
u32 D_8013B5FC;                          // TODO unused?
u16 D_8013B600[10];                      // TODO unused?
u8 g_UnkChannelSetting1[3];              // TODO type
u8 D_8013B617;                           // TODO unused?
u8 D_8013B618[4];                        // TODO type
u32 D_8013B61C;                          // TODO type
u16 g_SfxScriptVolume[3];                // TODO type
u16 D_8013B626;                          // TODO type
u32 g_CurrentSfxScript[3];               // TODO type
u32 D_8013B634[3];                       // TODO unused?
u32 D_8013B640[2];                       // TODO type
u16 D_8013B648[3];                       // TODO type
u16 D_8013B64E;                          // TODO type
u16 D_8013B650[3];                       // TODO type
u16 D_8013B656;                          // TODO unused?
u16 g_SeqAccessNum[2];                   // TODO type
u32 D_8013B65C;                          // TODO type
u32 g_MemcardStep;                       // TODO type
u16 D_8013B664[2];                       // TODO type
u16 g_CdVolume[2];                       // TODO type
u16 g_SfxScriptTimer[3];                 // TODO type
u16 D_8013B672[3];                       // TODO type
u16 D_8013B678[3];                       // TODO type
u16 D_8013B67E;                          // TODO type
u8 D_8013B680[4];                        // TODO type
u8 g_CdSoundCommand16[4];                // TODO type
u8 D_8013B688[8];                        // TODO type
u8 D_8013B690[4];                        // TODO type
u32 D_8013B694;                          // TODO type
u16 g_volumeR[2];                        // TODO type
u32 D_8013B69C;                          // TODO type
#if defined(VERSION_HD)
u32 D_8013B6A0; // TODO type
#endif
