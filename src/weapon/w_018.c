// Weapon ID #18. Used by weapons:
// Power of Sire
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_018_1.h"
#include "w_018_2.h"
#define g_Animset w_018_1
#define g_Animset2 w_018_2

extern const char D_82000_8017A73C[]; // "\no\n"
extern s32 D_82000_8017B1B4;          // g_DebugWaitInfoTimer

static void DebugShowWaitInfo(const char* msg) {
    g_CurrentBuffer = g_CurrentBuffer->next;
    FntPrint(msg);
    if (D_82000_8017B1B4++ & 4) {
        FntPrint(D_82000_8017A73C); // TODO: inline
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
        self->palette = PAL_DRA(0x110);
        self->unk5A = 0x64;
        if (g_HandId != 0) {
            self->animSet += 2;
            self->palette += 0x18;
            self->unk5A += 2;
        }
        self->facingLeft = 0;
        self->flags = FLAG_UNK_04000000 | FLAG_UNK_100000;
        self->zPriority = PLAYER.zPriority - 4;
        self->unk4C = D_82000_8017A6A8;
        SetWeaponProperties(self, 1);
        g_api.PlaySfx(SE_WPN_POWER_OF_SIRE);
        g_Player.D_80072F00[12] = 4;
        self->step++;
        break;
    // image of dracula appears
    case 1:
        if (self->animFrameDuration < 0) {
            self->drawMode = FLAG_DRAW_UNK20 | FLAG_DRAW_UNK10;
            self->unk4C = D_82000_8017A6E4;
            self->animFrameIdx = 0;
            self->animFrameDuration = 0;
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
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xC) + FACTORY(0, 0x38), 0)) {
            g_api.func_80118C28(6);
            SetWeaponProperties(self, 0);
        }

        self->ext.weapon.lifetime--;
        if ((self->ext.weapon.lifetime) == 0) {
            self->drawFlags = 3;
            self->rotY = 256;
            self->rotX = 256;
            self->ext.weapon.lifetime = 14;
            self->step++;
        }
        break;
    // squish and explode
    case 3:
        self->rotX -= FIX(1.0 / 2048.0);
        if (self->rotY < FIX(1.0 / 64.0)) {
            self->rotY += FIX(3.0 / 1024.0);
        }
        if (self->rotX == FIX(1.0 / 1024.0)) {
            self->rotPivotX = 1;
            g_api.PlaySfx(SFX_TELEPORT_BANG_B);
            g_api.CreateEntFactoryFromEntity(self, FACTORY(0xC00, 4), 0);
        }
        if (self->rotX == FIX(1.0 / 2048.0)) {
            self->palette = PAL_OVL(0x15F);
        }
        if (self->rotX <= 0) {
            self->rotX = 6;
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
            self->palette = PAL_DRA(0x128);
        } else {
            self->palette = PAL_DRA(0x110);
        }

        self->unk5A = self->ext.weapon.parent->unk5A;
        self->facingLeft = 0;
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_100000;
        self->zPriority = PLAYER.zPriority - 2;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
        self->unk4C = D_82000_8017A724;
        self->rotX = self->rotY = 256;

        angle = rand();
        self->velocityX = rcos(angle) << 7;
        self->velocityY = -(rsin(angle) << 7);

        scale = rand() & 7;
        self->posX.val += scale * self->velocityX;
        self->posY.val += (scale + 2) * self->velocityY;

        g_api.PlaySfx(SFX_UNK_69D);
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
        if (self->rotX < 512) {
            self->rotX += 16;
        }
        self->rotY = self->rotX;
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
