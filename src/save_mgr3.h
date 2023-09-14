
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

    D_8006C3AC &= g_UnkMemcardPort[nPort];
    sprintf(savePath, g_strMemcardRootPath, nPort, nCard);
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
    u16* src = g_saveIconPalette[0];

    src = g_saveIconPalette[palIdx];
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

void StoreSaveData(SaveData* save, s32 block, s32 memcardIcon) {
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

    GetSavePalette(h.Clut, memcardIcon);
    GetSaveIcon(h.Icon, memcardIcon);

    dst = save;
    dstStatus = &save->status;
    dstNav = &save->menuNavigation;
    dstSettings = &save->settings;
    dst->header = h;
    for (i = 0; i < 10; i++) {
        dst->saveName[i] = g_SaveName[i];
    }

    dst->level = g_Status.level;
    dst->goldAmount = g_Status.gold;
    dst->playTimeHours = g_Status.timerHours;
    dst->playTimeMinutes = g_Status.timerMinutes;
    dst->playTimeSeconds = g_Status.timerSeconds;
    dst->stageID = g_StageId;
    dst->memcardIcon = memcardIcon;
    dst->isTimeAttackUnlocked = g_IsTimeAttackUnlocked;
    dst->playableCharacter = g_PlayableCharacter;
    dst->exploredRoomCount = g_RoomCount;
    dst->roomX = g_CurrentRoom.left;
    dst->roomY = g_CurrentRoom.top;
    dst->saveSize = sizeof(SaveData);

    *dstStatus = g_Status;
    *dstNav = g_MenuNavigation;
    *dstSettings = g_Settings;

    for (i = 0; i < 0x300; i++) {
        dst->castleFlags[i] = g_CastleFlags[i];
    }

    for (i = 0; i < 0x800; i++) {
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

    if (save->saveSize != (sizeof(SaveData))) {
        return -1;
    }

    g_StageId = save->stageID;
    g_IsTimeAttackUnlocked = save->isTimeAttackUnlocked;
    g_PlayableCharacter = save->playableCharacter;
    g_RoomCount = save->exploredRoomCount;
    g_CurrentRoom.left = save->roomX;
    g_CurrentRoom.top = save->roomY;

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

    for (i = 0; i < 0x300; i++) {
        g_CastleFlags[i] = save->castleFlags[i];
    }

    for (i = 0; i < 0x800; i++) {
        g_CastleMap[i] = save->castleMap[i];
    }

    g_randomNext = save->rng;
    return 0;
}
