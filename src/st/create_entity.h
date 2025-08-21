// SPDX-License-Identifier: AGPL-3.0-or-later
//
// Section Sizes:
//
//         | Data  | RO Data | Text  | BSS  |
// --------+-------+---------+-------+------+
//  PSX US | TBD   | TBD     | 0xB78 | 0x10 |
//  PSX HD | TBD   | TBD     | 0xB78 | 0x10 |
//

#include <common.h>

static u16* g_LayoutObjHorizontal;
static u16* g_LayoutObjVertical;
static u8 g_LayoutObjPosHorizontal;
STATIC_PAD_BSS(3);
static u8 g_LayoutObjPosVertical;
STATIC_PAD_BSS(3);

#define LAYOUT_OBJ_START 0xfffe
#define LAYOUT_OBJ_END 0xffff

#define LAYOUT_OBJ_POSITION_FORWARD 0
#define LAYOUT_OBJ_POSITION_BACKWARD 1

// Follows the struct from LayoutEntity
#define LAYOUT_OBJ_POS_X 0
#define LAYOUT_OBJ_POS_Y 1
#define LAYOUT_OBJ_ID 2
#define LAYOUT_OBJ_SLOT 3
#define LAYOUT_OBJ_PARAMS 4

void CreateEntityFromLayout(Entity* entity, LayoutEntity* initDesc) {
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

void CreateEntityWhenInVerticalRange(LayoutEntity* obj) {
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
            CreateEntityFromLayout(entity, obj);
        }
        break;
    case 0xA000:
        entity =
            g_Entities + STAGE_ENTITY_START + (obj->entityRoomIndex & 0xFF);
        CreateEntityFromLayout(entity, obj);
        break;
    case 0x8000:
        break;
    }
}

void CreateEntityWhenInHorizontalRange(LayoutEntity* obj) {
    s16 xClose;
    s16 xFar;
    s16 posX;
    Entity* entity;
    Tilemap* tilemap;

    tilemap = &g_Tilemap;
    posX = tilemap->scrollX.i.hi;
    xClose = posX - 0x40;
    xFar = posX + 0x140;
    if (xClose < 0) {
        xClose = 0;
    }

    posX = obj->posX;
    if (posX < xClose || posX > xFar) {
        return;
    }

    switch (obj->entityId & 0xE000) {
    case 0x0:
        entity =
            g_Entities + STAGE_ENTITY_START + (obj->entityRoomIndex & 0xFF);
        if (!entity->entityId) {
            CreateEntityFromLayout(entity, obj);
        }
        break;
    case 0xA000:
        entity =
            g_Entities + STAGE_ENTITY_START + (obj->entityRoomIndex & 0xFF);
        CreateEntityFromLayout(entity, obj);
        break;
    case 0x8000:
        break;
    }
}

/*
 * Scans `g_LayoutObjVertical` looking for the next element with
 * an x  position to the right of the provided argument or the end
 * of the list.
 *
 * - Parameters:
 *   - posX - the position to search for
 *
 * - Side Effects:
 *    `g_LayoutObjHorizontal` will be positioned at an element with a
 *    x position larger than `posX` or the tail eleement.
 */
static void FindFirstEntityToTheRight(s16 posX) {
    while (1) {
        u16* layoutEntity = g_LayoutObjHorizontal;
        if (layoutEntity[LAYOUT_OBJ_POS_X] != LAYOUT_OBJ_START &&
            layoutEntity[LAYOUT_OBJ_POS_X] >= posX) {
            break;
        }

        g_LayoutObjHorizontal += sizeof(LayoutEntity) / sizeof(u16);
    }
}

/*
 * Scans `g_LayoutObjHorizontal` looking for the next element with an x
 * position below the provided argument or the beginning of the list.
 *
 * - Parameters:
 *   - posX - the position to search for
 *
 * - Side Effects:
 *    `g_LayoutObjVertical` will be positioned at an element with an
 *    x position smaller than `posX` or the head element.
 */
static void FindFirstEntityToTheLeft(s16 posX) {
    while (true) {
        u16* layoutEntity = g_LayoutObjHorizontal;
        if (layoutEntity[LAYOUT_OBJ_POS_X] != LAYOUT_OBJ_END &&
            (layoutEntity[LAYOUT_OBJ_POS_X] <= posX ||
             layoutEntity[LAYOUT_OBJ_POS_X] == LAYOUT_OBJ_START)) {
            break;
        }
        g_LayoutObjHorizontal -= sizeof(LayoutEntity) / sizeof(u16);
    }
}

/*
 * Creates entities between the previous horizontal position and
 * the passed in x position toward the right.
 *
 * - Parameters:
 *   - posX - the new right extent
 */
static void CreateEntitiesToTheRight(s16 posX) {
    u16* layoutObjHorizontal;
    s32 expected;
    u8 flag;

    // if previously scrolling left, scan right to the
    // previous x delta and start traversal from there
    // otherwise keep going from the current position.
    if (g_LayoutObjPosHorizontal) {
        FindFirstEntityToTheRight(posX - g_ScrollDeltaX);
        g_LayoutObjPosHorizontal = LAYOUT_OBJ_POSITION_FORWARD;
    }

    while (true) {
        layoutObjHorizontal = g_LayoutObjHorizontal;
        if (layoutObjHorizontal[LAYOUT_OBJ_POS_X] == LAYOUT_OBJ_END ||
            posX < layoutObjHorizontal[LAYOUT_OBJ_POS_X]) {
            break;
        }

        flag = (layoutObjHorizontal[LAYOUT_OBJ_SLOT] >> 8);
#ifdef VERSION_PSP
        if (flag--) {
            if (!(g_unkGraphicsStruct.D_80097428[flag >> 5] &
                  (1 << (flag & 0x1F)))) {
                CreateEntityWhenInVerticalRange(
                    (LayoutEntity*)g_LayoutObjHorizontal);
            }
        } else {
            CreateEntityWhenInVerticalRange(
                (LayoutEntity*)g_LayoutObjHorizontal);
        }
#else
        expected = 0;
        if (--flag == 0xFF || (g_unkGraphicsStruct.D_80097428[flag >> 5] &
                               (1 << (flag & 0x1F))) == expected) {
            CreateEntityWhenInVerticalRange(
                (LayoutEntity*)g_LayoutObjHorizontal);
        }
#endif
        g_LayoutObjHorizontal += sizeof(LayoutEntity) / sizeof(u16);
    }
}

/*
 * Creates entities between the previous horizontal position and
 * the passed in x position.
 *
 * - Parameters:
 *   - posX - the new left extent
 */
static void CreateEntitiesToTheLeft(s16 posX) {
    u16* layoutObjHorizontal;
    s32 expected;
    u8 flag;

    if (posX < 0) {
        posX = 0;
    }

    if (!g_LayoutObjPosHorizontal) {
        FindFirstEntityToTheLeft(posX - g_ScrollDeltaX);
        g_LayoutObjPosHorizontal = LAYOUT_OBJ_POSITION_BACKWARD;
    }
// MAD only runs once to create one entity to the left.
#if !defined(VERSION_BETA)
    while (true) {
#else
    if (true) {
#endif
        layoutObjHorizontal = g_LayoutObjHorizontal;
        if (layoutObjHorizontal[LAYOUT_OBJ_POS_X] == LAYOUT_OBJ_START) {
            return;
        }

        if (posX > layoutObjHorizontal[LAYOUT_OBJ_POS_X]) {
            return;
        }

        flag = (layoutObjHorizontal[LAYOUT_OBJ_SLOT] >> 8);
#ifdef VERSION_PSP
        if (flag--) {
            if (!(g_unkGraphicsStruct.D_80097428[flag >> 5] &
                  (1 << (flag & 0x1F)))) {
                CreateEntityWhenInVerticalRange(
                    (LayoutEntity*)g_LayoutObjHorizontal);
            }
        } else {
            CreateEntityWhenInVerticalRange(
                (LayoutEntity*)g_LayoutObjHorizontal);
        }
#else
        expected = 0;
        if (--flag == 0xFF || (g_unkGraphicsStruct.D_80097428[flag >> 5] &
                               (1 << (flag & 0x1F))) == expected) {
            CreateEntityWhenInVerticalRange(
                (LayoutEntity*)g_LayoutObjHorizontal);
        }
#endif
        g_LayoutObjHorizontal -= sizeof(LayoutEntity) / sizeof(u16);
    }
}

/*
 * Scans `g_LayoutObjVertical` looking for the next element with
 * a y position above the provided argument or the end of the list.
 *
 * - Parameters:
 *   - posY - the position to search for
 *
 * - Side Effects:
 *    `g_LayoutObjVertical` will be positioned at an element with a
 *    y position larger than `posY` or the tail eleement.
 */
static void FindFirstEntityAbove(s16 posY) {
    while (true) {
        u16* ptr = &g_LayoutObjVertical[LAYOUT_OBJ_POS_Y];
        if (*ptr != LAYOUT_OBJ_START && *ptr >= posY) {
            break;
        }
        g_LayoutObjVertical += sizeof(LayoutEntity) / sizeof(u16);
    }
}

/*
 * Scans `g_LayoutObjVertical` looking for the next element with a y
 * position below the provided argument or the beginning of the list.
 *
 * - Parameters:
 *   - posY - the position to search for
 *
 * - Side Effects:
 *    `g_LayoutObjVertical` will be positioned at an element with a
 *    y position smaller than `posY` or the head element.
 */
static void FindFirstEntityBelow(s16 posY) {
    while (true) {
        u16* ptr = &g_LayoutObjVertical[LAYOUT_OBJ_POS_Y];
        if (*ptr != LAYOUT_OBJ_END &&
            (*ptr <= posY || *ptr == LAYOUT_OBJ_START)) {
            break;
        }
        g_LayoutObjVertical -= sizeof(LayoutEntity) / sizeof(u16);
    }
}

/*
 * Creates entities between the previous vertical position and
 * the passed in y position going up.
 *
 * - Parameters:
 *   - posY - the new top extent
 */
static void CreateEntitiesAbove(s16 posY) {
    u16* layout;
    s32 expected;
    u8 flag;

    if (g_LayoutObjPosVertical) {
        FindFirstEntityAbove(posY - g_ScrollDeltaY);
        g_LayoutObjPosVertical = LAYOUT_OBJ_POSITION_FORWARD;
    }

    while (true) {
        layout = &g_LayoutObjVertical[LAYOUT_OBJ_POS_Y];

        if (layout[LAYOUT_OBJ_POS_X] == LAYOUT_OBJ_END ||
            posY < layout[LAYOUT_OBJ_POS_X]) {
            break;
        }

        flag = layout[LAYOUT_OBJ_ID] >> 8;
#ifdef VERSION_PSP
        if (flag--) {
            if (!(g_unkGraphicsStruct.D_80097428[flag >> 5] &
                  (1 << (flag & 0x1F)))) {
                CreateEntityWhenInHorizontalRange(
                    (LayoutEntity*)g_LayoutObjVertical);
            }
        } else {
            CreateEntityWhenInHorizontalRange(
                (LayoutEntity*)g_LayoutObjVertical);
        }
#else
        expected = 0;
        if (--flag == 0xFF || (g_unkGraphicsStruct.D_80097428[flag >> 5] &
                               (1 << (flag & 0x1F))) == expected) {
            CreateEntityWhenInHorizontalRange(
                (LayoutEntity*)g_LayoutObjVertical);
        }
#endif
        g_LayoutObjVertical += sizeof(LayoutEntity) / sizeof(u16);
    }
}

/*
 * Creates entities between the previous vertical position and
 * the passed in y position going down.
 *
 * - Parameters:
 *   - posY - the new top extent
 */
static void CreateEntitiesBelow(s16 posY) {
    u16* layout;
    s32 expected;
    u8 flag;

    if (posY < 0) {
        posY = 0;
    }

    if (!g_LayoutObjPosVertical) {
        FindFirstEntityBelow(posY - g_ScrollDeltaY);
        g_LayoutObjPosVertical = LAYOUT_OBJ_POSITION_BACKWARD;
    }

    while (true) {
        layout = &g_LayoutObjVertical[LAYOUT_OBJ_POS_Y];
        if (layout[LAYOUT_OBJ_POS_X] == LAYOUT_OBJ_START ||
            (posY > layout[LAYOUT_OBJ_POS_X])) {
            break;
        }
        flag = layout[LAYOUT_OBJ_ID] >> 8;
#ifdef VERSION_PSP
        if (flag--) {
            if (!(g_unkGraphicsStruct.D_80097428[flag >> 5] &
                  (1 << (flag & 0x1F)))) {
                CreateEntityWhenInHorizontalRange(
                    (LayoutEntity*)g_LayoutObjVertical);
            }
        } else {
            CreateEntityWhenInHorizontalRange(
                (LayoutEntity*)g_LayoutObjVertical);
        }
#else
        expected = 0;
        if (--flag == 0xFF || (g_unkGraphicsStruct.D_80097428[flag >> 5] &
                               (1 << (flag & 0x1F))) == expected) {
            CreateEntityWhenInHorizontalRange(
                (LayoutEntity*)g_LayoutObjVertical);
        }
#endif
        g_LayoutObjVertical -= sizeof(LayoutEntity) / sizeof(u16);
    }
}

/*
 * Sets up layout arrays and initializes stage state to
 * initial values.
 *
 * - Parameters:
 *   - objLayoutId - the room to initialize
 */
void InitRoomEntities(s32 objLayoutId) {
    Tilemap* tilemap = &g_Tilemap;
    s16 rightEdge;
    s16 temp;
    s16 i;

    g_LayoutObjHorizontal = (u16*)OBJ_LAYOUT_HORIZONTAL[objLayoutId];
    g_LayoutObjVertical = (u16*)OBJ_LAYOUT_VERTICAL[objLayoutId];

    if (*g_LayoutObjHorizontal != LAYOUT_OBJ_START) {
        g_LayoutObjHorizontal++;
        temp = Random() & 0xFF;
        for (i = 0; true; i++) {
            temp -= *g_LayoutObjHorizontal++;
            if (temp < 0) {
                g_LayoutObjHorizontal =
                    (u16*)((g_LayoutObjHorizontal[LAYOUT_OBJ_POS_Y] << 16) +
                           g_LayoutObjHorizontal[LAYOUT_OBJ_POS_X]);
                break;
            }
            g_LayoutObjHorizontal += 2;
        }
        g_LayoutObjVertical += i * 2 + 2;
        g_LayoutObjVertical =
            (u16*)((g_LayoutObjVertical[LAYOUT_OBJ_POS_Y] << 0x10) +
                   g_LayoutObjVertical[LAYOUT_OBJ_POS_X]);
    }
    temp = tilemap->scrollX.i.hi;
    i = temp - 64;
    rightEdge = temp + 320;

    if (i < 0) {
        i = 0;
    }

    g_LayoutObjPosHorizontal = LAYOUT_OBJ_POSITION_FORWARD;
    g_LayoutObjPosVertical = LAYOUT_OBJ_POSITION_FORWARD;
    FindFirstEntityToTheRight(i);
    CreateEntitiesToTheRight(rightEdge);
    temp = tilemap->scrollY.i.hi;
    i = temp + 288;
    FindFirstEntityAbove(i);
}

/*
 * Creates any new entities that may need to be created
 * based on a change in the scroll delta.
 */
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
