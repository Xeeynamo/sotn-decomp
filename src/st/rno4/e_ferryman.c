// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno4.h"

static u16 arr_indexes[] = {
    0x0000, 0x0000, 0x0000, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001,
    0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001};

static u8 D_us_801816D4[2][4] = {
    {0xC1, 0xDF, 0xE1, 0xFF}, {0xF4, 0xFC, 0x9C, 0xFC}};

static s16 D_us_801816DC[] = {0x0410, 0x0030, 0x0410, 0x01A0, 0x0500, 0x0030,
                              0x02E0, 0x0030, 0x02E0, 0x01A0, 0x01F0, 0x0030};

static s16 D_us_801816F4[] = {
    0x0000, 0x0422, 0xFFF0, 0x0000, 0x0422, 0x0050, 0x0000, 0x0422, 0x00B0,
    0x0000, 0x0422, 0x0110, 0x0001, 0x03FE, 0x0000, 0x0001, 0x03FE, 0x0060,
    0x0001, 0x03FE, 0x00C0, 0x0001, 0x03FE, 0x0120, 0x0002, 0x0438, 0x0042,
    0x0002, 0x0498, 0x0042, 0x0000, 0x02CE, 0xFFF0, 0x0000, 0x02CE, 0x0050,
    0x0000, 0x02CE, 0x00B0, 0x0000, 0x02CE, 0x0110, 0x0001, 0x02F2, 0x0000,
    0x0001, 0x02F2, 0x0060, 0x0001, 0x02F2, 0x00C0, 0x0001, 0x02F2, 0x0120,
    0x0003, 0x0200, 0x0040, 0x0003, 0x0260, 0x0040};

static u16 tiles[7][2] = {
    {0x0000, 0x0000}, {0x0000, 0x0000}, {0x0000, 0x0000}, {0x0000, 0x0000},
    {0x0000, 0x0000}, {0x0000, 0x0000}, {0x0374, 0x0374},
};

void RNO4_Unused801C8768(s32 _) {}

void RNO4_Unused801C8770(s32 _) {}

void EntityBoatElevatorChains(Entity* self) {
    u32 primIndex;
    u32 scrollX;

    u32 scrollY;
    s16 cos;
    u8* ptr;
    s32 i;
    s16* ptrTwo;
    s16 sin;
    s16 xOffset;
    s16 yOffset;
    Primitive* prim;

    scrollX = g_Tilemap.scrollX.i.hi;
    scrollY = g_Tilemap.scrollY.i.hi;
    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 13);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];

            i = 0;
            while (prim != NULL) {
                prim->tpage = 0xF;
                prim->clut = 0x5F;
                ptr = *D_us_801816D4;
                ptr += arr_indexes[i] * 4;
                prim->u0 = prim->u2 = *ptr++;
                prim->u1 = prim->u3 = *ptr++;
                prim->v0 = prim->v1 = *ptr++;
                prim->v2 = prim->v3 = *ptr;
                prim->priority = 0x80;
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
                i++;
            }
            self->rotate = ROT(45);
        } else {
            self->step = 0;
            return;
        }
    }

    if (self->ext.boatElevator_child.unk7C) {
        if (self->ext.boatElevator_child.unk7C < 0) {
            self->ext.boatElevator_child.unk7E++;
            self->rotate += ROT(1.40625);
        } else {
            self->ext.boatElevator_child.unk7E--;
            self->rotate -= ROT(1.40625);
        }
    }
    self->ext.boatElevator_child.unk7E &= 0xF;
    prim = &g_PrimBuf[self->primIndex];
    i = 0;
    while (prim != NULL) {
        if (i < 3) {
            ptrTwo = &D_us_801816DC[(self->params * 6) + (i * 2)];
            xOffset = *ptrTwo++ - scrollX;
            yOffset = *ptrTwo - scrollY;
            if (self->params) {
                sin = (rsin(-self->rotate) * 0x1A) >> 0xC;
                cos = (rcos(-self->rotate) * 0x1A) >> 0xC;
            } else {
                sin = (rsin(self->rotate) * 0x1A) >> 0xC;
                cos = (rcos(self->rotate) * 0x1A) >> 0xC;
            }

            prim->x0 = xOffset - cos;
            prim->x1 = xOffset + sin;
            prim->x2 = xOffset - sin;
            prim->x3 = xOffset + cos;
            prim->y0 = yOffset - sin;
            prim->y1 = yOffset - cos;
            prim->y2 = yOffset + cos;
            prim->y3 = yOffset + sin;
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
        } else {
            ptrTwo = &D_us_801816F4[(self->params * 3) * 10 + ((i - 3) * 3)];
            sin = *ptrTwo++;
            xOffset = *ptrTwo++ - scrollX;
            yOffset = *ptrTwo - scrollY;
            switch (sin) {
            case 0:
                prim->x0 = prim->x2 = xOffset - 4;
                prim->x1 = prim->x3 = xOffset + 4;
                yOffset += self->ext.boatElevator_child.unk7E;
                prim->y0 = prim->y1 = yOffset;
                prim->y2 = prim->y3 = yOffset + 0x60;
                break;
            case 1:
                prim->x0 = prim->x2 = xOffset - 4;
                prim->x1 = prim->x3 = xOffset + 4;
                yOffset -= self->ext.boatElevator_child.unk7E;
                prim->y0 = prim->y1 = yOffset;
                prim->y2 = prim->y3 = yOffset + 0x60;
                break;
            case 2:
                xOffset -= self->ext.boatElevator_child.unk7E;
                prim->x0 = prim->x1 = xOffset;
                prim->x2 = prim->x3 = xOffset + 0x60;
                prim->y1 = prim->y3 = yOffset - 4;
                prim->y0 = prim->y2 = yOffset + 4;
                break;
            case 3:
                xOffset += self->ext.boatElevator_child.unk7E;
                prim->x0 = prim->x1 = xOffset;
                prim->x2 = prim->x3 = xOffset + 0x60;
                prim->y1 = prim->y3 = yOffset - 4;
                prim->y0 = prim->y2 = yOffset + 4;
                break;
            }
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
        }
        i++;
    }
}

void RNO4_Unused801C8BD4(s32 _) {}

void RNO4_Unused801C8BDC(s32 _) {}

void LoadFerrymanGateTiles(void) {
    u16* tileLayoutPtr;
    Tilemap* tileMap;
    s32 i;
    s16 offset;

    tileMap = &g_Tilemap;
    offset = 0xF89;
    tileLayoutPtr = *tiles;

    for (i = 0; i < LEN(tiles); i++) {
        tileMap->fg[offset] = *tileLayoutPtr++;
        offset++;
        tileMap->fg[offset] = *tileLayoutPtr++;
        offset += 0xCF;
    }
}

void func_us_801C8C54(Entity* self) {
    LoadFerrymanGateTiles();
    DestroyEntity(self);
}
