// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rtop.h"

#define CANDELABRA_HIT_SFX SFX_CANDLE_HIT_WHOOSH_B
#define BREAKABLE_HIT_SFX SFX_SMALL_FLAME_IGNITE
#define OVL_BREAKABLE_ANIMSET ANIMSET_OVL(4)

extern EInit OVL_EXPORT(EInitBreakable);
extern EInit g_EInitInteractable;
extern EInit g_EInitParticle;

static AnimateEntityFrame anim_candelabra_wall_double[] = {
    {4, 1}, {4, 2}, POSE_LOOP(0)};
static AnimateEntityFrame anim_none[] = {{4, 0}, {4, 0}, POSE_LOOP(0)};
static AnimateEntityFrame anim_candelabra_tall[] = {
    {5, 1}, {5, 2}, {5, 3}, {5, 4}, POSE_LOOP(0)};
static AnimateEntityFrame anim_candelabra_short[] = {
    {5, 5}, {5, 6}, {5, 7}, {5, 8}, POSE_LOOP(0)};
static AnimateEntityFrame anim_candelabra_table[] = {
    {5, 9}, {5, 10}, {5, 11}, {5, 12}, POSE_LOOP(0)};
static AnimateEntityFrame anim_brazier[] = {
    {5, 13}, {5, 14}, {5, 15}, {5, 16}, POSE_LOOP(0)};
static AnimateEntityFrame anim_candelabra_wall[] = {
    {5, 17}, {5, 18}, {5, 19}, POSE_LOOP(0)};
static AnimateEntityFrame anim_urn[] = {{5, 23}, POSE_LOOP(0)};
static AnimateEntityFrame anim_jug[] = {{5, 22}, POSE_LOOP(0)};
static AnimateEntityFrame anim_bust[] = {
    {5, 20}, {-1, -1}, {5, 21}, {5, 21}, POSE_END};
static AnimateEntityFrame* animations[] = {
    anim_candelabra_wall_double, // params 0x0000-0x0FFF
    anim_none,                   // params 0x1000-0x1FFF
    anim_candelabra_tall,        // params 0x2000-0x2FFF
    anim_candelabra_short,       // params 0x3000-0x3FFF
    anim_candelabra_table,       // params 0x4000-0x4FFF
    anim_brazier,                // params 0x5000-0x5FFF
    anim_candelabra_wall,        // params 0x6000-0x6FFF
    anim_urn,                    // params 0x7000-0x7FFF
    anim_jug,                    // params 0x8000-0x8FFF
    anim_bust,                   // params 0x9000-0x9FFF
};

static u8 hitbox_heights[] = {8, 8, 40, 24, 16, 16, 8, 10, 16, 16, 8, 0};
static u8 explosion_types[] = {
    EXPLOSION_SMALL,          EXPLOSION_SMALL,
    EXPLOSION_SMALL_MULTIPLE, EXPLOSION_SMALL_MULTIPLE,
    EXPLOSION_SMALL_MULTIPLE, EXPLOSION_SMALL_MULTIPLE,
    EXPLOSION_SMALL_MULTIPLE, EXPLOSION_SMALL_MULTIPLE,
    EXPLOSION_SMALL_MULTIPLE, EXPLOSION_SMALL_MULTIPLE};
static u16 palettes[] = {
    PAL_NONE,      PAL_NONE,      PAL_BREAKABLE, PAL_BREAKABLE, PAL_BREAKABLE,
    PAL_BREAKABLE, PAL_BREAKABLE, PAL_BREAKABLE, PAL_BREAKABLE, PAL_BREAKABLE};
static u16 anim_sets[] = {
    ANIMSET_DRA(3),        ANIMSET_DRA(3),        OVL_BREAKABLE_ANIMSET,
    OVL_BREAKABLE_ANIMSET, OVL_BREAKABLE_ANIMSET, OVL_BREAKABLE_ANIMSET,
    OVL_BREAKABLE_ANIMSET, OVL_BREAKABLE_ANIMSET, OVL_BREAKABLE_ANIMSET,
    OVL_BREAKABLE_ANIMSET};
static u16 unk_5A[] = {124, 124, 91, 91, 91, 91, 91, 91, 91, 91};
static u8 draw_modes[] = {
    DRAW_TPAGE | DRAW_TPAGE2, DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2, DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2, DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2, DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2, DRAW_TPAGE | DRAW_TPAGE2};
static u16 hitbox_offsets_y[] = {0, 0, -24, -16, 0, 0, 0, 0, 0, 0, 0, 0};
static s16 candelabra_debris_offsets_y[] = {0, 1, 2, 2, 3, 0, 1, 2, 3, 0};

#include "../e_breakable_with_debris.h"
