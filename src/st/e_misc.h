// SPDX-License-Identifier: AGPL-3.0-or-later

#include "entity_relic_orb.h"

#if STAGE != STAGE_ST0
#include "entity_heart_drop.h"

#if !defined(VERSION_BETA)
#include "entity_message_box.h"
#endif

#endif

#include "check_coll_offsets.h"

#include "entity_unkId13.h"

#include "entity_explosion_variants_spawner.h"

#include "entity_greypuff_spawner.h"

// NOTE: This entity data is slightly out of order.
// Grey puff data comes before explosion variants data,
// but explosion variant entity comes before grey puff entity.

static s16 greyPuff_rot[] = {
    /* FF8 */ 0x0030,
    /* FFA */ 0x0050,
    /* FFC */ 0x0080,
    /* FFE */ 0x00B0,
    /* 1000 */ 0x00D0,
    /* 1002 */ 0x0100,
    /* 1004 */ 0x0100,
    /* 1006 */ 0x0000,
};

static s32 greyPuff_yVel[] = {
    /* 1008 */ FIX(2.0 / 128),
    /* 100C */ FIX(18.0 / 128),
    /* 1010 */ FIX(30.0 / 128),
    /* 1014 */ FIX(48.0 / 128),
    /* 1018 */ FIX(60.0 / 128),
    /* 101C */ FIX(96.0 / 128),
};

static s32 explode_yVel[] = {
    /* 1020 */ FIX(4.0 / 128),
    /* 1024 */ FIX(20.0 / 128),
    /* 1028 */ FIX(36.0 / 128),
    /* 102C */ FIX(56.0 / 128),
    /* 1030 */ FIX(112.0 / 128),
    /* 1034 */ FIX(144.0 / 128),
};

static u8 explode_startFrame[] = {
    /* 1038 */ 1,
    /* 1039 */ 9,
    /* 103A */ 21,
    /* 103B */ 43,
};

static u16 explode_lifetime[] = {
    /* 103C */ 0x0010,
    /* 103E */ 0x0018,
    /* 1040 */ 0x002A,
    /* 1042 */ 0x002F,
};

#include "entity_explosion_variants.h"

#include "entity_greypuff.h"

u32 g_olroxDroolCollOffsets[] = {
    /* 1044 */ 0x00000000,
    /* 1048 */ 0x000000FF,
};
#include "entity_olrox_drool.h"

#include "unk_collision_func5.h"

#if !defined(STAGE_IS_NO0)
#include "unk_collision_func4.h"
#endif

#include "entity_intense_explosion.h"

u8 g_UnkEntityAnimData[] = {
    2, 1, 2, 2, 2, 3, 2, 4, 2, 5, 4, 6, -1,
};

#include "initialize_unk_entity.h"

#if defined(VERSION_BETA)
void func_801966B0(u16* sensors) {
    switch (g_CurrentEntity->step_s) {
    case 0:
        g_CurrentEntity->animCurFrame = 0;
        g_CurrentEntity->hitboxState = 0;
        g_CurrentEntity->zPriority -= 0x10;
        g_CurrentEntity->drawFlags |= DRAW_HIDE;
        g_CurrentEntity->unk6C = 0;
        g_CurrentEntity->step_s++;
        break;
    case 1:
        if (UnkCollisionFunc3(sensors) & 1) {
            g_CurrentEntity->animCurFrame = 1;
            g_CurrentEntity->step_s++;
        }
        break;
    case 2:
        g_CurrentEntity->unk6C += 2;
        if (g_CurrentEntity->unk6C == 0xC0) {
            g_CurrentEntity->drawFlags = FLAG_DRAW_DEFAULT;
            g_CurrentEntity->drawMode = DRAW_DEFAULT;
            g_CurrentEntity->hitEffect = g_CurrentEntity->palette;
            g_CurrentEntity->step_s++;
            D_80199DE8 = 64;
        }
        break;
    case 3:
        if (D_80199DE8 & 1) {
            g_CurrentEntity->palette = g_CurrentEntity->hitEffect;
        } else {
            g_CurrentEntity->palette = PAL_OVL(0x19F);
        }
        if (!--D_80199DE8) {
            g_CurrentEntity->hitboxState = 3;
            g_CurrentEntity->palette = g_CurrentEntity->hitEffect;
            SetStep(1);
        }
        break;
    }
}
#endif

#include "make_entity_from_id.h"

#include "make_explosions.h"

#include "entity_big_red_fireball.h"

#if !defined(STAGE_IS_NO0)
u16 g_UnkRecursPrimVecOrder[] = {
    0, 1, 3, 4, 1, 2, 4, 5, 3, 4, 6, 7, 4, 5, 7, 8};
#include "unk_recursive_primfunc_1.h"

u16 g_UnkRecursPrim2Inds[] = {0, 1, 3, 4, 1, 2, 4, 5, 3, 4, 6, 7, 4, 5, 7, 8,
#if !defined(STAGE_IS_NZ0) && !defined(STAGE_IS_NO1) && STAGE != STAGE_ST0
                              0, 0,
#endif
#if defined(VERSION_BETA)
                              0, 0
#endif
};

#include "unk_recursive_primfunc_2.h"
#endif

#include "clut_lerp.h"

#include "play_sfx_positional.h"
