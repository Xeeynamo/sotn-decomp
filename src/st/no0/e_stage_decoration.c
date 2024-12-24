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
    ANIMSET_OVL(1), ANIMSET_OVL(1), ANIMSET_OVL(1), ANIMSET_DRA(0)};

static u8 angel_statue_left[] = {0x40, 0x01, 0xFF, 0x00};
static u8 anim_2[] = {0x40, 0x06, 0xFF, 0x00};
static u8 angel_statue_left_2[] = {0x40, 0x01, 0xFF, 0x00};
static u8 angel_statue_right[] = {0x40, 0x02, 0xFF, 0x00};
static u8 lamp_brasier[] = {0x40, 0x2F, 0xFF, 0x00};
static u8 clock_face_1[] = {0x04, 0x22, 0x00, 0x00};
static u8 clock_face_2[] = {0x04, 0x23, 0x00, 0x00};
static u8 clock_face_3[] = {0x04, 0x24, 0x00, 0x00};
static u8 window_highlight_1[] = {0x04, 0x25, 0x00, 0x00};
static u8 window_highlight_2[] = {0x04, 0x26, 0x00, 0x00};
static u8 window_highlight_3[] = {0x04, 0x27, 0x00, 0x00};
static u8 window_highlight_4[] = {0x04, 0x28, 0x00, 0x00};
static u8 red_moveable_floor[] = {0x04, 0x2A, 0x00, 0x00};

static u16 zPriority[] = {
    0x01FA, 0x0040, 0x006A, 0x006A, 0x003F, 0x0080, 0x0080,
    0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080,
    0x0080, 0x0080, 0x009E, 0x009E, 0x0080, 0x0000};

static u16 unk5A[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static u16 palette[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static u16 drawFlags[] = {
    FLAG_DRAW_DEFAULT, FLAG_DRAW_DEFAULT, FLAG_DRAW_DEFAULT, FLAG_DRAW_DEFAULT,
    FLAG_DRAW_DEFAULT, FLAG_DRAW_DEFAULT, FLAG_DRAW_DEFAULT, FLAG_DRAW_DEFAULT,
    FLAG_DRAW_DEFAULT, FLAG_DRAW_DEFAULT, FLAG_DRAW_DEFAULT, FLAG_DRAW_DEFAULT,
    FLAG_DRAW_DEFAULT, FLAG_DRAW_DEFAULT, FLAG_DRAW_DEFAULT, FLAG_DRAW_DEFAULT,
    FLAG_DRAW_DEFAULT, FLAG_DRAW_DEFAULT, FLAG_DRAW_DEFAULT, FLAG_DRAW_DEFAULT};
static u16 drawMode[] = {
    DRAW_TPAGE,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_TPAGE2 | DRAW_TPAGE,
    DRAW_TPAGE,
    DRAW_TPAGE,
    DRAW_TPAGE,
    DRAW_TPAGE,
    DRAW_TPAGE,
    DRAW_TPAGE,
    DRAW_TPAGE,
    DRAW_TPAGE,
    DRAW_TPAGE,
    DRAW_TPAGE,
    DRAW_TPAGE,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_TPAGE,
    DRAW_DEFAULT};
static s32 flags[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static u32 facingLeft[] = {
    false, false, false, false, false, false, false, false, false, false,
    false, false, true,  true,  true,  true,  false, true,  true};
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

void EntityStageDecoration(Entity* self) {
    u16 params = self->params;

    if (self->step == 0) {
        InitializeEntity(g_EInitCommon);

        self->animSet = animset[params];
        self->zPriority = zPriority[params];
        self->unk5A = unk5A[params];
        self->palette = palette[params];
        self->drawFlags = drawFlags[params];
        self->drawMode = drawMode[params];

        if (flags[params] != 0) {
            self->flags = flags[params];
        }

        self->facingLeft = facingLeft[params];
    }

    AnimateEntity(animations[params], self);
}
