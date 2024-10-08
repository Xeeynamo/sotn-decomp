// SPDX-License-Identifier: AGPL-3.0-or-later
#include <servant.h>

// all of the shared functions need to be marked static
static s32 AccumulateTowardZero(s32 arg0, s32 arg1);
static s16 CalculateAngleToEntity(Entity* entity, s16 targetX, s16 targetY);
static s32 CalculateDistance(Entity* entity, s32 targetX, s32 targetY);
static s32 CheckAllEntitiesValid(void);
static s32 CheckEntityValid(Entity* entity);
static void CreateEventEntity(Entity* entityParent, s32 entityId, s32 params);
static void DestroyServantEntity(Entity* self);
static s16 GetTargetPositionWithDistanceBuffer(
    s16 currentX, s16 targetX, s16 distanceBuffer);
static s32 IsMovementAllowed(s32 arg0);
static void ProcessEvent(Entity* self, bool resetEvent);
static void ProcessSfxState(Entity* entity);
static Entity* SearchForEntityInRange(s32 rangeIndex, s32 entityId);
static void ServantInit(InitializeMode mode);
static s32 ServantUnk0(void);
static u32 ServantUpdateAnim(
    Entity* self, s8* frameProps, AnimationFrame** frames);
static void SetEntityAnimation(Entity* entity, AnimationFrame* anim);
static void UpdateServantDefault(Entity* self);
