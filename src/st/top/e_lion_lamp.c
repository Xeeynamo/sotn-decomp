// SPDX-License-Identifier: AGPL-3.0-or-later
#include "top.h"

extern EInit g_EInitTOPCommon;

static AnimateEntityFrame LionLampAnim[] = {
    {0x03, 0x06}, {0x03, 0x07}, {0x03, 0x08},
    {0x03, 0x09}, {0x03, 0x0A}, POSE_LOOP(0),
};

static u8 clut_ids[] = {
    0x92, 0x95, 0x96, 0x97, 0x98, 0xA5, 0xA8, 0xA9, 0xAA, 0xAB,
    0xAC, 0xAF, 0xB0, 0xB1, 0xB2, 0xB4, 0xB7, 0xB8, 0xB9, 0xBA,
};
extern s32 D_us_801BC514;

void EntityLionLamp(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitTOPCommon);
        self->zPriority = 0x58;
        // fallthrough

    case 1:
        AnimateEntity(LionLampAnim, self);
        if (g_Timer & 1) {
            self->palette = 0;
        } else {
            self->palette = 1;
        }
        break;

    case 255:
#include "../pad2_anim_debug.h"
    }
}

void func_us_801AB45C(Entity* self) {
    u8* lookup;
    s32 writeIndex;
    s32 readIndex;
    s32 offsetY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitTOPCommon);
        self->animSet = 7;
        self->animCurFrame = 3;
        self->zPriority = 0x5C;
        self->palette = PAL_FLAG(PAL_FILL_BLACK);
        if (g_CastleFlags[TOP_LION_LIGHTS] & (1 << (self->params + 2))) {
            self->step = 3;
        }
        break;
    case 1:
        if (g_CastleFlags[TOP_LION_LIGHTS]) {
            offsetY = self->posY.i.hi + g_Tilemap.scrollY.i.hi + 0x20;
            if (offsetY > D_us_801BC514) {
                g_CastleFlags[TOP_LION_LIGHTS] |= 1 << (self->params + 2);
                g_api.PlaySfx(SFX_SMALL_FLAME_IGNITE);
                SetStep(3);
            }
        }
        break;
    case 3:
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 0xB;
        self->blendMode = BLEND_TRANSP | BLEND_ADD;
        self->palette = 0;
        self->zPriority = 0x70;
        self->step++;
        // fallthrough

    case 4:
        if (g_Timer & 2) {
            self->palette = 0;
        } else {
            self->palette = 1;
        }

        if (!self->poseTimer) {
            self->poseTimer = 4;
            lookup = clut_ids;
            lookup += self->params * 5;
            writeIndex = lookup[0];
            // cursed composition!
            readIndex = self->pose;
            readIndex = lookup[readIndex];
            g_ClutIds[writeIndex] = g_ClutIds[readIndex];
            self->pose++;
            if (self->pose > 3) {
                self->pose = 0;
            }
        } else {
            self->poseTimer--;
        }
        break;
    }
}
