// SPDX-License-Identifier: AGPL-3.0-or-later
#include "mad.h"

#define HEART_DROP_CASTLE_FLAG 0
#include "../entity_heart_drop.h"

#include "../check_coll_offsets.h"

#include "../entity_unkId13.h"

#include "../entity_unkId14_spawner.h"

#include "../entity_unkId15_spawner.h"

#include "../entity_unkId14.h"

#include "../entity_unkId15.h"

#include "../entity_olrox_drool.h"

#include "../unk_collision_func5.h"

#include "../unk_collision_func4.h"

#include "../entity_intense_explosion.h"

#include "../initialize_unk_entity.h"

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

#include "../make_entity_from_id.h"

#include "../make_explosions.h"

#include "../entity_big_red_fireball.h"

#include "../unk_recursive_primfunc_1.h"

#include "../unk_recursive_primfunc_2.h"

#include "../clut_lerp.h"

#include "../play_sfx_positional.h"
