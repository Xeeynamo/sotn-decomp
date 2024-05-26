#include <game.h>

// *** TODO ***
// REMOVE THIS WHEN DOING #include <stage.h>
#if defined(VERSION_PSP)
extern PfnEntityUpdate* PfnEntityUpdates;
#else
extern PfnEntityUpdate PfnEntityUpdates[];
#endif

// redeclaring for the moment due to header conflict with Random() definition
typedef struct {
    /* 0x0 */ u16 posX;
    /* 0x2 */ u16 posY;
    /* 0x4 */ u16 entityId;
    /* 0x6 */ u16 entityRoomIndex;
    /* 0x8 */ u16 params;
} LayoutEntity; // size = 0xA

#include "../create_entity_from_layout.h"

#include "../create_entity_in_range.h"

extern LayoutEntity* g_LayoutObjHorizontal;
extern LayoutEntity* g_LayoutObjVertical;

void FindFirstEntityToTheRight(s16 arg0) {
    while (1) {
        LayoutEntity* layoutEntity = g_LayoutObjHorizontal;
        if ((layoutEntity->posX != 0xFFFE) &&
            ((s32)layoutEntity->posX >= arg0)) {
            break;
        }

        g_LayoutObjHorizontal++;
    }
}

#define LAYOUT_OBJ_START 0xfffe
#define LAYOUT_OBJ_END 0xffff

void FindFirstEntityToTheLeft(s16 posX) {
    while (true) {
        LayoutEntity* layoutObject = g_LayoutObjHorizontal;
        if (layoutObject->posX != LAYOUT_OBJ_END &&
            (layoutObject->posX <= posX ||
             layoutObject->posX == LAYOUT_OBJ_START)) {
            break;
        }
        g_LayoutObjHorizontal--;
    }
}

void CreateEntitiesToTheRight(s16);
INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/create_entity", CreateEntitiesToTheRight);

void CreateEntitiesToTheLeft(s16);
INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/create_entity", CreateEntitiesToTheLeft);

void FindFirstEntityAbove(s16 arg0) {
    while (true) {
        u16* ptr = &g_LayoutObjVertical->posY;
        if ((*ptr != (u16)~1) && !(*ptr < arg0)) {
            break;
        }
        g_LayoutObjVertical++;
    }
}

void FindFirstEntityBelow(s16 arg0) {
    while (true) {
        u16* ptr = &g_LayoutObjVertical->posY;

        if ((*ptr != 0xFFFF) && ((*ptr <= arg0) || !(*ptr != 0xFFFE))) {
            break;
        }
        g_LayoutObjVertical--;
    }
}

void CreateEntitiesAbove(s16);
INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/create_entity", CreateEntitiesAbove);

void CreateEntitiesBelow(s16);
INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/create_entity", CreateEntitiesBelow);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/create_entity", InitRoomEntities);

void UpdateRoomPosition() {
    Tilemap* tilemap = &g_Tilemap;
    s16 tmp;
    if (g_ScrollDeltaX != 0) {
        tmp = tilemap->scrollX.i.hi;
        if (g_ScrollDeltaX > 0) {
            tmp += 320;
            CreateEntitiesToTheRight(tmp);
        } else {
            tmp -= 64;
            CreateEntitiesToTheLeft(tmp);
        }
    }

    if (g_ScrollDeltaY != 0) {
        tmp = tilemap->scrollY.i.hi;
        if (g_ScrollDeltaY > 0) {
            tmp += 288;
            CreateEntitiesAbove(tmp);
        } else {
            tmp -= 64;
            CreateEntitiesBelow(tmp);
        }
    }
}

extern PfnEntityUpdate* PfnEntityUpdates;
void CreateEntityFromCurrentEntity(u16 entityId, Entity* entity) {
    DestroyEntity(entity);
    entity->entityId = entityId;
    entity->pfnUpdate = PfnEntityUpdates[entityId - 1];
    entity->posX.i.hi = g_CurrentEntity->posX.i.hi;
    entity->posY.i.hi = g_CurrentEntity->posY.i.hi;
}

void CreateEntityFromEntity(u16 entityId, Entity* source, Entity* entity) {
    DestroyEntity(entity);
    entity->entityId = entityId;
    entity->pfnUpdate = PfnEntityUpdates[entityId - 1];
    entity->posX.i.hi = source->posX.i.hi;
    entity->posY.i.hi = source->posY.i.hi;
}