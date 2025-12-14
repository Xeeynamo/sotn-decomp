// SPDX-License-Identifier: AGPL-3.0-or-later
#include "are.h"

void OVL_EXPORT(EntityBreakable)(Entity* self);
void EntityExplosion(Entity* self);
void EntityPrizeDrop(Entity* self);
void EntityDamageDisplay(Entity* self);
void OVL_EXPORT(EntityRedDoor)(Entity* self);
void EntityIntenseExplosion(Entity* self);
void EntitySoulStealOrb(Entity* self);
void EntityRoomForeground(Entity* self);
void EntityStageNamePopup(Entity* self);
void EntityEquipItemDrop(Entity* self);
void EntityRelicOrb(Entity* self);
void EntityHeartDrop(Entity* self);
void EntityEnemyBlood(Entity* self);
void EntityMessageBox(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void OVL_EXPORT(EntityBackgroundBlock)(Entity* self);
void OVL_EXPORT(EntityLockCamera)(Entity* self);
void EntityUnkId13(Entity* self);
void EntityExplosionVariants(Entity* self);
void EntityGreyPuff(Entity* self);
void func_us_801B628C(Entity* self);
void func_us_801B6420(Entity* self);
void EntityBridgeBackgroundPiece(Entity* self);
void func_us_801B6DF0(Entity* self);
void EntityElevator(Entity* self);
void EntityElevatorSwitch(Entity* self);
void EntityElevatorGates(Entity* self);
void EntityFountainWater(Entity* self);
void EntityBreakableCeilingSecret(Entity* self);
void EntityBackgroundDoorRubble(Entity* self);
void EntityExplosionPuffOpaque(Entity* self);
void OVL_EXPORT(EntityBreakableDebris)(Entity* self);
void EntityBladeMaster(Entity* self);
void EntityBladeMasterAttackHitbox(Entity* self);
void EntityBladeMasterDeathParts(Entity* self);
void EntityBladeMasterDeathExplosion(Entity* self);
void EntityBladeSoldier(Entity* self);
void EntityBladeSoldierAttackHitbox(Entity* self);
void EntityBladeSoldierDeathParts(Entity* self);
void EntityBoneMusket(Entity* self);
void func_us_801CF298(Entity* self);
void EntityOwlKnight(Entity* self);
void EntityOwl(Entity* self);
void EntityOwlKnightSword(Entity* self);
void EntityOwlTarget(Entity* self);
void EntityValhallaKnight(Entity* self);
void func_us_801C8954(Entity* self);
void func_us_801C8AAC(Entity* self);
void EntityAxeKnightBlue(Entity* self);
void EntityAxeKnightThrowingAxe(Entity* self);
void func_us_801CBA30(Entity* self);
void InitializeUnkEntity(Entity* self);
void EntityArmorLord(Entity* self);
void func_us_801D348C(Entity* self);
void EntityArmorLordFireWave(Entity* self);
void func_us_801D3700(Entity* self);
void EntityHuntingGirl(Entity* self);
void EntityHuntingGirlAttack(Entity* self);
void EntityParanthropus(Entity* self);
void EntityParanthropusBoneHitbox(Entity* self);
void EntityParanthropusSkull(Entity* self);
void EntityParanthropusThrownBone(Entity* self);
void EntityFleaArmor(Entity* self);
void EntityFleaArmorAttackHitbox(Entity* self);
void EntityFleaMan(Entity* self);
void EntityBoneScimitar(Entity* self);
void EntityBoneScimitarParts(Entity* self);
void EntityPlateLord(Entity* self);
void func_us_801D4324(Entity* self);
void func_us_801D44A0(Entity* self);
void func_us_801D4AA4(Entity* self);
void func_us_801D542C(Entity* self);
void func_us_801D4CAC(Entity* self);
void EntityGraveKeeper(Entity* self);
void EntityGraveKeeperHitbox(Entity* self);
void EntityMistDoor(Entity* self);

PfnEntityUpdate OVL_EXPORT(EntityUpdates)[] = {
    OVL_EXPORT(EntityBreakable),
    EntityExplosion,
    EntityPrizeDrop,
    EntityDamageDisplay,
    OVL_EXPORT(EntityRedDoor),
    EntityIntenseExplosion,
    EntitySoulStealOrb,
    EntityRoomForeground,
    EntityStageNamePopup,
    EntityEquipItemDrop,
    EntityRelicOrb,
    EntityHeartDrop,
    EntityEnemyBlood,
    EntityMessageBox,
    EntityDummy,
    EntityDummy,
    OVL_EXPORT(EntityBackgroundBlock),
    OVL_EXPORT(EntityLockCamera),
    EntityUnkId13,
    EntityExplosionVariants,
    EntityGreyPuff,
    func_us_801B628C,
    func_us_801B6420,
    EntityBridgeBackgroundPiece,
    func_us_801B6DF0,
    EntityElevator,
    EntityElevatorSwitch,
    EntityElevatorGates,
    EntityFountainWater,
    EntityBreakableCeilingSecret,
    EntityBackgroundDoorRubble,
    EntityExplosionPuffOpaque,
    OVL_EXPORT(EntityBreakableDebris),
    EntityBladeMaster,
    EntityBladeMasterAttackHitbox,
    EntityBladeMasterDeathParts,
    EntityBladeMasterDeathExplosion,
    EntityBladeSoldier,
    EntityBladeSoldierAttackHitbox,
    EntityBladeSoldierDeathParts,
    EntityBoneMusket,
    func_us_801CF298,
    EntityOwlKnight,
    EntityOwl,
    EntityOwlKnightSword,
    EntityOwlTarget,
    EntityValhallaKnight,
    func_us_801C8954,
    func_us_801C8AAC,
    EntityAxeKnightBlue,
    EntityAxeKnightThrowingAxe,
    func_us_801CBA30,
    InitializeUnkEntity,
    EntityArmorLord,
    func_us_801D348C,
    EntityArmorLordFireWave,
    func_us_801D3700,
    EntityHuntingGirl,
    EntityHuntingGirlAttack,
    EntityParanthropus,
    EntityParanthropusBoneHitbox,
    EntityParanthropusSkull,
    EntityParanthropusThrownBone,
    EntityFleaArmor,
    EntityFleaArmorAttackHitbox,
    EntityFleaMan,
    EntityBoneScimitar,
    EntityBoneScimitarParts,
    EntityPlateLord,
    func_us_801D4324,
    func_us_801D44A0,
    func_us_801D4AA4,
    func_us_801D542C,
    func_us_801D4CAC,
    EntityGraveKeeper,
    EntityGraveKeeperHitbox,
    EntityMistDoor,
};

// Common
EInit OVL_EXPORT(
    EInitBreakable) = {ANIMSET_DRA(0x03), 0x00, 0x00, 0x0000, 0x000};
EInit g_EInitObtainable = {ANIMSET_DRA(0x03), 0x00, 0x00, 0x0000, 0x001};
EInit g_EInitParticle = {ANIMSET_DRA(0x03), 0x00, 0x00, 0x0000, 0x002};
EInit g_EInitSpawner = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x0000, 0x004};
EInit g_EInitInteractable = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x0000, 0x005};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x0000, 0x002};
EInit g_EInitLockCamera = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x0000, 0x001};
EInit g_EInitCommon = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x0000, 0x003};
EInit g_EInitDamageNum = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x0000, 0x003};

EInit D_us_80180AF8 = {ANIMSET_OVL(0x01), 0x00, 0x00, 0x0000, 0x005};
EInit D_us_80180B04 = {ANIMSET_OVL(0x02), 0x00, 0x53, 0x0200, 0x005};

// Blade Master
EInit g_EInitBladeMaster = {ANIMSET_OVL(0x03), 0x01, 0x48, 0x0201, 0x07A};
EInit g_EInitBladeMasterAttackHitbox = {
    ANIMSET_OVL(0x00), 0x00, 0x00, 0x0000, 0x07B};

// Blade Soldier
EInit g_EInitBladeSoldier = {ANIMSET_OVL(0x04), 0x01, 0x4B, 0x0203, 0x07C};
EInit g_EInitBladeSoldierAttackHitbox = {
    ANIMSET_OVL(0x00), 0x00, 0x00, 0x0000, 0x07D};

// Bone Musket
EInit g_EInitBoneMusket = {ANIMSET_OVL(0x05), 0x00, 0x4C, 0x0205, 0x066};
EInit D_us_80180AA0 = {ANIMSET_OVL(0x05), 0x00, 0x4C, 0x0205, 0x067};

// Owl Knight
EInit g_EInitOwlKnight = {ANIMSET_OVL(0x06), 0x10, 0x49, 0x0209, 0x014};
EInit g_EInitOwlKnightSword = {ANIMSET_OVL(0x06), 0x00, 0x49, 0x209, 0x015};

// Owl
EInit g_EInitOwl = {ANIMSET_OVL(0x06), 0x01, 0x49, 0x0209, 0x016};

// Valhalla Knight
EInit g_EInitValhallaKnight = {ANIMSET_OVL(0x07), 0x01, 0x4C, 0x0210, 0x085};
EInit g_EInitValhallaKnightUnk1 = {
    ANIMSET_OVL(0x07), 0x01, 0x4C, 0x0210, 0x003};
EInit g_EInitValhallaKnightUnk2 = {
    ANIMSET_OVL(0x00), 0x00, 0x00, 0x0000, 0x086};
EInit g_EInitValhallaKnightUnk3 = {
    ANIMSET_OVL(0x00), 0x00, 0x00, 0x0000, 0x087};

// (Blue) Axe Knight
EInit g_EInitAxeKnight = {ANIMSET_OVL(0x08), 0x01, 0x50, 0x0213, 0x006};
EInit g_EInitAxeKnightAxe = {ANIMSET_OVL(0x08), 0x2F, 0x50, 0x0213, 0x007};

// Armor Lord
EInit g_EInitArmorLord = {ANIMSET_OVL(0x09), 0x01, 0x52, 0x0216, 0x022};
EInit D_us_80180AE8 = {ANIMSET_OVL(0x09), 0x00, 0x52, 0x0216, 0x023};
EInit D_us_80180AF4 = {ANIMSET_OVL(0x00), 0x00, 0x00, 0x0000, 0x024};

// Hunting Girl
EInit g_EInitHuntingGirl = {ANIMSET_OVL(0x0A), 0x00, 0x54, 0x021D, 0x0E3};

// Paranthropus
EInit g_EInitParanthropus = {ANIMSET_OVL(0x0B), 0x01, 0x48, 0x021F, 0x0D3};
EInit g_EInitParanthropusBoneHitbox = {
    ANIMSET_OVL(0x00), 0x00, 0x00, 0x0000, 0x0D4};
EInit g_EInitParanthropusThrownBone = {
    ANIMSET_OVL(0x0B), 0x36, 0x48, 0x021F, 0x0D5};

// Flea Armor
EInit g_EInitFleaArmor = {ANIMSET_OVL(0x0C), 0x01, 0x48, 0x0222, 0x029};
EInit g_EInitFleaArmorAttackHitbox = {
    ANIMSET_DRA(0x00), 0x00, 0x00, 0x0000, 0x02A};

// Flea Man
EInit g_EInitFleaMan = {ANIMSET_OVL(0x0C), 0x00, 0x48, 0x0222, 0x028};

// Bone Scimitar
EInit g_EInitBoneScimitar = {ANIMSET_OVL(0x0D), 0x01, 0x4D, 0x0225, 0x069};
EInit g_EInitScimitarParts = {ANIMSET_OVL(0x0D), 0x00, 0x4D, 0x0225, 0x002};

// Plate Lord
EInit g_EInitPlateLord = {ANIMSET_OVL(0x0E), 0x01, 0x4C, 0x0226, 0x061};
EInit D_us_80180B90 = {ANIMSET_OVL(0x0E), 0x16, 0x4C, 0x0226, 0x062};

// Grave Keeper
EInit g_EInitGraveKeeper = {ANIMSET_OVL(0x18), 0x01, 0x4D, 0x0229, 0x06F};
EInit g_EInitGraveKeeperHitbox = {ANIMSET_OVL(0x00), 0x00, 0x00, 0x0000, 0x070};
