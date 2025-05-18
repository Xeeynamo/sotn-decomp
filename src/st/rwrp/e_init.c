// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rwrp.h"
#include "../st_private.h"

void OVL_EXPORT(EntityRedDoor)(Entity*);
void EntityBackgroundBlock(Entity*);
void EntityLockCamera(Entity*);
void EntityUnkId13(Entity*);
void EntityExplosionVariants(Entity*);
void EntityGreyPuff(Entity*);
void EntityRWarpRoom(Entity*);
void EntityWarpSmallRocks(Entity*);
void EntityPrizeDrop(Entity*);
PfnEntityUpdate OVL_EXPORT(EntityUpdates)[] = {
    EntityBreakable,
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
    EntityBackgroundBlock, // unused
    EntityLockCamera,      // unused? looks debugging stuff
    EntityUnkId13,
    EntityExplosionVariants,
    EntityGreyPuff,
    EntityRWarpRoom,
    EntityWarpSmallRocks,
};

// *** Group here all the Entity Init ***
EInit OVL_EXPORT(EInitBreakable) = {ANIMSET_OVL(1), 0, 0x00, 0x000, 0};
u16 g_EInitObtainable[] = {
    0x0003, 0x0000, 0x0000, 0x0000, 0x0001, 0x0000,
};
u16 g_EInitParticle[] = {
    0x0003, 0x0000, 0x0000, 0x0000, 0x0002, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000,
};
u16 g_EInitInteractable[] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0005, 0x0000,
};
u16 g_EInitUnkId13[] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0002, 0x0000,
};
u16 g_EInitLockCamera[] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0000,
};
u16 g_EInitCommon[] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0003, 0x0000,
};
u16 g_EInitDamageNum[] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0003, 0x0000,
};
u16 D_801804AC[] = {
    0x8001, 0x0000, 0x0000, 0x0000, 0x0003, 0x0000,
};
u16 g_EInitReverseSmallRocks[] = {
    0x8001, 0x0000, 0x0000, 0x0000, 0x0005, 0x0000,
};
u16 g_EInitSmallRocks[] = {
    0x8002, 0x0000, 0x0000, 0x82E8, 0x0005, 0x0000,
};
// ******

static u8 D_801804D0[] = {0x40, 0x01, 0xFF, 0x00};
static u8 D_801804D4[] = {0x02, 0x25, 0x02, 0x26, 0x02, 0x27, 0x02, 0x26, 0x00};
ObjInit2 OVL_EXPORT(BackgroundBlockInit)[] = {
    {
        .animSet = 0x0006,
        .zPriority = 0x01FA,
        .unk5A = 0x0000,
        .palette = PAL_DRA(0),
        .drawFlags = FLAG_DRAW_DEFAULT,
        .drawMode = DRAW_TPAGE,
        .flags = 0,
        .animFrames = D_801804D0,
    },
    {
        .animSet = 0x8001,
        .zPriority = 0x00C0,
        .unk5A = 0,
        .palette = PAL_DRA(0),
        .drawFlags = FLAG_DRAW_ROTY | FLAG_DRAW_ROTX,
        .drawMode = DRAW_TPAGE2 | DRAW_TPAGE,
        .flags = 0,
        .animFrames = D_801804D4,
    }};

// Owned by EntityRedDoor to animate the tiles behind the door itself.
// There is a loop in EntityRedDoor that forces to write those tiles
// at every frame based on the door state to create the animation.
u16 OVL_EXPORT(RedDoorTiles)[][8] = {
    {0x7D, 0x75, 0x25, 0x1D, 0xC9, 0xC8, 0xC7, 0xC6},
    {0x7F, 0x77, 0x27, 0x1F, 0xCD, 0xCC, 0xCB, 0xCA},
};
