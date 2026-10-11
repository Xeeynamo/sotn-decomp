// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rbo6/rbo6.h"

extern EInit g_EInitBreakable;
extern u8* D_pspeu_09256C38[];
extern u8 D_pspeu_09256C58[];
extern u16 D_pspeu_09256C60[];
extern u8 D_pspeu_0926C040[];
extern u8 D_pspeu_09256C70[];
extern EInit g_EInitInteractable;
extern s32 D_pspeu_0926C048;
extern s32 D_pspeu_0926C050;
extern s32 D_pspeu_0926C058;
extern s32 E_ID(UNK_32);

void EntityBreakable(Entity* self) {
    Entity* entity;
    u16 breakableType;

    breakableType = self->params >> 12;
    if (self->step) {
        AnimateEntity(D_pspeu_09256C38[breakableType], self);
        if (self->hitParams) {
            g_api.PlaySfx(SFX_CANDLE_HIT);
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, entity);
                entity->params = D_pspeu_0926C040[breakableType];
            }
            ReplaceBreakableWithItemDrop(self);
        }
    } else {
        InitializeEntity(g_EInitBreakable);
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 20;
        self->blendMode = D_pspeu_09256C70[breakableType];
        self->hitboxHeight = D_pspeu_09256C58[breakableType];
        self->animSet = D_pspeu_09256C60[breakableType];
    }
}

s32 DecreaseBrightness(Primitive* prim, s32 brightnessOffset) {
    s32 newColor;
    s32 i;
    s32 j;
    u8* rgbVal;
    u8* rPtr;
    s32 ret;

    ret = 0;
    rPtr = &prim->r0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            rgbVal = &rPtr[j];
            newColor = *rgbVal;
            newColor += brightnessOffset;
            if (newColor > 0xFF) {
                newColor = 0xFF;
            } else {
                ret |= 1;
            }
            *rgbVal = newColor;
        }
        rPtr += 0xC;
    }
    return ret;
}

void func_us_801A4594(Entity* self) {
    Primitive* prim;
    s32 brightness;
    Entity* entity;
    s32 finished;
    s32 primIndex;

    FntPrint("end_step %x\n", self->step);
    g_Player.padSim = 0;
    g_Player.demo_timer = 0x80;
    g_Player.status |= PLAYER_STATUS_UNK100000;
    g_PauseAllowed = false;
    g_unkGraphicsStruct.pauseEnemies = true;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x20);
        if (primIndex == -1) {
            self->step = 0;
            return;
        }
        LOW(self->flags) |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801BA290.unk7C = prim;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        if (g_Player.status & PLAYER_STATUS_MIST_FORM) {
            g_Player.padSim = 0;
        } else if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
            g_Player.padSim = PAD_WOLF;
        } else if (g_Player.status & PLAYER_STATUS_BAT_FORM) {
            g_Player.padSim = PAD_BAT;
        }
        // fallthrough
    case 1:
        prim = self->ext.et_801BA290.unk7C;
        prim->type = PRIM_GT4;
        prim->tpage = 0x1A;
        prim->clut = 0x19F;
        prim->clut = 0x2E2;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x3F;
        prim->v0 = prim->v1 = 0xC0;
        prim->v2 = prim->v3 = 0xFF;
        prim->x0 = prim->x2 = 0x80;
        prim->x1 = prim->x3 = 0x80;
        prim->y0 = prim->y1 = 0x80;
        prim->y1 = prim->y3 = 0x80;
        PGREY(prim, 0) = 0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0x90;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim = prim->next;
        self->ext.et_801BA290.unk84 = prim;
        prim->type = PRIM_G4;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0x100;
        prim->y0 = prim->y1 = 0x10;
        prim->y2 = prim->y3 = 0xF0;
        prim->priority = 0x50;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        self->ext.et_801BA290.unk88 = prim;
        prim->type = PRIM_G4;
        prim->x0 = prim->x2 = 0x40;
        prim->x1 = prim->x3 = 0;
        prim->y0 = prim->y1 = 0x10;
        prim->y2 = prim->y3 = 0xF0;
        prim->priority = 0x90;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        prim->type = PRIM_G4;
        prim->x0 = prim->x2 = 0xC0;
        prim->x1 = prim->x3 = 0x100;
        prim->y0 = prim->y1 = 0x10;
        prim->y2 = prim->y3 = 0xF0;
        prim->priority = 0x90;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        self->ext.et_801BA290.unk8C = prim;
        prim->type = PRIM_G4;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0x100;
        prim->y0 = prim->y1 = 0x10;
        prim->y2 = prim->y3 = 0xF0;
        prim->priority = 0x1FF;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        self->step++;
        // fallthrough
    case 2:
        prim = self->ext.et_801BA290.unk7C;
        prim->x0 = prim->x2 -= 3;
        prim->x1 = prim->x3 += 3;
        prim->y0 = prim->y1 -= 3;
        prim->y2 = prim->y3 += 3;
        brightness = prim->r0;
        brightness += 8;
        if (brightness > 0x60) {
            brightness = 0x60;
            self->ext.et_801BA290.unk80 = 0x10;
            g_api.PlaySfx(SFX_WEAPON_APPEAR);
            self->step++;
        }
        prim->g0 = prim->b0 = prim->r0 = brightness;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        break;
    case 3:
        prim = self->ext.et_801BA290.unk7C;
        if (self->ext.et_801BA290.unk80 & 1) {
            prim->x0 = prim->x2 -= 1;
            prim->x1 = prim->x3 += 1;
            prim->y0 = prim->y1 -= 1;
            prim->y2 = prim->y3 += 1;
        }
        if (!--self->ext.et_801BA290.unk80) {
            self->step++;
        }
        break;
    case 4:
        prim = self->ext.et_801BA290.unk7C;
        finished = PrimDecreaseBrightness(prim, 4);
        if (!finished) {
            prim->drawMode = DRAW_HIDE;
            self->step++;
        }
        prim = self->ext.et_801BA290.unk84;
        prim->drawMode = DRAW_COLORS;
        prim->r0 += 4;
        prim->g0 += 3;
        prim->b0 += 2;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        D_pspeu_0926C048 = 1;
        // fallthrough
    case 5:
        prim = self->ext.et_801BA290.unk88;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        brightness = prim->r1;
        if (brightness < 0xC0) {
            brightness += 4;
        } else {
            self->step++;
        }
        prim->g1 = prim->b1 = prim->r1 = brightness;
        LOW(prim->r3) = LOW(prim->r1);
        prim = prim->next;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        prim->g1 = prim->b1 = prim->r1 = brightness;
        LOW(prim->r3) = LOW(prim->r1);
        if (self->step == 5 && D_pspeu_0926C048 < 4 && !(g_Timer & 0xF)) {
            D_pspeu_0926C048++;
        }
        break;
    case 6:
        prim = self->ext.et_801BA290.unk84;
        prim->drawMode = DRAW_COLORS;
        if (prim->r0 < 0xA0) {
            prim->r0 += 4;
        }
        if (prim->g0 < 0x80) {
            prim->g0 += 3;
        }
        if (prim->g0 < 0x30) {
            prim->b0 += 2;
        }
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        finished = 1;
        prim = self->ext.et_801BA290.unk88;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        brightness = prim->r1;
        brightness++;
        if (brightness > 0xFF) {
            brightness = 0xFF;
        }
        prim->g1 = prim->b1 = prim->r1 = brightness;
        LOW(prim->r3) = LOW(prim->r1);
        if (prim->x0 < 0x80) {
            prim->x0 = prim->x2 += 1;
            finished = 0;
        }
        prim = prim->next;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        prim->g1 = prim->b1 = prim->r1 = brightness;
        LOW(prim->r3) = LOW(prim->r1);
        if (prim->x0 > 0x80) {
            prim->x0 = prim->x2 -= 1;
            finished = 0;
        }
        if (finished) {
            self->step++;
        }
        break;
    case 7:
        finished = 0;
        prim = self->ext.et_801BA290.unk88;
        finished += DecreaseBrightness(prim, 2);
        prim = prim->next;
        finished += DecreaseBrightness(prim, 2);
        D_pspeu_0926C058 = 0x80 - prim->r0 / 2;
        entity = AllocEntity(&g_Entities[64], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromCurrentEntity(E_ID(UNK_32), entity);
            brightness = Random();
            if (brightness < 0x20) {
                brightness += 0x60;
            }
            if (brightness > 0xE0) {
                brightness -= 0x80;
            }
            entity->posX.i.hi = brightness;
            entity->posY.i.hi = 0xF0;
            entity->params = 0;
        }
        if (!finished) {
            self->step++;
        }
        break;
    case 8:
        entity = &PLAYER;
        if (entity->posX.i.hi > 0x80) {
            D_pspeu_0926C050 = PAD_LEFT;
        } else {
            D_pspeu_0926C050 = PAD_RIGHT;
        }
        self->step++;
        // fallthrough
    case 9:
        g_Player.padSim = D_pspeu_0926C050;
        prim = self->ext.et_801BA290.unk8C;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        finished = DecreaseBrightness(prim, 4);
        if (!finished) {
            self->step++;
        }
        return;
    case 10:
        prim = self->ext.et_801BA290.unk8C;
        prim->drawMode = DRAW_DEFAULT;
        finished = PrimDecreaseBrightness(prim, 8);
        if (!finished) {
            self->step++;
        }
        return;
    case 11:
        g_PauseAllowed = true;
        g_unkGraphicsStruct.pauseEnemies = false;
        if (g_RoomCount > 0x736) {
            D_800978B4 = 3;
        } else {
            D_800978B4 = 5;
        }
        g_GameState = Game_Ending;
        g_GameStep = Play_Reset;
        self->step++;
        // fallthrough
    case 12:
        g_PauseAllowed = true;
        g_unkGraphicsStruct.pauseEnemies = false;
        return;
    }

    if (D_pspeu_0926C048) {
        if (!(g_Timer & 7)) {
            if (D_pspeu_0926C058) {
                g_api.PlaySfxVolPan(SFX_MAGIC_SWITCH, D_pspeu_0926C058, 0);
            } else {
                g_api.PlaySfx(SFX_MAGIC_SWITCH);
            }
        }
        if (!(g_Timer & 1)) {
            entity = AllocEntity(&g_Entities[64], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromCurrentEntity(E_ID(UNK_32), entity);
                brightness = Random();
                if (brightness < 0x20) {
                    brightness += 0x60;
                }
                if (brightness > 0xE0) {
                    brightness -= 0x80;
                }
                entity->posX.i.hi = brightness;
                entity->posY.i.hi = 0xF0;
                entity->params = 0;
            }
        }
    }
}
