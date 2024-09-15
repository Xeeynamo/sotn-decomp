// SPDX-License-Identifier: AGPL-3.0-or-later
#include "mad.h"
#include "sfx.h"

#include "../../destroy_entity.h"
#include "../../destroy_entities_from_index.h"
#include "../prevent_entity_from_respawning.h"
#include "../animate_entity.h"

#include "../unk_anim_func.h"

#include "../get_distance_to_player_x.h"

#include "../get_distance_to_player_y.h"

#include "../get_side_to_player.h"

#include "../move_entity.h"

#include "../fall_entity.h"

u8 func_8019214C(void) {
    u8 unkState;
    Entity* entity;

    MoveEntity();
    FallEntity();

    entity = g_CurrentEntity;

    if (unkState & 1) {
        entity->velocityY = 0;
    }

    return unkState;
}

#include "../unk_collision_func3.h"

s32 func_80192408(u16* sensors, u16 arg1) {
    Collider col[5];
    s16 i;
    u16 var_a0;
    s16 x;
    s16 y;
    Collider* c;

    MoveEntity();
    FallEntity();
    if (g_CurrentEntity->velocityY >= 0) {
        x = g_CurrentEntity->posX.i.hi;
        y = i = g_CurrentEntity->posY.i.hi; // FAKE, no reason to set i.
        c = col;
        i = 0;
        while (true) {
            x += *sensors++;
            y += *sensors++;
            g_api.CheckCollision(x, y, c, 0);
            if (++i >= 4) {
                break;
            }
            c++;
        }

        var_a0 = true;
        for (i = 0, c = col; i < 4; i++, c++) {
            if (c->effects & EFFECT_UNK_8000) {
                // i in [0, 1]
                if (!(i >> 1)) {
                    break;
                }
            } else if (c->effects & EFFECT_SOLID) {
                if (i == 1 && !var_a0) {
                    c = col; // fake?
                    break;
                }
            } else if (i != 1) {
                var_a0 = false;
            }
        }

        for (i = 0; i < 4; i++) {
            c = &col[i];
            if (c->effects & EFFECT_SOLID) {
                if (i == 1) {
                    g_CurrentEntity->posY.i.hi += 4;
                }
                g_CurrentEntity->posY.i.hi += c->unk18;
                g_CurrentEntity->velocityY = 0;
                if (arg1) {
                    g_CurrentEntity->velocityX = 0;
                }
                return 1;
            }
        }
    }
    return 0;
}

#include "../unk_collision_func2.h"

#include "../alloc_entity.h"

s32 GetSineScaled(u8 arg0, s16 arg1) { return D_801809EC[arg0 & 0xFF] * arg1; }

s16 GetSine(u8 arg0) { return D_801809EC[arg0]; }

#include "../set_entity_velocity_from_angle.h"

#include "../ratan2_shifted.h"

#include "../get_angle_between_entities_shifted.h"

#include "../get_angle_point_to_entity_shifted.h"

#include "../adjust_value_within_threshold.h"

#include "../unk_entity_func0.h"

#include "../ratan2.h"

#include "../get_angle_between_entities.h"

#include "../get_angle_point_to_entity.h"

#include "../get_normalized_angle.h"

#include "../set_step.h"

#include "../set_sub_step.h"

void EntityExplosionSpawn(u16 arg0, u16 arg1) {
    Entity* entity;

    if (arg1 != 0) {
        g_api.PlaySfx(arg1);
    }
    if (arg0 == 0xFF) {
        DestroyEntity(g_CurrentEntity);
        return;
    }

    entity = g_CurrentEntity;
    entity->drawFlags = FLAG_DRAW_DEFAULT;
    entity->entityId = E_EXPLOSION;
    entity->pfnUpdate = (PfnEntityUpdate)EntityExplosion;
    entity->params = arg0;
    entity->animCurFrame = 0;
    g_CurrentEntity->step = 0;
    g_CurrentEntity->step_s = 0;
}

#include "../init_entity.h"

#include "../entity_dummy.h"

#include "../unk_collision_func.h"

#include "../check_field_collision.h"

#include "../get_player_collision_with.h"

#include "../replace_breakable_with_item_drop.h"
