// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../no2/no2.h"

void func_us_801B3D8C(Entity* self) {
    Primitive* prim;
    s16 offsetX;
    s16 offsetY;
    s32 i;

    if (self->params) {
        offsetX = 0;
        offsetY = -0x40;
    } else {
        offsetX = 0;
        offsetY = 0x58;
    }
    if (!self->step) {
        self->step++;
        if (self->params) {
            self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x20);
        } else {
            self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
        }
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; prim != NULL; i++, prim = prim->next) {
            prim->x0 = prim->x2 = (i & 7) * 0x40 + offsetX;
            prim->x1 = prim->x3 = prim->x0 + 0x48;
            prim->y1 = prim->y0 = (i >> 3) * 0x64 + offsetY;
            prim->y3 = prim->y2 = prim->y0 + 0x6C;
            prim->u0 = 0x80;
            prim->v0 = 0;
            prim->u1 = 0xC8;
            prim->v1 = 0;
            prim->u2 = 0x80;
            prim->v2 = 0x68;
            prim->u3 = 0xC8;
            prim->v3 = 0x68;
            prim->tpage = 0xF;
            prim->clut = 0x36;
            prim->priority = 0x10;
            prim->drawMode = DRAW_DEFAULT;
        }
    }
}

INCLUDE_ASM("st/no2_psp/nonmatchings/no2_psp/1FF58", func_pspeu_09257810);

void func_us_801B4148(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(2);
        self->animCurFrame = 1;
        self->zPriority = 0xA0;
    }
}

void func_us_801B41A4(Entity* self) {
    if (g_CurrentEntity->step == 0) {
        g_CurrentEntity->step++;
    }
    g_GpuBuffers[0].draw.r0 = 0x20;
    g_GpuBuffers[0].draw.g0 = 0x18;
    g_GpuBuffers[0].draw.b0 = 0x28;
    g_GpuBuffers[1].draw.r0 = 0x20;
    g_GpuBuffers[1].draw.g0 = 0x18;
    g_GpuBuffers[1].draw.b0 = 0x28;
}

INCLUDE_ASM("st/no2_psp/nonmatchings/no2_psp/1FF58", func_pspeu_09257C00);
