// SPDX-License-Identifier: AGPL-3.0-or-later
#include "game.h"
#include "st0.h"
#include "sfx.h"

#include "../entity_soul_steal_orb.h"

#include "../entity_enemy_blood.h"

extern ObjInit D_80181FE8[];
void EntityRoomForeground(Entity* entity) {
    ObjInit* objInit = &D_80181FE8[entity->params];

    if (entity->step == 0) {
        InitializeEntity(g_EInitCommon);
        entity->animSet = objInit->animSet;
        entity->zPriority = objInit->zPriority;
        entity->unk5A = objInit->unk5A;
        entity->palette = objInit->palette;
        entity->drawFlags = objInit->drawFlags;
        entity->drawMode = objInit->drawMode;
        if (objInit->unkC != 0) {
            entity->flags = objInit->unkC;
        }
        if (entity->params >= 5) {
            entity->rotZ = 0x800;
            entity->drawFlags |= FLAG_DRAW_ROTZ;
        }
    }
    AnimateEntity(objInit->animFrames, entity);
}

#include "../popup.h"

INCLUDE_ASM("st/st0/nonmatchings/39EA8", EntityClouds);

typedef struct {
    u8 u0, v0, u1, v1, u2, v2;
    u16 clut;
} ClockTowerData;

extern ClockTowerData D_80182184[];

typedef struct {
    u8 u, v, w, h;
    u16 clut;
} ClockTowerData2;
extern ClockTowerData2 D_8018219C[];

extern u8 D_80182398;
extern u8 D_801823D0;
extern s32 D_80182414[];

void EntityClockTower3D(Entity* self) {
    s32 unusedHalfZ;
    SVECTOR rotVector;
    VECTOR transVector;
    MATRIX matrix;

    s32 unusedScratch0;
    s32 unusedScratch4;
    s32 xBase;
    s32 primIndex;
    s32 var_s4;
    ClockTowerData2* var_s3;
    ClockTowerData* var_s2;
    u8* var_s1; // not a struct, weird state machine sort of
    Primitive* prim;

    if (!self->step) {
        InitializeEntity(D_801805D4);
        xBase = 0x480;
        self->posX.i.hi = xBase - g_Tilemap.scrollX.i.hi;
        self->posY.i.hi = 0x80 - g_Tilemap.scrollY.i.hi;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x28);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.clockTower.prim = prim;
        while (prim != NULL) {
            prim->tpage = 0xF;
            PGREY(prim, 0) = 0x80;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim = prim->next;
        }
    }
    SetGeomScreen(0x300);
    SetGeomOffset(0x80, 0x80);

    rotVector.vx = 0;
    rotVector.vy = -0x90;
    rotVector.vz = 0;

    rotVector.vx += self->ext.clockTower.unk9C;
    rotVector.vy += self->ext.clockTower.unk9E;
    rotVector.vz += self->ext.clockTower.unkA0;

    RotMatrix(&rotVector, &matrix);
    SetRotMatrix(&matrix);
    transVector.vx = self->posX.i.hi - 0x80;
    transVector.vy = self->posY.i.hi - 0x80;
    transVector.vz = 0x580;
    transVector.vz += self->ext.clockTower.unkAE;
    TransMatrix(&matrix, &transVector);
    SetTransMatrix(&matrix);
    unusedHalfZ = transVector.vz / 2;

    // Weird, we allocate two 32-bit values (could be pointers, idk) on
    // scratchpad but we never end up using them. These are orphan variables.
    unusedScratch0 = (s32)SP(0);
    unusedScratch4 = (s32)SP(sizeof(s32));

    prim = self->ext.clockTower.prim;
    var_s1 = &D_80182398;
    while (*var_s1 != 0xFF) {
        if (*var_s1 & 0x80) {
            var_s4 = D_80182414[var_s1[1]];
            var_s1 += 2;
        }
        var_s2 = &D_80182184[0];
        var_s2 += *var_s1++;
        prim->u0 = var_s2->u0;
        prim->v0 = var_s2->v0;
        prim->u1 = var_s2->u1;
        prim->v1 = var_s2->v1;
        prim->u2 = var_s2->u2;
        prim->v2 = var_s2->v2;
        prim->clut = var_s2->clut;
        prim->type = PRIM_GT3;
        gte_ldv3(var_s4 + var_s1[0] * 8, var_s4 + var_s1[1] * 8,
                 var_s4 + var_s1[2] * 8);
        gte_rtpt();
        gte_stsxy3_gt3(prim);
        prim->drawMode = DRAW_UNK02;
        prim->priority = var_s1[3] + 0x40;
        var_s1 += 4;
        prim = prim->next;
    }
    var_s1 = &D_801823D0;
    while (*var_s1 != 0xFF) {
        if (*var_s1 & 0x80) {
            var_s4 = D_80182414[var_s1[1]];
            var_s1 += 2;
        }
        var_s3 = &D_8018219C[0];
        var_s3 += (*var_s1++);
        prim->u0 = prim->u2 = var_s3->u;
        prim->v0 = prim->v1 = var_s3->v;
        prim->u1 = prim->u3 = var_s3->u + var_s3->w;
        prim->v2 = prim->v3 = var_s3->v + var_s3->h;
        prim->clut = var_s3->clut;
        prim->type = PRIM_GT4;
        gte_ldv3(var_s4 + var_s1[0] * 8, var_s4 + var_s1[1] * 8,
                 var_s4 + var_s1[2] * 8);
        gte_rtpt();
        gte_stsxy3_gt3(prim);
        gte_ldv0(var_s4 + var_s1[3] * 8);
        gte_rtps();
        gte_stsxy(&prim->x3);
        prim->priority = var_s1[4] + 0x40;
        prim->drawMode = DRAW_UNK02;
        var_s1 += 5;
        prim = prim->next;
    }
    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
    if ((g_Tilemap.scrollX.i.hi + PLAYER.posX.i.hi) < 0x100) {
        DestroyEntity(self);
    }
}

extern u8 D_80182438[3];
extern SVECTOR D_8018243C;
extern SVECTOR D_80182444;
extern SVECTOR D_8018244C;
extern SVECTOR D_80182454;
extern s16 D_8018245C[];

void EntityCutscenePhotograph(Entity* self) {
    RECT clipRect;
    DRAWENV drawEnv;
    SVECTOR rotVector;
    VECTOR transVector;
    MATRIX m;

    s32 newEntX;
    s32 newEntY;
    s32 primIndex;
    s16* newEntXY;
    s32 dualFlag; // Used in color limit system, and as facing left
    s32 i;
    DR_ENV* dr_env;
    Entity* otherEnt;
    Primitive* prim;

    // These 5 variables are not used in PSP.
    u8* colorPtr;
    u8* comparePtr;
    s32 j;
    s32 newColor;
    s32 limit;

    g_Player.D_80072EFC = 4;
    g_Player.padSim = 0;
    D_8003C8B8 = 0;
    switch (self->step) {
    case 0:
        InitializeEntity(D_801805D4);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
        if (primIndex == -1) {
            self->step = 0;
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.cutscenePhoto.prim = prim;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }

    case 1:
        prim = self->ext.cutscenePhoto.prim;
        drawEnv = g_CurrentBuffer->draw;
        if (drawEnv.ofs[0] == 0) {
            prim->tpage = 0x100;
        } else {
            prim->tpage = 0x104;
        }
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0xFF;
        prim->v0 = prim->v1 = 12;
        prim->v2 = prim->v3 = 12 + 0xE0;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0xFF;
        prim->y0 = prim->y1 = 12;
        prim->y2 = prim->y3 = 12 + 0xE0;
        prim->r0 = prim->g0 = prim->b0 = 0x80;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0x1F8;
        prim->drawMode = DRAW_UNK_400 | DRAW_COLORS;
        prim = prim->next;
        self->step++;
        // Fallthrough!
    case 2:
        prim = self->ext.cutscenePhoto.prim;
        drawEnv = g_CurrentBuffer->draw;
        if (drawEnv.ofs[0] == 0) {
            prim->tpage = 0x100;
        } else {
            prim->tpage = 0x104;
        }

        dualFlag = 1;
        comparePtr = &D_80182438[0];
        colorPtr = &prim->r0;
        // Iterate through prim r0, r1, r2, r3
        // Colors are spaced 12 bytes apart.
        for (i = 0; i < 4; i++, colorPtr += 12) {
            // Iterate through r, g, b
            for (j = 0; j < 3; j++) {
                newColor = colorPtr[j];
                newColor--;
                if (newColor < comparePtr[j]) {
                    newColor = comparePtr[j];
                } else {
                    dualFlag = 0;
                }
                colorPtr[j] = newColor;
            }
        }

        if (dualFlag == 0) {
            return;
        }
        self->step++;
        return;
    case 3:
        prim = self->ext.cutscenePhoto.prim;
        prim = prim->next;

        drawEnv = g_CurrentBuffer->draw;
        if (drawEnv.ofs[0] == 0) {
            prim->tpage = 0x100;
        } else {
            prim->tpage = 0x104;
        }
        prim->type = PRIM_GT4;
        prim->u0 = prim->u2 = 6;
        prim->u1 = prim->u3 = 0xF9;
        prim->v0 = prim->v1 = 18;
        prim->v2 = prim->v3 = 18 + 0xD4;
        prim->x0 = prim->x2 = 6;
        prim->x1 = prim->x3 = 0xF9;
        prim->y0 = prim->y1 = 18;
        prim->y2 = prim->y3 = 18 + 0xD4;
        prim->priority = 0x1FB;
        prim->drawMode = DRAW_DEFAULT;

        prim = prim->next;
        dr_env = g_api.func_800EDB08(prim);
        if (dr_env == NULL) {
            SetStep(12);
            return;
        }
        prim->type = PRIM_ENV;
        drawEnv.isbg = 1;
        drawEnv.r0 = 0x70;
        drawEnv.g0 = 0x70;
        drawEnv.b0 = 0x60;
        drawEnv.dtd = 0;
        clipRect.x = 0;
        clipRect.y = 0x100;
        clipRect.w = 0x100;
        clipRect.h = 0x100;
        drawEnv.clip = clipRect;
        drawEnv.ofs[0] = 0;
        drawEnv.ofs[1] = 0x100;
        SetDrawEnv(dr_env, &drawEnv);
        prim->priority = 0x1FA;
        prim->drawMode = DRAW_DEFAULT;

        prim = prim->next;
        dr_env = g_api.func_800EDB08(prim);
        if (dr_env == NULL) {
            SetStep(12);
            return;
        }
        prim->type = PRIM_ENV;
        prim->priority = 0x1FC;
        prim->drawMode = DRAW_UNK_800;

        prim = prim->next;
        prim->type = PRIM_G4;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0x100;
        prim->y0 = prim->y1 = 0;
        prim->y2 = prim->y3 = 0x100;
        prim->r0 = prim->g0 = prim->b0 = 8;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0x1F9;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        self->step++;
        break;
    case 4:
        prim = self->ext.cutscenePhoto.prim;
        prim = prim->next;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        for (i = 0; i < 2; i++) {
            dr_env = (DR_ENV*)LOW(prim->r1);
            dr_env->tag = 0;
            prim->type = PRIM_GT4;
            prim = prim->next;
        }
        prim->drawMode = DRAW_HIDE;
        // useless line due to the following line!
        prim = prim->next;

        prim = self->ext.cutscenePhoto.prim;
        prim->tpage = 0x110;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0xFF;
        prim->v0 = prim->v1 = 12;
        prim->v2 = prim->v3 = 12 + 0xE0;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0xFF;
        prim->y0 = prim->y1 = 12;
        prim->y2 = prim->y3 = 12 + 0xE0;
        prim->r0 = prim->g0 = prim->b0 = 0x80;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);

        prim->priority = 0x1F9;
        prim->drawMode = DRAW_DEFAULT;

        for (otherEnt = &g_Entities[1], i = 1; i < 256; i++, otherEnt++) {
            if (otherEnt != self) {
                DestroyEntity(otherEnt);
            }
        }
        PLAYER.animSet = 0;
        D_8003C744 = 5;
        g_GpuBuffers[0].draw.clip.y = 0;
        g_GpuBuffers[0].draw.clip.h = 0xF0;
        g_GpuBuffers[1].draw.clip.y = 0;
        g_GpuBuffers[1].draw.clip.h = 0xF0;
        self->rotZ = 0;
        self->rotX = 0x100;
        self->ext.cutscenePhoto.cameraDistance = 0;
        self->ext.cutscenePhoto.rotationTimer = 0x20;

        g_api.PlaySfx(SFX_EXPLODE_A);
        self->step++;
        /* fallthrough */
    case 5:
        g_GpuBuffers[0].draw.r0 = 0;
        g_GpuBuffers[0].draw.g0 = 0;
        g_GpuBuffers[0].draw.b0 = 0;
        g_GpuBuffers[1].draw.r0 = 0;
        g_GpuBuffers[1].draw.g0 = 0;
        g_GpuBuffers[1].draw.b0 = 0;
        prim = self->ext.cutscenePhoto.prim;
        SetGeomScreen(0x400);
        SetGeomOffset(0x80, 0x80);
        rotVector.vx = 0;
        rotVector.vy = 0;
        rotVector.vz = self->rotZ;
        RotMatrix(&rotVector, &m);
        SetRotMatrix(&m);
        transVector.vx = 0;
        transVector.vy = 0;
        transVector.vz = 0x400;
        transVector.vz += self->ext.cutscenePhoto.cameraDistance;
        TransMatrix(&m, &transVector);
        SetTransMatrix(&m);
        gte_ldv3(&D_8018243C, &D_80182444, &D_8018244C);
        gte_rtpt();
        gte_stsxy3_gt3(prim);
        gte_ldv0(&D_80182454);
        gte_rtps();
        gte_stsxy(&prim->x3);

        if (!self->ext.cutscenePhoto.rotationTimer) {
            self->rotZ += 2;
            self->ext.cutscenePhoto.cameraDistance += 8;
        } else {
            self->ext.cutscenePhoto.rotationTimer--;
        }
        if (self->ext.cutscenePhoto.cameraDistance <= 0x600) {
            return;
        }
        self->step++;
        return;
    case 6:
        prim = self->ext.cutscenePhoto.prim;
        prim = prim->next;

        drawEnv = g_CurrentBuffer->draw;
        if (drawEnv.ofs[0] == 0) {
            prim->tpage = 0x100;
        } else {
            prim->tpage = 0x104;
        }
        prim->type = PRIM_GT4;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0xFF;
        prim->v0 = prim->v1 = 12;
        prim->v2 = prim->v3 = 12 + 0xE0;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0xFF;
        prim->y0 = prim->y1 = 12;
        prim->y2 = prim->y3 = 12 + 0xE0;
        prim->priority = 0x1FB;
        prim->drawMode = DRAW_DEFAULT;

        prim = prim->next;
        dr_env = g_api.func_800EDB08(prim);
        if (dr_env == NULL) {
            SetStep(12);
            return;
        }
        prim->type = PRIM_ENV;
        drawEnv.isbg = 1;
        drawEnv.r0 = 8;
        drawEnv.g0 = 8;
        drawEnv.b0 = 8;
        drawEnv.dtd = 1;
        clipRect.x = 0;
        clipRect.y = 0x100;
        clipRect.w = 0x100;
        clipRect.h = 0x100;
        drawEnv.clip = clipRect;
        drawEnv.ofs[0] = 0;
        drawEnv.ofs[1] = 0x100;
        SetDrawEnv(dr_env, &drawEnv);
        prim->priority = 0x1FA;
        prim->drawMode = DRAW_DEFAULT;

        prim = prim->next;
        dr_env = g_api.func_800EDB08(prim);
        if (dr_env == NULL) {
            SetStep(12);
            return;
        }
        prim->type = PRIM_ENV;
        prim->priority = 0x1FD;
        prim->drawMode = DRAW_UNK_800;

        prim = prim->next;
        prim->type = PRIM_TILE;
        prim->x0 = 0;
        prim->y0 = 0;
        prim->u0 = 0xFF;
        prim->v0 = 0xFF;
        prim->r0 = prim->g0 = prim->b0 = 8;
        prim->priority = 0x1FC;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        self->step++;
        return;
    case 7:
        prim = self->ext.cutscenePhoto.prim;
        prim->tpage = 0x110;
        prim->u0 = prim->x0;
        prim->u1 = prim->x1;
        prim->u2 = prim->x2;
        prim->u3 = prim->x3;
        prim->v0 = prim->y0;
        prim->v1 = prim->y1;
        prim->v2 = prim->y2;
        prim->v3 = prim->y3;
        prim->priority = 0x1FE;
        prim->drawMode = DRAW_DEFAULT;

        prim = prim->next;
        prim->drawMode = DRAW_HIDE;

        prim = prim->next;
        prim->type = PRIM_ENV;
        dr_env = (DR_ENV*)LOW(prim->r1);

        drawEnv = g_CurrentBuffer->draw;

        drawEnv.isbg = 0;
        drawEnv.dtd = 0;

        clipRect.x = 0;
        clipRect.y = 0x100;
        clipRect.w = 0x100;
        clipRect.h = 0x100;
        drawEnv.clip = clipRect;

        drawEnv.ofs[0] = 0;
        drawEnv.ofs[1] = 0x100;
        SetDrawEnv(dr_env, &drawEnv);
        prim->priority = 0x1FA;
        prim->drawMode = DRAW_DEFAULT;

        prim = prim->next;

        prim = prim->next;
        prim->type = PRIM_TILE;
        prim->x0 = 0x40;
        prim->y0 = 0x40;
        prim->u0 = 0x80;
        prim->v0 = 0x80;
        prim->r0 = prim->g0 = prim->b0 = 0;
        prim->priority = 0x1FC;
        prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
        self->animFrameIdx = 0;
        g_api.PlaySfx(NA_SE_CS_BURNING_PHOTOGRAPH);
        self->step++;
        /* fallthrough */
    case 8:
        if (self->animFrameDuration) {
            self->animFrameDuration--;
            return;
        }
        self->animFrameDuration = 4;
        // Ugh, this should have been a 2D array.
        newEntXY = &D_8018245C[0];
        newEntXY += self->animFrameIdx * 2;

        self->animFrameIdx++;
        if (newEntXY[0] == -1) {
            self->step++;
            return;
        }
        newEntX = newEntXY[0];
        newEntY = newEntXY[1];

        if (self->animFrameIdx & 1) {
            dualFlag = 0;
        } else {
            dualFlag = 1;
        }
        otherEnt = AllocEntity(self, (Entity*)&g_EvHwCardEnd);
        if (otherEnt != NULL) {
            CreateEntityFromCurrentEntity(E_ID_2D, otherEnt);
            otherEnt->posX.i.hi = newEntX;
            otherEnt->posY.i.hi = newEntY;
            otherEnt->facingLeft = dualFlag;
            otherEnt->params = 0;
        }

        otherEnt = AllocEntity(self, (Entity*)&g_EvHwCardEnd);
        if (otherEnt != NULL) {
            CreateEntityFromCurrentEntity(E_ID_2D, otherEnt);
            otherEnt->posX.i.hi = newEntX;
            otherEnt->posY.i.hi = newEntY + 0xC;
            otherEnt->facingLeft = dualFlag;
            otherEnt->params = 1;
        }
        break;
    case 9:
        prim = self->ext.cutscenePhoto.prim;
        prim = prim->next;
        prim->type = PRIM_G4;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0x100;
        prim->y0 = prim->y1 = 0;
        prim->y2 = prim->y3 = 0x100;
        prim->r0 = prim->g0 = prim->b0 = 0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0x1FF;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        self->step++;
        return;
    case 10:
        prim = self->ext.cutscenePhoto.prim;
        prim = prim->next;
        prim->r0 += 8;
        if (prim->r0 > 0xF0) {
            self->step++;
        }
        prim->g0 = prim->b0 = prim->r0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        return;
    case 11:
    case 12:
        g_GameEngineStep = Engine_10;
        g_MenuStep = 0;
        break;
    }
}

void EntityCutscenePhotographFire(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_801805D4);
        entity->animSet = ANIMSET_OVL(7);
        entity->unk5A = 0x57;
        entity->palette = 0x8285;
        entity->drawFlags = FLAG_DRAW_UNK8;
        entity->unk6C = 0x40;
        entity->flags &= ~FLAG_POS_CAMERA_LOCKED;
        if (entity->params) {
            entity->unk6C = 0x10;
            entity->zPriority = 0x1FB;
            entity->drawMode = DRAW_UNK_40 | DRAW_TPAGE;
        } else {
            entity->zPriority = 0x1FE;
            entity->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        }
    case 1:
        entity->posY.val -= FIX(1.0);
        if (AnimateEntity(D_801824CC, entity) == 0) {
            DestroyEntity(entity);
        }
        break;
    }
}
