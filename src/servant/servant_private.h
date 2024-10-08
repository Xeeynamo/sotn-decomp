// SPDX-License-Identifier: AGPL-3.0-or-later
#include <servant.h>

#ifndef VERSION_PSP
#define STATIC static
#else
#define STATIC
#endif

// all of the shared functions need to be marked static for PC build due to name
// collisions
STATIC s32 AccumulateTowardZero(s32 arg0, s32 arg1);
STATIC s16 CalculateAngleToEntity(Entity* entity, s16 targetX, s16 targetY);
STATIC s32 CalculateDistance(Entity* entity, s32 targetX, s32 targetY);
STATIC s32 CheckAllEntitiesValid(void);
STATIC s32 CheckEntityValid(Entity* entity);
STATIC void CreateEventEntity(Entity* entityParent, s32 entityId, s32 params);
STATIC void DestroyServantEntity(Entity* self);
STATIC s16 GetTargetPositionWithDistanceBuffer(
    s16 currentX, s16 targetX, s16 distanceBuffer);
STATIC s32 IsMovementAllowed(s32 arg0);
STATIC void ProcessEvent(Entity* self, bool resetEvent);
STATIC void ProcessSfxState(Entity* entity);
STATIC Entity* SearchForEntityInRange(s32 rangeIndex, s32 entityId);
STATIC void ServantInit(InitializeMode mode);
STATIC s32 ServantUnk0(void);
STATIC u32 ServantUpdateAnim(
    Entity* self, s8* frameProps, AnimationFrame** frames);
STATIC void SetEntityAnimation(Entity* entity, AnimationFrame* anim);
STATIC void UpdateServantDefault(Entity* self);
