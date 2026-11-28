// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo6.h"

static s32 DecreaseBrightness(Primitive* prim, u32 brightnessOffset) {
    s32 newColor;
    s32 i;
    s32 j;
    u8* rgbVal;
    u8* rPtr;
    s32 ret;

    ret = 0;

    // Starting at prim->r0, update r0,g0,b0
    // Then we skip 0xC bytes of the prim to take us to r1,g1,b1
    // and so on for r2,g2,b2 and r3,g3,b3
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

#if TARGET == TARGET_PSP
extern s32 E_ID(RISING_SPARK);
#endif

extern EInit g_EInitInteractable;
extern s32 g_EndingVariant;

s32 sparksSpeed = 0;
s32 unused = 0;
u32 dirToMiddle = 0;
s32 soundVolume = 0;
// After Dracula has been defeated, and the last cutscene plays with Dracula,
// This entity is created to run the effects after the fight.
void EntityConcludeFight(Entity* self) {
    Entity* other;
    Primitive* prim;
    s32 primIndex;
    s32 temp;
    s32 tempBool;

    FntPrint("end_step %x\n", self->step);
    g_Player.padSim = PAD_NONE;
    g_Player.demo_timer = 0x80;
    g_Player.status |= PLAYER_STATUS_UNK100000;
    g_PauseAllowed = 0;
    g_unkGraphicsStruct.pauseEnemies = 1;
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x20);
        if (primIndex == -1) {
            self->step = 0;
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.concludeFight.prim1 = prim;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        if (g_Player.status & PLAYER_STATUS_MIST_FORM) {
#if TARGET == TARGET_PSP
            g_Player.padSim = PAD_NONE;
#else
            g_Player.padSim = PAD_MIST;
#endif
        } else if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
            g_Player.padSim = PAD_WOLF;
        } else if (g_Player.status & PLAYER_STATUS_BAT_FORM) {
            g_Player.padSim = PAD_BAT;
        }
    case 1:
        prim = self->ext.concludeFight.prim1;
        prim->type = PRIM_GT4; // already gt4 from allocprimitives but sure
        prim->tpage = 0x1A;
        prim->clut = 0x19F; // and let's assign clut twice, why the hell not
        prim->clut = 0x2E2;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x3F;
        prim->v0 = prim->v1 = 0xC0;
        prim->v2 = prim->v3 = 0xFF;
        prim->x0 = prim->x2 = 0x80;
        prim->x1 = prim->x3 = 0x80;
        prim->y0 = prim->y1 = 0x80;
        prim->y1 = prim->y3 = 0x80; // probably a typo here, should be y2
        prim->r0 = prim->g0 = prim->b0 = 0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0x90;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim = prim->next;

        self->ext.concludeFight.prim2 = prim;
        prim->type = PRIM_G4;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0x100;
        prim->y0 = prim->y1 = 0x10;
        prim->y2 = prim->y3 = 0xF0;
        prim->priority = 0x50;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;

        self->ext.concludeFight.prim3 = prim;
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

        self->ext.concludeFight.prim4 = prim;
        prim->type = PRIM_G4;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0x100;
        prim->y0 = prim->y1 = 0x10;
        prim->y2 = prim->y3 = 0xF0;
        prim->priority = 0x1FF;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        self->step += 1;
        /* fallthrough */
    case 2:
        prim = self->ext.concludeFight.prim1;
        prim->x0 = prim->x2 -= 3;
        prim->x1 = prim->x3 += 3;
        prim->y0 = prim->y1 -= 3;
        prim->y2 = prim->y3 += 3;
        temp = prim->r0;
        temp += 8;
        if (temp > 0x60) {
            temp = 0x60;
            self->ext.concludeFight.timer = 0x10;
            g_api.PlaySfx(SFX_WEAPON_APPEAR);
            self->step += 1;
        }

        prim->g0 = prim->b0 = prim->r0 = temp;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        break;
    case 3:
        prim = self->ext.concludeFight.prim1;
        if (self->ext.concludeFight.timer & 1) {
            prim->x0 = prim->x2 -= 1;
            prim->x1 = prim->x3 += 1;
            prim->y0 = prim->y1 -= 1;
            prim->y2 = prim->y3 += 1;
        }
        if (!--self->ext.concludeFight.timer) {
            self->step += 1;
        }
        break;
    case 4:
        prim = self->ext.concludeFight.prim1;
        tempBool = PrimDecreaseBrightness(prim, 4);

        if (tempBool == 0) {
            prim->drawMode = DRAW_HIDE;
            self->step += 1;
        }
        prim = self->ext.concludeFight.prim2;
        prim->drawMode = DRAW_COLORS;
        prim->r0 += 4;
        prim->g0 += 3;
        prim->b0 += 2;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        sparksSpeed = 1;
        /* fallthrough */
    case 5:
        prim = self->ext.concludeFight.prim3;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        temp = prim->r1;
        if (temp < 0xC0) {
            temp += 4;
        } else {
            self->step += 1;
        }

        prim->g1 = prim->b1 = prim->r1 = temp;
        LOW(prim->r3) = LOW(prim->r1);

        prim = prim->next;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        prim->g1 = prim->b1 = prim->r1 = temp;
        LOW(prim->r3) = LOW(prim->r1);
        if ((self->step == 5) && (sparksSpeed < 4) && !(g_Timer & 0xF)) {
            sparksSpeed += 1;
        }
        break;
    case 6:
        prim = self->ext.concludeFight.prim2;
        prim->drawMode = DRAW_COLORS;
        if ((prim->r0) < 0xA0) {
            prim->r0 += 4;
        }
        if ((prim->g0) < 0x80) {
            prim->g0 += 3;
        }
        if ((prim->g0) < 0x30) {
            prim->b0 += 2;
        }
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        tempBool = 1;
        prim = self->ext.concludeFight.prim3;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        temp = prim->r1;
        temp++;
        if (temp > 0xFF) {
            temp = 0xFF;
        }
        prim->g1 = prim->b1 = prim->r1 = temp;
        LOW(prim->r3) = LOW(prim->r1);
        if (prim->x0 < 0x80) {
            prim->x0 = prim->x2 += 1;
            tempBool = 0;
        }
        prim = prim->next;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        prim->g1 = prim->b1 = prim->r1 = temp;
        LOW(prim->r3) = LOW(prim->r1);
        if (prim->x0 > 0x80) {
            prim->x0 = prim->x2 -= 1;
            tempBool = 0;
        }
        if (tempBool != 0) {
            self->step += 1;
        }
        break;
    case 7:
        tempBool = 0;
        prim = self->ext.concludeFight.prim3;
        tempBool += DecreaseBrightness(prim, 2);
        prim = prim->next;
        tempBool += DecreaseBrightness(prim, 2);
        soundVolume = 0x80 - prim->r0 / 2;
        other = AllocEntity(&g_Entities[64], &g_Entities[256]);
        if (other != NULL) {
            CreateEntityFromCurrentEntity(E_ID(RISING_SPARK), other);
            temp = Random();
            if (temp < 0x20) {
                temp += 0x60;
            }
            if (temp > 0xE0) {
                temp -= 0x80;
            }
            other->posX.i.hi = temp;
            other->posY.i.hi = 0xF0;
            other->params = 0;
        }
        if (tempBool == 0) {
            self->step += 1;
        }
        break;
    case 8:
        other = &PLAYER;
        if (other->posX.i.hi > 0x80) {
            dirToMiddle = PAD_LEFT;
        } else {
            dirToMiddle = PAD_RIGHT;
        }
        self->step += 1;
        /* fallthrough */
    case 9:
        g_Player.padSim = dirToMiddle;
        prim = self->ext.concludeFight.prim4;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        tempBool = DecreaseBrightness(prim, 4);
        if (tempBool == 0) {
            self->step += 1;
        }
        return;
    case 10:
        prim = self->ext.concludeFight.prim4;
        prim->drawMode = DRAW_DEFAULT;
        tempBool = PrimDecreaseBrightness(prim, 8);
        if (tempBool == 0) {
            self->step += 1;
        }
        return;
    case 11:
        g_PauseAllowed = 1;
        g_unkGraphicsStruct.pauseEnemies = 0;
        if (g_RoomCount > 1846) {
            g_EndingVariant = ENDING_GOOD;
        } else {
            g_EndingVariant = ENDING_BEST;
        }
        g_GameState = Game_Ending;
        g_GameStep = 0;
        self->step += 1;
        /* fallthrough */
    case 12:
        g_PauseAllowed = 1;
        g_unkGraphicsStruct.pauseEnemies = 0;
        return;
    }
    if (sparksSpeed != 0) {
        if (!(g_Timer & 7)) {
            if (soundVolume != 0) {
                g_api.PlaySfxVolPan(SFX_MAGIC_SWITCH, soundVolume, 0);
            } else {
                g_api.PlaySfx(SFX_MAGIC_SWITCH);
            }
        }
        if (!(g_Timer & 1)) {
            other = AllocEntity(&g_Entities[64], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromCurrentEntity(E_ID(RISING_SPARK), other);
                temp = Random();
                if (temp < 0x20) {
                    temp += 0x60;
                }
                if (temp > 0xE0) {
                    temp -= 0x80;
                }
                other->posX.i.hi = temp;
                other->posY.i.hi = 0xF0;
                other->params = 0;
            }
        }
    }
}

extern EInit g_EInitParticle;

// Fuzzy gold shape, rises up as the screen fades to white
void EntityRisingSpark(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 initRandy;
    s32 yVar;
    s32 xVar;
    s32 width;
    s16* yPtr;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        self->animCurFrame = 0;
        // The sparks speed up as the sequence plays out.
        // This variable increases to accomplish that.
        initRandy = Random() % sparksSpeed;
        self->hitboxWidth = (initRandy + 2);
        initRandy++;
        self->velocityY = FIX(-1.5) - ((Random() % (initRandy + 2)) * FIX(2));
        self->ext.concludeFight.accelY =
            -0x1000 - ((Random() % (initRandy + 1)) * 0x3000);
        self->opacity = (((Random() % initRandy) * 8) + 0x20);
        if (initRandy < sparksSpeed / 2) {
            self->zPriority = 0x54;
        } else {
            self->zPriority = 0x90;
        }
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 7);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.concludeFight.prim1 = prim;
        prim->tpage = 0x1A;
        prim->clut = 0x2EC;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x40;
        prim->v0 = prim->v1 = 0xC0;
        prim->v2 = prim->v3 = 0xE0;
        prim->r0 = prim->g0 = prim->b0 = self->opacity;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = self->zPriority;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim = prim->next;

        for (i = 0; i < 4; i++) {
            prim->tpage = 0x1A;
            prim->clut = 0x2EC;
            prim->u0 = prim->u2 = 0;
            prim->u1 = prim->u3 = 0x40;
            prim->v0 = prim->v1 = 0xE0;
            prim->v2 = prim->v3 = 0xE2;
            prim->r0 = prim->g0 = prim->b0 = self->opacity;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = self->zPriority + 1;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;
            prim = prim->next;
        }
        prim->tpage = 0x1A;
        prim->clut = 0x2EC;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x40;
        prim->v0 = prim->v1 = 0xE0;
        prim->v2 = prim->v3 = 0xFF;
        prim->r0 = prim->g0 = prim->b0 = self->opacity;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = self->zPriority;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim = prim->next;

        self->ext.concludeFight.prim2 = prim;
        prim->tpage = 0x1A;
        prim->clut = 0x15F;
        prim->clut = 0x2EC;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x3F;
        prim->v0 = prim->v1 = 0xC0;
        prim->v2 = prim->v3 = 0xFF;
        prim->r0 = prim->g0 = prim->b0 = self->opacity + 0x20;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = self->zPriority;
        prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                         DRAW_UNK02 | DRAW_TRANSP;
        if (self->hitboxWidth < 4) {
            prim->drawMode = DRAW_HIDE;
        }
        yPtr = &self->ext.concludeFight.unk9C[0];
        for (i = 0; i < 6; i++) {
            *yPtr = self->posY.i.hi;
            yPtr++;
        }
        break;
    case 1:
        MoveEntity();
        self->velocityY += self->ext.concludeFight.accelY;
        break;
    }
    yPtr = &self->ext.concludeFight.unk9C[5];
    for (i = 0; i < 5; i++) {
        yPtr[0] = yPtr[-1];
        yPtr--;
    }
    yPtr = &self->ext.concludeFight.unk9C[0];
    *yPtr = self->posY.i.hi;
    width = self->hitboxWidth;
    prim = self->ext.concludeFight.prim1;
    xVar = self->posX.i.hi;
    yVar = self->posY.i.hi - self->hitboxWidth;
    prim->x0 = xVar - width;
    prim->x1 = xVar + width;
    prim->y0 = prim->y1 = yVar;
    prim = self->ext.concludeFight.prim2;
    prim->x0 = (xVar - (width * 2));
    prim->x1 = (xVar + (width * 2));
    prim->y0 = prim->y1 = yVar - width;

    prim = self->ext.concludeFight.prim1;
    // redundant, yPtr already holds this
    yPtr = &self->ext.concludeFight.unk9C[0];
    for (i = 0; i < 5; i++) {
        yVar = *yPtr;
        prim->x2 = xVar - width;
        prim->x3 = xVar + width;
        prim->y2 = prim->y3 = yVar;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        prim = prim->next;
        prim->x0 = xVar - width;
        prim->x1 = xVar + width;
        prim->y0 = prim->y1 = yVar;
        yPtr++;
    }
    yVar += self->hitboxWidth;
    prim->x2 = xVar - width;
    prim->x3 = xVar + width;
    prim->y2 = prim->y3 = yVar;
    prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
    prim = prim->next;
    prim = self->ext.concludeFight.prim2;
    prim->x2 = (xVar - (width * 2));
    prim->x3 = (xVar + (width * 2));
    prim->y2 = prim->y3 = yVar + self->hitboxWidth * 2;
    if (yVar < 0x10) {
        DestroyEntity(self);
    }
}
