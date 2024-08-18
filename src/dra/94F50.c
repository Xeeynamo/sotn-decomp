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

        if (id > 0x200 && id <= 0x205) {
            PlaySeq(id);
            continue;
        }

#ifdef VERSION_HD
        if (id > 0x300 && id <= 0x530) {
#else
        if (id > 0x300 && id <= 0x532) {
#endif
            if (D_8013901C != 0) {
                if (D_8013901C != (id - 0x300)) {
                    AddCdSoundCommand(CD_SOUND_COMMAND_FADE_OUT_2);
                    g_CurrentXaSoundId = id - 0x300;
                    AddCdSoundCommand(CD_SOUND_COMMAND_START_XA);
                    continue;
                } else {
                    return;
                }
            } else {
                g_CurrentXaSoundId = id - 0x300;
                AddCdSoundCommand(CD_SOUND_COMMAND_START_XA);
                continue;
            }
        } else {
            switch (--id) {
            case 0xC:
                SoundWait();
                break;
            case SET_SOUNDMODE_MONO - 1:
                SetMonoStereo(MONO_SOUND);
                break;
            case SET_SOUNDMODE_STEREO - 1:
                SetMonoStereo(STEREO_SOUND);
                break;
            case SET_STOP_SEQ - 1:
                StopSeq();
                break;
            case SET_STOP_MUSIC - 1:
                AddCdSoundCommand(CD_SOUND_COMMAND_FADE_OUT_2);
                break;
            case SET_PAUSE_SFX_SCRIPTS - 1:
                PauseSfxScripts();
                break;
            case SET_UNPAUSE_SFX_SCRIPTS - 1:
                UnpauseSfxScripts();
                break;
            case 0x7F:
                D_80139A6C = 0x20;
                AddCdSoundCommand(CD_SOUND_COMMAND_10);
                break;
            case 0x80:
                D_80139A6C = 8;
                AddCdSoundCommand(CD_SOUND_COMMAND_10);
                break;
            case 0x81:
                D_80139A6C = 4;
                AddCdSoundCommand(CD_SOUND_COMMAND_10);
                break;
            case 0x82:
                D_80139A6C = 2;
                AddCdSoundCommand(CD_SOUND_COMMAND_10);
                break;
            case 0x83:
                D_80139A6C = 1;
                AddCdSoundCommand(CD_SOUND_COMMAND_10);
                break;
            case 0x8F:
                D_80139A6C = 0x80;
                AddCdSoundCommand(CD_SOUND_COMMAND_8);
                break;
            case 0x90:
                D_80139A6C = 8;
                AddCdSoundCommand(CD_SOUND_COMMAND_8);
                break;
            case 0x91:
                D_80139A6C = 4;
                AddCdSoundCommand(CD_SOUND_COMMAND_8);
                break;
            case 0x92:
                D_80139A6C = 2;
                AddCdSoundCommand(CD_SOUND_COMMAND_8);
                break;
            case 0x93:
                D_80139A6C = 1;
                AddCdSoundCommand(CD_SOUND_COMMAND_8);
                break;
            case 0x9F:
                SetReleaseRate1();
                break;
            case 0xA0:
                SetReleaseRateHigh20_21();
                g_CurSfxId2 = 0;
                break;
            case 0xA4:
                SetReleaseRateHigh22_23();
                g_CurSfxId = 0;
                break;
            case 0xA1:
                SetReleaseRateLow_20_21();
                g_CurSfxId2 = 0;
                break;
            case 0xA2:
                if (g_CurSfxId2 != 0) {
                    SetReleaseRateLow_20_21();
                }
                break;
            case 0xA3:
                if (g_CurSfxId2 != 0) {
                    KeyOnChannels20_21();
                }
                break;
            case 0xA5:
                SetReleaseRateLow_22_23();
                g_CurSfxId = 0;
                break;
            case 0xA6:
                if (g_CurSfxId != 0) {
                    SetReleaseRateLow_22_23();
                }
                break;
            case 0xA7:
                if (g_CurSfxId != 0) {
                    KeyOnChannels22_23();
                }
                break;
            case SET_VOLUME_22_23 - 1:
                SetVolume22_23();
                break;
            case SET_UNK_10 - 1:
                AddCdSoundCommand(CD_SOUND_COMMAND_12);
                break;
            case SET_UNK_11 - 1:
                AddCdSoundCommand(CD_SOUND_COMMAND_14);
                break;
            case SET_UNK_12 - 1:
                AddCdSoundCommand(CD_SOUND_COMMAND_16);
                break;
            case SET_UNK_0B - 1:
                AddCdSoundCommand(CD_SOUND_COMMAND_FADE_OUT_2);
                StopSeq();
                SetReleaseRate2();
                break;
            case 0x7:
                SetReleaseRate2();
                break;
            case 0xB:
                AddCdSoundCommand(CD_SOUND_COMMAND_FADE_OUT_2);
                StopSeq();
                SoundWait();
                SetReleaseRate2();
                break;
            case 0x59:
                EnableCdReverb(1);
                break;
            case 0x5A:
                EnableCdReverb(0);
                break;
            case 0x5B:
                SetReverbDepth(0x8);
                break;
            case 0x5C:
                SetReverbDepth(0x10);
                break;
            case 0x5D:
                SetReverbDepth(0x18);
                break;
            case 0x5E:
                SetReverbDepth(0x20);
                break;
            case 0x5F:
                SetReverbDepth(0x28);
                break;
            case 0x60:
                SetReverbDepth(0x30);
                break;
            case 0x61:
                SetReverbDepth(0x38);
                break;
            case 0x62:
                SetReverbDepth(0x40);
                break;
            case 0x63:
                SetReverbDepth(0x48);
                break;
            case 0x64:
                SetReverbDepth(0x50);
                break;
            case 0x65:
                SetReverbDepth(0x58);
                break;
            case 0x66:
                SetReverbDepth(0x60);
                break;
            case 0x67:
                SetReverbDepth(0x68);
                break;
            case 0x68:
                SetReverbDepth(0x70);
                break;
            case 0x69:
                SetReverbDepth(0x78);
                break;
            case 0x6A:
                SetReverbDepth(0x7f);
                break;
            }
        }
    }
}
