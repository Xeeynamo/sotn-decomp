// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno4.h"

INCLUDE_ASM("st/rno4/nonmatchings/unk_58A30", func_us_801BBE58_from_rnz1);

INCLUDE_ASM("st/rno4/nonmatchings/unk_58A30", func_us_801BC650_from_rnz1);

INCLUDE_ASM("st/rno4/nonmatchings/unk_58A30", func_us_801BCA5C_from_rnz1);

INCLUDE_ASM("st/rno4/nonmatchings/unk_58A30", func_us_801BCB9C_from_rnz1);

INCLUDE_ASM("st/rno4/nonmatchings/unk_58A30", func_us_801BCD80_from_rnz1);

INCLUDE_ASM("st/rno4/nonmatchings/unk_58A30", func_us_801BCE4C_from_rnz1);

INCLUDE_ASM("st/rno4/nonmatchings/unk_58A30", func_us_801BCFC8_from_rnz1);

INCLUDE_ASM("st/rno4/nonmatchings/unk_58A30", TryThrow);

INCLUDE_ASM("st/rno4/nonmatchings/unk_58A30", EntityJackOBones);

void EntityJackOBonesDeathParts(Entity* self) {
    extern EInit g_EInitJackOBones2;
    extern u16 g_JackOBonesDeathPartsRotSpeeds[];
    if (self->step) {
        if (--self->ext.jackoBones.deathPartLife) {
            self->rotate += g_JackOBonesDeathPartsRotSpeeds[self->params];
            FallEntity();
            MoveEntity();
            return;
        }
        self->entityId = E_EXPLOSION;
        self->pfnUpdate = EntityExplosion;
        self->params = 0;
        self->step = 0;
        return;
    }
    InitializeEntity(g_EInitJackOBones2);
    self->animCurFrame = (self->params & 0xFF) + 15;
    if (self->params & 0x100) {
        self->palette++;
    }
    self->drawFlags = ENTITY_ROTATE;
    if (self->facingLeft) {
        self->velocityX = -self->velocityX;
    }
}

INCLUDE_ASM("st/rno4/nonmatchings/unk_58A30", EntityJackOBonesJack);

INCLUDE_ASM("st/rno4/nonmatchings/unk_58A30", TryShoot);

INCLUDE_ASM("st/rno4/nonmatchings/unk_58A30", DrawLaserRing);

INCLUDE_RODATA("st/rno4/nonmatchings/unk_58A30", D_us_801C4800);

void EntityNovaSkeleton(Entity* self) {
    extern u16 g_EInitNovaSkeleton;
    extern u8 g_NovaSkeletonSensors[];
    extern u8 g_NovaSkeletonAnimWalkLeft[];
    extern u8 g_NovaSkeletonAnimWalkRight[];
    extern u8 g_NovaSkeletonAnimIdle[];
    extern u8 g_NovaSkeletonAnimAttack[];
    extern u8 g_NovaSkeletonAnimAttackEnd[];
    extern u8 g_NovaSkeletonDeathPartLifetimes[];
    extern s32 g_NovaSkeletonDeathPartVelocityX[];
    extern s32 g_NovaSkeletonDeathPartVelocityY[];
    extern s16 g_NovaSkeletonDeathPartOffsetX[];
    extern s16 g_NovaSkeletonDeathPartOffsetY[];
    extern u8 g_NovaSkeletonCooldowns[];
    s32 var_s4;
    Entity* other;
    Primitive* prim;
    s32 primIndex;
    s32 i;

    if (self->flags & FLAG_DEAD) {
        SetStep(8);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(&g_EInitNovaSkeleton);
        self->ext.nova.cooldown = 0x50;
#if defined(VERSION_PSP)
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
#else
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
#endif
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.nova.prim = prim;
        UnkPolyFunc2(prim);
        prim->tpage = 0x12;
        prim->clut = 0x216;
        prim->u0 = prim->u2 = 0xC0;
        prim->u1 = prim->u3 = 0xFF;
        prim->v0 = prim->v1 = 0;
        prim->v2 = prim->v3 = 0x40;
        prim->priority = self->zPriority + 1;
        prim->drawMode = DRAW_HIDE;
        break;

    case 1:
        if (UnkCollisionFunc3(g_NovaSkeletonSensors) == 0) {
            break;
        }
        SetStep(2);
        break;

    case 2:
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        AnimateEntity(g_NovaSkeletonAnimIdle, self);
        if (GetDistanceToPlayerX() < 0x70) {
            SetStep(4);
        }
        break;

    case 3:
        if (AnimateEntity(g_NovaSkeletonAnimWalkLeft, self) == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        self->ext.nova.movingLeft = self->facingLeft;
        if (self->ext.nova.movingLeft) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }
        if (GetDistanceToPlayerX() < 0x4C) {
            self->step = 4;
        }
        TryShoot();
        break;

    case 4:
        if (AnimateEntity(g_NovaSkeletonAnimWalkRight, self) == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        self->ext.nova.movingLeft = self->facingLeft ^ 1;
        if (self->ext.nova.movingLeft) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }
        if (GetDistanceToPlayerX() > 0x5C) {
            self->step = 3;
        }
        TryShoot();
        break;

    case 5:
        break;

    case 6:
        if (AnimateEntity(g_NovaSkeletonAnimAttack, self) == 0) {
            self->ext.nova.ringState = 0;
            SetStep(7);
        }
        if ((!self->poseTimer) && (self->pose == 2)) {
            PlaySfxPositional(SFX_ELECTRICITY);
        }
        break;

    case 7:
        switch (self->step_s) {
        case 0:
            other = self + 1;
            CreateEntityFromEntity(E_NOVA_LASER, self, other);
            if (self->facingLeft) {
                other->posX.i.hi += 0xA;
            } else {
                other->posX.i.hi -= 0xA;
            }
            other->posY.i.hi -= 4;
            other->facingLeft = self->facingLeft;
            self->step_s++;
            break;

        case 1:
            prim = self->ext.nova.prim;
            PrimDecreaseBrightness(prim, 5);
            break;
        }

        DrawLaserRing();
        if (AnimateEntity(g_NovaSkeletonAnimAttackEnd, self) == 0) {
            prim = self->ext.nova.prim;
            prim->drawMode = DRAW_HIDE;
            var_s4 = ++self->ext.nova.laserTimerIndex & 7;
            self->ext.nova.cooldown = g_NovaSkeletonCooldowns[var_s4];
            SetStep(4);
        }
        break;

    case 8:
        for (i = 0; i < 6; i++) {
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other == NULL) {
                break;
            }
            CreateEntityFromCurrentEntity(E_BLADE_SOLDIER_DEATH_PARTS, other);
            other->facingLeft = self->facingLeft;
            other->params = i;
            other->ext.nova.deathPartLife = g_NovaSkeletonDeathPartLifetimes[i];
            if (self->facingLeft) {
                other->posX.i.hi -= g_NovaSkeletonDeathPartOffsetX[i];
            } else {
                other->posX.i.hi += g_NovaSkeletonDeathPartOffsetX[i];
            }
            other->posY.i.hi += g_NovaSkeletonDeathPartOffsetY[i];
            other->velocityX = g_NovaSkeletonDeathPartVelocityX[i];
            other->velocityY = g_NovaSkeletonDeathPartVelocityY[i];
        }
        PlaySfxPositional(SFX_SKELETON_DEATH_B);
        DestroyEntity(self);
        break;
    }
}

void EntityBladeSoldierDeathParts(Entity* self) {
    extern EInit g_EInitNovaSkeleton;
    extern u16 g_BladeSoldierDeathPartsRotSpeeds[];
    if (self->step) {
        if (--self->ext.bladeSoldierDeathParts.lifetime) {
            self->rotate += g_BladeSoldierDeathPartsRotSpeeds[self->params];
            FallEntity();
            MoveEntity();
            return;
        }
        self->entityId = E_EXPLOSION;
        self->pfnUpdate = EntityExplosion;
        self->params = 0;
        self->step = 0;
        return;
    }
    InitializeEntity(g_EInitNovaSkeleton);
    self->hitboxState = 0;
    self->flags |=
        FLAG_DESTROY_IF_OUT_OF_CAMERA | FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
        FLAG_UNK_00200000 | FLAG_UNK_2000;
    self->animCurFrame = self->params + 29;
    self->drawFlags = ENTITY_ROTATE;
    if (self->facingLeft) {
        self->velocityX = -self->velocityX;
    }
}

extern u16 D_us_80180C20;
extern Entity g_Entities_224;
extern u8 g_NovaLaserPrimData[];
extern Entity g_Entities[];

void EntityNovaLaser(Entity* self) {
    s32 centerX;
    s32 primIndex;
    s32 centerY;
    Entity* other;
    s32 primX;
    s32 var_s2;
    u8* var_s1;
    Primitive* prim;

    switch (self->step) {
    case 0:
        InitializeEntity(&D_us_80180C20);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 3);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.nova.prim = prim;
        var_s1 = g_NovaLaserPrimData;
        for (var_s2 = 0; var_s2 < 3; prim = prim->next, var_s2++) {
            prim->tpage = 0x12;
            prim->clut = 0x216;
            prim->u0 = prim->u2 = *var_s1++ + 0x80;
            prim->u1 = prim->u3 = *var_s1++ + 0x80;
            prim->v0 = prim->v1 = 0x40;
            prim->v2 = prim->v3 = 0x5F;
            prim->r0 = prim->g0 = prim->b0 = *var_s1++;
            LOW(prim->r2) = LOW(prim->r0);
            prim->r1 = prim->g1 = prim->b1 = *var_s1++;
            LOW(prim->r3) = LOW(prim->r1);
            prim->priority = self->zPriority + 2;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;
        }
        self->ext.nova.laserTimer = 0x60;
        self->ext.nova.laserLength = 0;

    case 1:
        self->ext.nova.laserFadeTimer = 0x10;
        if (self->ext.nova.laserLength < 0x80) {
            self->ext.nova.laserLength += 0x10;
        } else {
            self->ext.nova.laserLength = 0x80;
            self->hitboxState = 1;
            self->step++;
        }

    case 2:
        if (!(self->ext.nova.laserTimer & 3)) {
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(E_NOVA_PULSE, self, other);
                other->zPriority = self->zPriority - 1;
                other->ext.nova.laserLength = self->ext.nova.laserLength;
                other->facingLeft = self->facingLeft;
            }
        }
        if (!(self->ext.nova.laserTimer & 0xF)) {
            PlaySfxPositional(SFX_BAT_ECHO_A);
        }
        if (self->ext.nova.laserTimer < 0x10) {
            PlaySfxPositional(SFX_BAT_ECHO_D);
            self->step++;
        }

    case 3:
        if (Random() & 1) {
            if (self->ext.nova.laserLength < 0x88) {
                self->ext.nova.laserLength++;
            } else if (self->ext.nova.laserLength > 0x78) {
                self->ext.nova.laserLength--;
            }
        }
        self->hitboxWidth = self->ext.nova.laserLength / 2 + 0x10;
        self->hitboxOffX = -self->ext.nova.laserLength / 2 - 0x10;
        self->hitboxHeight = 8;
        other = self - 1;
        if (other->entityId != 0x56) {
            self->ext.nova.laserTimer = 1;
        }
        if (!--self->ext.nova.laserTimer) {
            self->hitboxState = 0;
            self->step++;
        }
        break;

    case 4:
        self->ext.nova.laserFadeTimer--;
        if (!self->ext.nova.laserFadeTimer) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    centerX = self->posX.i.hi;
    centerY = self->posY.i.hi;
    prim = self->ext.nova.prim;
    for (var_s2 = 0; var_s2 < 3; prim = prim->next, var_s2++) {
        prim->y0 = prim->y1 = centerY - self->ext.nova.laserFadeTimer;
        prim->y2 = prim->y3 = centerY + self->ext.nova.laserFadeTimer;
        if (g_Timer & 1) {
            prim->clut = 0x216;
        } else {
            prim->clut = 0x217;
        }
    }

    prim = self->ext.nova.prim;
    primX = centerX;
    if (self->facingLeft) {
        primX -= 0x10;
    } else {
        primX += 0x10;
    }

    prim->x1 = prim->x3 = primX;
    if (self->facingLeft) {
        primX += 0x20;
    } else {
        primX -= 0x20;
    }
    prim->x0 = prim->x2 = primX;

    prim = prim->next;
    prim->x1 = prim->x3 = primX;
    if (self->facingLeft) {
        primX += self->ext.nova.laserLength;
    } else {
        primX -= self->ext.nova.laserLength;
    }
    prim->x0 = prim->x2 = primX;

    prim = prim->next;
    prim->x1 = prim->x3 = primX;
    if (self->facingLeft) {
        primX += 0x20;
    } else {
        primX -= 0x20;
    }
    prim->x0 = prim->x2 = primX;
    prim = prim->next;
}

INCLUDE_ASM("st/rno4/nonmatchings/unk_58A30", EntityNovaLaserPulse);

INCLUDE_ASM("st/rno4/nonmatchings/unk_58A30", EntityImp);

#include "../e_imp_smoke.h"

#define RDAI_UNK33_DEATH_PARTICLE E_IMP_DEATH_PARTICLE
#include "../e_rdai_unk33.h"
#undef RDAI_UNK33_DEATH_PARTICLE

#include "../e_imp_death_particle.h"
