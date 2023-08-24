#include "weapon_private.h"
#include "shared.h"

extern const char D_12A000_8017A760[]; // "\no\n"
extern s32 D_12A000_8017B5EC;          // g_DebugWaitInfoTimer

void DebugShowWaitInfo(const char* msg) {
    g_CurrentBuffer = g_CurrentBuffer->next;
    FntPrint(msg);
    if (D_12A000_8017B5EC++ & 4) {
        FntPrint(D_12A000_8017A760); // TODO: inline
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

INCLUDE_ASM("weapon/nonmatchings/w_042", func_12A000_8017AC08);

INCLUDE_ASM("weapon/nonmatchings/w_042", EntityWeaponAttack);

INCLUDE_ASM("weapon/nonmatchings/w_042", func_ptr_80170004);

INCLUDE_ASM("weapon/nonmatchings/w_042", func_ptr_80170008);

INCLUDE_ASM("weapon/nonmatchings/w_042", func_ptr_8017000C);

void func_ptr_80170010(Entity* self) {}

void func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 42; }

void EntityWeaponShieldSpell(Entity* self) {}

void func_ptr_80170024(Entity* self) {}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
