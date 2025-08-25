// SPDX-License-Identifier: MIT
#include "common.h"
#include "registers.h"
#include <psxsdk/libcd.h>

extern s32 D_80097960;
extern s32 D_800987B8;
extern StHEADER* D_800987C8;
extern volatile s32 D_80098894;

u_long StGetNext(u_long** addr, u_long** header) {
    volatile StHEADER* ptr = &D_800987C8[D_80097960];
    if (ptr->id == 1) {
        D_80097960 = 0;
        if (D_800987B8 != 0) {
            ptr->id = 0;
        }
        ptr = &D_800987C8[D_80097960];
    }
    if (ptr->id == 2) {
        ptr->id = 4;
        *addr = &D_800987C8[D_80098894] + (D_80097960 * 0x3F);
        *header = ptr;
        return 0;
    } else {
        return 1;
    }
}
