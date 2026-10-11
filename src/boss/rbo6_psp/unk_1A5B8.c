// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rbo6/rbo6.h"
#include <scratchpad.h>

typedef struct {
    u16 animSet;
    u16 unk2;
    u16 palette;
    u16 blendMode;
    u32 animation;
} Borbo6ParticleData;

extern Borbo6ParticleData D_pspeu_0926BC10[];
extern EInit g_EInitParticle;
extern EInit g_EInitInteractable;
extern SVECTOR D_pspeu_0926C700[0x100];
extern u8 D_pspeu_0926CF00[0x100];
extern u32 g_CutsceneFlags;

void func_us_8019D330_from_rcen(Entity* self) {
    u32 index;
    Borbo6ParticleData* particle;
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        index = self->params & 0xF;
        particle = &D_pspeu_0926BC10[index];
        self->palette = particle->palette + 0x2E0;
        self->blendMode = (u8)particle->blendMode;
        self->animSet = particle->animSet;
        self->unk5A = particle->unk2;
        self->ext.et_801A518C.anim = (u8*)particle->animation;
        self->step = index + 1;
        if (self->params & 0xFF00) {
            self->zPriority = (self->params & 0xFF00) >> 8;
        }
        if (!(self->params & 0xF0)) {
            return;
        }
        self->palette = PAL_FLAG(PAL_UNK_19F);
        self->blendMode = BLEND_TRANSP;
        self->facingLeft = 1;
        return;

    case 1:
        if (AnimateEntity(self->ext.et_801A518C.anim, self) == 0) {
            DestroyEntity(self);
        }
        break;

    case 2:
        MoveEntity();
        self->velocityY = FIX(-1.0);
        if (AnimateEntity(self->ext.et_801A518C.anim, self) == 0) {
            DestroyEntity(self);
        }
        break;

    case 3:
        if (!self->step_s) {
            self->drawFlags = ENTITY_OPACITY;
            self->drawFlags |= ENTITY_ROTATE;
            self->opacity = 0x80;
            self->facingLeft = Random() & 1;
            self->rotate = rand() & 0xFFF;
            angle = self->rotate;
            if (self->facingLeft) {
                angle = -angle;
            }
            self->velocityX = rsin(angle) * 0x28;
            self->velocityY = rcos(angle) * -0x28;
            self->ext.et_801A518C.acceleration = (Random() << 4) + 0x1000;
            self->step_s++;
        }
        MoveEntity();
        self->opacity--;
        angle = self->rotate;
        if (self->facingLeft) {
            angle = -angle;
        }
        self->velocityX +=
            (rsin(angle) * (s32)self->ext.et_801A518C.acceleration) >> 12;
        self->velocityY +=
            (-(s32)self->ext.et_801A518C.acceleration * rcos(angle)) >> 12;
        if (AnimateEntity(self->ext.et_801A518C.anim, self) == 0) {
            DestroyEntity(self);
        }
        break;

    case 4:
        if (!self->step_s) {
            self->drawFlags = ENTITY_OPACITY;
            self->opacity = 0x80;
            self->facingLeft = Random() & 1;
            self->velocityX = ((Random() << 9) - 0x8000) - 0x8000;
            self->velocityY = FIX(-2.5);
            self->ext.et_801A518C.accelerationY = -(Random() << 4) - 0x1000;
            self->step_s++;
        }
        MoveEntity();
        self->velocityY += (s32)self->ext.et_801A518C.accelerationY;
        self->opacity--;
        if (AnimateEntity(self->ext.et_801A518C.anim, self) == 0) {
            DestroyEntity(self);
        }

    default:
        return;
    }
}

void EntityBackgroundVortex(Entity* self) {
    u8 brightness; // writes into an array, later that array is used for colors
    u8 leftV;
    u8 rightV;
    s32 primIndex;
    s32 scale;
    s32 xSize;
    s32 ySize;
    s32 zSize;
    SVECTOR rotVector;
    VECTOR transVector;
    MATRIX m;
    DRAWENV draw_env;
    DR_ENV* dr_env;
    RECT tw_rect;
    CVECTOR unused_Cvector;

    s32 size;
    s16 angle;
    s32 vectorIndex1;
    s32 vectorIndex2;
    s32 j;
    CVECTOR* scratchColor;
    s32 var_s2;
    s32 i;
    Primitive* prim;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->posX.i.hi = 0x80;
        self->posY.i.hi = 0x1A0;
        self->opacity = 0;
        primIndex = g_api.func_800EDB58(PRIM_GT4, 0x110);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.bgVortex.prim = prim;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->ext.bgVortex.unk9C = 0x5F0;
        self->ext.bgVortex.unk9E = 0xB0;
        self->ext.bgVortex.unkA0 = 0;
        self->ext.bgVortex.unkAE = 0xD0;
        // Fallthrough
    case 1:
        size = 0x60;
        scale = 0;
        brightness = 0x10;
        var_s2 = 0;
        angle = 0;
        for (j = 0; j < 16; j++) {
            scale = SquareRoot0(j * 0x120) * 4;
            for (i = 0; i < 16; i++) {
                xSize = (size * rcos(angle + i * 0x100)) >> 0xC;
                ySize = (size * rsin(angle + i * 0x100)) >> 0xC;
                zSize = scale;
                D_pspeu_0926C700[var_s2].vx = xSize;
                D_pspeu_0926C700[var_s2].vy = ySize;
                D_pspeu_0926C700[var_s2].vz = zSize;
                var_s2++;
            }
            D_pspeu_0926CF00[j] = brightness;
            angle += 0x80;
            size += 0x1C;
            brightness += 0x28;
            if (brightness > 0xA0) {
                brightness = 0xA0;
            }
        }
        self->step++;
        break;
    case 2:
        func_psp_0891CB80(0x180, 0x100, 0x40, 0x40, 0x40, 0, 0);
        func_psp_0891CB80(0x180, 0x100, 0x40, 0x40, 0x40, 0x40, 0);
        func_psp_0891CB80(0x180, 0x100, 0x40, 0x40, 0x40, 0x80, 0);
        func_psp_0891CB80(0x180, 0x100, 0x40, 0x40, 0x40, 0xC0, 0);
        prim = self->ext.bgVortex.prim;
        while (prim != NULL) {
            prim->clut = PAL_UNK_19E;
            prim->tpage = 1;
            prim->u0 = prim->u2 = 0;
            prim->u1 = prim->u3 = 0x3F;
            prim->v0 = prim->v1 = 0;
            prim->v2 = prim->v3 = 0x40;
            prim->priority = 0x80;
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
        }
        prim = self->ext.bgVortex.prim;
        draw_env = g_CurrentBuffer->draw;

        dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
        if (dr_env == NULL) {
            DestroyEntity(self);
            return;
        }
        prim->type = PRIM_ENV;
        draw_env.isbg = 0;
        draw_env.r0 = 0;
        draw_env.g0 = 0;
        draw_env.b0 = 0;
        draw_env.dtd = 0;
        draw_env.clip.x = 0;
        draw_env.ofs[0] = 0;
        tw_rect.x = 0;
        tw_rect.y = 0;
        tw_rect.w = 0x40;
        tw_rect.h = 0x40;
        draw_env.tw = tw_rect;
        SetDrawEnv(dr_env, &draw_env);
        prim->priority = 2;
        prim->drawMode = DRAW_UNK_1000;
        prim = prim->next;
        dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
        if (dr_env == NULL) {
            DestroyEntity(self);
            return;
        }
        prim->type = PRIM_ENV;
        prim->priority = 0x59;
        prim->drawMode = DRAW_UNK_800;
        prim = prim->next;
        self->step++;
        break;
    case 3:
        if ((g_CutsceneFlags & 0x20) && self->opacity < 0x80) {
            self->opacity++;
        }
        switch (self->step_s) {
        case 0:
            self->posY.val -= FIX(0.75);
            if (self->posY.i.hi < 0xA0) {
                self->posY.i.hi = 0xA0;
                self->step_s++;
            }
            break;
        case 1:
            self->ext.bgVortex.unkA4 += 16;
            self->ext.bgVortex.unkA6 += 8;
            self->ext.bgVortex.unkA8 += 32;
            self->ext.bgVortex.unkAA += 2;
            self->ext.bgVortex.unk9C =
                ((rsin(self->ext.bgVortex.unkA4) << 6) >> 0xC) + 0x5F0;
            self->ext.bgVortex.unk9E =
                ((rsin(self->ext.bgVortex.unkA6) << 7) >> 0xC) + 0xB0;
            self->ext.bgVortex.unkA0 =
                ((rsin(self->ext.bgVortex.unkA8) << 4) >> 0xC);
            self->ext.bgVortex.unkAE =
                ((rsin(self->ext.bgVortex.unkAA) * 24) >> 0xC) + 0xD0;
            break;
        }
        prim = self->ext.bgVortex.prim;
        prim = prim->next;
        prim = prim->next;
        leftV = prim->v0;
        rightV = prim->v2;
        leftV += 2;
        rightV += 2;

        if (rightV < leftV) {
            leftV = rightV;
            rightV = leftV + 0x40;
        }
        while (prim != NULL) {
            prim->v0 = prim->v1 = leftV;
            prim->v2 = prim->v3 = rightV;
            prim = prim->next;
        }
        self->ext.bgVortex.unk80 -= 4;
        SetGeomScreen(0xC0);
        SetGeomOffset(self->posX.i.hi, self->posY.i.hi);
        SetFarColor(0, 0, 0);
        SetFogNear(0x128, 0xC0);
        rotVector.vx = 0;
        rotVector.vy = 0;
        rotVector.vz = self->ext.bgVortex.unk80;
        rotVector.vx += self->ext.bgVortex.unk9C;
        rotVector.vy += self->ext.bgVortex.unk9E;
        rotVector.vz += self->ext.bgVortex.unkA0;

        RotMatrix(&rotVector, &m);
        SetRotMatrix(&m);
        transVector.vx = 0;
        transVector.vy = 0;
        transVector.vz = 0x1E0;
        transVector.vz += self->ext.bgVortex.unkAE;
        TransMatrix(&m, &transVector);
        SetTransMatrix(&m);
        // scratchpad memory
        scale = self->opacity;
        scratchColor = (CVECTOR*)SP(0);
        for (i = 0; i < 16; i++, scratchColor++) {
            var_s2 = ((i & 1) * 2) + 1;
            scratchColor->b = (scale * (D_pspeu_0926CF00[i] / var_s2)) / 0x80;
            scratchColor->r = scratchColor->g =
                (scale * ((D_pspeu_0926CF00[i] / 2) / var_s2)) / 0x80;
            scratchColor->cd = 4;
        }
        prim = self->ext.bgVortex.prim;
        prim = prim->next;
        prim = prim->next;
        unused_Cvector.r = 0x80;
        unused_Cvector.g = 0x80;
        unused_Cvector.b = 0x80;
        unused_Cvector.cd = 4;
        scratchColor = (CVECTOR*)SP(0);
        for (i = 0; i < 15; i++) {
            for (j = 0; j < 16; j++) {
                var_s2 = i * 0x10;
                vectorIndex1 = var_s2 + j;
                vectorIndex2 = var_s2 + ((j + 1) & 0xF);
                gte_ldv0(&D_pspeu_0926C700[vectorIndex1]);
                gte_rtps();
                gte_stsxy((long*)&prim->x0);
                gte_ldrgb(&scratchColor[i]);
                gte_dpcs();
                gte_strgb(&prim->r0);
                prim->type = PRIM_GT4;
                gte_ldv0(&D_pspeu_0926C700[vectorIndex2]);
                gte_rtps();
                gte_stsxy((long*)&prim->x1);
                gte_ldrgb(&scratchColor[i]);
                gte_dpcs();
                if ((prim->y0 >= 0) || (prim->y1 >= 0)) {
                    gte_strgb(&prim->r1);
                    gte_ldv0(&D_pspeu_0926C700[vectorIndex1] + 0x10);
                    gte_rtps();
                    if (prim->y0 <= 0x100 || prim->y1 <= 0x100) {
                        gte_stsxy((long*)&prim->x2);
                        gte_ldrgb(&scratchColor[i] + 1);
                        gte_dpcs();
                        gte_strgb(&prim->r2);
                        gte_ldv0(&D_pspeu_0926C700[vectorIndex2] + 0x10);
                        gte_rtps();
                        gte_stsxy((long*)&prim->x3);
                        gte_ldrgb(&scratchColor[i] + 1);
                        gte_dpcs();
                        if (prim->x0 <= 0x100 || prim->x1 <= 0x100 ||
                            prim->x2 <= 0x100 || prim->x3 <= 0x100) {
                            gte_strgb(&prim->r3);
                            if (prim->x0 >= 0 || prim->x1 >= 0 ||
                                prim->x2 >= 0 || prim->x3 >= 0) {
                                gte_stszotz((long*)&zSize);
                                if (zSize < 0x55) {
                                    prim->priority = 0x58 - zSize;
                                } else {
                                    prim->priority = 3;
                                }
                                prim->drawMode = DRAW_COLORS;
                                prim = prim->next;
                            }
                        }
                    }
                }
            }
        }
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }
}
