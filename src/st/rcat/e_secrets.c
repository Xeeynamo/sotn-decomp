// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rcat.h"

// prim { u0/2, v2/3 }
static u8 D_us_80181518[][2] = {{0, 96}, {32, 96}, {64, 96}, {0, 16}};
static Point32 breakable_wall_particle_velocity[] = {
    {.x = FIX(0.125), .y = FIX(0.0)},
    {.x = FIX(0.625), .y = FIX(-1.125)},
    {.x = FIX(0.375), .y = FIX(-2.0)},
    {.x = FIX(0.875), .y = FIX(-0.5)},
};
static Point32 D_us_80181540[] = {
    {.x = FIX(0.125), .y = FIX(-0.125)}, {.x = FIX(0.25), .y = FIX(-0.5)},
    {.x = FIX(0.375), .y = FIX(-1.0)},   {.x = FIX(0.5), .y = FIX(-0.125)},
    {.x = FIX(-0.125), .y = FIX(0.125)}, {.x = FIX(-0.25), .y = FIX(-1.0)},
    {.x = FIX(0.75), .y = FIX(-1.5)},    {.x = FIX(0.0), .y = FIX(0.0)},
};
static u16 tile_positions_right_wall[] = {
    0x031D, 0x031C, 0x02FD, 0x02FC, 0x02DD, 0x02DC};
static u16 right_secret_tiles[][6] = {
    {0x0023, 0x0024, 0x0000, 0x0000, 0x0322, 0x038F},
    {0x0010, 0x0011, 0x001D, 0x001D, 0x0021, 0x0022},
    {0x0010, 0x0011, 0x001D, 0x001D, 0x0021, 0x0022},
    {0x0010, 0x0011, 0x001D, 0x001D, 0x0021, 0x0022},
    {0x0010, 0x0011, 0x001D, 0x001D, 0x0021, 0x0022},
    {0x0023, 0x0024, 0x0000, 0x0000, 0x0021, 0x0022},
    {0x0010, 0x0011, 0x0000, 0x0000, 0x0322, 0x038F},
};

static u16 tile_positions_circlet_wall[] = {0x008E, 0x007E, 0x006E, 0x0000};
static u16 tile_positions_spike_breaker[] = {0x01AE, 0x017E, 0x014E, 0x0000};
static u16 secret_wall_tiles[][3] = {
    {0x0026, 0x0027, 0x0028}, {0x0012, 0x0013, 0x0014},
    {0x0012, 0x0013, 0x0014}, {0x0012, 0x0013, 0x0014},
    {0x0012, 0x0013, 0x0014}, {0x0026, 0x0027, 0x0014},
    {0x0012, 0x0027, 0x0028}};

#ifdef VERSION_PSP
extern s32 E_ID(BREAKABLE_WALL_SEGMENT);
extern s32 E_ID(BREAKABLE_WALL_PARTICLES);
extern s32 E_ID(BREAKABLE_WALL_DEBRIS);
#endif

extern EInit g_EInitEnvironment;
extern EInit g_EInitParticle;
extern EInit g_EInitBreakableWallSegment;

// Larger bricks that drop after breaking wall
void EntityBreakableWallDebris(Entity* self) {
    Collider collider;

    Primitive* prim;
    Primitive* prevPrim;
    Entity* newEntity;
    s32 primIndex;
    s16 posX;
    s16 posY;
    Primitive* nextPrim;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 3);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.segmentedBreakableWall.prim = prim;
            UnkPolyFunc2(prim);
            prim->tpage = 0xB;
            prim->clut = PAL_BREAKABLE_WALL_DEBRIS_MAIN;
            prim->u0 = prim->u2 = D_us_80181518[self->params][0];
            prim->u1 = prim->u3 = prim->u0 + 0xF;
            prim->v2 = prim->v3 = D_us_80181518[self->params][1];
            prim->v0 = prim->v1 = prim->v2 + 0xF;
            prim->next->x1 = self->posX.i.hi;
            prim->next->y0 = self->posY.i.hi;
            LOH(prim->next->r2) = 0x10;
            LOH(prim->next->b2) = 0x10;
            prim->next->b3 = 0x80;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
            prim = prim->next;

            prim->clut = PAL_BREAKABLE_WALL_DEBRIS_HIGHLIGHT;
            prim->drawMode = DRAW_TPAGE | DRAW_TRANSP;
        } else {
            DestroyEntity(self);
            return;
        }

        break;
    case 1:
        MoveEntity();
        self->velocityY += FIX(0.125);
        prim = self->ext.segmentedBreakableWall.prim;
        posX = prim->next->x1 = self->posX.i.hi;
        posY = prim->next->y0 = self->posY.i.hi;
        UnkPrimHelper(prim);
        prevPrim = prim;
        prim = prim->next;
        prim = prim->next;

        nextPrim = prim->next;
        *prim = *prevPrim;
        prim->next = nextPrim;

        prim->clut = PAL_BREAKABLE_WALL_DEBRIS_HIGHLIGHT;
        prim->y0 -= 2;
        prim->y1 -= 2;
        prim->y2 -= 2;
        prim->y3 -= 2;
        prim->priority -= 1;
        prim->drawMode = DRAW_TPAGE | DRAW_TRANSP;

        // After hitting the ground, the bricks do a slight bounce
        posY += 2;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects) {
            self->velocityY = FIX(-1.75);
            self->step++;
        }
        break;
    case 2:
        MoveEntity();
        self->velocityY += FIX(0.125);
        prim = self->ext.segmentedBreakableWall.prim;
        posX = prim->next->x1 = self->posX.i.hi;
        posY = prim->next->y0 = self->posY.i.hi;
        UnkPrimHelper(prim);
        if (self->params > 1) {
            LOH(prim->next->tpage) += 0x10;
        } else {
            LOH(prim->next->tpage) -= 0x10;
        }
        posY += 2;

        prevPrim = prim;
        prim = prim->next;
        prim = prim->next;

        nextPrim = prim->next;
        *prim = *prevPrim;
        prim->next = nextPrim;

        prim->clut = PAL_BREAKABLE_WALL_DEBRIS_HIGHLIGHT;
        prim->y0 -= 2;
        prim->y1 -= 2;
        prim->y2 -= 2;
        prim->y3 -= 2;
        prim->priority -= 1;
        prim->drawMode = DRAW_TPAGE | DRAW_TRANSP;

        // After hitting the ground once more crumble into dust
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects) {
            newEntity =
                AllocEntity(&g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, newEntity);
                newEntity->params = 0x10;
            }
            DestroyEntity(self);
        }
        break;
    }
}

void EntityBreakableWallParticles(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 i;
    s16 posX;
    s16 posY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                       FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
        self->velocityX = breakable_wall_particle_velocity[self->params].x;
        self->velocityY = breakable_wall_particle_velocity[self->params].y;
        primIndex = g_api.func_800EDB58(PRIM_TILE_ALT, 8);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.segmentedBreakableWall.prim = prim;

            for (i = 0; prim != NULL; i++, prim = prim->next) {
                prim->u0 = 1;
                prim->v0 = 2;
                prim->x0 = self->posX.i.hi;
                prim->y0 = self->posY.i.hi;
                prim->r0 = 0x40;
                prim->g0 = 0x90;
                prim->b0 = 0x70;
                // Seems likely these are velocity values?
                LOW(prim->r2) = D_us_80181540[i].x;
                LOW(prim->x2) = D_us_80181540[i].y;
                LOW(prim->r1) = 0;
                LOW(prim->x1) = 0;
                prim->priority = self->zPriority;
                prim->drawMode = DRAW_DEFAULT;
            }
        } else {
            DestroyEntity(self);
            return;
        }

        break;
    case 1:
        MoveEntity();
        self->velocityY += FIX(0.0625);
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        prim = self->ext.segmentedBreakableWall.prim;
        while (prim != NULL) {
            LOW(prim->r1) += LOW(prim->r2);
            LOW(prim->x1) += LOW(prim->x2);
            prim->x0 = posX + LOH(prim->b1);
            prim->y0 = posY + prim->y1;
            LOW(prim->x2) += FIX(0.0625);
            prim = prim->next;
        }
        break;
    }
}

void EntitySecretWallRight(Entity* self) {
    Entity* entity;
    s32 i;
    s32 tilePos;
    u8 animCurFrame;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitEnvironment);
        self->animCurFrame = 4;
        self->zPriority = 0xA8;
        if (g_CastleFlags[RCAT_RIGHT_SECRET_WALL_OPEN]) {
            self->animCurFrame = 0;
            self->step = 4;
            break;
        }

        entity = self + 1;
        CreateEntityFromEntity(E_ID(BREAKABLE_WALL_SEGMENT), self, entity);
        entity->posX.i.hi -= 0x10;
        entity->posY.i.hi -= 0x20;
        entity->params = 1;

        entity = self + 2;
        CreateEntityFromEntity(E_ID(BREAKABLE_WALL_SEGMENT), self, entity);
        entity->posX.i.hi -= 0x10;
        entity->posY.i.hi -= 0x40;
        entity->params = 2;
        // fallthrough
    case 1:
        if (self->ext.segmentedBreakableWall.damageTaken > 2) {
            g_api.PlaySfx(SFX_WALL_DEBRIS_B);
            self->ext.segmentedBreakableWall.damageTaken = 0;

            for (i = 0; i < 4; i++) {
                entity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(BREAKABLE_WALL_PARTICLES), self, entity);
                    entity->posX.i.hi -= 0x20;
                    entity->posY.i.hi -= 0x20;
                    entity->params = i;
                }
            }

            if (self->animCurFrame < 7) {
                self->animCurFrame++;
            }
        }

        if (self->ext.segmentedBreakableWall.pieceBroken) {
            self->step_s = 0;
            self->step = self->ext.segmentedBreakableWall.pieceBroken + 1;
            // If both pieces are broken
            if (self->ext.segmentedBreakableWall.pieceBroken == 3) {
                self->step = 2;
            }
        }
        break;
    case 2:
        // Top part broken (or both)
        self->animCurFrame = 8;
        if (self->ext.segmentedBreakableWall.pieceBroken & 2) {
            g_api.PlaySfx(SFX_WALL_DEBRIS_B);
            self->step = 4;
        }
        break;
    case 3:
        // Bottom part broken
        self->animCurFrame = 9;
        if (self->ext.segmentedBreakableWall.pieceBroken & 1) {
            g_api.PlaySfx(SFX_WALL_DEBRIS_B);
            self->step = 4;
        }
        break;
    case 4:
        self->animCurFrame = 0;
        g_CastleFlags[RCAT_RIGHT_SECRET_WALL_OPEN] = true;
        break;
    }

    animCurFrame = self->animCurFrame;
    if (animCurFrame) {
        animCurFrame -= 3;
    }

    for (i = 0; i < 6; i++) {
        tilePos = tile_positions_right_wall[i];
        g_Tilemap.fg[tilePos] = right_secret_tiles[animCurFrame][i];
    }
}

void EntityBreakableWallSegment(Entity* self) {
    Entity* entity;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitBreakableWallSegment);
        self->hitboxState = 2;
        self->hitPoints = 8;
        self->hitboxWidth = 0x10;
        self->hitboxHeight = 0xC;
        self->ext.segmentedBreakableWall.hitPoints = self->hitPoints;
        self->hitboxOffY = 0xC;
        break;
    case 1:
        if (self->hitPoints ^ self->ext.segmentedBreakableWall.hitPoints) {
            (self - self->params)->ext.segmentedBreakableWall.damageTaken +=
                (self->ext.segmentedBreakableWall.hitPoints - self->hitPoints);
            self->ext.segmentedBreakableWall.hitPoints = self->hitPoints;
        }

        if (self->flags & FLAG_DEAD) {
            (self - self->params)->ext.segmentedBreakableWall.pieceBroken |=
                self->params;
            self->step++;
        }
        break;
    case 2:
        switch (self->step_s) {
        case 0:
            entity =
                AllocEntity(&g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->posY.i.hi += 8;
                entity->params = EXPLOSION_UNK_19;
            }

            for (i = 0; i < 3; i++) {
                entity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, entity);
                    entity->posX.i.hi -= (i * 0x10) - 0x10;
                    entity->params = 0x10;
                }
            }

            for (i = 0; i < 4; i++) {
                entity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(BREAKABLE_WALL_DEBRIS), self, entity);
                    entity->posX.i.hi -= (i * 8) - 0x10 + (Random() & 3);
                    entity->posY.i.hi += (Random() & 7);
                    if (self->params == 2) {
                        entity->posY.i.hi -= 0x18;
                    }
                    entity->params = i;
                }
            }
            self->step_s++;
            break;
        }
        break;
    }
}

// params = 0: secret wall behind Firebrand containing Buffalo Star
// params != 0: breakable wall behind Elixir containing Library Card
void EntitySecretWall(Entity* self) {
    Entity* entity;
    s32 i;
    s32 tilePos;
    s16 posX;
    s16 posY;
    s16 scrollX;
    s16 scrollY;
    u32 mod;
    u8 animCurFrame;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitEnvironment);
        self->animCurFrame = 0xA;
        self->zPriority = 0xA8;
        if (!self->params) {
            if (g_CastleFlags[RCAT_SECRET_WALL_BROKEN]) {
                self->animCurFrame = 0;
                self->step = 4;
                break;
            }
        } else if (g_CastleFlags[RCAT_LEFT_SECRET_WALL_OPEN]) {
            self->animCurFrame = 0;
            self->step = 4;
            break;
        }

        entity = self + 1;
        CreateEntityFromEntity(E_ID(BREAKABLE_WALL_SEGMENT), self, entity);
        entity->posX.i.hi -= 4;
        entity->posY.i.hi -= 0x10;
        entity->params = 1;

        entity = self + 2;
        CreateEntityFromEntity(E_ID(BREAKABLE_WALL_SEGMENT), self, entity);
        entity->posX.i.hi -= 4;
        entity->posY.i.hi -= 0x30;

        entity->params = 2;
        // fallthrough
    case 1:
        if (self->ext.segmentedBreakableWall.damageTaken > 2) {
            g_api.PlaySfx(SFX_WALL_DEBRIS_B);
            self->ext.segmentedBreakableWall.damageTaken = 0;

            for (i = 0; i < 4; i++) {
                entity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(BREAKABLE_WALL_PARTICLES), self, entity);
                    entity->posX.i.hi -= 8;
                    entity->posY.i.hi -= 0x20;
                    entity->params = i;
                }
            }

            if (self->animCurFrame < 0xD) {
                self->animCurFrame++;
            }
        }

        if (self->ext.segmentedBreakableWall.pieceBroken) {
            self->step_s = 0;
            self->step = self->ext.segmentedBreakableWall.pieceBroken + 1;
            // If both pieces are broken
            if (self->ext.segmentedBreakableWall.pieceBroken == 3) {
                self->step = 2;
            }
        }
        break;
    case 2:
        // Top part broken (or both)
        self->animCurFrame = 0xE;
        if (self->ext.segmentedBreakableWall.pieceBroken & 2) {
            self->step = 4;
        }
        break;
    case 3:
        // Bottom part broken
        self->animCurFrame = 0xF;
        if (self->ext.segmentedBreakableWall.pieceBroken & 1) {
            self->step = 4;
        }
        break;
    case 4:
        self->animCurFrame = 0;
        if (!self->params) {
            g_CastleFlags[RCAT_SECRET_WALL_BROKEN] = true;
        } else {
            g_CastleFlags[RCAT_LEFT_SECRET_WALL_OPEN] = true;
        }

        for (i = 0; i < 3; i++) {
            tilePos = tile_positions_circlet_wall[i];
            if (self->params) {
                tilePos = tile_positions_spike_breaker[i];
            }

            g_Tilemap.fg[tilePos] = secret_wall_tiles[0][i];
        }

        self->step = 0;
        self->step_s = 0;
        self->posX.i.hi -= 8;
        self->poseTimer = self->pose = 0;
        self->pfnUpdate = EntityHeartDrop;
        if (self->params) {
            // Library Card
            self->params = 8;
        } else {
            // Buffalo Star
            self->params = 1;
        }
        return;

    case 16:
        // NOTE: This has some unique debug functionality not present in other
        // entities that use pad2_anim_debug
        for (i = 0; i < 4; i++) {
            posX = self->posX.i.hi + 8;
            posY = self->posY.i.hi + (i * 0x10) + 2;
            scrollX = posX + g_Tilemap.scrollX.i.hi;
            scrollY = posY + g_Tilemap.scrollY.i.hi;
            tilePos = (scrollX >> 4) + (scrollY >> 4) * g_Tilemap.hSize * 0x10;
            mod = g_Tilemap.fg[tilePos];
            FntPrint("index %x mod:%x\n", tilePos, mod);
        }

#include "../pad2_anim_debug.h"
    }

    animCurFrame = self->animCurFrame;
    if (animCurFrame) {
        animCurFrame -= 9;
    }

    for (i = 0; i < 3; i++) {
        tilePos = tile_positions_circlet_wall[i];
        if (self->params) {
            tilePos = tile_positions_spike_breaker[i];
        }
        g_Tilemap.fg[tilePos] = secret_wall_tiles[animCurFrame][i];
    }
}
