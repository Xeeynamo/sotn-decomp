// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno4/rno4.h"

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", EntityRdaiUnk33);

#include "../e_imp_death_particle.h"

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_us_801BBE58_from_rnz1);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_us_801BC650_from_rnz1);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_us_801BCA5C_from_rnz1);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_us_801BCB9C_from_rnz1);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_us_801BCD80_from_rnz1);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_us_801BCE4C_from_rnz1);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_us_801BCFC8_from_rnz1);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", StepTowards);

void func_us_801D5DC8(Primitive* prim) {
    s32 yPos;
    switch (prim->p2) {
    case 0:
        LOW(prim->x2) = Random() * 8;
        prim->x3 = (Random() & 0x1F) + 0x10;
        prim->drawMode = DRAW_UNK02;
        prim->p2 += 1;

    case 1:
        yPos = (prim->y0 << 0x10) + prim->y1;
        yPos = yPos + LOW(prim->x2);
        LOW(prim->x2) -= 0x1000;
        prim->y0 = yPos >> 0x10;
        prim->y1 = yPos & 0xffff;
        if (!(prim->x3 -= 1)) {
            prim->p2 = 0;
            prim->drawMode = DRAW_HIDE;
            prim->p3 = 0;
        }
        return;
    }
}

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_us_801D5E90);

extern u16 D_us_80180B6C;

void func_us_801D68E0(Entity* self) {
    Primitive* prim;
    Entity* ent;
    s32 xPosition;
    s32 primIndex;
    s32 yPosition;
    s16 angle;

    if (self->hitFlags && !(self->hitFlags & 0x80)) {
        self->hitboxState = 0;
        SetStep(2);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(&D_us_80180B6C);
        primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 1);

        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801D68E0.unk7C = prim;

        prim->x0 = (prim->x1 = self->posX.i.hi);
        prim->y0 = (prim->y1 = self->posY.i.hi);
        prim->r0 = 0xFF;
        prim->g0 = 0x60;
        prim->b0 = 0x60;
        prim->r1 = 0x80;
        prim->g1 = 0x40;
        prim->b1 = 0x40;
        prim->priority = self->zPriority;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;

        angle = self->ext.et_801D68E0.unk8C;

        if (self->facingLeft) {
            angle = -angle;
        }

        self->velocityX = rsin((s32)angle) * (-0x80);
        self->velocityY = rcos((s32)angle) << 7;
        self->ext.et_801D68E0.unk80 = 0x20;

    case 1:
        MoveEntity();

        prim = self->ext.et_801D68E0.unk7C;
        xPosition = (prim->x0 = self->posX.i.hi);
        yPosition = (prim->y0 = self->posY.i.hi);

        if (!(self->ext.et_801D68E0.unk80 -= 1)) {
            self->step = 2;
        }

    default:
        break;

    case 2:
        self->velocityX = -self->velocityX;
        self->velocityY = -self->velocityY;
        self->step++;

    case 3:
        MoveEntity();

        prim = self->ext.et_801D68E0.unk7C;
        xPosition = (prim->x0 = self->posX.i.hi);
        yPosition = (prim->y0 = self->posY.i.hi);

        prim = self->ext.et_801D68E0.unk7C;
        xPosition -= prim->x1;
        yPosition -= prim->y1;

        if ((abs(xPosition) < 8) && (abs(yPosition) < 8)) {
            DestroyEntity(self);
        }
    }

    ent = self->ext.et_801D68E0.unk9C;
#if defined(VERSION_PSP) || defined(FIX_UB)
    // Non-PSX versions fix a null pointer here
    if (ent != NULL) {
#else
    if (1) {
#endif
        if (ent->entityId != 0x40) {
            DestroyEntity(self);
        }
    }
}

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_3B78", func_us_801D6B8C);
