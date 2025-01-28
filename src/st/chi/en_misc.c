// SPDX-License-Identifier: AGPL-3.0-or-later
/*
 * File: en_relic_orb.c
 * Overlay: CHI
 * Description: ENTITY - Relic: Spirit Orb. Displays damage
 */

#include "chi.h"

void EntityExplosionVariants(Entity* self);
void EntityGreyPuff(Entity* self);

#define HEART_DROP_CASTLE_FLAG 0xB0

// D_80181314: g_RelicOrbTexts
// D_80181318: g_RelicOrbTextBg1EY
// D_80181328: g_RelicOrbTextBg1SY
// D_80181338: g_RelicOrbTextBg2SY
// D_80181348: g_RelicOrbTextBg2EY
// D_80181358: g_RelicOrbSparkleX
// D_80181368: g_RelicOrbSparkleY
// func_801A3F58: [E_RELIC_ORB] EntityRelicOrb
// func_801A4A28: [E_HEART_DROP] EntityHeartDrop
// func_801A4B50: [E_SAVE_GAME_POPUP] EntityMessageBox
// func_801A50AC: CheckColliderOffsets
// func_801A519C: [E_PARTICLE_TRAIL] EntityUnkId13 (EntityParticleTrail)
// D_80181378: explosionVariantSizes
// func_801A52AC: EntityExplosionVariantsSpawner
// func_801A53DC: EntityGreyPuffSpawner
// D_80181388: greyPuff_rot
// D_80181398: greyPuff_yVel
// D_801813B0: explode_yVel
// D_801813C8: explode_startFrame
// D_801813CC: explode_lifetime
// func_801A54C4: [E_ID_14] EntityExplosionVariants
// func_801A55B4: [E_GREY_PUFF] EntityGreyPuff
// D_801813D4: g_olroxDroolCollOffsets
// func_801A56A8: EntityOlroxDrool
// func_801A58D8: UnkCollisionFunc5
// func_801A59D4: UnkCollisionFunc4
// func_801A5F54: [E_INTENSE_EXPLOSION] EntityIntenseExplosion
// D_801813DC: g_UnkEntityAnimData
// func_801A6054: InitializeUnkEntity
// func_801A6120: MakeEntityFromId
// func_801A61E8: MakeExplosions
// func_801A62A0: EntityBigRedFireball
// D_801813EC: g_UnkRecursPrimVecOrder
// func_801A6478: UnkRecursivePrimFunc1
// D_8018140C: g_UnkRecursPrim2Inds
// func_801A6A58: UnkRecursivePrimFunc2
// func_801A7158: ClutLerp
// func_801A7350: PlaySfxPositional
#include "../e_misc.h"
