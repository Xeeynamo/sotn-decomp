#include "sel.h"

extern s32 g_StreamWidth;
extern int g_StreamHeight;
extern u32 g_StreamEndFrame;
extern u32 g_StreamIsRGB24;
extern s32 g_StreamRewindSwitch[];

typedef struct {
    u_long* vlcbuf[2];
    int vlcid;
    u_short* imgbuf[2];
    int imgid;
    RECT rect[2];
    int rectid;
    RECT slice;
    int isdone;
} DECENV;

s32 func_801B9744(void) {
    u8 res;
    int ret;

    if (CdSync(1, &res) == CdlNoIntr) {
        return D_801BC344 = 0;
    }

    ret = CdLastCom();
    if (ret >= CdlGetlocL && ret <= CdlGetlocP || !(res & CdlStatShellOpen)) {
        CdControlF(1, NULL);
        return D_801BC344 = 0;
    }

    return D_801BC344 = 1;
}

u_long* StreamNext(DECENV* dec) {
    u_long* addr;
    StHEADER* sector;
    int* rewindSwitch;
    int count;

    count = 0x40000;
    while (StGetNext(&addr, &sector)) {
        if (--count == 0) {
            dec->isdone = 1;
            return 0;
        }
    }

    rewindSwitch = g_StreamRewindSwitch;
    if (sector->frameCount >= g_StreamEndFrame) {
        *rewindSwitch = 1;
    }

    g_StreamWidth = sector->width;
    g_StreamHeight = sector->height;
    dec->rect[0].w = dec->rect[1].w = count = g_StreamWidth * 3 / 2;
    dec->rect[0].h = dec->rect[1].h = g_StreamHeight;
    dec->slice.h = g_StreamHeight;
    return addr;
}

void StreamNextVlc(DECENV* dec) {
    const int WAIT_TIME = 4;
    int count = WAIT_TIME;
    u_long* next;

    while ((next = StreamNext(dec)) == 0) {
        if (--count == 0)
            return;
    }

    D_801BC340++;
    dec->vlcid = dec->vlcid ? 0 : 1;
    DecDCTvlc(next, dec->vlcbuf[dec->vlcid]);
    StFreeRing(next);
}

void func_801B9924(void) {
    volatile u32 pad[4]; // FAKE
    SetDispMask(0);
    func_801B18F4();
}

INCLUDE_ASM("asm/us/st/sel/nonmatchings/stream", func_801B994C);

INCLUDE_ASM("asm/us/st/sel/nonmatchings/stream", func_801B99E4);

// func_801B9B7C(Unkstruct_801B9B7C* arg0, s16 arg1, s16 arg2, s16 arg3, s32
// arg4);
INCLUDE_ASM("asm/us/st/sel/nonmatchings/stream", func_801B9B7C);

void func_801B9C18(s32 unused, void (*callback)()) {
    const int START_FRAME = 1;

    s32* s0 = g_StreamRewindSwitch;
    func_801BA460(0);
    *s0 = 0;
    func_801BA6CC(callback);
    func_800192DC((s32)(s0 + 2), 0x28);
    StSetStream(g_StreamIsRGB24, START_FRAME, -1, NULL, NULL);
}

INCLUDE_ASM("asm/us/st/sel/nonmatchings/stream", func_801B9C80);

void func_801BA460(s32 option) {
    if (option == 0) {
        ResetCallback();
    }

    MDEC_rest(option);
}

s32* func_801BA498(Unkstruct_801BA498* arg0) {
    s32 i;
    s32 *src1, *dst1;
    s32 *src2, *dst2;
    s32 *src3, *dst3;

    dst1 = &arg0->unk00;
    src1 = D_801962F8;
    for (i = 15; i != -1; i--) {
        *dst1++ = *src1++;
    }

    dst2 = &arg0->unk10;
    src2 = D_80196338;
    for (i = 15; i != -1; i--) {
        *dst2++ = *src2++;
    }

    dst3 = &arg0->unk20;
    src3 = D_8019637C;
    for (i = 31; i != -1; i--) {
        *dst3++ = *src3++;
    }

    return arg0;
}

s32* func_801BA524(Unkstruct_801BA498* arg0) {
    s32 i;
    s32 *src1, *dst1;
    s32 *src2, *dst2;

    dst1 = D_801962F8;
    src1 = &arg0->unk00;
    for (i = 15; i != -1; i--) {
        *dst1++ = *src1++;
    }

    dst2 = D_80196338;
    src2 = &arg0->unk10;
    for (i = 15; i != -1; i--) {
        *dst2++ = *src2++;
    }

    func_801BA7EC(&D_801962F4, 0x20);
    func_801BA7EC(&D_80196378, 0x20);

    return arg0;
}

u16 func_801BA5C0(u16* arg0) { return *arg0; }

void func_801BA5CC(s32* arg0, s32 arg1) {
    s32 new_var2;
    s32 var_v0;
    s32 var_v0_2;

    if (arg1 & 1) {
        var_v0 = (*arg0) & 0xF7FFFFFF;
    } else {
        new_var2 = 0x08000000;
        var_v0 = 0x08000000;
        var_v0 = (*arg0) | var_v0;
    }

    *arg0 = var_v0;
    var_v0 = 0x02000000;
    if (arg1 & 2) {
        new_var2 = var_v0;
        var_v0_2 = (*arg0) | new_var2;
    } else {
        var_v0_2 = (*arg0) & 0xFDFFFFFF;
    }

    *arg0 = var_v0_2;
    func_801BA7EC(arg0, *(u16*)arg0);
}

void func_801BA648(s32 arg0, u32 arg1) { func_801BA880(arg0, arg1); }

void func_801BA668(void) { MDEC_in_sync(); }

void func_801BA688(void) { MDEC_out_sync(); }

void func_801BA6A8(void (*func)()) { DMACallback(0, func); }

void func_801BA6CC(void (*func)()) { DMACallback(1, func); }

INCLUDE_ASM("asm/us/st/sel/nonmatchings/stream", MDEC_rest);

void func_801BA7EC(s32* arg0, u32 arg1) {
    MDEC_in_sync();
    *D_80196434 |= 0x88;
    *D_801963FC = arg0 + 1;
    *D_80196400 = ((arg1 >> 5) << 0x10) | 0x20;
    *D_8019642C = *arg0;
    *D_80196404 = 0x01000201;
}
void func_801BA880(s32 arg0, u32 arg1) {
    MDEC_out_sync();
    *D_80196434 |= 0x88;
    *D_80196410 = 0;
    *D_80196408 = arg0;
    *D_8019640C = ((arg1 >> 5) << 0x10) | 0x20;
    *D_80196410 = 0x01000200;
}

INCLUDE_ASM("asm/us/st/sel/nonmatchings/stream", MDEC_in_sync);

// missing a return maybe?
#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/st/sel/nonmatchings/stream", MDEC_out_sync);
#else
void MDEC_out_sync(void) {
    volatile s32 sp10 = 0x100000;

    while (*D_80196410 & 0x01000000) {
        if (--sp10 == -1) {
            MDEC_print_error(D_801ABFC8);
            break;
        }
    }
}
#endif

INCLUDE_ASM("asm/us/st/sel/nonmatchings/stream", MDEC_print_error);

INCLUDE_ASM("asm/us/st/sel/nonmatchings/stream", func_801BAB70);

INCLUDE_ASM("asm/us/st/sel/nonmatchings/stream", DecDCTvlc);
