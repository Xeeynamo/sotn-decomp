// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../../st/lib/lib.h"

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09255068);

// func_us_801BB8DC code is shared with PSX and is ready for merge
// Seems to be related to the iframes of the ectoplasm and the skeleton spawns
// Mudman spawn animation causes iframes for it
void func_us_801BB8DC(s16* unkArg) {
    switch (g_CurrentEntity->step_s) {
    case 0:
        g_CurrentEntity->animCurFrame = 0;
        g_CurrentEntity->hitboxState = 0;
        g_CurrentEntity->zPriority -= 0x10;
        g_CurrentEntity->ext.lesserDemon.unkB2 = g_CurrentEntity->palette;
        g_CurrentEntity->drawFlags |= FLAG_DRAW_UNK8;
        g_CurrentEntity->unk6C = 2;
        g_CurrentEntity->step_s++;
        g_CurrentEntity->flags |= FLAG_UNK_2000;
        g_CurrentEntity->flags &= ~(FLAG_UNK_800 | FLAG_UNK_400);
        if (!unkArg) {
            g_CurrentEntity->step_s = 2;
        }
        break;
    case 1:
        if (UnkCollisionFunc3(unkArg) & 1) {
            g_CurrentEntity->animCurFrame = 1;
            g_CurrentEntity->step_s++;
        }
        break;
    case 2:
        g_CurrentEntity->unk6C += 4;
        if (g_CurrentEntity->unk6C > 0xA0) {
            g_CurrentEntity->drawFlags = FLAG_DRAW_DEFAULT;
            g_CurrentEntity->drawMode = DRAW_DEFAULT;
            g_CurrentEntity->ext.lesserDemon.unkB0 = 0x20;
            g_CurrentEntity->step_s++;
        }
        break;
    case 3:
        if (g_CurrentEntity->ext.lesserDemon.unkB0 % 2) {
            g_CurrentEntity->palette = g_CurrentEntity->ext.lesserDemon.unkB2;
        } else {
            g_CurrentEntity->palette = PAL_OVL(0x19F);
        }

        if (!(--g_CurrentEntity->ext.lesserDemon.unkB0)) {
            g_CurrentEntity->palette = g_CurrentEntity->ext.lesserDemon.unkB2;
            g_CurrentEntity->hitboxState = 3;
            SetStep(1);
        }
        break;
    }
}

// func_us_801BBAB4 code is shared with PSX and is ready for merge
// Seems to be the windup just before the spit attack
u8 func_us_801BBAB4(void) {
    Primitive* prim;
    Pos tempPrim;
    s32 primIndex;
    s32 unkVar;
    u8 randomVal;
    u8 ret;
#ifdef VERSION_US
    s32 dummy[2];
#endif

    ret = false;
    switch (g_CurrentEntity->ext.lesserDemon.unk84) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_TILE, 0x18);
        if (primIndex != -1) {
            g_CurrentEntity->primIndex = primIndex;
            g_CurrentEntity->flags |= FLAG_HAS_PRIMS;
            prim = &g_PrimBuf[primIndex];
            g_CurrentEntity->ext.lesserDemon.unk7C = prim;
            for (; prim != NULL; prim = prim->next) {
                PGREY_ALT(prim, 0, 0)
                prim->u0 = 2;
                prim->v0 = 2;
                prim->priority = g_CurrentEntity->zPriority + 2;
                prim->drawMode =
                    DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
                randomVal = Random() & 0x7F;
                if (g_CurrentEntity->facingLeft) {
                    // These look like they could be -= and += respectively,
                    // but that oddly does not match
                    randomVal = randomVal - 0x40;
                } else {
                    randomVal = randomVal + 0x40;
                }
                prim->x0 = (g_CurrentEntity->posX.i.hi +
                            ((rcos((randomVal) * 0x10) * 0x60) >> 0xC) +
                            (Random() & 0x3F)) -
                           0x1F;
                prim->y0 = (g_CurrentEntity->posY.i.hi +
                            ((rsin((randomVal) * 0x10) * 0x60) >> 0xC) +
                            (Random() & 0x3F)) -
                           0x1F;
                prim->x1 = 0;
                prim->y1 = 0;
                if (g_CurrentEntity->facingLeft) {
                    unkVar =
                        prim->x0 - (g_CurrentEntity->posX.i.hi + 0xA) << 0x10;
                } else {
                    unkVar =
                        prim->x0 - (g_CurrentEntity->posX.i.hi - 0xA) << 0x10;
                }
                LOW(prim->x2) = -unkVar / 48;
                unkVar =
                    (prim->y0 - (g_CurrentEntity->posY.i.hi - 0xB) << 0x10);
                LOW(prim->x3) = -unkVar / 48;
            }
        } else {
            ret = true;
            g_CurrentEntity->ext.lesserDemon.unk84 = 2;
        }
        g_CurrentEntity->ext.lesserDemon.unk80 = 0;
        g_CurrentEntity->ext.lesserDemon.unk84++;
        break;
    case 1:
        prim = g_CurrentEntity->ext.lesserDemon.unk7C;
        for (; prim != NULL; prim = prim->next) {
            tempPrim.x.i.hi = prim->x0;
            tempPrim.x.i.lo = prim->x1;
            tempPrim.y.i.hi = prim->y0;
            tempPrim.y.i.lo = prim->y1;
            tempPrim.x.val += LOWU(prim->x2);
            tempPrim.y.val += LOWU(prim->x3);
            LOH(prim->x0) = tempPrim.x.i.hi;
            LOH(prim->x1) = tempPrim.x.i.lo;
            LOH(prim->y0) = tempPrim.y.i.hi;
            LOH(prim->y1) = tempPrim.y.i.lo;
            prim->r0 += 3;
        }
        prim = g_CurrentEntity->ext.lesserDemon.unk7C;
        PrimToggleVisibility(prim, 0x18);
        if (g_CurrentEntity->ext.lesserDemon.unk80++ > 0x30) {
            primIndex = g_CurrentEntity->primIndex;
            g_api.FreePrimitives(primIndex);
            g_CurrentEntity->flags &= ~FLAG_HAS_PRIMS;
            g_CurrentEntity->ext.lesserDemon.unk84++;
            g_CurrentEntity->ext.lesserDemon.unk80 = 0;
        }
        break;
    case 2:
        ret = true;
    }
    return ret;
}

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

// func_us_801BC28C code is shared with PSX and is ready for merge
// Lesser Demon punch attack
void func_us_801BC28C(void) {
    Primitive* prim;
    s32 primIndex;

    switch (g_CurrentEntity->ext.lesserDemon.unk84) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex != -1) {
            g_CurrentEntity->flags |= FLAG_HAS_PRIMS;
            g_CurrentEntity->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            g_CurrentEntity->ext.prim = prim;
            UnkPolyFunc2(prim);
            prim->tpage = 0x13;
            prim->clut = 0x24A;
            prim->v0 = 0x70;
            prim->v1 = prim->v0;
            prim->v2 = 0x7F;
            prim->v3 = prim->v2;
            if (g_CurrentEntity->facingLeft) {
                prim->next->x1 = g_CurrentEntity->posX.i.hi + 4;
                prim->next->clut = 2;
                prim->u0 = 0x2F;
                prim->u1 = 0;
            } else {
                prim->u0 = 0;
                prim->u1 = 0x2F;
                prim->next->x1 = g_CurrentEntity->posX.i.hi - 4;
                LOH(prim->next->clut) = -2;
            }
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            prim->next->y0 = g_CurrentEntity->posY.i.hi + 1;
            prim->priority = g_CurrentEntity->zPriority + 2;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            prim->next->b3 = 0x80;
            LOH(prim->next->r2) = 0x28;
            LOH(prim->next->b2) = 0x10;
        } else {
            g_CurrentEntity->ext.lesserDemon.unk84 = 3;
        }
        g_CurrentEntity->ext.lesserDemon.unk84++;
        return;
    case 1:
        prim = g_CurrentEntity->ext.lesserDemon.unk7C;
        if (prim->next->r3) {
            prim->clut = 0x252;
        } else {
            prim->clut = 0x24A;
        }

        prim->next->r3 ^= 1;
        UnkPrimHelper(prim);
        LOH(prim->next->r2) += 2;
        LOH(prim->next->b2) -= 1;
        prim->next->b3 -= 4;
        if (LOH(prim->next->r2) > 0x38) {
            g_CurrentEntity->ext.lesserDemon.unk84++;
        }
        break;
    case 2:
        primIndex = g_CurrentEntity->primIndex;
        g_api.FreePrimitives(primIndex);
        g_CurrentEntity->flags &= ~FLAG_HAS_PRIMS;
        g_CurrentEntity->ext.lesserDemon.unk84++;
        break;
    }
}

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09256E08);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09257100);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_092576C8);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09257BF8);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09258100);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09258A38);

// Lesser Demon
INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09258B50);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_0925A798);
