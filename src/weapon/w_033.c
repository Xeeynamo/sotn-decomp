// Weapon ID #33. Used by weapons:
// Nunchaku
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_033_1.h"
#include "w_033_2.h"
#define g_Animset w_033_1
#define g_Animset2 w_033_2

extern WeaponAnimation D_EB000_8017AC3C[2];

void EntityWeaponAttack(Entity* self) {
    WeaponAnimation* anim;
    s8 animIndex;

    self->posX.val = g_Entities->posX.val;
    self->posY.val = PLAYER.posY.val;
    self->facingLeft = PLAYER.facingLeft;
    animIndex = (self->params & 0x7fff) >> 8;
    anim = &D_EB000_8017AC3C[animIndex];

    if (PLAYER.ext.player.anim >= anim->frameStart &&
        PLAYER.ext.player.anim < (anim->frameStart + 7) && g_Player.unk46) {

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
            self->flags = FLAG_UNK_20000 | FLAG_UNK_40000;
            self->zPriority = PLAYER.zPriority - 2;
            SetWeaponProperties(self, 0);
            self->step++;
        }

        self->ext.weapon.anim = PLAYER.ext.player.anim - anim->frameStart;
        if (PLAYER.animFrameDuration == 1 &&
            PLAYER.animFrameIdx == anim->soundFrame) {
            g_api.PlaySfx(anim->soundId);
        }

        if (PLAYER.animFrameIdx == 12 && PLAYER.animFrameDuration == 1) {
            g_api.PlaySfx(anim->soundId);
            g_api.PlaySfx(SFX_WEAPON_SWISH_B);
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

s32 func_ptr_80170004(Entity* self) {}

static void func_ptr_80170008(Entity* self) {}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 33; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
