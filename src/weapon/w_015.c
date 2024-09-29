// SPDX-License-Identifier: AGPL-3.0-or-later
// Weapon ID #15. Used by weapons:
// Shuriken, Cross shuriken, Buffalo star, Flame star, TNT
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_015_1.h"
#include "w_015_2.h"
#define g_Animset w_015_1
#define g_Animset2 w_015_2
#include "sfx.h"

extern SpriteParts D_6D000_8017A2B0[];
extern s16 D_6D000_8017A6B8[];
extern AnimationFrame D_6D000_8017A6C0[];
extern s16 D_6D000_8017A6FC[];
extern s16 D_6D000_8017A71C[];
extern AnimationFrame D_6D000_8017A770[];
extern s16 D_6D000_8017A78C[];
extern s32 D_6D000_8017BFC8;

void EntityWeaponAttack(Entity* self) {
    switch (self->step) {
    case 0:
        SetSpriteBank1(g_Animset);
        self->animSet = ANIMSET_OVL(0x10);
        self->palette = PAL_DRA(0x110);
        self->unk5A = 0x64;
        if (g_HandId) {
            self->animSet += 2;
            self->palette = PAL_DRA(0x128);
            self->unk5A = 0x66;
        }
        self->animCurFrame = D_6D000_8017A6B8[((self->params >> 8) & 0x7F)];
        self->facingLeft = PLAYER.facingLeft;
        self->zPriority = PLAYER.zPriority - 2;
        self->flags = FLAG_POS_CAMERA_LOCKED;

        SetSpeedX(FIX(8));
        if (((self->params >> 8) & 0x7F) == 3) {
            SetSpeedX(FIX(5.33333));
        }
        self->posY.i.hi = PLAYER.posY.i.hi + PLAYER.hitboxOffY - 3;
        if (PLAYER.step != 2) {
            self->posY.i.hi -= 6;
        }

        if (self->facingLeft != 0) {
            self->posX.i.hi = PLAYER.posX.i.hi - PLAYER.hitboxOffX;
        } else {
            self->posX.i.hi = PLAYER.posX.i.hi + PLAYER.hitboxOffX;
        }

        SetWeaponProperties(self, 0);
        DestroyEntityWeapon(true);

        self->hitboxWidth = 4;
        self->hitboxHeight = 4;
        if (((self->params >> 8) & 0x7F) == 1) {
            self->drawFlags |= FLAG_DRAW_ROTZ;
        }
        if (((self->params >> 8) & 0x7F) == 3) {
            self->palette = PAL_OVL(0x160);
            self->drawFlags |= FLAG_DRAW_ROTZ;
        }
        if (!((self->params >> 8) & 0x7F)) {
            g_api.PlaySfx(SFX_WEAPON_SWISH_A);
        } else {
            g_api.PlaySfx(SFX_ARROW_SHOT_A);
            if (((self->params >> 8) & 0x7F) == 3) {
                g_api.PlaySfx(SFX_FIREBALL_SHOT_B);
            }
        }
        g_Player.timers[10] = 4;
        self->step++;
        break;

    case 1:
        self->rotZ = self->rotZ + 256;
        self->posX.val += self->velocityX;

        if ((((self->params >> 8) & 0x7F) == 2) &&
            !((u16)self->ext.weapon.lifetime & 1)) {
            g_api.CreateEntFactoryFromEntity(self, WFACTORY(58, 0), 0);
        }

        if (((self->params >> 8) & 0x7F) == 3) {
            g_api.CreateEntFactoryFromEntity(self, WFACTORY(80, 0), 0);
        }

        self->ext.weapon.lifetime++;

        if (self->hitFlags != 0) {
            self->ext.weapon.lifetime = 24;
            self->hitboxState = 0;
            self->drawFlags |= FLAG_DRAW_UNK80;
            self->step++;
        }
        break;

    case 2:
        self->ext.weapon.lifetime--;
        if (self->ext.weapon.lifetime == 0) {
            DestroyEntity(self);
        }
        break;
    }
}

s32 func_ptr_80170004(Entity* self) {
    if (self->step == 0) {
        self->animSet = self->ext.weapon.parent->animSet;
        self->animCurFrame = self->ext.weapon.parent->animCurFrame;
        self->facingLeft = self->ext.weapon.parent->facingLeft;
        self->zPriority = self->ext.weapon.parent->zPriority - 2;
        self->flags = FLAG_POS_CAMERA_LOCKED;
        self->palette = self->ext.weapon.parent->palette;
        self->unk5A = self->ext.weapon.parent->unk5A;
        self->ext.generic.unk7C.s = 10;
        self->drawMode = DRAW_TPAGE;
        self->drawFlags = FLAG_DRAW_UNK8;
        self->unk6C = 0x80;
        self->step++;
    }
    if (self->unk6C >= 0x30) {
        self->unk6C += 0xF8;
    }

    if (--self->ext.generic.unk7C.s == 0) {
        DestroyEntity(self);
    }
}

static void func_ptr_80170008(Entity* self) {
    Entity* factory;

    if (self->step == 0) {
        self->animSet = 2;
        self->anim = D_6D000_8017A6C0;
        self->zPriority = PLAYER.zPriority - 4;
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_UNK_100000;
        self->velocityY = FIX(-1);

        if (!(D_6D000_8017BFC8 & 1)) {
            factory = g_api.CreateEntFactoryFromEntity(self, FACTORY(4, 11), 0);
            if (factory != NULL) {
                if (g_HandId == 0) {
                    factory->entityId = 0xEF;
                } else {
                    factory->entityId = 0xFF;
                }
            }
        }

        self->posY.i.hi += (rand() % 12) - 6;
        self->posX.i.hi += (rand() & 7) - 3;
        D_6D000_8017BFC8++;

        if (!(rand() & 1)) {
            self->drawMode =
                FLAG_DRAW_UNK40 | FLAG_DRAW_UNK20 | FLAG_DRAW_UNK10;
        }
        self->step++;
    }
    self->posY.val += self->velocityY;
    if (self->animFrameDuration < 0) {
        DestroyEntity(self);
    }
}

void func_ptr_8017000C(Entity* self) {
    Collider collider;
    Primitive* prim;
    s16 xOffset, yOffset;
    s16 x, y;
    Entity* e;

    switch (self->step) {
    case 0:
        SetSpriteBank1(g_Animset);

        self->animSet = ANIMSET_OVL(0x10);
        self->unk5A = 0x64;
        self->palette = PAL_DRA(0x110);

        if (g_HandId) {
            self->palette = PAL_DRA(0x128);
            self->unk5A = 0x66;
            self->animSet += 2;
        }

        self->facingLeft = PLAYER.facingLeft;
        self->zPriority = PLAYER.zPriority - 2;
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;

        self->primIndex = g_api.AllocPrimitives(PRIM_TILE, 32);

        if (self->primIndex == -1) {
            self->flags &= ~FLAG_HAS_PRIMS;
        }

        if (self->flags & FLAG_HAS_PRIMS) {
            prim = &g_PrimBuf[self->primIndex];
            while (prim != NULL) {
                prim->r0 = 128;
                prim->g0 = 64;
                prim->b0 = 0;
                prim->u0 = prim->v0 = 1;
                prim->x1 = rand() & 0xF;
                prim->x2 = 0;
                prim->x3 = rand() & 0xF;
                prim->priority = self->zPriority - 2;
                prim->drawMode = DRAW_HIDE | DRAW_UNK02;
                prim = prim->next;
            }
        }
        self->ext.weapon.lifetime = 10;
        self->velocityY = FIX(-5.0 / 2.0);
        SetSpeedX(FIX(3.0 / 2.0));

        self->posY.i.hi = PLAYER.posY.i.hi + PLAYER.hitboxOffY - 8;
        if (PLAYER.step != 2) {
            self->posY.i.hi -= 6;
        }

        self->attack = 1;
        self->attackElement = ELEMENT_HIT;
        self->hitboxState = 2;
        self->nFramesInvincibility = 20;
        self->stunFrames = 4;
        self->hitEffect = 1;
        self->entityRoomIndex = 0;
        g_api.func_80118894(self);
        DestroyEntityWeapon(true);

        self->hitboxWidth = 4;
        self->hitboxHeight = 4;
        g_api.PlaySfx(SFX_WEAPON_SWISH_C);
        g_Player.timers[10] = 4;
        self->step++;
        break;

    case 1:
        if (!(g_GameTimer & 7)) {
            g_api.PlaySfx(SFX_WATER_DAMAGE_SWISHES);
        }
        self->animCurFrame = 13;
        self->posX.val += self->velocityX;

        self->posY.val += self->velocityY;
        if (self->velocityY <= FIX(458751.0 / 65536.0)) {
            self->velocityY += FIX(1.0 / 8.0);
        }

        if (self->hitFlags) {
            self->velocityX = self->velocityX * 2 / 3;
            self->hitFlags = 0;
            return;
        }

        xOffset = 4;
        if (self->velocityX < 0) {
            xOffset = -xOffset;
        }
        yOffset = 0;
        x = self->posX.i.hi + xOffset;
        y = self->posY.i.hi + yOffset;
        g_api.CheckCollision(x, y, &collider, 0);
        if (collider.effects & EFFECT_UNK_0002) {
            if (xOffset < 0) {
                self->posX.i.hi += collider.unkC;
            } else {
                self->posX.i.hi += collider.unk4;
            }
            self->velocityX = -(self->velocityX / 2);
        }

        xOffset = 0;
        yOffset = -4;
        x = self->posX.i.hi + xOffset;
        y = self->posY.i.hi + yOffset;
        g_api.CheckCollision(x, y, &collider, 0);

        if (collider.effects & EFFECT_SOLID) {
            self->posY.i.hi += 1 + collider.unk20;
            self->velocityY = FIX(1);
            self->velocityX = self->velocityX / 2;
        }

        xOffset = 0;
        yOffset = 6;
        x = self->posX.i.hi + xOffset;
        y = self->posY.i.hi + yOffset;
        g_api.CheckCollision(x, y, &collider, 0);

        if (collider.effects & EFFECT_SOLID) {
            e = g_api.CreateEntFactoryFromEntity(self, WFACTORY(76, 0), 0);
            e = g_api.CreateEntFactoryFromEntity(self, WFACTORY(78, 16), 0);
            g_api.func_80102CD8(3);
            self->step++;
            self->velocityY = FIX(-6);
            self->ext.weapon.lifetime = 16;

            if (self->flags & FLAG_HAS_PRIMS) {
                prim = &g_PrimBuf[self->primIndex];
                while (prim != NULL) {
                    prim->drawMode |= DRAW_HIDE;
                    prim = prim->next;
                }
            }
        }

        x = self->posX.i.hi;
        y = self->posY.i.hi;

        if (self->flags & FLAG_HAS_PRIMS) {
            prim = &g_PrimBuf[self->primIndex];
            while (prim) {
                if (prim->x3 == 0) {
                    if (self->facingLeft) {
                        prim->x0 = x - 8 -
                                   (D_6D000_8017A6FC[prim->x1] * prim->x2 / 15);
                    } else {
                        prim->x0 = x + 8 +
                                   (D_6D000_8017A6FC[prim->x1] * prim->x2 / 15);
                    }

                    prim->y0 = y + (D_6D000_8017A71C[prim->x1] * prim->x2 / 15);

                    prim->x2++;
                    if (prim->x2 > 15) {
                        prim->x2 = 0;
                        prim->x1 = rand() & 0xF;
                    }

                    prim->drawMode &= ~DRAW_HIDE;
                } else {
                    prim->x3--;
                }
                prim = prim->next;
            }
        }
        break;

    case 2:
        self->hitboxState = 0;
        if ((self->ext.weapon.unk7E & 7) == 0) {
            g_api.PlaySfx(SFX_FM_EXPLODE_B);
        }
        self->animCurFrame = 0;
        self->posY.val += self->velocityY;

        if (--self->ext.weapon.lifetime == 0) {
            DestroyEntity(self);
            return;
        }

        if (self->ext.weapon.lifetime & 1) {
            e = g_api.CreateEntFactoryFromEntity(
                self, WFACTORY(0x4E, 0) + ((self->ext.weapon.unk7E + 16) << 16),
                0);
            self->ext.weapon.unk7E++;
        }

        break;

    case 3:
        self->hitboxState = 0;
        // the last three bits of weapon lifetime need to be zero.
        if ((self->ext.weapon.lifetime & 7) == 0) {
            g_api.PlaySfx(SFX_FM_EXPLODE_B);
        }
        // no, seriously. the last three bits of weapon lifetime really need
        // to be zero. and don't trust that last comparison. i'm not joking.
        if ((self->ext.weapon.lifetime & 7) == 0) {
            e = g_api.CreateEntFactoryFromEntity(self, WFACTORY(104, 0), 0);
        }

        self->animCurFrame = 0;
        if (--self->ext.weapon.lifetime == 0) {
            DestroyEntity(self);
            return;
        }

        break;
    }
}

s32 func_ptr_80170010(Entity* self) {
    s16 angle;
    s32 accelerationX;
    s32 accelerationY;
    u16 rotation;
    s16 params;

    params = (u16)self->params >> 8;
    if (self->step == 0) {
        if (self->ext.factory.parent->entityId == 0) {
            DestroyEntity(self);
            return;
        }
        SetSpriteBank2(D_6D000_8017A2B0);
        self->animSet = ANIMSET_OVL(0x11);
        self->palette = PAL_DRA(0x111);
        self->unk5A = 0x65;
        if (g_HandId != 0) {
            self->animSet += 2;
            self->palette += 0x18;
            self->unk5A = 0x67;
        }
        self->anim = D_6D000_8017A770;
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_UNK_100000;
        self->zPriority = PLAYER.zPriority - 2;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        if (params >= 0x10) {
            rotation = D_6D000_8017A78C[params];
            self->rotY = rotation;
            self->rotX = rotation;
        } else {
            self->zPriority = PLAYER.zPriority + 2;
            if (g_Player.padPressed & PAD_DOWN) {
                angle = (rand() % 1535) + 256;
                self->velocityX = rcos(angle) << 6;
                self->velocityY = -(rsin(angle) << 6);
                self->posX.val += self->velocityX;
                self->posY.val += self->velocityY;

                accelerationX = -self->velocityX;
                if (accelerationX < 0) {
                    accelerationX += 15;
                }
                self->ext.weapon.accelerationX = (accelerationX >> 4);

                accelerationY = -self->velocityY;
                if (accelerationY < 0) {
                    accelerationY += 15;
                }
                self->ext.weapon.accelerationY = (u32)(accelerationY >> 4);
            } else {
                self->velocityY = FIX(-1);
                self->posY.i.hi -= 12 - (rand() % 24);
                self->posX.i.hi -= 20 - (rand() % 40);
            }
        }
        self->ext.weapon.equipId = self->ext.weapon.parent->ext.weapon.equipId;
        SetWeaponProperties(self, 0);
        self->enemyId = self->ext.factory.parent->enemyId;
        self->hitboxWidth = 12;
        self->hitboxHeight = 12;

        self->step++;
        return;
    }
    if (self->animFrameDuration < 0) {
        DestroyEntity(self);
        return;
    }

    self->posY.val += self->velocityY;
    self->posX.val += self->velocityX;

    if (params == 0) {
        self->velocityX += self->ext.weapon.accelerationX;
        self->velocityY += self->ext.weapon.accelerationY;
    }
}

static s32 func_ptr_80170014(Entity* self) {
    s16 angle;

    if (self->step == 0) {
        if (self->ext.weapon.parent->entityId == 0) {
            DestroyEntity(self);
            return;
        }
        SetSpriteBank2(D_6D000_8017A2B0);
        self->animSet = ANIMSET_OVL(17);
        self->palette = 0x111;
        self->unk5A = 101;
        if (g_HandId != 0) {
            self->animSet += 2;
            self->palette += 24;
            self->unk5A = 103;
        }
        self->anim = D_6D000_8017A770;
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_UNK_100000;
        self->zPriority = PLAYER.zPriority - 2;
        self->drawMode = DRAW_TPAGE | 0x20;
        angle = ratan2(-self->ext.weapon.parent->velocityY,
                       self->ext.weapon.parent->velocityX);
        angle += (0x500 + (rand() % 0x600));
        self->velocityX = rcos(angle) * 64;
        self->velocityY = rsin(angle) * -64;
        self->ext.weapon.accelerationX = -self->velocityX / 13;
        self->ext.weapon.accelerationY = -self->velocityY / 13;
        self->ext.weapon.equipId = self->ext.weapon.parent->ext.weapon.equipId;
        SetWeaponProperties(self, 0);
        self->enemyId = self->ext.weapon.parent->enemyId;
        self->hitboxHeight = self->hitboxWidth = 12;
        self->step++;
        return;
    }
    if (self->animFrameDuration < 0) {
        DestroyEntity(self);
        return;
    }
    self->posY.val += self->velocityY;
    self->posX.val += self->velocityX;
    self->velocityX += self->ext.weapon.accelerationX;
    self->velocityY += self->ext.weapon.accelerationY;
}

static int GetWeaponId(void) { return 15; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
