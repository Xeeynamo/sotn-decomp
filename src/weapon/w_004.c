#include "weapon_private.h"
#include "shared.h"

extern AnimSoundEvent D_20000_8017B2F4[]; // g_SoundEvents

void EntityWeaponAttack(Entity* self) {
    AnimSoundEvent* sndEvent;
    s32 mask;

    self->posX.val = g_Entities->posX.val;
    self->posY.val = PLAYER.posY.val;
    self->facing = PLAYER.facing;
    mask = 0x17F;
    sndEvent = &D_20000_8017B2F4[(self->params >> 8) & mask];

    if (!(PLAYER.ext.weapon.unkAC >= sndEvent->ACshift &&
          PLAYER.ext.weapon.unkAC < sndEvent->ACshift + 7 &&
          g_Player.unk46 != 0)) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        SetSpriteBank1(g_Animset);
        self->animSet = ANIMSET_OVL(0x10);
        self->palette = 0x110;
        self->unk5A = 0x64;
        if (g_HandId != 0) {
            self->animSet += 2;
            self->palette += 0x18;
            self->unk5A += 2;
        }
        self->palette += sndEvent->unk8;
        self->flags = FLAG_UNK_20000 | FLAG_UNK_40000;
        self->zPriority = PLAYER.zPriority - 2;
        self->blendMode = 0x30;
        SetWeaponProperties(self, 0);
        self->step++;
    }

    self->ext.generic.unkAC = PLAYER.ext.weapon.unkAC - sndEvent->ACshift;
    if (PLAYER.animFrameDuration == 1 &&
        PLAYER.animFrameIdx == sndEvent->soundFrame) {
        g_api.PlaySfx(sndEvent->soundId);
        g_api.PlaySfx(0x640);
    }

    if (g_api.UpdateUnarmedAnim(sndEvent->frameProps, sndEvent->frames) < 0) {
        DestroyEntity(self);
    }

    self->unk19 = PLAYER.unk19;
    self->unk1C = PLAYER.unk1C;
    self->rotPivotY = PLAYER.rotPivotY;
}

void func_ptr_80170004(Entity* self) {}

void func_ptr_80170008(Entity* self) {}

void func_ptr_8017000C(Entity* self) {}

void func_ptr_80170010(Entity* self) {}

void func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 4; }

void EntityWeaponShieldSpell(Entity* self) {}

void func_ptr_80170024(Entity* self) {}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
