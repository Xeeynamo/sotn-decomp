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

static void func_801030B4(bool arg0, Primitive* prim, bool arg2) {
    s32 var_v1;

    if (arg2 == arg0) {
        if (g_Timer & 0x20) {
            var_v1 = (g_Timer & 0x1F) + 0x60;
        } else {
            var_v1 = 0x7F - (g_Timer & 0x1F);
        }

        prim->r0 = prim->r1 = var_v1 - 16;
        prim->r2 = prim->r3 = var_v1 + 16;
        PBLU(prim) = 0;
        prim->drawMode = DRAW_UNK_400 | DRAW_COLORS;
    } else {
        prim->b0 = prim->b1 = 96;
        prim->b2 = prim->b3 = 128;
        PRED(prim) = 0;
        prim->drawMode = DRAW_UNK_400 | DRAW_COLORS | DRAW_TPAGE | DRAW_TRANSP;
    }
}

static Primitive* func_80103148(Primitive* prim, Primitive* basis) {
    prim->x0 = basis->x0 - 1;
    prim->y0 = basis->y0 - 1;
    prim->x1 = basis->x1;
    prim->y1 = basis->y0 - 1;
    prim->drawMode = DRAW_DEFAULT;
    prim = prim->next;

    prim->x0 = basis->x0 - 1;
    prim->y0 = basis->y0 - 1;
    prim->x1 = basis->x0 - 1;
    prim->y1 = basis->y2;
    prim->drawMode = DRAW_DEFAULT;
    prim = prim->next;

    prim->x0 = basis->x0 - 1;
    prim->y0 = basis->y2;
    prim->x1 = basis->x1;
    prim->y1 = basis->y2;
    prim->drawMode = DRAW_DEFAULT;
    prim = prim->next;

    prim->x0 = basis->x1;
    prim->y0 = basis->y0 - 1;
    prim->x1 = basis->x1;
    prim->y1 = basis->y2;
    prim->drawMode = DRAW_DEFAULT;
    prim = prim->next;
    
    return prim;
}

INCLUDE_ASM("dra_psp/psp/dra_psp/80", HandleSaveMenu);

void func_80103EAC(void) {
    D_80137E4C = 0;
    MemcardInfoInit();
}

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

void func_8010427C(void) {
    FreePrimitives(D_80137E40);
    FreePrimitives(D_80137E44);
    FreePrimitives(D_80137E48);
}

SVECTOR D_800A31B0 = {34, -18, -11};
SVECTOR D_800A31B8 = {21, 18, -29};
SVECTOR D_800A31C0 = {0, -18, -36};
SVECTOR D_800A31C8 = {0, -40, 0};
SVECTOR D_800A31D0 = {21, -18, 29};
SVECTOR D_800A31D8 = {34, 18, 11};
SVECTOR D_800A31E0 = {0, 40, 0};
SVECTOR D_800A31E8 = {0, 18, 36};
SVECTOR D_800A31F0 = {-34, -18, -11};
SVECTOR D_800A31F8 = {-21, 18, -29};
SVECTOR D_800A3200 = {-21, -18, 29};
SVECTOR D_800A3208 = {-34, 18, 11};

SVECTOR* D_800A3210[][3] = {
    {&D_800A31C8, &D_800A31B0, &D_800A31C0},
    {&D_800A31C8, &D_800A31C0, &D_800A31F0},
    {&D_800A31F0, &D_800A31C0, &D_800A31F8},
    {&D_800A31C8, &D_800A31F0, &D_800A3200},
    {&D_800A31D0, &D_800A31B0, &D_800A31C8},
    {&D_800A31C0, &D_800A31B0, &D_800A31B8},
    {&D_800A31D0, &D_800A31D8, &D_800A31B0},
    {&D_800A31F0, &D_800A3208, &D_800A3200},
    {&D_800A31B0, &D_800A31D8, &D_800A31B8},
    {&D_800A31D0, &D_800A31C8, &D_800A3200},
    {&D_800A31F8, &D_800A31C0, &D_800A31B8},
    {&D_800A31F0, &D_800A31F8, &D_800A3208},
    {&D_800A3208, &D_800A31F8, &D_800A31E0},
    {&D_800A31E8, &D_800A31D8, &D_800A31D0},
    {&D_800A3208, &D_800A31E8, &D_800A3200},
    {&D_800A31D8, &D_800A31E0, &D_800A31B8},
    {&D_800A31E8, &D_800A31D0, &D_800A3200},
    {&D_800A31E0, &D_800A31F8, &D_800A31B8},
    {&D_800A31E8, &D_800A31E0, &D_800A31D8},
    {&D_800A3208, &D_800A31E0, &D_800A31E8},
    {&D_800A31E8, &D_800A31E8, &D_800A3200},
    {&D_800A31E0, &D_800A31E0, &D_800A31B8},
    {&D_800A31E8, &D_800A31E0, &D_800A31E8},
    {&D_800A31E8, &D_800A31E0, &D_800A31E0},
};

SVECTOR D_800A3330 = {-15, -46, 10};
SVECTOR D_800A3338 = {-25, -21, -10};
SVECTOR D_800A3340 = {-25, -21, 10};
SVECTOR D_800A3348 = {-12, 50, -10};
SVECTOR D_800A3350 = {-12, 50, 10};
SVECTOR D_800A3358 = {0, -9, -10};
SVECTOR D_800A3360 = {-15, -46, -10};
SVECTOR D_800A3368 = {15, -46, -10};
SVECTOR D_800A3370 = {12, 50, -10};
SVECTOR D_800A3378 = {25, -21, 10};
SVECTOR D_800A3380 = {15, -46, 10};
SVECTOR D_800A3388 = {25, -21, -10};
SVECTOR D_800A3390 = {12, 50, 10};
SVECTOR D_800A3398 = {0, -9, 10};

SVECTOR* D_800A33A0[][3] = {
    {&D_800A3380, &D_800A3368, &D_800A3360},
    {&D_800A3380, &D_800A3360, &D_800A3330},
    {&D_800A3330, &D_800A3360, &D_800A3338},
    {&D_800A3380, &D_800A3330, &D_800A3398},
    {&D_800A3378, &D_800A3368, &D_800A3380},
    {&D_800A3360, &D_800A3368, &D_800A3358},
    {&D_800A3378, &D_800A3388, &D_800A3368},
    {&D_800A3330, &D_800A3340, &D_800A3398},
    {&D_800A3368, &D_800A3388, &D_800A3358},
    {&D_800A3378, &D_800A3380, &D_800A3398},
    {&D_800A3338, &D_800A3360, &D_800A3358},
    {&D_800A3330, &D_800A3338, &D_800A3340},
    {&D_800A3340, &D_800A3338, &D_800A3348},
    {&D_800A3390, &D_800A3388, &D_800A3378},
    {&D_800A3340, &D_800A3350, &D_800A3398},
    {&D_800A3388, &D_800A3370, &D_800A3358},
    {&D_800A3390, &D_800A3378, &D_800A3398},
    {&D_800A3348, &D_800A3338, &D_800A3358},
    {&D_800A3390, &D_800A3370, &D_800A3388},
    {&D_800A3340, &D_800A3348, &D_800A3350},
    {&D_800A3350, &D_800A3390, &D_800A3398},
    {&D_800A3370, &D_800A3348, &D_800A3358},
    {&D_800A3350, &D_800A3370, &D_800A3390},
    {&D_800A3350, &D_800A3348, &D_800A3370},
};

SVECTOR* D_800A34C0[][3] = {
    {&D_800A3330, &D_800A3340, &D_800A3398},
    {&D_800A3340, &D_800A3350, &D_800A3398},
    {&D_800A3350, &D_800A3390, &D_800A3398},
    {&D_800A3390, &D_800A3378, &D_800A3398},
    {&D_800A3378, &D_800A3380, &D_800A3398},
    {&D_800A3380, &D_800A3330, &D_800A3398},
    {&D_800A3338, &D_800A3360, &D_800A3358},
    {&D_800A3360, &D_800A3368, &D_800A3358},
    {&D_800A3368, &D_800A3388, &D_800A3358},
    {&D_800A3388, &D_800A3370, &D_800A3358},
    {&D_800A3370, &D_800A3348, &D_800A3358},
    {&D_800A3348, &D_800A3338, &D_800A3358},
    {&D_800A3330, &D_800A3360, &D_800A3338},
    {&D_800A3340, &D_800A3338, &D_800A3348},
    {&D_800A3350, &D_800A3348, &D_800A3370},
    {&D_800A3390, &D_800A3370, &D_800A3388},
    {&D_800A3378, &D_800A3388, &D_800A3368},
    {&D_800A3380, &D_800A3368, &D_800A3360},
};

SVECTOR* D_800A3598[] = {
    &D_800A31F0, &D_800A31F8, &D_800A3208, &D_800A31E0, &D_800A31E8,
    &D_800A31B8, &D_800A31C0, &D_800A31B0, &D_800A31E0, &D_800A31D0,
    &D_800A31C8, &D_800A31D8, &D_800A31E8, &D_800A3200,
};

SVECTOR* D_800A35D0[] = {
    &D_800A3330, &D_800A3338, &D_800A3340, &D_800A3348, &D_800A3350,
    &D_800A3358, &D_800A3360, &D_800A3368, &D_800A3370, &D_800A3378,
    &D_800A3380, &D_800A3388, &D_800A3390, &D_800A3398,
};

SVECTOR* D_800A3608[][3] = {
    {&D_80137E70[10], &D_80137E70[7],  &D_80137E70[6]},  
    {&D_80137E70[10], &D_80137E70[6],  &D_80137E70[0]},  
    {&D_80137E70[0],  &D_80137E70[6],  &D_80137E70[1]},  
    {&D_80137E70[10], &D_80137E70[0],  &D_80137E70[13]},
    {&D_80137E70[9],  &D_80137E70[7],  &D_80137E70[10]}, 
    {&D_80137E70[6],  &D_80137E70[7],  &D_80137E70[5]},
    {&D_80137E70[9],  &D_80137E70[11], &D_80137E70[7]},  
    {&D_80137E70[0],  &D_80137E70[2],  &D_80137E70[13]},
    {&D_80137E70[7],  &D_80137E70[11], &D_80137E70[5]},  
    {&D_80137E70[9], &D_80137E70[10], &D_80137E70[13]}, 
    {&D_80137E70[1],  &D_80137E70[6], &D_80137E70[5]},  
    {&D_80137E70[0],  &D_80137E70[1],  &D_80137E70[2]},
    {&D_80137E70[2],  &D_80137E70[1],  &D_80137E70[3]},  
    {&D_80137E70[12], &D_80137E70[11], &D_80137E70[9]},  
    {&D_80137E70[2],  &D_80137E70[4], &D_80137E70[13]}, 
    {&D_80137E70[11], &D_80137E70[8],  &D_80137E70[5]},
    {&D_80137E70[12], &D_80137E70[9],  &D_80137E70[13]}, 
    {&D_80137E70[3], &D_80137E70[1],  &D_80137E70[5]},  
    {&D_80137E70[12], &D_80137E70[8], &D_80137E70[11]}, 
    {&D_80137E70[2],  &D_80137E70[3],  &D_80137E70[4]},
    {&D_80137E70[4],  &D_80137E70[12], &D_80137E70[13]}, 
    {&D_80137E70[8], &D_80137E70[3],  &D_80137E70[5]},  
    {&D_80137E70[4],  &D_80137E70[8], &D_80137E70[12]}, 
    {&D_80137E70[4],  &D_80137E70[3],  &D_80137E70[8]}
};
u8 D_800A3728[] = {
    0x01, 0x7E, 0x3E, 0x68, 0x01, 0x68, 0x01, 0x7E, 0x3E, 0x68, 0x3E, 0x7F,
    0x01, 0x7E, 0x3E, 0x68, 0x01, 0x68, 0x71, 0x71, 0x7E, 0x7E, 0x71, 0x7E,
    0x01, 0x7E, 0x3E, 0x68, 0x3E, 0x7F, 0x0C, 0x03, 0x2A, 0x03, 0x1B, 0x2A,
    0x01, 0x7E, 0x3E, 0x68, 0x01, 0x68, 0x71, 0x71, 0x7E, 0x7E, 0x71, 0x7E,
    0x2A, 0x03, 0x36, 0x1E, 0x1B, 0x2A, 0x71, 0x71, 0x7E, 0x7E, 0x71, 0x7E,
    0x01, 0x1E, 0x0C, 0x03, 0x1B, 0x2A, 0x01, 0x7E, 0x3E, 0x68, 0x3E, 0x7F,
    0x01, 0x7E, 0x3E, 0x68, 0x01, 0x68, 0x01, 0x7E, 0x3E, 0x68, 0x3E, 0x7F,
    0x71, 0x71, 0x7E, 0x7E, 0x71, 0x7E, 0x36, 0x1E, 0x27, 0x65, 0x1B, 0x2A,
    0x71, 0x71, 0x7E, 0x7E, 0x71, 0x7E, 0x0F, 0x65, 0x01, 0x1E, 0x1B, 0x2A,
    0x01, 0x7E, 0x3E, 0x68, 0x01, 0x68, 0x01, 0x7E, 0x3E, 0x68, 0x3E, 0x7F,
    0x71, 0x71, 0x7E, 0x7E, 0x71, 0x7E, 0x27, 0x65, 0x0F, 0x65, 0x1B, 0x2A,
    0x01, 0x7E, 0x3E, 0x68, 0x3E, 0x7F, 0x01, 0x7E, 0x3E, 0x68, 0x01, 0x68,
};

void func_801042C4(s32 arg0) {
    VECTOR sp10;
    Primitive* prim;
    s32 i;
    const int PrimCount = 4;

    D_80137EE0 = arg0;
    D_80097C98 = 0;
    func_800EA5E4(0x18);
    if (arg0 == 1) {
        func_800EA5E4(0x19);
        func_800EA5E4(0x401E);
    }
    D_801379BC = 0;
    D_80137E54 = 0;
    PlaySfx(SET_STOP_MUSIC);
    D_80097928 = 1;
    func_80103EAC();
    D_801379B8 = ((s32)(g_StageId & STAGE_INVERTEDCASTLE_FLAG) / 2) + 8;
    D_801379C8.vx = D_801379C8.vy = D_801379C8.vz = 0;

    D_801379D0.vx = D_801379D0.vy = 0;
    D_801379D0.vz = 0x100;
    D_80137E48 = AllocPrimitives(PRIM_TILE, PrimCount);
    
    for (i = 0, prim = &g_PrimBuf[D_80137E48]; i < PrimCount; prim = prim->next, i++) {
        prim->x0 = (i & 1) << 7;
        prim->y0 = (i / 2) * 0xD8;
        prim->u0 = 0x80;
        prim->v0 = 0x20;

        if ((i < 2 && !(g_StageId & 0x20)) || (i >= 2 && g_StageId & 0x20)) {
            prim->r0 = prim->g0 = 0x10;
            prim->b0 = 8;
        }

        prim->priority = 0x1EB;
        prim->drawMode = DRAW_DEFAULT;
    }

    for (i = 0; i < LEN(D_80137B20); i++) {
        D_80137B20[i].vx = (D_80137B20[i].vy = (D_80137B20[i].vz = 0));
        sp10.vx = (*(&D_800A33A0[i][0]))->vx + (*(&D_800A33A0[i][1]))->vx +
                  (*(&D_800A33A0[i][2]))->vx;
        sp10.vy = (*(&D_800A33A0[i][0]))->vy + (*(&D_800A33A0[i][1]))->vy +
                  (*(&D_800A33A0[i][2]))->vy;
        sp10.vz = (*(&D_800A33A0[i][0]))->vz + (*(&D_800A33A0[i][1]))->vz +
                  (*(&D_800A33A0[i][2]))->vz;

        func_80017008(&sp10, &D_80137D40[i]);
    }

    for (i = 0; i < LEN(D_801379E0); i++) {
        D_801379E0[i].vx = (D_801379E0[i].vy = (D_801379E0[i].vz = 0));
        sp10.vx = (*(&D_800A3210[i][0]))->vx + (*(&D_800A3210[i][1]))->vx +
                  (*(&D_800A3210[i][2]))->vx;
        sp10.vy = (*(&D_800A3210[i][0]))->vy + (*(&D_800A3210[i][1]))->vy +
                  (*(&D_800A3210[i][2]))->vy;
        sp10.vz = (*(&D_800A3210[i][0]))->vz + (*(&D_800A3210[i][1]))->vz +
                  (*(&D_800A3210[i][2]))->vz;
        func_80017008(&sp10, &D_80137CA0[i]);
    }

    SetGeomScreen(0x100);
    D_80137E40 = AllocPrimitives(5U, 0x18);
    for(prim = &g_PrimBuf[D_80137E40];prim != NULL; prim = prim->next){
        prim->u0 = 0xDB;
        prim->v0 = 0xA8;
        prim->u1 = 0xBC;
        prim->v1 = 0xDE;
        prim->u2 = 0xFA;
        prim->v2 = 0xDE;
        prim->tpage = 0x1B;
        prim->clut = arg0 + 0x1F1;
        prim->drawMode = DRAW_HIDE;
    }
    D_80137E44 = AllocPrimitives(2U, 0x12);
    for(prim = &g_PrimBuf[D_80137E44];prim != NULL; prim = prim->next){
        prim->r0 = 0xFF;
        prim->g0 = 0xFF;
        prim->b0 = 0xFF;
        prim->r1 = 0xFF;
        prim->g1 = 0xFF;
        prim->b1 = 0xFF;
        prim->drawMode = DRAW_HIDE;
    }
}

void func_80104790(s32 arg0, s32 arg1, s32 arg2) {
    #define PRIORITY_SHIFT 8
    s32 unused_interp;
    s32 nclip_otz;
    s32 unused_flag;
    VECTOR sp94;
    SVECTOR sp7c[3];
    SVECTOR sp64[3];
    s32 unhiddenCount;
    SVECTOR* vecSrc;
    SVECTOR** vecTriplet;
    u8* uvPtr;
    s32 i;
    s32 j;
    VECTOR* vecScaledShifted;
    Primitive* prim;
    s32 Nclip3_result;
    s32 XZ_scale;
    s32 Y_scale;
    s32 xShift;
    s32 yShift;
    s32 zShift;

    if(g_pads[1].tapped & PAD_TRIANGLE){
        D_801379C8.vz += 0x40;
    }

    if(g_pads[1].tapped & PAD_CROSS){
        D_801379C8.vz -= 0x40;
    }

    FntPrint("vz=0x%08x\n", D_801379C8.vz);

    if(g_pads[1].tapped & PAD_SQUARE){
        D_801379C8.vy += 0x40;
    }

    if(g_pads[1].tapped & PAD_CIRCLE){
        D_801379C8.vy -= 0x40;
    }

    FntPrint("vy=0x%08x\n", D_801379C8.vy);
    
    if(g_pads[1].tapped & PAD_R2){
        D_801379C8.vx += 0x40;
    }

    if(g_pads[1].tapped & PAD_L2){
        D_801379C8.vx -= 0x40;
    }

    FntPrint("vx=0x%08x\n", D_801379C8.vx);

    RotMatrix(&D_801379C8, &D_80137E00); // types copied
    prim = &g_PrimBuf[D_80137E40];

    switch (arg0) {
    case 0:
        vecTriplet = &D_800A3210[0][0];
        vecScaledShifted = &D_801379E0[0];
        vecSrc = &D_80137CA0[0];
        unhiddenCount = 0x14;
        break;
    case 1:
    case 2:
        vecTriplet = &D_800A33A0[0][0];
        vecScaledShifted = &D_80137B20[0];
        vecSrc = &D_80137D40[0];
        unhiddenCount = 0x18;
        break;
    case 3:
        vecTriplet = &D_800A3608[0][0];
        vecScaledShifted = &D_80137B20[0];
        vecSrc = &D_80137D40[0];
        unhiddenCount = 0x18;
        for (i = 0; i < LEN(D_800A3598); i++) {
            D_80137E70[i].vx =
                D_800A3598[i]->vx +
                (((D_800A35D0[i]->vx - D_800A3598[i]->vx) * arg2) / 96);
            D_80137E70[i].vy =
                D_800A3598[i]->vy +
                (((D_800A35D0[i]->vy - D_800A3598[i]->vy) * arg2) / 96);
            D_80137E70[i].vz =
                D_800A3598[i]->vz +
                (((D_800A35D0[i]->vz - D_800A3598[i]->vz) * arg2) / 96);
            D_80137E70[i].pad = 0;
        }
    }

    uvPtr = &D_800A3728[0];
    for (i = 0; i < LEN(D_800A3210); i++, prim = prim->next, vecTriplet += 3) {
        if (i >= unhiddenCount) {
            prim->drawMode = DRAW_HIDE;
            continue;
        }
        TransMatrix(&D_80137E00, &D_801379D0); // types copied
        SetRotMatrix(&D_80137E00);             // types copied
        SetTransMatrix(&D_80137E00);           // types copied
        XZ_scale = arg2;
        Y_scale = arg2;
        xShift = 0;
        yShift = 0;
        zShift = 0;
        nclip_otz = 0;
        if (arg0 == 2) {
            zShift = (i * 4);
            zShift -= 0x5C;
            zShift += arg2;
            if (zShift < 0) {
                zShift = 0;
            }
            if (zShift > 0x7F) {
                zShift = 0x7F;
            }
            zShift <<= 0xC;
            xShift = zShift;
            yShift = -zShift * 4;
            if (vecSrc[i].vx < 0) {
                xShift = -xShift;
            }
            if (vecSrc[i].vz < 0) {
                zShift = -zShift;
            }
            XZ_scale = 0;
            Y_scale = 0;
        }
        if (arg0 == 3) {
            XZ_scale = 0;
            Y_scale = 0;
        }
        vecScaledShifted[i].vx = ((vecSrc[i].vx * XZ_scale) + xShift);
        vecScaledShifted[i].vy = ((vecSrc[i].vy * Y_scale) + yShift);
        vecScaledShifted[i].vz = ((vecSrc[i].vz * XZ_scale) + zShift);
        for (j = 0; j < 3; j++) {
            sp94.vx = sp7c[j].vx = ((vecTriplet[j]->vx * arg1) >> 8) + (vecScaledShifted[i].vx >> 0xC);
            sp94.vy = sp7c[j].vy = ((vecTriplet[j]->vy * arg1) >> 8) + (vecScaledShifted[i].vy >> 0xC);
            sp94.vz = sp7c[j].vz = ((vecTriplet[j]->vz * arg1) >> 8) + (vecScaledShifted[i].vz >> 0xC);
            func_80017008(&sp94, &sp64[j]);
        }
        Nclip3_result = RotAverageNclip3(&sp7c[0], &sp7c[1], &sp7c[2], (s32*)&prim->x0, (s32*)&prim->x1, (s32*)&prim->x2, &unused_interp, &nclip_otz, &unused_flag);
        if (Nclip3_result < 0) {
            RotAverageNclip3(&sp7c[0], &sp7c[2], &sp7c[1], (s32*)&prim->x0, (s32*)&prim->x2, (s32*)&prim->x1, &unused_interp, &nclip_otz, &unused_flag);
        }
        PGREY(prim,3) = PGREY(prim,2) = PGREY(prim,1) = PGREY(prim,0) = 0xB0;
        prim->type = PRIM_GT3;
        if (nclip_otz >= 0xF0) {
            continue;
        }
        if (Nclip3_result >= 0) {
            prim->priority = g_unkGraphicsStruct.g_zEntityCenter + 4;
        } else {
            prim->priority = g_unkGraphicsStruct.g_zEntityCenter - 4;
        }
        prim->drawMode = DRAW_COLORS;
        if (((D_80137E4C == 6) || (D_80137EE0 != 0)) &&
            ((arg0 == 1) || (arg0 == 2) || ((arg0 == 3) && (arg2 >= 0x40)))) {
            prim->clut = (D_80137EE0 * 2) + 0x1F0;
            prim->u0 = *uvPtr++ + 0x80;
            prim->v0 = *uvPtr++ + 0x80;
            prim->u1 = *uvPtr++ + 0x80;
            prim->v1 = *uvPtr++ + 0x80;
            prim->u2 = *uvPtr++ + 0x80;
            prim->v2 = *uvPtr++ + 0x80;
            if (Nclip3_result < 0) {
                prim->u0 = 0xD1;
                prim->v0 = 0xF1;
                prim->u1 = 0xDE;
                prim->v1 = 0xFE;
                prim->u2 = 0xD1;
                prim->v2 = 0xFE;
            }
        } else {
            prim->clut = D_80137EE0 + 0x1F1;
            prim->u0 = 0xDB;
            prim->v0 = 0xA8;
            prim->u1 = 0xBC;
            prim->v1 = 0xDE;
            prim->u2 = 0xFA;
            prim->v2 = 0xDE;
        }

        if ((arg0 == 0) && (arg2 < 0x10)) {
            prim->priority -= PRIORITY_SHIFT;
        }
        if (arg0 == 3) {
            if (arg2 < 0x30) {
                prim->priority -= PRIORITY_SHIFT;
            }
        } 
        if (arg0 == 3){
            prim->drawMode = DRAW_COLORS;
        } else if ((arg0 != 2) && (arg2 >= 0x40)) {
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            prim->r0 = ((prim->r0 * (0x7F - arg2)) >> 6);
            prim->g0 = ((prim->g0 * (0x7F - arg2)) >> 6);
            prim->b0 = ((prim->b0 * (0x7F - arg2)) >> 6);
            prim->r1 = ((prim->r1 * (0x7F - arg2)) >> 6);
            prim->g1 = ((prim->g1 * (0x7F - arg2)) >> 6);
            prim->b1 = ((prim->b1 * (0x7F - arg2)) >> 6);
            prim->r2 = ((prim->r2 * (0x7F - arg2)) >> 6);
            prim->g2 = ((prim->g2 * (0x7F - arg2)) >> 6);
            prim->b2 = ((prim->b2 * (0x7F - arg2)) >> 6);
            
        }
    }
}

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
