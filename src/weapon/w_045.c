// Weapon ID #45. Used by weapons:
// Unknown#216
#include "weapon_private.h"
#include "shared.h"

int func_13F000_8017A718() {
    int var;
    if (!(g_Player.unk44 & 2)) {
        if (g_Entities[PLAYER_CHARACTER].facingLeft == 1) {
            if (g_Player.padPressed & PAD_RIGHT) {
                g_Entities[PLAYER_CHARACTER].facingLeft = 0;
                g_Player.unk4C = 1;
                return -1;
            }
            if (g_Player.padPressed & PAD_LEFT) {
                return 1;
            }
            do {
                var = 0;
            } while (0);
            return var;
        }
        if (!(g_Player.padPressed & PAD_RIGHT)) {
            if (g_Player.padPressed & PAD_LEFT) {
                g_Entities[PLAYER_CHARACTER].facingLeft = 1;
                g_Player.unk4C = 1;
                return -1;
            }
            return 0;
        }
        return 1;
    }
    return 0;
}

INCLUDE_ASM("weapon/nonmatchings/w_045", EntityWeaponAttack);

INCLUDE_ASM("weapon/nonmatchings/w_045", func_ptr_80170004);

INCLUDE_ASM("weapon/nonmatchings/w_045", func_ptr_80170008);

INCLUDE_ASM("weapon/nonmatchings/w_045", func_ptr_8017000C);

INCLUDE_ASM("weapon/nonmatchings/w_045", func_ptr_80170010);

s32 func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 45; }

void EntityWeaponShieldSpell(Entity* self) {}

void func_ptr_80170024(Entity* self) {}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
