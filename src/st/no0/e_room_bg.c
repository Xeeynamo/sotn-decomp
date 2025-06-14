// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

extern u16 animset[];
extern u16 zPriority[];
extern u16 unk5A[];
extern u16 palette[];
extern u16 drawFlags[];
extern u16 drawMode[];
extern s32 flags[];
extern u32 facingLeft[];
extern u8* animations[];

void OVL_EXPORT(EntityBackgroundBlock)(Entity* self) {
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
