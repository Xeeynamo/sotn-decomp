#define INCLUDE_ASM_NEW
#include "dra.h"

s32 MemcardFormat(s32 slot, s32 block) {
    char savePath[0x8];
    s32 ret;

    D_8006C3AC &= D_800A0510[slot];
    sprintf(savePath, g_strMemcardRootPath, slot, block);
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

#ifndef NON_MATCHING
INCLUDE_ASM("dra/nonmatchings/save_mgr3", StoreSaveData);
#else
extern const char D_800A1FD4[0x24] = {0};
extern s8* D_800A1FF8[];
extern const char D_800DBFB4[] = "";     // ?
extern const char D_800DC160[0x19] = ""; // "ＣＡＳＴＬＥＶＡＮＩＡ－"
extern const char D_800DC17C[5] = "";    // "００"
extern const char D_800DC184[3] = "";    // "０"
extern const char D_800DC188[7] = "";    // ?
extern const char D_800DC18C[3] = "";    // ?
extern const char D_800DC190[3] = "";    // ?

void StoreSaveData(SaveData* save, s32 slotNo, s32 memcardIcon) {
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
    // ＣＡＳＴＬＥＶＡＮＩＡ－１１　ＡＬＵＣＡＲＤ　２００％
    for (i = 0; i < 0x5C; i++) {
        h.Title[i] = 0;
    }

    // ＣＡＳＴＬＥＶＡＮＩＡ－
    __builtin_memcpy(h.Title, D_800DC160, sizeof(D_800DC160));

    // ＣＡＳＴＬＥＶＡＮＩＡ－１１
    if (slotNo >= 9) {
        __builtin_memcpy(saveTitle, D_800DC17C, sizeof(D_800DC17C));
        saveTitle[1] += (slotNo + 1) / 10;
        saveTitle[3] += (slotNo + 1) % 10;
        strcat(h.Title, saveTitle);
    } else {
        __builtin_memcpy(saveTitle, D_800DC184, sizeof(D_800DC184));
        saveTitle[1] += slotNo + 1;
        strcat(h.Title, saveTitle);
    }

    // adds space
    strcat(h.Title, D_800DBFB4);

    for (saveNameLen = 7; saveNameLen > 0; saveNameLen--) {
        if (g_SaveName[saveNameLen] != 0x20) {
            break;
        }
    }

    // ＣＡＳＴＬＥＶＡＮＩＡ－１１　ＡＬＵＣＡＲＤ
    for (i = 0; i < saveNameLen + 1; i++) {
        char ch = g_SaveName[i];
        for (j = 0; j < 0x20; j++) {
            // Converts ASCII into Shift-JIS
            if (ch == D_800A1FD4[j]) {
                strcat(h.Title, D_800A1FF8[j]);
                break;
            }
        }
    }

    // adds space
    strcat(h.Title, D_800DBFB4);

    // ＣＡＳＴＬＥＶＡＮＩＡ－１１　ＡＬＵＣＡＲＤ　２００
    i = roomPercentage = g_roomCount * 100 / RoomCount;
    if (i >= 100) {
        __builtin_memcpy(saveTitle, D_800DC188, sizeof(D_800DC188));
        saveTitle[1] += i / 100;
        saveTitle[3] += i / 10 - i / 100 * 10;
        saveTitle[5] += i % 10;
        strcat(h.Title, saveTitle);
    } else if (i >= 10) {
        __builtin_memcpy(saveTitle, D_800DC17C, sizeof(D_800DC17C));
        saveTitle[1] += i / 10;
        saveTitle[3] += i % 10;
        strcat(h.Title, saveTitle);
    } else {
        __builtin_memcpy(saveTitle, D_800DC184, sizeof(D_800DC184));
        saveTitle[1] += i;
        strcat(h.Title, saveTitle);
    }

    // adds '％' symbol
    strcat(h.Title, D_800DC190);

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
    dst->playableCharacter = g_CurrentPlayableCharacter;
    dst->exploredRoomCount = g_roomCount;
    dst->roomX = g_CurrentRoom.left;
    dst->roomY = g_CurrentRoom.top;
    dst->saveSize = sizeof(SaveData);

    *dstStatus = g_Status;
    *dstNav = g_MenuNavigation;
    *dstSettings = g_Settings;

    for (i = 0; i < 0x300; i++) {
        dst->castleFlags[i] = D_8003BDEC[i];
    }

    for (i = 0; i < 0x800; i++) {
        dst->castleMap[i] = D_8006BB74[i];
    }

    dst->rng = g_randomNext;
}
#endif

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
    g_CurrentPlayableCharacter = save->playableCharacter;
    g_roomCount = save->exploredRoomCount;
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
        D_8003BDEC[i] = save->castleFlags[i];
    }

    for (i = 0; i < 0x800; i++) {
        D_8006BB74[i] = save->castleMap[i];
    }

    g_randomNext = save->rng;
    return 0;
}

void func_800EA48C(char* dstname, s32 saveSlot) {
    __builtin_memcpy(dstname, aBaslus00067dra, sizeof(aBaslus00067dra));
    dstname[0x10] += saveSlot / 10;
    dstname[0x11] += saveSlot % 10;
}
