#include "sel.h"

extern Unkstruct_8013B15C D_801BC654[];

void SetupEvents(void) {
    EnterCriticalSection();
    g_EvSwCardEnd = OpenEvent(SwCARD, EvSpIOE, EvMdNOINTR, NULL);
    g_EvSwCardErr = OpenEvent(SwCARD, EvSpERROR, EvMdNOINTR, NULL);
    g_EvSwCardTmo = OpenEvent(SwCARD, EvSpTIMOUT, EvMdNOINTR, NULL);
    g_EvSwCardNew = OpenEvent(SwCARD, EvSpNEW, EvMdNOINTR, NULL);
    g_EvHwCardEnd = OpenEvent(HwCARD, EvSpIOE, EvMdNOINTR, NULL);
    g_EvHwCardErr = OpenEvent(HwCARD, EvSpERROR, EvMdNOINTR, NULL);
    g_EvHwCardTmo = OpenEvent(HwCARD, EvSpTIMOUT, EvMdNOINTR, NULL);
    g_EvHwCardNew = OpenEvent(HwCARD, EvSpNEW, EvMdNOINTR, NULL);
    ExitCriticalSection();
    EnableEvent(g_EvSwCardEnd);
    EnableEvent(g_EvSwCardErr);
    EnableEvent(g_EvSwCardTmo);
    EnableEvent(g_EvSwCardNew);
    EnableEvent(g_EvHwCardEnd);
    EnableEvent(g_EvHwCardErr);
    EnableEvent(g_EvHwCardTmo);
    EnableEvent(g_EvHwCardNew);
}

s32 _peek_event_with_retry(void) {
    if (TestEvent(g_EvSwCardEnd) == 1) {
        return 1;
    } else if (TestEvent(g_EvSwCardErr) == 1) {
        return 2;
    } else if (TestEvent(g_EvSwCardTmo) == 1) {
        return 3;
    } else if (TestEvent(g_EvSwCardNew) == 1) {
        return 4;
    } else if (D_801BC2F8-- < 0) {
        return 2;
    }
    return 0;
}

s32 _peek_event(void) {
    if (TestEvent(g_EvSwCardEnd) == 1) {
        return 1;
    } else if (TestEvent(g_EvSwCardErr) == 1) {
        return 2;
    } else if (TestEvent(g_EvSwCardTmo) == 1) {
        return 3;
    } else if (TestEvent(g_EvSwCardNew) == 1) {
        return 4;
    }
    return 0;
}

void _clear_event(void) {
    TestEvent(g_EvSwCardEnd);
    TestEvent(g_EvSwCardErr);
    TestEvent(g_EvSwCardTmo);
    TestEvent(g_EvSwCardNew);
}

s32 _card_event_x(void) {
    while (1) {
        if (TestEvent(g_EvHwCardEnd) == 1) {
            return 1;
        } else if (TestEvent((u32)g_EvHwCardErr) == 1) {
            return 2;
        } else if (TestEvent((u32)g_EvHwCardTmo) == 1) {
            return 3;
        } else if (TestEvent((u32)g_EvHwCardNew) == 1) {
            return 4;
        }
    }
}

void _clear_event_x(void) {
    TestEvent(g_EvHwCardEnd);
    TestEvent(g_EvHwCardErr);
    TestEvent(g_EvHwCardTmo);
    TestEvent(g_EvHwCardNew);
}

void func_801B84F0(void) { D_801D6B20 = 0; }

void func_801B8500(void) {
    D_801BC650 = 0;
    D_801BC8C8 = 0;
}

INCLUDE_ASM("asm/us/st/sel/nonmatchings/save_mgr", func_801B8518);

s32 func_801B8714(s32 arg0) { return D_801BC654[arg0].unk000; }

INCLUDE_ASM("asm/us/st/sel/nonmatchings/save_mgr", func_801B873C);

u8 func_801B881C(u32 arg0, u32 arg1) { return D_801BC654[arg0].pad004[arg1]; }

s32 MemcardReadFile(
    s32 slot, s32 block, const char* name, void* data, s32 saveLen) {
    char savePath[32];
    s32 fd;
    s32 nBytes;

    sprintf(savePath, g_MemcardSavePath, slot, block, name);
    if (saveLen == 0) {
        nBytes = 0x2B8;
    } else {
        nBytes = saveLen * 0x2000;
    }

    fd = open(savePath, O_RDONLY | O_NOWAIT);
    if (fd == -1) {
        return -1;
    }

    g_MemcardFd = fd;
    _clear_event();
    read(fd, data, nBytes);
    return 0;
}

s32 MemcardWriteFile(
    s32 slot, s32 block, const char* name, void* data, s32 flags, s32 create) {
    s8 savePath[32];
    s32 len;
    s32 fd;

    sprintf(savePath, &g_MemcardSavePath, slot, block, name);

    // known PSX bug: when creating a a file with open(), any read or write
    // will immediately fail. The workaround is to close the file and open
    // it again.
    if (create == 1) {
        fd = open(savePath, (flags << 0x10) | O_CREAT);
        if (fd == -1) {
            return -2;
        } else {
            close(fd);
        }
    }

    len = flags << 0xD;
    fd = open(savePath, O_WRONLY | O_NOWAIT);

    if (fd == -1) {
        return -1;
    } else {
        g_MemcardFd = fd;
        _clear_event();
        write(fd, data, len);
    }
    return 0;
}

s32 MemcardEraseFile(s32 slot, s32 block, const char* name) {
    char savePath[0x20];

    sprintf(savePath, g_MemcardSavePath, slot, block, name);
    return -(erase(savePath) == 0);
}

s32 MemcardClose(s32 nCardSlot) {
    s32 eventStep = _peek_event();

    if (eventStep == 0) {
        return 0;
    }

    close(g_MemcardFd);
    if (eventStep != 1) {
        return -3;
    }

    D_8006C3AC |= eventStep << nCardSlot;
    return 1;
}
