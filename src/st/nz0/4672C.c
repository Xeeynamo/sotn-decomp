/*
 * Overlay: NZ0
 * Enemy: Spittle Bone
 */

#include "nz0.h"

// moves around on walls and drips poison
void EntitySpittleBone(Entity* self) {
    Entity* newEntity;
    s32 i;

    if ((self->flags & 0x100) && (self->step < 3)) {
        self->step = 3;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180CAC);
        self->unk19 = 4;
        self->unk1E = 0;
        self->flags &= ~0x2200;
        self->facing = self->subId;
        break;

    case 1:
        if (func_801BCCFC(&D_801824CC) & 1) {
            newEntity = &self[1];
            self->ext.generic.unk7C.S8.unk0 = 0;
            CreateEntityFromEntity(0x32, self, newEntity);
            newEntity->facing = self->facing;
            newEntity->ext.generic.unk7C.S8.unk0 =
                self->ext.generic.unk7C.S8.unk0;
            if (self->facing != 0) {
                self->accelerationX = 0x10000;
                newEntity->posX.i.hi += 16;
            } else {
                self->accelerationX = -0x10000;
                newEntity->posX.i.hi -= 16;
            }
            newEntity->accelerationX = self->accelerationX;
            self->step++;
        }
        break;

    case 2:
        AnimateEntity(D_80182524, self);
        self->ext.generic.unk7C.U8.unk0 =
            func_801C1034(self->ext.generic.unk7C.U8.unk0);
        if (self->ext.generic.unk80.modeS16.unk2 != 0) {
            self->unk1E += self->ext.generic.unk80.modeS16.unk0;
            self->ext.generic.unk80.modeS16.unk2--;
            if (self->ext.generic.unk80.modeS16.unk2 == 0) {
                self->unk1E = self[1].unk1E;
            }
        }
        if (((self->ext.generic.unk7C.U8.unk0 & 0x3F) == 1) &&
            (!(Random() & 0x1F))) {
            newEntity = AllocEntity(D_8007A958, &D_8007A958[32]);
            if (newEntity != 0) {
                CreateEntityFromEntity(0x33, self, newEntity);
                newEntity->ext.generic.unk84.unk = self;
                newEntity->posY.i.hi += 24;
            }
        }
        self->unk10 = (u32)rsin(self->unk1E) >> 8;
        self->hitboxOffY = -(rcos(self->unk1E) * 16) >> 0xC;
        return;

    case 3:
        for (i = 0; i < 6; i++) {
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                func_801C1780(0x31, self, newEntity);
                newEntity->facing = self->facing;
                newEntity->flags = -0x37FFE000;
                newEntity->palette = 0x20D;
                newEntity->animCurFrame = i + 0x3A;
                newEntity->unk19 |= 4;
                newEntity->unk1E = self->unk1E;
                newEntity->step = 4;
                newEntity->accelerationX = D_80182504[i];
                newEntity->accelerationY = 0xFFFD0000 - ((Random() & 3) << 0xF);
                newEntity->ext.generic.unk80.modeS16.unk2 =
                    D_801824E2[i + 0x3A];
            }
        }

        newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->subId = 1;
            newEntity->posX.i.hi += -(rsin(self->unk1E) * 0x10) >> 0xC;
            newEntity->posY.i.hi += -(rcos(self->unk1E) * 0x10) >> 0xC;
        }
        func_801C29B0(0x62B);
        DestroyEntity(self);
        break;

    case 4:
        MoveEntity();
        self->accelerationY += 0x2800;
        self->ext.generic.unk80.modeS16.unk2--;
        if (self->ext.generic.unk80.modeS16.unk2 == 0) {
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->subId = 0;
            }
            DestroyEntity(self);
        }
        break;
    }
}

const u32 rodataPadding_801B08B0 = 0;

// DECOMP_ME_WIP func_801C6B24 https://decomp.me/scratch/T0T7K mostly regalloc
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/4672C", func_801C6B24);

// spit projectile from spittle bone
void EntitySpittleBoneSpit(Entity* self) {
    Collider collider;
    Unkstruct_801C6C6C test;
    s16 firstPrimIndex;
    Primitive* prim;
    Entity* entity;
    s32 u0, v0, r0, b0, blendMode;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180CB8);
        self->ext.generic.unk80.modeS16.unk2 = 0;
        self->unk1A = 0;
        self->unk1C = 0;
        return;

    case 1:
        entity = self->ext.generic.unk84.unk;
        if ((entity->unk1E & 0xFFF) == 0x800) {
            if (entity->facing != 0) {
                self->posX.i.hi = entity->posX.i.hi - 3;
            } else {
                self->posX.i.hi = entity->posX.i.hi + 3;
            }
            self->posY.i.hi = entity->posY.i.hi + 27;
            self->unk1A += 16;
            self->unk1C += 20;
            if (++self->ext.generic.unk80.modeS16.unk2 > 16) {
                self->ext.generic.unk80.modeS16.unk2 = 0;
                self->step++;
            }
            return;
        }
        self->unk1C = 0x140;
        self->unk1A = 0x100;
        self->step++;
        return;

    case 2:
        AnimateEntity(D_80182534, self);
        MoveEntity();
        self->accelerationY += 0x1000;
        g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi, &collider, 0);
        if (collider.effects != 0) {
            func_801C29B0(NA_SE_EN_SPITTLEBONE_ACID_SPLAT);
            func_801C090C(self, 1, 2, 0, 0, 5, 0);
            self->animCurFrame = 0;
            self->hitboxState = 0;
            self->step++;
        }
        break;

    case 3:
        firstPrimIndex = g_api.AllocPrimitives(1, 9);
        if (firstPrimIndex == -1) {
            DestroyEntity(self);
            break;
        }
        prim = &g_PrimBuf[firstPrimIndex];
        self->firstPolygonIndex = firstPrimIndex;
        self->ext.generic.unk84.unk = prim;
        self->flags |= 0x800000;
        if (prim != NULL) {
            for (u0 = 1, v0 = 2, r0 = 0x20, b0 = 0xc0, blendMode = 0x33, i = 0;
                 prim != NULL; i += 8) {
                prim->u0 = u0;
                prim->v0 = v0;
                prim->x0 = self->posX.i.hi;
                prim->y0 = self->posY.i.hi;
                prim->r0 = r0;
                prim->g0 = r0;
                prim->b0 = b0;
                *(s32*)&prim->x2 = *(s32*)&D_8018253C[i];
                *(s32*)&prim->x3 = *(s32*)&D_80182540[i];
                prim->priority = self->zPriority;
                prim->blendMode = blendMode;
                prim = prim->next;
            }
        }
        self->ext.generic.unk80.modeS16.unk2 = 0x30;
        self->step++;
        break;

    case 4:
        self->unk1C -= 0x14;
        if (self->unk1C < 0) {
            self->unk1C = 0;
        }

        prim = *(s32*)&self->ext.generic.unk84.unk;
        while (prim != NULL) {
            test.x.c.x = prim->x0;
            test.x.c.w = prim->x1;
            test.y.c.y = prim->y0;
            test.y.c.h = prim->y1;
            test.x.p += *(s32*)&prim->x2;
            test.y.p += *(s32*)&prim->x3;
            prim->x0 = test.x.c.x;
            prim->x1 = test.x.c.w;
            prim->y0 = test.y.c.y;
            prim->y1 = test.y.c.h;
            *(s32*)&prim->x3 += 0x1800;
            if (*(s32*)&prim->x3 > 0) {
                g_api.CheckCollision(prim->x0, (s16)(prim->y0 + 16), &collider,
                                     0);
                if (collider.effects != 0) {
                    prim->blendMode = 8;
                }
            }
            prim = prim->next;
        }

        if (--self->ext.generic.unk80.modeS16.unk2 == 0) {
            DestroyEntity(self);
        }
        break;
    }
}
