// Weapon ID #53. Used by weapons:
// Katana, Osafune katana, Masamune, Yasutsuna, Unknown#189, Unknown#192,
// Unknown#193, Unknown#194
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_053_1.h"
#include "w_053_2.h"
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
            self->flags = FLAG_UNK_40000 | FLAG_UNK_20000;
            self->zPriority = PLAYER.zPriority - 2;
            self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;

            switch (animIndex) {
            case 1:
                self->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE;
                g_api.CreateEntFactoryFromEntity(
                    self, ((g_HandId + 1) << 0xC) + FACTORY(0, 56), 0);
                break;
            case 3:
                self->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE;
                g_api.CreateEntFactoryFromEntity(
                    self, ((g_HandId + 1) << 0xC) + FACTORY(0xA00, 56), 0);
                break;
            case 4:
                g_api.CreateEntFactoryFromEntity(
                    self, ((g_HandId + 1) << 0xC) + FACTORY(0x1400, 56), 0);
                // fallthrough
            case 0:
            case 2:
            default:
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

INCLUDE_ASM("weapon/nonmatchings/w_053", func_ptr_80170004);

INCLUDE_ASM("weapon/nonmatchings/w_053", func_ptr_80170008);

INCLUDE_ASM("weapon/nonmatchings/w_053", func_ptr_8017000C);

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
