#include "dra.h"
#include "dra_bss.h"
#include "objects.h"
#include "sfx.h"

void CdSoundCommand14(void) {
    s32 i;

    switch (g_CdSoundCommandStep & 0xFF) {
    case 0:
        if (g_CdSoundCommand16 == 0 || g_CdSoundCommand16 >= 3) {
            D_8013980C = 0;
            AdvanceCdSoundCommandQueue();
            return;
        }
        if (D_8013901C != 0) {
            D_8013980C = 0;
            AdvanceCdSoundCommandQueue();
            return;
        }
        D_801390A0 = 1;

        for (i = 0; i < 8; i++) {
            D_8013B688[i] = D_8013B5F4[g_CdSoundCommand16 - 1].unk0[i];
        }
        D_8013901C = D_8013B5F4[g_CdSoundCommand16 - 1].unkc;
        g_XaMusicVolume = g_XaMusicConfigs[D_8013901C].volume;
        g_CdVolume = 0;
        SetCdVolume(0, 0, 0);
        g_CdMode[0] = 0xC8;
        g_CdSoundCommandStep++;
        break;
    case 1:
        if (DoCdCommand(CdlSetmode, g_CdMode, NULL) == 0) {
            g_CdMode[0] = g_XaMusicConfigs[D_8013901C].filter_file;
            g_CdMode[1] = g_XaMusicConfigs[D_8013901C].filter_channel_id & 0xf;
            g_CdSoundCommandStep++;
        }
        break;
    case 2:
        if (DoCdCommand(CdlSetfilter, g_CdMode, NULL) == 0) {
            g_CdSoundCommandStep++;
        }
        break;
    case 3:
        if (DoCdCommand(CdlSetloc, D_8013B688, NULL) == 0) {
            g_CdSoundCommandStep++;
        }
        break;
    case 4:
        if (DoCdCommand(CdlReadN, NULL, NULL) == 0) {
            g_CdSoundCommandStep++;
        }
        break;
    case 5:
        if (DoCdCommand(CdlNop, NULL, g_CdCommandResult) == 0) {
            if ((*g_CdCommandResult & 0x40) == 0) {
                g_CdSoundCommandStep++;
            }
        }
        break;
    case 6:
        D_8013AEF4 = VSync(-1);
        SsSetSerialAttr(0, 0, 1);
        D_8013AE90 = D_8013B5F4[g_CdSoundCommand16 - 1].unk8;
        D_80139014 = D_8013B5F4[g_CdSoundCommand16 - 1].unke;
        g_CdSoundCommandStep++;
        break;
    case 7:
        if ((g_CdVolume >= g_XaMusicVolume) ||
            (g_CdVolume += 0xC, g_CdVolume >= g_XaMusicVolume)) {
            g_CdVolume = g_XaMusicVolume;
            g_CdSoundCommandStep++;
        }
        SetCdVolume(0, g_CdVolume, g_CdVolume);
        break;
    case 8:
        D_801390A0 = 0;
        D_8013980C = 0;
        g_CdSoundCommandStep = 0;
        g_CdSoundCommand16--;
        AdvanceCdSoundCommandQueue();
        break;
    default:
        g_CdSoundCommandStep = 0;
        D_8013980C = 0;
        D_801390A0 = g_CdSoundCommandStep;
        AdvanceCdSoundCommandQueue();
        break;
    }
}

const u32 padding_CdSoundCommand14 = 0;

void func_80133FCC(void) {
    if (D_8013901C == 0)
        return;

    if (D_801390A0 != 0)
        return;

    D_8013B65C = VSync(-1) - D_8013AEF4;

    if (D_8013AE90 >= D_8013B65C) {
        return;
    }

    switch (D_80139014) {
    case 2:
        AddCdSoundCommand(2);
        break;
    case 1:
        g_CurrentXaSoundId = D_8013901C;
        D_80139014 = g_XaMusicConfigs[g_CurrentXaSoundId + 1].unk230;
        D_8013AEF4 = VSync(-1);
        D_8013AE90 = g_XaMusicConfigs[g_CurrentXaSoundId + 1].unk228;
        break;
    case 0:
        g_CurrentXaSoundId = D_8013901C;
        SetReverbDepth(0x7F);
        AddCdSoundCommand(6);
        break;
    }
}

void SetReleaseRate1(void) {
    D_80138FB4->mask = SPU_VOICE_ADSR_RR;
    D_80138FB4->voice = 0xFFFFFF;
    D_80138FB4->rr = 14;
    SpuSetVoiceAttr(D_80138FB4);
    g_KeyOffChannels = 0xFFFFFF;
    InitSoundVars2();
}

void SetReleaseRate2(void) {
    D_80138FB4->mask = SPU_VOICE_ADSR_RR;
    D_80138FB4->voice = 0xFFFFFF;
    D_80138FB4->rr = 8;
    SpuSetVoiceAttr(D_80138FB4);
    g_KeyOffChannels = 0xFFFFFF;
    InitSoundVars2();
}

void CdSoundCommand10(void) {
    s32 temp;

    switch (g_CdSoundCommandStep) {
    case 0:
        D_801390A0 = 1;
        D_80139A78 = 0;
        g_CdSoundCommandStep++;
        break;

    case 1:
        D_80139A78++;
        if (g_volumeL > 0) {
            temp = g_volumeR * D_80139A6C * D_80139A78;
            if (temp < 0) {
                temp += 0x1FF;
            }
            g_volumeL = g_volumeR - (temp >> 9);
            if (g_volumeL >> 0x10) {
                g_volumeL = 0;
            }
        } else {
            g_volumeL = 0;
        }
        SsSetMVol(g_volumeL, g_volumeL);
        if (g_volumeL == 0) {
            g_CdSoundCommandStep++;
        }
        break;

    case 2:
        SetReverbDepth(0);
        StopSeq();
        AddCdSoundCommand(3);
        D_800BD1C4 = 3;
        g_CdSoundCommandStep++;
        break;

    case 3:
        D_800BD1C4--;
        if (D_800BD1C4 == 0) {
            SetReleaseRate2();
        default:
            g_CdSoundCommandStep = 0;
            D_801390A0 = g_CdSoundCommandStep;
            D_8013B61C = 0;
            AdvanceCdSoundCommandQueue();
        }
        break;
    }
}

void CdSoundCommand8(void) {
    s32 temp;

    switch (g_CdSoundCommandStep) {
    case 0:
        g_CdSoundCommandStep++;
        D_801390A0 = 1;
        D_80139A78 = 0;
        break;

    case 1:
        D_80139A78++;
        if (g_CdVolume > 0) {
            temp = g_XaMusicVolume * D_80139A6C * D_80139A78;
            if (temp < 0) {
                temp += 0x1FF;
            }
            g_CdVolume = g_XaMusicVolume - (temp >> 9);
            if (g_CdVolume >> 0x10) {
                g_CdVolume = 0;
            }
        } else {
            g_CdVolume = 0;
        }
        SetCdVolume(0, g_CdVolume, g_CdVolume);
        if (g_CdVolume == 0) {
            g_CdSoundCommandStep++;
        }
        break;

    case 2:
        AddCdSoundCommand(2);

    default:
        g_CdSoundCommandStep = 0;
        D_801390A0 = g_CdSoundCommandStep;
        D_8013B61C = 0;
        AdvanceCdSoundCommandQueue();
        break;
    }
}

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

s32 func_80134678(s16 arg0, u16 arg1) {
    s32 ret = -2;
    u16 temp;

    if (g_CurSfxId != 0) {
        ret = 0;
        temp = arg1 + 8;

        if (temp >= 0x11) {
            arg1 = 0;
            ret = -1;
        }

        g_CurSfxDistance = arg1;
        g_CurSfxVol = arg0;
        g_SoundCommandRingBuffer[g_SoundCommandRingBufferWritePos] = 1;
        g_SoundCommandRingBufferWritePos++;

        if (g_SoundCommandRingBufferWritePos == 0x100) {
            g_SoundCommandRingBufferWritePos = 0;
        }
    }
    return ret;
}

// alternate to PlaySfx with extra params
u32 PlaySfxVolPan(s16 sfxId, s32 sfxVol, u16 sfxPan) {
    u32 ret;
    u32 var_v0;
    s16 temp_v0;
    s32 temp_a0;
    u16 var;

    ret = 0;
    if (g_SoundInitialized == 0) {
        return -2;
    }
    if (sfxId > SFX_START && sfxId <= SFX_LAST) {
        g_SfxRingBuffer[g_sfxRingBufferWritePos].sndId = sfxId - SFX_START;
        g_SfxRingBuffer[g_sfxRingBufferWritePos].sndVol = sfxVol & 0x7F;
        var = (sfxPan + 8); // Left panning uses signed values, zero is center
        if (var > 16) {
            g_SfxRingBuffer[g_sfxRingBufferWritePos].sndPan = 0;
            ret = -1;
        } else {
            g_SfxRingBuffer[g_sfxRingBufferWritePos].sndPan = sfxPan;
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
    if (g_SoundInitialized != 0) {
        if (sfxId > SFX_START && sfxId <= SFX_LAST) {
            g_SfxRingBuffer[g_sfxRingBufferWritePos].sndId = sfxId - SFX_START;
            g_SfxRingBuffer[g_sfxRingBufferWritePos].sndVol = 0xFFFF;
            g_SfxRingBuffer[g_sfxRingBufferWritePos].sndPan = 0;

            g_sfxRingBufferWritePos++;
            if (g_sfxRingBufferWritePos == LEN(g_SfxRingBuffer)) {
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

            default:
                break;
            }

            g_SoundCommandRingBuffer[g_SoundCommandRingBufferWritePos] = sfxId;
            g_SoundCommandRingBufferWritePos++;
            if (g_SoundCommandRingBufferWritePos == 0x100) {
                g_SoundCommandRingBufferWritePos = 0;
            }
        }
    }
}

void RestoreSfxScriptData(s16 arg0, s16 arg1) {
    g_CurrentSfxScriptSfxId[arg1] = g_CurrentSfxScriptSfxIdCopy[arg0];
    g_SfxScriptVolume[arg1] = g_SfxScriptVolumeCopy[arg0];
    g_SfxScriptDistance[arg1] = g_SfxScriptDistanceCopy[arg0];
    g_SfxScriptTimer[arg1] = g_SfxScriptTimerCopy[arg0];
    g_SfxScriptUnk4[arg1] = D_80139018[arg0];
    g_CurrentSfxScript[arg1] = D_801390B4[arg0];
}

void PauseSfxScripts(void) {
    s16 i;

    for (i = 0; i < NUM_CH; i++) {
        if (g_CurrentSfxScriptSfxId[i] == 0) {
            continue;
        }
        if (g_SfxScriptUnk4[i] == 5) {
            continue;
        }
        g_CurrentSfxScriptSfxIdCopy[i] = g_CurrentSfxScriptSfxId[i];
        g_SfxScriptVolumeCopy[i] = g_SfxScriptVolume[i];
        g_SfxScriptDistanceCopy[i] = g_SfxScriptDistance[i];
        g_SfxScriptTimerCopy[i] = g_SfxScriptTimer[i];
        D_80139018[i] = g_SfxScriptUnk4[i];
        D_801390B4[i] = g_CurrentSfxScript[i];
        g_CurrentSfxScriptSfxId[i] = 0;
        g_SfxScriptVolume[i] = 0;
        g_SfxScriptDistance[i] = 0;
        g_SfxScriptTimer[i] = 0;
        g_SfxScriptUnk4[i] = 0;
        g_CurrentSfxScript[i] = 0;
        g_CurrentSfxScriptSfxId2[i] = 0;
        g_SfxScriptUnk6[i] = 0;
    }
    D_8013B690 = 1;
}

void UnpauseSfxScripts(void) {
    s16 i;
    s16 j;

    for (i = 0; i < 3; i++) {
        if (g_CurrentSfxScriptSfxIdCopy[i]) {
            for (j = 0; j < 3; j++) {
                if (g_CurrentSfxScriptSfxId2[j] == 0) {
                    RestoreSfxScriptData(i, j);
                    break;
                }
            }
            g_CurrentSfxScriptSfxIdCopy[i] = 0;
        }
    }

    if (g_CurrentSfxScriptSfxIdCopy[3] != 0 &&
        g_CurrentSfxScriptSfxId2[3] == 0) {
        RestoreSfxScriptData(3, 3);
        g_CurrentSfxScriptSfxIdCopy[3] = 0;
    }
    D_8013B690 = 0;
}

void KeyOnChannels20_21(void) {
    u16 temp = (g_SfxVolumeMultiplier * g_SfxData[g_CurSfxId2].volume) >> 7;
    func_80132A04(20, g_SfxData[g_CurSfxId2].vabid, g_SfxData[g_CurSfxId2].prog,
                  g_SfxData[g_CurSfxId2].tone, g_SfxData[g_CurSfxId2].note,
                  (temp * (u16)g_CurSfxVol2) >> 7, g_CurSfxDistance2);
}

void KeyOnChannels22_23(void) {
    u16 volume;

    volume = g_SfxVolumeMultiplier * g_SfxData[g_CurSfxId].volume >> 7;
    volume = volume * g_CurSfxVol >> 7;
    func_80132A04(22, g_SfxData[g_CurSfxId].vabid, g_SfxData[g_CurSfxId].prog,
                  g_SfxData[g_CurSfxId].tone, g_SfxData[g_CurSfxId].note,
                  volume, g_CurSfxDistance);
    g_VolR = (volume * g_CdVolumeTable[g_CurSfxDistance * 2 + 144]) >> 8;
    g_VolL = (volume * g_CdVolumeTable[g_CurSfxDistance * 2 + 145]) >> 8;
    SsUtSetVVol(22, g_VolL, g_VolR);
    SsUtSetVVol(23, g_VolL, g_VolR);
}

void SetVolume22_23(void) {
    u16 volume;

    volume = g_SfxVolumeMultiplier * g_SfxData[g_CurSfxId].volume >> 7;
    volume = volume * g_CurSfxVol >> 7;
    g_VolR = (volume * g_CdVolumeTable[g_CurSfxDistance * 2 + 144]) >> 8;
    g_VolL = (volume * g_CdVolumeTable[g_CurSfxDistance * 2 + 145]) >> 8;
    SsUtSetVVol(22, g_VolL, g_VolR);
    SsUtSetVVol(23, g_VolL, g_VolR);
}
