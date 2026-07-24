// SPDX-License-Identifier: AGPL-3.0-or-later
#include "zero.h"
#include "inc_asm.h"
#include "sattypes.h"

void func_06011F40(s32 param);

void func_06012030(void) {
    func_06011F40(7);
    D_8013B61C = 0;
}

// _KeyOffVox
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6012054, func_06012054);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60120A0, func_060120A0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60120D8, func_060120D8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6012108, func_06012108);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6012154, func_06012154);

// _BgmFadeOut
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6012190, func_06012190);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60121F0, func_060121F0);

// _VoxFadeOutStop
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6012260, func_06012260);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6012290, func_06012290);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60122C0, func_060122C0);

// _BgmPauseFadeIn
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6012358, func_06012358);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60123D4, func_060123D4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6012428, func_06012428);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6012474, func_06012474);

// _BgmPauseOff
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6012554, func_06012554);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60125EC, func_060125EC);

// _BgmPauseKeyOff
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6012620, func_06012620);

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

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60126D4, func_060126D4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60127F0, func_060127F0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6012908, func_06012908);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6012954, func_06012954);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601298C, func_0601298C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60129BC, func_060129BC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6012C4C, func_06012C4C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6012CAC, func_06012CAC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6012D30, func_06012D30);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6012D88, func_06012D88);

// original name : xa_play_ck
bool func_80131F68_1(void) {
    bool ret;

    if (D_8013B61C == 9 || (D_8013B61C == 0 && g_PlayingXaBgmId == 0)) {
        ret = 0;
    } else {
        ret = 1;
    }
    return ret;
}

// original name : vox_play_ck
bool func_80131F68_2(void) {
    if (g_PlayingXaBgmId != 0) {
        return 1;
    }
    return 0;
}

extern s32 DAT_06064250;
extern u8 DAT_06064414;
extern u8 DAT_0606423a;

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
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6012E4C, func_06012E4C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6012F30, func_06012F30);

// _sd_xa_wait2
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6012F7C, func_06012F7C);
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
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6014424, func_06014424);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601449C, func_0601449C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6014504, func_06014504);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601454C, func_0601454C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60145B0, func_060145B0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60145F8, func_060145F8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601465C, func_0601465C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60146A4, func_060146A4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6014724, func_06014724);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601476C, func_0601476C);

// _RestartBgmStream
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6014B80, func_06014B80);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6014C20, func_06014C20);

// _OpenVoxFile
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6014C54, func_06014C54);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6014CB8, func_06014CB8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6014D44, func_06014D44);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6014F3C, func_06014F3C);

// _BgmCdLoadWithLoop
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6015140, func_06015140);

// _VoxCdLoad
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60155CC, func_060155CC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60157CC, func_060157CC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6015C70, func_06015C70);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6015E68, func_06015E68);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60164BC, func_060164BC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6016614, func_06016614);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60166A8, func_060166A8);

void code2name(u32 code, u8* name);
s32 func_06017F5C(u8*);

// _PcmOpen
void func_06016B44(s32 code) {
    u8 name[0x10];
    code2name(code, name);
    func_06017F5C(name);
}

int func_0601B8B4(int param_1, int param_2);
int func_0601B75C(int param_1, int param_2, int param_3);

// _PcmLseek
void _func_06016B6C(u32 param_1, int param_2) {
    int iVar1 = func_0601B8B4(param_1, param_2 + 1);
    func_0601B75C(param_1, iVar1 - 1, 0);
}

void func_06016B9C(s32 param_1, s32 param_2, s32 param_3) {
    func_06017FA4(param_2, param_3, param_1);
}

void func_06016BBC(s32 param_1, s32 param_2, s32 param_3) {
    func_06017FA4(param_2, param_3, param_1);
}

s32 d_060623B0[];

void func_0601B724();

// _PcmClose
void func_06016BDC(s32 param_0, int param_1) {
    func_0601B724();
    d_060623B0[param_1] = 0;
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6016C08, func_06016C08);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6016C60, func_06016C60);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6016D84, func_06016D84);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6016E84, func_06016E84);

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

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6016FB8, func_06016FB8);

// _StartvoxvdStream
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601701C, func_0601701C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60174D8, func_060174D8);

// _voxvdSpuTransOnmemNoloop
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6017508, func_06017508);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6017988, func_06017988);

// _RestartvoxvdStream
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6017F28, func_06017F28);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6017F5C, func_06017F5C);

// _dat_read
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6017FA4, func_06017FA4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6017FF4, func_06017FF4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018034, func_06018034);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60180E0, func_060180E0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018260, func_06018260);
