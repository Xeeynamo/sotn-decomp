// Weapon ID #18. Used by weapons:
// Power of Sire
#include "weapon_private.h"
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

INCLUDE_ASM("weapon/nonmatchings/w_018", EntityWeaponAttack);

INCLUDE_ASM("weapon/nonmatchings/w_018", func_ptr_80170004);

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
