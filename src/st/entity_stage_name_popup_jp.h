// SPDX-License-Identifier: AGPL-3.0-or-later
void EntityStageNamePopup(Entity* self) {
    u8 padding[0xD8];
    Primitive* prim;
    u8 var_s6;
    s16 primIndex;
    s16 var_s4;
    s16 var_s3;
    s16 var_s2;
    s32 i;

    switch (self->step) {
    case 0:
        if (g_CastleFlags[CASTLE_FLAG_2]) {
            DestroyEntity(self);
            return;
        }

        InitializeEntity(g_EInitInteractable);
        self->ext.stpopupj.unk8C = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 181);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->primIndex = primIndex;
        self->flags |= FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[primIndex];
        self->ext.stpopupj.prim = prim;
        for (i = 0; i < 2; i++) {
            prim->tpage = 0x11;
            prim->clut = 0x19F;
            if (i) {
                prim->clut = 0x19D;
            }
            prim->x2 = prim->x0 = 0x40;
            prim->y1 = prim->y0 = 0x9D;
            prim->x3 = prim->x1 = 0xC0;
            prim->y3 = prim->y2 = 0xC4;
            prim->u2 = prim->u0 = 0;
            prim->v0 = prim->v1 = 0;
            prim->u1 = prim->u3 = 0x80;
            prim->v2 = prim->v3 = 0x27;
            prim->r0 = 0x78;
            prim->g0 = 0x78;
            prim->b0 = 0xa8;
            if (i) {
                prim->r0 = prim->b0 = prim->g0 = 0;
            }
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);

            prim->priority = 0xC0 - i;
            prim->drawMode = DRAW_COLORS;
            if (i) {
                prim->drawMode =
                    DRAW_TRANSP | DRAW_TPAGE | DRAW_COLORS | DRAW_HIDE;
            }
            prim = prim->next;
        }

        self->ext.stpopupj.unk88 = prim;
        UnkPolyFunc2(prim);
        prim->tpage = 0x1A;
        prim->clut = 0x19E;
        prim->u0 = 0;
        prim->u1 = 0x10;
        prim->u2 = prim->u0;
        prim->u3 = prim->u1;
        prim->v0 = 0x40;
        prim->v1 = prim->v0;
        prim->v2 = 0x50;
        prim->v3 = prim->v2;
        LOH(prim->next->r2) = 0xE;
        LOH(prim->next->b2) = 0xE;
        prim->next->b3 = 0x80;
        prim->priority = 0xC0;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        prim = prim->next;
        self->ext.stpopupj.unk84 = prim;
        prim->type = PRIM_G4;
        prim->tpage = 0x1A;
        prim->clut = 0x15F;
        prim->u0 = 0;
        prim->u1 = 0x40;
        prim->u2 = prim->u0;
        prim->u3 = prim->u1;
        prim->v0 = 0xC0;
        prim->v1 = prim->v0;
        prim->v2 = 0xFF;
        prim->v3 = prim->v2;
        prim->x2 = prim->x0 = 8;
        prim->y1 = prim->y0 = 0x9B;
        prim->x3 = prim->x1 = 0xF8;
        prim->y3 = prim->y2 = 0xC6;
        prim->r0 = 0x10;
        prim->g0 = 0x28;
        prim->b0 = 0;
        LOW(prim->r1) = LOW(prim->r0);
        prim->r2 = 8;
        prim->g2 = 0;
        prim->b2 = 0x38;
        LOW(prim->r3) = LOW(prim->r2);
        prim->priority = 0xB0;
        prim->drawMode = DRAW_TRANSP | DRAW_TPAGE | DRAW_COLORS;
        prim = prim->next;
        self->step = 1;
    case 1:
        switch (self->step_s) {
        case 0:
            prim = self->ext.stpopupj.prim;
            for (i = 0; i < 2; i++) {
                prim->u0 = prim->u2 = 0x80;
                prim->v0 = prim->v1 = 0x14;
                prim->v2 = prim->v3 = prim->v0 + 2;
                prim->x3 = prim->x1 = i * 3 + 0xC0;
                prim->x0 = prim->x2 = i * 3 + 0xC0;
                prim->y1 = prim->y0 = i * 2 + 0xB1;
                prim->y3 = prim->y2 = prim->y0 + 2;
                prim = prim->next;
            }
            prim = self->ext.stpopupj.unk84;
            prim->x0 = prim->x2 = 0x80;
            prim->x1 = prim->x3 = 0x80;
            prim->y0 = prim->y1 = 0xB0;
            prim->y2 = prim->y3 = 0xB0;
            self->step_s++;
        case 1:
            var_s6 = 0;
            prim = self->ext.stpopupj.unk84;
            if (prim->y0 >= 0x9C) {
                prim->y0 -= 4;
                prim->y1 = prim->y0;
                prim->y2 += 4;
                prim->y3 = prim->y2;
                var_s6 |= 1;
            }
            if (prim->x0 >= 0x11) {
                prim->x0 -= 8;
                prim->x2 = prim->x0;
                prim->x1 += 8;
                prim->x3 = prim->x1;
                var_s6 |= 1;
            }
            if (!var_s6) {
                self->step_s++;
                prim = self->ext.stpopupj.prim;
                prim = prim->next;
                prim->drawMode = DRAW_TRANSP | DRAW_TPAGE | DRAW_COLORS;
                prim = self->ext.stpopupj.unk88;
                prim->drawMode =
                    DRAW_TRANSP | DRAW_TPAGE | DRAW_TPAGE2 | DRAW_COLORS;
            }
            break;
        case 2:
            prim = self->ext.stpopupj.prim;
            for (i = 0; i < 2; i++) {
                prim->u0 -= 8;
                prim->u2 = prim->u0;
                prim->x0 -= 8;
                prim->x2 = prim->x0;
                var_s4 = prim->x0;
                var_s3 = prim->y0;
                prim = prim->next;
            }
            prim = self->ext.stpopupj.unk88;
            prim->next->x1 = var_s4;
            prim->next->y0 = var_s3;
            LOH(prim->next->tpage) -= 0x80;
            UnkPrimHelper(prim);
            prim = self->ext.stpopupj.prim;
            if (!prim->u0) {
                self->step_s = 3;
            }
            break;
        case 3:
            PrimDecreaseBrightness(self->ext.stpopupj.unk88, 4);
            if (!(g_Timer % 2)) {
                prim = self->ext.stpopupj.prim;
                for (i = 0; i < 2; i++) {
                    if (prim->y0 > i * 2 + 0x9D) {
                        prim->v0--;
                        prim->v1 = prim->v0;
                        prim->y0--;
                        prim->y1 = prim->y0;
                    } else {
                        self->step_s = 4;
                    }
                    if (prim->y2 < i * 2 + 0xC4) {
                        prim->v2++;
                        prim->v3 = prim->v2;
                        prim->y2++;
                        prim->y3 = prim->y2;
                    }
                    prim = prim->next;
                }
            }
            break;
        case 4:
            self->step = 0x20;
            self->ext.stpopupj.unk80 = 0x20;
            break;
        }
        break;
    case 18:
        if (self->step_s != 0) {
            return;
        }
        prim = self->ext.stpopupj.unk84;
        prim->x1 -= 4;
        var_s2 = prim->x3 = prim->x1;
        prim = self->ext.stpopupj.prim;
        for (i = 0; i < 2; i++) {
            if (prim->x1 > var_s2) {
                prim->x1 -= 4;
                prim->x3 = prim->x1;
                if (prim->x1 < prim->x0) {
                    prim->drawMode = DRAW_HIDE;
                }
                prim->u1 -= 4;
                prim->u3 = prim->u1;
            }
            prim = prim->next;
        }
        prim = self->ext.stpopupj.unk84;
        if (prim->x0 > prim->x1) {
            DestroyEntity(self);
            return;
        }
        break;
    case 32:
        if (!--self->ext.stpopupj.unk80) {
            g_CastleFlags[CASTLE_FLAG_2] = 1;
            self->step_s = 0;
            self->step = 0x12;
        }
        break;
    }
}
