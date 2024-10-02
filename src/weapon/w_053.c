// SPDX-License-Identifier: AGPL-3.0-or-later
// Weapon ID #53. Used by weapons:
// Katana, Osafune katana, Masamune, Yasutsuna, Unknown#189, Unknown#192,
// Unknown#193, Unknown#194
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_053_1.h"
#include "w_053_2.h"
#include "w_053_056.h"
#define g_Animset w_053_1
#define g_Animset2 w_053_2

extern WeaponAnimation D_177000_8017AF4C[];

void EntityWeaponAttack(Entity* self) {
    WeaponAnimation* anim;
    s16 animIndex;

    self->posX.val = PLAYER.posX.val;
    self->posY.val = PLAYER.posY.val;
    self->facingLeft = PLAYER.facingLeft;

    animIndex = (self->params & 0x7FFF) >> 8;
    anim = &D_177000_8017AF4C[animIndex];

    if (PLAYER.ext.player.anim >= anim->frameStart &&
        PLAYER.ext.player.anim < (anim->frameStart + 7) &&
        g_Player.unk46 != 0) {
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
            self->flags = FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;
            self->zPriority = PLAYER.zPriority - 2;
            self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;

            switch (animIndex) {
            case 0:
                break;
            case 1:
                self->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE;
                g_api.CreateEntFactoryFromEntity(self, WFACTORY(56, 0), 0);
                break;
            case 2:
                break;
            case 3:
                self->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE;
                g_api.CreateEntFactoryFromEntity(self, WFACTORY(56, 10), 0);
                break;
            case 4:
                g_api.CreateEntFactoryFromEntity(self, WFACTORY(56, 0x14), 0);
                break;
            }
            SetWeaponProperties(self, 0);
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
    } else {
        DestroyEntity(self);
        return;
    }

    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;
}

extern W053_056Config D_177000_8017AFC4[];
extern u16 D_177000_8017AF9C[];
extern u16 D_177000_8017AFB0[];

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

    config = &D_177000_8017AFC4[params];

    if (self->step == 0) {
        self->facingLeft = PLAYER.facingLeft;
        self->ext.weapon.unk82 = 20;
        if (self->facingLeft != 0) {
            self->ext.weapon.unk82 = -20;
        }
        self->ext.weapon.unk80 = -5;
        if (g_Player.unk0C & PLAYER_STATUS_UNK_20) {
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
            self->flags =
                FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS | FLAG_UNK_20000;

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
        prim->clut = clut + D_177000_8017AFB0[self->ext.weapon.unk7E];
    } else {
        prim->clut = clut + D_177000_8017AF9C[self->ext.weapon.unk7E];
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
        if (g_Player.unk0C & PLAYER_STATUS_UNK_20) {
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

static void func_ptr_80170008(Entity* self) {
    switch (self->step) {
    case 0:
        self->palette = PAL_OVL(0x100);
        self->zPriority = PLAYER.zPriority;
        self->facingLeft = PLAYER.facingLeft;
        self->animCurFrame = PLAYER.animCurFrame + ANIM_FRAME_LOAD;
        self->animSet = 1;
        self->drawMode = DRAW_TPAGE;
        self->unk5A = 0;
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_UNK_20000;

        SetSpeedX(FIX(8));
        self->velocityY = FIX(-0.5);
        if (self->params & 0x7F00) {
            g_api.CreateEntFactoryFromEntity(self, WFACTORY(0x38, 0x28), 0);
        }
        self->step++;
        break;
    case 1:
        self->animCurFrame = PLAYER.animCurFrame + ANIM_FRAME_LOAD;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        DecelerateX(FIX(15) / 32);
        if (PLAYER.animFrameIdx == 6) {
            g_api.CreateEntFactoryFromEntity(self, WFACTORY(0x38, 0x1E), 0);
            self->step++;
        }
        break;
    case 2:
        self->drawMode = DRAW_DEFAULT;
        self->animCurFrame = PLAYER.animCurFrame + ANIM_FRAME_LOAD;
        if (PLAYER.animFrameIdx == 8 && PLAYER.animFrameDuration == 1) {
            g_api.CreateEntFactoryFromEntity(self, WFACTORY(0x38, 0x1E), 0);
        }
        if (PLAYER.animFrameIdx == 10) {
            SetSpeedX(FIX(-8));
            self->velocityY = FIX(0.5);
            self->step++;
        }
        break;
    case 3:
        self->drawMode = DRAW_TPAGE;
        self->animCurFrame = PLAYER.animCurFrame + ANIM_FRAME_LOAD;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        DecelerateX(FIX(15) / 32);
        if (PLAYER.animFrameIdx == 15) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;
}

void func_ptr_8017000C(Entity* self) {
    Primitive* prim;
    W053_056Config* config;
    s32 params;
    s32 clut;
    u16 x, y;
    u8 u, v;
    s16 angle;
    s16 lifetime;
    s32 shift;

    params = (self->params >> 8) & 0x7F;

    if (g_HandId != 0) {
        v = 0x80;
        clut = 0x18;
    } else {
        clut = 0;
        v = 0;
    }

    config = &D_177000_8017AFC4[params];

    if (self->step == 0) {
        self->facingLeft = PLAYER.facingLeft;
        self->ext.weapon.unk80 = -5;
        if (g_Player.unk0C & PLAYER_STATUS_UNK_20) {
            self->ext.weapon.unk80 = 0xB;
        }
        self->posY.i.hi = self->posY.i.hi + self->ext.weapon.unk80;
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);

        if (self->primIndex != -1) {
            prim = &g_PrimBuf[self->primIndex];
            if (config->uFlag) {
                prim->u0 = prim->u2 = 0xC0;
                prim->u1 = prim->u3 = 0x80;
            } else {
                prim->u0 = prim->u2 = 0x80;
                prim->u1 = prim->u3 = 0xC0;
            }

            if (config->vFlag) {
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

            self->flags =
                FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS | FLAG_UNK_20000;

            if (params == 0) {
                SetWeaponProperties(self, 0);
                self->enemyId = self->ext.weapon.parent->enemyId;
                self->hitboxWidth = 30;
                self->hitboxHeight = 32;
            }

            if (!(params & 3)) {
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

    if (params == 0) {
        g_api.CreateEntFactoryFromEntity(
            self,
            ((g_HandId + 1) << 12) + 0x38 +
                ((self->ext.weapon.unk7E + 1) << 16),
            0);
    }

    prim = &g_PrimBuf[self->primIndex];

    if (config->clutFlag) {
        prim->clut = clut + D_177000_8017AFB0[self->ext.weapon.unk7E];
    } else {
        prim->clut = clut + D_177000_8017AF9C[self->ext.weapon.unk7E];
    }

    self->ext.weapon.unk7E++;
    if (self->ext.weapon.unk7E >= 9) {
        DestroyEntity(self);
        return;
    }

    self->hitboxOffX = 0x12;

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

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 53; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
