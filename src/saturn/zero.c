// SPDX-License-Identifier: AGPL-3.0-or-later
#include "zero.h"
#include "inc_asm.h"
#include "sattypes.h"
#include "lib/sys.h"

#define _SPR2_
#include "lib/spr/spr.h"

// func_06004080
void entrypoint(void) {
    func_06030df0();
    Scl_s_reg.tvmode &= ~0x8100;
    SclProcess = 1;
    func_060044D0();
    DAT_0605cea2 = 0;
    DAT_0605c658 = 1;
    do {
        func_060040d8();
    } while (true);
}

void func_0600456c();
void SetVblank();
void ReturnToGame();
void func_06004f50();
void func_06005310();
void func_0600652C();
void func_06007d54();
void func_06007e14();
void func_06008264();
void func_06008298();
void func_06008a70();
void func_06008d04(s32, s32);
void func_06009838();
void func_0600d8bc();
void MoviePRGClear();
void func_06010400();
void PlaySfx();
void func_06012fb4();
void SPR_WaitDrawEnd();
void SCL_Vdp2Init();
void SCL_DisplayFrame();
extern s32 DAT_06057f34;
extern u16 DAT_0605cea0;
extern u16 DAT_0605cea2;
extern s32 DAT_0605d7f0;
extern s32 DAT_0605d7f8;

void func_060040d8(void) {
    g_Timer++;
    func_06007d54();
    switch (DAT_0605cea2) {
    case 0:
        func_0600456c();
        DAT_0605d7f8 = 0;
        func_06004f50(0x20);
        DAT_0605cea0++;
        break;
    case 6:
        if (DAT_0605cea0 == 0) {
            func_06005328();
            DAT_0605cea0++;
            Scl_s_reg.tvmode |= 0x8000;
            SclProcess = 1;
        }
        func_060645E0();
        break;
    case 2:
        if (DAT_0605cea0 == 0) {
            func_06005328();
            DAT_0605cea0++;
        }
        func_06064688();
        func_06008a70();
        break;
    case 3:
        func_0606468c();
        break;
    case 7:
        func_06064614();
        func_06008a70();
        break;
    case 4:
        if (DAT_0605cea0 == 0) {
            func_06005328();
            DAT_0605cea0++;
        }
        func_06064674();
        break;
    case 8:
        if (DAT_0605cea0 == 0) {
            func_06005328();
            DAT_0605cea0++;
        }
        func_06064580();
        break;
    case 0x11:
        if (*((u32*)&DAT_0605cea0) == 0x11) {
            if (func_06005328() == 0) {
                DAT_0605cea0++;
            }
        } else {
            func_06009838();
            func_0606463c();
            func_06008a70();
        }
        break;
    case 5:
        if (DAT_0605cea0 == 0) {
            func_06008d04(0, 2);
            func_06005328();
            DAT_0605cea0++;
        }
        func_06064644();
        func_06008a70();
        break;
    case 0x20:
        func_06007e14();
        Scl_s_reg.dispenbl &= ~0x003F;
        SclProcess = 1;
        Scl_s_reg.tvmode &= ~0x8100;
        SclProcess = 1;
        InitializePads();
        SPR_WaitDrawEnd();
        ClearFrameBuffer(0x8000);
        SCL_DisplayFrame();
        ClearFrameBuffer(0x8000);
        SetVblank(1);
        DAT_06057f34 = 0;
        MoviePRGClear();
        func_06005328();
        DAT_06057f34 = func_06064690();
        if ((DAT_06057f34 == 2) && (DAT_0605d7f8 == 0)) {
            SYS_EXECDMP();
        }
        Scl_s_reg.tvmode &= ~0x8100;
        SclProcess = 1;
        SCL_DisplayFrame();
        SCL_Vdp2Init();
        func_06011ce4();
        ReturnToGame();
        func_06004f50(0x31);
        func_06007d54();
        break;
    case 0x31:
        DAT_0605d7f0 = 1;
        func_0600d8bc();
        break;
    }
    if (func_0600fb4c() != 0) {
        if (DAT_0605cea2 == 6) {
            SYS_EXECDMP();
        } else {
            PlaySfx(SET_UNK_0B);
            while (func_06013320() == 0) {
                func_06010400();
                SCL_DisplayFrame();
            }
            func_06012fb4();
            func_0600652C();
            func_0601333c();
            if (DAT_0605cea2 == 2) {
                SYS_EXECDMP();
            }
        }
        func_06008d04(0, 4);
        func_06004f50(0x30);
    }
    func_06010400();
    func_06007e14();
    func_06005310();
    SPR_WaitDrawEnd();
    func_06008264();
    SCL_DisplayFrame();
    func_06008298();
    ((void (*)(void))rand)();
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60044D0, func_060044D0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600456C, func_0600456C);

// _RESET_SYSTEM
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600460C, func_0600460C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60046E8, func_060046E8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60047E8, func_060047E8);
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/f_nonmat", f6004886, func_06004886);
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/f_nonmat", f6004932, func_06004932);
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/f_nonmat", f6004A46, func_06004A46);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6004B20, func_06004B20);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6004C14, func_06004C14);

s32 g_PadsRepeatTimer[];

// func_06004C44
void ResetPadsRepeat(void) {
    u8* ptr;
    s32 i;

    g_pads[0].repeat = PAD_NONE;
    ptr = g_PadsRepeatTimer;
    for (i = 0; i < 0x10; i++) {
        *ptr++ = 0x10;
    }
}

// _REPEAT_PAD
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6004C70, func_06004C70);

// func_06004CDC
void InitializePads(void) {
    g_pads[0].previous = g_pads[0].pressed = g_pads[0].tapped =
        g_pads[0].repeat = PAD_NONE;
}

// SET_VBLANK
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6004D00, func_06004D00);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6004D84, func_06004D84);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6004DE8, func_06004DE8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6004E50, func_06004E50);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6004E94, func_06004E94);

// RETURN_TO_GAME
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6004EF0, func_06004EF0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6004F50, func_06004F50);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6005208, func_06005208);

void func_06005310(void) { func_06006FA8(); }

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6005328, func_06005328);

void func_0600544C(void) {}
const char* logo = "LOGO.PRG";
const char* kcen = "KCEN.MAP";

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6005470, func_06005470);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6005508, func_06005508);

// _READ_LOAD_MODE
s32 func_060055A4(void) { return 0; }
const char* rload_map = "RLOAD.MAP";
const char* load_map = "LOAD.MAP";

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60055C8, func_060055C8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600583C, func_0600583C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60058D0, func_060058D0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6005944, func_06005944);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60059F4, func_060059F4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6005A90, func_06005A90);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6005E3C, func_06005E3C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600607C, func_0600607C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6006170, func_06006170);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60062F8, func_060062F8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6006470, func_06006470);

void func_0600652C(void) {
    func_0601B600();
    DAT_06038a44 = 0;
}

struct Unk0600654C {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unka;
    s32 unkc;
    s32 unk10;
};
s32 func_06006574(struct Unk0600654C*);
void func_0600654C(s32 param_1, s32 param_2) {
    struct Unk0600654C unk;
    unk.unk0 = param_1;
    unk.unk4 = param_2;
    unk.unk8 = -1;
    unk.unka = 0;
    func_06006574(&unk);
}

// _FileReadSetAdrEx
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6006574, func_06006574);

void func_060066F0(u32 param_1, u32 param_2, u32 param_3, u32 param_4) {
    struct Unk0600654C unk;
    unk.unk0 = param_1;
    unk.unk4 = param_2;
    unk.unk8 = -1;
    unk.unka = 0;
    unk.unkc = param_3;
    unk.unk10 = param_4;
    func_06006720(&unk, 3, 0);
}

// _FileReadNWStartEx
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6006720, func_06006720);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6006A7C, func_06006A7C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6006C00, func_06006C00);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6006E14, func_06006E14);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6006E4C, func_06006E4C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6006E9C, func_06006E9C);

s32 func_0602DCFC();

// _IsCdOpened
u32 func_06006ED4() { return (func_0602DCFC() >> 5) & 1; }

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6006EF8, func_06006EF8);

bool func_06006F50(void) { return 1; }

// func_06006F5C
bool CdSeek(void) { return 1; }

// func_06006F68
bool GetFileReadStat(void) { return 0; }

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6006F74, func_06006F74);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6006FA8, func_06006FA8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60071C8, func_060071C8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60076D0, func_060076D0);

// _CD_READ_OUT
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6007714, func_06007714);

struct Unk0600654C prg_info;
struct Unk0600654C chr_info;
void func_0601AE2C(s32);
void func_0600C0C4(s32);
void func_0600C298(s32);
s32 func_0601AE5C(s32, s32);

char* WEAPON0_PRG;
char* WEAPON0_CHR;
char* WEAPON1_PRG;
char* WEAPON1_CHR;
extern s32 d_060481c0;

void func_06007824(int param_1, int param_2) {
    if ((d_060481c0 == 0) || (0x3f < param_2)) {
        func_0601AE5C(param_1, param_2);
    } else {
        prg_info.unka = param_2 * 6;
        chr_info.unka = param_2 * 8;
        if (param_1 == 0) {
            prg_info.unk0 = &WEAPON0_PRG;
            prg_info.unk4 = 0x060D6000;
            chr_info.unk0 = &WEAPON0_CHR;
            chr_info.unk4 = VRAM_ADDR + 0x1D980;
        } else {
            prg_info.unk0 = &WEAPON1_PRG;
            prg_info.unk4 = 0x060D9000;
            chr_info.unk0 = &WEAPON1_CHR;
            chr_info.unk4 = VRAM_ADDR + 0x21980;
        }
        func_06006574(&prg_info);
        func_0601AE2C(param_1);
        func_06006574(&chr_info);
        func_0600C298(param_1);
        func_0600C0C4(param_1);
    }
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60078EC, func_060078EC);

// _InitVdp1
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6007968, func_06007968);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6007A34, func_06007A34);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6007B34, func_06007B34);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6007B8C, func_06007B8C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6007BE0, func_06007BE0);

// _SprSetGourTbl
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6007CA0, func_06007CA0);

u16 func_06007CE0(u16 arg0) { return arg0 * 0x10 + 0x400; }

void SPR_2ClrAllChar(void);

s16 d_0605BECA;
s16 d_0605AEA8;
s16 d_0605AEB0;
s16 d_0605BEC8;
s32 d_06038dbc;
s32 d_0605BEC4;
s32 d_060576AC;

void func_06007CF8() {
    SPR_2ClrAllChar();
    d_0605BECA = 0;
    d_0605AEA8 = 0;
    d_0605AEB0 = 0;
    d_0605BEC8 = 0x304;
    d_060576AC = 0;
    d_0605BEC4 = 0x00011180;
    d_06038dbc = 0;
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6007D54, func_06007D54);

void SPR_2CloseCommand();

s32 d_0605AEAC;
s32 d_06038c5c;
s32 d_06038c5c;
s32 d_0605BEBE;
u16 d_0605AEA0[4];
void func_06007e14(void) {
    SprSpCmd cmd;

    if (d_06038c5c) {
        d_06038c5c--;
        cmd.control = JUMP_ASSIGN | FUNC_TEXTURE;
        cmd.drawMode = ECDSPD_DISABLE;
        cmd.color = RGB16_COLOR(0, 0, 0);
        cmd.ax = cmd.dx = 0;
        cmd.bx = cmd.cx = d_0605BEBE;
        cmd.ay = cmd.by = 0;
        cmd.cy = cmd.dy = d_0605AEA0[1] - 1;
        SPR_2Cmd(0x1FF, &cmd);
        d_0605AEAC += 0x20;
    }

    SPR_2CloseCommand();
}
void SPR_SetEraseData(
    Uint16 eraseData, Uint16 leftX, Uint16 topY, Uint16 rightX, Uint16 botY);

void SPR_2FrameEraseData(Uint16);
void FUN_06007eb8(s16 param_1) {
    SPR_2FrameEraseData(param_1);
    SPR_SetEraseData(
        param_1, d_0605AEA0[0], d_0605AEA0[1], d_0605AEA0[2], d_0605AEA0[3]);
}

void SetVdp2BackgroundColor();

void FUN_06007f04(void) {
    SCL_Vdp2Init();
    SCL_SetDisplayMode(0, 1, 0);
    SPR_2FrameChgIntr(-1);
    SclPriBuffDirty.SclColOffset = 1;
    SclColOffset.ColorOffsetEnable = 0x6f;
    SCL_SetColOffset(0, 0x6f, 0xFF01, 0xFF01, 0xFF01);
    SetVdp2BackgroundColor();
}

// _SET_VDP2_VRAM
void func_06007F6C(void) {
    SclVramConfig cfg;
    SCL_InitVramConfigTb(&cfg);
    cfg.vramModeA = 0;
    cfg.vramModeB = 1;
    cfg.vramA0 = cfg.vramB0 = cfg.vramB1 = 0;
    SCL_SetVramConfig(&cfg);
    SCL_SetColRamMode(1);
    SCL_DisplayFrame();
    SCL_SetSpriteMode(5, 1, 0);

    SCL_SetPriority(4, 7);
    SCL_SetPriority(8, 4);
    SCL_SetPriority(0x20, 3);
    SCL_SetPriority(0x10, 2);
    SCL_SetPriority(0x100, 4);
    SCL_SetPriority(0x200, 1);
    SCL_SetPriority(0x400, 2);
    SCL_SetPriority(0x800, 3);
    SCL_SetPriority(0x1000, 4);
    SCL_SetPriority(0x2000, 6);
    SCL_SetPriority(0x4000, 7);
    SCL_SetPriority(0x8000, 0);

    SCL_SetColMixMode(6, 1);
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6008048, func_06008048);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60080EC, func_060080EC);

// SetVdp2BackgroundColor
void SetVdp2BackgroundColor(void) {
    s16 local_c[2];
    local_c[0] = 0;
    SCL_SetBack(SCL_VDP2_VRAM + 0x7FE20, 1, local_c);
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600815C, func_0600815C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600819C, func_0600819C);

// func_0600824C
void InitScuDma(void) {
    // sega library func
    DMA_ScuInit();
}

// _VDP1_TRANS
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6008264, func_06008264);

void func_06008298(void) {
    s32 i;
    for (i = 0; i < 8; i++) {
        func_06008588(i);
    }
}

// _INIT_TRANS
void func_060082C8(void) {
    func_060082E8();
    func_0600841C();
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60082E8, func_060082E8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600831C, func_0600831C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6008374, func_06008374);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600841C, func_0600841C);

s32 d_0605DB60[];
void func_06008464(void) {
    s32* puVar1;
    s32 i;

    puVar1 = d_0605DB60;

    for (i = 0; i < 0x20; i++) {
        puVar1[0] = 0;
        puVar1[1] = 0;
        puVar1 += 4;
    }
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6008488, func_06008488);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6008524, func_06008524);

// Handles transfer of background tile graphics
// func_06008588
void func_06008588(int param_1) {
    s32 cnt;
    struct Unk0605d6c0* puVar5;
    struct Unk0605CD90* puVar6;

    puVar5 = &DAT_0605d6c0[param_1 * 4];
    puVar6 = &DAT_0605CD90[param_1];
    if (puVar5->tileFlags == 0) {
        return;
    }
    if (puVar5->tileFlags & 1) {
        cnt = func_0600F96C(puVar6->unkc, (s32)SYS_buf_060485E0, puVar6->unk18);
        DmaScroll((s32*)SYS_buf_060485E0, puVar6->dst0, cnt);
    }
    if (puVar5->tileFlags & 2) {
        cnt =
            func_0600F96C(puVar6->unk10, (s32)SYS_buf_060485E0, puVar6->unk1c);
        DmaScroll((s32*)SYS_buf_060485E0, puVar6->dst4, cnt);
    }
    if (puVar5->tileFlags & 4) {
        if (DAT_060086d4 == 4) {
            func_060089F0(puVar6);
        } else {
            func_0600871C(puVar6, &DAT_0605c680, param_1);
        }
    }
    if (puVar5->tileFlags & 8) {
        DmaScroll(puVar5->src, puVar5->dest, puVar5->cnt);
    }
    if (puVar5->tileFlags & 0x10) {
        DmaScroll(puVar5->src, puVar5->dest, puVar5->cnt);
    }
    if (puVar5->tileFlags & 0x20) {
        DmaScroll(puVar5->src, puVar5->dest, puVar5->cnt);
    }
    if (puVar5->tileFlags & 0x40) {
        cnt = func_0600F96C(puVar6->unkc, DMA_SRC_ADDR, puVar6->unk18);
        DmaScroll(DMA_SRC_ADDR, puVar6->dst0, cnt);
    }
    if (puVar5->tileFlags & 0x80) {
        cnt = func_0600F96C(puVar6->unk10, DMA_SRC_ADDR, puVar6->unk1c);
        DmaScroll(DMA_SRC_ADDR, puVar6->dst4, cnt);
    }
    puVar5->tileFlags = 0;
    puVar5->cnt = 0;
    puVar5->dest = 0;
    puVar5->src = 0;
    return;
}

// _DMA_SCROLL
// func_060086E8
void DmaScroll(s32* src, s32* dest, u32 cnt) {
    s32 result;

    if (cnt != 0) {
        // sega DMA lib
        DMA_CpuMemCopy2(dest, src, cnt >> 1);
        do {
            result = DMA_CpuResult();
        } while (result == 2);
    }
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600871C, func_0600871C);

void func_060089F0(struct Unk0605CD90* param_1) {
    u16 sVar2;
    s16* psVar5;
    s16* psVar7;
    u16 i; // r2
    u16 j; // r1

    psVar7 = DAT_0605c120[3] + 1;
    sVar2 = param_1->unk24 * 0x1000;
    j = 0;
    psVar5 = param_1->unk8 + j * 0x20;
    for (j = 0; j < 32; j++) {
        for (i = 0; i < 32; i++) {
            *psVar5++ = *psVar7++ + sVar2;
        }
        psVar5 = 0x400 + param_1->unk8 + j * 0x20;

        for (i = 0; i < 10; i++) {
            *psVar5++ = *psVar7++ + sVar2;
        }
        psVar5 = param_1->unk8 + (j + 1) * 0x20;
    }
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6008A70, func_06008A70);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6008AB4, func_06008AB4);

// _SCROLL_DSP
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6008B20, func_06008B20);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6008C2C, func_06008C2C);
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/f_nonmat", f6008E3A, func_06008E3A);
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/f_nonmat", f6008FBE, func_06008FBE);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6008FF0, func_06008FF0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6009010, func_06009010);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6009058, func_06009058);

// _GAME_SCROLL_SET
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6009510, func_06009510);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6009570, func_06009570);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600971C, func_0600971C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60097B4, func_060097B4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6009838, func_06009838);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60098F0, func_060098F0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6009AE8, func_06009AE8);

// _UPDATE_BG
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6009CCC, func_06009CCC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6009D30, func_06009D30);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6009D60, func_06009D60);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6009DB0, func_06009DB0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6009F10, func_06009F10);

// _X_SCROLL_TRANS
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6009F84, func_06009F84);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600A030, func_0600A030);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600A088, func_0600A088);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600A240, func_0600A240);

// _SetCharTrans
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600A264, func_0600A264);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600A29C, func_0600A29C);

// func_0600A304
void SetSprGourTable(u16 arg0, SprGourTbl* gourTbl) {
    SPR_2SetGourTbl(arg0, gourTbl);
}

// _SetPlTransNonSeparateAura
void func_0600A31C(void) { DAT_0605D910[3] = 1; }

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600A330, func_0600A330);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600A350, func_0600A350);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600A490, func_0600A490);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600A5FC, func_0600A5FC);

u8 d_060578A0[];
void func_0600A62C(u8* param_1, u8* param_2, int param_3) {
    for (; param_3 > 0; param_3--) {
        *param_2++ = d_060578A0[*param_1++];
    }
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600A650, func_0600A650);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600A77C, func_0600A77C);

// _UpdateMirage
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600AA18, func_0600AA18);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600AB60, func_0600AB60);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600AC30, func_0600AC30);

// func_0600AD80
int GetEnemyPlayerCharaAddr(void) {
    return -(s32)&DAT_00252000 + (s32)&DAT_00258000;
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600AD98, func_0600AD98);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600AE30, func_0600AE30);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600AEE4, func_0600AEE4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600AFA8, func_0600AFA8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600B004, func_0600B004);

// _SetParts
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600B084, func_0600B084);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600B0B8, func_0600B0B8);

void func_0600B104(u16* param_1, int param_2, int param_3)

{
    s32 i;
    for (i = 0; i < param_3; i++) {
        *param_1 = *param_1 & 0xE0FF | (param_2 << 8);
        param_1 = *(u16**)(param_1 + 6);
    }
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600B12C, func_0600B12C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600B1A8, func_0600B1A8);

void func_0600B234(void) {
    func_0600AD98();
    func_0600B254();
}

// _ClearOdma
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600B254, func_0600B254);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600B344, func_0600B344);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600B428, func_0600B428);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600B4C4, func_0600B4C4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600B954, func_0600B954);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600BA24, func_0600BA24);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600BCE0, func_0600BCE0);

int func_0600BD4C(u8* param_1) { return SpGourTbl + param_1[2] * 2; }

// _Odma
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600BD68, func_0600BD68);

// _AllocGameSprite
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600BE18, func_0600BE18);

void func_0600BEA8();
void func_0600BF08();
void func_0600C18C();

void func_0600BE7C(void) {
    func_0600BEA8();
    func_0600BF08();
    func_0600C18C();
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600BEA8, func_0600BEA8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600BF08, func_0600BF08);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600BF38, func_0600BF38);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600BF8C, func_0600BF8C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600BFD8, func_0600BFD8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600C00C, func_0600C00C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600C0C4, func_0600C0C4);

void func_0600C0FC(void) { DAT_060645D0->unk0->unk8 = 0xc; }

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600C114, func_0600C114);

void func_0600C18C(void) {
    d_0605AEA8 = 0x10;
    return;
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600C1A0, func_0600C1A0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600C254, func_0600C254);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600C298, func_0600C298);

// _SetLocalPalData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600C2EC, func_0600C2EC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600C3A8, func_0600C3A8);

// _RequestItemTrans
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600C43C, func_0600C43C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600C518, func_0600C518);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600C628, func_0600C628);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600C6AC, func_0600C6AC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600C6E4, func_0600C6E4);

// _SetGameoverToFrameBuffer
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600C7E4, func_0600C7E4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600C818, func_0600C818);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600C880, func_0600C880);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600C99C, func_0600C99C);

// ClearFrameBuffer
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600CAB8, func_0600CAB8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600CB04, func_0600CB04);
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/f_nonmat", f600CB26, func_0600CB26);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600CB74, func_0600CB74);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600CBCC, func_0600CBCC);

// _ASYS_RESET_DIS
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600CC14, func_0600CC14);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600CC5C, func_0600CC5C);

// _ABup_CheckRam
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600CD70, func_0600CD70);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600CE1C, func_0600CE1C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600CED0, func_0600CED0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600D028, func_0600D028);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600D0DC, func_0600D0DC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600D1A0, func_0600D1A0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600D264, func_0600D264);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600D370, func_0600D370);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600D47C, func_0600D47C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600D4C4, func_0600D4C4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600D508, func_0600D508);

// _ABup_ChechsumSet
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600D6C0, func_0600D6C0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600D6EC, func_0600D6EC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600D8BC, func_0600D8BC);

// original name: MOVIE_PRG_CLEAR
void MoviePRGClear(void) { memset(0x06066000, 0, 0x9A000); }

void func_0600DAB4(void) { func_0600DACC(); }

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600DACC, func_0600DACC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600DB38, func_0600DB38);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600DCA8, func_0600DCA8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600DCF0, func_0600DCF0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600DD38, func_0600DD38);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600DD84, func_0600DD84);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600DDD4, func_0600DDD4);

bool func_0600DE20(void) { return 0; }

bool func_0600DE2C(void) { return 1; }

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600DE38, func_0600DE38);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600DFC0, func_0600DFC0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600E01C, func_0600E01C);

void func_0600E050(struct Unk0600E050* param_1, short param_2, short param_3) {
    param_1->unkc = param_2 + param_1->unkc;
    param_1->unke = param_3 + param_1->unke;
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600E070, func_0600E070);

void func_0600E0A4(struct Unk0600E050* param_1, short param_2, short param_3) {
    param_1->unk4 = param_2 + param_1->unk4;
    param_1->unk8 = param_3 + param_1->unk8;
}

void func_0600E0C4() {}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600E0D0, func_0600E0D0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600E164, func_0600E164);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600E240, func_0600E240);

// _RotTransCurMatrix_ps
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600E2D4, func_0600E2D4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600E390, func_0600E390);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600E400, func_0600E400);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600E450, func_0600E450);

// _CheckClipScreenArea
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600E4E0, func_0600E4E0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600E51C, func_0600E51C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600E5A4, func_0600E5A4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600E61C, func_0600E61C);

const short ratan_tbl[] = {
    0x000, 0x000, 0x001, 0x001, 0x002, 0x003, 0x003, 0x004, 0x005, 0x005, 0x006,
    0x007, 0x007, 0x008, 0x008, 0x009, 0x00A, 0x00A, 0x00B, 0x00C, 0x00C, 0x00D,
    0x00E, 0x00E, 0x00F, 0x00F, 0x010, 0x011, 0x011, 0x012, 0x013, 0x013, 0x014,
    0x015, 0x015, 0x016, 0x016, 0x017, 0x018, 0x018, 0x019, 0x01A, 0x01A, 0x01B,
    0x01B, 0x01C, 0x01D, 0x01D, 0x01E, 0x01F, 0x01F, 0x020, 0x021, 0x021, 0x022,
    0x022, 0x023, 0x024, 0x024, 0x025, 0x026, 0x026, 0x027, 0x028, 0x028, 0x029,
    0x029, 0x02A, 0x02B, 0x02B, 0x02C, 0x02D, 0x02D, 0x02E, 0x02F, 0x02F, 0x030,
    0x030, 0x031, 0x032, 0x032, 0x033, 0x034, 0x034, 0x035, 0x035, 0x036, 0x037,
    0x037, 0x038, 0x039, 0x039, 0x03A, 0x03B, 0x03B, 0x03C, 0x03C, 0x03D, 0x03E,
    0x03E, 0x03F, 0x040, 0x040, 0x041, 0x041, 0x042, 0x043, 0x043, 0x044, 0x045,
    0x045, 0x046, 0x047, 0x047, 0x048, 0x048, 0x049, 0x04A, 0x04A, 0x04B, 0x04C,
    0x04C, 0x04D, 0x04D, 0x04E, 0x04F, 0x04F, 0x050, 0x051, 0x051, 0x052, 0x052,
    0x053, 0x054, 0x054, 0x055, 0x056, 0x056, 0x057, 0x057, 0x058, 0x059, 0x059,
    0x05A, 0x05B, 0x05B, 0x05C, 0x05C, 0x05D, 0x05E, 0x05E, 0x05F, 0x060, 0x060,
    0x061, 0x061, 0x062, 0x063, 0x063, 0x064, 0x065, 0x065, 0x066, 0x066, 0x067,
    0x068, 0x068, 0x069, 0x06A, 0x06A, 0x06B, 0x06B, 0x06C, 0x06D, 0x06D, 0x06E,
    0x06E, 0x06F, 0x070, 0x070, 0x071, 0x072, 0x072, 0x073, 0x073, 0x074, 0x075,
    0x075, 0x076, 0x076, 0x077, 0x078, 0x078, 0x079, 0x07A, 0x07A, 0x07B, 0x07B,
    0x07C, 0x07D, 0x07D, 0x07E, 0x07E, 0x07F, 0x080, 0x080, 0x081, 0x082, 0x082,
    0x083, 0x083, 0x084, 0x085, 0x085, 0x086, 0x086, 0x087, 0x088, 0x088, 0x089,
    0x089, 0x08A, 0x08B, 0x08B, 0x08C, 0x08C, 0x08D, 0x08E, 0x08E, 0x08F, 0x090,
    0x090, 0x091, 0x091, 0x092, 0x093, 0x093, 0x094, 0x094, 0x095, 0x096, 0x096,
    0x097, 0x097, 0x098, 0x099, 0x099, 0x09A, 0x09A, 0x09B, 0x09C, 0x09C, 0x09D,
    0x09D, 0x09E, 0x09F, 0x09F, 0x0A0, 0x0A0, 0x0A1, 0x0A2, 0x0A2, 0x0A3, 0x0A3,
    0x0A4, 0x0A5, 0x0A5, 0x0A6, 0x0A6, 0x0A7, 0x0A8, 0x0A8, 0x0A9, 0x0A9, 0x0AA,
    0x0AB, 0x0AB, 0x0AC, 0x0AC, 0x0AD, 0x0AE, 0x0AE, 0x0AF, 0x0AF, 0x0B0, 0x0B0,
    0x0B1, 0x0B2, 0x0B2, 0x0B3, 0x0B3, 0x0B4, 0x0B5, 0x0B5, 0x0B6, 0x0B6, 0x0B7,
    0x0B8, 0x0B8, 0x0B9, 0x0B9, 0x0BA, 0x0BA, 0x0BB, 0x0BC, 0x0BC, 0x0BD, 0x0BD,
    0x0BE, 0x0BF, 0x0BF, 0x0C0, 0x0C0, 0x0C1, 0x0C1, 0x0C2, 0x0C3, 0x0C3, 0x0C4,
    0x0C4, 0x0C5, 0x0C6, 0x0C6, 0x0C7, 0x0C7, 0x0C8, 0x0C8, 0x0C9, 0x0CA, 0x0CA,
    0x0CB, 0x0CB, 0x0CC, 0x0CC, 0x0CD, 0x0CE, 0x0CE, 0x0CF, 0x0CF, 0x0D0, 0x0D0,
    0x0D1, 0x0D2, 0x0D2, 0x0D3, 0x0D3, 0x0D4, 0x0D4, 0x0D5, 0x0D6, 0x0D6, 0x0D7,
    0x0D7, 0x0D8, 0x0D8, 0x0D9, 0x0DA, 0x0DA, 0x0DB, 0x0DB, 0x0DC, 0x0DC, 0x0DD,
    0x0DE, 0x0DE, 0x0DF, 0x0DF, 0x0E0, 0x0E0, 0x0E1, 0x0E2, 0x0E2, 0x0E3, 0x0E3,
    0x0E4, 0x0E4, 0x0E5, 0x0E5, 0x0E6, 0x0E7, 0x0E7, 0x0E8, 0x0E8, 0x0E9, 0x0E9,
    0x0EA, 0x0EA, 0x0EB, 0x0EC, 0x0EC, 0x0ED, 0x0ED, 0x0EE, 0x0EE, 0x0EF, 0x0EF,
    0x0F0, 0x0F1, 0x0F1, 0x0F2, 0x0F2, 0x0F3, 0x0F3, 0x0F4, 0x0F4, 0x0F5, 0x0F6,
    0x0F6, 0x0F7, 0x0F7, 0x0F8, 0x0F8, 0x0F9, 0x0F9, 0x0FA, 0x0FB, 0x0FB, 0x0FC,
    0x0FC, 0x0FD, 0x0FD, 0x0FE, 0x0FE, 0x0FF, 0x0FF, 0x100, 0x101, 0x101, 0x102,
    0x102, 0x103, 0x103, 0x104, 0x104, 0x105, 0x105, 0x106, 0x106, 0x107, 0x108,
    0x108, 0x109, 0x109, 0x10A, 0x10A, 0x10B, 0x10B, 0x10C, 0x10C, 0x10D, 0x10D,
    0x10E, 0x10E, 0x10F, 0x110, 0x110, 0x111, 0x111, 0x112, 0x112, 0x113, 0x113,
    0x114, 0x114, 0x115, 0x115, 0x116, 0x116, 0x117, 0x117, 0x118, 0x119, 0x119,
    0x11A, 0x11A, 0x11B, 0x11B, 0x11C, 0x11C, 0x11D, 0x11D, 0x11E, 0x11E, 0x11F,
    0x11F, 0x120, 0x120, 0x121, 0x121, 0x122, 0x122, 0x123, 0x123, 0x124, 0x125,
    0x125, 0x126, 0x126, 0x127, 0x127, 0x128, 0x128, 0x129, 0x129, 0x12A, 0x12A,
    0x12B, 0x12B, 0x12C, 0x12C, 0x12D, 0x12D, 0x12E, 0x12E, 0x12F, 0x12F, 0x130,
    0x130, 0x131, 0x131, 0x132, 0x132, 0x133, 0x133, 0x134, 0x134, 0x135, 0x135,
    0x136, 0x136, 0x137, 0x137, 0x138, 0x138, 0x139, 0x139, 0x13A, 0x13A, 0x13B,
    0x13B, 0x13C, 0x13C, 0x13D, 0x13D, 0x13E, 0x13E, 0x13F, 0x13F, 0x140, 0x140,
    0x141, 0x141, 0x142, 0x142, 0x143, 0x143, 0x144, 0x144, 0x145, 0x145, 0x146,
    0x146, 0x147, 0x147, 0x148, 0x148, 0x149, 0x149, 0x14A, 0x14A, 0x14B, 0x14B,
    0x14C, 0x14C, 0x14D, 0x14D, 0x14E, 0x14E, 0x14E, 0x14F, 0x14F, 0x150, 0x150,
    0x151, 0x151, 0x152, 0x152, 0x153, 0x153, 0x154, 0x154, 0x155, 0x155, 0x156,
    0x156, 0x157, 0x157, 0x158, 0x158, 0x159, 0x159, 0x159, 0x15A, 0x15A, 0x15B,
    0x15B, 0x15C, 0x15C, 0x15D, 0x15D, 0x15E, 0x15E, 0x15F, 0x15F, 0x160, 0x160,
    0x161, 0x161, 0x161, 0x162, 0x162, 0x163, 0x163, 0x164, 0x164, 0x165, 0x165,
    0x166, 0x166, 0x167, 0x167, 0x168, 0x168, 0x168, 0x169, 0x169, 0x16A, 0x16A,
    0x16B, 0x16B, 0x16C, 0x16C, 0x16D, 0x16D, 0x16D, 0x16E, 0x16E, 0x16F, 0x16F,
    0x170, 0x170, 0x171, 0x171, 0x172, 0x172, 0x172, 0x173, 0x173, 0x174, 0x174,
    0x175, 0x175, 0x176, 0x176, 0x177, 0x177, 0x177, 0x178, 0x178, 0x179, 0x179,
    0x17A, 0x17A, 0x17B, 0x17B, 0x17B, 0x17C, 0x17C, 0x17D, 0x17D, 0x17E, 0x17E,
    0x17F, 0x17F, 0x17F, 0x180, 0x180, 0x181, 0x181, 0x182, 0x182, 0x182, 0x183,
    0x183, 0x184, 0x184, 0x185, 0x185, 0x186, 0x186, 0x186, 0x187, 0x187, 0x188,
    0x188, 0x189, 0x189, 0x189, 0x18A, 0x18A, 0x18B, 0x18B, 0x18C, 0x18C, 0x18C,
    0x18D, 0x18D, 0x18E, 0x18E, 0x18F, 0x18F, 0x18F, 0x190, 0x190, 0x191, 0x191,
    0x192, 0x192, 0x192, 0x193, 0x193, 0x194, 0x194, 0x195, 0x195, 0x195, 0x196,
    0x196, 0x197, 0x197, 0x197, 0x198, 0x198, 0x199, 0x199, 0x19A, 0x19A, 0x19A,
    0x19B, 0x19B, 0x19C, 0x19C, 0x19C, 0x19D, 0x19D, 0x19E, 0x19E, 0x19E, 0x19F,
    0x19F, 0x1A0, 0x1A0, 0x1A1, 0x1A1, 0x1A1, 0x1A2, 0x1A2, 0x1A3, 0x1A3, 0x1A3,
    0x1A4, 0x1A4, 0x1A5, 0x1A5, 0x1A5, 0x1A6, 0x1A6, 0x1A7, 0x1A7, 0x1A7, 0x1A8,
    0x1A8, 0x1A9, 0x1A9, 0x1A9, 0x1AA, 0x1AA, 0x1AB, 0x1AB, 0x1AB, 0x1AC, 0x1AC,
    0x1AD, 0x1AD, 0x1AD, 0x1AE, 0x1AE, 0x1AF, 0x1AF, 0x1AF, 0x1B0, 0x1B0, 0x1B1,
    0x1B1, 0x1B1, 0x1B2, 0x1B2, 0x1B3, 0x1B3, 0x1B3, 0x1B4, 0x1B4, 0x1B5, 0x1B5,
    0x1B5, 0x1B6, 0x1B6, 0x1B7, 0x1B7, 0x1B7, 0x1B8, 0x1B8, 0x1B8, 0x1B9, 0x1B9,
    0x1BA, 0x1BA, 0x1BA, 0x1BB, 0x1BB, 0x1BC, 0x1BC, 0x1BC, 0x1BD, 0x1BD, 0x1BD,
    0x1BE, 0x1BE, 0x1BF, 0x1BF, 0x1BF, 0x1C0, 0x1C0, 0x1C0, 0x1C1, 0x1C1, 0x1C2,
    0x1C2, 0x1C2, 0x1C3, 0x1C3, 0x1C4, 0x1C4, 0x1C4, 0x1C5, 0x1C5, 0x1C5, 0x1C6,
    0x1C6, 0x1C7, 0x1C7, 0x1C7, 0x1C8, 0x1C8, 0x1C8, 0x1C9, 0x1C9, 0x1CA, 0x1CA,
    0x1CA, 0x1CB, 0x1CB, 0x1CB, 0x1CC, 0x1CC, 0x1CC, 0x1CD, 0x1CD, 0x1CE, 0x1CE,
    0x1CE, 0x1CF, 0x1CF, 0x1CF, 0x1D0, 0x1D0, 0x1D0, 0x1D1, 0x1D1, 0x1D2, 0x1D2,
    0x1D2, 0x1D3, 0x1D3, 0x1D3, 0x1D4, 0x1D4, 0x1D4, 0x1D5, 0x1D5, 0x1D6, 0x1D6,
    0x1D6, 0x1D7, 0x1D7, 0x1D7, 0x1D8, 0x1D8, 0x1D8, 0x1D9, 0x1D9, 0x1D9, 0x1DA,
    0x1DA, 0x1DB, 0x1DB, 0x1DB, 0x1DC, 0x1DC, 0x1DC, 0x1DD, 0x1DD, 0x1DD, 0x1DE,
    0x1DE, 0x1DE, 0x1DF, 0x1DF, 0x1DF, 0x1E0, 0x1E0, 0x1E1, 0x1E1, 0x1E1, 0x1E2,
    0x1E2, 0x1E2, 0x1E3, 0x1E3, 0x1E3, 0x1E4, 0x1E4, 0x1E4, 0x1E5, 0x1E5, 0x1E5,
    0x1E6, 0x1E6, 0x1E6, 0x1E7, 0x1E7, 0x1E7, 0x1E8, 0x1E8, 0x1E8, 0x1E9, 0x1E9,
    0x1E9, 0x1EA, 0x1EA, 0x1EA, 0x1EB, 0x1EB, 0x1EB, 0x1EC, 0x1EC, 0x1ED, 0x1ED,
    0x1ED, 0x1EE, 0x1EE, 0x1EE, 0x1EF, 0x1EF, 0x1EF, 0x1F0, 0x1F0, 0x1F0, 0x1F1,
    0x1F1, 0x1F1, 0x1F2, 0x1F2, 0x1F2, 0x1F3, 0x1F3, 0x1F3, 0x1F4, 0x1F4, 0x1F4,
    0x1F4, 0x1F5, 0x1F5, 0x1F5, 0x1F6, 0x1F6, 0x1F6, 0x1F7, 0x1F7, 0x1F7, 0x1F8,
    0x1F8, 0x1F8, 0x1F9, 0x1F9, 0x1F9, 0x1FA, 0x1FA, 0x1FA, 0x1FB, 0x1FB, 0x1FB,
    0x1FC, 0x1FC, 0x1FC, 0x1FD, 0x1FD, 0x1FD, 0x1FE, 0x1FE, 0x1FE, 0x1FF, 0x1FF,
    0x1FF, 0x200, 0x200, 0x200, 0x200, 0x201, 0x201, 0x201, 0x202, 0x202, 0x202,
    0x203, 0x203, 0x203, 0x204, 0x204, 0x204,
};

s32 func_0600EE64(s32 param_1) { return MTH_Sqrt(param_1 << 4) >> 4; }

long ratan2(long dx, long dy) {
    long ret;

    while (dx <= -0x200000 || dx >= 0x200000 || dy <= -0x200000 ||
           dy >= 0x200000) {
        dy = dy >> 1;
        dx = dx >> 1;
    }

    if (dy == 0) {
        if (dx == 0) {
            return 0;
        }
        if (dx > 0) {
            return 0x400;
        } else {
            return 0xC00;
        }
    }

    if (dx >= 0) {
        if (dy > 0) {
            if (dy >= dx) {
                ret = 0x000 + ratan_tbl[(dx << 10) / dy];
            } else {
                ret = 0x400 - ratan_tbl[(dy << 10) / dx];
            }
        } else {
            if (-dy >= dx) {
                ret = 0x800 - ratan_tbl[(dx << 10) / -dy];
            } else {
                ret = 0x400 + ratan_tbl[(-dy << 10) / dx];
            }
        }
    } else {
        if (dy < 0) {
            if (-dy >= -dx) {
                ret = 0x800 + ratan_tbl[(-dx << 10) / -dy];
            } else {
                ret = 0xC00 - ratan_tbl[(-dy << 10) / -dx];
            }
        } else {
            if (dy >= -dx) {
                ret = 0x1000 - ratan_tbl[(-dx << 10) / dy];
            } else {
                ret = 0xC00 + ratan_tbl[(dy << 10) / -dx];
            }
        }
    }
    return ret;
}

const s16 rsin_tbl[1024] = {
    0x0000, 0x0006, 0x000C, 0x0012, 0x0019, 0x001F, 0x0025, 0x002B, 0x0032,
    0x0038, 0x003E, 0x0045, 0x004B, 0x0051, 0x0057, 0x005E, 0x0064, 0x006A,
    0x0071, 0x0077, 0x007D, 0x0083, 0x008A, 0x0090, 0x0096, 0x009D, 0x00A3,
    0x00A9, 0x00AF, 0x00B6, 0x00BC, 0x00C2, 0x00C8, 0x00CF, 0x00D5, 0x00DB,
    0x00E2, 0x00E8, 0x00EE, 0x00F4, 0x00FB, 0x0101, 0x0107, 0x010D, 0x0114,
    0x011A, 0x0120, 0x0127, 0x012D, 0x0133, 0x0139, 0x0140, 0x0146, 0x014C,
    0x0152, 0x0159, 0x015F, 0x0165, 0x016B, 0x0172, 0x0178, 0x017E, 0x0184,
    0x018B, 0x0191, 0x0197, 0x019D, 0x01A4, 0x01AA, 0x01B0, 0x01B6, 0x01BD,
    0x01C3, 0x01C9, 0x01CF, 0x01D6, 0x01DC, 0x01E2, 0x01E8, 0x01EF, 0x01F5,
    0x01FB, 0x0201, 0x0208, 0x020E, 0x0214, 0x021A, 0x0221, 0x0227, 0x022D,
    0x0233, 0x0239, 0x0240, 0x0246, 0x024C, 0x0252, 0x0259, 0x025F, 0x0265,
    0x026B, 0x0271, 0x0278, 0x027E, 0x0284, 0x028A, 0x0290, 0x0297, 0x029D,
    0x02A3, 0x02A9, 0x02AF, 0x02B6, 0x02BC, 0x02C2, 0x02C8, 0x02CE, 0x02D5,
    0x02DB, 0x02E1, 0x02E7, 0x02ED, 0x02F3, 0x02FA, 0x0300, 0x0306, 0x030C,
    0x0312, 0x0318, 0x031F, 0x0325, 0x032B, 0x0331, 0x0337, 0x033D, 0x0344,
    0x034A, 0x0350, 0x0356, 0x035C, 0x0362, 0x0368, 0x036F, 0x0375, 0x037B,
    0x0381, 0x0387, 0x038D, 0x0393, 0x0399, 0x03A0, 0x03A6, 0x03AC, 0x03B2,
    0x03B8, 0x03BE, 0x03C4, 0x03CA, 0x03D0, 0x03D7, 0x03DD, 0x03E3, 0x03E9,
    0x03EF, 0x03F5, 0x03FB, 0x0401, 0x0407, 0x040D, 0x0413, 0x041A, 0x0420,
    0x0426, 0x042C, 0x0432, 0x0438, 0x043E, 0x0444, 0x044A, 0x0450, 0x0456,
    0x045C, 0x0462, 0x0468, 0x046E, 0x0474, 0x047A, 0x0480, 0x0486, 0x048C,
    0x0492, 0x0498, 0x049E, 0x04A5, 0x04AB, 0x04B1, 0x04B7, 0x04BD, 0x04C3,
    0x04C9, 0x04CF, 0x04D5, 0x04DB, 0x04E0, 0x04E6, 0x04EC, 0x04F2, 0x04F8,
    0x04FE, 0x0504, 0x050A, 0x0510, 0x0516, 0x051C, 0x0522, 0x0528, 0x052E,
    0x0534, 0x053A, 0x0540, 0x0546, 0x054C, 0x0552, 0x0558, 0x055D, 0x0563,
    0x0569, 0x056F, 0x0575, 0x057B, 0x0581, 0x0587, 0x058D, 0x0593, 0x0599,
    0x059E, 0x05A4, 0x05AA, 0x05B0, 0x05B6, 0x05BC, 0x05C2, 0x05C7, 0x05CD,
    0x05D3, 0x05D9, 0x05DF, 0x05E5, 0x05EB, 0x05F0, 0x05F6, 0x05FC, 0x0602,
    0x0608, 0x060E, 0x0613, 0x0619, 0x061F, 0x0625, 0x062B, 0x0630, 0x0636,
    0x063C, 0x0642, 0x0648, 0x064D, 0x0653, 0x0659, 0x065F, 0x0664, 0x066A,
    0x0670, 0x0676, 0x067B, 0x0681, 0x0687, 0x068D, 0x0692, 0x0698, 0x069E,
    0x06A3, 0x06A9, 0x06AF, 0x06B5, 0x06BA, 0x06C0, 0x06C6, 0x06CB, 0x06D1,
    0x06D7, 0x06DC, 0x06E2, 0x06E8, 0x06ED, 0x06F3, 0x06F9, 0x06FE, 0x0704,
    0x070A, 0x070F, 0x0715, 0x071B, 0x0720, 0x0726, 0x072B, 0x0731, 0x0737,
    0x073C, 0x0742, 0x0748, 0x074D, 0x0753, 0x0758, 0x075E, 0x0763, 0x0769,
    0x076F, 0x0774, 0x077A, 0x077F, 0x0785, 0x078A, 0x0790, 0x0795, 0x079B,
    0x07A0, 0x07A6, 0x07AC, 0x07B1, 0x07B7, 0x07BC, 0x07C2, 0x07C7, 0x07CD,
    0x07D2, 0x07D7, 0x07DD, 0x07E2, 0x07E8, 0x07ED, 0x07F3, 0x07F8, 0x07FE,
    0x0803, 0x0809, 0x080E, 0x0813, 0x0819, 0x081E, 0x0824, 0x0829, 0x082E,
    0x0834, 0x0839, 0x083F, 0x0844, 0x0849, 0x084F, 0x0854, 0x085A, 0x085F,
    0x0864, 0x086A, 0x086F, 0x0874, 0x087A, 0x087F, 0x0884, 0x088A, 0x088F,
    0x0894, 0x0899, 0x089F, 0x08A4, 0x08A9, 0x08AF, 0x08B4, 0x08B9, 0x08BE,
    0x08C4, 0x08C9, 0x08CE, 0x08D3, 0x08D9, 0x08DE, 0x08E3, 0x08E8, 0x08EE,
    0x08F3, 0x08F8, 0x08FD, 0x0902, 0x0908, 0x090D, 0x0912, 0x0917, 0x091C,
    0x0921, 0x0927, 0x092C, 0x0931, 0x0936, 0x093B, 0x0940, 0x0945, 0x094B,
    0x0950, 0x0955, 0x095A, 0x095F, 0x0964, 0x0969, 0x096E, 0x0973, 0x0978,
    0x097D, 0x0982, 0x0987, 0x098D, 0x0992, 0x0997, 0x099C, 0x09A1, 0x09A6,
    0x09AB, 0x09B0, 0x09B5, 0x09BA, 0x09BF, 0x09C4, 0x09C9, 0x09CE, 0x09D3,
    0x09D7, 0x09DC, 0x09E1, 0x09E6, 0x09EB, 0x09F0, 0x09F5, 0x09FA, 0x09FF,
    0x0A04, 0x0A09, 0x0A0E, 0x0A12, 0x0A17, 0x0A1C, 0x0A21, 0x0A26, 0x0A2B,
    0x0A30, 0x0A35, 0x0A39, 0x0A3E, 0x0A43, 0x0A48, 0x0A4D, 0x0A51, 0x0A56,
    0x0A5B, 0x0A60, 0x0A65, 0x0A69, 0x0A6E, 0x0A73, 0x0A78, 0x0A7C, 0x0A81,
    0x0A86, 0x0A8B, 0x0A8F, 0x0A94, 0x0A99, 0x0A9D, 0x0AA2, 0x0AA7, 0x0AAC,
    0x0AB0, 0x0AB5, 0x0ABA, 0x0ABE, 0x0AC3, 0x0AC8, 0x0ACC, 0x0AD1, 0x0AD5,
    0x0ADA, 0x0ADF, 0x0AE3, 0x0AE8, 0x0AEC, 0x0AF1, 0x0AF6, 0x0AFA, 0x0AFF,
    0x0B03, 0x0B08, 0x0B0C, 0x0B11, 0x0B15, 0x0B1A, 0x0B1F, 0x0B23, 0x0B28,
    0x0B2C, 0x0B31, 0x0B35, 0x0B3A, 0x0B3E, 0x0B42, 0x0B47, 0x0B4B, 0x0B50,
    0x0B54, 0x0B59, 0x0B5D, 0x0B62, 0x0B66, 0x0B6A, 0x0B6F, 0x0B73, 0x0B78,
    0x0B7C, 0x0B80, 0x0B85, 0x0B89, 0x0B8D, 0x0B92, 0x0B96, 0x0B9A, 0x0B9F,
    0x0BA3, 0x0BA7, 0x0BAC, 0x0BB0, 0x0BB4, 0x0BB8, 0x0BBD, 0x0BC1, 0x0BC5,
    0x0BCA, 0x0BCE, 0x0BD2, 0x0BD6, 0x0BDA, 0x0BDF, 0x0BE3, 0x0BE7, 0x0BEB,
    0x0BEF, 0x0BF4, 0x0BF8, 0x0BFC, 0x0C00, 0x0C04, 0x0C08, 0x0C0D, 0x0C11,
    0x0C15, 0x0C19, 0x0C1D, 0x0C21, 0x0C25, 0x0C29, 0x0C2D, 0x0C31, 0x0C36,
    0x0C3A, 0x0C3E, 0x0C42, 0x0C46, 0x0C4A, 0x0C4E, 0x0C52, 0x0C56, 0x0C5A,
    0x0C5E, 0x0C62, 0x0C66, 0x0C6A, 0x0C6E, 0x0C72, 0x0C76, 0x0C79, 0x0C7D,
    0x0C81, 0x0C85, 0x0C89, 0x0C8D, 0x0C91, 0x0C95, 0x0C99, 0x0C9D, 0x0CA0,
    0x0CA4, 0x0CA8, 0x0CAC, 0x0CB0, 0x0CB4, 0x0CB7, 0x0CBB, 0x0CBF, 0x0CC3,
    0x0CC7, 0x0CCA, 0x0CCE, 0x0CD2, 0x0CD6, 0x0CD9, 0x0CDD, 0x0CE1, 0x0CE5,
    0x0CE8, 0x0CEC, 0x0CF0, 0x0CF3, 0x0CF7, 0x0CFB, 0x0CFE, 0x0D02, 0x0D06,
    0x0D09, 0x0D0D, 0x0D11, 0x0D14, 0x0D18, 0x0D1C, 0x0D1F, 0x0D23, 0x0D26,
    0x0D2A, 0x0D2D, 0x0D31, 0x0D35, 0x0D38, 0x0D3C, 0x0D3F, 0x0D43, 0x0D46,
    0x0D4A, 0x0D4D, 0x0D51, 0x0D54, 0x0D58, 0x0D5B, 0x0D5F, 0x0D62, 0x0D65,
    0x0D69, 0x0D6C, 0x0D70, 0x0D73, 0x0D77, 0x0D7A, 0x0D7D, 0x0D81, 0x0D84,
    0x0D87, 0x0D8B, 0x0D8E, 0x0D91, 0x0D95, 0x0D98, 0x0D9B, 0x0D9F, 0x0DA2,
    0x0DA5, 0x0DA9, 0x0DAC, 0x0DAF, 0x0DB2, 0x0DB6, 0x0DB9, 0x0DBC, 0x0DBF,
    0x0DC2, 0x0DC6, 0x0DC9, 0x0DCC, 0x0DCF, 0x0DD2, 0x0DD5, 0x0DD9, 0x0DDC,
    0x0DDF, 0x0DE2, 0x0DE5, 0x0DE8, 0x0DEB, 0x0DEE, 0x0DF2, 0x0DF5, 0x0DF8,
    0x0DFB, 0x0DFE, 0x0E01, 0x0E04, 0x0E07, 0x0E0A, 0x0E0D, 0x0E10, 0x0E13,
    0x0E16, 0x0E19, 0x0E1C, 0x0E1F, 0x0E22, 0x0E25, 0x0E28, 0x0E2B, 0x0E2D,
    0x0E30, 0x0E33, 0x0E36, 0x0E39, 0x0E3C, 0x0E3F, 0x0E42, 0x0E44, 0x0E47,
    0x0E4A, 0x0E4D, 0x0E50, 0x0E53, 0x0E55, 0x0E58, 0x0E5B, 0x0E5E, 0x0E60,
    0x0E63, 0x0E66, 0x0E69, 0x0E6B, 0x0E6E, 0x0E71, 0x0E74, 0x0E76, 0x0E79,
    0x0E7C, 0x0E7E, 0x0E81, 0x0E84, 0x0E86, 0x0E89, 0x0E8B, 0x0E8E, 0x0E91,
    0x0E93, 0x0E96, 0x0E98, 0x0E9B, 0x0E9E, 0x0EA0, 0x0EA3, 0x0EA5, 0x0EA8,
    0x0EAA, 0x0EAD, 0x0EAF, 0x0EB2, 0x0EB4, 0x0EB7, 0x0EB9, 0x0EBC, 0x0EBE,
    0x0EC0, 0x0EC3, 0x0EC5, 0x0EC8, 0x0ECA, 0x0ECD, 0x0ECF, 0x0ED1, 0x0ED4,
    0x0ED6, 0x0ED8, 0x0EDB, 0x0EDD, 0x0EDF, 0x0EE2, 0x0EE4, 0x0EE6, 0x0EE8,
    0x0EEB, 0x0EED, 0x0EEF, 0x0EF2, 0x0EF4, 0x0EF6, 0x0EF8, 0x0EFA, 0x0EFD,
    0x0EFF, 0x0F01, 0x0F03, 0x0F05, 0x0F08, 0x0F0A, 0x0F0C, 0x0F0E, 0x0F10,
    0x0F12, 0x0F14, 0x0F16, 0x0F18, 0x0F1B, 0x0F1D, 0x0F1F, 0x0F21, 0x0F23,
    0x0F25, 0x0F27, 0x0F29, 0x0F2B, 0x0F2D, 0x0F2F, 0x0F31, 0x0F33, 0x0F35,
    0x0F37, 0x0F39, 0x0F3B, 0x0F3C, 0x0F3E, 0x0F40, 0x0F42, 0x0F44, 0x0F46,
    0x0F48, 0x0F4A, 0x0F4B, 0x0F4D, 0x0F4F, 0x0F51, 0x0F53, 0x0F55, 0x0F56,
    0x0F58, 0x0F5A, 0x0F5C, 0x0F5D, 0x0F5F, 0x0F61, 0x0F63, 0x0F64, 0x0F66,
    0x0F68, 0x0F69, 0x0F6B, 0x0F6D, 0x0F6E, 0x0F70, 0x0F72, 0x0F73, 0x0F75,
    0x0F77, 0x0F78, 0x0F7A, 0x0F7B, 0x0F7D, 0x0F7F, 0x0F80, 0x0F82, 0x0F83,
    0x0F85, 0x0F86, 0x0F88, 0x0F89, 0x0F8B, 0x0F8C, 0x0F8E, 0x0F8F, 0x0F91,
    0x0F92, 0x0F94, 0x0F95, 0x0F96, 0x0F98, 0x0F99, 0x0F9B, 0x0F9C, 0x0F9D,
    0x0F9F, 0x0FA0, 0x0FA1, 0x0FA3, 0x0FA4, 0x0FA5, 0x0FA7, 0x0FA8, 0x0FA9,
    0x0FAB, 0x0FAC, 0x0FAD, 0x0FAE, 0x0FB0, 0x0FB1, 0x0FB2, 0x0FB3, 0x0FB4,
    0x0FB6, 0x0FB7, 0x0FB8, 0x0FB9, 0x0FBA, 0x0FBB, 0x0FBD, 0x0FBE, 0x0FBF,
    0x0FC0, 0x0FC1, 0x0FC2, 0x0FC3, 0x0FC4, 0x0FC5, 0x0FC6, 0x0FC7, 0x0FC8,
    0x0FC9, 0x0FCA, 0x0FCB, 0x0FCC, 0x0FCD, 0x0FCE, 0x0FCF, 0x0FD0, 0x0FD1,
    0x0FD2, 0x0FD3, 0x0FD4, 0x0FD5, 0x0FD6, 0x0FD7, 0x0FD8, 0x0FD9, 0x0FD9,
    0x0FDA, 0x0FDB, 0x0FDC, 0x0FDD, 0x0FDE, 0x0FDE, 0x0FDF, 0x0FE0, 0x0FE1,
    0x0FE1, 0x0FE2, 0x0FE3, 0x0FE4, 0x0FE4, 0x0FE5, 0x0FE6, 0x0FE7, 0x0FE7,
    0x0FE8, 0x0FE9, 0x0FE9, 0x0FEA, 0x0FEB, 0x0FEB, 0x0FEC, 0x0FEC, 0x0FED,
    0x0FEE, 0x0FEE, 0x0FEF, 0x0FEF, 0x0FF0, 0x0FF0, 0x0FF1, 0x0FF1, 0x0FF2,
    0x0FF2, 0x0FF3, 0x0FF3, 0x0FF4, 0x0FF4, 0x0FF5, 0x0FF5, 0x0FF6, 0x0FF6,
    0x0FF7, 0x0FF7, 0x0FF7, 0x0FF8, 0x0FF8, 0x0FF9, 0x0FF9, 0x0FF9, 0x0FFA,
    0x0FFA, 0x0FFA, 0x0FFB, 0x0FFB, 0x0FFB, 0x0FFB, 0x0FFC, 0x0FFC, 0x0FFC,
    0x0FFC, 0x0FFD, 0x0FFD, 0x0FFD, 0x0FFD, 0x0FFE, 0x0FFE, 0x0FFE, 0x0FFE,
    0x0FFE, 0x0FFE, 0x0FFF, 0x0FFF, 0x0FFF, 0x0FFF, 0x0FFF, 0x0FFF, 0x0FFF,
    0x0FFF, 0x0FFF, 0x0FFF, 0x0FFF, 0x0FFF, 0x0FFF, 0x0FFF,
};

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600F7BC, func_0600F7BC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600F81C, func_0600F81C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600F87C, func_0600F87C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600F914, func_0600F914);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600F96C, func_0600F96C);

// _PSX_SHAKE_MAIN
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600FA4C, func_0600FA4C);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600FACC, func_0600FACC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600FB0C, func_0600FB0C);

void func_0600FB34(void) {
    DAT_06057A10[0] = 0;
    DAT_06057A10[4] = 0;
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600FB4C, func_0600FB4C);

// _TEST_TEST
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600FB9C, func_0600FB9C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600FBBC, func_0600FBBC);

// _all_map_check
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600FC04, func_0600FC04);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600FCF8, func_0600FCF8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600FE98, func_0600FE98);

void func_0600FEFC() {}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600FF08, func_0600FF08);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600FF64, func_0600FF64);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600FFB8, func_0600FFB8);

void func_06010008(void) {
    struct Unk0605d6c0* puVar2;
    SclConfig temp;

    DAT_06062224[1] = 0;
    DAT_06062224[0] = 0;
    ClearDebugPrintTilemap();
    SCL_InitConfigTb(&temp);
    temp.dispenbl = 1;
    temp.charsize = 0;
    temp.pnamesize = 1;
    temp.platesize = 0;
    temp.coltype = 0;
    temp.datatype = 0;
    temp.mapover = 0;
    temp.flip = 0;
    temp.patnamecontrl = 0x66;
    temp.plate_addr[0] = VDP2_DEBUG_TILEMAP_OFFSET;
    temp.plate_addr[1] = VDP2_DEBUG_TILEMAP_OFFSET;
    temp.plate_addr[2] = VDP2_DEBUG_TILEMAP_OFFSET;
    temp.plate_addr[3] = VDP2_DEBUG_TILEMAP_OFFSET;
    SCL_SetConfig(SCL_NBG0, &temp);
    puVar2 = &DAT_0605d6c0;
    puVar2->unk30 = 0x10;
    puVar2->unk34 = &DAT_06039214;
    puVar2->unk38 = VDP2_25F00600;
    puVar2->unk3c = 0x80;
}

// 0x060100b8
// clears the debug print tilemap area, debug prints are at least used by
// the stage select screen on the title screen
void ClearDebugPrintTilemap(void) {
    u16 i;
    u16* ptr;

    ptr = VDP2_DEBUG_TILEMAP_OFFSET;
    for (i = 0; i < 0x1000; i++) {
        *ptr++ = 0;
    }
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60100DC, func_060100DC);

// debug print function used by title screen stage select
// _DEBUG_FONT_SET2
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6010274, func_06010274);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6010328, func_06010328);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6010400, func_06010400);

// _pause_seq
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60110C0, func_060110C0);

void func_06011264(void) {
    // set input capture flag on sub-sh2
    *((u16*)SH2_REG_M_FRT_IC) = 0xffff;
    return;
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6011278, func_06011278);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6011A6C, func_06011A6C);

extern s32 DAT_06064230;
extern s16 DAT_060643c4;
extern u8 DAT_060644c4;

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
    DAT_060643c4 = sfxPan;
    DAT_060644c4 = 1;
    PlaySfx(sfxId);
    DAT_060644c4 = 0;
    return ret;
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6011B28, func_06011B28);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6011C28, func_06011C28);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6011CE4, func_06011CE4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6011EE0, func_06011EE0);

void func_06011F40(s32 param) { SND_StopPcm2(); }

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6011F58, func_06011F58);

// _KeyOffBGM2
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6011FC8, func_06011FC8);
