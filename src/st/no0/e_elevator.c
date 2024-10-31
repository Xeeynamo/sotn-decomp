// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

s16 func_us_801C1F98(Primitive* prim, s16 arg1) {
    s16 ret = arg1;
    s16 temp_v0;

    prim->x2 = arg1;
    prim->x0 = arg1;
    ret += 0x20;
    prim->drawMode = DRAW_UNK02;
    prim->v0 = prim->v1 = 0x50;
    prim->v2 = prim->v3 = 0x60;
    prim->y0 = prim->y1 = 0x2C;
    prim->y2 = prim->y3 = 0x3C;
    prim->u0 = prim->u2 = 2;

    if (ret > 0xB0) {
        temp_v0 = 0xB2 - arg1;
        prim->u1 = prim->u3 = temp_v0;
        ret = 0;
        prim->x1 = prim->x3 = 0xB0;
    } else {
        prim->u1 = prim->u3 = 0x22;
        prim->x1 = prim->x3 = ret;
    }
    return ret;
}

s16 func_us_801C2044(Primitive* prim, s16 offset) {
    prim->drawMode = DRAW_UNK02;
    prim->u0 = prim->u2 = 0x50;
    prim->u1 = prim->u3 = 0x60;
    prim->x0 = prim->x2 = g_CurrentEntity->posX.i.hi - 8;
    prim->x1 = prim->x3 = g_CurrentEntity->posX.i.hi + 8;
    prim->v2 = prim->v3 = 0x26;
    prim->y2 = prim->y3 = offset;
    offset -= 0x20;

    if (offset < 0x44) {
        offset = 0x44 - offset;
        prim->v0 = prim->v1 = offset + 6;
        prim->y0 = prim->y1 = 0x44;

        prim = prim->next;
        prim->drawMode = DRAW_UNK02;
        prim->v0 = prim->v1 = 0x50;
        prim->v2 = prim->v3 = 0x60;
        prim->y0 = prim->y1 = 0x2C;
        prim->y2 = prim->y3 = 0x3C;
        prim->u0 = prim->u2 = 0x22 - offset;
        prim->u1 = prim->u3 = 0x22;
        prim->x0 = prim->x2 = g_CurrentEntity->posX.i.hi;
        prim->x1 = prim->x3 = g_CurrentEntity->posX.i.hi + offset;
    } else {
        prim->v0 = prim->v1 = 6;
        prim->y0 = prim->y1 = offset;
    }
    return offset;
}

extern u16 g_EInitElevator[];
extern u8 D_us_80180FC0[];
extern u8 D_us_80180FD8[];
void func_us_801C2184(Entity* self) {
    Entity* player = &PLAYER;
    Entity* grandparent;
    Entity* parent;
    Primitive* prim;
    s32 fake = 0;
    s32 primIndex;
    s16 offset;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitElevator);
        self->animCurFrame = 3;
        self->zPriority = player->zPriority + 0xC;

        // TODO: Define this entity in no0.h - func_us_801C26B8
        parent = (self - 1);
        CreateEntityFromCurrentEntity(0x29U, parent);
        parent->params = 1;

        grandparent = (self - 2);
        CreateEntityFromCurrentEntity(0x29U, grandparent);
        grandparent->params = 2;

        primIndex = g_api.AllocPrimitives(PRIM_GT4, 12);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.prim = prim;
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
            self->animCurFrame = 0xA;
            g_Entities[UNK_ENTITY_1].ext.entSlot1.unk0 = 1;
            SetStep(2);
        }

        break;
    case 1:
        if ((self - 1)->ext.cenElevator.unk80) {
            offset = self->posX.i.hi - player->posX.i.hi;
            if (g_pads[0].pressed & PAD_DOWN && abs(offset) < 8) {
                g_Entities[UNK_ENTITY_1].ext.entSlot1.unk0 = 1;
                g_Player.D_80072EFC = 2;
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
        g_Player.D_80072EFC = 2;
        g_Player.padSim = 0;
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_80180FC0, self)) {
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                self->step_s += 1;
            }
            if (!self->animFrameDuration && self->animFrameIdx == 4) {
                g_api.PlaySfx(SFX_LEVER_METAL_BANG);
            }
            break;
        case 1:
            self->posY.val += FIX(0.5);
            player->posY.i.hi++;
            if (!(g_Timer & 0xF)) {
                PlaySfxPositional(SFX_METAL_CLANG_A);
            }
            break;
        }
        break;
    case 2:
        g_Player.D_80072EFC = 2;
        g_Player.padSim = 0;
        switch (self->step_s) {
        case 0:
            self->posY.val -= FIX(0.5);
            offset = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if (offset == 0x94) {
                self->step_s++;
            }
            if (!(g_Timer & 0xF)) {
                PlaySfxPositional(SFX_METAL_CLANG_A);
            }
            break;
        case 1:
            if (!AnimateEntity(D_us_80180FD8, self)) {
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                g_Entities[UNK_ENTITY_1].ext.entSlot1.unk0 = 0;
                self->step_s = 0;
                self->step = 1;
            }
            if (!self->animFrameDuration && self->animFrameIdx == 4) {
                g_api.PlaySfx(SFX_LEVER_METAL_BANG);
            }
            break;
        }
        break;
    }

    prim = self->ext.prim;
    prim->x0 = prim->x2 = self->posX.i.hi - 8;
    prim->x1 = prim->x3 = self->posX.i.hi + 8;
    prim->y2 = prim->y3 = self->posY.i.hi - 0x1F;
    prim->y0 = prim->y1 = prim->y2 - 0x10;
    prim->drawMode = DRAW_UNK02;

    prim = prim->next;
    offset = self->posY.i.hi - 0x28;

    while (prim != NULL) {
        offset = func_us_801C2044(prim, offset);
        prim = prim->next;

        if (offset <= 0x20)
            break;
    }

    prim = prim->next;
    offset += self->posX.i.hi;

    while (prim != NULL) {
        offset = func_us_801C1F98(prim, offset);
        prim = prim->next;

        if (!offset)
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
    s32 step = self->step;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitElevator);
        if (self->params & 16) {
            self->animCurFrame = self->params & 15;
            self->zPriority = 0x6A;
            self->step = 2;
            return;
        }
        self->animCurFrame = 0;
        break;

    case 1:
        self->posX.i.hi = entity->posX.i.hi;
        if (self->params == 1) {
            self->posY.i.hi = entity->posY.i.hi + 35;
            self->ext.cenElevator.unk80 =
                GetPlayerCollisionWith(self, 12, 8, 4);
        } else {
            self->posY.i.hi = entity->posY.i.hi - 24;
            self->ext.cenElevator.unk80 =
                GetPlayerCollisionWith(self, 12, 8, 6);
        }
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
            self->ext.prim = prim;
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
            g_Entities[1].ext.entSlot1.unk0 = 1;
            SetStep(2);
        } else {
            self->posY.i.hi = player->posY.i.hi;
            player->posX.i.hi = self->posX.i.hi;
            self->animCurFrame = 10;
            g_Entities[1].ext.entSlot1.unk0 = 1;
            SetStep(3);
        }

        break;
    case 3:
        g_Player.D_80072EFC = 2;
        g_Player.padSim = 0;
        self->posY.val += FIX(0.5);
        player->posY.i.hi = self->posY.i.hi + 4;
        g_Player.pl_vram_flag = 0x41;
        break;
    case 2:
        g_Player.D_80072EFC = 2;
        g_Player.padSim = 0;
        self->posY.val -= FIX(0.5);
        player->posY.i.hi = self->posY.i.hi + 4;
        g_Player.pl_vram_flag = 0x41;
        break;
    }

    yOffset = self->posY.i.hi - 0x28;
    prim = self->ext.prim;
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
