// SPDX-License-Identifier: AGPL-3.0-or-later
// SPDX-License-Identifier: AGPL-3.0-or-later(Entity* self);
#include "rnz0.h"

void EntityBreakableNZ0(Entity* self);
void EntityExplosion(Entity* self);
void EntityPrizeDrop(Entity* self);
void EntityDamageDisplay(Entity* self);
void EntityRedDoor(Entity* self);
void EntityIntenseExplosion(Entity* self);
void EntitySoulStealOrb(Entity* self);
void EntityRoomForeground(Entity* self);
void EntityStageNamePopup(Entity* self);
void EntityEquipItemDrop(Entity* self);
void EntityRelicOrb(Entity* self);
void EntityPersistentItemDrop(Entity* self);
void EntityEnemyBlood(Entity* self);
void EntityMessageBox(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityBackgroundBlock(Entity* self);
void EntityLockCamera(Entity* self);
void EntityUnkId13(Entity* self);
void EntityExplosionVariants(Entity* self);
void EntityGreyPuff(Entity* self);
void EntityPurpleBrickScrollingBackground(Entity* self);
void EntityLeftSecretRoomWall(Entity* self);
void EntityBottomSecretRoomFloor(Entity* self);
void EntitySecretWallDebris(Entity* self);
void EntityFloorTrap(Entity* self);
void EntityCtulhu(Entity* self);
void EntityCtulhuFireball(Entity* self);
void EntityCtulhuIceShockwave(Entity* self);
void EntityCtulhuDeath(Entity* self);
void EntityFireDemon(Entity* self);
void EntityFireDemonPopoutEffect(Entity* self);
void EntityFireDemonFireball(Entity* self);
void EntityFireDemonFlames(Entity* self);
void EntityLesserDemon(Entity* self);
void EntityLesserDemonSpit(Entity* self);
void EntityLesserDemonFireball(Entity* self);
void EntityLesserDemonDummy(Entity* self);
void EntityTableWithGlobe(Entity* self);
void EntityLifeMaxTank(Entity* self);
void EntityBlueFlameTable(Entity* self);
void EntityRelicContainer(Entity* self);
void EntitySealedDoor(Entity* self);
void EntityRedEyeBust(Entity* self);
void EntityCannonLever(Entity* self);
void EntityCannon(Entity* self);
void EntityCannonShot(Entity* self);
void EntityCannonWall(Entity* self);
void EntityBitterfly(Entity* self);
void EntityImp(Entity* self);
void EntityImpSmoke(Entity* self);
void EntityGremlin(Entity* self);
void EntityGremlinEffect(Entity* self);
void EntityGremlinFire(Entity* self);
void EntitySalemWitch(Entity* self);
void EntitySalemWitchGlow(Entity* self);
void EntitySalemWitchCurse(Entity* self);
void EntitySalemWitchTriboltLaunch(Entity* self);
void EntitySalemWitchTriboltProjectile(Entity* self);

PfnEntityUpdate EntityUpdates[] = {
    EntityBreakableNZ0,
    EntityExplosion,
    EntityPrizeDrop,
    EntityDamageDisplay,
    EntityRedDoor,
    EntityIntenseExplosion,
    EntitySoulStealOrb,
    EntityRoomForeground,
    EntityStageNamePopup,
    EntityEquipItemDrop,
    EntityRelicOrb,
    EntityPersistentItemDrop,
    EntityEnemyBlood,
    EntityMessageBox,
    EntityDummy,
    EntityDummy,
    EntityBackgroundBlock,
    EntityLockCamera,
    EntityUnkId13,
    EntityExplosionVariants,
    EntityGreyPuff,
    EntityPurpleBrickScrollingBackground,
    EntityLeftSecretRoomWall,
    EntityBottomSecretRoomFloor,
    EntitySecretWallDebris,
    EntityFloorTrap,
    EntityCtulhu,
    EntityCtulhuFireball,
    EntityCtulhuIceShockwave,
    EntityCtulhuDeath,
    EntityFireDemon,
    EntityFireDemonPopoutEffect,
    EntityFireDemonFireball,
    EntityFireDemonFlames,
    EntityLesserDemon,
    EntityLesserDemonSpit,
    EntityLesserDemonFireball,
    EntityLesserDemonDummy,
    EntityTableWithGlobe,
    EntityLifeMaxTank,
    EntityBlueFlameTable,
    EntityRelicContainer,
    EntitySealedDoor,
    EntityRedEyeBust,
    EntityCannonLever,
    EntityCannon,
    EntityCannonShot,
    EntityCannonWall,
    EntityBitterfly,
    EntityImp,
    EntityImpSmoke,
    EntityGremlin,
    EntityGremlinEffect,
    EntityGremlinFire,
    EntitySalemWitch,
    EntitySalemWitchGlow,
    EntitySalemWitchCurse,
    EntitySalemWitchTriboltLaunch,
    EntitySalemWitchTriboltProjectile,
};

// clang-format off
EInit g_EInitBreakable = {ANIMSET_OVL(1), 0x00, 0x00, PAL_NONE, ENEMY_BREAKABLE};
#include "../e_init_common.h"
EInit g_EInitFloorTrap = {ANIMSET_OVL(3), 0x00, 0x4B, PAL_FLOOR_TRAP, ENEMY_INTERACTABLE};
EInit g_EInitCtulhu = {ANIMSET_OVL(4), 0x00, 0x48, PAL_CTULHU, ENEMY_CTULHU};
EInit g_EInitCtulhuFireball = {ANIMSET_OVL(4), 0x00, 0x48, PAL_CTULHU, ENEMY_CTULHU_FIREBALL};
EInit g_EInitCtulhuIceShockwave = {ANIMSET_OVL(4), 0x2C, 0x48, PAL_CTULHU, ENEMY_CTULHU_ICE_SHOCKWAVE};
EInit g_EInitFireDemon = {ANIMSET_OVL(5), 0x01, 0x4F, PAL_FIRE_DEMON, ENEMY_FIRE_DEMON};
EInit g_EInitFireDemonFireball = {ANIMSET_DRA(2), 0x01, 0x00, PAL_NONE, ENEMY_FIRE_DEMON_FIREBALL};
EInit g_EInitLesserDemon = {ANIMSET_OVL(6), 0x01, 0x4C, PAL_LESSER_DEMON, ENEMY_LESSER_DEMON};
EInit g_EInitLesserDemonSpit = {ANIMSET_OVL(6), 0x19, 0x4C, PAL_LESSER_DEMON, ENEMY_LESSER_DEMON_SPIT};
EInit g_EInitLesserDemonFireball = {ANIMSET_DRA(9), 0x01, 0x00, PAL_FLAG(PAL_UNK_1B0), ENEMY_LESSER_DEMON_FIREBALL};
EInit g_EInitLesserDemonDummy = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_LESSER_DEMON_DUMMY};
EInit g_EInitWallDebris = {ANIMSET_OVL(1), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInitEnemy3 = {ANIMSET_OVL(2), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInitTableWithGlobe = {ANIMSET_OVL(7), 0x00, 0x4B, PAL_BREAKABLE, ENEMY_INTERACTABLE};
EInit g_EInitLifeMaxTank = {ANIMSET_OVL(8), 0x00, 0x4F, PAL_LIFE_MAX_TANK, ENEMY_INTERACTABLE};
EInit g_EInitPrizeContainer = {ANIMSET_OVL(9), 0x00, 0x53, PAL_PRIZE_CONTAINER, ENEMY_INTERACTABLE};
EInit g_EInitBitterfly = {ANIMSET_OVL(10), 0x01, 0x48, PAL_BITTERFLY, ENEMY_BITTERFLY};
EInit g_EInitImp = {ANIMSET_OVL(11), 0x01, 0x5F, PAL_IMP, ENEMY_IMP};
EInit g_EInitImpSmoke = {ANIMSET_OVL(11), 0x01, 0x5F, PAL_IMP, ENEMY_PARTICLE};
EInit g_EInitGremlin = {ANIMSET_OVL(12), 0x00, 0x5E, PAL_GREMLIN, ENEMY_GREMLIN};
EInit g_EInitGremlinUnused = {ANIMSET_OVL(12), 0x00, 0x5E, PAL_GREMLIN, ENEMY_INTERACTABLE};
EInit g_EInitGremlinFire = {ANIMSET_OVL(12), 0x00, 0x5E, PAL_GREMLIN, ENEMY_GREMLIN_FIRE};
EInit g_EInitSalemWitch = {ANIMSET_OVL(13), 0x01, 0x50, PAL_SALEM_WITCH, ENEMY_SALEM_WITCH};
EInit g_EInitSalemWitchCurse = {ANIMSET_OVL(13), 0x00, 0x50, PAL_SALEM_WITCH, ENEMY_SALEM_WITCH_CURSE};
EInit g_EInitSalemWitchTribolt = {ANIMSET_OVL(14), 0x00, 0x5C, PAL_SALEM_WITCH_TRIBOLT, ENEMY_SALEM_WITCH_TRIBOLT};
