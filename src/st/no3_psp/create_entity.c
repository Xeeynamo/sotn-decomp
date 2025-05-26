// SPDX-License-Identifier: AGPL-3.0-or-later

#include "../no3/no3.h"
#include "../pfn_entity_update.h"

//CreateEntityFromLayout
void func_pspeu_09245A58(Entity* entity, LayoutEntity* initDesc) {
    Tilemap* tilemap;

    tilemap = &g_Tilemap;

    DestroyEntity(entity);
    entity->entityId = initDesc->entityId & 0x3FF;
    entity->pfnUpdate = PfnEntityUpdates[entity->entityId - 1];
    entity->posX.i.hi = (s16)initDesc->posX - tilemap->scrollX.i.hi;
    entity->posY.i.hi = (s16)initDesc->posY - tilemap->scrollY.i.hi;
    entity->params = initDesc->params;
    entity->entityRoomIndex = initDesc->entityRoomIndex >> 8;
    entity->unk68 = (initDesc->entityId >> 0xA) & 7;
}

// CreateEntityWhenInVerticalRange
void func_pspeu_09245B78(LayoutEntity* obj) {
    s16 yClose;
    s16 yFar;
    s16 posY;
    Entity* entity;
    Tilemap* tilemap;

    tilemap = &g_Tilemap;
    posY = tilemap->scrollY.i.hi;
    yClose = posY - 0x40;
    yFar = posY + 0x120;
    if (yClose < 0) {
        yClose = 0;
    }

    posY = obj->posY;
    if (posY < yClose || posY > yFar) {
        return;
    }
    switch (obj->entityId & 0xE000) {
    case 0x0:
        entity =
            g_Entities + STAGE_ENTITY_START + (obj->entityRoomIndex & 0xFF);
        if (!entity->entityId) {
            func_pspeu_09245A58(entity, obj);
        }
        break;
    case 0xA000:
        entity =
            g_Entities + STAGE_ENTITY_START + (obj->entityRoomIndex & 0xFF);
            func_pspeu_09245A58(entity, obj);
        break;
    case 0x8000:
        break;
    }
}

INCLUDE_ASM("st/no3_psp/psp/no3_psp/create_entity", func_pspeu_09245D10);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/create_entity", func_pspeu_09245EA8);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/create_entity", func_pspeu_09245F18);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/create_entity", func_pspeu_09245FA0);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/create_entity", func_pspeu_092460E0);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/create_entity", func_pspeu_09246238);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/create_entity", func_pspeu_092462B0);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/create_entity", func_pspeu_09246338);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/create_entity", func_pspeu_09246480);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/create_entity", InitRoomEntities);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/create_entity", UpdateRoomPosition);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/create_entity", CreateEntityFromCurrentEntity);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/create_entity", CreateEntityFromEntity);