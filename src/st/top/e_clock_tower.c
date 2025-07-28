// SPDX-License-Identifier: AGPL-3.0-or-later
#include "top.h"
#include <psxsdk/libgte.h>
#include "../../../include/cloud_struct.h"
#include "../clock_tower.h"

INCLUDE_ASM("st/top/nonmatchings/e_clock_tower", EntityClouds);

extern ClockTowerData s_RoofTextureData[];
extern ClockTowerData2 s_TowerTextureData[];

extern u8 s_ClockRoofScript[];
extern u8 s_ClockTowerScript[];
extern SVECTOR* s_ClockVertexSets[];
extern u16 g_EInitInteractable;

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
        InitializeEntity(&g_EInitInteractable);
        self->posX.i.hi = 0x700 - g_Tilemap.scrollX.i.hi;
        self->posY.i.hi = 0x3C0 - g_Tilemap.scrollY.i.hi;
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
