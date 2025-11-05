// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

extern s32 D_8C630D4;
extern s32 D_psp_08C630DC;

// BSS
static u8* g_DemoPtr = DEMO_KEY_PTR;
s32 g_DemoKeyIdx;

static u8 D_800A243C[] = {
    STAGE_ST0,       STAGE_BO0,      STAGE_BO4,      STAGE_BO1,  STAGE_BO2,
    STAGE_BO3,       STAGE_NZ0_DEMO, STAGE_BO5,      STAGE_RBO1, STAGE_DRE,
    STAGE_NZ1_DEMO,  STAGE_RBO0,     STAGE_RBO2,     STAGE_BO7,  STAGE_BO6,
    STAGE_RBO3,      STAGE_RBO4,     STAGE_LIB_DEMO, STAGE_RBO5, STAGE_RBO7,
    STAGE_RNZ1_DEMO, STAGE_RBO8,     STAGE_NO0,      STAGE_NO0,  STAGE_NO0,
    STAGE_NO0,       STAGE_CEN,      STAGE_RCEN,     STAGE_RBO6, STAGE_NO0,
    STAGE_NO0,       STAGE_NO0,
};

void DemoGameInit(s32 arg0) {
    s32 i;

    if (arg0 != 2) {
        g_DemoKeyIdx = D_80097C98 & STAGE_INVERTEDCASTLE_MASK;
        if (g_StageId == STAGE_NZ0) {
            g_StageId = STAGE_NZ0_DEMO;
        } else if (g_StageId == STAGE_NZ1) {
            g_StageId = STAGE_NZ1_DEMO;
        } else if (g_StageId == STAGE_LIB) {
            g_StageId = STAGE_LIB_DEMO;
        } else if (g_StageId == STAGE_RNZ1) {
            g_StageId = STAGE_RNZ1_DEMO;
        } else {
            g_StageId = D_800A243C[g_DemoKeyIdx];
        }
    } else {
        g_DemoKeyIdx = D_80097C98 & STAGE_INVERTEDCASTLE_MASK;
        g_StageId = D_800A243C[g_DemoKeyIdx];
    }

    InitStatsAndGear(0);
    if (g_StageId != STAGE_ST0) {
        g_Status.level = 99;
        for (i = 0; i < RELIC_BAT_CARD; i++) {
            g_Status.relics[i] = RELIC_FLAG_FOUND | RELIC_FLAG_ACTIVE;
        }
        for (; i < LEN(g_Status.relics); i++) {
            g_Status.relics[i] = RELIC_FLAG_FOUND;
        }
        g_Status.relics[RELIC_GAS_CLOUD] = RELIC_FLAG_FOUND;
        g_Status.subWeapon = 0;
        g_Status.hp = 80;
        g_Status.hpMax = 80;
        g_Status.hearts = 30;
        g_Status.heartsMax = 99;
        g_Status.mpMax = 20;
        g_Status.mp = g_Status.mpMax;
        g_Status.statsBase[0] = 10;
        g_Status.statsBase[1] = 10;
        g_Status.statsBase[2] = 10;
        g_Status.statsBase[3] = 10;
        g_Status.equipment[LEFT_HAND_SLOT] = ITEM_BEKATOWA;
        g_Status.equipment[RIGHT_HAND_SLOT] = ITEM_LEATHER_SHIELD;
        g_Status.equipment[HEAD_SLOT] = ITEM_EMPTY_HEAD;
        g_Status.equipment[ARMOR_SLOT] = ITEM_HIDE_CUIRASS;
        g_Status.equipment[CAPE_SLOT] = ITEM_NO_CAPE;
        g_Status.equipment[ACCESSORY_1_SLOT] = ITEM_NO_ACCESSORY;
        g_Status.equipment[ACCESSORY_2_SLOT] = ITEM_NO_ACCESSORY;

        if (g_StageId == STAGE_NZ0_DEMO) {
            g_Status.subWeapon = 2;
            g_Status.equipment[LEFT_HAND_SLOT] = ITEM_SHORT_SWORD;
        }
        if (g_StageId == STAGE_BO4) {
            g_Status.subWeapon = 3;
            g_Status.equipment[LEFT_HAND_SLOT] = ITEM_SHORT_SWORD;
        }
        if (g_StageId == STAGE_BO5) {
            g_Status.equipment[LEFT_HAND_SLOT] = ITEM_GLADIUS;
        }
        if (g_StageId == STAGE_BO3) {
            g_Status.subWeapon = 3;
            g_Status.relics[RELIC_HOLY_SYMBOL] = RELIC_FLAG_FOUND;
            g_Status.equipment[LEFT_HAND_SLOT] = ITEM_GLADIUS;
            g_Status.hearts = 60;
        }
        if (g_StageId == STAGE_BO2) {
            g_Status.equipment[LEFT_HAND_SLOT] = ITEM_CUTLASS;
        }
        if (g_StageId == STAGE_LIB_DEMO) {
            g_Status.equipment[LEFT_HAND_SLOT] = ITEM_CUTLASS;
            g_Status.statsBase[0] = 15;
        }
        if (g_StageId == STAGE_BO0) {
            g_Status.hearts = 60;
            g_Status.subWeapon = 2;
            g_Status.equipment[LEFT_HAND_SLOT] = ITEM_CLAYMORE;
            g_Status.equipment[RIGHT_HAND_SLOT] = ITEM_CLAYMORE;
            g_Status.mpMax = 50;
            g_Status.mp = g_Status.mpMax;
            g_Status.statsBase[0] = 20;
            g_Status.statsBase[2] = 20;
            g_Status.equipment[ARMOR_SLOT] = ITEM_FIRE_MAIL;
        }
        if (g_StageId == STAGE_BO7) {
            g_Status.subWeapon = 3;
            g_Status.equipment[LEFT_HAND_SLOT] = ITEM_DAMASCUS_SWORD;
        }
        if (g_StageId == STAGE_BO1) {
            g_Status.equipment[LEFT_HAND_SLOT] = ITEM_ICEBRAND;
        }
        if (g_StageId == STAGE_DRE) {
            g_Status.equipment[LEFT_HAND_SLOT] = ITEM_CLAYMORE;
        }
        if (g_StageId == STAGE_NZ1_DEMO) {
            g_Status.equipment[LEFT_HAND_SLOT] = ITEM_FALCHION;
            g_Status.statsBase[0] = 20;
            g_Status.statsBase[2] = 20;
            g_Status.equipment[RIGHT_HAND_SLOT] = ITEM_IRON_SHIELD;
            g_Status.subWeapon = 8;
            g_Status.hearts = 30;
        }
        if (g_StageId == STAGE_BO6) {
            g_Status.equipment[LEFT_HAND_SLOT] = ITEM_MORMEGIL;
            g_Status.equipment[RIGHT_HAND_SLOT] = ITEM_IRON_SHIELD;
            g_Status.subWeapon = 9;
            g_Status.statsBase[0] = 10;
        }
        if (g_StageId == STAGE_CEN) {
            g_Status.equipment[LEFT_HAND_SLOT] = ITEM_BASTARD_SWORD;
            g_Status.equipment[RIGHT_HAND_SLOT] = ITEM_LEATHER_SHIELD;
            g_Status.subWeapon = 2;
            g_Status.hearts = 30;
            g_Status.statsBase[0] = 20;
            g_Status.statsBase[2] = 20;
        }
        if (g_StageId == STAGE_RBO6) {
            g_Status.mpMax = 80;
            g_Status.mp = g_Status.mpMax;
        }
        if (g_StageId == STAGE_RBO7) {
            g_Status.equipment[ARMOR_SLOT] = ITEM_AXE_LORD_ARMOR;
        }
        if (g_StageId == STAGE_RBO1) {
            g_Status.subWeapon = 2;
            g_Status.equipment[LEFT_HAND_SLOT] = ITEM_CLAYMORE;
            g_Status.equipment[HEAD_SLOT] = ITEM_TOPAZ_CIRCLET;
            g_Status.statsBase[0] = 25;
            g_Status.statsBase[2] = 35;
            g_Status.hearts = 70;
        }
        if (g_StageId == STAGE_RBO8) {
            g_Status.equipment[LEFT_HAND_SLOT] = ITEM_IRON_CUIRASS;
            g_Status.equipment[RIGHT_HAND_SLOT] = ITEM_SKULL_SHIELD;
            g_Status.equipment[HEAD_SLOT] = ITEM_BERYL_CIRCLET;
            g_Status.statsBase[0] = 60;
            g_Status.mpMax = 200;
            g_Status.mp = g_Status.mpMax;
        }
        if (g_StageId == STAGE_RNZ1_DEMO) {
            g_Status.subWeapon = 2;
            g_Status.statsBase[0] = 25;
            g_Status.statsBase[2] = 35;
            g_Status.hearts = 70;
        }
        if (g_StageId == STAGE_RBO4) {
            g_Status.equipment[LEFT_HAND_SLOT] = ITEM_CLAYMORE;
            g_Status.statsBase[0] = 25;
        }
        if (g_StageId == STAGE_RBO2) {
            g_Status.equipment[LEFT_HAND_SLOT] = ITEM_CLAYMORE;
            g_Status.equipment[RIGHT_HAND_SLOT] = ITEM_CLAYMORE;
            g_Status.statsBase[0] = 25;
            g_Status.statsBase[2] = 40;
            g_Status.equipment[ARMOR_SLOT] = ITEM_ALUCARD_MAIL;
            g_Status.subWeapon = 9;
            g_Status.hearts = 80;
        }
        if (g_StageId == STAGE_RCEN) {
            g_Status.subWeapon = 2;
            g_Status.equipment[LEFT_HAND_SLOT] = ITEM_ALUCARD_SWORD;
            g_Status.equipment[RIGHT_HAND_SLOT] = ITEM_ALUCARD_SHIELD;
            g_Status.statsBase[0] = 25;
            g_Status.statsBase[2] = 35;
            g_Status.hearts = 70;
            g_Status.mpMax = 80;
            g_Status.mp = g_Status.mpMax;
        }
        if (g_StageId == STAGE_RBO5) {
            g_Status.equipment[LEFT_HAND_SLOT] = ITEM_SWORD_OF_HADOR;
            g_Status.equipment[RIGHT_HAND_SLOT] = ITEM_IRON_SHIELD;
            g_Status.subWeapon = 8;
            g_Status.statsBase[0] = 30;
            g_Status.statsBase[2] = 35;
            g_Status.heartsMax = 99;
        }
        if (g_StageId == STAGE_RBO3) {
            g_Status.equipment[LEFT_HAND_SLOT] = ITEM_FALCHION;
            g_Status.equipment[RIGHT_HAND_SLOT] = ITEM_IRON_SHIELD;
            g_Status.subWeapon = 3;
            g_Status.statsBase[0] = 30;
            g_Status.statsBase[2] = 30;
            g_Status.heartsMax = 99;
        }
        if (g_StageId == STAGE_RBO0) {
            g_Status.equipment[LEFT_HAND_SLOT] = ITEM_BASTARD_SWORD;
            g_Status.equipment[RIGHT_HAND_SLOT] = ITEM_IRON_SHIELD;
            g_Status.equipment[ARMOR_SLOT] = ITEM_ALUCARD_MAIL;
            g_Status.subWeapon = 2;
            g_Status.statsBase[0] = 30;
            g_Status.statsBase[2] = 35;
            g_Status.heartsMax = 40;
        }
        g_Status.timerHours = 0;
        g_Status.timerMinutes = 0;
        g_Status.timerSeconds = 0;
        g_Status.timerFrames = 0;
        func_800F53A4();
    }
}

void DemoOpenFile(s32 arg0) {
    char fileName[0x100];
    s32 var_s0;

    memset(DEMO_KEY_PTR, 0, 0x2000);
    if ((D_8C630D4 == 2) && (arg0 == 0)) {
        sprintf(fileName, "BIN/DEMOKEY%c%c.BIN;1",
                ((D_psp_08C630DC / 10) % 10) + '0',
                (D_psp_08C630DC % 10) + '0');
        var_s0 = 0;
    } else {
        sprintf(fileName, "BIN/DEMOKEY.BIN;1");
        var_s0 = g_DemoKeyIdx << 0xD;
    }
    while (func_890FBEC(fileName, DEMO_KEY_PTR, var_s0, 0x2000) == 0) {
        VSync(30);
    }
}

void DemoSaveFile(void) {
    char buf[0x100];
    long fd;
    // Castlevania X
    sprintf(buf,
            "host0:c:/psp/悪魔城ドラキュラＸ/PRODUCTS/DISK/BIN/DEMOKEY%c%c.BIN",
            ((D_psp_08C630DC / 10) % 10) + '0', (D_psp_08C630DC % 10) + '0');
    fd = func_8939D68(buf, 0x602, 0x1FF);
    func_8939D20(fd, DEMO_KEY_PTR, 0x2000);
    func_8939D40(fd);
}

void DemoInit(s32 arg0) {
    s32* temp;
    g_DemoPtr = DEMO_KEY_PTR;
    temp = (s32*)g_DemoPtr;
    *temp = 0;

    DemoGameInit(arg0);
    switch (arg0) {
    case 0:
    case 2:
        DemoOpenFile(arg0);
        if (arg0 == 0) {
            g_DemoMode = Demo_PlaybackInit;
        } else {
            g_DemoMode = Demo_Playback;
        }
        break;

    case 1:
        g_DemoMode = Demo_Recording;
        break;
    }
}

typedef struct {
    u16 psx;
    u16 psp;
} ButtonMap;

// mapping between PSX and PSP buttons
static ButtonMap D_psp_09160AA0[] = {
    {0x1000, PAD_UP},     {0x4000, PAD_DOWN},        {0x8000, PAD_LEFT},
    {0x2000, PAD_RIGHT},  {0x0010, PAD_TRIANGLE},    {0x0040, PAD_CROSS},
    {0x0080, PAD_SQUARE}, {0x0020, PAD_CIRCLE},      {0x0100, PAD_SELECT},
    {0x0800, PAD_START},  {0x0004, PAD_L1 | PAD_R1}, {0x0008, PAD_R1},
    {0x0002, PAD_L1}};
static ButtonMap D_psp_09160AD8[] = {
    {0x1000, PAD_UP},     {0x4000, PAD_DOWN},     {0x8000, PAD_LEFT},
    {0x2000, PAD_RIGHT},  {0x0010, PAD_TRIANGLE}, {0x0040, PAD_CROSS},
    {0x0080, PAD_SQUARE}, {0x0020, PAD_CIRCLE},   {0x0100, PAD_SELECT},
    {0x0008, PAD_R1},     {0x0004, PAD_L1},       {0x0800, PAD_START}};

u16 func_psp_090FF548(u16 psx) {
    ButtonMap* ptr;
    s32 i;
    u16 ret;
    s32 count;

    ret = 0;
    if (g_PlayableCharacter == PLAYER_ALUCARD) {
        ptr = D_psp_09160AA0;
        count = LEN(D_psp_09160AA0);
    } else {
        ptr = D_psp_09160AD8;
        count = LEN(D_psp_09160AD8);
    }
    for (i = 0; i < count; i++) {
        if (psx & ptr[i].psx) {
            ret |= ptr[i].psp;
        }
    }
    return ret;
}

u16 func_psp_090FF608(u16 psp) {
    s32 i;
    s32 count;
    ButtonMap* ptr;

    u16 ret = 0;
    if (g_PlayableCharacter == PLAYER_ALUCARD) {
        ptr = D_psp_09160AA0;
        count = LEN(D_psp_09160AA0);
        for (i = 0; i < count; i++) {
            if ((psp & ptr[i].psp) != ptr[i].psp) {
                continue;
            }
            ret |= ptr[i].psx;

            if (i >= 10) {
                break;
            }
        }
    } else {
        ptr = D_psp_09160AD8;
        count = LEN(D_psp_09160AD8);
        for (i = 0; i < count; i++) {
            if (psp & ptr[i].psp) {
                ret |= ptr[i].psx;
            }
        }
    }
    return ret;
}

void DemoUpdate(void) {
    u8 curBtnLo;
    u8 curBtnHi;
    u16 curBtn;
    u8 btnLo;
    u8 btnHi;
    u32 btn;
    u8 frameCount;
    s32 demoOffset;

#ifdef VERSION_PC
    g_DemoPtr = DEMO_KEY_PTR;
#endif
    btnLo = g_DemoPtr[0];
    btnHi = g_DemoPtr[1];
    frameCount = g_DemoPtr[2];
    switch (g_DemoMode) {
    case Demo_None:
    case Demo_End:
        return;

    case Demo_PlaybackInit:
    case Demo_Playback:
        func_8926498();
        FntPrint("demonstration\n");
        if (!frameCount) {
            g_DemoPtr += DEMO_KEY_LEN;
            btnLo = g_DemoPtr[0];
            btnHi = g_DemoPtr[1];
            frameCount = g_DemoPtr[2];
        }

        // Check if end of playback
        if ((btnLo == 0xFF && btnHi == 0xFF) || g_pads[0].tapped & PAD_START) {
            if (g_DemoMode == Demo_Playback) {
                g_DemoMode = Demo_End;
            } else {
                g_DemoMode = Demo_None;
            }
        } else {
            btn = btnLo + (btnHi << 8);
            g_pads[0].pressed = 0;
            g_pads[0].pressed = func_psp_090FF548(btn);
            g_pads[0].tapped = 0;
            g_DemoPtr[2]--;
        }
        break;

    case Demo_Recording:
        FntPrint("demo key in:%04x/%04x\n", (s32)(g_DemoPtr - DEMO_KEY_PTR),
                 DEMO_MAX_LEN);
        if ((s32)(g_DemoPtr - DEMO_KEY_PTR) > DEMO_MAX_LEN - DEMO_KEY_LEN - 1) {
            FntPrint("demo overflow\n");
            return;
        }

        if (g_pads[0].tapped & PAD_SELECT) {
            g_DemoPtr += DEMO_KEY_LEN;
            g_DemoPtr[0] = 0xFF;
            g_DemoPtr[1] = 0xFF;
            DemoSaveFile();
            g_DemoMode = Demo_None;
        }
        curBtn = func_psp_090FF608(g_pads[0].pressed);
        curBtnLo = curBtn & 0xFF;
        curBtnHi = curBtn >> 8;
        if (frameCount != 0xFF && btnLo == curBtnLo && btnHi == curBtnHi) {
            g_DemoPtr[2]++;
        } else {
            if (g_DemoPtr[2]) {
                g_DemoPtr += DEMO_KEY_LEN;
            }
            g_DemoPtr[0] = curBtnLo;
            g_DemoPtr[1] = curBtnHi;
            g_DemoPtr[2] = 1;
        }
        break;
    }
}
