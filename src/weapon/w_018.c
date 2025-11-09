// SPDX-License-Identifier: AGPL-3.0-or-later
// Weapon ID #18. Used by weapons:
// Power of Sire
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "gen/w_018_1.h"
#include "gen/w_018_2.h"
#define g_Animset w_018_1
#define g_Animset2 w_018_2
#include "sfx.h"

static s32 g_DebugWaitInfoTimer;

static void DebugShowWaitInfo(const char* msg) {
    g_CurrentBuffer = g_CurrentBuffer->next;
    FntPrint(msg);
    if (g_DebugWaitInfoTimer++ & 4) {
        FntPrint("\no\n");
    }
    DrawSync(0);
    VSync(0);
    PutDrawEnv(&g_CurrentBuffer->draw);
    PutDispEnv(&g_CurrentBuffer->disp);
    FntFlush(-1);
}

static void DebugInputWait(const char* msg) {
    while (PadRead(0))
        DebugShowWaitInfo(msg);
    while (!PadRead(0))
        DebugShowWaitInfo(msg);
}

extern AnimationFrame D_82000_8017A6A8[];
extern AnimationFrame D_82000_8017A6E4[];

void EntityWeaponAttack(Entity* self) {
    self->hitboxState = 0;
    switch (self->step) {
    // bat appears
    case 0:
        self->posX.i.hi = PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi - 0x38;
        SetSpriteBank1(g_Animset);

        self->animSet = ANIMSET_OVL(0x10);
        self->palette = PAL_UNK_110;
        self->unk5A = 0x64;
        if (g_HandId != 0) {
            self->animSet += 2;
            self->palette += 0x18;
            self->unk5A += 2;
        }
        self->facingLeft = 0;
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_UNK_100000;
        self->zPriority = PLAYER.zPriority - 4;
        self->anim = D_82000_8017A6A8;
        SetWeaponProperties(self, 1);
        g_api.PlaySfx(SFX_MAGIC_WEAPON_APPEAR_B);
        g_Player.timers[12] = 4;
        self->step++;
        break;
    // image of dracula appears
    case 1:
        if (self->poseTimer < 0) {
            self->drawMode = FLAG_DRAW_UNK20 | FLAG_DRAW_UNK10;
            self->anim = D_82000_8017A6E4;
            self->pose = 0;
            self->poseTimer = 0;
            self->ext.weapon.lifetime = 71;
            g_api.func_80118C28(5);
            g_api.func_80102CD8(3);
            g_api.PlaySfx(SFX_TELEPORT_BANG_A);
            self->step++;
        }
        break;
    // emit starbursts
    case 2:
        if (self->ext.weapon.lifetime % 8 == 0 &&
            self->ext.weapon.lifetime >= 9 &&
            g_api.CreateEntFactoryFromEntity(self, WFACTORY(0x38, 0), 0)) {
            g_api.func_80118C28(6);
            SetWeaponProperties(self, 0);
        }

        self->ext.weapon.lifetime--;
        if ((self->ext.weapon.lifetime) == 0) {
            self->drawFlags = FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
            self->scaleY = 256;
            self->scaleX = 256;
            self->ext.weapon.lifetime = 14;
            self->step++;
        }
        break;
    // squish and explode
    case 3:
        self->scaleX -= 32;
        if (self->scaleY < 1024) {
            self->scaleY += 192;
        }
        if (self->scaleX == 64) {
            self->rotPivotX = 1;
            g_api.PlaySfx(SFX_TELEPORT_BANG_B);
            g_api.CreateEntFactoryFromEntity(self, FACTORY(4, 12), 0);
        }
        if (self->scaleX == 32) {
            self->palette = PAL_FLAG(PAL_FILL_WHITE);
        }
        if (self->scaleX <= 0) {
            self->scaleX = 6;
        }

        self->ext.weapon.lifetime--;
        if (self->ext.weapon.lifetime == 0) {
            DestroyEntity(self);
        }
        break;
    }
}

extern AnimationFrame D_82000_8017A724[];

s32 func_ptr_80170004(Entity* self) {
    s16 angle;
    s32 scale;

    if (self->ext.weapon.parent->ext.weapon.equipId != 0x48) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        SetSpriteBank1(g_Animset);
        self->animSet = ANIMSET_OVL(0x10);
        if (g_HandId != 0) {
            self->animSet = ANIMSET_OVL(0x12);
        }

        if (self->ext.weapon.parent->palette >= 0x128U) {
            self->palette = PAL_UNK_128;
        } else {
            self->palette = PAL_UNK_110;
        }

        self->unk5A = self->ext.weapon.parent->unk5A;
        self->facingLeft = 0;
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_UNK_100000;
        self->zPriority = PLAYER.zPriority - 2;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->drawFlags = FLAG_DRAW_SCALEX | FLAG_DRAW_SCALEY;
        self->anim = D_82000_8017A724;
        self->scaleX = self->scaleY = 256;

        angle = rand();
        self->velocityX = rcos(angle) << 7;
        self->velocityY = -(rsin(angle) << 7);

        scale = rand() & 7;
        self->posX.val += scale * self->velocityX;
        self->posY.val += (scale + 2) * self->velocityY;

        g_api.PlaySfx(SFX_MAGIC_SWITCH);
        self->ext.weapon.lifetime = 6;
        self->step++;
        break;

    case 1:
        self->ext.weapon.lifetime--;
        if (self->ext.weapon.lifetime == 0) {
            self->step++;
        }
        break;

    case 2:
        if (self->scaleX < 512) {
            self->scaleX += 16;
        }
        self->scaleY = self->scaleX;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        break;
    }
}

static void func_ptr_80170008(Entity* self) {}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 18; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
