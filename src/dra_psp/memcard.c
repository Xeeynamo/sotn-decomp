// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

extern MemcardInfo g_MemcardInfo[2];

void SetupEvents(void) {}

void MemcardInit(void) { g_MemcardStep = 0; }

void MemcardInfoInit(void) {
    g_MemcardInfo[0].nBlockUsed = 0;
    g_MemcardInfo[1].nBlockUsed = 0;
}

s32 MemcardParse(s32 nPort, s32 nCard) {
    s32 blocksFree = 0;

    if (nPort == 0) {
        // Presumably func_psp_08919278 is something like
        // getNumFreeBlocks, but I don't know the SDK function set.
        blocksFree = func_psp_08919278();
    }
    g_MemcardInfo[nPort].nBlockUsed = BLOCK_PER_CARD - blocksFree;
    g_MemcardInfo[nPort].nFreeBlock = blocksFree;
    return g_MemcardInfo[nPort].nFreeBlock;
}

s32 GetMemcardFreeBlockCount(s32 nPort) {
    return g_MemcardInfo[nPort].nFreeBlock;
}

bool MemcardDetectSave(s32 nPort, u8* expectedSaveName, s32 block) {
    bool isCastlevaniaSave;
    bool found;

    isCastlevaniaSave = false;
    if (nPort == 0) {
        if (func_psp_08919188(expectedSaveName) >= 0) {
            found = true;
        } else {
            found = false;
        }
        isCastlevaniaSave = found;
    }
    g_MemcardInfo[nPort].blocks[block] = isCastlevaniaSave;
    return isCastlevaniaSave;
}

s32 IsMemcardBlockUsed(u32 nPort, u32 block) {
    return g_MemcardInfo[nPort].blocks[block];
}

s32 MemcardReadFile(s32 nPort, s32 nCard, char* name, void* data, s32 nblock) {
    s32 len;
    s32 ret;

    if (nPort != 0) {
        return -1;
    }
    if (nCard != 0) {
        return -1;
    }
    len = nblock * CARD_BLOCK_SIZE;
    if (nblock == 0) {
        len = 0x238;
    }
    if (func_psp_089194E4(data, name, len) > 0) {
        ret = 0;
    } else {
        ret = -1;
    }
    return ret;
}

s32 MemcardWriteFile(s32 nPort, s32 nCard, const char* name, void* data,
                     s32 flags, s32 unused, s32 create) {
    s32 ret;

    if (nPort != 0) {
        return -2;
    }
    if (nCard != 0) {
        return -2;
    }
    if (func_psp_089193D4(data, name, flags << 0xD, create) > 0) {
        ret = 0;
    } else {
        ret = -1;
    }
    return ret;
}

s32 MemcardEraseFile(s32 nPort, s32 nCard, const char* name, s32 arg3) {
    if (nPort != 0) {
        return -1;
    }
    if (nCard != 0) {
        return -1;
    }
    return func_psp_089192EC(name, arg3);
}

s32 MemcardClose(s32 nPort) { return 1; }

s32 func_800E9880(s32 nPort, s32 nCard) {
    if ((nPort != 0) || (nCard != 0)) {
        return -1;
    }
    switch (func_psp_08919770(4)) {
    case 2:
        return -1;
    }
    return 1;
}

u16 g_saveIconPal[] = {
#include "../dra/gen/g_saveIconPal.h"
};

void GetSavePalette(u8* dst, s32 palIdx) {
    u16* dst_u16 = (u16*)dst;
    s32 i;
    u16* src = g_saveIconPal;

    src += palIdx * 16;
    for (i = 0; i < COLORS_PER_PAL; i++) {
        *dst_u16++ = *src++;
    }
}

u8 g_saveIcon0[] = {
#include "../dra/gen/psp/g_saveIcon0.h"
};

u8 g_saveIcon1[] = {
#include "../dra/gen/psp/g_saveIcon1.h"
};

u8 g_saveIcon2[] = {
#include "../dra/gen/psp/g_saveIcon2.h"
};

u8 g_saveIcon3[] = {
#include "../dra/gen/psp/g_saveIcon3.h"
};

u8 g_saveIcon4[] = {
#include "../dra/gen/psp/g_saveIcon4.h"
};

u8 g_saveIcon5[] = {
#include "../dra/gen/psp/g_saveIcon5.h"
};

u8 g_saveIcon6[] = {
#include "../dra/gen/psp/g_saveIcon6.h"
};

u8 g_saveIcon7[] = {
#include "../dra/gen/psp/g_saveIcon7.h"
};

u8 g_saveIcon8[] = {
#include "../dra/gen/psp/g_saveIcon8.h"
};

u8 g_saveIcon9[] = {
#include "../dra/gen/psp/g_saveIcon9.h"
};

u8 g_saveIcon10[] = {
#include "../dra/gen/psp/g_saveIcon10.h"
};

u8 g_saveIcon11[] = {
#include "../dra/gen/psp/g_saveIcon11.h"
};

u8 g_saveIcon12[] = {
#include "../dra/gen/psp/g_saveIcon12.h"
};

u8 g_saveIcon13[] = {
#include "../dra/gen/psp/g_saveIcon13.h"
};

u8 g_saveIcon14[] = {
#include "../dra/gen/psp/g_saveIcon14.h"
};

u8 g_saveIcon15[] = {
#include "../dra/gen/psp/g_saveIcon15.h"
};

u8* g_saveIconTexture[] = {
    g_saveIcon0,  g_saveIcon1,  g_saveIcon2,  g_saveIcon3,
    g_saveIcon4,  g_saveIcon5,  g_saveIcon6,  g_saveIcon7,
    g_saveIcon8,  g_saveIcon9,  g_saveIcon10, g_saveIcon11,
    g_saveIcon12, g_saveIcon13, g_saveIcon14, g_saveIcon15,
};

void GetSaveIcon(u8* dst, s32 iconIdx) {
    const s32 IconSize = sizeof(((MemcardHeader*)0)->Icon);
    s32 i;
    u8* src;

    src = g_saveIconTexture[iconIdx];
    for (i = 0; i < IconSize; i++) {
        *dst++ = *src++;
    }
}

char g_AsciiSet[] = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',  'j', 'k',
    'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',  'u', 'v',
    'w', 'x', 'y', 'z', '&', '!', '-', '.', '\'', ' ', ' ',
};

char* g_ShiftJisSet[] = {
    "Ａ", "Ｂ", "Ｃ", "Ｄ", "Ｅ", "Ｆ", "Ｇ", "Ｈ", "Ｉ", "Ｊ", "Ｋ",
    "Ｌ", "Ｍ", "Ｎ", "Ｏ", "Ｐ", "Ｑ", "Ｒ", "Ｓ", "Ｔ", "Ｕ", "Ｖ",
    "Ｗ", "Ｘ", "Ｙ", "Ｚ", "＆", "！", "−",  "．", "’",  "　",
};

void StoreSaveData(SaveData* save, s32 block, s32 cardIcon) {
    const int RoomCount = 942;
    MemcardHeader h;

    MemcardHeader* dstHeader;
    PlayerStatus* dstStatus;
    MenuNavigation* dstNav;
    GameSettings* dstSettings;

    char saveTitle[64];
    u32* saveRaw;
    SaveData* dst;
    s32 saveNameLen;
    s32 i, j;

    saveRaw = (u32*)save;
    for (i = 0; i < 0x800; i++) {
        *saveRaw++ = 0;
    }

    h.Magic[0] = 'S';
    h.Magic[1] = 'C';
    h.Type = 0x13;
    h.BlockEntry = 1;

    // The h.Title content will look like this:
    // US: ＣＡＳＴＬＥＶＡＮＩＡ−１１　ＡＬＵＣＡＲＤ　２００％
    // HD: ドラキュラＸ−１１　ＡＬＵＣＡＲＤ　オルロックの間　２００％
    for (i = 0; i < 0x5C; i++) {
        h.Title[i] = 0;
    }

#if defined(VERSION_US)
    strcpy(h.Title, "ＣＡＳＴＬＥＶＡＮＩＡ−");
#else
    strcpy(h.Title, "ドラキュラＸ−");
#endif

    // writes slot number
    if (block > 8) {
        strcpy(saveTitle, "００");
        saveTitle[1] += (block + 1) / 10;
        saveTitle[3] += (block + 1) % 10;
        strcat(h.Title, saveTitle);
    } else {
        strcpy(saveTitle, "０");
        saveTitle[1] += block + 1;
        strcat(h.Title, saveTitle);
    }

    strcat(h.Title, "　");
    for (saveNameLen = 7; saveNameLen > 0; saveNameLen--) {
        if (g_Status.saveName[saveNameLen] != 0x20) {
            break;
        }
    }

    // writes save name
    for (i = 0; i < saveNameLen + 1; i++) {
        char ch = g_Status.saveName[i];
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
    strcat(h.Title, g_SaveAreaNames[g_StageId]);
    strcat(h.Title, "　");
    i = g_RoomCount * 100 / RoomCount;
    if (i >= 100) {
        strcpy(saveTitle, "０００");
        saveTitle[1] += i / 100;
        saveTitle[3] += (i / 10) % 10;
        saveTitle[5] += i % 10;
        strcat(h.Title, saveTitle);
    } else if (i > 9) {
        strcpy(saveTitle, "００");
        saveTitle[1] += i / 10;
        saveTitle[3] += i % 10;
        strcat(h.Title, saveTitle);
    } else {
        strcpy(saveTitle, "０");
        saveTitle[1] += i;
        strcat(h.Title, saveTitle);
    }
    strcat(h.Title, "％");

    GetSavePalette(h.Clut, cardIcon);
    GetSaveIcon(h.Icon, cardIcon);

    dst = save;
    dstHeader = &dst->header;
    dstStatus = &dst->status;
    dstNav = &dst->menuNavigation;
    dstSettings = &dst->settings;

    *dstHeader = h;
    for (i = 0; i < 10; i++) {
        dst->info.name[i] = g_Status.saveName[i];
    }

    dst->info.level = g_Status.level;
    dst->info.gold = g_Status.gold;
    dst->info.playHours = g_Status.timerHours;
    dst->info.playMinutes = g_Status.timerMinutes;
    dst->info.playSeconds = g_Status.timerSeconds;
    dst->info.cardIcon = cardIcon;
    dst->info.stage = g_StageId;
    dst->info.endGameFlags = g_GameClearFlag;
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

extern s32 D_psp_091FC3F8;
extern s32 D_psp_091FC400;
extern s32 D_psp_091FC408;
extern s32 D_psp_091FC410;

s32 LoadSaveData(SaveData* save) {
    s32 i;
    u32 prevCompletionFlags1;
    u32 prevCompletionFlags2;
    PlayerStatus* srcStatus;
    MenuNavigation* srcNav;
    GameSettings* settings;
    SaveData* savePtr = save;

    if (savePtr->info.saveSize != (sizeof(SaveData))) {
        return -1;
    }
    srcStatus = &savePtr->status;
    srcNav = &savePtr->menuNavigation;
    settings = &savePtr->settings;

    g_StageId = savePtr->info.stage;
    g_GameClearFlag = savePtr->info.endGameFlags;
    g_PlayableCharacter = savePtr->info.character;
    g_RoomCount = savePtr->info.nRoomsExplored;
    g_Tilemap.left = savePtr->info.roomX;
    g_Tilemap.top = savePtr->info.roomY;

    g_Status = *srcStatus;
    D_psp_091FC410 = g_Status.timerHours;
    D_psp_091FC408 = g_Status.timerMinutes;
    D_psp_091FC400 = g_Status.timerSeconds;
    D_psp_091FC3F8 = g_Status.timerFrames;

    g_MenuNavigation = *srcNav;

    prevCompletionFlags1 = g_Settings.D_8003CB00;
    prevCompletionFlags2 = g_Settings.D_8003CB04;
    g_Settings = *settings;
    g_Settings.D_8003CB00 |= prevCompletionFlags1;
    g_Settings.D_8003CB04 |= prevCompletionFlags2;

    for (i = 0; i < LEN(g_CastleFlags); i++) {
        g_CastleFlags[i] = savePtr->castleFlags[i];
    }

    for (i = 0; i < LEN(g_CastleMap); i++) {
        g_CastleMap[i] = savePtr->castleMap[i];
    }

    g_randomNext = savePtr->rng;
    return 0;
}

void MakeMemcardPath(char* dstSaveName, s32 block) {
    strcpy(dstSaveName, MEMCARD_ID);
    dstSaveName[0x10] += block / 10;
    dstSaveName[0x11] += block % 10;
}
