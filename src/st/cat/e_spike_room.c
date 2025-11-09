// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cat.h"

#ifdef VERSION_PSP
extern s32 E_ID(UNK_23);
#endif

// nb. this can be made static after merging files
s32 echo_flag = false;

// Used when echo_flag == 1
// This drops the prim rgb values by the specified amount until they hit a
// minimum of 0x38
static s32 IncreaseBrightness(Primitive* prim, u8 brightnessOffset) {
    s32 newColor;
    s32 i;
    s32 j;
    u8* rgbVal;
    u8* rPtr;
    s32 ret;

    ret = 0;

    // Starting at prim->r0, update r0,g0,b0
    // Then we skip 0xC bytes of the prim to take us to r1,g1,b1
    // and so on for r2,g2,b2 and r3,g3,b3
    rPtr = &prim->r0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            rgbVal = &rPtr[j];
            newColor = *rgbVal;
            newColor -= brightnessOffset;
            if (newColor < 0x38) {
                newColor = 0x38;
            } else {
                ret |= 1;
            }
            *rgbVal = newColor;
        }
        rPtr += 0xC;
    }
    return ret;
}

// Used when echo_flag == 0
// This raises the prim rgb values by the specified amount until they hit a
// maximum of 0x68 which is the max darkness of the spikes room
static s32 DecreaseBrightness(Primitive* prim, u8 brightnessOffset) {
    s32 newColor;
    s32 i;
    s32 j;
    u8* rgbVal;
    u8* rPtr;
    s32 ret;

    ret = 0;

    // Starting at prim->r0, update r0,g0,b0
    // Then we skip 0xC bytes of the prim to take us to r1,g1,b1
    // and so on for r2,g2,b2 and r3,g3,b3
    rPtr = &prim->r0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            rgbVal = &rPtr[j];
            newColor = *rgbVal;
            newColor += brightnessOffset;
            if (newColor > 0x68) {
                newColor = 0x68;
            } else {
                ret |= 1;
            }
            *rgbVal = newColor;
        }
        rPtr += 0xC;
    }
    return ret;
}

void EntitySpikeRoomDarkness(Entity* self) {
    Entity* newEntity;
    Primitive* prim;
    Entity* entity;
    s32 i;
    s32 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        if (!g_CastleFlags[CAT_SPIKE_ROOM_LIT]) {
            entity = &PLAYER;
            entity->zPriority = 0xD8;
            g_unkGraphicsStruct.g_zEntityCenter = 0xD8;

            for (i = 0; i < 0x300; i++) {
                if (!g_Tilemap.fg[i]) {
                    g_Tilemap.fg[i] = 0xFF0;
                }
            }

            for (i = 0; i < 0x300; i++) {
                if (!g_BgLayers[0].layout[i]) {
                    g_BgLayers[0].layout[i] = 0xFF0;
                }
            }
        } else {
            DestroyEntity(self);
            return;
        }

        primIndex = g_api.func_800EDB58(PRIM_G4, 2);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.spikes.prim = prim;

        prim->x2 = prim->x0 = 0;
        prim->x3 = prim->x1 = 0x100;
        prim->y0 = prim->y1 = 0;
        prim->y2 = prim->y3 = 0x100;
        prim->r0 = 0x68;
        prim->g0 = 0x68;
        prim->b0 = 0x68;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0xD0;
        prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
        prim = prim->next;

        prim->type = PRIM_G4;
        prim->x0 = prim->x2 = 0 - g_Tilemap.scrollX.i.hi;
        prim->x1 = prim->x3 = 0xC0 - g_Tilemap.scrollX.i.hi;
        prim->y0 = prim->y1 = 0 - g_Tilemap.scrollY.i.hi;
        prim->y2 = prim->y3 = 0xF0 - g_Tilemap.scrollY.i.hi;
        PGREY(prim, 0) = 0x80;
        LOW(prim->r2) = LOW(prim->r0);
        PGREY(prim, 1) = 0;
        LOW(prim->r3) = LOW(prim->r1);
        prim->priority = 0xCE;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        prim = prim->next;
        // fallthrough
    case 1:
        // Iterate over g_Entities[0] -> g_Entities[39] and
        // test if player has bat echoed
        for (entity = &g_Entities[0], i = 0; i < 0x40; i++, entity++) {
            // dra.h E_BAT_ECHO
            if (entity->entityId == 0x34 && !entity->ext.spikes.echoCooldown) {
                // If user has initiated the echo and we're not on cooldown,
                // spawn the bounce entity func_us_801BACF4
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromCurrentEntity(E_ID(UNK_23), newEntity);
                    newEntity->posX.i.hi = entity->posX.i.hi;
                    newEntity->posY.i.hi = entity->posY.i.hi;
                    newEntity->facingLeft = entity->facingLeft;
                    newEntity->zPriority = 0x5F;
                    newEntity->params = 0;
                }

                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromCurrentEntity(E_ID(UNK_23), newEntity);
                    newEntity->posX.i.hi = entity->posX.i.hi;
                    newEntity->posY.i.hi = entity->posY.i.hi;
                    newEntity->facingLeft = entity->facingLeft;
                    newEntity->zPriority = 0x5F;
                    newEntity->params = 1;
                }
                // Prevent user spamming the echo bounce too quickly
                entity->ext.spikes.echoCooldown = 0x40;
            }
        }

        prim = self->ext.spikes.prim;
        if (echo_flag) {
            IncreaseBrightness(prim, 12);
        } else {
            DecreaseBrightness(prim, 6);
        }
        FntPrint("echo_flag %x\n", echo_flag);
        break;
    }

    if (g_CastleFlags[CAT_SPIKE_ROOM_LIT]) {
        DestroyEntity(self);
    }
}
