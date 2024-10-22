/*
 * File: en_particles.c
 * Overlay: CHI
 * Description: ENTITY - Various particles with different behaviours
 */

#include "chi.h"

// func_801A50AC: CheckColliderOffsets
#include "../check_coll_offsets.h"

// [Rename in repo]
// func_801A519C: [E_PARTICLE_TRAIL] EntityUnkId13 (EntityParticleTrail)
#include "../entity_unkId13.h"

//D_80181378
static u16 g_eUnk14SpawnRots[] = {
    0x0010, 0x0020, 0x0030, 0x0040, 0x0050, 0x0060, 0x0070, 0x0000
};

void EntityUnkId14(Entity*);

// func_801A52AC: EntityUnkId14Spawner
#include "../entity_unkId14_spawner.h"

void EntityUnkId15(Entity*);

// func_801A53DC: EntityUnkId15Spawner
#include "../entity_unkId15_spawner.h"

// D_80181388
static s16 unk15_rot[] = {
    0x0030, 0x0050, 0x0080, 0x00B0, 0x00D0, 0x0100, 0x0100, 0x0000
};

// D_80181398
static s32 unk15_yVel[] = {
    0x00000400, 0x00002400, 0x00003C00, 0x00006000,
    0x00007800, 0x0000C000
};

// D_801813B0
static s32 unk14_yVel[] = {
    0x00000800, 0x00002800, 0x00004800, 0x00007000,
    0x0000E000, 0x00012000
};

// D_801813C8
static u8 unk14_startFrame[] = {
    0x01, 0x09, 0x15, 0x2B
};

// D_801813CC
static u16 unk14_lifetime[] = {
    0x0010, 0x0018, 0x002A, 0x002F
};

// func_801A54C4: [E_ID_14] EntityUnkId14
#include "../entity_unkId14.h"

// [Rename in shared files]
// func_801A55B4: [E_ID_15 (E_GREY_PUFF)] EntityUnkId15 (EntityDustPuff)
#include "../entity_unkId15.h"

extern u16 g_InitializeEntityData0[];

// D_801813D4
static u32 g_olroxDroolCollOffsets[] = {
    0x00000000, 0x000000FF
};

// func_801A56A8: EntityOlroxDrool
#include "../entity_olrox_drool.h"

// func_801A58D8: UnkCollisionFunc5
#include "../unk_collision_func5.h"

// func_801A59D4: UnkCollisionFunc4
#include "../unk_collision_func4.h"

// func_801A5F54: [E_INTENSE_EXPLOSION] EntityIntenseExplosion
#include "../entity_intense_explosion.h"

// D_801813DC
static u8 g_UnkEntityAnimData[] = {
    0x02, 0x01, 0x02, 0x02, 0x02, 0x03, 0x02, 0x04, 0x02, 0x05, 0x04, 0x06, 0xFF, 0x00, 0x00, 0x00
};

// func_801A6054: InitializeUnkEntity
#include "../initialize_unk_entity.h"

// func_801A6120: MakeEntityFromId
#include "../make_entity_from_id.h"

// func_801A61E8: MakeExplosions
#include "../make_explosions.h"

// func_801A62A0: EntityBigRedFireball
#include "../entity_big_red_fireball.h"