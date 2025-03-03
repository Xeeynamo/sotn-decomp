// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"
#include "dra_bss.h"
#include "objects.h"
#include "sfx.h"

void MemCardSetPort(s32 nPort) {
    g_MemCardRStep = 0;
    g_MemCardRStepSub = nPort;
}

s32 MemCardInitAndFormat(void) {
    u32 nPort = g_MemCardRStepSub;
    s32 state = g_MemCardRStep;

    switch (state) {
    case 0:
        MemcardInit();
        g_MemCardRetryCount = 4;
        g_MemCardRStep++;
        break;

    case 1:
        if (MemcardFormat(nPort, 0) != 1) {
            if (--g_MemCardRetryCount == -1) {
                return -1;
            }
        } else {
            return 1;
        }
        break;
    }

    return 0;
}

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
        poly1->priority = g_unkGraphicsStruct.g_zEntityCenter + 32;
        poly1->drawMode = DRAW_HIDE;
        poly1->p1 = 0;
        SetPrimRect(poly2, 80, 79, 96, 0);
        func_801072DC(poly2);
        func_801071CC(poly2, 96, 0);
        func_801071CC(poly2, 96, 1);
        poly2->g0 = poly2->g1 = poly2->g2 = poly2->g3 = poly2->r0 = poly2->r1 =
            poly2->r2 = poly2->r3 = 0;
        poly2->tpage = 0x1F;
        poly2->priority = g_unkGraphicsStruct.g_zEntityCenter + 31;
        poly2->drawMode = DRAW_HIDE;
        poly1 = poly1->next;
        poly2 = poly2->next;
    }

    for (i = 0; i < 12; i++) {
        func_80107250(poly3, 255);
        poly3->priority = g_unkGraphicsStruct.g_zEntityCenter + 32;
        poly3->drawMode = DRAW_HIDE;
        poly3 = poly3->next;
    }
}

void func_801030B4(s32 arg0, POLY_GT4* poly, s32 arg2) {
    s32 var_v1;

    if (arg2 == arg0) {
        if (g_Timer & 0x20) {
            var_v1 = (g_Timer & 0x1F) + 0x60;
        } else {
            var_v1 = 0x7F - (g_Timer & 0x1F);
        }

        poly->r0 = poly->r1 = var_v1 - 16;
        poly->r2 = poly->r3 = var_v1 + 16;
        poly->b0 = poly->b1 = poly->b2 = poly->b3 = 0;
        poly->pad3 = 0x404;
    } else {
        poly->b1 = 96;
        poly->b0 = 96;
        poly->b3 = 128;
        poly->b2 = 128;
        poly->r0 = poly->r1 = poly->r2 = poly->r3 = 0;
        poly->pad3 = 0x415;
    }
}

POLY_GT4* func_80103148(POLY_GT4* poly1, POLY_GT4* arg1) {
    poly1->x0 = arg1->x0 - 1;
    poly1->y0 = arg1->y0 - 1;
    poly1->x1 = arg1->x1;
    poly1->y1 = arg1->y0 - 1;
    poly1->pad3 = 0;
    poly1 = (POLY_GT4*)poly1->tag;

    poly1->x0 = arg1->x0 - 1;
    poly1->y0 = arg1->y0 - 1;
    poly1->x1 = arg1->x0 - 1;
    poly1->y1 = arg1->y2;
    poly1->pad3 = 0;
    poly1 = (POLY_GT4*)poly1->tag;

    poly1->x0 = arg1->x0 - 1;
    poly1->y0 = arg1->y2;
    poly1->x1 = arg1->x1;
    poly1->y1 = arg1->y2;
    poly1->pad3 = 0;
    poly1 = (POLY_GT4*)poly1->tag;

    poly1->x0 = arg1->x1;
    poly1->y0 = arg1->y0 - 1;
    poly1->x1 = arg1->x1;
    poly1->y1 = arg1->y2;
    poly1->pad3 = 0;
    return (POLY_GT4*)poly1->tag;
}

s32 HandleSaveMenu(s32 arg0) {
// For some reason, US and HD have different controls for confirm and exit,
// so we handle that with a couple of constants.
#if defined(VERSION_US)
    const s32 CONFIRM = PAD_CROSS;
    const s32 EXIT = PAD_TRIANGLE;
#elif defined(VERSION_HD)
    const s32 CONFIRM = (PAD_START | PAD_SQUARE | PAD_CIRCLE);
    const s32 EXIT = PAD_CROSS;
#endif
    Primitive* prim1;
    Primitive* prim2;
    Primitive* prim3;
    u8 temp_t0;
    s32 temp_a1;

    prim2 = &g_PrimBuf[D_80137E58];
    temp_t0 = prim2->p1;
    prim1 = &g_PrimBuf[D_80137E5C];
    prim3 = &g_PrimBuf[D_80137E60];
    if (arg0 == 0) {
        if (temp_t0 == 0) {
            prim2->drawMode = DRAW_DEFAULT;
            prim1->drawMode = DRAW_UNK_400 | DRAW_COLORS;
            if (D_80137E4C == 6) {
                PlaySfx(SFX_START_SLAM_B);
            } else {
                PlaySfx(SFX_UI_ALERT_TINK);
            }
            if (D_80137E4C == 6) {
#if defined(VERSION_US)
                func_800F9D88("Data saved．", 0, 1);
#elif defined(VERSION_HD)
                func_800F9D40("セーブしました　　　", 0, 1);
#endif
                prim2->p1 += 2;
            }
            if (D_80137E4C == 7) {
#if defined(VERSION_US)
                func_800F9D88("Memory Card", 0, 1);
                func_800F9D88("  not found．", 1, 0);
#elif defined(VERSION_HD)
                func_800F9D40("メモリーカードが　　", 0, 1);
                func_800F9D40("ささっていません　　", 1, 0);
#endif
                prim2->p1 += 2;
            }
            if (D_80137E4C == 8) {
#if defined(VERSION_US)
                func_800F9D88("Memory Card", 0, 1);
                func_800F9D88("is Defective．", 1, 0);
#elif defined(VERSION_HD)
                func_800F9D40("メモリーカードが　　", 0, 1);
                func_800F9D40("　壊れています　　　", 1, 0);
#endif
                prim2->p1 += 2;
            }
            if (D_80137E4C == 9) {
#if defined(VERSION_US)
                func_800F9D88("Memory Card is", 0, 1);
                func_800F9D88("not formatted．", 1, 0);
#elif defined(VERSION_HD)
                func_800F9D40("　メモリーカードが　", 0, 1);
                func_800F9D40("初期化されていません", 1, 0);
#endif
                prim2->p1 += 2;
            }
            if (D_80137E4C == 10) {
                if (D_80137E54 == 2) {
#if defined(VERSION_US)
                    func_800F9D88("Cannot", 0, 1);
                    func_800F9D88("overwrite file．", 1, 0);
#elif defined(VERSION_HD)
                    func_800F9D40("　　上書き　　　　　", 0, 1);
                    func_800F9D40("　できません　　　　", 1, 0);
#endif
                } else if (D_80137E54 == 3) {
#if defined(VERSION_US)
                    func_800F9D88("No game", 0, 1);
                    func_800F9D88("data found．", 1, 0);
#elif defined(VERSION_HD)
                    func_800F9D40("データがないため　　", 0, 1);
                    func_800F9D40("上書きできません　　", 1, 0);
#endif
                } else {
#if defined(VERSION_US)
                    func_800F9D88("   ０ memory", 0, 1);
                    func_800F9D88("blocks available．", 1, 0);
#elif defined(VERSION_HD)
                    func_800F9D40("空きブロックが　　　", 0, 1);
                    func_800F9D40("　足りません　　　　", 1, 0);
#endif
                }
                prim2->p1 += 2;
            }
            if (D_80137E4C == 11) {
#if defined(VERSION_US)
                func_800F9D88("  Memory card", 0, 1);
                func_800F9D88("  format error．", 1, 0);
#elif defined(VERSION_HD)
                func_800F9D40("　メモリーカードの　", 0, 1);
                func_800F9D40("初期化に失敗しました　", 1, 0);
#endif
                prim2->p1 += 2;
            }
        } else {
            if ((D_80137E4C == 7 || D_80137E4C == 8) && (temp_t0 < 33)) {
                SetTexturedPrimRect(prim2, 80, 96 - temp_t0, 96, temp_t0, 0, 0);
                prim2->p1 += 2;
                SetPrimRect(prim1, 72, 96 - temp_t0, 112, temp_t0);
                func_80103148(prim3, prim1);
            } else if (
                (D_80137E4C == 9 || D_80137E4C == 11) && (temp_t0 < 33)) {
                SetTexturedPrimRect(
                    prim2, 68, 96 - temp_t0, 120, temp_t0, 0, 0);
                prim2->p1 += 2;
                SetPrimRect(prim1, 60, 96 - temp_t0, 136, temp_t0);
                func_80103148(prim3, prim1);
            } else if (D_80137E4C == 10 && temp_t0 < 33) {
#if defined(VERSION_US)
                // silly logic here. if 2 or 3, it's 0, otherwise it's -10
                temp_a1 = (-(!(D_80137E54 == 2 || D_80137E54 == 3))) & -10;
                SetTexturedPrimRect(
                    prim2, temp_a1 + 80, 96 - temp_t0, 112, temp_t0, 0, 0);
                prim2->p1 += 2;
                if (D_80137E54 == 2 || D_80137E54 == 3) {
                    SetPrimRect(prim1, 72, 96 - temp_t0, 112, temp_t0);
                } else {
                    SetPrimRect(prim1, 68, 96 - temp_t0, 120, temp_t0);
                }
#elif defined(VERSION_HD)
                temp_a1 = (-(!(D_80137E54 ^ 3))) & -6;
                SetTexturedPrimRect(
                    prim2, temp_a1 + 86, 96 - temp_t0, 96, temp_t0, 0, 0);
                prim2->p1 += 2;
                SetPrimRect(prim1, 72, 96 - temp_t0, 112, temp_t0);
#endif
                func_80103148(prim3, prim1);
            } else if (temp_t0 < 17) {
                SetTexturedPrimRect(prim2, 86, 80 - temp_t0, 96, temp_t0, 0, 0);
                prim2->p1 += 2;
                SetPrimRect(prim1, 80, 80 - temp_t0, 96, temp_t0);
                func_80103148(prim3, prim1);
            } else {
                func_80103148(prim3, prim1);
                if (D_80137E4C == 6) {
                    prim2->p1 += 2;
                }
                if ((prim2->p1 >= 224) || (g_pads[0].tapped & CONFIRM)) {
                    FreePrimitives(D_80137E58);
                    FreePrimitives(D_80137E5C);
                    FreePrimitives(D_80137E60);
                    return 1;
                }
            }
        }
        // Seems this one shouldn't be needed since the else's would send it to
        // the end anyway?
        return 0;
    } else if (arg0 == 1) {
        if (temp_t0 == 0) {
            PlaySfx(SFX_UI_ALERT_TINK);
            prim2->p1 += 2;
#if defined(VERSION_US)
            func_800F9D88("  Select the slot．", 0, 1);
            func_800F9D88(" Slot １", 1, 0);
            func_800F9D88(" Slot ２", 2, 0);
#elif defined(VERSION_HD)
            func_800F9D40("スロットを選んで下さい　", 0, 1);
            func_800F9D40("スロット１　", 1, 0);
            func_800F9D40("スロット２　", 2, 0);
#endif
            SetTexturedPrimRect(prim2, 56, 79, 144, 0, 0, 0);
            prim2->drawMode = DRAW_DEFAULT;
            prim1->drawMode = DRAW_UNK_400 | DRAW_COLORS;
            prim2 = prim2->next;
            prim1 = prim1->next;
            prim2->drawMode = DRAW_DEFAULT;
            func_801030B4(0, prim1, D_80097924);
            prim2 = prim2->next;
            prim1 = prim1->next;
            prim2->drawMode = DRAW_DEFAULT;
            func_801030B4(1, prim1, D_80097924);
        } else if (temp_t0 < 17) {
            prim2->p1 += 2;
            SetTexturedPrimRect(prim2, 62, 80 - temp_t0, 144, temp_t0, 0, 0);
            SetPrimRect(prim1, 56, 80 - temp_t0, 144, temp_t0);
            prim3 = func_80103148(prim3, prim1);
            prim2 = prim2->next;
            prim1 = prim1->next;
            SetTexturedPrimRect(prim2, 54, 104 - temp_t0, 64, temp_t0, 0, 16);
            SetPrimRect(prim1, 52, 104 - temp_t0, 64, temp_t0);
            func_801030B4(0, prim1, D_80097924);
            prim3 = func_80103148(prim3, prim1);
            prim2 = prim2->next;
            prim1 = prim1->next;
            SetTexturedPrimRect(prim2, 142, 104 - temp_t0, 64, temp_t0, 0, 32);
            SetPrimRect(prim1, 140, 104 - temp_t0, 64, temp_t0);
            func_801030B4(1, prim1, D_80097924);
            func_80103148(prim3, prim1);
        } else {
            if (g_pads[0].tapped & PAD_LEFT) {
                if (D_80097924 != 0) {
                    PlaySfx(SFX_UI_TINK);
                }
                D_80097924 = 0;
            }
            if (g_pads[0].tapped & PAD_RIGHT) {
                if (D_80097924 == 0) {
                    PlaySfx(SFX_UI_TINK);
                }
                D_80097924 = 1;
            }
            prim3 = func_80103148(prim3, prim1);
            prim1 = prim1->next;
            func_801030B4(0, prim1, D_80097924);
            prim3 = func_80103148(prim3, prim1);
            prim1 = prim1->next;
            func_801030B4(1, prim1, D_80097924);
            func_80103148(prim3, prim1);
            if (g_pads[0].tapped & EXIT) {
                FreePrimitives(D_80137E58);
                FreePrimitives(D_80137E5C);
                FreePrimitives(D_80137E60);
                D_80097924 = -1;
                return 2;
            }
            if (g_pads[0].tapped & CONFIRM) {
                PlaySfx(SFX_UI_CONFIRM);
                FreePrimitives(D_80137E58);
                FreePrimitives(D_80137E5C);
                FreePrimitives(D_80137E60);
                D_8006C378 = -1;
                return 1;
            }
        }
    } else {
        if (temp_t0 == 0) {
            PlaySfx(SFX_UI_ALERT_TINK);
            prim2->p1 += 2;
            if (arg0 == 2) {
#if defined(VERSION_US)
                func_800F9D88(" Wish to format？", 0, 1);
#elif defined(VERSION_HD)
                func_800F9D40("初期化してもいいですか　", 0, 1);
#endif
                D_80137E6C = 1;
            }
            if (arg0 == 3) {
#if defined(VERSION_US)
                func_800F9D88(" Overwrite data？", 0, 1);
#elif defined(VERSION_HD)
                func_800F9D40("　　上書きしますか　　　", 0, 1);
#endif
                D_80137E6C = 0;
            }
            if (arg0 == 4) {
#if defined(VERSION_US)
                func_800F9D88("   Wish to save？", 0, 1);
#elif defined(VERSION_HD)
                func_800F9D40("　　セーブしますか　　　", 0, 1);
#endif
                D_80137E6C = 0;
            }
#if defined(VERSION_US)
            func_800F9D88("Yes ", 1, 0);
            func_800F9D88("  No  ", 2, 0);
#elif defined(VERSION_HD)
            func_800F9D40("はい　　", 1, 0);
            func_800F9D40("いいえ　", 2, 0);

#endif

            SetTexturedPrimRect(prim2, 56, 79, 144, 0, 0, 0);
            prim2->drawMode = DRAW_DEFAULT;
            prim1->drawMode = DRAW_UNK_400 | DRAW_COLORS;
            prim2 = prim2->next;
            prim1 = prim1->next;
            prim2->drawMode = DRAW_DEFAULT;
            func_801030B4(0, prim1, D_80137E6C);
            prim2 = prim2->next;
            prim1 = prim1->next;
            prim2->drawMode = DRAW_DEFAULT;
            func_801030B4(1, prim1, D_80137E6C);
        } else if (temp_t0 < 17) {
            prim2->p1 += 2;
            SetTexturedPrimRect(prim2, 62, 80 - temp_t0, 144, temp_t0, 0, 0);
            SetPrimRect(prim1, 56, 80 - temp_t0, 144, temp_t0);
            prim3 = func_80103148(prim3, prim1);
            prim2 = prim2->next;
            prim1 = prim1->next;
            SetTexturedPrimRect(prim2, 72, 104 - temp_t0, 24, temp_t0, 0, 16);
            SetPrimRect(prim1, 60, 104 - temp_t0, 48, temp_t0);
            func_801030B4(0, prim1, D_80137E6C);
            prim3 = func_80103148(prim3, prim1);
            prim2 = prim2->next;
            prim1 = prim1->next;
            SetTexturedPrimRect(prim2, 154, 104 - temp_t0, 36, temp_t0, 0, 32);
            SetPrimRect(prim1, 148, 104 - temp_t0, 48, temp_t0);
            func_801030B4(1, prim1, D_80137E6C);
            func_80103148(prim3, prim1);
        } else {
            if (g_pads[0].tapped & PAD_LEFT) {
                if (D_80137E6C != 0) {
                    PlaySfx(SFX_UI_TINK);
                }
                D_80137E6C = 0;
            }
            if (g_pads[0].tapped & PAD_RIGHT) {
                if (D_80137E6C == 0) {
                    PlaySfx(SFX_UI_TINK);
                }
                D_80137E6C = 1;
            }
            prim3 = func_80103148(prim3, prim1);
            prim1 = prim1->next;
            func_801030B4(0, prim1, D_80137E6C);
            prim3 = func_80103148(prim3, prim1);
            prim1 = prim1->next;

            func_801030B4(1, prim1, D_80137E6C);
            func_80103148(prim3, prim1);
            if (g_pads[0].tapped & EXIT) {
                D_80137E6C = 1;
                FreePrimitives(D_80137E58);
                FreePrimitives(D_80137E5C);
                FreePrimitives(D_80137E60);
                return 1;
            } else if (g_pads[0].tapped & CONFIRM) {
                PlaySfx(SFX_UI_CONFIRM);
                FreePrimitives(D_80137E58);
                FreePrimitives(D_80137E5C);
                FreePrimitives(D_80137E60);
                return 1;
            }
        }
    }
    return 0;
}

void func_80103EAC(void) {
    D_80137E4C = 0;
    MemcardInfoInit();
}
