// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo6.h"

extern s32 g_CutsceneFlags;
extern EInit g_EInitInteractable;

void func_us_801A367C(Entity* self) {
    Tilemap* unusedTilemap = &g_Tilemap;
    Entity* player = &PLAYER;
    s16 unusedX = player->posX.i.hi + g_Tilemap.scrollX.i.hi;
    s16 unusedY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        g_PauseAllowed = 0;
        g_unkGraphicsStruct.pauseEnemies = 1;
        player->facingLeft = 0;
        if (g_Status.wornEquipment[1] != ITEM_AXE_LORD_ARMOR) {
            player->animCurFrame = 0xBF;
        }
        player->posX.i.hi = 0x70;
        g_Player.padSim = 0;
        g_Player.demo_timer = 1;
        break;
    case 1:
        if (g_Status.wornEquipment[1] != ITEM_AXE_LORD_ARMOR) {
            player->animCurFrame = 0xBF;
        }
        player->posX.i.hi = 0x70;
        if (g_CutsceneFlags & 2) {
            self->step++;
        }
        g_Player.padSim = 0;
        g_Player.demo_timer = 1;
        break;
    case 2:
        g_PauseAllowed = 1;
        g_unkGraphicsStruct.pauseEnemies = 0;
        g_Entities[E_AFTERIMAGE_1].ext.afterImage.disableFlag = 1;
        DestroyEntity(self);
        break;
    }
}

void func_us_801A37B4(Entity* self) {
    Primitive* prim;
    s32 primIndex;

    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_G4, 1);
        if (primIndex != -1) {
            InitializeEntity(&g_EInitInteractable);
            self->flags |= 0x800000;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            
            prim->x0 = prim->x2 = 0;
            prim->x1 = prim->x3 = 0x100;
            prim->y0 = prim->y1 = 0;
            prim->y2 = prim->y3 = 0xF0;
            
            PCOL(prim) = 0xFF;
            prim->priority = 0x1F8;
            prim->drawMode = 0x55;
        }
        break;
    case 1:
        self->step++;
        break;
    case 2:
        prim = &g_PrimBuf[self->primIndex];
        PCOL(prim) -= 4;
        if (prim->r0 < 4) {
            DestroyEntity(self);
            g_CutsceneFlags |= 1;
        }
        break;
    }
}

void func_us_801A399C(Entity* self) {
    Primitive* prim;
    s32 primIndex;

    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_G4, 1);
        if (primIndex != -1) {
            InitializeEntity(&g_EInitInteractable);
            self->flags |= 0x800000;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            
            prim->x0 = prim->x2 = 0;
            prim->x1 = prim->x3 = 0x100;
            prim->y0 = prim->y1 = 0;
            prim->y2 = prim->y3 = 0xF0;
            
            PCOL(prim) = 0;
            prim->priority = 0x80;
            prim->drawMode = 0;
        }
        break;
    case 1:
        if(g_CutsceneFlags & 0x100){
            prim = &g_PrimBuf[self->primIndex];
            PCOL(prim) = 0xFF;
            prim->drawMode = 0x55;
            self->step++;
        }
        break;
    case 2:
        prim = &g_PrimBuf[self->primIndex];
        PCOL(prim) -= 4;
        if (prim->r0 < 4) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_us_801A3BE0(Entity* self) {
    Primitive* prim;
    s32 primIndex;

    switch (self->step) {                              /* irregular */
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_G4, 1);
        if (primIndex != -1) {
            InitializeEntity(&g_EInitInteractable);
            self->flags |= 0x800000;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            prim->x0 = prim->x2 = 0x60;
            prim->x1 = prim->x3 = 0xA0;
            prim->y0 = prim->y1 = 0x40;
            prim->y2 = prim->y3 = 0xC0;
            PCOL(prim) = 0xFF;
            prim->drawMode = 0x55;
            prim->priority = 0x82;
        }
        break;
    case 1:
        prim = &g_PrimBuf[self->primIndex];
        if (g_CutsceneFlags & 4) {
            PCOL(prim) -= 1;
            if (prim->r0 <= 0) {
                PCOL(prim) = 0;
                g_CutsceneFlags |= 0x200;
                self->step++;
            }
        }
        break;
    case 2:
        prim = &g_PrimBuf[self->primIndex];
        if (g_CutsceneFlags & 0x80) {
            PCOL(prim)++;
            if (prim->r0 > 0xC0) {
                g_CutsceneFlags |= 0x100;
            }
            if (prim->r0 > 0xFD) {
                PCOL(prim) = 0;
                prim->drawMode = 0;
                SetStep(3);
                g_api.PlaySfx(0x62F);
            }
        }
        break;
    case 3:
        prim = &g_PrimBuf[self->primIndex];
        prim->type = 3;
        
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0x100;
        prim->y0 = prim->y1 = 0x10;
        prim->y2 = prim->y3 = 0xF0;
        prim->priority = 0x7F;
        prim->drawMode = 0;
        if (self->poseTimer & 1) {
            prim->r0 = 0x80;
            prim->g0 = 0x80;
            prim->b0 = 0x80;
            prim->r1 = 0x80;
            prim->g1 = 0x80;
            prim->b1 = 0x80;
            prim->r2 = 0x80;
            prim->g2 = 0x80;
            prim->b2 = 0x80;
            prim->r3 = 0x80;
            prim->g3 = 0x80;
            prim->b3 = 0x80;
        } else {
            prim->r0 = 0;
            prim->g0 = 0;
            prim->b0 = 0;
            prim->r1 = 0;
            prim->g1 = 0;
            prim->b1 = 0;
            prim->r2 = 0;
            prim->g2 = 0;
            prim->b2 = 0;
            prim->r3 = 0;
            prim->g3 = 0;
            prim->b3 = 0;
        }
        self->poseTimer++;
        if (self->poseTimer > 8) {
            DestroyEntity(self);
            g_CutsceneFlags |= 0x20;
        }
        break;
    }
}

void func_us_801A4028(Entity* self) {
    switch (self->step) {                              /* irregular */
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0x8001;
        self->palette = 0x200;
        self->unk5A = 0x48;
        self->animCurFrame = 0x35;
        self->drawFlags = 3;
        self->scaleX = 0x100;
        self->scaleY = 0x100;
        self->zPriority = 0x81;
        break;
    case 1:
        if (g_CutsceneFlags & 0x80) {
            self->step++;
            self->velocityY = 0x8000;
        }
        break;
    case 2:
        self->velocityY -= 0x180;
        MoveEntity();
        self->scaleX--;
        self->scaleY--;
        if (g_CutsceneFlags & 0x100) {
            DestroyEntity(self);
        }
        break;
    }
}

INCLUDE_ASM("boss/rbo6/nonmatchings/unk_2367C", func_us_801A9208_from_bo6);
