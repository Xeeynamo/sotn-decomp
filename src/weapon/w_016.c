// SPDX-License-Identifier: AGPL-3.0-or-later
// Weapon ID #16. Used by weapons:
// Bwaka knife, Boomerang, Javelin, Fire boomerang, Iron ball
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_016_1.h"
#include "w_016_2.h"
#define g_Animset w_016_1
#define g_Animset2 w_016_2
#include "sfx.h"

// Weapon 16
extern SpriteParts D_74000_8017A040[];

static void EntityWeaponAttack(Entity* self) {
    FakePrim* fakePrim;
    s16 angle;
    u16 temp_a0;
    s32 sine;
    s32 cosine;

    switch (self->step) { /* irregular */
    case 0:
        SetSpriteBank1(D_74000_8017A040);
        self->animSet = ANIMSET_OVL(0x10);
        self->unk5A = 100;
        self->palette = 0x11A;
        if (g_HandId != 0) {
            self->palette = 0x132;
            self->unk5A = 102;
            self->animSet = self->animSet + 2;
        }
        self->animCurFrame = 14;
        self->facingLeft = PLAYER.facingLeft;
        self->zPriority = PLAYER.zPriority - 2;
        self->drawFlags = FLAG_DRAW_ROTZ;
        self->primIndex = g_api.AllocPrimitives(PRIM_TILE, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
        fakePrim = (FakePrim*)&g_PrimBuf[self->primIndex];
        fakePrim->drawMode = DRAW_HIDE;
        fakePrim->priority = 0;
        fakePrim->posY.val = self->posY.val;
        fakePrim->posX.val = self->posX.val;
        fakePrim->x0 = self->posX.i.hi;
        fakePrim->y0 = self->posY.i.hi;
        fakePrim->velocityX.val = FIX(3.5);
        if (self->facingLeft) {
            fakePrim->velocityX.val = FIX(-3.5);
        }
        self->ext.weapon.unk82 = -0x100;
        self->ext.weapon.unk80 = 0x800;
        if (self->facingLeft != 0) {
            self->ext.weapon.unk82 = -self->ext.weapon.unk82;
            self->ext.weapon.unk80 += 0x800;
        }
        self->posY.i.hi = PLAYER.posY.i.hi + PLAYER.hitboxOffY - 8;
        if (PLAYER.step != Player_Crouch) {
            self->posY.i.hi -= 6;
        }
        if (self->facingLeft) {
            self->posX.i.hi = PLAYER.posX.i.hi - PLAYER.hitboxOffX;
        } else {
            self->posX.i.hi = PLAYER.posX.i.hi + PLAYER.hitboxOffX;
        }
        SetWeaponProperties(self, 0);
        DestroyEntityWeapon(1);
        self->hitboxHeight = self->hitboxWidth = 4;
        g_api.PlaySfx(0x69E);
        g_Player.timers[10] = 4;
        self->step++;
        break;
    case 1:
        if (self->ext.weapon.unk7E < 448) {
            self->ext.weapon.unk7E += 8;
        }
        fakePrim = (FakePrim*)&g_PrimBuf[self->primIndex];
        self->rotZ += abs(self->ext.weapon.unk82);
        self->ext.weapon.unk80 += self->ext.weapon.unk82;
        fakePrim->posX.i.hi = fakePrim->x0;
        fakePrim->posY.i.hi = fakePrim->y0;
        fakePrim->posX.val += fakePrim->velocityX.val;
        fakePrim->x0 = fakePrim->posX.i.hi;
        fakePrim->y0 = fakePrim->posY.i.hi;
        break;
    }
    fakePrim = (FakePrim*)&g_PrimBuf[self->primIndex];
    angle = self->ext.weapon.unk80;
    cosine = rcos(angle) * self->ext.weapon.unk7E;
    sine = -rsin(angle) * self->ext.weapon.unk7E;
    self->posX.val = cosine + fakePrim->posX.val;
    self->posY.val = sine + fakePrim->posY.val;
    if (self->ext.weapon.lifetime & 1) {
        // Create a factory, with a 1 shifted 0xC, or a 2 shifted 0xC (which is
        // a 1 shifted 0xD)
        //  Therefore this is 0x1000 or 0x2000. Will trigger if-statements so
        //  factory gets unkA8 = 0xE0 or 0xF0, putting it into the range of
        //  weapon functions. Then we use blueprint 0x3A, or 58, so child is E1
        //  or F1. This will make the entity in func_ptr_80170004.
        g_api.CreateEntFactoryFromEntity(self, WFACTORY(0x3A, 0), 0);
    }
    self->ext.weapon.lifetime++;
}

s32 func_ptr_80170004(Entity* self) {

    if (self->step == 0) {
        self->animSet = self->ext.weapon.parent->animSet;
        self->animCurFrame = self->ext.weapon.parent->animCurFrame;
        self->facingLeft = self->ext.weapon.parent->facingLeft;
        self->zPriority = PLAYER.zPriority - 4;
        self->flags = FLAG_POS_CAMERA_LOCKED;
        self->palette = self->ext.weapon.parent->palette;
        self->unk5A = self->ext.weapon.parent->unk5A;
        self->ext.weapon.lifetime = 0x16;
        self->drawFlags = FLAG_DRAW_ROTZ | FLAG_DRAW_UNK8;
        self->drawMode = DRAW_TPAGE;
        self->rotZ = self->ext.weapon.parent->rotZ;
        self->unk6C = 0x80;
        self->step++;
    }
    if (--self->ext.weapon.lifetime == 0) {
        DestroyEntity(self);
        return;
    }
    if (self->unk6C >= 48) {
        self->unk6C -= 8;
    }
}

extern SpriteParts D_74000_8017A040[];

void func_ptr_80170008(Entity* self) {
    s32 angle;
    s8 flag;

    flag = (self->params & 0x7F00) != 0;

    switch (self->step) {
    case 0:
        SetSpriteBank1(D_74000_8017A040);
        self->animSet = ANIMSET_OVL(0x10);
        self->unk5A = 0x64;
        self->palette = 0x11A;
        if (g_HandId != 0) {
            self->palette = 0x132;
            self->unk5A = 0x66;
            self->animSet += 2;
        }
        self->animCurFrame = 0xF;
        self->facingLeft = PLAYER.facingLeft;
        self->zPriority = PLAYER.zPriority - 2;
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA;
        self->drawFlags = DRAW_COLORS;

        self->posY.i.hi = PLAYER.posY.i.hi + PLAYER.hitboxOffY;
        if (PLAYER.step != 2) {
            self->posY.i.hi -= 8;
        }
        if (self->facingLeft) {
            self->posX.i.hi = PLAYER.posX.i.hi - PLAYER.hitboxOffX - 20;
        } else {
            self->posX.i.hi = PLAYER.posX.i.hi + PLAYER.hitboxOffX + 20;
        }
        self->ext.weapon_016.unk7C = -0x20;
        self->ext.weapon_016.unk80 = 0x48;
        self->ext.weapon_016.unk7E = 0xA;
        self->ext.weapon_016.unk84 = 0;
        self->rotZ = 0x400;
        SetWeaponProperties(self, 0);
        DestroyEntityWeapon(true);
        self->hitboxHeight = 0xC;
        self->hitboxWidth = 0xC;
        g_api.PlaySfx(0x69E);
        if (flag != 0) {
            g_api.PlaySfx(0x65B);
        }
        g_Player.timers[10] = 4;
        self->step++;
        break;
    case 1:
        self->ext.weapon_016.unk7C += self->ext.weapon_016.unk7E;
        self->rotZ -= 0x100;
        angle = self->ext.weapon_016.unk7C;
        self->velocityX = rcos(angle) * self->ext.weapon_016.unk80;
        self->velocityY = -rsin(angle) * self->ext.weapon_016.unk80;
        if (self->facingLeft) {
            self->posX.val = self->posX.val - self->velocityX;
        } else {
            self->posX.val = self->posX.val + self->velocityX;
        }
        self->posY.val += self->velocityY;
        if (self->ext.weapon_016.unk84 < 0x23) {
            self->ext.weapon_016.unk7E += 2;
        }
        if (self->ext.weapon_016.unk84 > 0x23) {
            self->ext.weapon_016.unk80 += 3;
            if (self->ext.weapon_016.unk7E > 6) {
                self->ext.weapon_016.unk7E -= 6;
            }
            if (self->ext.weapon_016.unk84 == 0x40) {
                self->flags &= ~FLAG_KEEP_ALIVE_OFFCAMERA;
            }
        }
        if (self->ext.weapon_016.unk84 <= 0x7000) {
            self->ext.weapon_016.unk84 += 1;
        }
        if ((u16)self->ext.weapon_016.unk84 & 1) {
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xC) | 0x3A, 0);
        }
        if (flag != 0) {
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xC) | 0x6E, 0);
        }
        break;
    }
}

static void func_ptr_8017000C(Entity* self) {
    s16 temp_a0;

    switch (self->step) {
    case 0:
        SetSpriteBank1(D_74000_8017A040);
        self->animSet = ANIMSET_OVL(0x10);
        self->unk5A = 0x64;
        self->palette = 0x11B;
        if (g_HandId != 0) {
            self->palette = 0x133;
            self->unk5A = 0x66;
            self->animSet += 2;
        }
        self->animCurFrame = 0x10;
        self->facingLeft = PLAYER.facingLeft;
        self->zPriority = PLAYER.zPriority - 2;
        self->flags = FLAG_POS_CAMERA_LOCKED;
        self->drawFlags = DRAW_COLORS;
        temp_a0 = PLAYER.posY.i.hi + PLAYER.hitboxOffY;
        self->posY.i.hi = temp_a0 - 6;
        if (PLAYER.step != 2) {
            self->posY.i.hi = temp_a0 - 14;
        }
        if (self->facingLeft) {
            self->posX.i.hi = PLAYER.posX.i.hi - PLAYER.hitboxOffX - 10;
        } else {
            self->posX.i.hi = PLAYER.posX.i.hi + PLAYER.hitboxOffX + 10;
        }
        SetSpeedX(FIX(6));
        self->velocityY = FIX(-1.125);
        SetWeaponProperties(self, 0);
        DestroyEntityWeapon(true);
        self->hitboxHeight = 12;
        self->hitboxWidth = 12;
        g_api.PlaySfx(SFX_WEAPON_SWISH_B);
        g_Player.timers[10] = 4;
        self->step++;
        break;
    case 1:
        if (self->velocityY < FIX(7)) {
            self->velocityY += FIX(3) / 64;
        }
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        break;
    }
    self->rotZ = ratan2(self->velocityY, abs(self->velocityX));
}

extern AnimationFrame D_74000_8017A5B0[];
extern s32 D_74000_8017BD74;

s32 func_ptr_80170010(Entity* self) {
    Entity* factory;

    if (self->step == 0) {
        self->animSet = 2;
        self->anim = D_74000_8017A5B0;
        self->zPriority = PLAYER.zPriority - 4;
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_UNK_100000;
        self->velocityY = FIX(-1.0);

        if (!(D_74000_8017BD74 & 1)) {
            factory = g_api.CreateEntFactoryFromEntity(self, FACTORY(4, 11), 0);
            if (factory) {
                if (g_HandId == 0) {
                    factory->entityId = 0xEF;
                } else {
                    factory->entityId = 0xFF;
                }
            }
        }
        self->posY.i.hi += -6 + (rand() % 12);
        self->posX.i.hi += -3 + (rand() & 7);
        D_74000_8017BD74 += 1;
        if (!(rand() & 1)) {
            self->drawMode |= DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE;
        }
        self->step += 1;
    }
    self->posY.val += self->velocityY;
    if (self->animFrameDuration < 0) {
        DestroyEntity(self);
    }
}

// Tracing function calls in emulator indicates that this function manages
// the physics for the Iron Ball item.
static s32 func_ptr_80170014(Entity* self) {
    Collider collider;
    s16 collX;
    s16 collY;
    u16 tempEffects;
    s16 xShift;
    s16 yShift;

    switch (self->step) {
    case 0:
        SetSpriteBank1(D_74000_8017A040);
        self->animSet = ANIMSET_OVL(0x10);
        self->unk5A = 100;
        self->palette = 0x11D;
        if (g_HandId != 0) {
            self->palette = 0x135;
            self->unk5A += 2;
            self->animSet += 2;
        }
        self->animCurFrame = 17;
        self->facingLeft = PLAYER.facingLeft;
        self->zPriority = PLAYER.zPriority - 2;
        self->flags = FLAG_POS_CAMERA_LOCKED;
        self->velocityY = FIX(-2.25) - (rand() & 0x7FFF); // -2.5 +- 0.25
        SetSpeedX((rand() & 0x7FFF) + FIX(1.25));         // 1.5 +- 0.25
        self->posY.i.hi = PLAYER.posY.i.hi + PLAYER.hitboxOffY;
        SetWeaponProperties(self, 0);
        DestroyEntityWeapon(true);
        self->hitboxHeight = self->hitboxWidth = 8;
        g_api.PlaySfx(0x6EE);
        self->ext.weapon.unk7E = 0x40;
        g_Player.timers[10] = 4;
        self->step++;
        return;
    case 1:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (self->velocityY < FIX(7)) {
            self->velocityY += FIX(0.125);
        }
        if (self->velocityX < 0) {
            xShift = -5;
        } else {
            xShift = 5;
        }
        collX = xShift + self->posX.i.hi;
        collY = self->posY.i.hi;
        g_api.CheckCollision(collX, collY, &collider, 0);
        if (collider.effects & EFFECT_UNK_0002) {
            g_api.PlaySfx(SFX_EXPLODE_B);
            g_api.func_80102CD8(4);
            if (xShift < 0) {
                self->posX.i.hi += collider.unkC;
            } else {
                self->posX.i.hi += collider.unk4;
            }
            self->velocityX /= -2;
            self->facingLeft = (self->facingLeft + 1) & 1;
        }
        collX = self->posX.i.hi;
        collY = self->posY.i.hi - 6;
        g_api.CheckCollision(collX, collY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            g_api.PlaySfx(SFX_EXPLODE_B);
            g_api.func_80102CD8(4);
            self->posY.i.hi += collider.unk20 + 1;
            self->velocityX /= 2;
            self->velocityY = FIX(1);
        }
        collX = self->posX.i.hi;
        collY = self->posY.i.hi + 7;
        g_api.CheckCollision(collX, collY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            g_api.PlaySfx(SFX_EXPLODE_B);
            g_api.func_80102CD8(4);
            self->posY.i.hi += collider.unk18;
            if (self->ext.weapon.lifetime != 0) {
                self->step++;
            }
            self->velocityY = FIX(-1.125);
            self->velocityX /= 2;
            self->ext.weapon.lifetime++;
            // Create factory with blueprint 31. Blueprint 31 has child entity
            // 2, which is func_8011B5A4.
            g_api.CreateEntFactoryFromEntity(self, FACTORY(31, 9), 0);
        }
        return;
    case 2:
        if (self->velocityX == 0) {
            if (--self->ext.weapon.unk7E == 0) {
                self->step = 3;
                self->ext.weapon.unk7E = 0x20;
                self->drawFlags = FLAG_DRAW_UNK80;
            }
        }
        collX = self->posX.i.hi;
        collY = self->posY.i.hi + 11;
        g_api.CheckCollision(collX, collY, &collider, 0);
        tempEffects = collider.effects;
        if (tempEffects & 1) {
            yShift = collider.unk18 + 4;
            collY = collY + yShift - 5;
            g_api.CheckCollision(collX, collY, &collider, 0);
            if (!(collider.effects & EFFECT_SOLID)) {
                self->posY.i.hi = yShift + self->posY.i.hi;
            } else if (!(collider.effects & EFFECT_UNK_8000)) {
                self->step = 1;
                self->velocityY = 0;
                self->hitboxWidth = 8;
                return;
            } else {
                self->posY.i.hi += 3 + (yShift + collider.unk18);
                tempEffects = collider.effects;
            }
            tempEffects &= 0xF000; // mask off just a couple effects
            if (tempEffects == EFFECT_UNK_8000 + EFFECT_UNK_4000) {
                self->facingLeft = 0;
                self->velocityX += 0x400;
            }
            if (tempEffects ==
                EFFECT_UNK_8000 + EFFECT_UNK_4000 + EFFECT_UNK_1000) {
                self->facingLeft = 0;
                self->velocityX += 0x300;
            }
            if (tempEffects ==
                EFFECT_UNK_8000 + EFFECT_UNK_4000 + EFFECT_UNK_2000) {
                self->facingLeft = 0;
                self->velocityX += 0x200;
            }
            if (tempEffects == EFFECT_UNK_8000) {
                self->facingLeft = 1;
                self->velocityX -= 0x400;
            }
            if (tempEffects == EFFECT_UNK_8000 + EFFECT_UNK_1000) {
                self->facingLeft = 1;
                self->velocityX -= 0x300;
            }
            if (tempEffects == EFFECT_UNK_8000 + EFFECT_UNK_2000) {
                self->facingLeft = 1;
                self->velocityX -= 0x200;
            }
            if (self->velocityX > FIX(1)) {
                self->velocityX = FIX(1);
            }
            if (self->velocityX < FIX(-1)) {
                self->velocityX = FIX(-1);
            }

            if (!(tempEffects & EFFECT_UNK_8000)) {
                if (self->velocityX < 0) {
                    xShift = -5;
                } else {
                    xShift = 5;
                }
                collX = xShift + self->posX.i.hi;
                collY = self->posY.i.hi;
                g_api.CheckCollision(collX, collY, &collider, 0);
                if (collider.effects & EFFECT_UNK_0002) {
                    if (self->velocityX != 0) {
                        g_api.PlaySfx(SFX_EXPLODE_B);
                        g_api.func_80102CD8(1);
                    }
                    if (xShift < 0) {
                        self->posX.i.hi += collider.unkC;
                    } else {
                        self->posX.i.hi += collider.unk4;
                    }
                }
                DecelerateX(FIX(1.0 / 128));
            }
        } else {
            self->step = 1;
            self->velocityY = 0;
            self->hitboxWidth = 4;
        }
        self->posX.val += self->velocityX;
        if (abs(self->velocityX) >= FIX(0.5)) {
            self->hitboxWidth = 8;
            return;
        }
        self->hitboxWidth = 0;
        return;
    case 3:
        if (--self->ext.weapon.unk7E == 0) {
            DestroyEntity(self);
        }
        break;
    case 4:
        break;
    }
}

static int GetWeaponId(void) { return 16; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
