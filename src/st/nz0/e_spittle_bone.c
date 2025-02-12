// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"
#include "sfx.h"

static s16 D_801824CC[] = {0, 0, 0, 4, 8, -4, -16, 0};
static s16 D_801824DC[] = {0x0000, 0x0800, 0x0C00, 0x0400};
static u16 D_801824E4[] = {
    0x0000, 0x0E00, 0x0F00, 0x0F80, 0x0000, 0x0200, 0x0100, 0x0080,
    0x0000, 0x0A00, 0x0900, 0x0880, 0x0000, 0x0600, 0x0700, 0x0780};
static s32 D_80182504[] = {
    0x0000A000, 0xFFFF6000, 0xFFFFE000, 0x00000000, 0x00012000, 0xFFFEE000};
static u8 D_8012518[] = {0x20, 0x20, 0x28, 0x30, 0x30, 0x30};
static u8 D_80182524[] = {
    0x04, 0x34, 0x04, 0x35, 0x04, 0x36, 0x04, 0x37,
    0x04, 0x38, 0x04, 0x39, 0x00, 0x00, 0x00, 0x00,
};
static u8 D_80182534[] = {
    0x02, 0x40, 0x02, 0x41, 0x02, 0x42, 0x00, 0x00,
};
static s32 D_8018253C[] = {
    0x00000000, 0xFFFDC000, 0x00002000, 0xFFFDD000, 0x00004000, 0xFFFDE000,
    0x00006000, 0xFFFE0000, 0x00008000, 0xFFFE4000, 0xFFFFE000, 0xFFFDD000,
    0xFFFFC000, 0xFFFDE000, 0xFFFFA000, 0xFFFE0000, 0xFFFF8000, 0xFFFE4000,
};

// moves around on walls and drips poison
void EntitySpittleBone(Entity* self) {
    Entity* newEntity;
    s32 i;

    if ((self->flags & FLAG_DEAD) && (self->step < 3)) {
        self->step = 3;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpittleBone);
        self->drawFlags = FLAG_DRAW_ROTZ;
        self->rotZ = 0;
        self->flags &= ~(FLAG_UNK_2000 | FLAG_UNK_200);
        self->facingLeft = self->params;
        break;

    case 1:
        if (UnkCollisionFunc3(D_801824CC) & 1) {
            newEntity = &self[1];
            self->ext.spittleBone.unk7C = 0;
            CreateEntityFromEntity(E_ROTATE_SPITTLEBONE, self, newEntity);
            newEntity->facingLeft = self->facingLeft;
            newEntity->ext.spittleBone.unk7C = self->ext.spittleBone.unk7C;
            if (self->facingLeft != 0) {
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
            UnkCollisionFunc4(self->ext.spittleBone.unk7C);
        if (self->ext.spittleBone.unk82 != 0) {
            self->rotZ += self->ext.spittleBone.unk80;
            self->ext.spittleBone.unk82--;
            if (self->ext.spittleBone.unk82 == 0) {
                self->rotZ = self[1].rotZ;
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
        self->hitboxOffX = (u32)rsin(self->rotZ) >> 8;
        self->hitboxOffY = -(rcos(self->rotZ) * 16) >> 0xC;
        return;

    case 3:
        for (i = 0; i < LEN(D_8012518); i++) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                MakeEntityFromId(E_SPITTLEBONE, self, newEntity);
                newEntity->facingLeft = self->facingLeft;
                newEntity->flags = FLAG_UNK_2000 | FLAG_POS_CAMERA_LOCKED |
                                   FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                                   FLAG_DESTROY_IF_OUT_OF_CAMERA;
                newEntity->palette = 0x20D;
                newEntity->animCurFrame = i + 0x3A;
                newEntity->drawFlags |= FLAG_DRAW_ROTZ;
                newEntity->rotZ = self->rotZ;
                newEntity->step = 4;
                newEntity->velocityX = D_80182504[i];
                newEntity->velocityY = 0xFFFD0000 - ((Random() & 3) << 0xF);
                newEntity->ext.spittleBone.unk82 = D_8012518[i];
            }
        }

        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->params = 1;
            newEntity->posX.i.hi += -(rsin(self->rotZ) * 0x10) >> 0xC;
            newEntity->posY.i.hi += -(rcos(self->rotZ) * 0x10) >> 0xC;
        }
        PlaySfxPositional(SFX_SKELETON_DEATH_C);
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

void EntityRotateSpittlebone(Entity* self) {
    Entity* prevEntity;
    s16 rotZ;
    u32 temp1;
    u32 temp2;
    s32 temp3;
    s8 temp4;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->flags &= ~(FLAG_UNK_2000 | FLAG_UNK_200);
        break;

    case 1:
        temp1 = self->ext.spittleBone.unk7C & 0x3F;
        prevEntity = &self[-1];
        temp4 = UnkCollisionFunc4(self->ext.spittleBone.unk7C);
        self->ext.spittleBone.unk7C = temp4;
        if ((temp4 & 0x3F) != temp1) {
            temp2 = temp4 & 0x3C;
            if (temp2 != 0) {
                temp1 = temp2 >> 2;
                rotZ = D_801824E4[temp1];
            } else {
                rotZ = D_801824DC[temp4 & 3];
            }

            if (self->facingLeft != 0) {
                rotZ = -rotZ;
            }

            self->rotZ = rotZ;
            rotZ -= prevEntity->rotZ;

            if (rotZ > 0x800) {
                rotZ -= 0x1000;
            }
            if (rotZ < -0x800) {
                rotZ += 0x1000;
            }

            temp3 = rotZ;
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
    s32 u0, v0, r0, b0, drawMode;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpittleBoneSpit);
        self->ext.spittleBone.unk82 = 0;
        self->rotX = 0;
        self->rotY = 0;
        return;

    case 1:
        entity = self->ext.spittleBone.unk84;
        if ((entity->rotZ & 0xFFF) == 0x800) {
            if (entity->facingLeft != 0) {
                self->posX.i.hi = entity->posX.i.hi - 3;
            } else {
                self->posX.i.hi = entity->posX.i.hi + 3;
            }
            self->posY.i.hi = entity->posY.i.hi + 27;
            self->rotX += 16;
            self->rotY += 20;
            if (++self->ext.spittleBone.unk82 > 16) {
                self->ext.spittleBone.unk82 = 0;
                self->step++;
            }
            return;
        }
        self->rotY = 0x140;
        self->rotX = 0x100;
        self->step++;
        return;

    case 2:
        AnimateEntity(D_80182534, self);
        MoveEntity();
        self->velocityY += FIX(0.0625);
        g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi, &collider, 0);
        if (collider.effects != EFFECT_NONE) {
            PlaySfxPositional(NA_SE_EN_SPITTLEBONE_ACID_SPLAT);
            EntityExplosionVariantsSpawner(self, 1, 2, 0, 0, 5, 0);
            self->animCurFrame = 0;
            self->hitboxState = 0;
            self->step++;
        }
        break;

    case 3:
        primIndex = g_api.AllocPrimBuffers(PRIM_TILE, 9);
        if (primIndex == -1) {
            DestroyEntity(self);
            break;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.spittleBone.unk84 = prim;
        self->flags |= FLAG_HAS_PRIMS;
        if (prim != NULL) {
            for (u0 = 1, v0 = 2, r0 = 0x20, b0 = 0xc0, drawMode = 0x33, i = 0;
                 prim != NULL; i += 8) {
                prim->u0 = u0;
                prim->v0 = v0;
                prim->x0 = self->posX.i.hi;
                prim->y0 = self->posY.i.hi;
                prim->r0 = r0;
                prim->g0 = r0;
                prim->b0 = b0;
                LOW(prim->x2) = LOW(((u8*)&D_8018253C)[i]);
                LOW(prim->x3) = LOW(((u8*)&D_8018253C)[i + 4]);
                prim->priority = self->zPriority;
                prim->drawMode = drawMode;
                prim = prim->next;
            }
        }
        self->ext.spittleBone.unk82 = 0x30;
        self->step++;
        break;

    case 4:
        self->rotY -= 0x14;
        if (self->rotY < 0) {
            self->rotY = 0;
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
                if (collider.effects != EFFECT_NONE) {
                    prim->drawMode = DRAW_HIDE;
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
