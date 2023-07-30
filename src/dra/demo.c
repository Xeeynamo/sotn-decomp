#include "dra.h"
#include "items.h"

void DemoGameInit(s32 arg0) {
    s32 i;

    if (arg0 != 2) {
        if (g_StageId == STAGE_NZ0) {
            g_StageId = STAGE_NZ0_DEMO;
        }
        if (g_StageId == STAGE_NZ1) {
            g_StageId = STAGE_NZ1_DEMO;
        }
        if (g_StageId == STAGE_LIB) {
            g_StageId = STAGE_LIB_DEMO;
        }
        if (g_StageId == (STAGE_NZ1 | STAGE_INVERTEDCASTLE_FLAG)) {
            g_StageId = STAGE_RNZ1;
        }
    } else {
        D_80137594 = D_80097C98 & STAGE_INVERTEDCASTLE_MASK;
        g_StageId = D_800A243C[D_80137594];
    }

    InitStatsAndGear(0);
    if (g_StageId != STAGE_ST0) {
        g_Status.level = 99;
        for (i = 0; i < RELIC_BAT_CARD; i++) {
            g_Status.relics[i] = RELIC_FLAG_FOUND | RELIC_FLAG_ACTIVE;
        }
        for (; i < RELIC_END; i++) {
            g_Status.relics[i] = RELIC_FLAG_FOUND;
        }
        g_Status.relics[RELIC_GAS_CLOUD] = RELIC_FLAG_FOUND;
        g_Status.hp = 80;
        g_Status.hpMax = 80;
        g_Status.subWeapon = 0;
        g_Status.hearts = 30;
        g_Status.heartsMax = 99;
        g_Status.mpMax = 20;
        g_Status.mp = 20;
        g_Status.statsBase[0] = 10;
        g_Status.statsBase[1] = 10;
        g_Status.statsBase[2] = 10;
        g_Status.statsBase[3] = 10;
        g_Status.equipment[0] = ITEM_BEKATOWA;
        g_Status.equipment[1] = ITEM_LEATHER_SHIELD;
        g_Status.equipment[2] = 0x1A;
        g_Status.equipment[3] = 2;
        g_Status.equipment[4] = 0x30;
        g_Status.equipment[5] = 0x39;
        g_Status.equipment[6] = 0x39;
        if (g_StageId == STAGE_NZ0_DEMO) {
            g_Status.subWeapon = 2;
            g_Status.equipment[0] = ITEM_SHORT_SWORD;
        }
        if (g_StageId == STAGE_BO4) {
            g_Status.subWeapon = 3;
            g_Status.equipment[0] = ITEM_SHORT_SWORD;
        }
        if (g_StageId == STAGE_BO5) {
            g_Status.equipment[0] = ITEM_GLADIUS;
        }
        if (g_StageId == STAGE_BO3) {
            g_Status.subWeapon = 3;
            g_Status.equipment[0] = ITEM_GLADIUS;
            g_Status.relics[RELIC_HOLY_SYMBOL] = 1;
            g_Status.hearts = 60;
        }
        if (g_StageId == STAGE_BO2) {
            g_Status.equipment[0] = ITEM_CUTLASS;
        }
        if (g_StageId == STAGE_LIB_DEMO) {
            g_Status.equipment[0] = ITEM_CUTLASS;
            g_Status.statsBase[0] = 15;
        }
        if (g_StageId == STAGE_BO0) {
            g_Status.hearts = 60;
            g_Status.equipment[0] = ITEM_CLAYMORE;
            g_Status.subWeapon = 2;
            g_Status.mpMax = 50;
            g_Status.mp = 50;
            g_Status.statsBase[0] = 20;
            g_Status.statsBase[2] = 20;
            g_Status.equipment[3] = 0xA;
        }
        if (g_StageId == STAGE_BO7) {
            g_Status.subWeapon = 3;
            g_Status.equipment[0] = ITEM_DAMASCUS_SWORD;
        }
        if (g_StageId == STAGE_BO1) {
            g_Status.equipment[0] = ITEM_ICEBRAND;
        }
        if (g_StageId == STAGE_DRE) {
            g_Status.equipment[0] = ITEM_CLAYMORE;
        }
        if (g_StageId == STAGE_NZ1_DEMO) {
            g_Status.equipment[0] = ITEM_FALCHION;
            g_Status.equipment[1] = ITEM_IRON_SHIELD;
            g_Status.statsBase[0] = 20;
            g_Status.statsBase[2] = 20;
            g_Status.subWeapon = 8;
            g_Status.hearts = 30;
        }
        if (g_StageId == STAGE_BO6) {
            g_Status.equipment[0] = ITEM_MORMEGIL;
            g_Status.equipment[1] = ITEM_IRON_SHIELD;
            g_Status.subWeapon = 9;
            g_Status.statsBase[0] = 10;
        }
        if (g_StageId == STAGE_RBO6) {
            g_Status.mpMax = 80;
            g_Status.mp = 80;
        }
        if (g_StageId == STAGE_RBO7) {
            g_Status.equipment[3] = 25;
        }
        if (g_StageId == STAGE_RBO1) {
            g_Status.subWeapon = 2;
            g_Status.equipment[0] = ITEM_CLAYMORE;
            g_Status.equipment[2] = 0x29;
            g_Status.statsBase[0] = 25;
            g_Status.statsBase[2] = 35;
            g_Status.hearts = 70;
        }
        if (g_StageId == STAGE_RBO8) {
            g_Status.equipment[0] = 4;
            g_Status.equipment[1] = ITEM_SKULL_SHIELD;
            g_Status.equipment[2] = 0x2A;
            g_Status.statsBase[0] = 60;
            g_Status.mpMax = 200;
            g_Status.mp = 200;
        }
        if (g_StageId == STAGE_RNZ1) {
            g_Status.subWeapon = 2;
            g_Status.statsBase[0] = 25;
            g_Status.statsBase[2] = 35;
            g_Status.hearts = 70;
        }
        if (g_StageId == STAGE_RBO4) {
            g_Status.equipment[0] = ITEM_CLAYMORE;
            g_Status.statsBase[0] = 25;
        }
        if (g_StageId == STAGE_RBO2) {
            g_Status.equipment[0] = ITEM_CLAYMORE;
            g_Status.statsBase[0] = 25;
            g_Status.statsBase[2] = 40;
            g_Status.equipment[3] = 15;
            g_Status.subWeapon = 9;
            g_Status.hearts = 80;
        }
        if (g_StageId == STAGE_RCEN) {
            g_Status.subWeapon = 2;
            g_Status.equipment[0] = ITEM_ALUCARD_SWORD;
            g_Status.equipment[1] = ITEM_ALUCARD_SHIELD;
            g_Status.statsBase[0] = 25;
            g_Status.statsBase[2] = 35;
            g_Status.hearts = 70;
            g_Status.mpMax = 80;
            g_Status.mp = 80;
        }
        if (g_StageId == STAGE_RBO5) {
            g_Status.equipment[0] = ITEM_SWORD_OF_HADOR;
            g_Status.equipment[1] = ITEM_IRON_SHIELD;
            g_Status.subWeapon = 8;
            g_Status.statsBase[0] = 30;
            g_Status.statsBase[2] = 35;
            g_Status.heartsMax = 99;
        }
        if (g_StageId == STAGE_RBO3) {
            g_Status.equipment[0] = ITEM_FALCHION;
            g_Status.equipment[1] = ITEM_IRON_SHIELD;
            g_Status.subWeapon = 3;
            g_Status.statsBase[0] = 30;
            g_Status.statsBase[2] = 30;
            g_Status.heartsMax = 99;
        }
        if (g_StageId == STAGE_RBO0) {
            g_Status.equipment[0] = ITEM_BASTARD_SWORD;
            g_Status.equipment[1] = ITEM_IRON_SHIELD;
            g_Status.equipment[3] = 15;
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
// #endif

void DemoOpenFile(s32 arg0) {
    char fileName[0x100];
    long fd;

    if (g_UseDisk) {
        g_CdStep = CdStep_LoadInit;
        g_LoadFile = CdFile_DemoKey;
        g_mapTilesetId = D_80137594;
        return;
    }
    if (arg0 == 0) {
        __builtin_memcpy(fileName, "sim:c:\\bin\\demo_key.bin",
                         sizeof("sim:c:\\bin\\demo_key.bin"));
    } else {
        __builtin_memcpy(fileName, "sim:c:\\bin\\dk_000.bin",
                         sizeof("sim:c:\\bin\\dk_000.bin"));
        fileName[15] = '0' + (D_80137594 / 10 % 10);
        fileName[16] = '0' + (D_80137594 % 10);
    }
    fd = open(fileName, O_RDONLY);
    if (fd < 0) {
        return;
    }
    read(fd, DEMO_KEY_PTR, 0x2000);
    close(fd);
}

void DemoSaveFile(void) {
    char buf[0x100];
    long fd;

    __builtin_memcpy(
        buf, "sim:c:\\bin\\demo_key.bin", sizeof("sim:c:\\bin\\demo_key.bin"));
    fd = open(buf, O_CREAT);
    if (fd < 0) {
        return;
    }
    if (write(fd, DEMO_KEY_PTR, 0x2000) < 0) {
        close(fd);
        return;
    }
    if (close(fd) < 0) {
        return;
    }

    __builtin_memcpy(buf, "  OK", sizeof("  OK"));
    DebugInputWait(buf);
}

void DemoInit(s32 arg0) {
    D_80137590 = DEMO_KEY_PTR;
    *((s32*)DEMO_KEY_PTR) = 0;

    DemoGameInit(arg0);

    switch (arg0) {
    case 0:
    case 2:
        DemoOpenFile(arg0);
        g_DemoMode = arg0 == 0 ? Demo_PlaybackInit : Demo_Playback;
        break;

    case 1:
        g_DemoMode = Demo_Recording;

    default:
        break;
    }
}

#define DEMO_KEY_LEN 3
#define DEMO_MAX_LEN 0x2000
void DemoUpdate(void) {
    u8 curBtnLo;
    u8 curBtnHi;
    u8 frameCount;
    u8 btnHi;
    u8 btnLo;
    s32 demoOffset;

    btnLo = D_80137590[0];
    btnHi = D_80137590[1];
    frameCount = D_80137590[2];
    switch (g_DemoMode) {
    case Demo_None:
    case Demo_End:
        return;
    case Demo_PlaybackInit:
    case Demo_Playback:
        FntPrint("demonstration\n");
        if (frameCount == 0) {
            D_80137590 += DEMO_KEY_LEN;
            btnLo = D_80137590[0];
            btnHi = D_80137590[1];
        }

        // Check if end of playback
        if ((btnLo == 0xFF && btnHi == 0xFF) || g_pads[0].tapped & PAD_START) {
            if (g_DemoMode == Demo_Playback) {
                g_DemoMode = Demo_End;
            } else {
                g_DemoMode = Demo_None;
            }
        } else {
            g_pads->pressed = btnLo + (btnHi << 8);
            g_pads[0].tapped = 0;
            D_80137590[2]--;
        }
        break;
    case Demo_Recording:
        demoOffset = D_80137590 - DEMO_KEY_PTR;
        FntPrint("demo key in:%04x/%04x\n", demoOffset, DEMO_MAX_LEN);
        if ((s32)(D_80137590 - DEMO_KEY_PTR) >= DEMO_MAX_LEN - DEMO_KEY_LEN) {
            FntPrint("demo overflow\n");
            return;
        }

        if (g_pads[1].tapped & PAD_CIRCLE) {
            D_80137590 += DEMO_KEY_LEN;
            D_80137590[0] = 0xFF;
            D_80137590[1] = 0xFF;
            DemoSaveFile();
            g_DemoMode = Demo_None;
        }
        curBtnLo = g_pads[0].pressed;
        curBtnHi = g_pads->pressed >> 8;
        if (frameCount != 0xFF && btnLo == curBtnLo && btnHi == curBtnHi) {
            D_80137590[2]++;
        } else {
            if (D_80137590[2] != 0) {
                D_80137590 += DEMO_KEY_LEN;
            }
            D_80137590[0] = curBtnLo;
            D_80137590[1] = curBtnHi;
            D_80137590[2] = 1;
        }
        break;
    }
}
