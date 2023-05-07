#ifndef STAGE_H
#define STAGE_H

#include "common.h"
#include "game.h"
#include "objects.h"
#include "sfx.h"

typedef struct {
    /* 0x0 */ u16 posX;
    /* 0x2 */ u16 posY;
    /* 0x4 */ u16 objectId;
    /* 0x6 */ u16 objectRoomIndex;
    /* 0x8 */ u16 subId;
} LayoutObject; // size = 0xA

s32 Random();
void Update(void);
void CreateEntityFromEntity(u16 objectId, Entity_*source, Entity_*entity);
void CreateEntityFromLayout(Entity_*entity, LayoutObject* initDesc);
void DestroyEntity(Entity_*);
void DestroyEntityFromIndex(s16 index);
s32 AnimateEntity(const u8 frames[], Entity_*entity);
void MoveEntity();
void FallEntity(void);
Entity_*AllocEntity(Entity_*start, Entity_*end);
void InitializeEntity(u16 arg0[]);

#endif
