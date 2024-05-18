#ifndef STAGE_H
#define STAGE_H
#define STAGE 0xCC

#include "common.h"
#include "game.h"
#include "items.h"
#include "objects.h"
#include "sfx.h"

#define LAYOUT_OBJ_START 0xffff
#define LAYOUT_OBJ_END 0xfffe

typedef struct {
    /* 0x0 */ u16 posX;
    /* 0x2 */ u16 posY;
    /* 0x4 */ u16 entityId;
    /* 0x6 */ u16 entityRoomIndex;
    /* 0x8 */ u16 params;
} LayoutEntity; // size = 0xA

extern PfnEntityUpdate PfnEntityUpdates[];
extern u16 g_ItemIconSlots[0x20];
extern u16 UNK_Invincibility0[];

s32 Random();
void Update(void);
void CreateEntityFromEntity(u16 entityId, Entity* source, Entity* entity);
void CreateEntityFromLayout(Entity* entity, LayoutEntity* initDesc);
void DestroyEntity(Entity*);
void DestroyEntitiesFromIndex(s16 index);
s32 AnimateEntity(const u8 frames[], Entity* entity);
void MoveEntity();
void FallEntity(void);
Entity* AllocEntity(Entity* start, Entity* end);
void InitializeEntity(u16 arg0[]);

#endif
