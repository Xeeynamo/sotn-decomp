#include "wrp.h"

void EntityUnkId0E(Entity* self) {
    RECT rect;
    u16 xOffset;
    u8* chPix;
    u8* dstPix;
    u8* str;
    Primitive* prim;
    s16 primIndex;
    s32 i;
    u8 ch;

    switch (self->step) {
    case 0:
        InitializeEntity(g_InitializeData0);
        self->flags = (self->flags | FLAG_UNK_10000) ^ FLAG_UNK_08000000;
        if (self->params == 0) {
            self->params = 0x60;
        }
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 3);
        if (primIndex == -1) {
            self->step = 0;
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->flags |= FLAG_HAS_PRIMS;

        while (prim != NULL) {
            prim->blendMode = BLEND_VISIBLE;
            prim = prim->next;
        }

        str = self->ext.unk0e.label;
        self->ext.unk0e.width = *str++;
        self->ext.unk0e.height = *str++;
        self->ext.unk0e.label += 2;
        return;

    case 1:
        rect.x = 0;
        rect.y = 0x180;
        rect.w = 0x40;
        rect.h = self->ext.unk0e.height;
        ClearImage(&rect, 0, 0, 0);

        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; prim != NULL; prim = prim->next, i++) {
            if (i == 0) {
                prim->type = PRIM_SPRT;
                prim->tpage = 0x10;
                prim->x0 = self->posX.i.hi - self->ext.unk0e.width / 2;
                prim->y0 = self->posY.i.hi - self->ext.unk0e.height / 2;
                prim->u0 = 0;
                prim->v0 = 0x80;
                prim->u1 = self->ext.unk0e.width;
                prim->v1 = self->ext.unk0e.height;
                prim->clut = 0x1A1;
                prim->priority = 0x1FD;
                prim->blendMode = BLEND_VISIBLE;
            } else {
                prim->type = PRIM_G4;
                prim->x0 = prim->x2 =
                    self->posX.i.hi - self->ext.unk0e.width / 2 - 4;
                prim->x1 = prim->x3 =
                    self->posX.i.hi + self->ext.unk0e.width / 2 + 4;
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0;
                prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0;
                prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0;
                if (i == 1) {
                    prim->y0 = prim->y1 = prim->y2 = prim->y3 =
                        self->posY.i.hi - self->ext.unk0e.height / 2 - 4;
                    prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0x80;
                } else {
                    prim->y0 = prim->y1 = prim->y2 = prim->y3 =
                        self->posY.i.hi + self->ext.unk0e.height / 2 + 4;
                    prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0x80;
                }
                prim->priority = 0x1FC;
                prim->blendMode = 0x11;
            }
        }

        self->step++;
        break;

    case 2:
        dstPix = &D_8007EFE4;
        chPix = dstPix;
        str = self->ext.unk0e.label;
        xOffset = 0;
        for (i = 0; i < self->ext.unk0e.width / 2 * self->ext.unk0e.height;
             i++) {
            *chPix++ = 0;
        }

        chPix = dstPix;
        while (true) {
            if (*str == 0) {
                break;
            }
            if (*str == 1) {
                str++;
                xOffset = 0;
                chPix = &dstPix[self->ext.unk0e.width * 8];
            } else {
                str = BlitChar(str, &xOffset, chPix, self->ext.unk0e.width / 2);
            }
        }

        LoadTPage(dstPix, 0, 0, 0, 0x180, self->ext.unk0e.width,
                  self->ext.unk0e.height);
        self->ext.unk0e.duration = 0;
        self->step++;
        break;

    case 3:
        self->ext.unk0e.duration++;
        prim = g_PrimBuf[self->primIndex].next;
        for (i = 0; prim != NULL; prim = prim->next, i++) {
            if (i == 0) {
                prim->y2 = prim->y3 =
                    prim->y0 +
                    (self->ext.unk0e.height + 8) * self->ext.unk0e.duration / 8;
                prim->b0 = prim->b1 = prim->b1 - 0x10;
            } else {
                prim->y0 = prim->y1 =
                    prim->y2 -
                    (self->ext.unk0e.height + 8) * self->ext.unk0e.duration / 8;
                prim->g2 = prim->g3 = prim->g3 - 0x10;
            }
        }
        if (self->ext.unk0e.duration == 8) {
            self->ext.unk0e.duration = 0;
            self->step++;
        }
        break;

    case 4:
        D_8008701E[self->primIndex * 0x1A] = 0;
        self->ext.unk0e.duration++;
        if (self->ext.unk0e.duration > self->params) {
            DestroyEntity(self);
        }
        break;
    }
}
