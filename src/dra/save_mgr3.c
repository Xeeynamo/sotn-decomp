#define INCLUDE_ASM_NEW
#include "dra.h"

s32 MemcardFormat(s32 slot, s32 block) {
    char savePath[0x8];
    s32 ret;

    D_8006C3AC &= D_800A0510[slot];
    sprintf(savePath, g_strMemcardRootPath, slot, block);
    func_800E928C();
    format(savePath);
    ret = func_800E9208();

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
    const s32 ColorCount = 16;
    s32 i;
    u16* src = g_saveIconPalette[0];

    src = g_saveIconPalette[palIdx];
    for (i = 0; i < ColorCount; i++) {
        *dst++ = *src++;
    }
}

void GetSaveIcon(u8* dst, s32 iconIdx) {
    const s32 IconSize = 0x80 * 3;
    s32 i;
    u8* src;

    src = g_saveIconTexture[iconIdx];
    for (i = 0; i < IconSize; i++) {
        *dst++ = *src++;
    }
}

INCLUDE_ASM("dra/nonmatchings/save_mgr3", StoreSaveData);

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
