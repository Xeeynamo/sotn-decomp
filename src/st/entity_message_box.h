// SPDX-License-Identifier: AGPL-3.0-or-later

// params: message box duration
// ext.messageBox.label: box size and text to render
void EntityMessageBox(Entity* self) {
    const u16 VramX = 0;
    const u16 VramY = 0x180;
    const int FontW = 12;
    const int FontH = 16;
    const int FontLen = FontW * FontH / 2 / sizeof(u16); // 4bpp

    Primitive* prim;
    s32 i;
    char* str;
    s32 primIndex;
    u16 xOffset;
    u8* chPix;
    u8* dstPix;
    u8 ch;
    RECT rect;

    u16 x;
    u16 y;
    u16 nCh;

    u16 chjp;
    u16* srcJpPix;
    u16* dstJpPix;

    switch (self->step) {
    case 0:
        InitializeEntity(g_InitializeData0);
        self->flags |= FLAG_UNK_10000;
        self->flags ^= FLAG_POS_CAMERA_LOCKED;
        if (!self->params) {
            self->params = 96; // default to 96 frames, or 1.5 seconds
        }

        primIndex = g_api.AllocPrimitives(PRIM_GT4, 3);
        if (primIndex == -1) {
            self->step = 0;
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }

        str = self->ext.messageBox.label;
        self->ext.messageBox.width = *str++;
        self->ext.messageBox.height = *str++;
        self->ext.messageBox.label += 2;
        break;
    case 1:
        rect.x = 0;
        rect.y = 0x180;
        rect.w = 64;
        rect.h = self->ext.messageBox.height;
        ClearImage(&rect, 0, 0, 0);

        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; prim != NULL; prim = prim->next, i++) {
            if (i == 0) {
                prim->type = PRIM_SPRT;
                prim->tpage = 0x10;
                prim->x0 = self->posX.i.hi - self->ext.messageBox.width / 2;
                prim->y0 = self->posY.i.hi - self->ext.messageBox.height / 2;
                prim->u0 = 0;
                prim->v0 = 0x80;
                prim->u1 = self->ext.messageBox.width;
                prim->v1 = self->ext.messageBox.height;
                prim->clut = 0x1A1;
                prim->priority = 0x1FD;
                prim->drawMode = DRAW_HIDE;
            } else {
                prim->type = PRIM_G4;
                prim->x0 = prim->x2 =
                    self->posX.i.hi - self->ext.messageBox.width / 2 - 4;
                prim->x1 = prim->x3 =
                    self->posX.i.hi + self->ext.messageBox.width / 2 + 4;
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0;
                prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0;
                prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0;
                if (i == 1) {
                    prim->y0 = prim->y1 = prim->y2 = prim->y3 =
                        self->posY.i.hi - self->ext.messageBox.height / 2 - 4;
                    prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0x80;
                } else {
                    prim->y0 = prim->y1 = prim->y2 = prim->y3 =
                        self->posY.i.hi + self->ext.messageBox.height / 2 + 4;
                    prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0x80;
                }
                prim->priority = 0x1FC;
                prim->drawMode = DRAW_TPAGE | DRAW_TRANSP;
            }
        }
        self->step++;
        break;
    case 2:
#if defined(VERSION_US)
        dstPix = g_Pix[0];
        chPix = dstPix;
        str = self->ext.messageBox.label;
        xOffset = 0;
        for (i = 0;
             i < self->ext.messageBox.width / 2 * self->ext.messageBox.height;
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
                chPix = &dstPix[self->ext.messageBox.width * 8];
            } else {
                str = BlitChar(
                    str, &xOffset, chPix, (self->ext.messageBox.width >> 1));
            }
        }
        LoadTPage((u_long*)dstPix, 0, 0, VramX, VramY,
                  self->ext.messageBox.width, self->ext.messageBox.height);
#elif defined(VERSION_PSP)
        nCh = 0;
        x = VramX;
        y = VramY;
        str = self->ext.messageBox.label;
        BlitChar(str, 0, 0, 0x180);
#elif defined(VERSION_HD)
        nCh = 0;
        x = VramX;
        y = VramY;
        str = self->ext.messageBox.label;
        while (true) {
            chjp = *str++;
            if (!chjp) {
                break;
            }
            if (chjp == 1) {
                y += FontH;
                x = 0;
            } else {
                chjp = (*str++ | (chjp << 8));
                srcJpPix = g_api.func_80106A28(chjp, 1);
                if (srcJpPix) {
                    dstJpPix = &D_801997E8[nCh * FontLen];
                    for (i = 0; i < FontLen; i++) {
                        *dstJpPix++ = *srcJpPix++;
                    }
                    LoadTPage(
                        &D_801997E8[nCh * FontLen], 0, 0, x, y, FontW, FontH);
                    x += 3;
                    nCh++;
                }
            }
        }
#endif
        self->ext.messageBox.duration = 0;
        self->step++;
        break;
    case 3:
        self->ext.messageBox.duration++;
        prim = &g_PrimBuf[self->primIndex];
        prim = prim->next;
        for (i = 0; prim != NULL; prim = prim->next, i++) {
            if (i == 0) {
                prim->y2 = prim->y3 =
                    prim->y0 + (self->ext.messageBox.height + 8) *
                                   self->ext.messageBox.duration / 8;
                prim->b0 = prim->b1 -= 0x10;
            } else {
                prim->y0 = prim->y1 =
                    prim->y2 - (self->ext.messageBox.height + 8) *
                                   self->ext.messageBox.duration / 8;
                prim->g2 = prim->g3 -= 0x10;
            }
        }
        if (self->ext.messageBox.duration == 8) {
            self->ext.messageBox.duration = 0;
            self->step++;
        }
        break;
    case 4:
        prim = &g_PrimBuf[self->primIndex];
        prim->drawMode = DRAW_DEFAULT;
        self->ext.messageBox.duration++;
        if (self->ext.messageBox.duration > self->params) {
            DestroyEntity(self);
        }
        break;
    }
}
