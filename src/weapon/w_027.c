// Weapon ID #27. Used by weapons:
// Medusa shield, Unknown#211
#include "weapon_private.h"
#include "shared.h"

extern const char D_C1000_8017ACCC[]; // "\no\n"
extern s32 D_C1000_8017C6EC;          // g_DebugWaitInfoTimer

void DebugShowWaitInfo(const char* msg) {
    g_CurrentBuffer = g_CurrentBuffer->next;
    FntPrint(msg);
    if (D_C1000_8017C6EC++ & 4) {
        FntPrint(D_C1000_8017ACCC); // TODO: inline
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

INCLUDE_ASM("weapon/nonmatchings/w_027", EntityWeaponAttack);

void func_ptr_80170004(Entity* self) {}

void func_ptr_80170008(Entity* self) {}

void func_ptr_8017000C(Entity* self) {}

void func_ptr_80170010(Entity* self) {}

void func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 27; }

INCLUDE_ASM("weapon/nonmatchings/w_027", EntityWeaponShieldSpell);

INCLUDE_ASM("weapon/nonmatchings/w_027", func_ptr_80170024);

void func_ptr_80170028(Entity* self) {
    Entity* parent = self->ext.generic.unk8C.entityPtr;
    if (parent->entityId == 0) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        self->ext.weapon.equipId = parent->ext.weapon.equipId;
        SetWeaponProperties(self, 0);
        self->hitboxHeight = 6;
        self->hitboxWidth = 6;
        self->ext.generic.unk80.modeS16.unk0 = 6;
        self->step++;
    } else if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
        DestroyEntity(self);
    }

    if (self->hitFlags != 0) {
        if (++self->ext.generic.unkA2 >= 6) {
            self->ext.generic.unk8C.entityPtr->ext.weapon.unk90 = 0;
        }
        self->hitFlags = 0;
    }
}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
