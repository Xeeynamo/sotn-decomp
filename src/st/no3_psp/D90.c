// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../no3/no3.h"

#include "../e_castle_door.h"

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityHeartRoomSwitch);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityHeartRoomGoldDoor);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09239020);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityWeightsSwitch);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityPathBlockSmallWeight);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityPathBlockTallWeight);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09239940);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityCavernDoorLever);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityCavernDoorPlatform);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityCavernDoor);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityTransparentWater);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityBackgroundBushes);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityBackgroundTrees);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityStairwayPiece);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityFallingRock);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityMermanRockLeftSide);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityMermanRockRightSide);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityJewelSwordDoor);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityFallingRock2);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_0923C528);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityDeathSkySwirl);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityLightningThunder);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityLightningCloud);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityTrapDoor);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_0923D348);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityExplosionPuffOpaque);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityPushAlucard);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityCastleDoorTransition);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityForegroundTree);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityUnkId50);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityBackgroundPineTrees);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityUnkId52);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityCastleBridge);

// clumsy thing, linter splits the line which breaks INCLUDE_ASM
// clang-format off
INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityDistantBackgroundTrees);
// clang-format on

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityBackgroundCastleWall);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityFlyingOwlAndLeaves);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityFallingLeaf);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityRoomTransition2);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityDeathStolenItem);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityDeath);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityDeathScythe);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityDeathScytheShadow);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityTilemapShufflerUnused);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityShuttingWindow);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityBreakable);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityCavernDoorVase);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityUnkId16);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09242C00);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09242CA0);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09242FB8);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09243040);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09243108);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09243168);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09243378);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_092433B0);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09243748);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", NO3_EntityCutscene);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityLockCamera);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09245A58);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09245B78);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09245D10);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09245EA8);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09245F18);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09245FA0);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_092460E0);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09246238);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_092462B0);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09246338);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09246480);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", InitRoomEntities);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", UpdateRoomPosition);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", CreateEntityFromCurrentEntity);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09246978);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityBat);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityStageNamePopup);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09247BB8);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", NO3_EntityRedDoor);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", Random);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", Update);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", UpdateStageEntities);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_092493F8);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09249590);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09249738);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09249878);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityFireWarg);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityUnkId30);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityUnkId31);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityExplosion3);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_0924C7A8);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityFireWargWaveAttack);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityUnkId2F);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityFireWargDeathBeams);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_0924D9C0);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityMerman2);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityExplosion2);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityMediumWaterSplash);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityMermanWaterSplash);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityFallingObject2);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityHighWaterSplash);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityDeadMerman);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityMermanSpawner);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityMerman);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityMermanFireball);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityFallingObject);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityMermanExplosion);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_092516E8);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09251C70);
