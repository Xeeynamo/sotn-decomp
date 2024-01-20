#include "stage.h"

#ifndef CASTLE_FLAG_BANK
#define CASTLE_FLAG_BANK 0
#endif

s32 PrimDecreaseBrightness(Primitive* prim, u8 arg1);
void StageNamePopupHelper(Primitive* prim) {
    u8 xPos;
    s32 i;
    s32 j;

    switch (prim->p3) {
    case 0:
        if (prim->p1 < 0x80) {
            if (--prim->p1 == 0) {
                prim->p3 = 1;
            }
        } else {
            if (++prim->p1 == 0) {
                prim->p3 = 2;
            }
        }

        if (prim->p3 != 0) {
            u8* dst = prim->p3 == 1 ? &prim->r1 : &prim->r0;
            for (i = 0; i < 2; i++) {
                for (j = 0; j < 3; j++) {
                    dst[j] = 0x50;
                }
                dst += 0x18;
            }
            prim->p2 = 0;
        }
        break;
    case 1:
        if (prim->p2 < 0x14) {
            prim->p2++;
        }
        xPos = prim->p2 / 5;
        prim->x2 = prim->x0 = prim->x0 + xPos;
        prim->x1 = prim->x1 + xPos;
        prim->x3 = prim->x0;
        PrimDecreaseBrightness(prim, 4);
        break;
    case 2:
        if (prim->p2 < 0x14) {
            prim->p2++;
        }
        xPos = prim->p2 / 5;
        prim->x2 = prim->x0 = prim->x0 - xPos;
        prim->x1 = prim->x1 - xPos;
        prim->x3 = prim->x0;
        PrimDecreaseBrightness(prim, 4);
        break;
    }
}

extern u16 g_EInitGeneric[];
void EntityStageNamePopup(Entity* self) {
    u8 pad[100];
    Primitive* prim;
    s16 primIndex;
    u8 var_a0;
    s32 i;
    s32 drawMode;

    switch (self->step) {
    case 0:
        if (g_DemoMode != Demo_None ||
            g_CastleFlags[CASTLE_FLAG_BANK + 2] != 0) {
            DestroyEntity(self);
            return;
        }

        InitializeEntity(g_EInitGeneric);
        primIndex = g_api_AllocPrimitives(PRIM_GT4, 0x57);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.stpopup.prim = prim;
        self->flags |= 0x800000;
        while (prim != NULL) {
            prim->drawMode = 8;
            prim = prim->next;
        }
        prim = self->ext.stpopup.prim;
        for (i = 0; i < 2; i++) {
            prim->tpage = 0x11;
            prim->clut = 0x19F;
            prim->u0 = prim->u2 = 4;
            prim->u1 = prim->u3 = 0x78;
            prim->v0 = prim->v1 = 0;
            prim->v2 = prim->v3 = 0x28;
            prim->x2 = prim->x0 = 0xC;
            prim->y1 = prim->y0 = 0x9D;
            prim->x3 = prim->x1 = 0x80;
            prim->y3 = prim->y2 = 0xC5;
            prim->priority = 0xC0 - i;
            prim->drawMode = 8;
            prim = prim->next;

            prim->tpage = 0x11;
            prim->clut = 0x19F;
            prim->u0 = prim->u2 = 8;
            prim->u1 = prim->u3 = 0x7C;
            prim->v0 = prim->v1 = 0x40;
            prim->v2 = prim->v3 = 0x68;
            prim->x2 = prim->x0 = 0x80;
            prim->y1 = prim->y0 = 0x9D;
            prim->x3 = prim->x1 = 0xF4;
            prim->y3 = prim->y2 = 0xC5;
            prim->priority = 0xC0 - i;
            prim->drawMode = 8;
            prim = prim->next;
        }

        i = 0;
        self->ext.stpopup.unk88 = prim;
        prim->tpage = 0x11;
        prim->clut = 0x19D;
        prim->u0 = prim->u2 = 4;
        prim->u1 = prim->u3 = 0x78;
        prim->v0 = prim->v1 = 0;
        prim->v2 = prim->v3 = 0x28;
        prim->x2 = prim->x0 = 0xC;
        prim->y1 = prim->y0 = 0x9D;
        prim->x3 = prim->x1 = 0x80;
        prim->y3 = prim->y2 = 0xC5;
        prim->priority = 0xBF;
        prim->drawMode = 8;
        prim = prim->next;

        prim->clut = 0x19D;
        prim->tpage = 0x11;
        prim->u0 = prim->u2 = 8;
        prim->u1 = prim->u3 = 0x7C;
        prim->v0 = prim->v1 = 0x40;
        prim->v2 = prim->v3 = 0x68;
        prim->x2 = prim->x0 = 0x80;
        prim->y1 = prim->y0 = 0x9D;
        prim->x3 = prim->x1 = 0xF4;
        prim->y3 = prim->y2 = 0xC5;
        prim->priority = 0xBF;
        prim->drawMode = 8;
        prim = prim->next;

        self->ext.stpopup.unk84 = prim;
        prim->type = 3;
        prim->tpage = 0x1A;
        prim->clut = 0x15F;
        prim->u0 = 0;
        prim->u1 = 0x40;
        prim->u2 = prim->u0;
        prim->u3 = prim->u1;
        prim->v1 = prim->v0 = 0xC0;
        prim->v3 = prim->v2 = 0xFF;
        prim->y1 = prim->y0 = 0x9B;
        prim->y3 = prim->y2 = 0xC7;
        prim->x2 = prim->x0 = 0xC;
        prim->x3 = prim->x1 = 0xF4;
        prim->r0 = 0x10;
        prim->g0 = 0x28;
        prim->b0 = 0;
        prim->r2 = 8;
        prim->g2 = 0;
        prim->b2 = 0x38;
        prim->priority = 0xB0;
        prim->drawMode = 0x1D;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r2);
        prim = prim->next;

        self->ext.stpopup.unk8C = prim;
        for (i = 0; i < 0x28; i++) {
            prim->tpage = 0x11;
            prim->clut = 0x19F;
            prim->v2 = prim->v3 = i + 1;
            prim->y1 = prim->y0 = i + 0x9D;
            prim->r0 = 0x78;
            prim->g0 = 0x78;
            prim->b0 = 0xA8;
            prim->y3 = prim->y2 = i + 0x9E;
            prim->v0 = prim->v1 = i;
            prim->x2 = prim->x0 = 0xC;
            prim->x3 = prim->x1 = 0x80;
            prim->u2 = prim->u0 = 4;
            prim->u1 = prim->u3 = primIndex = 0x78; // FAKE
            prim->priority = 0xC0;
            prim->drawMode = 0xC;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim = prim->next;
        }
        for (i = 0; i < 0x28; i++) {
            prim->tpage = 0x11;
            prim->clut = 0x19F;
            prim->y1 = prim->y0 = i + 0x9D;
            prim->y3 = prim->y2 = i + 0x9E;
            prim->v0 = prim->v1 = i + 0x40;
            prim->x2 = prim->x0 = 0x80;
            prim->x3 = prim->x1 = 0xF4;
            prim->u2 = prim->u0 = 8;
            prim->u1 = prim->u3 = 0x7C;
            prim->v2 = prim->v3 = i + 0x41;
            prim->r0 = 0x78;
            prim->g0 = 0x78;
            prim->b0 = 0xA8;
            prim->priority = 0xC0;
            prim->drawMode = 0xC;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim = prim->next;
        }
        self->ext.stpopup.unk80 = 0x20;
    case 1:
        switch (self->step_s) {
        case 0:
            if (self->ext.stpopup.unk80 != 0) {
                self->ext.stpopup.unk80--;
            } else {
                prim = self->ext.stpopup.unk84;
                prim->x0 = prim->x2 = 0x80;
                prim->x1 = prim->x3 = 0x80;
                prim->y0 = prim->y1 = 0xB1;
                prim->y2 = prim->y3 = 0xB1;
                prim->drawMode = 0x15;
                self->step_s++;
            }
            break;
        case 1:
            prim = self->ext.stpopup.unk84;
            var_a0 = 0;
            if (prim->y0 >= 0x9C) {
                var_a0 = 1;
                prim->y1 = prim->y0 = prim->y0 - 4;
                prim->y3 = prim->y2 = prim->y2 + 4;
            }
            if (prim->x0 >= 0xD) {
                var_a0 |= 1;
                prim->x2 = prim->x0 = prim->x0 - 8;
                prim->x3 = prim->x1 = prim->x1 + 8;
            }
            if (var_a0 == 0) {
                self->ext.stpopup.unk80 = 0;
                self->ext.stpopup.unk90 = 0;
                self->ext.stpopup.unk92 = 0;
                self->step_s++;
            }
            break;
        case 2:
            self->ext.stpopup.unk90 += 3;
            if (self->ext.stpopup.unk90 >= 0x80) {
                self->step_s++;
            }
            prim = self->ext.stpopup.unk88;
            for (i = 0; i < 2; i++) {
                prim->drawMode = 0x75;
                prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 =
                    prim->b1 = prim->r2 = prim->g2 = prim->b2 = prim->r3 =
                        prim->g3 = prim->b3 = self->ext.stpopup.unk90;
                prim = prim->next;
            }
            break;
        case 3:
            self->ext.stpopup.unk90 -= 2;
            if (self->ext.stpopup.unk90 < 0) {
                self->ext.stpopup.unk90 = 0;
            }
            prim = self->ext.stpopup.unk88;
            for (i = 0; i < 2; i++) {
                prim->drawMode = 0x35;
                prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 =
                    prim->b1 = prim->r2 = prim->g2 = prim->b2 = prim->r3 =
                        prim->g3 = prim->b3 = self->ext.stpopup.unk90;
                prim = prim->next;
            }
            if (self->ext.stpopup.unk90 != 0) {
                self->ext.stpopup.unk92 = 0x80 - self->ext.stpopup.unk90;
            } else {
                self->ext.stpopup.unk92 += 4;
            }
            if (self->ext.stpopup.unk92 >= 0x80) {
                self->ext.stpopup.unk92 = 0x80;
                self->step_s++;
            }
            prim = self->ext.stpopup.prim;
            for (i = 0; i < 2; i++) {
                prim->drawMode = 0x35;
                prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 =
                    prim->b1 = prim->r2 = prim->g2 = prim->b2 = prim->r3 =
                        prim->g3 = prim->b3 = self->ext.stpopup.unk92;
                prim = prim->next;
            }
            for (i = 0; i < 2; i++) {
                prim->drawMode = 0x15;
                prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 =
                    prim->b1 = prim->r2 = prim->g2 = prim->b2 = prim->r3 =
                        prim->g3 = prim->b3 = self->ext.stpopup.unk92;
                prim = prim->next;
            }
            break;
        case 4:
            prim = self->ext.stpopup.unk88;
            prim->drawMode = 8;
            self->ext.stpopup.unk80 = 0x40;
            self->step = 2;
            self->step_s = 0;
            g_CastleFlags[CASTLE_FLAG_BANK + 2] = 1;
            break;
        }
        break;
    case 2:
        self->ext.stpopup.unk80--;
        if (self->ext.stpopup.unk80 == 0) {
            self->step_s = 0;
            self->step = 3;
        }
        break;
    case 3:
        switch (self->step_s) {
        case 0:
            prim = self->ext.stpopup.prim;
            prim = prim->next;
            prim = prim->next;
            for (i = 0; i < 2; i++) {
                prim->drawMode = 0x15;
                prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 =
                    prim->b1 = prim->r2 = prim->g2 = prim->b2 = prim->r3 =
                        prim->g3 = prim->b3 = self->ext.stpopup.unk92;
                prim = prim->next;
            }
            self->ext.stpopup.unk92 -= 4;
            if (self->ext.stpopup.unk92 < 0) {
                self->ext.stpopup.unk92 = 0;
                self->step_s++;
                break;
            }
            break;
        case 1:
            prim = self->ext.stpopup.prim;
            for (i = 0; i < 4; i++) {
                prim->drawMode = 8;
                prim = prim->next;
            }

            prim = self->ext.stpopup.unk8C;
            for (i = 0; i < 0x14; i++) {
                prim->r0 = 0x80;
                prim->g0 = 0x80;
                prim->b0 = 0x80;
                drawMode = 0x35;
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                prim->p1 = i * 4;
                prim->p2 = Random() & 3;
                prim->p3 = 0;
                prim->drawMode = drawMode;
                prim = prim->next;
            }

            for (i = 0; i < 0x14; i++) {
                prim->r0 = 0x80;
                prim->g0 = 0x80;
                prim->b0 = 0x80;
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                prim->p1 = -((0x14 - i) * 4);
                prim->p2 = Random() & 3;
                prim->p3 = 0;
                prim->drawMode = 0x35;
                prim = prim->next;
            }

            for (i = 0; i < 0x14; i++) {
                prim->r0 = 0x80;
                prim->g0 = 0x80;
                prim->b0 = 0x80;
                drawMode = 0x35;
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                prim->p1 = i * 4;
                prim->p2 = Random() & 3;
                prim->p3 = 0;
                prim->drawMode = drawMode;
                prim = prim->next;
            }

            for (i = 0; i < 0x14; i++) {
                prim->r0 = 0x80;
                prim->g0 = 0x80;
                prim->b0 = 0x80;
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                prim->p1 = -((0x14 - i) * 4);
                prim->p2 = Random() & 3;
                prim->p3 = 0;
                prim->drawMode = 0x35;
                prim = prim->next;
            }

            self->ext.stpopup.unk80 = 0x70;
            self->step_s++;
            break;
        case 2:
            prim = self->ext.stpopup.unk8C;
            while (prim != NULL) {
                StageNamePopupHelper(prim);
                prim = prim->next;
            }
            self->ext.stpopup.unk80--;
            if (self->ext.stpopup.unk80 == 0) {
                self->step_s++;
            }
            break;
        case 3:
            prim = self->ext.stpopup.unk8C;
            while (prim != NULL) {
                StageNamePopupHelper(prim);
                prim = prim->next;
            }
            prim = self->ext.stpopup.unk84;
            prim->y0 += 2;
            prim->y1 = prim->y0;
            prim->y2 -= 2;
            prim->y3 = prim->y2;
            prim->x0 -= 2;
            prim->x1 += 2;
            prim->x2 -= 2;
            prim->x3 += 2;
            if (prim->y2 < prim->y0) {
                DestroyEntity(self);
                return;
            }
            break;
        }
        break;
    }
    FntPrint("t_step   %x\n", self->step);
    FntPrint("t_step_s %x\n", self->step_s);
}
