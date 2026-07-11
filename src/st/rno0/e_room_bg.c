// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno0.h"

u16 animSets[] = {
    ANIMSET_DRA(6), ANIMSET_OVL(2), ANIMSET_OVL(2), ANIMSET_OVL(2),
    ANIMSET_OVL(2), ANIMSET_OVL(2), ANIMSET_OVL(2), ANIMSET_OVL(2),
    ANIMSET_OVL(2), ANIMSET_OVL(2), ANIMSET_OVL(2), ANIMSET_OVL(2),
    ANIMSET_OVL(2), ANIMSET_OVL(2), ANIMSET_OVL(2), ANIMSET_OVL(2),
    ANIMSET_OVL(2), ANIMSET_OVL(2), ANIMSET_OVL(2)};

u8 anim1[] = {64, 2, 255};
u8 anim2[] = {64, 6, 255};
u8 anim3[] = {64, 1, 255};
u8 anim4[] = {64, 2, 255};
u8 anim5[] = {64, 47, 255};
u8 anim6[] = {4, 34, 0};
u8 anim7[] = {4, 35, 0};
u8 anim8[] = {4, 36, 0};
u8 anim9[] = {4, 37, 0};
u8 anim10[] = {4, 38, 0};
u8 anim11[] = {4, 39, 0};
u8 anim12[] = {4, 40, 0};
u8 anim13[] = {4, 42, 0};

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
u8* animations[] = {anim1,  anim2,  anim3,  anim4,  anim5,  anim6, anim7,
                    anim8,  anim9,  anim10, anim11, anim12, anim7, anim8,
                    anim10, anim12, anim13, anim13, anim11};

extern EInit OVL_EXPORT(EInitCommon);

void OVL_EXPORT(EntityBackgroundBlock)(Entity* self) {
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
