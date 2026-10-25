// SPDX-License-Identifier: AGPL-3.0-or-later
#include <psyz/module.h>
#include <game.h>
#include <string.h>
#include "overlay.h"
#include "../../st/tek/tek.h"

extern AbbreviatedOverlay g_Overlay;
extern PfnEntityUpdate EntityUpdates[];
extern LayoutEntity* entityLayoutHorizontal[];
extern LayoutEntity* entityLayoutVertical[];
extern PfnEntityUpdate* PfnEntityUpdates;
extern LayoutEntity** g_pStObjLayoutHorizontal;
extern LayoutEntity** g_pStObjLayoutVertical;

// beta-style entity freeze flag, never raised by the US engine
s32 D_800A6C18;

// entities still not decompiled
static void UnsupportedEntity(Entity* self) { DestroyEntity(self); }
void EntityBlackCrow(Entity* self) { UnsupportedEntity(self); }
void EntityBladeMaster(Entity* self) { UnsupportedEntity(self); }
void EntityBladeMasterAttackHitbox(Entity* self) { UnsupportedEntity(self); }
void EntityBladeMasterDeathExplosion(Entity* self) { UnsupportedEntity(self); }
void EntityBladeMasterDeathParts(Entity* self) { UnsupportedEntity(self); }
void EntityBladeSoldier(Entity* self) { UnsupportedEntity(self); }
void EntityBladeSoldierAttackHitbox(Entity* self) { UnsupportedEntity(self); }
void EntityBladeSoldierDeathParts(Entity* self) { UnsupportedEntity(self); }
void EntityBlueRaven(Entity* self) { UnsupportedEntity(self); }
void EntityBombFuseSparks(Entity* self) { UnsupportedEntity(self); }
void EntityBombKnight(Entity* self) { UnsupportedEntity(self); }
void EntityBombKnightArm(Entity* self) { UnsupportedEntity(self); }
void EntityBombKnightDeathParts(Entity* self) { UnsupportedEntity(self); }
void EntityBoneArcher(Entity* self) { UnsupportedEntity(self); }
void EntityBoneArcherArrow(Entity* self) { UnsupportedEntity(self); }
void EntityBoneHalberd(Entity* self) { UnsupportedEntity(self); }
void EntityBoneHalberdAttack(Entity* self) { UnsupportedEntity(self); }
void EntityBoneHalberdPieces(Entity* self) { UnsupportedEntity(self); }
void EntityBoneMusket(Entity* self) { UnsupportedEntity(self); }
void EntityBoneMusketUnk(Entity* self) { UnsupportedEntity(self); }
void EntityBoneScimitar(Entity* self) { UnsupportedEntity(self); }
void EntityBoneScimitarParts(Entity* self) { UnsupportedEntity(self); }
void EntityCorpseweed(Entity* self) { UnsupportedEntity(self); }
void EntityCorpseweedProjectile(Entity* self) { UnsupportedEntity(self); }
void EntityDodoBird(Entity* self) { UnsupportedEntity(self); }
void EntityDragonHeadParts(Entity* self) { UnsupportedEntity(self); }
void EntityDragonRider(Entity* self) { UnsupportedEntity(self); }
void EntityDragonRiderHitbox(Entity* self) { UnsupportedEntity(self); }
void EntityDragonSegment(Entity* self) { UnsupportedEntity(self); }
void EntityFrog(Entity* self) { UnsupportedEntity(self); }
void EntityGraveKeeper(Entity* self) { UnsupportedEntity(self); }
void EntityGraveKeeperHitbox(Entity* self) { UnsupportedEntity(self); }
void EntityJackOBones(Entity* self) { UnsupportedEntity(self); }
void EntityJackOBonesJack(Entity* self) { UnsupportedEntity(self); }
void EntityJackOBonesPieces(Entity* self) { UnsupportedEntity(self); }
void EntityNovaLaser(Entity* self) { UnsupportedEntity(self); }
void EntityNovaLaserPulse(Entity* self) { UnsupportedEntity(self); }
void EntityNovaSkeleton(Entity* self) { UnsupportedEntity(self); }
void EntityNovaSkeletonPieces(Entity* self) { UnsupportedEntity(self); }
void EntityOrobHeadParts(Entity* self) { UnsupportedEntity(self); }
void EntityOrobHolyAttacker(Entity* self) { UnsupportedEntity(self); }
void EntityOrobRider(Entity* self) { UnsupportedEntity(self); }
void EntityOrobSegment(Entity* self) { UnsupportedEntity(self); }
void EntityOrobourous(Entity* self) { UnsupportedEntity(self); }
void EntityPoltergeist(Entity* self) { UnsupportedEntity(self); }
void EntityRockPiece(Entity* self) { UnsupportedEntity(self); }
void EntityShield(Entity* self) { UnsupportedEntity(self); }
void EntitySpear(Entity* self) { UnsupportedEntity(self); }
void EntitySpectralSwordDAI(Entity* self) { UnsupportedEntity(self); }
void EntitySpectralSwordDAIAura(Entity* self) { UnsupportedEntity(self); }
void EntitySpectralSwordNO2(Entity* self) { UnsupportedEntity(self); }
void EntitySpectralSwordNO2Aura(Entity* self) { UnsupportedEntity(self); }
void EntitySpectralSwordRDAI(Entity* self) { UnsupportedEntity(self); }
void EntitySpectralSwordRDAIAura(Entity* self) { UnsupportedEntity(self); }
void EntitySpectralSwordWeapon(Entity* self) { UnsupportedEntity(self); }
void EntityThornweed(Entity* self) { UnsupportedEntity(self); }
void EntityThrownBomb(Entity* self) { UnsupportedEntity(self); }
void EntityThrownRock(Entity* self) { UnsupportedEntity(self); }
void EntityToad(Entity* self) { UnsupportedEntity(self); }
void EntityTombstone(Entity* self) { UnsupportedEntity(self); }
void EntityValhallaKnight(Entity* self) { UnsupportedEntity(self); }
void EntityValhallaKnightUnk1(Entity* self) { UnsupportedEntity(self); }
void EntityValhallaKnightUnk2(Entity* self) { UnsupportedEntity(self); }
void EntityVenusWeed(Entity* self) { UnsupportedEntity(self); }
void EntityVenusWeedDart(Entity* self) { UnsupportedEntity(self); }
void EntityVenusWeedFlower(Entity* self) { UnsupportedEntity(self); }
void EntityVenusWeedSpike(Entity* self) { UnsupportedEntity(self); }
void EntityVenusWeedTendril(Entity* self) { UnsupportedEntity(self); }
void EntityWingedGuard(Entity* self) { UnsupportedEntity(self); }
void EntityWingedGuardParts(Entity* self) { UnsupportedEntity(self); }
void EntityYorick(Entity* self) { UnsupportedEntity(self); }
void EntityYorickPieces(Entity* self) { UnsupportedEntity(self); }
void EntityYorickSkull(Entity* self) { UnsupportedEntity(self); }

void Psyz_ModuleStart(void* param) {
    Overlay* o = param;

    memcpy(o, &g_Overlay, sizeof(AbbreviatedOverlay));
    PfnEntityUpdates = EntityUpdates;
    g_pStObjLayoutHorizontal = entityLayoutHorizontal;
    g_pStObjLayoutVertical = entityLayoutVertical;
}

void Psyz_ModuleStop(void) {}
