// SPDX-License-Identifier: AGPL-3.0-or-later
#include <dra.h>
#include "dra_bss.h"
#include <log.h>
#include "pc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lba.h>
#include "weapon_pc.h"
#include "servant_pc.h"

s32 g_SimVabId = 0;

SimFile D_800A024C[] = {
    {"sim:c:\\bin\\f_title1.bin", 13}, {"sim:c:\\bin\\f_game.bin", 1},
    {"sim:c:\\bin\\f_title0.bin", 2},  {"sim:c:\\bin\\face.bin", 6},
    {"sim:c:\\bin\\arc_f.bin", 8},     {"sim:c:\\bin\\ric.bin", 8},
    {"sim:c:\\bin\\f_prolo0.bin", 11}, {"sim:c:\\bin\\f_prolo1.bin", 12},
    {"sim:c:\\bin\\gof.bin", 14},      {"sim:c:\\bin\\gob.bin", 15},
    {"sim:c:\\bin\\c_gof.bin", 16},    {"sim:c:\\bin\\c_gob.bin", 17},
    {"sim:c:\\bin\\f_sel.bin", 2},     {"sim:c:\\bin\\f_game2.bin", 1},
    {"sim:c:\\bin\\edf.bin", 21},      {"sim:c:\\bin\\edb.bin", 15},
    {"sim:c:\\bin\\c_edf.bin", 16},    {"sim:c:\\bin\\c_edb.bin", 17},
};

// need a place for the data loaded to hardcoded offset
u8 D_80280000[110000] = {0};

SimFile D_800A036C[] = {
    {
        "VAB/SD_ALK.VH",
        aPbav_0,
        SD_ALK_VH_LEN,
        SIM_VH,
    },
    {
        "VAB/SD_ALK.VB",
        D_80280000,
        SD_ALK_VB_LEN,
        SIM_VB,
    },
    {
        "VAB/SD_RIH.VH",
        aPbav_0,
        SD_RIH_VH_LEN,
        SIM_VH,
    },
    {
        "VAB/SD_RIH.VB",
        D_80280000,
        SD_RIH_VB_LEN,
        SIM_VB,
    },
    {
        "VAB/SD_MAR.VH",
        aPbav_1,
        SD_MAR_VH_LEN,
        SIM_VH,
    },
    {
        "VAB/SD_MAR.VB",
        D_80280000,
        SD_MAR_VB_LEN,
        SIM_VB,
    },
    {
        "SERVANT/SD_BAT.VH",
        aPbav_1,
        SD_TUKA2_VH_LEN,
        SIM_VH,
    },
    {
        "SERVANT/SD_BAT.VB",
        D_80280000,
        SD_TUKA2_VB_LEN,
        SIM_VB,
    },
    {
        "SERVANT/SD_GHOST.VH",
        aPbav_1,
        SD_TUKA2_VH_LEN,
        SIM_VH,
    },
    {
        "SERVANT/SD_GHOST.VB",
        D_80280000,
        SD_TUKA2_VB_LEN,
        SIM_VB,
    },
    {
        "SERVANT/SD_FAIRY.VH",
        aPbav_1,
        SD_TUKA2_VH_LEN,
        SIM_VH,
    },
    {
        "SERVANT/SD_FAIRY.VB",
        D_80280000,
        SD_TUKA2_VB_LEN,
        SIM_VB,
    }};

const char* D_800A04AC[] = {
    "sim:c:\\sound\\data\\sd_eve1.seq",
    "sim:c:\\sound\\data\\sd_eve3.seq",
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

void VSyncHandler(void) {
    RECT* rect;

    D_800A04F4++;
    D_800A04F8 = (D_800A04F4 / 4) % 32;
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

void LoadStageTileset(u8* pTilesetData, size_t len, s32 y) {
    const u32 MaxBlockCount = 0x20;
    RECT rect;
    u8* pTilesetDataSrc;
    u32 i;
    u32 blockCount;

    rect.w = 0x20;
    rect.h = 0x80;

    // different behaviour from PSX as F_SEL is 192KB long, not 256KB
    blockCount = len >> 13;
    if (blockCount > MaxBlockCount) {
        WARNF("tileset too large (%d > %d): it wil not be fully read",
              blockCount, MaxBlockCount);
        blockCount = MaxBlockCount;
    }

    for (i = 0; i < blockCount; i++) {
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

void InitStageDummy(Overlay* o);
void InitStageCEN(Overlay* o);
void InitStageNZ0(Overlay* o);
void InitStageST0(Overlay* o);
void InitStageWRP(Overlay* o);
void InitStageSEL(Overlay* o);
void InitPlayerArc(const struct FileUseContent* file);
void InitPlayerRic(void);
void func_80131EBC(const char* str, s16 arg1);
s32 LoadFileSimToMem(SimKind kind) {
    u16* clutAddr;

    switch (kind) {
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
        LoadStageTileset(STAGE_PRG_PTR, 0, 0x100);
        DrawSync(0);
        LoadImage(&g_Vram.D_800ACD98, D_800A04CC);
        LoadImage(&g_Vram.D_800ACDA8, 0x801C0000);
        while (DrawSync(1)) {
        }
        StoreImage(&g_Vram.D_800ACDA8, g_Clut + 0x1000);
        break;
    case SIM_STAGE_CHR:
    case SIM_11:
        LoadStageTileset(SIM_CHR0, 0, 0);
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
        LoadStageTileset(SIM_CHR0, 0, 0x100);
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
        if (SsVabTransBodyPartly(
                g_SimFile->addr, g_SimFile->size, g_SimVabId) == -1) {
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

bool LoadFilePc(const struct FileUseContent* file) {
    SimFile* sim = (SimFile*)file->param;
    sim->addr = file->content;
    switch (sim->kind) { // slowly replacing the original func
    case SIM_1:
        LoadStageTileset(sim->addr, file->length, 0x100);
        LoadImage(&g_Vram.D_800ACD98, D_800A04CC);
        LoadImage(&g_Vram.D_800ACDA8, (u8*)sim->addr + 0x40000);
        StoreImage(&g_Vram.D_800ACDA8, g_Clut + 0x1000);
        break;
    case SIM_STAGE_CHR:
        LoadStageTileset(sim->addr, file->length, 0);
        StoreImage(&g_Vram.D_800ACDB8, g_Clut);
        break;
    case SIM_12:
        LoadStageTileset(sim->addr, file->length, 0x100);
    case SIM_13:
        LoadStageTileset(sim->addr, file->length, 0x100);
        LoadImage(&g_Vram.D_800ACD98, D_800A04CC);
        break;
    case 99:
        InitPlayerArc(file);
        break;
    default:
        g_SimFile = sim;
        if (LoadFileSimToMem(sim->kind) < 0) {
            return false;
        }
    }
    return true;
}

int readToBuf(const char* filename, char* dest) {
    FILE* file = fopen(filename, "rb");

    if (file == NULL) {
        printf("Failed to open file %s\n", filename);
        exit(1);
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Read the file into the buffer
    size_t read_size = fread(dest, 1, filesize, file);
    if (read_size != filesize) {
        printf("Failed to read file");
        fclose(file);
        return 1;
    }
    return 0;
}

static bool isFirstBoot() {
    return g_StageId == STAGE_SEL && g_GameState == Game_Init;
}

s32 LoadFileSim(s32 fileId, SimFileType type) {
    char smolbuf[48];
    char buf[128];
    s32 fid;

    SimFile sim = {0};
    switch (type) {
    case SimFileType_System:
        switch (fileId) {
        case 0:
            sim.path = "BIN/F_TITLE1.BIN";
            sim.kind = SIM_13;
            break;
        case 1:
            sim.path = "BIN/F_GAME.BIN";
            sim.kind = SIM_1;
            break;
        case 2:
            sim.path = "BIN/F_TITLE0.BIN";
            sim.kind = SIM_STAGE_CHR;
            break;
        case 4:
            sim.path = "BIN/ARC_F.BIN";
            sim.kind = 99;
            break;
        case 5:
            InitPlayerRic();
            sim.path = "BIN/RIC.BIN";
            sim.kind = 99;
            break;
        case 12:
            sim.path = "ST/SEL/F_SEL.BIN";
            sim.kind = SIM_STAGE_CHR;
            break;
        case 13:
            sim.path = "BIN/F_GAME2.BIN";
            sim.kind = SIM_1;
            break;
        default:
            WARNF("not implemented for ID %d: %s", fileId, D_800A024C[fileId]);
            return -1;
        }
        break;
    case SimFileType_StagePrg:
        if (isFirstBoot()) {
            if (g_GameParams.player >= 0) {
                g_PlayableCharacter = g_GameParams.player;
            }
            if (g_GameParams.stage >= 0) {
                g_StageId = g_GameParams.stage;
                SetGameState(Game_NowLoading);
                g_GameStep = 1;
            }
        }
        switch (g_StageId) {
        case STAGE_SEL:
            InitStageSEL(&g_api.o);
            break;
        case STAGE_CEN:
            InitStageCEN(&g_api.o);
            break;
        case STAGE_NZ0:
            InitStageNZ0(&g_api.o);
            break;
        case STAGE_ST0:
            InitStageST0(&g_api.o);
            break;
        case STAGE_WRP:
            InitStageWRP(&g_api.o);
            break;
        default:
            InitStageDummy(&g_api.o);
            INFOF("TODO: will load stage '%s'", g_StagesLba[g_StageId].ovlName);
            break;
        }
        return 0;
    case SimFileType_Vh:
        g_SimFile = &sim;
        if (fileId & 0x8000) {
            u16 actualFileId = fileId & 0x7FFF;
            if (actualFileId >= LEN(D_800A036C)) {
                WARNF("not implemented for VH ID %04X", fileId);
                return -1;
            }
            sim.path = D_800A036C[actualFileId].path;
            sim.size = D_800A036C[actualFileId].size;
            sim.addr = D_800A036C[actualFileId].addr;
            sim.kind = SIM_VH;
            snprintf(buf, sizeof(buf), "disks/us/%s", sim.path);
            return readToBuf(buf, sim.addr);
        } else {
            sim.path = smolbuf;
            snprintf(smolbuf, sizeof(smolbuf), "ST/%s/SD_ZK%s.VH",
                     g_StagesLba[g_StageId].ovlName,
                     g_StagesLba[g_StageId].ovlName);
            sim.addr = aPbav_2;
            sim.path = smolbuf;
            sim.size = g_StagesLba[g_StageId].vhLen;
            sim.kind = SIM_VH;
        }
        if (sim.addr == aPbav) {
            g_SimVabId = 0;
        }
        if (sim.addr == aPbav_0) {
            g_SimVabId = 1;
        }
        if (sim.addr == aPbav_2) {
            g_SimVabId = 3;
        }
        if (sim.addr == aPbav_1) {
            g_SimVabId = 2;
        }
        SsVabClose(g_SimVabId);
        break;
    case SimFileType_Vb:
        g_SimFile = &sim;
        if (fileId & 0x8000) {
            u16 actualFileId = fileId & 0x7FFF;
            if (actualFileId >= LEN(D_800A036C)) {
                WARNF("not implemented for VB ID %04X", fileId);
                return -1;
            }
            sim.path = D_800A036C[actualFileId].path;
            sim.size = D_800A036C[actualFileId].size;
            sim.addr = D_800A036C[actualFileId].addr;
            sim.kind = SIM_VB;
            snprintf(buf, sizeof(buf), "disks/us/%s", sim.path);
            return readToBuf(buf, sim.addr);
        } else {
            sim.path = smolbuf;
            snprintf(smolbuf, sizeof(smolbuf), "ST/%s/SD_ZK%s.VB",
                     g_StagesLba[g_StageId].ovlName,
                     g_StagesLba[g_StageId].ovlName);
            sim.path = sim.path;
            sim.size = g_StagesLba[g_StageId].vbLen;
            sim.kind = SIM_VB;
        }
        break;
    case SimFileType_StageChr:
        sim.kind = SIM_STAGE_CHR;
        sim.path = smolbuf;
        snprintf(smolbuf, sizeof(smolbuf), "ST/%s/F_%s.BIN",
                 g_StagesLba[g_StageId].ovlName,
                 g_StagesLba[g_StageId].ovlName);
        break;
    case SimFileType_Weapon0Prg:
        HandleWeapon0Prg(fileId);
        return 0;
    case SimFileType_Weapon1Prg:
        INFOF("TODO: will load weapon 'w1_%03d'", fileId);
        return 0;
    case SimFileType_Weapon0Chr:
        HandleWeapon0Chr(fileId);
        return 0;
    case SimFileType_Weapon1Chr:
        INFOF("TODO: will load weapon 'f1_%03d'", fileId);
        return 0;
    case SimFileType_FamiliarPrg:
        HandleServantPrg();
        return 0;
    case SimFileType_FamiliarChr:
        HandleServantChr();
        return 0;
    }
    if (!sim.path) {
        WARNF("unimplemented %d, %d", fileId, type);
        return -1;
    }

    snprintf(buf, sizeof(buf), "disks/us/%s", sim.path);
    DEBUGF("about to load %s", buf);
    if (!FileUseContent(LoadFilePc, buf, &sim)) {
        ERRORF("failed to load '%s'", buf);
        D_800A04EC = 0;
        return -1;
    }

    D_800A04EC = 0;
    return 0;
}
