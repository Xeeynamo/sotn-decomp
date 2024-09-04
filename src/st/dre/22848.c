#include "dre.h"

extern SVECTOR* D_80181544[][3];
extern u8 D_80181590[][5];
extern u8 D_8018159C[][4];
extern u8 D_801815A4[][20];
extern s16 D_801815CC[][7];

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
REDACTED
REDACTED
REDACTED
REDACTED
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
REDACTED
REDACTED
REDACTED
REDACTED
            CreateEntityFromCurrentEntity(E_ID_BACKGROUND_HOUSE, newEntity);
            newEntity->posX.i.hi = *dataPtr++ - g_Tilemap.scrollX.i.hi;
            newEntity->posY.i.hi = *dataPtr++ - g_Tilemap.scrollY.i.hi;
            // Params is either 0 or 1. In-game, there are 3 houses in
            // a row, and behind them 2 more houses, which are rotated 90 deg.
            // This likely controls the rotation.
            newEntity->params = *dataPtr++;
        }
        self->step++;
    }
}

// 3D house object in background ID 0x16
void Entity3DBackgroundHouse(Entity* self) {
    SVECTOR rot;
    VECTOR trans;
    MATRIX m;
    s32 unused1;
    s32 unused2;
    Primitive* prim;
    s32 primIndex;
    s16* houseData;
    s32 i;
    SVECTOR** vertices;
    s32* scratchpad;
    u8* model;
REDACTED
REDACTED
REDACTED
        InitializeEntity(g_EInitGeneric);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 16);
        // Usually this can be if primIndex == -1 DestroyEntity but nope
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.bghouse.prim = prim;
            for (; prim != NULL; prim = prim->next) {
                prim->tpage = 0xF;
                prim->priority = 0x58 - self->params;
                prim->drawMode = DRAW_HIDE;
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
        // surprised this isn't just if abs(posX) > 0x200
        if (self->posX.i.hi > 0x200 || self->posX.i.hi < -0x200) {
            for (prim = self->ext.bghouse.prim; prim != NULL;
                 prim = prim->next) {
                prim->drawMode = DRAW_HIDE;
            }
            return;
        }
        prim = self->ext.bghouse.prim; // unused
        SetGeomScreen(0x400);
        SetGeomOffset(128, 192);
        // this is a 7-by-X array, so params picks a set of 7 values
        houseData = D_801815CC;
        // Params is 0 or 1. 0 if house is straight, 1 if rotated 90 degree.
        houseData += 7 * self->params;
        rot.vx = 0;
        rot.vy = *houseData++;
        rot.vz = 0;
        RotMatrix(&rot, &m);
        trans.vx = self->posX.i.hi - 0x80;
        trans.vy = self->posY.i.hi - 0xC0;
        trans.vz = *houseData++ + 0x400;
        TransMatrix(&m, &trans);
        SetRotMatrix(&m);
        SetTransMatrix(&m);
        vertices = &D_80181544[0][0];
        scratchpad = SPAD(0);
        for (i = 0; i < 6; i++) {
            RotTransPers3(vertices[0], vertices[1], vertices[2], &scratchpad[0],
                          &scratchpad[1], &scratchpad[2], &unused1, &unused2);
            vertices += 3;
            scratchpad += 3;
        }
        RotTransPers(vertices[0], scratchpad, &unused1, &unused2);
        prim = self->ext.bghouse.prim;
        // Would be nice if all of these could just be D_whatever[i] but model
        // seems needed
        model = D_80181590;
        for (i = 0; i < 2; i++) {
            prim = func_801A2848(prim, model, houseData);
            model += 5;
        }
        model = D_8018159C;
        for (i = 0; i < 2; i++) {
            prim = func_801A2A58(prim, model, houseData);
            model += 4;
        }
        houseData += 3;
        model = D_801815A4;
        for (i = 0; i < 2; i++) {
            prim = func_801A2C9C(prim, model, houseData);
            model += 20;
        }
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        break;
    }
}
