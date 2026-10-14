// SPDX-License-Identifier: AGPL-3.0-or-later

// unused
static u8 D_us_8018110C[] = {
    0x24, 0x1A, 0x21, 0x1A, 0x2B, 0x1B, 0x22, 0x1B, 0x2C, 0x1C, 0x23,
    0x1C, 0x2D, 0x1D, 0x24, 0x1D, 0x2E, 0x1E, 0x25, 0x1E, 0x2F, 0x1F,
    0x26, 0x1F, 0x56, 0x20, 0x21, 0x20, 0xFF, 0x00, 0x00, 0x00,
};

static u8 D_us_8018112C[] = {
    0x81, 0x81, 0x7E, 0x06, 0x81, 0x89, 0x7E, 0x06, 0x81, 0x91, 0x7E, 0x06,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x81, 0x7E, 0x46,
};

static u8 D_us_80181144[] = {10, 0, 10, 1, 10, 2, 10, 1, 0, 0};

s16 water_surface_lines[] = {
    0x00D0, 0x00F0, 0x00B0, 0x00F0, 0xFFFE, 0x0060, 0x00C0, 0x05B0, 0x05F0,
    0x0000, 0x0B80, 0x0060, 0x00B0, 0x00F0, 0x0000, 0x0A40, 0x00A0, 0x00B0,
    0x00E0, 0x0000, 0x0540, 0x02B0, 0x00B0, 0x0130, 0x0000, 0x04D0, 0x0070,
    0x00B0, 0x00F0, 0xFFFF, 0x0260, 0x0230, 0x0120, 0x0180, 0x0000, 0x01D0,
    0x004C, 0x00B0, 0x00F0, 0x0001, 0x0050, 0x0180, 0x00B0, 0x01A0, 0x0000,
    0x0510, 0x0050, 0x00B0, 0x00F0, 0x0000, 0x0840, 0x0090, 0x0100, 0x01D0,
    0x0000, 0x02A0, 0x0160, 0x00B0, 0x0170, 0x0000, 0x00A0, 0x0150, 0x00B0,
    0x0130, 0x0000, 0x0620, 0x00B0, 0x00B0, 0x00C0, 0x0000, 0x0070, 0x0C10,
    0x00B0, 0x0160, 0x0000, 0x0060, 0x00D0, 0x00B0, 0x00E0, 0x0000, 0x0050,
    0x0078, 0x00B8, 0x00E0, 0x0000, 0x0050, 0x0070, 0x00B0, 0x00F0, 0xFFFE,
    0x0050, 0x0070, 0x00B0, 0x00E0, 0x0000, 0x0030, 0x007C, 0x00B8, 0x00E0,
    0x0000, 0x0058, 0x0148, 0x00B0, 0x00E8, 0x0000, 0x0220, 0x00D0, 0x00B0,
    0x00E8, 0x0000, 0x0000, 0x04D0, 0x00D8, 0x00E8, 0x0000, 0x0068, 0x00B0,
    0x00F0, 0x00F0, 0x0000, 0x0340, 0x0074, 0x00F0, 0x00F0, 0x0000, 0x0000,
};

void func_us_801C12B0(Entity* self) {
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
        InitializeEntity(g_EInitInteractable);
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
            prim->priority = 0x9E;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        break;
    }

    prim = self->ext.et_801C12B0.prim;
    AnimateEntity(D_us_80181144, self);
    i = (self->params >> 8) & 0xFF;
    ptr = &water_surface_lines[(self->params & 0xFF) * 5];
    scrollX = g_Tilemap.scrollX.i.hi - 0x10;
    scrollY = g_Tilemap.scrollY.i.hi;
    xOffset = scrollX + 0x120;
    var_s5 = &D_us_8018112C[self->animCurFrame * 4];
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
            // This fixes a bunch of registers on PSP
            // It should mean the else below is not necessary but
            // removing it reintroduces the issue.
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

s16 water_tile_rects[] = {
    0x0D0, 0x0F0, 0x0B1, 0x0F0, 0x060, 0x0C0, 0x5B1, 0x5F0, 0xB80, 0x060, 0x0B1,
    0x0F0, 0xA40, 0x0A0, 0x0B1, 0x0E0, 0x540, 0x2B0, 0x0B1, 0x130, 0x4D0, 0x070,
    0x0B1, 0x0F0, 0x260, 0x230, 0x121, 0x180, 0x1D0, 0x048, 0x0B1, 0x0F0, 0x050,
    0x180, 0x0B1, 0x1A0, 0x510, 0x050, 0x0B1, 0x0F0, 0x840, 0x090, 0x101, 0x1D0,
    0x2A0, 0x1D2, 0x0B1, 0x170, 0x0A0, 0x150, 0x0B1, 0x130, 0x620, 0x0B0, 0x0B1,
    0x0C0, 0x560, 0x1B0, 0x0C0, 0x0F0, 0x530, 0x1E2, 0x0F0, 0x1D2, 0x712, 0x12E,
    0x120, 0x1A2, 0x010, 0x090, 0x100, 0x1E0, 0x0A0, 0x0F2, 0x130, 0x1E0, 0x010,
    0xC70, 0x0B1, 0x160, 0x060, 0x0D0, 0x0B1, 0x0E0, 0x050, 0x078, 0x0B9, 0x0E0,
    0x050, 0x070, 0x0B1, 0x0F0, 0x050, 0x070, 0x0B1, 0x0E0, 0x030, 0x07C, 0x0B9,
    0x0E0, 0x058, 0x148, 0x0B1, 0x0E8, 0x220, 0x0D0, 0x0B1, 0x0E8, 0x000, 0x4D0,
    0x0D9, 0x0E8, 0x068, 0x0B0, 0x0F0, 0x0F0, 0x340, 0x074, 0x0F0, 0x0F0,
};

void func_us_801C15F8(Entity* self) {
    s32 scrollX;
    s32 scrollY;
    s16* ptr;
    s32 var_s5;
    s32 var_s4;
    s32 var_s3;
    s32 var_s2;
    s32 var_s1;
    Primitive* prim;

    s32 primIndex;
    s32 xOffset;
    s32 yOffset;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        self->ext.et_801C12B0.unk80 = 4;
        primIndex = g_api.AllocPrimitives(PRIM_TILE, 16);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C12B0.prim = prim;
        while (prim != NULL) {
            prim->r0 = 0;
            prim->g0 = 0x10;
            prim->b0 = 0x20;
            prim->priority = 0x9D;
            prim = prim->next;
        }
        break;
    }

    prim = self->ext.et_801C12B0.prim;
    ptr = &water_tile_rects[(self->params & 0xFF) * 4];
    i = (self->params >> 8) & 0xFF;
    scrollX = g_Tilemap.scrollX.i.hi - 0x10;
    scrollY = g_Tilemap.scrollY.i.hi - 0x10;
    xOffset = scrollX + 0x120;
    yOffset = scrollY + 0x100;

    for (; i > 0; i--) {
        var_s3 = *ptr++;
        var_s2 = var_s3 + *ptr++;
        if (scrollX >= var_s2 || xOffset < var_s3) {
            ptr += 2;
            continue;
        }

        var_s5 = *ptr++;
        var_s4 = *ptr++;
        if (var_s4 > scrollY && yOffset >= var_s5) {
            if (var_s3 < scrollX) {
                var_s3 = scrollX;
            }
            if (xOffset < var_s2) {
                var_s2 = xOffset;
            }

            var_s2 -= var_s3;
            var_s3 -= scrollX + 0x10;

            if (var_s5 < scrollY) {
                var_s5 = scrollY;
            }

            if (yOffset < var_s4) {
                var_s4 = yOffset;
            }
            var_s4 -= var_s5;
            var_s5 -= scrollY + 0x10;
            if (var_s4 >= 0x100) {
                var_s4 = 0xFF;
            }

            do {
                var_s1 = var_s2;
                if (var_s1 >= 0x100) {
                    var_s1 = 0xFF;
                }
                prim->u0 = var_s1;
                prim->v0 = var_s4;
                prim->x0 = var_s3;
                prim->y0 = var_s5;
                var_s3 += var_s1;
                var_s2 -= var_s1;
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

static s16 D_us_8018133C[] = {
    0x128, 0x158, 0x058, 0x0AC, 0x168, 0x198, 0x068, 0x0AC, 0x568, 0x598, 0x058,
    0x0AC, 0x5B0, 0x5D8, 0x068, 0x0AC, 0x5E8, 0x658, 0x058, 0x0AC, 0x6E8, 0x758,
    0x058, 0x0AC, 0x768, 0x798, 0x058, 0x0AC, 0x7B0, 0x7D8, 0x068, 0x0AC, 0x8F0,
    0x918, 0x068, 0x0AC, 0xA68, 0xA98, 0x058, 0x0AC, 0x068, 0x098, 0x058, 0x0AC,
    0x0B0, 0x0D8, 0x068, 0x0AC, 0x130, 0x198, 0x058, 0x0AC, 0x070, 0x0D8, 0x058,
    0x0AC, 0x070, 0x092, 0x058, 0x088, 0x0F0, 0x118, 0x068, 0x0AC, 0x1A8, 0x1D8,
    0x058, 0x0AC, 0x1F0, 0x218, 0x068, 0x0AC, 0x068, 0x098, 0x058, 0x0AC, 0x0B0,
    0x0D8, 0x068, 0x0AC, 0x0E8, 0x158, 0x058, 0x0AC, 0x168, 0x198, 0x058, 0x0AC,
    0x1B0, 0x1D8, 0x068, 0x0AC, 0x2A8, 0x318, 0x058, 0x0AC, 0x330, 0x358, 0x068,
    0x0AC, 0x368, 0x398, 0x058, 0x0AC, 0x3B0, 0x3D8, 0x068, 0x0AC, 0x430, 0x458,
    0x068, 0x0A8, 0x470, 0x498, 0x058, 0x09C, 0x4F0, 0x518, 0x068, 0x0AC, 0x070,
    0x098, 0x068, 0x0AC, 0x0A8, 0x0D8, 0x058, 0x0AC, 0x0F0, 0x118, 0x068, 0x0AC,
    0x128, 0x158, 0x058, 0x0AC, 0x1E8, 0x258, 0x058, 0x0AC, 0x368, 0x398, 0x058,
    0x0AC, 0x3B0, 0x3D8, 0x068, 0x0AC, 0x4B0, 0x4D8, 0x068, 0x0AC, 0x568, 0x5D8,
    0x058, 0x0AC, 0x5E8, 0x618, 0x058, 0x0AC, 0x630, 0x658, 0x068, 0x0AC, 0x7F0,
    0x818, 0x068, 0x0AC, 0x928, 0x959, 0x058, 0x0AC, 0x971, 0x998, 0x068, 0x0AC,
    0x9A8, 0xA18, 0x058, 0x0AC, 0xA28, 0xA58, 0x058, 0x0AC, 0xA70, 0xA98, 0x068,
    0x0AC, 0xB68, 0xB98, 0x058, 0x0AC, 0xC28, 0xC58, 0x058, 0x0AC, 0xC70, 0xC98,
    0x068, 0x0AC, 0x068, 0x098, 0x058, 0x0AC, 0x0B0, 0x0D8, 0x068, 0x0AC, 0x0E8,
    0x158, 0x058, 0x0AC,
};

void func_us_801C1844(Entity* self) {
    s32 primIndex;
    s32 scrollX;
    s32 scrollY;
    s32 xOffset;
    s32 yOffset;
    s32 sp38;
    s32 sp34;
    s16* ptr;

    s32 var_s8;
    s32 var_s7;
    s32 var_s6;
    u8* var_s5;
    s32 var_s4;
    s32 var_s3;
    s32 var_s2;
    s32 var_s1;
    Primitive* prim;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        self->ext.et_801C12B0.unk80 = 4;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x10);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C12B0.prim = prim;
        while (prim != NULL) {
            prim->tpage = 0xF;
            prim->clut = 0x85;
            prim->priority = 0x18;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }

    g_GpuBuffers[0].draw.r0 = 8;
    g_GpuBuffers[0].draw.g0 = 8;
    g_GpuBuffers[0].draw.b0 = 0x10;
    g_GpuBuffers[1].draw.r0 = 8;
    g_GpuBuffers[1].draw.g0 = 8;
    g_GpuBuffers[1].draw.b0 = 0x10;

    prim = self->ext.et_801C12B0.prim;
    sp38 = (self->params >> 8) & 0xFF;
    ptr = &D_us_8018133C[(self->params & 0xFF) * 4];
    scrollX = g_Tilemap.scrollX.i.hi - 0x10;
    scrollY = g_Tilemap.scrollY.i.hi;
    xOffset = scrollX + 0x120;
    yOffset = scrollY + 0xE0;
    var_s5 = &D_us_8018112C[20];
    var_s4 = var_s5[1];

    for (; sp38 > 0; sp38--) {
        var_s3 = *ptr++;
        var_s2 = *ptr++;
        if (scrollX >= var_s2 || xOffset < var_s3) {
            ptr += 2;
            // This fixes a bunch of registers on PSP
            // It should mean the else below is not necessary but
            // removing it reintroduces the issue.
            continue;
        } else {
            var_s7 = *ptr++;
            var_s8 = *ptr++;
            if (var_s8 <= scrollY || yOffset < var_s7) {
                continue;
            }

            if (var_s3 < scrollX) {
                var_s3 = scrollX;
            }
            if (xOffset < var_s2) {
                var_s2 = xOffset;
            }
            var_s2 -= var_s3;
            var_s3 -= scrollX + 0x10;
            var_s6 = ((scrollX / 4) + var_s3) % 0x7E;
            if (var_s7 < scrollY) {
                var_s7 = scrollY;
            }

            if (yOffset < var_s8) {
                var_s8 = yOffset;
            }
            var_s4 = 0x58 - (scrollY / 4);
            yOffset += 0x46;
            var_s7 -= scrollY;
            var_s8 -= scrollY;
            if (var_s4 >= var_s8 || yOffset < var_s7) {
                continue;
            }

            if (var_s7 < var_s4) {
                var_s7 = var_s4;
            }
            if (yOffset < var_s8) {
                var_s8 = yOffset;
            }

            var_s8 -= var_s7;
            var_s4 = (((scrollY / 4) + (var_s7 - 0x58)) % 70);
            var_s6 += var_s5[0];
            var_s4 += var_s5[1];
            do {
                prim->u0 = prim->u2 = var_s6;
                var_s1 = 0x7E - (var_s6 - var_s5[0]);
                if (var_s2 < var_s1) {
                    var_s1 = var_s2;
                }
                prim->u1 = prim->u3 = var_s6 + var_s1;
                prim->x0 = prim->x2 = var_s3;
                var_s3 += var_s1;
                prim->x1 = prim->x3 = var_s3;
                var_s2 -= var_s1;
                var_s6 = var_s5[0];
                prim->v0 = prim->v1 = var_s4;

                var_s1 = 0x46 - (var_s4 - var_s5[1]);
                if (var_s8 < var_s1) {
                    var_s1 = var_s8;
                }

                prim->v2 = prim->v3 = var_s4 + var_s1;
                prim->y0 = prim->y1 = var_s7;
                prim->y2 = prim->y3 = var_s7 + var_s1;
                prim->drawMode = DRAW_COLORS;

                if (g_Timer & 0x80) {
                    if (g_Timer & 0x40) {
                        sp34 = 0x3F - (g_Timer & 0x3F);
                    } else {
                        sp34 = g_Timer & 0x3F;
                    }
                } else {
                    sp34 = 0;
                }

                PRED(prim) = PBLU(prim) = sp34 + 0x80;
                PGRN(prim) = 0x80;
                prim = prim->next;
            } while (var_s2 != 0);
        }
    }

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

static s16 bg_columns_parallax_props[][3] = {
    {0x022, 0x023, 0x003}, {0x048, 0x022, 0x001}, {0x070, 0x021, 0x002},
    {0x0CE, 0x024, 0x001}, {0x122, 0x023, 0x003}, {0x148, 0x022, 0x001},
    {0x170, 0x021, 0x002}, {0x1CE, 0x024, 0x001},
};

// background columns scrolling in parallax
void EntityBgColumnsParallax(Entity* self) {
    s32 primIndex;
    s32 scrollY;
    s32 scrollX;
    s32 flipXY;
    s16* ptr;
    s32 posYBottom;
    s32 posY;
    s32 posX;
    Primitive* prim;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 10);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C12B0.prim = prim;
        while (prim != NULL) {
            prim->tpage = 0xE;
            prim->clut = 0x84;
            prim->u0 = prim->u2 = 0xE9;
            prim->u1 = prim->u3 = 0xFD;
            prim->v0 = prim->v1 = 1;
            prim->v2 = prim->v3 = 0x7F;
            prim->priority = 0x1C;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }

    prim = self->ext.et_801C12B0.prim;
    ptr = (s16*)bg_columns_parallax_props;
    scrollX = g_Tilemap.scrollX.i.hi;
    scrollX /= 2;
    scrollX &= 0xFF;
    scrollY = g_Tilemap.scrollY.i.hi;
    if (scrollY < 0xB0) {
        scrollY /= 2;
#ifdef FIX_UB
        // the original while loop does not prevent the function to read
        // outside the array boundaries
        for (int i = 0; i < LEN(bg_columns_parallax_props); i++) {
#else
        while (1) {
#endif
            posX = *ptr++;
            posY = *ptr++;
            flipXY = *ptr++;
            posX -= scrollX;
            posY -= scrollY;
            posYBottom = posY + 0x7E;
            if (posX < -20) {
                continue;
            }
            if (posX >= STAGE_WIDTH) {
                break;
            }
            if (posYBottom >= 0 && posY < 0xE0) {
                if (flipXY & 1) {
                    prim->x0 = prim->x2 = posX + 0x14;
                    prim->x1 = prim->x3 = posX;
                } else {
                    prim->x0 = prim->x2 = posX;
                    prim->x1 = prim->x3 = posX + 0x14;
                }
                if (flipXY & 2) {
                    prim->y0 = prim->y1 = posY;
                    prim->y2 = prim->y3 = posYBottom;
                } else {
                    prim->y0 = prim->y1 = posYBottom;
                    prim->y2 = prim->y3 = posY;
                }
                prim->drawMode = DRAW_DEFAULT;
                prim = prim->next;
            }
        }
    }
    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

static s16 D_us_80181514[] = {
    0x010, 0x032, 0x070, 0x09E, 0x0DF, 0x110,
    0x132, 0x170, 0x19E, 0x1DF, 0x210, 0x000,
};

void func_us_801C1EE4(Entity* self) {
    s32 scrollX;
    s32 clut;
    s32 yOffset;
    s32 var_s5;
    s32 var_s4;
    s32 scrollY;
    s32 var_s2;
    s32 var_s1;
    Primitive* prim;

    s32 primIndex;
    s16* ptr;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 16);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->ext.et_801C12B0.clut = 0;
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C12B0.prim = prim;
        while (prim != NULL) {
            prim->tpage = 0xE;
            prim->u0 = prim->u2 = 0xFC;
            prim->u1 = prim->u3 = 0xFE;
            prim->priority = 0x1A;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }

    prim = self->ext.et_801C12B0.prim;
    ptr = D_us_80181514;
    self->ext.et_801C12B0.clut++;
    if (self->ext.et_801C12B0.clut >= 0xE) {
        self->ext.et_801C12B0.clut = 0;
    }
    scrollX = g_Tilemap.scrollX.i.hi;
    scrollX *= 3;
    scrollX /= 8;
    scrollX &= 0xFF;
    scrollY = g_Tilemap.scrollY.i.hi;
    yOffset = 0x50 - scrollY;
    if (yOffset < 0) {
        yOffset = 0;
    }
    var_s5 = 0xB0 - scrollY;
    if (var_s5 >= 0) {
        scrollY *= 3;
        scrollY /= 8;
        scrollY += yOffset;
        scrollY %= 0x20;

        var_s5 -= yOffset;
        if (scrollY + var_s5 > 0x60) {
            var_s2 = 0x60 - scrollY;
        } else {
            var_s2 = var_s5;
        }

        var_s4 = var_s5 - var_s2;
        var_s5 = var_s2;
        var_s2 += yOffset;
        clut = self->ext.et_801C12B0.clut + 0x90;

        while (true) {
            var_s1 = *ptr++;
            var_s1 -= scrollX;
            if (var_s1 < -2) {
                continue;
            }

            if (var_s1 >= 0x100) {
                break;
            }

            prim->clut = clut;
            prim->v0 = prim->v1 = scrollY + 0x84;
            prim->v2 = prim->v3 = prim->v0 + var_s5;
            prim->x0 = prim->x2 = var_s1;
            prim->x1 = prim->x3 = var_s1 + 2;
            prim->y0 = prim->y1 = yOffset;
            prim->y2 = prim->y3 = var_s2;
            prim->drawMode =
                DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
            prim = prim->next;
            if (var_s4 != 0) {
                prim->clut = clut;
                prim->v0 = prim->v1 = 0x84;
                prim->v2 = prim->v3 = var_s4 + 0x84;
                prim->x0 = prim->x2 = var_s1;
                prim->x1 = prim->x3 = var_s1 + 2;
                prim->y0 = prim->y1 = var_s2;
                prim->y2 = prim->y3 = var_s2 + var_s4;
                prim->drawMode =
                    DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
                prim = prim->next;
            }
        }
    }

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

// Foreground waterfall
void func_us_801C21AC(Entity* self) {
    s32 primIndex;
    s32 var_s7;
    s32 var_s6;
    s32 scrollY;
    s32 clut;
    u16 params;
    s32 posX;
    s32 posY;
    Primitive* prim;

    s16* ptr;

    params = self->params;
    if (!self->step) {
        InitializeEntity(g_EInitParticle);
        self->animSet = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                       FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA | FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C12B0.prim = prim;
        while (prim != NULL) {
            if (params) {
                prim->tpage = 0xF;
                prim->u0 = prim->u2 = 0x82;
                prim->u1 = prim->u3 = 0x9D;
            } else {
                prim->tpage = 0xE;
                prim->u0 = prim->u2 = 0xE9;
                prim->u1 = prim->u3 = 0xF7;
            }

            prim->priority = 0x62;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }

    prim = self->ext.et_801C12B0.prim;
    // Pointer is loaded but never used
    // Likely copy pasted from previous function.
    ptr = D_us_80181514;
    self->ext.et_801C12B0.clut++;
    if (self->ext.et_801C12B0.clut >= 0xE) {
        self->ext.et_801C12B0.clut = 0;
    }

    posY = self->posY.i.hi;
    scrollY = g_Tilemap.scrollY.i.hi;

    if (posY >= 0) {
        scrollY %= 0x20;

        // Strange code here - looks like a copy-paste / cleanup bug
        if (params) {
            clut = 0x90;
        } else {
            clut = 0xB0;
        }
        clut = 0xB0;

        clut += self->ext.et_801C12B0.clut;
        if (scrollY + posY > 0x60) {
            var_s7 = 0x60 - scrollY;
        } else {
            var_s7 = posY;
        }

        var_s6 = posY - var_s7;
        posY = var_s7;
        prim->clut = clut;

        if (params) {
            posX = self->posX.i.hi - 0xD;
            prim->v0 = prim->v1 = scrollY + 4;
            prim->x1 = prim->x3 = posX + 0x1B;
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_UNK02 | DRAW_TRANSP;
        } else {
            posX = self->posX.i.hi - 7;
            prim->v0 = prim->v1 = scrollY + 0x84;
            prim->x1 = prim->x3 = posX + 0xE;
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_UNK02 | DRAW_TRANSP;
        }

        prim->v2 = prim->v3 = prim->v0 + posY;
        prim->x0 = prim->x2 = posX;
        prim->y0 = prim->y1 = 0;
        prim->y2 = prim->y3 = posY;
        prim = prim->next;

        if (var_s6 != 0) {
            prim->clut = clut;
            if (params) {
                prim->v0 = prim->v1 = 4;
                prim->v2 = prim->v3 = var_s6 + 4;
                prim->x0 = prim->x2 = posX;
                prim->x1 = prim->x3 = posX + 0x1B;
                prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                                 DRAW_UNK02 | DRAW_TRANSP;
            } else {
                prim->v0 = prim->v1 = 0x84;
                prim->v2 = prim->v3 = var_s6 + 0x84;
                prim->x0 = prim->x2 = posX;
                prim->x1 = prim->x3 = posX + 0xE;
                prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                                 DRAW_UNK02 | DRAW_TRANSP;
            }

            prim->y0 = prim->y1 = posY;
            prim->y2 = prim->y3 = posY + var_s6;
            prim = prim->next;
        }
    }

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

// Big waterfall
void func_us_801C2474(Entity* self) {
    Primitive* prim;
    s32 volume;
    s32 pan;
    s32 i;
    s32 var_s4;
    s32 scrollX;
    s32 scrollY;
    s32 clut;
    s32 primIndex;

    Entity* player;

    player = &PLAYER;
    scrollX = g_Tilemap.scrollX.i.hi;
    scrollY = g_Tilemap.scrollY.i.hi;
    volume = (scrollY / 24) + 0x4D;
    if (volume > 0x7F) {
        volume = 0x7F;
    }
    pan = (scrollX + player->posX.i.hi) - 0xD8;
    if (pan > 0) {
        if (pan < 0x20) {
            pan = 0;
        } else {
            pan = (pan - 0x20) / -24;
        }
        if (pan < -8) {
            pan = -8;
        }
    } else {
        if (pan > -0x20) {
            pan = 0;
        } else {
            pan = (pan + 0x20) / -0x10;
        }
        if (pan > 8) {
            pan = 8;
        }
    }
#ifdef VERSION_US
    FntPrint("vol ; %x\n", volume);
    FntPrint("pan : %d\n", pan);
#endif

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 4);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->ext.et_801C12B0.clut = 0;
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C12B0.prim = prim;

        while (prim != NULL) {
            prim->priority = 0x9C;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }

    g_api.SetVolumeCommand22_23(volume, pan);
    self->ext.et_801C12B0.clut++;
    if (self->ext.et_801C12B0.clut >= 0xE) {
        self->ext.et_801C12B0.clut = 0;
    }
    clut = self->ext.et_801C12B0.clut + 0xA0;

    prim = self->ext.et_801C12B0.prim;
    pan = 0xB0;
    i = 0x5B0;
    pan -= scrollY;
    i -= scrollY;
    if (pan < 0) {
        pan = 0;
    }
    if (i > 0xF0) {
        i = 0xF0;
    }

    i -= pan;
    do {
        volume = (pan + scrollY) - 0xB0;
        if (volume < 0xFE) {
            prim->tpage = 0xE;
            prim->u0 = prim->u2 = 0x87;
            prim->u1 = prim->u3 = 0xE7;
            prim->v0 = prim->v1 = volume + 1;
            var_s4 = volume + i;
            if (var_s4 > 0xFE) {
                prim->v2 = prim->v3 = 0xFF;
                volume = 0xFE - volume;
            } else {
                prim->v2 = prim->v3 = var_s4 + 1;
                volume = i;
            }
            prim->x0 = prim->x2 = 0xC0 - scrollX;
            prim->x1 = prim->x3 = 0x120 - scrollX;
        } else {
            prim->tpage = 0xF;
            volume -= 0xFE;
            volume %= 126;
            prim->u0 = prim->u2 = 0xCC;
            prim->u1 = prim->u3 = 0xFD;
            prim->v0 = prim->v1 = volume + 1;
            var_s4 = volume + i;
            if (var_s4 > 0x7E) {
                prim->v2 = prim->v3 = 0x7F;
                volume = 0x7E - volume;
            } else {
                prim->v2 = prim->v3 = (var_s4 + 1);
                volume = i;
            }
            prim->x0 = prim->x2 = 0xC0 - scrollX;
            prim->x1 = prim->x3 = 0xF1 - scrollX;
        }
        prim->y0 = prim->y1 = pan;
        pan += volume;
        prim->y2 = prim->y3 = pan;
        i -= volume;
        prim->clut = clut;
        prim->drawMode = DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        prim = prim->next;

        if (i == 0) {
            break;
        }
    } while (true);

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

void func_us_801C2850(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 scrollX;
    s32 scrollY;
    s32 var_s4;
    s32 var_s3;
    s32 var_s2;
    s32 var_s1;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        primIndex = g_api.AllocPrimitives(PRIM_G4, 3);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C12B0.prim = prim;

        while (prim != NULL) {
            prim->priority = 0x9E;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }

    prim = self->ext.et_801C12B0.prim;
    scrollX = g_Tilemap.scrollX.i.hi;
    scrollY = g_Tilemap.scrollY.i.hi;
    self->ext.et_801C12B0.unk80++;
    if (scrollY > 0x300) {
        var_s4 = 0x3E0;
        var_s3 = 0x5E0;
        var_s4 -= scrollY;
        var_s3 -= scrollY;
        var_s1 = scrollY & 7;
        if (var_s4 < -0x10) {
            var_s4 = -0x10 - var_s1;
        }
        if (var_s3 > 0xF0) {
            var_s3 = (-var_s1 & 7) + 0xF0;
        }
        var_s1 = (var_s4 + scrollY) - 0x3E0;
        var_s2 = (var_s3 + scrollY) - 0x3E0;
        if (self->ext.et_801C12B0.unk80 & 1) {
            var_s1 *= 0x13;
            var_s1 /= 40;
            var_s2 *= 0x13;
            var_s2 /= 40;
        } else {
            var_s1 *= 0x12;
            var_s1 /= 40;
            var_s2 *= 0x12;
            var_s2 /= 40;
        }

        // Prim 1
        prim->r0 = prim->r1 = prim->b0 = prim->b1 = prim->g0 = prim->g1 =
            var_s1;
        prim->r2 = prim->r3 = prim->b2 = prim->b3 = prim->g2 = prim->g3 =
            var_s2;
        prim->x0 = prim->x2 = 0x80 - scrollX;
        prim->x1 = prim->x3 = 0x120 - scrollX;
        prim->y0 = prim->y1 = var_s4;
        prim->y2 = prim->y3 = var_s3;
        prim->drawMode = DRAW_DITHERING | DRAW_TPAGE2 | DRAW_TPAGE |
                         DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim = prim->next;

        // Prim 2
        prim->r0 = prim->r2 = prim->b0 = prim->b2 = prim->g0 = prim->g2 = 0;
        prim->r1 = prim->b1 = prim->g1 = var_s1;
        prim->r3 = prim->b3 = prim->g3 = var_s2;
        prim->x0 = prim->x2 = 0x20 - scrollX;
        prim->x1 = prim->x3 = 0x80 - scrollX;
        prim->y0 = prim->y1 = var_s4;
        prim->y2 = prim->y3 = var_s3;
        prim->drawMode = DRAW_DITHERING | DRAW_TPAGE2 | DRAW_TPAGE |
                         DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim = prim->next;

        // Prim 3
        prim->r0 = prim->b0 = prim->g0 = var_s1;
        prim->r2 = prim->b2 = prim->g2 = var_s2;
        prim->r1 = prim->b1 = prim->g1 = prim->r3 = prim->b3 = prim->g3 = 0;
        prim->x0 = prim->x2 = 0x120 - scrollX;
        prim->x1 = prim->x3 = 0x180 - scrollX;
        prim->y0 = prim->y1 = var_s4;
        prim->y2 = prim->y3 = var_s3;
        prim->drawMode = DRAW_DITHERING | DRAW_TPAGE2 | DRAW_TPAGE |
                         DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim = prim->next;
    }

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

void func_us_801C2B78(Entity* self) {
    Primitive* prim;
    s32 i;
    s32 var_s2;
    s32 var_s3;
    s32 scrollX;
    s32 primIndex;
    s32 scrollY;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        primIndex = g_api.AllocPrimitives(PRIM_TILE, 128);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C12B0.prim = prim;
        while (prim != NULL) {
            prim->priority = 0x6C;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }

    prim = self->ext.et_801C12B0.prim;
    scrollX = g_Tilemap.scrollX.i.hi;
    scrollY = g_Tilemap.scrollY.i.hi;
    self->ext.et_801C12B0.unk80++;
    if (scrollY > 0x4D0) {
        var_s3 = 0x5B0;
        var_s3 -= scrollY;
        for (i = 0; i < 4; i++) {
            while (prim != NULL) {
                if (prim->drawMode == DRAW_HIDE) {
                    prim->r0 = prim->b0 = prim->g0 = 0x80;
                    prim->x0 = ((((rand() % 11) * 4) + 0xBF) - scrollX) + i;
                    prim->y0 = var_s3 - 4 + (rand() & 7);
                    prim->x1 = 0;
                    LOH(prim->r1) = 0;
                    prim->u0 = prim->v0 = 2;
                    LOW(prim->r2) = FIX(4);
                    LOW(prim->u1) = 0;
                    LOW(prim->x3) = (0x4000 - (rand() & 0xFF0));
                    LOW(prim->r3) = ((rand() & 0x1F00) - 0xF80);
                    prim->clut = 0x20;
                    prim->drawMode = DRAW_UNK02;
                    break;
                }

                prim = prim->next;
            }
        }
    }

    // This is probably an alternate Primitive
    prim = self->ext.et_801C12B0.prim;
    while (prim != NULL) {
        if (prim->drawMode != DRAW_HIDE) {
            LOH(prim->b1) = prim->x0;
            prim->y1 = prim->y0;
            LOW(prim->x1) += LOW(prim->r2);
            LOW(prim->r1) += LOW(prim->u1);
            prim->x0 = LOH(prim->b1);
            prim->y0 = prim->y1;

            var_s2 = 0;
            if (LOW(prim->r2) < 0) {

            } else {
                var_s2 = 1;
            }
            LOW(prim->r2) -= LOW(prim->x3);
            LOW(prim->u1) -= LOW(prim->r3);

            if (!--prim->clut) {
                prim->drawMode = DRAW_HIDE;
            }
        }
        prim = prim->next;
    }
}

static u16 D_us_8018152C[] = {0, 10, 4, 8, 1, 12, 5, 9, 2, 6, 11, 3, 7};

void func_us_801C2E60(Entity* self) {
    s32 var_s5;
#ifdef VERSION_PSP
    u32 scrollX;
#else
    s32 scrollX;
#endif
    s32 scrollY;
    s32 var_s2;
    s32 primIndex;
    Primitive* prim;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 32);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C12B0.prim = prim;
        while (prim != NULL) {
            prim->clut = PAL_CC_STONE_EFFECT;
            prim->tpage = 0x1A;
            prim->u0 = prim->u2 = 0;
            prim->u1 = prim->u3 = 0x1E;
            prim->v0 = prim->v1 = 0x60;
            prim->v2 = prim->v3 = 0x7C;
            prim->priority = 0x9D;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }

    prim = self->ext.et_801C12B0.prim;
    scrollX = g_Tilemap.scrollX.i.hi;
    scrollY = g_Tilemap.scrollY.i.hi;
    self->ext.et_801C12B0.unk80++;
    if (self->ext.et_801C12B0.unk80 >= LEN(D_us_8018152C)) {
        self->ext.et_801C12B0.unk80 = 0;
    }
    if (scrollY > 0x480) {
        var_s2 = 0x5B0;
        var_s2 -= scrollY;

        while (prim != NULL) {
            if (prim->drawMode == DRAW_HIDE) {
                prim->y0 = prim->y1 = prim->y2 = prim->y3 = var_s2;
#ifdef VERSION_PSP
                var_s5 = (D_us_8018152C[self->ext.et_801C12B0.unk80] * 4) +
                         0xBB - scrollX - 9;
                prim->x2 = prim->x0 = var_s5 + (rand() & 3);
#else
                var_s5 = (rand() & 3) - 9;
                prim->x2 = prim->x0 =
                    (D_us_8018152C[self->ext.et_801C12B0.unk80] * 4) + 0xBB -
                    scrollX + var_s5;
#endif
                prim->x3 = prim->x1 = prim->x0 + 0x12;
                PGREY(prim, 0) = PGREY(prim, 1) = 0xFF;
                PGREY(prim, 2) = PGREY(prim, 3) = 0x80;
                prim->p1 = 0;
                prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                                 DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
                break;
            }

            prim = prim->next;
        }
    }
    prim = self->ext.et_801C12B0.prim;
    while (prim != NULL) {
        if (prim->drawMode != DRAW_HIDE) {
            prim->y0--;
            if (rand() & 7) {
                prim->y0--;
            }
            prim->y1 = prim->y0;
            prim->p1++;
            prim->b1 -= 0x10;
            PGREY(prim, 0) = PGREY(prim, 1);
            prim->b3 -= 8;
            PGREY(prim, 2) = PGREY(prim, 3);
            if (prim->r0 < 0x11) {
                prim->drawMode = DRAW_HIDE;
            }
        }

        prim = prim->next;
    }
}

void func_us_801C3160(Entity* self) {
    s32 scrollY;
    s32 primIndex;
    u16 iterations;
    u16 params;
    s32 scrollX;
    s32 i;
    s32 yOffset;
    s32 randVal;
    Primitive* prim;

    params = self->params;
    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        if (!params) {
            primIndex = g_api.AllocPrimitives(PRIM_TILE, 0x80);
        } else {
            primIndex = g_api.AllocPrimitives(PRIM_TILE, 8);
        }
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = (s32)primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C12B0.prim = prim;
        while (prim != NULL) {
            prim->priority = 0x6C;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }

    // This is probably an alternative Primitive type
    prim = self->ext.et_801C12B0.prim;
    scrollX = g_Tilemap.scrollX.i.hi;
    scrollY = g_Tilemap.scrollY.i.hi;
    self->ext.et_801C12B0.unk80++;
    if (scrollY < 0xF0) {
        if (!params) {
            iterations = 4;
            yOffset = 0xB0 - scrollY;
        } else {
            iterations = 1;
            yOffset = 0xD6 - scrollY;
        }

        for (i = 0; i < iterations; i++) {
            while (prim != NULL) {
                if (prim->drawMode == DRAW_HIDE) {
                    if (!params) {
                        randVal = rand() & 0x1F;
                        prim->y0 = yOffset + randVal;
                        prim->x0 =
                            ((0x100 - (rand() % 40)) - scrollX) - randVal;
                        LOW(prim->u1) = 0xFFFE0000;
                        prim->u0 = prim->v0 = 2;
                        LOW(prim->r2) = 0;
                        prim->clut = 0x10;
                    } else {
                        prim->y0 = yOffset + (rand() & 3);
                        prim->x0 = (0x70E - scrollX) + (rand() & 3);
                        LOW(prim->u1) = 0x14000;
                        LOW(prim->r2) = ((rand() & 0x1F) << 0xB);
                        prim->u0 = prim->v0 = 1;
                        prim->clut = 8;
                    }
                    prim->r0 = prim->b0 = prim->g0 = 0x80;
                    prim->x1 = 0;
                    LOH(prim->r1) = 0;
                    LOW(prim->x3) = 0x4000;
                    LOW(prim->r3) = 0;
                    prim->drawMode = DRAW_UNK02;
                    break;
                }

                prim = prim->next;
            }
        }
    }

    // This is probably an alternate Primitive
    prim = self->ext.et_801C12B0.prim;
    while (prim != NULL) {
        if (prim->drawMode != DRAW_HIDE) {
            LOH(prim->b1) = prim->x0;
            prim->y1 = prim->y0;
            LOW(prim->x1) = LOW(prim->x1) + LOW(prim->r2);
            LOW(prim->r1) = LOW(prim->r1) + LOW(prim->u1);
            prim->x0 = LOH(prim->b1);
            prim->y0 = prim->y1;
            LOW(prim->r2) = LOW(prim->r2) + LOW(prim->x3);
            prim->r0 = prim->b0 = prim->g0 -= 8;
            if (!--prim->clut) {
                prim->drawMode = DRAW_HIDE;
            }
        }
        prim = prim->next;
    }
}

static s16 D_us_80181548[][5] = {
    {0x0058, 0x0068, 0x00B0, 0x0030, 0xFFFE},
    {0x06A0, 0x0060, 0x00C8, 0x0020, 0x0001},
};

void func_us_801C34EC(Entity* self) {
    s32 scrollX;
    s16 xOffset;
    s16 randX;
    s16 randY;
    s16 tpage;
    s32 yOffset;
    s32 scrollY;
    s32 primIndex;
    s16* ptr;
    Primitive* prim;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        primIndex = g_api.AllocPrimitives(PRIM_TILE, 0x40);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C12B0.prim = prim;
        while (prim != NULL) {
            prim->priority = 0x9B;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }

    ptr = D_us_80181548[self->params];
    xOffset = *ptr++;
    randX = *ptr++;
    yOffset = *ptr++;
    randY = *ptr++;
    tpage = *ptr;
    prim = self->ext.et_801C12B0.prim;
    scrollX = g_Tilemap.scrollX.i.hi;
    scrollY = g_Tilemap.scrollY.i.hi;
    self->ext.et_801C12B0.unk80++;
    if (scrollY < 0xF0) {
        yOffset -= scrollY;

        while (prim != NULL) {
            if (prim->drawMode == DRAW_HIDE) {
                prim->r0 = prim->b0 = prim->g0 = 0x80;
                prim->y0 = yOffset + (rand() % randY);
                prim->x0 = (xOffset - scrollX) + (rand() % randX);
                prim->x1 = 0;
                LOH(prim->r1) = 0;
                prim->u0 = prim->v0 = 2;
                LOW(prim->u1) = 0;
                prim->tpage = tpage;
                prim->drawMode = DRAW_UNK02;
                break;
            }

            prim = prim->next;
        }
    }

    // This is probably an alternate Primitive
    prim = self->ext.et_801C12B0.prim;
    while (prim != NULL) {
        if (prim->drawMode != DRAW_HIDE) {
            LOH(prim->b1) = prim->x0;
            LOW(prim->r1) += LOW(prim->u1);
            prim->x0 = LOH(prim->b1);
            prim->r0 -= 8;
            prim->b0 = prim->g0 = prim->r0;
            if (prim->r0 < 8) {
                prim->drawMode = DRAW_HIDE;
            }
        }
        prim = prim->next;
    }
}

void func_us_801C37C8(Entity* self) {
    Primitive* prim;
    s32 scrollX;
    s32 scrollY;
    s32 xOffset;
    s32 primIndex;
    s32 clut;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->ext.et_801C12B0.clut = 0;
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C12B0.prim = prim;
        prim->tpage = 0xF;
        prim->v0 = prim->v1 = 1;
        prim->v2 = prim->v3 = 0x7F;
        prim->priority = 0x9C;
        prim->drawMode = DRAW_HIDE;
    }

    scrollX = (rand() & 0x1F) - 0x10;
    water_surface_lines[35] = scrollX + 0x1D0;
    water_surface_lines[36] = 0x4C - scrollX;
    water_surface_lines[41] = scrollX + 0x180;
    water_surface_lines[20] = scrollX + 0x540;
    water_surface_lines[21] = 0x2B0 - scrollX;
    water_surface_lines[26] = scrollX + 0x70;
    self->ext.et_801C12B0.clut++;
    if (self->ext.et_801C12B0.clut >= 0xE) {
        self->ext.et_801C12B0.clut = 0;
    }

    clut = self->ext.et_801C12B0.clut + 0xA0;
    prim = self->ext.et_801C12B0.prim;
    scrollX = g_Tilemap.scrollX.i.hi;
    scrollY = g_Tilemap.scrollY.i.hi;

    if (scrollX < 0x288) {
        xOffset = 0x218 - scrollX;
        if (xOffset < 0x100) {
            prim->u0 = prim->u2 = 0x11;
            prim->u1 = prim->u3 = 0x80;
        } else {
            prim->drawMode = DRAW_HIDE;
            return;
        }
    } else if (scrollX < 0x4D8) {
        xOffset = 0x468 - scrollX;
        if (xOffset < 0x100) {
            prim->u0 = prim->u2 = 0x80;
            prim->u1 = prim->u3 = 0x11;
        } else {
            prim->drawMode = DRAW_HIDE;
            return;
        }
    } else {
        prim->drawMode = DRAW_HIDE;
        return;
    }

    prim->clut = clut;
    prim->x0 = prim->x2 = xOffset;
    prim->x1 = prim->x3 = xOffset + 0x6F;
    prim->y0 = prim->y1 = 0xB0 - scrollY;
    prim->y2 = prim->y3 = prim->y0 + 0x7F;
    prim->drawMode = DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
}

void func_us_801C3A04(Entity* self) {
    Primitive* prim;
    s32 i;
    s32 var_s2;
    s32 yOffset;
    s32 posX;
    s32 primIndex;
    s32 scrollY;

    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = 0;
        primIndex = g_api.AllocPrimitives(PRIM_TILE, 0x40);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C12B0.prim = prim;

        while (prim != NULL) {
            prim->priority = 0x6C;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }

    prim = self->ext.et_801C12B0.prim;
    posX = self->posX.i.hi;
    scrollY = g_Tilemap.scrollY.i.hi;
    self->ext.et_801C12B0.unk80++;
    yOffset = 0x120;
    yOffset -= scrollY;

    // This is probably an alternate Primitive
    for (i = 0; i < 2; i++) {
        while (prim != NULL) {
            if (prim->drawMode == DRAW_HIDE) {
                prim->r0 = prim->b0 = prim->g0 = 0x80;
                prim->x0 = ((rand() % 0x10) * 2) + i + posX;
                prim->y0 = yOffset - 4 + (rand() & 7);
                prim->x1 = 0;
                LOH(prim->r1) = 0;
                prim->u0 = prim->v0 = 2;
                LOW(prim->r2) = 0x40000;
                LOW(prim->u1) = 0;
                LOW(prim->x3) = 0x4000 - (rand() & 0xFF0);
                LOW(prim->r3) = (rand() & 0x1F00) - 0xF80;
                prim->clut = 0x20;
                prim->drawMode = DRAW_UNK02;
                break;
            }

            prim = prim->next;
        }
    }

    // This is probably an alternate Primitive
    prim = self->ext.et_801C12B0.prim;
    while (prim != NULL) {
        if (prim->drawMode != DRAW_HIDE) {
            LOH(prim->b1) = prim->x0;
            prim->y1 = prim->y0;
            LOW(prim->x1) += LOW(prim->r2);
            LOW(prim->r1) += LOW(prim->u1);
            prim->x0 = LOH(prim->b1);
            prim->y0 = prim->y1;

            var_s2 = 0;
            if (LOW(prim->r2) >= 0) {
                var_s2 = 1;
            }
            LOW(prim->r2) -= LOW(prim->x3);
            LOW(prim->u1) -= LOW(prim->r3);
            if (!--prim->clut) {
                prim->drawMode = DRAW_HIDE;
            }
        }
        prim = prim->next;
    }
}

static u16 D_us_8018155C[] = {0, 4, 8, 1, 5, 2, 6, 3, 7, 0};

void func_us_801C3CC4(Entity* self) {
    s32 var_s5;
    s32 posX;
    s32 scrollY;
    s32 var_s2;
    s32 primIndex;
    Primitive* prim;

    if (!self->step) {
        InitializeEntity(g_EInitParticle);
        self->animSet = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x20);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C12B0.prim = prim;
        while (prim != NULL) {
            prim->clut = PAL_CC_STONE_EFFECT;
            prim->tpage = 0x1A;
            prim->u0 = prim->u2 = 0;
            prim->u1 = prim->u3 = 0x1E;
            prim->v0 = prim->v1 = 0x60;
            prim->v2 = prim->v3 = 0x7C;
            prim->priority = 0x9D;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }

    prim = self->ext.et_801C12B0.prim;
    posX = self->posX.i.hi;
    scrollY = g_Tilemap.scrollY.i.hi;
    self->ext.et_801C12B0.unk80++;
    if (self->ext.et_801C12B0.unk80 >= 9) {
        self->ext.et_801C12B0.unk80 = 0;
    }
    var_s2 = 0x120;
    var_s2 -= scrollY;

    while (prim != NULL) {
        if (prim->drawMode == DRAW_HIDE) {
            prim->y0 = prim->y1 = prim->y2 = prim->y3 = var_s2;
#ifdef VERSION_PSP
            var_s5 = D_us_8018155C[self->ext.et_801C12B0.unk80] * 4;
            prim->x2 = prim->x0 = var_s5 + (rand() & 3) - 0x19 + posX;
#else
            var_s5 = rand() & 3;
            prim->x2 = prim->x0 =
                (D_us_8018155C[self->ext.et_801C12B0.unk80] * 4) + var_s5 -
                0x19 + posX;
#endif
            prim->x3 = prim->x1 = prim->x0 + 0x12;
            PGREY(prim, 0) = PGREY(prim, 1) = 0xFF;
            PGREY(prim, 2) = PGREY(prim, 3) = 0x80;
            prim->p1 = 0;
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
            break;
        }

        prim = prim->next;
    }

    prim = self->ext.et_801C12B0.prim;

    while (prim != NULL) {
        if (prim->drawMode != DRAW_HIDE) {
            prim->y0--;
            if (rand() & 3) {
                prim->y0--;
            }
            prim->y1 = prim->y0;
            prim->p1++;
            prim->b1 -= 0x10;
            PGREY(prim, 0) = PGREY(prim, 1);
            prim->b3 -= 8;
            PGREY(prim, 2) = PGREY(prim, 3);
            if (prim->r0 < 0x11) {
                prim->drawMode = DRAW_HIDE;
            }
        }

        prim = prim->next;
    }
}

static s16 D_us_80181570[] = {
    0x0100, 0x0000, 0x0240, 0x0018, 0x02E0, 0x000C,
    0x0300, 0x0000, 0x0320, 0x0010, 0x7FFF, 0x0000,
};

void func_us_801C3FB0(Entity* self) {
    s32 primIndex;
    s32 scrollX;
    s32 scrollY;
    s16* ptr;
    s32 clut;
    s32 var_s4;
    s32 var_s3;
    s32 var_s2;
    s32 var_s1;
    Primitive* prim;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x10);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->ext.et_801C12B0.clut = 0;
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C12B0.prim = prim;

        while (prim != NULL) {
            prim->tpage = 0xF;
            prim->u0 = prim->u2 = 0x82;
            prim->u1 = prim->u3 = 0x9D;
            prim->priority = 0xC0;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }

    prim = self->ext.et_801C12B0.prim;
    ptr = D_us_80181570;
    self->ext.et_801C12B0.clut++;
    if (self->ext.et_801C12B0.clut >= 0xE) {
        self->ext.et_801C12B0.clut = 0;
    }
    scrollX = g_Tilemap.scrollX.i.hi;
    scrollX *= 5;
    scrollX /= 4;

    scrollY = g_Tilemap.scrollY.i.hi;
    scrollY *= 5;
    scrollY /= 4;
    scrollY %= 0x20;

    clut = self->ext.et_801C12B0.clut + 0x90;

    while (prim != NULL) {
        var_s3 = *ptr++;
        var_s3 -= scrollX;
        if (var_s3 < -0x1B) {
            continue;
        }

        if (var_s3 >= 0x100) {
            break;
        }

        var_s4 = scrollY + *ptr++;
        var_s2 = 0x60 - var_s4;
        var_s1 = 0;

        while (prim != NULL) {
            prim->clut = clut;
            prim->v0 = prim->v1 = var_s4 + 4;
            prim->v2 = prim->v3 = prim->v0 + var_s2;
            prim->x0 = prim->x2 = var_s3;
            prim->x1 = prim->x3 = var_s3 + 0x1B;
            prim->y0 = prim->y1 = var_s1;
            var_s1 += var_s2;
            prim->y2 = prim->y3 = var_s1;
            prim->drawMode =
                DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
            prim = prim->next;

            if (var_s1 >= 0xE8) {
                break;
            }

            var_s4 = 0;
            if (var_s1 > 0x88) {
                var_s2 = 0xE8 - var_s1;
            } else {
                var_s2 = 0x60;
            }
        }
    }

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

void func_us_801C4228(Entity* self) {
    s32 scrollY;
    s32 scrollX;
    s32 primIndex;
    s32 yOffset;
    s32 yMax;
    s32 xOffset;
    Primitive* prim;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        primIndex = g_api.AllocPrimitives(PRIM_G4, 4);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C12B0.prim = prim;

        while (prim != NULL) {
            prim->priority = 0xC0;
            prim->r0 = prim->r2 = prim->g0 = prim->g2 = prim->r1 = prim->r3 =
                prim->g1 = prim->g3 = 0x10;
            prim->b0 = prim->b2 = prim->b1 = prim->b3 = 0;
            prim = prim->next;
        }
    }

    prim = self->ext.et_801C12B0.prim;
    scrollX = g_Tilemap.scrollX.i.hi;
    scrollY = g_Tilemap.scrollY.i.hi;
    if (scrollX > 0x90) {
        xOffset = PLAYER.posX.i.hi + 0x10;
    } else {
        xOffset = 0x120 - scrollX;
    }
    yOffset = 0x550 - scrollY;
    yMax = yOffset + 0x80;
    if (yMax > 0 && xOffset < 0x110) {
        // Prim 1
        prim->x0 = prim->x2 = xOffset;
        prim->x1 = prim->x3 = xOffset + 0x30;
        prim->y0 = prim->y1 = yOffset;
        prim->y2 = prim->y3 = yMax;
        prim->r1 = prim->r3 = prim->g1 = prim->g3 = prim->b1 = prim->b3 = 0xFF;
        prim->r0 = prim->r2 = prim->g0 = prim->g2 = prim->b0 = prim->b2 = 0;
        prim->drawMode =
            DRAW_UNK_40 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim = prim->next;

        // Prim 2
#ifdef VERSION_PSP
        prim->x0 = prim->x2 = xOffset;
        prim->x1 = prim->x3 = xOffset + 1;
#else
        prim->x0 = prim->x2 = xOffset + 1;
        xOffset += 3;
        prim->x1 = prim->x3 = xOffset;
#endif
        prim->y0 = prim->y1 = yOffset;
        prim->y2 = prim->y3 = yMax;
#ifdef VERSION_PSP
        prim->r0 = prim->r2 = prim->g0 = prim->g2 = prim->r1 = prim->r3 =
            prim->g1 = prim->g3 = 8;
        prim->b0 = prim->b2 = prim->b1 = prim->b3 = 0;
        prim->drawMode =
            DRAW_UNK_40 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
#else
        prim->r0 = prim->r2 = prim->g0 = prim->g2 = 7;
        prim->b0 = prim->b2 = prim->b1 = prim->b3 = 0;
        prim->r1 = prim->r3 = prim->g1 = prim->g3 = 8;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
#endif
        prim->priority = 0xC1;
        prim = prim->next;

        // Prim 3
        prim->x0 = prim->x2 = xOffset;
#ifdef VERSION_PSP
        xOffset += 0x30;
#else
        xOffset += 0x2D;
#endif
        prim->x1 = prim->x3 = xOffset;
        prim->y0 = prim->y1 = yOffset;
        prim->y2 = prim->y3 = yMax;

        prim->r0 = prim->r2 = prim->g0 = prim->g2 = prim->r1 = prim->r3 =
            prim->g1 = prim->g3 = 0x10;
        prim->b0 = prim->b2 = prim->b1 = prim->b3 = 0;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim->priority = 0xC1;
        prim = prim->next;

        // Prim 4
        if (xOffset < 0x110) {
            prim->x0 = prim->x2 = xOffset;
            prim->x1 = prim->x3 = 0x110;
            prim->y0 = prim->y1 = yOffset;
            prim->y2 = prim->y3 = yMax;
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
        }
    }

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

// Function that checks when alucard pushes the box in underground caverns
// to block the water hole
void EntityWaterBox(Entity* self) {
    Entity* player;
    u16 collision;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 6;
        if (g_CastleFlags[NO4_WATER_BLOCKED]) {
            self->posX.i.hi = 0x720 - g_Tilemap.scrollX.i.hi;
        } else {
            self->posX.i.hi = 0x760 - g_Tilemap.scrollX.i.hi;
        }
    }

    player = &PLAYER;
    collision = GetPlayerCollisionWith(self, 16, 17, 5);

    if (collision & 1 && g_Player.vram_flag & TOUCHING_GROUND) {
        if (self->posX.i.hi > player->posX.i.hi) {
            if (g_pads[0].pressed & PAD_RIGHT && PLAYER.step == Player_Walk) {
                if (self->ext.timer.t) {
                    self->ext.timer.t--;
                    return;
                }
                if (self->posX.i.hi + g_Tilemap.scrollX.i.hi < 0x7A0) {
                    self->posX.i.hi++;
                    player->posX.i.hi++;
                }
                self->ext.timer.t = 3;
            }
        } else {
            if (g_pads[0].pressed & PAD_LEFT && PLAYER.step == Player_Walk) {
                if (self->ext.timer.t) {
                    self->ext.timer.t--;
                    return;
                }
                if (self->posX.i.hi + g_Tilemap.scrollX.i.hi > 0x720) {
                    self->posX.i.hi--;
                    player->posX.i.hi--;
                    if (self->posX.i.hi + g_Tilemap.scrollX.i.hi == 0x720) {
                        g_CastleFlags[NO4_WATER_BLOCKED] = 1;
                    }
                }
                self->ext.timer.t = 3;
            }
        }
    }
}
