// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"

static s16 D_801824CC[] = {0, 0, 0, 4, 8, -4, -16, 0};
static s16 D_801824DC[] = {0x000, 0x800, 0xC00, 0x400};
static s16 D_801824E4[] = {
    0x000, 0xE00, 0xF00, 0xF80, 0x000, 0x200, 0x100, 0x080,
    0x000, 0xA00, 0x900, 0x880, 0x000, 0x600, 0x700, 0x780};
static s32 D_80182504[] = {FIX(5.0 / 8), FIX(-5.0 / 8), FIX(-1.0 / 8),
                           FIX(0),       FIX(9.0 / 8),  FIX(-9.0 / 8)};
static u8 D_8012518[] = {0x20, 0x20, 0x28, 0x30, 0x30, 0x30};
static u8 D_80182524[] = {4, 52, 4, 53, 4, 54, 4, 55, 4, 56, 4, 57, 0, 0};
static u8 D_80182534[] = {2, 64, 2, 65, 2, 66, 0, 0};
static Point32 D_8018253C[] = {
    {0x0000, -0x24000},  {0x2000, -0x23000},  {0x4000, -0x22000},
    {0x6000, -0x20000},  {0x8000, -0x1C000},  {-0x2000, -0x23000},
    {-0x4000, -0x22000}, {-0x6000, -0x20000}, {-0x8000, -0x1C000},
};

// moves around on walls and drips poison
void EntitySpittleBone(Entity* self) {
    Entity* newEntity;
    s32 i;
    u8 var_s2;

    if ((self->flags & FLAG_DEAD) && self->step < 3) {
        self->step = 3;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpittleBone);
        self->flags &= ~(FLAG_UNK_2000 | FLAG_UNK_200);
        self->facingLeft = self->params;
        self->drawFlags = ENTITY_ROTATE;
        self->rotate = 0;
        break;

    case 1:
        if (UnkCollisionFunc3(D_801824CC) & 1) {
            self->ext.spittleBone.unk7C = 0;
            newEntity = self + 1;
            CreateEntityFromEntity(E_ROTATE_SPITTLEBONE, self, newEntity);
            newEntity->facingLeft = self->facingLeft;
            newEntity->ext.spittleBone.unk7C = self->ext.spittleBone.unk7C;
            if (self->facingLeft) {
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
        var_s2 = (self->ext.spittleBone.unk7C & 0x3F);
        self->ext.spittleBone.unk7C =
            UnkCollisionFunc4(self->ext.spittleBone.unk7C);
        if (self->ext.spittleBone.unk82) {
            self->rotate += self->ext.spittleBone.unk80;
            self->ext.spittleBone.unk82--;
            if (!self->ext.spittleBone.unk82) {
                self->rotate = (self + 1)->rotate;
            }
        }
        if ((self->ext.spittleBone.unk7C & 0x3F) == 1 &&
            (Random() & 0x1F) == 0) {
            newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_SPITTLEBONE_SPIT, self, newEntity);
                newEntity->posY.i.hi += 24;
                newEntity->ext.spittleBone.unk84 = self;
            }
        }
        self->hitboxOffX = (rsin(self->rotate) * 16) >> 0xC;
        self->hitboxOffY = (rcos(self->rotate) * -16) >> 0xC;
        break;

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
                newEntity->drawFlags |= ENTITY_ROTATE;
                newEntity->rotate = self->rotate;
                newEntity->step = 4;
                newEntity->velocityX = D_80182504[i];
                newEntity->velocityY = FIX(-3) - ((Random() & 3) << 0xF);
                newEntity->ext.spittleBone.unk82 = D_8012518[i];
            }
        }

        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->params = 1;
            newEntity->posX.i.hi += (rsin(self->rotate) * -16) >> 0xC;
            newEntity->posY.i.hi += (rcos(self->rotate) * -16) >> 0xC;
        }
        PlaySfxPositional(SFX_SKELETON_DEATH_C);
        DestroyEntity(self);
        break;

    case 4:
        MoveEntity();
        self->velocityY += FIX(0.15625);
        if (!--self->ext.spittleBone.unk82) {
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
    s16 rotate;
    u8 var_s2;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->flags &= ~(FLAG_UNK_2000 | FLAG_UNK_200);
        break;

    case 1:
        prevEntity = self - 1;
        var_s2 = self->ext.spittleBone.unk7C & 0x3F;
        self->ext.spittleBone.unk7C =
            UnkCollisionFunc4(self->ext.spittleBone.unk7C);
        if ((self->ext.spittleBone.unk7C & 0x3F) != var_s2) {
            var_s2 = self->ext.spittleBone.unk7C & 0x3F;
            if (var_s2 & 0x3C) {
                var_s2 = (var_s2 & 0x3C) >> 2;
                rotate = D_801824E4[var_s2];
            } else {
                var_s2 = var_s2 & 3;
                rotate = D_801824DC[var_s2];
            }

            if (self->facingLeft) {
                rotate = -rotate;
            }

            self->rotate = rotate;
            rotate = rotate - prevEntity->rotate;

            if (rotate > 0x800) {
                rotate = rotate - 0x1000;
            }
            if (rotate < -0x800) {
                rotate = rotate + 0x1000;
            }

            prevEntity->ext.spittleBone.unk80 = rotate / 0x20;
            prevEntity->ext.spittleBone.unk82 = 0x20;
        }
        break;
    }
}

// spit projectile from spittle bone
void EntitySpittleBoneSpit(Entity* self) {
    Collider collider;
    Pos tempPos;
    s32 primIndex;
    Primitive* prim;
    Entity* entity;
    s32 i;
    s16 x, y;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpittleBoneSpit);
        self->ext.spittleBone.unk82 = 0;
        self->scaleX = 0;
        self->scaleY = 0;
        break;

    case 1:
        entity = self->ext.spittleBone.unk84;
        if ((entity->rotate & 0xFFF) == 0x800) {
            if (entity->facingLeft) {
                self->posX.i.hi = entity->posX.i.hi - 3;
            } else {
                self->posX.i.hi = entity->posX.i.hi + 3;
            }
            self->posY.i.hi = entity->posY.i.hi + 27;
            self->scaleX += 16;
            self->scaleY += 20;
            if (++self->ext.spittleBone.unk82 > 16) {
                self->ext.spittleBone.unk82 = 0;
                self->step++;
            }
        } else {
            self->scaleY = 0x140;
            self->scaleX = 0x100;
            self->step++;
        }
        break;

    case 2:
        AnimateEntity(D_80182534, self);
        MoveEntity();
        self->velocityY += FIX(0.0625);
        x = self->posX.i.hi;
        y = self->posY.i.hi;
        g_api.CheckCollision(x, y, &collider, 0);
        if (collider.effects != EFFECT_NONE) {
            PlaySfxPositional(SFX_SPITTLEBONE_ACID_SPLAT);
            EntityExplosionVariantsSpawner(self, 1, 2, 0, 0, 5, 0);
            self->animCurFrame = 0;
            self->hitboxState = 0;
            self->step++;
        }
        break;

    case 3:
        primIndex = g_api.AllocPrimitives(PRIM_TILE, 9);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.spittleBone.unk84 = (Entity*)prim;
            for (i = 0; prim != NULL; i++, prim = prim->next) {
                prim->u0 = 1;
                prim->v0 = 2;
                prim->x0 = self->posX.i.hi;
                prim->y0 = self->posY.i.hi;
                prim->r0 = 0x20;
                prim->g0 = 0x20;
                prim->b0 = 0xC0;
                LOW(prim->x2) = D_8018253C[i].x;
                LOW(prim->x3) = D_8018253C[i].y;
                prim->priority = self->zPriority;
                prim->drawMode =
                    DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            }
            self->ext.spittleBone.unk82 = 0x30;
            self->step++;
        } else {
            DestroyEntity(self);
        }
        break;

    case 4:
        self->scaleY -= 0x14;
        if (self->scaleY < 0) {
            self->scaleY = 0;
        }

        prim = (Primitive*)self->ext.spittleBone.unk84;
        while (prim != NULL) {
            tempPos.x.i.hi = prim->x0;
            tempPos.x.i.lo = prim->x1;
            tempPos.y.i.hi = prim->y0;
            tempPos.y.i.lo = prim->y1;
            tempPos.x.val += LOWU(prim->x2);
            tempPos.y.val += LOWU(prim->x3);
            LOH(prim->x0) = tempPos.x.i.hi;
            LOH(prim->x1) = tempPos.x.i.lo;
            LOH(prim->y0) = tempPos.y.i.hi;
            LOH(prim->y1) = tempPos.y.i.lo;
            LOW(prim->x3) += 0x1800;
            if (LOW(prim->x3) > 0) {
                x = prim->x0;
                y = prim->y0 + 16;
                g_api.CheckCollision(x, y, &collider, 0);
                if (collider.effects != EFFECT_NONE) {
                    prim->drawMode = DRAW_HIDE;
                }
            }
            prim = prim->next;
        }

        if (!--self->ext.spittleBone.unk82) {
            DestroyEntity(self);
        }
        break;
    }
}
