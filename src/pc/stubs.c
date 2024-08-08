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
s32 g_entityDestroyed[18] = {0};
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
s32 g_PlayerX;
s32 g_PlayerY;
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
s32 g_MapCursorTimer;
s32 g_PlayableCharacter;
s32 g_backbufferX;
s32 g_backbufferY;
u32 g_Timer;
s32 D_80097904;
s32 g_ScrollDeltaX;
s32 g_ScrollDeltaY;
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
s16 D_80136308[0x80];
u16 g_Clut[0x3000];
u16 D_8006EBCC[0x1000]; // part of g_Clut?
u16 D_8006EBE0;
Point32 D_8006C384;
MenuNavigation g_MenuNavigation;
GameSettings g_Settings;
Point32 D_8006C38C;
s32 g_CurrentStream;
u16 g_ClutIds[0x400];
s32 D_8003C738;
u8 g_CastleFlags[0x300];
s32 D_8006C374;
s32 D_8006C378;
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
Event g_EvSwCardNew;
s32 g_PrevScrollX;
s32 g_PrevScrollY;
s32 D_80073080;
s32 g_IsTimeAttackUnlocked;
bool D_8003C908;
s32 D_8003C100;
s32 D_800978B4;
u32 g_RoomCount;
char D_80097902[] = "dummy";
s32 g_EquippedWeaponIds[2] = {0};
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
s32 D_80097448[2];
s32 D_80097450;
Pos D_80097488;

// dra.h
u16 D_800AC958[] = {
    0x0200, 0x0220, 0x0200, 0x0220, 0x0240, 0x0260, 0x0240, 0x0260,
    0x0280, 0x02A0, 0x0280, 0x02A0, 0x02C0, 0x02E0, 0x02C0, 0x02E0,
    0x0300, 0x0320, 0x0300, 0x0320, 0x0340, 0x0360, 0x0340, 0x0360,
    0x0380, 0x03A0, 0x0380, 0x03A0, 0x03C0, 0x03E0, 0x03C0, 0x03E0,
};
s32 D_80138090;
mistStruct D_80138094[16];
s32 D_8013808C;
s16 D_801381D4;
s16 D_801381D8;
s16 D_801381DC;
s16 D_801381E0;
s16 D_801381E4;
s16 D_801381E8;
s16 D_801381EC;
s16 D_801381F0;
Primitive D_801381F4[8]; // unknown size
GpuUsage g_GpuMaxUsage;
GpuBuffer* g_BackBuffer;
s32 g_DebugFreeze;
s32 g_DebugHitboxViewMode;
u32 D_801362B4;
u32 g_DebugCurPal;
s32 D_801362D4;
s32 D_8013640C;
s32 D_800974A4;
OT_TYPE* g_CurrentOT;
s32 D_801362B8;
s32 D_801362BC;
s32 g_DebugPlayer;
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
u8 D_8018B4E0[108048] = {0}; // VB file
u8 D_801A9C80[64496] = {0};  // VB file
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
EquipKind D_801375CC;
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
s16 D_8013767C;
s16 D_80137688;
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
s32 g_NewPlayerStatsTotal[4];
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
VECTOR D_801379E0[20];
VECTOR D_80137B20[24];
SVECTOR D_80137CA0[20];
SVECTOR D_80137D40[24];
SVECTOR D_80137E70[14] = {0};
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
u8* g_DecSrcPtr = NULL;
u8* g_DecDstPtr = NULL;
s32 g_DecReadNibbleFlag = 0;
s32 g_DecWriteNibbleFlag = 0;
u8 g_GfxEquipIcon[320][16 * 16 / 2];
s16 g_PalEquipIcon[320 * 16];
u16 D_80137478[0x20];
u16 D_801374B8[0x20];
u16 D_801374F8[0x20];
u16 D_80137538[0x20];
u32 g_DisplayHP[1];
PlayerHud g_PlayerHud;
s32 D_8013B5E8;
s32 g_HealingMailTimer[1] = {0};
s32 D_8013B5E8;
s32 D_80139008;
s32 D_801397FC;
SimFile* g_SimFile;
SimFile D_80136450;
s16 D_80136460[0x400] = {0};
s16 D_80136C60[0x400] = {0};
u16 D_8006ED0C[0x10] = {0};
u16 D_8006ED2C[0x10] = {0};
u16 D_8006ED4C[0x10] = {0};

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
s32 D_80139060;
u32 D_8013799C;
s32 D_801379A0;
s32 D_801379A4;
s32 D_801379A8;
Unkstruct_80102CD8 D_801379AC;
s32 D_801379B0;
SVECTOR D_801379C0;
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
s32 D_80137FEC;
s32 D_80137FF0;
u32 g_WingSmashButtonCounter;
s32 g_WingSmashButtonTimer;
s32 g_WingSmashTimer;
s32 g_BatScreechDone;
s32 g_MistTimer;
s32 D_80138008;
s32 D_8013800C[100]; // random size to play safe
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
PlayerOvl g_PlOvl = {0};
u8** g_PlOvlAluBatSpritesheet[1] = {0};

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
s32 D_8013AEBC[4];
s32 D_8013AECC;
u16 D_8013AEE0;
Unkstruct_800BF554 g_SfxData[737];
u16 D_8013AE7C;
s16 D_801390A4;
s16 D_80139010;
s8 D_8013B690;
s16 D_8013B678[4];
s16 D_8013B648[4];
s16 D_8013AEA0[4];
u16 D_8013B626;
s8* g_CurrentSfxScript[4];
u8 D_8013B5EC[4];
u8 D_8013B5F6[32];
s16 g_SfxScriptTimer[4];
s16 D_8013B672[1];
s8 g_UnkChannelSetting1[4];
u16 g_SfxScriptVolume[4];
s16 g_CurrentSfxScriptSfxId[4];
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
SpuVoiceAttr D_80138FB4_;
SpuVoiceAttr* D_80138FB4 = &D_80138FB4_;
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
s32 D_8013843C;
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
s16 D_801396E0;
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
s32 D_8013841C;
RECT D_80138424;
s32 D_8013842C;
s32 D_80138430;
s32 D_80138438;
s32 D_80138440;
s32 D_80138444;
s32 D_80138448;
s32 D_8013844C;
s32 D_80138450;
s32 D_80138454;
s32 D_80138394;
s32 D_80138398;
Point16 D_8013839C[12];
Point16 D_8013804C[16];
u32 D_80139A7C[0x1400] = {0};

// sound stubs

void SpuGetAllKeysStatus(char* status) { NOT_IMPLEMENTED; }

void func_801073C0(void) { NOT_IMPLEMENTED; }

void UpdateCd(void) { NOT_IMPLEMENTED; }

int CdInit(void) {
    NOT_IMPLEMENTED;
    return 0;
}

void func_801083BC(void) { NOT_IMPLEMENTED; }

u16 g_FontCharData[0x60] = {1, 1, 1, 0, 0, 0};
u16* func_80106A28(u32 arg0, u16 kind) {
    NOT_IMPLEMENTED;
    return g_FontCharData;
}

// ric stubs

SubweaponDef D_80154688[1];
FactoryBlueprint g_RicFactoryBlueprints[1];
