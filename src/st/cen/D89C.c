// SPDX-License-Identifier: AGPL-3.0-or-later

#include "cen.h"
#include "game.h"
#include "sfx.h"

void EntityBreakable(Entity* self) {
    Entity* newEntity;
    u16* ptr;
    s32 j;
    s32 i;
    u16 params = self->params >> 0xC;

    if (self->step == 0) {
        InitializeEntity(D_80180404);
        self->zPriority = 0xB0;
        self->drawMode = D_801805B4[params];
        newEntity = &self[1];
        self->hitboxHeight = D_80180594[params];
        self->animSet = D_801805A4[params];
        DestroyEntity(newEntity);
        CreateEntityFromEntity(E_BACKGROUND_BLOCK, self, newEntity);
        if (params != 0) {
            self[1].posY.i.hi -= 32;
        } else {
            self[1].posY.i.hi -= 16;
        }
        newEntity->params = 1;
    }

    AnimateEntity(D_80180574[params], self);

    if (self->hitParams) {
        g_api.PlaySfx(SFX_CANDLE_HIT);
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != 0) {
            CreateEntityFromCurrentEntity(E_EXPLOSION, newEntity);
            newEntity->params = D_8018059C[params] | 0x10;
        }

        for (ptr = &D_801805BC, i = 0; i < 4; i++) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != 0) {
                CreateEntityFromEntity(0x80, self, newEntity);
                newEntity->posX.i.hi += *ptr;
                ptr++;
                newEntity->posY.i.hi = newEntity->posY.i.hi + *ptr;
                ptr++;
                if (params != 0) {
                    newEntity->posY.i.hi -= 20;
                }
                newEntity->params = i;
            }
        }

        if (params != 0) {
            for (j = 0; j < 3; j++) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != 0) {
                    CreateEntityFromEntity(0x80, self, newEntity);
                    newEntity->posX.i.hi += *ptr;
                    ptr++;
                    newEntity->posY.i.hi += *ptr;
                    ptr++;
                    newEntity->params = j + 4;
                }
            }
        }
        ReplaceBreakableWithItemDrop(self);
        DestroyEntity(&self[1]);
    }
}

void func_8018DB18(Entity* self) {
    Entity* newEntity;
    Collider collider;
    Primitive* prim;
    s16 primIndex;
    s32 facing;
    s16 temp;
    s32 temp2;
    s32 temp3;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180404);
        self->zPriority = 0xB0;
        self->drawFlags = FLAG_DRAW_ROTZ;
        self->animCurFrame = self->params + 28;
        facing = GetSideToPlayer() & 1;

        temp = (Random() & 30) + 8;
        self->ext.generic.unk80.modeS16.unk0 = temp;
        if (self->facingLeft != 0) {
            self->ext.generic.unk80.modeS16.unk0 = -temp;
        }

        if (self->params >= 4) {
            self->ext.generic.unk80.modeS16.unk0 =
                -self->ext.generic.unk80.modeS16.unk0;
        }

        if (facing == 0) {
            self->velocityX = FIX(-1);
        } else {
            self->velocityX = FIX(1);
        }

        temp3 = 0x8000;
        temp2 = Random() << 8;
        self->velocityX = self->velocityX + temp3 - temp2;
        self->velocityY = FIX(-3);
        self->velocityY = (self->params >> 1) * 0x6000 - 0x30000;
        if (self->params == 6) {
            self->velocityX = 0;
            self->velocityY = 0;
            self->step = 2;
        }

        self->primIndex = 0;
        if (self->params == 0) {
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
            if (primIndex != -1) {
                prim = &g_PrimBuf[primIndex];
                self->primIndex = primIndex;
                self->flags |= FLAG_HAS_PRIMS;
                UnkPolyFunc2(prim);
                prim->tpage = 0x1A;
                prim->clut = 0x159;
                prim->u0 = prim->u2 = 0x40;
                prim->u1 = prim->u3 = 0x60;
                prim->v0 = prim->v1 = 0;
                prim->v2 = prim->v3 = 0x20;
                prim->next->x1 = self->posX.i.hi + 4;
                prim->next->y0 = self->posY.i.hi - 8;
                facing = LOH(prim->next->r2) = 32;
                LOH(prim->next->b2) = facing;
                prim->next->b3 = 16;
                prim->priority = 0xB2;
                prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                 DRAW_UNK02 | DRAW_TRANSP;
            }
        }
        break;

    case 1:
        MoveEntity();
        self->rotZ += self->ext.generic.unk80.modeS16.unk0;
        self->velocityY += FIX(0.25);
        g_api.CheckCollision(
            self->posX.i.hi, self->posY.i.hi + 6, &collider, 0);
        if (collider.effects & 1) {
            self->posY.i.hi += collider.unk18;
            self->velocityY = -self->velocityY / 2;
            self->velocityX -= self->velocityX / 3;
            if (self->velocityY > FIX(-0.625)) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != 0) {
                    CreateEntityFromEntity(
                        E_INTENSE_EXPLOSION, self, newEntity);
                    newEntity->params = 16;
                }
                DestroyEntity(self);
                break;
            }
        }

        if (self->primIndex != 0) {
            prim = &g_PrimBuf[self->primIndex];
            UnkPrimHelper(prim);
            LOH(prim->next->r2) = LOH(prim->next->b2) += 4;
            if (LOH(prim->next->r2) > 64) {
                prim->next->b3 += 252;
                if (prim->next->b3 == 0) {
                    g_api.FreePrimitives(self->primIndex);
                    self->primIndex = 0;
                    self->flags &= ~FLAG_HAS_PRIMS;
                }
            }
        }
        break;
    }
}
