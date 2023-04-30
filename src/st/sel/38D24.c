#include "sel.h"

s32 func_801B8D24(s32 cardSlot, s32 cardSubSlot);
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/st/sel/nonmatchings/38D24", func_801B8D24);
#else
s32 func_801B8D24(s32 cardSlot, s32 cardSubSlot) {
    s8 cardPath[0x8];
    s32 ret;

    D_8006C3AC &= D_801808DC[cardSlot];
    sprintf(cardPath, D_801A7D78, cardSlot, cardSubSlot);
    _clear_event_x();
    format(cardPath);

    ret = _card_event_x();
    if (ret != 1) {
        if (ret == 3) {
            return -1;
        }
        return -3;
    }
    return ret;
}
#endif

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

void StoreSaveData(SaveData* save, s32 arg1, s32 arg2);
INCLUDE_ASM("asm/us/st/sel/nonmatchings/38D24", StoreSaveData);

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

void func_801B9698(char* dstSaveName, s32 saveSlot) {
    __builtin_memcpy(dstSaveName, D_801A802C, sizeof(D_801A802C));
    dstSaveName[0x10] += saveSlot / 10;
    dstSaveName[0x11] += saveSlot % 10;
}

s32 func_801B9744(void) {
    u8 res;

    if (CdSync(1, &res) == 0) {
        D_801BC344 = 0;
        return 0;
    }

    if (func_80019444() - 0x10 < 2U || !(res & 0x10)) {
        CdControlF(1, NULL);
        D_801BC344 = 0;
        return 0;
    }

    D_801BC344 = 1;
    return 1;
}

s32 func_801B97BC(s32*);
INCLUDE_ASM("asm/us/st/sel/nonmatchings/38D24", func_801B97BC);

void func_801B988C(u32* arg0) {
    s32 temp_v0;
    s32 var_s0;

    var_s0 = 4;
loop_1:
    temp_v0 = func_801B97BC(arg0);
    if (temp_v0 == 0) {
        var_s0 -= 1;
        if (var_s0 != 0) {
            goto loop_1;
        }
    } else {
        s32 temp_v0_2 = arg0[2] == 0;
        arg0[2] = temp_v0_2;
        D_801BC340++;
        func_801BABA4(temp_v0, *((temp_v0_2) + arg0));
        func_8001C550(temp_v0);
    }
}

void func_801B9924(void) {
    volatile u32 pad[4]; // FAKE
    SetDispMask(0);
    func_801B18F4();
}

INCLUDE_ASM("asm/us/st/sel/nonmatchings/38D24", func_801B994C);

INCLUDE_ASM("asm/us/st/sel/nonmatchings/38D24", func_801B99E4);

// func_801B9B7C(Unkstruct_801B9B7C* arg0, s16 arg1, s16 arg2, s16 arg3, s32
// arg4);
INCLUDE_ASM("asm/us/st/sel/nonmatchings/38D24", func_801B9B7C);

void func_801B9C18(s32 unused, void (*callback)()) {
    s32* s0 = D_801BD044;
    func_801BA460(0);
    *s0 = 0;
    func_801BA6CC(callback);
    func_800192DC((s32)(s0 + 2), 0x28);
    StSetStream(D_801BD038, 1, -1, NULL, NULL);
}

INCLUDE_ASM("asm/us/st/sel/nonmatchings/38D24", func_801B9C80);

void func_801BA460(s32 option) {
    if (option == 0) {
        ResetCallback();
    }

    MDEC_rest(option);
}

s32* func_801BA498(Unkstruct_801BA498* arg0) {
    s32 i;
    s32 *src1, *dst1;
    s32 *src2, *dst2;
    s32 *src3, *dst3;

    dst1 = &arg0->unk00;
    src1 = D_801962F8;
    for (i = 15; i != -1; i--) {
        *dst1++ = *src1++;
    }

    dst2 = &arg0->unk10;
    src2 = D_80196338;
    for (i = 15; i != -1; i--) {
        *dst2++ = *src2++;
    }

    dst3 = &arg0->unk20;
    src3 = D_8019637C;
    for (i = 31; i != -1; i--) {
        *dst3++ = *src3++;
    }

    return arg0;
}

s32* func_801BA524(Unkstruct_801BA498* arg0) {
    s32 i;
    s32 *src1, *dst1;
    s32 *src2, *dst2;

    dst1 = D_801962F8;
    src1 = &arg0->unk00;
    for (i = 15; i != -1; i--) {
        *dst1++ = *src1++;
    }

    dst2 = D_80196338;
    src2 = &arg0->unk10;
    for (i = 15; i != -1; i--) {
        *dst2++ = *src2++;
    }

    func_801BA7EC(&D_801962F4, 0x20);
    func_801BA7EC(&D_80196378, 0x20);

    return arg0;
}

u16 func_801BA5C0(u16* arg0) { return *arg0; }

void func_801BA5CC(s32* arg0, s32 arg1) {
    s32 new_var2;
    s32 var_v0;
    s32 var_v0_2;

    if (arg1 & 1) {
        var_v0 = (*arg0) & 0xF7FFFFFF;
    } else {
        new_var2 = 0x08000000;
        var_v0 = 0x08000000;
        var_v0 = (*arg0) | var_v0;
    }

    *arg0 = var_v0;
    var_v0 = 0x02000000;
    if (arg1 & 2) {
        new_var2 = var_v0;
        var_v0_2 = (*arg0) | new_var2;
    } else {
        var_v0_2 = (*arg0) & 0xFDFFFFFF;
    }

    *arg0 = var_v0_2;
    func_801BA7EC(arg0, *(u16*)arg0);
}

void func_801BA648(s32 arg0, u32 arg1) { func_801BA880(arg0, arg1); }

void func_801BA668(void) { MDEC_in_sync(); }

void func_801BA688(void) { MDEC_out_sync(); }

void func_801BA6A8(void (*func)()) { DMACallback(0, func); }

void func_801BA6CC(void (*func)()) { DMACallback(1, func); }

INCLUDE_ASM("asm/us/st/sel/nonmatchings/38D24", MDEC_rest);

void func_801BA7EC(s32* arg0, u32 arg1) {
    MDEC_in_sync();
    *D_80196434 |= 0x88;
    *D_801963FC = arg0 + 1;
    *D_80196400 = ((arg1 >> 5) << 0x10) | 0x20;
    *D_8019642C = *arg0;
    *D_80196404 = 0x01000201;
}
void func_801BA880(s32 arg0, u32 arg1) {
    MDEC_out_sync();
    *D_80196434 |= 0x88;
    *D_80196410 = 0;
    *D_80196408 = arg0;
    *D_8019640C = ((arg1 >> 5) << 0x10) | 0x20;
    *D_80196410 = 0x01000200;
}

INCLUDE_ASM("asm/us/st/sel/nonmatchings/38D24", MDEC_in_sync);

// missing a return maybe?
#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/st/sel/nonmatchings/38D24", MDEC_out_sync);
#else
void MDEC_out_sync(void) {
    volatile s32 sp10 = 0x100000;

    while (*D_80196410 & 0x01000000) {
        if (--sp10 == -1) {
            MDEC_print_error(D_801ABFC8);
            break;
        }
    }
}
#endif

INCLUDE_ASM("asm/us/st/sel/nonmatchings/38D24", MDEC_print_error);

INCLUDE_ASM("asm/us/st/sel/nonmatchings/38D24", func_801BAB70);

INCLUDE_ASM("asm/us/st/sel/nonmatchings/38D24", func_801BABA4);
