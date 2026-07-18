// SPDX-License-Identifier: AGPL-3.0-or-later
#include <libgte.h>
#include <scratchpad.h>
#include "clock_tower.h"

extern EInit g_EInitInteractable;

#if !defined(INVERTED_STAGE)
#define UP +
#define DOWN -
#define POSX_3D 0x700
#define POSY_3D 0x3C0
#define ROTZ_3D 0
#else
#define UP -
#define DOWN +
#define POSX_3D 0x100
#define POSY_3D 0x440
#define ROTZ_3D 0x800
#endif

static ClockTowerData s_RoofTextureData[] = {
    {0x10, 0x29, 0x02, 0x44, 0x1E, 0x44, 0x40},
    {0x30, 0x29, 0x22, 0x44, 0x3E, 0x44, 0x40},
    {0x15, 0x4C, 0x03, 0x6F, 0x26, 0x6F, 0x3E},
};

static ClockTowerData2 s_TowerTextureData[] = {
    {0x02, 0x02, 0x3C, 0x24, 0x3E}, {0x41, 0x01, 0x3D, 0x75, 0x44},
    {0x81, 0x01, 0x3D, 0x75, 0x44}, {0x01, 0x71, 0x3D, 0x0D, 0x44},
    {0x01, 0x71, 0x3D, 0x0D, 0x45}, {0xC1, 0x01, 0x25, 0x3D, 0x44},
    {0xC1, 0x41, 0x25, 0x3D, 0x44},
};

// these are unique sets of vertexes which are used to build
// the clock tower. each contains all of the points needed to
// build one "feature" of the clock tower (one of 5 roof sections,
// clock section, tower, etc.)
static SVECTOR D_801821C8[] = {
    {0, -182, 65},  {0, -182, -65}, {-65, -99, -65},
    {-65, -99, 65}, {65, -99, 65},  {65, -99, -65},
};
static SVECTOR D_801821F8[] = {
    {83, -163, -82}, {65, -99, -99}, {65, -99, -65},
    {99, -99, -99},  {99, -99, -65},
};
static SVECTOR D_80182220[] = {
    {83, -163, 82}, {65, -99, 66}, {65, -99, 99}, {99, -99, 66}, {99, -99, 99},
};
static SVECTOR D_80182248[] = {
    {-83, -163, -82}, {-99, -99, -99}, {-99, -99, -65},
    {-65, -99, -99},  {-65, -99, -65},
};
static SVECTOR D_80182270[] = {
    {-82, -163, 82}, {-99, -99, 65}, {-99, -99, 99},
    {-65, -99, 65},  {-65, -99, 99},
};
static SVECTOR D_80182298[] = {
    {-99, 83, 99},   {-99, -100, 99}, {-99, -100, -99}, {-99, 83, -99},
    {99, -100, -99}, {99, 83, -99},   {99, -100, 99},   {99, 83, 99},
};
static SVECTOR D_801822D8[] = {
    {-99, 83, 99},  {-99, 83, -99},  {99, 83, -99},  {99, 83, 99},
    {-65, 116, 65}, {-65, 116, -65}, {65, 116, -65}, {65, 116, 65},
};
static SVECTOR D_80182318[] = {
    {-65, 283, 65}, {-65, 116, 65}, {-65, 116, -65}, {-65, 283, -65},
    {65, 116, -65}, {65, 283, -65}, {65, 116, 65},   {65, 283, 65},
};
static SVECTOR D_80182358[] = {
    {-65, 450, 65}, {-65, 283, 65}, {-65, 283, -65}, {-65, 450, -65},
    {65, 283, -65}, {65, 450, -65}, {65, 283, 65},   {65, 450, 65},
};

static SVECTOR D_801818C8[] = {
    {-65, 616, 65}, {-65, 450, 65}, {-65, 450, -65}, {-65, 616, -65},
    {65, 450, -65}, {65, 616, -65}, {65, 450, 65},   {65, 616, 65}};

static SVECTOR D_80181908[] = {
    {-65, 783, 65}, {-65, 616, 65}, {-65, 616, -65}, {-65, 783, -65},
    {65, 616, -65}, {65, 783, -65}, {65, 616, 65},   {65, 783, 65}};

static SVECTOR D_80181948[] = {
    {-65, 983, 65}, {-65, 783, 65}, {-65, 783, -65}, {-65, 983, -65},
    {65, 783, -65}, {65, 983, -65}, {65, 783, 65},   {65, 983, 65}};

// clocktower roof
static u8 s_ClockRoofScript[] = {
    // clang-format off
    VINDEX(1),
    DRAW_TRIANGLE(1, 0, 3, 1, 1),
    DRAW_TRIANGLE(0, 0, 4, 3, 0),
    VINDEX(2),
    DRAW_TRIANGLE(1, 0, 3, 1, 1),
    DRAW_TRIANGLE(0, 0, 4, 3, 0),
    VINDEX(3),
    DRAW_TRIANGLE(1, 0, 3, 1, 4),
    DRAW_TRIANGLE(0, 0, 1, 2, 3),
    VINDEX(4),
    DRAW_TRIANGLE(1, 0, 3, 1, 0),
    DRAW_TRIANGLE(0, 0, 1, 2, 0),
    VINDEX(0),
    DRAW_TRIANGLE(2, 1, 5, 2, 2),
    OBJ_END,
    // clang-format on
};

// clocktower clock and base
static u8 s_ClockTowerScript[] = {
    // clang-format off
    VINDEX(0),
    DRAW_QUAD(0, 0, 1, 3, 2, 2),
    VINDEX(5),
    DRAW_QUAD(2, 2, 4, 3, 5, 5),
    DRAW_QUAD(1, 1, 2, 0, 3, 5),
    DRAW_QUAD(2, 1, 6, 2, 4, 0),
    VINDEX(6),
    DRAW_QUAD(3, 0, 1, 4, 5, 5),
    DRAW_QUAD(4, 1, 2, 5, 6, 5),
    VINDEX(7),
    DRAW_QUAD(6, 2, 4, 3, 5, 5),
    DRAW_QUAD(5, 1, 2, 0, 3, 5),
    VINDEX(8),
    DRAW_QUAD(6, 2, 4, 3, 5, 5),
    DRAW_QUAD(5, 1, 2, 0, 3, 5),
    VINDEX(9),
    DRAW_QUAD(6, 2, 4, 3, 5, 5),
    DRAW_QUAD(5, 1, 2, 0, 3, 5),
    VINDEX(10),
    DRAW_QUAD(6, 2, 4, 3, 5, 5),
    DRAW_QUAD(5, 1, 2, 0, 3, 5),
    VINDEX(11),
    DRAW_QUAD(6, 2, 4, 3, 5, 5),
    DRAW_QUAD(5, 1, 2, 0, 3, 5),
    OBJ_END,
    // clang-format on
};

SVECTOR* s_ClockVertexSets[] = {
    D_801821C8, D_801821F8, D_80182220, D_80182248, D_80182270, D_80182298,
    D_801822D8, D_80182318, D_80182358, D_801818C8, D_80181908, D_80181948};

void EntityClockTower3D(Entity* self) {
    SVECTOR rotVector;
    VECTOR transVector;
    MATRIX matrix;
    s32 unusedHalfZ;         // s8
    s32 unusedScratch0;      // s7
    s32 unusedScratch4;      // s6
    s32 primIndex;           // s5
    SVECTOR* vectors;        // s4
    ClockTowerData2* var_s3; // s3
    ClockTowerData* var_s2;  // s2
    u8* script;              // s1
    Primitive* prim;         // s0

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);

        self->posX.i.hi = POSX_3D - g_Tilemap.scrollX.i.hi;
        self->posY.i.hi = POSY_3D - g_Tilemap.scrollY.i.hi;

        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x28);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.clockTower.prim = prim;
        while (prim != NULL) {
            prim->tpage = 0xF;
            PGREY(prim, 0) = 0x80;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim = prim->next;
        }
    }

    SetGeomScreen(0x300);
    SetGeomOffset(0x80, 0x80);
    rotVector.vx = 0;
    rotVector.vy = DOWN 0x90;
    rotVector.vz = ROTZ_3D;
    rotVector.vx += self->ext.clockTower.unk9C;
    rotVector.vy += self->ext.clockTower.unk9E;
    rotVector.vz += self->ext.clockTower.unkA0;
    RotMatrix(&rotVector, &matrix);
    SetRotMatrix(&matrix);
    transVector.vx = self->posX.i.hi - 0x80;
    transVector.vy = self->posY.i.hi - 0x80;
    transVector.vz = 0x580;
    transVector.vz += self->ext.clockTower.unkAE;
    TransMatrix(&matrix, &transVector);
    SetTransMatrix(&matrix);

    // These variables are unused and get stripped by optimisations on PSX
    unusedHalfZ = transVector.vz / 2;
    // Weird, we allocate two 32-bit values (could be pointers, idk) on
    // scratchpad but we never end up using them. These are orphan variables.
    unusedScratch0 = (s32)SP(0);
    unusedScratch4 = (s32)SP(sizeof(s32));

    prim = self->ext.clockTower.prim;
    script = s_ClockRoofScript;
    while (*script != OBJ_END) {
        if (*script & VINDEX_MARKER) {
            vectors = s_ClockVertexSets[script[1]];
            script += 2;
        }
        var_s2 = &s_RoofTextureData[0];
        var_s2 += *script++;
        prim->u0 = var_s2->u0;
        prim->v0 = var_s2->v0;
        prim->u1 = var_s2->u1;
        prim->v1 = var_s2->v1;
        prim->u2 = var_s2->u2;
        prim->v2 = var_s2->v2;
        prim->clut = var_s2->clut;
        prim->type = PRIM_GT3;
        gte_ldv3(&vectors[script[0]], &vectors[script[1]], &vectors[script[2]]);
        gte_rtpt();
        gte_stsxy3_gt3(prim);
        prim->drawMode = DRAW_UNK02;
        prim->priority = script[3] + 0x40;
        script += 4;
        prim = prim->next;
    }

    script = s_ClockTowerScript;
    while (*script != OBJ_END) {
        if (*script & VINDEX_MARKER) {
            vectors = s_ClockVertexSets[script[1]];
            script += 2;
        }
        var_s3 = &s_TowerTextureData[0];
        var_s3 += (*script++);
        prim->u0 = prim->u2 = var_s3->u;
        prim->v0 = prim->v1 = var_s3->v;
        prim->u1 = prim->u3 = var_s3->u + var_s3->w;
        prim->v2 = prim->v3 = var_s3->v + var_s3->h;
        prim->clut = var_s3->clut;
        prim->type = PRIM_GT4;
        gte_ldv3(&vectors[script[0]], &vectors[script[1]], &vectors[script[2]]);
        gte_rtpt();
        gte_stsxy3_gt3(prim);
        gte_ldv0(&vectors[script[3]]);
        gte_rtps();
        gte_stsxy((long*)&prim->x3);
        prim->priority = script[4] + 0x40;
        prim->drawMode = DRAW_UNK02;
        script += 5;
        prim = prim->next;
    }

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}
