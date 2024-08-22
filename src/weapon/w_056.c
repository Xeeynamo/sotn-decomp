// SPDX-License-Identifier: AGPL-3.0-or-later
// Weapon ID #56. Used by weapons:
// Muramasa
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_056_1.h"
#include "w_056_2.h"
#include "w_053_056.h"
#define g_Animset w_056_1
#define g_Animset2 w_056_2

extern WeaponAnimation D_18C000_8017AF64[];
extern u16 D_18C000_8017AF94[];
extern u16 D_18C000_8017AF9C[];

void EntityWeaponAttack(Entity* self) {
    WeaponAnimation* anim;
    s16 animIndex;
    Primitive* prim;
    s32 i;
    s16 x;
    s32 y;
    s32 x2;
    s32 offsetIndex;
    u8 brightness;
    u16* xValues;
    s32 primIndex;

    self->posX.val = PLAYER.posX.val;
    self->posY.val = PLAYER.posY.val;
    self->facingLeft = PLAYER.facingLeft;

    animIndex = (self->params >> 8) & 0x7F;

    if (g_Player.D_80072F00[11] != 0) {
        animIndex = 2;
    }

    anim = &D_18C000_8017AF64[animIndex];

    if (PLAYER.ext.player.anim < anim->frameStart ||
        PLAYER.ext.player.anim >= (anim->frameStart + 7) ||
        g_Player.unk46 == 0) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        SetSpriteBank1(g_Animset);
        self->animSet = ANIMSET_OVL(0x10);
        self->palette = PAL_DRA(0x110);
        self->unk5A = 0x64;
        if (g_HandId != 0) {
            self->animSet += 2;
            self->palette += 0x18;
            self->unk5A += 2;
        }
        self->palette += anim->palette;
        self->flags = FLAG_UNK_40000 | FLAG_UNK_20000;

        primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 0xC);

        self->primIndex = primIndex;
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            prim = &g_PrimBuf[self->primIndex];
            for (i = 0; i < 12; i++) {
                if (i <= 3) {
                    prim->r2 = rand() & 3;
                    prim->b2 = 1;
                }
                if (i < 7) {
                    prim->r2 = rand() & 7;
                    prim->b2 = 1;
                } else if (i & 1) {
                    prim->r2 = rand() & 0xF;
                    prim->b2 = 2;
                } else {
                    prim->r2 = rand() & 7;
                    prim->b2 = 1;
                }
                prim->r3 = i / 6;
                if (i == 11) {
                    prim->r2 = 0x18;
                    prim->r3 = 2;
                    prim->b2 = 3;
                }
                prim->r0 = prim->r1 = 255;
                prim->b0 = prim->b1 = prim->g0 = prim->g1 = rand() & 0x1F;

                prim->priority = PLAYER.zPriority;
                prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_HIDE;
                prim = prim->next;
            }
        }

        self->zPriority = PLAYER.zPriority - 2;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        SetWeaponProperties(self, 0);

        if (self->attack >= 0x1E) {
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xC) + FACTORY(0, 56), 0);
        }
        self->step++;
    }

    self->ext.weapon.anim = PLAYER.ext.player.anim - anim->frameStart;

    if (PLAYER.animFrameDuration == 1 &&
        PLAYER.animFrameIdx == anim->soundFrame) {
        g_api.PlaySfx(anim->soundId);
    }

    if (g_api.UpdateUnarmedAnim(anim->frameProps, anim->frames) < 0) {
        DestroyEntity(self);
        return;
    }

    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;

    if (self->animCurFrame != 0xD && self->animCurFrame != 0x22 &&
        self->animCurFrame != 0x2C && self->animCurFrame != 0x3E) {
        return;
    }

    if (self->primIndex != -1) {
        i = 0;

        xValues = D_18C000_8017AF94;
        self->flags |= FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];

        for (; i < 12; i++) {
            switch (self->animCurFrame) {
            case 0xD:
                offsetIndex = 0;
                break;
            case 0x22:
                offsetIndex = 1;
                break;
            case 0x2C:
                offsetIndex = 2;
                break;
            case 0x3E:
                offsetIndex = 3;
                break;
            }

            x2 = -1;
            x = xValues[offsetIndex] - i;
            if (self->facingLeft != 0) {
                x = -x;
                x2 = 1;
            }
            prim->x2 = x2 + prim->x2;

            y = D_18C000_8017AF9C[offsetIndex] + (i / 6);

            prim->x0 = x + self->posX.i.hi;
            prim->x1 = prim->x0 + prim->x2;

            prim->y0 = y + self->posY.i.hi;
            prim->y1 = y + self->posY.i.hi + prim->r3;

            if (prim->r2 > prim->r3) {
                prim->r3 += prim->b2;
            }

            prim->drawMode &= ~DRAW_HIDE;
            prim = prim->next;
        }
    }
}

extern s16 D_18C000_8017AFA4[];
extern s16 D_18C000_8017AFB8[];
extern W053_056Config D_18C000_8017AFCC[];

s32 func_ptr_80170004(Entity* self) {
    Primitive* prim;
    W053_056Config* config;
    s16 angle;
    s32 shift;
    s16 x, y;
    s16 lifetime;
    s32 clut;
    u8 u, v;
    u16 params;

    u32 factory;

    params = (self->params >> 8) & 0x7F;

    if (g_HandId != 0) {
        v = 0x80;
        clut = 0x18;
    } else {
        clut = 0;
        v = 0;
    }

    config = &D_18C000_8017AFCC[params];

    if (self->step == 0) {
        self->facingLeft = PLAYER.facingLeft;
        self->ext.weapon.unk82 = 20;
        if (self->facingLeft != 0) {
            self->ext.weapon.unk82 = -20;
        }
        self->ext.weapon.unk80 = -5;
        if (g_Player.unk0C & 0x20) {
            self->ext.weapon.unk80 = 11;
        }
        self->posX.i.hi += self->ext.weapon.unk82;
        self->posY.i.hi += self->ext.weapon.unk80;

        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);

        if (self->primIndex != -1) {
            prim = &g_PrimBuf[self->primIndex];

            if (config->uFlag != 0) {
                prim->u0 = prim->u2 = 0xC0;
                prim->u1 = prim->u3 = 0x80;
            } else {
                prim->u0 = prim->u2 = 0x80;
                prim->u1 = prim->u3 = 0xC0;
            }

            if (config->vFlag != 0) {
                prim->v1 = v | 0x40;
                prim->v0 = v | 0x40;
                prim->v3 = v;
                prim->v2 = v;
            } else {
                prim->v1 = v;
                prim->v0 = v;
                prim->v3 = v | 0x40;
                prim->v2 = v | 0x40;
            }

            prim->r0 = prim->r1 = prim->r2 = prim->r3 = config->r;
            prim->g0 = prim->g1 = prim->g2 = prim->g3 = config->g;
            prim->b0 = prim->b1 = prim->b2 = prim->b3 = config->b;

            prim->tpage = 0x19;
            prim->priority = PLAYER.zPriority + 2;
            prim->drawMode = DRAW_UNK_100 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
            self->flags = FLAG_UNK_08000000 | FLAG_HAS_PRIMS | FLAG_UNK_20000;

            if ((params == 0) || (params == 0xA) || (params == 0x14) ||
                (params == 0x1E) || (params > 0x27 && params <= 0x31)) {
                self->ext.weapon.equipId =
                    self->ext.weapon.parent->ext.weapon.equipId;
                SetWeaponProperties(self, 0);
                self->enemyId = self->ext.weapon.parent->enemyId;
                self->hitboxWidth = 30;
                self->hitboxHeight = 32;
            }

            if ((params & 3) == 0) {
                g_api.PlaySfx(SFX_WEAPON_SWISH_C);
            }
            self->rotZ = config->rotZ;
            self->ext.weapon.lifetime = config->lifetime;
            self->ext.weapon.unk7E = 0;
            self->step++;
        } else {
            DestroyEntity(self);
            return;
        }
    }

    if ((params == 0) || (params == 0xA) || (params == 0x14) ||
        (params == 0x1E) || (params == 0x28)) {
        factory = params + 1;
        factory = ((g_HandId + 1) << 0xC) + 0x38 +
                  ((self->ext.weapon.unk7E + (factory)) << 0x10);
        g_api.CreateEntFactoryFromEntity(self, factory, 0);
    }
    prim = &g_PrimBuf[self->primIndex];
    if (config->clutFlag != 0) {
        prim->clut = clut + D_18C000_8017AFB8[self->ext.weapon.unk7E];
    } else {
        prim->clut = clut + D_18C000_8017AFA4[self->ext.weapon.unk7E];
    }

    self->ext.weapon.unk7E++;
    if (self->ext.weapon.unk7E >= 9) {
        DestroyEntity(self);
        return;
    }

    if (params >= 0x1E && params < 0x32) {
        self->hitboxOffX = 0x12;
    } else {
        self->ext.weapon.unk82 = 0x26;
        if (self->facingLeft) {
            self->ext.weapon.unk82 = -0x26;
        }
        self->ext.weapon.unk80 = -5;
        if (g_Player.unk0C & 0x20) {
            self->ext.weapon.unk80 = 0xB;
        }
        self->posX.i.hi = self->ext.weapon.unk82 + PLAYER.posX.i.hi;
        self->posY.i.hi = self->ext.weapon.unk80 + PLAYER.posY.i.hi;
    }

    x = self->posX.i.hi;
    y = self->posY.i.hi;

    lifetime = self->ext.weapon.lifetime;
    angle = self->rotZ;
    // this may seem silly, however the right shift
    // for assigning `prim->y`_X_ on PSX uses `srav`
    // and this ensures 8 gets put into a register.
    // the shifts used to compute the value for `x`_X_
    // also shift by 8, but that is done with `sra`
    // which uses the immediate value. 🤦
    shift = 8;

    angle += 1536;
    if (self->facingLeft) {
        prim->x0 = x - (((rcos(angle) >> 4) * lifetime) >> 8);
    } else {
        prim->x0 = x + (((rcos(angle) >> 4) * lifetime) >> 8);
    }
    prim->y0 = y - (((rsin(angle) >> 4) * lifetime) >> shift);

    angle -= 1024;
    if (self->facingLeft) {
        prim->x1 = x - (((rcos(angle) >> 4) * lifetime) >> 8);
    } else {
        prim->x1 = x + (((rcos(angle) >> 4) * lifetime) >> 8);
    }
    prim->y1 = y - (((rsin(angle) >> 4) * lifetime) >> shift);

    angle -= 2048;
    if (self->facingLeft) {
        prim->x2 = x - (((rcos(angle) >> 4) * lifetime) >> 8);
    } else {
        prim->x2 = x + (((rcos(angle) >> 4) * lifetime) >> 8);
    }
    prim->y2 = y - (((rsin(angle) >> 4) * lifetime) >> shift);

    angle += 1024;
    if (self->facingLeft) {
        prim->x3 = x - (((rcos(angle) >> 4) * lifetime) >> 8);
    } else {
        prim->x3 = x + (((rcos(angle) >> 4) * lifetime) >> 8);
    }
    prim->y3 = y - (((rsin(angle) >> 4) * lifetime) >> shift);
}

static void func_ptr_80170008(Entity* self) {}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 56; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
