#include "st0.h"

void EntityStageTitleFadeout(Entity* self) {
    s16 firstPrimIndex;
    Primitive* prim;
    s32 temp_a0;
    s32 temp_a1;
    s32 posX;

    switch (self->step) {
    case 0:
        if (D_80180908 == 0) {
            InitializeEntity(D_801805D4);
            firstPrimIndex = g_api.AllocPrimitives(PRIM_G4, 5);
            if (firstPrimIndex != -1) {
                prim = &g_PrimBuf[firstPrimIndex];
                self->firstPolygonIndex = firstPrimIndex;
                self->ext.stageTitleCard.prim = prim;
                self->flags |= FLAG_FREE_POLYGONS;
                while (prim != NULL) {
                    prim->blendMode = 8;
                    prim = prim->next;
                }
                prim = self->ext.stageTitleCard.prim;
                prim->r0 = prim->g0 = prim->b0 = 0;
                prim->x1 = prim->x3 = 0x100;
                prim->y2 = prim->y3 = 0xF0;
                prim->priority = 0x1FD;
                prim->y0 = prim->y1 = prim->x0 = prim->x2 = 0;
                prim->blendMode = 0;
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                self->ext.stageTitleCard.unk88 = 0x20;
            } else {
                DestroyEntity(self);
                break;
            }
        } else {
            DestroyEntity(self);
            break;
        }

    case 1:
        if (D_80180908 != 0) {
            prim = self->ext.stageTitleCard.prim;
            prim->r0 = prim->g0 = prim->b0 = 247;
            prim->blendMode = 0x51;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            self->step++;
        }
        break;

    case 2:
        prim = self->ext.stageTitleCard.prim;
        prim = prim->next;
        prim->r0 = prim->g0 = prim->b0 = 0;
        prim->priority = 0xC0;
        prim->x1 = prim->x3 = 0x100;
        prim->y2 = prim->y3 = 0xF0;
        prim->blendMode = 0;
        prim->y0 = prim->y1 = prim->x0 = prim->x2 = 0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        PLAYER.zPriority = 0xD0;
        self->step++;

    case 3:
        PLAYER.zPriority = 0xD0;
        prim = self->ext.stageTitleCard.prim;
        prim->r0 += 248;
        if (prim->r0 > 248) {
            prim->r0 = 0;
            prim->blendMode = 8;
            prim = prim->next;
            prim->blendMode = 0;
            self->step = 5;
            break;
        }
        prim->g0 = prim->b0 = LOW(prim->r0);
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        break;

    case 4:
        PLAYER.zPriority = 0xD0;
        prim = self->ext.stageTitleCard.prim;
        prim = prim->next;
        prim->r0 += 248;
        if (prim->r0 > 248) {
            prim->r0 = 0;
            prim->blendMode = 8;
            PLAYER.zPriority = g_zEntityCenter.S16.unk0;
            self->step = 1;
        }
        prim->g0 = prim->b0 = LOW(prim->r0);
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        break;

    case 5:
        prim = self->ext.stageTitleCard.prim;
        while (prim != NULL) {
            prim->y0 = prim->y1 = 0;
            prim->y2 = prim->y3 = 0xF0;
            prim->priority = 0xB0;
            prim->blendMode = 0x55;
            prim->r0 = prim->g0 = prim->b0 = 255;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim = prim->next;
        }
        prim = self->ext.stageTitleCard.prim;
        prim->x0 = prim->x2 = 0;

        prim = prim->next;
        prim->r0 = prim->g0 = prim->b0 = 255;
        prim->r1 = prim->g1 = prim->b1 = 0;
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r1);

        prim = prim->next;
        prim->x1 = prim->x3 = 0x100;

        prim = prim->next;
        prim->r0 = prim->g0 = prim->b0 = 0;
        prim->r1 = prim->g1 = prim->b1 = 255;
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r1);

        posX = PLAYER.posX.i.hi;
        self->ext.stageTitleCard.unk88 = 32;
        self->ext.stageTitleCard.unk84 = posX;
        self->ext.stageTitleCard.unk80 = posX;
        self->step++;

    case 6:
        if (self->ext.stageTitleCard.unk88 != 0) {
            self->ext.stageTitleCard.unk88--;
            if (self->ext.stageTitleCard.unk88 == 0) {
                g_Entities[PLAYER_CHARACTER].zPriority =
                    g_zEntityCenter.S16.unk0;
            }
        }
        temp_a0 = self->ext.stageTitleCard.unk80;
        temp_a1 = self->ext.stageTitleCard.unk84;
        prim = self->ext.stageTitleCard.prim;
        temp_a0 -= 4;
        temp_a1 += 4;
        prim->x1 = prim->x3 = temp_a0;

        prim = prim->next;
        prim->x0 = prim->x2 = temp_a0;
        prim->x1 = prim->x3 = temp_a0 + 0x40;

        prim = prim->next;
        prim->x0 = prim->x2 = temp_a1;

        prim = prim->next;
        prim->x1 = prim->x3 = temp_a1;
        prim->x0 = prim->x2 = temp_a1 - 0x40;

        if ((temp_a0 < -0x40) && (temp_a1 > 0x140)) {
            prim = self->ext.stageTitleCard.prim;
            while (prim != 0) {
                prim->blendMode = 8;
                prim = prim->next;
            }
            PreventEntityFromRespawning(self);
            DestroyEntity(self);
            break;
        }
        self->ext.stageTitleCard.unk80 = temp_a0;
        self->ext.stageTitleCard.unk84 = temp_a1;
        break;
    }
}

const u32 rodataPadding_801A7AFC = 0;

void EntityStageTitleCard(Entity* self) {
    Entity* fakeEntity; // !FAKE
    s16 firstPrimIndex;
    Primitive* prim;
    Triangle* triangle;
    s16 temp_unk8E;
    s32 var_s7;
    s16 angle;
    s32 i;
    s32 j;

    switch (self->step) {
    case 0:
        if (D_80180908 == 0) {
            InitializeEntity(D_801805D4);
            firstPrimIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
            if (firstPrimIndex == -1) {
                D_80180908 = 1;
            label:
                DestroyEntity(self);
                return;
            }
            prim = &g_PrimBuf[firstPrimIndex];
            self->firstPolygonIndex = firstPrimIndex;
            self->ext.stageTitleCard.prim = prim;
            self->flags |= FLAG_FREE_POLYGONS;
            prim->type = 5;
            prim->tpage = 0x1A;
            prim->clut = 0x15F;
            prim->v2 = prim->v3 = prim->u1 = prim->u3 = 0x18;
            prim->r0 = prim->g0 = 8;
            prim->b0 = 0x60;
            prim->priority = 0x1FE;
            prim->v0 = prim->v1 = prim->u0 = prim->u2 = 0x10;
            prim->blendMode = 4;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);

            prim = prim->next;
            prim->u1 = prim->u3 = 0x6F;
            prim->tpage = 0x11;
            prim->clut = 0x210;
            prim->v0 = prim->v1 = prim->u0 = prim->u2 = 0;
            prim->v2 = prim->v3 = 0xF;
            prim->x0 = prim->x2 = -0x6F;
            prim->y0 = prim->y1 = 0x70;
            prim->priority = 0x1FF;
            prim->blendMode = 0;
            prim->x1 = prim->x3 = 0;
            prim->y2 = prim->y3 = 0x7F;

            prim = prim->next;
            prim->u1 = prim->u3 = 0x7F;
            prim->v2 = prim->v3 = 0x2A;
            prim->x0 = prim->x2 = 0x100;
            prim->x1 = prim->x3 = 0x17F;
            prim->y0 = prim->y1 = 0x80;
            prim->tpage = 0x11;
            prim->clut = 0x210;
            prim->u0 = prim->u2 = 0;
            prim->v0 = prim->v1 = 0x10;
            prim->priority = 0x1FF;
            prim->blendMode = 0;
            prim->y2 = prim->y3 = 0x9A;

            prim = prim->next;
            while (prim != NULL) {
                prim->blendMode = 8;
                prim = prim->next;
            }
            D_8003C8B8 = 0;
            self->ext.stageTitleCard.unk88 = 0x10;
        } else {
            goto label;
        }

    case 1:
        if (--self->ext.stageTitleCard.unk88 == 0) {
            self->step++;
        }
        g_Player.D_80072EFC = 4;
        g_Player.D_80072EF4 = 0;
        break;

    case 2:
        prim = self->ext.stageTitleCard.prim;
        self->ext.stageTitleCard.unk8E += 6;
        if (self->ext.stageTitleCard.unk8E > 0x20) {
            self->ext.stageTitleCard.unk8E = 0x20;
            var_s7 = 1;
        } else {
            var_s7 = 0;
        }

        triangle = (Triangle*)&prim->x0;
        temp_unk8E = self->ext.stageTitleCard.unk8E;
        angle = self->ext.stageTitleCard.unk8C + 0x400;

        for (i = 0; i < 3; i++) {
            triangle->x0 = (temp_unk8E * rcos(angle) >> 0xC) + 0x60;
            triangle->y0 = (temp_unk8E * rsin(angle) >> 0xC) + 0x80;
            angle += 0x555;
            triangle++;
        }

        prim = prim->next;
        if (prim->x0 < 0x40) {
            prim->x0 = prim->x0 + 8;
        } else {
            prim->x0 = 0x40;
            var_s7++;
        }
        prim->x2 = prim->x0;
        prim->x1 = prim->x3 = prim->x0 + 0x6F;

        prim = prim->next;
        if (prim->x0 > 0x40) {
            prim->x0 -= 6;
        } else {
            prim->x0 = 0x40;
            var_s7++;
        }
        prim->x2 = prim->x0;
        prim->x1 = prim->x3 = prim->x0 + 0x7F;

        if (var_s7 == 3) {
            self->step++;
        }
        g_Player.D_80072EFC = 4;
        g_Player.D_80072EF4 = 0;
        break;

    case 3:
        prim = self->ext.stageTitleCard.prim;
        prim->blendMode |= 0x31;

        prim = prim->next;
        prim->u1 = prim->u3 = 0x7F;
        prim->v2 = prim->v3 = 0x2A;
        prim->x0 = prim->x2 = 0x40;
        prim->x1 = prim->x3 = 0xBF;
        prim->y0 = prim->y1 = 0x70;
        prim->y2 = prim->y3 = 0x9A;
        prim->r0 = prim->g0 = prim->b0 = 0x80;
        prim->v0 = prim->v1 = prim->u0 = prim->u2 = 0;
        prim->blendMode = 0x35;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);

        prim = prim->next;
        while (prim != NULL) {
            prim->blendMode = 8;
            prim = prim->next;
        }
        self->ext.stageTitleCard.unk88 = 0x20;
        self->step++;
        g_Player.D_80072EFC = 4;
        g_Player.D_80072EF4 = 0;
        break;

    case 4:
        if (self->ext.stageTitleCard.unk88 == 0x10) {
            D_80180908 = 1;
        }
        if (--self->ext.stageTitleCard.unk88 == 0) {
            self->step++;
        }
        g_Player.D_80072EFC = 4;
        g_Player.D_80072EF4 = 0;
        return;

    case 5:
        prim = self->ext.stageTitleCard.prim;
        angle = self->ext.stageTitleCard.unk8C + 0x400;
        triangle = (Triangle*)&prim->x0;
        self->ext.stageTitleCard.unk8C -= 4;
        temp_unk8E = self->ext.stageTitleCard.unk8E;

        fakeEntity = self; // !FAKE

        for (j = 0; j < 3; j++) {
            triangle->x0 = (temp_unk8E * rcos(angle) >> 0xC) + 0x60;
            triangle->y0 = (temp_unk8E * rsin(angle) >> 0xC) + 0x80;
            angle += 0x555;
            triangle++;
        }

        func_801BD88C(prim, 4);
        if (func_801BD88C(prim->next, 3) == 0) {
            PreventEntityFromRespawning(fakeEntity);
            D_8003C8B8 = 1;
            DestroyEntity(fakeEntity);
        }
    default:
        g_Player.D_80072EFC = 4;
        g_Player.D_80072EF4 = 0;
        break;
    }
}

INCLUDE_ASM("asm/us/st/st0/nonmatchings/2B0C8", func_801ABBBC);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/2B0C8", func_801AC458);