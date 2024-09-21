// SPDX-License-Identifier: AGPL-3.0-or-later
#include "wrp.h"
#include "../st_private.h"

void func_80186FD0(Entity*);
void EntityUnkId12(Entity*);
void EntityUnkId13(Entity*);
void EntityUnkId14(Entity*);
void EntityUnkId15(Entity*);
void EntityWarpRoom(Entity*);
void EntityWarpSmallRocks(Entity*);
void EntityPrizeDrop(Entity*);
PfnEntityUpdate PfnEntityUpdates[] = {
    EntityBreakable,
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
    EntityHeartDrop,
    EntityEnemyBlood,
    EntityMessageBox,
    EntityDummy,
    EntityDummy,
    func_80186FD0, // unused
    EntityUnkId12, // unused? looks debugging stuff
    EntityUnkId13,
    EntityUnkId14,
    EntityUnkId15,
    EntityWarpRoom,
    EntityWarpSmallRocks,
};

u16 g_eBreakableInit[] = {
    0x8001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};
u16 g_InitializeData0[] = {
    0x0003, 0x0000, 0x0000, 0x0000, 0x0001, 0x0000,
};
u16 g_InitializeEntityData0[] = {
    0x0003, 0x0000, 0x0000, 0x0000, 0x0002, 0x0000,
};
u16 g_MariaInit[] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000,
};
u16 g_EInitGeneric[] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0005, 0x0000,
};
u16 g_InitDataEnt13[] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0002, 0x0000,
};
u16 g_EntityUnkId12Init[] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0000,
};
u16 g_eInitGeneric2[] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0003, 0x0000,
};
u16 g_eDamageDisplayInit[] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0003, 0x0000,
};
u16 D_801804AC[] = {
    0x8001, 0x0000, 0x0000, 0x0000, 0x0003, 0x0000,
};
u16 g_EInitReverseSmallRocks[] = {
    0x800B, 0x0001, 0x0048, 0x021A, 0x0061, 0x0000,
};
u16 g_EInitSmallRocks[] = {
    0x8001, 0x0000, 0x0000, 0x0000, 0x0005, 0x0000,
};

static u32 D_801804D0[] = {0x00FF0140};
static u32 D_801804D4[] = {0x26022502, 0x26022702, 0x00000000};
ObjInit D_801804E0[] = {
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
