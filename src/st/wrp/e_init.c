// SPDX-License-Identifier: AGPL-3.0-or-later
#include "wrp.h"
#include "../st_private.h"

void EntityBackgroundBlock(Entity*);
void EntityUnkId12(Entity*);
void EntityUnkId13(Entity*);
void EntityExplosionVariants(Entity*);
void EntityGreyPuff(Entity*);
void EntityWarpRoom(Entity*);
void EntityWarpSmallRocks(Entity*);
void EntityPrizeDrop(Entity*);
PfnEntityUpdate OVL_EXPORT(EntityUpdates)[] = {
    EntityBreakable,       EntityExplosion,         EntityPrizeDrop,
    EntityDamageDisplay,   EntityRedDoor,           EntityIntenseExplosion,
    EntitySoulStealOrb,    EntityRoomForeground,    EntityStageNamePopup,
    EntityEquipItemDrop,   EntityRelicOrb,          EntityHeartDrop,
    EntityEnemyBlood,      EntityMessageBox,        EntityDummy,
    EntityDummy,
    EntityBackgroundBlock, // unused
    EntityUnkId12,         // unused? looks debugging stuff
    EntityUnkId13,         EntityExplosionVariants, EntityGreyPuff,
    EntityWarpRoom,        EntityWarpSmallRocks,
};

u16 g_EInitBreakable[] = {ANIMSET_OVL(1), 0x0000, 0x0000, 0x0000, 0x0000};
u16 g_EInitObtainable[] = {ANIMSET_DRA(3), 0x0000, 0x0000, 0x0000, 0x0001};
u16 g_EInitParticle[] = {ANIMSET_DRA(3), 0x0000, 0x0000, 0x0000, 0x0002};
u16 g_EInitMaria[] = {ANIMSET_DRA(0), 0x0000, 0x0000, 0x0000, 0x0004};
u16 g_EInitInteractable[] = {ANIMSET_DRA(0), 0x0000, 0x0000, 0x0000, 0x0005};
u16 g_EInitUnkId13[] = {ANIMSET_DRA(0), 0x0000, 0x0000, 0x0000, 0x0002};
u16 g_EInitUnkId12[] = {ANIMSET_DRA(0), 0x0000, 0x0000, 0x0000, 0x0001};
u16 g_EInitCommon[] = {ANIMSET_DRA(0), 0x0000, 0x0000, 0x0000, 0x0003};
u16 g_EInitDamageNum[] = {ANIMSET_DRA(0), 0x0000, 0x0000, 0x0000, 0x0003};
u16 g_EInitUnused[] = {ANIMSET_OVL(1), 0x0000, 0x0000, 0x0000, 0x0003};
u16 g_EInitReverseSmallRocks[] = {
    ANIMSET_OVL(11), 0x0001, 0x0048, 0x021A, 0x0061};
u16 g_EInitSmallRocks[] = {ANIMSET_OVL(1), 0x0000, 0x0000, 0x0000, 0x0005};

static u32 D_801804D0[] = {0x00FF0140};
static u32 D_801804D4[] = {0x26022502, 0x26022702, 0x00000000};
ObjInit g_eBackgroundBlockInit[] = {
    {0x0006, 0x01FA, 0x0000, 0x0000, 0x00, 0x10, 0x00000000, D_801804D0},
    {0x8001, 0x00C0, 0x0000, 0x0000, 0x03, 0x30, 0x00000000, D_801804D4},
};

// Owned by EntityRedDoor to animate the tiles behind the door itself.
// There is a loop in EntityRedDoor that forces to write those tiles
// at every frame based on the door state to create the animation.
u16 g_eRedDoorTiles[][8] = {
    {0x1D, 0x25, 0x75, 0x7D, 0xC6, 0xC7, 0xC8, 0xC9},
    {0x1F, 0x27, 0x77, 0x7F, 0xCA, 0xCB, 0xCC, 0xCD},
};
