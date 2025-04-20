// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"
#include "dra_bss.h"

void func_80102EB8(void) {
    Primitive *prim1, *prim2, *prim3;
    s32 i;

    D_80137E58 = AllocPrimitives(PRIM_GT4, 3);
    prim1 = &g_PrimBuf[D_80137E58];

    D_80137E5C = AllocPrimitives(PRIM_G4, 3);
    prim2 = &g_PrimBuf[D_80137E5C];

    D_80137E60 = AllocPrimitives(PRIM_LINE_G2, 12);
    prim3 = &g_PrimBuf[D_80137E60];

    for (i = 0; i < 3; i++) {
        SetTexturedPrimRect(prim1, 98, 79, 96, 0, 0, 0);
        func_801072DC(prim1);
        prim1->tpage = 0x10;
        prim1->clut = 0x1A1;
#ifdef VERSION_PSP
        prim1->priority = 0x1FF;
#else
        prim1->priority = g_unkGraphicsStruct.g_zEntityCenter + 32;
#endif
        prim1->drawMode = DRAW_HIDE;
        prim1->p1 = 0;
        SetPrimRect(prim2, 80, 79, 96, 0);
        func_801072DC(prim2);
        func_801071CC(prim2, 96, 0);
        func_801071CC(prim2, 96, 1);
        PRED(prim2) = 0;
        PGRN(prim2) = 0;
        prim2->tpage = 0x1F;
#ifdef VERSION_PSP
        prim2->priority = 0x1FF;
#else
        prim2->priority = g_unkGraphicsStruct.g_zEntityCenter + 31;
#endif
        prim2->drawMode = DRAW_HIDE;
        prim1 = prim1->next;
        prim2 = prim2->next;
    }

    for (i = 0; i < 12; i++) {
        func_80107250(prim3, 255);
#ifdef VERSION_PSP
        prim3->priority = 0x1FF;
#else
        prim3->priority = g_unkGraphicsStruct.g_zEntityCenter + 32;
#endif
        prim3->drawMode = DRAW_HIDE;
        prim3 = prim3->next;
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

#ifdef VERSION_PSP
extern s32* D_psp_091CE248;
extern s32* D_psp_091CE240;
extern s32* D_psp_091CE238;
extern s32* D_psp_091CE230;
extern s32* D_psp_091CE228;
extern s32* D_psp_091CE220;
extern s32* D_psp_091CE218;

extern u32 D_psp_08B42050; // psp cross button
extern u32 D_psp_08B42054; // psp triangle button
#endif

s32 HandleSaveMenu(s32 arg0) {
#if defined(VERSION_US)
#define CONFIRM PAD_CROSS
#define EXIT PAD_TRIANGLE
#elif defined(VERSION_HD)
#define CONFIRM (PAD_START | PAD_SQUARE | PAD_CIRCLE)
#define EXIT PAD_CROSS
#elif defined(VERSION_PSP)
#define CONFIRM (D_psp_08B42050 | PAD_START | PAD_SQUARE)
#define EXIT D_psp_08B42054
#endif

// Somewhat clumsy way to avoid ifdef throughout the code.
// V86P70 means "Value is 86, except on PSP it's 70"
#ifdef VERSION_PSP
#define V86P70 70
#define Vx60Px90 0x90
#define Vx70PxA0 0xA0
#define V72P56 56
#define V86P62 62
#define V96P152 152
#define V80P56 56
#define V62P46 46
#define V144P184 184
#define V56P40 40
#define V24P36 36
#else
#define V86P70 86
#define Vx60Px90 0x60
#define Vx70PxA0 0x70
#define V72P56 72
#define V86P62 86
#define V96P152 96
#define V80P56 80
#define V62P46 62
#define V144P184 144
#define V56P40 56
#define V24P36 24
#endif
    u8 temp_t0;

    Primitive* prim2;
    Primitive* prim1;
    Primitive* prim3;

    s32 temp_a1;

    prim2 = &g_PrimBuf[D_80137E58];
    prim1 = &g_PrimBuf[D_80137E5C];
    prim3 = &g_PrimBuf[D_80137E60];
    temp_t0 = prim2->p1;

    if (arg0 == 0) {
        if (!temp_t0) {
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
#elif defined(VERSION_PSP)
                func_800F9D88(D_psp_091CE238, 0, 1);
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
#elif defined(VERSION_PSP)
                func_800F9D88("セーブできません　　", 0, 1);
                func_800F9D88("でした　　　　　　　", 1, 0);
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
#elif defined(VERSION_PSP)
                func_800F9D88("メモリーカードが　　", 0, 1);
                func_800F9D88("　壊れています　　　", 1, 0);
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
#elif defined(VERSION_PSP)
                func_800F9D88("　メモリーカードが　", 0, 1);
                func_800F9D88("初期化されていません", 1, 0);
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
#elif defined(VERSION_PSP)
                    func_800F9D88("　　上書き　　　　　", 0, 1);
                    func_800F9D88("　できません　　　　", 1, 0);
#endif
                } else if (D_80137E54 == 3) {
#if defined(VERSION_US)
                    func_800F9D88("No game", 0, 1);
                    func_800F9D88("data found．", 1, 0);
#elif defined(VERSION_HD)
                    func_800F9D40("データがないため　　", 0, 1);
                    func_800F9D40("上書きできません　　", 1, 0);
#elif defined(VERSION_PSP)
                    func_800F9D88("データがないため　　", 0, 1);
                    func_800F9D88("上書きできません　　", 1, 0);
#endif
                } else {
#if defined(VERSION_US)
                    func_800F9D88("   ０ memory", 0, 1);
                    func_800F9D88("blocks available．", 1, 0);
#elif defined(VERSION_HD)
                    func_800F9D40("空きブロックが　　　", 0, 1);
                    func_800F9D40("　足りません　　　　", 1, 0);
#elif defined(VERSION_PSP)
                    func_800F9D88(D_psp_091CE230, 0, 1);
                    func_800F9D88(D_psp_091CE228, 1, 0);
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
#elif defined(VERSION_PSP)
                func_800F9D88("　メモリーカードの　", 0, 1);
                func_800F9D88("初期化に失敗しました　", 1, 0);
#endif
                prim2->p1 += 2;
            }
        } else if ((D_80137E4C == 7 || D_80137E4C == 8) && (temp_t0 < 33)) {
            SetTexturedPrimRect(prim2, 80, 96 - temp_t0, 96, temp_t0, 0, 0);
            prim2->p1 += 2;
            SetPrimRect(prim1, 72, 96 - temp_t0, 112, temp_t0);
            func_80103148(prim3, prim1);
        } else if ((D_80137E4C == 9 || D_80137E4C == 11) && (temp_t0 < 33)) {
            SetTexturedPrimRect(prim2, 68, 96 - temp_t0, 120, temp_t0, 0, 0);
            prim2->p1 += 2;
            SetPrimRect(prim1, 60, 96 - temp_t0, 136, temp_t0);
            func_80103148(prim3, prim1);
        } else if (D_80137E4C == 10 && temp_t0 < 33) {
#if defined(VERSION_US)
            temp_a1 = 0;
            if (D_80137E54 != 2 && D_80137E54 != 3) {
                temp_a1 = -10;
            }
            SetTexturedPrimRect(
                prim2, temp_a1 + 80, 96 - temp_t0, 112, temp_t0, 0, 0);
            prim2->p1 += 2;
            if (D_80137E54 == 2 || D_80137E54 == 3) {
                SetPrimRect(prim1, 72, 96 - temp_t0, 112, temp_t0);
            } else {
                SetPrimRect(prim1, 68, 96 - temp_t0, 120, temp_t0);
            }
#else
            temp_a1 = 0;
            if (D_80137E54 == 3) {
                temp_a1 = -6;
            }
            SetTexturedPrimRect(
                prim2, temp_a1 + V86P70, 96 - temp_t0, Vx60Px90, temp_t0, 0, 0);
            prim2->p1 += 2;
            SetPrimRect(prim1, V72P56, 96 - temp_t0, Vx70PxA0, temp_t0);
#endif
            func_80103148(prim3, prim1);
        } else if (temp_t0 < 17) {
            SetTexturedPrimRect(
                prim2, V86P62, 80 - temp_t0, V96P152, temp_t0, 0, 0);
            prim2->p1 += 2;
            SetPrimRect(prim1, V80P56, 80 - temp_t0, V96P152, temp_t0);
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
        return 0;
    }

    if (arg0 == 1) {
// This section handles memory card selection. PSP doesn't give that option.
#ifdef VERSION_PSP
        D_80097924 = 0;
        D_8006C378 = -1;
        return 1;
    }
#else
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
        return 0;
    }
#endif
    if (!temp_t0) {
        PlaySfx(SFX_UI_ALERT_TINK);
        prim2->p1 += 2;
        if (arg0 == 2) {
#if defined(VERSION_US)
            func_800F9D88(" Wish to format？", 0, 1);
#elif defined(VERSION_HD)
            func_800F9D40("初期化してもいいですか　", 0, 1);
#else
                func_800F9D88("初期化してもいいですか　", 0, 1);
#endif
            D_80137E6C = 1;
        }
        if (arg0 == 3) {
#if defined(VERSION_US)
            func_800F9D88(" Overwrite data？", 0, 1);
#elif defined(VERSION_HD)
            func_800F9D40("　　上書きしますか　　　", 0, 1);
#else
                func_800F9D88(D_psp_091CE240, 0, 1);
#endif
            D_80137E6C = 0;
        }
        if (arg0 == 4) {
#if defined(VERSION_US)
            func_800F9D88("   Wish to save？", 0, 1);
#elif defined(VERSION_HD)
            func_800F9D40("　　セーブしますか　　　", 0, 1);
#else
                func_800F9D88(D_psp_091CE248, 0, 1);
#endif
            D_80137E6C = 0;
        }
#if defined(VERSION_US)
        func_800F9D88("Yes ", 1, 0);
        func_800F9D88("  No  ", 2, 0);
#elif defined(VERSION_HD)
        func_800F9D40("はい　　", 1, 0);
        func_800F9D40("いいえ　", 2, 0);
#else
            func_800F9D88(D_psp_091CE220, 1, 0);
            func_800F9D88(D_psp_091CE218, 2, 0);
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
        SetTexturedPrimRect(
            prim2, V62P46, 80 - temp_t0, V144P184, temp_t0, 0, 0);
        SetPrimRect(prim1, V56P40, 80 - temp_t0, V144P184, temp_t0);
        prim3 = func_80103148(prim3, prim1);
        prim2 = prim2->next;
        prim1 = prim1->next;
        SetTexturedPrimRect(prim2, 72, 104 - temp_t0, V24P36, temp_t0, 0, 16);
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

    return 0;
}

void func_80103EAC(void) {
    D_80137E4C = 0;
    MemcardInfoInit();
}

void func_80103ED4(void) {
    #if defined(VERSION_PSP)
    #define IFSTATEMENT (g_MemCardRetryCount-- == 0)
    #else
    #define IFSTATEMENT (--g_MemCardRetryCount == -1)
    #endif

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
            if (IFSTATEMENT) {
                D_80137E4C = 7;
            }
        } else if (case1_state == -3) {
            if (IFSTATEMENT) {
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
        #ifdef VERSION_PSP
        func_psp_090DFC68();
        if (MemcardWriteFile(D_80097924, 0, saveFile, g_Pix, 1, i, 1) != 0) {
            D_801379BC = 0x101;
            D_80137E54 = 0;
            D_80097924 = D_80137EF0;
            D_8006C378 = D_80137EF4;
            g_Player.padSim = 0;
            g_Player.demo_timer = 1;
            D_80137E4C = 6;
        #else
        if (MemcardWriteFile(D_80097924, 0, saveFile, g_Pix, 1, i) != 0) {
            if (--g_MemCardRetryCount == -1) {
                D_80137E4C = 0;
            }
        #endif
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
            if (--g_MemCardRetryCount != -1) {
                D_80137E4C--;
                break;
            }
            D_80137E4C = 0;
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
    {&D_80137E70[10], &D_80137E70[7], &D_80137E70[6]},
    {&D_80137E70[10], &D_80137E70[6], &D_80137E70[0]},
    {&D_80137E70[0], &D_80137E70[6], &D_80137E70[1]},
    {&D_80137E70[10], &D_80137E70[0], &D_80137E70[13]},
    {&D_80137E70[9], &D_80137E70[7], &D_80137E70[10]},
    {&D_80137E70[6], &D_80137E70[7], &D_80137E70[5]},
    {&D_80137E70[9], &D_80137E70[11], &D_80137E70[7]},
    {&D_80137E70[0], &D_80137E70[2], &D_80137E70[13]},
    {&D_80137E70[7], &D_80137E70[11], &D_80137E70[5]},
    {&D_80137E70[9], &D_80137E70[10], &D_80137E70[13]},
    {&D_80137E70[1], &D_80137E70[6], &D_80137E70[5]},
    {&D_80137E70[0], &D_80137E70[1], &D_80137E70[2]},
    {&D_80137E70[2], &D_80137E70[1], &D_80137E70[3]},
    {&D_80137E70[12], &D_80137E70[11], &D_80137E70[9]},
    {&D_80137E70[2], &D_80137E70[4], &D_80137E70[13]},
    {&D_80137E70[11], &D_80137E70[8], &D_80137E70[5]},
    {&D_80137E70[12], &D_80137E70[9], &D_80137E70[13]},
    {&D_80137E70[3], &D_80137E70[1], &D_80137E70[5]},
    {&D_80137E70[12], &D_80137E70[8], &D_80137E70[11]},
    {&D_80137E70[2], &D_80137E70[3], &D_80137E70[4]},
    {&D_80137E70[4], &D_80137E70[12], &D_80137E70[13]},
    {&D_80137E70[8], &D_80137E70[3], &D_80137E70[5]},
    {&D_80137E70[4], &D_80137E70[8], &D_80137E70[12]},
    {&D_80137E70[4], &D_80137E70[3], &D_80137E70[8]}};

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

MATRIX D_800A37B8 = {0};

u16 D_800A37D8[] = {0x8430, 0x843F};
u16 g_JosephsCloakColors[] = {0x8000, 0x8000, 0x8000, 0x8000};

u16 D_800A37E4[] = {0x8430, 0x843F};
u16 D_800A37E8[] = {0xD5CE, 0xE739};
u16 D_800A37EC[] = {0xBEBB, 0xFFFF};
u16 D_800A37F0[] = {0x8594, 0x873F};
u16 D_800A37F4[] = {0x994A, 0xA5CE, 0x8421, 0x9CE7};
u16 D_800A37FC[] = {0x8420, 0x8427};
u16 D_800A3800[] = {0x8421, 0x9CE7};
u16 D_800A3804[] = {0xA4A8, 0xAD0A, 0xCC21, 0xFC42};
u16 D_800A380C[] = {0x910C, 0x996E, 0x8048, 0x80B2};
u16 D_800A3814[] = {0x90A1, 0x9102, 0xA821, 0xCC42};
u16 D_800A381C[] = {0x90C9, 0x94EB, 0x85E4, 0xA2CD};
u16 D_800A3824[] = {0x842C, 0x8C6F, 0x8018, 0x98DD};
u16 D_800A382C[] = {0x994A, 0xA5CE, 0x0000, 0xBC0F};
u16 D_800A3834[] = {0x8433, 0x843A};
u16 D_800A3838[] = {0x0000, 0x0000, 0x0000, 0x0000};
u16 D_800A3840[] = {0xCC21, 0xFC42, 0xA4A8, 0xAD0A};

extern u16 D_8006ED0C[0x10];
extern u16 D_8006ED2C[0x10];
extern u16 D_8006ED4C[0x10];
extern u8 D_800C217C[]; // external file
extern u8 D_800C27B0[]; // external file
extern u8 D_800C3560[]; // external file
extern u8 D_800C4864[]; // external file
extern u8 D_800C4A90[]; // external file
extern u16 D_800D68D4[0x10];
extern u16 D_800D68F4[0x10];
extern u16 D_800D6914[0x10];
extern u16 D_800D6934[0x10];
extern u16 D_800D6954[0x10];
extern u16 D_800D6974[0x10];
extern u16 D_800D6994[0x10];
extern u16 D_800D69B4[0x10];
extern u16 D_800D69D4[0x10];
extern u16 D_800D69F4[0x10];
extern u16 D_800D6A14[0x10];
extern u16 D_800D6A34[0x10];
extern u16 D_800D6A54[0x40]; // UNUSED
extern u16 D_800D6AD4[0x100];
extern u16 D_800D6CD4[0x100];
extern u16 D_800D6ED4[0x100];
extern u16 D_800D70D4[0x100];
extern u16 D_800D72D4[0x100];
extern u16 D_800DB0D4[0x10];
extern u16 D_800DB0F4[0x10];
extern u16 D_800DB114[0x70];
extern u16 D_800DB1F4[0xE0];

u_long* D_800A3848[] = {GFX_TERMINATE()};
u_long* D_800A384C[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(256, 800, 128, 128, D_800C217C),
    GFX_TERMINATE(),
};

u_long* D_800A3860[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(256, 800, 128, 128, D_800C3560),
    GFX_ENTRY(368, 992, 16, 80, D_800C4A90),
    GFX_TERMINATE(),
};

u_long* D_800A3880[] = {
    GFX_BANK_COMPRESSED,
    GFX_ENTRY(256, 800, 128, 128, D_800C27B0),
    GFX_ENTRY(368, 992, 16, 80, D_800C4864),
    GFX_TERMINATE(),
};

u16 D_800A38A0[] = {
    0x0000, 0xA108, 0xC210, 0xCA92, 0xD294, 0xDF97, 0xE739, 0xF39C,
    0xFBDE, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};
u_long* D_800A38C0[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA(0x1A10, D_800A38A0),
    PAL_TERMINATE(),
};

u_long* D_800A38D4[] = {
    MAKE_PAL_OP(PAL_GLOW_ANIM, 6),
    PAL_GLOW_INFO(0x1721, 1),
    PAL_GLOW_DATA(&D_800A37E4[0]),
    PAL_GLOW_DATA(&D_800A37E4[1]),
    PAL_TERMINATE(),
};

u_long* D_800A38EC[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA(0x171E, D_800A37E8),
};

u_long* D_800A38FC[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA(0x171E, D_800A37EC),
};

u_long* D_800A390C[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA(0x171E, D_800A37F0),
};

u_long* D_800A391C[] = {
    MAKE_PAL_OP(PAL_UNK_OP3, 4),
    PAL_UNK_OP3_INFO(0x1700, LEN(D_800D68D4)),
    PAL_UNK_OP3_DATA(D_800D68D4),
    PAL_UNK_OP3_DATA(D_800D68F4),
    PAL_TERMINATE(),
};

u_long* D_800A3934[] = {
    MAKE_PAL_OP(PAL_UNK_OP3, 4),  PAL_UNK_OP3_INFO(0x1600, LEN(D_800D6AD4)),
    PAL_UNK_OP3_DATA(D_800D6AD4), PAL_UNK_OP3_DATA(D_800D6CD4),
    PAL_UNK_OP3_DATA(D_800D6ED4), PAL_UNK_OP3_DATA(D_800D70D4),
    PAL_UNK_OP3_DATA(D_800D72D4), PAL_TERMINATE(),
};

u_long* D_800A3958[] = {
    MAKE_PAL_OP(PAL_UNK_OP3, 4),  PAL_UNK_OP3_INFO(0x17E0, LEN(D_800D6914)),
    PAL_UNK_OP3_DATA(D_800D6914), PAL_UNK_OP3_DATA(D_800D6934),
    PAL_UNK_OP3_DATA(D_800D6954), PAL_UNK_OP3_DATA(D_800D6974),
    PAL_UNK_OP3_DATA(D_800D6994), PAL_TERMINATE(),
};

u_long* D_800A397C[] = {
    MAKE_PAL_OP(PAL_UNK_OP3, 4),  PAL_UNK_OP3_INFO(0x17F0, LEN(D_800D69B4)),
    PAL_UNK_OP3_DATA(D_800D69B4), PAL_UNK_OP3_DATA(D_800D69D4),
    PAL_UNK_OP3_DATA(D_800D69F4), PAL_UNK_OP3_DATA(D_800D6A14),
    PAL_UNK_OP3_DATA(D_800D6A34), PAL_TERMINATE(),
};

u_long* D_800A39A0[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA(0x1006, D_800A37F4),
};

u_long* D_800A39B0[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA(0x1008, D_800A3800),
};

u_long* D_800A39C0[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA(0x1006, D_800A3804),
};

u_long* D_800A39D0[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA(0x1006, D_800A3840),
};

u_long* D_800A39E0[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA(0x1006, D_800A380C),
};

u_long* D_800A39F0[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA(0x1006, D_800A3814),
};

u_long* D_800A3A00[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA(0x1006, D_800A381C),
};

u_long* D_800A3A10[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA(0x1006, D_800A3824),
};

u_long* D_800A3A20[] = {
    MAKE_PAL_OP(PAL_UNK_OP3, 1),
    PAL_UNK_OP3_INFO(0x1006, LEN(D_800A382C)),
    PAL_UNK_OP3_DATA(D_800A382C),
    PAL_UNK_OP3_DATA(D_800A3838),
    PAL_TERMINATE(),
};

u_long* D_800A3A38[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA(0x1006, g_JosephsCloakColors),
};

u_long* D_800A3A48[] = {
    MAKE_PAL_OP(PAL_GLOW_ANIM, 2),
    PAL_GLOW_INFO(0x1006, LEN(D_800A37FC)),
    PAL_GLOW_DATA(D_800A37FC),
    PAL_GLOW_DATA(D_800A3834),
    PAL_TERMINATE(),
};

u_long* D_800A3A60[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA(0x0000, D_800DB0D4),
    PAL_TERMINATE(),
};

u_long* D_800A3A74[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA(0x1F00, D_800DB0F4),
    PAL_TERMINATE(),
};

u_long* D_800A3A88[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA_(0x1F20, D_800D6AD4 + 64, 16),
    PAL_TERMINATE(),
};

u_long* D_800A3A9C[] = {
    MAKE_PAL_OP(PAL_GLOW_ANIM, 1),
    PAL_GLOW_INFO(0x1F20, 16),
    PAL_GLOW_DATA(D_800D6AD4 + 160),
    PAL_GLOW_DATA(D_800D6AD4 + 64),
    PAL_TERMINATE(),
};

u16 D_800A3AB4[] = {0x8076, 0x80FB};
u16 D_800A3AB8[] = {0x8048, 0x80B1};
u_long* D_800A3ABC[] = {
    MAKE_PAL_OP(PAL_UNK_OP2, 1),
    PAL_UNK_OP2_INFO(0x1F0E, LEN(D_800A3AB4)),
    PAL_UNK_OP2_DATA(D_800A3AB4),
    PAL_UNK_OP2_DATA(D_800A3AB8),
    PAL_TERMINATE(),
};

u_long* D_800A3AD4[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA(0x1D00, D_800DB114),
    PAL_TERMINATE(),
};

u_long* D_800A3AE8[] = {
    MAKE_PAL_OP(PAL_GLOW_ANIM, 2),
    PAL_GLOW_INFO(0x100A, 1),
    PAL_GLOW_DATA(&D_800A37D8[0]),
    PAL_GLOW_DATA(&D_800A37D8[1]),
    PAL_TERMINATE(),
};

u_long* D_800A3B00[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA(0x10F0, D_8006ED0C),
};

u_long* D_800A3B10[] = {
    MAKE_PAL_OP(PAL_UNK_OP2, 2),
    PAL_UNK_OP2_INFO(0x10F0, LEN(D_8006ED4C)),
    PAL_UNK_OP2_DATA(D_8006ED4C),
    PAL_TERMINATE(),
};

u_long* D_800A3B24[] = {
    MAKE_PAL_OP(PAL_UNK_OP2, 2),
    PAL_UNK_OP2_INFO(0x10F0, 16),
    PAL_UNK_OP2_DATA(&g_Clut[0x1000]),
    PAL_TERMINATE(),
};

u_long* D_800A3B38[] = {
    MAKE_PAL_OP(PAL_UNK_OP2, 2),
    PAL_UNK_OP2_INFO(0x10F0, LEN(D_8006ED2C)),
    PAL_UNK_OP2_DATA(D_8006ED2C),
    PAL_TERMINATE(),
};

u_long* D_800A3B4C[] = {
    PAL_COPY_INFO(),
    PAL_COPY_DATA(0x1000, D_800DB1F4),
};

GfxBank** g_GfxSharedBank[] = {
    D_800A3848, D_800A384C, D_800A3848, D_800A3860, D_800A3880,
};

extern s16* D_800CF324[];
extern s16* D_800CFF10[];
extern s16* D_800D0F68[];
extern s16* D_800D2BF4[];
extern s16* D_800D2CF8[];
extern s16* D_800D2FFC[];
extern s16* D_800D3428[];
extern s16* D_800D34B8[];
extern s16* D_800D372C[];
extern s16* D_800D3B88[];
extern s16* D_800D5628[];
extern s16* D_800D327C[];
extern s16* D_800D56AC[];
extern s16* D_800D5868[];
extern s16* D_800D684C[];

s16** D_800A3B70[] = {
    NULL,       D_800CF324, D_800CFF10, D_800D0F68, D_800D2BF4, D_800D2CF8,
    D_800D2FFC, D_800D3428, D_800D34B8, D_800D372C, D_800D3B88, D_800D5628,
    D_800D327C, D_800CFE48, D_800D56AC, D_800D5868, D_800D5868, D_800D684C,
};

u_long* D_800A3BB8[] = {
    D_800A38C0, D_800A38EC, D_800A38FC, D_800A390C, D_800A391C, D_800A3934,
    D_800A3958, D_800A397C, D_800A38D4, D_800A39A0, D_800A39B0, D_800A39C0,
    D_800A39D0, D_800A39F0, D_800A3A00, D_800A3A10, D_800A3A20, D_800A3A38,
    D_800A39E0, D_800A39A0, D_800A39A0, D_800A3A48, D_800A3B4C, D_800A3AE8,
    D_800A3A74, D_800A3A88, D_800A3A60, D_800A3B00, D_800A3B10, D_800A3B24,
    D_800A3A9C, D_800A3B38, D_800A3ABC, D_800A3AD4,
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
    D_801379C0.vx = D_801379C0.vy = D_801379C0.vz = 0;

    D_801379D0.vx = D_801379D0.vy = 0;
    D_801379D0.vz = 0x100;
    D_80137E48 = AllocPrimitives(PRIM_TILE, PrimCount);
    prim = &g_PrimBuf[D_80137E48];
    i = 0;

    for (i = 0; i < PrimCount; i++) {
        prim->x0 = (i & 1) << 7;
        prim->y0 = (i / 2) * 0xD8;
        prim->u0 = 0x80;
        prim->v0 = 0x20;

        if ((i < 2 && !(g_StageId & 0x20)) || (i >= 2 && g_StageId & 0x20)) {
            prim->g0 = 0x10;
            prim->r0 = 0x10;
            prim->b0 = 8;
        }

        prim->priority = 0x1EB;
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
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
    prim = &g_PrimBuf[D_80137E40];
    if (prim != NULL) {
        do {
            prim->u0 = 0xDB;
            prim->v0 = 0xA8;
            prim->u1 = 0xBC;
            prim->v1 = 0xDE;
            prim->u2 = 0xFA;
            prim->v2 = 0xDE;
            prim->tpage = 0x1B;
            prim->clut = arg0 + 0x1F1;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        } while (prim != NULL);
    }
    D_80137E44 = AllocPrimitives(2U, 0x12);
    prim = &g_PrimBuf[D_80137E44];
    if (prim != NULL) {
        do {
            prim->r0 = 0xFF;
            prim->g0 = 0xFF;
            prim->b0 = 0xFF;
            prim->r1 = 0xFF;
            prim->g1 = 0xFF;
            prim->b1 = 0xFF;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        } while (prim != NULL);
    }
}

void func_80104790(s32 arg0, s32 arg1, s32 arg2) {
#if defined(VERSION_US)
    const s32 PRIORITY_SHIFT = 16;
#elif defined(VERSION_HD)
    const s32 PRIORITY_SHIFT = 8;
#endif
    VECTOR sp28;
    SVECTOR pad;
    SVECTOR sp40[3];
    SVECTOR sp58[3];
    u8 sp70[4];
    s32 sp78;
    s32 sp7C;
    s32 sp80;
    s32 spA0;
    s32 spA8;
    SVECTOR** spB0;
    SVECTOR* var_s2;
    VECTOR* var_s3;
    Primitive* prim;
    s32 temp_v0_5;
    s32 var_a0;
    s32 var_a1;
    s32 var_a2_2;
    s32 var_a3_2;
    s32 i;
    s32 var_v1;
    s32 var_v1_2;
    u8* var_s7;

    sp70[2] = sp70[1] = sp70[0] = 0x80;
    sp70[3] = 0;
    RotMatrix(&D_801379C8, &D_80137E00); // types copied
    RotMatrix(&D_801379C8, &D_80137E20); // types copied
    SetColorMatrix(&D_800A37B8);         // types copied
    SetLightMatrix(&D_80137E20);         // types copied
    SetBackColor(0xC0, 0xC0, 0xC0);
    prim = &g_PrimBuf[D_80137E40];

    switch (arg0) {
    case 0:
        spB0 = &D_800A3210;
        var_s3 = &D_801379E0;
        var_s2 = &D_80137CA0;
        spA8 = 0x14;
        break;
    case 1:
    case 2:
        spB0 = &D_800A33A0;
        var_s3 = &D_80137B20;
        var_s2 = &D_80137D40;
        spA8 = 0x18;
        break;
    case 3:
        spB0 = &D_800A3608;
        var_s3 = &D_80137B20;
        var_s2 = &D_80137D40;
        spA8 = 0x18;
        for (spA0 = 0; spA0 < LEN(D_800A3598); spA0++) {
            D_80137E70[spA0].vx =
                D_800A3598[spA0]->vx +
                (((D_800A35D0[spA0]->vx - D_800A3598[spA0]->vx) * arg2) / 96);
            D_80137E70[spA0].vy =
                D_800A3598[spA0]->vy +
                (((D_800A35D0[spA0]->vy - D_800A3598[spA0]->vy) * arg2) / 96);
            D_80137E70[spA0].vz =
                D_800A3598[spA0]->vz +
                (((D_800A35D0[spA0]->vz - D_800A3598[spA0]->vz) * arg2) / 96);
            D_80137E70[spA0].pad = 0;
        }
    }

    var_s7 = &D_800A3728;
    for (spA0 = 0; spA0 < LEN(D_800A3210); spA0++, prim = prim->next,
        spB0 += 3) {
        if (spA0 >= spA8) {
            prim->drawMode = DRAW_HIDE;
            continue;
        }
        TransMatrix(&D_80137E00, &D_801379D0); // types copied
        SetRotMatrix(&D_80137E00);             // types copied
        SetTransMatrix(&D_80137E00);           // types copied

        var_a1 = 0;
        var_a3_2 = 0;
        var_a2_2 = 0;
        var_a0 = arg2;
        var_v1 = arg2;
        sp7C = 0;
        if (arg0 == 2) {
            var_v1_2 = (spA0 * 4);
            var_v1_2 -= 0x5C;
            var_v1_2 += arg2;
            if (var_v1_2 < 0) {
                var_v1_2 = 0;
            }
            if (var_v1_2 >= 0x80) {
                var_v1_2 = 0x7F;
            }
            var_a2_2 = var_v1_2 << 0xC;
            var_a1 = var_a2_2;
            var_a3_2 = -var_a2_2 * 4;
            if (var_s2[spA0].vx < 0) {
                do {
                    var_a1 = -var_a1;
                } while (0);
            }
            if (var_s2[spA0].vz < 0) {
                var_a2_2 = -var_a2_2;
            }
            var_a0 = 0;
            var_v1 = 0;
        }
        if (arg0 == 3) {
            var_a0 = 0;
            var_v1 = 0;
        }
        var_s3[spA0].vx = ((var_s2[spA0].vx * var_a0) + var_a1);
        var_s3[spA0].vy = ((var_s2[spA0].vy * var_v1) + var_a3_2);
        var_s3[spA0].vz = ((var_s2[spA0].vz * var_a0) + var_a2_2);
        for (i = 0; i < 3; i++) {
            sp28.vx = sp40[i].vx =
                ((spB0[i]->vx * arg1) >> 8) + (var_s3[spA0].vx >> 0xC);
            sp28.vy = sp40[i].vy =
                ((spB0[i]->vy * arg1) >> 8) + (var_s3[spA0].vy >> 0xC);
            sp28.vz = sp40[i].vz =
                ((spB0[i]->vz * arg1) >> 8) + (var_s3[spA0].vz >> 0xC);
            func_80017008(&sp28, &sp58[i]);
        }
        temp_v0_5 = RotAverageNclip3(
            &sp40[0], &sp40[1], &sp40[2], (s32*)&prim->x0, (s32*)&prim->x1,
            (s32*)&prim->x2, &sp78, &sp7C, &sp80);
        if (temp_v0_5 < 0) {
            RotAverageNclip3(
                &sp40[0], &sp40[2], &sp40[1], (s32*)&prim->x0, (s32*)&prim->x2,
                (s32*)&prim->x1, &sp78, &sp7C, &sp80);
        }
        func_801072DC(prim);
        prim->type = PRIM_GT3;
        if (sp7C >= 0xF0) {
            continue;
        }
        if (temp_v0_5 >= 0) {
            prim->priority = g_unkGraphicsStruct.g_zEntityCenter + 4;
        } else {
            prim->priority = g_unkGraphicsStruct.g_zEntityCenter - 4;
        }
        prim->drawMode = DRAW_COLORS;
        if (((D_80137E4C == 6) || (D_80137EE0 != 0)) &&
            (((u32)(arg0 - 1) < 2U) || ((arg0 == 3) && (arg2 >= 0x40)))) {
            prim->clut = (D_80137EE0 * 2) + 0x1F0;
            prim->u0 = *var_s7++ + 0x80;
            prim->v0 = *var_s7++ + 0x80;
            prim->u1 = *var_s7++ + 0x80;
            prim->v1 = *var_s7++ + 0x80;
            prim->u2 = *var_s7++ + 0x80;
            prim->v2 = *var_s7++ + 0x80;
            if (temp_v0_5 < 0) {
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
            prim->drawMode = DRAW_COLORS;
        } else if ((arg0 != 2) && (arg2 >= 0x40)) {
            // this i is a register reuse, not an iterator
            i = 0x7F - arg2;
            prim->r0 = ((prim->r0 * i) >> 6);
            prim->g0 = ((prim->g0 * i) >> 6);
            prim->b0 = ((prim->b0 * i) >> 6);
            prim->r1 = ((prim->r1 * i) >> 6);
            prim->g1 = ((prim->g1 * i) >> 6);
            prim->b1 = ((prim->b1 * i) >> 6);
            prim->r2 = ((prim->r2 * i) >> 6);
            prim->g2 = ((prim->g2 * i) >> 6);
            prim->b2 = ((prim->b2 * i) >> 6);
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        }
    }
}

void func_80105078(s32 arg0, s32 arg1) {
    VECTOR sp28;
    SVECTOR pad;
    SVECTOR sp40[3];
    SVECTOR sp58[3];
    u8 sp70[4];
    s32 sp78;
    s32 sp7C;
    s32 sp80;
    s32 sp88;
    SVECTOR** sp90;
    Primitive* prim;
    s32 temp_v0_4;
    s32 i;

    sp70[2] = sp70[1] = sp70[0] = 0x80;
    sp70[3] = 0;
    RotMatrix(&D_801379C8, &D_80137E00);
    RotMatrix(&D_801379C8, &D_80137E20);
    SetColorMatrix(&D_800A37B8);
    SetLightMatrix(&D_80137E20);
    SetBackColor(0xC0, 0xC0, 0xC0);

    sp90 = &D_800A34C0;
    prim = &g_PrimBuf[D_80137E44];

    for (sp88 = 0; sp88 < 18; sp88++, prim = prim->next, sp90 += 3) {
        if (arg0 == 0) {
            prim->drawMode = DRAW_HIDE;
            continue;
        }
        TransMatrix(&D_80137E00, &D_801379D0);
        SetRotMatrix(&D_80137E00);
        SetTransMatrix(&D_80137E00);
        sp7C = 0;
        for (i = 0; i < 3; i++) {
            sp28.vx = sp40[i].vx = (sp90[i]->vx * arg0) >> 8;
            sp28.vy = sp40[i].vy = (sp90[i]->vy * arg0) >> 8;
            sp28.vz = sp40[i].vz = (sp90[i]->vz * arg0) >> 8;
            func_80017008(&sp28, &sp58[i]);
        }
        temp_v0_4 = RotAverageNclip3(
            &sp40[0], &sp40[1], &sp40[2], (s32*)&prim->x0, (s32*)&prim->x1,
            (s32*)&prim->x2, &sp78, &sp7C, &sp80);
        if (temp_v0_4 < 0) {
            RotAverage3(&sp40[0], &sp40[2], &sp40[1], (s32*)&prim->x0,
                        (s32*)&prim->x2, (s32*)&prim->x1, &sp78, &sp80);
        }
        prim->type = PRIM_LINE_G2;
        if (sp7C < 0xF0) {
            if (temp_v0_4 >= 0) {
                prim->priority = g_unkGraphicsStruct.g_zEntityCenter + 3;
            } else {
                prim->priority = g_unkGraphicsStruct.g_zEntityCenter - 3;
            }
            if (arg1 != 0) {
                if (arg1 & 0x80) {
                    prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 =
                        prim->b1 = arg1 & 0x7F;
                } else if (arg1 < 0x11) {
                    prim->r0 = prim->g0 = prim->b0 = (0x10 - arg1) * 8;
                } else if (arg1 < 0x21) {
                    prim->r1 = prim->g1 = prim->b1 = (0x20 - arg1) * 8;
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

void func_80105408(void) {
    g_Player.padSim = PAD_UP;
    g_Player.demo_timer = 1;
}

void func_80105428(void) {
#if defined(VERSION_US)
    const s32 PAD_MASK = PAD_CROSS | PAD_TRIANGLE;
#elif defined(VERSION_HD)
    const s32 PAD_MASK = PAD_START | PAD_SQUARE | PAD_CROSS | PAD_CIRCLE;
#endif
    s32 temp_s0;
    s32 temp_result;
    s32 timer_temp;
    u16 temp_s3;
    u32 gameTimer;

    SetGeomScreen(0x100);
    SetGeomOffset(0x80, D_801379B8 + 0x80);
    if (D_8003C730 != 0) {
        D_80137E4C = 6;
        D_80137EE4 = 0x100;
        g_PauseAllowed = false;
        D_801379BC = 7;
        D_8003C730 = 0;
    }
    if (D_80137E54 != 0) {
        func_80103ED4();
    }
    temp_s3 = D_801379C8.vy;
#if defined(VERSION_US)
    g_Player.unk7A = 1;
#endif
    temp_s0 = D_801379BC;
    switch (temp_s0) {
    case 0x0:
        gameTimer = g_GameTimer;
        timer_temp = gameTimer & 0x7F;
        D_801379C8.vy = temp_s3 + 6;
        if (timer_temp == 0) {
            PlaySfx(SFX_SAVE_HEARTBEAT);
        }
        if (gameTimer & 0x40) {
            timer_temp = 0x7F - timer_temp;
        }
        if (timer_temp >= 8) {
            timer_temp = 0xC0;
        } else {
            timer_temp = (timer_temp * 4) + 0xA0;
        }
        func_80104790(0, timer_temp, 0);
        D_80137EE4 = timer_temp;

        if (func_8010E334(0x60, 0xA0) != 0) {
            g_PauseAllowed = false;
            D_80137EF0 = D_80097924;
            D_80137EF4 = D_8006C378;
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
        if ((D_801379B8 <
             (((s32)(g_StageId & STAGE_INVERTEDCASTLE_FLAG) >> 1) + 8)) &&
            (g_GameTimer != 0)) {
            D_801379B8++;
        }
        if (PLAYER.posX.i.hi < 0x7F) {
            g_Player.padSim = PAD_RIGHT;
            g_Player.demo_timer = 1;
        } else if (PLAYER.posX.i.hi > 0x80) {
            g_Player.padSim = PAD_LEFT;
            g_Player.demo_timer = 1;
        } else if (D_801379B8 ==
                   (((s32)(g_StageId & STAGE_INVERTEDCASTLE_FLAG) >> 1) + 8)) {
            func_80105408();
            D_80137EE8 = 8;
            if (D_80137EE0 == 0) {
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
            } else {
                D_801379BC++;
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
            } else {
                D_801379BC = 0x101;
                D_80097924 = D_80137EF0;
                D_8006C378 = D_80137EF4;
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
    case 0xB:
        break;
    case 0x101:
        D_801379C8.vy = temp_s3 + D_80137EE8;
        func_80104790(0, D_80137EE4, 0);
        if (g_pads[0].pressed & PAD_MASK) {
            g_Player.padSim = 0;
            g_Player.demo_timer = 1;
            D_80097924 = D_80137EF0;
            D_8006C378 = D_80137EF4;

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
        if (D_80137EE4 >= 0x101) {
            D_80137EE4 = 0x100;
        }
        func_80104790(0, D_80137EE4, 0);

        if (D_80137EE4 == 0x100) {
            if ((D_80137E4C < 4) && (D_80137EE0 == 0)) {
                if (++D_80137EE8 >= 0x81) {
                    D_80137EE8 = 0x80;
                }
            } else {
                D_801379BC++;
            }
        }
        break;
    case 0x3:
        func_80105408();
        D_801379C8.vy += D_80137EE8;
        if (++D_80137EE8 >= 0x81) {
            D_80137EE8 = 0x80;
        }
        func_80104790(0, D_80137EE4, 0);

        if (D_80137EE8 == 0x80) {
            D_80137EEC = 0;
            D_801379BC++;
        }
        break;
    case 0x4:
        func_80105408();
        D_801379C8.vy += D_80137EE8;
        D_80137EEC += 2;
        if (D_80137EEC >= 0x80) {
            D_80137EEC = 0x7F;
        }
        func_80104790(0, D_80137EE4, D_80137EEC);
        if (D_80137EEC >= 0x10) {
            temp_s0 = (D_80137EEC - 0x10) * 0x10;
            if (temp_s0 >= 0x101) {
                temp_s0 = 0x100;
            }
            func_80105078(temp_s0, 0);
        }

        if (D_80137EEC != 0x7F) {
            break;
        }
        if ((D_80137E4C >= 6) || (D_80137EE0 != 0)) {
            if ((u32)((D_801379C8.vy & 0xFFF) - 0x100) < 0x80U) {
                D_801379BC++;
            }
        }
        break;
    case 0x5:
        func_80105408();
        if (D_80137EE8 < 0x41) {
            if ((D_801379C8.vy & 0x7FF) >= 0x400) {
                D_80137EE8 = (0x800 - (D_801379C8.vy & 0x7FF)) / 16;
            }
        } else {
            D_80137EE8--;
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
                if (D_80137EE0 == 0) {
                    func_80102EB8();
                }
                D_801379BC++;
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
                if (D_80137E4C != temp_s0) {
                    D_80097924 = -1;
                    D_801379BC = 0x20;
                    D_80137EEC = 0x60;
                } else {
                    D_801379BC++;
                }
            }
        }
        break;
    case 0x200:
        func_80105408();
        if (HandleSaveMenu(2) != 0) {
            if (D_80137E6C == 0) {
                D_8006C378 = -1;
                PlaySfx(SFX_UI_CONFIRM);
                MemCardSetPort(D_80097924);
                D_801379BC++;
            } else {
                D_80097924 = -1;
                D_801379BC = 0x20;
                D_80137EEC = 0x60;
            }
        }
        break;
    case 0x201:
        func_80105408();
        temp_result = MemCardInitAndFormat();
        if (temp_result == 1) {
            D_801379BC = 0x30;
            D_80137EEC = 0x60;
            break;
        }
        if (temp_result == -1) {
            D_80137E4C = 0xB;
            func_80102EB8();
            D_801379BC++;
        }
        break;
    case 0x202:
        func_80105408();
        if (HandleSaveMenu(0) != 0) {
            D_80097924 = -1;
            D_801379BC = 0x20;
            D_80137EEC = 0x60;
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
        if (D_80137EE8 >= 0x41) {
            D_80137EE8 = 0x40;
        }
        func_80104790(1, D_80137EE4, 0);

        if (D_80137EE8 == 0x40) {
            D_80137EEC = 0;
            D_801379BC++;
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
        D_801379C8.vy = temp_s3 + D_80137EE8;
        if (++D_80137EEC >= 0x80) {
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
            D_80137EEC = 0;
            D_801379BC++;
        }
        break;
    case 0xA:
        D_801379C8.vy += D_80137EE8;
        if (++D_80137EEC >= 0x23) {
            D_80137EEC = 0x22;
        }
        func_80105078(D_80137EE4, D_80137EEC);
        if (D_80137EE8 == 0) {
            D_801379BC++;
        }
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
    case 0x30:
    case 0x20:
        if (D_801379BC == 0x30) {
            func_80105408();
        }
        if (D_80137EEC >= 0x31) {
            func_80105408();
        }
        D_801379C8.vy += 6;
        if (D_80137EE4 >= 0xC1) {
            D_80137EE4 -= 2;
        }
        func_80104790(3, D_80137EE4, D_80137EEC);
        D_80137EEC -= 2;
        if ((g_Player.demo_timer == 0) && (g_pads[0].pressed & PAD_MASK)) {
            g_Player.padSim = 0;
            g_Player.demo_timer = 1;
            if (D_80137EEC <= 0) {
                D_80137EEC = 0;
            }
        } else if (D_80137EEC <= 0) {
            if (D_801379BC == 0x30) {
                D_80137E54 = 0;
                func_80103EAC();
                D_801379BC = 1;
            } else {
                D_80137E54 = 0;
                D_80097924 = D_80137EF0;
                D_8006C378 = D_80137EF4;
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
        ((u32)(D_801379BC - 3) < 7U)) {
        PlaySfx(SFX_SAVE_COFFIN_SWISH);
    }
}
