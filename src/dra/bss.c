#include "common.h"

u32 g_DebugFreeze;
u32 g_DebugHitboxViewMode;
u32 D_801362B4;
u32 D_801362B8;
u32 D_801362BC;
u32 g_DebugPalIdx;
u32 g_DebugColorChannel;
u32 D_801362C8;
u32 g_CurrentOT;
u32 D_801362D0;
u32 D_801362D4;
u32 g_DebugIsRecordingVideo;
u32 g_GpuMaxUsage;
u32 D_80135EBC; // unused?
u32 D_80135EC0; // unused?
u32 D_80135EC4; // unused?
u32 D_80135EC8; // unused?
u32 D_80135ECC; // unused?
u32 D_80135ED0; // unused?
u32 D_80135ED4; // unused?
u32 D_80135ED8; // unused?
u32 g_DebugWaitInfoTimer;
u32 g_DebugRecordVideoFid;
u16 D_80136308[128];
#if defined(VERSION_US)
u32 g_softResetTimer;
#endif
u32 D_8013640C;
u32 D_80136410;
u32 g_NowLoadingModel[14];
u32 g_SimFile;
u32 D_80136450[4];
u16 D_80136460[1024];
u16 D_80136C60[1024];
u8 g_PadsRepeatTimer[16];
u32 g_MemcardRetryCount;
u32 g_MemcardFd;
u16 D_80137478[32];
u16 D_801374B8[32];
u16 D_801374F8[32];
u16 D_80137538[32];
u32 g_DecSrcPtr;
u32 g_DecDstPtr;
u32 g_DecReadNibbleFlag;
u32 g_DecWriteNibbleFlag[3];
u32 D_80137590;
u32 D_80137594;
u32 D_80137598;
u32 D_8013759C;
u32 D_801375A0;
u16 D_801375A4;
u16 D_801375A6;
u16 D_801375A8;
u16 D_801375AA;
u32 D_801375AC;
u32 D_801375B0;
u32 D_801375B4;
u32 D_801375B8;
u32 D_801375BC;
u32 D_801375C0;
u32 D_801375C4;
u32 D_801375C8;
u32 D_801375CC;
u32 D_801375D0;
u32 D_801375D4;
u32 D_801375D8;
u32 D_801375DC;
u32 D_801375E0[7];
u32 D_801375FC;
u32 g_IsCloakLiningUnlocked;
u32 g_IsCloakColorUnlocked;
u32 D_80137608;
u32 g_IsSelectingEquipment;
u32 g_EquipmentCursor;
u32 D_80137614;
u32 g_EquipOrderType;
u16 g_MenuData[12];
u16 D_80137634[2]; // unused
u8 D_80137638;
u8 D_80137639;     // unused
u8 D_8013763A[60]; // unused
u16 D_80137676;    // unused
u16 D_80137678[2]; // unused
u16 D_8013767C[6];
u16 D_80137688[2];
u16 D_80137692[18]; // unused
u8 D_801376B0[20];
u16 D_801376C4[2];
u16 D_801376C8[19];
u16 g_JosephsCloakContext[135];
u32 D_801377FC[16];
u32 D_8013783C;
u32 D_80137840;
u32 D_80137844;
u32 D_80137848;
#if defined(VERSION_US)
u32 D_8013784C;
#endif
u32 g_RelicMenuFadeTimer;
u32 g_TimeAttackEntryTimes[27];
u32 c_strTimeAttackEntry[27];
u32 g_NewAttackRightHand;
u32 g_NewAttackLeftHand;
u32 g_NewDefenseEquip;
u32 g_NewPlayerStatsTotal[4];
u32 D_80137948;
u32 D_8013794C;
u32 D_80137950;
u32 D_80137954;
u32 D_80137958;
u32 g_ServantPrevious;
u32 D_80137960;
u32 D_80137964;
u32 D_80137968;
u32 g_PlayerHud;
u32 D_80137970;
u32 D_80137974;
u32 D_80137978;
u32 D_8013797C;
u32 D_80137980;
u32 D_80137984;
u32 D_80137988;
u32 D_8013798C;
u32 D_80137990;
u32 D_80137994;
u32 g_HealingMailTimer;
u32 D_8013799C;
u32 D_801379A0;
u32 D_801379A4;
u32 D_801379A8;
u16 D_801379AC;
u16 D_801379AE; // unused
u32 D_801379B0;
u16 D_801379B4[2]; // unused
u32 D_801379B8;
u32 D_801379BC;
u16 D_801379C0;
u16 D_801379C2; // unused?
u16 D_801379C4[2];
u16 D_801379C8;
u16 D_801379CA;    // unused?
u16 D_801379CC[2]; // unused?
u32 D_801379D0;
u32 D_801379D4;    // unused?
u32 D_801379D8[2]; // unused?
u32 D_801379E0[80];
u32 D_80137B20[96];
u32 D_80137CA0[40];
u32 D_80137D40[48];
u32 D_80137E00[8];
u32 D_80137E20[8];
u32 D_80137E40;
u32 D_80137E44;
u32 D_80137E48;
u32 D_80137E4C;
u32 g_MemCardRetryCount;
u32 D_80137E54;
u32 D_80137E58;
u32 D_80137E5C;
u32 D_80137E60;
u32 g_MemCardRStep;
u32 g_MemCardRStepSub;
u32 D_80137E6C;
u16 D_80137E70;
u16 D_80137E72;    // unused?
u16 D_80137E74;    // unused?
u16 D_80137E76;    // unused?
u32 D_80137E78[2]; // unused?
u32 D_80137E80[2]; // unused?
u32 D_80137E88[2]; // unused?
u32 D_80137E90[2]; // unused?
u32 D_80137E98[2]; // unused?
u32 D_80137EA0[2]; // unused?
u32 D_80137EA8[2]; // unused?
u32 D_80137EB0[2]; // unused?
u32 D_80137EB8[2]; // unused?
u32 D_80137EC0[2]; // unused?
u32 D_80137EC8[2]; // unused?
u32 D_80137ED0[2]; // unused?
u32 D_80137ED8[2]; // unused?
u32 D_80137EE0;
u32 D_80137EE4;
u32 D_80137EE8;
u32 D_80137EEC;
u32 D_80137EF0;
u32 D_80137EF4;
u32 D_80137EF8[24];
u32 g_CdCallback;
u32 g_CdLoc;
u16 g_Cd;
u16 D_80137F62;      // unused?
u16 D_80137F64;      // unused?
u16 D_80137F66;      // unused?
u32 g_Cd_D_80137F68; // unused?
u32 D_80137F6C;
u32 g_Cd_D_80137F70;           // unused?
u32 g_Cd_D_80137F74;           // unused?
u32 g_Cd_D_80137F78;           // unused?
u32 g_Cd_D_80137F7C;           // unused?
u32 g_Cd_overlayCopySrc;       // unused?
u32 g_Cd_overlayCopyDst;       // unused?
u32 g_Cd_addr;                 // unused?
u32 g_Cd_overlayBlockCount;    // unused?
u32 g_Cd_overlayLastBlockSize; // unused?
u8 g_VabId[2];                 // unused?
u8 D_80137F96[6];              // unused?
u32 D_80137F9C;
u32 D_80137FA0[2];
u16 D_80137FA8[2];
u32 D_80137FAC;
u32 D_80137FB0;
u32 D_80137FB4;
u32 D_80137FB8;
#if defined(VERSION_US)
u32 D_80137FBC;
#endif
u16 g_WasFacingLeft[2];
u16 g_WasFacingLeft2[2];
u32 g_WasFacingLeft3;
u32 g_WasFacingLeft4;
u16 g_WasFacingLeft5[2];
u32 g_WasFacingLeft6;
u32 g_WasFacingLeft7;
#if defined(VERSION_US)
u32 D_80137FDC;
#endif
u32 D_80137FE0;
u32 D_80137FE4;
u32 D_80137FE8;
u32 D_80137FEC;
u32 D_80137FF0;
u32 g_WingSmashButtonCounter;
u32 g_WingSmashButtonTimer;
u32 g_WingSmashTimer;
u32 g_BatScreechDone;
u32 g_MistTimer;
u32 D_80138008;
u32 D_8013800C;
u32 D_80138010;
u32 D_80138014;
u32 D_80138018[8];
u32 D_80138038;
u8 D_8013803C[4];
u8 D_80138040[4];
u8 D_80138044[4];
u8 D_80138048[4];
u16 D_8013804C;
u16 D_8013804E[31]; // unused?
u32 D_8013808C;
u32 D_80138090;
u16 D_80138094;
u16 D_80138096[2];  // unused?
u16 D_8013809A;     // unused?
u32 D_8013809C;     // unused?
u32 D_801380A0;     // unused?
u32 D_801380A4[76]; // unused?
u32 D_801381D4;
u32 D_801381D8;
u32 D_801381DC;
u32 D_801381E0;
u32 D_801381E4;
u32 D_801381E8;
u32 D_801381EC;
u32 D_801381F0;
u8 D_801381F4[416];
u32 D_80138394;
u32 D_80138398;
u16 D_8013839C;
u16 D_8013839E[63]; // unused?
u32 D_8013841C;
u32 D_80138420; // unused?
u16 D_80138424;
u16 D_80138426; // unused?
u16 D_80138428; // unused?
u16 D_8013842A; // unused?
u32 D_8013842C;
u32 D_80138430[2];
u32 D_80138438;
u32 D_8013843C;
u32 D_80138440;
u32 D_80138444;
u32 D_80138448;
u32 D_8013844C;
u32 D_80138450;
u32 D_80138454;
u32 g_CurrentXaConfigId;
u32 D_8013845C;
u32 g_SeqTable[201];
u32 D_80138784[487];
u32 g_CurCdPos;
u8 g_CdMode;
u8 D_80138F25[3];
u32 g_KeyOffChannels;
u8 g_CdCommandResult[54];
u8 D_80138F62[2]; // unused?
u8 D_80138F64[14];
u8 D_80138F72;    // unused?
u8 D_80138F73;    // unused?
u8 D_80138F74;    // unused?
u8 D_80138F75;    // unused?
u8 D_80138F76;    // unused?
u8 D_80138F77[5]; // unused?
u32 D_80138F7C;
u16 D_80138F80[2];
u32 g_SeqPointers[10];
u16 g_SfxRingBufferReadPos[2];
u32 g_DebugMode;
u32 D_80138FB4;
u16 g_VolL[2];
u16 D_80138FBC[2];
u16 g_ButtonCombo;
u16 D_80138FC2; // unused?
u16 D_80138FC4;
u16 D_80138FC6; // unused?
u16 D_80138FC8;
u16 D_80138FCA;
u32 D_80138FCC;    // unused?
u32 D_80138FD0[2]; // unused?
u32 D_80138FD8[3]; // unused?
u32 D_80138FE4[5]; // unused?
u32 D_80138FF8;    // unused?
u32 D_80138FFC;    // unused?
u16 g_sfxRingBufferWritePos[2];
u16 g_VolR[2];
u32 D_80139008;
u32 g_DebugCurPal;
u16 D_80139010[2];
u8 D_80139014[4];
u8 D_80139018[4];
u16 D_8013901C[2];
u8 g_MuteCd[56];
u8 D_80139058[4];
u32 g_PrevEquippedWeapons;
u32 D_80139060;
u16 g_CurrentXaSoundId[28];
u16 g_SeqVolume1[2];
u8 D_801390A0[4];
u16 D_801390A4[2];
u32 D_801390A8;
u16 D_801390AC[4];
u32 D_801390B4[4];
u8 D_801390C4[4];
u32 D_801390C8;
u32 D_801390CC[2];
u32 g_BackBuffer;
u8 D_801390D8[4];
u16 g_SfxRingBuffer;
u16 D_801390DE;
u16 D_801390E0[766];
u16 D_801396DC[2];
u16 D_801396E0[2];
u16 D_801396E4;
u16 D_801396E6;
u16 D_801396E8;
u16 D_801396EA;
u16 D_801396EC[2];
u32 g_CdCommandStatus;
u16 g_CdSoundCommandQueuePos[2];
u32 D_801396F8[32];
u32 D_80139778[32];
u32 D_801397F8;
u32 D_801397FC;
u16 D_80139800[2];
u16 D_80139804[4];
u32 D_8013980C;
u8 g_SeqPlayingId[4];
u16 D_80139814[6];
u16 g_XaMusicVolume[2];
u32 D_80139824;
u32 D_80139828;
u32 D_8013982C;
u32 D_80139830;
u32 D_80139834; // unused?
u32 D_80139838; // unused?
u32 D_8013983C;
u32 D_80139840;
u32 D_80139844;
u32 D_80139848;
u32 D_8013984C;
u32 D_80139850;
u32 D_80139854[5];
u16 g_CdSoundCommandQueue[256];
u16 g_SoundCommandRingBufferReadPos[2];
u16 D_80139A6C[2];
u16 g_SoundCommandRingBufferWritePos[2];
u16 D_80139A74[2];
u32 D_80139A78;
u32 D_80139A7C[1280]; // unused?
u16 D_8013AE7C[2];
u8 g_CdSoundCommandStep[4];
u16 g_CurrentSfxScriptSfxId[3];
u16 D_8013AE8A;
u16 g_volumeL[2];
u32 D_8013AE90;
u16 D_8013AE94[2];
u8 g_ReverbDepth[4];
u32 D_8013AE9C;
u16 D_8013AEA0[3];
u16 D_8013AEA6[11];
u32 D_8013AEBC;
u16 D_8013AEC0[2];
u32 D_8013AEC4;
u32 D_8013AEC8;
u32 D_8013AECC;
u32 D_8013AED0;
u16 D_8013AED4[3];
u16 D_8013AEDA; // unused?
u32 D_8013AEDC;
u16 D_8013AEE0[2];
u32 D_8013AEE4;
u8 D_8013AEE8[4];
u8 g_SoundInitialized[4];
u16 g_SeqVolume2[2];
u32 D_8013AEF4;
u32 g_MemcardInfo[152];
u32 D_8013B158;
u32 D_8013B15C;
u8 D_8013B160[624];
u32 D_8013B3D0[6];
u16 g_SoundCommandRingBuffer[256];
u32 D_8013B5E8;
u8 D_8013B5EC[4];
u32 g_MemcardBlockRead;
u8 D_8013B5F4[2];
u8 D_8013B5F6[6];
u32 D_8013B5FC;     // unused?
u16 D_8013B600[10]; // unused?
u8 g_UnkChannelSetting1[3];
u8 D_8013B617; // unused?
u8 D_8013B618[4];
u32 D_8013B61C;
u16 g_SfxScriptVolume[3];
u16 D_8013B626;
u32 g_CurrentSfxScript[3];
u32 D_8013B634[3]; // unused?
u32 D_8013B640[2];
u16 D_8013B648[3];
u16 D_8013B64E;
u16 D_8013B650[3];
u16 D_8013B656; // unused?
u16 g_SeqAccessNum[2];
u32 D_8013B65C;
u32 g_MemcardStep;
u16 D_8013B664[2];
u16 g_CdVolume[2];
u16 g_SfxScriptTimer[3];
u16 D_8013B672[3];
u16 D_8013B678[3];
u16 D_8013B67E;
u8 D_8013B680[4];
u8 g_CdSoundCommand16[4];
u8 D_8013B688[8];
u8 D_8013B690[4];
u32 D_8013B694;
u16 g_volumeR[2];
u32 D_8013B69C;
#if defined(VERSION_HD)
u32 D_8013B6A0;
#endif
