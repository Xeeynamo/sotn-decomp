#include <unistd.h>

#include "dra.h"
#include "objects.h"
#include "sfx.h"

// psy-q stubs
short SsUtSetVVol(short vc, short voll, short volr) {
    printf("SsUtSetVVol\n");
    return 0;
}

void SpuSetVoiceAttr(SpuVoiceAttr* arg) { printf("SpuSetVoiceAttr\n"); }

void SsSetSerialAttr(char s_num, char attr, char mode) {
    printf("SsSetSerialAttr\n");
}

int VSync(int mode) {
    printf("VSync\n");
    return 0;
}

void SsSeqPlay(s16 seq_access_num, s8 play_mode, s16 l_count) {
    printf("SsSeqPlay\n");
}

void SsSetMVol(short voll, short volr) { printf("SsSetMVol\n"); }

void SsSeqSetVol(s16 arg0, s32 arg1, s32 arg2) { printf("SsSeqSetVol\n"); }

short SsSeqOpen(u_long* addr, short vab_id) {
    printf("SsSeqOpen\n");
    return 0;
}

void SsSeqClose(short seq_access_num) { printf("SsSeqClose\n"); }

void SsSeqStop(short seq_access_num) { printf("SsSeqStop\n"); }

short SsUtKeyOnV(short voice, short vabId, short prog, short tone, short note,
                 short fine, short voll, short volr) {
    printf("SsUtKeyOnV\n");
    return 0;
}

long SpuMallocWithStartAddr(unsigned long addr, long size) {
    printf("SpuMallocWithStartAddr\n");
}

CdlCB CdReadyCallback(CdlCB func) {
    printf("CdReadyCallback\n");
    return func;
}

SpuIRQCallbackProc SpuSetIRQCallback(SpuIRQCallbackProc in) {
    printf("SpuSetIRQCallback\n");
    return in;
}

long SpuSetTransferMode(long mode) {
    printf("SpuSetTransferMode\n");
    return 0;
}

void SsUtReverbOn(void) { printf("SsUtReverbOn\n"); }

long SpuClearReverbWorkArea(long rev_mode) {
    printf("SpuClearReverbWorkArea\n");
    return 0;
}

void SsUtSetReverbType(short type) { printf("SsUtSetReverbType\n"); }

void SsSetTableSize(char* table, short s_max, short t_max) {
    printf("SsSetTableSize\n");
}

void SsStart(void) { printf("SsStart\n"); }

char SsSetReservedVoice(char voices) {
    printf("SsSetReservedVoice %d\n", voices);
    return 0;
}

void SsSetTickMode(long tick_mode) { printf("SsSetTickMode %d\n", tick_mode); }

void SsInitHot(void) { printf("SsInitHot\n"); }

int CdMix(CdlATV* vol) {
    printf("CdMix\n");
    return 0;
}

void SsSetStereo(void) { printf("SsSetStereo\n"); }

void SsSetMono(void) { printf("SsSetMono\n"); }

void SsSetSerialVol(short s_num, short voll, short volr) {
    printf("SsSetSerialVol s_num %d voll %d volr %d\n");
}

int CdControl(u_char com, u_char* param, u_char* result) {
    printf("CdControl: com %d\n", com);
    return 1;
}

int CdSync(int mode, u_char* result) {
    printf("CdSync: mode %0d\n", mode);
    return CdlComplete;
}

void SsUtSetReverbDepth(short ldepth, short rdepth) {
    printf("SsUtSetReverbDepth ldepth %d rdepth %d\n");
}

void SpuSetKey(long on_off, unsigned long voice_bit) {
    printf("SpuSetKey on_off %d voice_bit %08X\n");
}

// sound stubs
void func_801327B4(int arg0, int arg1, int vabId, int prog, int tone, int note,
                   int g_VolL, int g_VolR) {
    printf("func_801327B4\n");
}

void func_80133FCC(void) { printf("func_80133FCC\n"); }

void func_80135D8C() { printf("func_80135D8C\n"); }

s32 func_80136010(void) {
    printf("func_80136010\n");
    return 0;
}

void func_8013572C(int sndId, int unk02, int unk04) {
    printf("func_8013572C\n");
}

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
const char* D_80138784[487];
s32 D_800C1ECC[];

int main() {
    bool init = false;
    int frame = 0;
    while (true) {
        printf("-------------------- frame %d --------------------\n", frame);
        if (!init) {
            SoundInit();
            PlaySfx(MU_LOST_PAINTING);
            init = true;
        }
        func_801361F8();
        usleep((1001.0/60.0)*1000.0); // 59.94 fps (16.68 ms)
        frame++;
    }
}
