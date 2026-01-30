// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz1.h"
#include <scratchpad.h>

extern EInit g_EInitEnvironment;
typedef s16 CloudData[5];

// This EntityClouds is quite a bit different from the dai and rbo3 EntityClouds
void EntityClouds(Entity* self) {
    Primitive* prim;
    s32 i;

    s32 primIndex;
    s32 var_s4;
    s32 var_s5;
    CloudData* var_v1;
    s16 angleX;
    s16 angleY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitEnvironment);
        self->animCurFrame = 2;
        self->drawFlags = FLAG_DRAW_OPACITY;
        self->opacity = 0x40;
        self->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE;
        self->zPriority = 0x1C;
        self->flags &= ~FLAG_POS_CAMERA_LOCKED;
        self->posX.i.hi = 0x50;
        self->posY.i.hi = 0x30;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x60);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        i = 0;
        while (prim != NULL) {
            i &= 3;
            prim->tpage = 0x15;
            prim->clut = 3;
            prim->u0 = prim->u2 = 0;
            prim->u1 = prim->u3 = 0x7F;
            prim->v0 = prim->v1 = i << 5;
            prim->v2 = prim->v3 = (i << 5) + 0x20;
            prim->priority = 0x16;
            prim->drawMode = DRAW_HIDE;
            i++;
            prim = prim->next;
        }
        // fallthrough

    case 1:
        self->ext.clockTowerClouds.unk80.val += FIX(1.5);
        self->ext.clockTowerClouds.unk86 += 0x30;
        self->ext.clockTowerClouds.unk84 += 0x40;

        var_s5 = self->ext.clockTowerClouds.unk80.i.hi;
        if (var_s5 > 0x80) {
            var_s5 = self->ext.clockTowerClouds.unk80.i.hi = var_s5 - 0x80;
            self->ext.clockTowerClouds.unk86 -= 0x500;
            self->ext.clockTowerClouds.unk84 -= 0x8C0;
        }
        var_s5 -= 0xC0;
        var_v1 = (CloudData*)SP(0);
        angleX = self->ext.clockTowerClouds.unk86;
        angleY = self->ext.clockTowerClouds.unk84;
        while (var_s5 < 0x1C0) {
            var_s4 = 0x90;
            for (i = 4; i >= 0; i--) {
                var_v1[1][i] = var_s4;
                var_s4 -= FLT_TO_I(rcos(angleX) * 4) + 0x1C;
                var_v1[0][i] = var_s5 + FLT_TO_I((8 - i * 3) * rcos(angleY));
                angleX += 0x80;
                angleY += 0x1C0;
            }
            angleX += 0x280;
            var_v1[1][0] = 0x10;
            var_s5 += 0x80;
            var_v1 += 2;
        }
        var_v1[0][0] = 0x7FFF;

        prim = self->ext.prim;

        var_v1 = (CloudData*)SP(0);

        while (var_v1[0][0] != 0x7FFF) {
            for (i = 0; i < 4; i++) {
                prim->x0 = var_v1[0][i];
                prim->x2 = var_v1[0][i + 1];
                prim->x1 = var_v1[2][i];
                prim->x3 = var_v1[2][i + 1];
                prim->y0 = var_v1[1][i];
                prim->y2 = var_v1[1][i + 1];
                prim->y1 = var_v1[3][i];
                prim->y3 = var_v1[3][i + 1];
                prim->drawMode = DRAW_DEFAULT;
                prim = prim->next;
            }
            var_v1 += 2;
        }

        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        break;

    case 0xFF:
#include "../pad2_anim_debug.h"
        break;
    }
}
