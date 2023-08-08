#include "nz0.h"

void func_801B6DE4(Entity* self) {
    s32 temp_s1 = self->hitFlags;
    s16 primIndex;
    POLY_GT4* poly;
    s32 temp;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180BF8);
        self->ext.generic.unk80.modeS32 = self->posY.i.hi + g_Camera.posY.i.hi;
        self->hitboxHeight = 8;
        self->hitboxOffY = -0x16;
        self->hitboxWidth = 6;
        self->hitboxState = 1;

        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        poly = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        *((s32*)(&self->ext.generic.unk7C)) = poly;

        self->flags |= FLAG_HAS_PRIMS;
        poly->tpage = 0xF;
        poly->clut = 9;
        poly->u0 = 72;
        poly->v0 = 200;
        poly->u1 = 16;
        poly->v1 = 16;
        poly->pad2 = 0x5F;
        poly->code = 6;
        poly->pad3 = 2;

    case 1:
        if (temp_s1 != 0) {
            self->posY.val += FIX(1.0);
            temp = g_Camera.posY.i.hi + self->posY.i.hi;
            if ((self->ext.generic.unk80.modeS32 + 4) < temp) {
                self->posY.i.hi = (u16)(self->ext.generic.unk80.modeS16.unk0 -
                                        (g_Camera.posY.i.hi - 4));
                self->step++;
                func_801C29B0(NA_SE_EV_SWITCH_CLICK);
                D_801813A4 = self->params;
            }
        }
        break;

    case 2:
        if (temp_s1 == 0) {
            self->posY.val += 0xFFFF0000;
            temp = g_Camera.posY.i.hi + self->posY.i.hi;
            if (temp < self->ext.generic.unk80.modeS32) {
                self->posY.i.hi = (u16)(self->ext.generic.unk80.modeS16.unk0) -
                                  g_Camera.posY.i.hi;
                self->step = 1;
            }
        }
        break;
    }

    poly = (POLY_GT4*)(*((s32*)(&self->ext.generic.unk7C)));
    poly->x0 = self->posX.i.hi - 8;
    poly->y0 = self->posY.i.hi;
    poly->y0 = poly->y0 - 8;
}

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/36DE4", func_801B7034);

void func_801B74CC(void) {
    D_801CB694 = 2;
    D_801CB692 = 2;
    D_801CB696 = 0;
    D_801CB69A = 0;
    D_801CB69E = 0;
    D_801CB69F = 8;
    D_801CB68E = D_801CB690 + 0x14;
}

// called from EntityMariaCutscene
s32 func_801B7520(s32 arg0) {
    Primitive* prim;
    s16 firstPrimIndex;

    firstPrimIndex = g_api.AllocPrimitives(PRIM_SPRT, 7);
    D_801CB6C0[0] = firstPrimIndex;
    if (firstPrimIndex == -1) {
        D_801CB6C0[0] = 0;
        return 0;
    }
    D_801CB688 = arg0;
    D_801CB6C4 = 0;
    D_801CB6BC = -1;
    D_801CB6B8 = -1;
    func_801B74CC();

    if (prim && prim) { // !FAKE
    }

    prim = D_801CB6A0[0] = &g_PrimBuf[D_801CB6C0[0]];

    prim->blendMode = BLEND_VISIBLE;
    prim = D_801CB6A0[1] = prim->next;

    prim->blendMode = BLEND_VISIBLE;
    prim = D_801CB6A0[2] = prim->next;

    prim->blendMode = BLEND_VISIBLE;
    prim = D_801CB6A0[3] = prim->next;

    prim->blendMode = BLEND_VISIBLE;
    prim = D_801CB6A0[4] = prim->next;

    prim->blendMode = BLEND_VISIBLE;
    prim = D_801CB6A0[5] = prim->next;

    prim->type = 4;
    prim->blendMode = BLEND_VISIBLE;

    prim = prim->next;
    prim->type = 3;
    prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0xFF;
    prim->b0 = prim->b1 = prim->b2 = prim->b3 = prim->g0 = prim->g1 = prim->g2 =
        prim->g3 = 0;
    prim->x0 = prim->x2 = 4;
    prim->x1 = prim->x3 = 0xF8;
    prim->priority = 0x1FD;
    prim->blendMode = BLEND_VISIBLE;

    prim = prim->next;
    prim->type = 1;
    prim->x0 = 3;
    prim->y0 = 0x2F;
    prim->v0 = 0x4A;
    prim->r0 = prim->g0 = prim->b0 = 0xFF;
    prim->priority = 0x1FC;
    prim->blendMode = BLEND_VISIBLE;
    return 1;
}

void func_801B76E4(s16 arg0) {
    RECT rect;

    rect.y = (arg0 * 12) + 384;
    rect.w = 64;
    rect.x = 0;
    rect.h = 12;
    ClearImage(&rect, 0, 0, 0);
}

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/36DE4", func_801B7740);

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/36DE4", func_801B77F8);

void func_801B797C(s32 arg0) {
    D_801CB6C8 = arg0 + 0x100000;
    D_801CB6C6 = 0;
    D_801CB6C4 = 1;
}

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/36DE4", func_801B79A8);

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/36DE4", func_801B7C54);

// cutscene where alucard and maria discuss castle changing
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/36DE4", EntityMariaCutscene);

void func_801B8E0C(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(D_80180BEC);
        D_8003C8B8 = 0;
        *D_80097400 = 1;
        g_Player.D_80072EF4 = 0x8000;
        if (g_Player.unk0C & 4) {
            g_Player.D_80072EF4 = 2;
        }
        g_Player.D_80072EFC = 1;
        break;

    case 1:
        if (PLAYER.posX.i.hi < 176) {
            g_Player.D_80072EF4 = 0;
            self->step++;
        } else {
            g_Player.D_80072EF4 = 0;
            if (g_Player.unk0C & 4) {
                if (g_blinkTimer & 1) {
                    g_Player.D_80072EF4 = 2;
                }
            } else {
                g_Player.D_80072EF4 = 0x8000;
            }
        }
        g_Player.D_80072EFC = 1;
        break;

    case 2:
        if (D_801CB734 & 0x2000) {
            D_8003C8B8 = 1;
            if (*D_80097400 != 0) {
                *D_80097400 = 0;
            }
            DestroyEntity(self);
        }
        g_Player.D_80072EF4 = 0;
        g_Player.D_80072EFC = 1;
        break;
    }
}

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/36DE4", func_801B8F94);

