// Weapon ID #5. Used by weapons:
// Star flail, Unknown#171
#include "weapon_private.h"
#include "w_005_1.h"
#define g_Animset w_005_1
#include "color_tables.h"
#include "animations.h"

static WeaponAnimation D_27000_8017B2F4[] = {
    {g_Anim0, g_Hitboxes, 3, SFX_UNK_689, 0x4F, 3},
    {g_Anim1, g_Hitboxes, 3, SFX_UNK_689, 0x56, 3}};

static u16* g_WeaponCluts[] = {g_Clut0};
static s32 g_HandId = HAND_ID;

#include "shared.h"

static void EntityWeaponAttack(Entity* self) {
    WeaponAnimation* anim;
    s8 animIndex;

    self->posX.val = PLAYER.posX.val;
    self->posY.val = PLAYER.posY.val;
    self->facingLeft = PLAYER.facingLeft;
    animIndex = (self->params & 0x7fff) >> 8;
    anim = &D_27000_8017B2F4[animIndex];

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
            self->flags = FLAG_UNK_20000 | FLAG_UNK_40000;
            self->zPriority = PLAYER.zPriority - 2;
            self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
            SetWeaponProperties(self, 0);
            self->step++;
        }
        self->ext.weapon.anim = PLAYER.ext.player.anim - anim->frameStart;
        if ((PLAYER.animFrameDuration == 1) &&
            (PLAYER.animFrameIdx == anim->soundFrame)) {
            g_api.PlaySfx(anim->soundId);
            g_api.PlaySfx(SFX_ANIME_SWORD_B);
        }
        if (g_api.UpdateUnarmedAnim(anim->frameProps, anim->frames) < 0) {
            DestroyEntity(self);
            return;
        }
    } else {
        DestroyEntity(self);
        return;
    }

    if (PLAYER.animFrameIdx >= 6 && PLAYER.animFrameIdx < 8) {
        self->hitboxOffX = self->hitboxOffX + 7;
        self->hitboxWidth += 7;
    }
    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;
}

static s32 func_ptr_80170004(Entity* self) {}

static void func_ptr_80170008(Entity* self) {}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 5; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
