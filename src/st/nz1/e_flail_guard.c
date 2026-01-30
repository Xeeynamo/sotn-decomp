// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz1.h"

static Point32 D_us_80182160[] = {
    {FIX(1.5), FIX(4)},     {FIX(2.5), FIX(3)},      {FIX(2), FIX(4)},
    {FIX(1), FIX(4)},       {FIX(1.5), FIX(4.5)},    {FIX(2), FIX(4)},
    {FIX(1.5), FIX(2.125)}, {FIX(1.0), FIX(1.8125)},
};
static u8 D_us_801821A0[] = {
    26, 34, 31, 32, 36, 38, 20, 22,
};
static u8 D_us_801821A8[] = {
    15, 2, 8, 3, 10, 4, 8, 3, 0, 0, 0, 0,
};
static u8 D_us_801821B4[] = {
    33, 2, 2, 5, 15, 6, 32, 6, 4, 16, 4, 7, 0xFF,
};

static Point16 D_us_801821C4[] = {
    {8, -17}, {8, -6}, {0, -21}, {20, -14},
    {28, -5}, {0, 6},  {13, 18}, {-6, 16},
};

static s16 D_us_801821E4[] = {
    0, 24, 0, 4, 8, -4, -16, 0,
};
extern EInit g_EInitFlailGuard;

// similar to the checks in `create_entities.h` but inverted.
#ifdef VERSION_PSP
#define DECREMENT_AND_CHECK(x) !(x)--
#else
#define DECREMENT_AND_CHECK(x) --(x) == (u8) - 1
#endif

void EntityFlailGuard(Entity* self) {
    Entity* entity;
    s32 i;

    if (self->flags & FLAG_DEAD && self->step < 4) {
        PlaySfxPositional(SFX_SKELETON_DEATH_A);
        self->step = 4;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitFlailGuard);
        self->hitboxOffY = 2;
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        CreateEntityFromEntity(E_FLAIL_GUARD_FLAIL, self, self + 1);
        self->hitboxOffX = 4;
        self->drawMode |= DRAW_TPAGE;
        break;
    case 1:
        UnkCollisionFunc3(D_us_801821E4);
        if (GetDistanceToPlayerX() < 0x50) {
            self->ext.flailGuard.facingLeft = self->facingLeft;
            self->ext.flailGuard.timer = 0;
            self->step = 2;
            return;
        }
        break;
    case 2:
        if (!AnimateEntity(D_us_801821A8, self)) {
            self->ext.flailGuard.timer++;
        }
        if (self->poseTimer == 0) {
            if (self->ext.flailGuard.facingLeft) {
                self->posX.i.hi -= 4;
            } else {
                self->posX.i.hi += 4;
            }
        }
        if (self->ext.flailGuard.timer >= 4) {
            self->ext.flailGuard.timer = 0;
            self->pose = 0;
            self->poseTimer = 0;
            self->ext.flailGuard.facingLeft ^= 1;
            self->step = 3;
        }
        break;
    case 3:
        if (!AnimateEntity(D_us_801821B4, self)) {
            self->pose = 0;
            self->poseTimer = 0;
            self->step = 2;
        }
        if (self->pose == 1 && !self->poseTimer) {
            PlaySfxPositional(SFX_BONE_THROW);
        }
        if (self->pose == 3 && !self->poseTimer) {
            PlaySfxPositional(SFX_FAST_SWORD_SWISHES);
        }
        break;
    case 4:
        for (i = 0; i < 8; i++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_FLAIL_GUARD, self, entity);
                entity->params = i;
                entity->step = 5;
                entity->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                                 FLAG_UNK_00200000 | FLAG_UNK_2000;
                if ((GetSideToPlayer() & 1) ^ 1) {
                    entity->velocityX = -D_us_80182160[i].x;
                } else {
                    entity->velocityX = D_us_80182160[i].x;
                }
                entity->velocityY = -D_us_80182160[i].y;
                entity->ext.flailGuard.timer = D_us_801821A0[i];
            }
        }
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 3;
        }
        entity = self + 1;
        DestroyEntity(entity);
        DestroyEntity(self);
        break;

    case 5:
        InitializeEntity(g_EInitFlailGuard);
        self->hitboxState = 0;
        self->animCurFrame = self->params + 8;
        self->flags |=
            FLAG_DESTROY_IF_OUT_OF_CAMERA | FLAG_UNK_00200000 | FLAG_UNK_2000;
        self->step = 6;
        break;

    case 6:
        MoveEntity();
        self->velocityY += FIX(0.25);

        if (DECREMENT_AND_CHECK(self->ext.flailGuard.timer)) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->params = 1;
                if (self->facingLeft) {
                    entity->posX.i.hi -=
                        D_us_801821C4[self->animCurFrame - 8].x;
                } else {
                    entity->posX.i.hi +=
                        D_us_801821C4[self->animCurFrame - 8].x;
                }
                entity->posY.i.hi += D_us_801821C4[self->animCurFrame - 8].y;
            }
            g_api.PlaySfx(SFX_EXPLODE_B);
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit g_EInitFlailGuardFlail;
static s16 D_us_801821F0[] = {
    13,
    13,
    11,
    0,
};

void EntityFlailGuardFlail(Entity* self) {
    Entity* parent;
    s32 primIndex;
    Primitive* prim;

    s16 posX;
    s16 posY;
    s16 rotX;
    s16 rotY;
    s16 rotX2;
    s16 rotY2;

    parent = self - 1;
    if (!self->step) {
        InitializeEntity(g_EInitFlailGuardFlail);

        self->animCurFrame = 17;
        self->ext.flailGuardFlail.unk7C = 0x100;
        self->ext.flailGuardFlail.unk80 = 8;
        self->ext.flailGuardFlail.prevAttack = self->attack;
        self->attack = self->ext.flailGuardFlail.prevAttack / 4;

        primIndex = g_api.AllocPrimitives(PRIM_GT4, 3);
        if (primIndex != -1) {
            self->primIndex = primIndex;
            self->flags |= FLAG_HAS_PRIMS;
            prim = &g_PrimBuf[primIndex];
            self->ext.flailGuardFlail.prim = prim;
            while (prim != NULL) {
                prim->tpage = 0x1A;
                prim->clut = 0x170;
                prim->u0 = 0;
                prim->u1 = 0x1F;
                prim->u2 = 0;
                prim->u3 = 0x1F;
                prim->v0 = 0;
                prim->v1 = 0;
                prim->v2 = 0x1F;
                prim->v3 = 0x1F;
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0x30;
                prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0x30;
                prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0x30;
                prim->priority = self->zPriority;
                prim->drawMode = DRAW_UNK02;
                prim->drawMode |= DRAW_COLORS;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
            return;
        }
    }

    switch (parent->animCurFrame) {
    case 6:
        self->hitboxState = 1;
        self->animCurFrame = 17;
        self->attack = self->ext.flailGuardFlail.prevAttack;
        if (parent->facingLeft) {
            self->ext.flailGuardFlail.unk7C += self->ext.flailGuardFlail.unk7E;
            posX = parent->posX.i.hi + 64;
            rotX = -FLT_TO_I(rcos(self->ext.flailGuardFlail.unk7C) * 20);
        } else {
            self->ext.flailGuardFlail.unk7C -= self->ext.flailGuardFlail.unk7E;
            posX = parent->posX.i.hi - 64;
            rotX = FLT_TO_I(rcos(self->ext.flailGuardFlail.unk7C) * 20);
        }
        posY = (s32)parent->posY.i.hi; // n.b.! necessary cast
        rotY = FLT_TO_I(rsin(self->ext.flailGuardFlail.unk7C) * 20);
        self->posX.i.hi = posX + rotX;
        self->posY.i.hi = posY + rotY;
        self->ext.flailGuardFlail.unk7E -= 8;
        break;
    case 2:
    case 3:
    case 4:
        self->hitboxState = 1;
        self->animCurFrame = 17;
        self->attack = self->ext.flailGuardFlail.prevAttack / 8;
        if (parent->facingLeft) {
            posX = parent->posX.i.hi - 51;
            rotX = FLT_TO_I(rcos(self->ext.flailGuardFlail.unk7C) * 16);
        } else {
            posX = parent->posX.i.hi + 51;
            rotX = -FLT_TO_I(rcos(self->ext.flailGuardFlail.unk7C) * 16);
        }
        posY = parent->posY.i.hi + D_us_801821F0[parent->animCurFrame - 2];
        rotY = FLT_TO_I(rsin(self->ext.flailGuardFlail.unk7C) * 16);
        self->posX.i.hi = posX + rotX;
        self->posY.i.hi = posY + rotY;
        self->ext.flailGuardFlail.unk7C += self->ext.flailGuardFlail.unk7E;
        self->ext.flailGuardFlail.unk7E += self->ext.flailGuardFlail.unk80;
        if (self->ext.flailGuardFlail.unk7E > 0) {
            self->step_s |= 1;
        }

        if (self->step_s && (self->ext.flailGuardFlail.unk7E < -0x70 ||
                             self->ext.flailGuardFlail.unk7E > 0x70)) {
            self->ext.flailGuardFlail.unk80 = -self->ext.flailGuardFlail.unk80;
        }
        break;
    case 5:
        self->ext.flailGuardFlail.unk7E = 0x200;
        self->hitboxState = 0;
        self->animCurFrame = 0;
        break;

    case 7:
        self->attack = self->ext.flailGuardFlail.prevAttack / 2;
        self->ext.flailGuardFlail.unk80 = 8;
        self->ext.flailGuardFlail.unk7E = -0x110;
        self->ext.flailGuardFlail.unk7C = 0x360;
        self->step_s = 0;
        // fallthrough

    default:
        self->hitboxState = 0;
        self->animCurFrame = 0;
        break;
    }

    rotX2 = rotX / 4;
    rotY2 = rotY / 4;

    prim = self->ext.flailGuardFlail.prim;
    primIndex = 1;
    while (prim != NULL) {
        prim->x0 = posX + rotX2 * primIndex - 3;
        prim->x1 = prim->x0 + 3;
        prim->x2 = prim->x0;
        prim->x3 = prim->x1;

        prim->y0 = posY + rotY2 * primIndex - 3;
        prim->y1 = prim->y0;
        prim->y2 = prim->y0 + 3;
        prim->y3 = prim->y2;

        primIndex++;
        prim = prim->next;
    }

    if (parent->entityId != 0x46) {
        DestroyEntity(self);
    }
}
