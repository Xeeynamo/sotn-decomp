// SPDX-License-Identifier: AGPL-3.0-or-later
#include "lib.h"

void EntityBreakable(Entity* self);
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
void EntityBackgroundBookcase(Entity* self);
void EntityBackgroundFurniture(Entity* self);
void EntityBackgroundShadow(Entity* self);
void func_us_801AFA80(Entity* self);
void func_us_801AE8E8(Entity* self);
void EntityFlyingZombie2(Entity* self);
void EntityFlyingZombie1(Entity* self);
void EntityBloodDrips(Entity* self);
void EntityBloodSplatter(Entity* self);
void EntityLesserDemon(Entity* self);
void EntityLesserDemonSpit(Entity* self);
void func_us_801BCC10(Entity* self);
void func_us_801BED48(Entity* self);
void func_us_801AFE0C(Entity* self);
void EntityLibrarianChair(Entity* self);
void EntityCutscene(Entity* self);
void func_us_801B15C0(Entity* self);
void func_us_801B2BE4(Entity* self);
void func_us_801B4830(Entity* self);
void func_us_801B5068(Entity* self);
void func_us_801B56E4(Entity* self);
void func_us_801B5F84(Entity* self);
void func_us_801B60C8(Entity* self);
void func_us_801B6324(Entity* self);
void func_us_801B6F30(Entity* self);
void func_us_801B8234(Entity* self);
void EntitySpellbook(Entity* self);
void func_us_801D2CE0(Entity* self);
void EntityMagicTome(Entity* self);
void EntityDhuron(Entity* self);
void func_us_801CC6B0(Entity* self);
void func_us_801CC984(Entity* self);
void func_us_801CC7BC(Entity* self);
void func_us_801CD318(Entity* self);
void func_us_801CD9EC(Entity* self);
void func_us_801CCF6C(Entity* self);
void EntityThornweed(Entity* self);
void EntityCorpseweed(Entity* self);
void EntityCorpseweedProjectile(Entity* self);
void EntityCandleTable(Entity* self);
void func_us_801D35B8(Entity* self);
void EntityBreakableHelper(Entity* self);
void func_us_801BB200(Entity* self);
void func_us_801BB53C(Entity* self);
void EntityLifeUpSpawn(Entity* self);
void EntitySkeleton(Entity* self);
void EntitySkeletonThrownBone(Entity* self);
void EntitySkeletonPieces(Entity* self);
void EntityChair(Entity* self);
void EntityBreakableDebris(Entity* self);
void func_us_801B8A00(Entity* self);
void EntityMistDoor(Entity* self);
void EntityFleaArmor(Entity* self);
void EntityFleaArmorAttackHitbox(Entity* self);
void EntityFleaMan(Entity* self);
void EntityMudman(Entity* self);
void func_us_801D1298(Entity* self);
#ifdef VERSION_PSP
void func_psp_0926AED0(Entity* self);
#endif

PfnEntityUpdate EntityUpdates[] = {
    /* 0x00 */ EntityBreakable,
    /* 0x01 */ EntityExplosion,
    /* 0x02 */ EntityPrizeDrop,
    /* 0x03 */ EntityDamageDisplay,
    /* 0x04 */ EntityRedDoor,
    /* 0x05 */ EntityIntenseExplosion,
    /* 0x06 */ EntitySoulStealOrb,
    /* 0x07 */ EntityRoomForeground,
    /* 0x08 */ EntityStageNamePopup,
    /* 0x09 */ EntityEquipItemDrop,
    /* 0x0A */ EntityRelicOrb,
    /* 0x0B */ EntityPersistentItemDrop,
    /* 0x0C */ EntityEnemyBlood,
    /* 0x0D */ EntityMessageBox,
    /* 0x0E */ EntityDummy,
    /* 0x0F */ EntityDummy,
    /* 0x10 */ EntityBackgroundBlock,
    /* 0x11 */ EntityLockCamera,
    /* 0x12 */ EntityUnkId13,
    /* 0x13 */ EntityExplosionVariants,
    /* 0x14 */ EntityGreyPuff,
    /* 0x15 */ EntityBackgroundBookcase,
    /* 0x16 */ EntityBackgroundFurniture,
    /* 0x17 */ EntityBackgroundShadow,
    /* 0x18 */ func_us_801AFA80,
    /* 0x19 */ func_us_801AE8E8,
    /* 0x1A */ EntityFlyingZombie2,
    /* 0x1B */ EntityFlyingZombie1,
    /* 0x1C */ EntityBloodDrips,
    /* 0x1D */ EntityBloodSplatter,
    /* 0x1E */ EntityLesserDemon,
    /* 0x1F */ EntityLesserDemonSpit,
    /* 0x20 */ func_us_801BCC10,
    /* 0x21 */ func_us_801BED48,
    /* 0x22 */ func_us_801AFE0C,
    /* 0x23 */ EntityLibrarianChair,
    /* 0x24 */ EntityCutscene,
    /* 0x25 */ func_us_801B15C0,
    /* 0x26 */ func_us_801B2BE4,
    /* 0x27 */ func_us_801B4830,
    /* 0x28 */ func_us_801B5068,
    /* 0x29 */ func_us_801B56E4,
    /* 0x2A */ func_us_801B5F84,
    /* 0x2B */ func_us_801B60C8,
    /* 0x2C */ func_us_801B6324,
    /* 0x2D */ func_us_801B6F30,
    /* 0x2E */ func_us_801B8234,
    /* 0x2F */ EntitySpellbook,
    /* 0x30 */ func_us_801D2CE0,
    /* 0x31 */ EntityMagicTome,
    /* 0x32 */ EntityDhuron,
    /* 0x33 */ func_us_801CC6B0,
    /* 0x34 */ func_us_801CC984,
    /* 0x35 */ func_us_801CC7BC,
    /* 0x36 */ func_us_801CD318,
    /* 0x37 */ func_us_801CD9EC,
    /* 0x38 */ func_us_801CCF6C,
    /* 0x39 */ EntityThornweed,
    /* 0x3A */ EntityCorpseweed,
    /* 0x3B */ EntityCorpseweedProjectile,
    /* 0x3C */ EntityCandleTable,
    /* 0x3D */ func_us_801D35B8,
    /* 0x3E */ EntityBreakableHelper,
    /* 0x3F */ func_us_801BB200,
    /* 0x40 */ func_us_801BB53C,
    /* 0x41 */ EntityLifeUpSpawn,
    /* 0x42 */ EntitySkeleton,
    /* 0x43 */ EntitySkeletonThrownBone,
    /* 0x44 */ EntitySkeletonPieces,
    /* 0x45 */ EntityChair,
    /* 0x46 */ EntityBreakableDebris,
#ifdef VERSION_PSP
    /* 0x47 */ func_psp_0926AED0,
#else
    /* 0x47 */ func_us_801B8A00,
#endif
    /* 0x48 */ EntityMistDoor,
    /* 0x49 */ EntityFleaArmor,
    /* 0x4A */ EntityFleaArmorAttackHitbox,
    /* 0x4B */ EntityFleaMan,
    /* 0x4C */ EntityMudman,
    /* 0x4D */ func_us_801D1298,
#ifdef VERSION_PSP
    /* 0x4E */ func_us_801B8A00,
#endif
};

// clang-format off
EInit g_EInitBreakable = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_BREAKABLE};
EInit g_EInitObtainable = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_OBTAINABLE};
EInit g_EInitParticle = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit D_us_80180824 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_SPAWNER};
EInit g_EInitInteractable = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit g_EInitLockCamera = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_OBTAINABLE};
EInit g_EInitCommon = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInitDamageNum = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};

EInit g_EInitBloodyZombie = {ANIMSET_OVL(5), 0x01, 0x48, PAL_BLOODY_ZOMBIE, ENEMY_BLOODY_ZOMBIE};
EInit g_EInitFlyingZombie2 = {ANIMSET_OVL(6), 0x01, 0x49, PAL_FLYING_ZOMBIE, ENEMY_FLYING_ZOMBIE_2};
EInit g_EInitFlyingZombie1 = {ANIMSET_OVL(6), 0x00, 0x49, PAL_FLYING_ZOMBIE, ENEMY_FLYING_ZOMBIE_1};
EInit D_us_80180890 = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};

EInit g_EInitDhuron = {ANIMSET_OVL(3), 0x01, 0x4D, PAL_DHURON, ENEMY_DHURON};
EInit D_us_801808A8 = {ANIMSET_OVL(0), 0x00, 0x00, PAL_NONE, ENEMY_DHURON_DEATH_PARTS};
EInit D_us_801808B4 = {ANIMSET_OVL(3), 0x01, 0x4D, PAL_DHURON, ENEMY_PARTICLE};

EInit g_EInitEctoplasm = {ANIMSET_OVL(5), 0x00, 0x4A, PAL_ECTOPLASM, ENEMY_ECTOPLASM};

EInit g_EInitThornweed = {ANIMSET_OVL(7), 0x00, 0x50, PAL_THORNWEED_CORPSEWEED, ENEMY_THORNWEED};
EInit D_us_801808D8 = {ANIMSET_OVL(7), 0x00, 0x50, PAL_THORNWEED_CORPSEWEED, ENEMY_CORPSEWEED_UNUSED};

EInit g_EInitCorpseweed = {ANIMSET_OVL(7), 0x00, 0x50, PAL_THORNWEED_CORPSEWEED, ENEMY_CORPSEWEED};
EInit g_EInitCorpseweedProjectile = {ANIMSET_OVL(7), 0x00, 0x50, PAL_THORNWEED_CORPSEWEED, ENEMY_CORPSEWEED_PROJECTILE};
EInit D_us_801808FC = {ANIMSET_OVL(8), 0x00, 0x50, PAL_CANDLE_TABLE, ENEMY_INTERACTABLE};
EInit D_us_80180908 = {ANIMSET_OVL(2), 0x00, 0x54, PAL_SPELLBOOK_ATTACK, ENEMY_PARTICLE};

EInit g_EInitSpellbook = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_SPELLBOOK};
EInit D_us_80180920 = {ANIMSET_OVL(2), 0x00, 0x54, PAL_SPELLBOOK_ATTACK, ENEMY_SPELLBOOK_ATTACK};
EInit D_us_8018092C = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_MAGIC_TOME_LV8};
EInit D_us_80180938 = {ANIMSET_OVL(2), 0x00, 0x54, PAL_SPELLBOOK_ATTACK, ENEMY_MAGIC_TOME_LV8_ATTACK};

EInit g_EInitMagicTome = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_MAGIC_TOME};
EInit D_us_80180950 = {ANIMSET_OVL(2), 0x00, 0x54, PAL_SPELLBOOK_ATTACK, ENEMY_MAGIC_TOME_ATTACK};
EInit D_us_8018095C = {ANIMSET_OVL(1), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};

EInit g_EInitLesserDemon = {ANIMSET_OVL(10), 0x01, 0x4C, PAL_LESSER_DEMON, ENEMY_LESSER_DEMON};
EInit g_EInitLesserDemonSpit = {ANIMSET_OVL(10), 0x19, 0x4C, PAL_LESSER_DEMON, ENEMY_LESSER_DEMON_SPIT};
EInit D_us_80180980 = {ANIMSET_DRA(9), 0x01, 0x00, PAL_FLAG(PAL_UNK_1B0), ENEMY_LESSER_DEMON_FIREBALL};
EInit D_us_8018098C = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_LESSER_DEMON_DUMMY};

EInit g_EInitSkeleton = {ANIMSET_OVL(9), 0x01, 0x4B, PAL_SKELETON, ENEMY_SKELETON};
EInit g_EInitSkeletonPieces = {ANIMSET_OVL(9), 0x00, 0x4B, PAL_SKELETON, ENEMY_PARTICLE};
EInit g_EInitSkeletonBone = {ANIMSET_OVL(9), 0x15, 0x4B, PAL_SKELETON, ENEMY_SKELETON_BONE};

EInit g_EInitFleaArmor = {ANIMSET_OVL(13), 0x01, 0x49, PAL_FLEA_ARMOR_FLEA_MAN, ENEMY_FLEA_ARMOR};
EInit g_EInitFleaArmorAttackHitbox = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_FLEA_ARMOR_ATTACK_HITBOX};
EInit g_EInitFleaMan = {ANIMSET_OVL(13), 0x00, 0x49, PAL_FLEA_ARMOR_FLEA_MAN, ENEMY_FLEA_MAN};

EInit g_EInitMudman = {ANIMSET_OVL(14), 0x00, 0x53, PAL_MUDMAN, ENEMY_MUDMAN};
EInit D_us_801809EC = {ANIMSET_OVL(0), 0x00, 0x00, PAL_NONE, ENEMY_MUDMAN_UNK_D7};
