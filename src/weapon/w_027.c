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

INCLUDE_ASM("weapon/nonmatchings/w_027", func_ptr_80170020);

INCLUDE_ASM("weapon/nonmatchings/w_027", func_ptr_80170024);

INCLUDE_ASM("weapon/nonmatchings/w_027", func_ptr_80170028);

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
