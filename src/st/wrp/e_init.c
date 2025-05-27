// SPDX-License-Identifier: AGPL-3.0-or-later
#include "wrp.h"

void OVL_EXPORT(EntityRedDoor)(Entity*);
void OVL_EXPORT(EntityBackgroundBlock)(Entity*);
void OVL_EXPORT(EntityLockCamera)(Entity*);
void EntityUnkId13(Entity*);
void EntityExplosionVariants(Entity*);
void EntityGreyPuff(Entity*);
void EntityWarpRoom(Entity*);
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
    OVL_EXPORT(EntityBackgroundBlock), // unused
    OVL_EXPORT(EntityLockCamera),      // unused? looks debugging stuff
    EntityUnkId13,
    EntityExplosionVariants,
    EntityGreyPuff,
    EntityWarpRoom,
    EntityWarpSmallRocks,
};

EInit OVL_EXPORT(EInitBreakable) = {ANIMSET_OVL(1), 0, 0x00, 0x000, 0};
#include "../e_init_common.h"
EInit g_EInitSecret = {ANIMSET_OVL(1), 0, 0x00, 0x000, 3};
EInit g_EInitReverseSmallRocks = {ANIMSET_OVL(11), 1, 0x48, 0x21A, 97};
EInit g_EInitSmallRocks = {ANIMSET_OVL(1), 0, 0x00, 0x000, 5};

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
    {0x01D, 0x025, 0x075, 0x07D, 0x0C6, 0x0C7, 0x0C8, 0x0C9},
    {0x01F, 0x027, 0x077, 0x07F, 0x0CA, 0x0CB, 0x0CC, 0x0CD},
};
