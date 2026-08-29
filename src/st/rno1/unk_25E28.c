// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno1.h"

typedef struct {
    /* 0x00 */ u16 animSet;
    /* 0x02 */ u16 zPriority;
    /* 0x04 */ u16 unk5A;
    /* 0x06 */ u16 palette;
    /* 0x08 */ u16 drawFlags;
    /* 0x0A */ u16 blendMode;
    /* 0x0C */ u32 flags;
    /* 0x10 */ u8* animFrames;
} Rno1BackgroundBlockInit; // size = 0x14

extern Rno1BackgroundBlockInit BackgroundBlockInit[];
extern EInit g_EInitCommon;

void EntityBackgroundBlock(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    Rno1BackgroundBlockInit* init;

    init = &BackgroundBlockInit[self->params];

    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = init->animSet;
        self->zPriority = init->zPriority;
        self->unk5A = init->unk5A;
        self->palette = init->palette;
        self->drawFlags = init->drawFlags;
        self->blendMode = init->blendMode;
        if (init->flags) {
            self->flags = init->flags;
        }

        if (self->params == 6) {
            primIndex = (s16)g_api_AllocPrimitives(PRIM_TILE, 1);
            if (primIndex == -1) {
                DestroyEntity(self);
                return;
            }

            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            prim->u0 = 0x30;
            prim->v0 = 0x50;
            prim->r0 = prim->g0 = prim->b0 = 0x10;
            prim->x0 = self->posX.i.hi - 0x30;
            prim->y0 = self->posY.i.hi - 0x28;
            prim->priority = self->zPriority - 1;
            prim->drawMode = DRAW_UNK02;
        }
    }

    AnimateEntity(init->animFrames, self);
}
