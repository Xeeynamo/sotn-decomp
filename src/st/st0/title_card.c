// SPDX-License-Identifier: AGPL-3.0-or-later
#include "st0.h"
#include "sfx.h"

#if defined(VERSION_PSP)
extern s32 D_80180908;
extern u8 D_pspeu_09253FB0[];
extern u8 D_pspeu_09253FF0[];
extern u8 D_pspeu_09254300[];
extern u8 D_pspeu_092545D8[];
extern u8 D_pspeu_092548E8[];
extern u8 D_pspeu_09254BD8[];
extern u16 D_pspeu_09254E98[];
extern u8* D_pspeu_09254EA4;
#else
static s32 D_80180908 = 0;
#endif

void EntityStageTitleFadeout(Entity* self) {
    Primitive* prim;
    s32 var_s2;
    s32 var_s1;
    s32 primIndex;

    switch (self->step) {
    case 0:
        if (D_80180908) {
            DestroyEntity(self);
            return;
        }
        InitializeEntity(g_EInit3DObject);
        primIndex = g_api.AllocPrimitives(PRIM_G4, 5);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->primIndex = primIndex;
        self->flags |= FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[primIndex];
        self->ext.stageTitleCard.prim = prim;
        while (prim) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        prim = self->ext.stageTitleCard.prim;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0x100;
        prim->y0 = prim->y1 = 0;
        prim->y2 = prim->y3 = 0xF0;
        prim->r0 = prim->g0 = prim->b0 = 0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0x1FD;
        prim->drawMode = DRAW_DEFAULT;
        self->ext.stageTitleCard.unk88 = 0x20;
    case 1:
        if (D_80180908) {
            prim = self->ext.stageTitleCard.prim;
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
            prim->r0 = prim->g0 = prim->b0 = 247;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            self->step++;
        }
        break;
    case 2:
        prim = self->ext.stageTitleCard.prim;
        prim = prim->next;
        prim->priority = 0xC0;
        prim->drawMode = DRAW_DEFAULT;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0x100;
        prim->y0 = prim->y1 = 0;
        prim->y2 = prim->y3 = 0xF0;
        prim->r0 = prim->g0 = prim->b0 = 0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        PLAYER.zPriority = 0xD0;
        self->step++;
    case 3:
        PLAYER.zPriority = 0xD0;
        prim = self->ext.stageTitleCard.prim;
        prim->r0 -= 8;
        if (prim->r0 > 248) {
            prim->r0 = 0;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            prim->drawMode = DRAW_DEFAULT;
            self->step = 5;
            break;
        }
        prim->g0 = prim->b0 = prim->r0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        break;
    case 4:
        PLAYER.zPriority = 0xD0;
        prim = self->ext.stageTitleCard.prim;
        prim = prim->next;
        prim->r0 -= 8;
        if (prim->r0 > 248) {
            prim->r0 = 0;
            prim->drawMode = DRAW_HIDE;
            PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter;
            self->step = 1;
        }
        prim->g0 = prim->b0 = prim->r0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        break;
    case 5:
        prim = self->ext.stageTitleCard.prim;
        while (prim) {
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
        LOW(prim->r2) = LOW(prim->r0);
        prim->r1 = prim->g1 = prim->b1 = 0;
        LOW(prim->r3) = LOW(prim->r1);
        prim = prim->next;

        prim->x1 = prim->x3 = 0x100;
        prim = prim->next;

        prim->r0 = prim->g0 = prim->b0 = 0;
        LOW(prim->r2) = LOW(prim->r0);
        prim->r1 = prim->g1 = prim->b1 = 255;
        LOW(prim->r3) = LOW(prim->r1);
        prim = prim->next;

        var_s1 = PLAYER.posX.i.hi;
        self->ext.stageTitleCard.unk80 = self->ext.stageTitleCard.unk84 =
            var_s1;
        self->ext.stageTitleCard.unk88 = 32;
        self->step++;
    case 6:
        if (self->ext.stageTitleCard.unk88) {
            if (!--self->ext.stageTitleCard.unk88) {
                g_Entities[PLAYER_CHARACTER].zPriority =
                    g_unkGraphicsStruct.g_zEntityCenter;
            }
        }
        var_s1 = self->ext.stageTitleCard.unk80;
        var_s2 = self->ext.stageTitleCard.unk84;
        var_s1 -= 4;
        var_s2 += 4;

        prim = self->ext.stageTitleCard.prim;
        prim->x1 = prim->x3 = var_s1;
        prim = prim->next;

        prim->x0 = prim->x2 = var_s1;
        prim->x1 = prim->x3 = var_s1 + 0x40;
        prim = prim->next;

        prim->x0 = prim->x2 = var_s2;
        prim = prim->next;

        prim->x1 = prim->x3 = var_s2;
        prim->x0 = prim->x2 = var_s2 - 0x40;
        prim = prim->next;

        if ((var_s1 < -0x40) && (var_s2 > 0x140)) {

            for (prim = self->ext.stageTitleCard.prim; prim != NULL;
                 prim = prim->next) {
                prim->drawMode = DRAW_HIDE;
            }
            PreventEntityFromRespawning(self);
            DestroyEntity(self);
            break;
        }
        self->ext.stageTitleCard.unk80 = var_s1;
        self->ext.stageTitleCard.unk84 = var_s2;
        break;
    }
}

void EntityStageTitleCard(Entity* self) {
#if defined(VERSION_PSP)
    // on PSP the title card is 8px taller
    const int TexHeightMod = 8;
#else
    const int TexHeightMod = 0;
#endif
    Primitive* prim; // s0
    VertexFake* v;   // s1
    s16 angle;       // s2
    s32 i;           // s3
    s32 var_s4;      // s4
    s32 var_s5;      // s5
    s32 primIndex;   // s6

    switch (self->step) {
    case 0:
        if (D_80180908) {
            DestroyEntity(self);
            return;
        }
        InitializeEntity(g_EInit3DObject);
#if defined(VERSION_PSP)
        D_pspeu_09254EA4 =
            GetLang(D_pspeu_09253FF0, D_pspeu_09254BD8, D_pspeu_092545D8,
                    D_pspeu_092548E8, D_pspeu_09254300);
        func_91040A0(D_pspeu_09254E98);
        func_892667C(0x8210, D_pspeu_09253FB0);
#endif
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
        if (primIndex == -1) {
            D_80180908 = 1;
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.stageTitleCard.prim = prim;
        prim->type = PRIM_GT3;
        prim->tpage = 0x1A;
        prim->clut = 0x15F;
        prim->u0 = prim->u2 = 0x10;
        prim->u1 = prim->u3 = 0x18;
        prim->v0 = prim->v1 = 0x10;
        prim->v2 = prim->v3 = 0x18;
        prim->r0 = prim->g0 = 8;
        prim->b0 = 0x60;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        prim->priority = 0x1FE;
        prim->drawMode = DRAW_COLORS;
        prim = prim->next;

        prim->tpage = 0x11;
        prim->clut = 0x210;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x6F;
        prim->v0 = prim->v1 = 0;
        prim->v2 = prim->v3 = 0xF + TexHeightMod;
#if defined(VERSION_PSP)
        prim->y0 = prim->y1 = 0x70;
        prim->y2 = prim->y3 = 0x7F + TexHeightMod;
        prim->priority = 0x1FF;
        prim->drawMode = DRAW_DEFAULT;
        prim->x0 = prim->x2 = -0x6F;
        prim->x1 = prim->x3 = 0;
#else
        prim->x0 = prim->x2 = -0x6F;
        prim->y0 = prim->y1 = 0x70;
        prim->priority = 0x1FF;
        prim->drawMode = DRAW_DEFAULT;
        prim->x1 = prim->x3 = 0;
        prim->y2 = prim->y3 = 0x7F + TexHeightMod;
#endif
        prim = prim->next;

        prim->tpage = 0x11;
        prim->clut = 0x210;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x7F;
        prim->v0 = prim->v1 = 0x10 + TexHeightMod;
        prim->v2 = prim->v3 = 0x2A;
#if defined(VERSION_PSP)
        prim->y0 = prim->y1 = 0x80 + TexHeightMod;
        prim->y2 = prim->y3 = 0x9A;
        prim->priority = 0x1FF;
        prim->drawMode = DRAW_DEFAULT;
        prim->x0 = prim->x2 = 0x100;
        prim->x1 = prim->x3 = 0x17F;
#else
        prim->x0 = prim->x2 = 0x100;
        prim->priority = 0x1FF;
        prim->drawMode = DRAW_DEFAULT;
        prim->x1 = prim->x3 = 0x17F;
        prim->y0 = prim->y1 = 0x80 + TexHeightMod;
        prim->y2 = prim->y3 = 0x9A;
#endif
        prim = prim->next;

        while (prim) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        g_PauseAllowed = false;
        self->ext.stageTitleCard.unk88 = 0x10;
    case 1:
        if (!--self->ext.stageTitleCard.unk88) {
            self->step++;
        }
        break;
    case 2:
        var_s5 = 0;
        prim = self->ext.stageTitleCard.prim;
        self->ext.stageTitleCard.unk8E += 6;
        if (self->ext.stageTitleCard.unk8E > 0x20) {
            self->ext.stageTitleCard.unk8E = 0x20;
            var_s5 += 1;
        }
        var_s4 = self->ext.stageTitleCard.unk8E;
        v = (VertexFake*)&prim->x0;
        angle = self->ext.stageTitleCard.unk8C + 0x400;
        for (i = 0; i < 3; i++) {
            v->x = (var_s4 * rcos(angle) >> 0xC) + 0x60;
            v->y = (var_s4 * rsin(angle) >> 0xC) + 0x80;
            v++;
            angle += 0x555;
        }
        prim = prim->next;

        if (prim->x0 < 0x40) {
            prim->x0 += 8;
        } else {
            prim->x0 = 0x40;
            var_s5++;
        }
        prim->x2 = prim->x0;
        prim->x1 = prim->x3 = prim->x0 + 0x6F;
        prim = prim->next;

        if (prim->x0 > 0x40) {
            prim->x0 -= 6;
        } else {
            prim->x0 = 0x40;
            var_s5++;
        }
        prim->x2 = prim->x0;
        prim->x1 = prim->x3 = prim->x0 + 0x7F;
        prim = prim->next;

        if (var_s5 == 3) {
            self->step++;
        }
        break;
    case 3:
        prim = self->ext.stageTitleCard.prim;
        prim->drawMode |= DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        prim = prim->next;

        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x7F;
        prim->v0 = prim->v1 = 0;
        prim->v2 = prim->v3 = 0x2A;
        prim->x0 = prim->x2 = 0x40;
        prim->x1 = prim->x3 = 0xBF;
        prim->y0 = prim->y1 = 0x70;
        prim->y2 = prim->y3 = 0x9A;
        prim->r0 = prim->g0 = prim->b0 = 0x80;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        prim = prim->next;

        while (prim) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
#if defined(VERSION_PSP)
        D_80180908 = 1;
        self->ext.stageTitleCard.unk88 = 0x10;
#else
        self->ext.stageTitleCard.unk88 = 0x20;
#endif
        self->step++;
        break;
    case 4:
#if defined(VERSION_US)
        if (self->ext.stageTitleCard.unk88 == 0x10) {
            D_80180908 = 1;
        }
#endif
        if (!--self->ext.stageTitleCard.unk88) {
            self->step++;
        }
        break;
    case 5:
        prim = self->ext.stageTitleCard.prim;
        angle = self->ext.stageTitleCard.unk8C + 0x400;
        self->ext.stageTitleCard.unk8C -= 4;
        var_s4 = self->ext.stageTitleCard.unk8E;
        v = (VertexFake*)&prim->x0;
        for (i = 0; i < 3; i++) {
            v->x = (var_s4 * rcos(angle) >> 0xC) + 0x60;
            v->y = (var_s4 * rsin(angle) >> 0xC) + 0x80;
            v++;
            angle += 0x555;
        }
        PrimDecreaseBrightness(prim, 4);
        prim = prim->next;
        if (PrimDecreaseBrightness(prim, 3) == 0) {
            PreventEntityFromRespawning(self);
            g_PauseAllowed = true;
            DestroyEntity(self);
        }
        break;
    }
    g_Player.D_80072EFC = 4;
    g_Player.padSim = 0;
}
