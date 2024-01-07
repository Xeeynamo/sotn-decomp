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
SVECTOR* D_800A3210[1];
SVECTOR* D_800A33A0[1];
SVECTOR* D_800A34C0[18][3];
SVECTOR* D_800A3598[1];
SVECTOR* D_800A35D0[1];
SVECTOR* D_800A3608[1];
u8 D_800A3728;
MATRIX D_800A37B8;
s16 D_80136308[1];
u16 g_Clut[0x3000];
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
s16 D_800705CC[0x100];
PlayerDraw g_PlayerDraw[0x10];
s32 D_8013AED0;
DR_ENV D_800974AC;
u32 D_8003C744 = 0;
s32 D_800973F8;
s32 D_800973FC;
s32 D_80097400[3];
s32 D_8009740C[3];
s32 g_BottomCornerTextTimer;
s32 g_BottomCornerTextPrims;
s32 D_80097418;
s32 D_8009741C;
s32 D_80097420[1];
s32 D_80097424;
s32 D_80097448[2];
s32 D_80097450;
Pos D_80097488;
u32 mocked_800C52F8[0x200] = {0};
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
u8 D_8013B6A0[] = {0}; // VAB file
u8 D_8017D350[] = {0}; // VAB file
u8 D_8018B4E0[] = {0}; // VAB file
u8 D_801A9C80[] = {0}; // VAB file
u8 aPbav[] = {0};      // VAB file?
u8 aPbav_0[] = {0};    // VAB file?
u8 aPbav_1[] = {0};    // VAB file?
u8 aPbav_2[] = {0};    // VAB file?
u8 aPqes[] = {0};      // SEQ file
u8 aPqes_0[] = {0};    // SEQ file
u8 aPqes_1[] = {0};    // SEQ file
s32 D_801362D0[1];
s32 D_800987B4;
u8 g_PadsRepeatTimer[BUTTON_COUNT * PAD_COUNT];
s32 D_80136410;
s32 D_80136414[1];
ItemTypes D_801375CC;
s32 D_801375D0;
s32 D_801375D4;
s32* D_801375D8;
s32 D_801375DC[1];
s32 D_801375E0[8];
s32 D_801375FC;
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
s32 D_80139828[1];
s32 D_8013982C;
s32 D_80139830[1];
s32 D_8013983C;
s32 D_80139840;
s32 D_80139844;
s32 D_80139848;
s32 D_8013984C;
s32 D_80139850;
s32 D_80139854;
u16 D_80137538[32];
GfxBank g_FakeGfxBank = {0};
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
u8 g_GfxEquipIcon[32][16 * 16 / 2] = {0};
s16 g_PalEquipIcon[32] = {0};
UnkStructClut g_FakeUnkStruct = {0};
UnkStructClut* D_800A3BB8[] = {
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
u32 D_800AC90C = 0x000F423F;
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
    NULL,
};
ImgSrc* g_imgUnk8013C200 = &g_imgUnk8013C200_impl;
ImgSrc* g_imgUnk8013C270 = &g_imgUnk8013C200_impl;
s32 g_ExpNext[100] = {0};
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
u16 D_8013AEE0;
Unkstruct_800BF554 g_SfxData[1];
u16 D_8013AE7C;
s16 D_801390A4;
s16 D_80139010;
s8 D_8013B690;
s16 D_8013B678[1];
s16 D_8013B648[4];
s16 D_8013AEA0[4];
s32 D_8013B628[4];
u8 D_8013B5EC[4];
s16 D_8013B66C[4];
s8 g_UnkChannelSetting1[4];
s16 g_ChannelGroupVolume[4];
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
SpuVoiceAttr* D_801390C8;
SpuVoiceAttr* D_801390CC;
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
u8 D_8013B688[1];
u8 g_CdMode[3];

// TODO
struct XaMusicConfig g_XaMusicConfigs[6] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 3417, 0, 0, 80, 0, 1, 0, 0, 0},
    {8544, 5011, 0, 0, 80, 0, 0, 0, 0, 0},
    {21072, 8022, 10, 0, 64, 0, 1, 0, 0, 0},
    {41128, 3987, 10, 0, 64, 0, 0, 0, 0, 0},
    {51096, 7692, 20, 0, 84, 0, 1, 0, 0, 0}};

s8 D_801390C4;
u8 g_SeqPlayingId;
s16 g_SeqAccessNum;
volatile s16 g_CdSoundCommandQueuePos;
s16 g_SeqVolume1;
s16 g_SeqVolume2;
u8 g_ReverbDepth;
s32 g_SeqPointers[0xA];
s16 D_8013845C;
u8 D_8013B640[3];
s32 g_CurCdPos;
s16 g_CurrentXaConfigId;
s16 g_CdSoundCommandQueue[MAX_SND_COUNT];
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
s16 D_8013AED4[4];
s16 D_8013B650[4];
s32 g_CdCommandStatus;
const char* D_80138784[0x800];
s32 D_800C1ECC[1];
s32 D_8013B65C;

// sound stubs
void func_801327B4(int arg0, int arg1, int vabId, int prog, int tone, int note,
                   int g_VolL, int g_VolR) {
    NOT_IMPLEMENTED;
}

void func_80135D8C() { NOT_IMPLEMENTED; }

s32 func_80136010(void) {
    NOT_IMPLEMENTED;
    return 0;
}

void func_8013572C(int sndId, int unk02, int unk04) { NOT_IMPLEMENTED; }

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

void func_8010DFF0(s32 arg0, s32 arg1) { NOT_IMPLEMENTED; }

void func_800E5D30(void* arg0, u16 arg1, u16 arg2, s32 arg3) {
    NOT_IMPLEMENTED;
}

void func_801083BC(void) { NOT_IMPLEMENTED; }

void DrawRichterHudSubweapon(void) { NOT_IMPLEMENTED; }

void func_8010A234(s32 arg0) { NOT_IMPLEMENTED; }

void func_80109594(void) { NOT_IMPLEMENTED; }

void func_800F24F4(void) { NOT_IMPLEMENTED; }

void func_8011A4D0(void) { NOT_IMPLEMENTED; }

void func_800F2658(void) { NOT_IMPLEMENTED; }

void func_8011A9D8(void) { NOT_IMPLEMENTED; }

void func_8010BFFC(void) { NOT_IMPLEMENTED; }

void func_8011A870(void) { NOT_IMPLEMENTED; }

void func_8010DF70(void) { NOT_IMPLEMENTED; }

void func_8010E0D0(s32 arg0) { NOT_IMPLEMENTED; }

void func_80121F14(s32 arg0, s32 arg1) { NOT_IMPLEMENTED; }

void func_8010E168(s32 arg0, s16 arg1) { NOT_IMPLEMENTED; }

void func_800F1D54(s32 arg0, s32 arg1, s32 arg2, s32 arg3) { NOT_IMPLEMENTED; }

void func_800F1B08(s32 arg0, s32 arg1, s32 arg2) { NOT_IMPLEMENTED; }

void EntityAlucard(Entity* self) { NOT_IMPLEMENTED; }

s32 func_800F0CD8(s32 arg0) {
    NOT_IMPLEMENTED;
    return 0;
}

s32 func_8010E334(s32 xStart, s32 xEnd) {
    NOT_IMPLEMENTED;
    return 0;
}

s32 func_800FB23C(MenuNavigation* nav, u8* order, u8* count, u32* selected) {
    NOT_IMPLEMENTED;
    return 0;
}

void AddToInventory(u16 itemId, s32 itemCategory) { NOT_IMPLEMENTED; }

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
