// SPDX-License-Identifier: AGPL-3.0-or-later
#include "are.h"

extern EInit g_EInitInteractable;

typedef struct {
    // These are possibly coordinates on the spritesheet?
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    s16 posX;
    s16 posY;
} BackgroundDoorRubbleConfig;

static BackgroundDoorRubbleConfig door_rubble_config[] = {
    {0x84, 0x03, 0x03, 0x84, 0x0100, 0x0040},
    {0x03, 0x03, 0x84, 0x84, 0x01C0, 0x0040},
    {0x84, 0x03, 0x03, 0x84, 0x0340, 0x0040},
    {0x84, 0x03, 0x03, 0x84, 0x0100, 0x0140},
    {0x03, 0x03, 0x84, 0x84, 0x0340, 0x0140},
    {0x03, 0x03, 0x84, 0x84, 0x0130, 0x0040},
    {0x84, 0x03, 0x03, 0x84, 0x0260, 0x0040},
    {0x00, 0x03, 0xFF, 0x84, 0x01D0, 0x0140},
};

void EntityBackgroundDoorRubble(Entity* self) {
    Primitive* prim;
    BackgroundDoorRubbleConfig* config;
    s32 primIndex;
    s32 var_s3;
    s32 var_s4;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        config = &door_rubble_config[self->params];
        prim->tpage = 0xE;
        // Used for the wider room with the beast skull
        if (self->params == 7) {
            prim->tpage += 1;
        }
        prim->clut = PAL_BACKGROUND_DOOR_RUBBLE;
        prim->u0 = prim->u2 = config->unk0;
        prim->u1 = prim->u3 = config->unk2;
        prim->v0 = prim->v1 = config->unk1;
        prim->v2 = prim->v3 = config->unk3;
        var_s3 = abs(config->unk0 - config->unk2);
        var_s4 = abs(config->unk1 - config->unk3);
        prim->x0 = prim->x2 = config->posX - g_Tilemap.scrollX.i.hi;
        prim->x1 = prim->x3 = prim->x0 + var_s3;
        prim->y0 = prim->y1 = config->posY - g_Tilemap.scrollY.i.hi;
        prim->y2 = prim->y3 = prim->y0 + var_s4;
        prim->priority = 0x68;
        prim->drawMode = DRAW_UNK02;
        // fallthrough
    case 1:
        // BUG! This is unused
        prim = self->ext.prim;
        break;
    }
}
