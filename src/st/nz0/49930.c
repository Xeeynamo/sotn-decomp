#include "nz0.h"

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/49930", func_801C9930);

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

void func_801CA0D0(Primitive* poly) {
    poly->p3 = 0;
    poly->blendMode = BLEND_VISIBLE;
    poly->next->p3 = 0;
    poly->next->type = 4;
    poly->next->blendMode = BLEND_VISIBLE;
}

#include "../unk_loop_func.h"

// particle effect that spawns life up item
// Probably it's own file
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/49930", EntityLifeUpSpawn);
