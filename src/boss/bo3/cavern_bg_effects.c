// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo3.h"

extern u16 g_EInitInteractable;
extern u8 D_us_8018080C[];
extern u8 D_us_80180824[];
extern s16 D_us_80180830[];

void func_us_801C12B0_from_no4(Entity* self) {
    u32 var_s8;
    s16* ptr;
    s32 var_s6;
    u8* var_s5;
    s32 var_s4;
    s32 var_s3;
    s32 var_s2;
    s32 var_s1;

    Primitive* prim;
    s32 primIndex;
    s32 scrollX;
    s32 scrollY;
    s32 i;
    s32 xOffset;
    s32 sp38;

    switch (self->step) {
    case 0:
        InitializeEntity(&g_EInitInteractable);
        self->animSet = 0;
        self->ext.et_801C12B0.unk80 = 4;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 16);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C12B0.prim = prim;
        self->ext.et_801C12B0.unk82 = 0;
        while (prim != NULL) {
            prim->tpage = 0xF;
            prim->clut = 0x5E;
            prim->priority = 0x9C;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        break;
    }

    prim = self->ext.et_801C12B0.prim;
    AnimateEntity(D_us_80180824, self);
    i = (self->params >> 8) & 0xFF;
    ptr = &D_us_80180830[(self->params & 0xFF) * 5];
    scrollX = g_Tilemap.scrollX.i.hi - 0x10;
    scrollY = g_Tilemap.scrollY.i.hi;
    xOffset = scrollX + 0x120;
    var_s5 = &D_us_8018080C[self->animCurFrame * 4];
    var_s8 = var_s5[1];

    for (; i > 0; i--) {
        var_s3 = *ptr++;
        var_s2 = var_s3 + *ptr++;
        if (scrollX >= var_s2 || xOffset < var_s3) {
            ptr += 3;
            continue;
        }

        var_s6 = *ptr++;
        if (scrollY - 4 > var_s6 || var_s6 > scrollY + 0xE0) {
            ptr += 2;
            continue;
        } else {
            ptr++;
            sp38 = *ptr++;
            var_s6 -= scrollY;
            if (var_s3 < scrollX) {
                var_s3 = scrollX;
            }
            if (xOffset < var_s2) {
                var_s2 = xOffset;
            }
            if (sp38 != 0) {
                self->ext.et_801C12B0.unk82 += sp38;
                var_s4 = (u32)(var_s3 - self->ext.et_801C12B0.unk82) % 126;
            } else {
                var_s4 = (u32)var_s3 % 126;
            }
            var_s2 -= var_s3;
            var_s3 -= scrollX + 0x10;
            var_s4 += var_s5[0];

            do {
                prim->u0 = prim->u2 = var_s4;
                var_s1 = 0x7E - (var_s4 - var_s5[0]);
                if (var_s2 < var_s1) {
                    var_s1 = var_s2;
                }
                prim->u1 = prim->u3 = var_s4 + var_s1;
                prim->v0 = prim->v1 = var_s8;
                prim->v2 = prim->v3 = var_s8 + 1;
                prim->x0 = prim->x2 = var_s3;
                var_s3 += var_s1;
                prim->x1 = prim->x3 = var_s3;
                var_s2 -= var_s1;
                var_s4 = var_s5[0];
                prim->y0 = prim->y1 = var_s6;
                prim->y2 = prim->y3 = var_s6 + 1;
                prim->drawMode = DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
                prim = prim->next;
            } while (var_s2 != 0);
        }
    }

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

INCLUDE_ASM("boss/bo3/nonmatchings/cavern_bg_effects", func_us_801C15F8_from_no4);

INCLUDE_ASM("boss/bo3/nonmatchings/cavern_bg_effects", func_us_801C1844_from_no4);

INCLUDE_ASM("boss/bo3/nonmatchings/cavern_bg_effects", EntityBgColumnsParallax_from_no4);

INCLUDE_ASM("boss/bo3/nonmatchings/cavern_bg_effects", func_us_801C1EE4_from_no4);

INCLUDE_ASM("boss/bo3/nonmatchings/cavern_bg_effects", func_us_801C21AC_from_no4);

INCLUDE_ASM("boss/bo3/nonmatchings/cavern_bg_effects", func_us_8019E398);

INCLUDE_ASM("boss/bo3/nonmatchings/cavern_bg_effects", func_us_801C2850_from_no4);

INCLUDE_ASM("boss/bo3/nonmatchings/cavern_bg_effects", func_us_801C2B78_from_no4);

INCLUDE_ASM("boss/bo3/nonmatchings/cavern_bg_effects", func_us_801C2E60_from_no4);

INCLUDE_ASM("boss/bo3/nonmatchings/cavern_bg_effects", func_us_8019F03C);

INCLUDE_ASM("boss/bo3/nonmatchings/cavern_bg_effects", func_us_801C34EC_from_no4);

INCLUDE_ASM("boss/bo3/nonmatchings/cavern_bg_effects", func_us_801C37C8_from_no4);

INCLUDE_ASM("boss/bo3/nonmatchings/cavern_bg_effects", func_us_801C3A04_from_no4);

INCLUDE_ASM("boss/bo3/nonmatchings/cavern_bg_effects", func_us_801C3CC4_from_no4);

INCLUDE_ASM("boss/bo3/nonmatchings/cavern_bg_effects", func_us_801C3FB0_from_no4);

INCLUDE_ASM("boss/bo3/nonmatchings/cavern_bg_effects", func_us_801C4228_from_no4);

INCLUDE_ASM("boss/bo3/nonmatchings/cavern_bg_effects", EntityWaterBox);

INCLUDE_ASM("boss/bo3/nonmatchings/cavern_bg_effects", func_us_801A051C);

INCLUDE_ASM("boss/bo3/nonmatchings/cavern_bg_effects", func_us_801A069C);
