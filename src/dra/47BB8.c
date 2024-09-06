// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"
#include "lba.h"

s32 g_SimVabId = 0;

SimFile D_800A024C[] = {
    {
        "sim:c:\\bin\\f_title1.bin",
        0x80280000,
        0x00042000,
        13,
    },
    {
        "sim:c:\\bin\\f_game.bin",
        0x80180000,
        0x00042000,
        1,
    },
    {
        "sim:c:\\bin\\f_title0.bin",
        0x80280000,
        0x00042000,
        2,
    },
    {
        "sim:c:\\bin\\face.bin",
        0x80180000,
        0x0001C000,
        6,
    },
    {
        "sim:c:\\bin\\arc_f.bin",
        0x8013C000,
        0x00034000,
        8,
    },
    {
        "sim:c:\\bin\\ric.bin",
        0x8013C000,
        0x00044000,
        8,
    },
    {
        "sim:c:\\bin\\f_prolo0.bin",
        0x80280000,
        0x00042000,
        11,
    },
    {
        "sim:c:\\bin\\f_prolo1.bin",
        0x80280000,
        0x00042000,
        12,
    },
    {
        "sim:c:\\bin\\gof.bin",
        0x80280000,
        0x00008000,
        14,
    },
    {
        "sim:c:\\bin\\gob.bin",
        0x80280000,
        0x00010000,
        15,
    },
    {
        "sim:c:\\bin\\c_gof.bin",
        0x80280000,
        0x00002000,
        16,
    },
    {
        "sim:c:\\bin\\c_gob.bin",
        0x80280000,
        0x00002000,
        17,
    },
    {
        "sim:c:\\bin\\f_sel.bin",
        0x80280000,
        0x00042000,
        2,
    },
    {
        "sim:c:\\bin\\f_game2.bin",
        0x80180000,
        0x00042000,
        1,
    },
    {
        "sim:c:\\bin\\edf.bin",
        0x80280000,
        0x00002000,
        21,
    },
    {
        "sim:c:\\bin\\edb.bin",
        0x80280000,
        0x00010000,
        15,
    },
    {
        "sim:c:\\bin\\c_edf.bin",
        0x80280000,
        0x00002000,
        16,
    },
    {
        "sim:c:\\bin\\c_edb.bin",
        0x80280000,
        0x00002000,
        17,
    },
};

SimFile D_800A036C[] = {
    {
        "sim:c:\\sound\\data\\sd_alk.vh",
        aPbav_0,
        SD_ALK_VH_LEN,
        SIM_VH,
    },
    {
        "sim:c:\\sound\\data\\sd_alk.vb",
        0x80280000,
        SD_ALK_VB_LEN,
        SIM_VB,
    },
    {
        "sim:c:\\sound\\data\\sd_rih.vh",
        aPbav_0,
        SD_RIH_VH_LEN,
        SIM_VH,
    },
    {
        "sim:c:\\sound\\data\\sd_rih.vb",
        0x80280000,
        SD_RIH_VB_LEN,
        SIM_VB,
    },
    {
        "sim:c:\\sound\\data\\sd_mar.vh",
        aPbav_1,
        SD_MAR_VH_LEN,
        SIM_VH,
    },
    {
        "sim:c:\\sound\\data\\sd_mar.vb",
        0x80280000,
        SD_MAR_VB_LEN,
        SIM_VB,
    },
    {
        "sim:c:\\sound\\data\\sd_tuka2.vh",
        aPbav_1,
        SD_TUKA2_VH_LEN,
        SIM_VH,
    },
    {
        "sim:c:\\sound\\data\\sd_tuka2.vb",
        0x80280000,
        SD_TUKA2_VB_LEN,
        SIM_VB,
    },
    {
        "sim:c:\\sound\\data\\sd_tuka2.vh",
        aPbav_1,
        SD_TUKA2_VH_LEN,
        SIM_VH,
    },
    {
        "sim:c:\\sound\\data\\sd_tuka2.vb",
        0x80280000,
        SD_TUKA2_VB_LEN,
        SIM_VB,
    },
    {
        "sim:c:\\sound\\data\\sd_tuka1.vh",
        aPbav_1,
        SD_TUKA1_VH_LEN,
        SIM_VH,
    },
    {
        "sim:c:\\sound\\data\\sd_tuka1.vb",
        0x80280000,
        SD_TUKA1_VB_LEN,
        SIM_VB,
    },
    {
        "sim:c:\\sound\\data\\sd_koa1.vh",
        aPbav_1,
        SD_KOA1_VH_LEN,
        SIM_VH,
    },
    {
        "sim:c:\\sound\\data\\sd_koa1.vb",
        0x80280000,
        SD_KOA1_VB_LEN,
        SIM_VB,
    },
    {
        "sim:c:\\sound\\data\\sd_mak.vh",
        aPbav_1,
        SD_MAK_VH_LEN,
        SIM_VH,
    },
    {
        "sim:c:\\sound\\data\\sd_mak.vb",
        0x80280000,
        SD_MAK_VB_LEN,
        SIM_VB,
    },
    {
        "sim:c:\\sound\\data\\sd_tuka2.vh",
        aPbav_1,
        SD_TUKA2_VH_LEN,
        SIM_VH,
    },
    {
        "sim:c:\\sound\\data\\sd_tuka2.vb",
        0x80280000,
        SD_TUKA2_VB_LEN,
        SIM_VB,
    },
    {
        "sim:c:\\sound\\data\\sd_koa2.vh",
        aPbav_1,
        SD_KOA2_VH_LEN,
        SIM_VH,
    },
    {
        "sim:c:\\sound\\data\\sd_koa2.vb",
        0x80280000,
        SD_KOA2_VB_LEN,
        SIM_VB,
    },
};

SimFile D_800A04AC[] = {
    {
        "sim:c:\\sound\\data\\sd_eve1.seq",
        aPqes_1,
        0x00001EB3,
        SIM_SEQ,
    },
    {
        "sim:c:\\sound\\data\\sd_eve3.seq",
        aPqes_1,
        0x00000178,
        SIM_SEQ,
    },
};

u16 D_800A04CC[] = {
    0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
};

u32 D_800A04EC = 0;
u32 D_800A04F0 = 0;
u32 D_800A04F4 = 0;
u32 D_800A04F8 = 0;
u32 D_800A04FC = 0;
RECT D_800A0500 = {112, 32, 128, 1};
RECT D_800A0508 = {368, 32, 128, 1};

// BSS
extern SimFile* g_SimFile;
extern SimFile D_80136450;
extern s16 D_80136460[VSYNC_UNK_LEN];
extern s16 D_80136C60[VSYNC_UNK_LEN];

void VSyncHandler(void) {
    RECT* rect;

    D_800A04F4++;
    D_800A04F8 = (D_800A04F4 / 4) % 32;
    nullsub_10();
    if (D_800A04F0) {
        return;
    }

    switch (D_800A04EC) {
    case 0:
        break;
    case 2:
        D_80136460[D_800A04FC * 2] |= 0xFF00;
        rect = &D_800A0500;
        if (g_CurrentBuffer->disp.disp.x == 0) {
            rect = &D_800A0508;
        }
        LoadImage(rect, D_80136460);
        if (D_800A04FC < VSYNC_UNK_LEN) {
            D_800A04FC++;
        }
        break;
    case 1:
    case 3:
        D_800A04FC = 0;
        D_800A04EC++;
        break;
    case 4:
        D_80136460[D_800A04FC * 2] |= 0x00FF;
        rect = &D_800A0500;
        if (g_CurrentBuffer->disp.disp.x == 0) {
            rect = &D_800A0508;
        }
        LoadImage(rect, D_80136460);
        if (D_800A04FC < VSYNC_UNK_LEN) {
            D_800A04FC++;
        }
        break;
    }
    D_800A04F0 = 0;
}

void func_800E7D08(void) {
    s32 i;

    for (i = 0; i < VSYNC_UNK_LEN; i++) {
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
s32 LoadFileSimToMem(SimKind kind) {
    char pad[0x20];
    s32 i;
    u32* pDst;
    u32* pSrc;
    u16* clutAddr;

    switch (kind) {
    case SIM_STAGE_PRG:
        pSrc = STAGE_PRG_PTR;
        i = 0;
        pDst = &g_api.o;
        do {
            i++;
            *pDst++ = *pSrc++;
        } while (i < (s32)(sizeof(Overlay) / sizeof(void*)));
        break;
    case SIM_FAMILIAR_CHR:
        LoadTPage(SIM_CHR0, 0, 0, 0x2C0, 0x100, 0x100, 0x80);
        LoadTPage(SIM_CHR1, 0, 0, 0x2C0, 0x180, 0x80, 0x80);
        break;
    case SIM_WEAPON0_CHR:
        LoadTPage(g_Pix[0], 0, 0, 0x240, 0x100, 0x100, 0x80);
        break;
    case SIM_WEAPON1_CHR:
        LoadTPage(g_Pix[2], 0, 0, 0x240, 0x180, 0x100, 0x80);
        break;
    case SIM_MONSTER:
        LoadTPage(SIM_CHR0, 2, 0, 0x20, 0x100, 0x60, 0x70);
        break;
    case SIM_1:
        LoadStageTileset(STAGE_PRG_PTR, 0x100);
        DrawSync(0);
        LoadImage(&g_Vram.D_800ACD98, D_800A04CC);
        LoadImage(&g_Vram.D_800ACDA8, 0x801C0000);
        while (DrawSync(1)) {
        }
        StoreImage(&g_Vram.D_800ACDA8, g_Clut + 0x1000);
        break;
    case SIM_STAGE_CHR:
    case SIM_11:
        LoadStageTileset(SIM_CHR0, 0);
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
    case SIM_12:
    case SIM_13:
        LoadStageTileset(SIM_CHR0, 0x100);
        if (kind == 13) {
            LoadImage(&g_Vram.D_800ACD98, D_800A04CC);
        }
        DrawSync(0);
        break;
    case SIM_VH:
        while (SsVabTransCompleted(SS_IMEDIATE) != 1) {
        }
        if (SsVabOpenHeadSticky(
                g_SimFile->addr, g_SimVabId, g_VabAddrs[g_SimVabId]) < 0) {
            return -1;
        }
        break;
    case SIM_VB:
        if (SsVabTransBodyPartly(SIM_PTR, g_SimFile->size, g_SimVabId) == -1) {
            return -1;
        }
        while (SsVabTransCompleted(SS_IMEDIATE) != 1) {
        }
        break;
    case SIM_SEQ:
        if (g_StageId == STAGE_LIB) {
            func_80131EBC(aPqes_1, 0x202);
        }
        if (g_StageId == STAGE_DAI) {
            func_80131EBC(aPqes_1, 0x204);
        }
        break;
    case SIM_6:
        LoadImage(&g_Vram.D_800ACDC0, STAGE_PRG_PTR);
        break;
    case SIM_14:
        LoadImage(&g_Vram.D_800ACDD0, SIM_PTR);
        break;
    case SIM_21:
        LoadImage(&g_Vram.D_800ACDE0, SIM_PTR);
        break;
    case SIM_15:
        LoadImage(&g_Vram.D_800ACDD8, SIM_PTR);
        break;
    case SIM_16:
        LoadImage(&g_Vram.D_800ACDB8, SIM_PTR);
        StoreImage(&g_Vram.D_800ACDB8, g_Clut + 0x2000);
        break;
    case SIM_17:
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
        g_SimFile->kind = SIM_STAGE_PRG;
    }
    if (type == SimFileType_Vh) {
        if (fileId & 0x8000) {
            g_SimFile = &D_800A036C[fileId & 0x7FFF];
        } else {
            STRCPY(buf, "sim:c:\\sound\\data\\sd_");
            g_SimFile = &D_80136450;
            strcat(buf, g_StagesLba[g_StageId].name);
            strcat(buf, ".vh");
            g_SimFile->addr = aPbav_2;
            g_SimFile->path = buf;
            g_SimFile->size = g_StagesLba[g_StageId].vhLen;
            g_SimFile->kind = SIM_VH;
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
            g_SimFile->kind = SIM_VB;
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
        g_SimFile->kind = SIM_STAGE_CHR;
    }
    if (type == SimFileType_Weapon0Prg) {
        g_SimFile = &D_80136450;
        STRCPY(buf, "sim:c:\\bin\\w0_000.bin");
        buf[15] = ((fileId / 10) % 10) + '0';
        buf[16] = (fileId % 10) + '0';
        g_SimFile->path = buf;
        g_SimFile->size = 0x3000;
        g_SimFile->addr = WEAPON0_PTR;
        g_SimFile->kind = SIM_WEAPON_PRG;
    }
    if (type == SimFileType_Weapon1Prg) {
        g_SimFile = &D_80136450;
        STRCPY(buf, "sim:c:\\bin\\w1_000.bin");
        buf[15] = ((fileId / 10) % 10) + '0';
        buf[16] = (fileId % 10) + '0';
        g_SimFile->path = buf;
        g_SimFile->addr = WEAPON1_PTR;
        g_SimFile->size = 0x3000;
        g_SimFile->kind = SIM_WEAPON_PRG;
    }
    if (type == SimFileType_Weapon0Chr) {
        g_SimFile = &D_80136450;
        STRCPY(buf, "sim:c:\\bin\\f0_000.bin");
        buf[15] = ((fileId / 10) % 10) + '0';
        buf[16] = (fileId % 10) + '0';
        g_SimFile->path = buf;
        g_SimFile->addr = g_Pix[0];
        g_SimFile->size = 0x4000;
        g_SimFile->kind = SIM_WEAPON0_CHR;
    }
    if (type == SimFileType_Weapon1Chr) {
        g_SimFile = &D_80136450;
        STRCPY(buf, "sim:c:\\bin\\f1_000.bin");
        buf[15] = ((fileId / 10) % 10) + '0';
        buf[16] = (fileId % 10) + '0';
        g_SimFile->path = buf;
        g_SimFile->addr = g_Pix[2];
        g_SimFile->size = 0x4000;
        g_SimFile->kind = SIM_WEAPON1_CHR;
    }
    if (type == SimFileType_FamiliarPrg) {
        g_SimFile = &D_80136450;
        STRCPY(buf, "sim:c:\\bin\\tt_000.bin");
        buf[16] = (fileId % 10) + '0';
        g_SimFile->path = buf;
        g_SimFile->addr = FAMILIAR_PTR;
        g_SimFile->size = 0xA000;
        g_SimFile->kind = SIM_FAMILIAR_PRG;
    }
    if (type == SimFileType_FamiliarChr) {
        g_SimFile = &D_80136450;
        STRCPY(buf, "sim:c:\\bin\\ft_000.bin");
        buf[16] = (fileId % 10) + '0';
        g_SimFile->path = buf;
        g_SimFile->addr = SIM_PTR;
        g_SimFile->size = 0x6000;
        g_SimFile->kind = SIM_FAMILIAR_CHR;
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
        g_SimFile->kind = SIM_MONSTER;
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
    if (LoadFileSimToMem(g_SimFile->kind) < 0) {
        FntPrint("tr err\n");
        D_800A04EC = 0;
        return -1;
    }
    D_800A04EC = 0;
    return 0;
}
