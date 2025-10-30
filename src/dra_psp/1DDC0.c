// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"
#include "lba.h"

extern u_long D_8D6DC40;
extern s32 D_8B42064;
extern char* D_psp_08B42060;
extern u8 g_ServantDesc;
extern s32 g_UserLanguage;

s32 g_SimVabId = 0;

SimFile D_800A024C[] = {
    {
        "hdbin/f_title1.bin;1",
        SIM_PTR,
        0x00042000,
        SIM_13,
    },
    {
        "hdbin/f_game.bin;1",
        STAGE_PRG_PTR,
        0x00042000,
        SIM_1,
    },
    {
        "hdbin/f_title0.bin;1",
        SIM_PTR,
        0x00042000,
        SIM_STAGE_CHR,
    },
    {
        "hdbin/face.bin;1",
        STAGE_PRG_PTR,
        0x0001C000,
        SIM_6,
    },
    {
        "hdbin/arc_f.bin;1",
        RIC_PRG_PTR,
        0x00034000,
        SIM_WEAPON_PRG,
    },
    {
        "hdbin/ric.bin;1",
        RIC_PRG_PTR,
        0x00044000,
        SIM_WEAPON_PRG,
    },
    {
        "hdbin/f_prolo0.bin;1",
        SIM_PTR,
        0x00042000,
        SIM_11,
    },
    {
        "hdbin/f_prolo1.bin;1",
        SIM_PTR,
        0x00042000,
        SIM_12,
    },
    {
        "hdbin/gof.bin;1",
        SIM_PTR,
        0x00008000,
        SIM_14,
    },
    {
        "hdbin/gob.bin;1",
        SIM_PTR,
        0x00010000,
        SIM_15,
    },
    {
        "hdbin/c_gof.bin;1",
        SIM_PTR,
        0x00002000,
        SIM_16,
    },
    {
        "hdbin/c_gob.bin;1",
        SIM_PTR,
        0x00002000,
        SIM_17,
    },
    {
        "hdbin/f_sel.bin;1",
        SIM_PTR,
        0x00042000,
        SIM_STAGE_CHR,
    },
    {
        "hdbin/f_game2.bin;1",
        STAGE_PRG_PTR,
        0x00042000,
        SIM_1,
    },
    {
        "hdbin/edf.bin;1",
        SIM_PTR,
        0x00002000,
        SIM_21,
    },
    {
        "hdbin/edb.bin;1",
        SIM_PTR,
        0x00010000,
        SIM_15,
    },
    {
        "hdbin/c_edf.bin;1",
        SIM_PTR,
        0x00002000,
        SIM_16,
    },
    {
        "hdbin/c_edb.bin;1",
        SIM_PTR,
        0x00002000,
        SIM_17,
    },
};

SimFile D_800A036C[] = {
    {
        "sound/data/sd_alk.vh;1",
        aPbav_0,
        SD_ALK_VH_LEN,
        SIM_VH,
    },
    {
        "sound/data/sd_alk.vb;1",
        SIM_PTR,
        SD_ALK_VB_LEN,
        SIM_VB,
    },
    {
        "sound/data/sd_rih.vh;1",
        aPbav_0,
        SD_RIH_VH_LEN,
        SIM_VH,
    },
    {
        "sound/data/sd_rih.vb;1",
        SIM_PTR,
        SD_RIH_VB_LEN,
        SIM_VB,
    },
    {
        "sound/data/sd_mar.vh;1",
        aPbav_1,
        SD_MAR_VH_LEN,
        SIM_VH,
    },
    {
        "sound/data/sd_mar.vb;1",
        SIM_PTR,
        SD_MAR_VB_LEN,
        SIM_VB,
    },
    {
        "sound/data/sd_tuka2.vh;1",
        aPbav_1,
        SD_TUKA2_VH_LEN,
        SIM_VH,
    },
    {
        "sound/data/sd_tuka2.vb;1",
        SIM_PTR,
        SD_TUKA2_VB_LEN,
        SIM_VB,
    },
    {
        "sound/data/sd_tuka2.vh;1",
        aPbav_1,
        SD_TUKA2_VH_LEN,
        SIM_VH,
    },
    {
        "sound/data/sd_tuka2.vb;1",
        SIM_PTR,
        SD_TUKA2_VB_LEN,
        SIM_VB,
    },
    {
        "sound/data/sd_tuka1.vh;1",
        aPbav_1,
        SD_TUKA1_VH_LEN,
        SIM_VH,
    },
    {
        "sound/data/sd_tuka1.vb;1",
        SIM_PTR,
        SD_TUKA1_VB_LEN,
        SIM_VB,
    },
    {
        "sound/data/sd_koa1.vh;1",
        aPbav_1,
        SD_KOA1_VH_LEN,
        SIM_VH,
    },
    {
        "sound/data/sd_koa1.vb;1",
        SIM_PTR,
        SD_KOA1_VB_LEN,
        SIM_VB,
    },
    {
        "sound/data/sd_mak.vh;1",
        aPbav_1,
        SD_MAK_VH_LEN,
        SIM_VH,
    },
    {
        "sound/data/sd_mak.vb;1",
        SIM_PTR,
        SD_MAK_VB_LEN,
        SIM_VB,
    },
    {
        "sound/data/sd_tuka2.vh;1",
        aPbav_1,
        SD_TUKA2_VH_LEN,
        SIM_VH,
    },
    {
        "sound/data/sd_tuka2.vb;1",
        SIM_PTR,
        SD_TUKA2_VB_LEN,
        SIM_VB,
    },
    {
        "sound/data/sd_koa2.vh;1",
        aPbav_1,
        SD_KOA2_VH_LEN,
        SIM_VH,
    },
    {
        "sound/data/sd_koa2.vb;1",
        SIM_PTR,
        SD_KOA2_VB_LEN,
        SIM_VB,
    },
    {
        "sound/data/sd_mar2.vh;1",
        aPbav_0,
        SD_MAR2_VH_LEN,
        SIM_VH,
    },
    {
        "sound/data/sd_mar2.vb;1",
        SIM_PTR,
        SD_MAR2_VB_LEN,
        SIM_VB,
    },
};

SimFile D_800A04AC[] = {
    {
        "sound/data/sd_eve1.seq;1",
        aPqes_1,
        0x00001EB3,
        SIM_SEQ,
    },
    {
        "sound/data/sd_eve3.seq;1",
        aPqes_1,
        0x00000178,
        SIM_SEQ,
    },
};

SimFile D_psp_09160430[] = {
    {
        "snd_e/data/sd_alk.vh;1",
        aPbav_0,
        SD_ALK_VH_LEN,
        SIM_VH,
    },
    {
        "snd_e/data/sd_alk.vb;1",
        SIM_PTR,
        SD_ALK_VB_LEN,
        SIM_VB,
    },
    {
        "snd_e/data/sd_rih.vh;1",
        aPbav_0,
        SD_RIH_VH_LEN,
        SIM_VH,
    },
    {
        "snd_e/data/sd_rih.vb;1",
        SIM_PTR,
        SD_RIH_VB_LEN,
        SIM_VB,
    },
    {
        "snd_e/data/sd_mar.vh;1",
        aPbav_1,
        SD_MAR_VH_LEN,
        SIM_VH,
    },
    {
        "snd_e/data/sd_mar.vb;1",
        SIM_PTR,
        SD_MAR_VB_LEN,
        SIM_VB,
    },
    {
        "snd_e/data/sd_tuka2.vh;1",
        aPbav_1,
        SD_TUKA1_VH_LEN,
        SIM_VH,
    },
    {
        "snd_e/data/sd_tuka2.vb;1",
        SIM_PTR,
        SD_TUKA2_VB_LEN,
        SIM_VB,
    },
    {
        "snd_e/data/sd_tuka2.vh;1",
        aPbav_1,
        SD_TUKA1_VH_LEN,
        SIM_VH,
    },
    {
        "snd_e/data/sd_tuka2.vb;1",
        SIM_PTR,
        SD_TUKA2_VB_LEN,
        SIM_VB,
    },
    {
        "snd_e/data/sd_tuka1.vh;1",
        aPbav_1,
        SD_TUKA1_VH_LEN,
        SIM_VH,
    },
    {
        "snd_e/data/sd_tuka1.vb;1",
        SIM_PTR,
        SD_TUKA1_VB_LEN,
        SIM_VB,
    },
    {
        "snd_e/data/sd_koa1.vh;1",
        aPbav_1,
        SD_KOA1_VH_LEN,
        SIM_VH,
    },
    {
        "snd_e/data/sd_koa1.vb;1",
        SIM_PTR,
        SD_KOA1_VB_LEN,
        SIM_VB,
    },
    {
        "snd_e/data/sd_mak.vh;1",
        aPbav_1,
        SD_MAK_VH_LEN,
        SIM_VH,
    },
    {
        "snd_e/data/sd_mak.vb;1",
        SIM_PTR,
        SD_MAK_VB_LEN,
        SIM_VB,
    },
    {
        "snd_e/data/sd_tuka2.vh;1",
        aPbav_1,
        SD_TUKA2_VH_LEN,
        SIM_VH,
    },
    {
        "snd_e/data/sd_tuka2.vb;1",
        SIM_PTR,
        SD_TUKA2_VB_LEN,
        SIM_VB,
    },
    {
        "snd_e/data/sd_koa2.vh;1",
        aPbav_1,
        SD_KOA2_VH_LEN,
        SIM_VH,
    },
    {
        "snd_e/data/sd_koa2.vb;1",
        SIM_PTR,
        SD_KOA2_VB_LEN,
        SIM_VB,
    },
    {
        "snd_e/data/sd_mar2.vh;1",
        aPbav_0,
        SD_MAR2_VH_LEN,
        SIM_VH,
    },
    {
        "snd_e/data/sd_mar2.vb;1",
        SIM_PTR,
        SD_MAR2_VB_LEN,
        SIM_VB,
    },
};

SimFile D_psp_091605D0[] = {
    {
        "snd_e/data/sd_eve1.seq;1",
        aPqes_1,
        0x00001EB3,
        SIM_SEQ,
    },
    {
        "snd_e/data/sd_eve3.seq;1",
        aPqes_1,
        0x00000178,
        SIM_SEQ,
    },
};

u16 D_800A04CC[] = {
    0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
};

// BSS
SimFile* g_SimFile;
SimFile D_80136450;
u_long* clutAddr;
u_long* D_psp_091CE378;
s32 D_psp_091CE370;
s32 D_psp_091CE368;
s32 D_psp_091CE360;

void func_psp_090FA740(void) {
    D_psp_091CE368++;
    D_psp_091CE370 = (D_psp_091CE368 >> 2) & 0x1F;
    func_psp_09144C80();
    if (D_psp_091CE360 == 0) {
        D_psp_091CE360 = 0;
    }
}

void LoadStageTileset(u8* pTilesetData, s32 y) {
    RECT rect;
    s32 i;
    u8* ptr;

    rect.w = 0x20;
    rect.h = 0x80;
    for (i = 0; i < 0x20; i++) {
        ptr = &pTilesetData[i * 0x2000];
        rect.x = D_800AC958[i];
        if (i & 2) {
            rect.y = y + 0x80;
        } else {
            rect.y = y;
        }
        LoadImage(&rect, (u_long*)ptr);
    }
}

// Equivalent of CdStep_6 with their g_CdCallback but for the sim device
s32 LoadFileSimToMem(SimKind kind) {
    switch (kind) {
    case SIM_FAMILIAR_CHR:
        LoadTPage((u_long*)SIM_CHR0, 0, 0, 0x2C0, 0x100, 0x100, 0x80);
        LoadTPage((u_long*)SIM_CHR1, 0, 0, 0x2C0, 0x180, 0x80, 0x80);
        break;
    case SIM_WEAPON0_CHR:
        LoadTPage((u_long*)g_Pix[0], 0, 0, 0x240, 0x100, 0x100, 0x80);
        break;
    case SIM_WEAPON1_CHR:
        LoadTPage((u_long*)g_Pix[2], 0, 0, 0x240, 0x180, 0x100, 0x80);
        break;
    case SIM_MONSTER:
        LoadTPage((u_long*)SIM_CHR0, 2, 0, 0x20, 0x100, 0x60, 0x70);
        break;
    case SIM_1:
        LoadStageTileset(STAGE_PRG_PTR, 0x100);
        LoadImage(&g_Vram.D_800ACD98, (u_long*)D_800A04CC);
        D_psp_091CE378 = &D_8D6DC40;
        LoadImage(&g_Vram.D_800ACDA8, D_psp_091CE378);
        clutAddr = (u_long*)g_Clut[1];
        StoreImage(&g_Vram.D_800ACDA8, clutAddr);
        break;
    case SIM_STAGE_CHR:
    case SIM_11:
        LoadStageTileset(SIM_CHR0, 0);
        clutAddr = (u_long*)g_Clut[0];
        StoreImage(&g_Vram.D_800ACDB8, clutAddr);
        if (kind == SIM_11) {
            clutAddr = (u_long*)g_Clut[2];
            StoreImage(&g_Vram.D_800ACDB8, clutAddr);
            LoadImage(&g_Vram.D_800ACDB0, clutAddr);
        }
        break;
    case SIM_12:
    case SIM_13:
        LoadStageTileset(SIM_CHR0, 0x100);
        if (kind == SIM_13) {
            LoadImage(&g_Vram.D_800ACD98, (u_long*)D_800A04CC);
        }
        break;
    case SIM_6:
        LoadImage(&g_Vram.D_800ACDC0, (u_long*)STAGE_PRG_PTR);
        break;
    case SIM_14:
        LoadImage(&g_Vram.D_800ACDD0, (u_long*)SIM_PTR);
        break;
    case SIM_21:
        LoadImage(&g_Vram.D_800ACDE0, (u_long*)SIM_PTR);
        break;
    case SIM_15:
        LoadImage(&g_Vram.D_800ACDD8, (u_long*)SIM_PTR);
        break;
    case SIM_16:
        LoadImage(&g_Vram.D_800ACDB8, (u_long*)SIM_PTR);
        clutAddr = (u_long*)g_Clut[2];
        StoreImage(&g_Vram.D_800ACDB8, clutAddr);
        break;
    case SIM_17:
        LoadImage(&g_Vram.D_800ACDA8, (u_long*)SIM_PTR);
        clutAddr = (u_long*)g_Clut[0];
        StoreImage(&g_Vram.D_800ACDA8, clutAddr);
        break;
    }
    return 0;
}

s32 func_psp_090FAB30(s32 fileId, SimFileType type, bool arg2) {
    char buf[40];
    char buf1[64];
    char buf2[64];

    s32 var_a0;
    s32 i;
    s32 var_s2;
    s32 var_s1;
    s32 var_s0;
    s32 var_s6;

    u32* src;
    u32* dst;

    g_SimFile = &D_800A024C[fileId];
    var_s2 = -1;
    if (type == SimFileType_StagePrg) {
        if (strcmp(g_StagesLba[g_StageId].ovlName, "SEL") == 0) {
            var_s2 = 1;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "ST0") == 0) {
            var_s2 = 2;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "ARE") == 0) {
            var_s2 = 3;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "CAT") == 0) {
            var_s2 = 4;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "CEN") == 0) {
            var_s2 = 5;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "CHI") == 0) {
            var_s2 = 6;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "DAI") == 0) {
            var_s2 = 7;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "DRE") == 0) {
            var_s2 = 8;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "LIB") == 0) {
            var_s2 = 9;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "NO0") == 0) {
            var_s2 = 0xA;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "NO1") == 0) {
            var_s2 = 0xB;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "NO2") == 0) {
            var_s2 = 0xC;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "NO3") == 0) {
            var_s2 = 0xD;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "NO4") == 0) {
            var_s2 = 0xE;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "NP3") == 0) {
            var_s2 = 0xF;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "NZ0") == 0) {
            var_s2 = 0x10;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "NZ1") == 0) {
            var_s2 = 0x11;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "TOP") == 0) {
            var_s2 = 0x12;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "WRP") == 0) {
            var_s2 = 0x13;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "RARE") == 0) {
            var_s2 = 0x14;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "RCAT") == 0) {
            var_s2 = 0x15;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "RCEN") == 0) {
            var_s2 = 0x16;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "RCHI") == 0) {
            var_s2 = 0x17;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "RDAI") == 0) {
            var_s2 = 0x18;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "RLIB") == 0) {
            var_s2 = 0x19;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "RNO0") == 0) {
            var_s2 = 0x1A;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "RNO1") == 0) {
            var_s2 = 0x1B;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "RNO2") == 0) {
            var_s2 = 0x1C;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "RNO3") == 0) {
            var_s2 = 0x1D;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "RNO4") == 0) {
            var_s2 = 0x1E;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "RNZ0") == 0) {
            var_s2 = 0x1F;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "RNZ1") == 0) {
            var_s2 = 0x20;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "RTOP") == 0) {
            var_s2 = 0x21;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "RWRP") == 0) {
            var_s2 = 0x22;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "MAR") == 0) {
            var_s2 = 0x23;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "BO0") == 0) {
            var_s2 = 0x24;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "BO1") == 0) {
            var_s2 = 0x25;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "BO2") == 0) {
            var_s2 = 0x26;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "BO3") == 0) {
            var_s2 = 0x27;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "BO4") == 0) {
            var_s2 = 0x28;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "BO5") == 0) {
            var_s2 = 0x29;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "BO6") == 0) {
            var_s2 = 0x2A;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "BO7") == 0) {
            var_s2 = 0x2B;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "RBO0") == 0) {
            var_s2 = 0x2C;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "RBO1") == 0) {
            var_s2 = 0x2D;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "RBO2") == 0) {
            var_s2 = 0x2E;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "RBO3") == 0) {
            var_s2 = 0x2F;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "RBO4") == 0) {
            var_s2 = 0x30;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "RBO5") == 0) {
            var_s2 = 0x31;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "RBO6") == 0) {
            var_s2 = 0x32;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "RBO7") == 0) {
            var_s2 = 0x33;
        }
        if (strcmp(g_StagesLba[g_StageId].ovlName, "RBO8") == 0) {
            var_s2 = 0x34;
        }
        g_SimFile = &D_80136450;
        strcpy(buf, "hdbin/");
        strcpy(buf1, g_StagesLba[g_StageId].ovlName);
        func_890CAF8(buf1);
        strcat(buf, buf1);
        strcat(buf, ".bin;1");
        g_SimFile->path = buf;
        g_SimFile->addr = STAGE_PRG_PTR;
        g_SimFile->size = 0x60000;
        g_SimFile->kind = SIM_STAGE_PRG;
        var_s1 = func_8932BF0();
        var_s0 = func_8932C80();
        var_s6 = func_8932C5C();
    }
    if (type == SimFileType_Vh) {
        if (fileId & 0x8000) {
            if (!D_8B42064) {
                var_a0 = fileId & 0x7FFF;
                g_SimFile = &D_800A036C[var_a0];
            } else {
                var_a0 = fileId & 0x7FFF;
                g_SimFile = &D_psp_09160430[var_a0];
            }
            if (var_a0 == 4) {
                var_s1 = func_89330A0();
            } else if ((var_a0 >= 6) && (var_a0 < 0x13)) {
                var_s1 = func_8932F44();
            } else {
                var_s1 = func_893307C();
            }
        } else {
            g_SimFile = &D_80136450;
            strcpy(buf, D_psp_08B42060);
            strcpy(buf, "data/sd_");
            strcat(buf, g_StagesLba[g_StageId].name);
            strcat(buf, ".vh;1");
            g_SimFile->path = buf;
            g_SimFile->addr = aPbav_2;
            g_SimFile->size = g_StagesLba[g_StageId].vhLen;
            g_SimFile->kind = SIM_VH;
            var_s1 = func_8932C14();
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
        if (arg2) {
            func_892EB04(g_SimFile->path, g_SimVabId, var_s1);
        } else {
            func_892EB04(g_SimFile->path, g_SimVabId, 0);
        }
        return 0;
    }
    if (type == SimFileType_Vb) {
        if (fileId & 0x8000) {
            if (!D_8B42064) {
                g_SimFile = &D_800A036C[fileId & 0x7FFF];
            } else {
                g_SimFile = &D_psp_09160430[fileId & 0x7FFF];
            }
        } else {
            g_SimFile = &D_80136450;
            strcpy(buf, D_psp_08B42060);
            strcpy(buf, "data/sd_");
            strcat(buf, g_StagesLba[g_StageId].name);
            strcat(buf, ".vb;1");
            g_SimFile->path = buf;
            g_SimFile->addr = SIM_PTR;
            g_SimFile->size = g_StagesLba[g_StageId].vbLen;
            g_SimFile->kind = SIM_VB;
        }
        return 0;
    }
    if (type == SimFileType_Seq) {
        if (!D_8B42064) {
            g_SimFile = &D_800A04AC[fileId];
        } else {
            g_SimFile = &D_psp_091605D0[fileId];
        }
        return 0;
    }
    if (type == SimFileType_StageChr) {
        g_SimFile = &D_80136450;
        strcpy(buf, "hdbin/");
        strcpy(buf2, g_StagesLba[g_StageId].gfxName);
        func_890CAF8(buf2);
        strcat(buf, buf2);
        strcat(buf, ".bin;1");
        g_SimFile->path = buf;
        g_SimFile->addr = SIM_PTR;
        g_SimFile->size = 0x40000;
        g_SimFile->kind = SIM_STAGE_CHR;
        var_s1 = func_8932C38();
    }
    if (type == SimFileType_Weapon0Prg) {
        g_SimFile = &D_80136450;
        var_s2 = fileId + 0x3F;
        sprintf(buf, "hdbin/w0_%03d.bin;1", fileId);
        g_SimFile->path = buf;
        g_SimFile->addr = &D_8017A000;
        g_SimFile->size = 0x3000;
        g_SimFile->kind = SIM_WEAPON_PRG;
        var_s1 = func_8932DC8(0);
        var_s0 = func_8932E4C(0);
        var_s6 = func_8932E20(0);
    }
    if (type == SimFileType_Weapon1Prg) {
        g_SimFile = &D_80136450;
        var_s2 = fileId + 0x7A;
        sprintf(buf, "hdbin/w1_%03d.bin;1", fileId);
        g_SimFile->path = buf;
        g_SimFile->addr = WEAPON1_PTR;
        g_SimFile->size = 0x3000;
        g_SimFile->kind = SIM_WEAPON_PRG;
        var_s1 = func_8932DC8(1);
        var_s0 = func_8932E4C(1);
        var_s6 = func_8932E20(1);
    }
    if (type == SimFileType_Weapon0Chr) {
        g_SimFile = &D_80136450;
        sprintf(buf, "hdbin/f0_%03d.bin;1", fileId);
        g_SimFile->path = buf;
        g_SimFile->addr = g_Pix[0];
        g_SimFile->size = 0x4000;
        g_SimFile->kind = SIM_WEAPON0_CHR;
        var_s1 = func_8932DF4(0);
    }
    if (type == SimFileType_Weapon1Chr) {
        g_SimFile = &D_80136450;
        sprintf(buf, "hdbin/f1_%03d.bin;1", fileId);
        g_SimFile->path = buf;
        g_SimFile->addr = g_Pix[2];
        g_SimFile->size = 0x4000;
        g_SimFile->kind = SIM_WEAPON1_CHR;
        var_s1 = func_8932DF4(1);
    }
    if (type == SimFileType_FamiliarPrg) {
        g_SimFile = &D_80136450;
        var_s2 = fileId + 0x38;
        sprintf(buf, "hdbin/tt_%03d.bin;1", fileId);
        g_SimFile->path = buf;
        g_SimFile->addr = &g_ServantDesc;
        g_SimFile->size = 0xA000;
        g_SimFile->kind = SIM_FAMILIAR_PRG;
        var_s1 = func_8932F20();
        var_s0 = func_8932FB0();
        var_s6 = func_8932F8C();
    }
    if (type == SimFileType_FamiliarChr) {
        g_SimFile = &D_80136450;
        sprintf(buf, "hdbin/ft_%03d.bin;1", fileId);
        g_SimFile->path = buf;
        g_SimFile->addr = SIM_PTR;
        g_SimFile->size = 0x6000;
        g_SimFile->kind = SIM_FAMILIAR_CHR;
        var_s1 = func_8932F68();
    }
    if (type == SimFileType_Monster) {
        g_SimFile = &D_80136450;
        sprintf(buf, "hdbin/mo_%03d.bin;1", fileId);
        g_SimFile->path = buf;
        g_SimFile->addr = SIM_PTR;
        g_SimFile->size = 0x5800;
        g_SimFile->kind = SIM_MONSTER;
    }
    if (type == SimFileType_System) {
        if (fileId == 1 || fileId == 13) {
            var_s1 = func_89331AC();
        } else if (fileId == 9) {
            SimFile buf3[] = {
                {
                    "hdbin/gob.bin;1",
                    SIM_PTR,
                    0x00010000,
                    SIM_15,
                },
                {
                    "hdbin/F_GV_BKF.BIN;1",
                    SIM_PTR,
                    0x00010000,
                    SIM_15,
                },
                {
                    "hdbin/F_GV_BKS.BIN;1",
                    SIM_PTR,
                    0x00010000,
                    SIM_15,
                },
                {
                    "hdbin/F_GV_BKG.BIN;1",
                    SIM_PTR,
                    0x00010000,
                    SIM_15,
                },
                {
                    "hdbin/F_GV_BKI.BIN;1",
                    SIM_PTR,
                    0x00010000,
                    SIM_15,
                },
            };
            g_SimFile = &buf3[g_UserLanguage - 1];
        } else if (fileId == 11) {
            SimFile buf4[] = {
                {
                    "hdbin/c_gob.bin;1",
                    SIM_PTR,
                    0x00002000,
                    SIM_17,
                },
                {
                    "hdbin/C_GOB_EU.BIN;1",
                    SIM_PTR,
                    0x00002000,
                    SIM_17,
                },
                {
                    "hdbin/C_GOB_EU.BIN;1",
                    SIM_PTR,
                    0x00002000,
                    SIM_17,
                },
                {
                    "hdbin/C_GOB_EU.BIN;1",
                    SIM_PTR,
                    0x00002000,
                    SIM_17,
                },
                {
                    "hdbin/C_GOB_EU.BIN;1",
                    SIM_PTR,
                    0x00002000,
                    SIM_17,
                }};
            g_SimFile = &buf4[g_UserLanguage - 1];
        }
        if (strcmp(g_SimFile->path, "hdbin/ric.bin;1") == 0) {
            if (g_PlayableCharacter != 2) {
                var_s1 = func_89330C4();
                var_s2 = 0x35;
            } else {
                var_s1 = func_89330C4();
                var_s2 = 0x37;
            }
        } else if (strcmp(g_SimFile->path, "hdbin/arc_f.bin;1") == 0) {
            var_s2 = 0x36;
            var_s1 = func_89330C4();
        }
        var_s0 = func_893310C();
        var_s6 = func_89330E8();
    }
    if (arg2) {
        memcpy(g_SimFile->addr, (void*)var_s1, g_SimFile->size);
    } else {
        func_890FBEC(g_SimFile->path, g_SimFile->addr, 0, (s32)g_SimFile->size);
    }
    if (LoadFileSimToMem(g_SimFile->kind) < 0) {
        FntPrint("tr err\n");
        return -1;
    }
    if (var_s2 >= 0) {
        if (arg2) {
            func_892A0F0(var_s2, var_s6, var_s0);
        } else {
            func_892A1EC(var_s2);
        }
    }
    return 0;
}

s32 LoadFileSim(s32 fileId, SimFileType type) {
    return func_psp_090FAB30(fileId, type, false);
}
