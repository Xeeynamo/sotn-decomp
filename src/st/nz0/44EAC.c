/*
 * Overlay: NZ0
 * Enemy: Bloody Zombie
 */

#include "nz0.h"

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

void EntityBloodSplatter(Entity* self) {
    Primitive *prim, *prim2, *prim3;
    s16 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180BE0);
        return;

    case 1:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
        if (primIndex != -1) {
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            *(s32*)&self->ext.generic.unk7C = prim;
            self->flags |= FLAG_HAS_PRIMS;
            self->step++;
            return;
        }
        DestroyEntity(self);
        break;

    case 2:
        prim = func_801C9E98(*(s32*)&self->ext.generic.unk7C, 2);
        if (prim != NULL) {
            self->ext.generic.unk8C.primPtr = prim;
            func_801CA07C(prim);
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

        prim = func_801C9E98(*(s32*)&self->ext.generic.unk7C, 2);
        if (prim != NULL) {
            *(s32*)&self->ext.generic.unk90 = prim;
            func_801CA07C(prim);
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
        prim = self->ext.generic.unk8C.entityPtr;
        func_801C9930(prim);

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
        if (func_801C9D18(&D_8018238C, prim) == 0) {
            func_801CA0D0(prim);
        }

        prim = *(s32*)&self->ext.generic.unk90;
        func_801C9930(prim);
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

        if (func_801C9D18(&D_801823A4, prim) == 0) {
            func_801CA0D0(prim);
        }

        if (self->ext.generic.unk80.modeS16.unk0++ > 128) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_801C53AC(Primitive* prim) {
    switch (prim->next->u2) {
    case 0:
        prim->tpage = 0x12;
        prim->clut = 0x16D;
        prim->u0 = 80;
        prim->u1 = 96;
        prim->v1 = 239;
        prim->v0 = 239;
        prim->v3 = 255;
        prim->v2 = 255;
        prim->u2 = prim->u0;
        prim->u3 = prim->u1;
        *(s16*)&prim->next->r2 = 16;
        *(s16*)&prim->next->b2 = 16;
        prim->next->x1 = g_CurrentEntity->posX.i.hi;
        prim->next->y0 = g_CurrentEntity->posY.i.hi;

        if (g_CurrentEntity->facing != 0) {
            prim->next->x1 -= 8;
        } else {
            prim->next->x1 += 8;
        }
        if (prim->next->r3 == 0) {
            *(s32*)&prim->next->u0 = -0x4000;
        } else {
            *(s32*)&prim->next->u0 = 0x4000;
        }
        *(s32*)&prim->next->r1 = -0x20000;
        prim->next->b3 = 0x80;
        prim->priority = g_CurrentEntity->zPriority + 1;
        prim->blendMode = 2;
        prim->next->u2 = 1;
        break;

    case 1:
        func_801C9930(prim);
        *(s32*)&prim->next->r1 += 0x2000;
        if (*(s32*)&prim->next->r1 > 0x20000) {
            func_801CA0D0(prim);
        }
        break;
    }
}

void EntityBloodyZombie(Entity* self) {
    Primitive* prim;
    Entity* newEntity;
    s16 primIndex;
    s16 facing;
    s32 animStatus;

    if (self->unk44 && self->step & 1) {
        func_801C29B0(NA_SE_EN_BLOODY_ZOMBIE_INJURED_SCREAM);
        func_801C29B0(NA_SE_EN_BLOODY_ZOMBIE_INJURED);
        SetStep(BLOODY_ZOMBIE_TAKE_HIT);
    }

    if (self->flags & 0x100 && self->step < 8) {
        func_801C29B0(NA_SE_EN_BLOODY_ZOMBIE_DEATH_SCREAM);
        self->hitboxState = 0;
        self->flags &= ~FLAG_UNK_20000000;
        SetStep(BLOODY_ZOMBIE_DYING);
    }

    switch (self->step) {
    case BLOODY_ZOMBIE_INIT:
        InitializeEntity(D_80180C7C);
        self->hitboxOffX = 1;
        self->hitboxOffY = 4;
        SetStep(BLOODY_ZOMBIE_UNK_2);
        break;

    case BLOODY_ZOMBIE_UNK_2:
        if (func_801BCCFC(D_801822D4) & 1) {
            SetStep(BLOODY_ZOMBIE_WALK);
        }
        break;

    case BLOODY_ZOMBIE_WALK:
        if (self->step_s == 0) {
            self->ext.generic.unk80.modeS16.unk0 = 128;
            self->step_s++;
        }

        AnimateEntity(D_801822EC, self);
        func_801BCF74(D_801822E4);

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
                CreateEntityFromEntity(0x2C, self, newEntity);
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
            SetStep(BLOODY_ZOMBIE_CHASE);
        }
        break;

    case BLOODY_ZOMBIE_CHASE:
        if (AnimateEntity(D_8018237C, self) == 0) {
            self->facing = (GetPlayerSide() & 1) ^ 1;
        }
        func_801BCF74(D_801822E4);

        if (self->facing != 0) {
            self->accelerationX = 0xC000;
        } else {
            self->accelerationX = -0xC000;
        }

        if (!(Random() % 64)) { // Drop BloodDrips from the enemy knife
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x2C, self, newEntity);
                if (self->facing != 0) {
                    newEntity->posX.i.hi += 18;
                } else {
                    newEntity->posX.i.hi -= 18;
                }
                newEntity->posY.i.hi += 12;
            }
        }

        if (GetPlayerDistanceX() < 40) {
            SetStep(BLOODY_ZOMBIE_ATTACK);
        }
        break;

    case BLOODY_ZOMBIE_ATTACK:
        animStatus = AnimateEntity(D_801822FC, self);
        if (animStatus & 0x80 && self->animFrameIdx == 10) {
            func_801C29B0(NA_SE_EN_BLOOD_ZOMBIE_SWORD_SLASH);
        }
        if (animStatus == 0) {
            SetStep(BLOODY_ZOMBIE_WALK);
        }
        break;

    case BLOODY_ZOMBIE_TAKE_HIT:
        if (self->step_s == 0) {
            // Splat blood
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x2D, self, newEntity);
                newEntity->facing = GetPlayerSide() & 1;
            }
            self->step_s++;
        }

        if (AnimateEntity(D_80182320, self) == 0) {
            SetStep(BLOODY_ZOMBIE_WALK);
            self->step_s++;
        }
        break;

    case BLOODY_ZOMBIE_DYING:
        if (self->step_s == 0) {
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x14);
            if (primIndex == -1) {
                DestroyEntity(self);
                return;
            }
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            *(s32*)&self->ext.generic.unk7C = prim;
            self->flags |= FLAG_HAS_PRIMS;
            self->step_s++;
        }

        if (self->animFrameIdx < 13) {
            if (!(g_blinkTimer % 8)) {
                func_801C29B0(NA_SE_EN_BLOODY_ZOMBIE_HEMORRHAGE);
                newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(0x2D, self, newEntity);
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
                func_801C29B0(NA_SE_EN_BLOODY_ZOMBIE_HEMORRHAGE);
            }

            self->ext.generic.unk80.modeS16.unk0++;
            if (!(g_blinkTimer & 3)) {
                prim = func_801C9E98(*(s32*)&self->ext.generic.unk7C, 2);
                if (prim != NULL) {
                    func_801CA07C(prim);
                    prim->next->r3 = self->ext.generic.unk84.U8.unk0;
                }
                self->ext.generic.unk84.U8.unk0 ^= 1;
            }
        }

        if (self->flags & FLAG_HAS_PRIMS) {
            prim = *(s32*)&self->ext.generic.unk7C;
            while (prim != NULL) {
                if (prim->p3 & 8) {
                    func_801C53AC(prim);
                }
                prim = prim->next;
            }
        }

        if (AnimateEntity(D_80182334, self) == 0) {
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->params = 2;
                newEntity->posY.i.hi += 16;
                if (self->facing != 0) {
                    newEntity->posX.i.hi -= 8;
                } else {
                    newEntity->posX.i.hi += 8;
                }
            }
            self->ext.generic.unk80.modeS16.unk0 = 64;
            self->animCurFrame = 0;
            func_801C29B0(NA_SE_EN_EXPLOSIVE_DEATH);
            self->step++;
        }
        break;

    case BLOODY_ZOMBIE_DESTROY:
        if (self->flags & FLAG_HAS_PRIMS) {
            prim = *(s32*)&self->ext.generic.unk7C;
            while (prim != NULL) {
                if (prim->p3 & 8) {
                    func_801C53AC(prim);
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
        *(s16*)&self->hitboxOffX = -12;
        self->hitboxOffY = -12;
    } else {
        self->hitboxWidth = 4;
        self->hitboxHeight = 22;
        self->hitboxOffX = 1;
        self->hitboxOffY = 4;
    }
}

void func_801C5D20(Entity* self) { // BloodDrips
    Primitive* prim;
    s16 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180BE0);
        primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 1);
        if (primIndex != -1) {
            prim = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
            self->hitboxState = 0;
            *(s32*)&self->ext.generic.unk7C = prim;
            self->flags |= FLAG_HAS_PRIMS;
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
        if (func_801C070C(&D_801823C4, 0) != 0) {
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
            g_api.FreePrimitives(self->primIndex);
            DestroyEntity(self);
        }
        break;
    }
}
