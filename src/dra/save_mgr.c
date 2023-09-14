#include "dra.h"
#include "memcard.h"

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
    } else if (D_80137470-- < 0) {
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
    while (true) {
        if (TestEvent(g_EvHwCardEnd) == 1) {
            return 1;
        } else if (TestEvent(g_EvHwCardErr) == 1) {
            return 2;
        } else if (TestEvent(g_EvHwCardTmo) == 1) {
            return 3;
        } else if (TestEvent(g_EvHwCardNew) == 1) {
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

void MemcardInit(void) { g_MemcardStep = 0; }

void MemcardInfoInit(void) {
    g_MemcardInfo[0].nBlockUsed = 0;
    g_MemcardInfo[1].nBlockUsed = 0;
}

s32 MemcardParse(s32 port, s32 port_s) {
    char cardName[32];
    struct DIRENTRY* dirent;
    s32 totalEntrySize;
    s32 i;

    if (g_MemcardStep == 0) {
        sprintf(cardName, g_strMemcardRootPath, port, port_s);
        dirent = &g_MemcardInfo[port].entries;
        g_MemcardBlockRead = 0;
        if (firstfile(cardName, dirent) == dirent) {
            g_MemcardBlockRead++;
            g_MemcardStep++;
            return -1;
        } else {
            g_MemcardStep = 2;
            return -1;
        }
    } else {
        if (g_MemcardStep == 1) {
            dirent = &g_MemcardInfo[port].entries[g_MemcardBlockRead];
            if (nextfile(dirent) == dirent) {
                g_MemcardBlockRead++;
                return -1;
            } else {
                g_MemcardStep++;
            }
        } else {
            g_MemcardInfo[port].nBlockUsed = g_MemcardBlockRead;
            dirent = &g_MemcardInfo[port].entries;
            totalEntrySize = 0;
            for (i = 0; i < g_MemcardBlockRead; i++) {
                totalEntrySize += dirent[i].size;
            }

            totalEntrySize /= CARD_BLOCK_SIZE;
            g_MemcardInfo[port].nFreeBlock = BLOCK_PER_CARD - totalEntrySize;
            do {
                if (g_MemcardInfo[port].nFreeBlock <= 0) {
                    return 0;
                }
            } while (0);
            return g_MemcardInfo[port].nFreeBlock;
        }
    }
    return -1;
}

s32 GetMemcardFreeBlockCount(s32 port) {
    return g_MemcardInfo[port].nFreeBlock;
}

INCLUDE_ASM("dra/nonmatchings/save_mgr", func_800E9530);

u8 IsMemcardBlockUsed(u32 port, u32 block) {
    return g_MemcardInfo[port].blocks[block];
}

s32 MemcardReadFile(
    s32 port, s32 port_s, const char* name, void* data, s32 nBlock) {
    char savePath[32];
    s32 fd;
    s32 nBytes;

    sprintf(savePath, g_MemcardSavePath, port, port_s, name);
    if (nBlock == 0) {
        nBytes = 0x2B8;
    } else {
        nBytes = nBlock * CARD_BLOCK_SIZE;
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
    s32 port, s32 port_s, const char* name, void* data, s32 flags, s32 create) {
    char savePath[32];
    s32 len;
    s32 fd;

    sprintf(savePath, &g_MemcardSavePath, port, port_s, name);

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

s32 MemcardEraseFile(s32 port, s32 port_s, const char* name) {
    char savePath[0x20];

    sprintf(savePath, g_MemcardSavePath, port, port_s, name);
    return -(erase(savePath) == 0);
}

s32 MemcardClose(s32 port) {
    s32 eventStep = _peek_event();

    if (eventStep == 0) {
        return 0;
    }

    close(g_MemcardFd);
    if (eventStep != 1) {
        return -3;
    }

    D_8006C3AC |= eventStep << port;
    return 1;
}
