// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

#define CANDELABRA_HIT_SFX SFX_CANDLE_HIT
#define BREAKABLE_HIT_SFX SFX_QUICK_STUTTER_EXPLODE_B
#define OVL_BREAKABLE_ANIMSET ANIMSET_OVL(14)

static AnimateEntityFrame anim_background_flame[] = {
    {3, 3}, {3, 4}, {3, 5}, {3, 6}, POSE_LOOP(0)};
static AnimateEntityFrame anim_wall_sconce[] = {
    {3, 7}, {3, 8}, {3, 9}, {3, 10}, {3, 11}, POSE_LOOP(0)};
static AnimateEntityFrame anim_candelabra_tall[] = {
    {5, 1}, {5, 2}, {5, 3}, {5, 4}, POSE_LOOP(0)};
static AnimateEntityFrame anim_candelabra_short[] = {
    {5, 5}, {5, 6}, {5, 7}, {5, 8}, POSE_LOOP(0)};
static AnimateEntityFrame anim_candelabra_table[] = {
    {5, 9}, {5, 10}, {5, 11}, {5, 12}, POSE_LOOP(0)};
static AnimateEntityFrame anim_brazier[] = {
    {5, 13}, {5, 14}, {5, 15}, {5, 16}, POSE_LOOP(0)};
static AnimateEntityFrame anim_candelabra_wall_triple[] = {
    {5, 17}, {5, 18}, {5, 19}, POSE_LOOP(0)};
static AnimateEntityFrame anim_urn[] = {{5, 23}, POSE_LOOP(0)};
static AnimateEntityFrame anim_jug[] = {{5, 22}, POSE_LOOP(0)};
static AnimateEntityFrame anim_bust[] = {
    {5, 20}, {-1, -1}, {5, 21}, {5, 21}, POSE_END};
static AnimateEntityFrame* animations[] = {
    anim_background_flame,
    anim_wall_sconce,
    anim_candelabra_tall,
    anim_candelabra_short,
    anim_candelabra_table,
    anim_brazier,
    anim_candelabra_wall_triple,
    anim_urn,
    anim_jug,
    anim_bust,
};

static u8 hitbox_heights[] = {8, 8, 40, 24, 16, 16, 8, 8, 8, 8, 8, 0};
static u8 explosion_types[] = {
    EXPLOSION_SMALL,          EXPLOSION_SMALL,
    EXPLOSION_SMALL_MULTIPLE, EXPLOSION_SMALL_MULTIPLE,
    EXPLOSION_SMALL_MULTIPLE, EXPLOSION_SMALL_MULTIPLE,
    EXPLOSION_SMALL_MULTIPLE, EXPLOSION_SMALL_MULTIPLE,
    EXPLOSION_SMALL_MULTIPLE, EXPLOSION_SMALL_MULTIPLE,
};
static u16 palettes[] = {
    PAL_NONE,      PAL_NONE,      PAL_BREAKABLE, PAL_BREAKABLE, PAL_BREAKABLE,
    PAL_BREAKABLE, PAL_BREAKABLE, PAL_BREAKABLE, PAL_BREAKABLE, PAL_BREAKABLE,
};
static u16 anim_sets[] = {
    ANIMSET_OVL(1),        ANIMSET_OVL(1),        OVL_BREAKABLE_ANIMSET,
    OVL_BREAKABLE_ANIMSET, OVL_BREAKABLE_ANIMSET, OVL_BREAKABLE_ANIMSET,
    OVL_BREAKABLE_ANIMSET, OVL_BREAKABLE_ANIMSET, OVL_BREAKABLE_ANIMSET,
    OVL_BREAKABLE_ANIMSET,
};
static u16 unk_5A[] = {0, 0, 91, 91, 91, 91, 91, 91, 91, 91};
static u8 draw_modes[] = {
    DRAW_TPAGE | DRAW_TPAGE2, DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2, DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2, DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2, DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2, DRAW_TPAGE | DRAW_TPAGE2,
};
static u16 hitbox_offsets_y[] = {0, 0, -24, -16, 0, 0, 0, 0, 0, 0, 0, 0};

// The first 5 elements are used with the tall candelabra and the last 5 are
// used with the short candelabra
static s16 candelabra_debris_offsets_y[] = {0, 1, 2, 2, 3, 0, 1, 2, 3, 0};

#include "../e_breakable_with_debris.h"
