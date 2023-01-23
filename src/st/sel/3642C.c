#include "sel.h"

void func_801B642C(void) {
    D_801BC360 = 2;
    D_801BC35E = 2;
    D_801BC362 = 0;
    D_801BC366 = 0;
    D_801BC36A = 0;
    D_801BC36B = 8;
    D_801BC35A = D_801BC35C + 0x14;
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/3642C", func_801B6480);

void func_801B6648(s16 yOffset) {
    RECT rect;

    rect.y = (yOffset * 12) + 384;
    rect.w = 64;
    rect.x = 0;
    rect.h = 12;
    ClearImage(&rect, 0, 0, 0);
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/3642C", func_801B66A4);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/3642C", func_801B675C);

void func_801B68E0(s32 arg0) {
    D_801BC394 = arg0 + 0x100000;
    D_801BC392 = 0;
    D_801BC390 = 1;
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/3642C", func_801B690C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/3642C", func_801B69F8);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/3642C", func_801B76F0);

void func_801B786C(s16 arg0) {
    RECT rect;
    rect.x = 0x200;
    rect.y = arg0 * 16;
    rect.w = 0x80;
    rect.h = 0x10;

    ClearImage(&rect, 0, 0, 0);
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/3642C", func_801B78BC);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/3642C", func_801B79D4);

void func_801B80F0(void) {
    EnterCriticalSection();
    D_80073068 = OpenEvent(SwCARD, EvSpIOE, EvMdNOINTR, NULL);
    D_8007306C = OpenEvent(SwCARD, EvSpERROR, EvMdNOINTR, NULL);
    D_80073070 = OpenEvent(SwCARD, EvSpTIMOUT, EvMdNOINTR, NULL);
    D_80073078 = OpenEvent(SwCARD, EvSpNEW, EvMdNOINTR, NULL);
    D_8007EFD8 = OpenEvent(HwCARD, EvSpIOE, EvMdNOINTR, NULL);
    D_8007EFDC = OpenEvent(HwCARD, EvSpERROR, EvMdNOINTR, NULL);
    D_8007EFE0 = OpenEvent(HwCARD, EvSpTIMOUT, EvMdNOINTR, NULL);
    D_80086FE4 = OpenEvent(HwCARD, EvSpNEW, EvMdNOINTR, NULL);
    ExitCriticalSection();
    EnableEvent(D_80073068);
    EnableEvent(D_8007306C);
    EnableEvent(D_80073070);
    EnableEvent(D_80073078);
    EnableEvent(D_8007EFD8);
    EnableEvent(D_8007EFDC);
    EnableEvent(D_8007EFE0);
    EnableEvent(D_80086FE4);
}

s32 _peek_event_with_retry(void) {
    if (TestEvent(D_80073068) == 1) {
        return 1;
    } else if (TestEvent(D_8007306C) == 1) {
        return 2;
    } else if (TestEvent(D_80073070) == 1) {
        return 3;
    } else if (TestEvent(D_80073078) == 1) {
        return 4;
    } else if (D_801BC2F8-- < 0) {
        return 2;
    }
    return 0;
}

s32 _peek_event(void) {
    if (TestEvent(D_80073068) == 1) {
        return 1;
    } else if (TestEvent(D_8007306C) == 1) {
        return 2;
    } else if (TestEvent(D_80073070) == 1) {
        return 3;
    } else if (TestEvent(D_80073078) == 1) {
        return 4;
    }
    return 0;
}

void _clear_event(void) {
    TestEvent(D_80073068);
    TestEvent(D_8007306C);
    TestEvent(D_80073070);
    TestEvent(D_80073078);
}

s32 _card_event_x(void) {
    while (1) {
        if (TestEvent(D_8007EFD8) == 1) {
            return 1;
        } else if (TestEvent((u32)D_8007EFDC) == 1) {
            return 2;
        } else if (TestEvent((u32)D_8007EFE0) == 1) {
            return 3;
        } else if (TestEvent((u32)D_80086FE4) == 1) {
            return 4;
        }
    }
}

void _clear_event_x(void) {
    TestEvent(D_8007EFD8);
    TestEvent(D_8007EFDC);
    TestEvent(D_8007EFE0);
    TestEvent(D_80086FE4);
}

void func_801B84F0(void) { D_801D6B20 = 0; }

void func_801B8500(void) {
    D_801BC650 = 0;
    D_801BC8C8 = 0;
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/3642C", func_801B8518);

s32 func_801B8714(s32 arg0) { return D_801BC654[arg0 * 0x9E]; }

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/3642C", func_801B873C);

#ifndef NON_MATCHING
INCLUDE_ASM("config/../asm/st/sel/nonmatchings/3642C", func_801B881C);
#else
extern volatile u8 D_801BC658[];
u8 func_801B881C(s32 arg0, s32 arg1) {
    s32 idx = arg0 * 0x9E * 4;
    return D_801BC658[idx + arg1];
}
#endif

s32 func_801B884C(s32 cardSlot, s32 cardSubSlot, const char* saveFile,
                  void* saveData, s32 saveLen) {
    char savePath[32];
    s32 fd;
    s32 actualSaveLen;

    sprintf(savePath, D_801A7D84, cardSlot, cardSubSlot, saveFile);
    if (saveLen == 0) {
        actualSaveLen = 0x2B8;
    } else {
        actualSaveLen = saveLen * 0x2000;
    }

    fd = open(savePath, O_RDONLY | O_NOWAIT);
    if (fd == -1) {
        return -1;
    }

    D_801BC2FC = fd;
    _clear_event();
    read(fd, saveData, actualSaveLen);
    return 0;
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/3642C", func_801B88F4);

s32 func_801B89C8(s32 cardSlot, s32 cardBlock, const char* path) {
    char buf[0x20];
    sprintf(buf, D_801A7D84, cardSlot, cardBlock, path);
    return -(erase(buf) == 0);
}

s32 func_801B8A10(s32 nCardSlot) {
    s32 unk = _peek_event();

    if (unk == 0) {
        return 0;
    }

    close(D_801BC2FC);
    if (unk != 1) {
        return -3;
    }

    D_8006C3AC |= unk << nCardSlot;
    return 1;
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/3642C", func_801B8A8C);

s32 func_801B8D24(s32 cardSlot, s32 cardSubSlot);
#ifndef NON_MATCHING
INCLUDE_ASM("config/../asm/st/sel/nonmatchings/3642C", func_801B8D24);
#else
s32 func_801B8D24(s32 cardSlot, s32 cardSubSlot) {
    s8 cardPath[0x8];
    s32 ret;

    D_8006C3AC &= D_801808DC[cardSlot];
    sprintf(cardPath, D_801A7D78, cardSlot, cardSubSlot);
    _clear_event_x();
    format(cardPath);

    ret = _card_event_x();
    if (ret != 1) {
        if (ret == 3) {
            return -1;
        }
        return -3;
    }
    return ret;
}
#endif

void func_801B8DB0(u16* arg0, s32 arg1) {
    s32 i;
    u16* var_v1;

    var_v1 = &(D_801808E4 - 1)[arg1 * 0x10]; // FAKE
    var_v1++;
    for (i = 0; i < 0x10; i++)
        *arg0++ = *var_v1++;
}

void func_801B8DE8(u8* dst, s32 arg1) {
    s32 i;
    u8* src = (u8*)D_801822E4[arg1];

    for (i = 0; i < 0x180; i++) {
        *dst++ = *src++;
    }
}

void StoreSaveData(SaveData* save, s32 arg1, s32 arg2);
INCLUDE_ASM("config/../asm/st/sel/nonmatchings/3642C", StoreSaveData);

s32 LoadSaveData(SaveData* save); // LoadSaveData
INCLUDE_ASM("config/../asm/st/sel/nonmatchings/3642C", LoadSaveData);

void func_801B9698(char* dstSaveName, s32 saveSlot);
#ifndef NON_MATCHING
INCLUDE_ASM("config/../asm/st/sel/nonmatchings/3642C", func_801B9698);
#else
void func_801B9698(char* dstSaveName, s32 saveSlot) {
    strncpy(dstSaveName, D_801A802C, sizeof(D_801A802C));
    dstSaveName[0x10] += saveSlot / 10;
    dstSaveName[0x11] += saveSlot % 10;
}
#endif

s32 func_801B9744(void) {
    u8 res;

    if (CdSync(1, &res) == 0) {
        D_801BC344 = 0;
        return 0;
    }

    if (func_80019444() - 0x10 < 2U || !(res & 0x10)) {
        CdControlF(1, NULL);
        D_801BC344 = 0;
        return 0;
    }

    D_801BC344 = 1;
    return 1;
}

s32 func_801B97BC(s32*);
INCLUDE_ASM("config/../asm/st/sel/nonmatchings/3642C", func_801B97BC);

void func_801B988C(u32* arg0) {
    s32 temp_v0;
    s32 var_s0;

    var_s0 = 4;
loop_1:
    temp_v0 = func_801B97BC(arg0);
    if (temp_v0 == 0) {
        var_s0 -= 1;
        if (var_s0 != 0) {
            goto loop_1;
        }
    } else {
        s32 temp_v0_2 = arg0[2] == 0;
        arg0[2] = temp_v0_2;
        D_801BC340++;
        func_801BABA4(temp_v0, *((temp_v0_2) + arg0));
        func_8001C550(temp_v0);
    }
}

void func_801B9924(void) {
    volatile u32 pad[4]; // FAKE
    SetDispMask(0);
    func_801B18F4();
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/3642C", func_801B994C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/3642C", func_801B99E4);

// func_801B9B7C(Unkstruct_801B9B7C* arg0, s16 arg1, s16 arg2, s16 arg3, s32
// arg4);
INCLUDE_ASM("config/../asm/st/sel/nonmatchings/3642C", func_801B9B7C);

void func_801B9C18(s32 unused, void (*callback)()) {
    s32* s0 = D_801BD044;
    func_801BA460(0);
    *s0 = 0;
    func_801BA6CC(callback);
    func_800192DC((s32)(s0 + 2), 0x28);
    StSetStream(D_801BD038, 1, -1, NULL, NULL);
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/3642C", func_801B9C80);

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

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/3642C", MDEC_rest);

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

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/3642C", MDEC_in_sync);

#ifndef NON_MATCHING
INCLUDE_ASM("config/../asm/st/sel/nonmatchings/3642C", MDEC_out_sync);
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

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/3642C", MDEC_print_error);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/3642C", func_801BAB70);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/3642C", func_801BABA4);
