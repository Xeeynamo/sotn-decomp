// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rbo6/rbo6.h"

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
extern EInit g_EInitInteractable;
extern s32 g_EndingVariant;
extern s32 D_psp_E_UNK_32;
s32 D_pspeu_0926C058;
u32 D_pspeu_0926C050;
s32 D_pspeu_0926C048;


void func_us_801A4594(Entity* self) {
    Entity* other;
    Primitive* prim;
    s32 primIndex;
    s32 temp;
    s32 tempBool;

    FntPrint("end_step %x\n", self->step);
    g_Player.padSim = 0;
    g_Player.demo_timer = 0x80;
    g_Player.status |= 0x100000;
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
        self->flags |= 0x800000;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        while (prim != NULL) {
            prim->drawMode = 8;
            prim = prim->next;
        }
        if (g_Player.status & 2) {
            g_Player.padSim = 0;
        } else if (g_Player.status & 4) {
            g_Player.padSim = PAD_L1;
        } else if (g_Player.status & 1) {
            g_Player.padSim = PAD_R1;
        }
    case 1:
        prim = self->ext.prim;
        prim->type = 4;
        prim->tpage = 0x1A;
        prim->clut = 0x19F;
        prim->clut = 0x2E2;
        
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x3F;
        prim->v0 = prim->v1 = 0xC0;
        prim->v2 = prim->v3 = 0xFF;
       
        prim->x0 =  prim->x2 = 0x80;
        prim->x1 = prim->x3 = 0x80;
        prim->y0 = prim->y1 = 0x80;
        prim->y1 = prim->y3 = 0x80;
        
        prim->r0 = prim->g0 = prim->b0 = 0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0x90;
        prim->drawMode = 0x37;
        prim = prim->next;
        self->ext.ILLEGAL.u32[2] = (u32) prim;
        prim->type = 3;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0x100;
        prim->y0 = prim->y1 = 0x10;
        prim->y2 = prim->y3 = 0xF0;
        prim->priority = 0x50;
        prim->drawMode = 8;
        prim = prim->next;
        self->ext.ILLEGAL.u32[3] = (u32) prim;
        prim->type = 3;
        
        prim->x0 = prim->x2 = 0x40;
        prim->x1 = prim->x3 = 0;
        prim->y0 = prim->y1 = 0x10;
        prim->y2 = prim->y3 = 0xF0;
        prim->priority = 0x90;
        prim->drawMode = 8;
        prim = prim->next;
        prim->type = 3;
        prim->x0 = prim->x2 = 0xC0;
        prim->x1 = prim->x3 = 0x100;
        prim->y0 = prim->y1 = 0x10;
        prim->y2 = prim->y3 = 0xF0;
        prim->priority = 0x90;
        prim->drawMode = 8;
        prim = prim->next;
        self->ext.ILLEGAL.u32[4] = (u32) prim;
        prim->type = 3;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0x100;
        prim->y0 = prim->y1 = 0x10;
        prim->y2 = prim->y3 = 0xF0;
        prim->priority = 0x1FF;
        prim->drawMode = 8;
        prim = prim->next;
        self->step += 1;
        /* fallthrough */
    case 2:
        prim = self->ext.prim;
        prim->x0 = prim->x2 -= 3;        
        prim->x1 = prim->x3 += 3;
        prim->y0 =  prim->y1 -= 3;               
        prim->y2 = prim->y3 += 3;
        temp = prim->r0;
        temp += 8;
        if (temp > 0x60) {
            temp = 0x60;
            self->ext.ILLEGAL.s16[2] = 0x10;
            g_api.PlaySfx(0x62F);
            self->step += 1;
        }
        
        prim->g0 = prim->b0 = prim->r0 = temp;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        break;
    case 3:
        prim = self->ext.prim;
        if (self->ext.ILLEGAL.s16[2] & 1) {
            prim->x0 = prim->x2 -= 1;
            prim->x1 = prim->x3 += 1;
            prim->y0 = prim->y1 -= 1;
            prim->y2 = prim->y3 += 1;
        }
        if (!--self->ext.ILLEGAL.s16[2]) {
            self->step += 1;
        }
        break;
    case 4:
        prim = self->ext.prim;
        tempBool = PrimDecreaseBrightness(prim, 4);

        if (tempBool == 0) {
            prim->drawMode = 8;
            self->step += 1;
        }
        prim = (Primitive*)self->ext.ILLEGAL.u32[2];
        prim->drawMode = 4;
        prim->r0 += 4;
        prim->g0 += 3;
        prim->b0 += 2;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        D_pspeu_0926C048 = 1;
        /* fallthrough */
    case 5:
        prim = (Primitive*)self->ext.ILLEGAL.u32[3];
        prim->drawMode = 0x31;
        temp = prim->r1;
        if (temp < 0xC0) {
            temp += 4;
        } else {
            self->step += 1;
        }
        
        prim->g1 = prim->b1 = prim->r1 = temp;
        LOW(prim->r3) = LOW(prim->r1);

        prim = prim->next;
        prim->drawMode = 0x31;
        prim->g1 = prim->b1 = prim->r1 = temp;
        LOW(prim->r3) = LOW(prim->r1);
        if ((self->step == 5) && (D_pspeu_0926C048 < 4) && !(g_Timer & 0xF)) {
            D_pspeu_0926C048 += 1;
        }
        break;
    case 6:
        prim = (Primitive*)self->ext.ILLEGAL.u32[2];
        prim->drawMode = 4;
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
        prim = (Primitive*)self->ext.ILLEGAL.u32[3];
        prim->drawMode = 0x31;
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
        prim->drawMode = 0x31;
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
        prim = (Primitive*)self->ext.ILLEGAL.u32[3];
        tempBool += DecreaseBrightness(prim, 2);
        prim = prim->next;
        tempBool += DecreaseBrightness(prim, 2);
        D_pspeu_0926C058 = 0x80 - prim->r0 / 2;
        other = AllocEntity(&g_Entities[0x40], &g_Entities[256]);
        if (other != NULL) {
            CreateEntityFromCurrentEntity(D_psp_E_UNK_32, other);
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
            D_pspeu_0926C050 = 0x80;
        } else {
            D_pspeu_0926C050 = 0x20;
        }
        self->step += 1;
        /* fallthrough */
    case 9:
        g_Player.padSim = D_pspeu_0926C050;
        prim = (Primitive*)self->ext.ILLEGAL.u32[4];
        prim->drawMode = 0x31;
        tempBool = DecreaseBrightness(prim, 4);
        if (tempBool == 0) {
            self->step += 1;
        }
        return;
    case 10:
        prim = (Primitive*)self->ext.ILLEGAL.u32[4];
        prim->drawMode = 0;
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
    if (D_pspeu_0926C048 != 0) {
        if (!(g_Timer & 7)) {
            if (D_pspeu_0926C058 != 0) {
                g_api.PlaySfxVolPan(0x69D, D_pspeu_0926C058, 0);
            } else {
                g_api.PlaySfx(0x69D);
            }
        }
        if (!(g_Timer & 1)) {
            other = AllocEntity(&g_Entities[0x40], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromCurrentEntity(D_psp_E_UNK_32, other);
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

void func_us_801A4F14(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 intRandy;
    s32 yVar;
    s32 xVar;
    s32 width;
    s16* yPtr;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        self->animCurFrame = 0;
        intRandy = Random() % D_pspeu_0926C048;
        self->hitboxWidth = (intRandy + 2);
        intRandy++;
        self->velocityY = 0xFFFE8000 - ((Random() % (intRandy + 2)) << 0x11);
        self->ext.ILLEGAL.u32[5] = -0x1000 - ((Random() % (intRandy + 1)) * 0x3000);
        self->opacity = (((Random() % intRandy) * 8) + 0x20);
        if (intRandy < D_pspeu_0926C048 / 2) {
            self->zPriority = 0x54;
        } else {
            self->zPriority = 0x90;
        }
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 7);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= 0x800000;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
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
        prim->drawMode = 0x37;
        prim = prim->next;
        for(i = 0; i < 4; i++) {
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
            prim->drawMode = 0x37;
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
        prim->drawMode = 0x37;
        prim = prim->next;
        self->ext.ILLEGAL.u32[2] = (u32) prim;
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
        prim->drawMode = 0x77;
        if ((self->hitboxWidth) < 4) {
            prim->drawMode = 8;
        }
        yPtr = &self->ext.ILLEGAL.s16[0x10];
        for(i = 0; i < 6; i++) {
            *yPtr = self->posY.i.hi;
            yPtr ++;
        }
        break;
    case 1:
        MoveEntity();
        self->velocityY += self->ext.ILLEGAL.u32[5];
        break;
    }
    yPtr = &self->ext.ILLEGAL.s16[0x15];
    for(i = 0; i < 5; i++) {
        yPtr[0] = yPtr[-1];
        yPtr --;
    }
    yPtr = &self->ext.ILLEGAL.s16[0x10];
    *yPtr = self->posY.i.hi;
    width = self->hitboxWidth;
    prim = self->ext.prim;
    xVar = self->posX.i.hi;
    yVar = self->posY.i.hi - self->hitboxWidth;
    prim->x0 = xVar - width;
    prim->x1 = xVar + width;
    prim->y0 = prim->y1 = yVar;
    prim = (Primitive*)self->ext.ILLEGAL.u32[2];
    prim->x0 = (xVar - (width * 2));
    prim->x1 = (xVar + (width * 2));
    prim->y0 = prim->y1 = yVar - width;
    prim = self->ext.prim;
    // redundant, yPtr already holds this
    yPtr = &self->ext.ILLEGAL.s16[0x10];
    for(i = 0; i < 5; i++) {
        yVar = *yPtr;
        prim->x2 = xVar - width;
        prim->x3 = xVar + width;
        prim->y2 = prim->y3 = yVar;
        prim->drawMode = 0x35;
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
    prim->drawMode = 0x35;
    prim = prim->next;
    prim = (Primitive*)self->ext.ILLEGAL.u32[2];
    prim->x2 = (xVar - (width * 2));
    prim->x3 = (xVar + (width * 2));
    prim->y2 = prim->y3 = yVar + self->hitboxWidth * 2;
    if (yVar < 0x10) {
        DestroyEntity(self);
    }
}
