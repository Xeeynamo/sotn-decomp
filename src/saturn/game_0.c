// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include "game.h"

void PlaySfx(s32 sfxId);

extern LayoutEntity* g_LayoutObjHorizontal;
extern LayoutEntity* g_LayoutObjVertical;
extern u8 g_LayoutObjPosHorizontal;
extern u8 g_LayoutObjPosVertical;

static inline void CreateEntityFromLayout(
    Entity* entity, LayoutEntity* initDesc) {
    s32 entityId;

    DestroyEntity(entity);

    entity->entityId = initDesc->entityId & 0x3FF;
    entityId = entity->entityId - 1;
    entity->pfnUpdate = (*PfnEntityUpdates)[entityId]->func;
    entity->posX.i.hi = initDesc->posX - g_Tilemap.scrollX.i.hi;
    entity->posY.i.hi = initDesc->posY - g_Tilemap.scrollY.i.hi;
    entity->params = initDesc->params;
    entity->entityRoomIndex = initDesc->entityRoomIndex >> 8;
    entity->unk68 = (initDesc->entityId >> 0xA) & 0x7;
}

void CreateEntityWhenInVerticalRange(LayoutEntity* obj) {
    s16 yClose;
    s16 yFar;
    Entity* entity;
    s16 posY;

    posY = g_Tilemap.scrollY.i.hi;
    yClose = posY - 0x40;
    yFar = posY + 0x130;
    if (yClose < 0) {
        yClose = 0;
    }

    if ((s16)obj->posY < yClose || yFar < (s16)obj->posY) {
        return;
    }

    posY = 0xE000U;
    switch (obj->entityId & (u32)posY) {
    case 0x0:
        entity =
            &g_Entities[STAGE_ENTITY_START + (obj->entityRoomIndex & 0xFF)];
        if (!entity->entityId) {
            CreateEntityFromLayout(entity, obj);
        }
        break;
    case 0x8000:
        break;
    case 0xA000:
        entity =
            &g_Entities[STAGE_ENTITY_START + (obj->entityRoomIndex & 0xFF)];
        CreateEntityFromLayout(entity, obj);
        break;
    }
}

void CreateEntityWhenInHorizontalRange(LayoutEntity* obj) {
    s16 xClose;
    s16 xFar;
    Entity* entity;
    s16 posX;

    posX = g_Tilemap.scrollX.i.hi;
    xClose = posX - 0x50;
    xFar = posX + 0x190;
    if (xClose < 0) {
        xClose = 0;
    }

    if ((s16)obj->posX < xClose || xFar < (s16)obj->posX) {
        return;
    }

    posX = 0xE000U;
    switch (obj->entityId & (u32)posX) {
    case 0x0:
        entity =
            &g_Entities[STAGE_ENTITY_START + (obj->entityRoomIndex & 0xFF)];
        if (!entity->entityId) {
            CreateEntityFromLayout(entity, obj);
        }
        break;
    case 0x8000:
        break;
    case 0xA000:
        entity =
            &g_Entities[STAGE_ENTITY_START + (obj->entityRoomIndex & 0xFF)];
        CreateEntityFromLayout(entity, obj);
        break;
    }
}

static inline void FindFirstEntityToTheRight(u16 posX) {
    while (true) {
        if (g_LayoutObjHorizontal->posX != 0xFFFE &&
            g_LayoutObjHorizontal->posX >= posX) {
            break;
        }
        g_LayoutObjHorizontal++;
    }
}

static inline void FindFirstEntityToTheLeft(u16 posX) {
    while (true) {
        if (g_LayoutObjHorizontal->posX != 0xFFFF &&
            (g_LayoutObjHorizontal->posX <= posX ||
             g_LayoutObjHorizontal->posX == 0xFFFE)) {
            break;
        }
        g_LayoutObjHorizontal--;
    }
}

void CreateEntitiesToTheRight(s16 posX) {
    u8 roomIndex;

    if (g_LayoutObjPosHorizontal) {
        FindFirstEntityToTheRight(posX - (DAT_0605c680.g_ScrollDeltaX >> 0x10));
        g_LayoutObjPosHorizontal = 0;
    }
    while (true) {
        if (g_LayoutObjHorizontal->posX == 0xFFFF ||
            posX < g_LayoutObjHorizontal->posX) {
            break;
        }
        roomIndex = g_LayoutObjHorizontal->entityRoomIndex >> 8;
        if (roomIndex != 0) {
            s32 temp;
            roomIndex--;
            temp = g_unkGraphicsStruct.D_80097428[roomIndex >> 5];
            if ((temp & (1 << (roomIndex & 0x1F))) == 0) {
                CreateEntityWhenInVerticalRange(g_LayoutObjHorizontal);
            }
        } else {
            CreateEntityWhenInVerticalRange(g_LayoutObjHorizontal);
        }
        g_LayoutObjHorizontal++;
    }
}

void CreateEntitiesToTheLeft(s16 posX) {
    u8 roomIndex;

    if (posX < 0) {
        posX = 0;
    }
    if (g_LayoutObjPosHorizontal == 0) {
        FindFirstEntityToTheLeft(posX - (DAT_0605c680.g_ScrollDeltaX >> 0x10));
        g_LayoutObjPosHorizontal = 1;
    }
    while (true) {
        if (g_LayoutObjHorizontal->posX == 0xFFFE ||
            posX > g_LayoutObjHorizontal->posX) {
            break;
        }
        roomIndex = *((u8*)&g_LayoutObjHorizontal->entityRoomIndex);
        if (roomIndex != 0) {
            roomIndex--;
            if ((g_unkGraphicsStruct.D_80097428[roomIndex >> 5] &
                 (1 << (roomIndex & 0x1F))) == 0) {
                CreateEntityWhenInVerticalRange(g_LayoutObjHorizontal);
            }
        } else {
            CreateEntityWhenInVerticalRange(g_LayoutObjHorizontal);
        }
        g_LayoutObjHorizontal--;
    }
}

static inline void FindFirstEntityAbove(u16 posY) {
    while (true) {
        if (g_LayoutObjVertical->posY != 0xFFFE &&
            g_LayoutObjVertical->posY >= posY) {
            break;
        }
        g_LayoutObjVertical++;
    }
}

static inline void FindFirstEntityBelow(u16 posY) {
    while (true) {
        if (g_LayoutObjVertical->posY != 0xFFFF &&
            (g_LayoutObjVertical->posY <= posY ||
             g_LayoutObjVertical->posY == 0xFFFE)) {
            break;
        }
        g_LayoutObjVertical--;
    }
}

void CreateEntitiesAbove(s16 posY) {
    u8 roomIndex;

    if (g_LayoutObjPosVertical) {
        FindFirstEntityAbove(posY - (DAT_0605c680.g_ScrollDeltaY >> 0x10));
        g_LayoutObjPosVertical = 0;
    }
    while (true) {
        if (g_LayoutObjVertical->posY == 0xFFFF ||
            posY < g_LayoutObjVertical->posY) {
            break;
        }
        roomIndex = g_LayoutObjVertical->entityRoomIndex >> 8;
        if (roomIndex != 0) {
            roomIndex--;
            if ((g_unkGraphicsStruct.D_80097428[roomIndex >> 5] &
                 (1 << (roomIndex & 0x1F))) == 0) {
                CreateEntityWhenInHorizontalRange(g_LayoutObjVertical);
            }
        } else {
            CreateEntityWhenInHorizontalRange(g_LayoutObjVertical);
        }
        g_LayoutObjVertical++;
    }
}

void CreateEntitiesBelow(s16 posY) {
    u8 roomIndex;

    if (posY < 0) {
        posY = 0;
    }
    if (g_LayoutObjPosVertical == 0) {
        FindFirstEntityBelow(posY - (DAT_0605c680.g_ScrollDeltaY >> 0x10));
        g_LayoutObjPosVertical = 1;
    }
    while (true) {
        if (g_LayoutObjVertical->posY == 0xFFFE ||
            posY > g_LayoutObjVertical->posY) {
            break;
        }
        roomIndex = g_LayoutObjVertical->entityRoomIndex >> 8;
        if (roomIndex != 0) {
            roomIndex--;
            if ((g_unkGraphicsStruct.D_80097428[roomIndex >> 5] &
                 (1 << (roomIndex & 0x1F))) == 0) {
                CreateEntityWhenInHorizontalRange(g_LayoutObjVertical);
            }
        } else {
            CreateEntityWhenInHorizontalRange(g_LayoutObjVertical);
        }
        g_LayoutObjVertical--;
    }
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f60666A4, func_060666A4);

void UpdateRoomPosition(void) {
    Tilemap* tilemap = &g_Tilemap;
    s16 tmp;

    if (DAT_0605c680.g_ScrollDeltaX != 0) {
        tmp = tilemap->scrollX.i.hi;
        if (DAT_0605c680.g_ScrollDeltaX > 0) {
            tmp += 0x190;
            CreateEntitiesToTheRight(tmp);
        } else {
            tmp -= 0x50;
            CreateEntitiesToTheLeft(tmp);
        }
    }
    if (DAT_0605c680.g_ScrollDeltaY != 0) {
        tmp = tilemap->scrollY.i.hi;
        if (DAT_0605c680.g_ScrollDeltaY > 0) {
            tmp += 0x130;
            CreateEntitiesAbove(tmp);
        } else {
            tmp -= 0x40;
            CreateEntitiesBelow(tmp);
        }
    }
}

// SAT: func_060668D4
void func_8011A9D8(void) {
    Entity* entity;
    s32 i;

    func_06064684();

    entity = &g_Entities[STAGE_ENTITY_START];
    for (i = STAGE_ENTITY_START; i < TOTAL_ENTITY_COUNT; i++, entity++) {
        if (!(entity->flags & FLAG_UNK_20000)) {
            DestroyEntity(entity);
        }
    }
}
