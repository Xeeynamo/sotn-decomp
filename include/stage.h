#ifndef STAGE_H
#define STAGE_H
#define STAGE 0xCC

#include "common.h"
#include "game.h"
#include "items.h"
#include "objects.h"
#include "sfx.h"

typedef struct {
    /* 0x0 */ u16 posX;
    /* 0x2 */ u16 posY;
    /* 0x4 */ u16 entityId;
    /* 0x6 */ u16 entityRoomIndex;
    /* 0x8 */ u16 params;
} LayoutEntity; // size = 0xA

#if defined(VERSION_PSP)
// A horizontally ordered array with head and tail sigils in the 1st field
extern LayoutEntity** g_pStObjLayoutHorizontal;
// A vertically ordered array with head and tail sigils in the 1st field
extern LayoutEntity** g_pStObjLayoutVertical;

#else
// A horizontally ordered array with head and tail sigils in the 1st field
extern LayoutEntity* g_pStObjLayoutHorizontal[];
// A vertically ordered array with head and tail sigils in the 1st field
extern LayoutEntity* g_pStObjLayoutVertical[];

#endif

#if defined(VERSION_PSP)
extern PfnEntityUpdate* PfnEntityUpdates;
#else
extern PfnEntityUpdate PfnEntityUpdates[];
#endif

extern u16 g_ItemIconSlots[0x20];

/*
 * Sets up layout arrays and initializes stage state to
 * initial values.
 *
 * - Parameters:
 *   - objLayoutId - the room to initialize
 */
void InitRoomEntities(s32 objLayoutId);

/*
 * An callback for notifying the stage that the
 * viewport has changed.
 */
void UpdateRoomPosition();

void Update(void);

void HitDetection(void);

s32 Random();
void CreateEntityFromEntity(u16 entityId, Entity* source, Entity* entity);
void CreateEntityFromLayout(Entity* entity, LayoutEntity* initDesc);
void DestroyEntity(Entity*);
void DestroyEntitiesFromIndex(s16 index);
void MoveEntity();
void FallEntity(void);
Entity* AllocEntity(Entity* start, Entity* end);
void InitializeEntity(u16 arg0[]);

#endif
