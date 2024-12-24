// SPDX-License-Identifier: AGPL-3.0-or-later
#include "st0.h"
#include "sfx.h"

static s32 D_80180908 = 0;
void EntityStageTitleFadeout(Entity* self) {
    s16 primIndex;
    Primitive* prim;
    s32 temp_a0;
    s32 temp_a1;
    s32 posX;

    switch (self->step) {
    case 0:
        if (D_80180908 != 0) {
            DestroyEntity(self);
            return;
        }

        InitializeEntity(g_EInit3DObject);
        primIndex = g_api.AllocPrimitives(PRIM_G4, 5);
        if (primIndex != -1) {
            prim = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
            self->ext.stageTitleCard.prim = prim;
            self->flags |= FLAG_HAS_PRIMS;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            prim = self->ext.stageTitleCard.prim;
            prim->r0 = prim->g0 = prim->b0 = 0;
            prim->x1 = prim->x3 = 0x100;
            prim->y2 = prim->y3 = 0xF0;
            prim->priority = 0x1FD;
            prim->y0 = prim->y1 = prim->x0 = prim->x2 = 0;
            prim->drawMode = DRAW_DEFAULT;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            self->ext.stageTitleCard.unk88 = 0x20;
        } else {
            DestroyEntity(self);
            break;
        }

    case 1:
        if (D_80180908 != 0) {
            prim = self->ext.stageTitleCard.prim;
            prim->r0 = prim->g0 = prim->b0 = 247;
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
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
        prim->drawMode = DRAW_DEFAULT;
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
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            prim->drawMode = DRAW_DEFAULT;
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
            prim->drawMode = DRAW_HIDE;
            PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter;
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
            prim->drawMode =
                DRAW_UNK_40 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
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
                    g_unkGraphicsStruct.g_zEntityCenter;
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

            for (prim = self->ext.stageTitleCard.prim; prim != NULL;
                 prim = prim->next) {
                prim->drawMode = DRAW_HIDE;
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

void EntityStageTitleCard(Entity* self) {
    Entity* fakeEntity; // !FAKE
    s16 primIndex;
    Primitive* prim;
    VertexFake* v;
    s16 temp_unk8E;
    s32 var_s7;
    s16 angle;
    s32 i;
    s32 j;

    switch (self->step) {
    case 0:
        if (D_80180908 == 0) {
            InitializeEntity(g_EInit3DObject);
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
            if (primIndex == -1) {
                D_80180908 = 1;
            label:
                DestroyEntity(self);
                return;
            }
            prim = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
            self->ext.stageTitleCard.prim = prim;
            self->flags |= FLAG_HAS_PRIMS;
            prim->type = PRIM_GT3;
            prim->tpage = 0x1A;
            prim->clut = 0x15F;
            prim->v2 = prim->v3 = prim->u1 = prim->u3 = 0x18;
            prim->r0 = prim->g0 = 8;
            prim->b0 = 0x60;
            prim->priority = 0x1FE;
            prim->v0 = prim->v1 = prim->u0 = prim->u2 = 0x10;
            prim->drawMode = DRAW_COLORS;
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
            prim->drawMode = DRAW_DEFAULT;
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
            prim->drawMode = DRAW_DEFAULT;
            prim->y2 = prim->y3 = 0x9A;

            prim = prim->next;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            g_PauseAllowed = false;
            self->ext.stageTitleCard.unk88 = 0x10;
        } else {
            goto label;
        }

    case 1:
        if (--self->ext.stageTitleCard.unk88 == 0) {
            self->step++;
        }
        g_Player.D_80072EFC = 4;
        g_Player.padSim = 0;
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

        temp_unk8E = self->ext.stageTitleCard.unk8E;
        angle = self->ext.stageTitleCard.unk8C + 0x400;

        v = (VertexFake*)&prim->x0;
        for (i = 0; i < 3; i++) {
            v->x = (temp_unk8E * rcos(angle) >> 0xC) + 0x60;
            v->y = (temp_unk8E * rsin(angle) >> 0xC) + 0x80;
            angle += 0x555;
            v++;
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
        g_Player.padSim = 0;
        break;

    case 3:
        prim = self->ext.stageTitleCard.prim;
        prim->drawMode |= DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;

        prim = prim->next;
        prim->u1 = prim->u3 = 0x7F;
        prim->v2 = prim->v3 = 0x2A;
        prim->x0 = prim->x2 = 0x40;
        prim->x1 = prim->x3 = 0xBF;
        prim->y0 = prim->y1 = 0x70;
        prim->y2 = prim->y3 = 0x9A;
        prim->r0 = prim->g0 = prim->b0 = 0x80;
        prim->v0 = prim->v1 = prim->u0 = prim->u2 = 0;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);

        for (prim = prim->next; prim != NULL; prim = prim->next) {
            prim->drawMode = DRAW_HIDE;
        }
        self->ext.stageTitleCard.unk88 = 0x20;
        self->step++;
        g_Player.D_80072EFC = 4;
        g_Player.padSim = 0;
        break;

    case 4:
        if (self->ext.stageTitleCard.unk88 == 0x10) {
            D_80180908 = 1;
        }
        if (--self->ext.stageTitleCard.unk88 == 0) {
            self->step++;
        }
        g_Player.D_80072EFC = 4;
        g_Player.padSim = 0;
        return;

    case 5:
        prim = self->ext.stageTitleCard.prim;
        angle = self->ext.stageTitleCard.unk8C + 0x400;
        self->ext.stageTitleCard.unk8C -= 4;
        temp_unk8E = self->ext.stageTitleCard.unk8E;

        fakeEntity = self; // !FAKE

        v = (VertexFake*)&prim->x0;
        for (j = 0; j < 3; j++) {
            v->x = (temp_unk8E * rcos(angle) >> 0xC) + 0x60;
            v->y = (temp_unk8E * rsin(angle) >> 0xC) + 0x80;
            angle += 0x555;
            v++;
        }

        PrimDecreaseBrightness(prim, 4);
        if (PrimDecreaseBrightness(prim->next, 3) == 0) {
            PreventEntityFromRespawning(fakeEntity);
            g_PauseAllowed = true;
            DestroyEntity(fakeEntity);
        }
    default:
        g_Player.D_80072EFC = 4;
        g_Player.padSim = 0;
        break;
    }
}
