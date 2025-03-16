// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

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
    g_Player.D_80072EFC = 1;
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
            g_Player.D_80072EFC = 1;
        } else if (PLAYER.posX.i.hi > 0x80) {
            g_Player.padSim = PAD_LEFT;
            g_Player.D_80072EFC = 1;
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
            g_Player.D_80072EFC = 1;
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
        if (g_Player.D_80072EFC == 0) {
            if (g_pads[0].pressed &
                (PAD_MASK | D_psp_08B42050 | D_psp_08B42054)) {
                g_Player.padSim = 0;
                g_Player.D_80072EFC = 1;
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

INCLUDE_ASM("dra_psp/psp/dra_psp/1E50", func_psp_090DFBD0);

INCLUDE_ASM("dra_psp/psp/dra_psp/1E50", func_psp_090DFC68);

INCLUDE_ASM("dra_psp/psp/dra_psp/1E50", func_psp_090DFC80);

void func_800EA538(s32 arg0) {
    u16 v1;
    s32 i, j;
    u16 unk8;

    v1 = (0x8000 >> (arg0 - 1));
    if (arg0) {
        for (i = 0; i < LEN(D_8006C3C4); i++) {
            unk8 = D_8006C3C4[i].unk8;
            if (unk8 & v1) {
                D_8006C3C4[i].unk8 = 0;
            }
        }
    } else {
        D_8003C0EC[3] = 0;
        for (j = 0; j < LEN(D_8006C3C4); j++) {
            D_8006C3C4[j].unk8 = 0;
        }
    }
}

void func_800EA5AC(u16 arg0, u8 arg1, u8 arg2, u8 arg3) {
    D_8003C0EC[3] = arg0;
    D_8003C0EC[0] = arg1;
    D_8003C0EC[1] = arg2;
    D_8003C0EC[2] = arg3;
}
