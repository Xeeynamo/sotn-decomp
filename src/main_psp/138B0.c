// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game_psp.h>

// https://pspdev.github.io/pspsdk/
#define PSP_LEGACY_TYPES_DEFINED // avoid processing psptypes.h

#include <pspumd.h>
#include <psppower.h>

// BSS
static s32 D_psp_08B1FB74;
static bool D_psp_08B1FB70;
static s32 powerLockCount;
static s32 D_psp_08B1FB68;
static s32 D_psp_08B1FB64;
static bool D_psp_08B1FB60;
static s32 D_psp_08B1FB5C;
static s32 D_psp_08B1FB58;
static s32 D_psp_08B1FB54;
static s32 umd_cb;

extern s32 D_psp_08B41FF0;
extern s32 power_cb;

static s32 umd_func(s32 count, s32 arg, void* param) {
    D_psp_08B1FB58 = arg;
    if (arg & PSP_UMD_MEDIA_IN) {
        D_psp_08B1FB54 |= 1;
    } else if (arg & PSP_UMD_MEDIA_OUT) {
        D_psp_08B1FB54 = 0;
        D_psp_08B1FB58 = 0;
    }
    if (arg & PSP_UMD_READABLE) {
        D_psp_08B1FB58 = 2;
    } else if (arg & PSP_UMD_READY) {
        D_psp_08B1FB58 = 1;
    } else if (arg & PSP_UMD_NOT_READY) {
        D_psp_08B1FB58 = 0;
    }
    return 0;
}

static void func_psp_0891228C(void) {
    volatile s32 ret;

    umd_cb = sceKernelCreateCallback("DVDUMD_SAMPLE", umd_func, NULL);
    if (umd_cb < 0) {
        umd_cb;
    }
    ret = sceUmdRegisterUMDCallBack(umd_cb);
    ret;
    if (sceUmdCheckMedium() == 0) {
        sceUmdWaitDriveStatCB(PSP_UMD_MEDIA_IN, 0);
    }
    ret = sceUmdActivate(PSP_UMD_MODE_POWERON, PSP_UMD_ALIAS_NAME);
    if (ret < 0) {
        sceUmdUnRegisterUMDCallBack(umd_cb);
        sceKernelDeleteCallback(umd_cb);
    }
    D_psp_08B1FB5C = 1;
    sceUmdWaitDriveStatCB(PSP_UMD_READABLE, 0);
    while (func_psp_089123B8() == 0) {
        sceKernelDelayThreadCB(100);
    }
    D_psp_08B1FB54 = 1;
}

static s32 func_psp_08912398(s32 argc, void* argv) {
    s32 var_s0;

    while (true) {
        sceKernelDelayThreadCB(100);
    }
    return var_s0;
}

s32 func_psp_089123B8(void) {
    u8 var_s2;
    u8 var_s1;
    u8 var_s0;

    sceKernelWaitSemaCB(D_psp_08B1FB68, 1, NULL);
    sceKernelSignalSema(D_psp_08B1FB68, 1);
    var_s2 = 0;
    var_s1 = 0;
    var_s0 = 0;
    if (D_psp_08B1FB58 == 2 && D_psp_08B1FB54 == 1) {
        var_s0 = 1;
    }
    if (var_s0 && D_psp_08B1FB5C) {
        var_s1 = 1;
    }
    if (var_s1 && !D_psp_08B1FB60 != 0) {
        var_s2 = 1;
    }
    return var_s2;
}

void func_psp_0891249C(void) {
    volatile s32 sp1C;
    volatile s32 sp18;

    D_psp_08B1FB54 = 0;
    D_psp_08B1FB58 = 0;
    D_psp_08B1FB5C = 0;
    func_psp_0891228C();
    sp18 = sceKernelCreateThread(
        "DVDUMD_CTRL", func_psp_08912398, 0x32, 0x1000, 0, NULL);
    sp18;
    D_psp_08B41FF0 = sp18;
    sp1C = sceKernelStartThread(D_psp_08B41FF0, 0, 0);
    sp1C;
}

static s32 power_func(s32 count, s32 arg, void* param) {
    if (arg & PSP_POWER_CB_POWER_SWITCH) {
        D_psp_08B1FB70 = true;
    }
    if (arg & PSP_POWER_CB_HOLD_SWITCH) {
    }
    if (arg & PSP_POWER_CB_STANDBY) {
    }
    if (arg & PSP_POWER_CB_RESUME_COMPLETE) {
        D_psp_08B1FB70 = false;
        D_psp_08B1FB60 = false;
        D_psp_08B1FB64++;
    }
    if (arg & PSP_POWER_CB_RESUMING) {
        D_psp_08B1FB60 = true;
    }
    if (arg & PSP_POWER_CB_SUSPENDING) {
        D_psp_08B1FB60 = true;
    }
    return 0;
}

s32 func_psp_089125F8(void) { return D_psp_08B1FB64; }

void LockPowerSwitch(void) {
    sceKernelPowerLock(0);
    powerLockCount++;
}

void UnlockPowerSwitch(void) {
    volatile s32* var_s0;

    if (powerLockCount <= 0) {
        var_s0 = &powerLockCount;
        *var_s0;
    }
    powerLockCount--;
    sceKernelPowerUnlock(0);
}

void func_psp_0891269C(void) {
    volatile s32 ret;

    D_psp_08B1FB60 = false;
    D_psp_08B1FB64 = 0;
    power_cb = sceKernelCreateCallback("DVDUMD_SAMPLE", power_func, NULL);
    if (power_cb < 0) {
        power_cb;
    }
    ret = scePowerRegisterCallback(0, power_cb);
    ret;
    powerLockCount = 0;
    D_psp_08B1FB68 = sceKernelCreateSema("p_off_lock_sema", 0, 1, 1, NULL);
}

void func_psp_0891273C(void) { D_psp_08B1FB74 = 0; }
