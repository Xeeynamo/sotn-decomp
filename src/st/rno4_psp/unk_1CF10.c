// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno4/rno4.h"

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", RNO4_Unused801C8768);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", RNO4_Unused801C8770);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", EntityBoatElevatorChains);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", RNO4_Unused801C8BD4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", RNO4_Unused801C8BDC);

void LoadFerrymanGateTiles(void) {
    extern u16 g_FerrymanGateTiles[];
    u16* tileData;
    Tilemap* tilemap = &g_Tilemap;
    s16 tileIndex = 0xF89;
    s32 i;
    tileData = g_FerrymanGateTiles;

    for (i = 0; i < 7; i++) {
        tilemap->fg[tileIndex] = *tileData++;
        tileIndex++;
        tilemap->fg[tileIndex] = *tileData++;
        tileIndex += 0xCF;
    }
}

void func_us_801C8C54(Entity* self) {
    LoadFerrymanGateTiles();
    DestroyEntity(self);
}

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C12B0_from_no4);

extern s16 g_BackgroundTileRects[];

void func_us_801C15F8_from_no4(Entity* self) {
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

    if (self->step) {
    } else {
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
            prim->r0 = 0x10;
            prim->g0 = 8;
            prim->b0 = 0x18;
            prim->priority = 0x9D;
            prim = prim->next;
        }
    }

    prim = self->ext.et_801C12B0.prim;
    ptr = &g_BackgroundTileRects[(self->params & 0xFF) * 4];
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

        var_s4 = *ptr++;
        var_s5 = *ptr++;
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

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C5364);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", EntityBgColumnsParallax_from_no4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C1EE4_from_no4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C5C78);

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
    collision = GetPlayerCollisionWith(self, hitboxPtr[0], hitboxPtr[1], 4);
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

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C8668);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", RNO4_Unused801C8704);

void func_us_801C870C(Entity* self) {
    s16 i;
    u16* tilemap;

    if (!self->params) {
        tilemap = &g_Tilemap.fg[0x143];
    } else {
        tilemap = &g_Tilemap.fg[0x53];
    }

    for (i = 0; i < 10; i++) {
        *tilemap++ = 0;
    }
}
