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

REDACTED
REDACTED
REDACTED

    MoveEntity();
    FallEntity();

    entity = g_CurrentEntity;
REDACTED
REDACTED
        entity->velocityY = 0;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
#include "../unk_collision_func3.h"

INCLUDE_ASM("asm/us/st/mad/nonmatchings/11D3C", func_80192408);

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
REDACTED
        return;
    }

    entity = g_CurrentEntity;
    entity->drawFlags = 0;
    entity->entityId = E_EXPLOSION;
    entity->pfnUpdate = (PfnEntityUpdate)EntityExplosion;
REDACTED
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
