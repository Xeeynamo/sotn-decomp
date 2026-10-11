// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rbo6/rbo6.h"
#include <scratchpad.h>

extern s32 D_91FC480;
extern EInit g_EInitInteractable;
extern s32 D_pspeu_0926C6C8;
extern u8 D_pspeu_0926BB70;

void EntityCutscene(Entity* self);

void func_us_801A362C(Entity* self) {
    if (D_91FC480) {
        EntityCutscene(self);
    }
    if (self->entityId) {
        EntityCutscene(self);
    }
}

#define BG_BLOCK_NEEDS_SCALE
#include "../../st/e_room_bg.h"

extern SVECTOR D_pspeu_0926B9A8[];
extern SVECTOR* D_pspeu_0926BA28[];
extern s16 D_pspeu_0926BB48[][3];
extern s32 E_ID(UNK_30);
extern s32 E_ID(UNK_31);
extern s32 D_pspeu_0926C060;
extern u32 g_CutsceneFlags;
extern s32 D_pspeu_0926C6C0;
extern SVECTOR D_pspeu_0926C6D0;
extern long D_pspeu_0926C6D8;
extern s16 D_pspeu_0926C6E0;
extern s16 D_pspeu_0926C6E8;
extern s16 D_pspeu_0926C6F0;
extern SVECTOR D_pspeu_0926C6F8;

void func_us_801B1738(Entity* self) {
    s16 var_s7;
    s16 var_s6;
    u8* var_s5;
    MATRIX* m;
    SVECTOR* vec;
    s32* var_s3;
    u8 var_s2;
    s32 j;
    Primitive* prim;
    s32 primIndex;
    s32 i;
    s32 spC4;
    s32 priority;
    s32 xSum;
    s32 ySum;
    s32 depthBase;
    s16* angles;
    s32* depths;
    SVECTOR* rotations;
    CVECTOR* color;
    SVECTOR* strip;
    SVECTOR** vectors;
    VECTOR translation;
    RECT clip;
    DRAWENV drawEnv;
    DR_ENV* drEnv;
    s16* spawn;
    Entity* entity;

    FntPrint("d_step %x\n", self->step);
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->flags |= FLAG_UNK_10000;
        self->zPriority = 0x80;
        g_Tilemap.flags &= 0xFFFE;
        g_BgLayers->flags &= 0xFFFE;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x2E);
        if (primIndex == -1) {
            self->step = 0;
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        drEnv = g_api.func_800EDB08((POLY_GT4*)prim);
        if (drEnv == NULL) {
            g_api.FreePrimitives(primIndex);
            self->flags &= ~FLAG_HAS_PRIMS;
            self->step = 0;
            return;
        }
        prim->type = PRIM_ENV;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        drEnv = g_api.func_800EDB08((POLY_GT4*)prim);
        if (prim == NULL) {
            g_api.FreePrimitives(primIndex);
            self->flags &= ~FLAG_HAS_PRIMS;
            self->step = 0;
            return;
        }
        prim->type = PRIM_ENV;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        self->ext.et_801B1738.prim1 = prim;
        for (i = 0; i < 20; i++) {
            prim->type = PRIM_GT3;
            prim->clut = 0x194;
            prim->tpage = 0x110;
            prim->u0 = 0x40;
            prim->v0 = 0xD;
            prim->u1 = 0x10;
            prim->v1 = 0x60;
            prim->u2 = 0x70;
            prim->v2 = 0x60;
            prim->priority = 0x80;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->ext.et_801B1738.unk80 = prim;
        while (prim != NULL) {
            prim->priority = 0x80;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        angles = &self->ext.et_801B1738.unk84[0];
        rotations = &D_pspeu_0926B9A8[0];
        for (i = 0; i < 4; i++, angles++, rotations++) {
            *angles = rotations->pad;
        }
        self->scaleX = 0x100;
        D_pspeu_0926C6F0 = 0x100;
        D_pspeu_0926C6E8 = 0x200;
        D_pspeu_0926C6E0 = 0x700;
        D_pspeu_0926C6D8 = 0;
        self->ext.et_801B1738.unkA4 = 4;
        self->ext.et_801B1738.unkA6 = 8;
        self->rotate = 2;
        self->ext.et_801B1738.unkA8 = 0;
        break;
    case 1:
        if (g_CutsceneFlags & 0x20) {
            D_pspeu_0926C6C0 = 1;
            D_pspeu_0926C6D8 = 0x10;
            self->step++;
        }
        break;
    case 2:
        D_pspeu_0926C6D8++;
        if (D_pspeu_0926C6D8 > 0x80) {
            D_pspeu_0926C6D8 = 0x80;
            self->step++;
        }
        break;
    case 3:
        if (D_pspeu_0926C060 & 2) {
            self->step++;
        }
        break;
    case 4:
        if (self->ext.et_801B1738.unkA4 < 0x18) {
            self->ext.et_801B1738.unkA4 += 2;
        }
        if (self->ext.et_801B1738.unkA6 < 0x18) {
            self->ext.et_801B1738.unkA6 += 2;
        }
        if (self->rotate < ROT(45)) {
            self->rotate += 2;
        }
        self->ext.et_801B1738.unkA8 += 0x50;
        if (self->ext.et_801B1738.unkA8 > 0x1200) {
            D_pspeu_0926C6C8 = 1;
            self->ext.et_801B1738.unkA0 = 0x40;
            entity = &g_Entities[159];
            CreateEntityFromCurrentEntity(E_ID(UNK_31), entity);
            self->step++;
        }
        break;
    case 5:
        if (D_pspeu_0926C6D8 < 0xA0) {
            D_pspeu_0926C6D8 += 2;
        }
        if (self->ext.et_801B1738.unkA4 > 0x10) {
            self->ext.et_801B1738.unkA4 -= 6;
        }
        if (self->ext.et_801B1738.unkA6 > 0x10) {
            self->ext.et_801B1738.unkA6 -= 6;
        }
        if (self->rotate > ROT(1.40625)) {
            self->rotate -= 12;
        }
        if (!--self->ext.et_801B1738.unkA0) {
            self->step++;
        }
        break;
    case 6:
        D_pspeu_0926C6D8 -= 10;
        if (D_pspeu_0926C6D8 < 0x10) {
            D_pspeu_0926C6D8 = 0;
            self->ext.et_801B1738.unkA0 = 0x60;
            self->step++;
        }
        break;
    case 7:
        prim = self->ext.et_801B1738.prim1;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        if (!--self->ext.et_801B1738.unkA0) {
            DestroyEntity(self);
        }
        return;
    }

    prim = &g_PrimBuf[self->primIndex];
    drawEnv = g_CurrentBuffer->draw;
    drawEnv.isbg = 1;
    drawEnv.r0 = 0;
    drawEnv.g0 = 0;
    drawEnv.b0 = 0;
    clip.x = 0;
    clip.y = 0x100;
    clip.w = 0x100;
    clip.h = 0x100;
    drawEnv.clip = clip;
    drawEnv.ofs[0] = 0;
    drawEnv.ofs[1] = 0x100;
    drEnv = (DR_ENV*)LOW(prim->r1);
    SetDrawEnv(drEnv, &drawEnv);
    prim->priority = 0x27;
    prim->drawMode = DRAW_DEFAULT;
    prim = prim->next;
    prim->priority = 0x29;
    prim->drawMode = DRAW_UNK_800;
    i = g_Timer & 3;
    if (i < 3 && (rand() & 3)) {
        spawn = D_pspeu_0926BB48[i];
        entity = AllocEntity(&g_Entities[192], &g_Entities[219]);
        if (entity != NULL) {
            CreateEntityFromCurrentEntity(E_ID(UNK_30), entity);
            entity->zPriority = 0x28;
            entity->rotate = spawn[2];
            if (D_pspeu_0926C6C8) {
                entity->rotate += (Random() * 2) - 0x100;
            } else {
                entity->rotate += Random() - 0x80;
            }
            entity->posX.i.hi = spawn[0];
            entity->posY.i.hi = spawn[1];
        }
    }
    D_pspeu_0926C6F8.vx += self->ext.et_801B1738.unkA4;
    D_pspeu_0926C6F8.vy += self->ext.et_801B1738.unkA6;
    D_pspeu_0926C6F8.vz += self->rotate;
    D_pspeu_0926C6F0 += 2;
    D_pspeu_0926C6E8 += 4;
    D_pspeu_0926C6E0 += 3;
    if (self->ext.et_801B1738.unkA8) {
        D_pspeu_0926C6F0 += 8;
        D_pspeu_0926C6E8 += 16;
        D_pspeu_0926C6E0 += 12;
    }
    m = (MATRIX*)SP(0);
    vec = (SVECTOR*)SP(0x40);
    depths = (s32*)SP(0x90);
    color = (CVECTOR*)SP(0xAC);
    color->r = color->g = color->b = 0x80;
    color->r = D_pspeu_0926C6D8 +
               (((D_pspeu_0926C6D8 / 2) * rcos(D_pspeu_0926C6F0)) >> 12);
    color->g = D_pspeu_0926C6D8 +
               (((D_pspeu_0926C6D8 / 2) * rsin(D_pspeu_0926C6E8)) >> 12);
    color->b = D_pspeu_0926C6D8 +
               (((D_pspeu_0926C6D8 / 2) * rcos(D_pspeu_0926C6E0)) >> 12);
    color->cd = 5;
    SetGeomScreen(0x600);
    SetGeomOffset(0x80, 0x80);
    SetFarColor(0, 0, 0);
    SetFogNear(0x200, 0x600);
    *vec = D_pspeu_0926C6F8;
    RotMatrix(vec, m);
    SetRotMatrix(m);
    translation.vx = 0;
    translation.vy = 0;
    translation.vz = -24;
    LOW(translation.vz) += self->ext.et_801B1738.unkA8;
    translation.vz = 0x400;
    depthBase = translation.vz >> 2;
    gte_ldtr(0, 0, translation.vz);
    prim = self->ext.et_801B1738.prim1;
    vectors = &D_pspeu_0926BA28[0];
    for (i = 0; i < 20; i++) {
        gte_ldv3(vectors[0], vectors[1], vectors[2]);
        gte_rtpt();
        gte_stsxy3_gt3(prim);
        *(CVECTOR*)&prim->r0 = *color;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        prim->drawMode = DRAW_COLORS | DRAW_UNK02;
        gte_nclip();
        gte_stopz(depths);
        if (!self->ext.et_801B1738.unkA8 && *depths > 0) {
            prim->drawMode = DRAW_HIDE;
        }
        xSum = (prim->x0 & 0x100) + (prim->x1 & 0x100) + (prim->x2 & 0x100);
        ySum = (prim->y0 & 0x100) + (prim->y1 & 0x100) + (prim->y2 & 0x100);
        if (xSum > 0x300 || ySum > 0x300) {
            prim->drawMode = DRAW_HIDE;
        }
        gte_avsz3();
        gte_stszotz((long*)depths);
        prim->type = PRIM_GT3;
        priority = 0x80 - ((*depths - depthBase) >> 2);
        if (!self->ext.et_801B1738.unkA8) {
            priority -= 2;
        }
        if (priority > 0x1F8) {
            priority = 0x1F8;
        }
        if (priority < 4) {
            priority = 4;
        }
        prim->priority = priority;
        vectors += 3;
        prim = prim->next;
    }
    if (!D_pspeu_0926C6C0 || (D_pspeu_0926C060 & 1)) {
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        return;
    }
    angles = &self->ext.et_801B1738.unk84[0];
    for (i = 0; i < 4; i++, angles++) {
        *angles += 0x38;
        if (*angles > 0 && *angles < 0x39) {
            g_api.PlaySfx(SFX_ELECTRICITY);
        }
        if (*angles > 0x2000) {
            *angles = -(*angles & 0xFFF);
        }
    }
    prim = self->ext.et_801B1738.unk80;
    angles = &self->ext.et_801B1738.unk84[0];
    rotations = &D_pspeu_0926B9A8[0];
    m = (MATRIX*)SP(0);
    vec = (SVECTOR*)SP(0x40);
    strip = (SVECTOR*)SP(0x48);
    var_s5 = (u8*)SP(0xB0);
    depths = (s32*)SP(0x90);
    SetGeomScreen(0x600);
    SetGeomOffset(0x80, 0x80);
    gte_ldtr(0, 0, 0x600);
    strip[0].vx = 0;
    strip[0].vy = -12;
    strip[1].vx = 0;
    strip[1].vy = 12;
    spC4 = 0;
    for (i = 0; i < 4; i++, angles++, rotations++) {
        var_s7 = *angles;
        if (var_s7 >= 0) {
            vec->vx += rotations->vx;
            vec->vy += rotations->vy;
            vec->vz += rotations->vz;
            RotMatrix(vec, &m[1]);
            gte_SetColorMatrix(&m[1]);
            var_s2 = 0;
            var_s3 = (s32*)SP(0x58);
            for (j = 0; j < 7; j++) {
                var_s6 = 0x90 - ((var_s7 * 0x78) / 0x1800);
                if (var_s6 < 0x18) {
                    var_s6 = 0x18;
                }
                strip[0].vz = -var_s6;
                strip[1].vz = -var_s6;
                RotMatrix(&D_pspeu_0926C6D0, m);
                RotMatrixY(var_s7, m);
                RotMatrixX(vec->vx, m);
                RotMatrixY(vec->vy, m);
                RotMatrixZ(vec->vz, m);
                SetRotMatrix(m);
                gte_ldv01c(strip);
                gte_rtpt();
                gte_stsxy01c(&var_s3[j * 2]);
                gte_stszotz((long*)&depths[j]);
                if (var_s7 < 0) {
                    var_s2++;
                    if (var_s2 > 4) {
                        var_s2 = 4;
                    }
                    var_s5[j] = 0x80 - (var_s2 * 0x20);
                } else {
                    var_s2 = 0;
                    var_s5[j] = 0x80;
                }
                var_s7 -= ratan2(16, var_s6);
                if (var_s7 > 0x1800) {
                    var_s5[j] = 0x60;
                    spC4 = 1;
                } else {
                    spC4 = 0;
                }
            }
            var_s3 = (s32*)SP(0x58);
            for (j = 0; j < 6; j++) {
                prim->tpage = 0x1A;
                prim->clut = 0x194;
                prim->u0 = prim->u2 = j * 16 + 0x90;
                prim->u1 = prim->u3 = prim->u0 + 15;
                if (g_Timer & 2) {
                    prim->v0 = prim->v1 = 0xC0;
                    prim->v2 = prim->v3 = 0xD0;
                } else {
                    prim->v0 = prim->v1 = 0xD0;
                    prim->v2 = prim->v3 = 0xC0;
                }
                LOW(prim->x0) = var_s3[0];
                LOW(prim->x1) = var_s3[2];
                LOW(prim->x2) = var_s3[1];
                LOW(prim->x3) = var_s3[3];
                prim->priority = depths[j] - 0x100;
                prim->drawMode = DRAW_UNK02;
                var_s2 = (var_s5 + j)[1];
                if (var_s2 != 0x80) {
                    prim->r0 = prim->g0 = prim->b0 = var_s5[j];
                    LOW(prim->r2) = LOW(prim->r0);
                    prim->r1 = prim->g1 = prim->b1 = (var_s5 + j)[1];
                    LOW(prim->r3) = LOW(prim->r1);
                    prim->drawMode |=
                        DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
                }
                prim = prim->next;
                var_s3 += 2;
            }
        }
    }
    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

void func_us_801B2864(Entity* self) {
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->flags |= FLAG_UNK_10000;
        self->palette = PAL_UNK_19E;
        self->palette = 0x2E2;
        self->palette = 0x2E5;
        self->animSet = 0xE;
        self->unk5A = 0x79;
        self->flags &= ~FLAG_POS_CAMERA_LOCKED;
        self->drawFlags = ENTITY_ROTATE;
        self->blendMode = BLEND_QUARTER | BLEND_TRANSP;
        self->facingLeft = Random() & 1;
        angle = self->rotate;
        if (self->facingLeft) {
            self->rotate = -(s16)angle;
        }
        self->velocityX = rsin((s32)(s16)angle) * 0x28;
        self->velocityY = rcos((s32)(s16)angle) * -0x28;
        self->drawFlags |= ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleX = 0xE0;
        self->scaleY = 0x140;
        if (D_pspeu_0926C6C8) {
            self->scaleX = 0x120;
            self->scaleY = 0x120;
        }
        /* fall through */
    case 1:
        MoveEntity();
        if (!AnimateEntity(&D_pspeu_0926BB70, self)) {
            DestroyEntity(self);
        }
        break;
    }
}
