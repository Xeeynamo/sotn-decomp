// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno0.h"

u16 animSets[] = {
    ANIMSET_DRA(6), ANIMSET_OVL(2), ANIMSET_OVL(2), ANIMSET_OVL(2),
    ANIMSET_OVL(2), ANIMSET_OVL(2), ANIMSET_OVL(2), ANIMSET_OVL(2),
    ANIMSET_OVL(2), ANIMSET_OVL(2), ANIMSET_OVL(2), ANIMSET_OVL(2),
    ANIMSET_OVL(2), ANIMSET_OVL(2), ANIMSET_OVL(2), ANIMSET_OVL(2),
    ANIMSET_OVL(2), ANIMSET_OVL(2), ANIMSET_OVL(2)};

AnimateEntityFrame anim1[] = {{64, 2}, POSE_END};
AnimateEntityFrame anim2[] = {{64, 6}, POSE_END};
AnimateEntityFrame anim3[] = {{64, 1}, POSE_END};
AnimateEntityFrame anim4[] = {{64, 2}, POSE_END};
AnimateEntityFrame anim5[] = {{64, 47}, POSE_END};
AnimateEntityFrame anim6[] = {{4, 34}, POSE_LOOP(0)};
AnimateEntityFrame anim7[] = {{4, 35}, POSE_LOOP(0)};
AnimateEntityFrame anim8[] = {{4, 36}, POSE_LOOP(0)};
AnimateEntityFrame anim9[] = {{4, 37}, POSE_LOOP(0)};
AnimateEntityFrame anim10[] = {{4, 38}, POSE_LOOP(0)};
AnimateEntityFrame anim11[] = {{4, 39}, POSE_LOOP(0)};
AnimateEntityFrame anim12[] = {{4, 40}, POSE_LOOP(0)};
AnimateEntityFrame anim13[] = {{4, 42}, POSE_LOOP(0)};

u16 zPrioritys[] = {0x1fa, 0x40, 0x80, 0x80, 0x3f, 0x80, 0x80, 0x80, 0x80, 0x80,
                    0x80,  0x80, 0x80, 0x80, 0x80, 0x80, 0x9e, 0x9e, 0x80};
u16 unk5As[19] = {0};
u16 palettes[19] = {0};
u16 drawFlags[19] = {0};
u16 blendModes[] = {
    BLEND_TRANSP,
    BLEND_NO,
    BLEND_NO,
    BLEND_NO,
    BLEND_ADD | BLEND_TRANSP,
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
    BLEND_NO};
u32 flagses[19] = {0};

u32 unused[] = {0, 0, 0,   0,   0,   0,   0, 0,   0,  0,
                0, 0, 0x1, 0x1, 0x1, 0x1, 0, 0x1, 0x1};
AnimateEntityFrame* animations[] = {
    anim1,  anim2,  anim3, anim4, anim5,  anim6,  anim7,  anim8,  anim9, anim10,
    anim11, anim12, anim7, anim8, anim10, anim12, anim13, anim13, anim11};

extern EInit OVL_EXPORT(EInitCommon);

void EntityBackgroundBlock(Entity* self) {
    u16 params = self->params;
    u32 flags;
    if (!self->step) {
        InitializeEntity(OVL_EXPORT(EInitCommon));
        self->animSet = (u16)animSets[params];
        self->zPriority = zPrioritys[params];
        self->unk5A = unk5As[params];
        self->palette = palettes[params];
        self->drawFlags = drawFlags[params];
        self->blendMode = blendModes[params];
        flags = flagses[params];
        if (flags) {
            self->flags = flags;
        }
    }
    AnimateEntity(animations[params], self);
}
