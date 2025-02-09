// SPDX-License-Identifier: AGPL-3.0-or-later
/*
 * File: en_demon_switch_wall.c
 * Overlay: CHI
 * Description: ENTITY - Secret wall that is opened by the demon familiar
 *                       pressing a button
 */

#include "chi.h"

// func_8019BD0C
void UpdateFallingPebble(Primitive* prim) {
    const int FallSpeed = 2;
    const int MaxScrolledY = 160;

    s8 dims;
    s16 newY;
    u32 scrollY;
    s32 newYScrolled;
    u8 newTimer;

    switch (prim->p3) {
    case 1: // Init (and fallthru to Idle)
        dims = (Random() & 1) + 1;
        prim->u0 = dims;
        prim->v0 = dims;
        prim->r0 = 0x60;
        prim->g0 = 0x80;
        prim->b0 = 0x30;
        prim->priority = 0xA0;
        prim->drawMode = DRAW_UNK02;
        prim->p2 = (Random() & 0x1F) + 0x10;
        prim->p3 = 2U;
        // fallthrough
    case 2: // Idle
        newY = prim->y0 + FallSpeed;
        newTimer = prim->p2 - 1;
        prim->y0 = newY;
        scrollY = g_Tilemap.scrollY.i.hi;
        newYScrolled = scrollY + newY;
        prim->p2 = newTimer;
        if (newTimer == 0 || newYScrolled > MaxScrolledY) {
            prim->drawMode = DRAW_HIDE;
            prim->p3 = 0U; // Inactive
        }
        return;
    }
}

// E_DEMON_SWITCH
// func_8019BDF8
void EntityDemonSwitch(Entity* self) {
    typedef enum Step {
        INIT = 0,
        PRESS = 1,
    };

    switch (self->step) {
    case INIT:
        InitializeEntity(&g_EInitSecret);

        self->animCurFrame = 3;
        self->hitPoints = 32767;
        self->hitboxState = 3;
        self->hitboxWidth = 6;
        self->hitboxHeight = 8;

        if (g_CastleFlags[CHI_DEMON_SWITCH] != 0) {
            self->animCurFrame = 4;
        }
        // fallthrough
    case PRESS:
        if (self->hitParams == 7) {
            g_api.PlaySfx(SFX_ANIME_SWORD_B);
            g_CastleFlags[CHI_DEMON_SWITCH] = 1;
            // Update the map "explored" state
            // This is read from an array of data in DRA, and in
            // this case results in exploring the room to the right
            g_api.func_800F1FC4(CHI_DEMON_SWITCH);
            self->animCurFrame = 4;
            self->step++; // Inactive
        }
        break;
    }
}

#if defined(VERSION_PSP)
extern s32 D_psp_0926BC50;
#endif

// clang-format off
// D_8018089C
static u16 WallTiles[] = {
    // With Collision
    0x039D, 0x03A0, 0x03A0, 0x039E, 0x03A0, 0x03A0, 0x03A0, 0x039F,
    0x03A0, 0x03A0, 0x03A0, 0x03A0,
    // Without Collision
    0x01C2, 0x01BF, 0x01BF, 0x01D2, 0x01BF, 0x01BF, 0x01BF, 0x01D3,
    0x01BF, 0x01BF, 0x01BF, 0x01BF,
};
// clang-format on

// E_DEMON_SWITCH_WALL
// func_8019BEDC
// https://decomp.me/scratch/oDbUj
// PSP:func_psp_0924ED28:No match
// PSP:https://decomp.me/scratch/DxiYq
void EntityDemonSwitchWall(Entity* self) {
    typedef enum Step {
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
        InitializeEntity(&g_EInitSecret);

        self->animCurFrame = 1; // Default: Collision (closed)

        // Determine tilemap collision adjustments based on current map flags
        pSrcTile = WallTiles;
        if (g_CastleFlags[CHI_DEMON_SWITCH]) {
            pSrcTile += 0xC; // No collision (opened)
        }

        // Adjust tilemap
        tileIdx = 0x6D;
        for (iCol = 0; iCol < 3; tileIdx++, iCol++) {
            for (iRow = 0; iRow < 4; iRow++, pSrcTile++) {
                *(&g_Tilemap.fg[tileIdx] + iRow * 16) = *pSrcTile;
            }
        }

        // Update internal state
        if (g_CastleFlags[CHI_DEMON_SWITCH]) {
            self->animCurFrame = 0;
            self->step = IDLE_OPEN;
            break;
        }
        // Fallthrough
    case IDLE_CLOSED: // Never set directly
        if (g_CastleFlags[CHI_DEMON_SWITCH]) {
            self->step++; // PrepToOpen
        }
        break;
    case PREP_TO_OPEN: // Never set directly
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

#if defined(VERSION_PSP)
        // There's a big diff here and I can't figure out how to match it

        // Here is the closest I've gotten
        // temp = self->ext.generic.unk80.modeS32;    // v1
        // var_t1 = temp & 7;    // v0
        // if (temp >= 0 ||
        //    (temp = temp & 7) != 0) {
        //    temp -= 8;
        //}
        // if (temp == 0) {
        //    g_api.PlaySfx(SFX_WALL_DEBRIS_B);
        //}
        // MoveEntity();

        // This is just what's in the PSX version
        if ((self->ext.demonSwitchWall.unk80 & 7) == 0) {
            g_api.PlaySfx(SFX_WALL_DEBRIS_B);
        }
        MoveEntity();
#else
        if ((self->ext.demonSwitchWall.unk80 & 7) == 0) {
            g_api.PlaySfx(SFX_WALL_DEBRIS_B);
        }
        MoveEntity();
#endif

        if (self->velocityX < FIX(0.25)) {
            self->velocityX += FIX(0.0078125);
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
                UpdateFallingPebble(prim);
            }
            prim = prim->next;
        }

        // Create "ground puff" entity
        xPos = self->posX.i.hi - 0x18;
        yPos = self->posY.i.hi + 0x20;
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
#if defined(VERSION_PSP)
            CreateEntityFromCurrentEntity(D_psp_0926BC50, newEntity);
#else
            CreateEntityFromCurrentEntity(E_GREY_PUFF, newEntity);
#endif
            newEntity->posX.i.hi = xPos + (Random() & 0x1F);
            newEntity->posY.i.hi = yPos;
            newEntity->params = Random() & 3;
            newEntity->zPriority = 0xA0;
        }

        // Calculate how many columns of tiles should be blocking the player
        remainingColumnCount = self->posX.i.hi - 0xE8;
        remainingColumnCount >>= 4;
        if (remainingColumnCount > 3) {
            remainingColumnCount = 3;
        }

        // Update tilemap to remove collision as the wall moves out of the way
        pSrcTile = WallTiles;
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
