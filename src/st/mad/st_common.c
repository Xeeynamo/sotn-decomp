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

static s16 g_SineTable[] = {
    0x0000, 0x0065, 0x00C9, 0x012D, 0x0191, 0x01F5, 0x0259, 0x02BC, 0x031F,
    0x0381, 0x03E3, 0x0444, 0x04A5, 0x0505, 0x0564, 0x05C2, 0x061F, 0x067C,
    0x06D7, 0x0732, 0x078B, 0x07E3, 0x083A, 0x088F, 0x08E4, 0x0937, 0x0988,
    0x09D8, 0x0A26, 0x0A73, 0x0ABF, 0x0B08, 0x0B50, 0x0B97, 0x0BDB, 0x0C1E,
    0x0C5E, 0x0C9D, 0x0CDA, 0x0D15, 0x0D4E, 0x0D85, 0x0DB9, 0x0DEC, 0x0E1C,
    0x0E4B, 0x0E77, 0x0EA1, 0x0EC8, 0x0EEE, 0x0F11, 0x0F31, 0x0F50, 0x0F6C,
    0x0F85, 0x0F9C, 0x0FB1, 0x0FC4, 0x0FD4, 0x0FE1, 0x0FEC, 0x0FF5, 0x0FFB,
    0x0FFF, 0x1000, 0x0FFF, 0x0FFB, 0x0FF5, 0x0FEC, 0x0FE1, 0x0FD4, 0x0FC4,
    0x0FB1, 0x0F9C, 0x0F85, 0x0F6C, 0x0F50, 0x0F31, 0x0F11, 0x0EEE, 0x0EC8,
    0x0EA1, 0x0E77, 0x0E4B, 0x0E1C, 0x0DEC, 0x0DB9, 0x0D85, 0x0D4E, 0x0D15,
    0x0CDA, 0x0C9D, 0x0C5E, 0x0C1E, 0x0BDB, 0x0B97, 0x0B50, 0x0B08, 0x0ABF,
    0x0A73, 0x0A26, 0x09D8, 0x0988, 0x0937, 0x08E4, 0x088F, 0x083A, 0x07E3,
    0x078B, 0x0732, 0x06D7, 0x067C, 0x061F, 0x05C2, 0x0564, 0x0505, 0x04A5,
    0x0444, 0x03E3, 0x0381, 0x031F, 0x02BC, 0x0259, 0x01F5, 0x0191, 0x012D,
    0x00C9, 0x0065, 0x0000, 0xFF9B, 0xFF37, 0xFED3, 0xFE6F, 0xFE0B, 0xFDA7,
    0xFD44, 0xFCE1, 0xFC7F, 0xFC1D, 0xFBBC, 0xFB5B, 0xFAFB, 0xFA9C, 0xFA3E,
    0xF9E1, 0xF984, 0xF929, 0xF8CE, 0xF875, 0xF81D, 0xF7C6, 0xF771, 0xF71C,
    0xF6C9, 0xF678, 0xF628, 0xF5DA, 0xF58D, 0xF541, 0xF4F8, 0xF4B0, 0xF469,
    0xF425, 0xF3E2, 0xF3A2, 0xF363, 0xF326, 0xF2EB, 0xF2B2, 0xF27B, 0xF247,
    0xF214, 0xF1E4, 0xF1B5, 0xF189, 0xF15F, 0xF138, 0xF112, 0xF0EF, 0xF0CF,
    0xF0B0, 0xF094, 0xF07B, 0xF064, 0xF04F, 0xF03C, 0xF02C, 0xF01F, 0xF014,
    0xF00B, 0xF005, 0xF001, 0xF000, 0xF001, 0xF005, 0xF00B, 0xF014, 0xF01F,
    0xF02C, 0xF03C, 0xF04F, 0xF064, 0xF07B, 0xF094, 0xF0B0, 0xF0CF, 0xF0EF,
    0xF112, 0xF138, 0xF15F, 0xF189, 0xF1B5, 0xF1E4, 0xF214, 0xF247, 0xF27B,
    0xF2B2, 0xF2EB, 0xF326, 0xF363, 0xF3A2, 0xF3E2, 0xF425, 0xF469, 0xF4B0,
    0xF4F8, 0xF541, 0xF58D, 0xF5DA, 0xF628, 0xF678, 0xF6C9, 0xF71C, 0xF771,
    0xF7C6, 0xF81D, 0xF875, 0xF8CE, 0xF929, 0xF984, 0xF9E1, 0xFA3E, 0xFA9C,
    0xFAFB, 0xFB5B, 0xFBBC, 0xFC1D, 0xFC7F, 0xFCE1, 0xFD44, 0xFDA7, 0xFE0B,
    0xFE6F, 0xFED3, 0xFF37, 0xFF9B,
};

s32 GetSineScaled(u8 arg0, s16 arg1) { return g_SineTable[arg0 & 0xFF] * arg1; }

s16 GetSine(u8 arg0) { return g_SineTable[arg0]; }

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
