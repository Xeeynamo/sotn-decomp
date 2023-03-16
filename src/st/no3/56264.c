#include "no3.h"

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
        func_801CAD28(0x69C);
        DestroyEntity(entity);
        return;
    }

    switch (entity->step) {
    case 0:
        InitializeEntity(&D_80180B90);
        entity->animCurFrame = 31;
        break;

    case 1:
        xDistance = func_801C4F64();
        yDistance = func_801C4FA0();
        if ((xDistance < 0x60) && (yDistance < 0x60) &&
            !(func_801C4FD4() & 2)) {
            entity->step++;
        }
        break;

    case 2:
        if (AnimateEntity(&D_80183C60, entity) == 0) {
            entity->facing = (func_801C4FD4() & 1) ^ 1;
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
        AnimateEntity(&D_80183C44, entity);
        MoveEntity();
        if (func_801C4FA0() < 0x20) {
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
        AnimateEntity(&D_80183C44, entity);
        MoveEntity();
        if ((u32)(entity->accelerationY + 0x10000) > 0x20000U) {
            *(s32*)&entity->unk7C.s = (s32) - *(s32*)&entity->unk7C.s;
        }
        entity->accelerationY += *(s32*)&entity->unk7C.u;
        break;
    }
}

INCLUDE_ASM("asm/us/st/no3/nonmatchings/56264", EntityZombie);

INCLUDE_ASM("asm/us/st/no3/nonmatchings/56264", EntityUnkId4D);

INCLUDE_ASM("asm/us/st/no3/nonmatchings/56264", func_801D6880);

INCLUDE_ASM("asm/us/st/no3/nonmatchings/56264", func_801D6C68);

POLY_GT4* func_801D6DB8(POLY_GT4* poly) {
    while (poly != NULL) {
        if (poly->p3 != 0) {
            poly = (POLY_GT4*)poly->tag;
        } else {
            return poly;
        }
    }
    return NULL;
}

POLY_GT4* func_8019C43C(POLY_GT4* poly, u8 index) {
    if (poly) {
        s32 index_ = index;
    loop_2:
        if (poly->p3 == 0) {
            POLY_GT4* var_v0 = NULL;
            POLY_GT4* firstPoly = poly;
            s32 i = 1;
            if (i < index_) {
                do {
                    poly = (POLY_GT4*)poly->tag;
                    if (!poly)
                        return NULL;
                } while (poly->p3 == 0 && ++i < index);
            }
            var_v0 = firstPoly;
            if (i == index_)
                return var_v0;
        }
        poly = (POLY_GT4*)poly->tag;
        if (poly) {
            goto loop_2;
        }
    }
    return NULL;
}

POLY_GT4* func_801D6E64(POLY_GT4* startPoly, s32 count) {
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

void func_801D6EEC(POLY_GT4* arg0) {
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

void func_801D6FCC(POLY_GT4* arg0) {
    func_801D6EEC(arg0);
    arg0->p3 = 8;
    ((POLY_GT4*)arg0->tag)->p3 = 1;
    ((POLY_GT4*)arg0->tag)->code = 2;
    ((POLY_GT4*)arg0->tag)->pad3 = 0xA;
}

void func_801D7020(POLY_GT4* arg0) {
    arg0->p3 = 0;
    arg0->pad3 = 8;
    ((POLY_GT4*)arg0->tag)->p3 = 0;
    ((POLY_GT4*)arg0->tag)->code = 4;
    ((POLY_GT4*)arg0->tag)->pad3 = 8;
}

s32 func_801D704C(s32 arg0, u8 arg1) {
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
        } while ((s32)var_v1 < ((s32)var_a0 + 3));

        var_a0 += 0xC;
    }

    return ret;
}