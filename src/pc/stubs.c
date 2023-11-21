#include "pc.h"
#include "dra.h"

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
u32 g_CdStep;
GameState g_GameState;
Entity g_Entities[TOTAL_ENTITY_COUNT];
FgLayer D_8003C708;
s16 D_8003C710;
s16 D_8003C712;
s32 D_8003C728;
s32 D_8003C730;
s32 g_IsUsingCd;
GpuUsage g_GpuUsage;
PlayerStatus g_Status;
u32 g_randomNext;
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
u32 D_800A04F8;
s16 D_80136308[];
u16 g_Clut[];
s32 D_8006C384;
s32 D_8006C388;
GameSettings g_Settings;
s32 D_8006C384;
s32 D_8006C388;
s32 D_8006C38C;
s32 D_8006C390;
u16 D_8003C104[];

// dra.h
void* g_ApiInit[sizeof(GameApi) / sizeof(void*)] = {0};
GpuUsage g_GpuMaxUsage;
GpuBuffer* g_BackBuffer;
s32 g_DebugFreeze;
s32 g_DebugHitboxViewMode;
u32 D_801362B4;
u32 g_DebugCurPal;
s32 D_801362D4;
RoomTeleport D_800A245C[];
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
s32 D_800A2438;
s32 D_801362D0[];
s32 D_800987B4;
u8 g_PadsRepeatTimer[BUTTON_COUNT * PAD_COUNT];

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
Unkstruct_800BF554 g_SfxData[];
u16 D_8013AE7C;
s16 D_801390A4;
s16 D_80139010;
s8 D_8013B690;
s16 D_8013B678[];
s16 D_8013B648[4];
s16 D_8013AEA0[4];
s32 D_8013B628[4];
u8 D_8013B5EC[4];
s16 D_8013B66C[4];
s8 g_UnkChannelSetting1[4];
s16 g_ChannelGroupVolume[4];
s16 g_UnkChannelSetting2[4];
s32 D_801390B4[];
s8 D_80139018[];
s16 D_80139814[];
s8 D_80139058[];
s16 D_801390AC[];
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
struct Cmd14 D_8013B5F4[];
s32 D_8013AE90;
s32 D_8013AEF4;
u8 g_CdCommandResult[];
u8 D_8013B688[];
u8 g_CdMode[3];

// TODO
struct XaMusicConfig g_XaMusicConfigs[2] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 3417, 0, 0, 80, 0, 1, 0, 0, 0}};

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
s32 D_800C1ECC[];

// sound stubs
void func_801327B4(int arg0, int arg1, int vabId, int prog, int tone, int note,
                   int g_VolL, int g_VolR) {
    DEBUGF("not implemented");
}

void func_80133FCC(void) { DEBUGF("not implemented"); }

void func_80135D8C() { DEBUGF("not implemented"); }

s32 func_80136010(void) {
    DEBUGF("not implemented");
    return 0;
}

void func_8013572C(int sndId, int unk02, int unk04) {
    DEBUGF("not implemented");
}

void func_801073C0(void) { DEBUGF("not implemented"); }

void func_800EAD7C(void) { DEBUGF("not implemented"); }

void HideAllBackgroundLayers(void) { DEBUGF("not implemented"); }

void DestroyAllPrimitives(void) { DEBUGF("not implemented"); }

void DestroyEntities(s16 startIndex) { DEBUGF("not implemented"); }

void SetupEvents(void) { DEBUGF("not implemented"); }

s32 LoadFileSim(s32 fileId, SimFileType type) {
    DEBUGF("not implemented");
    return 0;
}

void ResetPendingGfxLoad(void) { DEBUGF("not implemented"); }

void func_800EA538(s32 arg0) { DEBUGF("not implemented"); }

void func_800EA7CC(void) { DEBUGF("not implemented"); }

void func_800EDAE4(void) { DEBUGF("not implemented"); }

void VSyncHandler(void) { DEBUGF("not implemented"); }

void InitRenderer(void) { DEBUGF("not implemented"); }

void RenderEntities(void) { DEBUGF("not implemented"); }

void RenderTilemap(void) { DEBUGF("not implemented"); }

void RenderPrimitives(void) { DEBUGF("not implemented"); }

void DrawEntitiesHitbox(s32 blendMode) { DEBUGF("not implemented"); }

void UpdateCd(void) { DEBUGF("not implemented"); }

void LoadPendingGfx(void) { DEBUGF("not implemented"); }

int CdInit(void) {
    DEBUGF("not implemented");
    return 0;
}

void func_8010DFF0(s32 arg0, s32 arg1) { DEBUGF("not implemented"); }

void ResetEntityArray(void) { DEBUGF("not implemented"); }

void ResetPadsRepeat(void) {
    s8* ptr;
    s32 i;

    g_pads[0].repeat = 0;
    ptr = g_PadsRepeatTimer;

    for (i = 0; i < LEN(g_PadsRepeatTimer); i++) {
        *ptr++ = 0x10;
    }
}

void InitializePads(void) {
    Pad* pad;
    s32 i;

    PadInit(0);
    for (pad = g_pads, i = 0; i < PAD_COUNT; i++, pad++) {
        pad->tapped = 0;
        pad->previous = 0;
        pad->pressed = 0;
    }
    ResetPadsRepeat();
}

void ReadPads(void) {
    Pad* pad;
    s32 i;
    u_long padd;

    for (pad = g_pads, i = 0; i < PAD_COUNT; i++, pad++) {
        pad->previous = pad->pressed;
        padd = PadRead(i >> 1);
        if (!(i & 1))
            pad->pressed = padd;
        else
            pad->pressed = padd >> 0x10;
        pad->tapped = (pad->pressed ^ pad->previous) & pad->pressed;
    }
    ResetPadsRepeat();
}
