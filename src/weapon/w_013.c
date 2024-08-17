// Weapon ID #13. Used by weapons:
// Heaven sword, Unknown#202
// #202 seems to be the special attack with two heaven swords.
// Not clear how that actually works inside this file.

// Big TODO: Figure out what's going on with the extensions for
// the entities. They interact weirdly and seem to not line up.

#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_013_1.h"
#include "w_013_2.h"
#define g_Animset w_013_1
#define g_Animset2 w_013_2
#include "sfx.h"

extern SpriteParts D_5F000_8017A040[];
extern u8 D_5F000_8017A5B0[6][8];
extern s16 D_5F000_8017A5E0[];

s32 func_5F000_8017A9CC(Primitive* prim, s32 x, s32 y) {
    s32 size;
    s32 left;
    s32 right;
    s32 top;
    s32 bottom;
    u8* uvPtr;

    // Should be able to do this as an array access but nope
    uvPtr = &D_5F000_8017A5B0;
    uvPtr += prim->b0 * 8;

    if (prim->b0 >= 3) {
        size = 4;
    } else {
        size = 6;
    }
    if (prim->b0 == 6) {
        return -1;
    }
    left = x - size;
    top = y - size;
    right = x + size;
    bottom = y + size;

    prim->x0 = left;
    prim->y0 = top;
    prim->x1 = right;
    prim->y1 = top;
    prim->x2 = left;
    prim->y2 = bottom;
    prim->x3 = right;
    prim->y3 = bottom;

    prim->u0 = *uvPtr++;
    prim->v0 = *uvPtr++;
    prim->u1 = *uvPtr++;
    prim->v1 = *uvPtr++;
    prim->u2 = *uvPtr++;
    prim->v2 = *uvPtr++;
    prim->u3 = *uvPtr++;
    prim->v3 = *uvPtr++;
    if (!(++prim->b1 & 1)) {
        prim->b0++;
    }
    return 0;
}

static void EntityWeaponAttack(Entity* self) {
    Entity* unused;
    s16 var_s1;

    s16 xVar;
    s16 yVar;
    s16 var_s2;
    s16 angleDiff;
    s16 angle;

    switch (self->step) {
    case 0:
        SetSpriteBank1(D_5F000_8017A040);
        self->animSet = ANIMSET_OVL(0x10);
        self->unk5A = 0x64;
        self->palette = 0x110;
        if (g_HandId != 0) {
            self->animSet += 2;
            self->palette = 0x128;
            self->unk5A = 0x66;
        }
        self->animCurFrame = 6;
        self->facingLeft = PLAYER.facingLeft;
        self->zPriority = PLAYER.zPriority - 2;
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_04000000 | FLAG_UNK_20000;
        SetSpeedX(FIX(6));
        self->posY.i.hi = PLAYER.posY.i.hi + PLAYER.hitboxOffY - 8;
        if (PLAYER.step != Player_Crouch) {
            self->posY.i.hi -= 8;
        }
        if (self->facingLeft) {
            self->posX.i.hi = PLAYER.posX.i.hi - PLAYER.hitboxOffX;
        } else {
            self->posX.i.hi = PLAYER.posX.i.hi + PLAYER.hitboxOffX;
        }
        self->velocityX += PLAYER.velocityX;
        self->ext.timer.t = 0x16;
        SetWeaponProperties(self, 0);
        DestroyEntityWeapon(1);
        self->hitboxWidth = 0x12;
        self->hitboxHeight = 4;
        g_api.PlaySfx(SFX_WEAPON_SWISH_C);
        self->ext.heavenSword.unk98 = 0x50;
        g_Player.D_80072F00[10] = 4;
        self->step++;
        return;
    case 1:
        self->posX.val += self->velocityX;
        self->ext.timer.t--;
        if (self->ext.timer.t < 7) {
            DecelerateX(FIX(1));
        }
        if (self->ext.timer.t == 0) {
            self->velocityY = FIX(-1.5);
            self->ext.timer.t = 0x18;
            SetSpeedX(FIX(-3));
            self->step++;
        }
        return;
    case 2:
        self->hitboxWidth = 12;
        self->hitboxHeight = 12;
        self->drawFlags |= DRAW_COLORS;
        self->rotZ -= 0x80;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->velocityY += FIX(1.0 / 16);
        if (--self->ext.timer.t == 0) {
            self->ext.heavenSword.unk84 = 0x80;
            self->ext.heavenSword.unk82 =
                ratan2(-self->velocityY, self->velocityX) & 0xFFF;
            self->step++;
        }
        if (!(g_GameTimer & 1)) {
            unused = g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xC) + 0x3A, 0);
        }
        var_s2 = D_5F000_8017A5E0[(self->ext.heavenSword.unk7E >> 1) % 14];
        self->ext.weapon.childPalette = self->palette + var_s2;
        if (!(g_GameTimer & 7)) {
            g_api.PlaySfxVolPan(
                SFX_WEAPON_SWISH_A, self->ext.heavenSword.unk98, 0);
            self->ext.heavenSword.unk98 -= 4;
            if (self->ext.heavenSword.unk98 < 0) {
                self->ext.heavenSword.unk98 = 0;
            }
        }
        self->ext.heavenSword.unk7E++;
        return;
    case 3:
        self->rotZ -= 0x80;
        var_s1 = self->ext.heavenSword.unk84;
        self->ext.heavenSword.unk84 += 0x20;
        xVar = abs((PLAYER.posX.i.hi + PLAYER.hitboxOffX) - self->posX.i.hi);
        if (xVar < ((PLAYER.hitboxWidth + self->hitboxWidth) / 2)) {
            yVar =
                abs((PLAYER.posY.i.hi + PLAYER.hitboxOffY) - self->posY.i.hi);
            if (yVar < ((PLAYER.hitboxHeight + self->hitboxHeight) / 2)) {
                DestroyEntity(self);
                return;
            }
        }
        xVar = (PLAYER.posX.i.hi + PLAYER.hitboxOffX) - self->posX.i.hi;
        yVar = (PLAYER.posY.i.hi + PLAYER.hitboxOffY) - self->posY.i.hi;
        var_s2 = ratan2(-yVar, xVar) & 0xFFF;
        angle = self->ext.heavenSword.unk82 & 0xFFF;
        angleDiff = abs(angle - var_s2);
        if (var_s1 > angleDiff) {
            var_s1 = angleDiff;
        }
        if (angle < var_s2) {
            if (angleDiff < 0x800) {
                angle += var_s1;
            } else {
                angle -= var_s1;
            }
        } else {
            if (angleDiff < 0x800) {
                angle -= var_s1;
            } else {
                angle += var_s1;
            }
        }
        self->ext.heavenSword.unk82 = angle & 0xFFF;
        self->posX.val += rcos(self->ext.heavenSword.unk82) << 6;
        self->posY.val -= rsin(self->ext.heavenSword.unk82) << 6;
        if (!(g_GameTimer & 1)) {
            unused = g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xC) + 0x3A, 0);
        }
        var_s2 = D_5F000_8017A5E0[(self->ext.heavenSword.unk7E >> 1) % 14];
        self->ext.weapon.childPalette = self->palette + var_s2;
        self->ext.heavenSword.unk7E++;
        if (!(g_GameTimer & 7)) {
            g_api.PlaySfxVolPan(
                SFX_WEAPON_SWISH_A, self->ext.heavenSword.unk98, 0);
            self->ext.heavenSword.unk98 -= 4;
            if (self->ext.heavenSword.unk98 < 0) {
                self->ext.heavenSword.unk98 = 0;
            }
        }
        break;
    }
}

s32 func_ptr_80170004(Entity* self) {
    if (self->step == 0) {
        if (self->ext.weapon.parent->entityId == 0) {
            DestroyEntity(self);
            return;
        }
        self->animCurFrame = self->ext.weapon.parent->animCurFrame;
        self->animSet = self->ext.weapon.parent->animSet;
        self->facingLeft = self->ext.weapon.parent->facingLeft;
        self->unk5A = self->ext.weapon.parent->unk5A;
        self->zPriority = PLAYER.zPriority - 4;
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_04000000 | FLAG_UNK_20000;
        self->palette = self->ext.weapon.parent->ext.weapon.childPalette;
        self->drawFlags = self->ext.weapon.parent->drawFlags + FLAG_DRAW_UNK8;
        self->rotZ = self->ext.weapon.parent->rotZ;
        self->unk6C = 0x80;
        self->step++;
    }
    if (self->unk6C >= 48) {
        self->unk6C -= 8;
        return;
    }
    DestroyEntity(self);
}

static void func_ptr_80170008(Entity* self) {
    Entity* ents2;
    Primitive* prim;
    s16 angle;

    FntPrint("x:%02x,y:%02x\n", self->posX.i.hi, self->posY.i.hi);

    switch (self->step) {
    case 0:
        SetSpriteBank1(D_5F000_8017A040);
        self->animSet = ANIMSET_OVL(0x10);
        self->unk5A = 0x64;
        self->palette = 0x110;
        if (g_HandId != 0) {
            self->animSet += 2;
            self->palette = 0x128;
            self->unk5A = 0x66;
        }
        self->animCurFrame = 6;
        self->facingLeft = PLAYER.facingLeft;
        self->zPriority = PLAYER.zPriority + 2;
        self->flags = FLAG_UNK_04000000;
        self->drawFlags = FLAG_DRAW_ROTZ;
        self->posY.i.hi = PLAYER.posY.i.hi + PLAYER.hitboxOffY - 8;
        if (PLAYER.step != Player_Crouch) {
            self->posY.i.hi -= 8;
        }
        if (self->facingLeft) {
            self->posX.i.hi = PLAYER.posX.i.hi - PLAYER.hitboxOffX;
        } else {
            self->posX.i.hi = PLAYER.posX.i.hi + PLAYER.hitboxOffX;
        }
        self->ext.heavenSword.unk90 = self->posX.i.hi << 0x10;
        self->ext.heavenSword.unk94 = self->posY.i.hi << 0x10;
        self->ext.heavenSword.angle = -0x200;
        self->ext.heavenSword2.unk84 = 0x100;

        if (self->facingLeft) {
            self->ext.heavenSword.xPos = self->posX.i.hi - 0x78;
        } else {
            self->ext.heavenSword.xPos = self->posX.i.hi + 0x78;
        }
        self->ext.heavenSword.unk8A = self->posY.i.hi;
        SetWeaponProperties(self, 0);
        DestroyEntityWeapon(1);
        self->hitboxWidth = self->hitboxHeight = 14;
        self->ext.heavenSword.unk98 = 0x60;
        g_Player.D_80072F00[10] = 4;
        self->step++;
        return;
    case 1:
        self->rotZ += 0x100;
        angle = self->ext.heavenSword.angle;
        self->ext.heavenSword.angle += -0x20;
        self->ext.heavenSword2.unk84 += 0x10;
        if (self->facingLeft) {
            self->posX.val = (rcos(angle) * -self->ext.heavenSword2.unk84) +
                             self->ext.heavenSword.unk90;
        } else {
            self->posX.val = (rcos(angle) * self->ext.heavenSword2.unk84) +
                             self->ext.heavenSword.unk90;
        }
        self->posY.val = (-self->ext.heavenSword2.unk84 * rsin(angle)) +
                         self->ext.heavenSword.unk94;
        if (!(g_GameTimer & 1) && (self->ext.heavenSword.angle < -0x400)) {
            // what the hell
            ents2 = g_api.CreateEntFactoryFromEntity(
                self,
                (((g_HandId + 1) << 0xE) + 0x46 +
                 (D_5F000_8017A5E0[(self->ext.heavenSword.unk80 >> 1) % 14]
                  << 16)),
                0);
            self->ext.heavenSword.unk80++;
        }
        if (g_GameTimer % 6 == 0) {
            g_api.PlaySfxVolPan(
                SFX_WEAPON_SWISH_A, self->ext.heavenSword.unk98, 0);
            self->ext.heavenSword.unk98 -= 4;
            if (self->ext.heavenSword.unk98 < 0) {
                self->ext.heavenSword.unk98 = 0;
            }
        }
        if (self->ext.heavenSword.angle >= -0xB00) {
            return;
        }
        self->ext.heavenSword.unk82 = 8;
        self->step++;
        break;
    case 2:
        if (--self->ext.heavenSword.unk82 == 0) {
            self->drawFlags = FLAG_DRAW_UNK80;
            self->step++;
        }
        break;
    case 3:
        self->ext.heavenSword.unk82++;
        if ((self->ext.heavenSword.unk82 < 0x20) &&
            !(self->ext.heavenSword.unk82 & 3)) {
            g_api.PlaySfx(SFX_WEAPON_SWISH_B);
        }
        if (self->ext.heavenSword.unk82 > 0x10) {
            self->posX.i.hi = self->ext.heavenSword.xPos;
            self->posY.i.hi = self->ext.heavenSword.unk8A;
            self->hitboxWidth = 0x12;
            self->hitboxHeight = 4;
        }
        if (self->ext.heavenSword.unk82 > 0x30) {
            self->drawFlags = 0;
        }
        if (self->ext.heavenSword.unk82 == 0x34) {
            g_api.PlaySfx(0x66A);
            self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
            self->rotX = self->rotY = 0x100;
            self->palette = PAL_OVL(0x15F);
            self->primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 1);
            if (self->primIndex != -1) {
                self->flags |= FLAG_HAS_PRIMS;
                prim = &g_PrimBuf[self->primIndex];
                prim->r0 = prim->b0 = prim->r1 = prim->b1 = 0xF0;
                prim->g0 = 0x80;
                prim->g1 = 0x80;
                prim->x0 = prim->x1 = self->posX.i.hi;
                prim->y0 = prim->y1 = self->posY.i.hi;
                prim->priority = self->zPriority;
                prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
            } else {
                DestroyEntity(self);
                return;
            }
            self->step++;
        }
        break;
    case 4:
        if (self->primIndex != -1) {
            prim = &g_PrimBuf[self->primIndex];
            if (prim->x0 > -0x110) {
                prim->x0 -= 0x10;
            }
            if (prim->x1 < 0x110) {
                prim->x1 += 0x10;
            }
            if ((prim->x0 < 0) && (prim->x1 > 0x100)) {
                if (prim->b1 > 8) {
                    prim->b1 -= 8;
                }
                if (prim->g1 > 8) {
                    prim->g1 -= 4;
                } else {
                    DestroyEntity(self);
                    return;
                }

                prim->r0 = prim->b0 = prim->r1 = prim->b1;
                prim->g0 = prim->g1;
            }
        }
        self->rotX += 0x80;
        self->rotY = 0x20;
        if (self->rotX >= 0x700) {
            self->animCurFrame = 0;
        }
        if (self->posX.i.hi >= 0x101) {
            self->hitboxOffX = 0x100 - self->posX.i.hi;
        }
        if (self->posX.i.hi < 0) {
            self->hitboxOffX = -self->posX.i.hi;
        }
        if (self->facingLeft != 0) {
            self->hitboxOffX = -self->hitboxOffX;
        }
        self->hitboxWidth = 0xFE;
        self->hitboxHeight = 2;

        break;
    }
}

// Pay attention to unk80, unk8A, and childPalette. These all seem to be
// special for Heaven Sword and we should probably have it as a special weapon.
static void func_ptr_8017000C(Entity* self) {
    s16 angle;

    if (self->ext.weapon.parent->entityId == 0) {
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        self->animCurFrame = self->ext.weapon.parent->animCurFrame;
        self->animSet = self->ext.weapon.parent->animSet;
        self->facingLeft = self->ext.weapon.parent->facingLeft;
        self->unk5A = self->ext.weapon.parent->unk5A;
        self->zPriority = self->ext.weapon.parent->zPriority;
        self->flags = FLAG_UNK_04000000;
        self->palette = self->ext.weapon.parent->palette + (self->params >> 8);
        self->drawFlags = self->ext.weapon.parent->drawFlags | FLAG_DRAW_UNK80;
        self->rotZ = self->ext.weapon.parent->rotZ;
        self->ext.weapon.childPalette =
            self->ext.weapon.parent->ext.weapon.childPalette;
        self->ext.weapon.unk8A = self->ext.weapon.parent->ext.weapon.unk8A;
        self->ext.weapon.unk80 = (rand() & 0x1F) + 1;
        self->step++;
        break;
    case 1:
        if (self->ext.weapon.parent->step == 3) {
            self->step++;
        }
        break;
    case 2:
        if (--self->ext.weapon.unk80 == 0) {
            self->rotZ = 0;
            angle = ratan2(-(self->ext.weapon.unk8A - self->posY.i.hi),
                           self->ext.weapon.childPalette - self->posX.i.hi);
            self->velocityX = rcos(angle) * 0x100;
            self->velocityY = -rsin(angle) * 0x100;
            self->step++;
            self->ext.weapon.equipId =
                self->ext.weapon.parent->ext.weapon.equipId;
            SetWeaponProperties(self, 0);
            self->enemyId = self->ext.weapon.parent->enemyId;
            self->hitboxWidth = 0x12;
            self->hitboxHeight = 4;
        }
        break;
    case 3:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (self->facingLeft == 0) {
            if (self->posX.i.hi > self->ext.weapon.childPalette) {
                DestroyEntity(self);
                return;
            }
        } else {
            if (self->posX.i.hi < self->ext.weapon.childPalette) {
                DestroyEntity(self);
                return;
            }
        }
    }
}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 13; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
