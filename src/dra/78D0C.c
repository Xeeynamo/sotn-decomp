// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"
#include "objects.h"
#include "sfx.h"

// number appears and moves to HP meter, probably for healing effects
/* PSP version: func_psp_09125048 */
void EntityNumberMovesToHpMeter(Entity* self) {
    const int PrimCountA = 4;
    const int PrimCountB = 16;
    Primitive* prim;
    s16 x_to_meter;
    s16 y_to_meter;
    s16 temp_v0_10;
    s32 temp_s1_2;
    u16 tens;
    u16 hundreds;
    u16 thousands;
    s16 a0;
    s16 s7;
    s16 s5;
    s32 i;
    s32 var_v0;
    s16 offset_x;
    u16 offset_y;
    u16 temp_s0;
    s32 temp;
    s32 sp3C = -1;

    switch (self->step) {
    case 0:
        temp_s0 = self->ext.hpNumMove.number;
        self->primIndex = AllocPrimitives(PRIM_GT4, PrimCountA + PrimCountB);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags =
            FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS | FLAG_UNK_10000;
        self->ext.hpNumMove.unk8C = 0;
        self->ext.hpNumMove.unk8E = 2;
        self->ext.hpNumMove.unk90 = 8;

        tens = temp_s0 / 10;
        self->ext.hpNumMove.digits[0] = temp_s0 % 10;
        if (tens > 0) {
            self->ext.hpNumMove.unk84++;
            hundreds = tens / 10;
            self->ext.hpNumMove.digits[1] = tens % 10;
            if (hundreds > 0) {
                self->ext.hpNumMove.unk84++;
                thousands = hundreds / 10;
                self->ext.hpNumMove.digits[2] = hundreds % 10;
                if (thousands > 0) {
                    self->ext.hpNumMove.unk84++;
                    self->ext.hpNumMove.digits[3] = thousands % 10;
                }
            }
        }

        // iterate through all 0x14 prims created by AllocPrimitives in two
        // batches
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < PrimCountA; i++) {
            prim->clut = 0x1B2;
            if (self->ext.hpNumMove.number == 0) {
                prim->clut = 0x1B4;
            }
            if (self->ext.hpNumMove.type == 1) {
                prim->clut = 0x1B8;
            }
            if (self->ext.hpNumMove.type == 2) {
                prim->clut = 0x1B6;
            }
            prim->tpage = 0x1A;
            prim->priority = 0x1B8;
            prim->drawMode = DRAW_DEFAULT;
            temp = self->ext.hpNumMove.digits[i] * 8;
            if (self->ext.hpNumMove.digits[i]) {
                var_v0 = temp - 8;
            } else {
                var_v0 = temp + 72;
            }
            prim->u0 = var_v0 + 32;
            prim->v0 = 64;
            prim->u1 = var_v0 + 40;
            prim->v1 = 64;
            prim->u2 = var_v0 + 32;
            prim->v2 = 73;
            prim->u3 = var_v0 + 40;
            prim->v3 = 73;
            if (self->ext.hpNumMove.unk84 < i) {
                prim->drawMode = DRAW_HIDE;
            }
            prim = prim->next;
        }
        for (i = 0; i < PrimCountB; i++) {
            prim->type = PRIM_TILE;
            prim->r0 = 0xFF;
            prim->g0 = 0x40;
            prim->b0 = 0x40;
            if (self->ext.hpNumMove.number == 0) {
                prim->r0 = 0x40;
                prim->g0 = 0x40;
                prim->b0 = 0xFF;
            }
            if (self->ext.hpNumMove.type == 1) {
                prim->r0 = 0x40;
                prim->g0 = 0xFF;
                prim->b0 = 0x40;
            }
            if (self->ext.hpNumMove.type == 2) {
                prim->r0 = 0xFF;
                prim->g0 = 0x40;
                prim->b0 = 0xFF;
            }
            prim->priority = 0x1B8;
            prim->drawMode = DRAW_HIDE | DRAW_UNK02;

            prim->v0 = 1;
            prim->u0 = 1;
            prim = prim->next;
        }

        self->step++;
        break;
    case 1:
        self->ext.hpNumMove.unk8C++;
        self->ext.hpNumMove.unk8E++;
        if (self->ext.hpNumMove.type != 2) {
            self->posY.i.hi--;
        }
        if (--self->ext.hpNumMove.unk90 == 0) {
            self->ext.hpNumMove.unk90 = 8;
            self->step++;
        }
        break;
    case 2:
        self->ext.hpNumMove.unk8C--;
        self->ext.hpNumMove.unk8E--;
        if (self->ext.hpNumMove.unk8C == 4) {
            self->ext.hpNumMove.unk90 = 4;
            self->step++;
        }
        break;
    case 3:
        self->ext.hpNumMove.unk8C++;
        self->ext.hpNumMove.unk8E++;
        if (self->ext.hpNumMove.type != 2) {
            self->posY.i.hi--;
        }
        if (--self->ext.hpNumMove.unk90 == 0) {
            self->ext.hpNumMove.unk90 = 3;
            self->step++;
        }
        break;
    case 4:
        self->ext.hpNumMove.unk8C--;
        self->ext.hpNumMove.unk8E--;
        if (self->ext.hpNumMove.unk8C == 4) {
            self->ext.hpNumMove.unk90 = 24;
            self->step++;
        }
        break;
    case 5:
        if (--self->ext.hpNumMove.unk90 == 0) {
            y_to_meter = self->posY.i.hi - 0x46;
            x_to_meter = self->posX.i.hi - 0xD;
            self->ext.hpNumMove.angleToMeter =
                ratan2(-y_to_meter, x_to_meter) & 0xFFF;
            self->ext.hpNumMove.distToMeter =
                SquareRoot0(SQ(x_to_meter) + SQ(y_to_meter));
            self->ext.hpNumMove.unk90 = 0x10;
            self->ext.hpNumMove.unk98 = 0;
            self->step++;
        }
        break;
    case 6:
        if (self->ext.hpNumMove.unk8C != 2) {
            self->ext.hpNumMove.unk8C--;
            self->ext.hpNumMove.unk8E--;
        }
        sp3C = (--self->ext.hpNumMove.unk90);
        temp_s0 = self->ext.hpNumMove.angleToMeter;
        temp_s1_2 = self->ext.hpNumMove.distToMeter * sp3C / 16;
        self->posX.i.hi =
            13 + (((rcos((s16)temp_s0) >> 4) * (s16)temp_s1_2) >> 8);
        self->posY.i.hi =
            70 - (((rsin((s16)temp_s0) >> 4) * (s16)temp_s1_2) >> 8);
        temp_v0_10 = self->ext.hpNumMove.unk98 + 0x100;
        self->ext.hpNumMove.unk98 = temp_v0_10;
        self->posX.i.hi += rcos(temp_v0_10) >> 9;
        self->posY.i.hi -= rsin(self->ext.hpNumMove.unk98) >> 9;
        if (self->ext.hpNumMove.unk90 == 0) {
            if (self->ext.hpNumMove.type != 2) {
                self->step++;
                break;
            }
            DestroyEntity(self);
            return;
        }
        break;
    case 7:
    case 9:
        self->ext.hpNumMove.unk8C++;
        self->ext.hpNumMove.unk8E++;
        if (self->ext.hpNumMove.unk8C == 7) {
            self->ext.hpNumMove.unk90 = 0x18;
            self->step++;
        }
        break;
    case 8:
        if (self->ext.hpNumMove.unk8C != 4) {
            self->ext.hpNumMove.unk8C--;
            self->ext.hpNumMove.unk8E--;
        } else {
            self->step++;
        }
        break;
    case 10:
        if (self->ext.hpNumMove.unk8C != 4) {
            self->ext.hpNumMove.unk8C--;
            self->ext.hpNumMove.unk8E--;
        }
        if (--self->ext.hpNumMove.unk90 == 0) {
            self->step++;
        }
        break;
    case 11:
        self->ext.hpNumMove.unk92 += 2;
        self->posX.i.hi -= 2;
        if (!(--self->ext.hpNumMove.unk90 & 2)) {
            self->ext.hpNumMove.unk8E--;
        }
        if (self->ext.hpNumMove.unk8E == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    offset_x = self->ext.hpNumMove.unk8C;
    offset_y = self->ext.hpNumMove.unk8E;
    if (self->step != 0xB) {
        self->ext.hpNumMove.unk92 = self->posX.i.hi;
    }
    s5 = self->posX.i.hi + (offset_x * self->ext.hpNumMove.unk84);
    s7 = self->ext.hpNumMove.unk92 + (offset_x * self->ext.hpNumMove.unk84);
    a0 = self->posY.i.hi - 0x10;

    // iterate through all 0x14 prims created by AllocPrimitives in two batches
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < PrimCountA; i++) {
        prim->x0 = s5 - offset_x;
        prim->y0 = a0 - offset_y;
        prim->x1 = s5 + offset_x;
        prim->y1 = a0 - offset_y;
        prim->x2 = s7 - offset_x;
        prim->y2 = a0 + offset_y;
        prim->x3 = s7 + offset_x;
        prim->y3 = a0 + offset_y;
        s5 -= (offset_x * 2) - 3;
        s7 -= (offset_x * 2) - 3;
        prim = prim->next;
    }
    for (i = 0; i < PrimCountB; i++) {
        if (prim->r1) {
            if (--prim->g1 == 0) {
                prim->drawMode = DRAW_HIDE;
            }
            prim->y0++;
        } else if (sp3C == i) {
            prim->drawMode &= ~DRAW_HIDE;
            prim->x0 = self->posX.i.hi;
            prim->y0 = self->posY.i.hi;
            prim->r1++;
            prim->g1 = 0xC;
        }
        prim = prim->next;
    }
}

// "Guard" text displays on screen

typedef struct {
    u8 left;
    u8 top;
    u8 right;
    u8 bottom;
    u16 clut;
    u16 mode;
} GuardTextControl;
extern GuardTextControl D_800ACFEC[];

GuardTextControl* func_psp_09125DB8(GuardTextControl*, s32);

void EntityGuardText(Entity* self) {
    Primitive* firstPrim;
    Primitive* prim;
    Primitive* nextprim;
    s16 xPos;
    s16 yPos;
    s32 hider_ID;
    s32 i;
    u8 lowerParams;
    u8 upperParams;
    s16 halfWidth;
    s16 halfHeight;
#ifdef VERSION_PSP
    GuardTextControl sp40;
    GuardTextControl sp38;
#endif
    GuardTextControl* params_gtc; // Chosen via self->params
    GuardTextControl* fixed_gtc;  // Chosen by fixed offsets 5 and 6

    upperParams = self->params >> 8;
    lowerParams = self->params & 0xFF;
#ifdef VERSION_PSP
    params_gtc = func_psp_09125DB8(&sp40, upperParams);
#else
    params_gtc = &D_800ACFEC[upperParams];
#endif
    hider_ID = -1;
    FntPrint("str_y:%02x", self->ext.guardText.str_y);
    switch (self->step) {
    case 0:
        self->flags =
            FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_UNK_20000 | FLAG_UNK_10000;
        self->step++;
        return;
    case 1:
        if ((g_Player.pl_vram_flag & TOUCHING_GROUND) || (g_Player.unk04 & 1)) {
            self->step++;
        }
        return;
    case 2:
        self->ext.guardText.str_y = PLAYER.posY.val + FIX(32);
        if (self->ext.guardText.str_y > FIX(0xE0)) {
            self->ext.guardText.str_y = FIX(0xD8);
        }
        self->ext.guardText.str_x = PLAYER.posX.val;
        self->ext.guardText.unk98 = FIX(0x78);

        if (params_gtc->mode == 2) {
            self->ext.guardText.str_x += FIX(-6);
            self->ext.guardText.unk98 = FIX(0x78);
        }
        if (params_gtc->mode == 3) {
            self->ext.guardText.str_x += FIX(32);
            self->ext.guardText.unk98 = FIX(0xB0);
        }
        self->primIndex = AllocPrimitives(PRIM_GT4, 18);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        // Would have been better to do |= FLAG_HAS_PRIMS
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS |
                      FLAG_UNK_20000 | FLAG_UNK_10000;
        self->ext.guardText.timer = 0x38;
        self->ext.guardText.halfHeight = 0;
        self->ext.guardText.halfWidth = FIX_FRAC(self->ext.guardText.unk98) =
            (params_gtc->right - params_gtc->left) / 2;
        self->ext.guardText.angle = 0;
        for (i = 0, prim = &g_PrimBuf[self->primIndex]; prim != NULL; i++,
            prim = prim->next) {
            prim->drawMode = DRAW_HIDE | DRAW_UNK02;
            if (i >= 2) {
                prim->type = PRIM_TILE;
                prim->r0 = 0x80;
                prim->g0 = 0x80;
                prim->b0 = 0x80;
                prim->priority = 0x1B8;
                prim->u0 = prim->v0 = 1;
            }
        }
        self->step++;

        break;
    case 3:
        self->ext.guardText.halfHeight =
            ((rsin(self->ext.guardText.angle) * 2) >> 0xC) + 4;
        if (self->ext.guardText.angle > 0x1000) {
            self->ext.guardText.angle = 0x1000;
        }
        self->ext.guardText.angle += 0x80;
        if (--self->ext.guardText.timer == 0) {
            self->velocityX = FIX(6.0);
            self->step++;
        }
        break;
    case 4:
        self->velocityX += FIX(1);
        self->ext.guardText.str_x += self->velocityX;
        if (self->ext.guardText.halfHeight > 1) {
            self->ext.guardText.halfHeight--;
        }
        self->ext.guardText.halfWidth += 5;
        if (self->ext.guardText.str_x > FIX(0x180)) {
            self->ext.guardText.str_y = FIX(0x20);
            self->ext.guardText.str_x = FIX(0x180);
            self->velocityX = FIX(-10);
            self->ext.guardText.halfWidth = 0x1E;
            self->step++;
        }
        self->ext.guardText.timer++;
        break;
    case 5:
        if (upperParams == 0) {
            DestroyEntity(self);
            return;
        }

        self->ext.guardText.str_x += self->velocityX;
        self->ext.guardText.timer++;

        hider_ID = self->ext.guardText.timer & 0xF;

        if (self->ext.guardText.halfWidth > 12) {
            self->ext.guardText.halfWidth -= 5;
        }
        if (self->ext.guardText.str_x < self->ext.guardText.unk98) {
            self->ext.guardText.halfWidth = FIX_FRAC(self->ext.guardText.unk98);
            self->ext.guardText.str_x = self->ext.guardText.unk98;
            self->ext.guardText.timer = 0x60;
            self->ext.guardText.angle = 0;
            PlaySfx(SFX_GUARD_TINK);
            self->step++;
        }
        break;
    case 6:
        self->ext.guardText.halfHeight =
            ((rsin(self->ext.guardText.angle) * 2) >> 0xC) + 4;
        self->ext.guardText.angle += 0x80;
        if (self->ext.guardText.angle > 0x1000) {
            self->ext.guardText.angle = 0x1000;
        }
        if (--self->ext.guardText.timer == 0) {
            self->velocityX = FIX(-6);
            self->step++;
        }
        break;
    case 7:
        self->velocityX += FIX(-1);
        self->ext.guardText.str_x += self->velocityX;
        self->ext.guardText.timer++;
        hider_ID = self->ext.guardText.timer & 0xF;
        if (self->ext.guardText.halfHeight > 1) {
            self->ext.guardText.halfHeight--;
        }

        self->ext.guardText.halfWidth += 5;

        if (self->ext.guardText.str_x < FIX(-128)) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    xPos = FIX_TO_I(self->ext.guardText.str_x);
    yPos = FIX_TO_I(self->ext.guardText.str_y);

    halfWidth = self->ext.guardText.halfWidth;
    halfHeight = self->ext.guardText.halfHeight;
    firstPrim = prim = &g_PrimBuf[self->primIndex];

    prim->u0 = prim->u2 = params_gtc->left;
    prim->u1 = prim->u3 = params_gtc->right;
    prim->v0 = prim->v1 = params_gtc->top;
    prim->v2 = prim->v3 = params_gtc->bottom;
    prim->x0 = prim->x2 = xPos - halfWidth;
    prim->x1 = prim->x3 = xPos + halfWidth;
    prim->y0 = prim->y1 = yPos - halfHeight;
    prim->y2 = prim->y3 = yPos + halfHeight;
    prim->tpage = 0x1A;
    prim->clut = params_gtc->clut;
    prim->priority = 0x1B8;
    prim->drawMode = DRAW_UNK_100;
    prim = prim->next;
    if (params_gtc->mode == 2) {
#ifdef VERSION_PSP
        fixed_gtc = func_psp_09125DB8(&sp38, 5);
#else
        fixed_gtc = &D_800ACFEC[5];
#endif
        nextprim = prim->next;
        *prim = *firstPrim;
        prim->next = nextprim;
        prim->u0 = prim->u2 = fixed_gtc->left;
        prim->u1 = prim->u3 = fixed_gtc->right;
        prim->v0 = prim->v1 = fixed_gtc->top;
        prim->v2 = prim->v3 = fixed_gtc->bottom;
        prim->x0 = prim->x2 = firstPrim->x1;
        prim->x1 = prim->x3 =
            prim->x0 + (fixed_gtc->right - fixed_gtc->left) +
            ((self->ext.guardText.halfWidth -
              FIX_FRAC(self->ext.guardText.unk98)) *
             2);
    }
    if (params_gtc->mode == 3) {
#ifdef VERSION_PSP
        fixed_gtc = func_psp_09125DB8(&sp38, 6);
#else
        fixed_gtc = &D_800ACFEC[6];
#endif

        nextprim = prim->next;
        *prim = *firstPrim;
        prim->next = nextprim;

        prim->u0 = prim->u2 = fixed_gtc->left;
        prim->u1 = prim->u3 = fixed_gtc->right;
        prim->v0 = prim->v1 = fixed_gtc->top;
        prim->v2 = prim->v3 = fixed_gtc->bottom;
        prim->x1 = prim->x3 = firstPrim->x0 - 3;
        prim->x0 = prim->x2 =
            (prim->x1 - (fixed_gtc->right - fixed_gtc->left)) -
            ((self->ext.guardText.halfWidth -
              FIX_FRAC(self->ext.guardText.unk98)) *
             2);
    }
    prim = prim->next;
    for (i = 0; i < 16; i++) {
        if (prim->r1) {
            if (--prim->g1 == 0) {
                prim->drawMode = DRAW_HIDE;
                prim->r1 = 0;
            }
            prim->y0++;
        } else if (hider_ID == i) { // One prim in this loop will get this case
            prim->drawMode &= ~DRAW_HIDE;
            prim->x0 = xPos;
            prim->y0 = yPos;
            prim->r1++;
            prim->g1 = 12;
        }
        prim = prim->next;
    }
}

// Small heart that rises and then flickers away.
// Created by Factory 99 in AddHearts().
// That call is in the Blood Cloak, Alucard Shield, and Herald Shield.
void EntitySmallRisingHeart(Entity* self) {
    s32 temp;
    s32 cos;

    switch (self->step) {
    case 0:
        self->posY.i.hi -= 16;
        self->zPriority = PLAYER.zPriority - 2;
        self->ext.smallRisingHeart.swayAngle = 0;
        self->step++;
        self->velocityY = FIX(-0.5);
        self->ext.smallRisingHeart.swaySpeed = 0x40;
        self->animCurFrame = 0xE;
        self->animSet = ANIMSET_DRA(3);
        self->ext.smallRisingHeart.timer = 0x80;
        self->flags = FLAG_POS_CAMERA_LOCKED;
        break;

    case 1:
        if (self->ext.smallRisingHeart.timer < 32) {
            self->drawFlags = FLAG_BLINK;
        }
        self->posY.val += self->velocityY;
        cos = rcos(self->ext.smallRisingHeart.swayAngle);
        self->ext.smallRisingHeart.swayAngle +=
            self->ext.smallRisingHeart.swaySpeed;
        temp = cos * 8;

        if (!(g_GameTimer & 3)) {
            self->ext.smallRisingHeart.swaySpeed--;
        }
        self->posX.val += temp;
        self->ext.smallRisingHeart.timer--;
        if (self->ext.smallRisingHeart.timer == 0) {
            DestroyEntity(self);
        }
        break;
    }
}

// Corresponding RIC function is func_8015FDB0
s32 func_80119E78(Primitive* prim, s32 xCenter, s32 yCenter) {
    s16 left;
    s16 top;
    s16 right;
    s32 size;
    u8* idx;
    // 800AD094 is a read-only array of bytes in 8-byte groups.
    // These are sets of 4 pairs of u,v values.
    // the ->b0 value is very likely fake.
    idx = D_800AD094;
    idx += prim->b0 * 8;
    size = 6;
    if (prim->b0 >= 3U) {
        size = 4;
    }
    if (prim->b0 == 6) {
        return -1;
    }
    left = xCenter - size;
    top = yCenter - size;
    prim->y0 = top;            // a
    prim->y1 = top;            // 16
    prim->x0 = left;           // 8
    prim->x1 = xCenter + size; // 14
    prim->x2 = left;           // 20
    prim->y2 = yCenter + size; // 22
    prim->x3 = xCenter + size; // 2c
    prim->y3 = yCenter + size; // 2e

    prim->u0 = *idx++;
    prim->v0 = *idx++;
    prim->u1 = *idx++;
    prim->v1 = *idx++;
    prim->u2 = *idx++;
    prim->v2 = *idx++;
    prim->u3 = *idx++;
    prim->v3 = *idx;
    if (!(++prim->b1 & 1)) {
        prim->b0++;
    }
    return 0;
}
// Entity ID 47. Created by blueprint 119.
// No calls to FACTORY with 119 exist yet.
// Corresponding RIC function is RicEntityHitByHoly
extern Point16 D_8013804C[16]; // BSS
void func_80119F70(Entity* entity) {
    Primitive* prim;
    s16 temp_xRand;
    s32 temp_yRand;
    s32 i;
    s16 hitboxY;
    s16 hitboxX;
    s32 temp;

    switch (entity->step) {
    case 0:
        entity->primIndex = AllocPrimitives(PRIM_GT4, LEN(D_8013804C));
        if (entity->primIndex == -1) {
            DestroyEntity(entity);
            return;
        }
        entity->flags =
            FLAG_HAS_PRIMS | FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;
        hitboxX = PLAYER.posX.i.hi + PLAYER.hitboxOffX;
        hitboxY = PLAYER.posY.i.hi + PLAYER.hitboxOffY;
        prim = &g_PrimBuf[entity->primIndex];
        for (i = 0; i < LEN(D_8013804C); i++) {
            temp_xRand = hitboxX + rand() % 24 - 12;
            temp_yRand = rand();
            D_8013804C[i].x = temp_xRand;
            D_8013804C[i].y = hitboxY + temp_yRand % 48 - 24;
            prim->clut = 0x1B2;
            prim->tpage = 0x1A;
            prim->b0 = 0;
            prim->b1 = 0;
            prim->g0 = 0;
            prim->g1 = (rand() & 7) + 1;
            prim->g2 = 0;
            prim->priority = PLAYER.zPriority + 4;
            prim->drawMode = DRAW_UNK_100 | DRAW_TPAGE | DRAW_HIDE |
                             DRAW_UNK02 | DRAW_TRANSP;
            if (rand() & 1) {
                prim->drawMode =
                    DRAW_UNK_100 | DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                    DRAW_HIDE | DRAW_UNK02 | DRAW_TRANSP;
            }
            prim = prim->next;
        }
        entity->step++;
        break;

    case 1:
        if (!(g_Player.status & PLAYER_STATUS_UNK10000)) {
            DestroyEntity(entity);
            return;
        }
    }

    prim = &g_PrimBuf[entity->primIndex];
    for (i = 0; i < LEN(D_8013804C); i++) {
        switch (prim->g0) {
        case 0:
            if (!(--prim->g1 & 0xFF)) {
                prim->g0++;
            }
            break;
        case 1:
            hitboxX = D_8013804C[i].y;
            hitboxY = D_8013804C[i].x;
            temp = func_80119E78(prim, hitboxY, hitboxX);
            D_8013804C[i].y--;
            if (temp < 0) {
                prim->drawMode |= DRAW_HIDE;
                prim->g0++;
            } else {
                prim->drawMode &= ~DRAW_HIDE;
            }
            break;
        }
        prim = prim->next;
    }
    return;
}

void func_8011A290(Entity* entity) {
    SubweaponDef subwpn;

    func_800FE3C4(&subwpn, entity->ext.subweapon.subweaponId, 0);
    entity->attack = subwpn.attack;
    entity->attackElement = subwpn.attackElement;
    entity->hitboxState = subwpn.hitboxState;
    entity->nFramesInvincibility = subwpn.nFramesInvincibility;
    entity->stunFrames = subwpn.stunFrames;
    entity->hitEffect = subwpn.hitEffect;
    entity->entityRoomIndex = subwpn.entityRoomIndex;
    entity->ext.subweapon.unkB2 = subwpn.crashId;
    func_80118894(entity);
}

void func_8011A328(Entity* entity, s32 arg1) {
    SpellDef spell;

    GetSpellDef(&spell, arg1);
    entity->attack = spell.attack;
    entity->attackElement = spell.attackElement;
    entity->hitboxState = spell.hitboxState;
    entity->nFramesInvincibility = spell.nFramesInvincibility;
    entity->stunFrames = spell.stunFrames;
    entity->hitEffect = spell.hitEffect;
    entity->entityRoomIndex = spell.entityRoomIndex;
    func_80118894(entity);
}

/// @brief Fetches current FamiliarStats and
/// @param servant Entity to update with spell or attack information
/// @param spellId Spell/attack to execute
/// @param fetchSpell Fndicates if spell information should be fetched
/// @param out Fetched FamiliarStats set here
void GetServantStats(
    Entity* servant, s32 spellId, s32 fetchSpell, FamiliarStats* out) {
    SpellDef spell;

    *out = g_Status.statsFamiliars[g_Servant - 1];
    if (fetchSpell) {
        GetSpellDef(&spell, spellId);
        servant->attack = spell.attack;
        servant->attackElement = spell.attackElement;
        servant->hitboxState = spell.hitboxState;
        servant->nFramesInvincibility = spell.nFramesInvincibility;
        servant->stunFrames = spell.stunFrames;
        servant->hitEffect = spell.hitEffect;
        servant->entityRoomIndex = spell.entityRoomIndex;
        servant->attack = spell.attack * ((out->level * 4 / 95) + 1);
        func_80118894(servant);
    }
}

void func_8011A4C8(Entity* entity) {}
