// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no4.h"

static u8 anim_idle[] = {0x30, 0x02, 0x0F, 0x01, 0x00, 0x00, 0x00, 0x00};
static u8 anim_prep_attack[] = {
    0x05, 0x02, 0x04, 0x01, 0x03, 0x02, 0x03, 0x01, 0x03, 0x02, 0x02, 0x01,
    0x02, 0x02, 0x02, 0x01, 0x02, 0x02, 0x02, 0x03, 0x01, 0x04, 0x02, 0x01,
    0x02, 0x03, 0x02, 0x04, 0x02, 0x03, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02,
    0x01, 0x03, 0x01, 0x02, 0x01, 0x03, 0x02, 0x02, 0x03, 0x03, 0x11, 0x02,
    0x04, 0x05, 0x05, 0x0B, 0x02, 0x0C, 0x02, 0x0D, 0x02, 0x0E, 0x02, 0x0F,
    0x02, 0x10, 0x01, 0x0C, 0xFF, 0x00, 0x00, 0x00};
static u8 anim_post_attack[] = {
    0x08, 0x11, 0x05, 0x12, 0x30, 0x0C, 0x05, 0x0B, 0x05, 0x05, 0x05, 0x03,
    0x10, 0x02, 0x04, 0x01, 0x08, 0x02, 0x04, 0x04, 0x20, 0x02, 0xFF, 0x00};
static u8 anim_rotate[] = {
    0x32, 0x02, 0x02, 0x01, 0x02, 0x04, 0x02, 0x03, 0x06, 0x05,
    0x03, 0x03, 0x04, 0x02, 0x05, 0x06, 0x05, 0x07, 0x04, 0x0A,
    0x06, 0x09, 0x20, 0x0A, 0xFF, 0x00, 0x00, 0x00};

static u8 anim_fireball[] = {
    0x02, 0x17, 0x02, 0x18, 0x02, 0x19, 0x02, 0x1A, 0x00, 0x00, 0x00, 0x00};

static u8 anim_fireball_puff[] = {
    0x06, 0x1B, 0x06, 0x1C, 0x08, 0x1D, 0x08, 0x1E,
    0x06, 0x1F, 0x07, 0x20, 0x08, 0x21, 0xFF, 0x00};

static u8 anim_fire_breath[] = {
    0x03, 0x01, 0x03, 0x02, 0x03, 0x03, 0x03, 0x04, 0x03, 0x05, 0x03, 0x06,
    0x03, 0x07, 0x03, 0x08, 0x03, 0x09, 0x03, 0x0A, 0x03, 0x0B, 0xFF, 0x00};

// { hitboxOffX, hitboxOffY, hitboxWidth, hitboxHeight }
static s8 hitbox_data[][4] = {
    {0, 0, 0, 0},
    {-8, 1, 15, 12},
    {0, 1, 11, 12},
    {10, 1, 15, 12},
};
static u8 hitbox_data_indices[] = {
    0, 1, 1, 1, 1, 1, 2, 2, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 0};
// semi-random attack timers so the Fishheads fire at different intervals
static s16 attack_timers[] = {16, 32, 48, 64, 80, 64, 48, 32};

static s16 death_parts_posY_offset[] = {10, 8, 8};

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

void EntityFishhead(Entity* self) {
    Entity* entity;
    s32 playerFacing;
    s32 i;
    s8* ptr;

    if (self->flags & FLAG_DEAD && self->step != 5) {
        SetStep(5);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitFishhead);
        self->animCurFrame = 1;
        self->palette += 5;

        // First head spawned is the bottom head
        if (!(self->params & 1)) {
            self->ext.fishhead.isBottomHead = 1;
        }
        self->ext.fishhead.attackTimerIndex = Random() & 7;
        // fallthrough
    case 1:
    case 2:
        switch (self->step_s) {
        case 0:
            self->ext.fishhead.attackTimer =
                attack_timers[self->ext.fishhead.attackTimerIndex];
            self->ext.fishhead.attackTimerIndex++;
            self->ext.fishhead.attackTimerIndex &= 7;
            self->step_s++;
            // fallthrough
        case 1:
            AnimateEntity(anim_idle, self);
            if (!(self->flags & 0xF)) {
                self->ext.fishhead.palette += 0x10;
                if (self->ext.fishhead.palette > 0xA80) {
                    self->ext.fishhead.palette = -self->ext.fishhead.palette;
                }
                playerFacing = (abs(self->ext.fishhead.palette) >> 8);
                self->palette = g_EInitFishhead[3] + 5 + playerFacing;
            }
            if (!(self->ext.fishhead.attackTimer & 0xF)) {
                // Spawn 5 bubbles that float above the Fishhead
                for (i = 0; i < 5; i++) {
                    entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                    if (entity != NULL) {
                        CreateEntityFromEntity(
                            E_FISHHEAD_PARTICLES, self, entity);
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
            if (!self->ext.fishhead.attackTimer) {
                self->step_s++;
            } else {
                self->ext.fishhead.attackTimer--;
            }
            break;
        case 2:
            self->palette = g_EInitFishhead[3];
            playerFacing = (GetSideToPlayer() & 1) ^ 1;
            if (GetDistanceToPlayerX() < 0x48) {
                self->ext.fishhead.playerIsClose = 1;
            } else {
                self->ext.fishhead.playerIsClose = 0;
            }
            SetStep(4);
            if (self->facingLeft != playerFacing && !(self->params & 0x100)) {
                SetStep(3);
            }
            break;
        }
        break;
    case 3:
        if (!AnimateEntity(anim_rotate, self)) {
            self->facingLeft ^= 1;
            self->animCurFrame = 2;
            SetStep(2);
        }
        break;
    case 4:
        if (!(self->flags & 0xF)) {
            if (g_Timer & 2) {
                self->palette = g_EInitFishhead[3] + 0;
            } else {
                self->palette = g_EInitFishhead[3] + 2;
            }
        }
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(anim_prep_attack, self)) {
                SetSubStep(1);
            }
            break;
        case 1:
            PlaySfxPositional(SFX_FIRE_SHOT);

            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                if (self->ext.fishhead.playerIsClose) {
                    CreateEntityFromEntity(
                        E_FISHHEAD_FIRE_BREATH, self, entity);
                } else {
                    CreateEntityFromEntity(E_FISHHEAD_FIREBALL, self, entity);
                }
                entity->ext.fishhead.fishheadEntity = self;
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
                // Spawn the puff of smoke after the fireball goes off
                CreateEntityFromEntity(E_FISHHEAD_PARTICLES, self, entity);
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
            if (!AnimateEntity(anim_post_attack, self)) {
                SetStep(2);
            }
            break;
        }
        break;
    case 5:
        self->ext.fishhead.isBottomHead = 1;
        for (i = 0; i < 3; i++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_FISHHEAD_DEATH_PARTS, self, entity);
                entity->params = i;
                entity->facingLeft = self->facingLeft;
                entity->zPriority = self->zPriority + 4 - i;
            }
        }
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 2;
        }
        PlaySfxPositional(SFX_EXPLODE_B);
        DestroyEntity(self);
        return;
    }

    if (!self->ext.fishhead.isBottomHead) {
        entity = self - 1;
        if (entity->flags & FLAG_DEAD || entity->entityId != E_FISHHEAD) {
            // If the bottom head of a stack is killed, the top head falls to
            // the ground and becomes a bottom head
            self->posY.i.hi++;
            entity = self - 2;
            if (self->posY.i.hi >= entity->posY.i.hi) {
                self->ext.fishhead.isBottomHead = 1;
            }
        }
    }
    ptr = hitbox_data;
    ptr += hitbox_data_indices[self->animCurFrame] << 2;
    self->hitboxOffX = *ptr++;
    self->hitboxOffY = *ptr++;
    self->hitboxWidth = *ptr++;
    self->hitboxHeight = *ptr++;
    GetPlayerCollisionWith(self, self->hitboxWidth - 4, self->hitboxHeight, 4);
}

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
        AnimateEntity(anim_fireball, self);
        if (self->flags & FLAG_DEAD) {
            self->step = 0;
            self->pfnUpdate = EntityExplosion;
            self->params = 0;
        }
    }
}

// Params 0 = bubbles
// Params 1 = fireball smoke
void EntityFishheadParticles(Entity* self) {
    Primitive* prim;
    u8* r0_ptr;
    s32 primIndex;
    s32 newVal;
    s32 i;
    bool foundPositive;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitFishheadPieces);
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
        self->velocityX = (Random() << 7) - FIX(0.25);
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
        if (!AnimateEntity(anim_fireball_puff, self)) {
            DestroyEntity(self);
        }
        break;
    }
}

extern s16* D_us_801BCDD8[];

// Fire breath
void EntityFishheadFireBreath(Entity* self) {
    Entity* entity;
    Primitive* prim;
    s32 primIndex;
    s32 posX;
    s32 posY;
    s16* ptr;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitFishheadFireBreath);
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
        entity = self->ext.fishhead.fishheadEntity;
        self->posY.i.hi = entity->posY.i.hi + 1;
        if (!AnimateEntity(anim_fire_breath, self)) {
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
        self->ext.fishhead.attackTimer = 0x30;
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

        if (!--self->ext.fishhead.attackTimer) {
            DestroyEntity(self);
        }
        break;
    }
}

// Death parts
void EntityFishheadDeathParts(Entity* self) {
    Collider collider;
    s32 posX;
    s32 posY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitFishheadPieces);
        self->hitboxState = 0;
        self->animCurFrame = self->params + 0x14;
        self->ext.fishhead.attackTimer = self->params + 0xC;
        break;
    case 1:
        if (!--self->ext.fishhead.attackTimer) {
            self->step++;
        }
        break;
    case 2:
        MoveEntity();
        self->velocityY += FIX(0.15625);
        posX = self->posX.i.hi;
        posY = self->posY.i.hi + death_parts_posY_offset[self->params];
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->posY.i.hi += collider.unk18;
            self->ext.fishhead.attackTimer = 0xE;
            self->step++;
        }
        break;
    case 3:
        if (!--self->ext.fishhead.attackTimer) {
            self->step = 0;
            self->pfnUpdate = EntityExplosion;
            self->params = 2;
        }
        break;
    }
}
