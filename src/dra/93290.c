// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"
#include "dra_bss.h"
#include "objects.h"
#include "sfx.h"

#define CD_PREGAP_BLOCKS 150

void CdSoundCommand6(void) {
    u32 cd_pos;

    switch (g_CdSoundCommandStep & 0xFF) {
    case 0:
        D_801390A0 = 1;
        D_8013845C = g_CurrentXaSoundId;
        cd_pos = g_XaMusicConfigs[g_CurrentXaSoundId + 1].filter_channel_id +
                 g_XaMusicConfigs[g_CurrentXaSoundId + 1].cd_addr;
        cd_pos += CD_PREGAP_BLOCKS + g_CurCdPos;
        MakeCdLoc(cd_pos, &D_8013B640);
        g_CdSoundCommandStep++;
        /* fallthrough */
    case 1:
        if (!DoCdCommand(CdlSetloc, &D_8013B640, NULL)) {
            g_CdSoundCommandStep++;
        }
        break;

    case 2:
        if (!DoCdCommand(CdlReadN, NULL, NULL)) {
            g_CdSoundCommandStep++;
        }
        break;

    case 3:
        if (!DoCdCommand(CdlNop, NULL, g_CdCommandResult)) {
            if ((*g_CdCommandResult & CdlStatSeek) == 0) {
                g_CdSoundCommandStep++;
            }
        }
        break;

    case 4:
        D_8013AEF4 = VSync(-1);
        D_8013AE90 = g_XaMusicConfigs[D_8013845C + 1].unk228;
        SetReverbDepth(g_ReverbDepth);
        g_CdSoundCommandStep = 0;
        D_8013901C = (s16)D_8013845C;
        D_801390A0 = g_CdSoundCommandStep;
        AdvanceCdSoundCommandQueue();
        break;

    default:
        g_CdSoundCommandStep = 0;
        D_801390A0 = g_CdSoundCommandStep;
        AdvanceCdSoundCommandQueue();
        break;
    }
}

// func_80133488
void CdFadeOut1(void) {
    switch (g_CdSoundCommandStep & 0xFF) {
    case 0:
        if (D_8013901C == 0) {
            SetMaxVolume();
            AdvanceCdSoundCommandQueue();
            break;
        }
        D_801390A0 = 1;
        g_CdVolume -= 0x20;
        if (g_CdVolume < 0) {
            g_CdVolume = 0;
        }
        SetCdVolume(0, g_CdVolume, g_CdVolume);
        if (g_CdVolume == 0) {
            g_CdSoundCommandStep++;
        }
        break;

    case 1:
        SsSetSerialAttr(SS_SERIAL_A, SS_MIX, SS_SOFF);
        g_CdSoundCommandStep++;
        /* fallthrough */
    case 2:
        if (!DoCdCommand(CdlPause, 0, 0)) {
            g_CdSoundCommandStep++;
        }
        break;

    case 3:
        D_8013901C = 0;
        SetMaxVolume();
        /* fallthrough */
    default:
        g_CdSoundCommandStep = 0;
        D_801390A0 = g_CdSoundCommandStep;
        AdvanceCdSoundCommandQueue();
        break;
    }
}

void CdFadeOut2(void) {
    switch (g_CdSoundCommandStep & 0xFF) {
    case 0:
        if (D_8013901C == 0) {
            AdvanceCdSoundCommandQueue();
            break;
        }
        D_801390A0 = 1;
        g_CdVolume -= 0x20;
        if (g_CdVolume < 0) {
            g_CdVolume = 0;
        }
        SetCdVolume(0, g_CdVolume, g_CdVolume);
        if (g_CdVolume == 0) {
            g_CdSoundCommandStep++;
        }
        break;

    case 1:
        SsSetSerialAttr(SS_SERIAL_A, SS_MIX, SS_SOFF);
        g_CdSoundCommandStep++;
        /* fallthrough */
    case 2:
        if (!DoCdCommand(CdlPause, 0, 0)) {
            g_CdSoundCommandStep++;
        }
        break;

    case 3:
        g_CdSoundCommandStep = 0;
        D_8013901C = 0;
        D_801390A0 = g_CdSoundCommandStep;
        AdvanceCdSoundCommandQueue();
        break;

    default:
        g_CdSoundCommandStep = 0;
        D_801390A0 = g_CdSoundCommandStep;
        AdvanceCdSoundCommandQueue();
        break;
    }
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
        g_SeqIsPlaying = 0;
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
    g_SeqIsPlaying = 0xE;
}

bool CdSoundCommandQueueEmpty(void) { return g_CdSoundCommandQueuePos == 0; }

bool func_80133950(void) { return D_8013980C == 0; }

void CdSoundCommand12(void) {
    s32 temp_a2;
    s32 i;
    s32 var_t0;

    switch (g_CdSoundCommandStep) {
    case 0:
        if (g_CdSoundCommand16 >= 2) {
            g_CdSoundCommand16 = 0;
        }
        if (D_8013901C == 0) {
            D_8013980C = 0;
            AdvanceCdSoundCommandQueue();
            return;
        }
        D_801390A0 = 1;
        g_CdSoundCommandStep++;
        break;
    case 1:
        if (g_CdVolume <= 0 || (g_CdVolume -= 0xC, g_CdVolume <= 0)) {
            g_CdVolume = 0;
        }
        SetCdVolume(0, g_CdVolume, g_CdVolume);
        if (g_CdVolume == 0) {
            g_CdSoundCommandStep++;
        }
        break;
    case 2:
        if (DoCdCommand(CdlGetlocL, NULL, D_8013B688) == 0) {
            g_CdSoundCommandStep++;
        }
        break;
    case 3:
        temp_a2 = VSync(-1);
        for (i = 0; i < 8; i++) {
            D_8013B5F4[g_CdSoundCommand16].unk0[i] = D_8013B688[i];
        }
        var_t0 = D_8013AE90 - (temp_a2 - D_8013AEF4);
        if (var_t0 <= 0) {
            var_t0 = 1;
        }

        D_8013B5F4[g_CdSoundCommand16].unk8 = var_t0;
        D_8013B5F4[g_CdSoundCommand16].unkc = D_8013901C;
        D_8013B5F4[g_CdSoundCommand16].unke = D_80139014;
        SsSetSerialAttr(0, 0, 0);
        if (DoCdCommand(CdlPause, NULL, NULL) == 0) {
            g_CdSoundCommandStep++;
        }
        break;
    case 4:
        D_8013901C = 0;
        D_801390A0 = 0;
        D_8013980C = 0;
        g_CdSoundCommandStep = 0;
        g_CdSoundCommand16 += 1;
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

const u32 padding_CdSoundCommand12 = 0;
