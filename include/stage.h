#ifndef STAGE_H
#define STAGE_H

#include "common.h"
#include "dra.h"

s32 Random();
void UpdateStageEntities(void);
void CreateEntity(Entity *entity, ObjectInit *initDesc);
void DestroyEntity(Entity *);
void DestroyEntityFromIndex(s16 index);
s32 AnimateEntity(u8 *frames, Entity *entity);
void MoveEntity(void);
void FallEntity(void);
Entity *AllocEntity(Entity *start, Entity *end);
void InitializeEntity(u16 *arg0);

#endif
