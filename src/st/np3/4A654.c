#include "np3.h"

void EntityBloodyZombie(Entity* self) {
    Primitive** primPtrPtr;
    Primitive* prim;
    Entity* newEntity;
    s16 firstPrimIndex;
    s32 animStatus;
    s32 facing;

    if ((self->unk44) && (self->step & 1)) {
        func_801C2598(NA_SE_EN_BLOODY_ZOMBIE_INJURED_SCREAM);
        func_801C2598(NA_SE_EN_BLOODY_ZOMBIE_INJURED);
        func_801BD114(BLOODY_ZOMBIE_TAKE_HIT);
    }

    if ((self->flags & 0x100) && (self->step < 8)) {
        func_801C2598(NA_SE_EN_BLOODY_ZOMBIE_DEATH_SCREAM);
        self->unk3C = 0;
        self->flags &= 0xDFFFFFFF;
        func_801BD114(BLOODY_ZOMBIE_DYING);
    }

    switch (self->step) {
    case BLOODY_ZOMBIE_INIT:
        InitializeEntity(D_80180B38);
        self->unk10 = 1;
        self->unk12 = 4;
        func_801BD114(BLOODY_ZOMBIE_UNK_2);
        break;

    case BLOODY_ZOMBIE_UNK_2:
        if (func_801BC8E4(&D_801825D4) & 1) {
            func_801BD114(BLOODY_ZOMBIE_WALK);
        }
        break;

    case BLOODY_ZOMBIE_WALK:
        if (self->unk2E == 0) {
            self->unk80.modeS16.unk0 = 128;
            self->unk2E++;
        }

        AnimateEntity(D_801825EC, self);
        func_801BCB5C(D_801825E4);

        if (self->facing == 0) {
            self->accelerationX = -0x6000;
        } else {
            self->accelerationX = 0x6000;
        }

        if (--self->unk80.modeS16.unk0 == 0) {
            self->unk80.modeS16.unk0 = 128;
            self->facing ^= 1;
        }

        if (!(Random() % 64)) { // Drop BloodDrips from the enemy knife
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x49, self, newEntity);
                if (self->facing != 0) {
                    newEntity->posX.i.hi += 16;
                } else {
                    newEntity->posX.i.hi -= 16;
                }
                newEntity->posY.i.hi += 12;
            }
        }
        facing = (GetPlayerSide() & 1);
        if ((PLAYER.facing == facing) && (GetPlayerDistanceX() < 128)) {
            self->facing = facing ^ 1;
            func_801BD114(BLOODY_ZOMBIE_CHASE);
        }
        break;

    case BLOODY_ZOMBIE_CHASE:
        if (AnimateEntity(D_8018267C, self) == 0) {
            facing = self->facing = (GetPlayerSide() & 1) ^ 1;
        }
        func_801BCB5C(D_801825E4);

        if (self->facing != 0) {
            self->accelerationX = 0xC000;
        } else {
            self->accelerationX = -0xC000;
        }

        if (!(Random() % 64)) { // Drop BloodDrips from the enemy knife
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x49, self, newEntity);
                if (self->facing != 0) {
                    newEntity->posX.i.hi += 18;
                } else {
                    newEntity->posX.i.hi -= 18;
                }
                newEntity->posY.i.hi += 12;
            }
        }

        if (GetPlayerDistanceX() < 40) {
            func_801BD114(BLOODY_ZOMBIE_ATTACK);
        }
        break;

    case BLOODY_ZOMBIE_ATTACK:
        animStatus = AnimateEntity(D_801825FC, self);
        if ((animStatus & 0x80) && (self->animFrameIdx == 10)) {
            func_801C2598(NA_SE_EN_BLOOD_ZOMBIE_SWORD_SLASH);
        }
        if (animStatus == 0) {
            func_801BD114(BLOODY_ZOMBIE_WALK);
        }
        break;

    case BLOODY_ZOMBIE_TAKE_HIT:
        if (self->unk2E == 0) {
            // Splat blood
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x4A, self, newEntity);
                newEntity->facing = GetPlayerSide() & 1;
            }
            self->unk2E++;
        }

        if (AnimateEntity(D_80182620, self) == 0) {
            func_801BD114(BLOODY_ZOMBIE_WALK);
            self->unk2E++;
        }
        break;

    case BLOODY_ZOMBIE_DYING:
        if (self->unk2E == 0) {
            firstPrimIndex = g_api.AllocPrimitives(PRIM_GT4, 0x14);
            if (firstPrimIndex == -1) {
                DestroyEntity(self);
                return;
            }
            self->firstPolygonIndex = firstPrimIndex;
            prim = &g_PrimBuf[firstPrimIndex];
            *(s32*)&self->unk7C = prim;
            self->flags |= FLAG_FREE_POLYGONS;
            self->unk2E++;
        }

        if (self->animFrameIdx < 13) {
            if (!(g_blinkTimer % 8)) {
                func_801C2598(NA_SE_EN_BLOODY_ZOMBIE_HEMORRHAGE);
                newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(0x4A, self, newEntity);
                    newEntity->facing = self->unk84.U8.unk0;
                    if (self->facing != 0) {
                        newEntity->posX.i.hi -= 4;
                    } else {
                        newEntity->posX.i.hi += 4;
                    }
                    newEntity->posY.i.hi += 4;
                }
                self->unk84.U8.unk0 ^= 1;
            }
            self->unk80.modeS16.unk0 = 0;
        } else {
            if (self->unk80.modeS16.unk0 == 0) {
                func_801C2598(NA_SE_EN_BLOODY_ZOMBIE_HEMORRHAGE);
            }

            self->unk80.modeS16.unk0++;
            if (!(g_blinkTimer & 3)) {
                primPtrPtr = func_801D24A0(*(s32*)&self->unk7C, 2);
                if (primPtrPtr != NULL) {
                    func_801D2684(primPtrPtr);
                    (*primPtrPtr)->r3 = self->unk84.U8.unk0;
                }
                self->unk84.U8.unk0 ^= 1;
            }
        }

        if (self->flags & FLAG_FREE_POLYGONS) {
            prim = *(s32*)&self->unk7C;
            while (prim != NULL) {
                if (prim->p3 & 8) {
                    func_801CA498(prim);
                }
                prim = prim->next;
            }
        }

        if (AnimateEntity(D_80182634, self) == 0) {
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(2, self, newEntity);
                newEntity->subId = 2;
                newEntity->posY.i.hi += 16;
                if (self->facing != 0) {
                    newEntity->posX.i.hi -= 8;
                } else {
                    newEntity->posX.i.hi += 8;
                }
            }
            self->unk80.modeS16.unk0 = 64;
            self->animCurFrame = 0;
            func_801C2598(NA_SE_EN_EXPLOSIVE_DEATH);
            self->step++;
        }
        break;

    case BLOODY_ZOMBIE_DESTROY:
        if (self->flags & FLAG_FREE_POLYGONS) {
            prim = *(s32*)&self->unk7C;
            while (prim != NULL) {
                if (prim->p3 & 8) {
                    func_801CA498(prim);
                }
                prim = prim->next;
            }
        }

        if (--self->unk80.modeS16.unk0 == 0) {
            DestroyEntity(self);
        }
        break;
    }

    if ((u32)((u16)self->animCurFrame - 11) < 2) {
        self->hitboxWidth = 18;
        self->hitboxHeight = 12;
        *(s16*)&self->unk10 = -12;
        self->unk12 = -12;
    } else {
        self->hitboxWidth = 4;
        self->hitboxHeight = 22;
        self->unk10 = 1;
        self->unk12 = 4;
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801CAE0C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801CB018);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801CBF18);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801CC2E0);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801CD540);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801CD620);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801CD658);

void func_801CD734() {
    while (PadRead(0))
        func_801CD658();
    while (!PadRead(0))
        func_801CD658();
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801CD78C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801CD83C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801CD91C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801CDA14);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801CDA6C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801CDAC8);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801CDC80);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801CDD00);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801CDD80);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801CDE10);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801CDE88);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801CDF1C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801CDFD8);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801CE04C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801CE120);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801CE1E8);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801CE228);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801CE258);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801CE2CC);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801CE3FC);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801CE4CC);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801CE69C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801CF254);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801CF5B8);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801CF778);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801CF7A0);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801CF94C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801D0730);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801D0A00);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801D0B40);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801D0B78);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801D0D40);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801D1BB8);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801D1F38);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801D2320);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801D2470);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4A654", func_801D24A0);

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