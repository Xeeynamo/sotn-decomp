// Weapon ID #48. Used by weapons:
// Thunderbrand, Unknown#178
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_048_1.h"
#include "w_048_2.h"
#define g_Animset w_048_1
#define g_Animset2 w_048_2

extern WeaponAnimation D_154000_8017AFC0[];
extern SpriteParts D_154000_8017A040[];
extern s32 D_154000_8017C3B4;

/* near-duplicate of EntityWeaponAttack_w_049 */
void EntityWeaponAttack(Entity* self) {
    s8 animIndex = (self->params & 0x7FFF) >> 8;
    WeaponAnimation* anim = &D_154000_8017AFC0[animIndex];
    s32 var_s0;

    self->posX.val = PLAYER.posX.val;
    self->posY.val = PLAYER.posY.val;
    self->facingLeft = PLAYER.facingLeft;

    if ((PLAYER.ext.player.anim < anim->frameStart) ||
        (PLAYER.ext.player.anim >= anim->frameStart + 7) ||
        g_Player.unk46 == 0) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        SetSpriteBank1(D_154000_8017A040);
        self->animSet = ANIMSET_OVL(0x10);
        self->palette = 0x110;
        self->unk5A = 0x64;
        if (g_HandId != 0) {
            self->animSet += 2;
            self->palette += 0x18;
            self->unk5A += 2;
        }
        self->palette += anim->palette;
        self->flags = FLAG_UNK_40000 | FLAG_UNK_20000;
        self->zPriority = PLAYER.zPriority - 2;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;

        if (animIndex != 0) {
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xC) + 0x00038, 0);
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xC) + 0x1003A, 0);
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xC) + 0x2003A, 0);
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xC) + 0x3003A, 0);
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xC) + 0x00040, 0);
        }
        SetWeaponProperties(self, 0);
        D_154000_8017C3B4 = 0;
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
    if (D_154000_8017C3B4 == 0 && PLAYER.animFrameIdx == 1) {
        inline void create(Entity * self, s32 a, s32 b) {
            g_api.CreateEntFactoryFromEntity(self, a + b, 0);
        }

        var_s0 = 0x10;
        if (animIndex != 0) {
            var_s0 = 0x20;
        }

        create(self, ((g_HandId + 1) << 0xC), ((var_s0 + 0) << 0x10) + 0x38);
        create(self, ((g_HandId + 1) << 0xC), ((var_s0 + 1) << 0x10) + 0x3A);
        create(self, ((g_HandId + 1) << 0xC), ((var_s0 + 2) << 0x10) + 0x3A);
        create(self, ((g_HandId + 1) << 0xC), ((var_s0 + 3) << 0x10) + 0x3A);
    }
    D_154000_8017C3B4 = PLAYER.animFrameIdx;
    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;
}

extern s16 D_154000_8017B000[];

void func_154000_8017B810(Entity* ent, Point16* outPoint, bool arg2) {
    s32 idx;

    idx = PLAYER.ext.player.anim - 0x41;
    if (PLAYER.facingLeft) {
        ent->posX.i.hi = PLAYER.posX.i.hi - D_154000_8017B000[idx * 4 + 0];
        if (arg2) {
            outPoint->x = -(D_154000_8017B000[idx * 4 + 2] / 2);
        } else {
            outPoint->x = -(D_154000_8017B000[idx * 4 + 2]);
        }
    } else {
        ent->posX.i.hi = PLAYER.posX.i.hi + D_154000_8017B000[idx * 4 + 0];
        if (arg2) {
            outPoint->x = D_154000_8017B000[idx * 4 + 2] / 2;
        } else {
            outPoint->x = D_154000_8017B000[idx * 4 + 2];
        }
    }
    ent->posY.i.hi = PLAYER.posY.i.hi + D_154000_8017B000[idx * 4 + 1];
    if (arg2) {
        outPoint->y = D_154000_8017B000[idx * 4 + 3] / 2;
    } else {
        outPoint->y = D_154000_8017B000[idx * 4 + 3];
    }
}

INCLUDE_ASM("weapon/nonmatchings/w_048", func_ptr_80170004);

INCLUDE_ASM("weapon/nonmatchings/w_048", func_ptr_80170008);

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 48; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
