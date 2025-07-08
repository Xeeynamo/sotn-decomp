// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../np3/np3.h"


// The enemy called "Blade", his helper functions, and his swords

static void func_801D0A00(s16* arg0) {
    Entity* ent;

    ent = &g_CurrentEntity[arg0[1]];
    func_801CD91C(ent);
    ent = &g_CurrentEntity[arg0[0]];
    func_801CD91C(ent);
    ent = &g_CurrentEntity[18];
    func_801CD91C(ent);
    ent = &g_CurrentEntity[arg0[2]];
    func_801CD83C(ent);
    ent = &g_CurrentEntity[arg0[3]];
    func_801CD83C(ent);

    for (arg0 += 4; *arg0; arg0++) {
        if (*arg0 != 0xFF) {
            ent = &g_CurrentEntity[*arg0];
            func_801CD83C(ent);
        }
    }
}

static void func_801D0B40(void) {
    Entity* ent;
    s16* unk88;

    ent = &g_CurrentEntity[15];
    unk88 = ent->ext.et_801D0B40.unk88;
    ent->ext.et_801D0B40.unk84 = unk88[0x4E] - 0x600;
    
    ent = &g_CurrentEntity[16];
    unk88 = ent->ext.et_801D0B40.unk88;
    ent->ext.et_801D0B40.unk84 = unk88[0x4E] - 0x600;
}

static s32 func_801D0B78(Entity* ent) {
    Entity* player = &PLAYER;
    s32 xDist_unused;
    s32 ret;

    // This is the logic of GetDistanceToPlayerX.
    // We just call the function over and over instead.
    xDist_unused = player->posX.i.hi - ent->posX.i.hi;
    if (xDist_unused < 0){
        xDist_unused = -xDist_unused;
    }

    ret = 0;

    switch (g_CurrentEntity->step) {
    case 8:
        if (GetDistanceToPlayerX() < 64) {
            ret = 10;
        }
        if (GetDistanceToPlayerX() > 80) {
            ret = 6;
        }
        if (g_CurrentEntity->ext.et_801D0B78.unk88) {
            ret = 7;
        }
        break;

    case 10:
        if (GetDistanceToPlayerX() < 88) {
            ret = 8;
        }
        if (GetDistanceToPlayerX() < 56) {
            ret = 7;
        }
        if (GetDistanceToPlayerX() > 80) {
            ret = 6;
        }
        if (g_CurrentEntity->ext.et_801D0B78.unk88) {
            ret = 7;
        }
        break;

    case 12:
        if (GetDistanceToPlayerX() < 64) {
            ret = 10;
        }
        break;

    case 6:
        if (g_CurrentEntity->ext.et_801D0B78.unk88) {
            ret = 7;
        }
        if (GetDistanceToPlayerX() < 48) {
            ret = 10;
        }
        if (GetDistanceToPlayerX() < 80) {
            ret = 8;
        }
        break;

    default:
        if (GetDistanceToPlayerX() > 80) {
            ret = 6;
        }
        if (GetDistanceToPlayerX() < 64) {
            ret = 10;
        }
        if (g_CurrentEntity->ext.et_801D0B78.unk88) {
            ret = 7;
        }
        break;
    }

    if (g_CurrentEntity->facingLeft != ((GetSideToPlayer() & 1) ^ 1)) {
        ret = 12;
    }
    return ret;
}

// clang-format off

// EntityBlade
INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/e_blade", func_pspeu_0925C350);

// EntityBladeSword
INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/e_blade", func_pspeu_0925D890);

INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/e_blade", func_pspeu_0925DD30);

INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/e_blade", func_pspeu_0925DD78);

// Gurkha
INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/e_blade", func_pspeu_0925DF90);

// EntityGurkhaSword
INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/e_blade", func_pspeu_0925F370);

INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/e_blade", func_pspeu_0925F770);

// Hammer
INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/e_blade", func_pspeu_0925F9D0);

// EntityGurkhaBodyParts
INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/e_blade", func_pspeu_09260A58);

// EntityHammerWeapon
INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/e_blade", func_pspeu_09260EE0);

INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/e_blade", func_pspeu_09261108);

INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/e_blade", func_pspeu_09261240);

INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/e_blade", func_pspeu_09261320);

INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/e_blade", func_pspeu_092613B8);

INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/e_blade", func_pspeu_09261418);

INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/e_blade", func_pspeu_092614A8);

INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/e_blade", func_pspeu_09261630);

// clang-format on
