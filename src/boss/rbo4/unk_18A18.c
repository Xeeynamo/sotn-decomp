// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo4.h"

extern EInit g_EInitBossDoor;

// unused, flicker between the two variants of each half
static AnimateEntityFrame anim_top_fast[] = {
    POSE(1, 0x62, 0), POSE(1, 0x63, 0), POSE_LOOP(0)};
static AnimateEntityFrame anim_bottom_fast[] = {
    POSE(1, 0x64, 0), POSE(1, 0x65, 0), POSE_LOOP(0)};
static AnimateEntityFrame anim_top_slow[] = {
    POSE(2, 0x62, 0), POSE(2, 0x63, 0), POSE_LOOP(0)};
static AnimateEntityFrame anim_bottom_slow[] = {
    POSE(2, 0x64, 0), POSE(2, 0x65, 0), POSE_LOOP(0)};

// same setup as BO4's EntityUnkId17
void func_us_80198A18(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitBossDoor);
        self->drawFlags |= ENTITY_ROTATE;
        if ((self->params & 0xF) % 2) {
            self->rotate = ROT(-90);
        } else {
            self->rotate = 0;
        }
        self->zPriority = (0x40 - self->params) & 0xF;
        if (self->params & 0x100) {
            self->animCurFrame = 0x64;
        } else {
            self->animCurFrame = 0x62;
        }
        self->ext.et_801BDA0C.unk84 = 0;
        self->ext.et_801BDA0C.unk80 = 0;
        break;
    case 1:
        self->palette = PAL_FLAG(0x4F);
        break;
    }
}
