#include "dre.h"

extern SVECTOR* D_80181544[];
extern u8 D_80181590[];
extern u8 D_8018159C[];
extern u8 D_801815A4[];
extern u16 D_801815CC[];
long RotTransPers3(SVECTOR* v0, SVECTOR* v1, SVECTOR* v2, long* sxy0,
                   long* sxy1, long* sxy2, long* p, long* flag);
long NormalClip(long sxy0, long sxy1, long sxy2);

Primitive* func_801A2848(Primitive* prim, u8* arg1, u16* arg2) {
    s32 pad0;
    s32 pad1;
    s32 pad2;
    s32 pad3;
    s32 pad4;

    pad0 = *SPAD(arg1[0]);
    pad1 = *SPAD(arg1[1]);
    pad2 = *SPAD(arg1[2]);
    if (NormalClip(pad0, pad1, pad2) <= 0) {
        return prim;
    }
    pad3 = *SPAD(arg1[3]);
    pad4 = *SPAD(arg1[4]);

    prim->tpage = 0xF;
    prim->clut = arg2[0];
    prim->u0 = prim->u2 = 4;
    prim->u1 = prim->u3 = 0x7C;
    prim->v0 = prim->v1 = 3;
    prim->v2 = prim->v3 = 0x9E;
    LOW(prim->x0) = pad0;
    LOW(prim->x1) = pad1;
    LOW(prim->x2) = pad2;
    LOW(prim->x3) = pad3;
    prim->drawMode = DRAW_UNK02 | DRAW_COLORS;
    prim->r0 = prim->g0 = prim->b0 = arg2[1];
    LOW(prim->r1) = LOW(prim->r0);
    LOW(prim->r2) = LOW(prim->r0);
    LOW(prim->r3) = LOW(prim->r0);
    prim = prim->next;

    prim->tpage = 0xF;
    prim->clut = arg2[0];
    // Some of these values are shared but don't seem to match if combined
    prim->u0 = 0xFE;
    prim->u2 = prim->u1 = 0xC2;
    prim->u3 = 0xFE;
    prim->v0 = 0xAC;
    prim->v1 = 0x6C;
    prim->v3 = prim->v2 = 0xAC;
    LOW(prim->x0) = pad0;
    LOW(prim->x1) = pad4;
    LOW(prim->x3) = pad1;
    prim->x2 = (prim->x0 + prim->x3) / 2;
    prim->y2 = (prim->y0 + prim->y3) / 2;

    prim->drawMode = DRAW_UNK02 | DRAW_COLORS;
    prim->r0 = prim->g0 = prim->b0 = arg2[1];
    LOW(prim->r1) = LOW(prim->r0);
    LOW(prim->r2) = LOW(prim->r0);
    LOW(prim->r3) = LOW(prim->r0);
    return prim->next;
}

Primitive* func_801A2A58(Primitive* prim, u8* model, u16* arg2) {
    Point16 points[4];
    s32 clipper;
    s16 avg1;
    s16 avg2;
    s16 avg3;
    s16 avg4;
    u16 clut;

    LOW(points[0].x) = *SPAD(model[0]);
    LOW(points[1].x) = *SPAD(model[1]);
    LOW(points[2].x) = *SPAD(model[2]);
    clipper = NormalClip(LOW(points[0].x), LOW(points[1].x), LOW(points[2].x));
    if (clipper <= 0) {
        return prim;
    }
    LOW(points[3].x) = *SPAD(model[3]);

    prim->tpage = 0xF;
    clut = arg2[0];
    prim->u0 = prim->u2 = 4;
    prim->u1 = prim->u3 = 0x7C;
    prim->v0 = prim->v1 = 3;
    prim->v2 = prim->v3 = 0x9E;
    LOW(prim->x0) = LOW(points[0].x);
    LOW(prim->x2) = LOW(points[2].x);
    avg1 = (points[0].x + points[1].x) / 2;
    prim->clut = clut;
    avg2 = (points[2].x + points[3].x) / 2;
    prim->x1 = avg1;
    prim->x3 = avg2;
    avg3 = (points[0].y + points[1].y) / 2;
    prim->y1 = avg3;
    avg4 = (points[2].y + points[3].y) / 2;
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
    LOW(prim->x1) = LOW(points[1].x);
    LOW(prim->x3) = LOW(points[3].x);
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

Primitive* func_801A2C9C(Primitive* prim, u8* model, u16* arg2) {
    long* spad;
    s32 i;

    spad = SPAD(0);
    if (NormalClip(spad[model[0]], spad[model[1]], spad[model[2]]) > 0) {
        model += 4;
        for (i = 0; i < 4; i++) {
            prim->tpage = 0xF;
            prim->clut = arg2[0];
            prim->u0 = prim->u2 = 0x82;
            prim->u1 = prim->u3 = 0xBE;
            prim->v0 = prim->v1 = 0x6C;
            prim->v2 = prim->v3 = 0xA4;
            LOW(prim->x0) = *SPAD(model[0]);
            LOW(prim->x1) = *SPAD(model[1]);
            LOW(prim->x2) = *SPAD(model[2]);
            LOW(prim->x3) = *SPAD(model[3]);
            prim->drawMode = DRAW_UNK02 | DRAW_COLORS;
            prim->r0 = prim->g0 = prim->b0 = arg2[1];
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim = prim->next;
            model += 4;
        }
    }
    return prim;
}

// Spawns the set of 3D background houses.
void Entity3DHouseSpawner(Entity* self) {
    s16* dataPtr;
    Entity* newEntity;

    if (self->step == 0) {
        dataPtr = D_801815E8;
        // It appears that the data here will hit an FFFF after 5 cycles.
        while (*dataPtr != -1) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity == NULL) {
                break;
            }
            CreateEntityFromCurrentEntity(E_ID_BACKGROUND_HOUSE, newEntity);
            newEntity->posX.i.hi = *dataPtr++ - g_Tilemap.scrollX.i.hi;
            newEntity->posY.i.hi = *dataPtr++ - g_Tilemap.scrollY.i.hi;
            newEntity->params = *dataPtr++;
        }
        self->step++;
    }
}

// 3D house object in background ID 0x16
INCLUDE_ASM("st/dre/nonmatchings/22848", Entity3DBackgroundHouse);
