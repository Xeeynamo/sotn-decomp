#include "common.h"
#include "dra.h"
#include "objects.h"
#include "sfx.h"

s32 DecompressData(u8* dst, u8* src);

INCLUDE_ASM("asm/us/dra/nonmatchings/47BB8", func_800E7BB8);

void func_800E7D08(void) {
    s32 i;

    for (i = 0; i < 1024; i++) {
        D_80136460[i] = 0;
        D_80136C60[i] = 0;
    }

    D_800A04EC = 1;
}

#ifndef NON_MATCHING
void LoadStageTileset(u8* pTilesetData, s32 y);
INCLUDE_ASM("asm/us/dra/nonmatchings/47BB8", LoadStageTileset);
#else
void LoadStageTileset(u8* pTilesetData, s32 y) {
    int new_var;
    RECT rect;
    u16* var_s2;
    s32 i;
    s32 new_var2;

    i = 0;
    new_var2 = y;
    new_var = y + 0x80;
    var_s2 = D_800AC958;
    rect.w = 0x20;
    rect.h = 0x80;
    for (; i < 0x20; i++) {
        rect.x = *var_s2;
        if (i & 2) {
            rect.y = new_var;
        } else {
            rect.y = new_var2;
        }
        LoadImage(&rect, pTilesetData);
        while (DrawSync(1)) {
            ;
        }

        var_s2++;
        pTilesetData += 0x2000;
    }
}
#endif

// Not matching due to case 2/11
#ifndef NON_EQUIVALENT
s32 func_800E7E08(u32);
INCLUDE_ASM("asm/us/dra/nonmatchings/47BB8", func_800E7E08);
#else
extern u32 g_Clut;
extern u32 D_8006EBCC;
extern u32 D_80070BCC;
extern u32 D_800A04CC;
extern RECT D_800ACDA8;
extern RECT D_800ACDB8;
extern RECT D_800ACDC0;
extern RECT D_800ACDD0;
extern RECT D_800ACDD8;
extern RECT D_800ACDE0;
extern s32 D_800BD1C8[];
extern s32* D_8013644C;      // this is now an OvlDesc!!
extern const char aPqes_1[]; // pQES
extern RECT rect;
extern s32* g_StageOverlay;

s32 func_800E7E08(u32 arg0) {
    s32 i;
    void (**pSrc)();
    void (**pDst)();

    switch (arg0) {
    case 0:
        pSrc = g_StageOverlay;
        i = 0;
        pDst = &g_api.o;
        do {
            i++;
            *pDst++ = *pSrc++;
        } while (i < 0x10);
        break;
    case 19:
        LoadTPage((PixPattern*)0x80280000, 0, 0, 0x2C0, 0x100, 0x100, 0x80);
        LoadTPage((PixPattern*)0x80284000, 0, 0, 0x2C0, 0x180, 0x80, 0x80);
        break;
    case 9:
        LoadTPage((PixPattern*)&D_8007EFE4, 0, 0, 0x240, 0x100, 0x100, 0x80);
        break;
    case 10:
        LoadTPage((PixPattern*)&D_80082FE4, 0, 0, 0x240, 0x180, 0x100, 0x80);
        break;
    case 20:
        LoadTPage((PixPattern*)(s32*)0x80280000, 2, 0, 0x20, 0x100, 0x60, 0x70);
        break;
    case 1:
        LoadStageTileset(0x80180000, 0x100);
        DrawSync(0);
        LoadImage(&rect, &D_800A04CC);
        LoadImage(&rect + 2, (u32*)0x801C0000);
        while (DrawSync(1))
            ;
        StoreImage(&D_800ACDA8, &D_8006EBCC);
        break;
    default:
        break;
    case 2:
    case 11: // .rodata+0x8,0x2c
        LoadStageTileset(0x80280000, 0);
        DrawSync(0);
        StoreImage(&D_800ACDB8, &g_Clut);
        if (arg0 == 0xB) {
            StoreImage(&D_800ACDB8, &g_Clut + 0x4000);
            DrawSync(0);
            LoadImage(&D_800ACDB8 - 8, &g_Clut + 0x4000);
            break;
        }
        break;
    case 12:
    case 13: // .rodata+0x30,0x34
        LoadStageTileset(0x80280000, 0x100);
        if (arg0 == 0xD) {
            LoadImage(&rect, &D_800A04CC);
        }
        DrawSync(0);
        break;
    case 4:
        while (func_800219E0(0) != 1)
            ;
        if (func_80021350(D_8013644C[1], D_800A0248, D_800BD1C8[D_800A0248]) <
            0) {
            return -1;
        }
        break;
    case 5:
        if (func_80021880((s32*)0x80280000, D_8013644C[2], D_800A0248) == -1) {
            return -1;
        }
        while (func_800219E0(0) != 1)
            ;
        break;
    case 7:
        if (g_StageId == 2) {
            func_80131EBC(&aPqes_1, 0x202);
        }
        if (g_StageId == 6) {
            func_80131EBC(&aPqes_1, 0x204);
        }
        break;
    case 6:
        LoadImage(&D_800ACDC0, (u32*)0x80180000);
        break;
    case 14:
        LoadImage(&D_800ACDD0, (u32*)0x80280000);
        break;
    case 21:
        LoadImage(&D_800ACDE0, (u32*)0x80280000);
        break;
    case 15:
        LoadImage(&D_800ACDD8, (u32*)0x80280000);
        break;
    case 16:
        LoadImage(&D_800ACDB8, (u32*)0x80280000);
        StoreImage(&D_800ACDB8, &D_80070BCC);
        break;
    case 17:
        LoadImage(&D_800ACDA8, (u32*)0x80280000);
        StoreImage(&D_800ACDA8, &g_Clut);
        break;
    }

    return 0;
}
#endif

s32 func_800E81FC(s32 fileId, FileType type) {
    char buf[33];
    s32 fid;

    func_800E7D08();
    D_800A04EC = 1;
    D_8013644C = &D_800A024C[fileId];
    if (type == FILETYPE_STAGE_PRG) {
        STRCPY(buf, "sim:c:\\bin\\");
        D_8013644C = &D_80136450;
        strcat(buf, D_800A3C40[g_StageId].ovlName);
        strcat(buf, ".bin");
        D_8013644C->addr = (u8*)0x80180000;
        D_8013644C->path = buf;
        D_8013644C->size = 0x60000;
        D_8013644C->type = 0;
    }
    if (type == FILETYPE_VH) {
        if (fileId & 0x8000) {
            D_8013644C = &D_800A036C[fileId & 0x7FFF];
        } else {
            STRCPY(buf, "sim:c:\\sound\\data\\sd_");
            D_8013644C = &D_80136450;
            strcat(buf, D_800A3C40[g_StageId].name);
            strcat(buf, ".vh");
            D_8013644C->addr = (u8*)aPbav_2;
            D_8013644C->path = buf;
            D_8013644C->size = D_800A3C40[g_StageId].vhLen;
            D_8013644C->type = 4;
        }
        if (D_8013644C->addr == aPbav) {
            D_800A0248 = 0;
        }
        if (D_8013644C->addr == aPbav_0) {
            D_800A0248 = 1;
        }
        if (D_8013644C->addr == aPbav_2) {
            D_800A0248 = 3;
        }
        if (D_8013644C->addr == aPbav_1) {
            D_800A0248 = 2;
        }
        SsVabClose(D_800A0248);
    }
    if (type == FILETYPE_VB) {
        if (fileId & 0x8000) {
            D_8013644C = &D_800A036C[fileId & 0x7FFF];
        } else {
            D_8013644C = &D_80136450;
            STRCPY(buf, "sim:c:\\sound\\data\\sd_");
            strcat(buf, D_800A3C40[g_StageId].name);
            strcat(buf, ".vb");
            D_8013644C->addr = (u8*)0x80280000;
            D_8013644C->path = buf;
            D_8013644C->size = D_800A3C40[g_StageId].vbLen;
            D_8013644C->type = 5;
        }
    }
    if (type == FILETYPE_SEQ) {
        D_8013644C = &D_800A04AC[fileId];
    }
    if (type == FILETYPE_STAGE_CHR) {
        D_8013644C = &D_80136450;
        STRCPY(buf, "sim:c:\\bin\\");
        strcat(buf, D_800A3C40[g_StageId].gfxName);
        strcat(buf, ".bin");
        D_8013644C->addr = (u8*)0x80280000;
        D_8013644C->size = 0x40000;
        D_8013644C->path = buf;
        D_8013644C->type = 2;
    }
    if (type == FILETYPE_WEAPON0_PRG) {
        D_8013644C = &D_80136450;
        STRCPY(buf, "sim:c:\\bin\\w0_000.bin");
        buf[15] = ((fileId / 10) % 10) + '0';
        buf[16] = (fileId % 10) + '0';
        D_8013644C->path = buf;
        D_8013644C->size = 0x3000;
        D_8013644C->addr = (u8*)0x8017A000;
        D_8013644C->type = 8;
    }
    if (type == FILETYPE_WEAPON1_PRG) {
        D_8013644C = &D_80136450;
        STRCPY(buf, "sim:c:\\bin\\w1_000.bin");
        buf[15] = ((fileId / 10) % 10) + '0';
        buf[16] = (fileId % 10) + '0';
        D_8013644C->path = buf;
        D_8013644C->addr = (u8*)0x8017D000;
        D_8013644C->size = 0x3000;
        D_8013644C->type = 8;
    }
    if (type == FILETYPE_WEAPON0_CHR) {
        D_8013644C = &D_80136450;
        STRCPY(buf, "sim:c:\\bin\\f0_000.bin");
        buf[15] = ((fileId / 10) % 10) + '0';
        buf[16] = (fileId % 10) + '0';
        D_8013644C->path = buf;
        D_8013644C->addr = (u8*)&D_8007EFE4;
        D_8013644C->size = 0x4000;
        D_8013644C->type = 9;
    }
    if (type == FILETYPE_WEAPON1_CHR) {
        D_8013644C = &D_80136450;
        STRCPY(buf, "sim:c:\\bin\\f1_000.bin");
        buf[15] = ((fileId / 10) % 10) + '0';
        buf[16] = (fileId % 10) + '0';
        D_8013644C->path = buf;
        D_8013644C->addr = (u8*)&D_80082FE4;
        D_8013644C->size = 0x4000;
        D_8013644C->type = 10;
    }
    if (type == FILETYPE_FAMILIAR_PRG) {
        D_8013644C = &D_80136450;
        STRCPY(buf, "sim:c:\\bin\\tt_000.bin");
        buf[16] = (fileId % 10) + '0';
        D_8013644C->path = buf;
        D_8013644C->addr = (u8*)0x80170000;
        D_8013644C->size = 0xA000;
        D_8013644C->type = 18;
    }
    if (type == FILETYPE_FAMILIAR_CHR) {
        D_8013644C = &D_80136450;
        STRCPY(buf, "sim:c:\\bin\\ft_000.bin");
        buf[16] = (fileId % 10) + '0';
        D_8013644C->path = buf;
        D_8013644C->addr = (u8*)0x80280000;
        D_8013644C->size = 0x6000;
        D_8013644C->type = 19;
    }
    if (type == FILETYPE_MONSTER) {
        D_8013644C = &D_80136450;
        STRCPY(buf, "sim:c:\\bin\\mo_000.bin");
        buf[14] = fileId / 100 + '0';
        buf[15] = fileId / 10 - fileId / 100 * 10 + '0';
        buf[16] = fileId % 10 + '0';
        D_8013644C->path = buf;
        D_8013644C->addr = (u8*)0x80280000;
        D_8013644C->size = 0x5800;
        D_8013644C->type = 20;
    }

    fid = open(D_8013644C->path, 1);
    if (fid < 0) {
        FntPrint("o err:%s\n", D_8013644C->path);
        D_800A04EC = 0;
        return -1;
    }
    if (read(fid, D_8013644C->addr, D_8013644C->size) < 0) {
        FntPrint("r err\n");
        D_800A04EC = 0;
        return -1;
    }
    if (close(fid) < 0) {
        FntPrint("cl err\n");
        D_800A04EC = 0;
        return -1;
    }
    if (func_800E7E08(D_8013644C->type) < 0) {
        FntPrint("tr err\n");
        D_800A04EC = 0;
        return -1;
    }
    D_800A04EC = 0;
    return 0;
}

void func_800E8D24(void) {
    s8* ptr;
    s32 i;

    g_pads[0].repeat = 0;
    ptr = D_80137460;

    for (i = 0; i < 16; i++) {
        *ptr++ = 0x10;
    }
}

void func_800E8D54(void) {
    u16 button = 1;
    u16 repeat = 0;
    u16 unk = g_pads[0].tapped;
    u16 pressed = g_pads[0].pressed;
    u8* timers = D_80137460;
    s32 i = 0;

    do {
        NOP;
        if (pressed & button) {
            if (unk & button) {
                repeat |= button;
                timers[0] = 0x10;
            } else {
                if (--timers[0] == 0xFF) {
                    repeat |= button;
                    timers[0] = 5;
                }
            }
        }
        i++;
        timers++;
        button <<= 1;
    } while (i < 0x10);
    g_pads[0].repeat = repeat;
}

void InitializePads(void) {
    Pad* pad;
    s32 i;

    PadInit(0);
    for (pad = g_pads, i = 0; i < PAD_COUNT; i++, pad++) {
        pad->tapped = 0;
        pad->previous = 0;
        pad->pressed = 0;
    }
    func_800E8D24();
}

void ReadPads(void) {
    Pad* pad;
    s32 i;
    u_long padd;

    for (pad = g_pads, i = 0; i < PAD_COUNT; i++, pad++) {
        pad->previous = pad->pressed;
        padd = PadRead(i >> 1);
        if (!(i & 1))
            pad->pressed = padd;
        else
            pad->pressed = padd >> 0x10;
        pad->tapped = (pad->pressed ^ pad->previous) & pad->pressed;
    }
    func_800E8D54();
}

void func_800E8EE4(void) {
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

s32 func_800E908C(void) {
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

s32 func_800E912C(void) {
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

void func_800E91B0(void) {
    TestEvent(g_EvSwCardEnd);
    TestEvent(g_EvSwCardErr);
    TestEvent(g_EvSwCardTmo);
    TestEvent(g_EvSwCardNew);
}

s32 func_800E9208(void) {
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

void func_800E928C(void) {
    TestEvent(g_EvHwCardEnd);
    TestEvent(g_EvHwCardErr);
    TestEvent(g_EvHwCardTmo);
    TestEvent(g_EvHwCardNew);
}

void func_800E92E4(void) { D_8013B660 = 0; }

void func_800E92F4(void) {
    D_8013B158 = 0;
    D_8013B3D0 = 0;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/47BB8", func_800E930C);

extern Unkstruct_8013B15C D_8013B15C[];

s32 func_800E9508(s32 arg0) {
    s32 temp = D_8013B15C[arg0].unk000;

    return temp;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/47BB8", func_800E9530);

u8 func_800E9610(u32 arg0, u32 arg1) { return D_8013B160[arg0].unk0[arg1]; }

s32 func_800E9640(s32 arg0, s32 arg1, s32 arg2, s32* readBufferAddress,
                  s32 fd) {
    char file[32];
    s32 nBytes;
    s32 ret;

    sprintf(file, g_MemcardSavePath, arg0, arg1, arg2);
    nBytes = fd << 0xD;

    if (fd == 0) {
        nBytes = 0x2B8;
    }

    fd = open(file, 0x8001);
    ret = -1;

    if (fd != (-1)) {
        D_80137474 = fd;
        func_800E91B0();
        read(fd, readBufferAddress, nBytes);
        ret = 0;
    }
    return ret;
}

s32 func_800E96E8(s32 arg0, s32 arg1, s32 arg2, void* arg3, s32 arg4,
                  s32 arg5) {
    s8 savePath[32];
    s32 new_var;
    s32 device;

    sprintf(savePath, g_MemcardSavePath, arg0, arg1, arg2);

    if (arg5 == 1) {
        device = open(savePath, (arg4 << 0x10) | 0x200);
        if (device == -1) {
            return -2;
        } else {
            close(device);
        }
    }

    new_var = arg4 << 0xD;
    device = open(savePath, 0x8002);

    if (device == (-1)) {
        return -1;
    } else {
        D_80137474 = device;
        func_800E91B0();
        write(device, arg3, new_var);
    }
    return 0;
}

s32 func_800E97BC(s32 arg0, s32 arg1, s32 arg2) {
    char buffer[0x20];

    sprintf(buffer, g_MemcardSavePath, arg0, arg1, arg2);
    return -(erase(buffer) == 0);
}

s32 func_800E9804(s32 arg0) {
    s32 funcRet = func_800E912C();
    s32 ret = 0;

    if (funcRet != 0) {
        close(D_80137474);
        if (funcRet == 1) {
            D_8006C3AC |= funcRet << arg0;
            return 1;
        }
        ret = -3;
        return ret;
    }
    return ret;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/47BB8", func_800E9880);

s32 func_800E9B18(s32 arg0, s32 arg1) {
    char buffer[0x8];
    s32 ret;

    D_8006C3AC &= D_800A0510[arg0];
    sprintf(buffer, g_strMemcardRootPath, arg0, arg1);
    func_800E928C();
    format(buffer);
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

void StoreSaveData(SaveData* save, s32 arg1, s32 memcardIcon);
INCLUDE_ASM("asm/us/dra/nonmatchings/47BB8", StoreSaveData);

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

void func_800EA48C(char* dstSaveName, s32 saveSlot) {
    __builtin_memcpy(dstSaveName, aBaslus00067dra, sizeof(aBaslus00067dra));
    dstSaveName[0x10] += saveSlot / 10;
    dstSaveName[0x11] += saveSlot % 10;
}

extern Unkstruct_8006C3CC D_8006C3CC[];

void func_800EA538(s32 arg0) {
    Unkstruct_8006C3CC* var_v0;
    s32 temp;
    s32 v1;
    s32 i;

    // !FAKE: 0x8000 inside a temp is weird
    temp = 0x8000;
    v1 = (temp >> (arg0 - 1));

    if (arg0 != 0) {
        for (i = 0; i < 32; i++) {
            if (v1 & D_8006C3CC[i].unk0) {
                D_8006C3CC[i].unk0 = 0;
            }
        }
        return;
    }

    D_8003C0F8 = 0;
    var_v0 = &D_8006C3C4;

    for (i = 0; i < 32; i++) {
        var_v0->unk8 = 0;
        var_v0++;
    }
}

void func_800EA5AC(u16 arg0, u8 arg1, u8 arg2, u8 arg3) {
    D_8003C0EC[3] = arg0;
    D_8003C0EC[0] = arg1;
    D_8003C0EC[1] = arg2;
    D_8003C0EC[2] = arg3;
}

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/dra/nonmatchings/47BB8", func_800EA5E4);
#else
extern s32 D_8003C78C;
extern s32* D_800A3BB8[];

void func_800EA5E4(s32 arg0) {
    Unkstruct_8006C3CC* var_t0;
    s32 temp_a0;
    s32 temp_v0;
    s32 var_v1;
    s32 var_v1_2;
    u32 temp_a1;
    u32 temp_a2;
    u32 var_v1_3;
    u8 temp_v1_2;
    u8* var_a0_2;
    Unkstruct_800EA5E4* var_a0;
    u8* var_v0;

    temp_v0 = arg0 & 0xFF00;
    temp_a0 = arg0 & 0xFF;
    if (temp_v0 & 0x8000) {
        var_a0 = g_api.o.cluts[temp_a0];
    } else {
        var_a0 = D_800A3BB8[temp_a0];
    }
    if (var_a0->unk0 == 0 || var_a0->unk0 == -1) {
        return;
    }
    var_v1 = 0;
    var_t0 = D_8006C3C4;
    for (; var_v1 < 0x20; var_t0++, var_v1++) {
        if (var_t0->unk8 != 0)
            continue;
        var_t0->unk0 = var_a0->unk0;
        var_t0->unk4 = (void*)(var_a0 + 0xC);
        var_t0->unkA = 0;
        var_t0->unkC = 0;
        var_t0->unk8 = temp_v0 | var_a0->unk0;

        temp_a1 = var_a0->unk4;
        var_v1_2 = 0x2F;
        var_a0_2 = &var_t0->unk2F;
        temp_a2 = (u32)((temp_a1 + var_a0->unk8) - 1) >> 8;
        do {
            var_a0_2[0x10] = 0;
            var_v1_2 -= 1;
            var_a0_2 -= 1;
        } while (var_v1_2 >= 0);

        var_v1_3 = temp_a1 >> 8;
        var_v0 = var_t0 + var_v1_3;
        while (temp_a2 >= var_v1_3) {
            var_v0[0x10] = 1;
            var_v1_3++;
            var_v0 = var_t0 + var_v1_3;
        }

        temp_v1_2 = var_t0->unk8;
        if (temp_v1_2 == 2 || temp_v1_2 == 0x10) {
            var_t0->unkE = 0x1F;
        }
        break;
    }
}
#endif

INCLUDE_ASM("asm/us/dra/nonmatchings/47BB8", func_800EA720);

INCLUDE_ASM("asm/us/dra/nonmatchings/47BB8", func_800EA7CC);

s32 func_800EAD0C(void) { // the return type is needed for matching
    func_800EA5E4(4);
    func_800EA5E4(5);
    func_800EA5E4(6);
    func_800EA5E4(7);
    func_800EA5E4(8);

    if ((g_CurrentPlayableCharacter == PLAYER_ALUCARD) &&
        (g_StageId != STAGE_ST0)) {
        func_800EA5E4(0x17);
    }
}

void func_800EAD7C(void) {
    s32 index = 0;
    s32 i;
    s32 j;

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0x200; j < 0x300; j += 0x10) {
            D_8003C104[index++] = GetClut(j, i);
        }
    }

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0; j < 0x100; j += 0x10) {
            D_8003C104[index++] = GetClut(j, i);
        }
    }

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0x100; j < 0x200; j += 0x10) {
            D_8003C104[index++] = GetClut(j, i);
        }
    }
}

void func_800EAEA4(void) {
    u16* ptr;
    s32 i;

    for (ptr = D_801374F8, i = 0; i < 32; i++) {
        *ptr++ = ~0;
    }

    for (ptr = D_80137538, i = 0; i < 32; i++) {
        *ptr++ = ~0;
    }
}

void func_800EAEEC(void) {
    unkstruct_80072FA0* ptr = D_80072FA0;
    s32 i;

    for (i = 0; i < 16; i++, ptr++) {
        ptr->unk4 = 0;
    }

    func_800EAEA4();
}

// ASPSX jump to 'nop'
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/dra/nonmatchings/47BB8", func_800EAF28);
#else
void func_800EAF28(s32 arg0) {
    s32 temp_v1;
    s32 i;
    s32 new_var;
    Unsktruct_800EAF28* var_a1;
    unkstruct_80072FA0* var_a0;

    if (arg0 & 0x8000) {
        var_a1 = g_api.o.entityGfxs[arg0 & 0x7FFF];
    } else {
        var_a1 = D_800A3B5C[arg0];
    }

    temp_v1 = *(s32*)var_a1;
    if (temp_v1 != 0 && temp_v1 != (new_var = -1)) {
        for (i = 0; i < 0x10; i++) {
            var_a0 = &D_80072FA0[i];
            if (var_a0->unk4 == 0) {
                var_a0->unk4 = var_a1->unk0;
                var_a0->unk6 = 0;
                var_a0->unk8 = 0;
                var_a0->unk0 = var_a1 + 1;
                break;
            }
        }
    }
}
#endif

void DecompressWriteNibble(s32 ch) {
    u8 temp = ch;

    if (g_DecWriteNibbleFlag == 0) {
        g_DecWriteNibbleFlag = 1;
        *g_DecDstPtr = temp;
    } else {
        g_DecWriteNibbleFlag = 0;
        *g_DecDstPtr += ch * 16;
        g_DecDstPtr++;
    }
}

u32 DecompressReadNibble(void) {
    u8 ret;

    if (g_DecReadNibbleFlag != 0) {
        g_DecReadNibbleFlag = 0;
        ret = *g_DecSrcPtr;
        g_DecSrcPtr++;
        return (ret >> 0) & 0xF;
    } else {
        g_DecReadNibbleFlag = 1;
        ret = *g_DecSrcPtr;
        return (ret >> 4) & 0xF;
    }
}

// reg swap + fake stuff
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/dra/nonmatchings/47BB8", DecompressData);
#else
s32 DecompressData(u8* dst, u8* src) {
    u32 buf[8];
    s32 temp_s0;
    s32 ch;
    s32 temp_s1_3;
    s32 temp_s2;
    s32 temp_s2_2;
    s32 temp_s2_3;
    s32 temp_s2_4;
    s32 count;
    s32 i;
    s32 var_v1;
    s32* var_a0;
    u8* new_var;
    u8* srcptr;
    s32 op;
    srcptr = src;
    var_a0 = &buf;

    for (var_v1 = 0; var_v1 < 8; var_v1++) {
        *var_a0++ = *srcptr++;
    }

    g_DecReadNibbleFlag = 0;
    g_DecWriteNibbleFlag = 0;
    g_DecSrcPtr = srcptr;
    g_DecDstPtr = dst;
    while (count = true /*fake??*/) {
        op = DecompressReadNibble();
        switch (op) {
        case 0:
            do {
                temp_s2 = DecompressReadNibble();
                temp_s2_2 = DecompressReadNibble();
            } while (0);
            temp_s2_4 = temp_s2;
            temp_s2_3 = temp_s2_2;
            temp_s2_3 = temp_s2_4 * 0x10 + temp_s2_3 + 0x13;
            for (i = 0; i < temp_s2_3; i++) {
                DecompressWriteNibble(0);
            }
            break;
        case 2:
            temp_s0 = DecompressReadNibble();
            DecompressWriteNibble(temp_s0);
            DecompressWriteNibble(temp_s0);
            break;
        case 4:
            DecompressWriteNibble(DecompressReadNibble());
        case 3:
            DecompressWriteNibble(DecompressReadNibble());
        case 1:
            DecompressWriteNibble(DecompressReadNibble());
            break;
        case 5:
            temp_s1_3 = (ch = DecompressReadNibble());
            count = (op = DecompressReadNibble()) + 3;
            for (i = 0; i < count; i++) {
                temp_s2 = ch;
                DecompressWriteNibble(temp_s2 & 0xFF);
            }
            break;
        case 6:
            temp_s2 = DecompressReadNibble();
            count = temp_s2 + 3;
            for (i = 0; i < count; i++) {
                DecompressWriteNibble(0);
            }
            break;
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
            temp_s1_3 = (buf + op)[-7];
            switch (temp_s1_3 & 0xF0) {
            case 0x20:
                DecompressWriteNibble(temp_s1_3 & 0xF);
            case 0x10:
                DecompressWriteNibble(temp_s1_3 & 0xF);
                break;
            case 0x60:
                count = (temp_s1_3 & 0xF) + 3;
                for (i = 0; i < count; i++) {
                    DecompressWriteNibble(0);
                }
                break;
            }
            break;
        case 15:
            if ((dst + 0x2000) >= ((u32)g_DecDstPtr)) {
                return 0;
            }
            new_var = dst;
            return (g_DecDstPtr - new_var) + 0x2000;
        }
    }
}
#endif

INCLUDE_ASM("asm/us/dra/nonmatchings/47BB8", func_800EB314);

void func_800EB4F8(PixPattern* pix, s32 bitDepth, s32 x, s32 y) {
    LoadTPage(pix + 1, bitDepth, 0, x, y, (int)pix->w, (int)pix->h);
}

void func_800EB534(s32 equipIcon, s32 palette, s32 index) {
    u8* iconGfx;
    s32 vramX;
    s32 var_t0;
    s32 i;

    if (D_801374F8[index] != equipIcon) {
        iconGfx = g_GfxEquipIcon[equipIcon];
        vramX = ((index & 7) * 4) + 0x280;
        var_t0 = index;
        if (index < 0) {
            var_t0 = index + 7;
        }

        LoadTPage(iconGfx, 0, 0, vramX, (var_t0 >> 3) * 0x10 + 0x180, 16, 16);
    }

    if (D_80137538[index] != palette) {
        for (i = 0; i < 16; i++) {
            if (D_800705CC) { // FAKE
            }
            D_800705CC[index * 0x10 + i] = g_PalEquipIcon[palette * 0x10 + i];
        }

        LoadClut2(D_800705CC, 0, 0xFD);
        LoadClut2(D_800705CC + 0x100, 0, 0xFE);
    }
    if (D_800973EC == 0) {
        D_80137478[index] = equipIcon;
        D_801374B8[index] = palette;
    }
    D_801374F8[index] = equipIcon;
    D_80137538[index] = palette;
}

void func_800EB6B4(void) {
    s32 i;

    for (i = 0; i < 32; i++) {
        func_800EB534(D_80137478[i], D_801374B8[i], i);
    }
}

// https://decomp.me/scratch/n0Z3p match with -fforce-addr

bool func_800EB720(void) {
    unkstruct_80072FA0* temp = D_80072FA0;
    s32 i;

    for (i = 0; i < 16; i++) {
        if (temp[i].unk4 != 0) {
            return true;
        }
    }

    return false;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/47BB8", func_800EB758);

// clears out each entity struct 1 byte at a time
void func_800EBB70(void) {
    s8* byte;
    Entity* entity = &g_Entities[0];
    s32 i;
    u32 j;

    for (i = 0; i < ARRAY_COUNT(g_Entities); i++) {
        byte = (s8*)entity;
        for (j = 0; j < 188; j++) {
            byte[0] = 0;
            byte++;
        }
        entity++;
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/47BB8", func_800EBBAC);

// The loop at the end is weird, the rest is matching
#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/dra/nonmatchings/47BB8", func_800ECBF8);
#else
typedef struct {
    s16 unk00, unk02;
    u16 unk04, unk06;
    u16 unk08, unk0A;
    u16 unk0c, unk0E;
    u16 unk10, unk12;
    u16 unk14, unk16;
    u16 unk18, unk1A;
    u16 unk1c;
    u8 unk1E, unk1F;
    u16 unk20;
    u8 unk22, unk23;
    u16 unk24, unk26;
} Unkstruct_800ECBF8_1; /* size = 0x28 */

typedef struct {
    s16 unk0, unk4;
} Unkstruct_800ECBF8_2; /* size = 0x4 */

extern POLY_GT4 D_8004077C[0x300]; // TODO D_8003CB08.polyGT4
extern POLY_G4 D_8004A37C[0x100];  // TODO D_8003CB08.polyG4
extern POLY_GT3 D_8004C77C[0x30];  // TODO D_8003CB08.polyGT3
extern LINE_G2 D_8004CEFC[0x100];  // TODO D_8003CB08.lineG2
extern SPRT_16 D_8004E2FC[0x280];  // TODO D_8003CB08.sprite16
extern TILE D_80050AFC[0x100];     // TODO D_8003CB08.tiles
extern SPRT D_80051AFC[0x200];     // TODO D_8003CB08.sprite
extern POLY_GT4 D_80057F70[0x300]; // TODO D_800542FC.polyGT4
extern POLY_G4 D_80061B70[0x100];  // TODO D_80542FC8.polyG4
extern POLY_GT3 D_80063F70[0x30];  // TODO D_800542FC.polyGT3
extern LINE_G2 D_800646F0[0x100];  // TODO D_80542FC8.lineG2
extern SPRT_16 D_80065AF0[0x280];  // TODO D_8003542FCsprite16
extern TILE D_800682F0[0x100];     // TODO D_8542FC08.tiles
extern SPRT D_800692F0[0x200];     // TODO D_80542FC8.sprite
extern Unkstruct_800ECBF8_1 D_80097D1C[0x10];
extern Unkstruct_800ECBF8_2 D_800A21B8[0x10];

void func_800ECBF8(void) {
    int i;
    POLY_GT4 *a1, *a2;
    SPRT_16 *b1, *b2;
    TILE *c1, *c2;
    LINE_G2 *d1, *d2;
    POLY_G4 *e1, *e2;
    SPRT *f1, *f2;
    POLY_GT3 *g1, *g2;

    Unkstruct_800ECBF8_1* var_v1;
    Unkstruct_800ECBF8_2 *var_a2, *var_a0;

    for (a1 = D_8004077C, a2 = D_80057F70, i = 0; i < 0x300; i++, a1++, a2++) {
        SetPolyGT4(a1);
        SetPolyGT4(a2);
    }

    for (b1 = D_8004E2FC, b2 = D_80065AF0, i = 0; i < 0x280; i++, b1++, b2++) {
        SetSprt16(b1);
        SetSprt16(b2);
    }

    for (c1 = D_80050AFC, c2 = D_800682F0, i = 0; i < 0x100; i++, c1++, c2++) {
        SetTile(c1);
        SetTile(c2);
    }

    for (d1 = D_8004CEFC, d2 = D_800646F0, i = 0; i < 0x100; i++, d1++, d2++) {
        SetLineG2(d1);
        SetLineG2(d2);
    }

    for (e1 = D_8004A37C, e2 = D_80061B70, i = 0; i < 0x100; i++, e1++, e2++) {
        SetPolyG4(e1);
        SetPolyG4(e2);
    }

    for (f1 = D_80051AFC, f2 = D_800692F0, i = 0; i < 0x200; i++, f1++, f2++) {
        SetSprt(f1);
        SetSprt(f2);
    }

    for (g1 = D_8004C77C, g2 = D_80063F70, i = 0; i < 0x30; i++, g1++, g2++) {
        SetPolyGT3(g1);
        SetPolyGT3(g2);
    }

    var_v1 = &D_80097D1C;
    var_a0 = &D_800A21B8;
    i = 0;
    var_a2 = &D_800A21B8;
    for (; i < 16; var_a2++, i++, var_a0++, var_v1++) {
        var_v1->unk00 = var_a2->unk0;
        var_v1->unk02 = var_a0->unk4 & 0x1FF;
        var_v1->unk23 = (var_a0->unk4 >> 8) & ~1;
        var_v1->unk1F = (var_v1->unk00 >> 6) + 0x10;
    }
}
#endif

void func_800ECE2C(void) {
    s32 i;

    g_CurrentRoom.unk00 = 0;
    for (i = 0; i < MAX_BG_LAYER_COUNT; i++) {
        g_CurrentRoom.bg[i].D_800730F4 = 0;
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/47BB8", func_800ECE58);

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/dra/nonmatchings/47BB8", SetRoomForegroundLayer);
#else
extern s16 D_8003C70A;
extern s16 D_8003C70C;
extern u16 D_8003C70E;
extern s32 D_8007309C;
extern s32 D_8013AED0;

void SetRoomForegroundLayer(LayerDef2* layerDef) {
    D_8003C708 = 0;
    D_8013AED0 = 1;
    g_CurrentRoom.unk00 = 0;
    D_80073088 = layerDef->tileDef;
    if (layerDef->tileDef != NULL) {
        g_CurrentRoomTileLayout.fg = layerDef->layout;
        D_8007309C = (s32)layerDef->unkC;
        if (layerDef->rect.flags & 0x40) {
            D_8007309C = 0x60;
            D_8003C70A = 0;
            D_8003C70C = 0;
            D_8003C708 = (u16)layerDef->rect.flags;
            D_8003C70E = layerDef->unkC;
        }
        if (layerDef->rect.flags & 0x20) {
            D_8007309C = 0x60;
            D_8003C708 = (u16)layerDef->rect.flags;
        }
        if (layerDef->rect.flags & 0x10) {
            D_8007309C = 0x60;
            D_8013AED0 = 0;
        }
        g_CurrentRoom.unk00 = (s32)layerDef->unkE;
        g_CurrentRoom.left = layerDef->rect.left;
        g_CurrentRoom.top = layerDef->rect.top;
        g_CurrentRoom.right = layerDef->rect.right;
        g_CurrentRoom.hSize = (g_CurrentRoom.right - g_CurrentRoom.left) + 1;
        g_CurrentRoom.y = 0;
        g_CurrentRoom.x = 0;
        g_CurrentRoom.width = g_CurrentRoom.hSize << 8;
        g_CurrentRoom.D_800730AC = 1;
        g_CurrentRoom.bottom = layerDef->rect.bottom;
        g_CurrentRoom.vSize = (layerDef->rect.bottom - layerDef->rect.top) + 1;
        g_CurrentRoom.height = g_CurrentRoom.vSize << 8;
    }
}
#endif

void SetRoomBackgroundLayer(s32 index, LayerDef2* layerDef) {
    u32 rect;

    g_CurrentRoom.bg[index].D_800730F4 = 0;
    g_CurrentRoom.bg[index].tileDef = layerDef->tileDef;
    g_CurrentRoom.bg[index].layout = layerDef->layout;
    if (g_CurrentRoom.bg[index].tileDef != 0) {
        g_CurrentRoom.bg[index].zPriority = layerDef->zPriority;
        g_CurrentRoom.bg[index].D_800730F4 = layerDef->unkE;
#if 0 // matches with PSY-Q 3.5
        g_CurrentRoom.bg[index].w = layerDef->rect.right - layerDef->rect.left + 1;
        g_CurrentRoom.bg[index].h = layerDef->rect.bottom - layerDef->rect.top + 1;
#else
        rect = *(u32*)&layerDef->rect;
        g_CurrentRoom.bg[index].w = ((rect >> 12) & 0x3F) - (rect & 0x3F) + 1;
        rect = *(u32*)&layerDef->rect;
        g_CurrentRoom.bg[index].h =
            ((rect >> 18) & 0x3F) - ((rect >> 6) & 0x3F) + 1;
#endif
        g_CurrentRoom.bg[index].flags = layerDef->rect.flags;
        g_CurrentRoom.bg[index].D_80073100 = 1;
    }
}

void LoadRoomLayer(s32 arg0) {
    s32 i;

    SetRoomForegroundLayer(g_api.o.tileLayers[arg0].fg);
    SetRoomBackgroundLayer(0, g_api.o.tileLayers[arg0].bg);

    for (i = 1; i < MAX_BG_LAYER_COUNT; i++) {
        g_CurrentRoom.bg[i].D_800730F4 = 0;
    }
}

void func_800EDA70(Primitive* prim) {
    s32 i;
    s32 n;
    u32* primData = (u32*)prim;

    for (n = sizeof(Primitive) / sizeof(*primData), i = 0; i < n; i++) {
        *primData++ = 0;
    }
}

void func_800EDA94(void) {
    Primitive* prim;
    s32 i;

    for (i = 0, prim = g_PrimBuf; i < MAX_PRIM_COUNT; i++) {
        func_800EDA70(prim);
        prim->type = PRIM_NONE;
        prim++;
    }
}

void func_800EDAE4(void) {
    s32 i;
    DR_ENV* ptr = &D_800974AC;

    for (i = 0; i < 16; i++, ptr++) {
        ptr->tag = 0;
    }
}

DR_ENV* func_800EDB08(POLY_GT4* poly) {
    DR_ENV* ptr = &D_800974AC;
    s32 i = 0;

    for (; i < 0x10; i++, ptr++) {
        if (ptr->tag == 0) {
            ptr->tag = 1;
            setcode(poly, 7);
            *(u32*)&poly->r1 = (u32)ptr; // similar issue as FreePrimitives
            return ptr;
        }
    }

    return NULL;
}

s16 func_800EDB58(u8 primType, s32 count) {
    Primitive* prim;
    Primitive* temp_v0;
    bool isLooping;
    s32 primStartIdx;
    s32 var_s1;
    s32 i;
    s32 var_v1;

    var_v1 = count;
    primStartIdx = 0;
    i = 0;
    prim = g_PrimBuf;
    isLooping = 1;
    while (isLooping) {
        var_v1--;
        if (prim->type != 0) {
            var_v1 = i;
            primStartIdx = var_v1 + 1;
            var_v1 = count;
        } else if (var_v1 == 0) {
            break;
        }
        var_s1 = i + 1;
        prim++;
        i++;
        isLooping = i < 0x400;
        if (isLooping) {
            continue;
        }
        if (var_v1 != 0) {
            return -1;
        }
    }

    for (i = 0, prim = &g_PrimBuf[primStartIdx]; i < count; i++, prim++) {
        func_800EDA70(prim);
        var_s1 = 0;
        temp_v0 = &g_PrimBuf[i];
        prim->type = primType;
        prim->next = temp_v0;
        prim->next = prim->next + primStartIdx + 1;
    }
    prim[-1].next = NULL;
    prim[-1].type &= 0xEF;

    return primStartIdx;
}

s32 AllocPrimitives(u8 primType, s32 count) {
    s32 primIndex = 0;
    Primitive* prim = g_PrimBuf;
    u8* dstPrimType = &g_PrimBuf->type;
    s16 index;

    while (primIndex < MAX_PRIM_ALLOC_COUNT) {
        if (*dstPrimType == 0) {
            func_800EDA70(prim);
            if (count == 1) {
                *dstPrimType = primType;
                prim->next = NULL;
                if (D_800A2438 < primIndex) {
                    D_800A2438 = primIndex;
                }
            } else {
                *dstPrimType = primType;
                index = AllocPrimitives(primType, count - 1);
                if (index == -1) {
                    *dstPrimType = 0;
                    return -1;
                }
                prim->next = &g_PrimBuf[index];
            }
            return (s16)primIndex;
        }

        primIndex++;
        dstPrimType += sizeof(Primitive);
        prim++;
        if (primIndex >= 0x400) {
            return -1;
        }
    }
    return -1;
}

s32 func_800EDD9C(u8 primitives, s32 count) {
    u8* pCode;
    u8 temp_v0;
    u8* polyCode;
    POLY_GT4* poly;
    s32 polyIndex;
    s16 foundPolyIndex;
    poly = D_800973B8;
    polyIndex = 0x4FF;
    polyCode = &D_800973B8->code;

    while (polyIndex >= 0) {
        pCode = &poly->code;
        temp_v0 = *polyCode;
        if (temp_v0 == 0) {
            func_800EDA70(poly);
            if (count == 1) {
                *polyCode = primitives;
                poly->tag = 0;
            } else {
                *polyCode = primitives;
                foundPolyIndex = func_800EDD9C(primitives, count - 1);
                poly->tag = &g_PrimBuf[foundPolyIndex];
            }
            foundPolyIndex = polyIndex;
            return foundPolyIndex;
        }
        polyIndex--;
        polyCode -= sizeof(POLY_GT4);
        poly--;
        if (polyIndex < 0) {
            return (s16)temp_v0;
        }
    }
    return (s16)temp_v0;
}

void FreePrimitives(s32 primitiveIndex) {
    Primitive* prim = &g_PrimBuf[primitiveIndex];

    if (prim) {
        do {
            if (prim->type == PRIM_ENV) {
                *(*(s32**)&prim->r1) = 0;
                prim->type = PRIM_NONE;
            } else
                prim->type = PRIM_NONE;
            prim = prim->next;
        } while (prim);
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/47BB8", func_800EDEDC);
