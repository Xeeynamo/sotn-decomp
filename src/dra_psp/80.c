// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

void func_80102EB8(void) {
    Primitive *poly1, *poly2, *poly3;
    s32 i;

    D_80137E58 = AllocPrimitives(PRIM_GT4, 3);
    poly1 = &g_PrimBuf[D_80137E58];

    D_80137E5C = AllocPrimitives(PRIM_G4, 3);
    poly2 = &g_PrimBuf[D_80137E5C];

    D_80137E60 = AllocPrimitives(PRIM_LINE_G2, 12);
    poly3 = &g_PrimBuf[D_80137E60];

    for (i = 0; i < 3; i++) {
        SetTexturedPrimRect(poly1, 98, 79, 96, 0, 0, 0);
        func_801072DC(poly1);
        poly1->tpage = 0x10;
        poly1->clut = 0x1A1;
        poly1->priority = 0x1FF;
        poly1->drawMode = DRAW_HIDE;
        poly1->p1 = 0;
        SetPrimRect(poly2, 80, 79, 96, 0);
        func_801072DC(poly2);
        func_801071CC(poly2, 96, 0);
        func_801071CC(poly2, 96, 1);
        poly2->g0 = poly2->g1 = poly2->g2 = poly2->g3 = poly2->r0 = poly2->r1 =
            poly2->r2 = poly2->r3 = 0;
        poly2->tpage = 0x1F;
        poly2->priority = 0x1FF;
        poly2->drawMode = DRAW_HIDE;
        poly1 = poly1->next;
        poly2 = poly2->next;
    }

    for (i = 0; i < 12; i++) {
        func_80107250(poly3, 255);
        poly3->priority = 0x1FF;
        poly3->drawMode = DRAW_HIDE;
        poly3 = poly3->next;
    }
}

INCLUDE_ASM("dra_psp/psp/dra_psp/80", func_psp_090DCBC8);

INCLUDE_ASM("dra_psp/psp/dra_psp/80", func_psp_090DCC60);

INCLUDE_ASM("dra_psp/psp/dra_psp/80", HandleSaveMenu);

INCLUDE_ASM("dra_psp/psp/dra_psp/80", func_80103EAC);

s32 MemcardParse(s32 nPort, s32 nCard);
s32 MemcardDetectSave(s32 nPort, char* expectedSaveName, s32 block);
s32 GetMemcardFreeBlockCount(s32 nPort);
s32 MemcardClose(s32 nPort);
s32 MemcardWriteFile(s32 nPort, s32 nCard, char* name, void* data, s32 flags,
                     s32 create, s32 unk);
s32 func_800E9880(s32 nPort, s32 nCard);
void func_80103ED4(void) {
    char saveFile[32];
    s32 memCardClose;
    s32 i;
    s32 case1_state;

    switch (D_80137E4C) {
    case 0:
        MemcardInit();
        g_MemCardRetryCount = 4;
        D_80137E4C++;
        break;
    case 1:
        // This really should be doable as a switch, but that doesn't match.
        case1_state = func_800E9880(D_80097924, 0);
        if (case1_state == 0) {
            break;
        }
        if (case1_state == -1) {
            if (g_MemCardRetryCount-- == 0) {
                D_80137E4C = 7;
            }
        } else if (case1_state == -3) {
            if (g_MemCardRetryCount-- == 0) {
                D_80137E4C = 8;
            }
        } else if (case1_state == -2) {
            D_80137E4C = 9;
        } else {
            MemcardInit();
            D_80137E4C++;
        }
        break;
    case 2:
        if (MemcardParse(D_80097924, 0) >= 0) {
            g_MemCardRetryCount = 10;
            if (D_8006C378 >= 0) {
                i = 0;
                if (D_80137E54 == 2) {
                    for (i = 0; i < 15; i++) {
                        MakeMemcardPath(saveFile, i);
                        if (MemcardDetectSave(D_80097924, saveFile, 0) != 0) {
                            break;
                        }
                    }
                    if ((i == 15) &&
                        (GetMemcardFreeBlockCount(D_80097924) == 0)) {
                        D_80137E54 = 3;
                    }
                }
                D_80137E4C += 2;
                break;
            } else {
                D_80137E4C++;
                break;
            }
        }
        break;
    case 3:
        for (i = 0; i < 15; i++) {
            MakeMemcardPath(saveFile, i);
            if (MemcardDetectSave(D_80097924, saveFile, 0) == 0) {
                break;
            }
        }
        if (i == 15 || GetMemcardFreeBlockCount(D_80097924) == 0) {
            D_80137E4C = 10;
            break;
        }
        D_8006C378 = i;
        D_80137E4C++;
        break;
    case 4:
        MakeMemcardPath(saveFile, D_8006C378);
        // careful with i here, it's not an iterator.
        if (MemcardDetectSave(D_80097924, saveFile, 0) == 1) {
            i = 0;
        } else {
            i = 1;
            if (GetMemcardFreeBlockCount(D_80097924) == 0) {
                D_80137E4C = 10;
                break;
            }
        }
        // I believe the rand() call here selects the icon on the save
        // in the save-select screen.
        StoreSaveData(g_Pix, D_8006C378, rand() & 0xF);
        func_psp_090DFC68();
        if (MemcardWriteFile(D_80097924, 0, saveFile, g_Pix, 1, i, 1) != 0) {
            D_801379BC = 0x101;
            D_80137E54 = 0;
            D_80097924 = D_80137EF0;
            D_8006C378 = D_80137EF4;
            g_Player.padSim = 0;
            g_Player.demo_timer = 1;
            D_80137E4C = 6;
        } else {
            g_MemCardRetryCount = 10;
            D_80137E4C++;
            break;
        }
        break;
    case 5:
        memCardClose = MemcardClose(D_80097924);
        if (memCardClose == 0) {
            break;
        }
        if (memCardClose == -3) {
            if (g_MemCardRetryCount-- == 0) {
                D_80137E4C = 0;
                break;
            }
            D_80137E4C--;
            break;
        }
        D_80137E4C = 6;
        break;
    case 6:
        break;
    }
}

INCLUDE_ASM("dra_psp/psp/dra_psp/80", func_8010427C);

INCLUDE_ASM("dra_psp/psp/dra_psp/80", func_801042C4);

INCLUDE_ASM("dra_psp/psp/dra_psp/80", func_80104790);

extern SVECTOR* D_800A34C0[][3];

extern SVECTOR D_801379C8;
extern VECTOR D_801379D0;
extern MATRIX D_80137E00;
extern s32 D_80137E44;

static void func_80105078(s32 arg0, s32 arg1) {
    s32 interp;
    s32 otz;
    s32 unused_flag;
    VECTOR vec;
    SVECTOR rotVecs[3];
    SVECTOR unkSvectors[3];
    s32 i;
    s32 j;
    Primitive* prim;
    s32 nclip_result;

    RotMatrix(&D_801379C8, &D_80137E00);

    for (i = 0, prim = &g_PrimBuf[D_80137E44]; i < 18; i++, prim = prim->next) {
        if (arg0 == 0) {
            prim->drawMode = DRAW_HIDE;
            continue;
        }
        TransMatrix(&D_80137E00, &D_801379D0);
        SetRotMatrix(&D_80137E00);
        SetTransMatrix(&D_80137E00);
        otz = 0;
        for (j = 0; j < 3; j++) {
            vec.vx = rotVecs[j].vx = (D_800A34C0[i][j]->vx * arg0) >> 8;
            vec.vy = rotVecs[j].vy = (D_800A34C0[i][j]->vy * arg0) >> 8;
            vec.vz = rotVecs[j].vz = (D_800A34C0[i][j]->vz * arg0) >> 8;
            func_80017008(&vec, &unkSvectors[j]);
        }
        nclip_result = RotAverageNclip3(
            &rotVecs[0], &rotVecs[1], &rotVecs[2], (s32*)&prim->x0,
            (s32*)&prim->x1, (s32*)&prim->x2, &interp, &otz, &unused_flag);
        if (nclip_result < 0) {
            RotAverage3(
                &rotVecs[0], &rotVecs[2], &rotVecs[1], (s32*)&prim->x0,
                (s32*)&prim->x2, (s32*)&prim->x1, &interp, &unused_flag);
        }
        prim->type = PRIM_LINE_G2;
        if (otz < 0xF0) {
            if (nclip_result >= 0) {
                prim->priority = g_unkGraphicsStruct.g_zEntityCenter + 3;
            } else {
                prim->priority = g_unkGraphicsStruct.g_zEntityCenter - 3;
            }
            if (arg1 != 0) {
                if (arg1 & 0x80) {
                    PGREY(prim, 0) = PGREY(prim, 1) = arg1 & 0x7F;
                } else if (arg1 < 0x11) {
                    PGREY(prim, 0) = (u16)((0x10 - arg1) * 8);
                } else if (arg1 < 0x21) {
                    PGREY(prim, 1) = (u16)((0x20 - arg1) * 8);
                } else {
                    prim->drawMode = DRAW_HIDE;
                    continue;
                }
            }
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        }
    }
}

static void func_80105408(void) {
    g_Player.padSim = PAD_UP;
    g_Player.demo_timer = 1;
}

extern u32 D_psp_08B42050; // psp cross button
extern u32 D_psp_08B42054; // psp triangle button

void func_80105428(void) {
#define PAD_MASK (PAD_START | PAD_SQUARE)
    s32 temp_s0;
    s32 temp_result;
    s32 timer_temp;
    s32 temp_s3;

    SetGeomScreen(0x100);
    SetGeomOffset(0x80, D_801379B8 + 0x80);
    if (D_8003C730 != 0) {
        g_PauseAllowed = false;
        D_80137E4C = 6;
        D_80137EE4 = 0x100;
        D_801379BC = 7;
        D_8003C730 = 0;
    }
    if (D_80137E54 != 0) {
        func_80103ED4();
    }
    temp_s3 = D_801379C8.vy;
    switch (D_801379BC) {
    case 0x0:
        D_801379C8.vy = temp_s3 + 6;
        timer_temp = g_GameTimer & 0x7F;
        if (timer_temp == 0) {
            PlaySfx(SFX_SAVE_HEARTBEAT);
        }
        if (timer_temp & 0x40) {
            timer_temp = 0x7F - timer_temp;
        }
        if (timer_temp >= 8) {
            timer_temp = 0xC0;
        } else {
            timer_temp = (timer_temp * 4) + 0xA0;
        }
        D_80137E4C = 0;
        func_80104790(0, timer_temp, 0);
        D_80137EE4 = timer_temp;

        if (func_8010E334(0x60, 0xA0) != 0) {
            D_80137EF0 = D_80097924;
            D_80137EF4 = D_8006C378;
            g_PauseAllowed = false;
            if (D_80137EE0 == 0) {
                D_800978C4 = 0;
            }
            D_8013B5E8 = 0x10;
            // When a save point is activated, the player's HP and MP
            // are fully restored (regardless of whether they actually save)
            g_Status.hp = g_Status.hpMax;
            g_Status.mp = g_Status.mpMax;
            D_801379BC++;
        }
        break;
    case 0x1:
        D_801379C8.vy = temp_s3 + 7;
        if (D_80137EE4 < 0xC0) {
            D_80137EE4 += 4;
        }
        func_80104790(0, D_80137EE4, 0);
        if (D_801379B8 < ((g_StageId & STAGE_INVERTEDCASTLE_FLAG) / 2) + 8 &&
            (g_GameTimer != 0)) {
            D_801379B8++;
        }
        if (abs(PLAYER.posX.i.hi - 0x80) < 3) {
            PLAYER.posX.i.hi = 0x80;
        }
        if (PLAYER.posX.i.hi < 0x7F) {
            g_Player.padSim = PAD_RIGHT;
            g_Player.demo_timer = 1;
        } else if (PLAYER.posX.i.hi > 0x80) {
            g_Player.padSim = PAD_LEFT;
            g_Player.demo_timer = 1;
        } else if (
            D_801379B8 == ((g_StageId & STAGE_INVERTEDCASTLE_FLAG) / 2) + 8) {
            func_80105408();
            D_80137EE8 = 8;
            if (D_80137EE0 != 0) {
                D_801379BC++;
            } else {
                if (D_80097924 >= 0) {
                    func_80102EB8();
                    D_801379BC = 0x80;
                    if (D_8006C378 < 0) {
                        D_80137E54 = 1;
                        D_801379BC = 2;
                    }
                } else {
                    D_80097924 = 0;
                    func_80102EB8();
                    D_801379BC = 0x100;
                }
            }
        } else {
            func_80105408();
        }
        break;
    case 0x80:
        func_80105408();
        D_801379C8.vy += D_80137EE8;
        func_80104790(0, D_80137EE4, 0);
        if (HandleSaveMenu(3) != 0) {
            if (D_80137E6C == 0) {
                D_80137E54 = 2;
                D_801379BC = 2;
                D_80137E4C = 0;
            } else {
                func_80102EB8();
                D_801379BC++;
            }
        }
        break;
    case 0x81:
        func_80105408();
        D_801379C8.vy += D_80137EE8;
        func_80104790(0, D_80137EE4, 0);

        if (HandleSaveMenu(4) != 0) {
            if (D_80137E6C == 0) {
                D_80097924 = 0;
                func_80102EB8();
                D_801379BC = 0x100;
                D_80137E4C = 0;
            } else {
                D_80097924 = D_80137EF0;
                D_8006C378 = D_80137EF4;
                D_801379BC = 0x101;
            }
        }
        break;
    case 0x100:
        func_80105408();
        D_801379C8.vy += D_80137EE8;
        func_80104790(0, D_80137EE4, 0);
        temp_result = HandleSaveMenu(1);
        if (temp_result == 0) {
            break;
        }
        if (temp_result == 2) {
            D_801379BC++;
        } else {
            D_80137E54 = 1;
            D_801379BC = 2;
        }
        break;
    case 0x101:
        D_801379C8.vy = temp_s3 + (s16)D_80137EE8;
        func_80104790(0, D_80137EE4, 0);
        if (g_pads[0].pressed &
            ((D_psp_08B42050 | PAD_MASK) | D_psp_08B42054)) {
            D_80097924 = D_80137EF0;
            D_8006C378 = D_80137EF4;
            g_Player.padSim = 0;
            g_Player.demo_timer = 1;
        } else {
            g_PauseAllowed = true;
            D_800978C4 = 1;
            D_801379BC = 0;
        }
        break;
    case 0x2:
        func_80105408();
        D_801379C8.vy += D_80137EE8;
        D_80137EE4 += 4;
        if (D_80137EE4 > 0x100) {
            D_80137EE4 = 0x100;
        }
        func_80104790(0, D_80137EE4, 0);

        if (D_80137EE4 == 0x100) {
            if ((D_80137E4C >= 4) || (D_80137EE0 != 0)) {
                D_801379BC++;
            } else {
                if (++D_80137EE8 > 0x80) {
                    D_80137EE8 = 0x80;
                }
            }
        }
        break;
    case 0x3:
        func_80105408();
        D_801379C8.vy += D_80137EE8;
        if (++D_80137EE8 > 0x80) {
            D_80137EE8 = 0x80;
        }
        func_80104790(0, D_80137EE4, 0);

        if (D_80137EE8 == 0x80) {
            D_801379BC++;
            D_80137EEC = 0;
        }
        break;
    case 0x4:
        func_80105408();
        D_801379C8.vy += D_80137EE8;
        D_80137EEC += 2;
        if (D_80137EEC > 0x7F) {
            D_80137EEC = 0x7F;
        }
        func_80104790(0, D_80137EE4, D_80137EEC);
        if (D_80137EEC >= 0x10) {
            temp_s0 = (D_80137EEC - 0x10) * 0x10;
            if (temp_s0 > 0x100) {
                temp_s0 = 0x100;
            }
            func_80105078(temp_s0, 0);
        }

        if (D_80137EEC != 0x7F) {
            break;
        }
        if ((D_80137E4C >= 6) || (D_80137EE0 != 0)) {
            if ((D_801379C8.vy & 0xFFF) >= 0x100 &&
                (D_801379C8.vy & 0xFFF) < 0x180) {
                D_801379BC++;
            }
        }
        break;
    case 0x5:
        func_80105408();
        if (D_80137EE8 > 0x40) {
            D_80137EE8--;
        } else {
            if ((D_801379C8.vy & 0x7FF) >= 0x400) {
                D_80137EE8 = (0x800 - (D_801379C8.vy & 0x7FF)) / 16;
            }
        }
        if (D_80137EE8 < 0x10) {
            D_80137EE8 = 0x10;
        }
        D_801379C8.vy += D_80137EE8;
        D_80137EEC -= 2;
        if (D_80137EEC < 0) {
            D_80137EEC = 0;
        }
        func_80104790(1, D_80137EE4, D_80137EEC);
        if (D_80137EEC != 0) {
            func_80105078(D_80137EE4, 0);
        } else {
            func_80105078(0, 0);
        }

        if (D_80137EE8 == 0x10) {
            if ((D_801379C8.vy & 0x7FF) >= 0x7F0) {
                D_801379C8.vy = 0;
                func_80104790(1, D_80137EE4, 0);
                func_800EA5E4(0x4020U);
                if (D_80137EE0 != 0) {
                    D_801379BC++;
                } else {
                    func_80102EB8();
                    D_801379BC++;
                }
            }
        }
        break;
    case 0x6:
        func_80105408();
        if (D_80137EE0 != 0) {
            func_801027C4(5);
            D_801379BC = 0x300;

        } else if (D_80137E4C >= 6 && HandleSaveMenu(0) != 0) {
            if (D_80137E4C == 9) {
                func_80102EB8();
                D_801379BC = 0x200;
            } else {
                if (D_80137E4C != 6) {
                    D_80097924 = -1;
                    D_801379BC = 0x20;
                    D_80137EEC = 0x60;
                } else {
                    D_801379BC++;
                }
            }
        }
        break;
    case 0x7:
        func_80105408();
        func_80104790(1, D_80137EE4, 0);
        D_801379BC++;
        break;
    case 0x8:
        func_80105408();
        D_801379C8.vy += D_80137EE8;
        D_80137EE8 += 2;
        if (D_80137EE8 > 0x40) {
            D_80137EE8 = 0x40;
        }
        func_80104790(1, D_80137EE4, 0);

        if (D_80137EE8 == 0x40) {
            D_801379BC++;
            D_80137EEC = 0;
        }
        break;
    case 0x300:
        func_80105408();
        if (D_80137EE0 != 0) {
            if (func_801025F4() != 0) {
                D_801379BC++;
            }
        }
        break;
    case 0x301:
        if (D_80137EE0 != 0) {
            D_801379BC++;
        } else {
        case 0x302:
            func_80105408();
            D_80097C98 = 1;
        }
        break;
    case 0x303:
        func_80105408();
        break;
    case 0x9:
        D_801379C8.vy = temp_s3 + (s16)D_80137EE8;
        if (++D_80137EEC > 0x7F) {
            D_80137EEC = 0x7F;
        }
        func_80104790(2, D_80137EE4, D_80137EEC);
        if (D_80137EEC >= 0x40) {
            func_80105078(D_80137EE4, 0);
            g_PauseAllowed = true;
            D_800978C4 = 1;
        } else {
            func_80105078(D_80137EE4, (D_80137EEC * 2) + 0x80);
            func_80105408();
        }

        if (D_80137EEC == 0x7F) {
            D_801379BC++;
            D_80137EEC = 0;
        }
        break;
    case 0xA:
        D_801379C8.vy += D_80137EE8;
        if (++D_80137EEC > 0x22) {
            D_80137EEC = 0x22;
        }
        func_80105078(D_80137EE4, D_80137EEC);
        if (D_80137EE8 == 0) {
            D_801379BC++;
        }
        break;
    case 0xB:
        break;
    case 0xC:
        D_801379C8.vy = 0;
        D_80137EE4 = 0x180;
        func_80104790(1, 0x180, 0);
        D_80137EEC = 0;
        D_801379BC++;
        break;
    case 0xD:
        D_801379C8.vy = temp_s3 + 9;
        func_80104790(3, D_80137EE4, D_80137EEC);

        if (++D_80137EEC == 0x60) {
            D_801379BC++;
        }
        break;
    case 0xE:
        D_801379C8.vy = temp_s3 + 9;
        func_80104790(3, D_80137EE4, D_80137EEC);

        if (--D_80137EEC == 0) {
            D_801379BC -= 1;
        }
        break;
    case 0x20:
    case 0x30:
        if (D_801379BC == 0x30) {
            func_80105408();
        }
        if (D_80137EEC > 0x30) {
            func_80105408();
        }
        D_801379C8.vy += 6;
        if (D_80137EE4 > 0xC0) {
            D_80137EE4 -= 2;
        }
        func_80104790(3, D_80137EE4, D_80137EEC);
        D_80137EEC -= 2;
        if (g_Player.demo_timer == 0) {
            if (g_pads[0].pressed &
                (PAD_MASK | D_psp_08B42050 | D_psp_08B42054)) {
                g_Player.padSim = 0;
                g_Player.demo_timer = 1;
                if (D_80137EEC <= 0) {
                    D_80137EEC = 0;
                }
                break;
            }
        }

        if (D_80137EEC <= 0) {
            if (D_801379BC == 0x30) {
                D_80137E54 = 0;
                func_80103EAC();
                D_801379BC = 1;
            } else {
                D_80097924 = D_80137EF0;
                D_8006C378 = D_80137EF4;
                D_80137E54 = 0;
                func_80103EAC();
                D_801379BC = 0;
                g_PauseAllowed = true;
                D_800978C4 = 1;
            }
        }
        break;
    default:
        func_80104790(1, D_80137EE4, 0);
    }
    if (((((s16)temp_s3 + 0x400) ^ ((s16)D_801379C8.vy + 0x400)) & 0x800) &&
        (D_801379BC >= 3 && D_801379BC < 10)) {
        PlaySfx(SFX_SAVE_COFFIN_SWISH);
    }
}
