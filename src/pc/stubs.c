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
Primitive g_PrimBuf[MAX_PRIM_COUNT];
FgLayer D_8003C708;
s16 D_8003C710;
s16 D_8003C712;
s32 D_8003C728;
s32 D_8003C730;
s32 D_8003C8B8;
s32 g_IsUsingCd;
Entity* g_CurrentEntity;
GpuUsage g_GpuUsage;
PlayerStatus g_Status;
u32 g_randomNext;
s32 playerX;
s32 playerY;
PlayerState g_Player;
u32 g_GameTimer;
GpuBuffer g_GpuBuffers[2];
s16 g_GpuBuffers_1_buf_draw_clip_y; // member of D_800542FC, TODO
                                    // overlap, hard to remove
GpuBuffer* g_CurrentBuffer;
u32 D_8003C9A4;
s32 D_8003C0F8;
s32 D_800973EC;
s32 D_8003C704;
s32 D_800973EC;
s32 D_8003C73C;
s32 D_8003C99C;
s32 g_PlayableCharacter;
s32 g_backbufferX;
s32 g_backbufferY;
u32 g_Timer;
s32 D_80097904;
s32 D_80097908;
s32 D_8009790C;
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
SVECTOR* D_800A3210[1];
SVECTOR* D_800A33A0[1];
SVECTOR* D_800A34C0[18][3];
SVECTOR* D_800A3598[1];
SVECTOR* D_800A35D0[1];
SVECTOR* D_800A3608[1];
u8 D_800A3728;
MATRIX D_800A37B8;
u8 D_800B0608[0xC0]; // size guessed
s16 D_80136308[1];
u16 g_Clut[0x3000];
u32 D_8006EBCC;
u16 D_8006EBE0;
s32 D_8006C384;
s32 D_8006C388;
MenuNavigation g_MenuNavigation;
GameSettings g_Settings;
s32 D_8006C384;
s32 D_8006C388;
s32 D_8006C38C;
s32 D_8006C390;
u16 D_8003C104[0x400];
s32 D_8003C738;
u8 g_CastleFlags[0x300];
s32 D_8006C374;
s32 D_8006C378;
u16 D_8003C3C2[1];
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
s32 D_80073074;
u16 D_800734C0;
Event g_EvSwCardNew;
s32 D_8007307C;
s32 D_80073080;
s32 g_IsTimeAttackUnlocked;
Unkstruct_8003C908 D_8003C908;
s32 D_8003C100;
s32 D_800978B4;
u32 g_RoomCount;
char D_80097902[] = "dummy";
s32 D_8003C90C[2] = {0};
MemcardInfo g_MemcardInfo[2];
s32 g_MemcardBlockRead;
s32 g_MemcardStep;
s32 g_MemcardRetryCount;
s32 g_MemcardFd;
u8 g_SaveName[12];
Tilemap g_Tilemap;
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
s32 D_8013AED0;
DR_ENV D_800974AC[16];
u32 D_8003C744 = 0;
s32 D_800973F8;
s32 D_800973FC;
s32 D_80097400[18];
s32 D_8009740C[3];
s32 g_BottomCornerTextTimer;
s32 g_BottomCornerTextPrims;
s32 D_80097418;
s32 D_8009741C[1];
s32 D_80097420[1];
s32 D_80097424;
s32 D_80097448[2];
s32 D_80097450;
Pos D_80097488;
PixPattern* mocked_800C52F8[0x200] = {NULL};
PixPattern* D_800C52F8[] = {
    mocked_800C52F8, mocked_800C52F8, mocked_800C52F8, mocked_800C52F8,
    mocked_800C52F8, mocked_800C52F8, mocked_800C52F8, mocked_800C52F8,
    mocked_800C52F8, mocked_800C52F8, mocked_800C52F8, mocked_800C52F8,
    mocked_800C52F8, mocked_800C52F8, mocked_800C52F8, mocked_800C52F8,
    mocked_800C52F8, mocked_800C52F8, mocked_800C52F8, mocked_800C52F8,
    mocked_800C52F8, mocked_800C52F8, mocked_800C52F8, mocked_800C52F8,
    mocked_800C52F8, mocked_800C52F8, mocked_800C52F8, mocked_800C52F8,
    mocked_800C52F8, mocked_800C52F8, mocked_800C52F8, mocked_800C52F8,
};

// dra.h
u16 D_800AC958[] = {
    0x0200, 0x0220, 0x0200, 0x0220, 0x0240, 0x0260, 0x0240, 0x0260,
    0x0280, 0x02A0, 0x0280, 0x02A0, 0x02C0, 0x02E0, 0x02C0, 0x02E0,
    0x0300, 0x0320, 0x0300, 0x0320, 0x0340, 0x0360, 0x0340, 0x0360,
    0x0380, 0x03A0, 0x0380, 0x03A0, 0x03C0, 0x03E0, 0x03C0, 0x03E0,
};
s16 D_800AC998[] = {
    0x0200, 0x0220, 0x0200, 0x0220, 0x0240, 0x0260, 0x0240, 0x0260,
    0x0280, 0x02A0, 0x0280, 0x02A0, 0x02C0, 0x02E0, 0x02C0, 0x02E0,
    0x0300, 0x0320, 0x0300, 0x0320, 0x0340, 0x0360, 0x0340, 0x0360,
    0x0380, 0x03A0, 0x0380, 0x03A0, 0x03C0, 0x03E0, 0x03C0, 0x03E0,
};
Unkstruct_801092E8 D_800A37D8;
s32 D_800ACDF8;
s32 D_800ACDFC;
s32 D_800ACE00[8];
s32 D_800ACE44;
s32 D_800ACE48[12]; // size guessed
RECT D_800ACE60;
s16_pair D_800ACEC0[4];
Unkstruct_800ACED0 D_800ACED0;
u8 D_800ACF4C[0x200];                 // random size just to play safe
u8 D_800ACF54[0x200];                 // random size just to play safe
s32 D_800ACF74;                       // These two might...
s32 D_800ACF78;                       // ...be an array
unkstruct_800ACF7C D_800ACF7C[0x200]; // random size just to play safe
s16 D_800ACF60[6];                    // guessed size
s16 D_800ACF6C[4];                    // guessed size
s16 D_800ACF8A[5];                    // guessed size
s16 D_800ACF94[16];                   // guessed size
u8 D_800AD094[0x30];
GpuUsage g_GpuMaxUsage;
GpuBuffer* g_BackBuffer;
s32 g_DebugFreeze;
s32 g_DebugHitboxViewMode;
u32 D_801362B4;
u32 g_DebugCurPal;
s32 D_801362D4;
s32 D_8013640C;
s32 D_800974A4;
u32* g_CurrentOT;
s32 D_801362B8;
s32 D_801362BC;
s32 g_DebugPlayer;
Vram g_Vram;
s32 g_softResetTimer;
DebugMode g_DebugMode;
s32 g_DebugPalIdx;
DebugColorChannel g_DebugColorChannel;
u32 D_801362C8;
s32 g_DebugIsRecordingVideo;
s32 g_DebugWaitInfoTimer;
s32 g_DebugRecordVideoFid;
u8 D_8013B6A0[269488] = {0}; // VB file
u8 D_8017D350[57744] = {0};  // VB file
u8 D_8018B4E0[64496] = {0};  // VB file
u8 D_801A9C80[108048] = {0}; // VB file
u8 aPbav[0x3000] = {0};      // VH file
u8 aPbav_0[0x2000] = {0};    // VH file
u8 aPbav_1[0x2000] = {0};    // VH file
u8 aPbav_2[0x2000] = {0};    // VH file
u8 aPqes[] = {0};            // SEQ file
u8 aPqes_0[] = {0};          // SEQ file
u8 aPqes_1[] = {0};          // SEQ file
s32 D_801362D0[1];
s32 D_800987B4;
u8 g_PadsRepeatTimer[BUTTON_COUNT * PAD_COUNT];
s32 D_80136410;
NowLoadingModel g_NowLoadingModel;
ItemTypes D_801375CC;
s32 D_801375D0;
s32 D_801375D4;
s32* D_801375D8;
s32 D_801375DC;
s32 D_801375E0[NUM_FAMILIARS + 1];
s32 D_80137608;
s32 g_IsCloakLiningUnlocked;
s32 g_IsCloakColorUnlocked;
s32 g_IsSelectingEquipment;
s32 g_EquipmentCursor;
s32 D_80137614;
s32 g_EquipOrderType;
MenuData g_MenuData = {0};
u8 D_801376B0;
s16 D_801376C4;
s16 D_801376C8;
MenuContext g_JosephsCloakContext;
s32 D_8013783C;
s32 D_801377FC[0x10];
s32 D_80137840;
s32 D_80137844[1];
s32 D_80137848[1];
s32 D_8013784C;
s16 g_RelicMenuFadeTimer;
s32 g_TimeAttackEntryTimes[1];
s32 c_strTimeAttackEntry[1];
s32 c_strTimeAttackGoals[1];
s32 g_NewAttackRightHand;
s32 g_NewAttackLeftHand;
s32 g_NewDefenseEquip;
s32 g_NewPlayerStatsTotal[1];
s32 D_80137948;
s8* D_8013794C; // Pointer to texture pattern
s32 D_80137950;
s32 D_80137954;
s32 D_80137958;
s32 g_ServantPrevious;
s32 D_80137960;
s32 D_80137964;
s32 D_80137968;
s32 D_801379B8;
s32 D_801379BC;
VECTOR D_801379E0;
VECTOR D_80137B20;
SVECTOR D_80137CA0;
SVECTOR D_80137D40;
SVECTOR D_80137E70[1];
s32 D_80137EE0;
s32 D_80137EE4;
s32 D_80137EE8;
s32 D_80137EEC;
s32 D_80137EF0;
s32 D_80137EF4;
s32 D_80139824;
s32 D_80139828[0x10];
s32 D_8013982C;
s32 D_80139830[3];
s32 D_8013983C;
s32 D_80139840;
s32 D_80139844;
s32 D_80139848;
s32 D_8013984C;
s32 D_80139850;
s32 D_80139854;
u16 D_80137538[32];
GfxBank* g_FakeGfxBank = {NULL};
GfxBank** g_GfxSharedBank[] = {
    &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank,
    &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank,
    &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank,
    &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank,
    &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank,
    &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank,
    &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank,
    &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank,
    &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank,
    &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank,
    &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank,
    &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank,
    &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank,
    &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank,
    &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank,
    &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank,
};
u8* g_DecSrcPtr = NULL;
u8* g_DecDstPtr = NULL;
s32 g_DecReadNibbleFlag = 0;
s32 g_DecWriteNibbleFlag = 0;
u8 g_GfxEquipIcon[320][16 * 16 / 2];
s16 g_PalEquipIcon[320 * 16];
u_long g_FakeUnkStruct = {MAKE_PAL_OP(0, 0)};
u_long* D_800A3BB8[] = {
    &g_FakeUnkStruct, &g_FakeUnkStruct, &g_FakeUnkStruct, &g_FakeUnkStruct,
    &g_FakeUnkStruct, &g_FakeUnkStruct, &g_FakeUnkStruct, &g_FakeUnkStruct,
    &g_FakeUnkStruct, &g_FakeUnkStruct, &g_FakeUnkStruct, &g_FakeUnkStruct,
    &g_FakeUnkStruct, &g_FakeUnkStruct, &g_FakeUnkStruct, &g_FakeUnkStruct,
    &g_FakeUnkStruct, &g_FakeUnkStruct, &g_FakeUnkStruct, &g_FakeUnkStruct,
    &g_FakeUnkStruct, &g_FakeUnkStruct, &g_FakeUnkStruct, &g_FakeUnkStruct,
    &g_FakeUnkStruct, &g_FakeUnkStruct, &g_FakeUnkStruct, &g_FakeUnkStruct,
    &g_FakeUnkStruct, &g_FakeUnkStruct, &g_FakeUnkStruct, &g_FakeUnkStruct,
    &g_FakeUnkStruct, &g_FakeUnkStruct,
};
u16 D_80137478[0x20];
u16 D_801374B8[0x20];
u16 D_801374F8[0x20];
u16 D_80137538[0x20];
u32 g_DisplayHP[1];
s32 D_80137970;
s32 D_80137974;
u32 D_80137978;
u32 D_8013797C;
s32 D_80137980;
s32 D_80137984;
u32 D_80137988;
u32 D_8013798C;
Unkstruct_80137990 D_80137990;
s32 D_8013B5E8;
s32 g_HealingMailTimer[1] = {0};
s32 D_8013B5E8;
s32 D_80137994;
s32 D_80139008;
s32 D_801397FC;
SimFile* g_SimFile;
SimFile D_80136450;
s16 D_80136460[0x400];
s16 D_80136C60[0x400];

JosephsCloak g_JosephsCloak;
u8 g_Pix[4][128 * 128 / 2];
ImgSrc g_imgUnk8013C200_impl = {
    0,
    0,
    0,
};
ImgSrc* g_imgUnk8013C200 = &g_imgUnk8013C200_impl;
ImgSrc* g_imgUnk8013C270 = &g_imgUnk8013C200_impl;
s32 g_PrevEquippedWeapons[2];
s32 D_8013AEE4;
s32 D_800A3194[1];
s32 D_80139060;
u32 D_8013799C;
s32 D_801379A0;
s32 D_801379A4;
s32 D_801379A8;
Unkstruct_80102CD8 D_801379AC;
s32 D_801379B0;
SVECTOR D_801379C8;
VECTOR D_801379D0;
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
s32 D_80137F6C;
s32 D_80137F9C;
s32 D_80137FB4;
s32 D_80137FB8;
s32 D_80137FBC;
s16 g_WasFacingLeft;  // for QCF to tell what's "forward"
s16 g_WasFacingLeft2; // for BF to tell what's "forward"
s32 g_WasFacingLeft3; // for dark metamorphosis "" ""
s32 g_WasFacingLeft4; // for summon spirit "" ""
s16 g_WasFacingLeft5; // for hellfire "" ""
s32 g_WasFacingLeft6; // for tetra spirit "" ""
s32 g_WasFacingLeft7; // for soul steal "" ""
s32 D_80137FDC;
s32 D_80137FE0;
s32 D_80137FE4;
s32 D_80137FE8;
u32 g_WingSmashButtonCounter;
s32 g_WingSmashButtonTimer;
s32 g_WingSmashTimer;
s32 g_BatScreechDone;
s32 g_MistTimer;
s32 D_80138008;
s32 D_8013800C[1]; // unknown size
s32 D_80138038;
u8 D_8013803C;
u8 D_80138040;
u8 D_80138044;
u8 D_80138048;
u8* D_80137590;
s32 D_80137594;
s32 D_80137598;
s32 D_8013759C;
s32 D_801375A0;
s32 D_801375A4;
s16 D_801375A6;
s32 D_801375A8;
s16 D_801375AA;
s32 D_801375AC;
s32 D_801375B0;
s32 D_801375B4;
s32 D_801375B8;
RoomLoadDefHolder D_801375BC;
s32 D_801375C0;
s32 D_801375C4;
s32 D_801375C8;
void (*D_8013C000)(void);
void (*D_8013C004)(s32);
void (*D_8013C008)(void);
void (*D_8013C00C)(void);

// sound bss
s16 g_SoundCommandRingBufferReadPos;
s16 g_SoundCommandRingBufferWritePos;
s16 D_80139804;
s16 D_8013B664;
s16 D_80139A6C;
s16 g_CurrentXaSoundId;
s16 D_8013901C;
s16 g_SoundCommandRingBuffer[MAX_SND_COUNT];
s16 g_VolL;
s16 g_VolR;
s16 D_8013AE94;
s32 D_8013AECC;
u16 D_8013AEE0;
Unkstruct_800BF554 g_SfxData[737];
u16 D_8013AE7C;
s16 D_801390A4;
s16 D_80139010;
s8 D_8013B690;
s16 D_8013B678[1];
s16 D_8013B648[4];
s16 D_8013AEA0[4];
u16 D_8013B626;
s8* D_8013B628[4];
u8 D_8013B5EC[4];
u8 D_8013B5F6[32];
s16 D_8013B66C[4];
s16 D_8013B672[1];
s8 g_UnkChannelSetting1[4];
u16 g_ChannelGroupVolume[4];
s16 g_UnkChannelSetting2[4];
s32 D_801390B4[1];
s8 D_80139018[1];
s16 D_80139814[1];
s8 D_80139058[1];
s16 D_801390AC[1];
s32 D_8013B61C;
s32 D_8013980C;
s16 g_sfxRingBufferWritePos;
SfxRingBufferItem g_SfxRingBuffer[MAX_SND_COUNT];
u8 g_SoundInitialized;
s32 g_KeyOffChannels;
SpuVoiceAttr* D_80138FB4;
s16 D_80138FC8;
s16 D_80138FCA;
SpuVoiceAttr* D_801390C8;
SpuVoiceAttr* D_801390CC;
ButtonComboState g_ButtonCombo[16];
u8 D_801390A0;
volatile unsigned char g_CdSoundCommandStep;
s16 g_CdVolume;
s16 g_XaMusicVolume;
s16 D_80139A78;
s16 g_volumeL;
s16 g_volumeR;
u8 g_CdSoundCommand16;
u8 D_80139014;
struct Cmd14 D_8013B5F4[1];
s32 D_8013AE90;
s32 D_8013AEF4;
u8 g_CdCommandResult[1];
u8 D_8013B688[8];
u8 g_CdMode[3];

struct XaMusicConfig g_XaMusicConfigs[563] = {0};

s32 D_800B0130[] = {0, -1, 0, -1}; // dummy data
s32 D_800B01B8[] = {0, -1, 0, -1}; // dummy data
s8 D_80138F64[20];
u8 D_801390C4;
s16 D_8013AE8A[1];
s16 D_8013AEA6;
s16 D_8013B64E;
u8 g_SeqPlayingId;
s16 g_SeqAccessNum;
volatile s16 g_CdSoundCommandQueuePos;
s32 D_801396F8[0x20];
s32 D_80139778[0x20];
s16 g_SeqVolume1;
s16 g_SeqVolume2;
u8 g_ReverbDepth;
s32 g_SeqPointers[0xA];
s16 D_8013845C;
u8 D_8013B640[3];
s32 g_CurCdPos;
s16 g_CurrentXaConfigId;
s16 g_CdSoundCommandQueue[MAX_SND_COUNT];
u8 D_8013AEDC;
s8 D_8013AEE8;
u8 D_801390D8;
char g_SeqTable[SS_SEQ_TABSIZ * SEQ_TABLE_S_MAX * SEQ_TABLE_T_MAX];
u8 D_801390A8;
s32 D_8013B694;
u8 g_MuteCd;
s32 D_80138F7C;
u8 D_8013B680;
s8 D_8013B618;
s16 D_80138F80;
s16 D_80139800;
s16 D_80138FBC;
s32 D_8013B69C;
s16 D_80139A74;
s16 g_SfxRingBufferReadPos;
s32 D_80138454;
s16 D_801396DC;
u16 D_801396E0;
u16 D_801396E4;
Multi D_801396E6;
u16 D_801396E8;
s16 D_801396EA;
u16 D_801396EC;
s32 g_CdCommandStatus;
volatile s16 g_CdSoundCommandQueuePos;
u16 D_801397F8;
s16 D_8013AED4[4];
s16 D_8013B650[4];
s32 g_CdCommandStatus;
const char* D_80138784[0x800];
s32 D_8013B65C;

// sound stubs

void SpuGetAllKeysStatus(char* status) { NOT_IMPLEMENTED; }

void func_801073C0(void) { NOT_IMPLEMENTED; }

void func_800EA7CC(void) { NOT_IMPLEMENTED; }

void RenderEntities(void) { NOT_IMPLEMENTED; }

void RenderTilemap(void) {
    u16* layout = g_Tilemap.fg;
    if (!layout) {
        return;
    }

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 17; j++) {
            u16 tile = layout[j];
            if (tile == 0) {
                continue;
            }
            SPRT_16* sprt = &g_CurrentBuffer->sprite16[g_GpuUsage.sp16++];
            u16 gfxPage = g_Tilemap.D_80073088->gfxPage[tile];
            u16 gfxIndex = g_Tilemap.D_80073088->gfxIndex[tile];
            u16 clut = D_8003C104[g_Tilemap.D_80073088->clut[tile]];
            gfxPage += 0x8;

            sprt->clut = clut;
            sprt->code = gfxPage; // TODO: bad hack
            sprt->x0 = j * 16;
            sprt->y0 = i * 16;
            sprt->u0 = gfxIndex * 16;
            sprt->v0 = gfxIndex & ~TILE_MASK;
            sprt->r0 = 0xFF;
            sprt->g0 = 0xFF;
            sprt->b0 = 0xFF;
        }
        layout += g_Tilemap.hSize * 16;
    }
}

void UpdateCd(void) { NOT_IMPLEMENTED; }

int CdInit(void) {
    NOT_IMPLEMENTED;
    return 0;
}

void func_801083BC(void) { NOT_IMPLEMENTED; }

void DrawRichterHudSubweapon(void) { NOT_IMPLEMENTED; }

void func_800F24F4(void) { NOT_IMPLEMENTED; }

void func_8011A4D0(void) { NOT_IMPLEMENTED; }

void func_800F2658(void) { NOT_IMPLEMENTED; }

void func_8011A9D8(void) { NOT_IMPLEMENTED; }

void func_8011A870(void) { NOT_IMPLEMENTED; }

void func_80121F14(s32 arg0, s32 arg1) { NOT_IMPLEMENTED; }

void func_800F1D54(s32 arg0, s32 arg1, s32 arg2, s32 arg3) { NOT_IMPLEMENTED; }

void func_800F1B08(s32 arg0, s32 arg1, s32 arg2) { NOT_IMPLEMENTED; }

void EntityAlucard(Entity* self) { NOT_IMPLEMENTED; }

s32 func_800F0CD8(s32 arg0) {
    NOT_IMPLEMENTED;
    return 0;
}

void func_80118C28(s32 arg0) { NOT_IMPLEMENTED; }

void func_80115C50(void) { NOT_IMPLEMENTED; }

AnimationFrame frame = {0};
AnimationFrame* func_8010DA70(s32* frames) {
    NOT_IMPLEMENTED;
    return &frame;
}

void EntityWeaponAttack(Entity* self) { NOT_IMPLEMENTED; }
void func_ptr_80170004(Entity* self) { NOT_IMPLEMENTED; }
void func_ptr_80170008(Entity* self) { NOT_IMPLEMENTED; }
void func_ptr_8017000C(Entity* self) { NOT_IMPLEMENTED; }
void func_ptr_80170010(Entity* self) { NOT_IMPLEMENTED; }
void func_ptr_80170014(Entity* self) { NOT_IMPLEMENTED; }
int GetWeaponId(void) {
    NOT_IMPLEMENTED;
    return 0;
}
void LoadWeaponPalette(s32 clutIndex) { NOT_IMPLEMENTED; }
void EntityWeaponShieldSpell(Entity* self) { NOT_IMPLEMENTED; }
void func_ptr_80170024(Entity* self) { NOT_IMPLEMENTED; }
void func_ptr_80170028(Entity* self) { NOT_IMPLEMENTED; }

s32 func_800FB23C(MenuNavigation* nav, u8* order, u8* count, u32* selected) {
    NOT_IMPLEMENTED;
    return 0;
}

Entity* GetFreeEntity(s16 start, s16 end);
Entity* CreateEntFactoryFromEntity(
    Entity* source, u32 factoryParams, s32 arg2_raw) {
    return GetFreeEntity(8, 16);
}

u16 g_FontCharData[0x60] = {1, 1, 1, 0, 0, 0};
u16* func_80106A28(u32 arg0, u16 kind) {
    NOT_IMPLEMENTED;
    return g_FontCharData;
}

// copied from 75F54.c
Entity* GetFreeEntity(s16 start, s16 end) {
    Entity* entity = &g_Entities[start];
    s16 i;

    for (i = start; i < end; i++, entity++) {
        if (entity->entityId == E_NONE) {
            return entity;
        }
    }
    return NULL;
}
s32 func_80118C84(s16 arg0, s16 arg1) {
    Entity* entity = GetFreeEntity(0x38, 0x40);

    if (entity != NULL) {
        DestroyEntity(entity);
        entity->entityId = ENTITY_13;
        entity->posX.val = PLAYER.posX.val;
        entity->posY.val = PLAYER.posY.val;
        entity->ext.generic.unk80.modeS16.unk0 = arg0;
        entity->ext.generic.unk80.modeS16.unk2 = arg1;
        return 0;
    }
    return -1;
}

void func_801131C4(void) {
    s32 i;
    s32 x_offset;
    u16 local_flags;
    bool condition = false;

    local_flags = 0;
    condition = ((g_Player.pl_vram_flag & 0x20) != condition);

    if ((g_Player.padTapped & PAD_CROSS) && !(g_Player.unk46 & PAD_LEFT)) {
        if (g_Player.padPressed & PAD_DOWN) {
            for (i = 0; i < 4; i++) {
                if ((g_Player.colliders[i].effects & EFFECT_SOLID_FROM_ABOVE)) {
                    g_Player.D_80072F00[7] = 8;
                    return;
                }
            }
        }
        if (g_Player.unk72 == 0) {
            func_8010E83C(1);
            return;
        }
    }
    if (func_8010FDF8(0x100C) != 0) {
        return;
    }
    DecelerateX(0x2000);
    if (g_Player.unk48 != 0) {
        if (PLAYER.ext.player.unkAC == 0x11) {
            PLAYER.ext.player.unkAC = 0x65;
            PLAYER.animFrameDuration = 2;
            PLAYER.animFrameIdx = 3;
        }
    } else if (PLAYER.ext.player.unkAC == 0x65) {
        func_8010DA48(0x11);
    }
    switch (PLAYER.step_s) {
    case 0x0:
        if (D_800ACF74 != 0) {
            D_800ACF74--;
        } else if (D_80097448[0] >= 0x19) {
            if (g_Player.unk48 == 0) {
                x_offset = 0xC;
                if (PLAYER.facingLeft) {
                    x_offset = -0xC;
                }
                PLAYER.posX.i.hi = x_offset + PLAYER.posX.i.hi;
                PLAYER.posY.i.hi += 2;
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0xd00, 4), 0);
                D_800ACF74 = 0x60;
                PLAYER.posY.i.hi -= 2;
                PLAYER.posX.i.hi -= x_offset;
            }
        }
        local_flags = 6;
        break;
    case 0x1:
        if (!(g_Player.padPressed & PAD_DOWN)) {
            local_flags = 1;
            if ((PLAYER.animFrameIdx >= 4) || PLAYER.ext.player.unkAC == 0x65) {
                func_8010DA48(0x13);
                PLAYER.step_s = 2;
                PLAYER.animFrameIdx = 2;
                if (g_Player.unk72 == 1) {
                    PLAYER.animFrameIdx = 0;
                }
                if (g_Player.unk72 == 2) {
                    PLAYER.animFrameIdx = 1;
                }
                return;
            }
        } else if (PLAYER.ext.player.unkAC == 0x65) {
            PLAYER.step_s = 0;
        } else {
            if (PLAYER.animFrameDuration < 0) {
                local_flags = 0x20;
            }
        }
        break;
    case 0x5:
        func_8010DFF0(1, 1);
        if (g_Player.unk72 == PLAYER.animFrameIdx ||
            PLAYER.animFrameDuration < 0) {
            local_flags = 0x20;
        }
        break;
    case 0x3:
    case 0x4:
        func_8010DFF0(1, 1);
        if (PLAYER.animFrameDuration < 0) {
            local_flags = 0x20;
        }
        break;
    case 0x2:
        local_flags = 1;
        if (g_Player.padPressed & PAD_DOWN) {
            func_8010E470(0, PLAYER.velocityX);
            break;
        }
        if (g_Player.unk72 != 0) {
            func_8010DFF0(1, 1);
            if (g_Player.unk72 == 1) {
                PLAYER.animFrameIdx = 0;
                PLAYER.animFrameDuration = 3;
                break;
            } else if (g_Player.unk72 == 2) {
                if (PLAYER.animFrameIdx != 0) {
                    PLAYER.animFrameIdx = 1;
                    PLAYER.animFrameDuration = 3;
                }
                break;
            } else if (g_Player.unk72 == 3) {
                if (PLAYER.animFrameIdx >= 2) {
                    PLAYER.animFrameIdx = 2;
                    PLAYER.animFrameDuration = 3;
                }
                break;
            } else if (g_Player.unk72 == 4) {
                if (PLAYER.animFrameIdx >= 3) {
                    PLAYER.animFrameIdx = 3;
                    PLAYER.animFrameDuration = 3;
                }
                break;
            }
        }
        if (PLAYER.animFrameDuration < 0) {
            func_8010E570(0);
        }

        break;
    case 0x40:
    case 0x59:
        func_8010DFF0(1, 1);
        if (PLAYER.animFrameIdx < g_Player.unk54) {
            if (PLAYER.animFrameIdx < 2) {
                func_8010E27C();
                if (!(g_Player.padPressed & PAD_DOWN)) {
                    if (g_Player.unk72 == 0) {
                        PLAYER.step = 0;
                        PLAYER.ext.player.unkAC = 0x24;
                    }
                }
            }
        } else {
            g_Player.unk46 &= 0x7FFF;
            local_flags = 0xE;
            if (PLAYER.animFrameIdx == 7) {
                if (g_Player.padPressed & g_Player.D_80072EF8) {
                    PLAYER.animFrameDuration = 2;
                    local_flags = 0xE;
                } else {
                    local_flags = 0x2E;
                }
            }
        }
        break;
    case 0x47:
    case 0x49:
        if ((PLAYER.animFrameIdx == 6) &&
            (g_Player.padPressed & g_Player.D_80072EF8)) {
            PLAYER.animFrameDuration = 2;
        case 0x41:
        case 0x42:
        case 0x43:
        case 0x44:
        case 0x45:
        case 0x46:
        case 0x48:
        case 0x4A:
        case 0x4B:
        case 0x4C:
        case 0x4D:
        case 0x4E:
        case 0x4F:
        case 0x50:
        case 0x53:
        case 0x54:
        case 0x55:
        case 0x56:
        case 0x57:
        case 0x58:
        case 0x5A:
        case 0x5B:
        case 0x5C:
        case 0x5D:
        }
        func_8010DFF0(1, 1);
        if (PLAYER.animFrameIdx < g_Player.unk54) {
            if (PLAYER.animFrameIdx < 3) {
                func_8010E27C();
                if (!(g_Player.padPressed & PAD_DOWN)) {
                    if (g_Player.unk72 == 0) {
                        PLAYER.ext.player.unkAC =
                            D_800B0608[PLAYER.step_s - 0x41] + condition;
                        PLAYER.step = 0;
                    }
                }
            }
        } else {
            g_Player.unk46 &= 0x7FFF;
            local_flags = 0xE;
            if (PLAYER.animFrameDuration < 0) {
                local_flags = 0x2E;
            }
        }
        break;
    case 0x51:
        func_8010DFF0(1, 1);
        if (PLAYER.animFrameDuration < 0) {
            local_flags = 0x2E;
        }
        break;
    }

    if (local_flags & 0x20) {
        func_8010E470(0, 0);
        local_flags |= 0x8000;
    }
    if (local_flags & 2) {
        if (g_Player.unk4C != 0) {
            func_8010DA48(0x14);
            PLAYER.step_s = 0;
            local_flags |= 0x8000;
        }
    }
    if (local_flags & 4) {
        if (!(g_Player.padPressed & PAD_DOWN)) {
            func_8010DA48(0x13);
            PLAYER.step_s = 2;
            local_flags |= 0x8000;
        }
    }
    if (local_flags & 1) {
        if (func_8010E27C()) {
            switch ((u8)g_Player.unk72) {
            case 0:
            case 3:
            case 4:
                func_8010E6AC(0);
                local_flags |= 0x8000;
                break;
            case 1:
            case 2:
                if (g_Player.padTapped & (PAD_RIGHT | PAD_LEFT)) {
                    PLAYER.step_s = 5;
                    func_8010DA48(0xF6);
                    SetSpeedX(FIX(0.75));
                    local_flags |= 0x8000;
                }
                break;
            }
        }
    }
    if ((local_flags & 0x8000) && (local_flags & 8)) {
        func_8010FAF4();
    }
}

void func_80113148(void) {
    if (g_Player.D_80072F00[5] != 0 && g_Player.padTapped & PAD_CROSS) {
        func_8010E83C(1);
    } else if (func_8010FDF8(0x9029) == 0) {
        DecelerateX(0x1000);
        if (func_8010E27C() != 0) {
            SetSpeedX(0xC000);
        }
    }
}

void func_80112BB0(void) {
    char pad[12];
    s32 temp_v0;
    s32 temp_v1;
    s32 var_s2;

    if (PLAYER.step_s != 0x58) {
        DecelerateX(0x1000);
        if (PLAYER.velocityY < -0x10000) {
            if (!(g_Player.unk44 & 0x40) &&
                !(g_Player.padPressed & PAD_CROSS)) {
                PLAYER.velocityY = -0x10000;
            }
            if (g_Player.pl_vram_flag & 2) {
                PLAYER.velocityY = -0x4000;
                g_Player.unk44 |= 0x20;
            }
        }
        if (func_8010FDF8(0x11029) != 0) {
            return;
        }
    }
    switch (PLAYER.step_s) {
    case 0x0:
        var_s2 = func_8010E27C();
        if (var_s2 != 0) {
            if ((PLAYER.ext.player.unkAC == 0x16) ||
                (PLAYER.ext.player.unkAC == 0x19)) {
                func_8010DA48(0x18U);
            }
            SetSpeedX(0x18000);
        } else if ((PLAYER.ext.player.unkAC == 0x1A) ||
                   (PLAYER.ext.player.unkAC == 0x18)) {
            func_8010DA48(0x19U);
        }
        if (var_s2 <= 0) {
            g_Player.unk44 &= 0xFFEF;
        }
        if (PLAYER.velocityY > 0) {
            if (PLAYER.ext.player.unkAC != 0x1B) {
                func_8010DA48(0x1BU);
            }
            PLAYER.step_s = 1;
        }
        break;
    case 0x1:
        var_s2 = func_8010E27C();
        if ((var_s2 == 0) || (SetSpeedX(0x18000), (var_s2 <= 0))) {
            g_Player.unk44 &= 0xFFEF;
        }
        break;
    case 0x58:
        func_8010DFF0(1, 1);
        if (D_80139824 > 0) {
            D_80139824--;
        }
        if ((PLAYER.animFrameIdx == 3) && (PLAYER.animFrameDuration == 1) &&
            (D_80139824 != 0)) {
            PLAYER.animFrameIdx = 1;
        }
        if ((PLAYER.animFrameIdx == 4) ||
            (g_Player.padTapped & (PAD_DOWN | PAD_UP))) {
            PLAYER.step_s = 0x40;
        }
        break;
    case 0x57:
    case 0x5B:
        func_8010DFF0(1, 1);
        DecelerateX(0x1000);
        if (PLAYER.ext.player.unkAC == 0x6C) {
            if (PLAYER.animFrameDuration < 0) {
                temp_v0 = (PLAYER.velocityY > 0x10000) ^ 1;
                PLAYER.step_s = D_800ACF7C[temp_v0].unk0;
                func_8010DA48(D_800ACF7C[temp_v0].unk2);
                func_8010FAF4();
                g_Player.unk44 = 1;
                D_80138FC8 = 0xFE;
                D_80138FCA = 0x10;
            }
        } else if (
            (PLAYER.animFrameIdx == 4) && (PLAYER.animFrameDuration == 1)) {
            PLAYER.animFrameIdx = 5;
            PLAYER.ext.player.unkAC = 0x6C;
        }
        break;
    case 0x41:
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x45:
    case 0x46:
    case 0x47:
    case 0x48:
    case 0x49:
    case 0x4A:
    case 0x4B:
    case 0x4C:
    case 0x4D:
    case 0x4E:
    case 0x4F:
    case 0x50:
    case 0x51:
    case 0x53:
    case 0x54:
    case 0x55:
    case 0x56:
    case 0x5A:
    case 0x5C:
    case 0x5D:
        func_8010DFF0(1, 1);
    case 0x40:
    case 0x59:
        func_8010DFF0(1, 1);
        if (g_Player.padPressed & PAD_LEFT) {
            PLAYER.velocityX = -0x18000;
        }
        if (g_Player.padPressed & PAD_RIGHT) {
            PLAYER.velocityX = 0x18000;
        }
        if (PLAYER.animFrameDuration < 0) {
            temp_v1 = (PLAYER.velocityY > 0x10000) ^ 1;
            PLAYER.step_s = D_800ACF7C[temp_v1].unk0;
            func_8010DA48(D_800ACF7C[temp_v1].unk2);
            func_8010FAF4();
        }
        break;
    case 0x70:
        if (g_Player.unk44 & 0x80) {
            func_8010E83C(1);
            if (!(g_Player.padPressed & PAD_CROSS)) {
                PLAYER.velocityY = -0x44000;
            }
            g_Player.unk44 |= 0x40;
        }
        break;
    }

    if (PLAYER.step_s < 2) {
        if (g_Player.unk44 & 1) {
            if ((g_Player.padPressed & PAD_DOWN) &&
                (g_Player.padTapped & PAD_CROSS)) {
                func_8010DA48(0x22U);
                PLAYER.step_s = 0x70;
                CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 5), 0);
                PLAYER.velocityY = 0x60000;
                g_Player.unk44 &= 0xFF7F;
                if (var_s2 != 0) {
                    SetSpeedX(0x48000);
                }
                PlaySfx(0x6F0);
            }
            if (g_Player.unk44 & 0x100) {
                PLAYER.velocityX = 0;
            }
        }
    } else {
        if (g_Player.unk44 & 0x100) {
            PLAYER.velocityX = 0;
        }
    }
}

void ControlBatForm(void) {
    s32 pressingCross;
    s32 x_offset;
    // When we initially move left/right, bat makes a screech sound.
    s32 screechDone;
    u32 directionsPressed;

    screechDone = 0;
    if (BatFormFinished()) {
        return;
    }
    PLAYER.drawFlags = FLAG_DRAW_ROTZ;
    PLAYER.rotPivotY = 0;
    directionsPressed =
        g_Player.padPressed & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT);
    pressingCross = g_Player.padPressed & PAD_CROSS;

#if defined(VERSION_HD)
    if (PLAYER.step_s != 3) {
#elif defined(VERSION_US)
    // Just to make the curly brackets match at the end of this block
    if (1) {
#endif
        if (CheckWingSmashInput() && (!pressingCross) && (PLAYER.step_s != 0) &&
            (CastSpell(SPELL_WING_SMASH) != 0)) {
            LearnSpell(SPELL_WING_SMASH);
            func_8010DA48(0xC6);
            SetSpeedX(FIX(6));
            PLAYER.step_s = 3;
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x5c00, 44), 0);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 67), 0);
            g_WingSmashTimer = 0x40;
#if defined(VERSION_US)
            g_WingSmashButtonCounter = 0;
#endif
        } else if ((g_Player.padTapped & PAD_TRIANGLE) &&
                   ((u32)(PLAYER.step_s - 1) < 2U) &&
                   (IsRelicActive(RELIC_ECHO_OF_BAT))) {
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 103), 0);
        } else if ((g_Player.padTapped & (PAD_SQUARE | PAD_CIRCLE)) &&
                   ((u32)(PLAYER.step_s - 1) < 2U) &&
                   (IsRelicActive(RELIC_FIRE_OF_BAT)) && (CastSpell(9) != 0)) {
            func_8010DA48(0xC9);
            PLAYER.step_s = 4;
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x500, 44), 0);
        }
    }

    switch (PLAYER.step_s) {
    case 0:
        g_WingSmashButtonCounter = 0;
        PLAYER.rotZ = 0;
        g_Player.unk48 = 0;
        g_Player.unk46 = 0;
        g_Player.unk44 = 0;
        if (g_Entities[16].entityId == 0x22) {
            PLAYER.animSet = 0xD;
            D_800AFDA6[0] = 6;
            PLAYER.unk5A = 0;
            PLAYER.ext.player.unkAC = 0xCA;
            if (func_8011203C() == 0) {
                return;
            }
        } else {
            if (g_Player.unk66 == 0) {
#if defined(VERSION_US)
                if (CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0x2000, 44), 0) == NULL) {
                    return;
                }
#elif defined(VERSION_HD)
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0x2000, 44), 0);
#endif
                func_8010FAF4();
                g_Player.unk66++;
            }
            DecelerateX(0x480);
            DecelerateY(0x480);
            if (ABS(PLAYER.velocityY) > FIX(1.25)) {
                if (PLAYER.velocityY > 0) {
                    PLAYER.velocityY = FIX(1.25);
                } else {
                    PLAYER.velocityY = FIX(-1.25);
                }
            }
            func_8010DA48(0xCA);
            PLAYER.palette = 0x810D;
            D_800AFDA6[0] = (s16)PLAYER.animCurFrame;
            if (g_Player.unk66 == 1) {
                return;
            }
            if (g_Player.unk66 == 2) {
                PLAYER.animSet = 0xD;
                PLAYER.unk5A = 0;
                D_800AFDA6[0] = 6;
                return;
            }
        }
        func_8010DA48(0xC3);
        PLAYER.animFrameDuration = 1;
        PLAYER.animFrameIdx = 2;
        PLAYER.palette = 0x8100;
        func_8010E27C();
        PLAYER.step_s++;
        break;
    case 1:
        if ((directionsPressed != 0) && (pressingCross == 0)) {
            if (PLAYER.ext.player.unkAC == 0xC3) {
                PLAYER.animFrameIdx /= 3;
            }
            PLAYER.step_s += 1;
        } else {
            func_8011690C(0);
            DecelerateX(0x1200);
            DecelerateY(0x1200);
            break;
        }
    case 2:
        // If you're pressing cross, you can't move and inputs are ignored.
        if (pressingCross) {
            directionsPressed = 0;
        }
        switch (directionsPressed) {
        case 0:
        default:
            func_8010DA48(0xC3);
            PLAYER.step_s = 1;
            break;
        case PAD_UP:
            PLAYER.ext.player.unkAC = 0xC2;
            if (PLAYER.velocityY < FIX(-1.25)) {
                DecelerateY(0x1200);
            } else {
                PLAYER.velocityY = FIX(-1.25);
            }
            func_8011690C(-0x80);
            DecelerateX(0x1200);
            break;
        case PAD_DOWN:
            if (!(g_Player.pl_vram_flag & 1)) {
                PLAYER.ext.player.unkAC = 0xC5;
            } else {
                PLAYER.ext.player.unkAC = 0xC4;
            }
            if (PLAYER.velocityY > FIX(1.25)) {
                DecelerateY(0x1200);
            } else {
                PLAYER.velocityY = FIX(1.25);
            }
            func_8011690C(0);
            DecelerateX(0x1200);
            break;
        case PAD_RIGHT:
            PLAYER.ext.player.unkAC = 0xC2;
            PLAYER.facingLeft = 0;
            func_8011690C(0x180);
            if (PLAYER.velocityX > FIX(1.25)) {
                DecelerateX(0x1200);
            } else {
                PLAYER.velocityX = FIX(1.25);
            }
            DecelerateY(0x1200);
            screechDone = 1;
            if (!g_BatScreechDone) {
                PlaySfx(SOUND_BAT_SCREECH);
            }
            break;
        case PAD_LEFT:
            PLAYER.ext.player.unkAC = 0xC2;
            PLAYER.facingLeft = 1;
            func_8011690C(0x180);
            if (PLAYER.velocityX < FIX(-1.25)) {
                DecelerateX(0x1200);
            } else {
                PLAYER.velocityX = FIX(-1.25);
            }
            DecelerateY(0x1200);
            screechDone = 1;
            if (!g_BatScreechDone) {
                PlaySfx(SOUND_BAT_SCREECH);
            }
            break;
        case PAD_RIGHT | PAD_UP:
            PLAYER.ext.player.unkAC = 0xC2;
            PLAYER.facingLeft = 0;
            func_8011690C(0x80);
            if (PLAYER.velocityX > FIX(0.875)) {
                DecelerateX(0xC00);
            } else {
                PLAYER.velocityX = FIX(0.875);
            }
            if (PLAYER.velocityY < FIX(-0.875)) {
                DecelerateY(0xC00);
            } else {
                PLAYER.velocityY = FIX(-0.875);
            }
            break;
        case PAD_LEFT | PAD_UP:
            PLAYER.ext.player.unkAC = 0xC2;
            PLAYER.facingLeft = 1;
            func_8011690C(0x80);
            if (PLAYER.velocityX < FIX(-0.875)) {
                DecelerateX(0xC00);
            } else {
                PLAYER.velocityX = FIX(-0.875);
            }
            if (PLAYER.velocityY < FIX(-0.875)) {
                DecelerateY(0xC00);
            } else {
                PLAYER.velocityY = FIX(-0.875);
            }
            break;
        case PAD_RIGHT | PAD_DOWN:
            if (!(g_Player.pl_vram_flag & 1)) {
                PLAYER.ext.player.unkAC = 0xC5;
            } else {
                PLAYER.ext.player.unkAC = 0xC4;
            }
            PLAYER.facingLeft = 0;
            func_8011690C(0);
            if (PLAYER.velocityX > FIX(0.875)) {
                DecelerateX(0xC00);
            } else {
                PLAYER.velocityX = FIX(0.875);
            }
            if (PLAYER.velocityY > FIX(1.75)) {
                DecelerateY(0xC00);
            } else {
                PLAYER.velocityY = FIX(1.75);
            }
            break;
        case PAD_LEFT | PAD_DOWN:
            if (!(g_Player.pl_vram_flag & 1)) {
                PLAYER.ext.player.unkAC = 0xC5;
            } else {
                PLAYER.ext.player.unkAC = 0xC4;
            }
            PLAYER.facingLeft = 1;
            func_8011690C(0);
            if (PLAYER.velocityX < FIX(-0.875)) {
                DecelerateX(0xC00);
            } else {
                PLAYER.velocityX = FIX(-0.875);
            }
            if (PLAYER.velocityY > FIX(1.75)) {
                DecelerateY(0xC00);
            } else {
                PLAYER.velocityY = FIX(1.75);
            }
            break;
        }
        break;
    case 3:
        if (PLAYER.facingLeft == 0 && (g_Player.pl_vram_flag & 4) ||
            PLAYER.facingLeft != 0 && (g_Player.pl_vram_flag & 8)) {
            g_Player.padTapped = PAD_R1;
            BatFormFinished();
            func_80102CD8(2);
            PlaySfx(0x644);
            PLAYER.velocityX = 0;
            g_Player.D_80072EFC = 0x20;
            g_Player.D_80072EF4 = 0;
            break;
        }
        // When wing smash ends, force an un-transform
        if (--g_WingSmashTimer == 0) {
            g_Player.padTapped = PAD_R1;
            BatFormFinished();
            g_Player.D_80072EFC = 0x20;
            g_Player.D_80072EF4 = 0;
        } else {
            if (directionsPressed & PAD_UP) {
                PLAYER.velocityY -= FIX(0.125);
                func_8011690C(0x80);
            }
            if (directionsPressed & PAD_DOWN) {
                PLAYER.velocityY += FIX(0.125);
            }
            if (!(directionsPressed & PAD_UP)) {
                func_8011690C(0x180);
            }
            if (!(directionsPressed & (PAD_DOWN | PAD_UP))) {
                DecelerateY(0x2000);
            }
            if (g_Player.pl_vram_flag & 0x800) {
                if (PLAYER.facingLeft != 0 && (g_Player.pl_vram_flag & 0x400) ||
                    PLAYER.facingLeft == 0 &&
                        !(g_Player.pl_vram_flag & 0x400)) {
                    PLAYER.velocityY = FIX(6);
                }
            }
            if ((g_Player.pl_vram_flag & 0x8000) != 0) {
                if (PLAYER.facingLeft != 0 &&
                        (g_Player.pl_vram_flag & 0x4000) ||
                    PLAYER.facingLeft == 0 &&
                        !(g_Player.pl_vram_flag & 0x4000)) {
                    PLAYER.velocityY = FIX(-6);
                }
            }
            if (PLAYER.velocityY < FIX(-6)) {
                PLAYER.velocityY = FIX(-6);
            }
            if (PLAYER.velocityY > FIX(6)) {
                PLAYER.velocityY = FIX(6);
            }
            if (g_GameTimer % 3 == 0) {
                CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 65), 0);
                if (g_Player.pl_vram_flag & 1) {
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0x900, 69), 0);
                }
                if (g_Player.pl_vram_flag & 2) {
                    x_offset = 3;
                    if (PLAYER.facingLeft != 0) {
                        x_offset = -3;
                    }
                    PLAYER.posY.i.hi -= 8;
                    PLAYER.posX.i.hi = x_offset + PLAYER.posX.i.hi;
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0x100, 4), 0);
                    PLAYER.posY.i.hi += 8;
                    PLAYER.posX.i.hi -= x_offset;
                }
            }
        }
        break;
    // Happens when shooting fireball with Fire of Bat
    case 4:
        DecelerateX(FIX(12.0 / 128));
        DecelerateY(FIX(28.0 / 128));
        func_8011690C(0x180);
        if (PLAYER.animFrameDuration < 0) {
            // This actually creates the entity factory to produce the fireball
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 81), 0);
            SetSpeedX(FIX(-1.5));
            func_8011690C(0);
            func_8010DA48(0xC3);
            PLAYER.step_s++;
        }
        break;
    // Finishing up on the fireball
    case 5:
        DecelerateX(FIX(12.0 / 128));
        DecelerateY(FIX(28.0 / 128));
        func_8011690C(0);
        if (PLAYER.ext.player.unkAC == 0xC4 && PLAYER.animFrameIdx == 8) {
            PLAYER.step_s = 1;
        }
        break;
    }

    if (D_8013AECC != 0) {
        if (PLAYER.velocityX > 0) {
            PLAYER.velocityX = 0;
        }
        if (D_8013AECC > 0) {
            D_8013AECC--;
            g_CurrentEntity->posY.i.hi++;
        } else {
            D_8013AECC++;
            g_CurrentEntity->posY.i.hi--;
        }
    }
    g_BatScreechDone = screechDone;
}

void func_801177A0(void) {
    byte pad[0x28];
    s32 i;
    s32 else_cycles;

    PLAYER.drawFlags = FLAG_DRAW_ROTZ;
    DecelerateX(0x2000);
    if (g_Player.pl_vram_flag & 3) {
        PLAYER.velocityY = 0;
    }
    DecelerateY(0x2000);
    func_8011690C(0);
    else_cycles = 0;
    switch (PLAYER.step_s) {
    case 0:
        for (i = 0; i < 4; i++) {
            if (D_800ACED0.pairs[i].unk2 < D_800ACE90[i]) {
                D_800ACED0.pairs[i].unk2++;
            } else {
                else_cycles++;
            }
            if (D_800ACE88[i] < D_800ACEC0[i].unk2) {
                D_800ACEC0[i].unk2--;
            } else {
                else_cycles++;
            }
            // This means the lower parts only run once!
            if (i != 0) {
                continue;
            }
            if (g_Player.unk68 != 0) {
                if (D_8013AECC >= 12) {
                    continue;
                }
                D_8013AECC++;
            } else {
                if (g_Player.pl_vram_flag & 0x8000) {
                    PLAYER.posY.i.hi--;
                }
            }
        }

        if ((g_Player.pl_vram_flag & 3) == 3) {
            g_Player.unk68 = 1;
            PLAYER.velocityY = 0;
            PLAYER.velocityX = 0;
        }
        if (else_cycles == 8) {
            PLAYER.animSet = 1;
            PLAYER.rotZ = 0;
            PLAYER.drawFlags = 0;
            g_Player.unk66 = 1;
            if (g_Player.unk68 != 0) {
                PLAYER.step_s = 2;
                D_800AFDA6[0] = 0xC7;
            } else {
                PLAYER.step_s = 1;
                D_800AFDA6[0] = 0x5F;
            }
        }
        break;
    case 1:
        if (g_Player.unk66 == 3) {
            func_8010E83C(0);
            PLAYER.posY.i.hi -= 3;
            if (!(g_Player.pl_vram_flag & 0x8000)) {
                PLAYER.velocityY = FIX(-1);
            }
            PLAYER.palette = 0x8100;
#if defined(VERSION_US)
            g_Player.unk20[0] = 0x18;
#elif defined(VERSION_HD)
            D_800ACEDC_hd = 0x18;
#endif
            g_Player.unk44 |= 0x100;
            func_80111CC0();
        }
        break;
    case 2:
        if (g_Player.unk66 == 3) {
            func_8010E4D0();
        }
        break;
    }
    if (func_80111DE8(0) != 0) {
        PLAYER.velocityX = 0;
    }
}

void ControlMistForm(void) {
    s32 xSpeedDiag;
    s32 ySpeedDiag;
    s32 ySpeedOrtho;
    s32 xSpeedOrtho;
    u32 directionsPressed;

    if (!IsRelicActive(RELIC_POWER_OF_MIST)) {
        // Ortho and Diag describe the speeds when moving orthogonally (in a
        // single direction) versus moving diagonally (in two directions at
        // once). Overall speed diagonally is 5/16 * sqrt(2) which is 0.442, so
        // a fair bit slower than orthogonal speed.
        xSpeedOrtho = FIX(0.5);
        ySpeedOrtho = FIX(0.5);
        xSpeedDiag = FIX(5.0 / 16);
        ySpeedDiag = FIX(5.0 / 16);
    } else {
        // With Power of Mist, we move at double speed.
        xSpeedOrtho = FIX(1);
        ySpeedOrtho = FIX(1);
        xSpeedDiag = FIX(10.0 / 16);
        ySpeedDiag = FIX(10.0 / 16);
    }
    if (MistFormFinished()) {
        return;
    }
    directionsPressed =
        g_Player.padPressed & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT);
    switch (PLAYER.step_s) {
    case 0:
        func_800EA5E4(0x1BU);
        func_8010E27C();
        g_Player.unk48 = 0;
        g_Player.unk46 = 0;
        g_Player.unk44 = 0;
        func_8010FAF4();
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 73), 0);
        if (PLAYER.velocityX > 0) {
            PLAYER.velocityX = xSpeedOrtho;
        }
        if (PLAYER.velocityX < 0) {
            PLAYER.velocityX = -xSpeedOrtho;
        }
        if (PLAYER.velocityY > 0) {
            PLAYER.velocityY = ySpeedOrtho;
        }
        if (PLAYER.velocityY < 0) {
            PLAYER.velocityY = -ySpeedOrtho;
        }
        func_8010DA48(0xCA);
        D_800AFDA6[0] = PLAYER.animCurFrame;
        func_800EA538(8);
        if (!IsRelicActive(RELIC_GAS_CLOUD)) {
            func_800EA5E4(0x11CU);
        } else {
            func_800EA5E4(0x11FU);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 83), 0);
        }
        // Note that this means Power of Mist doesn't make mist infinite!
        // It just lasts 100,000 :)
        if (!IsRelicActive(RELIC_POWER_OF_MIST)) {
            g_MistTimer = 16;
        } else {
            g_MistTimer = 100000;
        }
        PLAYER.step_s += 1;
        break;
    case 1:
        switch (directionsPressed) {
        case 0:
        default:
            DecelerateX(FIX(3.0 / 256));
            DecelerateY(FIX(3.0 / 256));
            break;
        case PAD_UP:
            if (PLAYER.velocityY < -ySpeedOrtho) {
                DecelerateY(FIX(3.0 / 256));
            } else {
                PLAYER.velocityY = -ySpeedOrtho;
            }
            DecelerateX(FIX(3.0 / 256));
            break;
        case PAD_DOWN:
            if (ySpeedOrtho < PLAYER.velocityY) {
                DecelerateY(FIX(3.0 / 256));
            } else {
                PLAYER.velocityY = ySpeedOrtho;
            }
            DecelerateX(FIX(3.0 / 256));
            break;
        case PAD_RIGHT:
            PLAYER.facingLeft = 0;
            if (xSpeedOrtho < PLAYER.velocityX) {
                DecelerateX(FIX(3.0 / 256));
            } else {
                PLAYER.velocityX = xSpeedOrtho;
            }
            DecelerateY(FIX(3.0 / 256));
            break;
        case PAD_LEFT:
            PLAYER.facingLeft = 1;
            if (PLAYER.velocityX < -xSpeedOrtho) {
                DecelerateX(FIX(3.0 / 256));
            } else {
                PLAYER.velocityX = -xSpeedOrtho;
            }
            DecelerateY(FIX(3.0 / 256));
            break;
        case PAD_UP + PAD_RIGHT:
            PLAYER.facingLeft = 0;
            if (xSpeedDiag < PLAYER.velocityX) {
                DecelerateX(FIX(2.0 / 256));

            } else {
                PLAYER.velocityX = xSpeedDiag;
            }
            if (PLAYER.velocityY < -ySpeedDiag) {
                DecelerateY(FIX(2.0 / 256));
            } else {
                PLAYER.velocityY = -ySpeedDiag;
            }
            break;
        case PAD_UP + PAD_LEFT:
            PLAYER.facingLeft = 1;
            if (PLAYER.velocityX < -xSpeedDiag) {
                DecelerateX(FIX(2.0 / 256));
            } else {
                PLAYER.velocityX = -xSpeedDiag;
            }
            if (PLAYER.velocityY < -ySpeedDiag) {
                DecelerateY(FIX(2.0 / 256));
            } else {
                PLAYER.velocityY = -ySpeedDiag;
            }
            break;
        case PAD_DOWN + PAD_RIGHT:
            PLAYER.facingLeft = 0;
            if (xSpeedDiag < PLAYER.velocityX) {
                DecelerateX(FIX(2.0 / 256));
            } else {
                PLAYER.velocityX = xSpeedDiag;
            }
            if (ySpeedDiag < PLAYER.velocityY) {
                DecelerateY(FIX(2.0 / 256));
            } else {
                PLAYER.velocityY = ySpeedDiag;
            }
            break;
        case PAD_DOWN + PAD_LEFT:
            PLAYER.facingLeft = 1;
            if (PLAYER.velocityX < -xSpeedDiag) {
                DecelerateX(FIX(2.0 / 256));
            } else {
                PLAYER.velocityX = -xSpeedDiag;
            }
            if (ySpeedDiag < PLAYER.velocityY) {
                DecelerateY(FIX(2.0 / 256));
            } else {
                PLAYER.velocityY = ySpeedDiag;
            }
            break;
        }
        break;
    default:
        FntPrint("error step\n");
        break;
    }
    if (D_8013AECC != 0) {
        if (D_8013AECC > 0) {
            D_8013AECC -= 1;
            PLAYER.posY.i.hi++;
        } else {
            D_8013AECC += 1;
            PLAYER.posY.i.hi--;
        }
    }
}

void func_801182F8(void) {
    byte pad[0x28];
    s32 i;
    s32 else_cycles;

    if ((g_Player.pl_vram_flag & 1) && (PLAYER.velocityY > 0)) {
        PLAYER.velocityY = 0;
    }
    if ((g_Player.pl_vram_flag & 2) && (PLAYER.velocityY < 0)) {
        PLAYER.velocityY = 0;
    }
    DecelerateX(0x200);
    DecelerateY(0x200);
    else_cycles = 0;
    for (i = 0; i < 4; i++) {
        if (D_800ACED0.pairs[i].unk2 < D_800ACE90[i]) {
            D_800ACED0.pairs[i].unk2++;
        } else {
            else_cycles++;
        }
        if (D_800ACE88[i] < D_800ACEC0[i].unk2) {
            D_800ACEC0[i].unk2--;
        } else {
            else_cycles++;
        }
        // This means the lower parts only run once!
        if (i != 0) {
            continue;
        }
        if (PLAYER.step_s != 0) {
            if (D_8013AECC >= 12) {
                continue;
            }
            D_8013AECC++;
        } else {
            if (g_Player.pl_vram_flag & 0x8000) {
                PLAYER.posY.i.hi--;
            }
        }
    }
    if ((g_Player.pl_vram_flag & 3) == 3) {
        PLAYER.step_s = 1;
        PLAYER.velocityY = 0;
        PLAYER.velocityX = 0;
    }
    if (else_cycles == 8) {
        if (func_80111D24()) {
            return;
        }
        PLAYER.animSet = 1;
        PLAYER.unk5A = 0;
        func_8010DA48(0xCB);
        if (PLAYER.step_s != 0) {
            func_8010DA48(0xCC);
        }
        if (g_Entities[16].step < 3) {
            g_Entities[16].step = 3;
            return;
        }
        if (g_Entities[16].step == 5) {
            PLAYER.palette = 0x8100;
            func_8010FAF4();
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x5b00, 44), 0);
            if (PLAYER.step_s != 0) {
                func_8010E4D0();
                return;
            }
            func_8010E83C(0);
            PLAYER.posY.i.hi -= 3;
            if (!(g_Player.pl_vram_flag & 0x8000)) {
                PLAYER.velocityY = -0x10000;
            }
#if defined(VERSION_US)
            g_Player.unk20[0] = 0x18;
#elif defined(VERSION_HD)
            D_800ACEDC_hd = 0x18;
#endif
            g_Player.unk44 |= 0x100;
            func_80111CC0();
        }
    }
    if (func_80111DE8(1) != 0) {
        PLAYER.velocityX = 0;
    }
}

void func_8012EF2C(void) {
    s16 var_v1;
    s32 i;

    PLAYER.palette = 0x104;
    PLAYER.blendMode = 0;
// HD version lacks this line!
#if defined(VERSION_US)
    PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter.S16.unk0 - 2;
#endif
    if (WolfFormFinished()) {
        return;
    }
    if (D_8013842C != 0) {
        D_8013842C--;
    }
    if (D_80138440 != 0) {
        D_80138440--;
    }
    D_80138444 = 0;
    func_8012C97C();
    D_800B0920 = 14;
    switch (PLAYER.step_s) {
    case 0:
        func_8012E7A4();
        break;
    case 1:
        func_8012D024();
        break;
    case 2:
        func_8012D3E8();
        break;
    case 3:
        func_8012E550();
        break;
    case 4:
        func_8012E040();
        break;
    case 5:
        func_8012DBBC();
        break;
    case 7:
        func_8012D178();
        break;
    case 6:
        func_8012DF04();
        break;
    case 8:
        func_8012E9C0();
        break;
    case 9:
        func_8012ED30();
    }
    D_80138438 = g_Player.unk04;
    for (i = 0; i < 8; i++) {
        var_v1 = 4;
        if (ABS(PLAYER.velocityX) >= FIX(4)) {
            var_v1 = 3;
        }
        if (ABS(PLAYER.velocityX) >= FIX(5)) {
            var_v1--;
        }
        if (ABS(PLAYER.velocityX) >= FIX(6)) {
            var_v1--;
        }
        // Might be misusing D_800AFFB8 here
        D_800AFFB8[i * 2] = var_v1;
    }
    if (D_80138430 < 0x600) {
        D_80138430 = 0x600;
    }
    if (D_80138430 > 0xA00) {
        D_80138430 = 0xA00;
    }
    // HD version lacks this line!

#if defined(VERSION_US)
    PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter.S16.unk0 - 2;
#endif
}

void func_8012EAD0(void) {
    s32 i;
    s32 else_cycles;

    DecelerateX(FIX(0.125));
    if (g_Player.pl_vram_flag & 3) {
        PLAYER.velocityY = 0;
    }
    DecelerateY(FIX(0.125));
    else_cycles = 0;
    switch (PLAYER.step_s) {
    case 0:
        i = 0;
        for (i = 0; i < 4; i++) {
            if (D_800ACE88[i] < D_800ACEC0[i].unk2) {
                D_800ACEC0[i].unk2--;
            } else {
                else_cycles += 1;
            }
        }
        if ((g_Player.pl_vram_flag & 3) == 3) {
            g_Player.unk68 = 1;
            PLAYER.velocityY = 0;
            PLAYER.velocityX = 0;
        }
        if (else_cycles == 4) {
            PLAYER.animSet = 1;
            PLAYER.unk5A = 0;
            PLAYER.rotZ = 0;
            PLAYER.drawFlags = 0;
            func_8010DA48(0xCA);
            g_Player.unk66 = 1;
            if (g_Player.unk68 != 0) {
                PLAYER.step_s = 2;
                D_800AFDA6[0] = 0xC7;
            } else {
                PLAYER.step_s = 1;
                D_800AFDA6[0] = 0x5F;
            }
        }
        return;
    case 1:
        if (g_Player.unk66 == 3) {
            func_8010E83C(0);
            if (!(g_Player.pl_vram_flag & 0x8000)) {
                PLAYER.velocityY = FIX(-1);
            }
            PLAYER.palette = 0x8100;
#if defined(VERSION_US)
            g_Player.unk20[0] = 0x18;
#elif defined(VERSION_HD)
            D_800ACEDC_hd = 0x18;
#endif
            g_Player.unk44 |= 0x100;
            PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter.S16.unk0;
            func_80111CC0();
        }
        return;
    case 2:
        if (g_Player.unk66 == 3) {
#if defined(VERSION_US)
            PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter.S16.unk0;
#endif

            func_8010E4D0();
        }
    }
}

void func_80113AAC(void) {
    s32 var_s1 = 0;
    s32 temp;

    g_Player.unk4A++;
    if (func_8010FDF8(2) != 0) {
        return;
    }

    switch (PLAYER.step_s) {
    case 0:
        if (g_Player.pl_vram_flag & 2) {
            func_801139CC(3);
            if (g_Player.unk4A >= 5) {
                PLAYER.step_s = 2;
                PLAYER.rotZ = 0x800;
                PLAYER.rotPivotY = 2;
                PLAYER.rotPivotX = 0;
                PLAYER.drawFlags |= 4;
                PLAYER.facingLeft = (PLAYER.facingLeft + 1) & 1;
                func_8010DA48(0x2B);
            } else {
                PLAYER.step_s = 3;
            }
        } else if (g_Player.unk4A > 28) {
            PLAYER.step_s = 1;
            PLAYER.velocityY = -0x60000;
            func_8010DA48(0x1B);
        }
        break;

    case 1:
        if (g_Player.pl_vram_flag & 2) {
            PLAYER.step_s = 2;
            func_801139CC(3);
        } else {
            PLAYER.velocityY += 0x6000;
            if (PLAYER.velocityY > 0x8000) {
                var_s1 = 1;
            }
        }
        break;

    case 2:
        PLAYER.drawFlags |= 4;
        PLAYER.rotPivotX = 0;
        PLAYER.rotPivotY = 2;
        if (g_Player.unk4A >= 0x39) {
            func_8010DA48(0x2D);
            PLAYER.rotZ = 0;
            PLAYER.step_s = 4;
            PLAYER.drawFlags &= 0xFB;
            PLAYER.facingLeft = (PLAYER.facingLeft + 1) & 1;
        }
        break;

    case 3:
        if (g_Player.unk4A > 20) {
            var_s1 = 1;
        }
        break;

    case 4:
        PLAYER.velocityY += 0x1000;
        if (PLAYER.animFrameDuration < 0) {
            var_s1 = 2;
        }
        break;
    }

    if (var_s1 != 0) {
        temp = 0; // TODO: !FAKE
        if ((var_s1 - 1) != temp) {
            func_8010DA48(0x1C);
        }
        PLAYER.palette = 0x8100;
        PLAYER.step_s = 1;
        PLAYER.step = Player_Jump;
    }
}

void func_801186EC(void) {
    if (PLAYER.step_s == 0) {
        if (g_Entities[E_WEAPON].entityId == E_NONE) {
            D_80138008 = 0x10;
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x1500, 61), 0);
            PLAYER.step_s++;
        }
    } else if (--D_80138008 == 0) {
        PLAYER.palette = 0x8100;
        func_8010E570(0);
    }
}

void AlucardHandleDamage(DamageParam* damage, s16 arg1) {
    s32 randbit;
    u8 unkAC_offset;
    s32 var_s0;
    s32 sfxIndex;
    bool step_sIsZero = false;

    switch (PLAYER.step_s) {
    case 0:
        step_sIsZero = true;
        func_80113EE0();
        if (damage->damageKind < 16) {
            func_80113F7C();
        } else {
            if (damage->damageKind == 16) {
                func_80113F7C();
            }
            if (damage->damageKind == 17) {
                PLAYER.entityRoomIndex = 1;
            }
            if (damage->damageKind == 18) {
                PLAYER.entityRoomIndex = 0;
            }
        }
        if (g_Player.unk0C & PLAYER_STATUS_AXEARMOR) {
            PLAYER.velocityY = FIX(-3);
            func_8010E3B8(FIX(-1.25));
            PLAYER.step = Player_AxearmorHit;
            PLAYER.step_s = 0;
            PLAYER.ext.player.unkAC = 0xD1;
            PlaySfx(0x6ED);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 85), 0);
            D_8017A000.func_ptr_80170010();
            if (g_Player.unk72 != 0) {
                PLAYER.velocityY = 0;
            }
            return;
        }
        // Unfortunate reuse of var_s0 here. case 4 and 5 treat it as a step_s
        // offset, while others treat it as a velocity.
        var_s0 = 0;
        func_80111CC0();
        sfxIndex = 0;
        switch (damage->damageKind) {
        case 5:
            var_s0 = 13;
            g_Player.damageTaken = damage->damageTaken;
        case 4:
            PLAYER.posY.val -= 1;
            PLAYER.velocityY = FIX(-0.5);
            func_8010E3B8(FIX(-8));
            PLAYER.step_s = var_s0 + 2;
            PLAYER.ext.player.unkAC = 0x2E;
            g_Player.D_80072F00[2] = 0x200;
            PLAYER.facingLeft = PLAYER.entityRoomIndex;
            if (damage->damageKind == 4) {
                sfxIndex = (rand() & 1) + 1;
            }
            break;
        case 16:
        case 17:
        case 18:
            sfxIndex = (rand() & 1) + 3;
            switch (arg1) {
            case 0:
            case 1:
                break;
            case 3:
            case 4:
                var_s0 = FIX(1);
                break;
            }
            PLAYER.velocityY = var_s0 + FIX(-4);
            func_8010E3B8(FIX(-1.66666));
            PLAYER.step_s = 1;
            if (func_80113E68() == 0) {
                PLAYER.ext.player.unkAC = 0x40;
            }
            break;
        case 3:
        case 7:
            sfxIndex = (rand() & 1) + 3;
            switch (arg1) {
            case 3:
            case 4:
                var_s0 = FIX(1);
            case 0:
            default:
                PLAYER.velocityY = var_s0 + FIX(-4);
                func_8010E3B8(FIX(-1.66666));
                PLAYER.step_s = 1;
                if (func_80113E68() == 0) {
                    PLAYER.ext.player.unkAC = 0x40;
                }
                break;
            case 2:
            case 6:
                PLAYER.velocityY = 0;
                func_8010E3B8(FIX(-2.5));
                PLAYER.step_s = 7;
                PLAYER.ext.player.unkAC = 0x23;
                CreateEntFactoryFromEntity(g_CurrentEntity, 0, 0);
            }
            break;
        case 2:
            sfxIndex = (rand() & 1) + 5;
            switch (arg1) {
            case 0:
            case 1:
                PLAYER.velocityY = 0;
                func_8010E3B8(FIX(-2.5));
                PLAYER.step_s = 6;
                randbit = (rand() & 1);
                // Weird test, I  think PLAYER.entityRoomIndex is a wrong name.
                // But if they don't match, we add 2 to the offset.
                unkAC_offset =
                    randbit |
                    ((PLAYER.entityRoomIndex != PLAYER.facingLeft) ? 2 : 0);
                PLAYER.ext.player.unkAC = unkAC_offset + 0x31;
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0x600, 0), 0);
                break;
            case 2:
            case 6:
                PLAYER.velocityY = 0;
                func_8010E3B8(FIX(-2.5));
                PLAYER.step_s = 7;
                PLAYER.ext.player.unkAC = 0x23;
                CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 0), 0);
                break;
            case 3:
            case 4:
            case 5:
            default:
                PLAYER.velocityY = FIX(-2);
                func_8010E3B8(FIX(-1.25));
                PLAYER.step_s = 1;
                func_80113E68();
                break;
            }
            break;
        default:
            FntPrint("dam_kind:%04x\n", damage->damageKind);
            break;
        }
        g_Player.unk40 = 0x8166;
        g_Player.D_80072F00[2] = 6;
        PlaySfx(D_800ACF84[sfxIndex]);
        if (damage->effects & 0x100) {
            g_Player.D_80072F00[1] =
                GetStatusAilmentTimer(STATUS_AILMENT_CURSE, 0x400);
            g_Player.unk40 = 0x8165;
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x200, 47), 0);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x1700, 44), 0);
            PlaySfx(NA_SE_VO_AL_WHAT);
        } else if (damage->effects & 0x80) {
            g_Player.D_80072F00[0] =
                GetStatusAilmentTimer(STATUS_AILMENT_POISON, 0xFFF);
            g_Player.unk40 = 0x8164;
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x1600, 44), 0);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x100, 47), 0);
            PlaySfx(NA_SE_VO_AL_WHAT);
        } else if (damage->effects & 0x8000) {
            PlaySfx(0x690);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x4500, 44), 0);
            g_Player.unk40 = 0x8160;
            if (damage->effects & 0x10000) {
                CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 19), 0);
                g_Player.D_80072F00[2] = 10;
            } else {
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0x100, 17), 0);
                CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 18), 0);
                g_Player.D_80072F00[2] = 16;
            }
        } else if (damage->effects & 0x4000) {
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 45), 0);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x4600, 44), 0);
            g_Player.D_80072F00[2] = 24;
            g_Player.unk40 = 0x8102;
        } else if (damage->effects & 0x2000) {
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 46), 0);
            g_Player.D_80072F00[2] = 12;
            g_Player.unk40 = 0x8169;
            PLAYER.ext.player.unkAC = 0x2E;
        } else {
            if (damage->effects & 0x1000) {
                CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 119), 0);
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0x6800, 44), 0);
                g_Player.D_80072F00[2] = 8;
                g_Player.unk40 = 0x8168;
            }
            if (damage->effects & 0x800) {
                CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 113), 0);
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0x6200, 44), 0);
                g_Player.D_80072F00[2] = 16;
                g_Player.unk40 = 0x8164;
            }
            if (damage->effects & 0x40) {
                PlaySfx(0x62E);
                g_Player.unk40 = 0x8166;
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0x4200, 44), 0);
                if (damage->effects & 0x10000) {
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0x500, 21), 0);
                    g_Player.D_80072F00[2] = 10;
                } else {
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0x500, 20), 0);
                    g_Player.D_80072F00[2] = 16;
                }
            } else if (!(damage->effects & 0xFAC0)) {
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0x5800, 44), 0);
            }
        }

        break;
    case 1:
        if (func_8010FDF8(0x20280) != 0) {
            return;
        }
        if (PLAYER.animFrameDuration < 0) {
            func_8010DA48(0x1C);
            PLAYER.facingLeft = (PLAYER.facingLeft + 1) & 1;
        }
        break;
    case 2:
    case 15:
        if ((g_Player.unk04 & 0x8000) && !(g_Player.pl_vram_flag & 0x8000)) {
            goto deepcond;
        }
        if ((g_Player.pl_vram_flag & 0x8000) && !(g_GameTimer & 1)) {
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0xA00, 69), 0);
        }
        if (!(g_Player.pl_vram_flag & 0xE)) {
            break;
        }
        if (g_Player.pl_vram_flag & 2) {
            func_801139CC(1);
            PLAYER.velocityX /= 2;
            PLAYER.velocityY = 0;
            g_Player.D_80072F00[8] = 24;
            PLAYER.step_s = 5;
            if (g_Player.unk52 == 0xF &&
                (func_80113D7C(g_Player.damageTaken) != 0)) {
                return;
            }
            break;
        }
        if ((g_StageId != STAGE_BO6) && (g_StageId != STAGE_RBO6) &&
            (g_StageId != STAGE_DRE)) {
            for (var_s0 = 2; var_s0 < 7; var_s0++) {
                if ((g_Player.colliders3[var_s0].effects & 2)) {
                    break;
                }
            }
            if (var_s0 == 7) {
                for (var_s0 = 9; var_s0 < 14; var_s0++) {
                    if ((g_Player.colliders3[var_s0].effects & 2)) {
                        break;
                    }
                }
            }
            if (var_s0 == 14) {
            // Not a very good label name, but it's deep in a bunch of
            // conditionals.
            deepcond:
                PLAYER.velocityY = FIX(-4);
                func_8010E3B8(FIX(-1.25));
                PLAYER.ext.player.unkAC = 0x2F;
                var_s0 = -3;
                if (PLAYER.velocityX != 0) {
                    var_s0 = 3;
                }
                PLAYER.posY.i.hi += 0x15;
                PLAYER.posX.i.hi = var_s0 + PLAYER.posX.i.hi;
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0x900, 4), 0);
                PLAYER.posY.i.hi -= 0x15;
                PLAYER.posX.i.hi -= var_s0;
                PlaySfx(0x644);
                func_80102CD8(2);
                PLAYER.step_s = 1;
                if (g_Player.unk52 == 0xF &&
                    (func_80113D7C(g_Player.damageTaken) != 0)) {
                    return;
                }
                break;
            }
        }

        if (PLAYER.step_s == 0xF) {
            g_Player.D_80072F00[8] = 8;
            func_8010DA48(0x3F);
            PlaySfx(0x644);
            PLAYER.velocityY = FIX(-2.5);
            func_80102CD8(2);
            PLAYER.step_s = 3;
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x800, 31), 0);
            if (func_80113D7C(g_Player.damageTaken) != 0) {
                return;
            }
            break;
        }
        PLAYER.velocityY = 0;
        g_Player.D_80072F00[8] = 48;
        PLAYER.velocityX /= 2;
        PlaySfx(0x647);
        PLAYER.rotZ = 0x400;
        PLAYER.rotPivotX = 0x10;
        PLAYER.rotPivotY = 4;
        PLAYER.drawFlags |= 4;
        func_8010DA48(0x2C);
        PLAYER.step_s = 0xE;
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x800, 31), 0);
        break;
    case 3:
        if (g_Player.D_80072F00[8] == 0) {
            SetSpeedX(FIX(0.75));
            if (func_8010FDF8(0x20280) != 0) {
                return;
            }
        }
        break;
    case 5:
        DecelerateX(FIX(1.0 / 8));
        if (g_Player.D_80072F00[8] != 0) {
            if ((g_Player.pl_vram_flag & 2) && !(g_GameTimer & 3)) {
                func_801139CC(0);
            }
            break;
        } else if (g_Player.pl_vram_flag & 0xC) {
            if (!(g_Player.pl_vram_flag & 0xFF03)) {
                PLAYER.velocityY += FIX(12.0 / 128);
                if (PLAYER.velocityY > FIX(7)) {
                    PLAYER.velocityY = FIX(7);
                }
                if (!(g_GameTimer & 3)) {
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0x400, 12), 0);
                }
                break;
            }
        }
        PLAYER.step_s = 1;
        func_80113E68();
        PLAYER.animFrameIdx = 0;
        PLAYER.animFrameDuration = 0;
        break;
    case 14:
        PLAYER.drawFlags |= 4;
        if (g_Player.D_80072F00[8] <= 0) {
            PLAYER.drawFlags &= ~4;
            PLAYER.rotZ = 0x800;
            PLAYER.velocityY = 0;
            PLAYER.velocityX /= -2;
            func_8010DA48(0x1C);
            PLAYER.step_s = 1;
            PLAYER.step = 4;
            g_Player.unk44 = 0;
        }
        break;
    case 6:
    case 7:
        DecelerateX(FIX(1.0 / 8));
        if (!(g_Player.pl_vram_flag & 1)) {
            func_8010E7AC();
        }
        if (PLAYER.animFrameDuration < 0) {
            if (PLAYER.step_s == 6) {
                func_8010E570(0);
            } else {
                func_8010E470(0, PLAYER.velocityX);
            }
        }
        break;
    }
    if (step_sIsZero && (g_Player.unk72 != 0)) {
        PLAYER.velocityY = 0;
    }
}

void func_80114DF4(s32 arg0) {
    s16 randvar;
    s32 newlyPetrified;
    s32 yShift;

    newlyPetrified = 0;
    switch (PLAYER.step_s) {
    case 0:
        newlyPetrified = 1;
        func_80113EE0();
        func_80113F7C();
        PLAYER.velocityY = FIX(-4);
        if (!(g_Player.pl_vram_flag & 1)) {
            PLAYER.velocityY = FIX(-2);
        }
        func_8010E3B8(FIX(-1.25));
        func_80113E68();
        PLAYER.palette = 0x8161;
        PlaySfx(0x6EC);
        g_Player.D_80072F00[2] = 0;
        g_Player.D_80072F00[0] = 0;
        g_Player.D_80072F00[1] = 0;
        g_Player.unk5E = GetStatusAilmentTimer(STATUS_AILMENT_PETRIFIED, 8);
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x300, 47), 0);
        func_8010E168(1, 4);
        PLAYER.step_s = 1;
        break;
    case 1:
        func_8010E168(1, 4);
        PLAYER.palette = 0x8161;
        if (func_8010FDF8(0x20280) != 0) {
            PLAYER.step = Player_StatusStone;
            PLAYER.velocityY = 0;
            PLAYER.velocityX = 0;
            func_80102CD8(1);
            PlaySfx(0x644);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 39), 0);

            randvar = rand() % 64;

            if (g_Status.hp == 0) {
                D_80137FE0 = 0x20;
                randvar = 2;
            }
            if (randvar << 0x10) {
                PLAYER.palette = (randvar & 1) - 0x7E62;
                func_8010DA48(randvar & 1 | 0x38);
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0x300, 16), 0);
            } else {
                PLAYER.palette = 0x819E;
                func_8010DA48(0x3A);
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0x700, 29), 0);
            }
            PLAYER.step_s = 2;
        }
        break;
    case 2:
        if (D_80097448[0] >= 0x29) {
            yShift = FIX(11.0 / 256);
        } else {
            yShift = FIX(44.0 / 256);
        }

        // I don't know man
        do {
        } while (0);

        if (!(g_Player.pl_vram_flag & 1)) {
            PLAYER.velocityY += yShift;
            if (PLAYER.velocityY > FIX(7)) {
                PLAYER.velocityY = FIX(7);
            }
            func_8010E168(1, 4);
            break;
        }

        if (!(g_Player.unk04 & 1)) {
            func_80102CD8(1);
            PlaySfx(0x644);
        }

        PLAYER.velocityY = 0;
        if (g_Status.hp == 0) {
            if (--D_80137FE0 == 0) {
                PLAYER.step = Player_Kill;
                PlaySfx(0x6F6);
                PLAYER.step_s = 16;
            }
            func_8010E168(1, 4);
            break;
        }
        // Handles wiggling out of being petrified.
        if (g_Player.padTapped & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT) ||
            arg0 != 0 || D_800ACE44 != 0) {
            PLAYER.animFrameDuration = 0x10;
            g_Player.padTapped |= (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT);
            // Counter for how many wiggles left until we're out
            g_Player.unk5E--;
            PlaySfx(0x608);
            if (g_Player.unk5E == 0) {
                func_8010DA48(0x3B);
                if (PLAYER.ext.player.unkAC != 0x3A) {
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0x300, 16), 0);
                } else {
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0, 32), 0);
                }
                PlaySfx(0x6E7);
                PLAYER.step = Player_Hit;
                PLAYER.step_s = 6;
                PLAYER.palette = 0x8100;
                break;
            }
            func_8010E168(1, 0x1C);
            PLAYER.step_s = 3;
            if (PLAYER.ext.player.unkAC != 0x3A) {
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0x300, 13), 0);
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0x300, 31), 0);
            } else {
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0x800, 13), 0);
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0x700, 30), 0);
            }
        }
        PLAYER.palette = ((PLAYER.ext.player.unkAC + 0xFFC8) & 1) - 0x7E62;
        break;
    case 3:
        if (PLAYER.animFrameDuration < 0) {
            PLAYER.step_s = 2;
            PLAYER.drawFlags &= 0xFB;
        } else {
            PLAYER.rotPivotX = 0;
            PLAYER.drawFlags |= 4;
            PLAYER.rotZ = D_800ACF94[PLAYER.animFrameDuration] >> 4;
            if (PLAYER.rotZ == 0) {
                PLAYER.rotPivotY = 0x18;
            } else {
                PLAYER.rotPivotY = 0x14;
            }
        }
        break;
    }
    if (PLAYER.ext.player.unkAC == 0x3A) {
        func_8010E168(1, 4);
    }
    if (newlyPetrified && (g_Player.unk72 != 0)) {
        PLAYER.velocityY = 0;
    }
}

void func_80116208(void) {
    DamageParam damage;
    s32 temp_s0;

    switch (g_CurrentEntity->step_s) {
    case 0:
        func_80113EE0();
        if (g_Player.unk62 == 0) {
            PLAYER.ext.generic.unkAC = 0x37;
            g_Player.D_80072F00[2] = 8;
            g_Player.unk40 = 0x8166;
            PlaySfx(0x6EB);
        }
        PLAYER.step_s = 1;
        PLAYER.velocityY = 0;
        PLAYER.velocityX = 0;
        g_Player.unk60 = 2;
        return;
    case 1:
        if (g_Player.unk60 == 3) {
            temp_s0 = HandleDamage(&damage, 2, g_Player.unk64, 1);
            func_80118C84(damage.damageTaken, 0);
            if (temp_s0 == 4) {
                SetPlayerStep(Player_Kill);
                func_80115394(&damage, 0xC, 1);
                return;
            }
            if (g_Player.unk62 == 0) {
                g_Player.D_80072F00[2] = 4;
                g_Player.unk40 = 0x8166;
                PlaySfx(0x6E7);
            }
            if (g_Player.unk62 == 2) {
                g_Player.D_80072F00[2] = 4;
                g_Player.unk40 = 0x8161;
            }
            g_Player.unk60 = 2;
            return;
        }
        if (g_Player.unk60 == 4) {
            PLAYER.step = Player_Hit;
            PLAYER.step_s = 0xF;
            g_Player.unk60 = 0;
            func_8010DA48(0x2E);
            g_Player.damageTaken = g_Player.unk64;
            PlaySfx(0x6ED);
            return;
        }
        if (g_Player.unk60 == 0) {
            PLAYER.step = Player_Hit;
            PLAYER.step_s = 1;
            return;
        }
    }
}

void func_80115394(s32*, s16, s16) { NOT_IMPLEMENTED; }

void func_80115BB0(void) {
    PLAYER.drawFlags = FLAG_DRAW_ROTZ;
    PLAYER.velocityY = 0;
    PLAYER.velocityX = 0;
    PLAYER.animFrameDuration = 4;

    if (D_80097420[0] == 0) {
        if (g_Player.pl_vram_flag & 1) {
            func_8010E570(0);
        } else {
            func_8010E7AC();
        }
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x4a00, 44), 0);
        g_PlayerDraw->enableColorBlend = 0;
    }
}

void func_80115DA0(void) {
    PLAYER.velocityY = 0;
    PLAYER.velocityX = 0;
    g_Player.D_80072EF4 = 0;
    g_Player.D_80072EFC = 4;

    switch (PLAYER.step_s) {
    case 0:
        if (PLAYER.animFrameIdx == 8 && PLAYER.animFrameDuration == 1 &&
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 121), 0) ==
                NULL) {
            PLAYER.animFrameDuration = 2;
        }
        if (PLAYER.animFrameDuration < 0) {
            func_8010E570(0);
        }
        break;

    case 2:
        func_80115C50();
        if (PLAYER.animFrameIdx == 8 && PLAYER.animFrameDuration == 1 &&
            CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(0x200, 121), 0) == NULL) {
            PLAYER.animFrameDuration = 2;
        }
        if (PLAYER.animFrameDuration < 0) {
            func_8010E570(0);
        }
        break;

    case 4:
        func_80115C50();
        if (PLAYER.animFrameIdx == 8 && PLAYER.animFrameDuration == 1 &&
            CreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(0x400, 121), 0) == NULL) {
            PLAYER.animFrameDuration = 2;
        }
        if (PLAYER.animFrameDuration < 0) {
            func_8010E570(0);
        }
        break;

    case 1:
    case 3:
    case 5:
        if (PLAYER.animFrameDuration < 0) {
            func_8010E570(0);
        }
        if (g_Player.unk1C != 0) {
            func_8010E570(0);
        }
        break;
    }
}

void func_80118614(void) {
    if (PLAYER.animFrameDuration < 0) {
        func_8010E570(0);
    }
}

void PlayerStepHellfire(void) {
    // Whether we should run the last 3 function calls at the end
    bool runFinishingBlock = 0;
    switch (PLAYER.step_s) {
    case 0:
        // Make factory with blueprint #33. Factory makes entities with ID 25.
        // This is EntityHellfireHandler.
        if (CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 33), 0) ==
            NULL) {
            func_8010E570(0);
        }
        func_8010DA48(1);
        PLAYER.step_s++;
        break;
    case 1:
        if (g_Player.unk5C == 1) {
            PLAYER.step_s++;
        }
        break;
    case 2:
        PLAYER.velocityX = 0;
        if (func_8010E27C() != 0) {
            if (g_Player.padPressed & PAD_RIGHT) {
                if ((g_Player.colliders[2].effects &
                     (EFFECT_UNK_8000 + EFFECT_SOLID)) ||
                    (g_Player.colliders[1].effects & EFFECT_UNK_8000) ||
                    (PLAYER.posX.i.hi > 248)) {
                    SetSpeedX(FIX(3));
                }
            } else if ((g_Player.colliders[3].effects &
                        (EFFECT_UNK_8000 + EFFECT_SOLID)) ||
                       (g_Player.colliders[1].effects & EFFECT_UNK_8000) ||
                       (PLAYER.posX.i.hi < 8)) {
                SetSpeedX(FIX(3));
            }
        }
        if (g_Player.unk5C == 2) {
            PLAYER.velocityX = 0;
            func_8010DA48(0x3D);
            PLAYER.step_s++;
        }
        break;
    case 3:
        func_8010E27C();
        if (g_Player.unk5C == 3) {
            func_8010DA48(0x3C);
            PLAYER.step_s += 1;
            // In Hellfire, if you press down, it cancels the spell
            if (g_Player.padPressed & PAD_DOWN) {
                runFinishingBlock = 1;
            }
        }
        break;
    case 4:
        if (PLAYER.animFrameIdx == 10 && PLAYER.animFrameDuration == 1) {
            g_Player.D_80072F00[12] = 4;
            // Make factory with blueprint 37. This creates entity with ID 28,
            // which is EntityExpandingCircle.
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 37), 0);
        }
        if (PLAYER.animFrameDuration < 0) {
            runFinishingBlock = 1;
        }
        break;
    }
    // Not sure why this cast to u16 is needed but it is
    if (((u16)runFinishingBlock) || (g_Player.unk5C == 0xFFFF)) {
        func_8010E570(0);
        func_8010DA48(0x3D);
        func_80111CC0();
    }
}

void func_80118670(void) {
    if (PLAYER.animFrameIdx == 7 && PLAYER.animFrameDuration == 1) {
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x1600, 40), 0);
        PlaySfx(NA_SE_PL_MP_GAUGE);
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 112), 0);
    }
    if (PLAYER.animFrameDuration < 0) {
        func_8010E570(0);
    }
}

void func_80118640(void) {
    if (PLAYER.animFrameDuration < 0) {
        func_8010E470(0, 0);
    }
}

void func_801166A4(void) {
    switch (PLAYER.step_s) {
    case 0:
        func_80113EE0();
        g_Player.unk40 = 0x8166;
        g_Player.D_80072F00[2] = 6;
        PLAYER.velocityX = 0;
        PLAYER.velocityY = 0;
        PLAYER.ext.generic.unkAC = 0x33;
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 0), 0);
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x5800, 44), 0);
        PLAYER.step_s++;
        break;

    case 1:
        if (PLAYER.animFrameDuration < 0) {
            PlaySfx(NA_SE_VO_AL_WHAT);
            func_8010E570(0);
        }
        break;

    default:
        break;
    }
}

void func_8011678C(void) {
    PLAYER.velocityY = 0;
    PLAYER.velocityX = 0;
    if (g_Player_D_80072EF6 != 2) {
        func_8010E570(0);
    }
}

void func_801167D0(void) {
    s32* velocityX = &PLAYER.velocityX;
    PLAYER.velocityY = 0;
    *velocityX = 0;
    if (g_Player_D_80072EF6 != 2) {
        PLAYER.step = Player_AxearmorStand;
        PLAYER.step_s = 0;
        PLAYER.velocityY = 0;
        *velocityX = 0;
        PLAYER.ext.generic.unkAC = 0xCF;
        PLAYER.animFrameIdx = 0;
        PLAYER.animFrameDuration = 0;
    }
}

void func_80115F54(void) {
    PlayerDraw* plDraw;
    bool var_s2;

    var_s2 = false;
    PLAYER.drawFlags = FLAG_DRAW_ROTZ;
    plDraw = g_PlayerDraw;
    if (*D_80097420 == 0xFFF && PLAYER.step_s != 0) {
        SetPlayerStep(Player_Unk17);
        PLAYER.velocityY = 0;
        PLAYER.velocityX = 0;
        return;
    }

    switch (PLAYER.step_s) {
    case 0:
        var_s2 = true;
        PLAYER.velocityY = 0;
        PLAYER.velocityX = 0;
        PlaySfx(NA_SE_VO_AL_DYING);
        func_80113EE0();
        PLAYER.velocityY = -0x1A000;
        PLAYER.ext.generic.unkAC = 0xC1;
        PLAYER.blendMode = 0x30;
        PLAYER.rotZ = 0x200;
        func_80118C28(1);
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x5900, 44), 0);
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x600, 49), 0);
        plDraw->r3 = plDraw->b3 = plDraw->g3 = 128;
        plDraw->r2 = plDraw->b2 = plDraw->g2 = 128;
        plDraw->r1 = plDraw->b1 = plDraw->g1 = 128;
        plDraw->r0 = plDraw->b0 = plDraw->g0 = 128;
        plDraw->enableColorBlend = true;
        PLAYER.step_s++;
        break;
    case 1:
        if (plDraw->g0 < 0xF8) {
            plDraw->g0++;
        }
        if (plDraw->r0 >= 9) {
            plDraw->r0--;
        }
        plDraw->g3 = plDraw->g2 = plDraw->g1 = plDraw->g0;
        plDraw->b0 = plDraw->b1 = plDraw->r1 = plDraw->b2 = plDraw->r2 =
            plDraw->b3 = plDraw->r3 = plDraw->r0;
        PLAYER.velocityY += 0x1000;
        if (PLAYER.velocityY > 0x4000) {
            PLAYER.velocityY = 0x1000;
        }
        if (PLAYER.animFrameDuration < 0) {
            StoreImage(&D_800AE130, &D_80139A7C);
            PLAYER.step = 0x10;
            D_80137FE4 = 0;
            D_80137FE8 = 0x40;
            g_CurrentEntity->step_s++;
        }
        break;
    }

    if (var_s2 && g_Player.unk72) {
        PLAYER.velocityY = 0;
    }
}

void func_80117AC0(void) {
    Collider collider;
    s32 collisionCount;

    CheckCollision(PLAYER.posX.i.hi, PLAYER.posY.i.hi + 0x19, &collider, 0);
    collisionCount = (s32)collider.effects & EFFECT_SOLID;
    CheckCollision(PLAYER.posX.i.hi + 4, PLAYER.posY.i.hi + 0x19, &collider, 0);
    if ((s32)collider.effects & EFFECT_SOLID) {
        collisionCount += 1;
    }
    CheckCollision(PLAYER.posX.i.hi - 4, PLAYER.posY.i.hi + 0x19, &collider, 0);
    if ((s32)collider.effects & EFFECT_SOLID) {
        collisionCount += 1;
    }
    if ((g_Player.pl_vram_flag & 0x41) == 0x41) {
        collisionCount += 1;
    }
    PLAYER.rotZ = 0;
    func_8010E27C();
    if (collisionCount == 0) {
        func_8010E7AC();
        return;
    }

    switch (PLAYER.step_s) {
    case 0:
        if (PLAYER.animFrameDuration < 0) {
            func_8010DA48(0xF6);
            PLAYER.step_s += 1;
        }
        break;
    case 1:
        if (g_Player.padTapped & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT)) {
            func_8010DA48(0xC8);
            PlaySfx(0x6EE);
            PLAYER.step_s = 0;
        } else if (g_Player.unk72 == 1) {
            PLAYER.animFrameIdx = 0;
            PLAYER.animFrameDuration = 3;
        } else if (g_Player.unk72 == 2) {
            if (PLAYER.animFrameIdx != 0) {
                PLAYER.animFrameIdx = 1;
                PLAYER.animFrameDuration = 3;
            }
        } else if (g_Player.unk72 == 3) {
            if (PLAYER.animFrameIdx >= 2) {
                PLAYER.animFrameIdx = 2;
                PLAYER.animFrameDuration = 3;
                PLAYER.step = 2;
                PLAYER.step_s = 5;
            }
        } else if (g_Player.unk72 == 4) {
            if (PLAYER.animFrameIdx >= 3) {
                PLAYER.animFrameIdx = 3;
                PLAYER.animFrameDuration = 3;
                PLAYER.step = 2;
                PLAYER.step_s = 5;
            }
        }
        break;
    }
}

void func_80109A44(s32) { NOT_IMPLEMENTED; }
