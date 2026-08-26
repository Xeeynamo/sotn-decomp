// SPDX-License-Identifier: AGPL-3.0-or-later
#include "zero.h"
#include "zero/sound.h"
#include "inc_asm.h"
#include "sattypes.h"

void func_06012030(void) {
    StopPcm(7);
    D_8013B61C = 0;
}

// _KeyOffVox
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6012054, func_06012054);

void func_060120A0(void) {
    StopPcm(6);
    if (DAT_06062280 != 0) {
        func_0601BDD0(DAT_06062280);
    }
    g_PlayingXaBgmId = 0;
}

void func_060120D8(void) {
    StopPcm(6);
    if (DAT_06062280 != 0) {
        func_0601BDD0(DAT_06062280);
    }
}

s32 func_06012108(void) {
    s32 base;

    DAT_060641D0 = 0x11800;
    base = 0x200000;
    DAT_06062244 = base;
    DAT_06062378 = base + 0x4000;
    DAT_06062270.unk0 = DAT_06062378 + 0x800;
    DAT_06062270.unk4 = DAT_06062378 + 0x7000;
    return 0;
}

void func_06012154(u32 arg0) {
    u32 fadeStep;

    fadeStep = (DAT_060641EC / arg0) >> 1;
    DAT_06062388 = fadeStep;
    if (fadeStep == 0) {
        DAT_06062388 = 1;
    }
    DAT_0606422C = 0;
}

// _BgmFadeOut
s32 func_06012190(u32 arg0) {
    if (D_8013B61C != 0) {
        if (DAT_06063C18 != DAT_060641EC) {
            DAT_0606422C = (DAT_060641EC / arg0) >> 1;
            if (DAT_0606422C == 0) {
                DAT_0606422C = 1;
            }
            DAT_06062388 = 0;
            return 0;
        }
        return -1;
    }
    return -1;
}

s32 func_060121F0(u32 arg0) {
    if (D_8013B61C != 0) {
        if ((DAT_06063C18 != DAT_060641EC) || (DAT_06062388 != 0)) {
            DAT_0606422C = (DAT_060641EC / arg0) >> 1;
            if (DAT_0606422C == 0) {
                DAT_0606422C = 1;
            }
            DAT_06062388 = 0;
            DAT_06062258 = -1;
            return 0;
        }
        return -1;
    }
    return -1;
}

// _VoxFadeOutStop
s32 func_06012260(s32 arg0) {
    if (g_PlayingXaBgmId != 0) {
        DAT_06064384 = arg0;
        DAT_0606423C = 1;
        return 0;
    }

    return -1;
}

s32 func_06012290(s32 arg0) {
    if (DAT_06064300 != 0) {
        DAT_060642F4 = arg0;
        DAT_06064430 = 1;
        return 0;
    }
    return -1;
}

s32 func_060122C0(u32 arg0) {
    s32 temp_r7;
    u32 temp_r0;
    u32* temp_r2;

    temp_r7 = DAT_06064330;
    if (temp_r7 != 0) {
        return;
    }
    if ((u32)D_8013B61C <= 4U) {
        PlaySfx(0xF0000010);
        return 0;
    }
    DAT_06064330 = 1;
    if (D_8013B61C != 0) {
        if ((DAT_06063C18 != DAT_060641EC) || (DAT_06062388 != 0)) {
            temp_r2 = &DAT_0606422C;
            temp_r0 = (DAT_060641EC / arg0) >> 1;
            *temp_r2 = temp_r0;
            if (temp_r0 == 0) {
                *temp_r2 = 1;
            }
            DAT_06062388 = temp_r7;
            DAT_06064358 = 1;
            return 0;
        }
        return -1;
    }
    return -1;
}

// _BgmPauseFadeIn
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6012358, func_06012358);

s32 func_060123D4(s32 arg0) {
    s32 result;

    if ((u32)g_PlayingXaBgmId <= 4U) {
        PlaySfx(0xF0000010);
        return 0;
    }

    result = -1;
    if (g_PlayingXaBgmId != 0) {
        DAT_06064384 = arg0;
        DAT_0606423C = 1;
        DAT_060644E4 = 1;
        result = 0;
    }
    return result;
}

void func_06012428(s32 arg0) {
    if (arg0 != 0) {
        DAT_06064350 = arg0;
    } else {
        DAT_06064350 = 1;
    }
    DAT_0606423C = 1;
    DAT_06064488 = 2;
    DAT_06064384 = 0;
    func_06012554();
}

void func_06012474(void) {
    if (D_8013B61C == 5) {
        DAT_06063E70 = 1;
        if ((DAT_060641D4 != -1 && DAT_06063EB4 == 0) ||
            (DAT_060641D4 == -1 && DAT_06062238 != 0)) {
            DAT_06063EB4 = 1;
            DAT_060641F4 = 0;
            D_8013B61C = 8;
            StopPcm(7);
            d_060623B0[0] &= ~2;
        } else {
            DAT_06063E70 = 0;
        }
    }

    if (g_PlayingXaBgmId == 5) {
        DAT_06062250 = 1;
        if (DAT_06063EB0 != 0) {
            DAT_06062248 = 1;
            DAT_060623BC = 0;
            DAT_060641DC = 0;
            DAT_06064210 = 0;
            g_PlayingXaBgmId = 8;
            StopPcm(6);
            d_060623B0[1] &= ~2;
        } else {
            DAT_06062250 = DAT_06063EB0;
        }
    }
}

// _BgmPauseOff
void func_06012554(void) {
    if (DAT_06062248 == 1) {
        g_PlayingXaBgmId = DAT_06062248;
        DAT_060623BC = DAT_06062248;
        DAT_06062248 = 0;
        DAT_06062250 = 0;
    } else if (DAT_06063EB4 == 1 && g_PlayingXaBgmId == 0) {
        D_8013B61C = 9;
        DAT_060644C5 = 0;
        DAT_060644A0 = 30;
        func_0601C26C(DAT_06062290[DAT_06062268]);
    }
    DAT_060623A0 = 0;
    DAT_060641E4 = 0;
}

void func_060125EC(void) {
    D_8013B61C = 1;
    DAT_060641E0 = 1;
    DAT_060641F4 = 1;
    DAT_06063EB4 = 0;
    DAT_06063E70 = 0;
}

// _BgmPauseKeyOff
void func_06012620(void) {
    s32 bgmPaused;
    s32 voxPaused;

    bgmPaused = DAT_06063EB4;
    if (bgmPaused == 1) {
        D_8013B61C = 0;
        DAT_060641F4 = 0;
        DAT_06063EB4 = 0;
        DAT_06063E70 = 0;
        DAT_06063BD0 = bgmPaused;
    }

    voxPaused = DAT_06062248;
    if (voxPaused == 1) {
        g_PlayingXaBgmId = 0;
        DAT_060623BC = 0;
        DAT_06062248 = 0;
        DAT_06062250 = 0;
        DAT_06063BFC = voxPaused;
    }

    DAT_060623A0 = 0;
    DAT_060641E4 = 0;
}

void func_0601269C(void) {
    if (DAT_06064354 == 1) {
        DAT_06064354 = 0;
    }
}

void func_060126B8(void) {
    if (DAT_060644AC == 1) {
        DAT_060644AC = 0;
    }
}

s32 func_060126D4(s32 arg0) {
    s32 local[4];
    s32 status;
    s32 result;

    if (arg0 != 0) {
        DAT_06041280 = 0;
        return 1;
    }

    status = DAT_06041280;
    if (status == 0) {
        StopPcm(5);
        DAT_06064390 = ((s32(*)(s32, s32))PcmOpen)(DAT_06064324, 2);
        if (DAT_06064390 == 0) {
            DAT_06064390 = status;
            DAT_060644AC = status;
            return -1;
        }
        func_0601B910(DAT_06064390, local, local + 1, local + 2);
        DAT_06057C28 = local[0] * (local[1] - 1) + local[2];
        ((s32(*)(u32, s32))PcmLseek)(DAT_06064390, 0);
        result = ((s32(*)(s32, s32, s32))func_06016B9C)(
            DAT_06064390, 0x00211800, DAT_06057C28);
        if (result == -1) {
            DAT_06064390 = status;
            DAT_060644AC = status;
            return result;
        }
        DAT_06041280 = 1;
    }

    status = DAT_06041280;
    if (status == 1) {
        func_0601BEE8(DAT_06064390);
        func_0601BE3C(DAT_06064390, local + 3, &DAT_06057C24);
        if (DAT_06057C24 >= DAT_06057C28) {
            DAT_06064354 = status;
            PcmClose(DAT_06064390, 2);
            return 0;
        }
        return 1;
    }
    return status;
}

s32 func_060127F0(s32 arg0) {
    s32 work[4];
    s32 state;
    s32 handle;
    s32 result;

    if (arg0 != 0) {
        DAT_06041284 = 0;
        return 1;
    }

    state = DAT_06041284;
    if (state == 0) {
        StopPcm(5);
        handle = ((s32(*)(s32, s32))PcmOpen)(DAT_06064324, 2);
        DAT_060643D0 = handle;
        if (handle == 0) {
            DAT_060643D0 = state;
            DAT_060644AC = state;
            return -1;
        }

        func_0601B910(handle, &work[0], &work[1], &work[2]);
        DAT_06057C30 = work[0] * (work[1] - 1) + work[2];
        ((s32(*)(u32, s32))PcmLseek)((u32)DAT_060643D0, 0);
        result = ((s32(*)(s32, s32, s32))func_06016B9C)(
            DAT_060643D0, 0x22A000, DAT_06057C30);
        if (result == -1) {
            DAT_060643D0 = state;
            DAT_060644AC = state;
            return result;
        }
        DAT_06041284 = 1;
    }

    state = DAT_06041284;
    if (state == 1) {
        func_0601BEE8(DAT_060643D0);
        func_0601BE3C(DAT_060643D0, &work[3], &DAT_06057C2C);
        if (DAT_06057C2C >= DAT_06057C30) {
            DAT_060644AC = state;
            PcmClose(DAT_060643D0, 2);
            return 0;
        }
        return 1;
    }
    return state;
}

void func_06012908(void) {
    StopPcm(5);
    if (DAT_06064338 != 0) {
        func_0601BDD0(DAT_06064338);
        PcmClose(DAT_06064338, 2);
        DAT_06064338 = 0;
    }
    DAT_06064300 = 0;
}

void func_06012954(void) {
    StopPcm(5);
    if (DAT_06064338 != 0) {
        func_0601BDD0(DAT_06064338);
    }
    DAT_06064300 = 0;
}

void func_0601298C(void) {
    StopPcm(5);
    if (DAT_06064338 != 0) {
        func_0601BDD0(DAT_06064338);
    }
}
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60129BC, func_060129BC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6012C4C, func_06012C4C);

void func_06012CAC(void) {
    if (DAT_06064300 == 5) {
        DAT_06064234 = 1;
        if ((DAT_06064394 != -1 && DAT_0606438C == 0) ||
            (DAT_06064394 == -1 && DAT_06064360 != 0)) {
            DAT_0606438C = 1;
            DAT_06064334 = 0;
            DAT_06064300 = 8;
            StopPcm(5);
            d_060623B0[2] &= ~2;
        } else {
            DAT_06064234 = 0;
        }
    }
}

void func_06012D30(void) {
    if (DAT_0606438C == 1) {
        DAT_06064300 = DAT_0606438C;
        DAT_0606433C = DAT_0606438C;
        DAT_06064334 = DAT_0606438C;
        DAT_0606438C = 0;
        DAT_06064234 = 0;
        func_0601C26C(DAT_06064338);
    }
    DAT_060642DC = 0;
}

s32 func_06012D88(void) {
    if (DAT_060641D8 == 0) {
        if (DAT_060642EC <= 1) {
            if ((DAT_06064354 <= 1) && (DAT_060644AC <= 1)) {
                return 0;
            }
        }
    }
    return 2;
}

// original name : xa_play_ck
bool func_06012DD0(void) {
    bool ret;

    if (D_8013B61C == 9 || (D_8013B61C == 0 && g_PlayingXaBgmId == 0)) {
        ret = 0;
    } else {
        ret = 1;
    }
    return ret;
}

// original name : vox_play_ck
bool func_06012DFC(void) {
    if (g_PlayingXaBgmId != 0) {
        return 1;
    }
    return 0;
}

// SAT: 0x06012E18
bool CdSoundCommandQueueEmpty(void) {
    bool ret;

    if (DAT_06064250 != 0 || DAT_06064414 != DAT_0606423a) {
        ret = 0;
    } else {
        ret = 1;
    }
    return ret;
}

// _sd_xapause_chk
s32 func_06012E4C(void) {
    s32 var_r0;

    if ((DAT_060642E8 != 0) && (IsXaBgmPlaying() == 0)) {
        DAT_060642E8 = 0;
    }
    if ((DAT_060644C2 != 0) && (DAT_0606423C == 0)) {
        DAT_060644C2 = 0;
    }
    var_r0 = 0;
    if ((DAT_060642E8 == 0) && (DAT_060644C2 == 0)) {
        if (DAT_06064474 != 0) {
            if (((s32(*)(void))(s32)func_06012DD0)() == 0) {
                DAT_06064474 = 0;
            }
            if (DAT_06064400 != 0) {
                DAT_06064474 = 0;
            }
        }
        if ((DAT_06064378 != 0) &&
            (((s32(*)(void))(s32)func_06012DD0)() != 0) &&
            (DAT_06062388 == 0) && (DAT_06064350 == 0)) {
            DAT_06064378 = 0;
        }
        var_r0 = 0;
        if (DAT_06064474 == 0) {
            var_r0 = 1;
            if (DAT_06064378 != 0) {
                var_r0 = 0;
                if (DAT_0606442C != 0) {
                    var_r0 = 1;
                }
            }
        }
    }
    return var_r0;
}

void func_06012F30(void) {
    while ((D_8013B61C != 0 && (u32)D_8013B61C <= 4U) ||
           (g_PlayingXaBgmId != 0 && (u32)g_PlayingXaBgmId <= 4U)) {
        func_06010400();
        SCL_DisplayFrame();
    }
}

// _sd_xa_wait2
s32 func_06012F7C(void) {
    if ((D_8013B61C != 0) && ((u32)D_8013B61C <= 4U)) {
        return 0;
    }
    if ((g_PlayingXaBgmId != 0) && ((u32)g_PlayingXaBgmId <= 4U)) {
        return 0;
    }
    return 1;
}

const u16 DAT_06012FB0 = 0;
const u16 DAT_06012FB2 = 0;
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6012FB4, func_06012FB4);

// _sd_alloff_chk
bool func_06013320(void) {
    if (DAT_060644C0 == 2) {
        return 1;
    }
    return 0;
}

// _sd_reset2
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601333C, func_0601333C);

void MuteCd(void) {
    g_MuteCd = 1;
    DAT_060644dc = 2;
}

void UnMuteCd(void) {
    g_MuteCd = 0;
    DAT_060644dc = 2;
}

// _conve
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60133CC, func_060133CC);

// _convertDVI_STE
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6013538, func_06013538);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60139C4, func_060139C4);

void func_06014424(void) {
    while (SMPC_SF & 1) {
    }
    SMPC_SF = 1;
    SMPC_COMREG = 3;
    while (SMPC_SF & 1) {
    }
    DAT_06000310(0x94, func_060139C4);
    SMPC_SF = 1;
    SMPC_COMREG = 2;
    while (SMPC_SF & 1) {
    }
}
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601449C, func_0601449C);
void func_06014504(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 savedArg3;

    savedArg3 = arg3;

    while (UNCACHED_SOUND_REQUESTS[arg4].unk0 != 0) {
    }

    DAT_06063C30[arg4].unk8 = arg0;
    DAT_06063C30[arg4].unkC = arg1;
    DAT_06063C30[arg4].unk10 = arg2;
    arg3 = 1;
    DAT_06063C30[arg4].unk14 = arg3;
    DAT_06063C30[arg4].unk18 = savedArg3;
    DAT_06063C30[arg4].unk4 = 0;
    DAT_06063C30[arg4].unk0 = arg3;
}
void func_0601454C(s32 arg0, s32 arg1, s32 arg2, s16 arg3, s32 arg4, s32 arg5) {
    if (UNCACHED_SOUND_REQUESTS[arg5].unk0 != 0) {
        do {
        } while (UNCACHED_SOUND_REQUESTS[arg5].unk0 != 0);
    }

    DAT_06063C30[arg5].unk8 = arg0;
    DAT_06063C30[arg5].unkC = arg1;
    DAT_06063C30[arg5].unk10 = arg2;
    DAT_06063C30[arg5].unk24 = arg3;
    DAT_06063C30[arg5].unk1C = arg4;
    DAT_06063C30[arg5].unk14 = 0;
    DAT_06063C30[arg5].unk4 = 0;
    DAT_06063C30[arg5].unk0 = 1;
}
void func_060145AC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    while (UNCACHED_SOUND_REQUESTS[arg3].unk0 != 0) {
    }

    DAT_06063C30[arg3].unk8 = arg0;
    DAT_06063C30[arg3].unkC = arg1;
    DAT_06063C30[arg3].unk10 = arg2;
    DAT_06063C30[arg3].unk14 = 0;
    DAT_06063C30[arg3].unk4 = 0;
    DAT_06063C30[arg3].unk0 = 1;
}
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60145F8, func_060145F8);
void func_06014658(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    SoundRequest* request;

    if (UNCACHED_SOUND_REQUESTS[arg3].unk0 != 0) {
        do {
        } while (UNCACHED_SOUND_REQUESTS[arg3].unk0 != 0);
    }

    request = &DAT_06063C30[arg3];
    request->unk8 = arg0;
    request->unkC = arg1;
    request->unk10 = arg2;
    request->unk14 = 0;
    request->unk4 = 1;
    DAT_06063C30[arg3].unk0 = 1;
}
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60146A4, func_060146A4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6014724, func_06014724);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601476C, func_0601476C);

// _RestartBgmStream
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6014B80, func_06014B80);

s32 func_06014C20(void) {
    if (DAT_06062280 == 0) {
        return -1;
    }
    d_060623B0[1] |= 2;
    DAT_0606227C = 0;
    return 0;
}

// _OpenVoxFile
s32 func_06014C54(void) {
    if (DAT_06062280 != 0) {
        StopPcm(6);
        PcmClose(DAT_06062280, 1);
        DAT_06062280 = 0;
    }

    DAT_06062280 = ((s32(*)(s32, s32))PcmOpen)(-0x0FFFFF10, 1);
    if (DAT_06062280 == 0) {
        return -1;
    }

    d_060623B0[1] &= ~2;
    return 0;
}

s32 func_06014CB8(s32 arg0) {
    s32 temp_r0;

    if (DAT_06062290[arg0] != 0) {
        StopPcm(7);
        PcmClose(DAT_06062290[arg0], 0);
        DAT_06062290[arg0] = 0;
    }
    temp_r0 = ((s32(*)(s32, s32))PcmOpen)(arg0 + 0xE0000000, 0);
    DAT_06062290[arg0] = temp_r0;
    if (temp_r0 == 0)
        return -1;
    *d_060623B0 &= ~2;
    DAT_0601C01C(DAT_06062290[arg0], 0);
    return 0;
}
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6014D44, func_06014D44);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6014F3C, func_06014F3C);

// _BgmCdLoadWithLoop
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6015140, func_06015140);

// _VoxCdLoad
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60155CC, func_060155CC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60157CC, func_060157CC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6015E68, func_06015E68);

void func_06016614(void) {
    if (DAT_060641D4 == -1) {
        func_060157CC();
    } else {
        func_06015E68();
    }
}
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6016644, func_06016644);

void PcmOpen(s32 code) {
    u8 name[0x10];
    code2name(code, name);
    func_06017F5C(name);
}

void PcmLseek(u32 arg0, s32 arg1) {
    s32 iVar1 = func_0601B8B4(arg0, arg1 + 1);
    func_0601B75C(arg0, iVar1 - 1, 0);
}

void func_06016B9C(s32 arg0, s32 arg1, s32 arg2) {
    func_06017FA4(arg1, arg2, arg0);
}

void func_06016BBC(s32 arg0, s32 arg1, s32 arg2) {
    func_06017FA4(arg1, arg2, arg0);
}

s32 d_060623B0[];

void PcmClose(s32 arg0, s32 arg1) {
    func_0601B724();
    d_060623B0[arg1] = 0;
}

void func_06016C08(void) {
    s32* var_r8 = &DAT_06064208;

    // func_06012154 is defined above with a u32 parameter; the call site passes
    // its argument as a 16-bit value.
    if (*var_r8 == 0xFF0000F8) {
        ((void (*)(s16))func_06012154)(0x78);
    } else if (*var_r8 == 0xFF0000F9) {
        ((void (*)(s16))func_06012154)(0xF0);
    } else {
        return;
    }

    DAT_06063C18 = DAT_060641EC;
    *var_r8 = 0;
}
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6016C60, func_06016C60);

void func_06016D84(void) {
    u32 var_r0;
    u32 var_r0_2;
    u32 var_r2;

    if ((g_PlayingXaBgmId == 5) && (DAT_0606423C != 0)) {
        if (DAT_06064384 != 0) {
            var_r2 = DAT_06064498;
            var_r0 = DAT_06063EA8 / DAT_06064384;
            if (var_r0 <= 0xFU) {
                var_r0 = 0x10;
            }
            if (var_r2 < var_r0) {
                var_r2 = 0;
            } else {
                var_r2 -= var_r0;
            }
            DAT_06064498 = var_r2;
            if (var_r2 == 0) {
                DAT_0606423C = var_r2;
                if (DAT_060644E4 == 0) {
                    // func_060120A0 is defined above, so call it indirectly to
                    // keep -O3 from inlining it here.
                    ((void (*)())func_060120A0)();
                }
            }
        } else if (DAT_06064350 != 0) {
            if (((s8)DAT_06064488 != 0) && (var_r2 = 0, (DAT_06064498 == 0))) {
                DAT_06064488 -= 1;
            } else {
                var_r2 = DAT_06064498;
            }
            var_r0_2 = DAT_06063EA8 / DAT_06064350;
            if (var_r0_2 <= 0xFU) {
                var_r0_2 = 0x10;
            }
            var_r2 += var_r0_2;
            if (var_r2 > DAT_06063EA8) {
                var_r2 = DAT_06063EA8;
            }
            DAT_06064498 = var_r2;
            if (var_r2 == DAT_06063EA8) {
                DAT_0606423C = 0;
                DAT_06064350 = 0;
            }
        }
    }
    if ((DAT_06064498 == 0) && (DAT_060644E4 == 1)) {
        DAT_060644E4 = 0;
        func_06012474();
    }
}

void func_06016E84(void) {
    u32 var_r0;
    u32 var_r2;

    if (DAT_06064300 == 5) {
        if (DAT_06064430 != 0) {
            var_r2 = DAT_0606448C;
            var_r0 = var_r2 / DAT_060642F4;
            if (var_r0 <= 0xF) {
                var_r0 = 0x10;
            }
            if (var_r2 < var_r0) {
                var_r2 = 0;
            } else {
                var_r2 -= var_r0;
            }
            DAT_0606448C = var_r2;
            if (var_r2 == 0) {
                DAT_06064430 = var_r2;
            }
        }
    }
}

// ZOE apparently has a later version of this same library
// https://github.com/Joy-Division/old-zoe/blob/51af2e237d75aa27bc1e4803f08bdf48902fa90c/module/sound/sd_file.c#L545

// func_06016EE4
void code2name(u32 code, u8* name) {
    if (code >= 0xE0000000 && code < 0xE0010000) {
        name[0] = 'S';
        name[1] = 'D';
    }
    if (code >= 0xF0000000 && code < 0xF0010000) {
        name[0] = 'S';
        name[1] = 'D';
    }
    if (code >= 0xFE000000 && code < 0xFE010000) {
        name[0] = 'W';
        name[1] = 'V';
    }

    name[2] = num2char((code >> 4) & 0xF);
    name[3] = num2char(code & 0xF);

    name[4] = '.';
    name[5] = 'P';
    name[6] = 'C';
    name[7] = 'M';
    name[8] = '\0';
}

// func_06016F9C
char num2char(u32 num) {
    num &= 0x0F;

    if (num < 10) {
        num += 0x30;
    } else {
        num += 0x37;
    }
    return num;
}

s32 func_06016FB8(void) {
    if (DAT_06064338 != 0) {
        StopPcm(5);
        ((void (*)())PcmClose)(DAT_06064338, 2);
        DAT_06064338 = 0;
    }

    DAT_06064338 = ((s32(*)(s32, s32))PcmOpen)(-0x0FFFFF0B, 2);
    if (DAT_06064338 == 0)
        return -1;

    d_060623B0[2] &= ~2;
    return 0;
}

// _StartvoxvdStream
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601701C, func_0601701C);

void func_060174D8(void) {
    if (DAT_06064394 == -1) {
        func_06017508();
    } else {
        func_06017988();
    }
}

// _voxvdSpuTransOnmemNoloop
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6017508, func_06017508);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6017988, func_06017988);

// _RestartvoxvdStream
s32 func_06017F28(void) {
    if (DAT_06064338 == 0) {
        return -1;
    } else {
        d_060623B0[2] |= 2;
        DAT_06064238 = 0;
        return 0;
    }
}

s32 func_06017F5C(u8* arg0) {
    s32 handle;

    func_0601B448(&DAT_06063E90);
    handle = func_0601B674(func_0601B4AC(arg0));
    func_0601BDD0(handle);
    return handle;
}

// _dat_read
s32 func_06017FA4(s32 param_1, s32 param_2, s32 param_3) {
    s32 sector;

    sector = func_0601B8B4(param_3, param_2);
    if (func_0601BC14(param_3, sector, param_1, param_2) != 0) {
        return -1;
    }
    return sector * 0x800;
}
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6017FF4, func_06017FF4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018034, func_06018034);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60180E0, func_060180E0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018260, func_06018260);
