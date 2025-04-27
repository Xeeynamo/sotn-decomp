// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no4.h"

void EntityFishheadSpawner(Entity* self) {
    Entity* entity;
    s32 params;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitFishheadSpawner);
        self->animCurFrame = 0x13;
        params = self->params;

        // Spawn two stacked fishheads
        entity = self + 1;
        CreateEntityFromEntity(E_FISHHEAD, self, entity);
        entity->params = params & 0x100;
        entity->facingLeft = params & 1;

        entity = self + 2;
        CreateEntityFromEntity(E_FISHHEAD, self, entity);
        entity->params = (params & 0x100) + 1;
        entity->facingLeft = (params & 2) >> 1;
        entity->posY.i.hi -= 0x18;
        break;
    default:
        break;
    }
}

extern u16 D_us_80180C22; // palette
extern u8 D_us_80182700[];
extern u8 D_us_80182708[];
extern u8 D_us_8018274C[];
extern u8 D_us_80182764[];
extern s8 D_us_801827B4[];
extern u8 D_us_801827C4[];
extern s16 D_us_801827D8[];

void EntityFishhead(Entity* self) {
    Entity* entity;
    s32 playerFacing;
    s32 i;
    s8* ptr;

    if (self->flags & 0x100 && self->step != 5) {
        SetStep(5);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitFishhead);
        self->animCurFrame = 1;
        self->palette += 5;
        if (!(self->params & 1)) {
            self->ext.fishhead.unk86 = 1;
        }
        self->ext.fishhead.unk84 = Random() & 7;
        // fallthrough
    case 1:
    case 2:
        switch (self->step_s) {
        case 0:
            self->ext.fishhead.unk80 = D_us_801827D8[self->ext.fishhead.unk84];
            self->ext.fishhead.unk84++;
            self->ext.fishhead.unk84 &= 7;
            self->step_s++;
            // fallthrough
        case 1:
            AnimateEntity(D_us_80182700, self);
            if (!(self->flags & 0xF)) {
                self->ext.fishhead.unk82 += 0x10;
                if (self->ext.fishhead.unk82 > 0xA80) {
                    self->ext.fishhead.unk82 = -self->ext.fishhead.unk82;
                }
                playerFacing = (abs(self->ext.fishhead.unk82) >> 8);
                self->palette = D_us_80180C22 + 5 + playerFacing;
            }
            if (!(self->ext.fishhead.unk80 & 0xF)) {
                for (i = 0; i < 5; i++) {
                    entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                    if (entity != NULL) {
                        CreateEntityFromEntity(0x41, self, entity);
                        entity->zPriority = self->zPriority + 1;
                        if (self->facingLeft) {
                            entity->posX.i.hi += 0x12;
                        } else {
                            entity->posX.i.hi -= 0x12;
                        }
                        entity->posY.i.hi -= 4;
                        entity->posY.i.hi -= Random() & 7;
                        entity->posX.i.hi += (Random() & 7) - 4;
                        entity->params = 0;
                    }
                }
            }
            if (!self->ext.fishhead.unk80) {
                self->step_s++;
            } else {
                self->ext.fishhead.unk80--;
            }
            break;
        case 2:
            self->palette = D_us_80180C22;
            playerFacing = (GetSideToPlayer() & 1) ^ 1;
            if (GetDistanceToPlayerX() < 0x48) {
                self->ext.fishhead.unk85 = 1;
            } else {
                self->ext.fishhead.unk85 = 0;
            }
            SetStep(4);
            if (self->facingLeft != playerFacing && !(self->params & 0x100)) {
                SetStep(3);
            }
            break;
        }
        break;
    case 3:
        if (!AnimateEntity(D_us_80182764, self)) {
            self->facingLeft ^= 1;
            self->animCurFrame = 2;
            SetStep(2);
        }
        break;
    case 4:
        if (!(self->flags & 0xF)) {
            if (g_Timer & 2) {
                self->palette = D_us_80180C22 + 0;
            } else {
                self->palette = D_us_80180C22 + 2;
            }
        }
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_80182708, self)) {
                SetSubStep(1);
            }
            break;
        case 1:
            PlaySfxPositional(SFX_FIRE_SHOT);

            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                if (self->ext.fishhead.unk85) {
                    CreateEntityFromEntity(0x43, self, entity);
                } else {
                    CreateEntityFromEntity(0x40, self, entity);
                }
                entity->ext.fishhead.entity = self;
                entity->facingLeft = self->facingLeft;
                entity->zPriority = self->zPriority + 1;
                if (self->facingLeft) {
                    entity->posX.i.hi += 0xE;
                } else {
                    entity->posX.i.hi -= 0xE;
                }
                entity->posY.i.hi++;
            }

            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(0x41, self, entity);
                entity->zPriority = self->zPriority + 1;
                if (self->facingLeft) {
                    entity->posX.i.hi += 0x12;
                } else {
                    entity->posX.i.hi -= 0x12;
                }
                entity->posY.i.hi -= 4;
                entity->params = 1;
            }
            self->step_s++;
            // fallthrough
        case 2:
            if (!AnimateEntity(D_us_8018274C, self)) {
                SetStep(2);
            }
            break;
        }
        break;
    case 5:
        self->ext.fishhead.unk86 = 1;
        for (i = 0; i < 3; i++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(0x42, self, entity);
                entity->params = i;
                entity->facingLeft = self->facingLeft;
                entity->zPriority = self->zPriority + 4 - i;
            }
        }
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(2, self, entity);
            entity->params = 2;
        }
        PlaySfxPositional(SFX_EXPLODE_B);
        DestroyEntity(self);
        return;
    }

    if (!self->ext.fishhead.unk86) {
        entity = self - 1;
        if (entity->flags & 0x100 || entity->entityId != E_FISHHEAD) {
            self->posY.i.hi++;
            entity = self - 2;
            if (self->posY.i.hi >= entity->posY.i.hi) {
                self->ext.fishhead.unk86 = 1;
            }
        }
    }
    ptr = D_us_801827B4;
    ptr += D_us_801827C4[self->animCurFrame] << 2;
    self->hitboxOffX = *ptr++;
    self->hitboxOffY = *ptr++;
    self->hitboxWidth = *ptr++;
    self->hitboxHeight = *ptr++;
    GetPlayerCollisionWith(self, self->hitboxWidth - 4, self->hitboxHeight, 4);
}

extern u8 D_us_80182780[];

// Fishhead fireball
void EntityFishheadFireball(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitFishheadFireball);
        if (self->facingLeft) {
            self->velocityX = FIX(4.0);
        } else {
            self->velocityX = FIX(-4.0);
        }
        // fallthrough
    case 1:
        MoveEntity();
        AnimateEntity(D_us_80182780, self);
        if (self->flags & FLAG_DEAD) {
            self->step = 0;
            self->pfnUpdate = EntityExplosion;
            self->params = 0;
        }
    }
}

extern EInit D_us_80180C40;
extern u8 D_us_8018278C[];

// Fishman particles
void func_us_801D8DF0(Entity* self) {
    Primitive* prim;
    u8* r0_ptr;
    s32 primIndex;
    s32 newVal;
    s32 i;
    bool foundPositive;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180C40);
        if (self->params) {
            // Fireball puff
            self->step = 2;
            return;
        }

        primIndex = g_api.AllocPrimitives(PRIM_TILE, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.fishhead.prim = prim;
        prim->r0 = 0x60;
        prim->g0 = 0x40;
        prim->b0 = 0xC0;
        prim->u0 = prim->v0 = 1;
        prim->priority = self->zPriority;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        self->velocityX = (Random() << 7) - 0x4000;
        // Passthrough
    case 1:
        // Small bubbles when Fishhead is idling
        MoveEntity();
        if (self->velocityY > FIX(-2)) {
            self->velocityY -= 0x400;
        }
        prim = self->ext.fishhead.prim;
        prim->x0 = self->posX.i.hi;
        prim->y0 = self->posY.i.hi;

        r0_ptr = &prim->r0;
        foundPositive = false;
        for (i = 0; i < 3; i++, r0_ptr++) {
            newVal = *r0_ptr - 4;
            if (newVal < 0) {
                newVal = 0;
            } else {
                foundPositive = true;
            }
            *r0_ptr = newVal;
        }
        if (!foundPositive) {
            DestroyEntity(self);
        }
        break;
    case 2:
        // Vertical puff of smoke after shooting fireball
        MoveEntity();
        if (self->velocityY > FIX(-2)) {
            self->velocityY -= 0x400;
        }
        if (!AnimateEntity(D_us_8018278C, self)) {
            DestroyEntity(self);
        }
        break;
    }
}

extern s16* D_us_801BCDD8[];
extern EInit D_us_80180C4C;
extern u8 D_us_8018279C[];

// Fire breath
void func_us_801D8FE0(Entity* self) {
    Entity* entity;
    Primitive* prim;
    s32 primIndex;
    s32 posX;
    s32 posY;
    s16* ptr;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180C4C);
        self->animSet = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x10);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.fishhead.prim = prim;
        prim->tpage = 0x1E;
        prim->clut = 0x2E0;
        prim->priority = self->zPriority;
        prim->drawMode = DRAW_UNK02;
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        if (self->facingLeft) {
            prim->x0 = posX + 0x34;
            prim->x1 = posX;
            prim->x2 = posX + 0x40;
            prim->x3 = posX;
        } else {
            prim->x0 = posX - 0x34;
            prim->x1 = posX;
            prim->x2 = posX - 0x40;
            prim->x3 = posX;
        }
        prim->y0 = posY - 0x30;
        prim->y1 = posY - 0x10;
        prim->y2 = posY + 0xC;
        prim->y3 = posY + 8;
        self->hitboxWidth = 0x14;
        self->hitboxHeight = 0x10;
        self->hitboxOffX = -0x20;
        self->hitboxOffY = -8;
        PlaySfxPositional(SFX_FIREBALL_SHOT_B);
        // fallthrough
    case 1:
        entity = self->ext.fishhead.entity;
        self->posY.i.hi = entity->posY.i.hi + 1;
        if (!AnimateEntity(D_us_8018279C, self)) {
            self->hitboxState = 0;
            self->step += 1;
            return;
        }
        prim = self->ext.fishhead.prim;
        ptr = D_us_801BCDD8[self->animCurFrame];
        ptr += 8;
        prim->u0 = prim->u2 = *ptr++ + 0x80;
        if (!prim->u0) {
            prim->u0 = prim->u2 = 0xFF;
        }
        prim->v0 = prim->v1 = *ptr++;
        prim->u1 = prim->u3 = *ptr++ + 0x80;
        if (!prim->u1) {
            prim->u1 = prim->u3 = 0xFF;
        }
        prim->v2 = prim->v3 = *ptr++;
        break;
    case 2:
        prim = self->ext.fishhead.prim;
        while (prim != NULL) {
            prim->type = PRIM_TILE;
            if (self->facingLeft) {
                posX = (Random() & 0x1F) + 0x10;
            } else {
                posX = -(Random() & 0x1F) - 0x10;
            }
            prim->x0 = self->posX.i.hi + posX;
            posY = self->posY.i.hi;
            prim->y0 = (posY - (Random() & 0x1F)) + 8;
            prim->u0 = 1;
            prim->v0 = 1;
            prim->r0 = 0xE0;
            prim->b0 = 0x88;
            prim->g0 = 0xA0;
            prim->p2 = (Random() & 7) + 1;
            prim->priority = self->zPriority + 1;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            prim = prim->next;
        }
        self->ext.fishhead.unk80 = 0x30;
        self->step++;
        // fallthrough
    case 3:
        prim = self->ext.fishhead.prim;

        while (prim != NULL) {
            if (!(g_Timer % prim->p2)) {
                prim->y0--;
            }
            prim->r0 -= 2;
            prim->g0 -= 2;
            prim->b0 -= 2;
            prim = prim->next;
        }

        if (!--self->ext.fishhead.unk80) {
            DestroyEntity(self);
        }
        break;
    }
}

// Death parts
INCLUDE_ASM("st/no4/nonmatchings/e_fishhead", func_us_801D93E0);
