// SPDX-License-Identifier: AGPL-3.0-only
// Weapon ID #14. Used by weapons:
// Runesword
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_014_1.h"
#include "w_014_2.h"
#define g_Animset w_014_1
#define g_Animset2 w_014_2

extern u8 D_8007341E;
extern u8 D_8007341F;

void EntityWeaponAttack(Entity* self) {
    Primitive* prim;
    s16 angle;
    s16 unk9C;
    s16 start;
    s16 end;
    s16 xPreviousA;
    s16 xPreviousB;
    s16 yPreviousA;
    s16 yPreviousB;
    s16 xDiff, yDiff;
    s16 xVar, yVar;
    s16 offsetY;
    s16 step;
    s32 range;
    s32 i;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x30);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        SetSpriteBank1(g_Animset);
        self->animSet = ANIMSET_OVL(0x10);
        self->unk5A = 0x64;
        self->palette = 0x11C;
        if (g_HandId != 0) {
            self->palette = 0x134;
            self->unk5A = 0x66;
            self->animSet += 2;
        }
        self->animCurFrame = 8;
        self->facingLeft = PLAYER.facingLeft;
        self->zPriority = PLAYER.zPriority - 2;
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_04000000 | FLAG_HAS_PRIMS |
                      FLAG_UNK_20000;
        SetSpeedX(FIX(6));
        self->velocityY = FIX(1);
        offsetY = PLAYER.posY.i.hi + PLAYER.hitboxOffY;
        self->posY.i.hi = offsetY - 8;
        if (PLAYER.step != Player_Crouch) {
            self->posY.i.hi = offsetY - 16;
        }
        if (self->facingLeft != 0) {
            self->posX.i.hi = PLAYER.posX.i.hi - PLAYER.hitboxOffX;
        } else {
            self->posX.i.hi = PLAYER.posX.i.hi + PLAYER.hitboxOffX;
        }
        self->velocityX += PLAYER.velocityX;
        self->ext.weapon_014.unk7C = 0x16;
        SetWeaponProperties(self, 0);
        DestroyEntityWeapon(true);
        self->hitboxHeight = 4;
        self->hitboxWidth = 4;
        self->rotZ = -0x700;
        self->drawFlags |= FLAG_DRAW_ROTZ;

        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; prim != NULL; i++) {
            prim->r0 = 0;
            prim->g0 = 0x10;
            if (i == 0) {
                angle = self->rotZ;
                prim->x0 = self->posX.i.hi + (((rcos(angle) >> 4) * 47) >> 8);
                if (self->facingLeft) {
                    prim->x0 =
                        self->posX.i.hi - (((rcos(angle) >> 4) * 47) >> 8);
                }
                prim->y0 = self->posY.i.hi + (((rsin(angle) >> 4) * 47) >> 8);

                prim->x2 = self->posX.i.hi + (rcos(angle) >> 9);
                if (self->facingLeft) {
                    prim->x2 = self->posX.i.hi - (rcos(angle) >> 9);
                }
                prim->y2 = self->posY.i.hi + (rsin(angle) >> 9);
            }
            prim->clut = 0x11D;
            prim->tpage = 0x19;
            prim->v0 = prim->v1 = 0x60;
            prim->v2 = prim->v3 = 0x7F;

            if (self->params & 0x8000) {
                prim->v0 = prim->v1 = 0xE0;
                prim->v2 = prim->v3 = 0xFF;
                prim->clut = 0x135;
            }
            prim->priority = self->zPriority - 2;
            prim->drawMode = DRAW_UNK_100 | DRAW_UNK_40 | DRAW_TPAGE2 |
                             DRAW_TPAGE | DRAW_HIDE | DRAW_UNK02 | DRAW_TRANSP;
            prim = prim->next;
        }

        g_api.PlaySfxVolPan(SFX_WEAPON_ENERGY, 0x50, 0);
        g_api.PlaySfx(SFX_BONE_SWORD_SWISH_A);
        g_Player.D_80072F00[10] = 4;
        g_api.CreateEntFactoryFromEntity(
            self, ((g_HandId + 1) << 0xC) | 0x72, 0);
        self->step++;
        break;
    case 1:
        self->rotZ += 0x70;
        if (self->rotZ > 0) {
            self->rotZ = 0;
        }
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (--self->ext.weapon_014.unk7C < 7) {
            DecelerateX(FIX(14));
        }
        if (self->ext.weapon_014.unk7C == 0) {
            self->ext.weapon_014.unk7C = 8;
            SetSpeedX(-FIX(3));
            self->step++;
        }
        break;
    case 2:
        self->drawFlags &= ~FLAG_DRAW_ROTZ;
        self->posX.val += self->velocityX;
        if (--self->ext.weapon_014.unk7C == 0) {
            self->step++;
        }
        break;
    case 3:
        xDiff = abs((PLAYER.posX.i.hi + PLAYER.hitboxOffX) - self->posX.i.hi);
        if (xDiff < (D_8007341E + 16) / 2) {
            yDiff =
                abs((PLAYER.posY.i.hi + PLAYER.hitboxOffY) - self->posY.i.hi);
            if (yDiff < (D_8007341F + 4) / 2) {
                DestroyEntity(self);
                return;
            }
        }
        xVar = (PLAYER.posX.i.hi + PLAYER.hitboxOffX) - self->posX.i.hi;
        yVar = (PLAYER.posY.i.hi + PLAYER.hitboxOffY) - self->posY.i.hi;
        angle = ratan2(-yVar, xVar) & 0xFFF;
        self->posX.val += (rcos(angle) << 5) * 5;
        self->posY.val -= (rsin(angle) << 5) * 5;
        if (self->facingLeft) {
            self->rotZ = angle;
        } else {
            self->rotZ = 0x800 - angle;
        }
        self->drawFlags |= FLAG_DRAW_ROTZ;
        break;
    }

    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; prim != NULL; i++) {
        if (i != 0) {
            prim->x0 = xPreviousA;
            prim->y0 = yPreviousA;
            prim->x2 = xPreviousB;
            prim->y2 = yPreviousB;
        }
        if (prim->r0 == 0 && i == self->ext.weapon_014.unk9C - 1) {
            angle = self->rotZ;
            prim->x1 = self->posX.i.hi + (((rcos(angle) >> 4) * 47) >> 8);
            if (self->facingLeft) {
                prim->x1 = self->posX.i.hi - (((rcos(angle) >> 4) * 47) >> 8);
            }
            prim->y1 = self->posY.i.hi + (((rsin(angle) >> 4) * 47) >> 8);

            prim->x3 = self->posX.i.hi + (rcos(angle) >> 9);
            if (self->facingLeft) {
                prim->x3 = self->posX.i.hi - (rcos(angle) >> 9);
            }
            prim->y3 = self->posY.i.hi + (rsin(angle) >> 9);
            prim->drawMode &= ~DRAW_HIDE;
            prim->r0++;
        }
        xPreviousA = prim->x1;
        yPreviousA = prim->y1;
        xPreviousB = prim->x3;
        yPreviousB = prim->y3;
        if (self->ext.weapon_014.unk9C - 1 >= 0x11 &&
            i < self->ext.weapon_014.unk9C - 0x11) {
            prim->drawMode |= DRAW_HIDE;
        }
        prim = prim->next;
    }

    unk9C = self->ext.weapon_014.unk9C;
    if (self->ext.weapon_014.unk9C != 0) {
        end = (unk9C > 47) ? 47 : unk9C - 1;
        start = unk9C - 16;
        if (start < 0) {
            start = 0;
        }
        if (start > 47) {
            start = 47;
        }
        range = (end - start) + 1;
        if (range == 0) {
            range = 1;
        }

        step = 128 / range;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; prim != NULL; i++) {
            if (i >= start && i <= end) {
                prim->u0 = prim->u2 = (i - start) * step;
                prim->u1 = prim->u3 = (i - start + 1) * step;
            }
            prim = prim->next;
        }
    }
    self->ext.weapon_014.unk9C++;
}

s32 func_ptr_80170004(Entity* self) {
    s16 angle;
    u16 baseX, baseY;
    s16 paramsLo;

    if (self->ext.weapon.parent->entityId == 0) {
        DestroyEntity(self);
        return;
    }
    paramsLo = self->params & 0xFF;
    angle = 0;
    if (self->step == 0) {
        self->facingLeft = self->ext.weapon.parent->facingLeft;
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_04000000 | FLAG_UNK_20000;
        self->ext.weapon.equipId = self->ext.weapon.parent->ext.weapon.equipId;
        SetWeaponProperties(self, 0);
        self->enemyId = self->ext.weapon.parent->enemyId;
        self->hitboxWidth = 4;
        self->hitboxHeight = 4;
        self->step++;
    }

    if (self->ext.weapon.parent->drawFlags & FLAG_DRAW_ROTZ) {
        angle = self->ext.weapon.parent->rotZ;
    }
    if (self->facingLeft) {
        angle = 0x800 - angle;
    }
    switch (paramsLo) {
    case 0:
        baseX = ((rcos(angle) >> 4) * 5) >> 7;
        baseY = ((rsin(angle) >> 4) * 5) >> 7;
        break;
    case 1:
        baseX = ((rcos(angle) >> 4) * 5) >> 6;
        baseY = ((rsin(angle) >> 4) * 5) >> 6;
        break;
    case 2:
        baseX = ((rcos(angle) >> 4) * 0xF) >> 7;
        baseY = ((rsin(angle) >> 4) * 0xF) >> 7;
        break;
    case 3:
        baseX = ((rcos(angle) >> 4) * 5) >> 5;
        baseY = ((rsin(angle) >> 4) * 5) >> 5;
        break;
    }
    self->posX.i.hi = baseX + self->ext.weapon.parent->posX.i.hi;
    self->posY.i.hi = baseY + self->ext.weapon.parent->posY.i.hi;
}

static void func_ptr_80170008(Entity* self) {}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 14; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
