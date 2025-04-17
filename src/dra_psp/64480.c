// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

extern s32 D_psp_091893B8[];
extern s16 D_psp_09187240[][2];
extern s8* D_psp_09190C18[];

INCLUDE_ASM("dra_psp/psp/dra_psp/64480", func_psp_09140E00);

INCLUDE_ASM("dra_psp/psp/dra_psp/64480", func_psp_09140E50);

INCLUDE_ASM("dra_psp/psp/dra_psp/64480", func_80132A04);

INCLUDE_ASM("dra_psp/psp/dra_psp/64480", AddCdSoundCommand);

INCLUDE_ASM("dra_psp/psp/dra_psp/64480", func_psp_09141440);

INCLUDE_ASM("dra_psp/psp/dra_psp/64480", AdvanceCdSoundCommandQueue);

INCLUDE_ASM("dra_psp/psp/dra_psp/64480", func_psp_09141550);

INCLUDE_ASM("dra_psp/psp/dra_psp/64480", func_psp_09141570);

INCLUDE_ASM("dra_psp/psp/dra_psp/64480", func_psp_091415E0);

INCLUDE_ASM("dra_psp/psp/dra_psp/64480", func_psp_09141608);

INCLUDE_ASM("dra_psp/psp/dra_psp/64480", func_psp_09141668);

s32 func_psp_09141860(s32 arg0) { return D_psp_091893B8[arg0]; }

void func_psp_09141878(s32 arg0) {
    func_892A620(0, 0);
    SetCdVolume(0, 0x7F, 0x7F);
    if (arg0 >= 0 && arg0 <= 0x230) {
        func_psp_09141668(arg0);
    }
}

INCLUDE_ASM("dra_psp/psp/dra_psp/64480", CdSoundCommand4);

INCLUDE_ASM("dra_psp/psp/dra_psp/64480", CdSoundCommand6);

INCLUDE_ASM("dra_psp/psp/dra_psp/64480", CdFadeOut1);

INCLUDE_ASM("dra_psp/psp/dra_psp/64480", CdFadeOut2);

INCLUDE_ASM("dra_psp/psp/dra_psp/64480", func_psp_09141E30);

INCLUDE_ASM("dra_psp/psp/dra_psp/64480", EnableCdReverb);

INCLUDE_ASM("dra_psp/psp/dra_psp/64480", StopSeq);

INCLUDE_ASM("dra_psp/psp/dra_psp/64480", PlaySeq);

INCLUDE_ASM("dra_psp/psp/dra_psp/64480", CdSoundCommandQueueEmpty);

INCLUDE_ASM("dra_psp/psp/dra_psp/64480", func_80133950);

INCLUDE_ASM("dra_psp/psp/dra_psp/64480", CdSoundCommand12);

INCLUDE_ASM("dra_psp/psp/dra_psp/64480", CdSoundCommand14);

INCLUDE_ASM("dra_psp/psp/dra_psp/64480", func_80133FCC);

void SetReleaseRate1(void) {
    D_80138FB4->voice = 0;
    D_80138FB4->mask = SPU_VOICE_ADSR_RR;
    D_80138FB4->rr = 14;
    SpuSetVoiceAttr(D_80138FB4);
    g_KeyOffChannels = 0;
    InitSoundVars2();
}

void SetReleaseRate2(void) {
    D_80138FB4->voice = 0;
    D_80138FB4->mask = SPU_VOICE_ADSR_RR;
    D_80138FB4->rr = 8;
    SpuSetVoiceAttr(D_80138FB4);
    g_KeyOffChannels = 0;
    InitSoundVars2();
}

// requires AdvanceCdSoundCommandQueue to be static in the
// same file, https://decomp.me/scratch/t0j7W
INCLUDE_ASM("dra_psp/psp/dra_psp/64480", CdSoundCommand10);

// requires AdvanceCdSoundCommandQueue to be static in the
// same file, https://decomp.me/scratch/hmJYM
INCLUDE_ASM("dra_psp/psp/dra_psp/64480", CdSoundCommand8);

#define MASK_22_23 ((1 << 22) | (1 << 23))
#define MASK_20_21 ((1 << 20) | (1 << 21))

void SetReleaseRateHigh20_21(void) {
    D_801390C8->voice = MASK_20_21;
    D_801390C8->mask = SPU_VOICE_ADSR_RR;
    D_801390C8->rr = 14;
    SpuSetVoiceAttr(D_801390C8);
    g_KeyOffChannels |= MASK_20_21;
}

void SetReleaseRateHigh22_23(void) {
    D_801390CC->voice = MASK_22_23;
    D_801390CC->mask = SPU_VOICE_ADSR_RR;
    D_801390CC->rr = 14;
    SpuSetVoiceAttr(D_801390CC);
    g_KeyOffChannels |= MASK_22_23;
}

void SetReleaseRateLow_20_21(void) {
    D_801390C8->voice = MASK_20_21;
    D_801390C8->mask = SPU_VOICE_ADSR_RR;
    D_801390C8->rr = 8;
    SpuSetVoiceAttr(D_801390C8);
    g_KeyOffChannels |= MASK_20_21;
}

void SetReleaseRateLow_22_23(void) {
    D_801390CC->voice = MASK_22_23;
    D_801390CC->mask = SPU_VOICE_ADSR_RR;
    D_801390CC->rr = 8;
    SpuSetVoiceAttr(D_801390CC);
    g_KeyOffChannels |= MASK_22_23;
}

s32 SetVolumeCommand22_23(s16 vol, s16 distance) {
    s32 ret = -2;
    if (g_CurSfxId22_23) {
        if (distance < -8 || distance > 8) {
            distance = 0;
            ret = -1;
        } else {
            ret = 0;
        }
        g_CurSfxVol22_23 = vol;
        g_CurSfxDistance22_23 = distance;
        g_SoundCommandRingBuffer[g_SoundCommandRingBufferWritePos] =
            SET_VOLUME_22_23;
        g_SoundCommandRingBufferWritePos++;
        if (g_SoundCommandRingBufferWritePos == 0x100) {
            g_SoundCommandRingBufferWritePos = 0;
        }
    }
    return ret;
}

// alternate to PlaySfx with extra params
s32 PlaySfxVolPan(s16 sfxId, u16 sfxVol, s16 sfxPan) {
    s32 ret = 0;

    if (!g_SoundInitialized) {
        return -2;
    }
    if (sfxId > SFX_START && sfxId <= SFX_LAST) {
        g_SfxRingBuffer[g_sfxRingBufferWritePos].sndId = sfxId - SFX_START;
        g_SfxRingBuffer[g_sfxRingBufferWritePos].sndVol = sfxVol & 0x7F;
        if (sfxPan < -8 || sfxPan > 8) {
            g_SfxRingBuffer[g_sfxRingBufferWritePos].sndPan = 0;
            ret = -1;
        } else {
            g_SfxRingBuffer[g_sfxRingBufferWritePos].sndPan = sfxPan;
            ret = 0;
        }
        g_sfxRingBufferWritePos++;
        if (g_sfxRingBufferWritePos == LEN(g_SfxRingBuffer)) {
            g_sfxRingBufferWritePos = 0;
        }
    } else {
        ret = -3;
    }
    return ret;
}

void PlaySfx(s16 sfxId) {
    if (!g_SoundInitialized) {
        return;
    }
    if (sfxId > SFX_START && sfxId <= SFX_LAST) {
        g_SfxRingBuffer[g_sfxRingBufferWritePos].sndId = sfxId - SFX_START;
        g_SfxRingBuffer[g_sfxRingBufferWritePos].sndVol = 0xFFFF;
        g_SfxRingBuffer[g_sfxRingBufferWritePos].sndPan = 0;
        g_sfxRingBufferWritePos++;
        if (g_sfxRingBufferWritePos == 0x100) {
            g_sfxRingBufferWritePos = 0;
        }
    } else {
        switch (sfxId) {
        case 0x10:
        case 0x11:
            D_8013980C = 1;
            break;

        case 0x80:
        case 0x81:
        case 0x82:
        case 0x83:
        case 0x84:
        case 0x90:
        case 0x91:
        case 0x92:
        case 0x93:
        case 0x94:
            D_8013B61C = 1;
            break;
        }
        g_SoundCommandRingBuffer[g_SoundCommandRingBufferWritePos] = sfxId;
        g_SoundCommandRingBufferWritePos++;
        if (g_SoundCommandRingBufferWritePos == 0x100) {
            g_SoundCommandRingBufferWritePos = 0;
        }
    }
}

void RestoreSfxScriptData(s16 arg0, s16 arg1) {
    g_CurrentSfxScriptSfxId[arg1] = g_CurrentSfxScriptSfxIdCopy[arg0];
    g_SfxScriptVolume[arg1] = g_SfxScriptVolumeCopy[arg0];
    g_SfxScriptDistance[arg1] = g_SfxScriptDistanceCopy[arg0];
    g_SfxScriptTimer[arg1] = g_SfxScriptTimerCopy[arg0];
    g_SfxScriptMode[arg1] = g_SfxScriptModeCopy[arg0];
    g_CurrentSfxScript[arg1] = D_801390B4[arg0];
}

void PauseSfxScripts(void) {
    s16 i;

    for (i = 0; i < NUM_CH; i++) {
        if (!g_CurrentSfxScriptSfxId[i]) {
            continue;
        }
        if (g_SfxScriptMode[i] == SFX_MODE_SCRIPT_NO_PAUSE) {
            continue;
        }
        g_CurrentSfxScriptSfxIdCopy[i] = g_CurrentSfxScriptSfxId[i];
        g_SfxScriptVolumeCopy[i] = g_SfxScriptVolume[i];
        g_SfxScriptDistanceCopy[i] = g_SfxScriptDistance[i];
        g_SfxScriptTimerCopy[i] = g_SfxScriptTimer[i];
        g_SfxScriptModeCopy[i] = g_SfxScriptMode[i];
        D_801390B4[i] = g_CurrentSfxScript[i];
        g_CurrentSfxScriptSfxId[i] = 0;
        g_SfxScriptVolume[i] = 0;
        g_SfxScriptDistance[i] = 0;
        g_SfxScriptTimer[i] = 0;
        g_SfxScriptMode[i] = 0;
        g_CurrentSfxScript[i] = 0;
        g_CurrentSfxScriptSfxId2[i] = 0;
        g_SfxScriptUnk6[i] = 0;
    }
    D_8013B690 = 1;
}

void UnpauseSfxScripts(void) {
    s16 i, j;

    for (i = 0; i < 3; i++) {
        if (!g_CurrentSfxScriptSfxIdCopy[i]) {
            continue;
        }
        for (j = 0; j < 3; j++) {
            if (!g_CurrentSfxScriptSfxId2[j]) {
                RestoreSfxScriptData(i, j);
                break;
            }
        }
        g_CurrentSfxScriptSfxIdCopy[i] = 0;
    }
    if (g_CurrentSfxScriptSfxIdCopy[3] && !g_CurrentSfxScriptSfxId2[3]) {
        RestoreSfxScriptData(3, 3);
        g_CurrentSfxScriptSfxIdCopy[3] = 0;
    }
    D_8013B690 = 0;
}

void KeyOnChannels20_21(void) {
    u16 volume;

    volume = (g_SfxVolumeMultiplier * g_SfxData[g_CurSfxId20_21].volume) >> 7;
    volume = (volume * g_CurSfxVol20_21) >> 7;
    func_80132A04(
        20, g_SfxData[g_CurSfxId20_21].vabid, g_SfxData[g_CurSfxId20_21].prog,
        g_SfxData[g_CurSfxId20_21].tone, g_SfxData[g_CurSfxId20_21].note,
        volume, g_CurSfxDistance20_21);
}

void KeyOnChannels22_23(void) {
    u16 volume;

    volume = (g_SfxVolumeMultiplier * g_SfxData[g_CurSfxId22_23].volume) >> 7;
    volume = (volume * g_CurSfxVol22_23) >> 7;
    func_80132A04(
        22, g_SfxData[g_CurSfxId22_23].vabid, g_SfxData[g_CurSfxId22_23].prog,
        g_SfxData[g_CurSfxId22_23].tone, g_SfxData[g_CurSfxId22_23].note,
        volume, g_CurSfxDistance22_23);
    g_VolR = (volume * D_psp_09187240[g_CurSfxDistance22_23][0]) >> 8;
    g_VolL = (volume * D_psp_09187240[g_CurSfxDistance22_23][1]) >> 8;
    SsUtSetVVol(22, g_VolL, g_VolR);
    SsUtSetVVol(23, g_VolL, g_VolR);
}

void SetVolume22_23(void) {
    u16 volume;

    volume = (g_SfxVolumeMultiplier * g_SfxData[g_CurSfxId22_23].volume) >> 7;
    volume = (volume * g_CurSfxVol22_23) >> 7;
    g_VolR = (volume * D_psp_09187240[g_CurSfxDistance22_23][0]) >> 8;
    g_VolL = (volume * D_psp_09187240[g_CurSfxDistance22_23][1]) >> 8;
    SsUtSetVVol(22, g_VolL, g_VolR);
    SsUtSetVVol(23, g_VolL, g_VolR);
}

INCLUDE_ASM("dra_psp/psp/dra_psp/64480", ExecSoundCommands);

// requires AdvanceCdSoundCommandQueue to be static in the
// same file, https://decomp.me/scratch/9rjfX
INCLUDE_ASM("dra_psp/psp/dra_psp/64480", ExecCdSoundCommands);

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

INCLUDE_ASM("dra_psp/psp/dra_psp/64480", func_psp_09144C80);
