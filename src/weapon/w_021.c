// SPDX-License-Identifier: AGPL-3.0-or-later
// Weapon ID #21. Used by weapons:
// Orange, Apple, Banana, Grapes, Strawberry, Pineapple, Peanuts, Toadstool,
// Shiitake, Cheesecake, Shortcake, Tart, Parfait, Pudding, Ice cream,
// Frankfurter, Hamburger, Pizza, Cheese, Ham and eggs, Omelette, Morning set,
// Lunch A, Lunch B, Curry rice, Gyros plate, Spaghetti, Grape juice, Barley
// tea, Green tea, Natou, Ramen, Miso soup, Sushi, Pork bun, Red bean bun,
// Chinese bun, Dim Sum set, Pot roast, Sirloin, Turkey, Meal ticket
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_021_1.h"
#include "w_021_2.h"
#define g_Animset w_021_1
#define g_Animset2 w_021_2
#include "sfx.h"

extern SpriteParts D_97000_8017A040[];

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

    g_unkGraphicsStruct.BottomCornerTextPrims =
        g_api.AllocPrimitives(PRIM_SPRT, charcount + 4);
    if (g_unkGraphicsStruct.BottomCornerTextPrims == -1) {
        return;
    }
#undef charcount

    prim = &g_PrimBuf[g_unkGraphicsStruct.BottomCornerTextPrims];
    prim->type = PRIM_G4;
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
    prim->drawMode = DRAW_TPAGE | DRAW_TRANSP;
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

    prim->type = PRIM_GT4;
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
            prim->drawMode = DRAW_DEFAULT;
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
            prim->drawMode = DRAW_DEFAULT;
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
    g_unkGraphicsStruct.BottomCornerTextTimer = 0x130;
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
        if ((PLAYER.animCurFrame != 0x7B) || (PLAYER.ext.player.anim != 0) ||
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
    xDist = abs(self->posX.i.hi - PLAYER.posX.i.hi + PLAYER.hitboxOffX);
    yDist = abs(self->posY.i.hi - PLAYER.posY.i.hi + PLAYER.hitboxOffY);
    if (xDist > (self->hitboxWidth + PLAYER.hitboxWidth)) {
        return 0;
    }
    if (yDist > (self->hitboxHeight + PLAYER.hitboxHeight)) {
        return 0;
    }
    return 1;
}

static void EntityWeaponAttack(Entity* self) {
    Collider sp10;
    s16 xShift;
    s16 yShift;
    s32 factory_arg1;

    switch (self->step) {
    case 0:
        SetSpriteBank1(D_97000_8017A040);
        self->animSet = ANIMSET_OVL(0x10);
        self->palette = 0x110;
        self->unk5A = 100;
        if (g_HandId != 0) {
            self->palette += 0x18;
            self->unk5A += 2;
            self->animSet += 2;
        }
        // Testing for meal ticket
        if (((self->params >> 8) & 0x7F) == 41) {
            self->params &= 0x80FF;
            self->params |= (rand() % 41) << 8;
            self->step = 5;
            self->animCurFrame = 0;
            // weird logic here
            self->ext.food.foodId -= 41;
            self->ext.food.foodId += ((self->params & 0x7F00) >> 8);
            return;
        }
        self->zPriority = PLAYER.zPriority + 2;
        self->facingLeft = PLAYER.facingLeft;
        self->flags = FLAG_POS_CAMERA_LOCKED;
        self->animCurFrame = ((self->params >> 8) & 0x7F) + 1;
        self->posY.i.hi -= 4;
        SetSpeedX((rand() & 0x3FFF) + FIX(0.875)); // 1 +- 0.125
        self->velocityY = FIX(-2);
        // This tests for the peanut!
        if (((self->params >> 8) & 0x7F) == 6) {
            if (self->facingLeft) {
                self->posX.i.hi -= 8;
            } else {
                self->posX.i.hi += 8;
            }
            SetSpeedX((rand() & 0xFFF) | FIX(1.0 / 16)); // 1/16 to 1/8
            self->velocityY = FIX(-5.5);
            self->ext.food.unk80 = FIX(-5.5);
        }
        SetWeaponProperties(self, 2);
        DestroyEntityWeapon(1);
        self->facingLeft = 0;
        self->hitboxHeight = self->hitboxWidth = 8;
        self->step++;
        return;
    case 1:
        if (func_97000_8017AF2C(self, 0) != 0) {
            // Testing for toadstool!
            if (((self->params >> 8) & 0x7F) == 7) {
                self->ext.food.timer = 12;
                self->step = 4;
                self->animCurFrame = 0;
                g_Player.padSim = PAD_DOWN; // Note: different in steps 1 and 2
                g_Player.D_80072EFC = 20;   // stun player for 20 frames
                return;
            }
            if (g_Player.unk56 == 0) {
                g_Player.unk56 = 1;
                g_Player.unk58 = self->attack;
                DestroyEntity(self);
                return;
            }
            self->ext.food.timer = 8;
            self->animCurFrame = 0;
            self->step = 3;
            return;
        }
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->velocityY += FIX(20.0 / 128);
        g_api.CheckCollision(
            self->posX.i.hi, (s16)(self->posY.i.hi + 8), &sp10, 0);
        if (sp10.effects & EFFECT_SOLID) {
            self->posY.i.hi += sp10.unk18;
            // Test for peanut. Peanut should bounce.
            if (((self->params >> 8) & 0x7F) == 6) {
                self->ext.food.unk80 /= 2;
                self->velocityY = self->ext.food.unk80;
                if (self->velocityY <= FIX(-1)) {
                    self->posY.val += self->velocityY;
                } else {
                    DestroyEntity(self);
                    return;
                }
            } else {
                self->ext.food.timer = 0x80;
                self->step++;
                return;
            }
        }
        if (self->velocityX < 0) {
            xShift = -4;
        } else {
            xShift = 4;
        }
        g_api.CheckCollision(
            (s16)(xShift + self->posX.i.hi), self->posY.i.hi, &sp10, 0);
        if (sp10.effects & EFFECT_UNK_0002) {
            if (xShift < 0) {
                self->posX.i.hi += sp10.unkC;
            } else {
                self->posX.i.hi += sp10.unk4;
            }
            self->velocityX /= -2;
            // Applies to the peanut
            if (((self->params >> 8) & 0x7F) == 6) {
                DestroyEntity(self);
                return;
            }
        }
        // Peanut has lower collision than other food (probably because it's
        // tiny?)
        if (((self->params >> 8) & 0x7F) == 6) {
            yShift = -4;
        } else {
            yShift = -8;
        }
        g_api.CheckCollision(
            self->posX.i.hi, (s16)(yShift + self->posY.i.hi), &sp10, 0);
        if (sp10.effects & EFFECT_SOLID) {
            self->posY.i.hi += (1 + sp10.unk20);
            self->velocityX /= 2;
            self->velocityY = FIX(1);
            return;
        }

        return;
    case 2:
        DecelerateX(FIX(36.0 / 128));
        self->posX.val += self->velocityX;
        if (func_97000_8017AF2C(self, 1) != 0) {
            // Toadstool logic
            if (((self->params >> 8) & 0x7F) == 7) {
                self->ext.food.timer = 12;
                self->step = 4;
                self->animCurFrame = 0;
                g_Player.padSim = 0; // Note: different in steps 1 and 2
                g_Player.D_80072EFC = 20;
                return;
            }
            if (g_Player.unk56 == 0) {
                g_Player.unk56 = 1;
                g_Player.unk58 = self->attack;
                DestroyEntity(self);
                return;
            }
            self->ext.food.timer = 8;
            self->animCurFrame = 0;
            self->step = 3;
            return;
        }
        if (self->ext.food.timer == 24) {
            self->drawFlags |= FLAG_BLINK;
        }
        if (--self->ext.food.timer == 0) {
            DestroyEntity(self);
        }
        return;
    case 3:
        if (--self->ext.food.timer == 0) {
            if (g_Player.unk56 == 0) {
                g_Player.unk56 = 1;
                g_Player.unk58 = self->attack;
                DestroyEntity(self);
                return;
            }
            self->ext.food.timer = 8;
        }
        return;
    case 4:
        if (--self->ext.food.timer == 0) {
            PLAYER.hitParams = 0x81;
            PLAYER.hitPoints = 0;
            PLAYER.hitboxState = 0;
            DestroyEntity(self);
            return;
        }
        return;
    case 5:
        // Creates factory to make an entity where the params is the food ID.
        // Uses blueprint 56, indexed into the weapon functions.
        // Blueprint 56 is child offset 1, so this runs func_ptr_80170004 for
        // food.
        factory_arg1 =
            56 + ((g_HandId + 1) << 0xE) + (self->ext.food.foodId << 0x10);
        if (g_api.CreateEntFactoryFromEntity(self, factory_arg1, 0) != NULL) {
            self->ext.food.timer = 4;
            self->step++;
            return;
        }
        return;
    case 6:
        if (--self->ext.food.timer == 0) {
            DestroyEntity(self);
        }
        return;
    }
}

s32 func_ptr_80170004(Entity* self) {
    Collider sp10;
    u32 upperParams;
    s16 xShift;
    s16 yShift;
    const char* temp_s1;
    s16 xVar;
    s16 yVar;

    upperParams = (self->params >> 8) & 0x7F;

    switch (self->step) {
    case 0:
        SetSpriteBank1(D_97000_8017A040);
        self->animSet = ANIMSET_OVL(0x10);
        self->palette = 0x110;
        self->unk5A = 0x64;
        if (g_HandId != 0) {
            self->palette += 0x18;
            self->unk5A += 2;
            self->animSet += 2;
        }
        self->zPriority = PLAYER.zPriority + 2;
        self->facingLeft = PLAYER.facingLeft;
        self->flags = FLAG_POS_CAMERA_LOCKED;
        self->animCurFrame = upperParams - 0x1C;
        self->posY.i.hi -= 4;
        SetSpeedX((rand() & 0x3FFF) + FIX(0.875));
        self->velocityY = FIX(-2);
        DestroyEntityWeapon(1);
        self->facingLeft = 0;
        self->hitboxHeight = self->hitboxWidth = 8;
        self->step++;
        break;
    case 1:
        if (func_97000_8017AF2C(self, 0) != 0) {
            if (g_unkGraphicsStruct.BottomCornerTextTimer) {
                g_api.FreePrimitives(g_unkGraphicsStruct.BottomCornerTextPrims);
                g_unkGraphicsStruct.BottomCornerTextTimer = 0;
            }
            g_api.PlaySfx(SFX_ITEM_PICKUP);
            temp_s1 = g_api.equipDefs[upperParams].name;
            g_api.AddToInventory(upperParams, EQUIP_HAND);
            func_97000_8017AB54(temp_s1, 1);
            DestroyEntity(self);
            return;
        }
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->velocityY += FIX(0.15625);
        xShift = 0;
        yShift = 8;
        xVar = self->posX.i.hi + xShift;
        yVar = self->posY.i.hi + yShift;
        g_api.CheckCollision(xVar, yVar, &sp10, 0);
        if (sp10.effects & EFFECT_SOLID) {
            self->posY.i.hi += sp10.unk18;
            self->ext.timer.t = 0x200;
            self->step++;
            return;
        }
        xShift = 4;
        if (self->velocityX < 0) {
            xShift = -xShift;
        }
        yShift = 0;
        xVar = self->posX.i.hi + xShift;
        yVar = self->posY.i.hi + yShift;
        g_api.CheckCollision(xVar, yVar, &sp10, 0);
        if (sp10.effects & EFFECT_UNK_0002) {
            if (xShift < 0) {
                self->posX.i.hi += sp10.unkC;
            } else {
                self->posX.i.hi += sp10.unk4;
            }
            self->velocityX = -(self->velocityX / 2);
        }
        xShift = 0;
        yShift = -8;
        xVar = self->posX.i.hi + xShift;
        yVar = self->posY.i.hi + yShift;
        g_api.CheckCollision(xVar, yVar, &sp10, 0);
        if (sp10.effects & EFFECT_SOLID) {
            self->posY.i.hi += (1 + sp10.unk20);
            self->velocityY = FIX(1);
            self->velocityX = self->velocityX / 2;
        }
        break;
    case 2:
        self->velocityY = 0;
        if (--self->ext.timer.t == 0) {
            DestroyEntity(self);
            break;
        }
        if (func_97000_8017AF2C(self, 1) != 0) {
            if (g_unkGraphicsStruct.BottomCornerTextTimer) {
                g_api.FreePrimitives(g_unkGraphicsStruct.BottomCornerTextPrims);
                g_unkGraphicsStruct.BottomCornerTextTimer = 0;
            }
            g_api.PlaySfx(SFX_ITEM_PICKUP);
            temp_s1 = g_api.equipDefs[upperParams].name;
            g_api.AddToInventory(upperParams, EQUIP_HAND);
            func_97000_8017AB54(temp_s1, 1);
            DestroyEntity(self);
        }
        break;
    }
}

static void func_ptr_80170008(Entity* self) {}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 21; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
