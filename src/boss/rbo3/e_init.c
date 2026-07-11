// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo3.h"

extern s16* D_us_801814A0[];
s16* D_us_80180390[] = {D_us_801814A0};

void EntityBreakable(Entity* self);
void OVL_EXPORT(EntityExplosion)(Entity* self);
void OVL_EXPORT(EntityPrizeDrop)(Entity* self);
void OVL_EXPORT(EntityDamageDisplay)(Entity* self);
void OVL_EXPORT(EntityRedDoor)(Entity* self);
void EntityIntenseExplosion(Entity* self);
void EntitySoulStealOrb(Entity* self);
void EntityRoomForeground(Entity* self);
void EntityStageNamePopup(Entity* self);
void OVL_EXPORT(EntityEquipItemDrop)(Entity* self);
void OVL_EXPORT(EntityRelicOrb)(Entity* self);
void OVL_EXPORT(EntityHeartDrop)(Entity* self);
void EntityEnemyBlood(Entity* self);
void OVL_EXPORT(EntityMessageBox)(Entity* self);
void OVL_EXPORT(EntityDummy)(Entity* self);
void OVL_EXPORT(EntityDummy)(Entity* self);
void OVL_EXPORT(EntityBackgroundBlock)(Entity* self);
void OVL_EXPORT(EntityLockCamera)(Entity* self);
void EntityUnkId13(Entity* self);
void EntityExplosionVariants(Entity* self);
void EntityGreyPuff(Entity* self);
void func_us_80191438(Entity* self);
void EntityMedusa(Entity* self);
void func_us_80192020(Entity* self);
void func_us_801922EC(Entity* self);
void func_us_801923DC(Entity* self);
void func_us_80192998(Entity* self);
void func_us_80192B38(Entity* self);
void func_us_80192D64(Entity* self);
void EntityLifeUpSpawn(Entity* self);
void EntityClouds(Entity* self);
void func_us_80193050(Entity* self);

PfnEntityUpdate OVL_EXPORT(EntityUpdates)[] = {
    EntityBreakable,
    OVL_EXPORT(EntityExplosion),
    OVL_EXPORT(EntityPrizeDrop),
    OVL_EXPORT(EntityDamageDisplay),
    OVL_EXPORT(EntityRedDoor),
    EntityIntenseExplosion,
    EntitySoulStealOrb,
    EntityRoomForeground,
    EntityStageNamePopup,
    OVL_EXPORT(EntityEquipItemDrop),
    OVL_EXPORT(EntityRelicOrb),
    OVL_EXPORT(EntityHeartDrop),
    EntityEnemyBlood,
    OVL_EXPORT(EntityMessageBox),
    OVL_EXPORT(EntityDummy),
    OVL_EXPORT(EntityDummy),
    OVL_EXPORT(EntityBackgroundBlock),
    OVL_EXPORT(EntityLockCamera),
    EntityUnkId13,
    EntityExplosionVariants,
    EntityGreyPuff,
    func_us_80191438,
    EntityMedusa,
    func_us_80192020,
    func_us_801922EC,
    func_us_801923DC,
    func_us_80192998,
    func_us_80192B38,
    func_us_80192D64,
    EntityLifeUpSpawn,
    EntityClouds,
    func_us_80193050,
};

EInit OVL_EXPORT(EInitBreakable) = {
    ANIMSET_DRA(3), 0x0000, 0x0000, PAL_NULL, 0x0000,
};
EInit OVL_EXPORT(
    EInitObtainable) = {ANIMSET_DRA(3), 0x0000, 0x0000, PAL_NULL, 0x0001};
EInit OVL_EXPORT(
    EInitParticle) = {ANIMSET_DRA(3), 0x0000, 0x0000, PAL_NULL, 0x0002};
EInit D_us_80180438 = {ANIMSET_DRA(0), 0x0000, 0x0000, PAL_NULL, 0x0004};
EInit OVL_EXPORT(EInitInteractable) = {
    ANIMSET_DRA(0), 0x0000, 0x0000, PAL_NULL, 0x0005,
};
EInit OVL_EXPORT(
    EInitUnkId13) = {ANIMSET_DRA(0), 0x0000, 0x0000, PAL_NULL, 0x0002};
EInit OVL_EXPORT(
    EInitLockCamera) = {ANIMSET_DRA(0), 0x0000, 0x0000, PAL_NULL, 0x0001};
EInit OVL_EXPORT(
    EInitCommon) = {ANIMSET_DRA(0), 0x0000, 0x0000, PAL_NULL, 0x0003};
EInit OVL_EXPORT(
    EInitDamageNum) = {ANIMSET_DRA(0), 0x0000, 0x0000, PAL_NULL, 0x0003};
EInit g_EInitMedusa = {ANIMSET_OVL(3), 0x0000, 0x0048, 0x220, 0x016E};
EInit D_us_8018048C = {ANIMSET_DRA(0), 0x0000, 0x0000, PAL_NULL, 0x016F};
EInit D_us_80180498 = {ANIMSET_DRA(0), 0x0000, 0x0000, PAL_NULL, 0x0170};
EInit D_us_801804A4 = {ANIMSET_DRA(0), 0x0000, 0x0000, PAL_NULL, 0x0171};
// These two appear unused
EInit D_us_801804B0 = {ANIMSET_OVL(1), 0x0000, 0x0000, PAL_NULL, 0x0005};
EInit D_us_801804BC = {ANIMSET_OVL(2), 0x0000, 0x0000, PAL_NULL, 0x0005};
