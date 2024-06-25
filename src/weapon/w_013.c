// Weapon ID #13. Used by weapons:
// Heaven sword, Unknown#202
#include "weapon_private.h"
#include "shared.h"

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

INCLUDE_ASM("weapon/nonmatchings/w_013", EntityWeaponAttack);

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

void func_ptr_80170008(Entity* self) {
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
        self->ext.heavenSword.unk84 = 0x100;

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
        self->ext.heavenSword.unk84 += 0x10;
        if (self->facingLeft) {
            self->posX.val = (rcos(angle) * -self->ext.heavenSword.unk84) +
                             self->ext.heavenSword.unk90;
        } else {
            self->posX.val = (rcos(angle) * self->ext.heavenSword.unk84) +
                             self->ext.heavenSword.unk90;
        }
        self->posY.val = (-self->ext.heavenSword.unk84 * rsin(angle)) +
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
            g_api.func_80134714(0x60A, self->ext.heavenSword.unk98, 0);
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
            g_api.PlaySfx(0x60B);
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
            self->palette = 0x815F;
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
void func_ptr_8017000C(Entity* self) {
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

s32 func_ptr_80170010(Entity* self) {}

s32 func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 13; }

void EntityWeaponShieldSpell(Entity* self) {}

void func_ptr_80170024(Entity* self) {}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}