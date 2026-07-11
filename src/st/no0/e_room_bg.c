// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

// There are 19 decorations which can overlay the background
// based on self->params:
// 0: angel statue left (east exit)
// 1: bird wreath (south area)
// 2: angel statue left (east exit)
// 3: angel statue right (east exit)
// 4: wall lamp brasier (main clock room)
// 5: clock face 1 (long grandfather clock corridors)
// 6: clock face 2 (long grandfather clock corridors)
// 7: clock face 3 (long grandfather clock corridors)
// 8: tall rectangular window highlight 1
// 9: tall rectangular window highlight 2
// 10: tall rectangular window highlight 3
// 11: tall rectangular window highlight 4
// 12: clock face 2 (facing left)
// 13: clock face 3 (facing left)
// 14: tall rectangular window highlight 2 (facing left)
// 15: tall rectangular window highlight 4 (facing left)
// 16: red moveable floor (facing right)
// 17: red moveable floor (facing left)
// 18: tall rectangular window highlight 3 (facing left)

static u16 animset[] = {
    ANIMSET_DRA(6), ANIMSET_OVL(1), ANIMSET_OVL(1), ANIMSET_OVL(1),
    ANIMSET_OVL(1), ANIMSET_OVL(1), ANIMSET_OVL(1), ANIMSET_OVL(1),
    ANIMSET_OVL(1), ANIMSET_OVL(1), ANIMSET_OVL(1), ANIMSET_OVL(1),
    ANIMSET_OVL(1), ANIMSET_OVL(1), ANIMSET_OVL(1), ANIMSET_OVL(1),
    ANIMSET_OVL(1), ANIMSET_OVL(1), ANIMSET_OVL(1)};

static u8 angel_statue_left[] = {64, 1, -1, 0};
static u8 anim_2[] = {64, 6, -1, 0};
static u8 angel_statue_left_2[] = {64, 1, -1, 0};
static u8 angel_statue_right[] = {64, 2, -1, 0};
static u8 lamp_brasier[] = {64, 47, -1, 0};
static u8 clock_face_1[] = {4, 34, 0, 0};
static u8 clock_face_2[] = {4, 35, 0, 0};
static u8 clock_face_3[] = {4, 36, 0, 0};
static u8 window_highlight_1[] = {4, 37, 0, 0};
static u8 window_highlight_2[] = {4, 38, 0, 0};
static u8 window_highlight_3[] = {4, 39, 0, 0};
static u8 window_highlight_4[] = {4, 40, 0, 0};
static u8 red_moveable_floor[] = {4, 42, 0, 0};

static u16 zPriority[] = {
    0x1FA, 0x040, 0x06A, 0x06A, 0x03F, 0x080, 0x080, 0x080, 0x080, 0x080,
    0x080, 0x080, 0x080, 0x080, 0x080, 0x080, 0x09E, 0x09E, 0x080};

static u16 unk5A[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static u16 palette[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

static u16 drawFlags[] = {
    ENTITY_DEFAULT, ENTITY_DEFAULT, ENTITY_DEFAULT, ENTITY_DEFAULT,
    ENTITY_DEFAULT, ENTITY_DEFAULT, ENTITY_DEFAULT, ENTITY_DEFAULT,
    ENTITY_DEFAULT, ENTITY_DEFAULT, ENTITY_DEFAULT, ENTITY_DEFAULT,
    ENTITY_DEFAULT, ENTITY_DEFAULT, ENTITY_DEFAULT, ENTITY_DEFAULT,
    ENTITY_DEFAULT, ENTITY_DEFAULT, ENTITY_DEFAULT,
};

static u16 blendMode[] = {
    BLEND_TRANSP,
    BLEND_NO,
    BLEND_NO,
    BLEND_NO,
    BLEND_TRANSP | BLEND_ADD,
    BLEND_TRANSP,
    BLEND_TRANSP,
    BLEND_TRANSP,
    BLEND_TRANSP,
    BLEND_TRANSP,
    BLEND_TRANSP,
    BLEND_TRANSP,
    BLEND_TRANSP,
    BLEND_TRANSP,
    BLEND_TRANSP,
    BLEND_TRANSP,
    BLEND_NO,
    BLEND_NO,
    BLEND_TRANSP,
};
static s32 flags[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

static u32 facingLeft[] = {
    false, false, false, false, false, false, false, false, false, false,
    false, false, true,  true,  true,  true,  false, true,  true,
};

static u8* animations[] = {
    angel_statue_left,   anim_2,
    angel_statue_left_2, angel_statue_right,
    lamp_brasier,        clock_face_1,
    clock_face_2,        clock_face_3,
    window_highlight_1,  window_highlight_2,
    window_highlight_3,  window_highlight_4,
    clock_face_2,        clock_face_3,
    window_highlight_2,  window_highlight_4,
    red_moveable_floor,  red_moveable_floor,
    window_highlight_3};

void OVL_EXPORT(EntityBackgroundBlock)(Entity* self) {
    u16 params;
    s32 flag;

    params = self->params;
    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = (u16)animset[params];
        self->zPriority = zPriority[params];
        self->unk5A = unk5A[params];
        self->palette = palette[params];
        self->drawFlags = drawFlags[params];
        self->blendMode = blendMode[params];
        flag = flags[params];
        if (flag != 0) {
            self->flags = flag;
        }
        self->facingLeft = facingLeft[params];
    }
    AnimateEntity(animations[params], self);
}
