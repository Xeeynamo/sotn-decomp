#include "st0.h"

void func_801AF774(Entity* self) {
    RECT sp10;
    DRAWENV sp18;
    DRAWENV* var_a2;
    DRAWENV* var_a3;
    Primitive* prim;
    s32 primIndex;
    s32 i;
    u32 var_t0;
    u8 temp_t0;
    u8* var_a2_3;
    s16* temp_a3;
    s32 xBase;
    s32 yBase;
    inline s32 add(a, b) { return a + b; }

    switch (self->step) {
    case 0:
        InitializeEntity(D_801805E0);
        self->hitboxState = 0;
        self->animCurFrame = 0;
        self->drawMode |= (DRAW_TPAGE | 0x20);
        self->flags &= ~FLAG_UNK_08000000;
        D_801C2578 = 1;
        self->ext.aguneaCrash.unk8B[5] = 1;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x5C);
        if (primIndex != -1) {
            prim = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
            self->ext.et_801AF774.prim3 = prim;
            self->flags |= FLAG_HAS_PRIMS;
            prim->tpage = 0x110;
            if (!self->facingLeft) {
                prim->u0 = prim->u2 = 0;
                prim->u1 = prim->u3 = 0x80;
                prim->v0 = prim->v1 = 0;
                prim->v2 = prim->v3 = 0x80;
            } else {
                prim->u1 = prim->u3 = 0;
                do {
                    prim->u0 = prim->u2 = 0x7F;
                    prim->v0 = prim->v1 = 0;
                    prim->v2 = prim->v3 = 0x80;
                } while (0);
            }

            prim->x0 = prim->x2 = self->posX.i.hi - 0x40;
            prim->x1 = prim->x3 = self->posX.i.hi + 0x40;
            prim->y0 = prim->y1 = self->posY.i.hi - 0x25;
            prim->y2 = prim->y3 = self->posY.i.hi + 0x5B;
            prim->r0 = prim->g0 = prim->b0 = 0x80;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->drawMode = DRAW_UNK02 | DRAW_HIDE;
            prim->priority = 0xA8;
            prim = prim->next;
            self->ext.et_801AF774.prim4 = prim;
            if (g_api.func_800EDB08(prim) == NULL) {
                g_api.FreePrimitives(primIndex);
                self->step = 0;
                self->flags &= ~FLAG_HAS_PRIMS;
                return;
            }
            prim->type = PRIM_ENV;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            g_api.func_800EDB08(prim);
            if (prim == NULL) {
                g_api.FreePrimitives(primIndex);
                self->step = 0;
                self->flags &= ~FLAG_HAS_PRIMS;
                return;
            }
            prim->type = PRIM_ENV;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            self->ext.prim = prim;
            while (prim != NULL) {
                prim->priority = 0xA0;
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
                var_a3 = &sp18;
            }
        } else {
            self->step = 0;
            FntPrint("can't get effect works!\n");
            return;
        }
    case 1:
        var_a3 = &sp18;
        prim = self->ext.et_801AF774.prim4;
        var_a2 = &g_CurrentBuffer->draw;
        *var_a3 = *var_a2;
        sp18.isbg = 1;
        sp18.r0 = 0;
        sp18.g0 = 0;
        sp18.b0 = 0;
        sp10.x = 0;
        sp10.y = 0x100;
        sp10.w = 0x7f;
        sp10.h = 0xff;
        sp18.clip = sp10;
        sp18.ofs[0] = 0;
        sp18.ofs[1] = 0x100;
        SetDrawEnv(LOW(prim->r1), &sp18);
        prim->priority = 0x9F;
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        prim->priority = 0xA1;
        prim->drawMode = DRAW_UNK_800;
    case 6:
        self->step++;
        return;

    case 2:
        func_801AF380();
        var_a3 = &sp18;
        prim = self->ext.et_801AF774.prim4;
        var_a2 = &g_CurrentBuffer->draw;
        var_t0 = LOW(prim->r1);
        *var_a3 = *var_a2;
        sp18.isbg = 0;
        sp18.dtd = 0;
        sp10.x = 0;
        sp10.y = 0x100;
        sp10.w = 0x80;
        sp10.h = 0x80;
        sp18.clip = sp10;
        sp18.ofs[0] = 0;
        sp18.ofs[1] = 0x100;
        SetDrawEnv(var_t0, &sp18);
        prim->priority = 0x9F;
        prim->drawMode = 0;
        prim = prim->next;
        prim->priority = 0xA1;
        prim->drawMode = DRAW_UNK_800;
        self->ext.et_801AF774.unk8E = 0x80;
        self->ext.et_801AF774.unk8C = 0x8000;
        self->step_s = 0;
        self->step++;
        return;
    case 3:
        prim = self->ext.et_801AF774.prim3;
        prim->drawMode =
            DRAW_TPAGE | 0x20 | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        if (self->ext.et_801AF774.unk8E > 0) {
            func_801AF6D0();
        }
        var_t0 = (u16)self->ext.et_801AF774.unk8C >> 8;
        if (var_t0 >= 0x81) {
            var_t0 = 0x80;
        }
        var_t0 = (u8)var_t0 >> 3;
        prim = self->ext.prim;
        xBase = 0x40;
        yBase = 0x70;
        temp_a3 = &D_801BEB64;
        var_a2_3 = &D_801813E8;

        for (i = 0; i < 47; i++) {
            prim->x0 = add(xBase, temp_a3[*var_a2_3 * 4 + 1]);
            prim->y0 = add(yBase, temp_a3[*var_a2_3 * 4 + 3]);
            var_a2_3++;
            prim->x1 = add(xBase, temp_a3[*var_a2_3 * 4 + 1]);
            prim->y1 = add(yBase, temp_a3[*var_a2_3 * 4 + 3]);
            var_a2_3++;
            prim->x2 = add(xBase, temp_a3[*var_a2_3 * 4 + 1]);
            prim->y2 = add(yBase, temp_a3[*var_a2_3 * 4 + 3]);
            var_a2_3++;
            prim->x3 = add(xBase, temp_a3[*var_a2_3 * 4 + 1]);
            prim->y3 = add(yBase, temp_a3[*var_a2_3 * 4 + 3]);
            var_a2_3++;
            prim->b0 = var_t0;
            prim->g0 = var_t0;
            prim->r0 = var_t0;

            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim = prim->next;
        }
        var_t0 = (u16)self->ext.et_801AF774.unk8C >> 8;
        if (var_t0 >= 0x81U) {
            var_t0 = 0x80;
        }
        var_t0 = (0x80 - var_t0);
        temp_t0 = var_t0;
        temp_t0 >>= 3;
        prim = self->ext.et_801AF774.prim2;
        temp_a3 = &D_801BEB64;
        var_a2_3 = &D_801814A8;
        xBase = 0x40;
        yBase = 0x70;
        for (i = 0; i < 42; i++) {
            prim->x0 = add(xBase, temp_a3[*var_a2_3 * 4 + 1]);
            prim->y0 = add(yBase, temp_a3[*var_a2_3 * 4 + 3]);
            var_a2_3++;
            prim->x1 = add(xBase, temp_a3[*var_a2_3 * 4 + 1]);
            prim->y1 = add(yBase, temp_a3[*var_a2_3 * 4 + 3]);
            var_a2_3++;
            prim->x2 = add(xBase, temp_a3[*var_a2_3 * 4 + 1]);
            prim->y2 = add(yBase, temp_a3[*var_a2_3 * 4 + 3]);
            var_a2_3++;
            prim->x3 = add(xBase, temp_a3[*var_a2_3 * 4 + 1]);
            prim->y3 = add(yBase, temp_a3[*var_a2_3 * 4 + 3]);
            var_a2_3++;

            prim->r0 = prim->g0 = prim->b0 = temp_t0;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim = prim->next;
        }
        self->ext.et_801AF774.unk8C =
            ((--self->ext.et_801AF774.unk8E << 0x10) >> 8);
        if (self->ext.et_801AF774.unk8E < 0) {
            self->step = 4;
        }
        if ((self->ext.aguneaCrash.unk8B[5] != 0) &&
            (self->ext.et_801AF774.unk8E < 0x10)) {
            self->ext.aguneaCrash.unk8B[5] = 0;
            CreateEntityFromCurrentEntity(0x23, self + 1);
        }
        return;
    case 4:
        prim = self->ext.et_801AF774.prim3;
        prim->drawMode =
            DRAW_TPAGE | 0x20 | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim = prim->next;
        D_801C2578 = 0;
        if (prim != NULL) {
            do {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            } while (prim != NULL);
        }
        self->ext.et_801AF774.unk8E = 0x10;
        self->step++;
        return;
    case 5:
        if (--self->ext.et_801AF774.unk8E == 0) {
            self->step++;
            return;
        }
        break;
    case 7:
        if (PrimDecreaseBrightness(self->ext.et_801AF774.prim3, 7) == 0) {
            D_80180910 = 1;
            DestroyEntity(self);
        }
        break;
    }
}
