// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

static s16 sensors_move[] = {0, 32, 8, 0};
static s16 sensors_ground[4][2] = {{0, 32}, {0, 4}, {8, -4}, {-16, 0}};
static s16 dead_particle_pos[][2] = {
    {-8, -4}, {8, -6}, {-2, 4}, {-1, -7}, {2, 8}, {11, -7}, {4, 6}, {-3, 0}};
static u16 unused[] = {
    0x0114, 0x020A, 0x030A, 0x0414, 0x030A, 0x020A, 0x0000, 0x0000, 0x0508,
    0x0608, 0x0708, 0x0D08, 0x0E08, 0x0F02, 0x1402, 0x1502, 0x1620, 0x1708,
    0x0000, 0x0000, 0x0508, 0x0608, 0x0708, 0x0808, 0x090A, 0x0A04, 0x0B04,
    0x0C04, 0x0000, 0x0000, 0x0E04, 0x0F04, 0x1004, 0x1104, 0x0000, 0x0000,
    0x0D08, 0x0E08, 0x0F01, 0x1001, 0x1101, 0x1220, 0x1308, 0x0000};
static u8 anim_walk[] = {0x1A, 0x18, 0x0A, 0x19, 0x0A, 0x1A, 0x1A,
                         0x1B, 0x0A, 0x1A, 0x0A, 0x19, 0x00};
static u8 anim_throw_duck[] = {
    0x08, 0x1C, 0x08, 0x1D, 0x08, 0x1E, 0x08, 0x1F, 0x0A, 0x20, 0x04, 0x21,
    0x04, 0x22, 0x04, 0x23, 0x00, 0x00, 0x00, 0x00, 0x08, 0x24, 0x08, 0x25,
    0x02, 0x26, 0x02, 0x27, 0x02, 0x28, 0x20, 0x29, 0x08, 0x2A, 0x00};
static u8 anim_throw_stand[] = {
    0x08, 0x1C, 0x08, 0x1D, 0x08, 0x1E, 0x08, 0x24, 0x08, 0x25, 0x02,
    0x26, 0x02, 0x2B, 0x02, 0x2C, 0x20, 0x2D, 0x08, 0x2E, 0x00, 0x00,
    0x00, 0x00, 0x04, 0x25, 0x04, 0x26, 0x04, 0x27, 0x04, 0x28, 0x00};
static u8 anim_die[] = {
    0x08, 0x20, 0x08, 0x21, 0x08, 0x22, 0x08, 0x23, 0xFF, 0x00};
static u8 hitboxes[][4] = {
    {0, 0, 0, 0},
    {0, 6, 8, 26},
    {0, 11, 8, 21},
    {0, 12, 8, 20},
};
static u8 hitbox_lookup[] = {
    0, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 3, 1, 1, 1, 3, 1,
    1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 3, 1, 1, 1, 3, 1, 0};
static u8 steps[] = {AXE_KNIGHT_STANDING_THROW, AXE_KNIGHT_DUCKING_THROW,
                     AXE_KNIGHT_STANDING_THROW, AXE_KNIGHT_DUCKING_THROW,
                     AXE_KNIGHT_STANDING_THROW, AXE_KNIGHT_DUCKING_THROW,
                     AXE_KNIGHT_STANDING_THROW, AXE_KNIGHT_DUCKING_THROW};
static u32 init_velocity_x[] = {FIX(2), FIX(2), FIX(1)};
static u32 init_velocity_y[] = {FIX(0), FIX(0), FIX(-4)};

#include "../entity_axe_knight.h"
