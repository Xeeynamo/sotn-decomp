/*
 * File: en_falling_stairs.c
 * Overlay: CHI
 * Description: ENTITY - Falling stairs and falling step
 */

#include "chi.h"

// func_8019D0D8
// https://decomp.me/scratch/0asn9
// PSP:func_psp_0924D7F8:No match
// PSP:https://decomp.me/scratch/vOZf2
void UpdateDustParticles(Primitive* prim)
{
    s32 s1;
    s32 s0;

    if (!prim->p2) {
        prim->u0 = prim->v0 = 1;
        prim->drawMode = 2;
        LOW(prim->x2) = -(((Random() & 0x7F)) << 9);
        LOW(prim->x3) = 0;
        prim->p2 = 1U;
    }

    s1 = (prim->x0 << 0x10) + prim->x1;
    s0 = (prim->y0 << 0x10) + prim->y1;
    s1 += LOW(prim->x2);
    s0 += LOW(prim->x3);
    prim->x0 = s1 >> 0x10;
    prim->y0 = s0 >> 0x10;
    
    LOW(prim->x3) += 0x2800;
    if (prim->y0 > 0x140) {
        prim->p3 = 0;
        prim->p2 = 0;
        prim->drawMode = 8;
    }
}

void UpdateDustParticles(Primitive*);

// D_80180974
static u16 FallingStairsNotFallenTileIndices[] = {
    0x022B, 0x022C, 0x0239, 0x023A, 0x023B, 0x023C, 0x0247, 0x0248,
    0x0249, 0x024A, 0x0255, 0x0256, 0x0257, 0x0258, 0x0259, 0x0265,
    0x0266, 0x0000,
};

// D_80180998
static u16 FallingStairsFallenTileIndices[] = {
    0x028B, 0x028C, 0x0299, 0x029A, 0x029B, 0x029C, 0x02A7, 0x02A8,
    0x02A9, 0x02AA, 0x02B5, 0x02B6, 0x02B7, 0x02B8, 0x02B9, 0x02C5,
    0x02C6, 0x0000,
};

// D_801809BC
static u16 FallingStairsNotFallenTileValues[] = {
    0x01F9, 0x0224, 0x01F9, 0x0207, 0x0243, 0x0225, 0x01F9, 0x01E7,
    0x0244, 0x0226, 0x0229, 0x01E7, 0x0243, 0x01B5, 0x0226, 0x024B,
    0x0226, 0x0000,
};

// D_801809E0
static u16 FallingStairsFallenTileValues[] = {
    0x01C4, 0x0222,
};

// E_FALLING_STAIRS
// func_8019D1A8
// https://decomp.me/scratch/ydih8
// PSP:func_psp_0924D948:Match
// PSP:https://decomp.me/scratch/42GFW
void EntityFallingStairs(Entity* self)
{
    const s32 NotFallenPosX = 207;
    const s32 NotFallenPosY = 575;
    const s32 TriggerBoxX = 0x50;
    const s32 TriggerBoxY = 0x200;
    const u32 TriggerBoxW = 0x70;
    const u32 TriggerBoxH = 0x40;
    const s32 RightSideHitHeight = 0x29F;

    typedef enum Step {
        INIT = 0,
        WAIT_FOR_TRIGGER = 1,
        BREAK_AWAY = 2,
        FALLING = 3,
        LAND = 4,
    };

    typedef enum Falling_SubStep {
        ROTATE_CLOCKWISE = 0,
        ROTATE_COUNTER_CLOCKWISE = 1,
    };

    Primitive* prim;
    s32 i;
    s16* pDstTileIdx;
    s16* pSrcTile;
    s32 yPos;
    s32 xPos;
    Entity* entity;
    Entity* player;
    s32 scrolledY;
    s32 scrolledX;
    s32 selfPosX;
    s32 selfPosY;
    s32 primIdx;

    scrolledX = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
    scrolledY = g_Tilemap.scrollY.i.hi + self->posY.i.hi;

    switch (self->step) {
        case INIT:
            if (g_CastleFlags[CASTLE_FLAG_CHI_FALLING_STAIRS]) {
                DestroyEntity(self);
                return;
            }

            // Change position to be prepared for stairs falling
            self->posX.i.hi = NotFallenPosX - g_Tilemap.scrollX.i.hi;
            self->posY.i.hi = NotFallenPosY - g_Tilemap.scrollY.i.hi;
            InitializeEntity(&g_InitTilemap);

            self->drawFlags |= FLAG_DRAW_ROTZ;
            self->animCurFrame = 0;

            // Change tileset to show UNfallen stairs
            pDstTileIdx = &FallingStairsNotFallenTileIndices;
            pSrcTile = &FallingStairsNotFallenTileValues;
            for (i = 0; i < 0x11; i++, pDstTileIdx++, pSrcTile++) {
                g_Tilemap.fg[*pDstTileIdx] = *pSrcTile;
            }

            // Change tileset to hide fallen stairs
            pDstTileIdx = &FallingStairsFallenTileIndices;
            pSrcTile = &FallingStairsFallenTileValues;
            for (i = 0; i < 0xF; i++, pDstTileIdx++) {
                g_Tilemap.fg[*pDstTileIdx] = 0; // Most tiles are blank
            }
            for (i = 0; i < 2; i++, pDstTileIdx++, pSrcTile++) {
                g_Tilemap.fg[*pDstTileIdx] = *pSrcTile; // These two tiles have graphics
            }

            // Fallthrough
        case WAIT_FOR_TRIGGER:
            player = &PLAYER;
            xPos = player->posX.i.hi;
            yPos = player->posY.i.hi;
            scrolledX = xPos + g_Tilemap.scrollX.i.hi;
            scrolledY = yPos + g_Tilemap.scrollY.i.hi;
            scrolledX -= TriggerBoxX;
            scrolledY -= TriggerBoxY;
            if ((scrolledX < TriggerBoxW) &&
                (scrolledY < TriggerBoxH) &&
                (g_Player.pl_vram_flag & 1)) {  // Touching the ground
                self->step++;
            }
            break;

        case BREAK_AWAY:
            self->animCurFrame = 0x23;

            // Clear out all tiles in unfallen state
            pDstTileIdx = &FallingStairsNotFallenTileIndices;
            for (i = 0; i < 0x11; i++, pDstTileIdx++) {
                g_Tilemap.fg[*pDstTileIdx] = 0;
            }

            g_api.func_80102CD8(1); // Not sure what this does. Removing it doesn't make an obvious difference
            g_api.PlaySfx(SFX_WALL_DEBRIS_B);
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);

            // Spawn a long dust cloud
            if (entity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->params = 0x13;
                entity->params |= 0xC000;
            }
            primIdx = g_api.func_800EDB58(PRIM_TILE_ALT, 96);
            if (primIdx != -1) {
                self->flags |= FLAG_HAS_PRIMS;
                self->primIndex = primIdx;
                prim = &g_PrimBuf[primIdx];
                self->ext.prim = prim;

                prim->x0 = self->posX.i.hi;
                prim->y0 = self->posY.i.hi - 0x18;
                prim->drawMode = DRAW_HIDE | DRAW_UNK02;
                prim = prim->next;
                while (prim != NULL) {
                    prim->p3 = 0;
                    prim->r0 = 0x60;
                    prim->g0 = 0x60;
                    prim->b0 = 0x20;
                    prim->u0 = prim->v0 = 1;
                    prim->priority = 0xC0;
                    prim->drawMode = DRAW_HIDE;
                    self->ext.fallingStairs.prim = prim;
                    prim = prim->next;
                }

                // Show some dust particles
                prim = self->ext.prim;
                xPos = prim->x0;
                yPos = prim->y0;
                for (i = 0; i < 8; i++) {
                    prim = self->ext.prim;
                    prim = prim->next;
                    prim = FindFirstUnkPrim(prim);
                    if (prim != NULL) {
                        prim->p3 = 1;
                        prim->p2 = 0;
                        prim->x0 = xPos + ((Random() & 4)) - 2;
                        prim->y0 = yPos + (Random() & 0x1F);
                    }
                }
            } else {
                self->ext.prim = NULL;
            }
            self->step++;
            break;

        case FALLING:
            switch (self->step_s) {
                case ROTATE_CLOCKWISE:
                    MoveEntity();
                    self->rotZ += 0x12;
                    self->velocityY += 0x4000;
                    scrolledY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
                    if (self->ext.prim != NULL) {
                        prim = self->ext.prim;
                        xPos = prim->x0;
                        yPos = prim->y0;

                        // Show some additional dust particles
                        for (i = 0; i < 3; i++) {
                            prim = self->ext.prim;
                            prim = prim->next;
                            prim = FindFirstUnkPrim(prim);
                            if (prim != NULL) {
                                prim->p3 = 1;
                                prim->p2 = 0;
                                prim->x0 = xPos + (Random() & 7) - 3;
                                prim->y0 = yPos + (Random() & 0x1F);
                            }
                        }
                    }

                    // Check for if right side hit the ledge below
                    if (scrolledY > RightSideHitHeight) {
                        self->posY.i.hi = RightSideHitHeight - g_Tilemap.scrollY.i.hi;
                        g_api.PlaySfx(SFX_EXPLODE_B);
                        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);

                        // Spawn a short dust cloud
                        if (entity != NULL) {
                            CreateEntityFromEntity(E_EXPLOSION, self, entity);
                            entity->params = 0x11;
                            entity->params |= 0xC000;
                        }

                        // Show some dust particles
                        if (self->ext.prim != NULL) {
                            xPos = self->posX.i.hi;
                            yPos = self->posY.i.hi;
                            for (i = 0; i < 8; i++) {
                                prim = self->ext.prim;
                                prim = prim->next;
                                prim = FindFirstUnkPrim(prim);
                                if (prim != NULL) {
                                    prim->p3 = 1;
                                    prim->p2 = 0;
                                    prim->x0 = (xPos + (Random() & 7)) - 3;
                                    prim->y0 = yPos + (Random() & 3);
                                }
                            }
                        }
                        self->step_s++;
                    }
                    break;

                case ROTATE_COUNTER_CLOCKWISE:
                    self->rotZ -= self->ext.fallingStairs.rotateAccel;
                    self->ext.fallingStairs.rotateAccel += 1;

                    xPos = 0x74 - g_Tilemap.scrollX.i.hi;
                    yPos = 0x2C0 - g_Tilemap.scrollY.i.hi;
                    if (self->rotZ < 0) {
                        self->rotZ = 0; // Don't over-rotate
                        g_api.PlaySfx(SFX_EXPLODE_B);
                        g_api.func_80102CD8(1);
                        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);

                        // Spawn a dust cloud
                        if (entity != NULL) {
                            CreateEntityFromCurrentEntity(E_INTENSE_EXPLOSION, entity);
                            entity->params = 0x10;
                            entity->params |= 0xC000;
                            entity->posX.i.hi = xPos;
                            entity->posY.i.hi = yPos;
                        }

                        // Show some dust particles
                        if (self->ext.prim != NULL) {
                            for (i = 0; i < 8; i++) {
                                prim = self->ext.prim;
                                prim = prim->next;
                                prim = FindFirstUnkPrim(prim);
                                if (prim != NULL) {
                                    prim->p3 = 1;
                                    prim->p2 = 0;
                                    prim->x0 = (xPos + (Random() & 7)) - 3;
                                    prim->y0 = yPos + (Random() & 3);
                                }
                            }
                        }
                        self->step++;
                    }
                    break;
            }

            // Ensure the player stays above the stairs
            selfPosX = self->posX.i.hi;
            selfPosY = self->posY.i.hi - 0x1F;
            player = &PLAYER;
            xPos = selfPosX - player->posX.i.hi;
            if (xPos < 0x80U) {
                yPos = (selfPosY + ((xPos * rsin(0x100 - self->rotZ)) >> 0xC)) - (player->posY.i.hi + 0x18);
                if (yPos <= 0) {
                    player->posY.i.hi += yPos + 1;
                    g_Player.pl_vram_flag |= 0x41;  // Grounded. What does 0x40 mean?
                }
            }
            break;

        case LAND:
            // Update tilemap to show fallen stairs
            pDstTileIdx = &FallingStairsFallenTileIndices;
            pSrcTile = &FallingStairsNotFallenTileValues;
            for (i = 0; i < 0x10; i++, pDstTileIdx++, pSrcTile++) {
                g_Tilemap.fg[*pDstTileIdx] = *pSrcTile; // All except the last tile are in front of nothing
            }
            g_Tilemap.fg[*pDstTileIdx] = 0x1BA; // This is the only tile that overlaps existing graphics
            self->animCurFrame = 0;
            g_CastleFlags[CASTLE_FLAG_CHI_FALLING_STAIRS] = 1;
            self->step++;
            break;
    }
    if (self->ext.prim != NULL) {
        prim = self->ext.prim;
        prim = prim->next;

        // Update dust particles
        while (prim != NULL) {
            if (prim->p3) {
                UpdateDustParticles(prim);
            }
            prim = prim->next;
        }

        prim = self->ext.fallingStairs.prim;
        prim->u0 = prim->v0 = 0;
        prim->x0 = prim->y0 = 0;
        prim->drawMode = DRAW_UNK02;
    }
}

// E_FALLING_STEP
// func_8019D9C8
// https://decomp.me/scratch/aHmp1
// PSP:func_psp_0924E4D8:Match
// PSP:https://decomp.me/scratch/QAIZG
void EntityFallingStep(Entity* self) {
    const s32 TilePos = 0x20D;
    const s32 TileInitVal = 0x233;
    const s32 TriggerBoxX = 0xC8;
    const s32 TriggerBoxY = 0x1D0;
    const u32 TriggerBoxW = 0x18;
    const u32 TriggerBoxH = 0x40;

    typedef enum Step {
        INIT = 0,
        WAIT_FOR_TRIGGER = 1,
        BREAK_AWAY = 2,
        FALLING = 3,
    };

    Primitive* prim;
    s32 posX;
    s32 posY;
    s32 i;
    s32 scrolledY;
    Entity* entity;
    s32 primIdx;
    Entity* player;
    s32 scrolledX;
    Collider collider;

    switch (self->step) {
    case INIT:
        if (g_CastleFlags[CASTLE_FLAG_CHI_FALLING_STEP]) {
            DestroyEntity(self);
            return;
        }
        InitializeEntity(&g_InitTilemap);
        self->animCurFrame = 0;
        self->drawFlags |= 4;
        g_Tilemap.fg[TilePos] = TileInitVal;
        // Fallthrough
    case WAIT_FOR_TRIGGER:
        player = &PLAYER;
        posX = player->posX.i.hi;
        posY = player->posY.i.hi;
        scrolledX = posX + g_Tilemap.scrollX.i.hi;
        scrolledY = posY + g_Tilemap.scrollY.i.hi;
        scrolledX -= TriggerBoxX;
        scrolledY -= TriggerBoxY;
        if ((scrolledX < TriggerBoxW) &&
            (scrolledY < TriggerBoxH) &&
            (g_Player.pl_vram_flag & 1)) {
            g_CastleFlags[CASTLE_FLAG_CHI_FALLING_STEP] = 1;
            self->step++;
        }
        break;
        
    case BREAK_AWAY:
        self->animCurFrame = 0x24;
        g_Tilemap.fg[TilePos] = 0;
        g_api.PlaySfx(SFX_WALL_DEBRIS_B);
        primIdx = g_api.func_800EDB58(PRIM_TILE_ALT, 96);
        if (primIdx != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIdx;
            prim = &g_PrimBuf[primIdx];
            self->ext.prim = prim;
            
            prim->x0 = self->posX.i.hi + 8;
            prim->y0 = self->posY.i.hi - 8;
            prim->drawMode = DRAW_HIDE | DRAW_UNK02;
            prim = prim->next;
            while (prim != NULL) {
                prim->p3 = 0;
                prim->r0 = 0x60;
                prim->g0 = 0x60;
                prim->b0 = 0x20;
                prim->u0 = prim->v0 = 1;
                prim->priority = 0xC0;
                prim->drawMode = DRAW_HIDE;
                self->ext.fallingStairs.prim = prim;
                prim = prim->next;
            }
            self->ext.fallingStairs.primBatchCount = 32;
        } else {
            self->ext.fallingStairs.primBatchCount = 0;
            self->ext.prim = NULL;
        }
        self->step++;
        break;
        
    case FALLING:
        MoveEntity();
        self->rotZ -= 0x20;
        self->velocityY += 0x4000;
        posX = self->posX.i.hi;
        posY = self->posY.i.hi + 9;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & 1) {
            scrolledY = g_Tilemap.scrollY.i.hi + self->posY.i.hi;

            // Check for lowest possible position
            if (scrolledY > 0x3C0) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(6, self, entity);
                    entity->params = 0x10;
                }
                DestroyEntity(self);
                return;
            }
            posY = self->posY.i.hi += collider.unk18;
            self->velocityY = -self->velocityY / 3;
            if (self->velocityX == 0) {
                self->velocityX = -0xC000;
            } else {
                if (self->velocityX > 0) {
                    posX += 0xC;
                } else {
                    posX -= 0xC;
                }
    
                posY -= 2;
                g_api.CheckCollision(posX, posY, &collider, 0);
                if (collider.effects & 1) {
                    self->velocityX = -self->velocityX;
                }
            }
        }
        
        // Initialize a batch of 2 primitives
        if (self->ext.fallingStairs.primBatchCount != 0) {
            self->ext.fallingStairs.primBatchCount--;
            prim = self->ext.prim;
            posX = prim->x0;
            posY = prim->y0;

            for (i = 0; i < 2; i++) {
                prim = self->ext.prim;
                prim = prim->next;
                prim = FindFirstUnkPrim(prim);
                if (prim != NULL) {
                    prim->p3 = 1;
                    prim->p2 = 0;
                    prim->x0 = (posX + (Random() & 7)) - 3;
                    prim->y0 = posY + (Random() & 0xF);
                }
            }
        }
    }
    
    if (self->ext.prim != NULL) {
        prim = self->ext.prim;
        prim = prim->next;
        while (prim != NULL) {
            if (prim->p3) {
                UpdateDustParticles(prim);
            }
            prim = prim->next;
        }
        prim = self->ext.fallingStairs.prim;
        prim->u0 = prim->v0 = 0;
        prim->x0 = prim->y0 = 0;
        prim->drawMode = 2;
    }
}