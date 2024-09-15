// SPDX-License-Identifier: AGPL-3.0-or-later
#include "st0.h"
#include "sfx.h"

#include "../../destroy_entity.h"
#include "../../destroy_entities_from_index.h"
#include "../prevent_entity_from_respawning.h"
#include "../animate_entity.h"

#include "../unk_anim_func.h"

// Absolute distance from g_CurrentEntity to the player in the X Axis
s16 GetDistanceToPlayerX(void) {
    s16 xDistance = g_CurrentEntity->posX.i.hi - PLAYER.posX.i.hi;

    if (xDistance < 0) {
        xDistance = -xDistance;
    }
    return xDistance;
}

// Absolute distance from g_CurrentEntity to the player in the Y Axis
s32 GetDistanceToPlayerY(void) {
    s32 yDistance = g_CurrentEntity->posY.i.hi - PLAYER.posY.i.hi;

    if (yDistance < 0) {
        yDistance = -yDistance;
    }
    return yDistance;
}

s32 GetSideToPlayer(void) {
    s16 side = g_CurrentEntity->posX.i.hi > PLAYER.posX.i.hi;

    if (g_CurrentEntity->posY.i.hi > PLAYER.posY.i.hi) {
        side |= 2;
    }
    return side;
}

#include "../move_entity.h"

#include "../fall_entity.h"

u8 func_801B4D18(void) {
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

INCLUDE_ASM("st/st0/nonmatchings/34908", func_801B4FD4);

#include "../unk_collision_func2.h"

#include "../alloc_entity.h"

extern s16 g_SineTable[];

#include "../get_sine_scaled.h"

#include "../get_sine.h"

#include "../set_entity_velocity_from_angle.h"

#include "../ratan2_shifted.h"

#include "../get_angle_between_entities_shifted.h"

#include "../get_angle_point_to_entity_shifted.h"

#include "../adjust_value_within_threshold.h"

#include "../unk_entity_func0.h"

#include "../ratan2.h"

#include "../get_angle_between_entities.h"

#include "../get_angle_point_to_entity.h"

// different from other versions
u16 GetNormalizedAngle(u16 arg0, s16 arg1, s16 arg2) {
    u16 temp_a2 = arg2 - arg1;
    u16 ret;

    if (temp_a2 & 0x800) {
        ret = temp_a2 & 0x7FF;
    } else {
        ret = temp_a2;
    }

    if (ret > arg0) {
        if (temp_a2 & 0x800) {
            ret = arg1 - arg0;
        } else {
            ret = arg1 + arg0;
        }

        return ret;
    }

    return arg2;
}

#include "../set_step.h"

#include "../set_sub_step.h"

void func_801B57D0(u16 params) {
    Entity* current;

    if (params == 0xFF) {
        DestroyEntity(g_CurrentEntity);
        return;
    }
    current = g_CurrentEntity;
    g_CurrentEntity->entityId = E_EXPLOSION;
    g_CurrentEntity->pfnUpdate = EntityExplosion;
    g_CurrentEntity->drawFlags = FLAG_DRAW_DEFAULT;
    current->params = params;
    current->animCurFrame = 0;
    g_CurrentEntity->step = 0;
    g_CurrentEntity->step_s = 0;
}

#include "../init_entity.h"

#include "../entity_dummy.h"

#include "../unk_collision_func.h"

#include "../check_field_collision.h"

// This function checks if the player collides with the specified self
// and from which direction.
// w and h holds the collider size of the self
// while flags stores which sides are solid
s32 GetPlayerCollisionWith(Entity* self, u16 w, u16 h, u16 flags) {
    Entity* pl;
    s16 x;
    s16 y;
    u16 checks;

    pl = &PLAYER;

    if (self->posX.i.hi & 0x100) {
        return 0;
    }
    if (self->posY.i.hi & 0x100) {
        return 0;
    }

    x = pl->posX.i.hi - self->posX.i.hi;
    y = pl->posY.i.hi - self->posY.i.hi;
    if (self->facingLeft) {
        x += self->hitboxOffX;
    } else {
        x -= self->hitboxOffX;
    }
    y -= self->hitboxOffY;

    if (x > 0) {
        checks = 1;
    } else {
        checks = 0;
    }
    if (y > 0) {
        checks |= 2;
    }

    w += 8;
    h += 24;

    x += w;
    y += h;
    w += w;
    h += h;
    if ((u16)x > w || (u16)y > h) {
        return 0;
    }

    if (x && x != w) {
        // check collision from top
        if (flags & 4 && checks ^ 2 && pl->velocityY >= 0 && y < 8) {
            pl->posY.i.hi -= y;
            g_Player.pl_vram_flag |= 0x41;
            return 4;
        }

        // check collision from bottom
        if (flags & 2 && checks & 2 && (pl->velocityY <= 0 || flags & 0x10)) {
            y = h - y;
            if (y < 0x10) {
                pl->posY.i.hi += y;
                g_Player.pl_vram_flag |= 0x42;
                return 2;
            }
        }
    }

    // check collision from the sides
    if (y && y != h && flags & 1) {
        if (checks & 1) {
            x = w - x;
            if (flags & 8 && x > 2) {
                x = 2;
            }
            pl->posX.i.hi += x;
            return 1;
        } else {
            if (flags & 8 && x > 2) {
                x = 2;
            }
            pl->posX.i.hi -= x;
            return 1;
        }
    }

    return 0;
}

#include "../replace_breakable_with_item_drop.h"
