// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno1/rno1.h"

void func_us_801B9028_from_no1(Entity* self) {
    extern u16 D_us_8018076C[];
    extern u16 D_us_80180D44[];
    extern u16 D_us_80180D58[];
    extern char D_us_801A5C70;

    switch (self->step) {
    case 0: {
        InitializeEntity(D_us_8018076C);
        self->animCurFrame = self->params + 1;
        self->zPriority = D_us_80180D44[self->params];
        self->drawFlags = ENTITY_OPACITY;
        self->opacity = D_us_80180D58[self->params];
        break;
    }

    case 1:
        break;

    case 2:
#define PAD2_ANIM_DEBUG_PRINT() FntPrint(&D_us_801A5C70, self->animCurFrame)
#define PAD2_ANIM_DEBUG_ABORT return
#include "../pad2_anim_debug.h"
    }
}

void func_us_801B8F50_from_no1(Entity* self) {
    extern u16 D_us_8018073C;
    extern u8 D_us_80180BF8[];
    extern void* D_us_80180C04[];
    void* anim;

    switch (self->step) {
    case 0:
        InitializeEntity(&D_us_8018073C);
        self->animCurFrame = D_us_80180BF8[self->params];
        self->zPriority = 0x6A;
        break;

    case 1:
        if (g_CastleFlags[NO1_ELEVATOR_ACTIVATED]) {
            self->step += 1;
        }
        break;

    case 2:
        anim = D_us_80180C04[self->params];
        AnimateEntity(anim, self);
        break;
    }
}

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
