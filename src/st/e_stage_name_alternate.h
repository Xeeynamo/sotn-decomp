// SPDX-License-Identifier: AGPL-3.0-or-later

void EntityStageNamePopup(Entity* self) {
    s32 p;
    s32 flag;
    SVECTOR rotVector;
    VECTOR transVector;
    MATRIX mtx;
    MATRIX lightMtx;
    CVECTOR color;
    s32 x0x2vals[5];
    s32 x1x3vals[5];
    CVECTOR colors[5];
    s16 z[6];
    Primitive* prim;
    s32 i, j;
    u8 primsSet;
    s32 primIndex;
    s16 nextX1;
    s16 nextY0;
    s16 xStartVal;
    s16* ptr;

#ifdef STAGE_NAME_LOAD_GFX
    if (D_91CE570) {
        LoadStageNameGraphics();
    }
#endif

    switch (self->step) {
    case 0:
        if (g_CastleFlags[STAGE_FLAG]) {
            DestroyEntity(self);
            return;
        } else {
            g_CastleFlags[STAGE_FLAG]++;
            InitializeEntity(g_EInitInteractable);
        }

#ifdef STAGE_NAME_LOAD_GFX
        LoadStageNameGraphics();
#endif
        self->ext.stpopupj.unk8C = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, NUM_PRIMS);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->primIndex = primIndex;
        self->flags |= FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[primIndex];
        self->ext.stpopupj.prim = prim;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        prim = &g_PrimBuf[primIndex];
        for (i = 0; i < 2; i++) {
            prim->tpage = 17;
            prim->clut = 0x19F;
            if (i != 0) {
                prim->clut = 0x19D;
            }
            prim->x2 = prim->x0 = 16;
            prim->y1 = prim->y0 = 157;
            prim->x3 = prim->x1 = 240;
            prim->y3 = prim->y2 = 197;
            prim->u2 = prim->u0 = 0;
            prim->v0 = prim->v1 = 0;
            prim->u1 = prim->u3 = 128;
            prim->v2 = prim->v3 = 39;
            prim->r0 = 120;
            prim->g0 = 120;
            prim->b0 = 168;
            if (i) {
                prim->r0 = prim->b0 = prim->g0 = 0;
            }
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);

            prim->priority = 192 - i;
            prim->drawMode = DRAW_COLORS;
            if (i != 0) {
                prim->drawMode =
                    DRAW_TRANSP | DRAW_TPAGE | DRAW_COLORS | DRAW_HIDE;
            }
            prim = prim->next;
        }
        self->ext.stpopupj.unk84 = prim;
        prim->type = PRIM_G4;
        prim->tpage = 26;
        prim->clut = 0x15F; // Color gradient palette
        prim->u0 = 0;
        prim->u1 = 64;
        prim->u2 = prim->u0;
        prim->u3 = prim->u1;
        prim->v0 = 192;
        prim->v1 = prim->v0;
        prim->v2 = 255;
        prim->v3 = prim->v2;
        prim->x2 = prim->x0 = PRIM_X0_VAL;
        prim->y1 = prim->y0 = 155;
        prim->x3 = prim->x1 = 248;
        prim->y3 = prim->y2 = 199;
        prim->r0 = 16;
        prim->g0 = 40;
        prim->b0 = 0;
        LOW(prim->r1) = LOW(prim->r0);
        prim->r2 = 8;
        prim->g2 = 0;
        prim->b2 = 56;
        LOW(prim->r3) = LOW(prim->r2);
        prim->priority = 176;
        prim->drawMode = DRAW_TRANSP | DRAW_TPAGE | DRAW_COLORS;
        prim = prim->next;
        self->ext.stpopupj.primA4 = prim;
        for (j = 0; j < 2; j++) {
            for (i = 0; i < 4; i++) {
                prim->tpage = 17;
                prim->clut = 0x19F;
                prim->x2 = prim->x0 = 16;
                prim->x3 = prim->x1 = 240;
                prim->y1 = prim->y0 = (i * 10) + 157;
                prim->y3 = prim->y2 = prim->y0 + 10;
                prim->u2 = prim->u0 = 0;
                prim->u1 = prim->u3 = 128;
                prim->v0 = prim->v1 = (i * 8) + (j * 32);
                prim->v2 = prim->v3 = prim->v0 + 8;

                prim->r0 = 120;
                prim->g0 = 120;
                prim->b0 = 168;
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                prim->priority = 192;
                prim->drawMode = DRAW_HIDE | DRAW_COLORS;
                prim = prim->next;
            }
        }
        self->step = 4;
    case 4:
        switch (self->step_s) {
        case 0:
            prim = self->ext.stpopupj.prim;
            prim->drawMode = DRAW_HIDE;
            prim = self->ext.stpopupj.primA4;
            for (i = 0; i < 8; i++) {
                prim->drawMode =
                    DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
                prim = prim->next;
            }
            prim = self->ext.stpopupj.unk84;
            prim->x0 = prim->x2 = 128;
            prim->x1 = prim->x3 = 128;
            prim->y0 = prim->y1 = 177;
            prim->y2 = prim->y3 = 177;
            self->ext.stpopupj.unk94 = 1044;
            self->ext.stpopupj.unkA8 = FLT(-0.75);
            self->ext.stpopupj.unkAA = FLT(-0.75);
            self->ext.stpopupj.unkAC = FLT(-0.75);
            self->ext.stpopupj.unkAE = FLT(-0.75);
            self->ext.stpopupj.unkB0 = FLT(-0.75);
            self->step_s++;
            break;
        case 1:
            primsSet = 0;
            prim = self->ext.stpopupj.unk84;
            if (prim->y0 > 155) {
                prim->y0 -= 4;
                prim->y1 = prim->y0;
                prim->y2 += 4;
                prim->y3 = prim->y2;
                primsSet |= 1;
            }

            if (prim->x0 > PRIM_X0_VAL * 2) {
                prim->x0 -= 8;
                prim->x2 = prim->x0;
                prim->x1 += 8;
                prim->x3 = prim->x1;
                primsSet |= 1;
            }

            if (!primsSet) {
                self->step_s++;
                self->ext.stpopupj.unk80 = 0;
            }
            break;
        case 2:
            if (self->ext.stpopupj.unkB0 < FLT(0.25)) {
                self->ext.stpopupj.unkB0 += 64;
            } else {
                self->ext.stpopupj.unkB0 = FLT(0.25);
            }
            if (self->ext.stpopupj.unkB0 > FLT(-0.625)) {
                if (self->ext.stpopupj.unkAE < 341) {
                    self->ext.stpopupj.unkAE += 62;
                } else {
                    self->ext.stpopupj.unkAE = 341;
                }
            }
            if (self->ext.stpopupj.unkAE > FLT(-0.625)) {
                if (self->ext.stpopupj.unkAC < 0) {
                    self->ext.stpopupj.unkAC += 60;
                } else {
                    self->ext.stpopupj.unkAC = 0;
                }
            }
            if (self->ext.stpopupj.unkAC > FLT(-0.625)) {
                if (self->ext.stpopupj.unkAA < -341) {
                    self->ext.stpopupj.unkAA += 58;
                } else {
                    self->ext.stpopupj.unkAA = -341;
                }
            }
            if (self->ext.stpopupj.unkAA > FLT(-0.625)) {
                if (self->ext.stpopupj.unkA8 < FLT(-0.25)) {
                    self->ext.stpopupj.unkA8 += 56;
                } else {
                    self->ext.stpopupj.unkA8 = FLT(-0.25);
                    self->ext.stpopupj.unk80 = 64;
                    self->step_s++;
                }
            }
            break;
        case 3:
            prim = self->ext.stpopupj.primA4;
            for (j = 0; j < 2; j++) {
                for (i = 0; i < 4; i++) {
                    if (j == 0) {
                        prim->x2 = prim->x0 = 16;
                        prim->x1 = prim->x3 = 128;
                    } else {
                        prim->x0 = prim->x2 = 128;
                        prim->x3 = prim->x1 = 240;
                    }
                    prim->y0 = prim->y1 = (i * 10) + 157;
                    prim->y2 = prim->y3 = (i * 10) + 167;
                    prim = prim->next;
                }
            }

            if (!--self->ext.stpopupj.unk80) {
                ptr = &self->ext.stpopupj.unkA8;
                for (i = 0; i < 5; i++) {
                    *ptr -= 0x2000;
                    ptr++;
                }
                self->step_s++;
            }
            return;
        case 4:
            ptr = &self->ext.stpopupj.unkA8;
            for (i = 0; i < 5; i++) {
                *ptr += 0x50;
                ptr++;
            }
            self->ext.stpopupj.unk94 += 64;
            if (self->ext.stpopupj.unkB0 > 0) {
                prim = self->ext.stpopupj.primA4;
                for (i = 0; i < 8; i++) {
                    prim->drawMode = DRAW_HIDE;
                    prim = prim->next;
                }
                self->step_s++;
            }
            break;
        case 5:
            prim = self->ext.stpopupj.unk84;
            prim->y0 += 2;
            prim->y1 = prim->y0;
            prim->y2 -= 2;
            prim->y3 = prim->y2;
            prim->x0 = prim->x2 += 2;
            prim->x1 = prim->x3 -= 2;
            if (prim->y0 > prim->y2) {
                DestroyEntity(self);
                return;
            }
        }
        prim = self->ext.stpopupj.primA4;
        ptr = &self->ext.stpopupj.unkA8;
        SetGeomScreen(1024);
        transVector.vx = 0;
        transVector.vy = 0;
        transVector.vz = self->ext.stpopupj.unk94;
        TransMatrix(&mtx, &transVector);
        SetTransMatrix(&mtx);
        color.r = 120;
        color.g = 120;
        color.b = 168;
        color.cd = prim->type;
        SetColorMatrix(&D_psp_09254DF0);
        SetBackColor(64, 64, 64);
        SetGeomOffset(128, 177);
        for (i = 0; i < 5; i++) {
            rotVector.vx = *ptr;
            rotVector.vy = 0;
            rotVector.vz = 0;
            RotMatrix(&rotVector, &mtx);
            SetRotMatrix(&mtx);
            RotMatrix(&rotVector, &lightMtx);
            SetLightMatrix(&lightMtx);
            z[i] = RotTransPers(
                &D_psp_09254DD8, (long*)&x0x2vals[i], (long*)&p, (long*)&flag);
            z[i] = RotTransPers(
                &D_psp_09254DE0, (long*)&x1x3vals[i], (long*)&p, (long*)&flag);
            NormalColorCol(&D_psp_09254DE8, &color, &colors[i]);
            ptr++;
        }
        prim = self->ext.stpopupj.primA4;
        for (j = 0; j < 2; j++) {
            ptr = &self->ext.stpopupj.unkA8;
            for (i = 0; i < 4; i++) {
                ptr++;
                if (j == 0) {
                    LOW(prim->x0) = LOW(x0x2vals[i]);
                    LOW(prim->x1) = LOW(x1x3vals[i]);
                    LOW(prim->x2) = LOW(x0x2vals[i + 1]);
                    LOW(prim->x3) = LOW(x1x3vals[i + 1]);
                    prim->x1 = prim->x3 = 128;
                    if (*ptr > 0) {
                        prim->x2 = prim->x0 = 16;
                    }
                } else {
                    LOW(prim->x0) = LOW(x0x2vals[i]);
                    LOW(prim->x1) = LOW(x1x3vals[i]);
                    LOW(prim->x2) = LOW(x0x2vals[i + 1]);
                    LOW(prim->x3) = LOW(x1x3vals[i + 1]);
                    prim->x0 = prim->x2 = 128;
                    if (*ptr > 0) {
                        prim->x3 = prim->x1 = 240;
                    }
                }
                LOW(prim->r0) = LOW(colors[i].r);
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(colors[i + 1].r);
                LOW(prim->r3) = LOW(prim->r2);
                prim = prim->next;
            }
        }
    }
}
