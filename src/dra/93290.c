#include "dra.h"
#include "objects.h"
#include "sfx.h"

// incorrect function prototype seems to be required
s32 AdvanceCdSoundCommandQueue(void);

#define CD_PREGAP_BLOCKS 150

extern s16 D_8013845C;
extern s16 g_CurrentXaSoundId;
extern s32 D_8013AE90;
extern s32 D_8013AEF4;
extern CdlLOC D_8013B640;

s32 CdSoundCommand6(void) {
    u8 var_v0;
    s32 temp;
    u32 cd_pos;

    switch (g_CdSoundCommandStep & 0xFF) {
    case 0:
        D_801390A0 = 1;
        D_8013845C = g_CurrentXaSoundId;
        cd_pos = g_XaMusicConfigs[g_CurrentXaSoundId + 1].filter_channel_id +
                 g_XaMusicConfigs[g_CurrentXaSoundId + 1].cd_addr;
        cd_pos += CD_PREGAP_BLOCKS + g_CurCdPos;
        MakeCdLoc(cd_pos, &D_8013B640);
        g_CdSoundCommandStep += 1;
        var_v0 = g_CdSoundCommandStep;
        /* fallthrough */
    case 1:
        var_v0 = DoCdCommand(CdlSetloc, &D_8013B640, NULL);
        if (var_v0 == 0) {
            g_CdSoundCommandStep += 1;
            return g_CdSoundCommandStep;
        }
        return var_v0;
    case 2:
        var_v0 = DoCdCommand(CdlReadN, NULL, NULL);
        if (var_v0 == 0) {
            g_CdSoundCommandStep += 1;
            return g_CdSoundCommandStep;
        }
        return var_v0;
    case 3:
        var_v0 = DoCdCommand(CdlNop, NULL, g_CdCommandResult);
        if (var_v0 == 0) {
            var_v0 = *g_CdCommandResult & CdlStatSeek;
            if (var_v0 == 0) {
                g_CdSoundCommandStep += 1;
                return g_CdSoundCommandStep;
            }
            return var_v0;
        }
        return var_v0;
    case 4:
        D_8013AEF4 = VSync(-1);
        D_8013AE90 = g_XaMusicConfigs[D_8013845C + 1].unk228;
        SetReverbDepth(g_ReverbDepth);
        g_CdSoundCommandStep = 0;
        D_8013901C = (s16)D_8013845C;
        D_801390A0 = g_CdSoundCommandStep;
        return AdvanceCdSoundCommandQueue();
    default:
        g_CdSoundCommandStep = 0;
        D_801390A0 = g_CdSoundCommandStep;
        return AdvanceCdSoundCommandQueue();
    }
}

const u32 rodata_padding_80133290 = 0;
// func_80133488
s32 CdFadeOut1(void) {
    s32 var_v0;

    switch (g_CdSoundCommandStep & 0xFF) {
    case 0:
        if (D_8013901C == 0) {
            SetMaxVolume();
            break;
        }
        D_801390A0 = 1;
        g_CdVolume -= 0x20;
        if (g_CdVolume < 0) {
            g_CdVolume = 0;
        }
        SetCdVolume(0, g_CdVolume, g_CdVolume);
        if (g_CdVolume == 0) {
            g_CdSoundCommandStep += 1;
            return g_CdSoundCommandStep;
        }
        return g_CdVolume;
    case 1:
        SsSetSerialAttr(SS_SERIAL_A, SS_MIX, SS_SOFF);
        g_CdSoundCommandStep += 1;
        var_v0 = g_CdSoundCommandStep;
        /* fallthrough */
    case 2:
        var_v0 = DoCdCommand(CdlPause, 0, 0);
        if (var_v0 == 0) {
            g_CdSoundCommandStep += 1;
            return g_CdSoundCommandStep;
        }
        return var_v0;
    case 3:
        D_8013901C = 0;
        SetMaxVolume();
        /* fallthrough */
    default:
        g_CdSoundCommandStep = 0;
        D_801390A0 = g_CdSoundCommandStep;
    }
    return AdvanceCdSoundCommandQueue();
}

s32 CdFadeOut2(void) {
    s16 var_v0;

    switch (g_CdSoundCommandStep & 0xFF) {
    case 0:
        if (D_8013901C != 0) {
            D_801390A0 = 1;
            g_CdVolume -= 0x20;
            if (g_CdVolume < 0) {
                g_CdVolume = 0;
            }
            SetCdVolume(0, g_CdVolume, g_CdVolume);
            if (g_CdVolume == 0) {
                g_CdSoundCommandStep += 1;
                return g_CdSoundCommandStep;
            }
            return g_CdVolume;
        }
        break;
    case 1:
        SsSetSerialAttr(SS_SERIAL_A, SS_MIX, SS_SOFF);
        g_CdSoundCommandStep += 1;
        var_v0 = g_CdSoundCommandStep;
        /* fallthrough */
    case 2:
        var_v0 = DoCdCommand(CdlPause, 0, 0);
        if (var_v0 == 0) {
            g_CdSoundCommandStep += 1;
            return g_CdSoundCommandStep;
        }
        return var_v0;
    case 3:
        g_CdSoundCommandStep = 0;
        D_8013901C = 0;
        D_801390A0 = g_CdSoundCommandStep;
        break;
    default:
        g_CdSoundCommandStep = 0;
        D_801390A0 = g_CdSoundCommandStep;
    }
    return AdvanceCdSoundCommandQueue();
}

void EnableCdReverb(s8 arg0) {
    SsSetSerialAttr(SS_SERIAL_A, SS_REV, arg0 == SS_SON);
}

void StopSeq(void) {
    if (g_SeqPlayingId != 0) {
        SsSeqStop(g_SeqAccessNum);
        SsSeqClose(g_SeqAccessNum);
        SetReleaseRate2();
        g_SeqPlayingId = 0;
        D_801390C4 = 0;
    }
}

void PlaySeq(u8 arg0) {
    s16 index;

    if (g_SeqPlayingId != 0) {
        StopSeq();
    }
    index = arg0;
    g_SeqAccessNum =
        SsSeqOpen(g_SeqPointers[index], g_SeqInfo[index].unk2.info.vab_id);
    g_ReverbDepth = g_SeqInfo[index].reverb_depth;
    SetReverbDepth(g_ReverbDepth);
    g_SeqVolume1 = g_SeqInfo[index].volume;
    g_SeqVolume2 = g_SeqInfo[index].volume;
    SsSeqSetVol(g_SeqAccessNum, g_SeqVolume1, g_SeqVolume1);
    if (!g_SeqInfo[index].unk2.info.one_shot) {
        SsSeqPlay(g_SeqAccessNum, 1, 1);
    } else {
        SsSeqPlay(g_SeqAccessNum, 1, 0);
    }
    g_SeqPlayingId = index;
    D_801390C4 = 0xE;
}

bool CdSoundCommandQueueEmpty(void) { return g_CdSoundCommandQueuePos == 0; }

bool func_80133950(void) { return D_8013980C == 0; }

INCLUDE_ASM("dra/nonmatchings/93290", CdSoundCommand12);
void CdSoundCommand12();

INCLUDE_ASM("dra/nonmatchings/93290", CdSoundCommand14);
void CdSoundCommand14();

INCLUDE_ASM("dra/nonmatchings/93290", func_80133FCC);

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

u32 func_80134714(s16 sfxId, s32 arg1, u16 arg2) {
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
        g_SfxRingBuffer[g_sfxRingBufferWritePos].unk02 = arg1 & 0x7F;
        var = (arg2 + 8);
        if (var > 16) {
            g_SfxRingBuffer[g_sfxRingBufferWritePos].unk04 = 0;
            ret = -1;
        } else {
            g_SfxRingBuffer[g_sfxRingBufferWritePos].unk04 = arg2;
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
            g_SfxRingBuffer[g_sfxRingBufferWritePos].unk02 = 0xFFFF;
            g_SfxRingBuffer[g_sfxRingBufferWritePos].unk04 = 0;

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
    g_UnkChannelSetting2[arg1] = D_8013B678[arg0];
    g_ChannelGroupVolume[arg1] = D_801390AC[arg0];
    g_UnkChannelSetting1[arg1] = D_80139058[arg0];
    D_8013B66C[arg1] = D_80139814[arg0];
    D_8013B5EC[arg1] = D_80139018[arg0];
    D_8013B628[arg1] = D_801390B4[arg0];
}

void func_801349F4(void) {
    s16 i;

    for (i = 0; i < 4; i++) {
        if (g_UnkChannelSetting2[i] == 0) {
            continue;
        }
        if (D_8013B5EC[i] == 5) {
            continue;
        }
        D_8013B678[i] = g_UnkChannelSetting2[i];
        D_801390AC[i] = g_ChannelGroupVolume[i];
        D_80139058[i] = g_UnkChannelSetting1[i];
        D_80139814[i] = D_8013B66C[i];
        D_80139018[i] = D_8013B5EC[i];
        D_801390B4[i] = D_8013B628[i];
        g_UnkChannelSetting2[i] = 0;
        g_ChannelGroupVolume[i] = 0;
        g_UnkChannelSetting1[i] = 0;
        D_8013B66C[i] = 0;
        D_8013B5EC[i] = 0;
        D_8013B628[i] = 0;
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
    u16 temp = (D_8013AE7C * D_800BF554[D_8013B664].volume) >> 7;
    func_80132A04(
        0x14, D_800BF554[D_8013B664].vabid, D_800BF554[D_8013B664].prog,
        D_800BF554[D_8013B664].tone, D_800BF554[D_8013B664].note,
        (temp * (u16)D_801390A4) >> 7, D_80139010);
}

void func_80134D14(void) {
    u16 volume;

    volume = D_8013AE7C * D_800BF554[D_80139804].volume >> 7;
    volume = volume * D_8013AEE0 >> 7;
    func_80132A04(0x16, D_800BF554[D_80139804].vabid,
                  D_800BF554[D_80139804].prog, D_800BF554[D_80139804].tone,
                  D_800BF554[D_80139804].note, volume, D_8013AE94);
    g_VolR = (volume * g_VolumeTable[D_8013AE94 * 2 + 0]) >> 8;
    g_VolL = (volume * g_VolumeTable[D_8013AE94 * 2 + 1]) >> 8;
    SsUtSetVVol(0x16, g_VolL, g_VolR);
    SsUtSetVVol(0x17, g_VolL, g_VolR);
}

void func_80134E64(void) {
    u16 volume;

    volume = D_8013AE7C * D_800BF554[D_80139804].volume >> 7;
    volume = volume * D_8013AEE0 >> 7;
    g_VolR = (volume * g_VolumeTable[D_8013AE94 * 2 + 0]) >> 8;
    g_VolL = (volume * g_VolumeTable[D_8013AE94 * 2 + 1]) >> 8;
    SsUtSetVVol(0x16, g_VolL, g_VolR);
    SsUtSetVVol(0x17, g_VolL, g_VolR);
}
