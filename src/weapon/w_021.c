// Weapon ID #21. Used by weapons:
// Orange, Apple, Banana, Grapes, Strawberry, Pineapple, Peanuts, Toadstool,
// Shiitake, Cheesecake, Shortcake, Tart, Parfait, Pudding, Ice cream,
// Frankfurter, Hamburger, Pizza, Cheese, Ham and eggs, Omelette, Morning set,
// Lunch A, Lunch B, Curry rice, Gyros plate, Spaghetti, Grape juice, Barley
// tea, Green tea, Natou, Ramen, Miso soup, Sushi, Pork bun, Red bean bun,
// Chinese bun, Dim Sum set, Pot roast, Sirloin, Turkey, Meal ticket
#include "weapon_private.h"
#include "shared.h"

// Similar to BottomCornerText which exists in many overlays
// This one seems to process 2 characters at a time, weird.
void func_97000_8017AB54(u8* str, u8 lowerLeft) {
    u8 toPrint[64];
    Primitive* prim;
    s32 i;
    u32 ch;
    u32 ch2;
    u8* chIdx = &toPrint;

    s16 textWidth = 0;
    s32 widthTemp;
    // serves two purposes, use #define for dual names
    u16 dualVar = 0;
#define charcount dualVar
    for (i = 0; i < 64; i++) {
        *chIdx++ = 0;
    }

    chIdx = &toPrint;
    while (1) {
        ch = *str++;
        if (ch == 0xFF) {
            ch = *str++;
            if (ch == 0) {
                break;
            }
        }
        *chIdx = ch;
        chIdx++;
        textWidth += 1;
        if (ch != 0) {
            charcount += 1;
        }
        if (*str == 0xFF) {
            str++;
            ch = *str++;
            ch2 = ch & 0xFF;
            if (ch2 == 0) {
                break;
            }
            if (ch2 != 0xFF) {
                *chIdx = ch;
                charcount += 1;
            } else {
                str -= 2;
            }
        }
        chIdx++;
    }

    g_BottomCornerTextPrims = g_api.AllocPrimitives(PRIM_SPRT, charcount + 4);
    if (g_BottomCornerTextPrims == -1) {
        return;
    }
#undef charcount

    prim = &g_PrimBuf[g_BottomCornerTextPrims];
    prim->type = 3;
    prim->b0 = prim->b1 = prim->b2 = prim->b3 = prim->g0 = prim->g1 = prim->g2 =
        prim->g3 = prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0;
    if (lowerLeft) {
        prim->b0 = prim->b1 = 0xAF;
    } else {
        prim->g0 = prim->g1 = 0x5F;
    }
#define xpos dualVar

    textWidth <<= 3;
    if (lowerLeft) {
        textWidth |= 4;
        xpos = 7;
    } else {
        xpos = 0xD4 - textWidth;
    }
    prim->x0 = prim->x2 = xpos;
    prim->x1 = prim->x3 = xpos + textWidth + 0x20;
    prim->y0 = prim->y1 = 0xD0;
    prim->y2 = prim->y3 = 0xDF;
    prim->priority = 0x1EE;
    prim->drawMode = 0x11;
    prim = prim->next;

    prim->tpage = 0x1F;
    prim->clut = 0x197;
    prim->x0 = xpos - 6;
    prim->y0 = 0xCB;
    prim->u0 = 0x80;
    prim->v0 = 0;
    prim->u1 = 0x10;
    prim->v1 = 0x18;
    prim->priority = 0x1EF;
    prim->drawMode = DRAW_DEFAULT;
    prim = prim->next;

    prim->tpage = 0x1F;
    prim->clut = 0x197;
    prim->x0 = xpos + textWidth + 0x16;
    prim->y0 = 0xCB;
    prim->u0 = 0xA8;
    prim->v0 = 0;
    prim->u1 = 0x10;
    prim->v1 = 0x18;
    prim->priority = 0x1EF;
    prim->drawMode = DRAW_DEFAULT;
    prim = prim->next;

    prim->type = 4;
    prim->y0 = prim->y1 = 0xCD;
    prim->tpage = 0x1F;
    prim->clut = 0x197;
    prim->y2 = prim->y3 = 0xE1;
    prim->u0 = prim->u2 = 0x98;
    prim->u1 = prim->u3 = 0x9C;
    prim->v0 = prim->v1 = 2;
    prim->x0 = prim->x2 = xpos + 0xA;
    prim->x1 = prim->x3 = xpos + textWidth + 0x18;
    prim->v2 = prim->v3 = 0x16;
    prim->priority = 0x1EF;
    prim->drawMode = DRAW_DEFAULT;

    xpos += 0x10;

    chIdx = &toPrint;
    for (prim = prim->next; prim != NULL;) {
        ch = *chIdx++;
        if (ch != 0) {
            prim->u0 = (ch & 0xF) * 8;
            prim->v0 = (ch & 0xF0) >> 1;
            prim->tpage = 0x1E;
            prim->clut = 0x196;
            prim->v1 = 8;
            prim->u1 = 8;
            prim->priority = 0x1F0;
            prim->drawMode = 0;
            prim->x0 = xpos;
            prim->y0 = 0xD4;
            prim = prim->next;
        }
        ch = *chIdx++;
        if (ch != 0) {
            prim->u0 = (ch & 0xF) * 8;
            prim->v0 = (ch & 0xF0) >> 1;
            prim->tpage = 0x1E;
            prim->clut = 0x196;
            prim->v1 = 8;
            prim->u1 = 8;
            prim->priority = 0x1F0;
            prim->drawMode = 0;
            prim->x0 = xpos;
            prim->y0 = 0xCC;
            prim = prim->next;
        }
        if ((u32)((ch + 0x10) & 0xFF) < 0xDU) {
            xpos += 0xC;
        } else {
            xpos += 8;
        }
    }
    g_BottomCornerTextTimer = 0x130;
}

// Function that tests if a food is successfully eaten (collected)
s32 func_97000_8017AF2C(Entity* self, s32 arg1) {
    s16 xDist;
    s16 yDist;

    if (arg1 == 0) {
        // seems like silly logic to compare against 0 and then again 2
        if (self->velocityY < 0 || self->velocityY < FIX(2)) {
            return 0;
        }
    }
    // If peanut, use this logic to tell if it was eaten
    if (((self->params >> 8) & 0x7F) == 6) {
        if ((PLAYER.animCurFrame != 0x7B) || (PLAYER.ext.player.unkAC != 0) ||
            (self->posY.i.hi > (PLAYER.posY.i.hi - 16)) ||
            (self->posY.i.hi < (PLAYER.posY.i.hi - 24)) ||
            (self->posX.i.hi > (PLAYER.posX.i.hi + 4)) ||
            (self->posX.i.hi < (PLAYER.posX.i.hi - 4))) {
            return 0;
        }
        PLAYER.animFrameIdx = 3;
        PLAYER.animFrameDuration = 8;
        return 1;
    }
    // All other foods use this logic to tell if you've grabbed it
    xDist = ABS(self->posX.i.hi - PLAYER.posX.i.hi + PLAYER.hitboxOffX);
    yDist = ABS(self->posY.i.hi - PLAYER.posY.i.hi + PLAYER.hitboxOffY);
    if (xDist > (self->hitboxWidth + PLAYER.hitboxWidth)) {
        return 0;
    }
    if (yDist > (self->hitboxHeight + PLAYER.hitboxHeight)) {
        return 0;
    }
    return 1;
}

INCLUDE_ASM("weapon/nonmatchings/w_021", EntityWeaponAttack);

INCLUDE_ASM("weapon/nonmatchings/w_021", func_ptr_80170004);

void func_ptr_80170008(Entity* self) {}

void func_ptr_8017000C(Entity* self) {}

void func_ptr_80170010(Entity* self) {}

s32 func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 21; }

void EntityWeaponShieldSpell(Entity* self) {}

void func_ptr_80170024(Entity* self) {}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
