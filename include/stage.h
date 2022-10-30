#ifndef STAGE_H
#define STAGE_H

#include "common.h"
#include "dra.h"

// Those entity IDs are common across all stages
#define ENTITY_BREAKABLE 1
#define ENTITY_EXPLOSION 2
#define ENTITY_ITEM_DROP 3
#define ENTITY_HUD_DAMAGE 4
#define ENTITY_RED_DOOR 5
#define ENTITY_BIG_FOREGROUND 8
#define ENTITY_STAGE_NAME_POPUP 9
#define ENTITY_HEART_DROP 10
#define ENTITY_RELIC 11
#define ENTITY_COLLECTABLE 12

typedef struct {
    /* 0x0 */ u16 posX;
    /* 0x2 */ u16 posY;
    /* 0x4 */ u16 objectId;
    /* 0x6 */ u16 objectRoomIndex;
    /* 0x8 */ u16 subId;
} LayoutObject; // size = 0xA

typedef (*PfnOverlayEntry)(void);
typedef (*PfnLoadObjectLayout)(s32 layoutId);

s32 Random();
void UpdateStageEntities(void);
void CreateEntity(Entity* entity, LayoutObject* initDesc);
void DestroyEntity(Entity*);
void DestroyEntityFromIndex(s16 index);
s32 AnimateEntity(u8* frames, Entity* entity);
void MoveEntity(void);
void FallEntity(void);
Entity* AllocEntity(Entity* start, Entity* end);
void InitializeEntity(u16* arg0);

#endif
