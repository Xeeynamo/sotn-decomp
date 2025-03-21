// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

extern MemcardInfo g_MemcardInfo[2];

void func_psp_0913D610(void) {}

void MemcardInit(void) { g_MemcardStep = 0; }

void MemcardInfoInit(void) {
    g_MemcardInfo[0].nBlockUsed = 0;
    g_MemcardInfo[1].nBlockUsed = 0;
}

s32 MemcardParse(s32 nPort, s32 nCard) {
    s32 blocksFree = 0;

    if (nPort == 0) {
        // Presumably func_8919278 is something like
        // getNumFreeBlocks, but I don't know the SDK function set.
        blocksFree = func_8919278();
    }
    g_MemcardInfo[nPort].nBlockUsed = BLOCK_PER_CARD - blocksFree;
    g_MemcardInfo[nPort].nFreeBlock = blocksFree;
    return g_MemcardInfo[nPort].nFreeBlock;
}

s32 GetMemcardFreeBlockCount(s32 nPort) {
    return g_MemcardInfo[nPort].nFreeBlock;
}

s32 MemcardDetectSave(s32 nPort, s32 expectedSaveName, s32 block) {
    bool result;
    bool found;

    result = false;
    if (nPort == 0) {
        if (func_8919188(expectedSaveName) >= 0) {
            found = true;
        } else {
            found = false;
        }
        result = found;
    }
    g_MemcardInfo[nPort].blocks[block] = result;
    return result;
}

s32 IsMemcardBlockUsed(s32 cardNum, s32 blockNum) {
    return g_MemcardInfo[cardNum].blocks[blockNum];
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
    if (func_89194E4(data, name, len) > 0) {
        ret = 0;
    } else {
        ret = -1;
    }
    return ret;
}

s32 MemcardWriteFile(s32 nPort, s32 nCard, const char* name, void* data, s32 flags, s32 unused, s32 create) {
    s32 ret;

    if (nPort != 0) {
        return -2;
    }
    if (nCard != 0) {
        return -2;
    }
    if (func_89193D4(data, name, flags << 0xD, create) > 0) {
        ret = 0;
    } else {
        ret = -1;
    }
    return ret;
}

s32 MemcardEraseFile(s32 nPort, s32 nCard, s32 arg2, s32 arg3) {
    if (nPort != 0) {
        return -1;
    }
    if (nCard != 0) {
        return -1;
    }
    return func_89192EC(arg2, arg3);
}

s32 MemcardClose(s32 nPort) {
    return 1;
}

s32 func_800E9880(s32 nPort, s32 nCard) {
    if ((nPort != 0) || (nCard != 0)) {
        return -1;
    }
    switch(func_8919770(4)){
        case 2:
            return -1;
    }
    return 1;
}

INCLUDE_ASM("dra_psp/psp/dra_psp/60C90", GetSavePalette);

INCLUDE_ASM("dra_psp/psp/dra_psp/60C90", GetSaveIcon);

extern char** g_SaveAreaNames;
extern char g_AsciiSet[];
char* g_ShiftJisSet[] = {
    "Ａ", "Ｂ", "Ｃ", "Ｄ", "Ｅ", "Ｆ", "Ｇ", "Ｈ", "Ｉ", "Ｊ", "Ｋ",
    "Ｌ", "Ｍ", "Ｎ", "Ｏ", "Ｐ", "Ｑ", "Ｒ", "Ｓ", "Ｔ", "Ｕ", "Ｖ",
    "Ｗ", "Ｘ", "Ｙ", "Ｚ", "＆", "！", "−",  "．", "’",  "　",
};

void StoreSaveData(SaveData* save, s32 block, s32 cardIcon) {
    const int RoomCount = 942;
    MemcardHeader h;
    SaveData* dst2;
    char saveTitle[64];
    
    PlayerStatus* dstStatus;
    MenuNavigation* dstNav;
    GameSettings* dstSettings;
    u32* saveRaw;
    s32 saveNameLen;
    SaveData* dst;
    s32 j;
    s32 i;



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
    STRCPY(h.Title, "ＣＡＳＴＬＥＶＡＮＩＡ−");
#elif defined(VERSION_HD)
    STRCPY(h.Title, "ドラキュラＸ−");
#elif defined(VERSION_PSP)
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
        STRCPY(saveTitle, "０００");
        saveTitle[1] += i / 100;
        saveTitle[3] += (i / 10) % 10;
        saveTitle[5] += i % 10;
        strcat(h.Title, saveTitle);
    } else if (i > 9) {
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
    dst2 = dst;
    dstStatus = &dst->status;
    dstNav = &dst->menuNavigation;
    dstSettings = &dst->settings;
    dst2->header = h;
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

INCLUDE_ASM("dra_psp/psp/dra_psp/60C90", LoadSaveData);

INCLUDE_ASM("dra_psp/psp/dra_psp/60C90", MakeMemcardPath);