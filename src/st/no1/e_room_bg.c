// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

extern EInit g_EInitCommon;

static u8 anim0[] = {64, 1, -1, 0};
static u8 anim1[] = {64, 59, -1, 0};
static u8 anim2[] = {64, 60, -1, 0};
static u8 anim3[] = {1, 72, -1, 0};
static u8 anim4[] = {8, 68, 8, 69, 8, 70, 0, 0};
static u8 anim5[] = {64, 87, -1, 0};
static u8 anim6[] = {64, 113, -1, 0};
static u8 anim7[] = {64, 81, -1, 0};
static u8 anim8[] = {64, 73, -1, 0};
static u8 anim9[] = {64, 88, -1, 0};
static u8 anim10[] = {64, 89, -1, 0};
static u8 anim11[] = {4, 30, -1, 0};

static ObjInit2 OVL_EXPORT(BackgroundBlockInit)[] = {
    // Life/heart max up text
    {ANIMSET_DRA(6), 0x1FA, 0x00, 0, 0x000, 0, BLEND_TRANSP, 0, anim0},
    // The hanging skeleton with the rope
    {ANIMSET_OVL(1), 0x07F, 0x00, 0, 0x000, 0, BLEND_NO, 0, anim1},
    // The little piece of rope around the column that the skeleton is tied to
    {ANIMSET_OVL(1), 0x07F, 0x00, 0, 0x000, 0, BLEND_NO, 0, anim2},
    // Tile where the elevator cable goes into the stone
    {ANIMSET_OVL(1), 0x070, 0x00, 0, 0x000, 0, BLEND_NO, 0, anim3},
    // The gears to the right of the elevator
    {ANIMSET_OVL(1), 0x080, 0x00, 0, 0x000, 0, BLEND_NO, 0, anim4},
    // A medium sized stone tile
    {ANIMSET_OVL(1), 0x08A, 0x00, 0, 0x000, 0, BLEND_NO, 0, anim5},
    // The very dark bricks in the background creating the illusion of depth
    {ANIMSET_OVL(1), 0x056, 0x00, 0, 0x000, 0, BLEND_NO, 0, anim6},
    // A large stone tile with "seam" in it
    {ANIMSET_OVL(1), 0x070, 0x00, 0, 0x000, 0, BLEND_NO, 0, anim7},
    // A small stone tile
    {ANIMSET_OVL(1), 0x070, 0x00, 0, 0x000, 0, BLEND_NO, 0, anim8},
    // long instance of rain against wall
    {ANIMSET_OVL(1), 0x07F, 0x00, 0, 0x000, 0, BLEND_NO, 0, anim9},
    // short instance of rain against wall
    {ANIMSET_OVL(1), 0x07F, 0x00, 0, 0x000, 0, BLEND_NO, 0, anim10},
    // mist door
    {ANIMSET_OVL(4), 0x064, 0x4A, 0, 0x207, 0, BLEND_NO, 0, anim11},
};

void OVL_EXPORT(EntityBackgroundBlock)(Entity* self) {
    ObjInit2* objInit = &OVL_EXPORT(BackgroundBlockInit)[self->params];

    Primitive* prim;
    s32 primIndex;

    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = objInit->animSet;
        self->zPriority = objInit->zPriority;
#ifdef VERSION_PSP
        objInit->facingLeft; // For match on PSP
        self->unk5A = LOHU(objInit->facingLeft);
#else
        self->unk5A = LOH(objInit->facingLeft);
#endif
        self->palette = objInit->palette;
        self->drawFlags = objInit->drawFlags;
        self->blendMode = objInit->blendMode;
        if (objInit->flags) {
            self->flags = objInit->flags;
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
    AnimateEntity(objInit->animFrames, self);
    FntPrint("pri:%x\n", self->zPriority);
}
