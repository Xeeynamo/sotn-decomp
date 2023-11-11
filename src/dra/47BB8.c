#include "dra.h"
#include "objects.h"
#include "sfx.h"

extern const char aPqes_1[]; // TODO: import rodata

s32 DecompressData(u8* dst, u8* src);

INCLUDE_ASM("dra/nonmatchings/47BB8", func_800E7BB8);

void func_800E7D08(void) {
    s32 i;

    for (i = 0; i < 1024; i++) {
        D_80136460[i] = 0;
        D_80136C60[i] = 0;
    }

    D_800A04EC = 1;
}

void LoadStageTileset(u8* pTilesetData, s32 y) {
    RECT rect;
    u8* pTilesetDataSrc;
    s32 i;

    rect.w = 0x20;
    rect.h = 0x80;
    for (i = 0; i < 0x20; i++) {
        pTilesetDataSrc = pTilesetData + 0x2000 * i;
        rect.x = D_800AC958[i];
        if (i & 2) {
            rect.y = y + 0x80;
        } else {
            rect.y = y;
        }

        LoadImage(&rect, pTilesetDataSrc);
        while (DrawSync(1)) {
        }
    }
}

// Equivalent of CdStep_6 with their g_CdCallback but for the sim device
s32 LoadFileSimToMem(u32 kind) {
    char pad[0x20];
    s32 i;
    u32* pDst;
    u32* pSrc;
    u16* clutAddr;

    switch (kind) {
    case 0:
        pSrc = STAGE_PRG_PTR;
        i = 0;
        pDst = &g_api.o;
        do {
            i++;
            *pDst++ = *pSrc++;
        } while (i < (s32)(sizeof(Overlay) / sizeof(void*)));
        break;
    case 19:
        LoadTPage(SIM_PTR, 0, 0, 0x2C0, 0x100, 0x100, 0x80);
        LoadTPage(0x80284000, 0, 0, 0x2C0, 0x180, 0x80, 0x80);
        break;
    case 9:
        LoadTPage(g_Pix[0], 0, 0, 0x240, 0x100, 0x100, 0x80);
        break;
    case 10:
        LoadTPage(g_Pix[2], 0, 0, 0x240, 0x180, 0x100, 0x80);
        break;
    case 20:
        LoadTPage(SIM_PTR, 2, 0, 0x20, 0x100, 0x60, 0x70);
        break;
    case 1:
        LoadStageTileset(STAGE_PRG_PTR, 0x100);
        DrawSync(0);
        LoadImage(&g_Vram.D_800ACD98, D_800A04CC);
        LoadImage(&g_Vram.D_800ACDA8, 0x801C0000);
        while (DrawSync(1)) {
        }
        StoreImage(&g_Vram.D_800ACDA8, g_Clut + 0x1000);
        break;
    case 2:
    case 11:
        LoadStageTileset(SIM_PTR, 0);
        DrawSync(0);
        clutAddr = g_Clut;
        StoreImage(&g_Vram.D_800ACDB8, clutAddr);
        if (kind == 11) {
            clutAddr += 0x2000;
            StoreImage(&g_Vram.D_800ACDB8, clutAddr);
            DrawSync(0);
            LoadImage(&g_Vram.D_800ACDB0, clutAddr);
        }
        break;
    case 12:
    case 13:
        LoadStageTileset(SIM_PTR, 0x100);
        if (kind == 13) {
            LoadImage(&g_Vram.D_800ACD98, D_800A04CC);
        }
        DrawSync(0);
        break;
    case 4:
        while (SsVabTransCompleted(SS_IMEDIATE) != 1) {
        }
        if (SsVabOpenHeadSticky(
                g_SimFile->addr, g_SimVabId, g_VabAddrs[g_SimVabId]) < 0) {
            return -1;
        }
        break;
    case 5:
        if (SsVabTransBodyPartly(SIM_PTR, g_SimFile->size, g_SimVabId) == -1) {
            return -1;
        }
        while (SsVabTransCompleted(SS_IMEDIATE) != 1) {
        }
        break;
    case 7:
        if (g_StageId == STAGE_LIB) {
            func_80131EBC(aPqes_1, 0x202);
        }
        if (g_StageId == STAGE_DAI) {
            func_80131EBC(aPqes_1, 0x204);
        }
        break;
    case 6:
        LoadImage(&g_Vram.D_800ACDC0, STAGE_PRG_PTR);
        break;
    case 14:
        LoadImage(&g_Vram.D_800ACDD0, SIM_PTR);
        break;
    case 21:
        LoadImage(&g_Vram.D_800ACDE0, SIM_PTR);
        break;
    case 15:
        LoadImage(&g_Vram.D_800ACDD8, SIM_PTR);
        break;
    case 16:
        LoadImage(&g_Vram.D_800ACDB8, SIM_PTR);
        StoreImage(&g_Vram.D_800ACDB8, g_Clut + 0x2000);
        break;
    case 17:
        LoadImage(&g_Vram.D_800ACDA8, SIM_PTR);
        StoreImage(&g_Vram.D_800ACDA8, g_Clut);
        break;
    }
    return 0;
}

s32 LoadFileSim(s32 fileId, SimFileType type) {
    char buf[33];
    s32 fid;

    func_800E7D08();
    D_800A04EC = 1;
    g_SimFile = &D_800A024C[fileId];
    if (type == SimFileType_StagePrg) {
        STRCPY(buf, "sim:c:\\bin\\");
        g_SimFile = &D_80136450;
        strcat(buf, g_StagesLba[g_StageId].ovlName);
        strcat(buf, ".bin");
        g_SimFile->addr = STAGE_PRG_PTR;
        g_SimFile->path = buf;
        g_SimFile->size = 0x60000;
        g_SimFile->type = 0;
    }
    if (type == SimFileType_Vh) {
        if (fileId & 0x8000) {
            g_SimFile = &D_800A036C[fileId & 0x7FFF];
        } else {
            STRCPY(buf, "sim:c:\\sound\\data\\sd_");
            g_SimFile = &D_80136450;
            strcat(buf, g_StagesLba[g_StageId].name);
            strcat(buf, ".vh");
            g_SimFile->addr = (u8*)aPbav_2;
            g_SimFile->path = buf;
            g_SimFile->size = g_StagesLba[g_StageId].vhLen;
            g_SimFile->type = 4;
        }
        if (g_SimFile->addr == aPbav) {
            g_SimVabId = 0;
        }
        if (g_SimFile->addr == aPbav_0) {
            g_SimVabId = 1;
        }
        if (g_SimFile->addr == aPbav_2) {
            g_SimVabId = 3;
        }
        if (g_SimFile->addr == aPbav_1) {
            g_SimVabId = 2;
        }
        SsVabClose(g_SimVabId);
    }
    if (type == SimFileType_Vb) {
        if (fileId & 0x8000) {
            g_SimFile = &D_800A036C[fileId & 0x7FFF];
        } else {
            g_SimFile = &D_80136450;
            STRCPY(buf, "sim:c:\\sound\\data\\sd_");
            strcat(buf, g_StagesLba[g_StageId].name);
            strcat(buf, ".vb");
            g_SimFile->addr = SIM_PTR;
            g_SimFile->path = buf;
            g_SimFile->size = g_StagesLba[g_StageId].vbLen;
            g_SimFile->type = 5;
        }
    }
    if (type == SimFileType_Seq) {
        g_SimFile = &D_800A04AC[fileId];
    }
    if (type == SimFileType_StageChr) {
        g_SimFile = &D_80136450;
        STRCPY(buf, "sim:c:\\bin\\");
        strcat(buf, g_StagesLba[g_StageId].gfxName);
        strcat(buf, ".bin");
        g_SimFile->addr = SIM_PTR;
        g_SimFile->size = 0x40000;
        g_SimFile->path = buf;
        g_SimFile->type = 2;
    }
    if (type == SimFileType_Weapon0Prg) {
        g_SimFile = &D_80136450;
        STRCPY(buf, "sim:c:\\bin\\w0_000.bin");
        buf[15] = ((fileId / 10) % 10) + '0';
        buf[16] = (fileId % 10) + '0';
        g_SimFile->path = buf;
        g_SimFile->size = 0x3000;
        g_SimFile->addr = WEAPON0_PTR;
        g_SimFile->type = 8;
    }
    if (type == SimFileType_Weapon1Prg) {
        g_SimFile = &D_80136450;
        STRCPY(buf, "sim:c:\\bin\\w1_000.bin");
        buf[15] = ((fileId / 10) % 10) + '0';
        buf[16] = (fileId % 10) + '0';
        g_SimFile->path = buf;
        g_SimFile->addr = WEAPON1_PTR;
        g_SimFile->size = 0x3000;
        g_SimFile->type = 8;
    }
    if (type == SimFileType_Weapon0Chr) {
        g_SimFile = &D_80136450;
        STRCPY(buf, "sim:c:\\bin\\f0_000.bin");
        buf[15] = ((fileId / 10) % 10) + '0';
        buf[16] = (fileId % 10) + '0';
        g_SimFile->path = buf;
        g_SimFile->addr = g_Pix[0];
        g_SimFile->size = 0x4000;
        g_SimFile->type = 9;
    }
    if (type == SimFileType_Weapon1Chr) {
        g_SimFile = &D_80136450;
        STRCPY(buf, "sim:c:\\bin\\f1_000.bin");
        buf[15] = ((fileId / 10) % 10) + '0';
        buf[16] = (fileId % 10) + '0';
        g_SimFile->path = buf;
        g_SimFile->addr = g_Pix[2];
        g_SimFile->size = 0x4000;
        g_SimFile->type = 10;
    }
    if (type == SimFileType_FamiliarPrg) {
        g_SimFile = &D_80136450;
        STRCPY(buf, "sim:c:\\bin\\tt_000.bin");
        buf[16] = (fileId % 10) + '0';
        g_SimFile->path = buf;
        g_SimFile->addr = FAMILIAR_PTR;
        g_SimFile->size = 0xA000;
        g_SimFile->type = 18;
    }
    if (type == SimFileType_FamiliarChr) {
        g_SimFile = &D_80136450;
        STRCPY(buf, "sim:c:\\bin\\ft_000.bin");
        buf[16] = (fileId % 10) + '0';
        g_SimFile->path = buf;
        g_SimFile->addr = SIM_PTR;
        g_SimFile->size = 0x6000;
        g_SimFile->type = 19;
    }
    if (type == SimFileType_Monster) {
        g_SimFile = &D_80136450;
        STRCPY(buf, "sim:c:\\bin\\mo_000.bin");
        buf[14] = fileId / 100 + '0';
        buf[15] = fileId / 10 - fileId / 100 * 10 + '0';
        buf[16] = fileId % 10 + '0';
        g_SimFile->path = buf;
        g_SimFile->addr = SIM_PTR;
        g_SimFile->size = 0x5800;
        g_SimFile->type = 20;
    }

    fid = open(g_SimFile->path, O_RDONLY);
    if (fid < 0) {
        FntPrint("o err:%s\n", g_SimFile->path);
        D_800A04EC = 0;
        return -1;
    }
    if (read(fid, g_SimFile->addr, g_SimFile->size) < 0) {
        FntPrint("r err\n");
        D_800A04EC = 0;
        return -1;
    }
    if (close(fid) < 0) {
        FntPrint("cl err\n");
        D_800A04EC = 0;
        return -1;
    }
    if (LoadFileSimToMem(g_SimFile->type) < 0) {
        FntPrint("tr err\n");
        D_800A04EC = 0;
        return -1;
    }
    D_800A04EC = 0;
    return 0;
}

void ResetPadsRepeat(void) {
    s8* ptr;
    s32 i;

    g_pads[0].repeat = 0;
    ptr = g_PadsRepeatTimer;

    for (i = 0; i < LEN(g_PadsRepeatTimer); i++) {
        *ptr++ = 0x10;
    }
}

void UpdatePadsRepeat(void) {
    u16 button = 1;
    u16 repeat = 0;
    u16 unk = g_pads[0].tapped;
    u16 pressed = g_pads[0].pressed;
    u8* timers = g_PadsRepeatTimer;
    s32 i = 0;

    while (i < 0x10) {
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
    }
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
    ResetPadsRepeat();
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
    UpdatePadsRepeat();
}
