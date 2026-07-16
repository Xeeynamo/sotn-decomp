// SPDX-License-Identifier: AGPL-3.0-or-later
#include <libgte.h>
#include "clock_tower.h"
#include <scratchpad.h>

extern EInit g_EInitInteractable;
extern EInit g_EInitSpawner;

static s16 D_us_80181BFC[] = {0, 0, 0, 0, 0xC181, 0xC1BE, 0xDE81, 0xDEBE, 0xE181, 0xE1BE, 0xFE81, 0xFEBE, 0xC181, 0xC1BE, 0xDE81, 0xDEBE, 0xE181, 0xE1BE, 0xFE81, 0xFEBE, 0x8181, 0x81BE, 0xA081, 0xA0BE, 0xA081, 0xA0BE, 0xBE81, 0xBEBE, 0x81C1, 0x81FE, 0xA0C1, 0xA0FE, 0xA0C1, 0xA0FE, 0xBEC1, 0xBEFE};

static SVECTOR cloudVectorOne = {-128, 0, 0, 0};
static SVECTOR cloudVectorTwo = {128, 0, 0, 0};
static SVECTOR cloudVectorThree = {-128, 0, 224, 0};
static SVECTOR cloudVectorFour = {128, 0, 224, 0};

static u8 cloudData1[] = {5, 0, 7, 0, 0, 8, 0, 0, 6, 0, 8, 5, 0, 0, 7, 5, 0, 5, 0, 6, 5, 0, 8, 6, 0, 6, 0, 0, 6, 0, 0, 0, 5, 0, 0, 7, 0, 0, 0, 7, 6, 5, 0, 8, 0, 5, 5, 8, 0, 6, 0, 5, 5, 6, 6, 0, 0, 0, 0, 6, 6, 7, 0, 0};
static u8 cloudData2[] = {4, 3, 3, 4, 2, 4, 3, 4, 1, 3, 2, 3, 4, 2, 2, 4, 3, 2, 2, 3, 2, 4, 3, 4, 2, 2, 4, 3, 1, 3, 2, 4, 1, 1, 2, 1, 4, 4, 4, 4, 3, 2, 2, 3, 2, 1, 2, 2, 1, 2, 2, 2, 3, 4, 2, 2, 3, 3, 4, 2, 2, 4, 3, 4};
#if !defined(INVERTED_STAGE)
#define UP +
#define DOWN -
#define UNK9C 0x4B
#define UNKA0 0
#define X_OFF 0x65
#define POSX_3D 0x700
#define POSY_3D 0x3C0
#define ROTZ_3D 0
#else
#define UP -
#define DOWN +
#define UNK9C 0xB5
#define UNKA0 0x100
#define X_OFF 0x7B
#define POSX_3D 0x100
#define POSY_3D 0x440
#define ROTZ_3D 0x800
#endif
static cloudData data[] = {{cloudData1, DOWN 320, 24}, {cloudData2, UP 320, 28}};
static SVECTOR empty = {0,0,0};

// very simliar to ST0's EntityClouds, however,
// TOP & RTOP are much taller so many dimensional constants
// differ.
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
        InitializeEntity(g_EInitSpawner);
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

        self->ext.clouds.unk9C.i.hi = UNK9C;
        self->ext.clouds.unkA0.i.hi = UNKA0;

        prim->priority = 4;
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        while (prim != NULL) {
            prim->tpage = 0xF;
            prim->clut = 0x200;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }

    self->ext.clouds.unk84.val += FIX(3);
    self->ext.clouds.unk8C += FIX(8);
    self->ext.clouds.unk88 += FIX(8);
    self->ext.clouds.unk90 += FIX(4);

    g_GpuBuffers[0].draw.r0 = 24;
    g_GpuBuffers[0].draw.g0 = 0;
    g_GpuBuffers[0].draw.b0 = 40;
    g_GpuBuffers[1].draw.r0 = 24;
    g_GpuBuffers[1].draw.g0 = 0;
    g_GpuBuffers[1].draw.b0 = 40;

    matrix = (MATRIX*)SP(0);
    primTwo = (Primitive*)SP(0x20);
    vector = (SVECTOR*)SP(0x60);
    vector[0] = cloudVectorOne;
    vector[1] = cloudVectorTwo;
    vector[2] = cloudVectorThree;
    vector[3] = cloudVectorFour;

    var_s7 = (s32*)SP(0x80);
    var_s1 = D_us_80181BFC;
    for (i = 0; i < 0x24; i++, var_s7++, var_s1++) {
        *var_s7 = *var_s1;
    }

    var_s3 = (u8*)SP(0x200);
    var_s3[3] = 4;
    var_s3[7] = 4;

    SetGeomScreen(320);
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

    prim->x0 = prim->x2 = self->ext.clouds.unk9C.i.hi;
    prim->x1 = prim->x3 = self->ext.clouds.unk9C.i.hi UP 0x65;
    prim->y0 = prim->y1 = self->ext.clouds.unkA0.i.hi;
    prim->y2 = prim->y3 = self->ext.clouds.unkA0.i.hi UP 0x7B;

    prim = prim->next;

    for (i = 0; i < 2; i++, cloudData++, var_s1 += 4) {
        posX = self->posX.i.hi + *var_s1;
        posX %= 0x800;
        priority = cloudData->priority;
        var_s2 = cloudData->unk4;
        var_s2 += (0x340 - g_Tilemap.scrollY.i.hi >> 3);
        gte_ldty(var_s2);
        for (sp5C = 0; sp5C < 8; sp5C++) {
            var_s2 = sp5C * 0xE0 + 0x240;
            sp40 = (u16)var_s1[2];
            var_s2 -= sp40 % 224;
            gte_ldtz(var_s2);
            sp40 = (sp5C + (sp40 / 224)) % 8;
            sp38 = (cloudData->unkPtr + sp40 * 8);
            var_s2 -= 0x240;

            sp4C = FIX(15) - var_s2 * 0x1DB;
            var_s3[0] = sp4C >> 12;
            var_s3[4] = (sp4C - FIX(106400.0 / 0x10000)) >> 12;

            sp4C = FIX(15) - var_s2 * 0x200;
            var_s3[1] = sp4C >> 12;
            var_s3[5] = (sp4C - FIX(1.75)) >> 12;

            sp4C = FIX(15) - var_s2 * 0x192;
            var_s3[2] = sp4C >> 12;
            var_s3[6] = (sp4C - FIX(1.37403)) >> 12;

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
}

extern ClockTowerData s_RoofTextureData[];
extern ClockTowerData2 s_TowerTextureData[];

extern u8 s_ClockRoofScript[];
extern u8 s_ClockTowerScript[];
extern SVECTOR* s_ClockVertexSets[];

void EntityClockTower3D(Entity* self) {
    SVECTOR rotVector;
    VECTOR transVector;
    MATRIX matrix;
    Primitive* prim;
    s16 primIndex;
    SVECTOR* vectors;
    u8* script;
    ClockTowerData* var_s2;
    ClockTowerData2* var_s3;

    if (self->step == 0) {
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
