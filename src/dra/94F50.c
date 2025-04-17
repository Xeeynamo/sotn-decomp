// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"
#include "dra_bss.h"
#include "objects.h"
#include "sfx.h"

void ExecSoundCommands(void) {
    s16 id;

    while (
        g_SoundCommandRingBufferReadPos != g_SoundCommandRingBufferWritePos) {
        id = g_SoundCommandRingBuffer[g_SoundCommandRingBufferReadPos];
        g_SoundCommandRingBuffer[g_SoundCommandRingBufferReadPos] = 0;
        g_SoundCommandRingBufferReadPos++;
        if (g_SoundCommandRingBufferReadPos == 0x100) {
            g_SoundCommandRingBufferReadPos = 0;
        }
        if (id > 0x200 && id < 0x206) {
            PlaySeq(id);
            continue;
        }

#ifdef VERSION_HD
        if (id > 0x300 && id < 0x531) {
#elif defined(VERSION_PSP)
        if (id > 0x300 && id < 0x532) {
#else
        if (id > 0x300 && id < 0x533) {
#endif
            if (D_8013901C != 0) {
                if (D_8013901C == (id - 0x300)) {
                    return;
                }
                AddCdSoundCommand(CD_SOUND_COMMAND_FADE_OUT_2);
            }
            g_CurrentXaSoundId = id - 0x300;
            AddCdSoundCommand(CD_SOUND_COMMAND_START_XA);
            continue;
        }
        switch (id) {
        case SET_SOUND_WAIT:
            SoundWait();
            break;

        case SET_SOUNDMODE_MONO:
            SetMonoStereo(MONO_SOUND);
            break;

        case SET_SOUNDMODE_STEREO:
            SetMonoStereo(STEREO_SOUND);
            break;

        case SET_STOP_SEQ:
            StopSeq();
            break;

        case 0x8:
            SetReleaseRate2();
            break;

        case SET_STOP_MUSIC:
            AddCdSoundCommand(CD_SOUND_COMMAND_FADE_OUT_2);
            break;

        case SET_PAUSE_SFX_SCRIPTS:
            PauseSfxScripts();
            break;

        case SET_UNPAUSE_SFX_SCRIPTS:
            UnpauseSfxScripts();
            break;

        case 0x80:
            g_XaVolumeMultiplier = 0x20;
            AddCdSoundCommand(CD_SOUND_COMMAND_10);
            break;

        case 0x81:
            g_XaVolumeMultiplier = 8;
            AddCdSoundCommand(CD_SOUND_COMMAND_10);
            break;

        case 0x82:
            g_XaVolumeMultiplier = 4;
            AddCdSoundCommand(CD_SOUND_COMMAND_10);
            break;

        case 0x83:
            g_XaVolumeMultiplier = 2;
            AddCdSoundCommand(CD_SOUND_COMMAND_10);
            break;

        case 0x84:
            g_XaVolumeMultiplier = 1;
            AddCdSoundCommand(CD_SOUND_COMMAND_10);
            break;

        case 0x90:
            g_XaVolumeMultiplier = 0x80;
            AddCdSoundCommand(CD_SOUND_COMMAND_8);
            break;

        case 0x91:
            g_XaVolumeMultiplier = 8;
            AddCdSoundCommand(CD_SOUND_COMMAND_8);
            break;

        case 0x92:
            g_XaVolumeMultiplier = 4;
            AddCdSoundCommand(CD_SOUND_COMMAND_8);
            break;

        case 0x93:
            g_XaVolumeMultiplier = 2;
            AddCdSoundCommand(CD_SOUND_COMMAND_8);
            break;

        case 0x94:
            g_XaVolumeMultiplier = 1;
            AddCdSoundCommand(CD_SOUND_COMMAND_8);
            break;

        case 0xA0:
            SetReleaseRate1();
            break;

        case SET_RELEASE_RATE_HIGH_20_21:
            SetReleaseRateHigh20_21();
            g_CurSfxId20_21 = 0;
            break;

        case 0xA5:
            SetReleaseRateHigh22_23();
            g_CurSfxId22_23 = 0;
            break;

        case 0xA2:
            SetReleaseRateLow_20_21();
            g_CurSfxId20_21 = 0;
            break;

        case SET_RELEASE_RATE_LOW_20_21:
            if (g_CurSfxId20_21 != 0) {
                SetReleaseRateLow_20_21();
            }
            break;

        case SET_KEY_ON_20_21:
            if (g_CurSfxId20_21 != 0) {
                KeyOnChannels20_21();
            }
            break;

        case 0xA6:
            SetReleaseRateLow_22_23();
            g_CurSfxId22_23 = 0;
            break;

        case SET_RELEASE_RATE_LOW_22_23:
            if (g_CurSfxId22_23 != 0) {
                SetReleaseRateLow_22_23();
            }
            break;

        case SET_KEY_ON_22_23:
            if (g_CurSfxId22_23 != 0) {
                KeyOnChannels22_23();
            }
            break;

        case SET_VOLUME_22_23:
            SetVolume22_23();
            break;

        case SET_UNK_10:
            AddCdSoundCommand(CD_SOUND_COMMAND_12);
            break;

        case SET_UNK_11:
            AddCdSoundCommand(CD_SOUND_COMMAND_14);
            break;

        case SET_UNK_12:
            AddCdSoundCommand(CD_SOUND_COMMAND_16);
            break;

        case SET_UNK_0B:
            AddCdSoundCommand(CD_SOUND_COMMAND_FADE_OUT_2);
#ifdef VERSION_PSP
            func_892A620(0, 0);
            func_892A620(1, 0);
#endif
            StopSeq();
            SetReleaseRate2();
            break;

        case SET_UNK_0C:
            AddCdSoundCommand(CD_SOUND_COMMAND_FADE_OUT_2);
#ifdef VERSION_PSP
            func_892A620(0, 0);
            func_892A620(1, 0);
#endif
            StopSeq();
            SoundWait();
            SetReleaseRate2();
            break;

        case 0x5A:
            EnableCdReverb(1);
            break;

        case 0x5B:
            EnableCdReverb(0);
            break;

        case 0x5C:
            SetReverbDepth(8);
            break;

        case 0x5D:
            SetReverbDepth(0x10);
            break;

        case 0x5E:
            SetReverbDepth(0x18);
            break;

        case 0x5F:
            SetReverbDepth(0x20);
            break;

        case 0x60:
            SetReverbDepth(0x28);
            break;

        case 0x61:
            SetReverbDepth(0x30);
            break;

        case 0x62:
            SetReverbDepth(0x38);
            break;

        case 0x63:
            SetReverbDepth(0x40);
            break;

        case 0x64:
            SetReverbDepth(0x48);
            break;

        case 0x65:
            SetReverbDepth(0x50);
            break;

        case 0x66:
            SetReverbDepth(0x58);
            break;

        case 0x67:
            SetReverbDepth(0x60);
            break;

        case 0x68:
            SetReverbDepth(0x68);
            break;

        case 0x69:
            SetReverbDepth(0x70);
            break;

        case 0x6A:
            SetReverbDepth(0x78);
            break;

        case 0x6B:
            SetReverbDepth(0x7F);
            break;
        }
    }
}
