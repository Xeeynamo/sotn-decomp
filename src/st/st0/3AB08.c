// SPDX-License-Identifier: AGPL-3.0-or-later
#include "st0.h"
#include <scratchpad.h>
#include <sfx.h>
#include "../clock_tower.h"

static s16 D_80182084[] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0xC181, 0xC1BE, 0xDE81, 0xDEBE, 0xE181,
    0xE1BE, 0xFE81, 0xFEBE, 0xC181, 0xC1BE, 0xDE81, 0xDEBE, 0xE181, 0xE1BE,
    0xFE81, 0xFEBE, 0x8181, 0x81BE, 0xA081, 0xA0BE, 0xA081, 0xA0BE, 0xBE81,
    0xBEBE, 0x81C1, 0x81FE, 0xA0C1, 0xA0FE, 0xA0C1, 0xA0FE, 0xBEC1, 0xBEFE};
static SVECTOR cloudVectorOne = {-128, 0, 0};
static SVECTOR cloudVectorTwo = {128, 0, 0};
static SVECTOR cloudVectorThree = {-128, 0, 256};
static SVECTOR cloudVectorFour = {128, 0, 256};
static u8 D_801820EC[] = {
    0x05, 0x00, 0x07, 0x00, 0x00, 0x08, 0x00, 0x00, 0x06, 0x00, 0x08,
    0x05, 0x00, 0x00, 0x07, 0x05, 0x00, 0x05, 0x00, 0x06, 0x05, 0x00,
    0x08, 0x06, 0x00, 0x06, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x05,
    0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x07, 0x06, 0x05, 0x00, 0x08,
    0x00, 0x05, 0x05, 0x08, 0x00, 0x06, 0x00, 0x05, 0x05, 0x06, 0x06,
    0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x07, 0x00, 0x00};
static u8 D_8018212C[] = {
    0x04, 0x03, 0x03, 0x04, 0x02, 0x04, 0x03, 0x04, 0x01, 0x03, 0x02,
    0x03, 0x04, 0x02, 0x02, 0x04, 0x03, 0x02, 0x02, 0x03, 0x02, 0x04,
    0x03, 0x04, 0x02, 0x02, 0x04, 0x03, 0x01, 0x03, 0x02, 0x04, 0x01,
    0x01, 0x02, 0x01, 0x04, 0x04, 0x04, 0x04, 0x03, 0x02, 0x02, 0x03,
    0x02, 0x01, 0x02, 0x02, 0x01, 0x02, 0x02, 0x02, 0x03, 0x04, 0x02,
    0x02, 0x03, 0x03, 0x04, 0x02, 0x02, 0x04, 0x03, 0x04};
static cloudData data[] = {
    {.unkPtr = D_801820EC, .unk4 = 0xFEE0, .priority = 0x1C},
    {.unkPtr = D_8018212C, .unk4 = 0x00C0, .priority = 0x18}};
#ifdef VERSION_PSP
extern E_ID(ID_2D);
extern SVECTOR empty; // bss on PSP
#else
static SVECTOR empty = {0, 0, 0};
#endif

void EntityClouds(Entity* self) {
#ifdef VERSION_PC
    u8 sp[SP_LEN];
#endif
    Primitive* prim;
    s16* var_s1;
    s32 var_s2;
    u8* var_s3;
    s32 i;
    s32 j;
    Primitive* primTwo;
    s32* var_s7;

    s32 sp5C;
    s32 sp58;
    s32 priority;
    s32 primIndex;
    s32 sp4C;
    s32 posX;
    s32 sp44;
    long sp40;
    MATRIX* matrix;
    u8* sp38;
    cloudStructUnk* cloudStruct;
    cloudData* cloudData;
    SVECTOR* vector;

    if (!self->step) {
        InitializeEntity(g_EInit3DObject);
        primIndex = g_api.func_800EDB58(PRIM_GT4, 0x70);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.clouds.prim = prim;
        prim->tpage = 0xF;
        prim->clut = 0x46;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x65;
        prim->v0 = prim->v1 = 0x80;
        prim->v2 = prim->v3 = 0xFB;
        prim->x0 = prim->x2 = 0x4B;
        prim->x1 = prim->x3 = 0xB0;
        prim->y0 = prim->y1 = 0;
        prim->y2 = prim->y3 = 0x7B;

        self->ext.clouds.unk9C.i.hi = 0x4B;
        self->ext.clouds.unkA0.i.hi = 0;
        prim->priority = 4;
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        while (prim != NULL) {
            prim->tpage = 0xF;
            prim->clut = 0x226;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }

    self->ext.clouds.unk84.val += FIX(3);
    self->ext.clouds.unk8C += FIX(8);
    self->ext.clouds.unk88 += FIX(8);
    self->ext.clouds.unk90 += FIX(4);

    g_GpuBuffers[0].draw.r0 = 0x10;
    g_GpuBuffers[0].draw.g0 = 8;
    g_GpuBuffers[0].draw.b0 = 0x20;
    g_GpuBuffers[1].draw.r0 = 0x10;
    g_GpuBuffers[1].draw.g0 = 8;
    g_GpuBuffers[1].draw.b0 = 0x20;

    matrix = (MATRIX*)SP(0);
    primTwo = (Primitive*)SP(0x20);
    vector = (SVECTOR*)SP(0x60);
    vector[0] = cloudVectorOne;
    vector[1] = cloudVectorTwo;
    vector[2] = cloudVectorThree;
    vector[3] = cloudVectorFour;

    var_s7 = (s32*)SP(0x80);
    var_s1 = D_80182084;
    for (i = 0; i < 0x24; i++, var_s7++, var_s1++) {
        *var_s7 = *var_s1;
    }

    var_s3 = (u8*)SP(0x200);
    var_s3[3] = 4;
    var_s3[7] = 4;

    SetGeomScreen(256);
    SetGeomOffset(128, 160);
    RotMatrix(&empty, matrix);
    SetRotMatrix(matrix);
    cloudData = data;
    var_s1 = &self->ext.clouds.unk84.i.hi;
    prim = self->ext.clouds.prim;
    if (g_Timer & 1) {
        prim->clut = 0x46;
    } else {
        prim->clut = 0x47;
    }

    self->ext.clouds.unk9C.val -= (g_ScrollDeltaX << 0x10) / 6;
    self->ext.clouds.unkA0.val -= (g_ScrollDeltaY << 0x10) / 6;

    prim->x0 = prim->x2 = self->ext.clouds.unk9C.i.hi;
    prim->x1 = prim->x3 = self->ext.clouds.unk9C.i.hi + 0x65;
    prim->y0 = prim->y1 = self->ext.clouds.unkA0.i.hi;
    prim->y2 = prim->y3 = self->ext.clouds.unkA0.i.hi + 0x7B;
    prim = prim->next;

    for (i = 0; i < 2; i++, cloudData++, var_s1 += 4) {
        posX = self->posX.i.hi + *var_s1;
        posX %= 0x800;
        priority = cloudData->priority;
        var_s2 = cloudData->unk4;
        var_s2 += (0x40 - g_Tilemap.scrollY.i.hi / 4);
        gte_ldty(var_s2);
        for (sp5C = 0; sp5C < 8; sp5C++) {
            var_s2 = sp5C * 0x100 + 0x1C0;
            sp40 = (u16)var_s1[2];
            var_s2 -= sp40 % 0x100;
            gte_ldtz(var_s2);
            sp40 = (sp5C + (sp40 / 0x100)) % 8;
            sp38 = (cloudData->unkPtr + sp40 * 8);
            var_s2 -= 0x1C0;

            sp4C = FIX(15) - var_s2 * 0x1A0;
            var_s3[0] = sp4C >> 12;
            var_s3[4] = (sp4C + FIX(-1.625)) >> 12;

            sp4C = FIX(15) - var_s2 * 0x1C0;
            var_s3[1] = sp4C >> 12;
            var_s3[5] = (sp4C + FIX(-1.75)) >> 12;

            sp4C = FIX(15) - var_s2 * 0x160;
            var_s3[2] = sp4C >> 12;
            var_s3[6] = (sp4C + FIX(-1.375)) >> 12;

            sp44 = posX;
            j = 0;
            sp58 = -1;
            while (1) {
                sp44 += sp58 << 8;
                j += sp58;
                j &= 7;
                var_s2 = sp38[j];
                if (var_s2 == 0) {
                    continue;
                }

                gte_ldtx(sp44);
                gte_ldv0(&vector[3]);
                gte_rtps();
                prim->drawMode = DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;

                cloudStruct = &((cloudStructUnk*)(SP(0x80)))[var_s2];
                LOH(prim->u0) = cloudStruct->unk0;
                gte_stsxy((long*)&primTwo->x3);
                gte_ldv3c(vector);
                gte_rtpt();
                if (primTwo->y3 < 0) {
                    prim->drawMode = DRAW_HIDE;
                    break;
                }
                if (primTwo->x3 < 0) {
                    prim->drawMode = DRAW_HIDE;
                    if (sp58 < 0) {
                        sp58 += 2;
                        sp44 = posX - 0x100;
                        j = 7;
                    }
                    continue;
                }
                if (var_s2 < 5) {
                    prim->clut = (g_Timer & 1) + 0x4A;
                } else {
                    prim->clut = (g_Timer & 1) + 0x48;
                }
                LOH(prim->u1) = cloudStruct->unk4;
                LOH(prim->u2) = cloudStruct->unk8;
                gte_stsxy3_gt3(primTwo);

                if (primTwo->x2 > 0x100) {
                    prim->drawMode = DRAW_HIDE;
                    if (sp58 > 0) {
                        break;
                    } else {
                        continue;
                    }
                } else {
                    LOH(prim->u3) = cloudStruct->unkC;
                    LOW(prim->x0) = LOW(primTwo->x0);
                    LOW(prim->x1) = LOW(primTwo->x1);
                    LOW(prim->x2) = LOW(primTwo->x2);
                    LOW(prim->x3) = LOW(primTwo->x3);
                    LOW(prim->r0) = LOW(prim->r1) = LOW(var_s3[0]);
                    LOW(prim->r2) = LOW(prim->r3) = LOW(var_s3[4]);
                    prim->priority = priority;
                    prim = prim->next;
                    if (prim == NULL) {
                        return;
                    }
                }
            }
        }
    }

    for (j = 0; prim != NULL; j++, prim = prim->next) {
        prim->drawMode = DRAW_HIDE;
    }
    sp44 = g_Tilemap.scrollX.i.hi + PLAYER.posX.i.hi;
    if (sp44 < 0x100) {
        DestroyEntity(self);
    }
}

static ClockTowerData s_RoofTextureData[] = {
    {0x10, 0x29, 0x02, 0x44, 0x1E, 0x44, 0x40},
    {0x30, 0x29, 0x22, 0x44, 0x3E, 0x44, 0x40},
    {0x15, 0x49, 0x02, 0x6F, 0x26, 0x6F, 0x3E},
};

static ClockTowerData2 s_TowerTextureData[] = {
    {0x01, 0x01, 0x3D, 0x25, 0x3E}, {0x41, 0x01, 0x3D, 0x75, 0x44},
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
    {82, -163, -82}, {65, -99, -99}, {65, -99, -65},
    {99, -99, -99},  {99, -99, -65},
};
static SVECTOR D_80182220[] = {
    {83, -163, 82}, {66, -99, 66}, {66, -99, 99}, {99, -99, 66}, {99, -99, 99},
};
static SVECTOR D_80182248[] = {
    {-83, -163, -82}, {-99, -99, -99}, {-99, -99, -65},
    {-66, -99, -99},  {-66, -99, -65},
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
    VINDEX(6),
    DRAW_QUAD(3, 0, 1, 4, 5, 5),
    DRAW_QUAD(4, 1, 2, 5, 6, 5),
    VINDEX(7),
    DRAW_QUAD(6, 2, 4, 3, 5, 5),
    DRAW_QUAD(5, 1, 2, 0, 3, 5),
    VINDEX(8),
    DRAW_QUAD(6, 2, 4, 3, 5, 5),
    DRAW_QUAD(5, 1, 2, 0, 3, 5),
    OBJ_END,
    // clang-format on
};

SVECTOR* s_ClockVertexSets[] = {
    D_801821C8, D_801821F8, D_80182220, D_80182248, D_80182270,
    D_80182298, D_801822D8, D_80182318, D_80182358};

void EntityClockTower3D(Entity* self) {
#ifdef VERSION_PC
    u8 sp[SP_LEN];
#endif
    s32 unusedHalfZ;
    SVECTOR rotVector;
    VECTOR transVector;
    MATRIX matrix;

    s32 unusedScratch0;
    s32 unusedScratch4;
    s32 xBase;
    s32 primIndex;
    SVECTOR* vectors;
    ClockTowerData2* var_s3;
    ClockTowerData* var_s2;
    u8* script; // not a struct, script for creating polygons
    Primitive* prim;

    if (!self->step) {
        InitializeEntity(g_EInit3DObject);
        xBase = 0x480;
        self->posX.i.hi = xBase - g_Tilemap.scrollX.i.hi;
        self->posY.i.hi = 0x80 - g_Tilemap.scrollY.i.hi;
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
    rotVector.vy = -0x90;
    rotVector.vz = 0;

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
    if ((g_Tilemap.scrollX.i.hi + PLAYER.posX.i.hi) < 0x100) {
        DestroyEntity(self);
    }
}

static u8 D_80182438[3] = {0x70, 0x50, 0x40};
#ifdef VERSION_PSP
static SVECTOR D_8018243C = {-128, -108, 0};
static SVECTOR D_80182444 = {127, -108, 0};
static SVECTOR D_8018244C = {-128, 100, 0};
static SVECTOR D_80182454 = {127, 100, 0};
#else
static SVECTOR D_8018243C = {-128, -116, 0};
static SVECTOR D_80182444 = {127, -116, 0};
static SVECTOR D_8018244C = {-128, 108, 0};
static SVECTOR D_80182454 = {127, 108, 0};
#endif
static s16 D_8018245C[] = {
    0x0080, 0x00B8, 0x0078, 0x00B0, 0x0088, 0x00B0, 0x0070, 0x00A8,
    0x0080, 0x00A8, 0x0090, 0x00A8, 0x0068, 0x00A0, 0x0078, 0x00A0,
    0x0088, 0x00A0, 0x0098, 0x00A0, 0x0060, 0x0098, 0x0070, 0x0098,
    0x0080, 0x0098, 0x0090, 0x0098, 0x00A0, 0x0098, 0x0068, 0x0090,
    0x0078, 0x0090, 0x0088, 0x0090, 0x0098, 0x0090, 0x0058, 0x0090,
    0x00A8, 0x0090, 0x0070, 0x0078, 0x0080, 0x0078, 0x0090, 0x0078,
    0x0078, 0x0070, 0x0088, 0x0070, 0x0080, 0x0068, 0xFFFF, 0xFFFF};
void EntityCutscenePhotograph(Entity* self) {
    RECT clipRect;
    DRAWENV drawEnv;
    SVECTOR rotVector;
    VECTOR transVector;
    MATRIX m;

    s32 newEntX;
    s32 newEntY;
    s32 primIndex;
    s16* newEntXY;
    s32 dualFlag; // Used in color limit system, and as facing left
    s32 i;
    DR_ENV* dr_env;
    Entity* otherEnt;
    Primitive* prim;

    // These 5 variables are not used in PSP.
    u8* colorPtr;
    u8* comparePtr;
    s32 j;
    s32 newColor;
    s32 limit;

    g_Player.demo_timer = 4;
    g_Player.padSim = 0;
    g_PauseAllowed = false;
    switch (self->step) {
    case 0:
#ifdef VERSION_PSP
        func_psp_0891B0BC(0);
#endif
        InitializeEntity(g_EInit3DObject);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
        if (primIndex == -1) {
            self->step = 0;
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.cutscenePhoto.prim = prim;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }

#ifdef VERSION_PSP
        func_psp_0891B0DC(0x300, 0);
        prim = self->ext.prim;
        prim->tpage = 0;
        self->step = 2;
        break;
    case 2:
        prim = self->ext.prim;
        if (prim->tpage == 0) {
            prim->tpage = 0x10C;
            prim->u0 = prim->u2 = 0;
            prim->u1 = prim->u3 = 0xFF;
            prim->v0 = prim->v1 = 0x14;
            prim->v2 = prim->v3 = 0x14 + 0xD0;
            prim->x0 = prim->x2 = 0;
            prim->x1 = prim->x3 = 0xFF;
            prim->y0 = prim->y1 = 0x14;
            prim->y2 = prim->y3 = 0x14 + 0xD0;
            prim->r0 = prim->g0 = prim->b0 = 0xFF;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = 0x1F8;
            prim->drawMode = DRAW_UNK_400 | DRAW_COLORS;
        }

        prim = self->ext.prim;
        drawEnv = g_CurrentBuffer->draw;
        prim->tpage = 0x10C;
        dualFlag = 1;
        if (prim->r0 > D_80182438[0] * 2) {
            prim->r0--;
            dualFlag = 0;
        }
        if (prim->g0 > D_80182438[1] * 2) {
            prim->g0--;
            dualFlag = 0;
        }
        if (prim->b0 > D_80182438[2] * 2) {
            prim->b0--;
            dualFlag = 0;
        }

        LOW(prim->r1) = LOW(prim->r2) = LOW(prim->r3) = LOW(prim->r0);

        if (dualFlag == 0) {
            return;
        }
        self->step++;
        func_psp_0891B0DC(0x300, 0);
        return;
#else
    case 1:
        prim = self->ext.cutscenePhoto.prim;
        drawEnv = g_CurrentBuffer->draw;
        if (drawEnv.ofs[0] == 0) {
            prim->tpage = 0x100;
        } else {
            prim->tpage = 0x104;
        }
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0xFF;
        prim->v0 = prim->v1 = 12;
        prim->v2 = prim->v3 = 12 + 0xE0;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0xFF;
        prim->y0 = prim->y1 = 12;
        prim->y2 = prim->y3 = 12 + 0xE0;
        prim->r0 = prim->g0 = prim->b0 = 0x80;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0x1F8;
        prim->drawMode = DRAW_UNK_400 | DRAW_COLORS;
        prim = prim->next;
        self->step++;
        // Fallthrough!
    case 2:
        prim = self->ext.cutscenePhoto.prim;
        drawEnv = g_CurrentBuffer->draw;
        if (drawEnv.ofs[0] == 0) {
            prim->tpage = 0x100;
        } else {
            prim->tpage = 0x104;
        }

        dualFlag = 1;
        comparePtr = &D_80182438[0];
        colorPtr = &prim->r0;
        // Iterate through prim r0, r1, r2, r3
        // Colors are spaced 12 bytes apart.
        for (i = 0; i < 4; i++, colorPtr += 12) {
            // Iterate through r, g, b
            for (j = 0; j < 3; j++) {
                newColor = colorPtr[j];
                newColor--;
                if (newColor < comparePtr[j]) {
                    newColor = comparePtr[j];
                } else {
                    dualFlag = 0;
                }
                colorPtr[j] = newColor;
            }
        }

        if (dualFlag == 0) {
            return;
        }
        self->step++;
        return;
#endif
    case 3:
        prim = self->ext.cutscenePhoto.prim;
        prim = prim->next;

        drawEnv = g_CurrentBuffer->draw;
#ifdef VERSION_PSP
        prim->tpage = 0x10C;
#else
        if (drawEnv.ofs[0] == 0) {
            prim->tpage = 0x100;
        } else {
            prim->tpage = 0x104;
        }
#endif
        prim->type = PRIM_GT4;
        prim->u0 = prim->u2 = 6;
        prim->u1 = prim->u3 = 0xF9;
#ifdef VERSION_PSP
        prim->v0 = prim->v1 = 26;
        prim->v2 = prim->v3 = 26 + 0xC4;
        prim->x0 = prim->x2 = 6;
        prim->x1 = prim->x3 = 0xF9;
        prim->y0 = prim->y1 = 26;
        prim->y2 = prim->y3 = 26 + 0xC4;
#else
        prim->v0 = prim->v1 = 18;
        prim->v2 = prim->v3 = 18 + 0xD4;
        prim->x0 = prim->x2 = 6;
        prim->x1 = prim->x3 = 0xF9;
        prim->y0 = prim->y1 = 18;
        prim->y2 = prim->y3 = 18 + 0xD4;
#endif
        prim->priority = 0x1FB;
        prim->drawMode = DRAW_DEFAULT;

        prim = prim->next;
        dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
        if (dr_env == NULL) {
            SetStep(12);
            return;
        }
        prim->type = PRIM_ENV;
        drawEnv.isbg = 1;
        drawEnv.r0 = 0x70;
        drawEnv.g0 = 0x70;
        drawEnv.b0 = 0x60;
        drawEnv.dtd = 0;
        clipRect.x = 0;
        clipRect.y = 0x100;
        clipRect.w = 0x100;
        clipRect.h = 0x100;
        drawEnv.clip = clipRect;
        drawEnv.ofs[0] = 0;
        drawEnv.ofs[1] = 0x100;
        SetDrawEnv(dr_env, &drawEnv);
        prim->priority = 0x1FA;
        prim->drawMode = DRAW_DEFAULT;

        prim = prim->next;
        dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
        if (dr_env == NULL) {
            SetStep(12);
            return;
        }
        prim->type = PRIM_ENV;
        prim->priority = 0x1FC;
        prim->drawMode = DRAW_UNK_800;

        prim = prim->next;
        prim->type = PRIM_G4;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0x100;
        prim->y0 = prim->y1 = 0;
        prim->y2 = prim->y3 = 0x100;
        prim->r0 = prim->g0 = prim->b0 = 8;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0x1F9;
#ifdef VERSION_PSP
        prim->drawMode = DRAW_HIDE;
#else
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
#endif
        self->step++;
        break;
    case 4:
        prim = self->ext.cutscenePhoto.prim;
        prim = prim->next;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        for (i = 0; i < 2; i++) {
            dr_env = (DR_ENV*)LOW(prim->r1);
            dr_env->tag = 0;
            prim->type = PRIM_GT4;
            prim = prim->next;
        }
        prim->drawMode = DRAW_HIDE;
        // useless line due to the following line!
        prim = prim->next;

        prim = self->ext.cutscenePhoto.prim;
        prim->tpage = 0x110;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0xFF;
#ifdef VERSION_PSP
        prim->v0 = prim->v1 = 20;
        prim->v2 = prim->v3 = 20 + 0xD0;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0xFF;
        prim->y0 = prim->y1 = 20;
        prim->y2 = prim->y3 = 20 + 0xD0;
#else
        prim->v0 = prim->v1 = 12;
        prim->v2 = prim->v3 = 12 + 0xE0;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0xFF;
        prim->y0 = prim->y1 = 12;
        prim->y2 = prim->y3 = 12 + 0xE0;
#endif
        prim->r0 = prim->g0 = prim->b0 = 0x80;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);

        prim->priority = 0x1F9;
        prim->drawMode = DRAW_DEFAULT;

        for (otherEnt = &g_Entities[1], i = 1; i < 256; i++, otherEnt++) {
            if (otherEnt != self) {
                DestroyEntity(otherEnt);
            }
        }
        PLAYER.animSet = 0;
        D_8003C744 = 5;
        g_GpuBuffers[0].draw.clip.y = 0;
        g_GpuBuffers[0].draw.clip.h = 0xF0;
        g_GpuBuffers[1].draw.clip.y = 0;
        g_GpuBuffers[1].draw.clip.h = 0xF0;
        self->rotate = 0;
        self->scaleX = 0x100;
        self->ext.cutscenePhoto.cameraDistance = 0;
        self->ext.cutscenePhoto.rotationTimer = 0x20;

        g_api.PlaySfx(SFX_EXPLODE_A);
        self->step++;
        /* fallthrough */
    case 5:
        g_GpuBuffers[0].draw.r0 = 0;
        g_GpuBuffers[0].draw.g0 = 0;
        g_GpuBuffers[0].draw.b0 = 0;
        g_GpuBuffers[1].draw.r0 = 0;
        g_GpuBuffers[1].draw.g0 = 0;
        g_GpuBuffers[1].draw.b0 = 0;
        prim = self->ext.cutscenePhoto.prim;
        SetGeomScreen(0x400);
        SetGeomOffset(0x80, 0x80);
        rotVector.vx = 0;
        rotVector.vy = 0;
        rotVector.vz = self->rotate;
        RotMatrix(&rotVector, &m);
        SetRotMatrix(&m);
        transVector.vx = 0;
        transVector.vy = 0;
        transVector.vz = 0x400;
        transVector.vz += self->ext.cutscenePhoto.cameraDistance;
        TransMatrix(&m, &transVector);
        SetTransMatrix(&m);
        gte_ldv3(&D_8018243C, &D_80182444, &D_8018244C);
        gte_rtpt();
        gte_stsxy3_gt3(prim);
        gte_ldv0(&D_80182454);
        gte_rtps();
        gte_stsxy((long*)&prim->x3);

        if (!self->ext.cutscenePhoto.rotationTimer) {
            self->rotate += 2;
            self->ext.cutscenePhoto.cameraDistance += 8;
        } else {
            self->ext.cutscenePhoto.rotationTimer--;
        }
        if (self->ext.cutscenePhoto.cameraDistance <= 0x600) {
            return;
        }
        self->step++;
#ifdef VERSION_PSP
        func_psp_0891B0DC(0x300, 0);
#endif
        return;
    case 6:
        prim = self->ext.cutscenePhoto.prim;
        prim = prim->next;

        drawEnv = g_CurrentBuffer->draw;
#ifdef VERSION_PSP
        prim->tpage = 0x10C;
#else
        if (drawEnv.ofs[0] == 0) {
            prim->tpage = 0x100;
        } else {
            prim->tpage = 0x104;
        }
#endif
        prim->type = PRIM_GT4;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0xFF;
#ifdef VERSION_PSP
        prim->v0 = prim->v1 = 20;
        prim->v2 = prim->v3 = 20 + 0xD0;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0xFF;
        prim->y0 = prim->y1 = 20;
        prim->y2 = prim->y3 = 20 + 0xD0;
#else
        prim->v0 = prim->v1 = 12;
        prim->v2 = prim->v3 = 12 + 0xE0;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0xFF;
        prim->y0 = prim->y1 = 12;
        prim->y2 = prim->y3 = 12 + 0xE0;
#endif
        prim->priority = 0x1FB;
        prim->drawMode = DRAW_DEFAULT;

        prim = prim->next;
        dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
        if (dr_env == NULL) {
            SetStep(12);
            return;
        }
        prim->type = PRIM_ENV;
        drawEnv.isbg = 1;
        drawEnv.r0 = 8;
        drawEnv.g0 = 8;
        drawEnv.b0 = 8;
        drawEnv.dtd = 1;
        clipRect.x = 0;
        clipRect.y = 0x100;
        clipRect.w = 0x100;
        clipRect.h = 0x100;
        drawEnv.clip = clipRect;
        drawEnv.ofs[0] = 0;
        drawEnv.ofs[1] = 0x100;
        SetDrawEnv(dr_env, &drawEnv);
        prim->priority = 0x1FA;
        prim->drawMode = DRAW_DEFAULT;

        prim = prim->next;
        dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
        if (dr_env == NULL) {
            SetStep(12);
            return;
        }
        prim->type = PRIM_ENV;
        prim->priority = 0x1FD;
        prim->drawMode = DRAW_UNK_800;

        prim = prim->next;
        prim->type = PRIM_TILE;
        prim->x0 = 0;
        prim->y0 = 0;
        prim->u0 = 0xFF;
        prim->v0 = 0xFF;
        prim->r0 = prim->g0 = prim->b0 = 8;
        prim->priority = 0x1FC;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        self->step++;
        return;
    case 7:
        prim = self->ext.cutscenePhoto.prim;
        prim->tpage = 0x110;
        prim->u0 = prim->x0;
        prim->u1 = prim->x1;
        prim->u2 = prim->x2;
        prim->u3 = prim->x3;
        prim->v0 = prim->y0;
        prim->v1 = prim->y1;
        prim->v2 = prim->y2;
        prim->v3 = prim->y3;
        prim->priority = 0x1FE;
        prim->drawMode = DRAW_DEFAULT;

        prim = prim->next;
        prim->drawMode = DRAW_HIDE;

        prim = prim->next;
        prim->type = PRIM_ENV;
        dr_env = (DR_ENV*)LOW(prim->r1);

        drawEnv = g_CurrentBuffer->draw;

        drawEnv.isbg = 0;
        drawEnv.dtd = 0;

        clipRect.x = 0;
        clipRect.y = 0x100;
        clipRect.w = 0x100;
        clipRect.h = 0x100;
        drawEnv.clip = clipRect;

        drawEnv.ofs[0] = 0;
        drawEnv.ofs[1] = 0x100;
        SetDrawEnv(dr_env, &drawEnv);
        prim->priority = 0x1FA;
        prim->drawMode = DRAW_DEFAULT;

        prim = prim->next;

        prim = prim->next;
        prim->type = PRIM_TILE;
        prim->x0 = 0x40;
        prim->y0 = 0x40;
        prim->u0 = 0x80;
        prim->v0 = 0x80;
        prim->r0 = prim->g0 = prim->b0 = 0;
        prim->priority = 0x1FC;
        prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
        self->pose = 0;
        g_api.PlaySfx(SFX_BURNING_PHOTOGRAPH);
        self->step++;
#ifdef VERSION_PSP
        func_psp_0891B0BC(1);
#endif
        /* fallthrough */
    case 8:
        if (self->poseTimer) {
            self->poseTimer--;
            return;
        }
        self->poseTimer = 4;
        // Ugh, this should have been a 2D array.
        newEntXY = D_8018245C;
        newEntXY = &newEntXY[self->pose * 2];
        self->pose++;
        if (newEntXY[0] == -1) {
            self->step++;
            return;
        }
        newEntX = newEntXY[0];
        newEntY = newEntXY[1];

        if (self->pose & 1) {
            dualFlag = 0;
        } else {
            dualFlag = 1;
        }
        otherEnt = AllocEntity(self, &g_Entities[256]);
        if (otherEnt != NULL) {
            CreateEntityFromCurrentEntity(E_ID(ID_2D), otherEnt);
            otherEnt->posX.i.hi = newEntX;
            otherEnt->posY.i.hi = newEntY;
            otherEnt->facingLeft = dualFlag;
            otherEnt->params = 0;
        }

        otherEnt = AllocEntity(self, &g_Entities[256]);
        if (otherEnt != NULL) {
            CreateEntityFromCurrentEntity(E_ID(ID_2D), otherEnt);
            otherEnt->posX.i.hi = newEntX;
            otherEnt->posY.i.hi = newEntY + 0xC;
            otherEnt->facingLeft = dualFlag;
            otherEnt->params = 1;
        }
        break;
    case 9:
        prim = self->ext.cutscenePhoto.prim;
        prim = prim->next;
        prim->type = PRIM_G4;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0x100;
        prim->y0 = prim->y1 = 0;
        prim->y2 = prim->y3 = 0x100;
        prim->r0 = prim->g0 = prim->b0 = 0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0x1FF;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        self->step++;
        return;
    case 10:
        prim = self->ext.cutscenePhoto.prim;
        prim = prim->next;
        prim->r0 += 8;
        if (prim->r0 > 0xF0) {
            self->step++;
        }
        prim->g0 = prim->b0 = prim->r0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        return;
    case 11:
    case 12:
        g_GameEngineStep = Engine_10;
        g_MenuStep = 0;
        break;
    }
}

static u8 D_801824CC[] = {
    0x03, 0x01, 0x03, 0x02, 0x03, 0x03, 0x03, 0x04, 0x03, 0x05,
    0x03, 0x06, 0x03, 0x07, 0x03, 0x08, 0x03, 0x09, 0x03, 0x0A,
    0x03, 0x0B, 0x03, 0x0C, 0x03, 0x0D, 0xFF, 0x00};
void EntityCutscenePhotographFire(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(g_EInit3DObject);
        entity->animSet = ANIMSET_OVL(7);
        entity->unk5A = 0x57;
        entity->palette = PAL_FLAG(0x285);
        entity->flags &= ~FLAG_POS_CAMERA_LOCKED;
        entity->drawFlags = FLAG_DRAW_OPACITY;
        entity->opacity = 0x40;
        if (entity->params) {
            entity->opacity = 0x10;
            entity->zPriority = 0x1FB;
            entity->drawMode = DRAW_UNK_40 | DRAW_TPAGE;
        } else {
            entity->zPriority = 0x1FE;
            entity->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        }
    case 1:
        entity->posY.val -= FIX(1.0);
        if (AnimateEntity(D_801824CC, entity) == 0) {
            DestroyEntity(entity);
        }
        break;
    }
}
