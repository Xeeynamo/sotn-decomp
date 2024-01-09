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
    s16 arg0, s32 channel_group, bool do_key_off, u16 volume, s16 distance) {
    u16 volumeMod;
    u16 calcVolume;
    s32 progId;

    if (do_key_off) {
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
        g_UnkChannelSetting1[channel_group] = distance;
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
    s16 arg0, s32 channel_group, bool do_key_off, u16 volume, s16 distance) {
    if (do_key_off) {
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

void func_8013572C(s16 arg0, u16 volume, s16 distance) {
    s32 i;

    if (arg0 == 0) {
        return;
    }
    if (g_SfxData[arg0].vabid == 9) {
        if (D_801390C4 == 0) {
            for (i = 0; i < 3; i++) {
                if (arg0 == D_8013B648[i]) {
                    ApplyQuadChannelSetting(arg0, i, true, volume, distance);
                    return;
                }
            }
            for (i = 0; i < 3; i++) {
                if (D_8013B648[i] == 0) {
                    ApplyQuadChannelSetting(arg0, i, false, volume, distance);
                    return;
                }
            }
            for (i = 0; i < 3; i++) {
                if (D_8013AEA0[i] < g_SfxData[arg0].unk6) {
                    ApplyQuadChannelSetting(arg0, i, true, volume, distance);
                    return;
                }
            }
            for (i = 0; i < 3; i++) {
                if (g_SfxData[arg0].unk6 == D_8013AEA0[i]) {
                    ApplyQuadChannelSetting(arg0, i, true, volume, distance);
                    return;
                }
            }
            return;
        }
        if (g_SfxData[arg0].unk6 >= D_8013AEA6) {
            ApplyQuadChannelSetting(arg0, 3, true, volume, distance);
        }
    } else {
        switch (g_SfxData[arg0].unk4) {
        case 1:
            D_80139804 = arg0;
            if (volume == 0xFFFF) {
                D_8013AEE0 = 0x7F;
            } else {
                D_8013AEE0 = volume;
            }
            D_8013AE94 = distance;
            func_80134D14();
            return;
        case 3:
            D_8013B664 = arg0;
            if (volume == 0xFFFF) {
                D_801390A4 = 0x7F;
            } else {
                D_801390A4 = volume;
            }
            D_80139010 = distance;
            func_80134C60();
            return;
        case 2:
            SetReleaseRate6();
            D_80139804 = 0;
            return;
        case 0:
            D_801397F8 = (D_8013AE7C * g_SfxData[arg0].volume) >> 7;
            if (volume == 0xFFFF) {
                D_801396DC = 0;
            } else {
                D_801396DC = distance;
                D_801397F8 = (D_801397F8 * volume) >> 7;
            }
            if (D_801390C4 == 0) {
                for (i = 0; i < 4; i++) {
                    if (arg0 == D_8013B650[i]) {
                        func_80135624(arg0, i, true, D_801397F8, D_801396DC);
                        return;
                    }
                }
                for (i = 0; i < 4; i++) {
                    if (D_8013B650[i] == 0) {
                        func_80135624(arg0, i, false, D_801397F8, D_801396DC);
                        return;
                    }
                }
                for (i = 0; i < 4; i++) {
                    if (D_8013AED4[i] < g_SfxData[arg0].unk6) {
                        func_80135624(arg0, i, true, D_801397F8, D_801396DC);
                        return;
                    }
                }
                for (i = 0; i < 3; i++) {
                    if (g_SfxData[arg0].unk6 == D_8013AED4[i]) {
                        func_80135624(arg0, i, true, D_801397F8, D_801396DC);
                        return;
                    }
                }
                return;
            }
            if (D_8013B650[3] == 0) {
                func_80135624(arg0, 3, false, D_801397F8, D_801396DC);
                return;
            }
            if (g_SfxData[arg0].unk6 >= D_8013AED4[3]) {
                func_80135624(arg0, 3, true, D_801397F8, D_801396DC);
            }
            break;
        }
    }
}

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

void func_80135D8C(void) {
    s32 i;
    s8* temp_t2;
    s8** temp_t2_2;
    s8* temp_v1;
    s8** temp_t3;
    s8** temp_v1_2;

    s16 vab;
    s16 prog;
    s16 note;
    s16 tone;
    u32 volume;
    s8 distance;
    s8 distance2;

    if (D_801390C4 == 0) {
        for (i = 0; i < 3; i++) {
            if (g_UnkChannelSetting2[i] != 0) {
                if (D_8013B66C[i] == 0) {
                    // FAKE, should just be &D_8013B628[i]
                    temp_v1_2 = &D_8013B628;
                    temp_t3 = i + temp_v1_2;

                    temp_t2 = *temp_t3;
                    *temp_t3 = temp_t2 + 1;
                    vab = temp_t2[0];
                    if (vab == -1) {
                        g_UnkChannelSetting2[i] = 0;
                        continue;
                    }
                    *temp_t3 = temp_t2 + 2;
                    prog = temp_t2[1];
                    *temp_t3 = temp_t2 + 3;
                    note = temp_t2[2];
                    *temp_t3 = temp_t2 + 4;
                    tone = temp_t2[3];
                    *temp_t3 = temp_t2 + 5;
                    volume = g_ChannelGroupVolume[i] * temp_t2[4];
                    *temp_t3 = temp_t2 + 6;
                    D_8013B66C[i] = temp_t2[5];
                    distance = D_8013B5F6[30 + i];
                    func_80132A04(
                        30 + i, vab, prog, tone, note, volume >> 7, distance);
                } else {
                    D_8013B66C[i]--;
                }
            }
        }
    } else if (D_8013AE8A[0] != 0) {
        if (D_8013B672[0] == 0) {
            temp_t2_2 = &D_8013B628[3];
            temp_v1 = *temp_t2_2;
            *temp_t2_2 = temp_v1 + 1;
            vab = temp_v1[0];
            if (vab == -1) {
                D_8013AE8A[0] = 0;
                return;
            }
            *temp_t2_2 = temp_v1 + 2;
            prog = temp_v1[1];
            *temp_t2_2 = temp_v1 + 3;
            note = temp_v1[2];
            *temp_t2_2 = temp_v1 + 4;
            tone = temp_v1[3];
            distance2 = g_UnkChannelSetting1[3];
            *temp_t2_2 = temp_v1 + 5;
            volume = D_8013B626 * temp_v1[4];
            *temp_t2_2 = temp_v1 + 6;
            D_8013B672[0] = temp_v1[5];
            distance = distance2;
            func_80132A04(33, vab, prog, tone, note, volume >> 7, distance);

        } else {
            D_8013B672[0]--;
        }
    }
}

void func_80136010(void) {
    s16* var_t4;
    s32 i;
    s8* var_a0;
    s8* var_a2;

    s8* var_t0;
    s8* var_t1;
    s8* var_t2;
    s8* var_t3;

    s8 sum;
    s8* new_var;
    s16* fakeptr;

    SpuGetAllKeysStatus(&D_80138F64);
    if (D_801390C4 == 0) {
        var_a0 = &D_80138F64[12];
        var_a2 = &D_80138F64[13];
        for (i = 0; i < 4; i++) {
            sum = var_a0[i * 2] + var_a2[i * 2];
            if (sum == 0) {
                D_8013B650[i] = 0;
                D_8013AED4[i] = 0;
            }
        }
    } else if ((s8)(D_80138F64[18] + D_80138F64[19]) == 0) {
        D_8013B650[3] = 0;
        D_8013AED4[3] = 0;
    }
    if (D_801390C4 == 0) {
        var_t4 = D_8013B648;
        new_var = &D_80138F64;
        var_t3 = &D_80138F64[3];
        var_t2 = &D_80138F64[2];
        var_t1 = &D_80138F64[1];
        var_t0 = new_var;

        for (i = 0; i < 3; i++) {
            if (g_UnkChannelSetting2[i] == 0) {
                if ((s8)(*var_t0 + *var_t1 + *var_t2 + *var_t3) == 0) {
                    *var_t4 = 0;
                    fakeptr = D_8013AEA0;
                    D_8013AEA0[i] = 0;
                }
            }
            fakeptr++;
            var_t4 += 1;
            var_t3 += 4;
            var_t2 += 4;
            var_t1 += 4;
            var_t0 += 4;
        }
        return;
    }
    if ((D_8013AE8A[0] == 0) && ((s8)(D_80138F64[14] + D_80138F64[15] +
                                      D_80138F64[16] + D_80138F64[17]) == 0)) {
        D_8013B64E = 0;
        D_8013AEA6 = 0;
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

void nullsub_10(void) {}
