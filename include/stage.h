#ifndef STAGE_H
#define STAGE_H

#include "common.h"
#include "dra.h"

void CreateEntity(Entity *entity, ObjectInit* initDesc);
void DestroyEntity(Entity *);
void DestroyEntityFromIndex(s16 index);
s32 AnimateEntity(u8 *frames, Entity *entity);
Entity *AllocEntity(Entity* start, Entity* end);
void InitializeEntity(u16 *arg0);

#endif
