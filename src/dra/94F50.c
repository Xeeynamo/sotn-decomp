#include "dra.h"
#include "objects.h"
#include "sfx.h"

extern s16 D_80139064;

void ExecSoundCommands(void) {
    s16 id;

    while (g_SoundCommandRingBufferReadPos != g_SoundCommandRingBufferWritePos) {
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
                    func_80132C2C(2);
                    D_80139064 = id - 0x300;
                    func_80132C2C(4);
                    continue;
                } else {
                    return;
                }
            } else {
                D_80139064 = id - 0x300;
                func_80132C2C(4);
                continue;
            }
        } else {
            switch (--id) {
            case 0xC:
                func_8013271C();
                break;
            case 0x4:
                SetMonoStereo(MONO_SOUND);
                break;
            case 0x5:
                SetMonoStereo(STEREO_SOUND);
                break;
            case 0x6:
                StopSeq();
                break;
            case 0x9:
                func_80132C2C(2);
                break;
            case 0xD:
                func_801349F4();
                break;
            case 0xE:
                func_80134B48();
                break;
            case 0x7F:
                D_80139A6C = 0x20;
                func_80132C2C(0xA);
                break;
            case 0x80:
                D_80139A6C = 8;
                func_80132C2C(0xA);
                break;
            case 0x81:
                D_80139A6C = 4;
                func_80132C2C(0xA);
                break;
            case 0x82:
                D_80139A6C = 2;
                func_80132C2C(0xA);
                break;
            case 0x83:
                D_80139A6C = 1;
                func_80132C2C(0xA);
                break;
            case 0x8F:
                D_80139A6C = 0x80;
                func_80132C2C(8);
                break;
            case 0x90:
                D_80139A6C = 8;
                func_80132C2C(8);
                break;
            case 0x91:
                D_80139A6C = 4;
                func_80132C2C(8);
                break;
            case 0x92:
                D_80139A6C = 2;
                func_80132C2C(8);
                break;
            case 0x93:
                D_80139A6C = 1;
                func_80132C2C(8);
                break;
            case 0x9F:
                func_80134104();
                break;
            case 0xA0:
                func_80134508();
                D_8013B664 = 0;
                break;
            case 0xA4:
                func_80134564();
                D_80139804 = 0;
                break;
            case 0xA1:
                func_801345C0();
                D_8013B664 = 0;
                break;
            case 0xA2:
                if (D_8013B664 != 0) {
                    func_801345C0();
                }
                break;
            case 0xA3:
                if (D_8013B664 != 0) {
                    func_80134C60();
                }
                break;
            case 0xA5:
                func_8013461C();
                D_80139804 = 0;
                break;
            case 0xA6:
                if (D_80139804 != 0) {
                    func_8013461C();
                }
                break;
            case 0xA7:
                if (D_80139804 != 0) {
                    func_80134D14();
                }
                break;
            case 0x0:
                func_80134E64();
                break;
            case 0xF:
                func_80132C2C(0xC);
                break;
            case 0x10:
                func_80132C2C(0xE);
                break;
            case 0x11:
                func_80132C2C(0x10);
                break;
            case 0xA:
                func_80132C2C(2);
                StopSeq();
                func_8013415C();
                break;
            case 0x7:
                func_8013415C();
                break;
            case 0xB:
                func_80132C2C(2);
                StopSeq();
                func_8013271C();
                func_8013415C();
                break;
            case 0x59:
                func_80133780(1);
                break;
            case 0x5A:
                func_80133780(0);
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
