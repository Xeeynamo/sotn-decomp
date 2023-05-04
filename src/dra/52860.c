#include "dra.h"

// Needs PlaySfx to have a signature of
// void PlaySfx(s32 sfxId); but changing it causes other parts
// of binary to mismatch. Removing it from the header seems
// to make it match everywhere
void func_800F2860(void) {
    s32 var_v0;

    switch (D_801375C8) {
    case 1:
        PlaySfx(0x80);
        D_801375C8++;
        break;
    case 0:
    default:
        return;
    case 2:
        if (func_80131F68() == false) {
            D_801375C8++;
            break;
        }
        break;
    case 3:
#if defined(VERSION_US)
        PlaySfx(0x33F);
#elif defined(VERSION_HD)
        PlaySfx(0x33C);
#endif
        D_801375C8++;
        break;
    case 4:
        if (func_80131F68() != false) {
            D_801375C8++;
            break;
        }
        break;
    case 5:
        if (func_80131F68() == false) {
            D_801375C8++;
            break;
        }
        break;
    case 6:
        PlaySfx(D_80097910);
        D_801375C8 = 0;
        return;
    case 7:
        if (func_80131F68() != 0) {
            return;
        }
        D_801375C8--;
        break;
    case 8:
        PlaySfx(0x80);
        D_801375C8--;
        break;
    }
}

const int rodataPadding_jpt_800F288C = 0;
