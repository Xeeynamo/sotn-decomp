#include "dra.h"

// BSS shared
extern s32 D_8013640C;
extern s32 D_80136410;
extern s32 g_MemcardRetryCount;
extern s32 g_MemcardFd;

// BSS PC shared
extern SimFile* g_SimFile;
extern s16 D_80136460[VSYNC_UNK_LEN];
extern s16 D_80136C60[VSYNC_UNK_LEN];
extern u8* g_DemoPtr;

// BSS TODO 5D5BC.c, 627C4.c
extern u32 D_8013799C;
extern s32 D_801379A0;
extern s32 D_801379A4;
extern s32 D_801379A8;

// BSS shared between 627C4.c and 63ED4.c
extern Unkstruct_80102CD8 D_801379AC;
extern s32 D_801379B8;
extern s32 D_801379BC;
extern SVECTOR D_801379C0;
extern SVECTOR D_801379C8;
extern VECTOR D_801379D0;
extern VECTOR D_801379E0[20];
extern VECTOR D_80137B20[24];
extern SVECTOR D_80137CA0[20];
extern SVECTOR D_80137D40[24];
extern MATRIX D_80137E00;
extern MATRIX D_80137E20;
extern s32 D_80137E40;
extern s32 D_80137E44;
extern s32 D_80137E48;
extern s32 D_80137E4C;
extern s32 g_MemCardRetryCount;
extern s32 D_80137E54;
extern s32 D_80137E58;
extern s32 D_80137E5C;
extern s32 D_80137E60;
extern s32 g_MemCardRStep;
extern s32 g_MemCardRStepSub;
extern s32 D_80137E6C;
extern SVECTOR D_80137E70[14];
extern s32 D_80137EE0;
extern s32 D_80137EE4;
extern s32 D_80137EE8;
extern s32 D_80137EEC;
extern s32 D_80137EF0;
extern s32 D_80137EF4;

// BSS TODO merge? 6D59C.c, 704D0.c
extern s16 g_WasFacingLeft;  // for QCF to tell what's "forward"
extern s16 g_WasFacingLeft2; // for BF to tell what's "forward"
extern s32 g_WasFacingLeft3; // for dark metamorphosis "" ""
extern s32 g_WasFacingLeft4; // for summon spirit "" ""
extern s16 g_WasFacingLeft5; // for hellfire "" ""
extern s32 g_WasFacingLeft6; // for tetra spirit "" ""
extern s32 g_WasFacingLeft7; // for soul steal "" ""

// BSS TODO merge? 72BB0.c, 75F54.c
extern s32 D_80137FE0;
extern s32 D_80137FE4;
extern s32 D_80137FE8;
extern s32 D_80137FEC;
extern s32 D_80137FF0;

// BSS 75F54.c, 7A4D0.c
extern s32 D_8013800C[11];
extern u8 D_8013803C;
extern u8 D_80138040;
extern u8 D_80138044;
extern u8 D_80138048;

// BSS 8A0A4.c, 8D3E8.c
extern s32 D_8013842C;
extern s32 D_80138430;
extern s32 D_80138438;
extern s32 D_8013843C;
extern s32 D_80138440;
extern s32 D_80138444;

// BSS 91EBC.c, 92F60.c, 93290.c, 93BDC.c, 94F50.c, 953A0.c
extern s16 g_CurrentXaConfigId;
extern s16 D_8013845C;
extern u8 g_SeqTable[];
extern u_long* D_80138784[]; // 487?
extern s32 g_CurCdPos;
extern u8 g_CdMode[];
extern s32 g_KeyOffChannels;
extern u8 g_CdCommandResult[8];
extern s8 g_KeyStatus[SPU_VOICE_NUM];
extern s32 D_80138F7C;
extern s16 D_80138F80;
extern s32 g_SeqPointers[10];
extern s16 g_SfxRingBufferReadPos;
extern DebugMode g_DebugMode;
extern s16 g_VolL; // vol_l
extern SpuVoiceAttr* D_80138FB4;
extern s16 D_80138FBC;
extern SpuVoiceAttr* D_801390C8;
extern SpuVoiceAttr* D_801390CC;
extern ButtonComboState g_ButtonCombo[COMBO_NUM];
extern s16 g_sfxRingBufferWritePos; // D_80139000
extern s16 g_VolR;                  // vol_r
extern s32 D_80139008;
extern s16 g_CurSfxDistance20_21;
extern u8 D_80139014;
extern s8 g_SfxScriptModeCopy[4];
extern u32 g_DebugCurPal;
extern s16 D_8013901C;
extern u8 g_MuteCd;
extern s8 g_SfxScriptDistanceCopy[4];
extern s32 g_PrevEquippedWeapons[2];
extern s16 g_CurrentXaSoundId;
extern s16 g_SeqVolume1;
extern u8 D_801390A0;
extern s16 g_CurSfxVol20_21;
extern u8 D_801390A8;
extern s16 g_SfxScriptVolumeCopy[];
extern s32 D_801390B4[];
extern u8 g_SeqIsPlaying;
extern GpuBuffer* g_BackBuffer;
extern u8 D_801390D8;
extern SfxRingBufferItem g_SfxRingBuffer[MAX_SND_COUNT];
extern s16 g_CurSfxDistance12_19;
extern s16 D_801396E0;
extern u16 D_801396E4;
extern u16 D_801396E6;
extern u16 D_801396E8;
extern s16 D_801396EA;
extern u16 D_801396EC;
extern s32 g_CdCommandStatus;
extern volatile s16 g_CdSoundCommandQueuePos;
extern s32 D_801396F8[32];
extern s32 D_80139778[32];
extern u16 g_CurSfxVol12_19;
extern s32 D_801397FC;
extern s16 D_80139800;
extern s16 g_CurSfxId22_23;
extern s32 D_8013980C;
extern u8 g_SeqPlayingId;
extern s16 g_SfxScriptTimerCopy[];
extern s16 g_XaMusicVolume;
extern s32 D_80139824;
extern s32 D_80139828[16];
extern s32 D_8013983C;
extern s32 D_80139840;
extern s32 D_80139844;
extern s32 D_80139848;
extern s32 D_8013984C;
extern s32 D_80139850;
extern s32 D_80139854;
extern s16 g_CdSoundCommandQueue[MAX_SND_COUNT];
extern s16 g_SoundCommandRingBufferReadPos;
extern s16 g_XaVolumeMultiplier;
extern s16 g_SoundCommandRingBufferWritePos; // D_80139A70
extern s16 D_80139A74;
extern s16 g_XaFadeCounter;
extern u16 D_80139A7C[32 * 80]; // size from D_800AE130, D_800AE138
extern u16 g_SfxVolumeMultiplier;
extern volatile u8 g_CdSoundCommandStep;
extern s16 g_CurrentSfxScriptSfxId[4];
extern s16 D_8013AE8C;
extern s16 g_SfxScriptUnk6[4];
extern s16 D_8013AEA6;
extern s16 g_CurSfxDistance22_23;
extern u8 g_ReverbDepth;
extern s32 D_8013AE9C;
extern s32 D_8013AEBC[4];
extern s32 D_8013AECC;
extern s32 D_8013AED0;
extern s16 D_8013AED4[4];
extern u8 D_8013AEDC;
extern s32 D_8013AEE4;
extern s16 g_volumeL;
extern s32 D_8013AE90;
extern s16 g_volumeR;
extern s16 g_CurrentSfxScriptSfxId2[4];
extern s16 g_CurrentSfxId12_19[4];
extern s16 g_CurrentSfxScriptSfxIdCopy[4];
extern s16 D_8013B698;
extern u8 D_8013B6A0[269488]; // VAB file
extern u8 D_8017D350[57744];  // VAB file
extern u8 D_8018B4E0[108048]; // VAB file
extern u8 D_801A9C80[64496];  // VAB file
extern u16 g_CurSfxVol22_23;
extern s8 D_8013AEE8;
extern u8 g_SoundInitialized;
extern s16 g_SeqVolume2;
extern s32 D_8013AEF4;
extern s32 D_8013B158;
extern s32 D_8013B3D0;
extern s16 g_SoundCommandRingBuffer[MAX_SND_COUNT]; // D_8013B3E8
extern s32 D_8013B5E8;
extern u8 g_SfxScriptMode[4];
extern u8 D_8013B5F6[];
extern s8 g_SfxScriptDistance[4];
extern s8 D_8013B618;
extern s32 D_8013B61C;
extern u16 g_SfxScriptVolume[4];
extern u16 D_8013B626;
extern s8* g_CurrentSfxScript[4];
extern CdlLOC D_8013B640;
extern s16 g_CurrentSfxId12_19[4];
extern s32 D_8013B65C;
extern s16 g_SeqAccessNum;
extern s32 g_MemcardStep;
extern s16 g_CurSfxId20_21;
extern s16 g_CdVolume;
extern s16 g_SfxScriptTimer[4];
extern u8 D_8013B680;
extern u8 g_CdSoundCommand16;
extern s8 D_8013B690;
extern s32 D_8013B694;
extern s32 D_8013B69C;
extern ServantDesc D_80170000;
extern Weapon D_8017A000;
extern Weapon D_8017D000;
extern ImgSrc* g_imgUnk8013C200;
extern ImgSrc* g_imgUnk8013C270;
extern u8 D_8013B688[8];
extern struct Cmd14 D_8013B5F4[2];
extern u8 D_801EC000[];
