// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cat.h"

#ifdef VERSION_PSP
extern s32 E_ID(UNK_23);
#endif

// nb. this can be made static after merging files
s32 echo_flag = false;

// Used when echo_flag == 1
static s32 UpdatePrimEcho(Primitive* prim, u8 arg1) {
    s32 var_s0;
    s32 i;
    s32 j;
    u8* var_s2;
    u8* var_s3;
    s32 ret;

    ret = 0;
    var_s3 = &prim->r0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            var_s2 = &var_s3[j];
            var_s0 = *var_s2;
            var_s0 -= arg1;
            if (var_s0 < 0x38) {
                var_s0 = 0x38;
            } else {
                ret |= 1;
            }
            *var_s2 = var_s0;
        }
        var_s3 += 0xC;
    }
    return ret;
}

static s32 UpdatePrimNormal(Primitive* prim, u8 arg1) {
    s32 var_s0;
    s32 i;
    s32 j;
    u8* var_s2;
    u8* var_s3;
    s32 ret;

    ret = 0;
    var_s3 = &prim->r0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            var_s2 = &var_s3[j];
            var_s0 = *var_s2;
            var_s0 += arg1;
            if (var_s0 > 0x68) {
                var_s0 = 0x68;
            } else {
                ret |= 1;
            }
            *var_s2 = var_s0;
        }
        var_s3 += 0xC;
    }
    return ret;
}

void func_us_801B7B64(Entity* self) {
    Entity* newEntity;
    Primitive* prim;
    Entity* player;
    s32 i;
    s32 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        if (!g_CastleFlags[CAT_SPIKE_ROOM_LIT]) {
            player = &PLAYER;
            player->zPriority = 0xD8;
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

        primIndex = g_api.func_800EDB58(3, 2);
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
        player = &PLAYER;

        for (i = 0; i < 0x40; i++, player++) {
            // dra.h E_BAT_ECHO
            if (player->entityId == 0x34 && !player->ext.spikes.echoCooldown) {
                // If user has initiated the echo and we're not on cooldown,
                // spawn the bounce entity func_us_801BACF4
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromCurrentEntity(E_ID(UNK_23), newEntity);
                    newEntity->posX.i.hi = player->posX.i.hi;
                    newEntity->posY.i.hi = player->posY.i.hi;
                    newEntity->facingLeft = player->facingLeft;
                    newEntity->zPriority = 0x5F;
                    newEntity->params = 0;
                }

                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromCurrentEntity(E_ID(UNK_23), newEntity);
                    newEntity->posX.i.hi = player->posX.i.hi;
                    newEntity->posY.i.hi = player->posY.i.hi;
                    newEntity->facingLeft = player->facingLeft;
                    newEntity->zPriority = 0x5F;
                    newEntity->params = 1;
                }
                // Prevent user spamming the echo bounce too quickly
                player->ext.spikes.echoCooldown = 0x40;
            }
        }

        prim = self->ext.spikes.prim;
        if (echo_flag) {
            UpdatePrimEcho(prim, 12);
        } else {
            UpdatePrimNormal(prim, 6);
        }
        FntPrint("echo_flag %x\n", echo_flag);
        break;
    }

    if (g_CastleFlags[CAT_SPIKE_ROOM_LIT]) {
        DestroyEntity(self);
    }
}
