// SPDX-License-Identifier: AGPL-3.0-only
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
    } else if (g_MemcardRetryCount-- < 0) {
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

s32 MemcardParse(s32 nPort, s32 nCard) {
    char cardName[32];
    struct DIRENTRY* dirent;
    s32 totalEntrySize;
    s32 i;

    if (g_MemcardStep == 0) {
        sprintf(cardName, "bu%1d%1d:", nPort, nCard);
        dirent = &g_MemcardInfo[nPort].entries;
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
            dirent = &g_MemcardInfo[nPort].entries[g_MemcardBlockRead];
            if (nextfile(dirent) == dirent) {
                g_MemcardBlockRead++;
                return -1;
            } else {
                g_MemcardStep++;
            }
        } else {
            g_MemcardInfo[nPort].nBlockUsed = g_MemcardBlockRead;
            dirent = &g_MemcardInfo[nPort].entries;
            totalEntrySize = 0;
            for (i = 0; i < g_MemcardBlockRead; i++) {
                totalEntrySize += dirent[i].size;
            }

            totalEntrySize /= CARD_BLOCK_SIZE;
            g_MemcardInfo[nPort].nFreeBlock = BLOCK_PER_CARD - totalEntrySize;
            do {
                if (g_MemcardInfo[nPort].nFreeBlock <= 0) {
                    return 0;
                }
            } while (0);
            return g_MemcardInfo[nPort].nFreeBlock;
        }
    }
    return -1;
}

s32 GetMemcardFreeBlockCount(s32 nPort) {
    return g_MemcardInfo[nPort].nFreeBlock;
}

s32 MemcardDetectSave(s32 nPort, u8* expectedSaveName, s32 block) {
    s32 nBlocks;
    s32 didNotMatch;
    s32 i;
    s32 j;
    s32 isCastlevaniaSave;
    struct DIRENTRY* entries;

    isCastlevaniaSave = 0;
    entries = g_MemcardInfo[nPort].entries;
    nBlocks = g_MemcardInfo[nPort].nBlockUsed;
    for (i = 0; i < nBlocks; i++) {
        didNotMatch = 0;
        for (j = 0; j <= 20; j++) {
            char ch = expectedSaveName[j];
            if (ch != '\0') {
                if (ch != entries[i].name[j]) {
                    didNotMatch++;
                    break;
                }
            } else {
                break;
            }
        }

        if (didNotMatch == 0) {
            isCastlevaniaSave = 1;
            break;
        }
    }

    g_MemcardInfo[nPort].blocks[block] = isCastlevaniaSave;
    return isCastlevaniaSave;
}

u8 IsMemcardBlockUsed(u32 nPort, u32 block) {
    return g_MemcardInfo[nPort].blocks[block];
}

s32 MemcardReadFile(
    s32 nPort, s32 nCard, const char* name, void* data, s32 nBlock) {
    char savePath[32];
    s32 fd;
    s32 nBytes;

    sprintf(savePath, "bu%1d%1d:%s", nPort, nCard, name);
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
    s32 nPort, s32 nCard, const char* name, void* data, s32 flags, s32 create) {
    char savePath[32];
    s32 len;
    s32 fd;

    sprintf(savePath, &"bu%1d%1d:%s", nPort, nCard, name);

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

s32 MemcardEraseFile(s32 nPort, s32 nCard, const char* name) {
    char savePath[0x20];

    sprintf(savePath, "bu%1d%1d:%s", nPort, nCard, name);
    return -(erase(savePath) == 0);
}

s32 MemcardClose(s32 nPort) {
    s32 eventStep = _peek_event();

    if (eventStep == 0) {
        return 0;
    }

    close(g_MemcardFd);
    if (eventStep != 1) {
        return -3;
    }

    D_8006C3AC |= eventStep << nPort;
    return 1;
}

s32 func_800E9880(s32 nPort, s32 nCard) {
    s32 channel;
    MemcardInfo* memcard;
    channel = (nPort * 0x10) + nCard;
    memcard = &g_MemcardInfo[nPort];
    switch (g_MemcardStep) {
    case 0:
        memcard->unk25C = 0;
        g_MemcardRetryCount = 0x80;
        _card_info(channel);
        g_MemcardStep++;
        break;

    case 1:
        switch (_peek_event_with_retry()) {
        case 0:
            break;

        case 1:
            memcard->unk258 = 1;
            g_MemcardStep++;
            break;

        case 3:
            D_8006C3AC &= g_MemcardPortMask[nPort];
            memcard->unk258 = -1;
            g_MemcardStep = 4;
            break;

        case 4:
            D_8006C3AC &= g_MemcardPortMask[nPort];
            memcard->unk258 = 2;
            _clear_event_x();
            _card_clear(channel);
            _card_event_x();
            g_MemcardStep++;
            break;

        case 2:
            D_8006C3AC &= g_MemcardPortMask[nPort];
            memcard->unk258 = -3;
            g_MemcardStep = 4;
            break;
        }

        break;

    case 2:
        _clear_event();
        _card_load(channel);
        g_MemcardRetryCount = 0x80;
        g_MemcardStep++;
        break;

    case 3:
        switch (_peek_event_with_retry()) {
        case 0:
            break;

        case 1:
            g_MemcardStep++;
            break;

        case 3:
            D_8006C3AC &= g_MemcardPortMask[nPort];
            memcard->unk258 = -1;
            g_MemcardStep++;
            break;

        case 4:
            D_8006C3AC &= g_MemcardPortMask[nPort];
            memcard->unk258 = -2;
            g_MemcardStep++;
            break;

        case 2:
            D_8006C3AC &= g_MemcardPortMask[nPort];
            memcard->unk258 = -3;
            g_MemcardStep++;
            break;
        }

        break;

    case 4:
        g_MemcardStep = 0;
        memcard->unk25C = memcard->unk258;
        break;
    }

    return memcard->unk25C;
}

extern u8 g_saveIcon0[];
extern u8 g_saveIcon1[];
extern u8 g_saveIcon2[];
extern u8 g_saveIcon3[];
extern u8 g_saveIcon4[];
extern u8 g_saveIcon5[];
extern u8 g_saveIcon6[];
extern u8 g_saveIcon7[];
extern u8 g_saveIcon8[];
extern u8 g_saveIcon9[];
extern u8 g_saveIcon10[];
extern u8 g_saveIcon11[];
extern u8 g_saveIcon12[];
extern u8 g_saveIcon13[];
extern u8 g_saveIcon14[];
extern u8 g_saveIcon15[];

u8* g_saveIconTexture[] = {
    g_saveIcon0,  g_saveIcon1,  g_saveIcon2,  g_saveIcon3,
    g_saveIcon4,  g_saveIcon5,  g_saveIcon6,  g_saveIcon7,
    g_saveIcon8,  g_saveIcon9,  g_saveIcon10, g_saveIcon11,
    g_saveIcon12, g_saveIcon13, g_saveIcon14, g_saveIcon15,
};

#if defined(VERSION_US)
s32 g_saveUnkData[] = {
    1, 1, 3, 1, 1, 1, 3, 1, 2, 2, 1, 1, 1, 1, 1, 2,
};
#endif

const char* g_saveBlockName[] = {
    "　１", "　２", "　３", "　４", "　５", "　６", "　７", "　８",
    "　９", "１０", "１１", "１２", "１３", "１４", "１５",
};

char g_AsciiSet[] = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',  'j', 'k',
    'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',  'u', 'v',
    'w', 'x', 'y', 'z', '&', '!', '-', '.', '\'', ' ', ' ',
};

const char* g_ShiftJisSet[] = {
    "Ａ", "Ｂ", "Ｃ", "Ｄ", "Ｅ", "Ｆ", "Ｇ", "Ｈ", "Ｉ", "Ｊ", "Ｋ",
    "Ｌ", "Ｍ", "Ｎ", "Ｏ", "Ｐ", "Ｑ", "Ｒ", "Ｓ", "Ｔ", "Ｕ", "Ｖ",
    "Ｗ", "Ｘ", "Ｙ", "Ｚ", "＆", "！", "−",  "．", "’",  "　",
};
const char* g_SaveAreaNames[] = {
    "大理石の廊下",
    "崖側外壁",
    "蔵書庫",
    "地下墓地",
    "オルロックの間",
    "えん道",
    "礼拝堂",
    "城入り口",
    "",
    "地下水脈",
    "闘技場",
    "悪魔城最上部",
    "錬金研究棟",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "卑鉱石の廊下",
    "異界側外壁",
    "禁書保管庫",
    "空中墓地",
    "死翼の間",
    "洞窟",
    "異端礼拝堂",
    "逆さ城入り口",
    "",
    "天井水脈",
    "裏闘技場",
    "逆さ城最下部",
    "黒魔術研究棟",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "城入り口",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
};

s32 MemcardFormat(s32 nPort, s32 nCard) {
    char savePath[0x8];
    s32 ret;

    D_8006C3AC &= g_MemcardPortMask[nPort];
    sprintf(savePath, "bu%1d%1d:", nPort, nCard);
    _clear_event_x();
    format(savePath);
    ret = _card_event_x();

    if (ret != 1) {
        if (ret == 3) {
            ret = -1;
        } else {
            ret = -3;
        }
    }
    return ret;
}

void GetSavePalette(u16* dst, s32 palIdx) {
    s32 i;
    u16* src = g_saveIconPal0[0];

    src = g_saveIconPal0[palIdx];
    for (i = 0; i < COLORS_PER_PAL; i++) {
        *dst++ = *src++;
    }
}

void GetSaveIcon(u8* dst, s32 iconIdx) {
    const s32 IconSize = sizeof(((MemcardHeader*)0)->Icon);
    s32 i;
    u8* src;

    src = g_saveIconTexture[iconIdx];
    for (i = 0; i < IconSize; i++) {
        *dst++ = *src++;
    }
}

void StoreSaveData(SaveData* save, s32 block, s32 cardIcon) {
    const int RoomCount = 942;
    MemcardHeader h;
    char saveTitle[64];

    u32* saveRaw;
    s32 roomPercentage;
    SaveData* dst;
    s32 saveNameLen;
    s32 i;
    s32 j;

    PlayerStatus* dstStatus;
    MenuNavigation* dstNav;
    GameSettings* dstSettings;

    saveRaw = save;
    for (i = 0; i < 0x800; i++) {
        *saveRaw++ = 0;
    }

    h.Magic[0] = 'S';
    h.Magic[1] = 'C';
    h.Type = 0x13;
    h.BlockEntry = 1;

    // The h.Title content will look like this:
    // US: ＣＡＳＴＬＥＶＡＮＩＡ－１１　ＡＬＵＣＡＲＤ　２００％
    // HD: ドラキュラＸ−１１　ＡＬＵＣＡＲＤ　オルロックの間　２００％
    for (i = 0; i < 0x5C; i++) {
        h.Title[i] = 0;
    }

#if defined(VERSION_US)
    STRCPY(h.Title, "ＣＡＳＴＬＥＶＡＮＩＡ−");
#elif defined(VERSION_HD)
    STRCPY(h.Title, "ドラキュラＸ−");
#endif

    // writes slot number
    if (block > 8) {
        STRCPY(saveTitle, "００");
        saveTitle[1] += (block + 1) / 10;
        saveTitle[3] += (block + 1) % 10;
        strcat(h.Title, saveTitle);
    } else {
        STRCPY(saveTitle, "０");
        saveTitle[1] += block + 1;
        strcat(h.Title, saveTitle);
    }

    strcat(h.Title, "　");
    for (saveNameLen = 7; saveNameLen > 0; saveNameLen--) {
        if (g_SaveName[saveNameLen] != 0x20) {
            break;
        }
    }

    // writes save name
    for (i = 0; i < saveNameLen + 1; i++) {
        char ch = g_SaveName[i];
        for (j = 0; j < 0x20; j++) {
            // Converts ASCII into Shift-JIS
            if (ch == g_AsciiSet[j]) {
                strcat(h.Title, g_ShiftJisSet[j]);
                break;
            }
        }
    }

#if defined(VERSION_HD)
    // writes stage name
    strcat(h.Title, "　");
    strcat(h.Title, g_SaveAreaNames[g_StageId]);
#endif

    // writes room completion percentage
    strcat(h.Title, "　");
    i = roomPercentage = g_RoomCount * 100 / RoomCount;
    if (i >= 100) {
        STRCPY(saveTitle, "０００");
        saveTitle[1] += i / 100;
        saveTitle[3] += i / 10 - i / 100 * 10;
        saveTitle[5] += i % 10;
        strcat(h.Title, saveTitle);
    } else if (i >= 10) {
        STRCPY(saveTitle, "００");
        saveTitle[1] += i / 10;
        saveTitle[3] += i % 10;
        strcat(h.Title, saveTitle);
    } else {
        STRCPY(saveTitle, "０");
        saveTitle[1] += i;
        strcat(h.Title, saveTitle);
    }
    strcat(h.Title, "％");

    GetSavePalette(h.Clut, cardIcon);
    GetSaveIcon(h.Icon, cardIcon);

    dst = save;
    dstStatus = &save->status;
    dstNav = &save->menuNavigation;
    dstSettings = &save->settings;
    dst->header = h;
    for (i = 0; i < 10; i++) {
        dst->info.name[i] = g_SaveName[i];
    }

    dst->info.level = g_Status.level;
    dst->info.gold = g_Status.gold;
    dst->info.playHours = g_Status.timerHours;
    dst->info.playMinutes = g_Status.timerMinutes;
    dst->info.playSeconds = g_Status.timerSeconds;
    dst->info.stage = g_StageId;
    dst->info.cardIcon = cardIcon;
    dst->info.endGameFlags = g_IsTimeAttackUnlocked;
    dst->info.character = g_PlayableCharacter;
    dst->info.nRoomsExplored = g_RoomCount;
    dst->info.roomX = g_Tilemap.left;
    dst->info.roomY = g_Tilemap.top;
    dst->info.saveSize = sizeof(SaveData);

    *dstStatus = g_Status;
    *dstNav = g_MenuNavigation;
    *dstSettings = g_Settings;

    for (i = 0; i < LEN(g_CastleFlags); i++) {
        dst->castleFlags[i] = g_CastleFlags[i];
    }

    for (i = 0; i < LEN(g_CastleMap); i++) {
        dst->castleMap[i] = g_CastleMap[i];
    }

    dst->rng = g_randomNext;
}

s32 LoadSaveData(SaveData* save) {
    s32 i;
    u32 prevCompletionFlags1;
    u32 prevCompletionFlags2;
    PlayerStatus* srcStatus;
    MenuNavigation* srcNav;
    GameSettings* settings;

    if (save->info.saveSize != (sizeof(SaveData))) {
        return -1;
    }

    g_StageId = save->info.stage;
    g_IsTimeAttackUnlocked = save->info.endGameFlags;
    g_PlayableCharacter = save->info.character;
    g_RoomCount = save->info.nRoomsExplored;
    g_Tilemap.left = save->info.roomX;
    g_Tilemap.top = save->info.roomY;

    srcStatus = &save->status;
    srcNav = &save->menuNavigation;
    settings = &save->settings;
    __builtin_memcpy(&g_Status, srcStatus, sizeof(g_Status));
    __builtin_memcpy(&g_MenuNavigation, srcNav, sizeof(g_MenuNavigation));

    prevCompletionFlags1 = g_Settings.D_8003CB00;
    prevCompletionFlags2 = g_Settings.D_8003CB04;
    __builtin_memcpy(&g_Settings, settings, sizeof(g_Settings));
    g_Settings.D_8003CB00 |= prevCompletionFlags1;
    g_Settings.D_8003CB04 |= prevCompletionFlags2;

    for (i = 0; i < LEN(g_CastleFlags); i++) {
        g_CastleFlags[i] = save->castleFlags[i];
    }

    for (i = 0; i < LEN(g_CastleMap); i++) {
        g_CastleMap[i] = save->castleMap[i];
    }

    g_randomNext = save->rng;
    return 0;
}

void MakeMemcardPath(char* dstSaveName, s32 block) {
    STRCPY(dstSaveName, MEMCARD_ID);
    dstSaveName[0x10] += block / 10;
    dstSaveName[0x11] += block % 10;
}
