// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no4.h"

extern u8 D_us_8018112C[];
extern u8 D_us_80181144[]; // anim
extern s16 D_us_80181150[];

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
    ptr = &D_us_80181150[(self->params & 0xFF) * 5];
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

extern s16 D_us_8018124C[];

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
    ptr = &D_us_8018124C[(self->params & 0xFF) * 4];
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

extern u8 D_us_80181140[];
extern s16 D_us_8018133C[];

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
    var_s5 = D_us_80181140;
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

extern s16 D_us_801814E4[];
void func_us_801C1C94(Entity* self) {
    s32 primIndex;
    s32 scrollY;
    s32 scrollX;
    s32 var_s5;
    s16* ptr;
    s32 var_s3;
    s32 var_s2;
    s32 var_s1;
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
    ptr = D_us_801814E4;
    scrollX = g_Tilemap.scrollX.i.hi;
    scrollX /= 2;
    scrollX &= 0xFF;
    scrollY = g_Tilemap.scrollY.i.hi;

    if (scrollY < 0xB0) {
        scrollY /= 2;
        while (1) {
            var_s1 = *ptr++;
            var_s2 = *ptr++;
            var_s5 = *ptr++;
            var_s1 -= scrollX;
            var_s2 -= scrollY;
            var_s3 = var_s2 + 0x7E;
            if (var_s1 < -0x14) {
                continue;
            }

            if (var_s1 >= 0x100) {
                break;
            }

            if (var_s3 >= 0 && var_s2 < 0xE0) {
                if (var_s5 & 1) {
                    prim->x0 = prim->x2 = var_s1 + 0x14;
                    prim->x1 = prim->x3 = var_s1;
                } else {
                    prim->x0 = prim->x2 = var_s1;
                    prim->x1 = prim->x3 = var_s1 + 0x14;
                }

                if (var_s5 & 2) {
                    prim->y0 = prim->y1 = var_s2;
                    prim->y2 = prim->y3 = var_s3;
                } else {
                    prim->y0 = prim->y1 = var_s3;
                    prim->y2 = prim->y3 = var_s2;
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

extern s16 D_us_80181514[];
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
        prim->drawMode = DRAW_UNK_400 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                         DRAW_UNK02 | DRAW_TRANSP;
        prim = prim->next;

        // Prim 2
        prim->r0 = prim->r2 = prim->b0 = prim->b2 = prim->g0 = prim->g2 = 0;
        prim->r1 = prim->b1 = prim->g1 = var_s1;
        prim->r3 = prim->b3 = prim->g3 = var_s2;
        prim->x0 = prim->x2 = 0x20 - scrollX;
        prim->x1 = prim->x3 = 0x80 - scrollX;
        prim->y0 = prim->y1 = var_s4;
        prim->y2 = prim->y3 = var_s3;
        prim->drawMode = DRAW_UNK_400 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                         DRAW_UNK02 | DRAW_TRANSP;
        prim = prim->next;

        // Prim 3
        prim->r0 = prim->b0 = prim->g0 = var_s1;
        prim->r2 = prim->b2 = prim->g2 = var_s2;
        prim->r1 = prim->b1 = prim->g1 = prim->r3 = prim->b3 = prim->g3 = 0;
        prim->x0 = prim->x2 = 0x120 - scrollX;
        prim->x1 = prim->x3 = 0x180 - scrollX;
        prim->y0 = prim->y1 = var_s4;
        prim->y2 = prim->y3 = var_s3;
        prim->drawMode = DRAW_UNK_400 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                         DRAW_UNK02 | DRAW_TRANSP;
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

extern u16 D_us_8018152C[13];

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
            prim->clut = 0x161;
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

extern s16 D_us_80181548[2][5];
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

extern s16 D_us_80181178[];
extern s16 D_us_8018117A[];
extern s16 D_us_80181184[];
extern s16 D_us_80181196[];
extern s16 D_us_80181198[];
extern s16 D_us_801811A2[];
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
    D_us_80181196[0] = scrollX + 0x1D0;
    D_us_80181198[0] = 0x4C - scrollX;
    D_us_801811A2[0] = scrollX + 0x180;
    D_us_80181178[0] = scrollX + 0x540;
    D_us_8018117A[0] = 0x2B0 - scrollX;
    D_us_80181184[0] = scrollX + 0x70;
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

extern u16 D_us_8018155C[];
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
        self->primIndex = (s32)primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C12B0.prim = prim;
        while (prim != NULL) {
            prim->clut = 0x161;
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
            prim->y0 -= 1;
            if (rand() & 3) {
                prim->y0 -= 1;
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

extern s16 D_us_80181570[];
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
            prim->v0 = prim->v1 = (var_s4 + 4);
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

        continue;
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
        self->primIndex = (s32)primIndex;
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
void func_us_801C4520(Entity* self) {
    Entity* player;
    u16 collision;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 6;
        if (g_CastleFlags[NO4_WATER_BLOCKED]) {
            self->posX.i.hi = 1824 - g_Tilemap.scrollX.i.hi;
        } else {
            self->posX.i.hi = 1888 - g_Tilemap.scrollX.i.hi;
        }
    }

    player = &PLAYER;
    collision = GetPlayerCollisionWith(self, 16, 17, 5);

    if (collision & 1 && g_Player.vram_flag & TOUCHING_GROUND) {
        if (player->posX.i.hi < self->posX.i.hi) {
            if (g_pads[0].pressed & PAD_RIGHT && player->step == 1) {
                if (self->ext.timer.t) {
                    self->ext.timer.t--;
                    return;
                } else if (self->posX.i.hi + g_Tilemap.scrollX.i.hi < 1952) {
                    self->posX.i.hi++;
                    player->posX.i.hi++;
                }
                self->ext.timer.t = 3;
            }
        } else if (g_pads[0].pressed & PAD_LEFT && player->step == 1) {
            if (self->ext.timer.t) {
                self->ext.timer.t--;
            } else {
                if (self->posX.i.hi + g_Tilemap.scrollX.i.hi > 1824) {
                    self->posX.i.hi--;
                    player->posX.i.hi--;
                    if (self->posX.i.hi + g_Tilemap.scrollX.i.hi == 1824) {
                        g_CastleFlags[NO4_WATER_BLOCKED] = 1;
                    }
                }
                self->ext.timer.t = 3;
            }
        }
    }
}

extern s16 D_us_801811D6;  // water surface sprite height
extern s16 D_us_801812B8;  // water background sprite height
extern u8 D_us_80181588[]; // Water flow animation that needs to be blocked by
                           // the crate

/**
 * Does something with the water level that kills the 4 spear guards in the
 * alcove
 */
void func_us_801C4738(Entity* self) {
    Entity* newEnt;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = ANIMSET_OVL(1);
        self->palette = 68;
        self->drawFlags = FLAG_DRAW_UNK10;
        self->posX.i.hi = 0x711 - g_Tilemap.scrollX.i.hi;
        if (g_CastleFlags[NO4_WATER_BLOCKED] != 0) {
            self->ext.et_waterAlcove.waterHeight = 64;
        } else {
            newEnt = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEnt != NULL) {
                CreateEntityFromCurrentEntity(E_ID_27, newEnt);
                newEnt->params = 1;
            }
            self->ext.et_waterAlcove.entity7E = newEnt;

            newEnt = AllocEntity(newEnt, &g_Entities[256]);
            if (newEnt != NULL) {
                CreateEntityFromCurrentEntity(E_ID_26, newEnt);
                newEnt->params = 1;
            }
            self->ext.et_waterAlcove.entity82 = newEnt;
            self->ext.et_waterAlcove.waterHeight = 0;
        }
    }

    // Animates the small flow of water that needs to be blocked by the crate
    AnimateEntity(D_us_80181588, self);

    if (g_CastleFlags[NO4_WATER_BLOCKED] != 0) {
        if (self->ext.et_waterAlcove.waterHeight < 64) {
            if (!(self->ext.et_waterAlcove.unk8E & 0x7)) {
                if (!self->ext.et_waterAlcove.waterHeight) {
                    g_api.PlaySfx(SFX_WATER_BUBBLE);
                }
                self->ext.et_waterAlcove.waterHeight++;
                if (self->ext.et_waterAlcove.waterHeight == 20) {
                    g_CastleFlags[NO4_WATER_BLOCKED]++;
                }
                if (self->ext.et_waterAlcove.waterHeight == 52) {
                    g_CastleFlags[NO4_WATER_BLOCKED]++;
                }
            }
            self->ext.et_waterAlcove.unk8E++;
        }

        if (self->ext.et_waterAlcove.entity7E) {
            DestroyEntity(self->ext.et_waterAlcove.entity7E);
            self->ext.et_waterAlcove.entity7E = NULL;
        }

        if (self->ext.et_waterAlcove.entity82) {
            DestroyEntity(self->ext.et_waterAlcove.entity82);
            self->ext.et_waterAlcove.entity82 = NULL;
        }
        self->animCurFrame = 0;
    }

    D_us_801812B8 = 177 - self->ext.et_waterAlcove.waterHeight;
    D_us_801811D6 = 176 - self->ext.et_waterAlcove.waterHeight;

    if (self->ext.et_waterAlcove.waterHeight >= 64) {
        DestroyEntity(self);
    }
}

s32 GetPlayerCollisionWith(void*, u16, u16, u16);
extern u16 D_us_80181590[6];

void func_us_801C4980(Entity* self) {
    Entity* player;
    u16* hitboxPtr;
    s16 prevPosY, deltaX, deltaY, angle;
    u16 collision, hitboxIndex;

    player = &PLAYER;
    hitboxIndex = self->params;

    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = hitboxIndex + 25;
        self->drawFlags = FLAG_DRAW_ROTATE;
        self->ext.et_801C4980.posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
    }

    hitboxPtr = &D_us_80181590[hitboxIndex << 1];

    prevPosY = self->posY.i.hi;
    self->posY.i.hi = self->ext.et_801C4980.posY - g_Tilemap.scrollY.i.hi +
                      self->ext.et_801C4980.timer;
    collision = GetPlayerCollisionWith(self, *hitboxPtr++, *hitboxPtr, 4);
    self->posY.i.hi = prevPosY;
    self->ext.et_801C4980.prevTimer = self->ext.et_801C4980.timer;

    deltaX = self->posX.i.hi - player->posX.i.hi;

    if (collision) {
        if (self->ext.et_801C4980.timer < 4) {
            self->ext.et_801C4980.timer++;
        }
    } else if (self->ext.et_801C4980.timer) {
        self->ext.et_801C4980.timer--;
    }

    deltaY = self->ext.et_801C4980.timer;
    if (deltaX < 0) {
        prevPosY = (deltaX * deltaY * -0x100) / 56;
    } else {
        prevPosY = (deltaX * deltaY << 8) / 56;
    }

    self->posY.i.hi = (self->ext.et_801C4980.posY - g_Tilemap.scrollY.i.hi) +
                      (deltaY - prevPosY / 256);

    if (collision) {
        deltaY -= self->ext.et_801C4980.prevTimer;
        player->posY.i.hi += deltaY;
        D_80097488.x.i.hi += deltaY;
    }

    angle = -prevPosY;
    if (collision || deltaY) {
        if (deltaX < 0) {
            self->rotate = ratan2(angle, -0x3800);
            self->rotate = (self->rotate - 0x800) & 0xFFF;
            return;
        }
        self->rotate = ratan2(angle, 0x3800);
        return;
    }

    self->rotate = 0;
}

void func_us_801C4BD8(Entity* self) {
    Tilemap* tmap;
    s16* dataPtr;
    s32 volume;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
    }

    tmap = &g_Tilemap;
    dataPtr = &D_us_8018159C[self->params * 4];

    volume = PLAYER.posX.i.hi + tmap->scrollX.i.hi - *dataPtr++;
    volume = (volume * *dataPtr++) / 4096;
    volume += *dataPtr++;

    if (volume < 0) {
        volume = 0;
    } else if (volume >= 128) {
        volume = 127;
    }

    if (!volume) {
        if (D_us_80181108 != 0) {
            D_us_80181108 = 0;
            g_api.PlaySfx(SET_UNK_A6);
            return;
        }
    }
    if (D_us_80181108 != 0) {
        g_api.SetVolumeCommand22_23(volume, *dataPtr++);
        return;
    }

    g_api.PlaySfxVolPan(SFX_WATERFALL_LOOP, volume, *dataPtr++);
    D_us_80181108 = 1;
}

void func_us_801C4D2C(Entity* self) {
    s16 leftBoundX, rightBoundX, currentX, playerScreenY;
    u16 playerInRange;

    u16* tilePtr;
    Entity* newEntity;
    Tilemap* tilemap;
    Entity* player;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
    }

    player = &g_Entities[0];
    tilemap = &g_Tilemap;

    // Another P2 controller triangle secret ?
    if (g_pads[1].tapped & PAD_TRIANGLE) {
        g_api.PlaySfx(SFX_WOODEN_BRIDGE_EXPLODE);
    }

    playerInRange = 0;
    if (!(g_Player.status &
          (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_MIST_FORM))) {
        playerScreenY = player->posY.i.hi + tilemap->scrollY.i.hi;
        if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
            if (playerScreenY > 151 && playerScreenY < 171) {
                playerInRange = 1;
                leftBoundX = player->posX.i.hi + tilemap->scrollX.i.hi - 12;
                rightBoundX = leftBoundX + 24;
            }
        } else if (playerScreenY > 151 && playerScreenY < 199) {
            playerInRange = 1;
            leftBoundX = player->posX.i.hi + tilemap->scrollX.i.hi - 8;
            rightBoundX = leftBoundX + 16;
        }
    }

    if (playerInRange) {
        for (currentX = leftBoundX; currentX <= rightBoundX; currentX += 8) {
            playerInRange = 0;

            if ((currentX >= 2624 && currentX < 2784) ||
                (currentX >= 2944 && currentX < 3040)) {
                playerInRange = 1;
            }

            if (playerInRange) {
                tilePtr = &tilemap->fg[currentX / 16] + 2288;

                if (*tilePtr == 1793 || *tilePtr == 1797) {
                    newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (newEntity) {
                        CreateEntityFromCurrentEntity(E_ID_54, newEntity);
                        newEntity->posX.i.hi =
                            ((currentX & 0xFFF0) + 8) - tilemap->scrollX.i.hi;
                        newEntity->posY.i.hi = 178 - tilemap->scrollY.i.hi;
                        if (player->posX.i.hi > newEntity->posX.i.hi) {
                            newEntity->params = 1;
                        }
                    }
                    *tilePtr = 2759;
                } else if (*tilePtr == 1804) {
                    newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (newEntity) {
                        CreateEntityFromCurrentEntity(E_ID_54, newEntity);
                        newEntity->posX.i.hi =
                            ((currentX & 0xFFF0) + 8) - tilemap->scrollX.i.hi;
                        newEntity->posY.i.hi = 178 - tilemap->scrollY.i.hi;
                        if (player->posX.i.hi > newEntity->posX.i.hi) {
                            newEntity->params = 1;
                        }
                    }
                    *tilePtr = 1437;
                }
            }
        }
    }
}

void func_us_801C5020(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 12;
        self->drawFlags = FLAG_DRAW_OPACITY | FLAG_DRAW_ROTATE;
        self->drawMode = DRAW_TPAGE | DRAW_TPAGE2;
        self->opacity = 128;
        self->rotate = 0;
        self->zPriority = 159;
        PlaySfxPositional(SFX_UNK_NO4_7BE);
    }

    if (self->params != 0) {
        self->rotate += 32;
    } else {
        self->rotate -= 32;
    }

    self->opacity += 252;
    self->posY.val += FIX(0.5);

    if (self->opacity < 8) {
        DestroyEntity(self);
    }
}

void func_us_801C50FC(void) {
    u16* tile;
    s16 i;

    tile = &g_Tilemap.fg[691];

    for (i = 0; i < 10; i++, tile++) {
        *tile = 0;
    }
}

extern u16 D_us_801815BE[];
extern u16 D_us_801815CC[];

void func_us_801C5134(void) {
    Entity* newEntity;
    s16 offsetX;
    s32 i;

    PlaySfxPositional(SFX_WOODEN_BRIDGE_EXPLODE);

    for (i = 1; i < 4; i++) {
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity) {
            CreateEntityFromCurrentEntity(E_ID_5C, newEntity);
            newEntity->posX.i.hi += D_us_801815BE[i - 1];
            newEntity->posY.i.hi += D_us_801815CC[i];
            newEntity->params = i;
        } else {
            break;
        }
    }

    offsetX = -72;
    for (i = 0; i < 10; i++) {
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity) {
            CreateEntityFromCurrentEntity(E_EXPLOSION, newEntity);
            newEntity->params = 17;
            newEntity->posX.i.hi += ((offsetX + ((rand() & 7) * 2)) - 7);
            newEntity->posY.i.hi += (((rand() & 7) * 4) - 7);
            offsetX += 16;
        } else {
            break;
        }
    }
}

// Function that updates the bridge state in underground caverns
void func_us_801C5268(Entity* self) {
    Entity* entity;
    u16 offsetX;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = ANIMSET_OVL(0);
        self->posX.i.hi = 896 - g_Tilemap.scrollX.i.hi;
        if (g_CastleFlags[NO4_SKELETON_APE_AND_BRIDGE] > 1) {
            func_us_801C50FC();
            DestroyEntity(self);
            return;
        }
    }
    if (g_CastleFlags[NO4_SKELETON_APE_AND_BRIDGE] == 1) {
        if (!self->step_s) {
            entity = &g_Entities[88];
            if (entity->entityId == E_SKELETON_APE) {
                entity = entity->ext.et_801C5268.unk80;
                if (entity) {
                    self->ext.et_801C5268.unk7C = entity;
                    self->step_s++;
                }
            }
        } else {
            entity = self->ext.et_801C5268.unk7C;
            if (entity->entityId != E_SKELETON_APE_BARREL) {
                self->step_s = 0;
            } else if (entity->step == 4 &&
                       entity->posY.i.hi + g_Tilemap.scrollY.i.hi > 128) {
                offsetX = entity->posX.i.hi + g_Tilemap.scrollX.i.hi;
                if (offsetX > 808 && offsetX < 984) {
                    g_CastleFlags[NO4_SKELETON_APE_AND_BRIDGE] = 2;
                }
            }
        }
    }
    if (g_CastleFlags[NO4_SKELETON_APE_AND_BRIDGE] == 2 ||
        g_pads[1].tapped & PAD_TRIANGLE) {
        PlaySfxPositional(SFX_WOODEN_BRIDGE_EXPLODE);
        g_CastleFlags[NO4_SKELETON_APE_AND_BRIDGE]++;
        func_us_801C50FC();
        func_us_801C5134();
    }
}

extern s16 D_us_801815DC[]; // animCurFrame
extern u16 D_us_801815EC[]; // facingLeft
extern s16 D_us_801815FC[]; // rotate
extern s32 D_us_8018160C[]; // velocityY

void func_us_801C542C(Entity* self) {
    u16 params = self->params;
    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = D_us_801815DC[params];
        self->facingLeft = D_us_801815EC[params];
        self->velocityY = D_us_8018160C[params];
        self->drawFlags = FLAG_DRAW_ROTATE;
        self->rotate = false;
    }
    if (F(self->velocityY).i.hi < 8) {
        F(self->velocityY).val += FIX(0.25);
    }
    MoveEntity();
    self->rotate += D_us_801815FC[params];
}

extern s16 D_us_8018162C[];

void func_us_801C5518(Entity* self) {
    Tilemap* tmap;
    u16 diff;
    s16* dataPtr;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
    }

    tmap = &g_Tilemap;
    dataPtr = &D_us_8018162C[self->params << 2];
    diff = PLAYER.posX.i.hi + tmap->scrollX.i.hi - *dataPtr++;

    if (*dataPtr++ >= diff) {
        diff = PLAYER.posY.i.hi + tmap->scrollY.i.hi - *dataPtr++;
        if (*dataPtr >= diff) {
            if (PLAYER.velocityY < 0) {
                PLAYER.velocityY *= 7;
                PLAYER.velocityY /= 8;
            } else if (PLAYER.velocityY > 0) {
                PLAYER.nFramesInvincibility = 1;
            }
        }
    }
}

extern Primitive D_us_80181644;

/**
 * Function that runs when the player is in the switch room to activate the
 * skeleton ape that can destroy the bridge in underground caverns.
 * Location (X: 21, Y: 33)
 * https://guides.gamercorner.net/sotn/areas/underground-caverns
 */
void func_us_801C5628(Entity* self) {
    Entity* player;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 40;
        if (!g_CastleFlags[NO4_SKELETON_APE_AND_BRIDGE]) {
            self->posX.i.hi = 52;
        } else {
            self->posX.i.hi = 44;
        }
    }

    // Idk why it wants to store the entity before but it works so ¯\_(ツ)_/¯
    player = &PLAYER;

    if ((((GetPlayerCollisionWith(self, 0x8, 16, 5) & 1) &&
          (g_Player.vram_flag & TOUCHING_GROUND)) &&
         (g_pads[0].pressed & PAD_LEFT)) &&
        (PLAYER.step == 1)) {
        if (self->ext.et_801C4520.unk7C != 0) {
            self->ext.et_801C4520.unk7C--;
        } else {
            if (self->posX.i.hi > 44) {
                self->posX.i.hi--;
                PLAYER.posX.i.hi--;
                if (self->posX.i.hi == 44) {
                    g_CastleFlags[NO4_SKELETON_APE_AND_BRIDGE] = 1;
                    PlaySfxPositional(SFX_SWITCH_CLICK);
                    self->step++;
                }
            }
            self->ext.et_801C4520.unk7C = 2;
        }
    }

    if ((self->step == 2) && (player->posX.i.hi > 128)) {
        g_api.PlaySfxVolPan(SFX_WALL_DEBRIS_A, 127, 8);
        player = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (player != NULL) {
            CreateEntityFromCurrentEntity(E_MESSAGE_BOX, player);
            player->posX.i.hi = 128;
            player->posY.i.hi = 176;
            player->ext.prim = &D_us_80181644;
            player->params = 0x100;
        }
        self->step++;
    }
}

void func_us_801C582C(Entity* self) {
    if (g_CastleFlags[NO4_SKELETON_APE_AND_BRIDGE] != 0) {
        self->entityId = E_SKELETON_APE;
        self->pfnUpdate = EntitySkeletonApe;
        EntitySkeletonApe(self);
    }
}

void func_us_801C5868(void) {
    u16* tile;
    s16 i;

    tile = &g_Tilemap.fg[163];

    for (i = 0; i < 10; i++, tile++) {
        *tile = 0;
    }
}

void func_us_801C58A0(Entity* self) {
    Entity* newEnt;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        if (g_CastleFlags[NO4_SKELETON_APE_AND_BRIDGE]) {
            func_us_801C5868();
            DestroyEntity(self);
        }
        break;
    case 1:
        if (g_CastleFlags[NO4_SKELETON_APE_AND_BRIDGE]) {
            newEnt = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (newEnt != NULL) {
                CreateEntityFromCurrentEntity(E_SKELETON_APE, newEnt);
                newEnt->params = 2;
                newEnt->posY.i.hi = newEnt->posY.i.hi - 96;
                newEnt->posX.i.hi = newEnt->posX.i.hi + 96;
                self->ext.prim = (Primitive*)(newEnt + 2); // I dont like this
            }
            self->step += 1;
        }
        break;
    case 2:
        if (self->ext.prim->x3 == 4U) {
            func_us_801C5868();
            func_us_801C5134();
            DestroyEntity(self);
        }
        break;
    }
}
