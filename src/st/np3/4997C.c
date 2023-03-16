#include "np3.h"

void EntityBat(Entity* entity) {
    Entity* newEntity;
    s16 xDistance;
    s16 yDistance;

    if (entity->flags & 0x100) {
        newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(2, entity, newEntity);
            newEntity->subId = 1;
        }
        func_801C2598(0x69C);
        DestroyEntity(entity);
        return;
    }

    switch (entity->step) {
    case 0:
        InitializeEntity(&D_80180AFC);
        entity->animCurFrame = 31;
        break;

    case 1:
        xDistance = func_801BC7D4();
        yDistance = func_801BC810();
        if ((xDistance < 0x60) && (yDistance < 0x60) &&
            !(func_801BC844() & 2)) {
            entity->step++;
        }
        break;

    case 2:
        if (AnimateEntity(&D_80182570, entity) == 0) {
            entity->facing = (func_801BC844() & 1) ^ 1;
            entity->accelerationY = 0xE000;
            if (entity->facing != 0) {
                entity->accelerationX = 0x4000;
            } else {
                entity->accelerationX = -0x4000;
            }
            entity->animFrameIdx = (Random() & 3) * 3;
            entity->animFrameDuration = 0;
            entity->step++;
        }
        break;

    case 3:
        AnimateEntity(&D_80182554, entity);
        MoveEntity();
        if (func_801BC810() < 0x20) {
            if (entity->facing == 0) {
                entity->accelerationX = -0x10000;
            } else {
                entity->accelerationX = 0x10000;
            }
            *(s32*)&entity->unk7C.s = 0x800;
            entity->step++;
        }
        break;

    case 4:
        AnimateEntity(&D_80182554, entity);
        MoveEntity();
        if ((u32)(entity->accelerationY + 0x10000) > 0x20000U) {
            *(s32*)&entity->unk7C.s = (s32) - *(s32*)&entity->unk7C.s;
        }
        entity->accelerationY += *(s32*)&entity->unk7C.u;
        break;
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", EntityZombie);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", EntityUnkId4D);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801C9F98);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CA498);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CA654);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CAE0C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CB018);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CBF18);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CC2E0);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CD540);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CD620);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CD658);

void func_801CD734() {
    while (PadRead(0))
        func_801CD658();
    while (!PadRead(0))
        func_801CD658();
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CD78C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CD83C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CD91C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CDA14);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CDA6C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CDAC8);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CDC80);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CDD00);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CDD80);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CDE10);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CDE88);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CDF1C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CDFD8);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CE04C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CE120);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CE1E8);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CE228);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CE258);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CE2CC);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CE3FC);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CE4CC);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CE69C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CF254);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CF5B8);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CF778);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CF7A0);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801CF94C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801D0730);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801D0A00);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801D0B40);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801D0B78);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801D0D40);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801D1BB8);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801D1F38);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801D2320);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801D2470);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4997C", func_801D24A0);

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