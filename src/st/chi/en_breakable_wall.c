/*
 * File: en_breakable_wall.c
 * Overlay: CHI
 * Description: ENTITY - 3 layer wall that is breakable by attacking
 */

#include "chi.h"

// E_BREAKABLE_WALL_DEBRIS
// params: animCurFrame to use
//         (== 0xD) Different starting X velocity
//         (< 0xB) Different starting Y velocity
//         (>= 0xC) Will break into smaller pieces when it hits the ground
// func_8019C31C
// https://decomp.me/scratch/NKGUh
void EntityBreakableWallDebris(Entity* self) {
    const int Gravity = 0x2000;

    typedef enum Step {
        INIT = 0,
        CHECK_FLAG = 1,
        MOVEMENT = 2,
    };

    Collider collider;
    s32 velX;
    s32 velY;
    s32 newVelY;
    s32 i;
    u16 params;
    u8 animCurFrame;
    Entity* entity;

    switch (self->step) {
        case INIT:
            InitializeEntity(&g_InitTilemap);
            animCurFrame = self->params;
            self->drawFlags = FLAG_DRAW_ROTZ;
            self->zPriority = 0x69;
            self->animCurFrame = animCurFrame;
            if (self->rotZ & 1) {
                self->facingLeft = true;
                self->rotZ &= 0xFFF0;
            }

            velX = (Random() & 0xF) << 0xC;
            self->velocityX = velX;
            if (self->animCurFrame == 0xD) {
                self->velocityX = velX + 0x4000;
            }

            velY = ((Random() & 7) << 0xB) - 0x4000;
            self->velocityY = velY;
            if (self->animCurFrame < 0xB) {
                self->velocityY = velY + 0xFFFF0000;
            }

            self->ext.breakableWallDebris.rotSpeed = ((Random() & 3) + 1) * 32;
            return;

        case CHECK_FLAG:
            params = self->params;

            if (params & 0x100) {
                self->params = params & 0xFF;
                self->step++;
                return;
            }
            return;

        case MOVEMENT:
            self->rotZ += self->ext.breakableWallDebris.rotSpeed;

            MoveEntity();

            self->velocityY += Gravity;

            g_api_CheckCollision(self->posX.i.hi, (s16)(self->posY.i.hi + 6), &collider, 0);
            if (collider.effects & 1) {
                self->posY.i.hi += collider.unk18;
                if (self->animCurFrame >= 0xC) {
                    // Break into a couple pieces
                    for (i = 0; i < 2; i++) {
                        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                        if (entity != NULL) {
                            CreateEntityFromEntity(E_BREAKABLE_WALL_DEBRIS, self, entity);
                            entity->params = ((Random() & 3) + 9) | 0x100;
                        }
                    }
                    DestroyEntity(self);
                    return;
                }
                newVelY = self->velocityY;
                if (newVelY <= 0x7FFF) {
                    // Poof, gone
                    entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (entity != NULL) {
                        CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, entity);
                        entity->params = 0xC010;
                    }
                    DestroyEntity(self);
                    return;
                }

                // Bounce
                self->velocityY = -newVelY * 2 / 3;
            }
            break;
    }
}

// D_801808CC
static u16 BreakableWallTilesCollision[] = {
    0x0399, 0x039A, 0x0399, 0x039A, 0x039B, 0x039C, 0x039B, 0x039C,
    0x0399, 0x039A, 0x0399, 0x039A, 0x0106, 0x0108, 0x0106, 0x0108,
    0x010B, 0x010D, 0x010B, 0x010D, 0x0106, 0x0108, 0x0106, 0x0108,
};

// D_801808FC
static s16 BreakableRoomEntityData[] = {
    0x000D, 0x0012, 0xFFE8, 0x0000, 0x000D, 0x0012, 0xFFF8, 0x0800,
    0x000D, 0x0012, 0x0000, 0x0000, 0x000D, 0x0012, 0x0008, 0x0200,
    0x000D, 0x0012, 0x0018, 0x0800, 0x000C, 0x0006, 0x0014, 0x0100,
    0x000C, 0x0008, 0x0000, 0x0301, 0x000C, 0x0004, 0xFFEC, 0xFE00,
    0x000B, 0xFFFC, 0xFFF4, 0x0000, 0x000C, 0xFFFC, 0x000C, 0x0101,
    0x000B, 0xFFF8, 0xFFF0, 0xFF80, 0x000C, 0xFFF4, 0x0000, 0x0000,
    0x000C, 0xFFF0, 0xFFE8, 0x0100, 0x000B, 0xFFF0, 0x0008, 0x0180,
    0x000B, 0xFFEC, 0x0010, 0xFE40,
};

// E_BREAKABLE_WALL
// func_8019C5CC
// https://decomp.me/scratch/Xmw21
void EntityBreakableWall(Entity* self) {
    const int WallWidthTiles = 3;
    const int WallHeightTiles = 4;
    const int WallTotalTiles = WallWidthTiles * WallHeightTiles;
    const int ResetTime = 20;
    //TODO: Defined elsewhere?
    const int RoomWidthTiles = 16;

    const int startTileIdx = 0x160;

    typedef enum Step {
        INIT = 0,
        IDLE = 1,
        BREAK_1 = 2,    // Dynamically calculated, never set directly
        BREAK_2 = 3,    // Dynamically calculated, never set directly
        BREAK_3 = 4,    // Dynamically calculated, never set directly
        WAIT_FOR_RESET = 8,
    };

    s32 xPos; //s6
    s32 yPos; //s7
    s32 newPrimIdx; //s8
    s32 b; //s0
    s32 c; //s5
    s32 tileIdx; //s4
    s16* pSrcTile; //s1
    Primitive* prim;
    Entity* entity;
    
    switch (self->step) {
        case INIT:
            InitializeEntity(&g_InitTilemap);
            self->animCurFrame = 2;
            self->animCurFrame = 0;
            self->hitPoints = 0x20;
            self->hitboxWidth = 24;
            self->hitboxHeight = 32;
            self->hitboxState = 2;

            self->flags |= FLAG_UNK_400000;

            // Determine tile indices to use
            pSrcTile = BreakableWallTilesCollision;
            if (g_CastleFlags[CASTLE_FLAG_CHI_BREAKABLE_WALL]) {
                pSrcTile += 0xC;    // No collision
            }
            
            // Update tilemap with appropriate collision
            tileIdx = 0x160;
            for (c = 0; c < WallWidthTiles; tileIdx++, c++) {
                for (b = 0; b < WallHeightTiles; b++, pSrcTile++) {
                    *(&g_Tilemap.fg[tileIdx] + b * RoomWidthTiles) = *pSrcTile;
                }
            }

            if (g_CastleFlags[CASTLE_FLAG_CHI_BREAKABLE_WALL]) {
                DestroyEntity(self);
                return;
            }

            newPrimIdx = g_api.AllocPrimitives(PRIM_GT4, 2);
            if (newPrimIdx == -1) {
                DestroyEntity(self);
                return;
            }
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = newPrimIdx;
            prim = &g_PrimBuf[newPrimIdx];

            self->ext.prim = prim;

            // Calculate values for left prim
            xPos = self->posX.i.hi - 23;
            yPos = self->posY.i.hi - 31;

            // Left prim
            prim->tpage = 0xF;
            prim->clut = 7;
            prim->u0 = prim->u2 = 0x94;
            prim->u1 = prim->u3 = 0xB4;
            prim->v0 = prim->v1 = 0x84;
            prim->v2 = prim->v3 = 0xC4;
            prim->x0 = prim->x2 = xPos;
            xPos += 32;
            prim->x1 = prim->x3 = xPos;
            prim->y0 = prim->y1 = yPos;
            prim->y2 = prim->y3 = yPos + 64;
            prim->priority = 0x6A;
            prim->drawMode = DRAW_UNK02;


            // Right prim
            prim = prim->next;
            prim->tpage = 0xF;
            prim->clut = 8;
            prim->u0 = prim->u2 = 0xBC;
            prim->u1 = prim->u3 = 0xCC;
            prim->v0 = prim->v1 = 0x84;
            prim->v2 = prim->v3 = 0xC4;
            prim->x0 = prim->x2 = xPos;
            prim->x1 = prim->x3 = xPos + 0x10;
            prim->y0 = prim->y1 = yPos;
            prim->y2 = prim->y3 = yPos + 0x40;
            prim->priority = 0x6A;
            prim->drawMode = DRAW_UNK02;
            
            pSrcTile = BreakableRoomEntityData;
            entity = self + 1;
            for (c = 0; c < 15; c++, entity++) {
                DestroyEntity(entity);
                CreateEntityFromEntity(E_BREAKABLE_WALL_DEBRIS, self, entity);

                entity->params = *pSrcTile++;
                entity->posX.i.hi += *pSrcTile++;
                entity->posY.i.hi += *pSrcTile++;
                entity->rotZ = *pSrcTile++;
            }
            return;

        case IDLE:
            if (self->flags & FLAG_DEAD) {
                g_api.PlaySfx(SFX_WALL_DEBRIS_B);
                
                self->ext.breakableWall.breakCount++;

                self->flags &= ~FLAG_DEAD;
                self->hitPoints = 0x20;
                self->hitboxWidth -= 8;
                self->hitboxOffX -= 8;

                // Update collision via tilemap
                pSrcTile = BreakableWallTilesCollision;
                pSrcTile += 0x18 - self->ext.breakableWall.breakCount * 4;
                tileIdx = 0x163 - self->ext.breakableWall.breakCount;
                for (b = 0; b < WallHeightTiles; b++, pSrcTile++) {
                    *(&g_Tilemap.fg[tileIdx] + b * RoomWidthTiles) = *pSrcTile;
                }

                entity = self + 1;
                entity += (self->ext.breakableWall.breakCount - 1) * 5;
                for (c = 0; c < 5; c++, entity++) {
                    entity->step++;
                }

                // Smoke
                xPos = self->posX.i.hi + 0x20;
                yPos = self->posY.i.hi;
                xPos -= self->ext.breakableWall.breakCount * 0xC;
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, entity);
                    entity->posX.i.hi = xPos;
                    entity->posY.i.hi = yPos + 0x10;
                    entity->params = 0x13;
                    entity->params |= 0xC000;
                }
                
                // Rotating bricks?
                for (c = 0; c < 3; c++) {
                    entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (entity != NULL) {
                        CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, entity);
                        entity->posX.i.hi = xPos;
                        entity->posY.i.hi = yPos + 0x20 - (Random() & 3) * 8;
                        entity->params = 0x10;
                        entity->params |= 0xC000;
                    }
                }
                // Dynamically set Break_1, Break_2, or Break_3
                self->step += self->ext.breakableWall.breakCount;
            }
            return;

        case BREAK_1:   // Dynamically calculated, never set directly
            prim = self->ext.prim;
            prim = prim->next;
            prim->drawMode = DRAW_HIDE;
            self->ext.breakableWall.resetTimer = ResetTime;
            self->step = WAIT_FOR_RESET;
            return;

        case BREAK_2:   // Dynamically calculated, never set directly
            prim = self->ext.prim;
            prim->u1 = prim->u3 -= 0x10;
            prim->x1 = prim->x3 -= 0x10;
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromCurrentEntity(E_HEART_DROP, entity);
                entity->posX.i.hi = 0x20 - g_Tilemap.scrollX.i.hi;
                entity->posY.i.hi = 0x188 - g_Tilemap.scrollY.i.hi;
                entity->params = 3;
            }
            self->ext.breakableWall.resetTimer = ResetTime;
            self->step = WAIT_FOR_RESET;
            return;

        case BREAK_3:   // Dynamically calculated, never set directly
            prim = self->ext.prim;
            prim->drawMode = DRAW_HIDE;
            self->hitboxState = 0;
            g_CastleFlags[CASTLE_FLAG_CHI_BREAKABLE_WALL] = 1;
            // Update the map "explored" state
            // This is read from an array of data in DRA, and in
            // this case results in exploring the room to the left
            g_api.func_800F1FC4(CASTLE_FLAG_CHI_BREAKABLE_WALL);
            DestroyEntity(self);
            return;

        case WAIT_FOR_RESET:
            if (!--self->ext.breakableWall.resetTimer) {
                self->step = IDLE;
            }
            return;
    }
}