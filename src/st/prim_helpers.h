// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>

void UnkPrimHelper(Primitive* prim) {
    SVECTOR sp10; // FAKE, not really an svector
    SVECTOR stackpad;
    SVECTOR sp20;
    VECTOR trans1;
    SVECTOR sp38;
    SVECTOR sp40;
    SVECTOR sp48;
    SVECTOR sp50;
    MATRIX m;
    SVECTOR rot = {0, 0, 0};
    u8 temp_v1_2;
    u16 temp;

    if (prim->p3 & 8) {
        // Fake logic here, sp10 is not an SVECTOR but it matches.
        // tried using an f32 but couldn't get it to work.
        sp10.vy = prim->next->x1;
        sp10.vx = prim->next->y1;
        LOW(sp10.vx) += LOWU(prim->next->u0);
        prim->next->x1 = sp10.vy;
        prim->next->y1 = sp10.vx;
        LOW(prim->next->x0) += LOW(prim->next->r1);
    }
    temp_v1_2 = prim->next->b3;
    temp = (temp_v1_2 + (temp_v1_2 << 8));
    LOH(prim->r0) = LOH(prim->r1) = LOH(prim->r2) = LOH(prim->r3) = temp;
    prim->b0 = prim->b1 = prim->b2 = prim->b3 = temp_v1_2;
    trans1.vx = 0;
    trans1.vy = 0;
    trans1.vz = 0x400 - LOH(prim->next->u1);
    RotMatrix(&rot, &m);
    if (prim->p3 & 0x20) {
        sp20.vx = prim->next->x3;
        sp20.vy = prim->next->y3;
        RotMatrixX(sp20.vx, &m);
        RotMatrixY(sp20.vy, &m);
    }
    sp20.vz = LOH(prim->next->tpage);
    RotMatrixZ(sp20.vz, &m);
    TransMatrix(&m, &trans1);
    if (prim->p3 & 0x10) {
        trans1.vx = prim->next->x2;
        trans1.vy = prim->next->y2;
        trans1.vz = 0x1000;
        ScaleMatrix(&m, &trans1);
    }
    SetRotMatrix(&m);
    SetTransMatrix(&m);
    SetGeomScreen(0x400);
    SetGeomOffset(prim->next->x1, prim->next->y0);
    sp38.vx = -LOH(prim->next->r2) / 2;
    sp38.vy = -LOH(prim->next->b2) / 2;
    sp38.vz = 0;
    sp40.vx = LOH(prim->next->r2) / 2;
    sp40.vy = -LOH(prim->next->b2) / 2;
    sp40.vz = 0;
    sp48.vx = -LOH(prim->next->r2) / 2;
    sp48.vy = LOH(prim->next->b2) / 2;
    sp48.vz = 0;
    sp50.vx = LOH(prim->next->r2) / 2;
    sp50.vy = LOH(prim->next->b2) / 2;
    sp50.vz = 0;
    gte_ldv0(&sp38);
    gte_rtps();
    gte_stsxy((long*)&prim->x0);
    gte_ldv0(&sp40);
    gte_rtps();
    gte_stsxy((long*)&prim->x1);
    gte_ldv0(&sp48);
    gte_rtps();
    gte_stsxy((long*)&prim->x2);
    gte_ldv0(&sp50);
    gte_rtps();
    gte_stsxy((long*)&prim->x3);
}

s32 UpdateAnimation(u8* texAnimations, Primitive* prim) {
    u16 sp0;
    u16 tempUv;
    s32 retVal = 0;
    u8 index = prim->p1 * 5;
    u8* nextAnimation = &texAnimations[index];

    if (!prim->p2) {
        if (*nextAnimation) {
            if (*nextAnimation == 0xFF) {
                return 0;
            }
            prim->p2 = *nextAnimation++;
            tempUv = nextAnimation[0] + (nextAnimation[1] << 8);
            nextAnimation += 2;
            sp0 = nextAnimation[0] + (nextAnimation[1] << 8);
            LOH(prim->u0) = tempUv;
            LOH(prim->u1) = tempUv + *((u8*)(&sp0));
            LOH(prim->u2) = tempUv + (*((u8*)&sp0 + 1) << 8);
            LOH(prim->u3) = tempUv + sp0;
            prim->p1++;
            retVal = (retVal | 0x80) & 0xFFFF;
        } else {
            prim->p1 = 0;
            prim->p2 = 0;
            nextAnimation = &texAnimations[0];
            prim->p2 = *nextAnimation++;
            tempUv = nextAnimation[0] + (nextAnimation[1] << 8);
            nextAnimation += 2;
            sp0 = nextAnimation[0] + (nextAnimation[1] << 8);
            LOH(prim->u0) = tempUv;
            LOH(prim->u1) = tempUv + (*(u8*)&sp0);
            LOH(prim->u2) = tempUv + (*((u8*)&sp0 + 1) << 8);
            LOH(prim->u3) = tempUv + sp0;
            prim->p1++;
            return 0;
        }
    }

    prim->p2--;
#ifndef VERSION_PSP
    retVal |= 1;
#endif
    retVal = (retVal | 1) & 0xFFFF;
    return retVal & 0xFF;
}

Primitive* FindFirstUnkPrim(Primitive* prim) {
    Primitive* primLocal = prim;
    while (primLocal != NULL) {
        if (!primLocal->p3) {
            return primLocal;
        }
        primLocal = primLocal->next;
    }
    return NULL;
}

// Similar to FindFirstUnkPrim, but returns the first prim with
// p3 == 0 if there is a prim with p3 == 0 at index positions after
Primitive* FindFirstUnkPrim2(Primitive* prim, u8 index) {
    int i;
    Primitive* primLocal = prim;

    while (primLocal != NULL) {
        if (!primLocal->p3) {
            prim = primLocal;
            for (i = 1; i < index; i++) {
                primLocal = primLocal->next;
                if (!primLocal) {
                    return NULL;
                }

                if (primLocal->p3) {
                    break;
                }
            }

            if (i == index) {
                return prim;
            }
        }
        primLocal = primLocal->next;
    }
    return NULL;
}

Primitive* PrimToggleVisibility(Primitive* prim, s32 count) {
    s32 i;
    u8 isVisible;

    if (prim->p3) {
        prim->p3 = false;
    } else {
        prim->p3 = true;
    }

    for (i = 0; i < count; i++) {
        if (prim->p3) {
            prim->drawMode &= ~DRAW_HIDE;
            isVisible = false;
        } else {
            prim->drawMode |= DRAW_HIDE;
            isVisible = true;
        }

        prim = prim->next;
        if (prim == NULL) {
            // Required for PSP match
            if (true) {
                return NULL;
            }
        }

        prim->p3 = isVisible;
    }

    return prim;
}

void PrimResetNext(Primitive* prim) {
    prim->p1 = 0;
    prim->p2 = 0;
    prim->p3 = 0;
    prim->next->x1 = 0;
    prim->next->y1 = 0;
    prim->next->y0 = 0;
    prim->next->x0 = 0;
    prim->next->clut = 0;
    LOHU(prim->next->u0) = 0;
    LOHU(prim->next->b1) = 0;
    LOHU(prim->next->r1) = 0;
    LOHU(prim->next->u1) = 0;
    prim->next->tpage = 0;
    LOHU(prim->next->r2) = 0;
    LOHU(prim->next->b2) = 0;
    prim->next->u2 = 0;
    prim->next->v2 = 0;
    prim->next->r3 = 0;
    prim->next->b3 = 0;
    prim->next->x2 = 0;
    prim->next->y2 = 0;
}

void UnkPolyFunc2(Primitive* prim) {
    PrimResetNext(prim);
    prim->p3 = 8;
    prim->next->p3 = 1;
    prim->next->type = PRIM_LINE_G2;
    prim->next->drawMode = DRAW_HIDE | DRAW_UNK02;
}

void UnkPolyFunc0(Primitive* prim) {
    prim->p3 = 0;
    prim->drawMode = DRAW_HIDE;
    prim->next->p3 = 0;
    prim->next->type = PRIM_GT4;
    prim->next->drawMode = DRAW_HIDE;
}

#if !defined(VERSION_BETA)
struct SubPrim {
    u8 col[3];
    u8 type;
    s16 x0;
    s16 y0;
    u8 u0;
    u8 v0;
    u16 clut;
};

typedef struct Primitive2 {
    struct Primitive2* next;
#if defined(VERSION_PSP)
    u32 dummy;
#endif
    struct SubPrim prim[4];
} Primitive2;

s32 PrimDecreaseBrightness(Primitive2* prim, u8 amount) {
    s32 isEnd;
    s32 i;
    s32 j;
    struct SubPrim* subprim;
    u8* pColor;
    s32 col;

    isEnd = 0;
    subprim = &prim->prim[0];
    for (i = 0; i < 4; i++) {
        j = 0;
        for (; j < 3; j++) {
            pColor = &subprim->col[j];
            col = *pColor;
            col = col - amount;
            if (col < 0) {
                col = 0;
            } else {
                isEnd |= 1;
            }
            *pColor = col;
        }
        subprim++;
    }
    return isEnd;
}
#else
s32 PrimDecreaseBrightness(Primitive* prim, u8 amount) {
    u8 isEnd;
    s32 i;
    s32 j;
    u8* pColor;

    isEnd = 0;
    pColor = &prim->r0;
    for (i = 0; i < 4; i++, pColor += OFF(Primitive, r1) - OFF(Primitive, r0)) {
        for (j = 0; j < 3; j++) {
            pColor[j] -= amount;

            if (pColor[j] > 248) {
                pColor[j] = 0;
            } else {
                isEnd |= 1;
            }
        }
    }
    return isEnd;
}
#endif
