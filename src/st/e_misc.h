// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stage.h>

#ifndef CASTLE_FLAG_BANK
#define CASTLE_FLAG_BANK 0
#endif

extern u16 D_80180608[];

#include "entity_relic_orb.h"

void EntityHeartDrop(Entity* self) {
    u16 index;
    u8 value;
    PfnEntityUpdate update;

    if (!self->step) {
        index = self->ext.heartDrop.unkB4 =
            self->params + 0x118 + CASTLE_FLAG_BANK;
        value = g_CastleFlags[(index >> 3) + HEART_FLAGS_START] >> (index & 7);
        if (value & 1) {
            DestroyEntity(self);
            return;
        }

        index -= 0x118 + CASTLE_FLAG_BANK;
        index = D_80180608[index];
        if (index < 128) {
            self->ext.heartDrop.update = EntityPrizeDrop;
        } else {
            self->ext.heartDrop.update = EntityEquipItemDrop;
            index -= 128;
        }
        self->params = index + 0x8000;
    } else {
        index = self->ext.heartDrop.unkB4;
        if (self->step < 5) {
            if (self->hitFlags) {
                g_CastleFlags[(index >> 3) + HEART_FLAGS_START] |= 1 << (index & 7);
                self->step = 5;
            }
        }
    }
    update = self->ext.heartDrop.update;
    update(self);
}

#include "entity_message_box.h"

#include "check_coll_offsets.h"

#include "entity_unkId13.h"

u16 g_eUnk14SpawnRots[] = {
    /* FE8 */ 0x0010,
    /* FEA */ 0x0020,
    /* FEC */ 0x0030,
    /* FEE */ 0x0040,
    /* FF0 */ 0x0050,
    /* FF2 */ 0x0060,
    /* FF4 */ 0x0070,
    /* FF6 */ 0x0000,
};
#include "entity_unkId14_spawner.h"

#include "entity_unkId15_spawner.h"

static s16 unk15_rot[] = {
    /* FF8 */ 0x0030,
    /* FFA */ 0x0050,
    /* FFC */ 0x0080,
    /* FFE */ 0x00B0,
    /* 1000 */ 0x00D0,
    /* 1002 */ 0x0100,
    /* 1004 */ 0x0100,
    /* 1006 */ 0x0000,
};

static s32 unk15_yVel[] = {
    /* 1008 */ 0x00000400,
    /* 100C */ 0x00002400,
    /* 1010 */ 0x00003C00,
    /* 1014 */ 0x00006000,
    /* 1018 */ 0x00007800,
    /* 101C */ 0x0000C000,
};

s32 unk14_yVel[] = {
    /* 1020 */ 0x00000800,
    /* 1024 */ 0x00002800,
    /* 1028 */ 0x00004800,
    /* 102C */ 0x00007000,
    /* 1030 */ 0x0000E000,
    /* 1034 */ 0x00012000,
};

u8 unk14_startFrame[] = {
    /* 1038 */ 0x01,
    /* 1039 */ 0x09,
    /* 103A */ 0x15,
    /* 103B */ 0x2B,
};

u16 unk14_lifetime[] = {
    /* 103C */ 0x0010,
    /* 103E */ 0x0018,
    /* 1040 */ 0x002A,
    /* 1042 */ 0x002F,
};

#include "entity_unkId14.h"

#include "entity_unkId15.h"

u32 g_olroxDroolCollOffsets[] = {
    /* 1044 */ 0x00000000,
    /* 1048 */ 0x000000FF,
};
#include "entity_olrox_drool.h"

#include "unk_collision_func5.h"

#include "unk_collision_func4.h"

#include "entity_intense_explosion.h"

u8 g_UnkEntityAnimData[] = {
    2, 1, 2, 2, 2, 3, 2, 4, 2, 5, 4, 6, -1,
};

#include "initialize_unk_entity.h"

#include "make_entity_from_id.h"

#include "make_explosions.h"

u16 g_UnkRecursPrimVecOrder[] = {
    0, 1, 3, 4, 1, 2, 4, 5, 3, 4, 6, 7, 4, 5, 7, 8};
#include "entity_big_red_fireball.h"

#include "unk_recursive_primfunc_1.h"

u16 g_UnkRecursPrim2Inds[] = {
    0, 1, 3, 4, 1, 2, 4, 5, 3, 4, 6, 7, 4, 5, 7, 8, 0, 0};

#include "unk_recursive_primfunc_2.h"

#include "clut_lerp.h"

#include "play_sfx_positional.h"
