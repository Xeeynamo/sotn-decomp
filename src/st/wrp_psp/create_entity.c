#include "../wrp/wrp.h"
#include "../st_private.h"

#include "../create_entity_from_layout.h"

#include "../create_entity_in_range.h"

#include "../find_entity_horizontal.h"

void CreateEntitiesToTheRight(s16);
INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/create_entity", CreateEntitiesToTheRight);

void CreateEntitiesToTheLeft(s16);
INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/create_entity", CreateEntitiesToTheLeft);

#include "../find_entity_vertical.h"

void CreateEntitiesAbove(s16);
INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/create_entity", CreateEntitiesAbove);

void CreateEntitiesBelow(s16);
INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/create_entity", CreateEntitiesBelow);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/create_entity", InitRoomEntities);

#include "../update_room_position.h"

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
