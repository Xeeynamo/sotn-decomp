// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include "game.h"

void PlaySfx(s32 sfxId);

extern u16* g_LayoutObjHorizontal;
extern u16* g_LayoutObjVertical;
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

static inline void FindFirstEntityToTheRight(s16 posX) {
    while (true) {
        if (g_LayoutObjHorizontal[0] != 0xFFFE &&
            g_LayoutObjHorizontal[0] >= (u16)posX) {
            break;
        }
        g_LayoutObjHorizontal += 5;
    }
}

static inline void FindFirstEntityToTheLeft(s16 posX) {
    while (true) {
        if (g_LayoutObjHorizontal[0] != 0xFFFF &&
            (g_LayoutObjHorizontal[0] <= (u16)posX ||
             g_LayoutObjHorizontal[0] == 0xFFFE)) {
            break;
        }
        g_LayoutObjHorizontal -= 5;
    }
}

void CreateEntitiesToTheRight(s16 posX) {
    u8 roomIndex;

    if (g_LayoutObjPosHorizontal) {
        FindFirstEntityToTheRight(posX - (DAT_0605c680.g_ScrollDeltaX >> 0x10));
        g_LayoutObjPosHorizontal = 0;
    }
    while (true) {
        if (g_LayoutObjHorizontal[0] == 0xFFFF ||
            posX < g_LayoutObjHorizontal[0]) {
            break;
        }
        roomIndex = g_LayoutObjHorizontal[3] >> 8;
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
        g_LayoutObjHorizontal += 5;
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
        if (g_LayoutObjHorizontal[0] == 0xFFFE ||
            posX > g_LayoutObjHorizontal[0]) {
            break;
        }
        roomIndex = *((u8*)&g_LayoutObjHorizontal[3]);
        if (roomIndex != 0) {
            roomIndex--;
            if ((g_unkGraphicsStruct.D_80097428[roomIndex >> 5] &
                 (1 << (roomIndex & 0x1F))) == 0) {
                CreateEntityWhenInVerticalRange(g_LayoutObjHorizontal);
            }
        } else {
            CreateEntityWhenInVerticalRange(g_LayoutObjHorizontal);
        }
        g_LayoutObjHorizontal -= 5;
    }
}

static inline void FindFirstEntityAbove(u16 posY) {
    while (true) {
        if (g_LayoutObjVertical[1] != 0xFFFE &&
            g_LayoutObjVertical[1] >= posY) {
            break;
        }
        g_LayoutObjVertical += 5;
    }
}

static inline void FindFirstEntityBelow(u16 posY) {
    while (true) {
        if (g_LayoutObjVertical[1] != 0xFFFF &&
            (g_LayoutObjVertical[1] <= posY ||
             g_LayoutObjVertical[1] == 0xFFFE)) {
            break;
        }
        g_LayoutObjVertical -= 5;
    }
}

void CreateEntitiesAbove(s16 posY) {
    u8 roomIndex;

    if (g_LayoutObjPosVertical) {
        FindFirstEntityAbove(posY - (DAT_0605c680.g_ScrollDeltaY >> 0x10));
        g_LayoutObjPosVertical = 0;
    }
    while (true) {
        if (g_LayoutObjVertical[1] == 0xFFFF || posY < g_LayoutObjVertical[1]) {
            break;
        }
        roomIndex = g_LayoutObjVertical[3] >> 8;
        if (roomIndex != 0) {
            roomIndex--;
            if ((g_unkGraphicsStruct.D_80097428[roomIndex >> 5] &
                 (1 << (roomIndex & 0x1F))) == 0) {
                CreateEntityWhenInHorizontalRange(g_LayoutObjVertical);
            }
        } else {
            CreateEntityWhenInHorizontalRange(g_LayoutObjVertical);
        }
        g_LayoutObjVertical += 5;
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
        if (g_LayoutObjVertical[1] == 0xFFFE || posY > g_LayoutObjVertical[1]) {
            break;
        }
        roomIndex = g_LayoutObjVertical[3] >> 8;
        if (roomIndex != 0) {
            roomIndex--;
            if ((g_unkGraphicsStruct.D_80097428[roomIndex >> 5] &
                 (1 << (roomIndex & 0x1F))) == 0) {
                CreateEntityWhenInHorizontalRange(g_LayoutObjVertical);
            }
        } else {
            CreateEntityWhenInHorizontalRange(g_LayoutObjVertical);
        }
        g_LayoutObjVertical -= 5;
    }
}

extern u16** DAT_060645e4;
extern u16** DAT_060645f8;

void InitRoomEntities(s32 param_1) {
    Tilemap* tilemap;
    s16 temp;
    s16 i;
    u16* ptrV;
    u16* ptrH;
    s32 iVar9;
    s16 rightEdge;

    if (param_1 >= 0x60) {
        u16 uVar5 = D_8003C708.flags & 0x63;

        switch (uVar5) {
        case 0x20:
            param_1 = 0x30;
            break;
        case 0x21:
            param_1 = 0x31;
            break;
        case 0x22:
            param_1 = 0x32;
            break;
        default:
            param_1 = 0x0;
            break;
        }
    } else if (param_1 == 0x50) {
        switch (D_8003C708.flags & 0x63) {
        case 0x40:
            param_1 = 0x33;
            break;
        case 0x41:
            param_1 = 0x34;
            break;
        default:
            param_1 = 0;
            break;
        }
    } else {
        param_1++;
    }
    iVar9 = DAT_0605d750.unk8 * 0x35 + param_1;
    g_LayoutObjHorizontal = DAT_060645e4[iVar9];
    g_LayoutObjVertical = DAT_060645f8[iVar9];
    ptrH = g_LayoutObjHorizontal;
    ptrV = g_LayoutObjVertical;
    if (*ptrH != 0xFFFE) {
        ptrH++;
        temp = Random() & 0xFF;
        for (i = 0; true; i++) {
            temp -= *ptrH++;
            if (temp < 0) {
                break;
            }
            ptrH += 2;
        }
        g_LayoutObjHorizontal = (u16*)(ptrH[1] * 0x10000 + ptrH[0]);
        ptrV += i * 2 + 2;
        g_LayoutObjVertical = (u16*)(ptrV[1] * 0x10000 + ptrV[0]);
    }
    tilemap = &g_Tilemap;
    temp = tilemap->scrollX.i.hi;
    i = temp - 0x50;
    rightEdge = temp + 0x190;

    if (i < 0) {
        i = 0;
    }

    g_LayoutObjPosHorizontal = 0;
    g_LayoutObjPosVertical = 0;
    FindFirstEntityToTheRight(i);
    CreateEntitiesToTheRight(rightEdge);
    temp = tilemap->scrollY.i.hi;
    FindFirstEntityAbove(temp + 0x130);
    if ((g_PlayableCharacter == 0) && (g_Servant == 1)) {
        func_060CF01C(&g_Entities[4]);
    }
}

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
