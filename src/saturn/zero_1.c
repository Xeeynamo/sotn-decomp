// SPDX-License-Identifier: AGPL-3.0-or-later
#include "zero.h"
#include "zero/sound.h"
#include "inc_asm.h"
#include "sattypes.h"

static inline void set_sr(register Uint32 sr) {
    __asm__ volatile("ldc	%0, sr" : : "r"(sr));
}

static inline Uint32 get_sr(void) {
    Uint32 sr;
    __asm__ volatile("stc	sr, %0" : "=r"(sr));
    return sr;
}

static inline Uint32 get_imask(void) {
    Uint32 imask = (get_sr() & 0x000000F0) >> 4;
    return imask;
}

static inline void set_imask(register Uint32 imask) {
    Uint32 sr = get_sr();

    sr &= ~0x000000F0;
    sr |= imask << 4;
    set_sr(sr);
}

void func_06011A6C(s32 arg0) {
    s32 i;

    for (i = 0;; i++) {
        if (DAT_06064250[i] != 0) {
            if (i != 0x1E) {
                continue;
            }
        }
        break;
    }
    DAT_06064250[i] = arg0;
    DAT_06064250[i + 1] = 0;
}

s32 PlaySfxVolPan(s32 sfxId, s32 sfxVol, s16 sfxPan) {
    s32 ret = 0;

    if (sfxId < 0x600 || sfxId > 0x916) {
        return -3;
    }
    if (sfxPan < -8 || sfxPan > 8) {
        sfxPan = 0x40;
        ret = -1;
    } else {
        if (sfxPan == 0) {
            sfxPan = sfxPan * 8 + 0x40;
        } else if (sfxPan > 0) {
            sfxPan = sfxPan * 8 + 0x3F;
        } else {
            sfxPan = sfxPan * 8 + 0x40;
        }
    }
    DAT_06064230 = sfxVol;
    DAT_060643C4 = sfxPan;
    DAT_060644C4 = 1;
    PlaySfx(sfxId);
    DAT_060644C4 = 0;
    return ret;
}

s32 func_06011B28(s32 arg0) {
    if (arg0 < 0) {
        arg0 = 0;
    } else if (arg0 < 0x10) {
        arg0 *= 2;
    } else if (arg0 < 0x20) {
        arg0 = ((arg0 - 0x10) * 0x26) / 0x10 + 0x20;
    } else if (arg0 < 0x30) {
        arg0 = ((arg0 - 0x20) * 0x1A) / 0x10 + 0x46;
    } else if (arg0 < 0x40) {
        arg0 = ((arg0 - 0x30) * 0x0D) / 0x10 + 0x60;
    } else if (arg0 < 0x50) {
        arg0 = (arg0 - 0x40) / 2 + 0x6D;
    } else if (arg0 < 0x60) {
        arg0 = ((arg0 - 0x50) * 5) / 0x10 + 0x75;
    } else if (arg0 < 0x70) {
        arg0 = (arg0 - 0x60) / 4 + 0x7A;
    } else if (arg0 < 0x82) {
        arg0 = ((arg0 - 0x70) * 4) / 18 + 0x7E;
    }
    if (arg0 == 0) {
        arg0 = 1;
    }
    return arg0;
}

s32 func_06011C28(s32 volume, s16 pan) {
    s32 result;

    result = 0;
    if (DAT_060643E0[7] == 0) {
        return -2;
    }
    if (pan < -8 || pan > 8) {
        pan = 0x40;
        result = -1;
    } else if (pan == 0) {
        pan = 0x40;
    } else {
        if (pan > 0) {
            pan = pan * 8 + 0x3F;
        } else {
            pan = pan * 8 + 0x40;
        }
    }
    volume = func_06011B28((DAT_060644B0 * volume) / 127);
    if (volume == 0) {
        volume = 1;
    }
    SND_SetSeqVl(7, volume, 0);
    SND_SetSeqPan(7, 0, pan);
    DAT_0606436E = pan;
    return result;
}

const u16 DAT_06011CE0 = 0x5344;
const u16 DAT_06011CE2 = 0x0000;

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6011CE4, func_06011CE4);

void func_06011EE0(s32 arg0, s32 arg1) {
    s32 i;
    u32 msk;

    msk = get_imask();
    set_imask(15);
    DAT_06063BD8 = 0;
    for (i = 0; i < 4; i++) {
        DAT_06063C30[i].unk0 = 0;
    }
    func_06014424();
    set_imask(msk);
}

void func_06011F40(s32 arg0);
void func_06011F40_noInline(s32 arg0) { SND_StopPcm2(arg0); }

void func_06011F58(void) {
    s32 bgm;

    func_06011F40(7);
    DAT_060641F4 = 0;
    DAT_06063EB4 = 0;
    DAT_06062258 = 0;
    bgm = DAT_06062290[DAT_06062268];
    if (bgm != 0) {
        GFS_NwStop(bgm);
        DAT_06063C1C = 0;
    }
    DAT_06063BE0 = 0;
    DAT_06063BD4 = 0;
}

// original name: KeyOffBGM2
void func_06011FC8(void) {
    s32 bgm;

    func_06011F40(7);
    DAT_060641F4 = 0;
    DAT_06063EB4 = 0;
    bgm = DAT_06062290[DAT_06062268];
    if (bgm != 0) {
        GFS_NwStop(bgm);
        DAT_06063C1C = 0;
    }
    DAT_06063BE0 = 0;
    DAT_06063BD4 = 0;
}

void func_06012030(void) {
    func_06011F40(7);
    DAT_06063BE0 = 0;
}

// original name: KeyOffVox
void func_06012054(void) {
    func_06011F40(6);
    if (DAT_06062280 != NULL) {
        GFS_NwStop(DAT_06062280);
        PcmClose(DAT_06062280, 1);
        DAT_06062280 = NULL;
    }
    DAT_06064214 = 0;
}

void func_060120A0(void);
void func_060120A0_noInline(void) {
    func_06011F40(6);
    if (DAT_06062280 != NULL) {
        GFS_NwStop(DAT_06062280);
    }
    DAT_06064214 = 0;
}

void func_060120D8(void) {
    func_06011F40(6);
    if (DAT_06062280 != NULL) {
        GFS_NwStop(DAT_06062280);
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
    DAT_06062388 = (DAT_060641EC / arg0) >> 1;
    if (DAT_06062388 == 0) {
        DAT_06062388 = 1;
    }
    DAT_0606422C = 0;
}

// original name: BgmFadeOut
s32 func_06012190(u32 arg0) {
    if (DAT_06063BE0 != 0) {
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
    if (DAT_06063BE0 != 0) {
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

// original name: VoxFadeOutStop
s32 func_06012260(s32 arg0) {
    if (DAT_06064214 != 0) {
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
    if (DAT_06064330 != 0) {
        return;
    }
    if (DAT_06063BE0 < 5) {
        PlaySfx(SET_UNK_10);
        return 0;
    }
    DAT_06064330 = 1;
    if (DAT_06063BE0 != 0) {
        if ((DAT_06063C18 != DAT_060641EC) || (DAT_06062388 != 0)) {
            DAT_0606422C = (DAT_060641EC / arg0) >> 1;
            if (DAT_0606422C == 0) {
                DAT_0606422C = 1;
            }
            DAT_06062388 = 0;
            DAT_06064358 = 1;
            return 0;
        }
        return -1;
    }
    return -1;
}

// original name: BgmPauseFadeIn
void func_06012358(u32 fadeDuration) {
    if (DAT_06064400 != 0) {
        DAT_06062258 = 0;
        PlaySfx(DAT_06064320);
        DAT_06064400 = 0;
    }
    func_06012154(fadeDuration);
    func_06012554();
}

s32 func_060123D4(s32 arg0) {
    if (DAT_06064214 < 5) {
        PlaySfx(SET_UNK_10);
        return 0;
    }

    if (DAT_06064214 != 0) {
        DAT_06064384 = arg0;
        DAT_0606423C = 1;
        DAT_060644E4 = 1;
        return 0;
    }
    return -1;
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
    if (DAT_06063BE0 == 5) {
        DAT_06063E70 = 1;
        if ((DAT_060641D4 != -1 && DAT_06063EB4 == 0) ||
            (DAT_060641D4 == -1 && DAT_06062238 != 0)) {
            DAT_06063EB4 = 1;
            DAT_060641F4 = 0;
            DAT_06063BE0 = 8;
            func_06011F40(7);
            DAT_060623B0[0] &= ~2;
        } else {
            DAT_06063E70 = 0;
        }
    }

    if (DAT_06064214 == 5) {
        DAT_06062250 = 1;
        if (DAT_06063EB0 != 0) {
            DAT_06062248 = 1;
            DAT_060623BC = 0;
            DAT_060641DC = 0;
            DAT_06064210 = 0;
            DAT_06064214 = 8;
            func_06011F40(6);
            DAT_060623B0[1] &= ~2;
        } else {
            DAT_06062250 = DAT_06063EB0;
        }
    }
}

// original name: BgmPauseOff
void func_06012554(void) {
    if (DAT_06062248 == 1) {
        DAT_06064214 = DAT_06062248;
        DAT_060623BC = DAT_06062248;
        DAT_06062248 = 0;
        DAT_06062250 = 0;
    } else if (DAT_06063EB4 == 1 && DAT_06064214 == 0) {
        DAT_06063BE0 = 9;
        DAT_060644C5 = 0;
        DAT_060644A0 = 30;
        GFS_CdMovePickup(DAT_06062290[DAT_06062268]);
    }
    DAT_060623A0 = 0;
    DAT_060641E4 = 0;
}

void func_060125EC(void) {
    DAT_06063BE0 = 1;
    DAT_060641E0 = 1;
    DAT_060641F4 = 1;
    DAT_06063EB4 = 0;
    DAT_06063E70 = 0;
}

// original name: BgmPauseKeyOff
void func_06012620(void) {
    if (DAT_06063EB4 == 1) {
        DAT_06063BE0 = 0;
        DAT_060641F4 = 0;
        DAT_06063EB4 = 0;
        DAT_06063E70 = 0;
        DAT_06063BD0 = 1;
    }

    if (DAT_06062248 == 1) {
        DAT_06064214 = 0;
        DAT_060623BC = 0;
        DAT_06062248 = 0;
        DAT_06062250 = 0;
        DAT_06063BFC = 1;
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
    s32 sctsz;
    s32 nsct;
    s32 lstlen;
    s32 amode;
    s32 result;

    if (arg0 != 0) {
        DAT_06041280 = 0;
        return 1;
    }

    if (DAT_06041280 == 0) {
        func_06011F40(5);
        DAT_06064390 = ((s32(*)(s32, s32))PcmOpen)(DAT_06064324, 2);
        if (DAT_06064390 == 0) {
            DAT_06064390 = 0;
            DAT_060644AC = 0;
            return -1;
        }
        GFS_GetFileSize(DAT_06064390, &sctsz, &nsct, &lstlen);
        DAT_06057C28 = sctsz * (nsct - 1) + lstlen;
        PcmLseek(DAT_06064390, 0);
        result = func_06016B9C(DAT_06064390, 0x211800, DAT_06057C28);
        if (result == -1) {
            DAT_06064390 = 0;
            DAT_060644AC = 0;
            return result;
        }
        DAT_06041280 = 1;
    }

    if (DAT_06041280 == 1) {
        GFS_NwExecOne(DAT_06064390);
        GFS_NwGetStat(DAT_06064390, &amode, &DAT_06057C24);
        if (DAT_06057C24 >= DAT_06057C28) {
            DAT_06064354 = 1;
            PcmClose(DAT_06064390, 2);
            return 0;
        }
        return 1;
    }
    return DAT_06041280;
}

s32 func_060127F0(s32 arg0) {
    s32 sctsz;
    s32 nsct;
    s32 lstlen;
    s32 amode;
    s32 result;

    if (arg0 != 0) {
        DAT_06041284 = 0;
        return 1;
    }

    if (DAT_06041284 == 0) {
        func_06011F40(5);
        DAT_060643D0 = ((s32(*)(s32, s32))PcmOpen)(DAT_06064324, 2);
        if (DAT_060643D0 == 0) {
            DAT_060643D0 = 0;
            DAT_060644AC = 0;
            return -1;
        }

        GFS_GetFileSize(DAT_060643D0, &sctsz, &nsct, &lstlen);
        DAT_06057C30 = sctsz * (nsct - 1) + lstlen;
        PcmLseek(DAT_060643D0, 0);
        result = func_06016B9C(DAT_060643D0, 0x22A000, DAT_06057C30);
        if (result == -1) {
            DAT_060643D0 = 0;
            DAT_060644AC = 0;
            return result;
        }
        DAT_06041284 = 1;
    }

    if (DAT_06041284 == 1) {
        GFS_NwExecOne(DAT_060643D0);
        GFS_NwGetStat(DAT_060643D0, &amode, &DAT_06057C2C);
        if (DAT_06057C2C >= DAT_06057C30) {
            DAT_060644AC = 1;
            PcmClose(DAT_060643D0, 2);
            return 0;
        }
        return 1;
    }
    return DAT_06041284;
}

void func_06012908(void) {
    func_06011F40(5);
    if (DAT_06064338 != NULL) {
        GFS_NwStop(DAT_06064338);
        PcmClose(DAT_06064338, 2);
        DAT_06064338 = NULL;
    }
    DAT_06064300 = 0;
}

void func_06012954(void) {
    func_06011F40(5);
    if (DAT_06064338 != NULL) {
        GFS_NwStop(DAT_06064338);
    }
    DAT_06064300 = 0;
}

void func_0601298C(void) {
    func_06011F40(5);
    if (DAT_06064338 != NULL) {
        GFS_NwStop(DAT_06064338);
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
            func_06011F40(5);
            DAT_060623B0[2] &= ~2;
        } else {
            DAT_06064234 = 0;
        }
    }
}

void func_06012D30(void) {
    if (DAT_0606438C == 1) {
        DAT_06064300 = 1;
        DAT_0606433C = 1;
        DAT_06064334 = 1;
        DAT_0606438C = 0;
        DAT_06064234 = 0;
        GFS_CdMovePickup(DAT_06064338);
    }
    DAT_060642DC = 0;
}

s32 func_06012D88(void) {
    if (DAT_060641D8 == 0) {
        if (DAT_060642EC < 2) {
            if (DAT_06064354 < 2 && DAT_060644AC < 2) {
                return 0;
            }
        }
    }
    return 2;
}

// original name : xa_play_ck
bool func_06012DD0_noInline(void) {
    if (DAT_06063BE0 == 9 || (DAT_06063BE0 == 0 && DAT_06064214 == 0)) {
        return 0;
    } else {
        return 1;
    }
}

// original name : vox_play_ck
bool func_06012DFC_noInline(void) {
    if (DAT_06064214 != 0) {
        return 1;
    } else {
        return 0;
    }
}

// SAT: 0x06012E18
bool CdSoundCommandQueueEmpty(void) {
    if (DAT_06064250[0] != 0 || DAT_06064414 != DAT_0606423A) {
        return 0;
    } else {
        return 1;
    }
}

// original name: sd_xapause_chk
s32 func_06012E4C(void) {
    if ((DAT_060642E8 != 0) && (func_06012DFC() == 0)) {
        DAT_060642E8 = 0;
    }
    if ((DAT_060644C2 != 0) && (DAT_0606423C == 0)) {
        DAT_060644C2 = 0;
    }
    if ((DAT_060642E8 == 0) && (DAT_060644C2 == 0)) {
        if (DAT_06064474 != 0) {
            if (func_06012DD0() == 0) {
                DAT_06064474 = 0;
            }
            if (DAT_06064400 != 0) {
                DAT_06064474 = 0;
            }
        }
        if ((DAT_06064378 != 0) && (func_06012DD0() != 0) &&
            (DAT_06062388 == 0) && (DAT_06064350 == 0)) {
            DAT_06064378 = 0;
        }
        if (DAT_06064474 == 0 && (DAT_06064378 == 0 || DAT_0606442C != 0)) {
            return 1;
        }
    }
    return 0;
}

void func_06012F30(void) {
    while ((DAT_06063BE0 != 0 && DAT_06063BE0 < 5) ||
           (DAT_06064214 != 0 && DAT_06064214 < 5)) {
        func_06010400();
        SCL_DisplayFrame();
    }
}

// original name: sd_xa_wait2
s32 func_06012F7C(void) {
    if ((DAT_06063BE0 != 0) && (DAT_06063BE0 < 5)) {
        return 0;
    }
    if ((DAT_06064214 != 0) && (DAT_06064214 < 5)) {
        return 0;
    }
    return 1;
}

const s32 DAT_06012FB0 = 0;

void func_06012FB4(void) {
    s32 i;

    DAT_06063BE0 = DAT_06064214 = 0;
    DAT_0606238C = 0;
    DAT_06063BD4 = 0;
    DAT_06063BF8 = 0;
    DAT_060641FC = 0;
    DAT_06063BE4 = 0;
    DAT_06063E70 = DAT_06062250 = 0;
    DAT_060623A0 = DAT_060641E4 = 0;
    DAT_06063C1C = 0;
    DAT_06063E68 = DAT_06012FB0;
    DAT_06063EA4 = DAT_06012FB0;
    DAT_060641E8 = DAT_06012FB0;
    DAT_06063C00 = DAT_06012FB0;
    DAT_060641D8 = 0;
    DAT_06063EB4 = DAT_06062248 = DAT_06063EA0 = 0;
    DAT_06063BFC = 0;
    DAT_06063EC0 = 0;
    DAT_06062390[0] = -1;
    DAT_06062390[1] = -1;
    DAT_06062390[2] = -1;
    DAT_06062390[3] = -1;
    DAT_060641DC = 0;
    DAT_06064210 = 0;
    DAT_06062374 = 0;
    DAT_06063E64 = 0;
    DAT_060644E0 = 1;
    DAT_06064300 = 0;
    DAT_06064234 = DAT_0606437C = 0;
    DAT_0606438C = 0;
    DAT_0606435C = DAT_060643C0 = 0;
    DAT_06064344 = 0;
    DAT_060642E4 = 0;
    DAT_060643CC = 0;
    DAT_060642EC = 0;
    DAT_06064354 = 0;
    DAT_060644AC = 0;
    DAT_0606432C = 0;
    DAT_060642D0 = 0;
    DAT_06064470 = -1;
    DAT_060644A4 = 0;
    DAT_06064358 = DAT_060644E4 = 0;
    DAT_0606423C = 0;
    DAT_06064430 = 0;
    DAT_06062258 = 0;
    for (i = 0; i < 8; i++) {
        DAT_060643E0[i] = 0;
        DAT_060644B8[i] = 0;
    }
    DAT_060644C3 = 0;
    for (i = 0; i < 0x80; i++) {
        *((s16*)&DAT_06063ED0[i][0]) = 0;
        DAT_06063ED0[i][2] = 0;
        DAT_06063ED0[i][3] = 0;
        DAT_06063ED0[i][4] = 0;
    }
    DAT_0606423A = 0;
    DAT_06064414 = 0;
    DAT_06064310[0] = 0x40;
    DAT_06064310[1] = 0x40;
    DAT_06064310[2] = 0x40;
    DAT_06064310[3] = 0x40;
    DAT_06064310[4] = 0x40;
    DAT_06064310[5] = 0x40;
    DAT_06064310[6] = 0x40;
    DAT_06064310[7] = 0x40;
    DAT_06064310[8] = 0x40;
    DAT_0606436E = 0x40;
    DAT_060644E6 = 0x40;
    DAT_060643C7 = 0;
    DAT_0606440C = 0;
    DAT_06064328 = DAT_06064418 = DAT_060642F0 = 0;
    DAT_06064380 = DAT_060643C6 = DAT_06064379 = 0;
    DAT_060644C4 = 0;
    DAT_06064250[0] = 0;
    DAT_060643A0 = 1;
    DAT_06064324 = 0xF00000E0;
    DAT_06064400 = 0;
    DAT_06064330 = 0;
    DAT_06064474 = 0;
    DAT_06064378 = 0;
    DAT_060642E8 = 0;
    DAT_060644C2 = 0;
    DAT_06064420 = 0;
    DAT_060644A8 = 0;
    DAT_060642D8 = 0;
    DAT_06064401 = 0;
    DAT_060644C1 = 0;
    DAT_060644DC = 0;
    DAT_0606442C = 0;
    DAT_0606440D = 0;
    DAT_060644C5 = 1;
    DAT_060644A0 = 0;
    DAT_06064398 = 0;
    DAT_06064388 = 0;
    DAT_0606446C = 0x64;
    DAT_0606440E = 0;
}

// original name: sd_alloff_chk
bool func_06013320(void) {
    if (DAT_060644C0 == 2) {
        return 1;
    }
    return 0;
}

// original name: sd_reset2
void func_0601333C(void) {
    s32 temp_r0;
    u32 msk;

    msk = get_imask();
    set_imask(15);

    temp_r0 = func_06014C54();
    if (temp_r0 == -1) {
        DAT_06064218 = 0;
    } else if (temp_r0 == 0) {
        DAT_06064218 = 2;
    }

    set_imask(msk);
}

void MuteCd(void) {
    DAT_060644C1 = 1;
    DAT_060644DC = 2;
}

void UnMuteCd(void) {
    DAT_060644C1 = 0;
    DAT_060644DC = 2;
}

// _conve
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60133CC, func_060133CC);

// _convertDVI_STE
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6013538, func_06013538);

void func_060139C4(void);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60139C4, func_060139C4);

void func_06014424(void) {
    PER_SMPC_NO_IREG(PER_SM_SSHOFF);
    SYS_SETSINT(0x94, func_060139C4);
    PER_PokeByte(PER_REG_SF, PER_B_SF);
    PER_SMPC_GO_CMD(PER_SM_SSHON);
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
    DAT_06063C30[arg4].unk14 = 1;
    DAT_06063C30[arg4].unk18 = savedArg3;
    DAT_06063C30[arg4].unk4 = 0;
    DAT_06063C30[arg4].unk0 = 1;
}

void func_0601454C(s32 arg0, s32 arg1, s32 arg2, s16 arg3, s32 arg4, s32 arg5) {
    while (UNCACHED_SOUND_REQUESTS[arg5].unk0 != 0) {
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

void func_060145F8(s32 arg0, s32 arg1, s32 arg2, s16 arg3, s32 arg4, s32 arg5) {
    while (UNCACHED_SOUND_REQUESTS[arg5].unk0 != 0) {
    }

    DAT_06063C30[arg5].unk8 = arg0;
    DAT_06063C30[arg5].unkC = arg1;
    DAT_06063C30[arg5].unk10 = arg2;
    DAT_06063C30[arg5].unk14 = 0;
    DAT_06063C30[arg5].unk24 = arg3;
    DAT_06063C30[arg5].unk1C = arg4;
    DAT_06063C30[arg5].unk4 = 1;
    DAT_06063C30[arg5].unk0 = 1;
}

void func_06014658(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    while (UNCACHED_SOUND_REQUESTS[arg3].unk0 != 0) {
    }

    DAT_06063C30[arg3].unk8 = arg0;
    DAT_06063C30[arg3].unkC = arg1;
    DAT_06063C30[arg3].unk10 = arg2;
    DAT_06063C30[arg3].unk14 = 0;
    DAT_06063C30[arg3].unk4 = 1;
    DAT_06063C30[arg3].unk0 = 1;
}

void func_060146A4(s32 arg0, s32 arg1, s32 arg2, s16 arg3, s16 arg4, s32 arg5,
                   s32 arg6, s32 arg7, s32 arg8) {
    while (UNCACHED_SOUND_REQUESTS[arg8].unk0 != 0) {
    }

    DAT_06063C30[arg8].unk8 = arg0;
    DAT_06063C30[arg8].unkC = arg1;
    DAT_06063C30[arg8].unk10 = arg2;
    DAT_06063C30[arg8].unk24 = arg3;
    DAT_06063C30[arg8].unk26 = arg4;
    DAT_06063C30[arg8].unk1C = arg5;
    DAT_06063C30[arg8].unk20 = arg6;
    arg3 = 1;
    DAT_06063C30[arg8].unk14 = 1;
    DAT_06063C30[arg8].unk18 = arg7;
    DAT_06063C30[arg8].unk4 = 2;
    DAT_06063C30[arg8].unk0 = 1;
}

void func_06014724(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 savedArg3;

    savedArg3 = arg3;

    while (UNCACHED_SOUND_REQUESTS[arg4].unk0 != 0) {
    }

    DAT_06063C30[arg4].unk8 = arg0;
    DAT_06063C30[arg4].unkC = arg1;
    DAT_06063C30[arg4].unk10 = arg2;
    arg3 = 1;
    DAT_06063C30[arg4].unk14 = 1;
    DAT_06063C30[arg4].unk18 = savedArg3;
    DAT_06063C30[arg4].unk4 = 2;
    DAT_06063C30[arg4].unk0 = 1;
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601476C, func_0601476C);

// _RestartBgmStream
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6014B80, func_06014B80);

s32 func_06014C20(void) {
    if (DAT_06062280 == NULL) {
        return -1;
    }
    DAT_060623B0[1] |= 2;
    DAT_0606227C = 0;
    return 0;
}

// original name: OpenVoxFile
s32 func_06014C54(void) {
    if (DAT_06062280 != NULL) {
        func_06011F40(6);
        PcmClose(DAT_06062280, 1);
        DAT_06062280 = NULL;
    }

    DAT_06062280 = ((s32(*)(s32, s32))PcmOpen)(0xF00000F0, 1);
    if (DAT_06062280 == NULL) {
        return -1;
    }

    DAT_060623B0[1] &= ~2;
    return 0;
}

s32 func_06014CB8(s32 arg0) {
    if (DAT_06062290[arg0] != 0) {
        func_06011F40(7);
        PcmClose(DAT_06062290[arg0], 0);
        DAT_06062290[arg0] = 0;
    }

    DAT_06062290[arg0] = ((s32(*)(s32, s32))PcmOpen)(arg0 + 0xE0000000, 0);
    if (DAT_06062290[arg0] == 0)
        return -1;
    DAT_060623B0[0] &= ~2;
    GFS_SetGmode(DAT_06062290[arg0], GFS_GMODE_ERASE);
    return 0;
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6014D44, func_06014D44);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6014F3C, func_06014F3C);

// _BgmCdLoadWithLoop
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6015140, func_06015140);

// _VoxCdLoad
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60155CC, func_060155CC);

void func_060157CC(void);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60157CC, func_060157CC);

void func_06015E68(void);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6015E68, func_06015E68);

void func_06016614(void) {
    if (DAT_060641D4 == -1) {
        func_060157CC();
    } else {
        func_06015E68();
    }
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6016644, func_06016644);

s32 PcmOpen(s32 code) {
    u8 name[0x10];
    code2name(code, name);
    return func_06017F5C(name);
}

s32 PcmLseek(GfsHn gfs, Sint32 offset) {
    s32 sector = GFS_ByteToSct(gfs, offset + 1);
    return GFS_Seek(gfs, sector - 1, GFS_SEEK_SET);
}

s32 func_06016B9C(GfsHn gfs, s32 arg1, s32 arg2) {
    return func_06017FA4(arg1, arg2, gfs);
}

void func_06016BBC(GfsHn gfs, s32 arg1, s32 arg2) {
    func_06017FA4(arg1, arg2, gfs);
}

void PcmClose_noInline(GfsHn gfs, s32 arg1) {
    GFS_Close(gfs);
    DAT_060623B0[arg1] = 0;
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

    if ((DAT_06064214 == 5) && (DAT_0606423C != 0)) {
        if (DAT_06064384 != 0) {
            var_r2 = DAT_06064498;
            var_r0 = DAT_06063EA8 / DAT_06064384;
            if (var_r0 < 0x10) {
                var_r0 = 0x10;
            }
            if (var_r2 < var_r0) {
                var_r2 = 0;
            } else {
                var_r2 -= var_r0;
            }
            DAT_06064498 = var_r2;
            if (DAT_06064498 == 0) {
                DAT_0606423C = 0;
                if (DAT_060644E4 == 0) {
                    func_060120A0();
                }
            }
        } else if (DAT_06064350 != 0) {
            if ((DAT_06064488 != 0) && (var_r2 = 0, (DAT_06064498 == 0))) {
                DAT_06064488 -= 1;
            } else {
                var_r2 = DAT_06064498;
            }
            var_r0_2 = DAT_06063EA8 / DAT_06064350;
            if (var_r0_2 < 0x10) {
                var_r0_2 = 0x10;
            }
            var_r2 += var_r0_2;
            if (var_r2 > DAT_06063EA8) {
                var_r2 = DAT_06063EA8;
            }
            DAT_06064498 = var_r2;
            if (DAT_06064498 == DAT_06063EA8) {
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
            if (var_r0 < 0x10) {
                var_r0 = 0x10;
            }
            if (var_r2 < var_r0) {
                var_r2 = 0;
            } else {
                var_r2 -= var_r0;
            }
            DAT_0606448C = var_r2;
            if (DAT_0606448C == 0) {
                DAT_06064430 = 0;
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
    num &= 0xF;

    if (num < 10) {
        num += '0';
    } else {
        num -= 10;
        num += 'A';
    }
    return num;
}

s32 func_06016FB8(void) {
    if (DAT_06064338 != NULL) {
        func_06011F40(5);
        PcmClose(DAT_06064338, 2);
        DAT_06064338 = NULL;
    }

    DAT_06064338 = ((s32(*)(s32, s32))PcmOpen)(0xF00000F5, 2);
    if (DAT_06064338 == NULL)
        return -1;

    DAT_060623B0[2] &= ~2;
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

// original name: voxvdSpuTransOnmemNoloop
void func_06017508(void) {
    SndPcmPlayAdr sp0;
    s32 temp_r6;

    switch (DAT_06064300 & 0xF) {
    case 2:
        DAT_06044108 = 0;
        DAT_0604410C = 0;
        if (DAT_06064238 != 0) {
            if (DAT_06064360 > 0x800) {
                memcpy(DAT_06064480 + DAT_0606434C, DAT_060644E8, 0x800);
                DAT_060644E8 += 0x800;
                DAT_06064408 = (DAT_06064408 + 0x800) & 0x1FFF;
                DAT_06064360 -= 0x800;
                DAT_0606434C = 0x800;
                DAT_06064238 = 0;
                DAT_06064300 = 4;
            } else {
                memcpy(DAT_06064480 + DAT_0606434C, DAT_060644E8, DAT_06064360);
                DAT_060644E8 += DAT_06064360;
                temp_r6 = 0x800 - DAT_06064360;
                if (temp_r6 != 0) {
                    memset(
                        DAT_06064480 + DAT_0606434C + DAT_06064360, 0, temp_r6);
                }
                DAT_06064408 = (DAT_06064408 + DAT_06064360) & 0x1FFF;
                DAT_0606434C = 0x800;
                DAT_06064360 = 0;
                DAT_06064238 = 0;
                DAT_06064300 = 4;
            }
        } else {
            if (DAT_06064360 != 0) {
                if (DAT_06064360 > 0x800) {
                    memcpy(DAT_06064480 + DAT_0606434C, DAT_060644E8, 0x800);
                    DAT_060644E8 += 0x800;
                    DAT_06064360 -= 0x800;
                    DAT_06064408 = (DAT_06064408 + 0x800) & 0x1FFF;
                    DAT_0606434C = (DAT_0606434C + 0x800) & 0x1FFF;
                    DAT_06064300 = 4;
                } else {
                    memcpy(DAT_06064480 + DAT_0606434C, DAT_060644E8,
                           DAT_06064360);
                    DAT_060644E8 += DAT_06064360;
                    temp_r6 = 0x800 - DAT_06064360;
                    if (temp_r6 != 0) {
                        memset(DAT_06064480 + DAT_0606434C + DAT_06064360, 0,
                               temp_r6);
                    }
                    DAT_06064408 = (DAT_06064408 + DAT_06064360) & 0x1FFF;
                    DAT_06064360 = 0;
                    DAT_0606434C = (DAT_0606434C + 0x800) & 0x1FFF;
                    DAT_06064300 = 4;
                }
            } else {
                DAT_06064300 = 7;
            }
        }

        if ((DAT_06064408 & 0xFFF) == 0) {
            DAT_06064490[DAT_06064484] = DAT_06064408 & 0xFFF;
            DAT_06064484 = (DAT_06064484 + 1) & 1;
        }
        /* fallthrough */
    case 4:
        DAT_06064379 = 2;
        SND_PRM_MODE(DAT_06064368) = SND_MD_8;
        SND_PRM_SADR(DAT_06064368) = 0x7600;
        SND_PRM_SIZE(DAT_06064368) = 0x2000;
        SND_PRM_NUM(DAT_06064460) = 5;
        SND_PRM_LEV(DAT_06064460) = 7;
        SND_PRM_PAN(DAT_06064460) = 0;
        SND_PRM_PICH(DAT_06064460) = DAT_0606447C;
        SND_L_EFCT_IN(DAT_06064460) = 0;
        SND_L_EFCT_LEV(DAT_06064460) = DAT_060642D0;
        SND_R_EFCT_IN(DAT_06064460) = 0;
        SND_R_EFCT_LEV(DAT_06064460) = DAT_060642D0;
        SND_PRM_TL(DAT_06064460) = -1;
        SND_StartPcmTL(&DAT_06064368, &DAT_06064460);
        DAT_06064300++;
        if (DAT_06064360 == 0) {
            DAT_06064300++;
        }
        break;

    case 5:
        SND_GetPcmPlayAdr(&sp0, 5);
        if (sp0.radr == (DAT_0606434C >> 0xC) && (DAT_0606434C & 0xFFF) == 0) {
            break;
        }
        if (DAT_06064360 != 0) {
            if (DAT_06064360 > 0x800) {
                memcpy(DAT_06064480 + DAT_0606434C, DAT_060644E8, 0x800);
                DAT_060644E8 += 0x800;
                DAT_06064360 -= 0x800;
                DAT_06064408 = (DAT_06064408 + 0x800) & 0x1FFF;
                DAT_0606434C = (DAT_0606434C + 0x800) & 0x1FFF;
            } else {
                memcpy(DAT_06064480 + DAT_0606434C, DAT_060644E8, DAT_06064360);
                DAT_060644E8 += DAT_06064360;
                temp_r6 = 0x800 - DAT_06064360;
                if (temp_r6 != 0) {
                    memset(
                        DAT_06064480 + DAT_0606434C + DAT_06064360, 0, temp_r6);
                }
                DAT_06064408 += DAT_06064360;
                DAT_06064360 = 0;
                DAT_0606434C = (DAT_0606434C + 0x800) & 0x1FFF;
                DAT_06064300++;
            }
        }
        if ((DAT_06064408 & 0xFFF) == 0) {
            DAT_06064490[DAT_06064484] = DAT_06064408 & 0xFFF;
            DAT_06064484 = (DAT_06064484 + 1) & 1;
        }
        break;

    case 6:
        SND_GetPcmPlayAdr(&sp0, 5);
        if (DAT_0604410C == 0) {
            if (sp0.radr != (DAT_0606434C >> 0xC)) {
                memset(DAT_06064480 + DAT_0606434C, 0, 0x800);
                DAT_06044108 = (DAT_0606434C + 0x800) & 0x1FFF;
                DAT_0604410C = 1;
            } else if (DAT_0606434C & 0x800) {
                memset(DAT_06064480 + DAT_0606434C, 0, 0x800);
                DAT_0606434C = (DAT_0606434C + 0x800) & 0x1FFF;
            }
        }
        if (DAT_0604410C == 1) {
            if (sp0.radr == (DAT_0606434C >> 0xC)) {
                DAT_06064300++;
            } else if (DAT_06044108 & 0xFFF) {
                memset(DAT_06064480 + DAT_06044108, 0, 0x800);
                DAT_06044108 = (DAT_06044108 + 0x800) & 0x1FFF;
            }
        }
        break;

    case 7:
        SND_StopPcm2(5);
        break;
    }
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6017988, func_06017988);

// original name: RestartvoxvdStream
s32 func_06017F28(void) {
    if (DAT_06064338 == NULL) {
        return -1;
    } else {
        DAT_060623B0[2] |= 2;
        DAT_06064238 = 0;
        return 0;
    }
}

s32 func_06017F5C(char* fname) {
    s32 handle;

    GFS_SetDir(&DAT_06063E90);
    handle = GFS_Open(GFS_NameToId(fname));
    GFS_NwStop(handle);
    return handle;
}

// original name: dat_read
s32 func_06017FA4(void* buf, Sint32 nbyte, GfsHn gfs) {
    s32 sector;

    sector = GFS_ByteToSct(gfs, nbyte);
    if (GFS_NwFread(gfs, sector, buf, nbyte) != 0) {
        return -1;
    }
    return sector * 0x800;
}

void func_06017FF4(s32 arg0, s32 arg1) {
    arg1 = (0x7FFF - arg1) >> 7;
    if (arg0 == 1) {
        arg1 = (arg1 * 0x50) / 0x80;
    }
    func_06018034(arg1);
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018034, func_06018034);

u16 func_060180E0(u32 arg0, s32 arg1) {
    u32 uVar3;
    u32 uVar4;
    s32 scale[13] = {0x0,    0xF39,  0x1F5A, 0x3070, 0x428A, 0x55B8, 0x6A0A,
                     0x7F91, 0x9660, 0xAE8A, 0xC824, 0xE343, 0x10000};
    s32 shift[13] = {5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7};

    uVar4 = arg0 + ((scale[arg1 % 12] * arg0) >> 0x10);
    uVar3 = arg1 / 12;
    if (uVar3 > 5) {
        uVar4 <<= shift[uVar3];
    } else if (uVar3 < 5) {
        uVar4 >>= shift[uVar3];
    }

    return func_06018260(uVar4);
}

const double DAT_060181D8 = 0x100000000;
const double DAT_060181E0 = 88200;
const double DAT_060181E8 = 86.1328125;
const double DAT_060181F0 = 0.5;
const double DAT_060181F8 = 0x400;
const double DAT_06018200 = 44100;
const double DAT_06018208 = 43.06640625;
const double DAT_06018210 = 22050;
const double DAT_06018218 = 21.533203125;
const double DAT_06018220 = 11025;
const double DAT_06018228 = 10.7666015625;
const double DAT_06018230 = 5512;
const double DAT_06018238 = 5.3828125;
const double DAT_06018240 = 2756;
const double DAT_06018248 = 2.69140625;
const double DAT_06018250 = 1378;
const double DAT_06018258 = 1.345703125;

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018260, func_06018260);

/*u16 func_06018260(u32 arg0) {
    double temp_ret;
    double temp_ret_4;

    if (arg0 >= 176400) {
        return 0x1000;
    }
    if (arg0 >= 88200) {
        temp_ret = arg0;
        if (arg0 < 0) {
            temp_ret += DAT_060181D8;
        }
        temp_ret_4 = (temp_ret - DAT_060181E0) / DAT_060181E8 + DAT_060181F0;
        if (temp_ret_4 < DAT_060181F8) {
            return (u16)temp_ret_4 + 0x800;
        }
        return 0x1000;
    }
    if (arg0 >= 44100) {
        temp_ret = arg0;
        if (arg0 < 0) {
            temp_ret += DAT_060181D8;
        }
        temp_ret_4 = (temp_ret - DAT_06018200) / DAT_06018208 + DAT_060181F0;
        if (temp_ret_4 < DAT_060181F8) {
            return (u16)temp_ret_4;
        }
        return 0x800;
    }
    if (arg0 >= 22050) {
        temp_ret = arg0;
        if (arg0 < 0) {
            temp_ret += DAT_060181D8;
        }
        temp_ret_4 = (temp_ret - DAT_06018210) / DAT_06018218 + DAT_060181F0;
        if (temp_ret_4 < DAT_060181F8) {
            return (u16)temp_ret_4 + 0x7800;
        }
        return 0;
    }
    if (arg0 >= 11025) {
        temp_ret = arg0;
        if (arg0 < 0) {
            temp_ret += DAT_060181D8;
        }
        temp_ret_4 = (temp_ret - DAT_06018220) / DAT_06018228 + DAT_060181F0;
        if (temp_ret_4 < DAT_060181F8) {
            return (u16)temp_ret_4 + 0x7000;
        }
        return 0x7800;
    }
    if (arg0 >= 5512) {
        temp_ret = arg0;
        if (arg0 < 0) {
            temp_ret += DAT_060181D8;
        }
        temp_ret_4 = (temp_ret - DAT_06018230) / DAT_06018238 + DAT_060181F0;
        if (temp_ret_4 < DAT_060181F8) {
            return (u16)temp_ret_4 + 0x6800;
        }
        return 0x7000;
    }
    if (arg0 >= 2756) {
        temp_ret = arg0;
        if (arg0 < 0) {
            temp_ret += DAT_060181D8;
        }
        temp_ret_4 = (temp_ret - DAT_06018240) / DAT_06018248 + DAT_060181F0;
        if (temp_ret_4 < DAT_060181F8) {
            return (u16)temp_ret_4 + 0x6000;
        }
        return 0x6800;
    }
    if (arg0 >= 1378) {
        temp_ret = arg0;
        if (arg0 < 0) {
            temp_ret += DAT_060181D8;
        }
        temp_ret_4 = (temp_ret - DAT_06018250) / DAT_06018258 + DAT_060181F0;
        if (temp_ret_4 < DAT_060181F8) {
            return (u16)temp_ret_4 + 0x5800;
        }
        return 0x6000;
    }
    return 0x5800;
}
*/
