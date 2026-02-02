// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game_psp.h>
#include "main_psp_private.h"

extern s32 D_psp_089464E8;
extern s32 D_psp_08C62A3C;
extern DxCSaveData D_psp_08DED03C;

// BSS
static SoTNSaveData* D_psp_08B41F2C;
static SoTNSaveData saveData;
static SoTNSaveData* D_psp_08B21DE8;

static void func_psp_089190A0(SoTNSaveData* ptr, s32 len) {
    memmove(ptr, D_psp_08B21DE8, len);
    (u8*)D_psp_08B21DE8 += len;
}

static void func_psp_089190F0(SoTNSaveData* ptr, s32 len) {
    memmove(D_psp_08B21DE8, ptr, len);
    (u8*)D_psp_08B21DE8 += len;
}

void InitSaveData(void) {
    memset(&saveData, 0, sizeof(SoTNSaveData));
    saveData.quickSaveSlot = -2;
    ClearQuickSaveDataSlot();
}

s32 FindSaveDataSlot(char* name) {
    s32 slot;

    for (slot = 0; slot < SAVE_SLOT_COUNT; slot++) {
        if (strcmp(name, saveData.name[slot]) == 0) {
            return slot;
        }
    }
    return -1;
}

s32 FindFreeSaveDataSlot(void) {
    s32 slot;

    for (slot = 0; slot < SAVE_SLOT_COUNT; slot++) {
        if (saveData.name[slot][0] == 0) {
            return slot;
        }
    }
    return -1;
}

s32 GetFreeSaveDataSlotCount(void) {
    s32 freeSlotCount = 0;
    s32 slot;

    for (slot = 0; slot < SAVE_SLOT_COUNT; slot++) {
        if (saveData.name[slot][0] == 0) {
            freeSlotCount++;
        }
    }
    return freeSlotCount;
}

s32 ClearSaveDataSlot(char* name, bool clearQuickSave) {
    s32 slot;

    slot = FindSaveDataSlot(name);
    if (slot == -1) {
        return -1;
    }
    saveData.name[slot][0] = 0;
    memset(saveData.data[slot], 0, 0x2000);
    if (clearQuickSave && slot == GetQuickSaveDataSlot()) {
        ClearQuickSaveDataSlot();
    }
    if (func_psp_08919770(3) == 0) {
        func_psp_08919770(4);
        return -1;
    }
    return 0;
}

s32 WriteSaveDataSlot(u8* data, char* name, u32 len, bool clearQuickSave) {
    s32 slot;

    slot = FindSaveDataSlot(name);
    if (slot == -1) {
        slot = FindFreeSaveDataSlot();
        if (slot == -1) {
            return -1;
        }
    }
    strcpy(saveData.name[slot], name);
    memcpy(saveData.data[slot], data, (s32)len);
    if (clearQuickSave && GetQuickSaveDataSlot() >= 0) {
        ClearQuickSaveDataSlot();
    }
    if (func_psp_08919770(3) == 0) {
        func_psp_08919770(4);
        return -1;
    }
    return len;
}

s32 TryLoadSaveData(u8* data, char* name, u32 len) {
    s32 slot;

    slot = FindSaveDataSlot(name);
    if (slot == -1) {
        return -1;
    }
    memcpy(data, saveData.data[slot], (s32)len);
    return len;
}

s32 GetQuickSaveDataSlot(void) { return saveData.quickSaveSlot; }

s32 ClearQuickSaveDataSlot(void) {
    s32 prev = saveData.quickSaveSlot;
    saveData.quickSaveSlot = -2;
    return prev;
}

void SetQuickSaveDataSlot(s32 slot) { saveData.quickSaveSlot = slot; }

s32 WriteQuickSaveData(u8* data, u32 len, s32 slot) {
    saveData.quickSaveSlot = slot;
    memcpy(saveData.quickSaveData, data, (s32)len);
    if (func_psp_08919770(3) == 0) {
        func_psp_08919770(4);
        return -1;
    }
    return len;
}

s32 LoadQuickSaveData(u8* data, u32 len) {
    memcpy(data, saveData.quickSaveData, (s32)len);
    return len;
}

void func_psp_08919674(void) {
    func_psp_089190F0(&saveData, sizeof(SoTNSaveData));
}

s32 func_psp_089196A4(void) {
    func_psp_089190A0(&saveData, sizeof(SoTNSaveData));
    return 1;
}

s32 func_psp_089196D8(s32 arg0, s32 arg1) {
    s32 ret = 0;

    D_psp_08B41F2C = &D_psp_08DED03C.sotnSaveData;

    switch (arg0) {
    case 3:
        ret = func_psp_0891985C(arg1);
        break;
    case 4:
        ret = func_psp_08919928(arg1);
        break;
    default:
        ret = -1;
    }
    return ret;
}

s32 func_psp_08919770(s32 arg0) { return func_psp_089196D8(arg0, 1); }

void func_psp_0891979C(s32 arg0) { func_psp_089196D8(arg0, 0); }

void func_psp_089197C8(s32 arg0) {
    if (arg0 != 0) {
        D_psp_089464E8 = 2;
    } else {
        D_psp_089464E8 = 0;
        D_psp_08C62A3C = 2;
    }
    DrawSync(0);
    VSync(0);
    EndFrame();
    func_psp_0891FC64();
    DrawSync(0);
    UpdateSaveDataUtility();
    UpdateErrorDialog();
}

s32 func_psp_0891985C(s32 arg0) {
    s32 var_s0;

    memset(D_psp_08B41F2C, 0, sizeof(SoTNSaveData));
    D_psp_08B21DE8 = D_psp_08B41F2C;
    func_psp_08919674();
    func_psp_08931D3C();
    UpdateSaveDataUtility();
    UpdateErrorDialog();
    var_s0 = 0;
    while (var_s0 == 0) {
        PadReadPSP();
        var_s0 = func_psp_08931D64();
        func_psp_089197C8(arg0);
    }
    return (var_s0 == 1) ? 1 : 0;
}

s32 func_psp_08919928(s32 arg0) {
    s32 var_s0;

    StartDxCSaveDataTask(AUTOLOAD_DXC_SAVEDATA);
    UpdateSaveDataUtility();
    UpdateErrorDialog();
    var_s0 = 0;
    while (var_s0 == 0) {
        PadReadPSP();
        var_s0 = UpdateDxCSaveDataTask();
        func_psp_089197C8(arg0);
    }
    if (var_s0 == 1) {
        D_psp_08B21DE8 = D_psp_08B41F2C;
        if (func_psp_089196A4() == 0) {
            return 0;
        }
    }

    return (var_s0 == 1) ? 1 : 0;
}
