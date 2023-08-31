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
        self->rotAngle = 0;
        self->flags &= ~(FLAG_UNK_2000 | 0x200);
        self->facing = self->params;
        break;

    case 1:
        if (func_801BCCFC(&D_801824CC) & 1) {
            newEntity = &self[1];
            self->ext.spittleBone.unk7C = 0;
            CreateEntityFromEntity(E_ROTATE_SPITTLEBONE, self, newEntity);
            newEntity->facing = self->facing;
            newEntity->ext.spittleBone.unk7C = self->ext.spittleBone.unk7C;
            if (self->facing != 0) {
                self->velocityX = FIX(1);
                newEntity->posX.i.hi += 16;
            } else {
                self->velocityX = FIX(-1);
                newEntity->posX.i.hi -= 16;
            }
            newEntity->velocityX = self->velocityX;
            self->step++;
        }
        break;

    case 2:
        AnimateEntity(D_80182524, self);
        self->ext.spittleBone.unk7C =
            func_801C1034(self->ext.spittleBone.unk7C);
        if (self->ext.spittleBone.unk82 != 0) {
            self->rotAngle += self->ext.spittleBone.unk80;
            self->ext.spittleBone.unk82--;
            if (self->ext.spittleBone.unk82 == 0) {
                self->rotAngle = self[1].rotAngle;
            }
        }
        if (((self->ext.spittleBone.unk7C & 0x3F) == 1) &&
            (!(Random() & 0x1F))) {
            newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (newEntity != 0) {
                CreateEntityFromEntity(E_SPITTLEBONE_SPIT, self, newEntity);
                newEntity->ext.spittleBone.unk84 = self;
                newEntity->posY.i.hi += 24;
            }
        }
        self->hitboxOffX = (u32)rsin(self->rotAngle) >> 8;
        self->hitboxOffY = -(rcos(self->rotAngle) * 16) >> 0xC;
        return;

    case 3:
        for (i = 0; i < 6; i++) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                func_801C1780(E_SPITTLEBONE, self, newEntity);
                newEntity->facing = self->facing;
                newEntity->flags = FLAG_UNK_2000 | FLAG_UNK_08000000 |
                                   FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                                   FLAG_DESTROY_IF_OUT_OF_CAMERA;
                newEntity->palette = 0x20D;
                newEntity->animCurFrame = i + 0x3A;
                newEntity->unk19 |= 4;
                newEntity->rotAngle = self->rotAngle;
                newEntity->step = 4;
                newEntity->velocityX = D_80182504[i];
                newEntity->velocityY = 0xFFFD0000 - ((Random() & 3) << 0xF);
                newEntity->ext.spittleBone.unk82 = D_801824E2[i + 0x3A];
            }
        }

        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->params = 1;
            newEntity->posX.i.hi += -(rsin(self->rotAngle) * 0x10) >> 0xC;
            newEntity->posY.i.hi += -(rcos(self->rotAngle) * 0x10) >> 0xC;
        }
        func_801C29B0(0x62B);
        DestroyEntity(self);
        break;

    case 4:
        MoveEntity();
        self->velocityY += FIX(0.15625);
        self->ext.spittleBone.unk82--;
        if (self->ext.spittleBone.unk82 == 0) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->params = 0;
            }
            DestroyEntity(self);
        }
        break;
    }
}

const u32 rodataPadding_801B08B0 = 0;

void EntityRotateSpittlebone(Entity* self) {
    Entity* prevEntity;
    s16 rotAngle;
    u32 temp1;
    u32 temp2;
    s32 temp3;
    s8 temp4;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180BF8);
        self->flags &= ~0x2200;
        break;

    case 1:
        temp1 = self->ext.spittleBone.unk7C & 0x3F;
        prevEntity = &self[-1];
        temp4 = func_801C1034(self->ext.spittleBone.unk7C);
        self->ext.spittleBone.unk7C = temp4;
        if ((temp4 & 0x3F) != temp1) {
            temp2 = temp4 & 0x3C;
            if (temp2 != 0) {
                temp1 = temp2 >> 2;
                rotAngle = D_801824E4[temp1];
            } else {
                rotAngle = D_801824DC[temp4 & 3];
            }

            if (self->facing != 0) {
                rotAngle = -rotAngle;
            }

            self->rotAngle = rotAngle;
            rotAngle -= prevEntity->rotAngle;

            if (rotAngle > 0x800) {
                rotAngle -= 0x1000;
            }
            if (rotAngle < -0x800) {
                rotAngle += 0x1000;
            }

            temp3 = rotAngle;
            if (temp3 < 0) {
                temp3 += 0x1F;
            }
            prevEntity->ext.spittleBone.unk80 = temp3 >> 5;
            prevEntity->ext.spittleBone.unk82 = 0x20;
        }
        break;
    }
}

// spit projectile from spittle bone
void EntitySpittleBoneSpit(Entity* self) {
    Collider collider;
    Unkstruct_801C6C6C test;
    s16 primIndex;
    Primitive* prim;
    Entity* entity;
    s32 u0, v0, r0, b0, blendMode;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180CB8);
        self->ext.spittleBone.unk82 = 0;
        self->unk1A = 0;
        self->unk1C = 0;
        return;

    case 1:
        entity = self->ext.spittleBone.unk84;
        if ((entity->rotAngle & 0xFFF) == 0x800) {
            if (entity->facing != 0) {
                self->posX.i.hi = entity->posX.i.hi - 3;
            } else {
                self->posX.i.hi = entity->posX.i.hi + 3;
            }
            self->posY.i.hi = entity->posY.i.hi + 27;
            self->unk1A += 16;
            self->unk1C += 20;
            if (++self->ext.spittleBone.unk82 > 16) {
                self->ext.spittleBone.unk82 = 0;
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
        self->velocityY += FIX(0.0625);
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
        primIndex = g_api.AllocPrimitives(PRIM_TILE, 9);
        if (primIndex == -1) {
            DestroyEntity(self);
            break;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.spittleBone.unk84 = prim;
        self->flags |= FLAG_HAS_PRIMS;
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
                LOW(prim->x2) = LOW(D_8018253C[i]);
                LOW(prim->x3) = LOW(D_80182540[i]);
                prim->priority = self->zPriority;
                prim->blendMode = blendMode;
                prim = prim->next;
            }
        }
        self->ext.spittleBone.unk82 = 0x30;
        self->step++;
        break;

    case 4:
        self->unk1C -= 0x14;
        if (self->unk1C < 0) {
            self->unk1C = 0;
        }

        prim = *(s32*)&self->ext.spittleBone.unk84;
        while (prim != NULL) {
            test.x.c.x = prim->x0;
            test.x.c.w = prim->x1;
            test.y.c.y = prim->y0;
            test.y.c.h = prim->y1;
            test.x.p += LOW(prim->x2);
            test.y.p += LOW(prim->x3);
            prim->x0 = test.x.c.x;
            prim->x1 = test.x.c.w;
            prim->y0 = test.y.c.y;
            prim->y1 = test.y.c.h;
            LOW(prim->x3) += 0x1800;
            if (LOW(prim->x3) > 0) {
                g_api.CheckCollision(
                    prim->x0, (s16)(prim->y0 + 16), &collider, 0);
                if (collider.effects != 0) {
                    prim->blendMode = BLEND_VISIBLE;
                }
            }
            prim = prim->next;
        }

        if (--self->ext.spittleBone.unk82 == 0) {
            DestroyEntity(self);
        }
        break;
    }
}
