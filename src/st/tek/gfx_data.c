// SPDX-License-Identifier: AGPL-3.0-or-later
#include "tek.h"

u8 gfx_richter_subweapons[] = {
#include <gen/gfx_richter_subweapons.h>
};

u8 gfx_dodo[] = {
#include <gen/gfx_dodo.h>
};

u8 gfx_bone_scimitar[] = {
#include <gen/gfx_bone_scimitar.h>
};

u8 gfx_toad_frog[] = {
#include <gen/gfx_toad_frog.h>
};

u8 gfx_bone_archer[] = {
#include <gen/gfx_bone_archer.h>
};

u8 gfx_grave_keeper[] = {
#include <gen/gfx_grave_keeper.h>
};

u8 gfx_grave_keeper_tombstone[] = {
#include <gen/gfx_grave_keeper_tombstone.h>
};

u8 gfx_crow[] = {
#include <gen/gfx_crow.h>
};

u8 gfx_jacko_bones[] = {
#include <gen/gfx_jacko_bones.h>
};

u8 gfx_bone_halberd[] = {
#include <gen/gfx_bone_halberd.h>
};

u8 gfx_yorick[] = {
#include <gen/gfx_yorick.h>
};

u8 gfx_blade_master_1[] = {
#include <gen/gfx_blade_master_1.h>
};

u8 gfx_blade_master_2[] = {
#include <gen/gfx_blade_master_2.h>
};

u8 gfx_blade_master_3[] = {
#include <gen/gfx_blade_master_3.h>
};

u8 gfx_blade_soldier[] = {
#include <gen/gfx_blade_soldier.h>
};

u8 gfx_nova_skeleton[] = {
#include <gen/gfx_nova_skeleton.h>
};

u8 gfx_nova_laser[] = {
#include <gen/gfx_nova_laser.h>
};

u8 gfx_bone_musket[] = {
#include <gen/gfx_bone_musket.h>
};

u8 gfx_winged_guard[] = {
#include <gen/gfx_winged_guard.h>
};

u8 gfx_spectral_sword_1[] = {
#include <gen/gfx_spectral_sword_1.h>
};

u8 gfx_spectral_sword_2[] = {
#include <gen/gfx_spectral_sword_2.h>
};

u8 gfx_valhalla_knight_1[] = {
#include <gen/gfx_valhalla_knight_1.h>
};

u8 gfx_valhalla_knight_2[] = {
#include <gen/gfx_valhalla_knight_2.h>
};

u8 gfx_valhalla_knight_3[] = {
#include <gen/gfx_valhalla_knight_3.h>
};

u8 gfx_dragon_rider_1[] = {
#include <gen/gfx_dragon_rider_1.h>
};

u8 gfx_dragon_rider_2[] = {
#include <gen/gfx_dragon_rider_2.h>
};

u8 gfx_venus_weed_1[] = {
#include <gen/gfx_venus_weed_1.h>
};

u8 gfx_venus_weed_2[] = {
#include <gen/gfx_venus_weed_2.h>
};

u8 gfx_bomb_knight_1[] = {
#include <gen/gfx_bomb_knight_1.h>
};

u8 gfx_bomb_knight_2[] = {
#include <gen/gfx_bomb_knight_2.h>
};

u8 gfx_bomb_knight_3[] = {
#include <gen/gfx_bomb_knight_3.h>
};

u8 gfx_bomb_knight_4[] = {
#include <gen/gfx_bomb_knight_4.h>
};

u8 gfx_thornweed_corpseweed[] = {
#include <gen/gfx_thornweed_corpseweed.h>
};

u16 pal_19790[] = {
#include <gen/pal_19790.h>
};

u16 pal_dodo[] = {
#include <gen/pal_dodo.h>
};

u16 pal_bone_scimitar[] = {
#include <gen/pal_bone_scimitar.h>
};

u16 pal_197F0[] = {
#include <gen/pal_197F0.h>
};

u16 pal_toad_frog[] = {
#include <gen/pal_toad_frog.h>
};

u16 pal_bone_archer[] = {
#include <gen/pal_bone_archer.h>
};

u16 pal_grave_keeper[] = {
#include <gen/pal_grave_keeper.h>
};

u16 pal_crow[] = {
#include <gen/pal_crow.h>
};

u16 pal_jacko_bones[] = {
#include <gen/pal_jacko_bones.h>
};

u16 pal_bone_halberd[] = {
#include <gen/pal_bone_halberd.h>
};

u16 pal_yorick[] = {
#include <gen/pal_yorick.h>
};

u16 pal_blade_master[] = {
#include <gen/pal_blade_master.h>
};

u16 pal_blade_soldier[] = {
#include <gen/pal_blade_soldier.h>
};

u16 pal_nova_skeleton[] = {
#include <gen/pal_nova_skeleton.h>
};

u16 pal_bone_musket[] = {
#include <gen/pal_bone_musket.h>
};

u16 pal_winged_guard[] = {
#include <gen/pal_winged_guard.h>
};

u16 pal_spectral_sword[] = {
#include <gen/pal_spectral_sword.h>
};

u16 pal_valhalla_knight[] = {
#include <gen/pal_valhalla_knight.h>
};

#ifdef FIX_UB
// Avoid OOB/overflow due to palette_def bulk copies 0x50 colors
u16 pal_dragons[] = {
#include <gen/pal_dragons.h>
#include <gen/pal_venus_weed.h>
};
#else
u16 pal_dragons[] = {
#include <gen/pal_dragons.h>
};
#endif

u16 pal_venus_weed[] = {
#include <gen/pal_venus_weed.h>
};

u16 pal_1A350[] = {
#include <gen/pal_1A350.h>
};

u16 pal_bomb_knight[] = {
#include <gen/pal_bomb_knight.h>
};

u16 pal_thornweed_corpseweed[] = {
#include <gen/pal_thornweed_corpseweed.h>
};
