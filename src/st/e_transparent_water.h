// SPDX-License-Identifier: AGPL-3.0-or-later
#define UVWH(u, v, w, h) u, v, w, h

static u8 transWaterCluts[] = {
    0x24, 0x1A, 0x21, 0x1A, 0x2B, 0x1B, 0x22, 0x1B, 0x2C, 0x1C, 0x23,
    0x1C, 0x2D, 0x1D, 0x24, 0x1D, 0x2E, 0x1E, 0x25, 0x1E, 0x2F, 0x1F,
    0x26, 0x1F, 0x56, 0x20, 0x21, 0x20, 0xFF, 0x00, 0x00, 0x00};
static u8 transWaterUV[] = {
    UVWH(0xA1, 0x01, 0x26, 0x3E), UVWH(0xC9, 0x01, 0x26, 0x3E),
    UVWH(0xA1, 0x41, 0x26, 0x3E)};
static u8 transWaterAnim[] = {10, 0, 10, 1, 10, 2, 10, 1, 0, 0, 0, 0};
// Transparent water plane that can be seen in the merman room
void EntityTransparentWater(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    u32 selfY;
    s32 uCoord;
    s32 vCoord;
    u8* uvPtr;
    u8* clutIdx;
    s32 prim_xPos;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->ext.transparentWater.unk80 = 4;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 16);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.transparentWater.prim = prim;
        while (prim != NULL) {
            prim->tpage = 0xF;
            prim->clut = 0x18;
            prim->priority = 0xB0;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        break;

    case 1:
        clutIdx = &transWaterCluts[0];
        while (*clutIdx != 0xFF) {
            g_ClutIds[clutIdx[0]] = g_ClutIds[clutIdx[2] + 0x200];
            clutIdx += 4;
        }

        if (!--self->ext.transparentWater.unk80) {
            self->ext.transparentWater.unk80 = 4;
            self->step++;
        }
        break;

    case 2:
        clutIdx = &transWaterCluts[0];
        while (*clutIdx != 0xFF) {
            g_ClutIds[clutIdx[0]] = g_ClutIds[clutIdx[3] + 0x200];
            clutIdx += 4;
        }

        if (!--self->ext.transparentWater.unk80) {
            self->ext.transparentWater.unk80 = 4;
            self->step--;
        }
        break;
    }

    AnimateEntity(transWaterAnim, self);

    prim_xPos = -1 * g_Tilemap.scrollX.i.hi % 38;
    prim_xPos += 304;
    if (self->params) {
        prim_xPos = 96;
    }

    uvPtr = transWaterUV;
    uvPtr += 4 * self->animCurFrame;
    uCoord = uvPtr[0];
    vCoord = uvPtr[1];
    selfY = self->posY.i.hi;
    prim = self->ext.transparentWater.prim;
    while (prim_xPos > 0) {
        prim->u0 = prim->u2 = uCoord;
        prim->u1 = prim->u3 = uCoord + 0x26;
        prim->v0 = prim->v1 = vCoord;
        prim->v2 = prim->v3 = vCoord + 0x3E;
        prim->x1 = prim->x3 = prim_xPos;
        prim_xPos -= 0x26;
        prim->x0 = prim->x2 = prim_xPos;
        prim->y0 = prim->y1 = selfY;
        prim->y2 = prim->y3 = selfY + 0x3E;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        prim = prim->next;
    }

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}
