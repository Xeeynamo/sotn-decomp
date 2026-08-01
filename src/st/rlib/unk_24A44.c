// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rlib.h"

extern u16* g_LayoutObjHorizontal;
extern u16* g_LayoutObjVertical;
extern u8 g_LayoutObjPosHorizontal;
extern u8 g_LayoutObjPosVertical;

extern PfnEntityUpdate RLIB_EntityUpdates[];

extern u16* RLIB_pStObjLayoutHorizontal[];
extern u16* RLIB_pStObjLayoutVertical[];

#define LAYOUT_OBJ_START 0xfffe
#define LAYOUT_OBJ_END 0xffff

#define LAYOUT_OBJ_POSITION_FORWARD 0
#define LAYOUT_OBJ_POSITION_BACKWARD 1

#define LAYOUT_OBJ_POS_X 0
#define LAYOUT_OBJ_POS_Y 1
#define LAYOUT_OBJ_ID 2
#define LAYOUT_OBJ_SLOT 3
#define LAYOUT_OBJ_PARAMS 4

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

#define DECREMENT_AND_CHECK(x) --(x) != (u8) - 1

static void CreateEntitiesToTheRight(s16 posX) {
    const s32 expected = false;
    u16* layoutObjHorizontal;
    u8 flag;

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
        if (DECREMENT_AND_CHECK(flag)) {
            if ((g_unkGraphicsStruct.D_80097428[flag >> 5] &
                 (1 << (flag & 0x1F))) == expected) {
                CreateEntityWhenInVerticalRange(
                    (LayoutEntity*)g_LayoutObjHorizontal);
            }
        } else {
            CreateEntityWhenInVerticalRange(
                (LayoutEntity*)g_LayoutObjHorizontal);
        }

        g_LayoutObjHorizontal += sizeof(LayoutEntity) / sizeof(u16);
    }
}

static void CreateEntitiesToTheLeft(s16 posX) {
    const s32 expected = false;
    u16* layoutObjHorizontal;
    u8 flag;

    if (posX < 0) {
        posX = 0;
    }

    if (!g_LayoutObjPosHorizontal) {
        FindFirstEntityToTheLeft(posX - g_ScrollDeltaX);
        g_LayoutObjPosHorizontal = LAYOUT_OBJ_POSITION_BACKWARD;
    }
    while (true) {
        layoutObjHorizontal = g_LayoutObjHorizontal;
        if (layoutObjHorizontal[LAYOUT_OBJ_POS_X] == LAYOUT_OBJ_START) {
            return;
        }

        if (posX > layoutObjHorizontal[LAYOUT_OBJ_POS_X]) {
            return;
        }

        flag = (layoutObjHorizontal[LAYOUT_OBJ_SLOT] >> 8);
        if (DECREMENT_AND_CHECK(flag)) {
            if ((g_unkGraphicsStruct.D_80097428[flag >> 5] &
                 (1 << (flag & 0x1F))) == expected) {
                CreateEntityWhenInVerticalRange(
                    (LayoutEntity*)g_LayoutObjHorizontal);
            }
        } else {
            CreateEntityWhenInVerticalRange(
                (LayoutEntity*)g_LayoutObjHorizontal);
        }

        g_LayoutObjHorizontal -= sizeof(LayoutEntity) / sizeof(u16);
    }
}

static void FindFirstEntityAbove(s16 posY) {
    while (true) {
        u16* ptr = &g_LayoutObjVertical[LAYOUT_OBJ_POS_Y];
        if (*ptr != LAYOUT_OBJ_START && *ptr >= posY) {
            break;
        }
        g_LayoutObjVertical += sizeof(LayoutEntity) / sizeof(u16);
    }
}

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

static void CreateEntitiesAbove(s16 posY) {
    const s32 expected = false;
    u16* layout;
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
        if (DECREMENT_AND_CHECK(flag)) {
            if ((g_unkGraphicsStruct.D_80097428[flag >> 5] &
                 (1 << (flag & 0x1F))) == expected) {
                CreateEntityWhenInHorizontalRange(
                    (LayoutEntity*)g_LayoutObjVertical);
            }
        } else {
            CreateEntityWhenInHorizontalRange(
                (LayoutEntity*)g_LayoutObjVertical);
        }

        g_LayoutObjVertical += sizeof(LayoutEntity) / sizeof(u16);
    }
}

static void CreateEntitiesBelow(s16 posY) {
    const s32 expected = false;
    u16* layout;
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
        if (DECREMENT_AND_CHECK(flag)) {
            if ((g_unkGraphicsStruct.D_80097428[flag >> 5] &
                 (1 << (flag & 0x1F))) == expected) {
                CreateEntityWhenInHorizontalRange(
                    (LayoutEntity*)g_LayoutObjVertical);
            }
        } else {
            CreateEntityWhenInHorizontalRange(
                (LayoutEntity*)g_LayoutObjVertical);
        }

        g_LayoutObjVertical -= sizeof(LayoutEntity) / sizeof(u16);
    }
}

void InitRoomEntities(s32 objLayoutId) {
    Tilemap* tilemap = &g_Tilemap;
    s16 rightEdge;
    s16 temp;
    s16 i;

    g_LayoutObjHorizontal = (u16*)RLIB_pStObjLayoutHorizontal[objLayoutId];
    g_LayoutObjVertical = (u16*)RLIB_pStObjLayoutVertical[objLayoutId];

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
    entity->pfnUpdate = RLIB_EntityUpdates[entityId - 1];
    entity->posX.i.hi = g_CurrentEntity->posX.i.hi;
    entity->posY.i.hi = g_CurrentEntity->posY.i.hi;
}

void CreateEntityFromEntity(u16 entityId, Entity* source, Entity* entity) {
    DestroyEntity(entity);
    entity->entityId = entityId;
    entity->pfnUpdate = RLIB_EntityUpdates[entityId - 1];
    entity->posX.i.hi = source->posX.i.hi;
    entity->posY.i.hi = source->posY.i.hi;
}
