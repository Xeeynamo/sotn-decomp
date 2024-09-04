#include "dra.h"

extern u8 D_800A243C[32] = {
    STAGE_ST0,       STAGE_BO0,      STAGE_BO4,      STAGE_BO1,  STAGE_BO2,
    STAGE_BO3,       STAGE_NZ0_DEMO, STAGE_BO5,      STAGE_RBO1, STAGE_DRE,
    STAGE_NZ1_DEMO,  STAGE_RBO0,     STAGE_RBO2,     STAGE_BO7,  STAGE_BO6,
    STAGE_RBO3,      STAGE_RBO4,     STAGE_LIB_DEMO, STAGE_RBO5, STAGE_RBO7,
    STAGE_RNZ1_DEMO, STAGE_RBO8,     STAGE_NO0,      STAGE_NO0,  STAGE_NO0,
    STAGE_NO0,       STAGE_NO0,      STAGE_RCEN,     STAGE_RBO6,
};

// BSS
extern u8* g_DemoPtr;
extern s32 g_DemoKeyIdx;

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
            g_StageId = STAGE_RNZ1_DEMO;
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
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (g_StageId == STAGE_NZ0_DEMO) {
            g_Status.subWeapon = 2;
REDACTED
        }
        if (g_StageId == STAGE_BO4) {
            g_Status.subWeapon = 3;
REDACTED
        }
        if (g_StageId == STAGE_BO5) {
REDACTED
        }
        if (g_StageId == STAGE_BO3) {
            g_Status.subWeapon = 3;
REDACTED
            g_Status.relics[RELIC_HOLY_SYMBOL] = 1;
            g_Status.hearts = 60;
        }
        if (g_StageId == STAGE_BO2) {
REDACTED
        }
        if (g_StageId == STAGE_LIB_DEMO) {
REDACTED
            g_Status.statsBase[0] = 15;
        }
        if (g_StageId == STAGE_BO0) {
            g_Status.hearts = 60;
REDACTED
            g_Status.subWeapon = 2;
            g_Status.mpMax = 50;
            g_Status.mp = 50;
            g_Status.statsBase[0] = 20;
            g_Status.statsBase[2] = 20;
REDACTED
        }
        if (g_StageId == STAGE_BO7) {
            g_Status.subWeapon = 3;
REDACTED
        }
        if (g_StageId == STAGE_BO1) {
REDACTED
        }
        if (g_StageId == STAGE_DRE) {
REDACTED
        }
        if (g_StageId == STAGE_NZ1_DEMO) {
REDACTED
REDACTED
            g_Status.statsBase[0] = 20;
            g_Status.statsBase[2] = 20;
            g_Status.subWeapon = 8;
            g_Status.hearts = 30;
        }
        if (g_StageId == STAGE_BO6) {
REDACTED
REDACTED
            g_Status.subWeapon = 9;
            g_Status.statsBase[0] = 10;
        }
        if (g_StageId == STAGE_RBO6) {
            g_Status.mpMax = 80;
            g_Status.mp = 80;
        }
        if (g_StageId == STAGE_RBO7) {
REDACTED
        }
        if (g_StageId == STAGE_RBO1) {
            g_Status.subWeapon = 2;
REDACTED
REDACTED
            g_Status.statsBase[0] = 25;
            g_Status.statsBase[2] = 35;
            g_Status.hearts = 70;
        }
        if (g_StageId == STAGE_RBO8) {
REDACTED
REDACTED
REDACTED
            g_Status.statsBase[0] = 60;
            g_Status.mpMax = 200;
            g_Status.mp = 200;
        }
        if (g_StageId == STAGE_RNZ1_DEMO) {
            g_Status.subWeapon = 2;
            g_Status.statsBase[0] = 25;
            g_Status.statsBase[2] = 35;
            g_Status.hearts = 70;
        }
        if (g_StageId == STAGE_RBO4) {
REDACTED
            g_Status.statsBase[0] = 25;
        }
        if (g_StageId == STAGE_RBO2) {
REDACTED
            g_Status.statsBase[0] = 25;
            g_Status.statsBase[2] = 40;
REDACTED
            g_Status.subWeapon = 9;
            g_Status.hearts = 80;
        }
        if (g_StageId == STAGE_RCEN) {
            g_Status.subWeapon = 2;
REDACTED
REDACTED
            g_Status.statsBase[0] = 25;
            g_Status.statsBase[2] = 35;
            g_Status.hearts = 70;
            g_Status.mpMax = 80;
            g_Status.mp = 80;
        }
        if (g_StageId == STAGE_RBO5) {
REDACTED
REDACTED
            g_Status.subWeapon = 8;
            g_Status.statsBase[0] = 30;
            g_Status.statsBase[2] = 35;
            g_Status.heartsMax = 99;
        }
        if (g_StageId == STAGE_RBO3) {
REDACTED
REDACTED
            g_Status.subWeapon = 3;
            g_Status.statsBase[0] = 30;
            g_Status.statsBase[2] = 30;
            g_Status.heartsMax = 99;
        }
        if (g_StageId == STAGE_RBO0) {
REDACTED
REDACTED
REDACTED
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
    long fd;

    if (g_UseDisk) {
        g_CdStep = CdStep_LoadInit;
        g_LoadFile = CdFile_DemoKey;
        g_LoadOvlIdx = g_DemoKeyIdx;
        return;
    }
    if (arg0 == 0) {
        __builtin_memcpy(fileName, "sim:c:\\bin\\demo_key.bin",
                         sizeof("sim:c:\\bin\\demo_key.bin"));
    } else {
        __builtin_memcpy(fileName, "sim:c:\\bin\\dk_000.bin",
                         sizeof("sim:c:\\bin\\dk_000.bin"));
        fileName[15] = '0' + (g_DemoKeyIdx / 10 % 10);
        fileName[16] = '0' + (g_DemoKeyIdx % 10);
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
#if !defined(VERSION_PC)
    g_DemoPtr = DEMO_KEY_PTR;
#endif
    *((s32*)g_DemoPtr) = 0;

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

void DemoUpdate(void) {
    u8 curBtnLo;
    u8 curBtnHi;
    u8 frameCount;
    u8 btnHi;
    u8 btnLo;
    s32 demoOffset;

    btnLo = g_DemoPtr[0];
    btnHi = g_DemoPtr[1];
    frameCount = g_DemoPtr[2];
    switch (g_DemoMode) {
    case Demo_None:
    case Demo_End:
        return;
    case Demo_PlaybackInit:
    case Demo_Playback:
        FntPrint("demonstration\n");
        if (frameCount == 0) {
            g_DemoPtr += DEMO_KEY_LEN;
            btnLo = g_DemoPtr[0];
            btnHi = g_DemoPtr[1];
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
            g_DemoPtr[2]--;
        }
        break;
    case Demo_Recording:
        demoOffset = g_DemoPtr - DEMO_KEY_PTR;
        FntPrint("demo key in:%04x/%04x\n", demoOffset, DEMO_MAX_LEN);
        if ((s32)(g_DemoPtr - DEMO_KEY_PTR) >= DEMO_MAX_LEN - DEMO_KEY_LEN) {
            FntPrint("demo overflow\n");
            return;
        }

        if (g_pads[1].tapped & PAD_CIRCLE) {
            g_DemoPtr += DEMO_KEY_LEN;
            g_DemoPtr[0] = 0xFF;
            g_DemoPtr[1] = 0xFF;
            DemoSaveFile();
            g_DemoMode = Demo_None;
        }
        curBtnLo = g_pads[0].pressed;
        curBtnHi = g_pads->pressed >> 8;
        if (frameCount != 0xFF && btnLo == curBtnLo && btnHi == curBtnHi) {
            g_DemoPtr[2]++;
        } else {
            if (g_DemoPtr[2] != 0) {
                g_DemoPtr += DEMO_KEY_LEN;
            }
            g_DemoPtr[0] = curBtnLo;
            g_DemoPtr[1] = curBtnHi;
            g_DemoPtr[2] = 1;
        }
        break;
    }
}
