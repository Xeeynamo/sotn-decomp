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

INCLUDE_ASM("asm/us/st/sel/nonmatchings/3642C", func_801B6480);

void func_801B6648(s16 yOffset) {
    RECT rect;

    rect.y = (yOffset * 12) + 384;
    rect.w = 64;
    rect.x = 0;
    rect.h = 12;
    ClearImage(&rect, 0, 0, 0);
}

INCLUDE_ASM("asm/us/st/sel/nonmatchings/3642C", func_801B66A4);

INCLUDE_ASM("asm/us/st/sel/nonmatchings/3642C", func_801B675C);

void func_801B68E0(s32 arg0) {
    D_801BC394 = arg0 + 0x100000;
    D_801BC392 = 0;
    D_801BC390 = 1;
}

INCLUDE_ASM("asm/us/st/sel/nonmatchings/3642C", func_801B690C);

INCLUDE_ASM("asm/us/st/sel/nonmatchings/3642C", func_801B69F8);

INCLUDE_ASM("asm/us/st/sel/nonmatchings/3642C", func_801B76F0);

void func_801B786C(s16 arg0) {
    RECT rect;
    rect.x = 0x200;
    rect.y = arg0 * 16;
    rect.w = 0x80;
    rect.h = 0x10;

    ClearImage(&rect, 0, 0, 0);
}

INCLUDE_ASM("asm/us/st/sel/nonmatchings/3642C", func_801B78BC);

INCLUDE_ASM("asm/us/st/sel/nonmatchings/3642C", func_801B79D4);

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

INCLUDE_ASM("asm/us/st/sel/nonmatchings/3642C", func_801B8518);

s32 func_801B8714(s32 arg0) { return D_801BC654[arg0 * 0x9E]; }

INCLUDE_ASM("asm/us/st/sel/nonmatchings/3642C", func_801B873C);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/st/sel/nonmatchings/3642C", func_801B881C);
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

    sprintf(savePath, g_MemcardSavePath, cardSlot, cardSubSlot, saveFile);
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

s32 func_801B88F4(s32 arg0, s32 arg1, s32 arg2, void* arg3, s32 arg4,
                  s32 arg5) {
    s8 savePath[32];
    s32 new_var;
    s32 device;

    sprintf(savePath, &g_MemcardSavePath, arg0, arg1, arg2);

    if (arg5 == 1) {
        device = open(savePath, (arg4 << 0x10) | 0x200);
        if (device == -1) {
            return -2;
        } else {
            close(device);
        }
    }

    new_var = arg4 << 0xD;
    device = open(savePath, 0x8002);

    if (device == (-1)) {
        return -1;
    } else {
        D_801BC2FC = device;
        _clear_event();
        write(device, arg3, new_var);
    }
    return 0;
}

s32 func_801B89C8(s32 cardSlot, s32 cardBlock, const char* path) {
    char buf[0x20];
    sprintf(buf, g_MemcardSavePath, cardSlot, cardBlock, path);
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
