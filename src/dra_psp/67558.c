// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

extern s8* D_psp_09190C18[];

// requires func_psp_09141488 (AdvanceCdSoundCommandQueue) to be static in the
// same file, https://decomp.me/scratch/9rjfX
INCLUDE_ASM("dra_psp/psp/dra_psp/67558", ExecCdSoundCommands);

void PlaySfxScript(
    s16 arg0, s32 channel_group, bool do_key_off, u16 volume, s16 distance) {
    u16 calcVolume;
    s16 progId;

    if (volume == 0xFFFF) {
        g_SfxScriptVolume[channel_group] =
            (g_SfxVolumeMultiplier * g_SfxData[arg0].volume) >> 7;
        g_SfxScriptDistance[channel_group] = 0;
    } else {
        calcVolume = (g_SfxVolumeMultiplier * g_SfxData[arg0].volume) >> 7;
        g_SfxScriptVolume[channel_group] = (calcVolume * volume) >> 7;
        g_SfxScriptDistance[channel_group] = distance;
    }
    g_CurrentSfxScriptSfxId[channel_group] = arg0;
    g_SfxScriptMode[channel_group] = g_SfxData[arg0].mode;
    progId = g_SfxData[arg0].prog + 1;
    g_CurrentSfxScript[channel_group] = D_psp_09190C18[progId];
    g_SfxScriptTimer[channel_group] = 0;
    g_CurrentSfxScriptSfxId2[channel_group] = arg0;
    g_SfxScriptUnk6[channel_group] = g_SfxData[arg0].unk6;
}

// channel group is 0-3 so play on one of these pairs:
// (12,13),(14,15),(16,17),(18,19)
void KeyOn12_19(
    s16 arg0, s32 channel_group, bool do_key_off, u16 volume, s16 distance) {
    func_80132A04(
        (channel_group * 2) + 12, g_SfxData[arg0].vabid, g_SfxData[arg0].prog,
        g_SfxData[arg0].tone, g_SfxData[arg0].note, volume, distance);
    g_CurrentSfxId12_19[channel_group] = arg0;
    D_8013AED4[channel_group] = g_SfxData[arg0].unk6;
}

void func_8013572C(s16 arg0, u16 volume, s16 distance) {
    s32 i;

    if (!arg0) {
        return;
    }
    if (g_SfxData[arg0].vabid == 9) {
        if (!g_SeqIsPlaying) {
            for (i = 0; i < 3; i++) {
                if (arg0 == g_CurrentSfxScriptSfxId2[i]) {
                    PlaySfxScript(arg0, i, true, volume, distance);
                    return;
                }
            }
            for (i = 0; i < 3; i++) {
                if (g_CurrentSfxScriptSfxId2[i] == 0) {
                    PlaySfxScript(arg0, i, false, volume, distance);
                    return;
                }
            }
            for (i = 0; i < 3; i++) {
                if (g_SfxData[arg0].unk6 > g_SfxScriptUnk6[i]) {
                    PlaySfxScript(arg0, i, true, volume, distance);
                    return;
                }
            }
            for (i = 0; i < 3; i++) {
                if (g_SfxData[arg0].unk6 == g_SfxScriptUnk6[i]) {
                    PlaySfxScript(arg0, i, true, volume, distance);
                    return;
                }
            }
            return;
        }
        if (g_SfxData[arg0].unk6 >= g_SfxScriptUnk6[3]) {
            PlaySfxScript(arg0, 3, true, volume, distance);
        }
    } else {
        switch (g_SfxData[arg0].mode) {
        case SFX_MODE_CHANNELS_22_23:
            g_CurSfxId22_23 = arg0;
            if (volume == 0xFFFF) {
                g_CurSfxVol22_23 = 0x7F;
            } else {
                g_CurSfxVol22_23 = volume;
            }
            g_CurSfxDistance22_23 = distance;
            KeyOnChannels22_23();
            break;

        case SFX_MODE_CHANNELS_20_21:
            g_CurSfxId20_21 = arg0;
            if (volume == 0xFFFF) {
                g_CurSfxVol20_21 = 0x7F;
            } else {
                g_CurSfxVol20_21 = volume;
            }
            g_CurSfxDistance20_21 = distance;
            KeyOnChannels20_21();
            break;

        case SFX_MODE_RELEASE_22_23:
            SetReleaseRateLow_22_23();
            g_CurSfxId22_23 = 0;
            break;

        case SFX_MODE_CHANNELS_12_19:
            g_CurSfxVol12_19 =
                (g_SfxVolumeMultiplier * g_SfxData[arg0].volume) >> 7;
            if (volume == 0xFFFF) {
                g_CurSfxDistance12_19 = 0;
            } else {
                g_CurSfxVol12_19 = (g_CurSfxVol12_19 * volume) >> 7;
                g_CurSfxDistance12_19 = distance;
            }
            if (!g_SeqIsPlaying) {
                for (i = 0; i < 4; i++) {
                    if (arg0 == g_CurrentSfxId12_19[i]) {
                        KeyOn12_19(arg0, i, true, g_CurSfxVol12_19,
                                   g_CurSfxDistance12_19);
                        return;
                    }
                }
                for (i = 0; i < 4; i++) {
                    if (g_CurrentSfxId12_19[i] == 0) {
                        KeyOn12_19(arg0, i, false, g_CurSfxVol12_19,
                                   g_CurSfxDistance12_19);
                        return;
                    }
                }
                for (i = 0; i < 4; i++) {
                    if (g_SfxData[arg0].unk6 > D_8013AED4[i]) {
                        KeyOn12_19(arg0, i, true, g_CurSfxVol12_19,
                                   g_CurSfxDistance12_19);
                        return;
                    }
                }
                for (i = 0; i < 3; i++) {
                    if (g_SfxData[arg0].unk6 == D_8013AED4[i]) {
                        KeyOn12_19(arg0, i, true, g_CurSfxVol12_19,
                                   g_CurSfxDistance12_19);
                        return;
                    }
                }
                return;
            }
            if (g_CurrentSfxId12_19[3] == 0) {
                KeyOn12_19(
                    arg0, 3, false, g_CurSfxVol12_19, g_CurSfxDistance12_19);
            } else if (g_SfxData[arg0].unk6 >= D_8013AED4[3]) {
                KeyOn12_19(
                    arg0, 3, true, g_CurSfxVol12_19, g_CurSfxDistance12_19);
            }
            break;
        }
    }
}

s16 IncrementRingBufferPos(s16 sfxBufPos) {
    if (++sfxBufPos == LEN(g_SfxRingBuffer)) {
        sfxBufPos = 0;
    }

    return sfxBufPos;
}

void ExecSfx(void) {
    s16 sndId;
    s16 sfxBufPos;
    bool isFound;

    if (g_sfxRingBufferWritePos == g_SfxRingBufferReadPos) {
        return;
    }
    while (g_SfxRingBufferReadPos != g_sfxRingBufferWritePos) {
        sndId = g_SfxRingBuffer[g_SfxRingBufferReadPos].sndId;
        g_SfxRingBuffer[g_SfxRingBufferReadPos].sndId = 0;
        sfxBufPos = IncrementRingBufferPos(g_SfxRingBufferReadPos);
        isFound = false;
        while (sfxBufPos != g_sfxRingBufferWritePos) {
            if (sndId == g_SfxRingBuffer[sfxBufPos].sndId) {
                isFound = true;
                break;
            }
            sfxBufPos = IncrementRingBufferPos(sfxBufPos);
        }
        if (!isFound) {
            func_8013572C(sndId, g_SfxRingBuffer[g_SfxRingBufferReadPos].sndVol,
                          g_SfxRingBuffer[g_SfxRingBufferReadPos].sndPan);
        }
        g_SfxRingBufferReadPos = IncrementRingBufferPos(g_SfxRingBufferReadPos);
    }
}

void func_80135D8C(void) {
    s32 i;

    s16 vab;
    s16 prog;
    s16 tone;
    s16 note;
    s16 volume;
    s16 distance;

    if (g_SeqIsPlaying == 0) {
        for (i = 0; i < 3; i++) {
            if (!g_CurrentSfxScriptSfxId[i]) {
                continue;
            }
            if (g_SfxScriptTimer[i] == 0) {
                vab = *g_CurrentSfxScript[i]++;
                if (vab == -1) {
                    g_CurrentSfxScriptSfxId[i] = 0;
                } else {
                    prog = *g_CurrentSfxScript[i]++;
                    note = *g_CurrentSfxScript[i]++;
                    tone = *g_CurrentSfxScript[i]++;
                    volume = *g_CurrentSfxScript[i]++;
                    volume = (g_SfxScriptVolume[i] * volume) >> 7;
                    g_SfxScriptTimer[i] = *g_CurrentSfxScript[i]++;
                    distance = g_SfxScriptDistance[i];
                    func_80132A04(
                        i + 30, vab, prog, tone, note, volume, distance);
                }
            } else {
                g_SfxScriptTimer[i]--;
            }
        }
    } else {
        if (g_CurrentSfxScriptSfxId[3] != 0) {
            if (g_SfxScriptTimer[3] == 0) {
                vab = *g_CurrentSfxScript[3]++;
                if (vab == -1) {
                    g_CurrentSfxScriptSfxId[3] = 0;
                } else {
                    prog = *g_CurrentSfxScript[3]++;
                    note = *g_CurrentSfxScript[3]++;
                    tone = *g_CurrentSfxScript[3]++;
                    volume = *g_CurrentSfxScript[3]++;
                    volume = (g_SfxScriptVolume[3] * volume) >> 7;
                    g_SfxScriptTimer[3] = *g_CurrentSfxScript[3]++;
                    distance = g_SfxScriptDistance[3];
                    func_80132A04(33, vab, prog, tone, note, volume, distance);
                }
            } else {
                g_SfxScriptTimer[3]--;
            }
        }
    }
}

void func_80136010(void) {
    s32 i;
    s8 sum;

    SpuGetAllKeysStatus(g_KeyStatus);
    if (g_SeqIsPlaying == 0) {
        for (i = 0; i < 4; i++) {
            sum = g_KeyStatus[i * 2 + 12] + g_KeyStatus[i * 2 + 13];
            if (sum == 0) {
                g_CurrentSfxId12_19[i] = 0;
                D_8013AED4[i] = 0;
            }
        }
    } else {
        sum = g_KeyStatus[18] + g_KeyStatus[19];
        if (sum == 0) {
            g_CurrentSfxId12_19[3] = 0;
            D_8013AED4[3] = 0;
        }
    }
    if (g_SeqIsPlaying == 0) {
        for (i = 0; i < 3; i++) {
            if (g_CurrentSfxScriptSfxId[i] == 0) {
                sum = g_KeyStatus[i * 4 + 0] + g_KeyStatus[i * 4 + 1] +
                      g_KeyStatus[i * 4 + 2] + g_KeyStatus[i * 4 + 3];
                if (sum == 0) {
                    g_CurrentSfxScriptSfxId2[i] = 0;
                    g_SfxScriptUnk6[i] = 0;
                }
            }
        }
        return;
    }
    if (g_CurrentSfxScriptSfxId[3] == 0) {
        sum = g_KeyStatus[14] + g_KeyStatus[15] + g_KeyStatus[16] +
              g_KeyStatus[17];
        if (sum == 0) {
            g_CurrentSfxScriptSfxId2[3] = 0;
            g_SfxScriptUnk6[3] = 0;
        }
    }
}

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

INCLUDE_ASM("dra_psp/psp/dra_psp/67558", func_psp_09144C80);
