// SPDX-License-Identifier: AGPL-3.0-or-later
#include <scratchpad.h>

#ifdef VERSION_PSP
extern s32 E_ID(3D_BACKGROUND_HOUSE);
#endif

extern EInit g_EInitInteractable;

static SVECTOR v0 = {-0x3C, -0x9B, -0x78};
static SVECTOR v1 = {0x3C, -0x9B, -0x78};
static SVECTOR v2 = {-0x3C, 0x00, -0x78};
static SVECTOR v3 = {0x3C, 0x00, -0x78};
static SVECTOR v4 = {0x3C, -0x9B, 0x78};
static SVECTOR v5 = {-0x3C, -0x9B, 0x78};
static SVECTOR v6 = {0x3C, 0x00, 0x78};
static SVECTOR v7 = {-0x3C, 0x00, 0x78};
static SVECTOR v8 = {0x00, -0xDB, -0x78};
static SVECTOR v9 = {0x00, -0xDB, 0x78};
static SVECTOR v10 = {0x00, -0xDB, 0x3C};
static SVECTOR v11 = {0x00, -0xDB, 0x00};
static SVECTOR v12 = {0x00, -0xDB, -0x3C};
static SVECTOR v13 = {0x3C, -0x9B, 0x3C};
static SVECTOR v14 = {0x3C, -0x9B, 0x00};
static SVECTOR v15 = {0x3C, -0x9B, -0x3C};
static SVECTOR v16 = {-0x3C, -0x9B, 0x3C};
static SVECTOR v17 = {-0x3C, -0x9B, 0x00};
static SVECTOR v18 = {-0x3C, -0x9B, -0x3C};
static SVECTOR* vertices[] = {
    &v0,  &v1,  &v2,  &v3,  &v4,  &v5,  &v6,  &v7,  &v8,  &v9,
    &v10, &v11, &v12, &v13, &v14, &v15, &v16, &v17, &v18,
};
static u8 facadeIndices[] = {0, 1, 2, 3, 8, 4, 5, 6, 7, 9};
static u8 sideIndices[] = {1, 4, 3, 6, 5, 0, 7, 2};
static u8 roofIndices[] = {
    8, 9, 1, 4, 8, 10, 1, 13, 10, 11, 13, 14, 11, 12, 14, 15, 12, 9, 15, 4,
    9, 8, 5, 0, 9, 12, 5, 18, 12, 11, 18, 17, 11, 10, 17, 16, 10, 8, 16, 0,
};
// clang-format off
#if defined(STAGE_IS_NO2)
static s16 D_us_80180CD8[] = {
    0x000, 0x100, 0x046, 0x070, 0x090, 0x045, 0x080,
    0x400, 0x300, 0x04F, 0x0F0, 0x080, 0x04E, 0x070,
};
static s16 D_us_80180CF4[] = {
    0x060, 0x3E0, 0,
    0x140, 0x3E0, 0,
    0x280, 0x3E0, 0,
    0x380, 0x3E0, 0,
    0x4C0, 0x3E0, 0,
    0x5A0, 0x3E0, 0,
    0x100, 0x3E0, 1,
    0x200, 0x3E0, 1,
    0x300, 0x3E0, 1,
    0x400, 0x3E0, 1,
    0x500, 0x3E0, 1,
    -1,
};
#elif defined(STAGE_IS_DRE)
static s16 D_us_80180CD8[] = {
    0x000, 0x100, 0x004, 0x070, 0x090, 0x003, 0x080,
    0x400, 0x300, 0x004, 0x0F0, 0x080, 0x003, 0x070,
};
static s16 D_us_80180CF4[] = {
    0x020, 0x0E0, 0,
    0x0F0, 0x0E0, 0,
    0x1C0, 0x0E0, 0,
    0x040, 0x0E0, 1,
    0x140, 0x0E0, 1,
    -1,
};
#endif
// clang-format on

static Primitive* DrawFacade(Primitive* prim, u8* indices, u16* arg2) {
    s32 p0;
    s32 p1;
    s32 p2;
    s32 p3;
    s32 p4;
    s32 clip;

    p0 = *SPAD(indices[0]);
    p1 = *SPAD(indices[1]);
    p2 = *SPAD(indices[2]);
    clip = NormalClip(p0, p1, p2);
    if (clip <= 0) {
        return prim;
    }
    p3 = *SPAD(indices[3]);
    p4 = *SPAD(indices[4]);

    prim->tpage = 0xF;
    prim->clut = arg2[0];
    prim->u0 = prim->u2 = 4;
    prim->u1 = prim->u3 = 0x7C;
    prim->v0 = prim->v1 = 3;
    prim->v2 = prim->v3 = 0x9E;
    LOW(prim->x0) = p0;
    LOW(prim->x1) = p1;
    LOW(prim->x2) = p2;
    LOW(prim->x3) = p3;
    prim->drawMode = DRAW_UNK02;
    prim->drawMode |= DRAW_COLORS;
    prim->r0 = prim->g0 = prim->b0 = arg2[1];
    LOW(prim->r1) = LOW(prim->r0);
    LOW(prim->r2) = LOW(prim->r0);
    LOW(prim->r3) = LOW(prim->r0);
    prim = prim->next;

    prim->tpage = 0xF;
    prim->clut = arg2[0];
    prim->u0 = 0xFE;
    prim->u1 = 0xC2;
    prim->u2 = 0xC2;
    prim->u3 = 0xFE;
    prim->v0 = 0xAC;
    prim->v1 = 0x6C;
    prim->v2 = 0xAC;
    prim->v3 = 0xAC;
    LOW(prim->x0) = p0;
    LOW(prim->x3) = p1;
    LOW(prim->x1) = p4;

    prim->x2 = (prim->x0 + prim->x3) / 2;
    prim->y2 = (prim->y0 + prim->y3) / 2;

    prim->drawMode = DRAW_UNK02;
    prim->drawMode |= DRAW_COLORS;
    prim->r0 = prim->g0 = prim->b0 = arg2[1];
    LOW(prim->r1) = LOW(prim->r0);
    LOW(prim->r2) = LOW(prim->r0);
    LOW(prim->r3) = LOW(prim->r0);
    prim = prim->next;
    return prim;
}

static Primitive* DrawSides(Primitive* prim, u8* indices, u16* arg2) {
    s32 p0;
    s32 p1;
    s32 p2;
    s32 p3;
    s32 clip;
    s16 avg1;
    s16 avg2;
    s16 avg3;
    s16 avg4;

    p0 = *SPAD(indices[0]);
    p1 = *SPAD(indices[1]);
    p2 = *SPAD(indices[2]);
    clip = NormalClip(p0, p1, p2);
    if (clip <= 0) {
        return prim;
    }
    p3 = *SPAD(indices[3]);

    prim->tpage = 0xF;
    prim->clut = arg2[0];
    prim->u0 = prim->u2 = 4;
    prim->u1 = prim->u3 = 0x7C;
    prim->v0 = prim->v1 = 3;
    prim->v2 = prim->v3 = 0x9E;
    LOW(prim->x0) = p0;
    LOW(prim->x2) = p2;
    avg1 = (LOH(p0) + LOH(p1)) / 2;
    prim->x1 = avg1;
    avg2 = (LOH(p2) + LOH(p3)) / 2;
    prim->x3 = avg2;
    avg3 = (HIH(p0) + HIH(p1)) / 2;
    prim->y1 = avg3;
    avg4 = (HIH(p2) + HIH(p3)) / 2;
    prim->y3 = avg4;
    prim->drawMode = DRAW_UNK02;
    prim->drawMode |= DRAW_COLORS;
    prim->r0 = prim->g0 = prim->b0 = arg2[2];
    LOW(prim->r1) = LOW(prim->r0);
    LOW(prim->r2) = LOW(prim->r0);
    LOW(prim->r3) = LOW(prim->r0);
    prim = prim->next;

    prim->tpage = 0xF;
    prim->clut = arg2[0];
    prim->u0 = prim->u2 = 4;
    prim->u1 = prim->u3 = 0x7C;
    prim->v0 = prim->v1 = 3;
    prim->v2 = prim->v3 = 0x9E;
    LOW(prim->x1) = p1;
    LOW(prim->x3) = p3;
    prim->x0 = avg1;
    prim->x2 = avg2;
    prim->y0 = avg3;
    prim->y2 = avg4;
    prim->drawMode = DRAW_UNK02;
    prim->drawMode |= DRAW_COLORS;
    prim->r0 = prim->g0 = prim->b0 = arg2[2];
    LOW(prim->r1) = LOW(prim->r0);
    LOW(prim->r2) = LOW(prim->r0);
    LOW(prim->r3) = LOW(prim->r0);
    prim = prim->next;
    return prim;
}

static Primitive* DrawRoof(Primitive* prim, u8* indices, u16* arg2) {
    s32 p0;
    s32 p1;
    s32 p2;
    s32 clip;
    s32 i;

    p0 = *SPAD(indices[0]);
    p1 = *SPAD(indices[1]);
    p2 = *SPAD(indices[2]);
    clip = NormalClip(p0, p1, p2);
    if (clip <= 0) {
        return prim;
    }
    indices += 4;
    for (i = 0; i < 4; i++) {
        prim->tpage = 0xF;
        prim->clut = arg2[0];
        prim->u0 = prim->u2 = 0x82;
        prim->u1 = prim->u3 = 0xBE;
        prim->v0 = prim->v1 = 0x6C;
        prim->v2 = prim->v3 = 0xA4;
        LOW(prim->x0) = *SPAD(indices[0]);
        LOW(prim->x1) = *SPAD(indices[1]);
        LOW(prim->x2) = *SPAD(indices[2]);
        LOW(prim->x3) = *SPAD(indices[3]);
        indices += 4;
        prim->drawMode = DRAW_UNK02;
        prim->drawMode |= DRAW_COLORS;
        prim->r0 = prim->g0 = prim->b0 = arg2[1];
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim = prim->next;
    }
    return prim;
}

void Entity3DHouseSpawner(Entity* self) {
    Entity* tempEntity;
    s16* ptr;

    if (!self->step) {
        ptr = D_us_80180CF4;
        while (*ptr != -1) {
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity == NULL) {
                break;
            }
            CreateEntityFromCurrentEntity(
                E_ID(3D_BACKGROUND_HOUSE), tempEntity);
            tempEntity->posX.i.hi = *ptr - g_Tilemap.scrollX.i.hi;
            ptr++;
            tempEntity->posY.i.hi = *ptr - g_Tilemap.scrollY.i.hi;
            ptr++;
            // Params is either 0 or 1. In-game, there are 3 houses in
            // a row, and behind them 2 more houses, which are rotated 90 deg.
            // This likely controls the rotation.
            tempEntity->params = *ptr++;
        }
        self->step++;
    }
}

void Entity3DBackgroundHouse(Entity* self) {
    long p, flag;
    SVECTOR rot;
    VECTOR trans;
    MATRIX m;
    Primitive* prim;
    s32 primIndex;
    s16* modelData;
    s32 i;
    SVECTOR** vPtr;
    s32* scratchpad;
    u8* iPtr;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 16);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.bghouse.prim = prim;
            while (prim != NULL) {
                prim->tpage = 0xF;
                prim->priority = 0x58 - self->params;
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
            return;
        }
        // These seem to be unused?
        self->ext.bghouse.unk80 = 0x80;
        self->ext.bghouse.unk82 = 0x80;
        self->ext.bghouse.unk84 = 0x80;
        break;

    case 1:
        if (self->posX.i.hi > 0x200 || self->posX.i.hi < -0x200) {
            prim = self->ext.bghouse.prim;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            return;
        }
        prim = self->ext.bghouse.prim;
        SetGeomScreen(0x400);
        SetGeomOffset(128, 192);
        // this is a 7-by-X array, so params picks a set of 7 values
        modelData = D_us_80180CD8;
        // Params is 0 or 1. 0 if house is straight, 1 if rotated 90 degree.
        modelData += self->params * 7;
        rot.vx = 0;
        rot.vy = *modelData++;
        rot.vz = 0;
        RotMatrix(&rot, &m);
        trans.vx = self->posX.i.hi - 0x80;
        trans.vy = self->posY.i.hi - 0xC0;
        trans.vz = *modelData++ + 0x400;
        TransMatrix(&m, &trans);
        SetRotMatrix(&m);
        SetTransMatrix(&m);
        vPtr = vertices;
        scratchpad = SPAD(0);
        for (i = 0; i < 6; i++) {
            RotTransPers3(vPtr[0], vPtr[1], vPtr[2], &scratchpad[0],
                          &scratchpad[1], &scratchpad[2], &p, &flag);
            vPtr += 3;
            scratchpad += 3;
        }
        RotTransPers(vPtr[0], (long*)scratchpad, &p, &flag);
        prim = self->ext.bghouse.prim;
        iPtr = facadeIndices;
        for (i = 0; i < 2; i++) {
            prim = DrawFacade(prim, iPtr, (u16*)modelData);
            iPtr += 5;
        }
        iPtr = sideIndices;
        for (i = 0; i < 2; i++) {
            prim = DrawSides(prim, iPtr, (u16*)modelData);
            iPtr += 4;
        }
        modelData += 3;
        iPtr = roofIndices;
        for (i = 0; i < 2; i++) {
            prim = DrawRoof(prim, iPtr, (u16*)modelData);
            iPtr += 20;
        }
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        break;
    }
}
