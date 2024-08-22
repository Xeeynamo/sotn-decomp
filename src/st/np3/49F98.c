// SPDX-License-Identifier: AGPL-3.0-only
/*
 * Overlay: NP3
 * Enemy: Bloody Zombie
 */

// NOTE: There is an nz0/e_bloody_zombie.c which is almost exactly the same as
// this file. Would maybe be smart to try to de-duplicate. Could be marked as
// an Issue for someone to deal with later?

#include "np3.h"
#include "sfx.h"

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
    Primitive* prim;
    s32 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(g_InitializeEntityData0);
        break;

    case 1:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.bloodSplatter.prim = prim;
        } else {
            DestroyEntity(self);
            return;
        }
        self->step++;
        break;
    case 2:
        prim = FindFirstUnkPrim2(self->ext.bloodSplatter.prim, 2);
        if (prim != NULL) {
            self->ext.bloodSplatter.prim2 = prim;
            UnkPolyFunc2(prim);
            prim->tpage = 0x1A;
            prim->clut = 0x1B7;
            prim->u0 = 0x50;
            prim->u1 = 0x50;
            prim->u2 = 0x40;
            prim->u3 = 0x40;
            prim->v0 = 0x30;
            prim->v1 = 0x40;
            prim->v2 = 0x30;
            prim->v3 = 0x40;
            prim->next->b3 = 0x60;
            prim->next->x1 = self->posX.i.hi;
            prim->next->y0 = self->posY.i.hi;
            LOH(prim->next->r2) = 0x10;
            LOH(prim->next->b2) = 0x10;
            LOW(prim->next->r1) = -0x6000;

            if (self->facingLeft) {
                LOW(prim->next->u0) = 0xA000;
                prim->next->tpage = 0x200;
                prim->next->x1 += 4;
            } else {
                LOW(prim->next->u0) = 0xFFFF6000;
                LOH(prim->next->tpage) = -0x200;
                prim->next->x1 -= 4;
            }
            prim->priority = self->zPriority + 2;
            prim->drawMode = 6;
        }

        prim = FindFirstUnkPrim2(self->ext.bloodSplatter.prim, 2);
        if (prim != NULL) {
            self->ext.bloodSplatter.prim3 = prim;
            UnkPolyFunc2(prim);
            prim->tpage = 0x1A;
            prim->clut = 0x1B7;
            prim->u0 = 0x20;
            prim->u1 = 0x20;
            prim->u2 = 0;
            prim->u3 = 0;
            prim->v0 = 0x20;
            prim->v1 = 0x40;
            prim->v2 = 0x20;
            prim->v3 = 0x40;

            prim->next->x1 = self->posX.i.hi;
            prim->next->y0 = self->posY.i.hi;
            LOH(prim->next->r2) = 8;
            LOH(prim->next->b2) = 0x10;
            prim->next->b3 = 0x80;
            LOW(prim->next->r1) = -0x8000;
            if (self->facingLeft) {
                LOW(prim->next->u0) = 0xC000;
                LOH(prim->next->tpage) = 0x200;
            } else {
                LOW(prim->next->u0) = 0xFFFF4000;
                LOH(prim->next->tpage) = -0x200;
            }
            prim->priority = self->zPriority + 2;
            prim->drawMode = 6;
        }
        self->step++;
        break;

    case 3:
        prim = self->ext.bloodSplatter.prim2;
        UnkPrimHelper(prim);

        if (g_Timer % 2) {
            LOH(prim->next->r2)++;
            LOH(prim->next->b2)++;
            prim->clut = 0x1B7;
        } else {
            prim->clut = 0x16D;
        }

        LOW(prim->next->r1) += 0xC00;

        if (self->facingLeft) {
            prim->next->tpage += 0x18;
        } else {
            prim->next->tpage -= 0x18;
        }

        prim->next->b3 -= 2;
        if (UpdateAnimation(&D_8018268C, prim) == 0) {
            UnkPolyFunc0(prim);
        }

        prim = self->ext.bloodSplatter.prim3;
        UnkPrimHelper(prim);
        LOH(prim->next->r2) += 2;
        LOH(prim->next->b2) += 2;
        if (prim->p1 > 3) {
            LOH(prim->next->b2) = 16;
        }

        prim->next->b3 -= 3;
        if (prim->next->b3 > 240) {
            prim->next->b3 = 0;
        }

        if (UpdateAnimation(&D_801826A4, prim) == 0) {
            UnkPolyFunc0(prim);
        }

        if (self->ext.bloodSplatter.unk80++ > 128) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_801CA498(Primitive* prim) {
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

        if (g_CurrentEntity->facingLeft != 0) {
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
        prim->drawMode = 2;
        prim->next->u2 = 1;
        break;

    case 1:
        UnkPrimHelper(prim);
        *(s32*)&prim->next->r1 += 0x2000;
        if (*(s32*)&prim->next->r1 > 0x20000) {
            UnkPolyFunc0(prim);
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
        PlaySfxPositional(NA_SE_EN_BLOODY_ZOMBIE_INJURED_SCREAM);
        PlaySfxPositional(NA_SE_EN_BLOODY_ZOMBIE_INJURED);
        SetStep(BLOODY_ZOMBIE_TAKE_HIT);
    }

    if (self->flags & FLAG_DEAD && self->step < 8) {
        PlaySfxPositional(NA_SE_EN_BLOODY_ZOMBIE_DEATH_SCREAM);
        self->hitboxState = 0;
        self->flags &= ~FLAG_UNK_20000000;
        SetStep(BLOODY_ZOMBIE_DYING);
    }

    switch (self->step) {
    case BLOODY_ZOMBIE_INIT:
        InitializeEntity(D_80180B38);
        self->hitboxOffX = 1;
        self->hitboxOffY = 4;
        SetStep(BLOODY_ZOMBIE_UNK_2);
        break;

    case BLOODY_ZOMBIE_UNK_2:
        if (UnkCollisionFunc3(&D_801825D4) & 1) {
            SetStep(BLOODY_ZOMBIE_WALK);
        }
        break;

    case BLOODY_ZOMBIE_WALK:
        if (self->step_s == 0) {
            self->ext.generic.unk80.modeS16.unk0 = 128;
            self->step_s++;
        }

        AnimateEntity(D_801825EC, self);
        UnkCollisionFunc2(D_801825E4);

        if (self->facingLeft == 0) {
            self->velocityX = FIX(-0.375);
        } else {
            self->velocityX = FIX(0.375);
        }

        if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
            self->ext.generic.unk80.modeS16.unk0 = 128;
            self->facingLeft ^= 1;
        }

        if (!(Random() % 64)) { // Drop BloodDrips from the enemy knife
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x49, self, newEntity);
                if (self->facingLeft != 0) {
                    newEntity->posX.i.hi += 16;
                } else {
                    newEntity->posX.i.hi -= 16;
                }
                newEntity->posY.i.hi += 12;
            }
        }
        facing = GetSideToPlayer() & 1;
        if (PLAYER.facingLeft == facing && GetDistanceToPlayerX() < 128) {
            self->facingLeft = facing ^ 1;
            SetStep(BLOODY_ZOMBIE_CHASE);
        }
        break;

    case BLOODY_ZOMBIE_CHASE:
        if (AnimateEntity(D_8018267C, self) == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        UnkCollisionFunc2(D_801825E4);

        if (self->facingLeft != 0) {
            self->velocityX = FIX(0.75);
        } else {
            self->velocityX = FIX(-0.75);
        }

        if (!(Random() % 64)) { // Drop BloodDrips from the enemy knife
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x49, self, newEntity);
                if (self->facingLeft != 0) {
                    newEntity->posX.i.hi += 18;
                } else {
                    newEntity->posX.i.hi -= 18;
                }
                newEntity->posY.i.hi += 12;
            }
        }

        if (GetDistanceToPlayerX() < 40) {
            SetStep(BLOODY_ZOMBIE_ATTACK);
        }
        break;

    case BLOODY_ZOMBIE_ATTACK:
        animStatus = AnimateEntity(D_801825FC, self);
        if (animStatus & 0x80 && self->animFrameIdx == 10) {
            PlaySfxPositional(SFX_WEAPON_SWISH_B);
        }
        if (animStatus == 0) {
            SetStep(BLOODY_ZOMBIE_WALK);
        }
        break;

    case BLOODY_ZOMBIE_TAKE_HIT:
        if (self->step_s == 0) {
            // Splat blood
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x4A, self, newEntity);
                newEntity->facingLeft = GetSideToPlayer() & 1;
            }
            self->step_s++;
        }

        if (AnimateEntity(D_80182620, self) == 0) {
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
            if (!(g_Timer % 8)) {
                PlaySfxPositional(NA_SE_EN_BLOODY_ZOMBIE_HEMORRHAGE);
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(0x4A, self, newEntity);
                    newEntity->facingLeft = self->ext.generic.unk84.U8.unk0;
                    if (self->facingLeft != 0) {
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
                PlaySfxPositional(NA_SE_EN_BLOODY_ZOMBIE_HEMORRHAGE);
            }

            self->ext.generic.unk80.modeS16.unk0++;
            if (!(g_Timer & 3)) {
                prim = FindFirstUnkPrim2(*(s32*)&self->ext.generic.unk7C, 2);
                if (prim != NULL) {
                    UnkPolyFunc2(prim);
                    prim->next->r3 = self->ext.generic.unk84.U8.unk0;
                }
                self->ext.generic.unk84.U8.unk0 ^= 1;
            }
        }

        if (self->flags & FLAG_HAS_PRIMS) {
            prim = *(s32*)&self->ext.generic.unk7C;
            while (prim != NULL) {
                if (prim->p3 & 8) {
                    func_801CA498(prim);
                }
                prim = prim->next;
            }
        }

        if (AnimateEntity(D_80182634, self) == 0) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->params = 2;
                newEntity->posY.i.hi += 16;
                if (self->facingLeft != 0) {
                    newEntity->posX.i.hi -= 8;
                } else {
                    newEntity->posX.i.hi += 8;
                }
            }
            self->ext.generic.unk80.modeS16.unk0 = 64;
            self->animCurFrame = 0;
            PlaySfxPositional(NA_SE_EN_EXPLOSIVE_DEATH);
            self->step++;
        }
        break;

    case BLOODY_ZOMBIE_DESTROY:
        if (self->flags & FLAG_HAS_PRIMS) {
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
        *(s16*)&self->hitboxOffX = -12;
        self->hitboxOffY = -12;
    } else {
        self->hitboxWidth = 4;
        self->hitboxHeight = 22;
        self->hitboxOffX = 1;
        self->hitboxOffY = 4;
    }
}

void func_801CAE0C(Entity* self) { // BloodDrips
    Primitive* prim;
    s16 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(g_InitializeEntityData0);
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
                prim->drawMode |= 0x37;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
        }
        break;

    case 1:
        prim = *(s32*)&self->ext.generic.unk7C;
        if (CheckColliderOffsets(&D_801826C4, 0)) {
            prim->y1 += 2;
            if (self->step_s == 0) {
                self->step_s = 1;
            }
        } else {
            self->velocityY += FIX(0.09375);
            self->posY.val += self->velocityY;
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
