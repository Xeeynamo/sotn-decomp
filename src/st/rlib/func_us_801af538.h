// SPDX-License-Identifier: AGPL-3.0-or-later

extern EInit g_EInitInteractable;
extern SVECTOR D_us_80180924;
extern SVECTOR D_us_8018092C;

void func_us_801AF538_from_lib(Entity* self) {
    s32 primIndex;
    s16 x;
#ifdef VERSION_PSP
    struct {
        MATRIX matrix;
        VECTOR trans;
        long screenX;
        long screenZ;
        long screenY;
    } geometry;
#else
    struct {
        s32 pad[2];
        VECTOR trans;
        MATRIX matrix;
        s32 screenX;
        s32 screenY;
        s32 screenZ;
    } geometry;
    MATRIX* matrixPtr;
#endif
    Primitive* prim;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = (s16)g_api_AllocPrimitives(PRIM_GT4, 4);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.prim = prim;

            while (prim != NULL) {
                prim->tpage = 0xF;
                prim->clut = 0x34;
                prim->u0 = prim->u2 = 0x80;
                prim->u1 = prim->u3 = 0xF8;
                prim->v0 = prim->v1 = 0;
                prim->v2 = prim->v3 = 0x1C;
                prim->priority = 0x50;
                prim->drawMode = DRAW_UNK02;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
            return;
        }

    case 1:
        SetGeomScreen(0x400);
        SetGeomOffset(0x80, self->posY.i.hi);
#ifdef VERSION_PSP
        RotMatrix(&D_us_8018092C, &geometry.matrix);
        geometry.trans.vx = self->posX.i.hi - 0x80;
        geometry.trans.vy = 0;
        geometry.trans.vz = 0x400;
        TransMatrix(&geometry.matrix, &geometry.trans);
        SetRotMatrix(&geometry.matrix);
        SetTransMatrix(&geometry.matrix);
        RotTransPers(&D_us_80180924, &geometry.screenX, &geometry.screenY,
                     &geometry.screenZ);
        x = (s16)(u16)geometry.screenX;
#else
        matrixPtr = &geometry.matrix;
        RotMatrix(&D_us_8018092C, matrixPtr);
        geometry.trans.vx = self->posX.i.hi - 0x80;
        geometry.trans.vy = 0;
        geometry.trans.vz = 0x400;
        TransMatrix(matrixPtr, &geometry.trans);
        SetRotMatrix(matrixPtr);
        SetTransMatrix(matrixPtr);
        RotTransPers(&D_us_80180924, &geometry.screenX, &geometry.screenY,
                     &geometry.screenZ);
        x = (s16)geometry.screenX;
#endif
        if (x > 0) {
            while (x >= -0x3F) {
                x -= 0x78;
            }
        } else {
            while (x < -0x80) {
                x += 0x78;
            }
        }

        prim = self->ext.prim;
        while (prim != NULL) {
            prim->x0 = prim->x2 = x;
            x += 0x78;
            prim->x1 = prim->x3 = x;
            prim->y0 = prim->y1 = self->posY.i.hi + 0x1C;
            prim->y2 = prim->y3 = self->posY.i.hi;
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
            if (x >= 0x101) {
                break;
            }
        }

        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        return;

    default:
        return;
    }
}
