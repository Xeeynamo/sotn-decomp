#include "np3.h"

void EntityZombie(Entity* self) {
    Entity* newEntity;
    s32 temp_a0;

    if ((self->flags & 0x100) && (self->step < 4)) {
        func_801C2598(0x65E);
        self->unk3C = 0;
        newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(0x4D, self, newEntity);
            newEntity->zPriority = self->zPriority + 1;
            newEntity->subId = 3;
            newEntity->posY.i.hi += 12;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(&D_80180B08);
        self->hitboxWidth = 8;
        self->unk12 = 0x10;
        self->hitboxHeight = 0;
        self->zPriority += 4;
        if (g_blinkTimer & 1) {
            self->palette++;
        }
        if (Random() & 1) {
            self->palette++;
        }
        self->animCurFrame = 0;
        break;

    case 1:
        if (func_801BC8E4(&D_801825BC) & 1) {
            self->facing = (func_801BC844() & 1) ^ 1;
            self->step++;
        }
        break;

    case 2:
        if (AnimateEntity(&D_80182594, self) == 0) {
            func_801BD114(3);
        }
        if (self->animFrameDuration == 0) {
            self->unk12 -= 2;
            self->hitboxHeight += 2;
        }
        break;

    case 3:
        AnimateEntity(&D_8018258C, self);
        temp_a0 = func_801BCB5C(&D_801825CC);
        if (self->facing != 0) {
            self->accelerationX = 0x8000;
        } else {
            self->accelerationX = -0x8000;
        }

        if (temp_a0 & 0xC0) {
            self->unk3C = 0;
            func_801BD114(4);
        }
        break;

    case 4:
        if (AnimateEntity(&D_801825A8, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", EntityUnkId4D);

void EntityBloodSplatter(Entity* self) {
    Primitive *prim, *prim2, *prim3;
    s16 firstPrimIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180A54);
        break;

    case 1:
        firstPrimIndex = g_api.AllocPrimitives(4, 8);
        if (firstPrimIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->firstPolygonIndex = firstPrimIndex;
        prim = &g_PrimBuf[firstPrimIndex];
        *(s32*)&self->unk7C = prim;
        self->flags |= FLAG_FREE_POLYGONS;
        self->step++;
        break;

    case 2:
        prim = func_801D24A0(*(s32*)&self->unk7C, 2);
        if (prim != NULL) {
            self->unk8C.primPtr = prim;
            func_801D2684(prim);
            prim->v0 = 0x30;
            prim->tpage = 0x1A;
            prim->v2 = 0x30;
            prim->clut = 0x1B7;
            prim->u0 = 0x50;
            prim->u1 = 0x50;
            prim->u2 = 0x40;
            prim->u3 = 0x40;
            prim->v1 = 0x40;
            prim->v3 = 0x40;
            prim->next->b3 = 0x60;
            prim->next->x1 = self->posX.i.hi;
            prim->next->y0 = self->posY.i.hi;
            *(u16*)&prim->next->r2 = 0x10;
            *(u16*)&prim->next->b2 = 0x10;
            *(s32*)&prim->next->r1 = -0x6000;

            if (self->facing != 0) {
                *(s32*)&prim->next->u0 = 0xA000;
                prim->next->tpage = 0x200;
                prim->next->x1 = prim->next->x1 + 4;
            } else {
                *(s32*)&prim->next->u0 = 0xFFFF6000;
                *(s16*)&prim->next->tpage = -0x200;
                prim->next->x1 = prim->next->x1 - 4;
            }
            prim->priority = self->zPriority + 2;
            prim->blendMode = 6;
        }

        prim = func_801D24A0(*(s32*)&self->unk7C, 2);
        if (prim != NULL) {
            *(s32*)&self->unk90 = prim;
            func_801D2684(prim);
            prim->v1 = 0x40;
            prim->tpage = 0x1A;
            prim->v3 = 0x40U;
            prim->clut = 0x1B7;
            prim->u0 = 0x20;
            prim->u1 = 0x20;
            prim->u2 = 0;
            prim->u3 = 0;
            prim->v0 = 0x20;
            prim->v2 = 0x20;
            prim->next->x1 = self->posX.i.hi;
            prim->next->y0 = self->posY.i.hi;
            *(u16*)&prim->next->r2 = 8;
            *(u16*)&prim->next->b2 = 0x10;
            prim->next->b3 = 0x80;
            *(s32*)&prim->next->r1 = -0x8000;
            if (self->facing != 0) {
                *(s32*)&prim->next->u0 = 0xC000;
                *(s16*)&prim->next->tpage = 0x200;
            } else {
                *(s32*)&prim->next->u0 = 0xFFFF4000;
                *(s16*)&prim->next->tpage = -0x200;
            }
            prim->priority = self->zPriority + 2;
            prim->blendMode = 6;
        }
        self->step++;
        break;

    case 3:
        prim = self->unk8C.entityPtr;
        func_801D1F38(prim);

        if (g_blinkTimer & 1) {
            prim3 = prim->next;
            *(u16*)&prim3->r2 = *(u16*)&prim3->r2 + 1;
            prim3 = prim->next;
            *(u16*)&prim3->b2 = *(u16*)&prim3->b2 + 1;
            prim->clut = 0x1B7;
        } else {
            prim->clut = 0x16D;
        }

        prim2 = prim->next;
        *(s32*)&prim2->r1 += 0xC00;

        if (self->facing != 0) {
            prim->next->tpage += 0x18;
        } else {
            prim->next->tpage = prim->next->tpage - 0x18;
        }

        prim3 = prim->next;
        prim3->b3 += 254;
        if (func_801D2320(&D_8018268C, prim) == 0) {
            func_801D26D8(prim);
        }

        prim = *(s32*)&self->unk90;
        func_801D1F38(prim);
        prim3 = prim->next;
        *(u16*)&prim3->r2 = *(u16*)&prim3->r2 + 2;
        prim3 = prim->next;
        *(u16*)&prim3->b2 = *(u16*)&prim3->b2 + 2;
        if (prim->p1 >= 4) {
            *(u16*)&prim->next->b2 = 16;
        }

        prim->next->b3 += 253;
        prim3 = prim->next;
        if (prim3->b3 > 240) {
            prim3->b3 = 0;
        }

        if (func_801D2320(&D_801826A4, prim) == 0) {
            func_801D26D8(prim);
        }

        if (self->unk80.modeS16.unk0++ > 128) {
            DestroyEntity(self);
        }
        break;
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CA498);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CA654);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CAE0C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CB018);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CBF18);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CC2E0);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CD540);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CD620);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CD658);

void func_801CD734() {
    while (PadRead(0))
        func_801CD658();
    while (!PadRead(0))
        func_801CD658();
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CD78C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CD83C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CD91C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CDA14);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CDA6C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CDAC8);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CDC80);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CDD00);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CDD80);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CDE10);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CDE88);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CDF1C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CDFD8);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CE04C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CE120);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CE1E8);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CE228);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CE258);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CE2CC);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CE3FC);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CE4CC);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CE69C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CF254);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CF5B8);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CF778);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CF7A0);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CF94C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801D0730);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801D0A00);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801D0B40);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801D0B78);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801D0D40);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801D1BB8);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801D1F38);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801D2320);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801D2470);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801D24A0);

POLY_GT4* func_801D251C(POLY_GT4* startPoly, s32 count) {
    POLY_GT4* poly;
    s8 unk;
    s32 i;

    if (startPoly->p3) {
        startPoly->p3 = 0;
    } else {
        startPoly->p3 = 1;
    }

    poly = startPoly;
    for (i = 0; i < count; i++) {
        if (poly->p3) {
            poly->pad3 &= ~8;
            unk = 0;
        } else {
            poly->pad3 |= 8;
            unk = 1;
        }

        poly = (POLY_GT4*)poly->tag;
        if (poly == 0)
            return 0;
        poly->p3 = unk;
    }

    return poly;
}

void func_801D25A4(POLY_GT4* arg0) {
    arg0->p1 = 0;
    arg0->p2 = 0;
    arg0->p3 = 0;
    ((POLY_GT4*)arg0->tag)->x1 = 0;
    ((POLY_GT4*)arg0->tag)->y1 = 0;
    ((POLY_GT4*)arg0->tag)->y0 = 0;
    ((POLY_GT4*)arg0->tag)->x0 = 0;
    ((POLY_GT4*)arg0->tag)->clut = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->u0 = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->b1 = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->r1 = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->u1 = 0;
    ((POLY_GT4*)arg0->tag)->tpage = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->r2 = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->b2 = 0;
    ((POLY_GT4*)arg0->tag)->u2 = 0;
    ((POLY_GT4*)arg0->tag)->v2 = 0;
    ((POLY_GT4*)arg0->tag)->r3 = 0;
    ((POLY_GT4*)arg0->tag)->b3 = 0;
    ((POLY_GT4*)arg0->tag)->x2 = 0;
    ((POLY_GT4*)arg0->tag)->y2 = 0;
}

void func_801D2684(POLY_GT4* arg0) {
    func_801D25A4(arg0);
    arg0->p3 = 8;
    ((POLY_GT4*)arg0->tag)->p3 = 1;
    ((POLY_GT4*)arg0->tag)->code = 2;
    ((POLY_GT4*)arg0->tag)->pad3 = 0xA;
}

void func_801D26D8(POLY_GT4* arg0) {
    arg0->p3 = 0;
    arg0->pad3 = 8;
    ((POLY_GT4*)arg0->tag)->p3 = 0;
    ((POLY_GT4*)arg0->tag)->code = 4;
    ((POLY_GT4*)arg0->tag)->pad3 = 8;
}

s32 func_801D2704(s32 arg0, u8 arg1) {
    s32 var_v0;
    s32 ret = 0;
    u8* var_a0 = arg0 + 4;
    u8* var_v1;
    s32 i;

    for (i = 0; i < 4; i++) {
        var_v1 = var_a0;
        do {
            var_v0 = *var_v1 - arg1;

            if (var_v0 < 0) {
                var_v0 = 0;
            } else {
                ret |= 1;
            }

            *var_v1 = var_v0;
            var_v1++;
        } while (((s32)var_v1 < ((s32)var_a0 + 3)));

        var_a0 += 0xC;
    }

    return ret;
}