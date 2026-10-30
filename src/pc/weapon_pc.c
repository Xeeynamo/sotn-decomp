// SPDX-License-Identifier: AGPL-3.0-or-later
#include "weapon.h"
#include "pc.h"
#include "stages/overlay.h"
#include <string.h>

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

void HandleWeaponPrg(unsigned handId, unsigned weaponId) {
    char name[16];

    if (handId >= 2) {
        ERRORF("hand ID %d not valid", handId);
        return;
    }
    snprintf(name, sizeof(name), "w%d_%03d", handId, weaponId);
    if (!LoadWeaponOverlay(name, handId, handId ? &D_8017D000 : &D_8017A000)) {
        ERRORF("weapon '%s' was not loaded", name);
        abort();
    }
}

void HandleWeaponChr(unsigned handId, unsigned weaponId) {
    const int Width = 256;
    const int Height = 128;
    const int PixLen = Width * Height / 2;
    const int EntryLen = 0x3000 + PixLen;
    char path[512];

    snprintf(path, sizeof(path), SOTN_DATA_DIR "/BIN/WEAPON%d.BIN", handId);
    switch (handId) {
    case 0:
        FileReadToBuf(path, g_Pix[0], weaponId * EntryLen, PixLen);
        LoadTPage(g_Pix[0], 0, 0, 0x240, 0x100, Width, Height);
        break;
    case 1:
        FileReadToBuf(path, g_Pix[2], weaponId * EntryLen, PixLen);
        LoadTPage(g_Pix[2], 0, 0, 0x240, 0x180, Width, Height);
        break;
    default:
        ERRORF("hand ID %d not valid", handId);
        break;
    }
}
