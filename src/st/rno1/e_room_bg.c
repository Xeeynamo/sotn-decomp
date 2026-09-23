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
    /* 0x10 */ AnimateEntityFrame* animFrames;
} Rno1BackgroundBlockInit; // size = 0x14

static AnimateEntityFrame anim1[] = {{64, 2}, POSE_END};
static AnimateEntityFrame anim2[] = {{64, 59}, POSE_END};
static AnimateEntityFrame anim3[] = {{64, 60}, POSE_END};
static AnimateEntityFrame anim4[] = {{1, 72}, POSE_END};
// Looks like a mistake? Kind of weird here
static AnimateEntityFrame anim5[] = {
    {8, 68}, POSE_END, {8, 69}, {8, 70}, POSE_LOOP(0)};
static AnimateEntityFrame anim7[] = {{64, 87}, POSE_END};
static AnimateEntityFrame anim8[] = {{64, 113}, POSE_END};
static AnimateEntityFrame anim9[] = {{64, 81}, POSE_END};
static AnimateEntityFrame anim10[] = {{64, 73}, POSE_END};
static AnimateEntityFrame anim11[] = {{64, 88}, POSE_END};
static AnimateEntityFrame anim12[] = {{64, 89}, POSE_END};
static AnimateEntityFrame anim13[] = {{4, 30}, POSE_END};
static AnimateEntityFrame anim14[] = {{4, 31}, POSE_END};
static AnimateEntityFrame anim15[] = {{4, 67}, POSE_END};

Rno1BackgroundBlockInit BackgroundBlockInit[] = {
    {0x0006, 506, 0, 0x0000, 0x0000, 16, 0, anim1},
    {0x8002, 127, 0, 0x0000, 0x0000, 0, 0, anim2},
    {0x8002, 127, 0, 0x0000, 0x0000, 0, 0, anim3},
    {0x8002, 112, 0, 0x0000, 0x0000, 0, 0, anim4},
    {0x8002, 128, 0, 0x0000, 0x0000, 0, 0, anim5},
    {0x8002, 138, 0, 0x0000, 0x0000, 0, 0, anim7},
    {0x8002, 86, 0, 0x0000, 0x0000, 0, 0, anim8},
    {0x8002, 112, 0, 0x0000, 0x0000, 0, 0, anim9},
    {0x8002, 112, 0, 0x0000, 0x0000, 0, 0, anim10},
    {0x8002, 127, 0, 0x0000, 0x0000, 0, 0, anim11},
    {0x8002, 127, 0, 0x0000, 0x0000, 0, 0, anim12},
    {0x8008, 100, 79, 0x0219, 0x0000, 0, 0, anim13},
    {0x8008, 106, 79, 0x0219, 0x0000, 0, 0, anim14},
    {0x8002, 106, 0, 0x0000, 0x0000, 0, 0, anim15},
};
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
            primIndex = g_api.AllocPrimitives(PRIM_TILE, 1);
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
