// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cen.h"

void EntityBreakable(Entity*);
void EntityExplosion(Entity*);
void EntityPrizeDrop(Entity*);
void EntityDamageDisplay(Entity*);
void EntityRedDoor(Entity*);
void EntityIntenseExplosion(Entity*);
void EntitySoulStealOrb(Entity*);
void EntityRoomForeground(Entity*);
void EntityStageNamePopup(Entity*);
void EntityEquipItemDrop(Entity*);
void EntityRelicOrb(Entity*);
void EntityHeartDrop(Entity*);
void EntityEnemyBlood(Entity*);
void EntityMessageBox(Entity*);
void EntityDummy(Entity*);
void EntityBackgroundBlock(Entity*);
void EntityUnkId12(Entity*);
void EntityUnkId13(Entity*);
void EntityExplosionVariants(Entity*);
void EntityGreyPuff(Entity*);
void OVL_EXPORT(EntityCutscene)(Entity*);
void EntityPlatform(Entity*);
void EntityMaria(Entity*);
void EntityRoomDarkness(Entity*);
void EntityElevatorStationary(Entity*);
void EntityUnkId1B(Entity*);
void EntityMovingElevator(Entity*);

PfnEntityUpdate OVL_EXPORT(EntityUpdates)[] = {
    EntityBreakable,       EntityExplosion,
    EntityPrizeDrop,       EntityDamageDisplay,
    EntityRedDoor,         EntityIntenseExplosion,
    EntitySoulStealOrb,    EntityRoomForeground,
    EntityStageNamePopup,  EntityEquipItemDrop,
    EntityRelicOrb,        EntityHeartDrop,
    EntityEnemyBlood,      EntityMessageBox,
    EntityDummy,           EntityDummy,
    EntityBackgroundBlock, EntityUnkId12,
    EntityUnkId13,         EntityExplosionVariants,
    EntityGreyPuff,        OVL_EXPORT(EntityCutscene),
    EntityPlatform,        EntityMaria,
    EntityRoomDarkness,    EntityElevatorStationary,
    EntityUnkId1B,         EntityMovingElevator,
};

EInit OVL_EXPORT(EInitBreakable) = {ANIMSET_OVL(1), 0, 0x00, 0x000, 0};
#include "../e_init_common.h"
EInit g_EInitElevator = {ANIMSET_OVL(11), 1, 0x48, 0x223, 5};

static u32 JUNK_80180488 = 0x00FF0140;
static u32 D_8018048C = 0x00FF0740;

ObjInit OVL_EXPORT(BackgroundBlockInit) = {
    .animSet = ANIMSET_OVL(2),
    .zPriority = 129,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .drawFlags = DRAW_DEFAULT,
    .unkC = NULL,
    .animFrames = &D_8018048C,
};

u16 OVL_EXPORT(RedDoorTiles)[][8] = {
    {0x39C, 0x39B, 0x39C, 0x39B, 0x10D, 0x10B, 0x10D, 0x10B},
    {0x3A3, 0x3A4, 0x3A5, 0x3A6, 0x2F4, 0x309, 0x305, 0x307},
    {0x3A3, 0x3A7, 0x3A8, 0x3A3, 0x2F4, 0x30F, 0x310, 0x2F4},
};
