#include "dra.h"
#include "objects.h"
#include "sfx.h"

void ExecCdSoundCommands(void) {
    if (*(u16*)&g_CdSoundCommandQueuePos == 0)
        return;

    switch (g_CdSoundCommandQueue[0]) {
    case CD_SOUND_COMMAND_FADE_OUT_2:
        CdFadeOut2();
        break;
    case CD_SOUND_COMMAND_FADE_OUT_1:
        CdFadeOut1();
        break;
    case CD_SOUND_COMMAND_START_XA:
        CdSoundCommand4();
        break;
    case CD_SOUND_COMMAND_6:
        CdSoundCommand6();
        break;
    case CD_SOUND_COMMAND_8:
        CdSoundCommand8();
        break;
    case CD_SOUND_COMMAND_10:
        CdSoundCommand10();
        break;
    case CD_SOUND_COMMAND_12:
        CdSoundCommand12();
        break;
    case CD_SOUND_COMMAND_14:
        CdSoundCommand14();
        break;
    case CD_SOUND_COMMAND_16:
        g_CdSoundCommand16 = 0;
    case 0:
        AdvanceCdSoundCommandQueue();
        break;
    }
}

void ApplyQuadChannelSetting(
    s16 arg0, s32 channel_group, s32 do_key_off, s32 volume, u16 arg4) {
    u16 volumeMod;
    u16 calcVolume;
    s32 progId;

    if (do_key_off != 0) {
        // do key off for 4 consecutive channels
        // channel_group 0 -> 0,1,2,3 etc.
        g_KeyOffChannels |=
            (1 << (channel_group * 4 + 0)) + (1 << (channel_group * 4 + 1)) +
            (1 << (channel_group * 4 + 2)) + (1 << (channel_group * 4 + 3));
    }

    volumeMod = volume;
    if (volumeMod == 0xFFFF) {
        g_ChannelGroupVolume[channel_group] =
            (D_8013AE7C * g_SfxData[arg0].volume) >> 7;
        g_UnkChannelSetting1[channel_group] = 0;
    } else {
        calcVolume = (D_8013AE7C * g_SfxData[arg0].volume) >> 7;
        g_ChannelGroupVolume[channel_group] = (calcVolume * volumeMod) >> 7;
        g_UnkChannelSetting1[channel_group] = arg4;
    }
    g_UnkChannelSetting2[channel_group] = arg0;
    D_8013B5EC[channel_group] = g_SfxData[arg0].unk4;
    progId = g_SfxData[arg0].prog + 1;
    D_8013B628[channel_group] = D_800C1ECC[progId];
    D_8013B66C[channel_group] = 0;
    D_8013B648[channel_group] = arg0;
    D_8013AEA0[channel_group] = g_SfxData[arg0].unk6;
}

void func_80135624(
    s16 arg0, s32 channel_group, s32 should_key_off, s16 volume, s16 distance) {
    if (should_key_off != 0) {
        // do key off for two channels
        // channel_group 0 -> 12, 13 etc.
        g_KeyOffChannels |= (1 << ((channel_group + 6) * 2)) +
                            (1 << (((channel_group + 6) * 2) + 1));
    }
    func_80132A04(
        (channel_group * 2) + 12, g_SfxData[arg0].vabid, g_SfxData[arg0].prog,
        g_SfxData[arg0].tone, g_SfxData[arg0].note, volume, distance);
    D_8013B650[channel_group] = arg0;
    D_8013AED4[channel_group] = g_SfxData[arg0].unk6;
}

INCLUDE_ASM("dra/nonmatchings/953A0", func_8013572C);

s16 IncrementRingBufferPos(s16 arg0) {
    arg0++;

    if (arg0 == LEN(g_SfxRingBuffer)) {
        arg0 = 0;
    }

    return arg0;
}

void ExecSfx(void) {
    s16 sfxBufPos;
    s32 isFound;
    s16 sndId;

    if (g_sfxRingBufferWritePos == g_SfxRingBufferReadPos)
        return;
    while (g_SfxRingBufferReadPos != g_sfxRingBufferWritePos) {
        sndId = g_SfxRingBuffer[g_SfxRingBufferReadPos].sndId;
        g_SfxRingBuffer[g_SfxRingBufferReadPos].sndId = 0;
        isFound = 0;
        for (sfxBufPos = IncrementRingBufferPos(g_SfxRingBufferReadPos);
             sfxBufPos != g_sfxRingBufferWritePos;
             sfxBufPos = IncrementRingBufferPos(sfxBufPos)) {
            if (sndId == g_SfxRingBuffer[sfxBufPos].sndId) {
                isFound = 1;
                break;
            }
        }
        if (isFound == 0) {
            func_8013572C(sndId, g_SfxRingBuffer[g_SfxRingBufferReadPos].unk02,
                          g_SfxRingBuffer[g_SfxRingBufferReadPos].unk04);
        }

        g_SfxRingBufferReadPos = IncrementRingBufferPos(g_SfxRingBufferReadPos);
    }
}

INCLUDE_ASM("dra/nonmatchings/953A0", func_80135D8C);
void func_80135D8C();

INCLUDE_ASM("dra/nonmatchings/953A0", func_80136010);

void func_801361F8(void) {
    if (g_SoundInitialized != 0) {
        func_80136010();
        ExecSfx();
        func_80135D8C();
        ExecSoundCommands();
        func_80133FCC();
        ExecCdSoundCommands();
        SpuSetKey(SPU_OFF, g_KeyOffChannels);
        g_KeyOffChannels = 0;
        func_80131FCC();

        if (g_MuteCd) {
            SetCdVolume(0, 0, 0);
        } else {
            SetCdVolume(0, g_CdVolume, g_CdVolume);
        }
    }
}

void nullsub_10(void) {}
