// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo4.h"

INCLUDE_ASM("boss/bo4/nonmatchings/doppleganger", func_us_801C1A38);

INCLUDE_ASM("boss/bo4/nonmatchings/doppleganger", func_us_801C1CB0);

INCLUDE_ASM("boss/bo4/nonmatchings/doppleganger", func_us_801C2284);

typedef enum {
    THINK_STEP_0 = 0,
    THINK_STEP_1,
    THINK_STEP_2,
    THINK_STEP_3,
    THINK_STEP_5 = 5,
    THINK_STEP_6,
    THINK_STEP_7,
    THINK_STEP_19 = 19,
} ThinkStep;

extern u32 D_us_801D3D24; // think_step
extern s32 D_us_801D3D28; // timer
extern s32 D_us_801D3D2C;

void func_us_801C2DFC(void) {
    s32 temp_s2;
    s32 playerDistanceX;
    u32 facingLeft;

    temp_s2 = g_Tilemap.scrollX.i.hi + DOPPLEGANGER.posX.i.hi;
    g_Dop.demo_timer = 2;
    g_Dop.padSim = 0;

    if (g_Player.status & PLAYER_STATUS_DEAD) {
        D_us_801D3D24 = 0x10;
    }
    if (g_Dop.status & PLAYER_STATUS_UNK10000) {
        D_us_801D3D24 = 0;
    }
    if (g_Dop.status & PLAYER_STATUS_STONE) {
        D_us_801D3D24 = 0xF;
    }

    if ((g_Player.timers[ALU_T_12]) &&
        (D_us_801D3D24 != 0x10) &&
        !(g_Dop.status & 2)) {
        g_Dop.padSim = PAD_R2;
        D_us_801D3D28 = 0x40;
        D_us_801D3D24 = 0xE;
    }

    facingLeft = false;
    if ((DOPPLEGANGER.posX.i.hi - PLAYER.posX.i.hi) >= 0) {
        facingLeft = true;
    }

    playerDistanceX = abs(DOPPLEGANGER.posX.i.hi - PLAYER.posX.i.hi);

    FntPrint("hm:%02x\n", playerDistanceX);
    FntPrint("think_step:%02x\n", D_us_801D3D24);

    switch (D_us_801D3D24) {
    case 0:
        if (!(g_Dop.status & 0x10000)) {
            if (g_Player.timers[ALU_T_10]) {
                if (rand() & 1) {
                    if (facingLeft) {
                        g_Dop.padSim = PAD_LEFT;
                    } else {
                        g_Dop.padSim = PAD_RIGHT;
                    }
                    g_Dop.padSim |= PAD_CROSS;
                    D_us_801D3D24 = THINK_STEP_7;
                } else {
                    g_Dop.padSim |= PAD_DOWN;
                    D_us_801D3D24 = THINK_STEP_5;
                    D_us_801D3D28 = 0x48;
                }
            } else if (abs(DOPPLEGANGER.posY.i.hi - PLAYER.posY.i.hi) > 32) {
                if (facingLeft) {
                    g_Dop.padSim = PAD_LEFT;
                } else {
                    g_Dop.padSim = PAD_RIGHT;
                }
                g_Dop.padSim |= PAD_CROSS;
                D_us_801D3D24 = THINK_STEP_7;
            } else if (playerDistanceX > 80) {
                if (facingLeft) {
                    g_Dop.padSim = PAD_LEFT;
                } else {
                    g_Dop.padSim = PAD_RIGHT;
                }
            } else {
                D_us_801D3D28 = 0x10;
                D_us_801D3D24 = THINK_STEP_1;
            }
        }
        break;
    case 1:                                         /* switch 1 */
        if (DOPPLEGANGER.facingLeft != facingLeft) {
            if (facingLeft) {
                g_Dop.padSim = PAD_LEFT;
            } else {
                g_Dop.padSim = PAD_RIGHT;
            }
        }
        if (playerDistanceX > 80) {
            D_us_801D3D24 = THINK_STEP_0;
        } else {
            if ((temp_s2 < 96 && DOPPLEGANGER.facingLeft == false) ||
                (temp_s2 > 416 && DOPPLEGANGER.facingLeft)) {
                D_us_801D3D28 = 0x40;
                g_Dop.padSim |= PAD_R1;
                D_us_801D3D24 = THINK_STEP_3;
                break;
            }

            if ((g_Player.timers[ALU_T_9]) ||
                ((g_Player.status & 0x20) &&
                (rand() & 1))) {
                switch (rand() & 7) {
                case 0:
                case 6:
                case 7:
                    g_Dop.padSim |= PAD_CROSS;
                    D_us_801D3D24 = THINK_STEP_6;
                    D_us_801D3D28 = 0x48;
                    break;
                case 1:
                    g_Dop.padSim |= PAD_DOWN;
                    D_us_801D3D24 = THINK_STEP_5;
                    D_us_801D3D28 = 0x48;
                    break;
                case 2:
                    if ((g_Player.status & 0x20)) {
                        g_Dop.padSim |= PAD_DOWN;
                        D_us_801D3D24 = THINK_STEP_5;
                        D_us_801D3D28 = 0x48;
                        break;
                    }
                    // fallthrough
                case 3:
                case 4:
                case 5:
                    g_Dop.padSim |= PAD_TRIANGLE;
                    D_us_801D3D24 = THINK_STEP_2;
                    D_us_801D3D28 = 0x20;
                    break;
                }
            } else if (g_Player.timers[ALU_T_10]) {
                if (rand() & 1) {
                    if (facingLeft) {
                        g_Dop.padSim = PAD_LEFT;
                    } else {
                        g_Dop.padSim = PAD_RIGHT;
                    }
                    g_Dop.padSim |= PAD_CROSS;
                    D_us_801D3D24 = THINK_STEP_7;
                } else {
                    g_Dop.padSim |= PAD_DOWN;
                    D_us_801D3D24 = THINK_STEP_5;
                    D_us_801D3D28 = 0x48;
                }
            } else {
                if (playerDistanceX < 0x38) {
                    if (D_us_801D3D2C) {
                        D_us_801D3D2C--;
                    } else {
                        g_Dop.padSim |= PAD_SQUARE;
                        D_us_801D3D2C = 0x20;
                    }
                } else if (--D_us_801D3D28 == 0) {
                    g_Dop.padSim |= PAD_UP | PAD_SQUARE;
                    D_us_801D3D28 = 0x70;
                    D_us_801D3D2C = 0x20;
                }
            }
        }
        break;
    case 2:                                         /* switch 1 */
        if (--D_us_801D3D28 == 0) {
            g_Dop.padSim = PAD_UP | PAD_CIRCLE;
            D_us_801D3D24 = 0;
            D_us_801D3D28 = 0x70;
        }
        break;
    case 3:                                         /* switch 1 */
        if (DOPPLEGANGER.step_s) {
            g_Dop.padSim = PAD_SQUARE;
            D_us_801D3D28 = 0x18;
            D_us_801D3D24 = 4;
        }
        break;
    case 4:                                         /* switch 1 */
        if (!(g_GameTimer % 2)) {
            g_Dop.padSim = PAD_UP;
        }

        if (--D_us_801D3D28 == 0) {
            g_Dop.padSim = PAD_R1;
            D_us_801D3D24 = THINK_STEP_0;
        }
        break;
    case 5:
        if ((--D_us_801D3D28 == 0) || !(g_Dop.status & 0x20)) {
            D_us_801D3D24 = THINK_STEP_0;
            D_us_801D3D2C = 0x20;
        }
        if (DOPPLEGANGER.facingLeft != facingLeft) {
            if (facingLeft) {
                g_Dop.padSim = PAD_LEFT;
            } else {
                g_Dop.padSim = PAD_RIGHT;
            }
        }

        g_Dop.padSim |= PAD_DOWN;
        if (playerDistanceX < 56) {
            if (D_us_801D3D2C) {
                D_us_801D3D2C--;
            } else {
                g_Dop.padSim |= PAD_DOWN | PAD_SQUARE;
                D_us_801D3D2C = 0x20;
            }
        }
        break;
    case 6:                                         /* switch 1 */
        if ((g_Dop.vram_flag & 1)) {
            D_us_801D3D24 = THINK_STEP_0;
        } else {
            g_Dop.padSim |= PAD_CROSS;
            if (!(g_GameTimer % 32)) {
                g_Dop.padSim |= PAD_UP | PAD_CIRCLE;
            }
        }
        break;
    case 7:
        if ((g_Dop.vram_flag & 1)) {
            D_us_801D3D24 = THINK_STEP_0;
        } else {
            if (playerDistanceX > 16) {
                if (DOPPLEGANGER.facingLeft) {
                    g_Dop.padSim = PAD_LEFT;
                } else {
                    g_Dop.padSim = PAD_RIGHT;
                }
            }

            g_Dop.padSim |= 0x40;
            if (DOPPLEGANGER.velocityY > 0) {
                if (DOPPLEGANGER.velocityY > 0x20000) {
                    g_Dop.padSim |= PAD_DOWN | PAD_SQUARE | PAD_CROSS;
                }

                if (abs(DOPPLEGANGER.posY.i.hi - PLAYER.posY.i.hi) < 0x10) {
                    g_Dop.padSim |= PAD_DOWN | PAD_SQUARE;
                }
            }
        }
        break;
    case 14:                                        /* switch 1 */
        if (!(g_GameTimer % 8)) {
            g_Dop.padSim = PAD_UP;
        }
        if (!(g_Dop.status & 2) && (g_GameTimer & 1)) {
            g_Dop.padSim = PAD_R2;
        }

        if (--D_us_801D3D28 == 0) {
            if (g_Dop.status & PLAYER_STATUS_MIST_FORM) {
                g_Dop.padSim = PAD_R2;
            }
            D_us_801D3D24 = THINK_STEP_0;
        }
        break;
    case 15:
        if (!(g_Dop.status & 0x80)) {
            D_us_801D3D24 = THINK_STEP_0;
        }
        if (!(g_GameTimer & 0xF)) {
            g_Dop.padSim = PAD_UP;
        }
        break;
    case 16:
        if (!(g_Player.status & PLAYER_STATUS_DEAD)) {
            D_us_801D3D24 = 0;
        }
        g_Dop.padSim = PAD_UP;
        if (g_Dop.status & 1) {
            g_Dop.padSim = PAD_R1;
        }
        if (g_Dop.status & 2) {
            g_Dop.padSim = PAD_R2;
        }
        break;
    case 17:
        if (abs(DOPPLEGANGER.posY.i.hi - PLAYER.posY.i.hi) < 8) {
            D_us_801D3D24 = THINK_STEP_0;
        }
        break;
    case 18:
        if (DOPPLEGANGER.step == 1) {
            g_Dop.padSim |= PAD_TRIANGLE;
            D_us_801D3D24 = THINK_STEP_19;
            D_us_801D3D2C = 0x40;
        }
        break;
    case 19:                                        /* switch 1 */
        if (--D_us_801D3D2C == 0) {
            D_us_801D3D24 = THINK_STEP_0;
        }
        break;
    }
}

INCLUDE_ASM("boss/bo4/nonmatchings/doppleganger", func_us_801C37B4);

INCLUDE_ASM("boss/bo4/nonmatchings/doppleganger", func_us_801C38C0);

INCLUDE_ASM("boss/bo4/nonmatchings/doppleganger", func_us_801C3EEC);

INCLUDE_ASM("boss/bo4/nonmatchings/doppleganger", func_us_801C44C8);

INCLUDE_ASM("boss/bo4/nonmatchings/doppleganger", func_us_801C4710);
