// SPDX-License-Identifier: AGPL-3.0-only
#include "zero.h"
#include "inc_asm.h"
#include "sattypes.h"
#include "lib/scl.h"

// func_06004080
void entrypoint(void) {
    func_06030df0();
    Scl_s_reg.tvmode = Scl_s_reg.tvmode & 0x7eff;
    SclProcess = 1;
    func_060044D0();
    DAT_0605cea2 = 0;
    DAT_0605c658 = 1;
    do {
        func_060040D8();
    } while (true);
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60040D8, func_060040D8);
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
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6004C44, func_06004C44);

// _REPEAT_PAD
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6004C70, func_06004C70);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6004CDC, func_06004CDC);

// _SET_VBLANK
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6004D00, func_06004D00);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6004D84, func_06004D84);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6004DE8, func_06004DE8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6004E50, func_06004E50);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6004E94, func_06004E94);

// _RETURN_TO_GAME
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6004EF0, func_06004EF0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6004F50, func_06004F50);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6005208, func_06005208);

void func_06005310(void) { func_06006FA8(); }

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6005328, func_06005328);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600544C, func_0600544C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6005470, func_06005470);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6005508, func_06005508);

// _READ_LOAD_MODE
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60055A4, func_060055A4);
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

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600654C, func_0600654C);

// _FileReadSetAdrEx
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6006574, func_06006574);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60066F0, func_060066F0);

// _FileReadNWStartEx
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6006720, func_06006720);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6006A7C, func_06006A7C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6006C00, func_06006C00);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6006E14, func_06006E14);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6006E4C, func_06006E4C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6006E9C, func_06006E9C);

// _IsCdOpened
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6006ED4, func_06006ED4);
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
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6007824, func_06007824);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60078EC, func_060078EC);

// _InitVdp1
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6007968, func_06007968);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6007A34, func_06007A34);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6007B34, func_06007B34);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6007B8C, func_06007B8C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6007BE0, func_06007BE0);

// _SprSetGourTbl
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6007CA0, func_06007CA0);

u16 func_06007CE0(u16 param_1) { return param_1 * 0x10 + 0x400; }

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6007CF8, func_06007CF8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6007D54, func_06007D54);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6007E14, func_06007E14);
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/f_nonmat", f6007EE6, func_06007EE6);
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/f_nonmat", f6007F3A, func_06007F3A);

// _SET_VDP2_VRAM
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6007F6C, func_06007F6C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6008048, func_06008048);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60080EC, func_060080EC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6008134, func_06008134);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600815C, func_0600815C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60081C8, func_060081C8);

// func_0600824C
void InitScuDma(void) {
    // sega library func
    DMA_ScuInit();
}

// _VDP1_TRANS
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6008264, func_06008264);

void func_06008298(void) {
    int i;
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
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6008464, func_06008464);
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
    if (puVar5->flags == 0) {
        return;
    }
    if ((puVar5->flags & 1) != 0) {
        cnt = func_0600F96C(puVar6->unkc, &DAT_060485e0, puVar6->unk18);
        DmaScroll(&DAT_060485e0, puVar6->dst0, cnt);
    }
    if ((puVar5->flags & 2) != 0) {
        cnt = func_0600F96C(puVar6->unk10, &DAT_060485e0, puVar6->unk1c);
        DmaScroll(&DAT_060485e0, puVar6->dst4, cnt);
    }
    if ((puVar5->flags & 4) != 0) {
        if (DAT_060086d4 == 4) {
            func_060089F0(puVar6);
        } else {
            func_0600871C(puVar6, &DAT_0605c680, param_1);
        }
    }
    if ((puVar5->flags & 8) != 0) {
        DmaScroll(puVar5->src, puVar5->dest, puVar5->cnt);
    }
    if ((puVar5->flags & 0x10) != 0) {
        DmaScroll(puVar5->src, puVar5->dest, puVar5->cnt);
    }
    if ((puVar5->flags & 0x20) != 0) {
        DmaScroll(puVar5->src, puVar5->dest, puVar5->cnt);
    }
    if ((puVar5->flags & 0x40) != 0) {
        cnt = func_0600F96C(puVar6->unkc, DMA_SRC_ADDR, puVar6->unk18);
        DmaScroll(DMA_SRC_ADDR, puVar6->dst0, cnt);
    }
    if ((puVar5->flags & 0x80) != 0) {
        cnt = func_0600F96C(puVar6->unk10, DMA_SRC_ADDR, puVar6->unk1c);
        DmaScroll(DMA_SRC_ADDR, puVar6->dst4, cnt);
    }
    puVar5->flags = 0;
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
        DMA_CpuMemCopy(dest, src, cnt >> 1); // not sure which of 1-5
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
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6009038, func_06009038);
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
void SetSprGourTable(u16 arg0) { SPR_2SetGourTbl(arg0); }

// _SetPlTransNonSeparateAura
void func_0600A31C(void) { DAT_0605D910[3] = 1; }

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600A330, func_0600A330);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600A350, func_0600A350);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600A490, func_0600A490);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600A5FC, func_0600A5FC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600A62C, func_0600A62C);
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
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600B104, func_0600B104);
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

int func_0600BD4C(u8* param_1) { return DAT_0606471C + param_1[2] * 2; }

// _Odma
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600BD68, func_0600BD68);

// _AllocGameSprite
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600BE18, func_0600BE18);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600BE7C, func_0600BE7C);
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
    DAT_0605AEA8 = 0x10;
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

// _ClearFrameBuffer
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
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600CFE0, func_0600CFE0);
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

// _MOVIE_PRG_CLEAR
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600DA90, func_0600DA90);

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

void func_0600E050(struct Unk0600E050* param_1, short param_2, short param_3)

{
    param_1->unkc = param_2 + param_1->unkc;
    param_1->unke = param_3 + param_1->unke;
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600E070, func_0600E070);

void func_0600E0A4(struct Unk0600E050* param_1, short param_2, short param_3)

{
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
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600EE64, func_0600EE64);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600EE88, func_0600EE88);
INCLUDE_ASM("asm/saturn/zero/data", d600EFBC, d_0600EFBC);
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
    temp.plate_addr[0] = VDP2_25E58000;
    temp.plate_addr[1] = VDP2_25E58000;
    temp.plate_addr[2] = VDP2_25E58000;
    temp.plate_addr[3] = VDP2_25E58000;
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

INCLUDE_ASM("asm/saturn/zero/data", d6011278, d_06011278);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6011A6C, func_06011A6C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6011AA0, func_06011AA0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6011B28, func_06011B28);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6011C28, func_06011C28);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6011CE4, func_06011CE4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6011EE0, func_06011EE0);

void func_06011F40(void) { func_06018D88(); }

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6011F58, func_06011F58);

// _KeyOffBGM2
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6011FC8, func_06011FC8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6012030, func_06012030);

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

// _xa_play_ck
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6012DD0, func_06012DD0);

// _vox_play_ck
bool func_06012DFC(void) {
    if (DAT_06064214 != 0) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6012E18, func_06012E18);

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

void func_06013394(void) {
    DAT_060644c1 = 1;
    DAT_060644dc = 2;
}

void func_060133B0(void) {
    DAT_060644c1 = 0;
    DAT_060644dc = 2;
}

// _conve
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60133CC, func_060133CC);

// _convertDVI_STE
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6013538, func_06013538);
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
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6015C70, func_06015C70);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60164BC, func_060164BC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6016614, func_06016614);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60166A8, func_060166A8);

// _PcmOpen
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6016B44, func_06016B44);

// _PcmLseek
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6016B6C, func_06016B6C);

void func_06016B9C(s32 param_1, s32 param_2, s32 param_3) {
    func_06017FA4(param_2, param_3, param_1);
}

void func_06016BBC(s32 param_1, s32 param_2, s32 param_3) {
    func_06017FA4(param_2, param_3, param_1);
}

// _PcmClose
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6016BDC, func_06016BDC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6016C08, func_06016C08);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6016C60, func_06016C60);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6016D84, func_06016D84);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6016E84, func_06016E84);

// _code2name
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6016EE4, func_06016EE4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6016F9C, func_06016F9C);
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
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60186C8, func_060186C8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018848, func_06018848);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018910, func_06018910);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601896C, func_0601896C);

// _SND_StartSeq_DR
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60189F0, func_060189F0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018A78, func_06018A78);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018AD4, func_06018AD4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018B30, func_06018B30);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018B8C, func_06018B8C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018C00, func_06018C00);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018C74, func_06018C74);

// _SND_StopPcm2
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018D88, func_06018D88);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018DE4, func_06018DE4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018EB8, func_06018EB8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018EE0, func_06018EE0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018F04, func_06018F04);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018F20, func_06018F20);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018FA8, func_06018FA8);

void func_06018FC4(void) { func_06033024(); }

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018FDC, func_06018FDC);

// not sure if this is actually Entity*
void func_06019058(Entity* param_1) {
    if (param_1->step == 0) {
        param_1->step += 1;
    }
}

const u16 pad_14ff2 = 0;

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6019074, func_06019074);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60190D8, func_060190D8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6019560, func_06019560);

void func_060195F0(void) {
    DAT_060476a4 = 0;
    DAT_060476a0 = 0;
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601960C, func_0601960C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601972C, func_0601972C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60198F4, func_060198F4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601992C, func_0601992C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60199F8, func_060199F8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6019A7C, func_06019A7C);

// _INIT_NOW_LOADING
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6019FA0, func_06019FA0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6019FE4, func_06019FE4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601A020, func_0601A020);

// _SET_STAGE_OVERLAYADDR
void SetStageOverlayAddress() {
    *DAT_0601ac28 = *DAT_0601ac2c; // 0x60dc000
    *DAT_0601ac34 = *DAT_0601ac30; // 0x60dc004
    *DAT_0601ac3c = *DAT_0601ac38; // 0x60dc008
    *DAT_0601ac44 = *DAT_0601ac40; // 0x60dc00c
}

// _SET_SCL_OVERLAYADDR
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601AC48, func_0601AC48);

// _SET_PLAYER_OVERLAYADDR
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601AD14, func_0601AD14);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601AE2C, func_0601AE2C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601AE5C, func_0601AE5C);

s32 func_0601AE9C(void) { return 0xff; }

s32 func_0601AEA8(void) { return 0xff; }

void func_0601AEB4(void) { DAT_060645D0 = DAT_060cf040; }

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601AECC, func_0601AECC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601AEF4, func_0601AEF4);

void func_0601AF2C(void) { DAT_06064674 = DAT_060a5000; }

void func_0601AF44(void) { DAT_06064580 = DAT_060a5000; }

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601AF5C, func_0601AF5C);

void func_0601B184(void) { DAT_060645e0 = DAT_060a5000; }

void func_0601B19C(void) { DAT_06064644 = DAT_060dc000; }

void func_0601B1B4(void) { DAT_06064690 = DAT_06066000; }

// _SET_GAME_OVERLAYADDR
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B1CC, func_0601B1CC);

// I think everything beyond this point is sega libraries
