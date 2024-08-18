#include "dra.h"
#include "dra_bss.h"
#include "objects.h"
#include "sfx.h"

// BSS
extern s32 D_80138454;

void func_80131EBC(const char* str, s16 id) { D_80138784[id + 1] = str; }

// gets used later with MakeCdLoc
void SetCdPos(s32 value) { g_CurCdPos = value; }

void MuteCd(void) {
    g_MuteCd = 1;
    D_8013B694 = 0;
}

void UnMuteCd(void) {
    g_MuteCd = 0;
    D_8013B694++;
}

s32 func_80131F28(void) { return D_80138F7C; }

u16 func_80131F38(void) {
    if (g_SeqPlayingId == 0) {
        return 0;
    }
    return g_SeqPlayingId | 0x200;
}

bool func_80131F68(void) {
    if (D_8013B61C == 0) {
        return D_8013901C != 0;
    }
    return true;
}

s16 GetCdVolume(void) { return g_CdVolume; }

void SetReverbDepth(short depth) { SsUtSetReverbDepth(depth, depth); }

void func_80131FCC(void) {
    if (D_8013B680 == 0) {
        D_80138F7C = 0;
    } else {
        s32 temp_v1 = D_8013B680;
        s32 temp_v0 = D_8013B680;
        if (temp_v0 >= 0 && temp_v1 < 3)
            D_80138F7C++;
    }
    D_8013B680 = 0;
}

u8 DoCdCommand(u_char com, u_char* param, u_char* result) {
    g_CdCommandStatus = CdSync(1, g_CdCommandResult);

    if (com == CdlGetlocL) {
        if (g_CdCommandStatus != CdlComplete) {
            CdControl(CdlNop, 0, 0);
            D_8013B680 = 2;
            return D_8013B680;
        }
    } else if (*g_CdCommandResult & CdlStatShellOpen ||
               *g_CdCommandResult & CdlStatSeekError) {
        CdControl(CdlNop, 0, 0);
        D_8013B680 = 2;
        return D_8013B680;
    }

    if (g_CdCommandStatus == CdlComplete) {
        if (CdControl(com, param, result)) {
            D_8013B680 = 0;
            return D_8013B680;
        }
    }

    D_8013B680 = 1;
    return D_8013B680;
}

void SetMaxVolume(void) {
    g_volumeL = 127;
    g_volumeR = 127;
    SsSetMVol(g_volumeL, g_volumeR);
}

void InitSoundVars3(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        g_SfxScriptVolume[i] = 0;
        g_SfxScriptDistance[i] = 0;
        g_CurrentSfxScriptSfxId[i] = 0;
        g_SfxScriptTimer[i] = 0;
        g_SfxScriptUnk4[i] = 0;
        g_CurrentSfxScript[i] = 0;
        D_8013B648[i] = 0;
        g_SfxScriptUnk6[i] = 0;
    }
}

void InitSoundVars2(void) {
    s32 i;

    InitSoundVars3();
    D_8013B690 = 0;

    for (i = 0; i < NUM_CH_2; i++) {
        D_8013B650[i] = 0;
        D_8013AED4[i] = 0;
    }
    g_CurSfxId = 0;
    g_CurSfxId2 = 0;
}

void InitSoundVars1(void) {
    InitSoundVars2();
    g_CdSoundCommand16 = 0;
    for (D_80138454 = 0; D_80138454 < LEN(g_SeqPointers); D_80138454++) {
        g_SeqPointers[D_80138454] = 0;
    }
    for (D_80138454 = 0; D_80138454 < MAX_SND_COUNT; D_80138454++) {
        g_CdSoundCommandQueue[D_80138454] = 0;
    }

    g_CdSoundCommandQueuePos = 0;
    D_8013AEE8 = 0;
    for (D_80138454 = 0; D_80138454 < LEN(g_SoundCommandRingBuffer);
         D_80138454++) {
        g_SoundCommandRingBuffer[D_80138454] = 0;
    }

    g_SoundCommandRingBufferReadPos = 0;
    g_SoundCommandRingBufferWritePos = 0;
    for (D_80138454 = 0; D_80138454 < LEN(g_SfxRingBuffer); D_80138454++) {
        g_SfxRingBuffer[D_80138454].sndId = 0;
        g_SfxRingBuffer[D_80138454].sndVol = 0;
        g_SfxRingBuffer[D_80138454].sndPan = 0;
    }

    D_80139A6C = 0x20;
    g_SfxVolumeMultiplier = 0x7F;
    g_SfxRingBufferReadPos = 0;
    g_sfxRingBufferWritePos = 0;
    D_801390C4 = 0;
    g_CurSfxVol = 0;
    g_CurSfxDistance = 0;
    g_CurSfxVol2 = 0;
    g_CurSfxDistance2 = 0;
    D_80139A74 = 0;
    D_8013B69C = 0;
    g_SeqAccessNum = 0;
    D_80138FBC = 0;
    D_8013901C = 0;
    D_80139800 = 0;
    D_80138F80 = 0;
    D_80139014 = 0;
    D_8013B618 = 0;
    D_8013980C = 0;
    g_CdSoundCommandStep = 0;
    D_801390A0 = 0;
    g_SeqVolume1 = 0x70;
    g_SeqVolume2 = 0x70;
    D_8013B680 = 0;
    D_80138F7C = 0;
    D_801390D8 = 0;
    g_KeyOffChannels = 0;
    g_MuteCd = 0;
    D_8013B694 = 0;
    D_8013B61C = 0;
}

void SetCdVolume(s8 s_num, s16 arg1, s16 arg2) {
    short voll = g_CdVolumeTable[arg1];
    short volr = g_CdVolumeTable[arg2];

    SsSetSerialVol(s_num, voll, volr);
}

void SetMonoStereo(u8 soundMode) {
    CdlATV audioVolume;

    switch (soundMode) {
    case MONO_SOUND:
        if (D_801390A8 != 0) {
            SsSetMono();
            audioVolume.val2 = 128; // CD (R) --> SPU (R)
            audioVolume.val0 = 128; // CD (L) --> SPU (L)
            audioVolume.val3 = 128; // CD Right sound transferred to left
            audioVolume.val1 = 128; // CD Left sound transferred to right
            CdMix(&audioVolume);
            g_SfxVolumeMultiplier = 108;
            D_801390A8 = 0;
        }
        break;
    case STEREO_SOUND:
        if (D_801390A8 != 1) {
            SsSetStereo();
            audioVolume.val2 = 224; // CD (R) --> SPU (R)
            audioVolume.val0 = 224; // CD (L) --> SPU (L)
            audioVolume.val3 = 0;
            audioVolume.val1 = 0;
            CdMix(&audioVolume);
            g_SfxVolumeMultiplier = 127;
            D_801390A8 = 1;
        }
        break;
    }
}

void SoundInit(void) {
    g_SoundInitialized = 1;
    SsInitHot();
    SsSetTickMode(SS_TICK60);
    SetMonoStereo(STEREO_SOUND);
    SsSetReservedVoice(0x10);
    SsStart();
    SsSetTableSize(g_SeqTable, SEQ_TABLE_S_MAX, SEQ_TABLE_T_MAX);
    SsUtSetReverbType(SS_REV_TYPE_STUDIO_B);
    SpuClearReverbWorkArea(SS_REV_TYPE_STUDIO_B);
    SsUtReverbOn();
    SetMaxVolume();
    g_CdVolume = 0x78;
    SsSetSerialAttr(0, 0, 1);
    SetCdVolume(0, g_CdVolume, g_CdVolume);
    g_CdMode[0] = CdlModeSpeed | CdlModeRT | CdlModeSF;
    DoCdCommand(CdlSetmode, g_CdMode, 0);
    InitSoundVars1();
    SetReverbDepth(10);
    SpuSetTransferMode(0);
    SpuSetIRQCallback(NULL);
    CdReadyCallback(NULL);
    SpuMallocWithStartAddr(0x1010, 0x10000);
}

s32 func_801326D8(void) {
    if (D_8013901C)
        return 1;
    if (g_SeqPlayingId)
        return 3;
    if (D_801390D8)
        return 2;
    return 0;
}

void SoundWait(void) {
    while (!(func_801326D8() & 0xFF) == 0) {
        VSync(0);
        func_801361F8();
    }
}

void MuteSound(void) {
    SsSetMVol(0, 0);
    SsSetSerialAttr(SS_SERIAL_A, SS_MIX, SS_SOFF);
    SetCdVolume(SS_SERIAL_A, 0, 0);
    SetMaxVolume();
    InitSoundVars1();
}

void KeyOnRange(s32 minVoice, s32 maxVoice, s16 vabId, s16 prog, s16 tone,
                s16 note, s16 voll, s16 volr) {
    s32 i = minVoice;
    s32 didStuff = 0;

    for (; i < maxVoice; i += 2) {
        if (g_KeyStatus[i] != 0) {
            continue;
        }
        SsUtKeyOnV(i, vabId, prog, tone, note, 0, voll, volr);
        SsUtKeyOnV(i + 1, vabId, prog, tone + 1, note, 0, voll, volr);
        didStuff++;
        if (i == (maxVoice - 2)) {
            D_8013AEDC = minVoice;
        } else {
            D_8013AEDC = i + 2;
        }
        break;
    }
    if (!didStuff) {
        SsUtKeyOnV(D_8013AEDC, vabId, prog, tone, note, 0, voll, volr);
        // FAKE, needed to match registers
        i = voll;
        SsUtKeyOnV(D_8013AEDC + 1, vabId, prog, tone + 1, note, 0, voll, volr);
    }
}

// last entries seem like a different table
s16 g_CdVolumeTable[] = {
    0x0000, 0x0002, 0x0004, 0x0006, 0x0008, 0x000A, 0x000C, 0x000E, 0x0010,
    0x0012, 0x0014, 0x0016, 0x0018, 0x001A, 0x001C, 0x001E, 0x0020, 0x0022,
    0x0024, 0x0026, 0x0028, 0x002A, 0x002C, 0x002E, 0x0030, 0x0032, 0x0034,
    0x0036, 0x0038, 0x003A, 0x003C, 0x003E, 0x0040, 0x0041, 0x0042, 0x0043,
    0x0044, 0x0045, 0x0046, 0x0047, 0x0048, 0x0049, 0x004A, 0x004B, 0x004C,
    0x004D, 0x004E, 0x004F, 0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055,
    0x0056, 0x0057, 0x0058, 0x0059, 0x005A, 0x005B, 0x005C, 0x005D, 0x005E,
    0x005F, 0x0060, 0x0060, 0x0061, 0x0061, 0x0062, 0x0062, 0x0063, 0x0063,
    0x0064, 0x0064, 0x0065, 0x0065, 0x0066, 0x0066, 0x0067, 0x0067, 0x0068,
    0x0068, 0x0069, 0x0069, 0x006A, 0x006A, 0x006B, 0x006B, 0x006C, 0x006C,
    0x006D, 0x006D, 0x006E, 0x006E, 0x006F, 0x006F, 0x0070, 0x0070, 0x0071,
    0x0071, 0x0072, 0x0072, 0x0073, 0x0073, 0x0074, 0x0074, 0x0075, 0x0075,
    0x0076, 0x0076, 0x0077, 0x0077, 0x0078, 0x0078, 0x0079, 0x0079, 0x007A,
    0x007A, 0x007B, 0x007B, 0x007C, 0x007C, 0x007D, 0x007D, 0x007E, 0x007E,
    0x007F, 0x007F, 0x0000, 0x007F, 0x0010, 0x007F, 0x0020, 0x007F, 0x0030,
    0x007F, 0x0040, 0x007F, 0x0050, 0x007F, 0x0060, 0x007F, 0x0070, 0x007F,
    0x007F, 0x007F, 0x007F, 0x0070, 0x007F, 0x0060, 0x007F, 0x0050, 0x007F,
    0x0040, 0x007F, 0x0030, 0x007F, 0x0020, 0x007F, 0x0010, 0x007F, 0x0000};

s32 g_DebugEnabled = 0;
s32 D_800BD1C4 = 0;

#ifdef VERSION_US
s32 g_VabAddrs[] = {0x00001010, 0x00042CC0, 0x00050E50,
                    0x00060A40, 0x00060A40, 0x00060A40};
#else // VERSION_HD
s32 g_VabAddrs[] = {0x00001010, 0x00042CC0, 0x00050E90,
                    0x00060D40, 0x00060D40, 0x00060D40};
#endif

// clang-format off
struct SeqData g_SeqInfo[] = {
    {0x7f, 0x3c, {0, 0}},
    {0x6c, 0x20, {0, 0}},
    {0x62, 0x30, {0, 0}},
    {0x60, 0x30, {1, 0}},
    {0x70, 0x40, {1, 3}},
    {0x68, 0x40, {1, 0}},
    {0x68, 0x40, {1, 3}},
    {0x68, 0x40, {1, 3}},
    {0x68, 0x40, {1, 3}},
    {0x68, 0x40, {1, 3}},
    {0x68, 0x40, {1, 3}},
    {0x68, 0x40, {1, 3}},
    {0x68, 0x40, {1, 3}},
    {0x68, 0x40, {1, 3}},
    {0x68, 0x40, {1, 3}},
    {0x68, 0x40, {1, 3}},
    {0x68, 0x40, {1, 3}},
    {0x68, 0x40, {1, 3}},
    {0x68, 0x40, {1, 3}},
    {0x68, 0x40, {1, 3}},
    {0x68, 0x40, {1, 3}},
    {0x68, 0x40, {1, 3}}
};
// clang-format on

void func_80132A04(s16 voice, s16 vabId, s16 prog, s16 tone, s16 note,
                   s16 volume, s16 distance) {
    if (distance == 0) {
        g_VolL = volume;
        g_VolR = volume;
    } else {
        g_VolR = (volume * g_CdVolumeTable[distance * 2 + 144]) >> 7;
        g_VolL = (volume * g_CdVolumeTable[distance * 2 + 145]) >> 7;
    }

    // hardware voices 0-24
    if (voice >= 0 && voice < 24) {
        SsUtKeyOnV(voice, vabId, prog, tone, note, 0, g_VolL, g_VolR);
        SsUtKeyOnV(voice + 1, vabId, prog, 1 - -tone, note, 0, g_VolL, g_VolR);
        return;
    }

    // virtual voices 30-33 map to hardware channels 0-4,4-8,8-12,14-18
    switch (voice) {
    case 30:
        KeyOnRange(0, 4, vabId, prog, tone, note, g_VolL, g_VolR);
        break;
    case 31:
        KeyOnRange(4, 8, vabId, prog, tone, note, g_VolL, g_VolR);
        break;
    case 32:
        KeyOnRange(8, 12, vabId, prog, tone, note, g_VolL, g_VolR);
        break;
    case 33:
        KeyOnRange(14, 18, vabId, prog, tone, note, g_VolL, g_VolR);
        break;
    }
}

void AddCdSoundCommand(s16 arg0) {
    s32 i;
    s32 isFound;

    if (arg0 == CD_SOUND_COMMAND_6) {
        isFound = 0;
        for (i = 0; i < g_CdSoundCommandQueuePos; i++) {
            if (g_CdSoundCommandQueue[i] == CD_SOUND_COMMAND_12) {
                isFound = 1;
            }
        }

        if (isFound) {
            g_DebugEnabled++;
            g_CdSoundCommandQueue[g_CdSoundCommandQueuePos] =
                CD_SOUND_COMMAND_14;
            g_CdSoundCommandQueuePos++;
            if (g_CdSoundCommandQueuePos == MAX_SND_COUNT) {
                D_8013AEE8++;
                for (i = 1; i < MAX_SND_COUNT; i++) {
                    g_CdSoundCommandQueue[i] = 0;
                }

                g_CdSoundCommandQueuePos = 1;
                g_CdSoundCommandQueue[g_CdSoundCommandQueuePos] =
                    CD_SOUND_COMMAND_14;
                g_CdSoundCommandQueuePos++;
            }
        }
    }
    g_CdSoundCommandQueue[g_CdSoundCommandQueuePos] = arg0;
    g_CdSoundCommandQueuePos++;
    if (g_CdSoundCommandQueuePos == MAX_SND_COUNT) {
        D_8013AEE8++;
        for (i = 1; i < MAX_SND_COUNT; i++) {
            g_CdSoundCommandQueue[i] = 0;
        }

        g_CdSoundCommandQueuePos = 1;
    }
}

u16 AdvanceCdSoundCommandQueue(void) {
    s32 i;

    for (i = 0; i < MAX_SND_COUNT - 1; i++) {
        g_CdSoundCommandQueue[i] = g_CdSoundCommandQueue[i + 1];
    }
    return --g_CdSoundCommandQueuePos;
}

#define ENCODE_BCD(x) ((((x) / 10) << 4) + ((x) % 10))

void MakeCdLoc(u32 address, CdlLOC* cd_loc) {
    u32 minutes;
    cd_loc->sector = ENCODE_BCD(address % 75);
    cd_loc->second = ENCODE_BCD(address / 75 % 60);
    minutes = address / 75 / 60;
    cd_loc->minute = ENCODE_BCD(minutes);
}
