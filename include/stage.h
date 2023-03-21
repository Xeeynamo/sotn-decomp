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
void CreateEntityFromLayout(Entity* entity, LayoutObject* initDesc);
void DestroyEntity(Entity*);
void DestroyEntityFromIndex(s16 index);
s32 AnimateEntity(const u8 frames[], Entity* entity);
void MoveEntity(void);
void FallEntity(void);
Entity* AllocEntity(Entity* start, Entity* end);
void InitializeEntity(u16 arg0[]);

#endif
