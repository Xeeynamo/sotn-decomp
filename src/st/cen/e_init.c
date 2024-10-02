// SPDX-License-Identifier: AGPL-3.0-or-later
#include "game.h"
#include "stage.h"
#define OVL_EXPORT(x) CEN_##x

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
void EntityUnkId14(Entity*);
void EntityUnkId15(Entity*);
void OVL_EXPORT(EntityCutscene)(Entity*);
void EntityPlatform(Entity*);
void EntityMaria(Entity*);
void EntityRoomDarkness(Entity*);
void EntityElevatorStationary(Entity*);
void EntityUnkId1B(Entity*);
void EntityMovingElevator(Entity*);

PfnEntityUpdate PfnEntityUpdates[] = {
    EntityBreakable,       EntityExplosion,
    EntityPrizeDrop,       EntityDamageDisplay,
    EntityRedDoor,         EntityIntenseExplosion,
    EntitySoulStealOrb,    EntityRoomForeground,
    EntityStageNamePopup,  EntityEquipItemDrop,
    EntityRelicOrb,        EntityHeartDrop,
    EntityEnemyBlood,      EntityMessageBox,
    EntityDummy,           EntityDummy,
    EntityBackgroundBlock, EntityUnkId12,
    EntityUnkId13,         EntityUnkId14,
    EntityUnkId15,         OVL_EXPORT(EntityCutscene),
    EntityPlatform,        EntityMaria,
    EntityRoomDarkness,    EntityElevatorStationary,
    EntityUnkId1B,         EntityMovingElevator,
};

EntityInit D_80180404 = {
    .animSet = ANIMSET_OVL(1),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 0,
};

EntityInit g_InitializeData0 = {
    .animSet = ANIMSET_DRA(3),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 1,
};

EntityInit g_InitializeEntityData0 = {
    .animSet = ANIMSET_DRA(3),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 2,
};

EntityInit g_eMariaInit = {
    .animSet = ANIMSET_DRA(0),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 4,
};

EntityInit g_EInitGeneric = {
    .animSet = ANIMSET_DRA(0),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 5,
};

EntityInit g_InitDataEnt13 = {
    .animSet = ANIMSET_DRA(0),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 2,
};

EntityInit g_EntityUnkId12Init = {
    .animSet = ANIMSET_DRA(0),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 1,
};

EntityInit g_eInitGeneric2 = {
    .animSet = ANIMSET_DRA(0),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 3,
};

EntityInit g_eDamageDisplayInit = {
    .animSet = ANIMSET_DRA(0),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 3,
};

EntityInit D_80180470 = {
    .animSet = ANIMSET_OVL(1),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 3,
};

EntityInit g_eElevatorInit = {
    .animSet = ANIMSET_OVL(11),
    .animCurFrame = 1,
    .unk5A = 72,
    .palette = PAL_DRA(547),
    .enemyId = 5,
};

static u32 JUNK_80180488 = 0x00FF0140;
static u32 D_8018048C = 0x00FF0740;

ObjInit g_eBackgroundBlockInit = {
    .animSet = ANIMSET_OVL(2),
    .zPriority = 129,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .drawFlags = DRAW_DEFAULT,
    .unkC = NULL,
    .animFrames = &D_8018048C,
};

u16 g_eRedDoorTiles[][8] = {
    {0x039C, 0x039B, 0x039C, 0x039B, 0x010D, 0x010B, 0x010D, 0x010B},
    {0x03A3, 0x03A4, 0x03A5, 0x03A6, 0x02F4, 0x0309, 0x0305, 0x0307},
    {0x03A3, 0x03A7, 0x03A8, 0x03A3, 0x02F4, 0x030F, 0x0310, 0x02F4},
};
