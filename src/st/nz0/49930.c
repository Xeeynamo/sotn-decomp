#include "nz0.h"

void func_801C9930(Primitive* arg0) {
    SVECTOR sp10; // FAKE, not really an svector
    SVECTOR stackpad;
    SVECTOR sp20;
    VECTOR sp28;
    SVECTOR sp38;
    SVECTOR sp40;
    SVECTOR sp48;
    SVECTOR sp50;
    MATRIX sp58;
    SVECTOR sp78;
    u16 temp_a0;
    u8 temp_v1_2;

    sp78 = D_801B0934;
    if (arg0->p3 & 8) {
        // Fake logic here, sp10 is not an SVECTOR but it matches.
        // tried using an f32 but couldn't get it to work.
        sp10.vy = arg0->next->x1;
        sp10.vx = arg0->next->y1;
        LOW(sp10.vx) += LOW(arg0->next->u0);
        arg0->next->x1 = sp10.vy;
        arg0->next->y1 = sp10.vx;
        LOW(arg0->next->x0) += LOW(arg0->next->r1);
    }
    temp_v1_2 = arg0->next->b3;
    LOH(arg0->r0) = LOH(arg0->r1) = LOH(arg0->r2) = LOH(arg0->r3) =
        temp_v1_2 | (temp_v1_2 << 8);
    arg0->b0 = arg0->b1 = arg0->b2 = arg0->b3 = temp_v1_2;
    sp28.vx = 0;
    sp28.vy = 0;
    sp28.vz = 0x400 - LOH(arg0->next->u1);
    RotMatrix(&sp78, &sp58);
    if (arg0->p3 & 0x20) {
        sp20.vx = arg0->next->x3;
        sp20.vy = arg0->next->y3;
        RotMatrixX(sp20.vx, &sp58);
        RotMatrixY(sp20.vy, &sp58);
    }
    sp20.vz = arg0->next->tpage;
    RotMatrixZ(sp20.vz, &sp58);
    TransMatrix(&sp58, &sp28);
    if (arg0->p3 & 0x10) {
        sp28.vx = (s32)arg0->next->x2;
        sp28.vy = (s32)arg0->next->y2;
        sp28.vz = 0x1000;
        ScaleMatrix(&sp58, &sp28.vx);
    }
    SetRotMatrix(&sp58);
    SetTransMatrix(&sp58);
    SetGeomScreen(0x400);
    SetGeomOffset(arg0->next->x1, arg0->next->y0);
    sp38.vx = -LOH(arg0->next->r2) / 2;
    sp38.vy = -LOH(arg0->next->b2) / 2;
    sp38.vz = 0;
    sp40.vx = LOH(arg0->next->r2) / 2;
    sp40.vy = -LOH(arg0->next->b2) / 2;
    sp40.vz = 0;
    sp48.vx = -LOH(arg0->next->r2) / 2;
    sp48.vy = LOH(arg0->next->b2) / 2;
    sp48.vz = 0;
    sp50.vx = LOH(arg0->next->r2) / 2;
    sp50.vy = LOH(arg0->next->b2) / 2;
    sp50.vz = 0;
    gte_ldv0(&sp38);
    gte_rtps();
    gte_stsxy(&arg0->x0);
    gte_ldv0(&sp40);
    gte_rtps();
    gte_stsxy(&arg0->x1);
    gte_ldv0(&sp48);
    gte_rtps();
    gte_stsxy(&arg0->x2);
    gte_ldv0(&sp50);
    gte_rtps();
    gte_stsxy(&arg0->x3);
}

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/49930", func_801C9D18);

Primitive* func_801C9E68(Primitive* poly) {
    while (poly != NULL) {
        if (poly->p3 != 0) {
            poly = poly->next;
        } else {
            return poly;
        }
    }
    return NULL;
}

Primitive* func_801C9E98(Primitive* prim, u8 index) {
    if (prim) {
        s32 index_ = index;
    loop_2:
        if (prim->p3 == 0) {
            Primitive* var_v0 = NULL;
            Primitive* firstPrim = prim;
            s32 i = 1;
            if (i < index_) {
                do {
                    prim = prim->next;
                    if (!prim)
                        return NULL;
                } while (prim->p3 == 0 && ++i < index);
            }
            var_v0 = firstPrim;
            if (i == index_)
                return var_v0;
        }
        prim = prim->next;
        if (prim) {
            goto loop_2;
        }
    }
    return NULL;
}

Primitive* func_801C9F14(Primitive* startPoly, s32 count) {
    Primitive* poly;
    s8 unk;
    s32 i;

    if (startPoly->p3) {
        startPoly->p3 = 0;
    } else {
        startPoly->p3 = 1;
    }
    poly = startPoly;

    for (i = 0; i < count; i++) {
        if (poly->p3) {
            poly->blendMode &= ~8;
            unk = 0;
        } else {
            poly->blendMode |= 8;
            unk = 1;
        }

        poly = poly->next;
        if (poly == NULL) {
            return NULL;
        }
        poly->p3 = unk;
    }

    return poly;
}

void func_801C9F9C(Primitive* poly) {
    poly->p1 = 0;
    poly->p2 = 0;
    poly->p3 = 0;
    poly->next->x1 = 0;
    poly->next->y1 = 0;
    poly->next->y0 = 0;
    poly->next->x0 = 0;
    poly->next->clut = 0;
    *(u16*)&poly->next->u0 = 0;
    *(u16*)&poly->next->b1 = 0;
    *(u16*)&poly->next->r1 = 0;
    *(u16*)&poly->next->u1 = 0;
    poly->next->tpage = 0;
    *(u16*)&poly->next->r2 = 0;
    *(u16*)&poly->next->b2 = 0;
    poly->next->u2 = 0;
    poly->next->v2 = 0;
    poly->next->r3 = 0;
    poly->next->b3 = 0;
    poly->next->x2 = 0;
    poly->next->y2 = 0;
}

void func_801CA07C(Primitive* poly) {
    func_801C9F9C(poly);
    poly->p3 = 8;
    poly->next->p3 = 1;
    poly->next->type = 2;
    poly->next->blendMode = 0xA;
}

#include "../unk_poly_func_0.h"

#include "../unk_loop_func.h"

// particle effect that spawns life up item
// Probably it's own file
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/49930", EntityLifeUpSpawn);
