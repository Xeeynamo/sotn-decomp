// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno4/rno4.h"

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", RNO4_Unused801C8768);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", RNO4_Unused801C8770);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", EntityBoatElevatorChains);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", RNO4_Unused801C8BD4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", RNO4_Unused801C8BDC);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", LoadFerrymanGateTiles);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C8C54);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C12B0_from_no4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C15F8_from_no4);

extern u8 D_us_80181084[2];
extern s16 D_us_80181280[50]; // unknown size?

void func_us_801C5364(Entity* self) {
    Primitive* prim;
    u32 subTileX;
    int bgColorValue;
    int tileY1Wrap;
    s32 tileY1;
    s32 tileX0;
    s32 tileX1;
    u8* tilePos;
    s32 tileX1Wrap;
    s32 primIndex;
    s32 x0;
    long y0;
    s32 tileY0;
    s32 x1;
    s32 y1;
    s32 i;
    s16* tileDimensions; // It holds some dimensions of something, I'm guessing
                         // some tile or entity sprite

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        self->ext.et_801C5364.unk80 = 4;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x10);
        if (primIndex == (-1)) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C5364.prim7C = prim;
        while (prim) {
            prim->tpage = 0xF;
            prim->clut = 0x85;
            prim->priority = 0x18;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }
    if (g_Timer & 0x80) {
        if (g_Timer & 0x40) {
            bgColorValue = 0x3f - (g_Timer & 0x3f);
        } else {
            bgColorValue = g_Timer & 0x3f;
        }
    } else {
        bgColorValue = 0;
    }
    bgColorValue = bgColorValue + 0x80;
    bgColorValue = 0x80;

    g_GpuBuffers[0].draw.r0 = ((bgColorValue * 24) / 0x80) & 0xf8;
    g_GpuBuffers[0].draw.g0 = 0;
    g_GpuBuffers[0].draw.b0 = ((bgColorValue * 8) / 128) & 0xf8;
    g_GpuBuffers[1].draw.r0 = ((bgColorValue * 24) / 128) & 0xf8;
    g_GpuBuffers[1].draw.g0 = 0;
    g_GpuBuffers[1].draw.b0 = ((bgColorValue * 8) / 0x80) & 0xf8;

    prim = self->ext.et_801C5364.prim7C;

    i = (self->params >> 8) & 0xff;
    tileDimensions = D_us_80181280 + ((self->params & 0xff) * 4);
    x0 = g_Tilemap.scrollX.i.hi - 0x10;
    y0 = g_Tilemap.scrollY.i.hi;
    x1 = x0 + 0x120;
    y1 = y0 + 0xe0;
    tilePos = D_us_80181084;
    tileY1Wrap = tilePos[1];
    while (i > 0) {
        tileX0 = *(tileDimensions++);
        tileX1 = *(tileDimensions++);
        if ((x0 >= tileX0) || (x1 < tileX1)) {
            tileDimensions = tileDimensions + 2;
        } else {
            tileY0 = *(tileDimensions++);
            tileY1 = *(tileDimensions++);
            if ((y0 < tileY0) && (!(y1 < tileY1))) {
                {
                    if (x0 > tileX1) {
                        tileX1 = x0;
                    }
                }
                if (tileX0 > x1) {
                    tileX0 = x1;
                }
                tileX0 -= tileX1;
                tileX1 -= (x0 + 0x10);
                subTileX = ((x0 / 4) + tileX1) % 126;
                if (tileY1 < y0) {
                    tileY1 = y0;
                }
                if (y1 < tileY0) {
                    tileY0 = y1;
                }
                tileY1Wrap = 0x63 - ((y0 - (g_Tilemap.height - 0x100)) / 4);
                y1 = y1 + 0x46;
                tileY1 = tileY1 - y0;
                tileY0 -= y0;
                if ((tileY1Wrap < tileY0) && (y1 >= tileY1)) {
                    if (tileY1 < tileY1Wrap) {
                        tileY1 = tileY1Wrap;
                    }
                    if (y1 < tileY0) {
                        tileY0 = y1;
                    }
                    tileY0 -= tileY1;
                    tileY1Wrap = ((y0 - (g_Tilemap.height - 0x100)) / 4) +
                                 (tileY1 - 0x63);
                    subTileX += tilePos[0];
                    do {
                        prim->u0 = prim->u2 = subTileX;
                        tileX1Wrap = 0x7e - (subTileX - tilePos[0]);
                        if (tileX0 < tileX1Wrap) {
                            tileX1Wrap = tileX0;
                        }
                        prim->u1 = prim->u3 = subTileX + tileX1Wrap;
                        prim->x0 = prim->x2 = tileX1;
                        tileX1 = tileX1 + tileX1Wrap;

                        prim->x1 = (prim->x3 = tileX1);
                        tileX0 = tileX0 - tileX1Wrap;
                        subTileX = tilePos[0];

                        // There's this empty statement after all,
                        // I missed it when I thought I'd found the solution
                        // I had permuter running it for ~20 hours and couldn't
                        // find anything else
                        tilePos = tilePos;

                        if (tileY1Wrap > 0x46) {
                            tileX1Wrap = 0;
                        } else {
                            tileX1Wrap = 0x46 - tileY1Wrap;
                        }
                        prim->v0 = prim->v1 = tilePos[1] + tileX1Wrap;
                        prim->v2 = prim->v3 = tilePos[1];
                        prim->y0 = prim->y1 = tileY1;
                        prim->y2 = prim->y3 = tileY1 + tileX1Wrap;
                        prim->drawMode = DRAW_COLORS;
                        prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->b0 =
                            prim->b1 = prim->b2 = prim->b3 = bgColorValue;
                        prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0x80;
                        prim = prim->next;
                    } while (tileX0);
                }
            }
        }
        i -= 1;
    }

    while (prim) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", EntityBgColumnsParallax_from_no4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C1EE4_from_no4);

extern Tilemap* D_pspeu_0929B8B8; // This variable is assigned to a different
// var that is never used

void func_us_801C5C78(Entity* self) {
    Primitive* prim;
    Tilemap** tilemap_pp_0;
    u32 primIndex;
    u32 xOffset;
    u16 params;
    u32 clut;
    s32 scrollY;
    s32 posY;
    u32 scrollYModulo;

    params = self->params;
    if (!self->step) {
        InitializeEntity(g_EInitParticle);
        self->animSet = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex == (-1)) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                       FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA | FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C5C78.prim = prim;
        while (prim) {
            if (params) {
                prim->tpage = 0xF;
                prim->u0 = (prim->u2 = 0x82);
                prim->u1 = (prim->u3 = 0x9d);
            } else {
                prim->tpage = 0xE;
                prim->u0 = (prim->u2 = 0xe9);
                prim->u1 = (prim->u3 = 0xf7);
            }
            prim->priority = 0x62;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }

    prim = self->ext.et_801C5C78.prim;
    tilemap_pp_0 = &D_pspeu_0929B8B8;
    self->ext.et_801C5C78.unk84 += 1;

    if (self->ext.et_801C5C78.unk84 >= 0xE) {
        self->ext.et_801C5C78.unk84 = 0;
    }

    posY = self->posY.i.hi;
    scrollY = g_Tilemap.scrollY.i.hi;

    if (posY >= 0) {
        scrollY %= 32;
        if (params) {
            clut = 0x90;
        } else {
            clut = 0xB0;
        }
        clut = 0xB0;
        clut += self->ext.et_801C5C78.unk84;

        if (((scrollY + posY) - 0x50) > 0x60) {
            scrollYModulo = 0x60 - scrollY;
        }
        scrollYModulo = 0x60;

        prim->clut = clut;

        if (params) {
            xOffset = self->posX.i.hi - 0xD;
            prim->v2 = (prim->v3 = 3);
            prim->x1 = (prim->x3 = xOffset + 0x1B);
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_UNK02 | DRAW_TRANSP;
        } else {
            xOffset = self->posX.i.hi - 7;
            prim->v2 = (prim->v3 = 0x83);
            prim->x1 = (prim->x3 = xOffset + 0xe);
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_UNK02 | DRAW_TRANSP;
        }

        prim->v0 = (prim->v1 = prim->v2 + 0x60);
        prim->x0 = (prim->x2 = xOffset);
        prim->y0 = (prim->y1 = 0x4C);
        prim->y2 = (prim->y3 = 0xAC);
        prim = prim->next;
        prim->clut = clut;

        if (params) {
            prim->v0 = (prim->v1 = 0x63);
            prim->v2 = (prim->v3 = 0x2f);
            prim->x0 = (prim->x2 = xOffset);
            prim->x1 = (prim->x3 = xOffset + 0x1B);
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_UNK02 | DRAW_TRANSP;
        } else {
            prim->v0 = (prim->v1 = 0xe3);
            prim->v2 = (prim->v3 = 0xaf);
            prim->x0 = (prim->x2 = xOffset);
            prim->x1 = (prim->x3 = xOffset + 0xe);
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_UNK02 | DRAW_TRANSP;
        }

        prim->y0 = (prim->y1 = 0xAC);
        prim->y2 = (prim->y3 = 0xE0);
        prim = prim->next;
    }
}

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C5EE4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C2850_from_no4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C2B78_from_no4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C2E60_from_no4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C3160_from_no4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C34EC_from_no4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C37C8_from_no4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C3A04_from_no4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C3CC4_from_no4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C3FB0_from_no4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C4228_from_no4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", EntityWaterBox);

#ifdef VERSION_PSP
extern s32 E_ID(UNK_26);
extern s32 E_ID(UNK_27);
#endif
extern s16 D_us_801814D4;

void func_us_801C81C8(Entity* self) {
    Entity* child;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = -0x7FFE;
        self->palette = 0x44;
        self->drawFlags = ENTITY_MASK_R;
        self->posX.i.hi = (0x1EF - g_Tilemap.scrollX.i.hi);
        child = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (child) {
            CreateEntityFromCurrentEntity(E_ID(UNK_27), child);
            child->params = 1;
        }
        self->ext.et_801C81C8.unk80 = child;
        child = AllocEntity(child, &g_Entities[256]);
        if (child) {
            CreateEntityFromCurrentEntity(E_ID(UNK_26), child);
            child->params = 1;
        }
        self->ext.et_801C81C8.unk84 = child;
        self->ext.et_801C81C8.unk7C = 0;
    }
    AnimateEntity(&D_us_801814D4, self);
}

void EntityFloatingIcePlatform(Entity* self) {
    extern u16 g_FloatingIcePlatformHitbox[];
    u16* hitboxPtr;
    u16 collision;
    Entity* player;
    s16 prevPosY;
    s16 dx, dy;
    u16 hitboxIndex;

    player = &PLAYER;
    hitboxIndex = self->params;

    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = hitboxIndex + 25;
        self->drawFlags = ENTITY_ROTATE;
        self->ext.floatingIcePlatform.baseY =
            self->posY.i.hi + g_Tilemap.scrollY.i.hi;
    }

    hitboxPtr = &g_FloatingIcePlatformHitbox[hitboxIndex * 2];

    prevPosY = self->posY.i.hi;
    self->posY.i.hi =
        self->ext.floatingIcePlatform.baseY - g_Tilemap.scrollY.i.hi +
        self->ext.floatingIcePlatform.bobOffset;
#ifdef VERSION_PSP
    collision = GetPlayerCollisionWith(self, hitboxPtr[0], hitboxPtr[1], 4);
#else
    collision = GetPlayerCollisionWith(self, *hitboxPtr++, *hitboxPtr, 4);
#endif
    self->posY.i.hi = prevPosY;
    self->ext.floatingIcePlatform.previousBobOffset =
        self->ext.floatingIcePlatform.bobOffset;

    dx = self->posX.i.hi - player->posX.i.hi;

    if (collision) {
        if (self->ext.floatingIcePlatform.bobOffset < 4) {
            self->ext.floatingIcePlatform.bobOffset++;
        }
    } else {
        if (self->ext.floatingIcePlatform.bobOffset) {
            self->ext.floatingIcePlatform.bobOffset--;
        }
    }

    dy = self->ext.floatingIcePlatform.bobOffset;
    if (dx < 0) {
        prevPosY = (dx * dy * -0x100) / 56;
    } else {
        prevPosY = (dx * dy * 0x100) / 56;
    }

    self->posY.i.hi = self->ext.floatingIcePlatform.baseY -
                      g_Tilemap.scrollY.i.hi + (dy - prevPosY / 256);

    if (collision) {
        dy = dy - self->ext.floatingIcePlatform.previousBobOffset;
        player->posY.i.hi += dy;
        g_unkGraphicsStruct.shoveX.i.hi += dy;
    }

    prevPosY = -prevPosY;
    if (collision || dy) {
        if (dx < 0) {
            self->rotate = ratan2(prevPosY, -0x3800);
            self->rotate = (self->rotate - 0x800) & 0xFFF;
            return;
        }
        self->rotate = ratan2(prevPosY, 0x3800);
    } else {
        self->rotate = 0;
    }
}

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C4BD8_from_no4);

void func_us_801C8668(Entity* self) {
    s32 i;
    u16* tile;
    Tilemap* tilemap;

    tilemap = &g_Tilemap;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        tile = tilemap->fg + 0x1052;

        for (i = 0; i < 5; ++i) {
            *tile = 0xac7;
            tile += 1;
        }
        *tile = 0x59D;
        tile = tilemap->fg + 0x1062;

        for (i = 0; i < 0xA; ++i) {
            *tile = 0xAC7;
            tile += 1;
        }
    }
}

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", RNO4_Unused801C8704);

void func_us_801C870C(Entity* self) {
    s16 i;
    u16* tilePtr;
    if (!self->params) {
        tilePtr = g_Tilemap.fg + 0x143;
    } else {
        tilePtr = g_Tilemap.fg + 0x53;
    }
    for (i = 0; i < 0xA; ++i) {
        *(tilePtr++) = 0;
    }
}
