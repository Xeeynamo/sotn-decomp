// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no3.h"
#include "../e_merman2.h"

// some sort of explosion
void EntityExplosion2(Entity* self) {
    Primitive* prim;
    s16 primIndex;

    if (self->step == 0) {
        InitializeEntity(g_EInitWaterObject);
        self->animCurFrame = 0;
        self->hitboxState = 0;
        self->zPriority += 4;
        if (self->params != 0) {
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
            if (primIndex == -1) {
                DestroyEntity(self);
                return;
            }
            prim = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
            self->ext.entityExplosion2.prim = prim;
            self->flags |= FLAG_HAS_PRIMS;
            UnkPolyFunc2(prim);
            prim->u0 = 0;
            prim->u1 = 0x20;
            prim->tpage = 0x1A;
            prim->clut = 0x1FF;
            prim->v3 = prim->v2 = 0x20;
            prim->v1 = prim->v0 = 0;
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            LOH(prim->next->r2) = 0x40;
            LOH(prim->next->b2) = 0x40;
            LOH(prim->next->u1) = 0;
            prim->next->b3 = 0x60;
            prim->next->x1 = (u16)self->posX.i.hi;
            prim->next->y0 = (u16)self->posY.i.hi;
            prim->priority = self->zPriority - 4;
            prim->drawMode = DRAW_COLORS | DRAW_UNK02;
        }
    }

    if (self->params != 0) {
        prim = self->ext.entityExplosion2.prim;
        UnkPrimHelper(prim);
        prim->next->b3 += 252;
        LOH(prim->next->u1) -= 128;
        if (prim->next->b3 < 16) {
            prim->drawMode = DRAW_HIDE;
        }
    }

    self->ext.entityExplosion2.unk84++;
    if (!(self->ext.entityExplosion2.unk84 % 4)) {
        self->posY.i.hi++;
    }

    if (AnimateEntity(D_801839A0, self) == 0) {
        DestroyEntity(self);
    }
}

// medium sized water splash used with merman
void EntityMediumWaterSplash(Entity* entity) {
    Entity* newEntity;

    if (entity->step == 0) {
        InitializeEntity(D_80180B54);
        entity->animCurFrame = 0;
        if (entity->facingLeft != 0) {
            entity->velocityX = FIX(2);
            return;
        }
        entity->velocityX = FIX(-2);
        return;
    }
    AnimateEntity(D_80183994, entity);
    MoveEntity();
    if (entity->flags & FLAG_DEAD) {
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, entity, newEntity);
            newEntity->params = 0;
        }
        DestroyEntity(entity);
    }
}

// spawns EntityMediumWaterSplash, part of merman splash
void EntityMermanWaterSplash(Entity* self) {
    Unkstruct_801C7954 sp;
    Entity* newEntity;
    Primitive* prim;
    s16 primIndex;
    s16* posPtr;
    s32* velPtr;
    u8 temp;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        break;

    case 1:
        primIndex = g_api.AllocPrimitives(PRIM_TILE, 4);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.mermanWaterSplash.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;

        for (i = 0; prim != NULL; i++) {
            prim->g0 = prim->r0 = 64;
            prim->b0 = 160;
            prim->v0 = prim->u0 = 2;
            prim->x0 = self->posX.i.hi + D_801839E8[i];
            prim->y0 = self->posY.i.hi - 12;
            LOW(sp.y3) = D_801839C0[i].x;
            prim->y1 = sp.y1;
            prim->y3 = sp.y3;
            LOW(sp.x3) = D_801839C0[i].y;
            prim->x2 = sp.x2;
            prim->x3 = sp.x3;
            prim->p1 = 0;
            prim->p3 = 1;
            prim->p2 = i % 2;
            prim->priority = self->zPriority + 2;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            prim = prim->next;
        }

        posPtr = &D_801839FC;
        velPtr = &D_80183A0C;

        for (i = 0; i < 7; i++) {
            newEntity = AllocEntity(&g_Entities[232], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_HIGH_WATER_SPLASH, self, newEntity);
                newEntity->params = D_801839F4[i];
                newEntity->posX.i.hi = newEntity->posX.i.hi + posPtr[i];
                newEntity->velocityX = velPtr[i];
                newEntity->zPriority = self->zPriority + 1;
            }
        }
        self->ext.mermanWaterSplash.unk84 = 0;
        self->ext.mermanWaterSplash.unk86 = 0;
        self->step++;
        break;

    case 2:
        prim = self->ext.mermanWaterSplash.prim;
        temp = false;
        while (prim != NULL) {
            if (prim->p1 == 0) {
                sp.x0 = prim->x0;
                sp.x1 = prim->x1;
                sp.y0 = prim->y0;
                sp.y2 = prim->y2;
                sp.y1 = prim->y1;
                sp.y3 = prim->y3;
                sp.x2 = prim->x2;
                sp.x3 = prim->x3;
                temp |= true;
                LOW(sp.x1) += LOW(sp.y3);
                LOW(sp.y2) += LOW(sp.x3);
                LOW(sp.x3) += 0x2000;
                if ((LOW(sp.x3) > 0) && (prim->p2 != 0) && (prim->p3 != 0)) {
                    if (LOH(sp.x0) > self->posX.i.hi) {
                        LOW(sp.y3) += 0x4000;
                    } else {
                        LOW(sp.y3) -= 0x4000;
                    }
                    prim->p3 = 0;
                }
                if (prim->y0 & 0xFF00) {
                    prim->p1 = 1;
                    prim->drawMode |= DRAW_HIDE;
                }
                prim->x0 = sp.x0;
                prim->x1 = sp.x1;
                prim->y0 = sp.y0;
                prim->y2 = sp.y2;
                prim->x2 = sp.x2;
                prim->x3 = sp.x3;
                prim->y1 = sp.y1;
                prim->y3 = sp.y3;
            }
            prim = prim->next;
        }
        if (!temp) {
            DestroyEntity(self);
            return;
        }
        break;
    }
}

// some kind of falling object
void EntityFallingObject2(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(g_EInitWaterObject);
        self->animCurFrame = 0;
        self->hitboxState = 0;
        self->flags |= FLAG_UNK_2000;
        self->zPriority += 4;
    }
    MoveEntity();
    self->velocityY += FIX(0.15625);
    if (AnimateEntity(D_801839A8, self) == 0) {
        DestroyEntity(self);
    }
}

void EntityHighWaterSplash(Entity* self) {
    s8 temp; // probably !FAKE

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        self->animSet = ANIMSET_DRA(2);
        self->velocityY = FIX(-5);
        self->palette = 0x8162;
        self->drawMode = DRAW_TPAGE;
        self->palette = 0x8018;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->unk6C = 0xA0;
        self->rotX = 0x100;
        self->rotY = 0x1A0;
        self->drawFlags |= FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
        self->ext.mermanWaterSplash.unk85 = 0x11;
        self->ext.mermanWaterSplash.unk84 = self->params;
        self->drawFlags |= FLAG_DRAW_UNK8;
        break;

    case 1:
        temp = self->ext.mermanWaterSplash.unk84 - 1;
        self->ext.mermanWaterSplash.unk84--;
        self->ext.mermanWaterSplash.unk85--;
        if (!(temp & 0xFF)) {
            self->step++;
        }
        break;

    case 2:
        AnimateEntity(D_801839B0, self);
        MoveEntity();
        self->velocityY += FIX(0.25);
        self->rotX += 6;
        self->rotY -= 4;
        if (self->posY.i.hi > 256) {
            DestroyEntity(self);
        }
        if (!--self->ext.mermanWaterSplash.unk85) {
            self->velocityY = 0;
            self->step++;
        }
        break;

    case 3:
        if (AnimateEntity(D_801839B0, self) == 0) {
            MoveEntity();
            self->velocityY += FIX(0.25);
            self->rotX += 6;
            self->rotY -= 4;
        }
        if (self->posY.i.hi > 256) {
            DestroyEntity(self);
        }
        break;
    }
}

// falling object, larger
void EntityDeadMerman(Entity* self) {
    u8 temp_v0;

    if (self->step == 0) {
        InitializeEntity(g_EInitWaterObject);
        self->animCurFrame = 13;
        self->ext.generic.unk84.S8.unk0 = 0x20;
        self->hitboxState = 0;
        self->velocityY = FIX(0.0625);
        self->palette = self->params + 0xE;
        self->unk6C = 0x80;
        self->drawFlags |= FLAG_DRAW_UNK8;
        self->flags |= FLAG_UNK_2000;
        return;
    }
    MoveEntity();
    temp_v0 = self->ext.generic.unk84.U8.unk0 - 1;
    self->ext.generic.unk84.U8.unk0--;
    self->velocityY += FIX(0.0625);
    self->unk6C += 0xFE;
    if (temp_v0 == 0) {
        DestroyEntity(self);
    }
}

void EntityMermanSpawner(Entity* self) {
    Entity* newEntity;
    u16 temp_s0_2;
    u16 temp_s0;
    s32 temp2;
    s16 temp;

    if (self->step == 0) {
        InitializeEntity(D_80180AD0);
        self->flags |= FLAG_UNK_2000;
    }

    if (!(g_Timer & 0x3F)) {
        Entity* player = &PLAYER;
        temp = g_Tilemap.scrollY.i.hi + player->posY.i.hi;
        if (temp >= 256) {
            temp_s0 = g_Tilemap.scrollX.i.hi + player->posX.i.hi;
            temp_s0_2 = 128;
            temp_s0_2 = temp_s0 - temp_s0_2 + Random();
            temp_s0 = temp_s0_2 - 64;
            if (temp_s0 <= 0x280) {
                temp2 = 496;
                newEntity = AllocEntity(&g_Entities[160], &g_Entities[170]);
                if (newEntity != 0) {
                    if (Random() & 1) {
                        CreateEntityFromCurrentEntity(
                            E_MERMAN_SPAWNER_3A, newEntity);
                        newEntity->params = Random() & 1;
                    } else {
                        CreateEntityFromCurrentEntity(
                            E_MERMAN_SPAWNER_41, newEntity);
                    }
                    newEntity->posX.i.hi = temp_s0_2 - g_Tilemap.scrollX.i.hi;
                    newEntity->posY.i.hi = temp2 - g_Tilemap.scrollY.i.hi;
                }
            }
        }
    }
}
