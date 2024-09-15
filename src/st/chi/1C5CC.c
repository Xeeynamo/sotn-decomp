#include "chi.h"

/*
 * File: 1C5CC.c
 * Overlay: CHI
 * Description: Abandoned Mine
 */

extern EntityInit EntityInit_8018067C;
extern u16 Room5_BreakableWallTilesCollision[];
extern u16 Room5_BreakableRoomEntityData[];

// [Entity] Room 5, Middle/Bottom, Breakable Wall
void EntityBreakableWall(Entity* self) {
    const int WallWidthTiles = 3;
    const int WallHeightTiles = 4;
    const int WallTotalTiles = WallWidthTiles * WallHeightTiles;
    const int ResetTime = 20;
    //TODO: Defined elsewhere?
    const int RoomWidthTiles = 16;

    const int startTileIdx = 0x160;

    enum Step {
        Init = 0,
        Idle = 1,
        Break_1 = 2,    // Dynamically calculated, never set directly
        Break_2 = 3,    // Dynamically calculated, never set directly
        Break_3 = 4,    // Dynamically calculated, never set directly
        WaitForReset = 8,
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
        case Init:
            InitializeEntity(&EntityInit_8018067C);
            self->animCurFrame = 2;
            self->animCurFrame = 0;
            self->hitPoints = 0x20;
            self->hitboxWidth = 24;
            self->hitboxHeight = 32;
            self->hitboxState = 2;

            self->flags |= FLAG_UNK_400000;

            // Determine tile indices to use
            pSrcTile = Room5_BreakableWallTilesCollision;
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
            self->flags |= FLAG_UNK_800000;
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
            
            pSrcTile = Room5_BreakableRoomEntityData;
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
        case Idle:
            if (self->flags & FLAG_DEAD) {
                g_api.PlaySfx(NA_SE_EN_ROCK_BREAK);
                
                self->ext.breakableWall.breakCount++;

                self->flags &= ~FLAG_DEAD;
                self->hitPoints = 0x20;
                self->hitboxWidth -= 8;
                self->hitboxOffX -= 8;

                // Update collision via tilemap
                pSrcTile = Room5_BreakableWallTilesCollision;
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

                // Smoke entity?
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
                
                // Rotating brick entities?
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
        case Break_1:   // Dynamically calculated, never set directly
            prim = self->ext.prim;
            prim = prim->next;
            prim->drawMode = DRAW_HIDE;
            self->ext.breakableWall.resetTimer = ResetTime;
            self->step = WaitForReset;
            return;
        case Break_2:   // Dynamically calculated, never set directly
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
            self->step = WaitForReset;
            return;
        case Break_3:   // Dynamically calculated, never set directly
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
        case WaitForReset:
            if (!--self->ext.breakableWall.resetTimer) {
                self->step = Idle;
            }
            return;
    }
}
