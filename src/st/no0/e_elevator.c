// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

#ifdef VERSION_PSP
extern s32 E_ID(ID_29);
#endif

u8 GetPlayerCollisionWith(Entity* self, u16 w, u16 h, u16 flags);

static u8 anim0[] = {8, 3, 4, 4, 4,  5, 4,  6,  4,  7,  4,
                     8, 4, 9, 2, 10, 1, 11, 16, 10, -1, 0};
static u8 anim1[] = {4, 10, 4, 9, 4, 8, 4,  7, 4, 6,  4,
                     5, 4,  4, 4, 3, 2, 12, 4, 3, -1, 0};

static s16 func_us_801C1F98(Primitive* prim, s16 dx) {
    prim->drawMode = DRAW_UNK02;
    prim->v0 = prim->v1 = 0x50;
    prim->v2 = prim->v3 = 0x60;
    prim->y0 = prim->y1 = 0x2C;
    prim->y2 = prim->y3 = 0x3C;
    prim->u0 = prim->u2 = 2;
    prim->x0 = prim->x2 = dx;
    dx += 0x20;

    if (dx > 0xB0) {
        dx = dx - 0xB0;
        prim->u1 = prim->u3 = 0x22 - dx;
        prim->x1 = prim->x3 = 0xB0;
        dx = 0;
    } else {
        prim->u1 = prim->u3 = 0x22;
        prim->x1 = prim->x3 = dx;
    }
    return dx;
}

static s16 func_us_801C2044(Primitive* prim, s16 dy) {
    prim->drawMode = DRAW_UNK02;
    prim->u0 = prim->u2 = 0x50;
    prim->u1 = prim->u3 = 0x60;
    prim->x0 = prim->x2 = g_CurrentEntity->posX.i.hi - 8;
    prim->x1 = prim->x3 = g_CurrentEntity->posX.i.hi + 8;
    prim->v2 = prim->v3 = 0x26;
    prim->y2 = prim->y3 = dy;
    dy -= 0x20;

    if (dy < 0x44) {
        dy = 0x44 - dy;
        prim->v0 = prim->v1 = dy + 6;
        prim->y0 = prim->y1 = 0x44;

        prim = prim->next;
        prim->drawMode = DRAW_UNK02;
        prim->v0 = prim->v1 = 0x50;
        prim->v2 = prim->v3 = 0x60;
        prim->y0 = prim->y1 = 0x2C;
        prim->y2 = prim->y3 = 0x3C;
        prim->u0 = prim->u2 = 0x22 - dy;
        prim->u1 = prim->u3 = 0x22;
        prim->x0 = prim->x2 = g_CurrentEntity->posX.i.hi;
        prim->x1 = prim->x3 = g_CurrentEntity->posX.i.hi + dy;
    } else {
        prim->v0 = prim->v1 = 6;
        prim->y0 = prim->y1 = dy;
    }
    return dy;
}

void func_us_801C2184(Entity* self) {
    Entity* player = &PLAYER;
    Entity* parent;
    Primitive* prim;
    s32 primIndex;
    s16 dx, dy;
    u8 var_s6;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitElevator);
        self->animCurFrame = 3;
        self->zPriority = player->zPriority + 0xC;

        parent = (self - 1);
        CreateEntityFromCurrentEntity(E_ID(ID_29), parent);
        parent->params = 1;

        parent = (self - 2);
        CreateEntityFromCurrentEntity(E_ID(ID_29), parent);
        parent->params = 2;

        primIndex = g_api.AllocPrimitives(PRIM_GT4, 12);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.cenElevator.prim = prim;
            prim->tpage = 0x12;
            prim->clut = 0x223;
            prim->u0 = prim->u2 = 0x28;
            prim->u1 = prim->u3 = 0x38;
            prim->v0 = prim->v1 = 0x28;
            prim->v2 = prim->v3 = 0x38;
            prim->priority = 0x6B;
            prim->drawMode = DRAW_HIDE;

            prim = prim->next;
            while (prim != NULL) {
                prim->tpage = 0x12;
                prim->clut = 0x223;
                prim->priority = 0x6A;
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
            return;
        }

        if (player->posY.i.hi > 0xC0) {
            self->posY.i.hi = player->posY.i.hi;
            player->posX.i.hi = self->posX.i.hi;
            self->animCurFrame = 10;
            g_Entities[E_AFTERIMAGE_1].ext.afterImage.disableFlag = 1;
            SetStep(2);
        }
        break;

    case 1:
        var_s6 = (self - 1)->ext.cenElevator.unk80;
        if (var_s6) {
            dx = self->posX.i.hi - player->posX.i.hi;
            if (g_pads[0].pressed & PAD_DOWN && abs(dx) < 8) {
#ifdef VERSION_PSP
                if (F(player->velocityX).i.hi != 0) {
                    break;
                }
#endif
                g_Entities[E_AFTERIMAGE_1].ext.afterImage.disableFlag = 1;
                g_Player.demo_timer = 2;
                g_Player.padSim = PAD_DOWN;
#ifndef VERSION_PSP
                player->velocityX = 0;
                player->velocityY = 0;
#endif
                self->step = 3;
            }
        }
        break;

    case 3:
        g_Player.demo_timer = 2;
        g_Player.padSim = 0;
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(anim0, self)) {
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s += 1;
            }
            if (!self->poseTimer && self->pose == 4) {
                g_api.PlaySfx(SFX_LEVER_METAL_BANG);
            }
            break;

        case 1:
            self->posY.val += FIX(0.5);
            player->posY.i.hi++;
            if ((g_Timer & 0xF) == 0) {
                PlaySfxPositional(SFX_METAL_CLANG_A);
            }
            break;
        }
        break;

    case 2:
        g_Player.demo_timer = 2;
        g_Player.padSim = 0;
        switch (self->step_s) {
        case 0:
            self->posY.val -= FIX(0.5);
            dy = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if (dy == 0x94) {
                self->step_s++;
            }
            if ((g_Timer & 0xF) == 0) {
                PlaySfxPositional(SFX_METAL_CLANG_A);
            }
            break;

        case 1:
            if (!AnimateEntity(anim1, self)) {
                self->pose = 0;
                self->poseTimer = 0;
                g_Entities[E_AFTERIMAGE_1].ext.afterImage.disableFlag = 0;
                self->step_s = 0;
                self->step = 1;
            }
            if (!self->poseTimer && self->pose == 4) {
                g_api.PlaySfx(SFX_LEVER_METAL_BANG);
            }
            break;
        }
        break;
    }

    prim = self->ext.cenElevator.prim;
    prim->x0 = prim->x2 = self->posX.i.hi - 8;
    prim->x1 = prim->x3 = self->posX.i.hi + 8;
    prim->y2 = prim->y3 = self->posY.i.hi - 0x1F;
    prim->y0 = prim->y1 = prim->y2 - 0x10;
    prim->drawMode = DRAW_UNK02;

    prim = prim->next;
    dy = self->posY.i.hi - 0x28;

    while (prim != NULL) {
        dy = func_us_801C2044(prim, dy);
        prim = prim->next;

        if (dy <= 0x20)
            break;
    }

    prim = prim->next;
    dx = self->posX.i.hi + dy;

    while (prim != NULL) {
        dx = func_us_801C1F98(prim, dx);
        prim = prim->next;

        if (!dx)
            break;
    }

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }

    if (abs(self->posY.i.hi) > 0x180) {
        DestroyEntity(self);
    }
}

void func_us_801C26B8(Entity* self) {
    Entity* entity = &self[self->params];
    u8 collision;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitElevator);
        if (self->params & 0x10) {
            self->animCurFrame = self->params & 15;
            self->zPriority = 0x6A;
            self->step = 2;
        } else {
            self->animCurFrame = 0;
        }
        break;

    case 1:
        self->posX.i.hi = entity->posX.i.hi;
        if (self->params == 1) {
            self->posY.i.hi = entity->posY.i.hi + 35;
            collision = GetPlayerCollisionWith(self, 12, 8, 4);
        } else {
            self->posY.i.hi = entity->posY.i.hi - 24;
            collision = GetPlayerCollisionWith(self, 12, 8, 6);
        }
        self->ext.cenElevator.unk80 = collision;
        break;
    }
}

void func_us_801C27A4(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s16 yOffset;
    Entity* player = &PLAYER;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitElevator);
        self->animCurFrame = 3;
        self->zPriority = player->zPriority + 2;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 12);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.cenElevator.prim = prim;
            while (prim != NULL) {
                prim->tpage = 0x12;
                prim->u0 = prim->u2 = 0x50;
                prim->u1 = prim->u3 = 0x60;
                prim->v0 = prim->v1 = 6;
                prim->v2 = prim->v3 = 0x26;
                prim->clut = 0x223;
                prim->priority = 0x6A;
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
            return;
        }

        if (player->posY.i.hi > 192) {
            self->posY.i.hi = player->posY.i.hi;
            player->posX.i.hi = self->posX.i.hi;
            self->animCurFrame = 10;
            g_Entities[E_AFTERIMAGE_1].ext.afterImage.disableFlag = 1;
            SetStep(2);
        } else {
            self->posY.i.hi = player->posY.i.hi;
            player->posX.i.hi = self->posX.i.hi;
            self->animCurFrame = 10;
            g_Entities[E_AFTERIMAGE_1].ext.afterImage.disableFlag = 1;
            SetStep(3);
        }
        break;

    case 3:
        g_Player.demo_timer = 2;
        g_Player.padSim = 0;
        self->posY.val += FIX(0.5);
        player->posY.i.hi = self->posY.i.hi + 4;
        g_Player.vram_flag = VRAM_FLAG_UNK40 | TOUCHING_GROUND;
        break;

    case 2:
        g_Player.demo_timer = 2;
        g_Player.padSim = 0;
        self->posY.val -= FIX(0.5);
        player->posY.i.hi = self->posY.i.hi + 4;
        g_Player.vram_flag = VRAM_FLAG_UNK40 | TOUCHING_GROUND;
        break;
    }

    yOffset = self->posY.i.hi - 0x28;
    prim = self->ext.cenElevator.prim;
    while (prim != NULL) {
        prim->drawMode = DRAW_DEFAULT;
        prim->x0 = prim->x2 = self->posX.i.hi - 8;
        prim->x1 = prim->x3 = self->posX.i.hi + 8;
        prim->y2 = prim->y3 = yOffset;
        yOffset -= 0x20;
        prim->y0 = prim->y1 = yOffset;
        prim = prim->next;
    }

    // Code mistake? Don't think this code can ever run
    // but it's present in the PSP
    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }

    if (abs(self->posY.i.hi) > 0x180) {
        DestroyEntity(self);
    }
}
