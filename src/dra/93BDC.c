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

void SetReleaseRate3(void) {
    D_801390C8->voice = 0x300000;
    D_801390C8->mask = SPU_VOICE_ADSR_RR;
    D_801390C8->rr = 14;
    SpuSetVoiceAttr(D_801390C8);
    g_KeyOffChannels |= 0x300000;
}

void SetReleaseRate4(void) {
    D_801390CC->voice = 0xC00000;
    D_801390CC->mask = SPU_VOICE_ADSR_RR;
    D_801390CC->rr = 14;
    SpuSetVoiceAttr(D_801390CC);
    g_KeyOffChannels |= 0xC00000;
}

void SetReleaseRate5(void) {
    D_801390C8->voice = 0x300000;
    D_801390C8->mask = SPU_VOICE_ADSR_RR;
    D_801390C8->rr = 8;
    SpuSetVoiceAttr(D_801390C8);
    g_KeyOffChannels |= 0x300000;
}

void SetReleaseRate6(void) {
    D_801390CC->voice = 0xC00000;
    D_801390CC->mask = SPU_VOICE_ADSR_RR;
    D_801390CC->rr = 8;
    SpuSetVoiceAttr(D_801390CC);
    g_KeyOffChannels |= 0xC00000;
}

s32 func_80134678(s16 arg0, u16 arg1) {
    s32 ret = -2;
    u16 temp;

    if (D_80139804 != 0) {
        ret = 0;
        temp = arg1 + 8;

        if (temp >= 0x11) {
            arg1 = 0;
            ret = -1;
        }

        D_8013AE94 = arg1;
        D_8013AEE0 = arg0;
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

void func_8013493C(s16 arg0, s16 arg1) {
    g_CurrentSfxScriptSfxId[arg1] = D_8013B678[arg0];
    g_SfxScriptVolume[arg1] = D_801390AC[arg0];
    g_UnkChannelSetting1[arg1] = D_80139058[arg0];
    g_SfxScriptTimer[arg1] = D_80139814[arg0];
    D_8013B5EC[arg1] = D_80139018[arg0];
    g_CurrentSfxScript[arg1] = D_801390B4[arg0];
}

void func_801349F4(void) {
    s16 i;

    for (i = 0; i < NUM_CH; i++) {
        if (g_CurrentSfxScriptSfxId[i] == 0) {
            continue;
        }
        if (D_8013B5EC[i] == 5) {
            continue;
        }
        D_8013B678[i] = g_CurrentSfxScriptSfxId[i];
        D_801390AC[i] = g_SfxScriptVolume[i];
        D_80139058[i] = g_UnkChannelSetting1[i];
        D_80139814[i] = g_SfxScriptTimer[i];
        D_80139018[i] = D_8013B5EC[i];
        D_801390B4[i] = g_CurrentSfxScript[i];
        g_CurrentSfxScriptSfxId[i] = 0;
        g_SfxScriptVolume[i] = 0;
        g_UnkChannelSetting1[i] = 0;
        g_SfxScriptTimer[i] = 0;
        D_8013B5EC[i] = 0;
        g_CurrentSfxScript[i] = 0;
        D_8013B648[i] = 0;
        D_8013AEA0[i] = 0;
    }
    D_8013B690 = 1;
}

void func_80134B48(void) {
    s16 i;
    s16 j;

    for (i = 0; i < 3; i++) {
        if (D_8013B678[i]) {
            for (j = 0; j < 3; j++) {
                if (D_8013B648[j] == 0) {
                    func_8013493C(i, j);
                    break;
                }
            }
            D_8013B678[i] = 0;
        }
    }

    if (D_8013B678[3] != 0 && D_8013B648[3] == 0) {
        func_8013493C(3, 3);
        D_8013B678[3] = 0;
    }
    D_8013B690 = 0;
}

void func_80134C60(void) {
    u16 temp = (D_8013AE7C * g_SfxData[D_8013B664].volume) >> 7;
    func_80132A04(0x14, g_SfxData[D_8013B664].vabid, g_SfxData[D_8013B664].prog,
                  g_SfxData[D_8013B664].tone, g_SfxData[D_8013B664].note,
                  (temp * (u16)D_801390A4) >> 7, D_80139010);
}

void func_80134D14(void) {
    u16 volume;

    volume = D_8013AE7C * g_SfxData[D_80139804].volume >> 7;
    volume = volume * D_8013AEE0 >> 7;
    func_80132A04(0x16, g_SfxData[D_80139804].vabid, g_SfxData[D_80139804].prog,
                  g_SfxData[D_80139804].tone, g_SfxData[D_80139804].note,
                  volume, D_8013AE94);
    g_VolR = (volume * g_CdVolumeTable[D_8013AE94 * 2 + 144]) >> 8;
    g_VolL = (volume * g_CdVolumeTable[D_8013AE94 * 2 + 145]) >> 8;
    SsUtSetVVol(0x16, g_VolL, g_VolR);
    SsUtSetVVol(0x17, g_VolL, g_VolR);
}

void func_80134E64(void) {
    u16 volume;

    volume = D_8013AE7C * g_SfxData[D_80139804].volume >> 7;
    volume = volume * D_8013AEE0 >> 7;
    g_VolR = (volume * g_CdVolumeTable[D_8013AE94 * 2 + 144]) >> 8;
    g_VolL = (volume * g_CdVolumeTable[D_8013AE94 * 2 + 145]) >> 8;
    SsUtSetVVol(0x16, g_VolL, g_VolR);
    SsUtSetVVol(0x17, g_VolL, g_VolR);
}
