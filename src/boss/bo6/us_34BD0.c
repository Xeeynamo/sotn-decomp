// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo6.h"

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B4BD0);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B4EAC);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B4FA4);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B502C);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B50BC);

extern s32 D_us_801CF3C8; // Richter Think Step
extern s32 D_us_801CF3CC; // Richter Think Step_s
void func_us_801B5A14(s32 step) {
    D_us_801CF3C8 = step;
    D_us_801CF3CC = 0;
}

typedef enum { THINK_STEP_INIT } ThinkStep;

// RIC base = 0x800762D8
extern s32 D_us_80181278;
extern s32 D_us_801CF3C8; // Richter Think Step
extern s32 D_us_801CF3CC; // Richter Think Step_s
extern s32 D_us_801CF3D0;
extern s32 D_us_801CF3D8;
extern s32 D_us_801CF3E0;
extern s32 D_us_801CF3E4;
extern s32 D_us_801D11C4;

extern s32 D_us_801D169C; // padSim + 0xB0
static void func_us_801B5A14(s32 step);

// not matching on PSP
void RichterThinking(void) {
    s32 globalPosX;
    s32 playerDistanceX;
    bool facingLeft;

    if (D_us_801CF3D8) {
        D_us_801CF3D8--;
    }

    globalPosX = g_Tilemap.scrollX.i.hi + RIC.posX.i.hi;
    g_Ric.demo_timer = 2;
    g_Ric.padSim = 0;

    facingLeft = false;
    if ((RIC.posX.i.hi - PLAYER.posX.i.hi) >= 0) {
        facingLeft = true;
    }

    playerDistanceX = abs(RIC.posX.i.hi - PLAYER.posX.i.hi);

    if (D_us_801CF3E4 < g_Ric.unk6C && D_us_801CF3E4 >= g_Ric.unk6A) {
        D_us_801CF3C8 = 0x1E;
    }

    if (D_us_801D169C != 0) {
        func_us_801B5A14(0x28);
    }

    if (g_Player.status & PLAYER_STATUS_DEAD) {
        D_us_801CF3C8 = 0x32;
    }

    if (D_us_801CF3C8 < 0x12) {
        if (g_Ric.status & PLAYER_STATUS_UNK10000) {
            func_us_801B5A14(0);
        } else if (g_Player.timers[ALU_T_12] && D_us_801CF3C8 != 0xE) {
            func_us_801B5A14(0xE);
        }
    }

    FntPrint("think_step:%02x\n", D_us_801CF3C8);

    switch (D_us_801CF3C8) { /* switch 1 */
    // following item crash at start of fight
    case THINK_STEP_INIT: /* switch 1 */
        if (!(g_Ric.status & PLAYER_STATUS_UNK10000)) {
            if (g_Player.timers[ALU_T_10]) {
                if (rand() & 1) {
                    func_us_801B5A14(7);
                } else {
                    func_us_801B5A14(5);
                }
            } else if (abs(RIC.posY.i.hi - PLAYER.posY.i.hi) > 0x20) {
                func_us_801B5A14(7);
            } else {
                if (playerDistanceX > 0x58) {
                    if (facingLeft) {
                        g_Ric.padSim = 0x8000;
                    } else {
                        g_Ric.padSim = 0x2000;
                    }
                } else {
                    func_us_801B5A14(1);
                }
            }
        }
        break;
    // decicing on attack?
    case 1: /* switch 1 */
        if (RIC.facingLeft != facingLeft) {
            if (facingLeft) {
                g_Ric.padSim = 0x8000;
            } else {
                g_Ric.padSim = 0x2000;
            }
        }

        if (D_us_801CF3CC == 0) {
            D_us_801CF3D0 = 8;
            D_us_801CF3CC = 1;
            return;
        }

        if (playerDistanceX > 0x58) {
            func_us_801B5A14(0);
        } else {
            if (((globalPosX < 0x10) && (RIC.facingLeft == 0)) ||
                ((globalPosX > 0xF0) && (RIC.facingLeft))) {
                func_us_801B5A14(4);
                if (D_us_801CF3E0 != 0) {
                    func_us_801B5A14(0xD);
                    return;
                }
            } else if (g_Player.status & PLAYER_STATUS_CROUCH) {
                if (rand() & 1) {
                    func_us_801B5A14(6);
                } else {
                    func_us_801B5A14(5);
                }
            } else {
                if (g_Player.timers[ALU_T_9]) {
                    switch (rand() & 7) { /* switch 2 */
                    case 0:               /* switch 2 */
                    case 6:               /* switch 2 */
                        func_us_801B5A14(6);
                        break;
                    case 7: /* switch 2 */
                        func_us_801B5A14(7);
                        break;
                    case 1: /* switch 2 */
                        func_us_801B5A14(5);
                        break;
                    case 2: /* switch 2 */
                    case 3: /* switch 2 */
                    case 4: /* switch 2 */
                    case 5: /* switch 2 */
                    default:
                        func_us_801B5A14(2);
                        break;
                    }
                } else {
                    if (g_Player.timers[ALU_T_10]) {
                        if (rand() & 1) {
                            func_us_801B5A14(7);
                        } else {
                            func_us_801B5A14(5);
                        }
                    } else if (D_us_801CF3D0) {
                        D_us_801CF3D0--;
                    } else if (playerDistanceX < 0x40) {
                        if ((RIC.posY.i.hi - PLAYER.posY.i.hi) < 0x18) {
                            func_us_801B5A14(3);
                        } else {
                            func_us_801B5A14(8);
                        }
                    } else {
                        func_us_801B5A14(8);
                    }
                }
            }
        }
        break;
    case 2:                      /* switch 1 */
        switch (D_us_801CF3CC) { /* switch 3; irregular */
        case 0:                  /* switch 3 */
            if (RIC.step == 5) {
                D_us_801CF3CC = 1;
            } else if (g_Timer & 1) {
                g_Ric.padSim = 0x40;
            }
            break;
        case 1: /* switch 3 */
            if (g_Ric.unk44 & 8) {
                D_us_801CF3CC = 2;
            } else {
                if (g_Timer & 1) {
                    g_Ric.padSim = 0x40;
                }
                if (g_Ric.vram_flag & 1) {
                    func_us_801B5A14(0);
                }
            }
            break;
        case 2:
        default: /* switch 3 */
            if (D_us_801CF3E0 == 0) {
                func_us_801B5A14(9);
            }
            if (g_Ric.vram_flag & 1) {
                if (D_us_801CF3E0 != 0) {
                    func_us_801B5A14(0xC);
                } else {
                    func_us_801B5A14(0);
                }
            }
            break;
        }
        break;
    // whip attack
    case 3: /* switch 1 */
        if (D_us_801CF3CC == 0) {
            if (!g_Ric.unk46) {
                if (g_Timer & 1) {
                    g_Ric.padSim = 0x80;
                }
                D_us_801CF3CC = 1;
            }
        } else {
            if (!g_Ric.unk46) {
                func_us_801B5A14(0);
            }
        }
        break;
    // dash
    case 4: /* switch 1 */
        if (D_us_801CF3CC == 0) {
            if (g_Timer & 1) {
                g_Ric.padSim = PAD_R1;
            }
            if (RIC.step == 0x19) {
                D_us_801CF3C8 = 1;
            }
        } else if (RIC.step != 0x19) {
            func_us_801B5A14(0);
        }
        break;
    case 5: /* switch 1 */
        g_Ric.padSim = 0x4000;
        switch (D_us_801CF3CC) {
        case 0:
            if (RIC.facingLeft != facingLeft) {
                if (facingLeft) {
                    g_Ric.padSim |= 0x8000;
                } else {
                    g_Ric.padSim |= 0x2000;
                }
            }
            if (RIC.step == 3) {
                D_us_801CF3CC = 1;
                D_us_801CF3D0 = 8;
            }
            break;
        case 1:
        default:
            if (!--D_us_801CF3D0) {
                func_us_801B5A14(17);
            } else if (playerDistanceX < 0x40) {
                func_us_801B5A14(10);
            }
            break;
        }
        break;
    case 6: /* switch 1 */
        if (D_us_801CF3CC == 0) {
            if (RIC.step == 5) {
                D_us_801CF3CC = 1;
            } else if (g_Timer & 1) {
                g_Ric.padSim = 0x40;
            }
        } else if (g_Ric.vram_flag & 1) {
            func_us_801B5A14(0);
        } else if (RIC.velocityY > 0x4000) {
            func_us_801B5A14(9);
        }
        break;
    case 7: /* switch 1 */
        if (RIC.facingLeft) {
            g_Ric.padSim = PAD_LEFT;
        } else {
            g_Ric.padSim = PAD_RIGHT;
        }
        if (D_us_801CF3CC == 0) {
            if (RIC.step == 5) {
                D_us_801CF3CC = 1;
            } else if (g_Timer & 1) {
                g_Ric.padSim |= PAD_CROSS;
            }
        } else if (g_Ric.vram_flag & 1) {
            func_us_801B5A14(0);
        } else if (RIC.velocityY > 0x4000) {
            if (rand() & 1) {
                func_us_801B5A14(0xB);
            } else {
                func_us_801B5A14(9);
            }
        }
        break;
    // subweapon attack?
    case 8: /* switch 1 */
        if (D_us_801CF3CC == 0) {
            if (!g_Ric.unk46) {
                if (g_Timer & 1) {
                    g_Ric.padSim = PAD_UP | PAD_SQUARE;
                }
                D_us_801CF3CC = 1;
            }
        } else if (!g_Ric.unk46) {
            func_us_801B5A14(0);
        }
        break;
    case 9: /* switch 1 */
        if (g_Ric.vram_flag & 1) {
            func_us_801B5A14(0);
        } else if (D_us_801CF3CC == 0) {
            if (!g_Ric.unk46) {
                if (g_Timer & 1) {
                    g_Ric.padSim = PAD_UP | PAD_SQUARE;
                }
                D_us_801CF3CC = 1;
            }
        } else if (!g_Ric.unk46) {
            func_us_801B5A14(0);
        }
        break;
    case 10: /* switch 1 */
        g_Ric.padSim = PAD_DOWN;
        if (D_us_801CF3CC == 0) {
            if (!g_Ric.unk46) {
                if (g_Timer & 1) {
                    g_Ric.padSim |= PAD_SQUARE;
                }
                D_us_801CF3CC = 1;
            }
        } else if (!g_Ric.unk46) {
            func_us_801B5A14(0);
        }
        break;
    case 11: /* switch 1 */
        if (g_Ric.vram_flag & 1) {
            func_us_801B5A14(0);
        } else if (D_us_801CF3CC == 0) {
            if (!g_Ric.unk46) {
                if (g_Timer & 1) {
                    g_Ric.padSim = 0x80;
                }
                D_us_801CF3CC = 1;
            }
        } else if (!g_Ric.unk46) {
            func_us_801B5A14(0);
        }
        break;
    case 12: /* switch 1 */
        if (D_us_801CF3CC == 0) {
            if (RIC.step == 0x1C) {
                D_us_801CF3CC = 1;
            } else if (g_Timer & 1) {
                g_Ric.padSim = 0x110;
            }
        } else if (RIC.step != 0x1C) {
            func_us_801B5A14(0x11);
            return;
        }
        break;
    case 13: /* switch 1 */
        // STEP: cutscene
        if (D_us_801CF3CC == 0) {
            if (RIC.step == 0x1C) {
                D_us_801CF3CC = 1;
            } else if (g_Timer & 1) {
                g_Ric.padSim = 0x810;
            }
        } else if (RIC.step != 0x1C) {
            func_us_801B5A14(0);
        }
        break;

    case 14: /* switch 1 */
        if (D_us_801CF3CC == 0) {
            if (RIC.step == 0x13) {
                D_us_801CF3CC = 1;
            } else if (g_Timer & 1) {
                g_Ric.padSim = 0x14;
            }
        } else if (RIC.step != 0x13) {
            func_us_801B5A14(0);
        }
        break;

    case 15: /* switch 1 */
        if (D_us_801CF3CC == 0) {
            if (RIC.step == 0x15) {
                D_us_801CF3CC = 1;
            } else if (g_Timer & 1) {
                g_Ric.padSim = 0x11;
            }
        } else if (RIC.step != 0x15) {
            func_us_801B5A14(0);
        }
        break;
    case 16: /* switch 1 */
        if (D_us_801CF3CC == 0) {
            if (RIC.step == 0x13) {
                D_us_801CF3CC = 1;
            } else if (g_Timer & 1) {
                g_Ric.padSim = 0x10;
            }
        } else if (RIC.step != 0x13) {
            func_us_801B5A14(0);
        }
        break;
    case 17:                     /* switch 1 */
        switch (D_us_801CF3CC) { /* switch 4; irregular */
        case 0:                  /* switch 4 */
            g_Ric.padSim = 0x4000;
            if (RIC.step == 3) {
                D_us_801CF3CC = 1;
            }
            break;
        case 1: /* switch 4 */
            if (RIC.step == 0x18) {
                D_us_801CF3CC = 4;
                if (D_us_801CF3E0 != 0) {
                    if (RIC.facingLeft && RIC.posX.i.hi > 0x80) {
                        D_us_801CF3CC = 2;
                    }
                    if (!RIC.facingLeft && RIC.posX.i.hi < 0x80) {
                        D_us_801CF3CC = 2;
                    }
                }
            } else {
                g_Ric.padSim = 0x4000;
                if (g_Timer & 1) {
                    g_Ric.padSim |= PAD_CROSS;
                }
            }
            break;
        case 2: /* switch 4 */
            if (RIC.step == 0x1B) {
                D_us_801CF3CC = 3;
            } else {
                g_Ric.padSim = 0x4000;
                if (g_Timer & 1) {
                    g_Ric.padSim |= 0x40;
                }
            }
            break;
        case 3: /* switch 4 */
            g_Ric.padSim = 0x80;
            if (RIC.step != 0x1B) {
                func_us_801B5A14(0);
            }
            // fallthrough

        default:
            func_us_801B5A14(0);
            break;
        }
        break;
    case 18: /* switch 1 */
        func_us_801B9AF4(1, 4);
        if (RIC.step == 1) {
            func_us_801B5A14(0x13);
        }
        break;

    case 19: /* switch 1 */
        func_us_801B9AF4(1, 4);
        if (D_us_801CF3CC == 0) {
            D_us_801CF3D0 = 0x40;
            D_us_801CF3CC = 1;
        } else {
            if ((D_us_801D11C4 & 2) || (g_CastleFlags[SHAFT_ORB_DEFEATED]) ||
                (g_DemoMode != Demo_None)) {
                if (!--D_us_801CF3D0) {
                    OVL_EXPORT(RicCreateEntFactoryFromEntity)
                    (g_CurrentEntity, 0x48, 0);
                    func_us_801B5A14(0x10);
                }
            }
        }
        break;
    case 30: /* switch 1 */
        g_Player.timers[ALU_T_INVINCIBLE_CONSUMABLES] = 3;
        func_us_801B9AF4(1, 8);
        g_Ric.padSim = 0x1000;
        if (RIC.step == 1 && RIC.step_s == 1) {
            RIC.step = 0x50;
            RIC.step_s = 0;
            D_us_801CF3C8 = 0x1F;
        }
        break;
    case 31: /* switch 1 */
        g_Player.timers[ALU_T_INVINCIBLE_CONSUMABLES] = 3;
        func_us_801B9AF4(1, 8);
        if (RIC.step != 0x50) {
            D_us_801CF3E0 = 1;
            func_us_801B5A14(0x20);
        }
        break;
    case 32: /* switch 1 */
        g_Player.timers[ALU_T_INVINCIBLE_CONSUMABLES] = 3;
        func_us_801B9AF4(1, 8);
        if (D_us_801CF3CC == 0) {
            D_us_801CF3D0 = 0x10;
            D_us_801CF3CC = 1;
        } else {
            if (D_us_801CF3D0 != 0) {
                D_us_801CF3D0--;
            }
            func_us_801B5A14(0xF);
        }
        break;

    case 40: /* switch 1 */
        g_Player.timers[ALU_T_INVINCIBLE_CONSUMABLES] = 3;
        D_us_80181278 = 0x32;
        D_us_801CF3C8++;
        break;

    case 41: /* switch 1 */
        g_Player.timers[ALU_T_INVINCIBLE_CONSUMABLES] = 3;
        break;

    case 50: /* switch 1 */
        if (!(g_Player.status & PLAYER_STATUS_DEAD)) {
            func_us_801B5A14(0);
        }
        g_Ric.padSim = 0x1000;
        break;
    }
}

extern s32 D_us_801D11C0;

void func_us_801B6998(void) {
    switch (D_us_80181278) {
    case 0:
        break;
    case 10:
        if ((g_CastleFlags[SHAFT_ORB_DEFEATED] == 0) && (g_DemoMode == Demo_None)) {
            g_unkGraphicsStruct.pauseEnemies = true;
            D_us_801D11C0 = 0;
        }
        D_us_80181278++;
        break;
    case 11:
        if (++D_us_801D11C0 >1) {
            if ((g_CastleFlags[SHAFT_ORB_DEFEATED] == 0) && (g_DemoMode == Demo_None)) {
                g_unkGraphicsStruct.unk20 = 0xFF;
            }
            D_us_80181278++;
        }
        break;
    case 20:
        if (D_us_801D11C4 & 4) {
            D_us_80181278 = 0x1E;
        }
        break;
    case 40:
        D_us_801D11C4 |= 8;
        break;
    case 50:
    default:
        break;
    }
}


extern EInit D_us_80180400; //
extern s32 D_us_801CF3E0;
extern s32 D_us_801CF3E4;

void EntityRichter(Entity* self) {
    Entity* entity;
    s32 i;

    g_Ric.unk6A = RIC.hitPoints;
    if (self->step == 0) {
        InitializeEntity(D_us_80180400);
        func_us_801B4BD0();
        entity = &g_Entities[STAGE_ENTITY_START + 4];
        for (i = STAGE_ENTITY_START + 4; i < 144; i++, entity++) {
            DestroyEntity(entity);
        }
        g_Ric.unk6E = g_Ric.unk6A = g_Ric.unk6C = RIC.hitPoints;
        D_us_801CF3E4 = g_Ric.unk6E / 2;
        D_us_801CF3E0 = 0;
        g_Ric.unk70 = RIC.hitboxState;
        func_us_801B5A14(18);
        func_us_801B9B78(1, 48);
    } else {
        RichterThinking();
        func_us_801B50BC(); // equivalent to EntityDoppleganger{10,40}
        func_us_801BBBD0();
        func_us_801B6998();
    }
    g_Ric.unk6C = g_Ric.unk6A;
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B6BD8);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B6E3C);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B6EA8);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B6F88);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B7444);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B74DC);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B779C);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B77D8);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B7818);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B7E80);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B8540);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B85DC);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B8684);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B86B8);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B86EC);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B87B4);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B8A88);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B8D50);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B8E80);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B8F78);
