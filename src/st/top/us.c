#include "common.h"

// e_room_gb

INCLUDE_ASM("st/top/nonmatchings/us", TOP_EntityBackgroundBlock);

// e_lock_camera

INCLUDE_ASM("st/top/nonmatchings/us", PlayerIsWithinHitbox);

INCLUDE_ASM("st/top/nonmatchings/us", func_us_801A8D84);

INCLUDE_ASM("st/top/nonmatchings/us", func_us_801A9250);

INCLUDE_ASM("st/top/nonmatchings/us", func_us_801A9390);

INCLUDE_ASM("st/top/nonmatchings/us", func_801A8328);

INCLUDE_ASM("st/top/nonmatchings/us", func_us_801A99EC);

INCLUDE_ASM("st/top/nonmatchings/us", func_us_801A9CB8);

INCLUDE_ASM("st/top/nonmatchings/us", func_us_801A9F0C);

INCLUDE_ASM("st/top/nonmatchings/us", func_us_801AA354);

INCLUDE_ASM("st/top/nonmatchings/us", func_us_801AA624);

INCLUDE_ASM("st/top/nonmatchings/us", func_us_801AABA4);

INCLUDE_ASM("st/top/nonmatchings/us", func_us_801AB308);

INCLUDE_ASM("st/top/nonmatchings/us", func_us_801AB45C);

INCLUDE_ASM("st/top/nonmatchings/us", func_us_801AB67C);

// cutscene

INCLUDE_ASM("st/top/nonmatchings/us", CutsceneUnk1);

INCLUDE_ASM("st/top/nonmatchings/us", SetCutsceneScript);

INCLUDE_ASM("st/top/nonmatchings/us", CutsceneUnk3);

INCLUDE_ASM("st/top/nonmatchings/us", CutsceneUnk4);

INCLUDE_ASM("st/top/nonmatchings/us", DrawCutsceneActorName);

INCLUDE_ASM("st/top/nonmatchings/us", SetCutsceneEnd);

INCLUDE_ASM("st/top/nonmatchings/us", CutsceneRun);

INCLUDE_ASM("st/top/nonmatchings/us", CutsceneSkip);

INCLUDE_ASM("st/top/nonmatchings/us", ScaleCutsceneAvatar);

INCLUDE_RODATA("st/top/nonmatchings/us", D_us_801A898C);

INCLUDE_RODATA("st/top/nonmatchings/us", D_us_801A8998);

INCLUDE_RODATA("st/top/nonmatchings/us", D_us_801A89A0);

INCLUDE_ASM("st/top/nonmatchings/us", NZ0_EntityCutscene);

// end cutscene? or does it include the next 3 functions`

INCLUDE_ASM("st/top/nonmatchings/us", func_us_801AD11C);

INCLUDE_ASM("st/top/nonmatchings/us", func_us_801AD320);

INCLUDE_ASM("st/top/nonmatchings/us", func_us_801AD400);

// st_update

INCLUDE_ASM("st/top/nonmatchings/us", Random);

INCLUDE_ASM("st/top/nonmatchings/us", Update);

INCLUDE_ASM("st/top/nonmatchings/us", UpdateStageEntities);

INCLUDE_ASM("st/top/nonmatchings/us", HitDetection);

INCLUDE_ASM("st/top/nonmatchings/us", EntityDamageDisplay);

INCLUDE_ASM("st/top/nonmatchings/us", CreateEntityFromLayout);

INCLUDE_ASM("st/top/nonmatchings/us", CreateEntityWhenInVerticalRange);

INCLUDE_ASM("st/top/nonmatchings/us", CreateEntityWhenInHorizontalRange);

INCLUDE_ASM("st/top/nonmatchings/us", FindFirstEntityToTheRight);

INCLUDE_ASM("st/top/nonmatchings/us", FindFirstEntityToTheLeft);

INCLUDE_ASM("st/top/nonmatchings/us", CreateEntitiesToTheRight);

INCLUDE_ASM("st/top/nonmatchings/us", CreateEntitiesToTheLeft);

INCLUDE_ASM("st/top/nonmatchings/us", FindFirstEntityAbove);

INCLUDE_ASM("st/top/nonmatchings/us", FindFirstEntityBelow);

INCLUDE_ASM("st/top/nonmatchings/us", CreateEntitiesAbove);

INCLUDE_ASM("st/top/nonmatchings/us", CreateEntitiesBelow);

INCLUDE_ASM("st/top/nonmatchings/us", InitRoomEntities);

INCLUDE_ASM("st/top/nonmatchings/us", UpdateRoomPosition);

INCLUDE_ASM("st/top/nonmatchings/us", CreateEntityFromCurrentEntity);

INCLUDE_ASM("st/top/nonmatchings/us", CreateEntityFromEntity);

INCLUDE_ASM("st/top/nonmatchings/us", EntityIsNearPlayer);

INCLUDE_ASM("st/top/nonmatchings/us", TOP_EntityRedDoor);

INCLUDE_ASM("st/top/nonmatchings/us", DestroyEntity);

INCLUDE_ASM("st/top/nonmatchings/us", DestroyEntitiesFromIndex);

INCLUDE_ASM("st/top/nonmatchings/us", PreventEntityFromRespawning);

INCLUDE_ASM("st/top/nonmatchings/us", AnimateEntity);

INCLUDE_ASM("st/top/nonmatchings/us", UnkAnimFunc);

INCLUDE_ASM("st/top/nonmatchings/us", GetDistanceToPlayerX);

INCLUDE_ASM("st/top/nonmatchings/us", GetDistanceToPlayerY);

INCLUDE_ASM("st/top/nonmatchings/us", GetSideToPlayer);

INCLUDE_ASM("st/top/nonmatchings/us", MoveEntity);

INCLUDE_ASM("st/top/nonmatchings/us", FallEntity);

INCLUDE_ASM("st/top/nonmatchings/us", UnkCollisionFunc3);

INCLUDE_ASM("st/top/nonmatchings/us", UnkCollisionFunc2);

INCLUDE_ASM("st/top/nonmatchings/us", AllocEntity);

INCLUDE_ASM("st/top/nonmatchings/us", GetSineScaled);

INCLUDE_ASM("st/top/nonmatchings/us", GetSine);

INCLUDE_ASM("st/top/nonmatchings/us", SetEntityVelocityFromAngle);

INCLUDE_ASM("st/top/nonmatchings/us", Ratan2Shifted);

INCLUDE_ASM("st/top/nonmatchings/us", GetAngleBetweenEntitiesShifted);

INCLUDE_ASM("st/top/nonmatchings/us", GetAnglePointToEntityShifted);

INCLUDE_ASM("st/top/nonmatchings/us", AdjustValueWithinThreshold);

INCLUDE_ASM("st/top/nonmatchings/us", UnkEntityFunc0);

INCLUDE_ASM("st/top/nonmatchings/us", Ratan2);

INCLUDE_ASM("st/top/nonmatchings/us", GetAngleBetweenEntities);

INCLUDE_ASM("st/top/nonmatchings/us", GetAnglePointToEntity);

INCLUDE_ASM("st/top/nonmatchings/us", GetNormalizedAngle);

INCLUDE_ASM("st/top/nonmatchings/us", SetStep);

INCLUDE_ASM("st/top/nonmatchings/us", SetSubStep);

INCLUDE_ASM("st/top/nonmatchings/us", EntityExplosionSpawn);

INCLUDE_ASM("st/top/nonmatchings/us", InitializeEntity);

INCLUDE_ASM("st/top/nonmatchings/us", EntityDummy);

INCLUDE_ASM("st/top/nonmatchings/us", UnkCollisionFunc);

INCLUDE_ASM("st/top/nonmatchings/us", CheckFieldCollision);

INCLUDE_ASM("st/top/nonmatchings/us", GetPlayerCollisionWith);

INCLUDE_ASM("st/top/nonmatchings/us", ReplaceBreakableWithItemDrop);

INCLUDE_ASM("st/top/nonmatchings/us", PrizeDropFall);

INCLUDE_ASM("st/top/nonmatchings/us", PrizeDropFall2);

INCLUDE_ASM("st/top/nonmatchings/us", CollectHeart);

INCLUDE_ASM("st/top/nonmatchings/us", CollectGold);

INCLUDE_ASM("st/top/nonmatchings/us", CollectSubweapon);

INCLUDE_ASM("st/top/nonmatchings/us", CollectHeartVessel);

INCLUDE_ASM("st/top/nonmatchings/us", CollectLifeVessel);

INCLUDE_ASM("st/top/nonmatchings/us", CollectDummy);

INCLUDE_RODATA("st/top/nonmatchings/us", D_us_801A8A7C);

INCLUDE_RODATA("st/top/nonmatchings/us", D_us_801A8A84);

INCLUDE_RODATA("st/top/nonmatchings/us", D_us_801A8A8C);

INCLUDE_RODATA("st/top/nonmatchings/us", D_us_801A8A94);

INCLUDE_RODATA("st/top/nonmatchings/us", D_us_801A8A9C);

INCLUDE_RODATA("st/top/nonmatchings/us", D_us_801A8AA4);

INCLUDE_RODATA("st/top/nonmatchings/us", D_us_801A8AAC);

INCLUDE_RODATA("st/top/nonmatchings/us", D_us_801A8AB4);

INCLUDE_RODATA("st/top/nonmatchings/us", D_us_801A8ABC);

INCLUDE_RODATA("st/top/nonmatchings/us", D_us_801A8AC4);

INCLUDE_ASM("st/top/nonmatchings/us", EntityPrizeDrop);

INCLUDE_ASM("st/top/nonmatchings/us", EntityExplosion);

INCLUDE_ASM("st/top/nonmatchings/us", BlinkItem);

INCLUDE_ASM("st/top/nonmatchings/us", EntityEquipItemDrop);

INCLUDE_ASM("st/top/nonmatchings/us", BlitChar);

INCLUDE_RODATA("st/top/nonmatchings/us", D_us_801A8B04);

INCLUDE_ASM("st/top/nonmatchings/us", EntityRelicOrb);

INCLUDE_ASM("st/top/nonmatchings/us", EntityHeartDrop);

INCLUDE_ASM("st/top/nonmatchings/us", EntityMessageBox);

INCLUDE_ASM("st/top/nonmatchings/us", CheckColliderOffsets);

INCLUDE_ASM("st/top/nonmatchings/us", EntityUnkId13);

INCLUDE_ASM("st/top/nonmatchings/us", EntityExplosionVariantsSpawner);

INCLUDE_ASM("st/top/nonmatchings/us", EntityGreyPuffSpawner);

INCLUDE_ASM("st/top/nonmatchings/us", EntityExplosionVariants);

INCLUDE_ASM("st/top/nonmatchings/us", EntityGreyPuff);

INCLUDE_ASM("st/top/nonmatchings/us", EntityOlroxDrool);

INCLUDE_ASM("st/top/nonmatchings/us", UnkCollisionFunc5);

INCLUDE_ASM("st/top/nonmatchings/us", UnkCollisionFunc4);

INCLUDE_ASM("st/top/nonmatchings/us", EntityIntenseExplosion);

INCLUDE_ASM("st/top/nonmatchings/us", InitializeUnkEntity);

INCLUDE_ASM("st/top/nonmatchings/us", MakeEntityFromId);

INCLUDE_ASM("st/top/nonmatchings/us", MakeExplosions);

INCLUDE_ASM("st/top/nonmatchings/us", EntityBigRedFireball);

INCLUDE_ASM("st/top/nonmatchings/us", UnkRecursivePrimFunc1);

INCLUDE_ASM("st/top/nonmatchings/us", UnkRecursivePrimFunc2);

INCLUDE_ASM("st/top/nonmatchings/us", ClutLerp);

INCLUDE_ASM("st/top/nonmatchings/us", PlaySfxPositional);

INCLUDE_ASM("st/top/nonmatchings/us", StageNamePopupHelper);

INCLUDE_ASM("st/top/nonmatchings/us", EntityStageNamePopup);

INCLUDE_ASM("st/top/nonmatchings/us", EntitySoulStealOrb);

INCLUDE_ASM("st/top/nonmatchings/us", EntityEnemyBlood);

INCLUDE_ASM("st/top/nonmatchings/us", EntityRoomForeground);

INCLUDE_ASM("st/top/nonmatchings/us", BottomCornerText);

// flea rider?

INCLUDE_ASM("st/top/nonmatchings/us", func_us_801B86B8);

// e_blue_axe_night

INCLUDE_ASM("st/top/nonmatchings/us", AxeKnightUnkFunc1);

INCLUDE_ASM("st/top/nonmatchings/us", func_us_801CA51C);

INCLUDE_ASM("st/top/nonmatchings/us", func_us_801CAD20);

INCLUDE_RODATA("st/top/nonmatchings/us", D_us_801A8C00);

INCLUDE_ASM("st/top/nonmatchings/us", EntityAxeKnightBlue);

INCLUDE_ASM("st/top/nonmatchings/us", EntityAxeKnightRotateAxe);

INCLUDE_ASM("st/top/nonmatchings/us", EntityAxeKnightThrowingAxe);

INCLUDE_ASM("st/top/nonmatchings/us", func_us_801CBA30);

