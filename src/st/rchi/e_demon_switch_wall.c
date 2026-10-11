// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rchi.h"

extern EInit g_EInitBreakableWallDebris;

#ifdef VERSION_PSP
extern s32 E_ID(GREY_PUFF);
#endif

// D_us_801807EC
static s16 WallTiles[] = {
    // With Collision
    0x039D, 0x03A0, 0x03A0, 0x039E, 0x03A0, 0x03A0, 0x03A0, 0x039F, 0x03A0,
    0x03A0, 0x03A0, 0x03A0,
    // Without Collision
    0x01C2, 0x01BF, 0x01BF, 0x01D2, 0x01BF, 0x01BF, 0x01BF, 0x01D3, 0x01BF,
    0x01BF, 0x01BF, 0x01BF};

#include "../e_falling_pebble.h"

void EntityDemonSwitch(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitBreakableWallDebris);

        self->animCurFrame = 3;
        self->hitPoints = 32767;
        self->hitboxState = 3;
        self->hitboxWidth = 6;
        self->hitboxHeight = 8;

        if (g_CastleFlags[RCHI_DEMON_SWITCH]) {
            self->animCurFrame = 4;
        }
        /* fall through */
    case 1:
        if (self->hitParams == 7) {
            g_api.PlaySfx(SFX_ANIME_SWORD_B);
            g_CastleFlags[RCHI_DEMON_SWITCH] = 1;
            g_api.RevealSecretPassageAtPlayerPositionOnMap(RCHI_DEMON_SWITCH);
            self->animCurFrame = 4;
            self->step++;
        }
        break;
    }
}

extern Primitive* FindFirstUnkPrim(Primitive* poly);
void EntityDemonSwitchWall(Entity* self) {
    enum Step {
        INIT = 0,
        IDLE_CLOSED = 1,
        PREP_TO_OPEN = 2,
        OPENING = 3,
        IDLE_OPEN = 16, // NOTE: Never set from OPENING, it's only from INIT
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
    case INIT:
        InitializeEntity(g_EInitBreakableWallDebris);

        self->animCurFrame = 1; // Default: Collision (closed)

        // Determine tilemap collision adjustments based on current map flags
        pSrcTile = WallTiles;
        if (g_CastleFlags[RCHI_DEMON_SWITCH]) {
            pSrcTile += 0xC; // No collision (opened)
        }

        // Adjust tilemap
        tileIdx = 0x392;
        for (iCol = 0; iCol < 3; tileIdx--, iCol++) {
            for (iRow = 0; iRow < 4; iRow++, pSrcTile++) {
                *(&g_Tilemap.fg[tileIdx] - iRow * 16) = *pSrcTile;
            }
        }

        // Update internal state
        if (g_CastleFlags[RCHI_DEMON_SWITCH]) {
            self->animCurFrame = 0;
            self->step = IDLE_OPEN;
            break;
        }
        // Fallthrough
    case IDLE_CLOSED: // Never set directly
        if (g_CastleFlags[RCHI_DEMON_SWITCH]) {
            self->step++; // PrepToOpen
        }
        break;
    case PREP_TO_OPEN: // Never set directly
        primIdx = g_api.AllocPrimitives(PRIM_TILE, 16);
        if (primIdx != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIdx;
            prim = &g_PrimBuf[primIdx];
            self->ext.demonSwitchWall.prim = prim;

            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
            return;
        }
        self->step++; // Opening
        return;
    case OPENING: // Never set directly
        // Shake vertically
        self->ext.demonSwitchWall.unk80++;
        if (self->ext.demonSwitchWall.unk80 & 1) {
            self->posY.i.hi++;
        } else {
            self->posY.i.hi--;
        }

        if (!(self->ext.demonSwitchWall.unk80 % 8)) {
            g_api.PlaySfx(SFX_WALL_DEBRIS_B);
        }
        MoveEntity();

        if (self->velocityX > FIX(-0.25)) {
            self->velocityX += FIX(-0.0078125);
        }

        // Generate a "falling pebble" particle
        prim = self->ext.demonSwitchWall.prim;
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
        prim = self->ext.demonSwitchWall.prim;
        while (prim != NULL) {
            if (prim->p3) {
                UpdateFallingPebble(prim);
            }
            prim = prim->next;
        }

        // Create "ground puff" entity
        xPos = self->posX.i.hi + 0x18;
        yPos = self->posY.i.hi + 0x20;
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromCurrentEntity(E_ID(GREY_PUFF), newEntity);
            newEntity->posX.i.hi = xPos + (Random() & 0x1F);
            newEntity->posY.i.hi = yPos;
            newEntity->params = Random() & 3;
            newEntity->zPriority = 0xA0;
        }

        // Calculate how many columns of tiles should be blocking the player
        remainingColumnCount = 0;
        remainingColumnCount = 0x18 - self->posX.i.hi;
        remainingColumnCount >>= 4;
        if (remainingColumnCount > 3) {
            remainingColumnCount = 3;
        }

        // Update tilemap to remove collision as the wall moves out of the way
        pSrcTile = WallTiles;
        tileIdx = 0x392;
        pSrcTile += 0xC;
        for (iCol = 0; iCol < remainingColumnCount; tileIdx--, iCol++) {
            for (iRow = 0; iRow < 4; iRow++, pSrcTile++) {
                *((&g_Tilemap.fg[tileIdx]) - iRow * 16) = *pSrcTile;
            }
        }

        // Destroy myself if I've scrolled completely off the screen
        if (self->posX.i.hi < -0x28) {
            DestroyEntity(self);
        }
        break;
    case IDLE_OPEN:
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (self->params) {
                break;
            }
            self->animCurFrame++;
            self->params |= 1; // Once per button press
        } else {
            self->params = 0;
        }

        if (g_pads[1].pressed & PAD_CIRCLE) {
            if (self->step_s) {
                break;
            }
            self->animCurFrame--;
            self->step_s |= 1; // Once per button press
        } else {
            self->step_s = 0;
        }
        break;
    }
}
