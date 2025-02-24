// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../../st/lib/lib.h"

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09255068);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_us_801BB8DC);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09256018);

extern Collider D_us_80181AEC;
extern u8 D_us_80181BCC;
extern u8 D_us_80181BD8;
extern u8 D_us_80181BE8;

// EntityLesserDemonSpit code is shared with PSX and is ready for merge
// Lesser Demon aerial spit projectile
void EntityLesserDemonSpit(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    u16 posX, posY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitLesserDemonSpit);
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->drawFlags |= FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
        self->rotX = 0x180;
        self->rotY = 0x180;
        break;
    case 1:
        if (self->facingLeft) {
            self->velocityX = FIX(4.0);
        } else {
            self->velocityX = FIX(-4.0);
        }
        self->velocityY = FIX(4.0);
        self->step++;
        break;
    case 2:
        MoveEntity();
        AnimateEntity(&D_us_80181BCC, self);
        if (CheckColliderOffsets(&D_us_80181AEC, 0)) {
            self->animFrameIdx = 0;
            self->animFrameDuration = 0;
            self->rotX = 0x140;
            self->rotY = 0x200;
            self->hitboxWidth = 8;
            self->hitboxHeight = 8;
            self->step++;
        }
        break;
    case 3:
        if (!AnimateEntity(&D_us_80181BD8, self)) {
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
            if (primIndex != -1) {
                self->flags |= FLAG_HAS_PRIMS;
                self->primIndex = primIndex;
                prim = &g_PrimBuf[primIndex];
                self->ext.lesserDemon.unk7C = prim;
                prim->tpage = 0x13;
                prim->clut = 0x24D;
                prim->u0 = 0x68;
                prim->v0 = 0xC8;
                prim->u1 = 0x7F;
                prim->v1 = 0xC8;
                prim->u2 = 0x68;
                prim->v2 = 0xFF;
                prim->u3 = 0x7F;
                prim->v3 = 0xFF;
                prim->x0 = self->posX.i.hi - 0x10;
                prim->x1 = prim->x0 + 0x2C;
                prim->x2 = prim->x0;
                prim->x3 = prim->x1;
                prim->y0 = self->posY.i.hi - 0x30;
                prim->y1 = prim->y0;
                prim->y2 = self->posY.i.hi + 0xC;
                prim->y3 = prim->y2;
                prim->priority = self->zPriority + 2;
                prim->drawMode =
                    DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            } else {
                DestroyEntity(self);
                break;
            }
            self->animCurFrame = 0x25;
            self->animFrameDuration = 0;
            self->animFrameIdx = 0;
            self->ext.lesserDemon.unk80 = 0;
            PlaySfxPositional(SFX_FM_EXPLODE_B);
            self->step++;
        }
        break;
    case 4:
        prim = self->ext.lesserDemon.unk7C;
        if (self->ext.lesserDemon.unk80++ > 0x10) {
            self->step++;
            self->ext.lesserDemon.unk80 = 0x1D;
            self->hitboxHeight = 0x40;
            self->hitboxOffY -= 0x20;
            break;
        }
        prim->y0 -= 0x10 - self->ext.lesserDemon.unk80;
        prim->y1 = prim->y0;
        self->hitboxHeight = ((prim->y2 - prim->y0) / 2) - 0x10;
        self->hitboxOffY = -self->hitboxHeight;
        break;
    case 5:
        prim = self->ext.lesserDemon.unk7C;

        if (!(--self->ext.lesserDemon.unk80)) {
            self->animFrameIdx = 0;
            self->animFrameDuration = 0;
            self->hitboxState = 0;
            self->step++;
            prim->drawMode = DRAW_HIDE;
            break;
        }
        prim->y0 += 4;
        prim->y1 = prim->y0;
        prim->v2 -= 2;
        prim->v3 = prim->v2;
        self->hitboxHeight = 8;
        self->hitboxOffY = -4;
        self->hitboxHeight = ((prim->y2 - prim->y0) / 2) - 0x10;
        self->hitboxOffY = -self->hitboxHeight;
        break;
    case 6:
        self->rotY -= 0x20;
        if (!AnimateEntity(&D_us_80181BE8, self)) {
            self->drawFlags |= FLAG_DRAW_UNK8;
            self->unk6C = 0x80;
            self->step++;
            break;
        }
        break;
    case 7:
        self->rotY -= 0x10;
        self->unk6C -= 0x10;
        if (!self->unk6C) {
            DestroyEntity(self);
        }
        break;
    }
}

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09256AC0);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09256E08);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09257100);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_092576C8);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09257BF8);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09258100);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09258A38);

// Lesser Demon
INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09258B50);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_0925A798);
