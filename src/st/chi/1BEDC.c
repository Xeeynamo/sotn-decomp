#include "chi.h"

/*
 * File: 1BEDC.c
 * Overlay: CHI
 * Description: Abandoned Mine
 */

#ifdef VERSION_PSP
extern s32 D_psp_0926BC50;
#endif

extern EntityInit EntityInit_8018067C;

u16 Room3_DemonSwitchWallTilesCollision[] = {
    0x039D, 0x03A0, 0x03A0, 0x039E, 0x03A0, 0x03A0, 0x03A0, 0x039F,
    0x03A0, 0x03A0, 0x03A0, 0x03A0,
};

u16 D_801808B4[] = {    // Room3_DemonSwitchWallTilesNoCollision
    0x01C2, 0x01BF, 0x01BF, 0x01D2, 0x01BF, 0x01BF, 0x01BF, 0x01D3,
    0x01BF, 0x01BF, 0x01BF, 0x01BF,
};

// [Entity] Room 3, Top, Demon Switch Wall
void EntityDemonSwitchWall(Entity* self) {
    enum Step {
        Init = 0,
        IdleClosed = 1,
        PrepToOpen = 2,
        Opening = 3,
        IdleOpen = 16,  //NOTE: This state is never set from Opening, it's only set from Init
    };

    s32 tileIdx;
    s16* pSrcTile;
    s32 iRow;
    s32 iCol;
    s32 primIdx;
    Primitive* prim;
    Entity* newEntity;
    s32 remainingColumnCount;
    s32 xPos;
    s32 yPos;

    switch (self->step) {
        case Init:
            InitializeEntity(&EntityInit_8018067C);

            self->animCurFrame = 1; // Default: Collision (closed)

            // Determine tilemap adjustments to make for collision based on current map flags
            pSrcTile = Room3_DemonSwitchWallTilesCollision;
            if (g_CastleFlags[CASTLE_FLAG_CHI_DEMON_BUTTON]) {
                pSrcTile += 0xC;    // No collision (opened)
            }

            // Adjust tilemap
            tileIdx = 0x6D;
            for (iCol = 0; iCol < 3; tileIdx++, iCol++) {
                for (iRow = 0; iRow < 4; iRow++, pSrcTile++) {
                    *(&g_Tilemap.fg[tileIdx] + iRow * 16) = *pSrcTile;
                }
            }

            // Update internal state
            if (g_CastleFlags[CASTLE_FLAG_CHI_DEMON_BUTTON]) {
                self->animCurFrame = 0;
                self->step = IdleOpen;
                break;
            }
            // Fallthrough
        case IdleClosed: // Never set directly
            if (g_CastleFlags[CASTLE_FLAG_CHI_DEMON_BUTTON]) {
                self->step++;   // PrepToOpen
            }
            break;
        case PrepToOpen:    // Never set directly
            primIdx = g_api.AllocPrimitives(PRIM_TILE, 16);
            if (primIdx != -1) {
                self->flags |= FLAG_HAS_PRIMS;
                self->primIndex = primIdx;
                prim = &g_PrimBuf[primIdx];
                self->ext.prim = prim;
                
                while (prim != NULL) {
                    prim->drawMode = DRAW_HIDE;
                    prim = prim->next;
                }
            } else {
                DestroyEntity(self);
                return;
            }
            self->step++;   // Opening
            return;
        case Opening:   // Never set directly
            // Shake vertically
            self->ext.demonSwitchWall.unk80++;
            if (self->ext.demonSwitchWall.unk80 & 1) {
                self->posY.i.hi++;
            } else {
                self->posY.i.hi--;
            }

#ifdef VERSION_PSP
            // There's a big diff here and I can't figure out how to match it

            // Here is the closest I've gotten
            //temp = self->ext.generic.unk80.modeS32;    // v1
            //var_t1 = temp & 7;    // v0
            //if (temp >= 0 ||
            //    (temp = temp & 7) != 0) {
            //    temp -= 8;
            //}
            //if (temp == 0) {
            //    g_api.PlaySfx(0x644);
            //}
            //MoveEntity();

            // This is just what's in the PSX version
            if ((self->ext.demonSwitchWall.unk80 & 7) == 0) {
                g_api.PlaySfx(0x644);
            }
            MoveEntity();
#else
            if ((self->ext.demonSwitchWall.unk80 & 7) == 0) {
                g_api.PlaySfx(0x644);
            }
            MoveEntity();
#endif

            if (self->velocityX < 0x4000) {
                self->velocityX += 0x200;
            }

            // Generate a "falling pebble" particle
            prim = self->ext.prim;
            prim = FindFirstUnkPrim(prim);
            if (prim != NULL) {
                prim->p3 = 1;
                
                xPos = self->posX.i.hi + (Random() & 63) + -24;
                if (xPos > 0x100) {
                    xPos -= 0x10;
                }

                yPos = self->posY.i.hi - 0x20;
                prim->x0 = xPos;
                prim->y0 = yPos;
            }

            // Update ALL "falling pebble" particles
            prim = self->ext.prim;
            while (prim != NULL) {
                if (prim->p3) {
                    Particle_FallingPebbleUpdate(prim);
                }
                prim = prim->next;
            }

            // Create "ground puff" entity
            xPos = self->posX.i.hi - 0x18;
            yPos = self->posY.i.hi + 0x20;
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
#ifdef VERSION_PSP
                CreateEntityFromCurrentEntity(D_psp_0926BC50, newEntity);
#else
                CreateEntityFromCurrentEntity(E_ID_15, newEntity);
#endif
                newEntity->posX.i.hi = xPos + (Random() & 0x1F);
                newEntity->posY.i.hi = yPos;
                newEntity->params = Random() & 3;
                newEntity->zPriority = 0xA0;
            }

            // Calculate how many columns of tiles should still be blocking the player
            remainingColumnCount = self->posX.i.hi - 0xE8;
            remainingColumnCount >>= 4;
            if (remainingColumnCount > 3) {
                remainingColumnCount = 3;
            }

            // Update tilemap to remove collision as the wall moves out of the way
            pSrcTile = Room3_DemonSwitchWallTilesCollision;
            pSrcTile += 0xC;
            tileIdx = 0x6D;
            for (iCol = 0; iCol < remainingColumnCount; tileIdx++, iCol++) {
                for (iRow = 0; iRow < 4; iRow++, pSrcTile++) {
                    *((&g_Tilemap.fg[tileIdx]) + iRow * 16) = *pSrcTile;
                }
            }

            // Destroy myself if I've scrolled completely off the screen
            if (self->posX.i.hi > 0x128) {
                DestroyEntity(self);
            }
            break;
        case IdleOpen:
            if (g_pads[1].pressed & PAD_SQUARE) {
                if (self->params) {
                    break;
                }
                self->animCurFrame++;
                self->params |= 1;  // Once per button press
            } else {
                self->params = 0;
            }
            
            if (g_pads[1].pressed & PAD_CIRCLE) {
                if (self->step_s) {
                    break;
                }
                self->animCurFrame--;
                self->step_s |= 1;  // Once per button press
            } else {
                self->step_s = 0;
            }
            break;
    }
}

// [Entity] Room 5, Bottom, Breakable Wall Debris
void EntityBreakableWallDebris(Entity* entity) {
    Collider collider;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_v1_3;
    s32 var_s2;
    u16 temp_v1;
    u16 temp_v1_2;
    u8 temp_a0;
    Entity* temp_v0;
    Entity* temp_v0_2;

    temp_v1 = entity->step;
    switch (temp_v1) {
        case 0:
            InitializeEntity(&EntityInit_8018067C);
            temp_a0 = entity->params;
            entity->drawFlags = 4;
            entity->zPriority = 0x69;
            entity->animCurFrame = temp_a0;
            if (entity->rotZ & 1) {
                entity->facingLeft = 1;
                entity->rotZ = entity->rotZ & 0xFFF0;
            }
            temp_a0_2 = (Random() & 0xF) << 0xC;
            entity->velocityX = temp_a0_2;
            if (entity->animCurFrame == 0xD) {
                entity->velocityX = temp_a0_2 + 0x4000;
            }
            temp_a0_3 = ((Random() & 7) << 0xB) - 0x4000;
            entity->velocityY = temp_a0_3;
            if (entity->animCurFrame < 0xB) {
                entity->velocityY = temp_a0_3 + 0xFFFF0000;
            }
            entity->ext.generic.unk9C.modeS16.unk0 = ((Random() & 3) + 1) * 32;
            return;
        case 1:
            temp_v1_2 = entity->params;
            if (temp_v1_2 & 0x100) {
                entity->params = temp_v1_2 & 0xFF;
                entity->step = entity->step + 1;
                return;
            }
            return;
        case 2:
            entity->rotZ += entity->ext.generic.unk9C.modeS16.unk0;
            MoveEntity();
            entity->velocityY = entity->velocityY + 0x2000;
            g_api_CheckCollision(entity->posX.i.hi, (s32) (s16) (entity->posY.i.hi + 6), &collider, 0);
            if (collider.effects & 1) {
                entity->posY.i.hi = entity->posY.i.hi + collider.unk18;
                if (entity->animCurFrame >= 0xC) {
                    var_s2 = 0;
                    do {
                        temp_v0 = AllocEntity(&g_Entities[224], &g_Entities[256]);
                        var_s2 += 1;
                        if (temp_v0 != NULL) {
                            CreateEntityFromEntity(E_BREAKABLE_WALL_DEBRIS, entity, temp_v0);
                            temp_v0->params = ((Random() & 3) + 9) | 0x100;
                        }
                    } while (var_s2 < 2);
                    DestroyEntity(entity);
                    return;
                }
                temp_v1_3 = entity->velocityY;
                if (temp_v1_3 <= 0x7FFF) {
                    temp_v0_2 = AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (temp_v0_2 != NULL) {
                        CreateEntityFromEntity(E_INTENSE_EXPLOSION, entity, temp_v0_2);
                        temp_v0_2->params = 0xC010;
                    }
                    DestroyEntity(entity);
                    return;
                }
                entity->velocityY = -temp_v1_3 * 2 / 3;
            }
            break;
    }
}
