#include "weapon.h"
#include "pc.h"
#include <string.h>

// main variable
u16 D_8006EDCC[2][N_WEAPON_PAL * PALETTE_LEN];

void EntityWeaponAttackDummy(Entity* self) { NOT_IMPLEMENTED; }
s32 func_ptr_80170004Dummy(Entity* self) { NOT_IMPLEMENTED; }
void func_ptr_80170008Dummy(Entity* self) { NOT_IMPLEMENTED; }
void func_ptr_8017000CDummy(Entity* self) { NOT_IMPLEMENTED; }
s32 func_ptr_80170010Dummy(Entity* self) { NOT_IMPLEMENTED; }
s32 func_ptr_80170014Dummy(Entity* self) { NOT_IMPLEMENTED; }
int GetWeaponIdDummy(void) {
    NOT_IMPLEMENTED;
    return 0;
}
void LoadWeaponPaletteDummy(s32 clutIndex) { NOT_IMPLEMENTED; }
void EntityWeaponShieldSpellDummy(Entity* self) { NOT_IMPLEMENTED; }
void func_ptr_80170024Dummy(Entity* self) { NOT_IMPLEMENTED; }
void func_ptr_80170028Dummy(Entity* self) { NOT_IMPLEMENTED; }

Weapon D_8017A000 = {
    EntityWeaponAttackDummy,
    func_ptr_80170004Dummy,
    func_ptr_80170008Dummy,
    func_ptr_8017000CDummy,
    func_ptr_80170010Dummy,
    func_ptr_80170014Dummy,
    GetWeaponIdDummy,
    LoadWeaponPaletteDummy,
    EntityWeaponShieldSpellDummy,
    func_ptr_80170024Dummy,
    func_ptr_80170028Dummy,
};
Weapon D_8017D000 = {
    EntityWeaponAttackDummy,
    func_ptr_80170004Dummy,
    func_ptr_80170008Dummy,
    func_ptr_8017000CDummy,
    func_ptr_80170010Dummy,
    func_ptr_80170014Dummy,
    GetWeaponIdDummy,
    LoadWeaponPaletteDummy,
    EntityWeaponShieldSpellDummy,
    func_ptr_80170024Dummy,
    func_ptr_80170028Dummy,
};

void w_000_EntityWeaponAttack(Entity* self);
s32 w_000_func_ptr_80170004(Entity* self);
void w_000_func_ptr_80170008(Entity* self);
void w_000_func_ptr_8017000C(Entity* self);
s32 w_000_func_ptr_80170010(Entity* self);
s32 w_000_func_ptr_80170014(Entity* self);
int w_000_GetWeaponId(void);
void w_000_LoadWeaponPalette(s32 clutIndex);
void w_000_EntityWeaponShieldSpell(Entity* self);
void w_000_func_ptr_80170024(Entity* self);
void w_000_func_ptr_80170028(Entity* self);

Weapon g_Weapons[] = {
    {
        w_000_EntityWeaponAttack,
        w_000_func_ptr_80170004,
        w_000_func_ptr_80170008,
        w_000_func_ptr_8017000C,
        w_000_func_ptr_80170010,
        w_000_func_ptr_80170014,
        w_000_GetWeaponId,
        w_000_LoadWeaponPalette,
        w_000_EntityWeaponShieldSpell,
        w_000_func_ptr_80170024,
        w_000_func_ptr_80170028,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    },
    {
        EntityWeaponAttackDummy,
        func_ptr_80170004Dummy,
        func_ptr_80170008Dummy,
        func_ptr_8017000CDummy,
        func_ptr_80170010Dummy,
        func_ptr_80170014Dummy,
        GetWeaponIdDummy,
        LoadWeaponPaletteDummy,
        EntityWeaponShieldSpellDummy,
        func_ptr_80170024Dummy,
        func_ptr_80170028Dummy,
    }};

SpriteParts* g_Animset[1];

int readSubsetToBuf(char* filename, char* dest, size_t start, size_t size) {
    FILE* file = fopen(filename, "rb");

    if (file == NULL) {
        printf("Failed to open file");
        return 1;
    }

    // seek to target position
    fseek(file, start, SEEK_SET);

    // Read the file into the buffer
    size_t read_size = fread(dest, 1, size, file);
    if (read_size != size) {
        printf("Failed to read file");
        fclose(file);
        return 1;
    }

    if (ferror(file)) {
        printf("Error reading file");
        return 1;
    } else if (feof(file)) {
        printf("End of file reached\n");
        return 1;
    }

    fclose(file);

    return 0;
}

void HandleWeapon0Prg(int fileId) {
    memcpy(&D_8017A000, &g_Weapons[fileId], sizeof(Weapon));
    // todo animsets
}

void HandleWeapon0Chr(int fileId) {
    const int Width = 256;
    const int Height = 128;
    const int PixLen = Width * Height / 2;
    const int EntryLen = 0x3000 + PixLen;
    FileReadToBuf(
        "disks/us/BIN/WEAPON0.BIN", &g_Pix[0], fileId * EntryLen, PixLen);
    LoadTPage(&g_Pix[0], 0, 0, 0x240, 0x100, Width, Height);
}
