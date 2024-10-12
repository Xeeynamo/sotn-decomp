#include "no0.h"

extern s16 sensors_move[];
extern s16 sensors_ground[4][2];
extern s16 dead_particle_pos[][2];
extern u16 unused[];
extern u8 anim_walk[];
extern u8 anim_throw_duck[];
extern u8 anim_throw_stand[];
extern u8 anim_die[];
extern u8 hitboxes[][4];
extern u8 hitbox_lookup[];
extern u8 steps[];
extern u32 init_velocity_x[];
extern u32 init_velocity_y[];

#include "../entity_axe_knight.h"
