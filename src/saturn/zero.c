#include "zero.h"
#include "inc_asm.h"
#include "sattypes.h"

INCLUDE_ASM("asm/saturn/zero/data", d6004080, d_06004080);

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
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6005310, func_06005310);
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
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600652C, func_0600652C);
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
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6006F50, func_06006F50);

// _CdSeek
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6006F5C, func_06006F5C);

// _GetFileReadStat
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6006F68, func_06006F68);
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
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6008298, func_06008298);

// _INIT_TRANS
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60082C8, func_060082C8);
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
            goto LAB_0600862a;
        }
        func_0600871C(puVar6, &DAT_0605c680, param_1);
    }
LAB_0600862a:
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
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60089F0, func_060089F0);
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
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600B234, func_0600B234);

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
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600E050, func_0600E050);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600E070, func_0600E070);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600E0A4, func_0600E0A4);

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
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6010008, func_06010008);

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
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6011264, func_06011264);
INCLUDE_ASM("asm/saturn/zero/data", d6011278, d_06011278);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6011A6C, func_06011A6C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6011AA0, func_06011AA0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6011B28, func_06011B28);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6011C28, func_06011C28);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6011CE4, func_06011CE4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6011EE0, func_06011EE0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6011F40, func_06011F40);
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
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601269C, func_0601269C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60126B8, func_060126B8);
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
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6012DFC, func_06012DFC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6012E18, func_06012E18);

// _sd_xapause_chk
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6012E4C, func_06012E4C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6012F30, func_06012F30);

// _sd_xa_wait2
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6012F7C, func_06012F7C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6012FB4, func_06012FB4);

// _sd_alloff_chk
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6013320, func_06013320);

// _sd_reset2
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601333C, func_0601333C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6013394, func_06013394);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60133B0, func_060133B0);

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
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6016B9C, func_06016B9C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6016BBC, func_06016BBC);

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
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018FC4, func_06018FC4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018FDC, func_06018FDC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6019058, func_06019058);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6019074, func_06019074);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60190D8, func_060190D8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6019560, func_06019560);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60195F0, func_060195F0);
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
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601AE9C, func_0601AE9C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601AEA8, func_0601AEA8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601AEB4, func_0601AEB4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601AECC, func_0601AECC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601AEF4, func_0601AEF4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601AF2C, func_0601AF2C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601AF44, func_0601AF44);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601AF5C, func_0601AF5C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B184, func_0601B184);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B19C, func_0601B19C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B1B4, func_0601B1B4);

// _SET_GAME_OVERLAYADDR
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B1CC, func_0601B1CC);

// I think everything beyond this point is sega libraries

// SEGADGFS.A (debug version of lib)
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B2B4, func_0601B2B4); // GFS_Init
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B3A0, func_0601B3A0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B448, func_0601B448); // GFS_SetDir

// GFS_NameToId
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B4AC, func_0601B4AC);

// _GFS_IdToName
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B518, func_0601B518);

// _GFS_GetDirInfo
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B58C, func_0601B58C);

// _GFS_Reset
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B600, func_0601B600);

// _GFS_Open
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B674, func_0601B674);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B724, func_0601B724);

// _GFS_Seek
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B75C, func_0601B75C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B810, func_0601B810); // _GFS_Tell
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B860, func_0601B860); // _GFS_IsEof

// _GFS_ByteToScts
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B8B4, func_0601B8B4);
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/f_nonmat", f601B932, func_0601B932);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B998, func_0601B998);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B9E4, func_0601B9E4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601BA0C, func_0601BA0C); // _GFS_Load

// _GFS_Fread
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601BAD4, func_0601BAD4);
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/f_nonmat", f601BB86, func_0601BB86);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601BC74, func_0601BC74);

// _GFS_NwCdRead
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601BD20, func_0601BD20);

// _GFS_NwIsComplete
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601BD94, func_0601BD94);

// _GFS_NwStop
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601BDD0, func_0601BDD0);
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/f_nonmat", f601BE6A, func_0601BE6A);

// _gfs_recovRdErr
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601BEB8, func_0601BEB8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601BEE8, func_0601BEE8);

// _GFS_NwExecServer
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601BFA8, func_0601BFA8);
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/f_nonmat", f601C03A, func_0601C03A);
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/f_nonmat", f601C09E, func_0601C09E);
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/f_nonmat", f601C10A, func_0601C10A);
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/f_nonmat", f601C16E, func_0601C16E);

// _GFS_SetTrFunc
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C1BC, func_0601C1BC);

// _GFS_StartTrans
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C220, func_0601C220);

// _GFS_CdMovePickup
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C26C, func_0601C26C);

// _GFS_SetErrFunc
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C2D8, func_0601C2D8);

// _GFS_GetErrStat
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C308, func_0601C308);

// _GFS_ConvTno
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C32C, func_0601C32C);

// _gfs_chgRoot
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C354, func_0601C354);

// _gfs_aborttrans
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C420, func_0601C420);

// _gfs_mngSetupFuncTbl
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C42C, func_0601C42C);

// _gfs_mngInitWork
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C4A8, func_0601C4A8);

// _gfs_mngGetNumFile
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C54C, func_0601C54C);

// _GFS_mngAllocGrp
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C5B0, func_0601C5B0);

// _gfs_mngFreeGrp
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C5F8, func_0601C5F8);

// _gfs_mngTermAccess
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C604, func_0601C604);

// _gfs_mngSetErrCode
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C680, func_0601C680);

// _gfs_svrSearchHndl
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C6C8, func_0601C6C8);

// _gfs_svrAddHndl
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C708, func_0601C708);

// _gfs_svrRemoveHndl
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C744, func_0601C744);

// _GFS_OpenSub
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C7A0, func_0601C7A0);

// _gfs_loadVol
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C840, func_0601C840);

// _gfs_getRootDir
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C908, func_0601C908);

// _gfs_loadRootDir
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C9FC, func_0601C9FC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601CA88, func_0601CA88); // _gfs_flowIn
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/f_nonmat", f601CB46, func_0601CB46);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601CBD4, func_0601CBD4); // _GFS_GetFad
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601CC2C, func_0601CC2C); // _gfs_SetSct
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601CC80, func_0601CC80);

// _gfs_closeSub
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601CCA0, func_0601CCA0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601CCF0, func_0601CCF0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601CD08, func_0601CD08);

// _gfs_convFinStat
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601CD50, func_0601CD50);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601CDC0, func_0601CDC0);

// _GFCF_Setup
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601CE60, func_0601CE60);

// _GFCF_SetSct
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601CFA0, func_0601CFA0);

// _GFCF_GetFileInfo
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601CFEC, func_0601CFEC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D060, func_0601D060);

// _GFCF_StopInBuf
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D1B0, func_0601D1B0);

// _GFCF_Recover
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D250, func_0601D250);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D29C, func_0601D29C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D2B4, func_0601D2B4);

// _GFCF_MovePickup
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D2CC, func_0601D2CC);

// _GFCF_cnvIntlvOfs
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D36C, func_0601D36C);

// _GFCF_GetStat
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D3BC, func_0601D3BC);

// _gfcf_getSctSize
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D440, func_0601D440);
// _gfcf_isCdOk
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D478, func_0601D478);

// _gfcf_getPlayRange
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D534, func_0601D534);

// _GFMF_Init
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D674, func_0601D674);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D69C, func_0601D69C); // _GFMF_Setup

// _GFSF_FlowInBuf
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D758, func_0601D758);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D7B0, func_0601D7B0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D7C0, func_0601D7C0); // _GFSF_Seek
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D814, func_0601D814);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D824, func_0601D824);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D86C, func_0601D86C); // _GFSF_Setup

// _GFSF_FlowInBuf
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D94C, func_0601D94C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D9A4, func_0601D9A4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D9B4, func_0601D9B4); // _GFSF_Seek
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601DA08, func_0601DA08);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601DA18, func_0601DA18);

// _GFDR_SetupDirTbl
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601DA34, func_0601DA34);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601DA64, func_0601DA64);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601DAC4, func_0601DAC4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601DAD8, func_0601DAD8);

// _GFDR_GetAtrDirId
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601DAEC, func_0601DAEC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601DB08, func_0601DB08);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601DB1C, func_0601DB1C);

// _GFDR_ChgDir
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601DB34, func_0601DB34);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601DBC4, func_0601DBC4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601DE38, func_0601DE38);

// _gfdr_open
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E084, func_0601E084);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E0AC, func_0601E0AC); // _gfdr_read

// _gfdr_readByte
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E16C, func_0601E16C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E198, func_0601E198);

// _gfdr_readWordNB
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E1C4, func_0601E1C4);

// _gfdr_readLongNB
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E218, func_0601E218);

// _gfdr_readLongNM
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E264, func_0601E264);

// _gfdr_setNextRec
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E28C, func_0601E28C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E318, func_0601E318);

// _gfdr_setDirrecCd
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E688, func_0601E688);

// _gfdr_setDirrecMem
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E6C4, func_0601E6C4);

// _gfdr_setDirrecScsi
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E700, func_0601E700);

// _gfdr_getScsiFinfo
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E728, func_0601E728);

// _gfdr_findScsiFile
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E7B8, func_0601E7B8);

// _gfdr_findFile
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E7E4, func_0601E7E4);

// _gfdr_clearMemRsv
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E834, func_0601E834);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E89C, func_0601E89C); // _GFTR_Setup

// _GFTR_SetMode
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E8E4, func_0601E8E4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E8F8, func_0601E8F8);

// _GFTR_SetTransPara
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E904, func_0601E904);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E938, func_0601E938);

// _GFTR_GetNumTrans
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E944, func_0601E944);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E950, func_0601E950);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E95C, func_0601E95C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E968, func_0601E968);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E974, func_0601E974); // _GFTR_Stop
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601EA28, func_0601EA28); // _GFTR_Exec
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601EAAC, func_0601EAAC); // _GFTR_Idle

// _GFTR_ExecSvr
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601EB2C, func_0601EB2C);

// _gftr_getSrcPack
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601EC30, func_0601EC30);

// _gftr_getDstPack
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601ECB8, func_0601ECB8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601ED14, func_0601ED14);

// _gftr_execScu
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601ED20, func_0601ED20);

// _gftr_remScu
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601EDBC, func_0601EDBC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601EDEC, func_0601EDEC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601EDF8, func_0601EDF8); // _gfdma_exec

// _gfdma_getBytecnt
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601EEF4, func_0601EEF4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601EF28, func_0601EF28);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601EF48, func_0601EF48);

// _gftr_remDma0
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601EF64, func_0601EF64);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601EF7C, func_0601EF7C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601EF9C, func_0601EF9C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601EFB8, func_0601EFB8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601EFD0, func_0601EFD0);

// _gftr_execCpu
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601EFDC, func_0601EFDC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F01C, func_0601F01C);

// _gftr_reqTrn
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F028, func_0601F028);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F128, func_0601F128);

// _gftr_remTrn
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F160, func_0601F160);

// _gftr_copyFrac
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F1C8, func_0601F1C8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F1F0, func_0601F1F0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F1FC, func_0601F1FC);

// _GFTR_GetDstPack
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F210, func_0601F210);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F248, func_0601F248);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F264, func_0601F264);

// _GFTR_SetData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F278, func_0601F278);

// _GFTR_SetTransFunc
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F28C, func_0601F28C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F2D0, func_0601F2D0);

// _GFBF_GetNumData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F2F4, func_0601F2F4);

// _GFBF_GetSrcPk
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F320, func_0601F320);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F348, func_0601F348);

// _GFBF_RtnPk
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F370, func_0601F370);

// _gfbf_getSctDt
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F398, func_0601F398);
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/f_nonmat", f601F44A, func_0601F44A);

// _GFCB_Close
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F4B0, func_0601F4B0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F528, func_0601F528);

// _GFCB_GetLenRoom
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F57C, func_0601F57C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F5CC, func_0601F5CC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F5EC, func_0601F5EC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F614, func_0601F614);
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/f_nonmat", f601F63A, func_0601F63A);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F670, func_0601F670); // _GFCB_Seek
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F7C8, func_0601F7C8);

// _GFCB_GetSctData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F840, func_0601F840);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F878, func_0601F878);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F884, func_0601F884); // _GFCB_RtnPk

// _GFCB_MovePickup
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F8CC, func_0601F8CC);

// _GFCB_SetCon
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F8E8, func_0601F8E8);

// _GFCB_GetPickup
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F91C, func_0601F91C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F944, func_0601F944);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F95C, func_0601F95C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F974, func_0601F974);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F9A0, func_0601F9A0); // _GFCD_Init

// _GFCD_AllocFilt
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601FB98, func_0601FB98);

// _GFCD_FreeFilt
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601FBD0, func_0601FBD0);

// _GFCD_AllocBuf
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601FC00, func_0601FC00);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601FC34, func_0601FC34);

// _GFCD_GetBaseFad
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601FCD4, func_0601FCD4);

// _GFCD_GetPickup
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601FD08, func_0601FD08);

// _GFCD_UngetPickup
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601FD3C, func_0601FD3C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601FD68, func_0601FD68);

// _GFCD_SetFilt
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601FD8C, func_0601FD8C);

// _GFCD_GetFilt
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601FE4C, func_0601FE4C);

// _GFCD_SetCon
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601FE94, func_0601FE94);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601FEEC, func_0601FEEC); // _GFCD_Play

// _GFCD_GetLenData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601FF4C, func_0601FF4C);

// _GFCD_ReqData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601FFB0, func_0601FFB0);

// _GFCD_EndData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602000C, func_0602000C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6020054, func_06020054);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60200A8, func_060200A8);

// _GFCD_GetStat
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60200D4, func_060200D4);

// _GFCD_MovePickup
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6020188, func_06020188);

// _GFCD_MoveSctData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60201D4, func_060201D4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6020240, func_06020240);

// _GFCD_GetSctInfo
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6020264, func_06020264);

// _GFCD_ChgDir
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60202AC, func_060202AC);

// _GFCD_SetFiltCon
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6020328, func_06020328);

// _GFCD_GetFileInfo
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6020420, func_06020420);

// _GFCD_GetBufSiz
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60204F8, func_060204F8);

// _GFCD_ExecServer
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6020530, func_06020530);

// _gfcd_isIdleTask
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602060C, func_0602060C);

// _gfcd_doTask
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6020698, func_06020698);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6020744, func_06020744);

// _GFCD_WaitServer
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6020758, func_06020758);

// _gfcd_doSetFiltTsk
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6020794, func_06020794);

// _gfcd_doSetConTsk
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602093C, func_0602093C);

// _gfcd_doGetLenDataTsk
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60209C8, func_060209C8);

// _gfcd_doReqDataTsk
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6020B18, func_06020B18);

// _gfcd_doDelSctDataTsk
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6020BB8, func_06020BB8);

// _gfcd_doMoveSctTsk
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6020CE8, func_06020CE8);

// _gfcd_doChgDirTsk
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6020E4C, func_06020E4C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021048, func_06021048);

// _gfcd_checkEflag
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021180, func_06021180);

// _gfcd_initCdbMng
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60211A4, func_060211A4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021224, func_06021224);

// _GFCD_SetCsctFunc
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021250, func_06021250);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602126C, func_0602126C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021290, func_06021290);

// _GFCD_WaitScdqFlag
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60212AC, func_060212AC);

// _GFCD_WaitPause
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60212F0, func_060212F0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602133C, func_0602133C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021358, func_06021358);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60213A0, func_060213A0);

// _GFMB_GetSrcPack
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021434, func_06021434);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60214B4, func_060214B4); // _GFMB_RtnPk
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021500, func_06021500);

// _GFMC_GetFileInfo
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021510, func_06021510);

// _GFMC_GetNumFile
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021564, func_06021564);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021594, func_06021594);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60215B4, func_060215B4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60215D8, func_060215D8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60215FC, func_060215FC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021638, func_06021638);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021654, func_06021654);

// _GFSB_GetLenData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021670, func_06021670);

// _GFSB_GetSrcPack
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60216F4, func_060216F4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021770, func_06021770); // _GFSB_RtnPk

// _gfsb_getActSiz
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60217C0, func_060217C0);
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/f_nonmat", f602185A, func_0602185A);

// SEGA_SPR.A
// doesn't match as closely as SEGA_BUP, different version of lib?

// SPR_SetTvMode
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60218E8, func_060218E8);

// SPR_GetStatus
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021A58, func_06021A58);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021AE8, func_06021AE8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022060, func_06022060);

// _SPR_SetEosMode
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022088, func_06022088);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60220B4, func_060220B4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60220EC, func_060220EC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022138, func_06022138);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022148, func_06022148);

// _SPR_2Initial
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022164, func_06022164);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022194, func_06022194);

// SPR_2SetTvMode
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022514, func_06022514);

// SPR_2FrameChgIntr
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022588, func_06022588);
// func_060225C4 is SPR_2FrameEraseData, splitter bug
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60225F4, func_060225F4);

// SPR_2SetGourTbl
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602262C, func_0602262C);

// SPR_2SetLookupTbl
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022678, func_06022678);

// SPR_2ClrAllChar
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60226D0, func_060226D0);

// _SPR_2GourTblNoToVram
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022768, func_06022768);

// SPR_2LookupTblNoToVram
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60227AC, func_060227AC);

// SPR_2CharNoToVram
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60227E4, func_060227E4);

// SPR_2GetAreaSizeInfo
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602281C, func_0602281C);

// SPR_2OpenCommand
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602292C, func_0602292C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022A48, func_06022A48);

// _SPR_2FlushDrawPrty
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022C7C, func_06022C7C);

// _SPR_2LocalCoord
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022C9C, func_06022C9C);

// _SPR_2SysClip
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022D28, func_06022D28);

// SPR_2UserClip
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022D98, func_06022D98);

// _SPR_2Cmd
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022E2C, func_06022E2C); // SPR_2Cmd

// _SPR_2FlushDrawPrtyBlock
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022E8C, func_06022E8C);

// SlaveFlushDrawPrtyBlock
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60230B8, func_060230B8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6023108, func_06023108);

// SPR_RunSlaveSH
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6023114, func_06023114);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6023144, func_06023144);

// flushDrawPrtyBlock
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60231C0, func_060231C0);

INCLUDE_ASM("asm/saturn/zero/data", d6023394, d_06023394);

// SEGA_DMA.A

// _DMA_ScuInit
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60234F4, func_060234F4);

// _DMA_ScuMemCopy
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602354C, func_0602354C);

// _DMA_ScuResult - func_0602371C
// splitter bug
INCLUDE_ASM("asm/saturn/zero/data", d602371C, d_0602371C);

// _DMA_ScuStart
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6023950, func_06023950);

// _DMA_ScuGetStatus
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6023A60, func_06023A60);

// _DMA_ScuIntFunc0
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6023AB0, func_06023AB0);

// _DMA_ScuIntFunc1
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6023B54, func_06023B54);

// _DMA_ScuIntFunc2 - splitter bug
INCLUDE_ASM("asm/saturn/zero/data", d6023C00, d_06023C00);

// _DMA_CpuSetPrm
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6023DE0, func_06023DE0);

// _DMA_CpuStart
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6023F88, func_06023F88);

// _DMA_CpuStop
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6023FC8, func_06023FC8);

// _DMA_CpuAllStop
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6024008, func_06024008);

// _DMA_CpuGetComStatus
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602402C, func_0602402C);

// _DMA_CpuGetStatus
INCLUDE_ASM("asm/saturn/zero/data", d6024058, d_6024058);

// SEGA_SCL.A

// _SCL_Open
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6024444, func_06024444);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6024474, func_06024474);

// _SCL_MoveTo
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6024494, func_06024494);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602465C, func_0602465C);

// _SCL_CopyReg
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6024848, func_06024848);

// _SCL_ScrollShow
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6024A48, func_06024A48);

// _SCL_Memcpyw
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6024B20, func_06024B20);

// _SCL_SetColRamMode
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6024B84, func_06024B84);

// _SCL_PriIntProc
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6024C20, func_06024C20);

// _SCL_SetFrameInterval
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6024DB4, func_06024DB4);

// _SCL_DisplayFrame
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6024EC0, func_06024EC0);

// _SCL_VblInit
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6024F08, func_06024F08);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6024F64, func_06024F64);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6025074, func_06025074);

// _SCL_PriorityInit
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6025174, func_06025174);

// _SCL_GetColRamMode
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6025214, func_06025214);

// _SCL_AbortAutoVe
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6025244, func_06025244);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602525C, func_0602525C);

// _SCL_AutoExec
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6025AE4, func_06025AE4);

// _SCL_IncColOffset
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60263E0, func_060263E0);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6026534, func_06026534);

// _SCL_InitSclSpPriNum
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6026C30, func_06026C30);

// _SCL_InitSclBgPriNum
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6026D3C, func_06026D3C);

// _SCL_InitSclSpColMix
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6026DF0, func_06026DF0);

// _SCL_InitSclBgColMix
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6026EEC, func_06026EEC);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6026FC4, func_06026FC4);

// _SCL_SetShadowBit
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60271F0, func_060271F0);

// _SCL_SetDisplayMode
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60274C0, func_060274C0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60277D8, func_060277D8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6027B74, func_06027B74);

// _SCL_SetVramConfig
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6027BD8, func_06027BD8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6028548, func_06028548);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6028614, func_06028614);

// _SCL_SetColMixMode
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6028978, func_06028978);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6028A00, func_06028A00);

// _SCL_EnableLineCol
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6028BE4, func_06028BE4);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6028C0C, func_06028C0C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6028C34, func_06028C34);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6028D10, func_06028D10);
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/f_nonmat", f602915A, func_0602915A);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602A654, func_0602A654);

// _SCL_FreeColRam
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602A6DC, func_0602A6DC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602A778, func_0602A778);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602A964, func_0602A964);

// _Fcos
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602AA84, func_0602AA84);

INCLUDE_ASM("asm/saturn/zero/data", d602AB9C, d_0602AB9C);

// SEGA_CSH.A

// _CSH_Init
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602B9B4, func_0602B9B4);
// _CSH_AllClr
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602BA94, func_0602BA94);
// _CSH_Purge
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602BB3C, func_0602BB3C);

INCLUDE_ASM("asm/saturn/zero/data", d602bb98, d_0602bb98);

// SEGA_PER.A

//_JudgeOreg
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602CC0C, func_0602CC0C);

//_MoveBdryData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602CC48, func_0602CC48);

//_SetPerData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602CCC0, func_0602CCC0);

//_InitIntBackPer
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602CD44, func_0602CD44);

//_GoIntBack
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602CE04, func_0602CE04);

//_AnyInitPerData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602CE90, func_0602CE90);

//_SetPerId
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602CF10, func_0602CF10);

//_SetPerSize
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602CF4C, func_0602CF4C);

//_MoveOldToNew
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602CF8C, func_0602CF8C);

INCLUDE_ASM("asm/saturn/zero/data", d602D008, d_0602D008);

// SEGA_CDC.A

// _CDC_CdScan
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602D660, func_0602D660);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602D6BC, func_0602D6BC);

// _CDC_MpGetLastStat
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602D724, func_0602D724);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602D754, func_0602D754);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602D7CC, func_0602D7CC);

// _CDC_GetHwInfo
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602D86C, func_0602D86C);

// _CDC_TgetToc
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602D90C, func_0602D90C);

// _CDC_GetSes
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602D98C, func_0602D98C);

// _CDC_CdInit
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602D9FC, func_0602D9FC);

// _CDC_CdOpen
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DAD4, func_0602DAD4);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DB1C, func_0602DB1C);

// _CDC_DataEnd
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DBA4, func_0602DBA4);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DC14, func_0602DC14);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DC4C, func_0602DC4C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DC98, func_0602DC98);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DCA8, func_0602DCA8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DCE4, func_0602DCE4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DCFC, func_0602DCFC);

// _CDC_ClrHirqReq
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DD18, func_0602DD18);

// _CDREG_ClrHirqReq
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DD60, func_0602DD60);

// _CDREG_InitHirqReq
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DD88, func_0602DD88);

// _CDREG_SetHirqFlag
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DDBC, func_0602DDBC);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DDE8, func_0602DDE8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DE04, func_0602DE04);

// _CDC_GetMpegPtr
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DE2C, func_0602DE2C);

// _CDREG_TgetData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DE44, func_0602DE44);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DEDC, func_0602DEDC);

// _doCmdRsp
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DF38, func_0602DF38);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E044, func_0602E044);

// _writeCmd
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E0A8, func_0602E0A8);

// _CDREG_ReadRsp
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E0FC, func_0602E0FC);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E150, func_0602E150);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E188, func_0602E188);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E1D4, func_0602E1D4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E1E4, func_0602E1E4);

// _CDC_ChgDir
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E200, func_0602E200);

// _CDC_ReadDir
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E268, func_0602E268);

// _CDC_GetFileScope
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E2D0, func_0602E2D0);

// _CDC_TgetFileInfo
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E354, func_0602E354);

// _CDC_ReadFile
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E3E8, func_0602E3E8);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E458, func_0602E458);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E4B4, func_0602E4B4);

// _CDC_GetSctData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E520, func_0602E520);

// _CDC_DelSctData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E5A4, func_0602E5A4);

// _CDC_GetdelSctData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E628, func_0602E628);

// _CDC_PutSctData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E6AC, func_0602E6AC);

// _CDC_CopySctData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E71C, func_0602E71C);

// _CDC_MoveSctData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E7B0, func_0602E7B0);

// _CDC_GetCopyErr
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E844, func_0602E844);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E8A8, func_0602E8A8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E914, func_0602E914);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E998, func_0602E998);

// _CDC_GetFiltSubh
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602EA50, func_0602EA50);

// _CDC_SetFiltMode
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602EB14, func_0602EB14);

// _CDC_GetFiltMode
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602EB80, func_0602EB80);

// _CDC_SetFiltCon
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602EBF4, func_0602EBF4);

// _CDC_GetFiltCon
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602EC84, func_0602EC84);

// _CDC_ResetSelector
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602ED08, func_0602ED08);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602ED74, func_0602ED74);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602EDF8, func_0602EDF8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602EE6C, func_0602EE6C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602EEEC, func_0602EEEC);

// _chkEselUpdStatus
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602EF50, func_0602EF50);

// _CDC_GetSctInfo
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602EFA4, func_0602EFA4);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602F06C, func_0602F06C);

// _CDC_GetFadSearch
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602F0E0, func_0602F0E0);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602F164, func_0602F164);

// _CDC_CdGetCon
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602F1C0, func_0602F1C0);

// _CDC_CdGetLastBuf
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602F224, func_0602F224);

// _CDC_MpSetImgPos
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602F288, func_0602F288);

// _CDMSB_UpdMpstat
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602F2C4, func_0602F2C4);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602F300, func_0602F300);

// _CDSUB_GetCdstat
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602F398, func_0602F398);

// _CDSUB_RspToCdstat
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602F3FC, func_0602F3FC);

// _CDSUB_SoftTimer
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602F46C, func_0602F46C);

INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/data", d602F49E, d_0602F49E);

// SEGA_MTH.A
// _MTH_MoveMatrix (hasm)
INCLUDE_ASM("asm/saturn/zero/data", d602F638, d_0602F638);

// _MTH_RotateMatrixX (hasm)
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/data", d602F692, d_0602F692);

INCLUDE_ASM("asm/saturn/zero/data", d602F758, d_0602F758);

// _MTH_RotateMatrixZ (hasm)
INCLUDE_ASM("asm/saturn/zero/data", d602F83C, d_0602F83C);
INCLUDE_ASM("asm/saturn/zero/data", d602F90C, d_0602F90C);

// _MTH_MulMatrix (hasm)
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/data", d602F922, d_0602F922);

// _MTH_CoordTrans (hasm)
INCLUDE_ASM("asm/saturn/zero/data", d602FA5C, d_0602FA5C);

// _MTH_NormalTrans (hasm)
INCLUDE_ASM("asm/saturn/zero/data", d602FAA8, d_0602FAA8);

INCLUDE_ASM("asm/saturn/zero/data", d602FAEC, d_0602FAEC);

// _MTH_ComputeBright (hasm)
INCLUDE_ASM("asm/saturn/zero/data", d602FB5C, d_0602FB5C);

INCLUDE_ASM("asm/saturn/zero/data", d602FB84, d_0602FB84);

// _MTH_Hypot (C)
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030228, func_06030228);

// _INT_SetScuFunc
INCLUDE_ASM("asm/saturn/zero/data", d6030388, d_06030388);

// SEGA_BUP.A
const char* bup_version = "BUP Version 1.25 1997-06-20";
const u32 pad_06030400 = 0x00000000;
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030404, func_06030404); // BUP_Init
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030478, func_06030478); // preProc
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60304CC, func_060304CC); // postProc

// change_dfunc
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030518, func_06030518);
// return_dfunc
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030554, func_06030554);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030580, func_06030580); // dummy_func
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f603058C, func_0603058C); // isConSeri

// _BUP_SelPart
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60305CC, func_060305CC);

// _BUP_Format
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030640, func_06030640);

// _BUP_Stat
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030690, func_06030690);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60306EC, func_060306EC); // BUP_Write
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030768, func_06030768); // BUP_Read
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60307C4, func_060307C4); // BUP_Delete
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f603081C, func_0603081C); // BUP_Dir

// _BUP_Verify
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030898, func_06030898);

// _BUP_GetDate
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60308F4, func_060308F4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030968, func_06030968); // BUP_SetDate
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f603099C, func_0603099C); // get_imask
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60309D4, func_060309D4); // set_imask
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030A20, func_06030A20); // set_sr
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030A30, func_06030A30); // get_sr

INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/data", d6030A4A, d_6030A4A);

// SEGA_SYS.A
const char* sys_version = "SYS Version 2.50 1997-06-10";
const u32 pad_06030af8 = 0x00000000;

// _SYS_SetUintMacSave
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030AFC, func_06030AFC);

// _SYS_GetUintMacSave
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030B88, func_06030B88);

INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/data", d6030BF4, d_6030BF4);
