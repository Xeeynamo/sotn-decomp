// Weapon ID #29. Used by weapons:
// Fire shield, Unknown#213
#include "weapon_private.h"
#include "shared.h"

extern u16 D_CF000_8017ACF8[];
extern u16 D_CF000_8017AD04[];
extern AnimationFrame D_CF000_8017AD24[];

INCLUDE_ASM("weapon/nonmatchings/w_029", EntityWeaponAttack);

void func_ptr_80170004(Entity* self) {
    if (self->ext.weapon.parent->ext.weapon.equipId != 15) {
        DestroyEntity(self);
        return;
    }
    if (self->step == 0) {
        self->animSet = self->ext.weapon.parent->animSet;
        self->zPriority = self->ext.weapon.parent->zPriority + 4;
        self->unk5A = self->ext.weapon.parent->unk5A;
        self->ext.weapon.unk80 = self->ext.weapon.parent->ext.weapon.unk80;
        self->animCurFrame = self->ext.weapon.parent->animCurFrame;
        self->flags = 0x08000000;
        self->unk19 = 0x18;
        self->unk6C = 0x80;
        self->ext.weapon.unk7E = 0x14;
        self->step++;
    } else {
        if (self->unk6C >= 7) {
            self->unk6C -= 7;
        }

        if (--self->ext.weapon.unk7E == 0) {
            DestroyEntity(self);
            return;
        }
    }
    self->palette =
        self->ext.weapon.unk80 + D_CF000_8017AD04[g_GameTimer / 2 % 5];
}

void func_ptr_80170008(Entity* self) {}

void func_ptr_8017000C(Entity* self) {}

void func_ptr_80170010(Entity* self) {}

void func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 29; }

void EntityWeaponShieldSpell(Entity* self) {
    Primitive* prim;
    s32 var_v0;
    u16 selfX;
    u16 selfY;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        SetSpriteBank1(g_Animset);
        if (g_HandId != 0) {
            self->animSet = -0x7FEE;
            self->ext.weapon.childPalette = 0x128;
            self->unk5A = 0x66;
            self->ext.weapon29.unk7C = 0;
            self->ext.weapon29.unk7D = 0x80;
        } else {
            self->animSet = -0x7FF0;
            self->ext.weapon.childPalette = 0x110;
            self->unk5A = 0x64;
            self->ext.weapon29.unk7C = 0x80;
            self->ext.weapon29.unk7D = 0;
        }
        self->posY.i.hi -= 8;
        self->flags = 0x04810000;
        self->zPriority = PLAYER.zPriority - 2;
        self->facingLeft = PLAYER.facingLeft;
        self->animCurFrame = 0x3E;
        self->unk19 = 3;
        self->unk1C = 0;
        self->unk1A = 0;
        prim = &g_PrimBuf[self->primIndex];
        prim->clut = 0x19F;
        prim->tpage = 0x19;
        prim->u0 = prim->u2 = 0x80;
        prim->u1 = prim->u3 = 0xCF;
        prim->v0 = prim->v1 = self->ext.weapon29.unk7C;
        prim->v2 = prim->v3 = self->ext.weapon29.unk7C + 0x4F;
        self->ext.weapon.unk82 = 0;
        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 =
                0x80;
        prim->priority = self->zPriority - 4;
        prim->blendMode = 0x75;
        SetSpeedX(FIX(-2));
        self->velocityY = 0;
        DestroyEntityWeapon(1);
        g_api.PlaySfx(0x641);
        *D_80097420 = 1;
        self->step++;
        break;

    case 1:
        DecelerateX(FIX(1.0 / 16));
        self->velocityY -= FIX(20.0 / 128);
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->unk1A += 12;
        self->unk1C = self->unk1A;
        self->ext.weapon.unk82 = self->unk1A * 40 / 256;

        if (self->unk1A >= 0x100) {
            self->ext.weapon.unk82 = 0x28;
            self->unk1A = 0x100;
            self->unk1C = 0x100;
            self->ext.weapon.unk80 = 8;
            self->step++;
        }
        self->palette =
            self->ext.weapon.childPalette + D_CF000_8017ACF8[g_Timer / 2 % 5];
        break;
    case 2:
        if (--self->ext.weapon.unk80 == 0) {
            self->step++;
        }
        self->palette =
            self->ext.weapon.childPalette + D_CF000_8017ACF8[g_Timer / 2 % 5];
        break;
    case 3:
        self->palette = self->ext.weapon.childPalette +
                        D_CF000_8017ACF8[g_GameTimer / 2 % 5];
        self->unk1A -= 0x10;
        self->unk1C = self->unk1A;
        if (self->unk1A <= 0) {
            self->unk1A = 0;
            self->unk4C = D_CF000_8017AD24;
            self->animFrameIdx = 0;
            self->animFrameDuration = 0;
            self->flags |= 0x100000;
            self->ext.weapon.unk80 = 0x20;
            self->palette = self->ext.weapon.childPalette;
            self->zPriority = 0x1B6;
            g_api.PlaySfx(0x668);
            self->step++;
        }
        break;
    case 4:
        self->ext.weapon.unk82 += 8;
        self->unk1A += 0x10;
        if (self->unk1A >= 0x100) {
            self->unk1A = 0x100;
        }
        self->unk1C = self->unk1A;
        prim = &g_PrimBuf[self->primIndex];
        if (prim->b3 >= 9) {
            prim->b3 -= 4;
        }
        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3;
        if (--self->ext.weapon.unk80 == 0) {
            prim->blendMode |= 8;
            g_api.PlaySfx(0x660);
            g_api.func_8011AAFC(self, ((g_HandId + 1) << 0xE) + 0x66, 0);
            self->ext.weapon.unk80 = 0x18;
            *D_80097420 = 0;
            self->step++;
        }
        break;
    case 5:
        if (--self->ext.weapon.unk80 == 0) {
            self->step++;
        }
        break;
    case 6:
        self->unk1A -= 0x10;
        self->unk1C = self->unk1A;
        if (self->unk1A <= 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    selfX = self->posX.i.hi;
    selfY = self->posY.i.hi;
    prim = &g_PrimBuf[self->primIndex];
    prim->x0 = prim->x2 = selfX - self->ext.weapon.unk82;
    prim->x1 = prim->x3 = (selfX + self->ext.weapon.unk82) - 1;
    prim->y0 = prim->y1 = selfY - self->ext.weapon.unk82;
    prim->y2 = prim->y3 = (selfY + self->ext.weapon.unk82) - 1;
    return;
}

INCLUDE_ASM("weapon/nonmatchings/w_029", func_ptr_80170024);

void func_ptr_80170028(Entity* self) {
    if (self->ext.weapon.parent->entityId == 0) {
        DestroyEntity(self);
        return;
    }
    if (self->step == 0) {
        self->ext.weapon.equipId = self->ext.weapon.parent->ext.weapon.equipId;
        SetWeaponProperties(self, 0);
        self->hitboxHeight = 14;
        self->hitboxWidth = 14;
        self->ext.weapon.unk80 = 10;
        self->step++;
        return;
    }
    if (--self->ext.weapon.unk80 == 0) {
        DestroyEntity(self);
    }
}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
