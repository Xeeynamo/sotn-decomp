REDACTED
#include "sfx.h"
REDACTED
REDACTED
    s32 temp_s1;
    s16 primIndex;
    Primitive* prim;
REDACTED
REDACTED
    temp_s1 = self->hitFlags;
REDACTED
REDACTED
        InitializeEntity(g_EInitGeneric);
        self->ext.generic.unk80.modeS32 =
            self->posY.i.hi + g_Tilemap.scrollY.i.hi;
REDACTED
REDACTED
REDACTED
        self->hitboxState = 1;
REDACTED
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
REDACTED
        self->primIndex = primIndex;
        self->ext.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
REDACTED
REDACTED
        prim->u0 = 72;
        prim->v0 = 200;
        prim->u1 = 16;
        prim->v1 = 16;
        prim->priority = 0x5F;
        prim->type = PRIM_SPRT;
        prim->drawMode = DRAW_UNK02;
REDACTED
        if (temp_s1) {
            self->posY.val += FIX(1.0);
            y = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
REDACTED
REDACTED
                                        (g_Tilemap.scrollY.i.hi - 4));
REDACTED
                PlaySfxPositional(SFX_SWITCH_CLICK);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (!temp_s1) {
REDACTED
            y = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
REDACTED
REDACTED
                                  g_Tilemap.scrollY.i.hi;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    prim->x0 = self->posX.i.hi - 8;
REDACTED
    prim->y0 = prim->y0 - 8;
REDACTED
