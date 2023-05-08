#include "np3.h"

typedef enum {
    BLOODY_ZOMBIE_INIT,
    BLOODY_ZOMBIE_WALK,
    BLOODY_ZOMBIE_UNK_2,
    BLOODY_ZOMBIE_CHASE,
    BLOODY_ZOMBIE_ATTACK,
    BLOODY_ZOMBIE_TAKE_HIT = 6,
    BLOODY_ZOMBIE_DYING = 8,
    BLOODY_ZOMBIE_DESTROY
} EntityBloodyZombieSteps;

void EntityBloodyZombie(Entity* self) {
    Primitive* prim;
    Entity* newEntity;
    s16 firstPrimIndex;
    s16 facing;
    s32 animStatus;

    if (self->unk44 && self->step & 1) {
        func_801C2598(NA_SE_EN_BLOODY_ZOMBIE_INJURED_SCREAM);
        func_801C2598(NA_SE_EN_BLOODY_ZOMBIE_INJURED);
        func_801BD114(BLOODY_ZOMBIE_TAKE_HIT);
    }

    if (self->flags & 0x100 && self->step < 8) {
        func_801C2598(NA_SE_EN_BLOODY_ZOMBIE_DEATH_SCREAM);
        self->unk3C = 0;
        self->flags &= ~FLAG_UNK_20000000;
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
        if (self->step_s == 0) {
            self->ext.generic.unk80.modeS16.unk0 = 128;
            self->step_s++;
        }

        AnimateEntity(D_801825EC, self);
        func_801BCB5C(D_801825E4);

        if (self->facing == 0) {
            self->accelerationX = -0x6000;
        } else {
            self->accelerationX = 0x6000;
        }

        if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
            self->ext.generic.unk80.modeS16.unk0 = 128;
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
        facing = GetPlayerSide() & 1;
        if (PLAYER.facing == facing && GetPlayerDistanceX() < 128) {
            self->facing = facing ^ 1;
            func_801BD114(BLOODY_ZOMBIE_CHASE);
        }
        break;

    case BLOODY_ZOMBIE_CHASE:
        if (AnimateEntity(D_8018267C, self) == 0) {
            self->facing = (GetPlayerSide() & 1) ^ 1;
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
        if (animStatus & 0x80 && self->animFrameIdx == 10) {
            func_801C2598(NA_SE_EN_BLOOD_ZOMBIE_SWORD_SLASH);
        }
        if (animStatus == 0) {
            func_801BD114(BLOODY_ZOMBIE_WALK);
        }
        break;

    case BLOODY_ZOMBIE_TAKE_HIT:
        if (self->step_s == 0) {
            // Splat blood
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x4A, self, newEntity);
                newEntity->facing = GetPlayerSide() & 1;
            }
            self->step_s++;
        }

        if (AnimateEntity(D_80182620, self) == 0) {
            func_801BD114(BLOODY_ZOMBIE_WALK);
            self->step_s++;
        }
        break;

    case BLOODY_ZOMBIE_DYING:
        if (self->step_s == 0) {
            firstPrimIndex = g_api.AllocPrimitives(PRIM_GT4, 0x14);
            if (firstPrimIndex == -1) {
                DestroyEntity(self);
                return;
            }
            self->firstPolygonIndex = firstPrimIndex;
            prim = &g_PrimBuf[firstPrimIndex];
            *(s32*)&self->ext.generic.unk7C = prim;
            self->flags |= FLAG_FREE_POLYGONS;
            self->step_s++;
        }

        if (self->animFrameIdx < 13) {
            if (!(g_blinkTimer % 8)) {
                func_801C2598(NA_SE_EN_BLOODY_ZOMBIE_HEMORRHAGE);
                newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(0x4A, self, newEntity);
                    newEntity->facing = self->ext.generic.unk84.U8.unk0;
                    if (self->facing != 0) {
                        newEntity->posX.i.hi -= 4;
                    } else {
                        newEntity->posX.i.hi += 4;
                    }
                    newEntity->posY.i.hi += 4;
                }
                self->ext.generic.unk84.U8.unk0 ^= 1;
            }
            self->ext.generic.unk80.modeS16.unk0 = 0;
        } else {
            if (self->ext.generic.unk80.modeS16.unk0 == 0) {
                func_801C2598(NA_SE_EN_BLOODY_ZOMBIE_HEMORRHAGE);
            }

            self->ext.generic.unk80.modeS16.unk0++;
            if (!(g_blinkTimer & 3)) {
                prim = func_801D24A0(*(s32*)&self->ext.generic.unk7C, 2);
                if (prim != NULL) {
                    func_801D2684(prim);
                    prim->next->r3 = self->ext.generic.unk84.U8.unk0;
                }
                self->ext.generic.unk84.U8.unk0 ^= 1;
            }
        }

        if (self->flags & FLAG_FREE_POLYGONS) {
            prim = *(s32*)&self->ext.generic.unk7C;
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
            self->ext.generic.unk80.modeS16.unk0 = 64;
            self->animCurFrame = 0;
            func_801C2598(NA_SE_EN_EXPLOSIVE_DEATH);
            self->step++;
        }
        break;

    case BLOODY_ZOMBIE_DESTROY:
        if (self->flags & FLAG_FREE_POLYGONS) {
            prim = *(s32*)&self->ext.generic.unk7C;
            while (prim != NULL) {
                if (prim->p3 & 8) {
                    func_801CA498(prim);
                }
                prim = prim->next;
            }
        }

        if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
            DestroyEntity(self);
        }
        break;
    }

    if (self->animCurFrame > 10 && self->animCurFrame < 13) {
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

void func_801CAE0C(Entity* self) { // BloodDrips
    Primitive* prim;
    s16 firstPrimIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180A54);
        firstPrimIndex = g_api.AllocPrimitives(2, 1);
        if (firstPrimIndex != -1) {
            prim = &g_PrimBuf[firstPrimIndex];
            self->firstPolygonIndex = firstPrimIndex;
            self->unk3C = 0;
            *(s32*)&self->ext.generic.unk7C = prim;
            self->flags |= 0x800000;
            while (prim != NULL) {
                prim->x0 = prim->x1 = self->posX.i.hi;
                prim->y0 = prim->y1 = self->posY.i.hi;
                prim->r0 = 255;
                prim->r1 = 32;
                prim->g0 = 0;
                prim->g1 = 0;
                prim->b0 = 48;
                prim->b1 = 16;
                prim->priority = self->zPriority + 1;
                prim->blendMode |= 0x37;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
        }
        break;

    case 1:
        prim = *(s32*)&self->ext.generic.unk7C;
        if (func_801C02F4(&D_801826C4, 0) != 0) {
            prim->y1 += 2;
            if (self->step_s == 0) {
                self->step_s = 1;
            }
        } else {
            self->accelerationY += 0x1800;
            self->posY.val += self->accelerationY;
            if ((prim->y0 - prim->y1) >= 9) {
                prim->y1 = prim->y0 - 8;
            }
        }
        prim->x0 = self->posX.i.hi;
        prim->x1 = self->posX.i.hi;
        prim->y0 = self->posY.i.hi;
        if (prim->y0 < prim->y1) {
            g_api.FreePrimitives(self->firstPolygonIndex);
            DestroyEntity(self);
        }
        break;
    }
}
