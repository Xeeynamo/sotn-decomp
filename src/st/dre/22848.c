#include "dre.h"

extern SVECTOR* D_80181544[];
extern u8 D_80181590[];
extern u8 D_8018159C[];
extern u8 D_801815A4[];
extern u16 D_801815CC[];
long RotTransPers3(SVECTOR* v0, SVECTOR* v1, SVECTOR* v2, long* sxy0,
                   long* sxy1, long* sxy2, long* p, long* flag);
long NormalClip(long sxy0, long sxy1, long sxy2);

Primitive* func_801A2848(Primitive* prim, u8* model, u16* arg2);
INCLUDE_ASM("st/dre/nonmatchings/22848", func_801A2848);

Primitive* func_801A2A58(Primitive* prim, u8* model, u16* arg2);
INCLUDE_ASM("st/dre/nonmatchings/22848", func_801A2A58);

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
