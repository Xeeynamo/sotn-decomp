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

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C5364);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", EntityBgColumnsParallax_from_no4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C1EE4_from_no4);

extern Tilemap* D_pspeu_0929B8B8; // This variable is assigned to a different
                                  // var that is never used

void func_us_801C5C78(Entity* self) {
    Primitive* prim;
    Tilemap** tilemap_pp_0;
    u32 primIndex;
    u32 xOffset;
#if defined(VERSION_PSP)
    u32 params;
#else
    u16 params;
#endif
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
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA | FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA | FLAG_HAS_PRIMS;
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
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        } else {
            xOffset = self->posX.i.hi - 7;
            prim->v2 = (prim->v3 = 0x83);
            prim->x1 = (prim->x3 = xOffset + 0xe);
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        }

        prim->v0 = (prim->v1 = prim->v2 + 0x60);
        prim->x0 = (prim->x2 = xOffset);
        prim->y0 = (prim->y1 = 0x4C);
        prim->y2 = (prim->y3 = 0xAC);
        prim = prim->next;
        prim->clut = clut;

        if (params != 0) {
            prim->v0 = (prim->v1 = 0x63);
            prim->v2 = (prim->v3 = 0x2f);
            prim->x0 = (prim->x2 = xOffset);
            prim->x1 = (prim->x3 = xOffset + 0x1B);
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        } else {
            prim->v0 = (prim->v1 = 0xe3);
            prim->v2 = (prim->v3 = 0xaf);
            prim->x0 = (prim->x2 = xOffset);
            prim->x1 = (prim->x3 = xOffset + 0xe);
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
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

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C81C8);

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
