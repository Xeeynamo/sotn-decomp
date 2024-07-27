// Weapon ID #10. Used by weapons:
// Iron shield, Unknown#205
#include "weapon_private.h"
#include "shared.h"
#include "items.h"

extern s32 D_4A000_8017CC1C; // g_DebugWaitInfoTimer

void DebugShowWaitInfo(const char* msg) {
    g_CurrentBuffer = g_CurrentBuffer->next;
    FntPrint(msg);
    if (D_4A000_8017CC1C++ & 4) {
        FntPrint("\no\n");
    }
    DrawSync(0);
    VSync(0);
    PutDrawEnv(&g_CurrentBuffer->draw);
    PutDispEnv(&g_CurrentBuffer->disp);
    FntFlush(-1);
}

void DebugInputWait(const char* msg) {
    while (PadRead(0))
        DebugShowWaitInfo(msg);
    while (!PadRead(0))
        DebugShowWaitInfo(msg);
}

INCLUDE_ASM("weapon/nonmatchings/w_010", EntityWeaponAttack);

extern AnimationFrame D_4A000_8017ABA0[];

s32 func_ptr_80170004(Entity* self) {
    if (self->ext.weapon.parent->entityId == 0) {
        DestroyEntity(self);
        return;
    }
    if (self->ext.weapon.parent->ext.weapon.equipId != ITEM_IRON_SHIELD) {
        DestroyEntity(self);
        return;
    }
    FntPrint("charah:%02x\n", self->animSet);
    FntPrint("oya_ptr:%02x\n", self->ext.weapon.parent);
    self->posX.i.hi = PLAYER.posX.i.hi;
    self->posY.i.hi = PLAYER.posY.i.hi;
    if (self->step == 0) {
        self->animSet = self->ext.weapon.parent->animSet;
        self->palette = PAL_OVL(0x194);
        self->zPriority = self->ext.weapon.parent->zPriority + 4;
        self->unk5A = self->ext.weapon.parent->unk5A;
        self->flags = FLAG_UNK_100000 | FLAG_UNK_40000 | FLAG_UNK_20000;
        self->unk4C = D_4A000_8017ABA0;
        g_api.PlaySfx(SFX_UNK_664);
        self->step++;
    } else if (self->animFrameDuration < 0) {
        DestroyEntity(self);
    }
}

void func_ptr_80170008(Entity* self) {}

void func_ptr_8017000C(Entity* self) {}

s32 func_ptr_80170010(Entity* self) {}

s32 func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 10; }

INCLUDE_ASM("weapon/nonmatchings/w_010", EntityWeaponShieldSpell);

INCLUDE_ASM("weapon/nonmatchings/w_010", func_ptr_80170024);

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
