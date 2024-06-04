// Weapon ID #41. Used by weapons:
// Monster vial 2
#include "weapon_private.h"
#include "shared.h"

void func_123000_8017A914(void) {
    RECT rect;
    RECT rectDummy;
    s16 color;

    color = (g_GameTimer >> 1) % 2 ? 0x039C : 0x199D;
    D_8006EDCC[g_HandId][8] = color;

    rect.x = 0;
    rect.y = 0xF1;
    rect.w = 0x100;
    rect.h = 3;
    LoadImage(&rect, D_8006EDCC);
}

extern s32 D_123000_8017B200;

// Purpose is not 100% clear, but appears to be something like:
// Iterate over entities 64-192. Look for any which are positioned
// in a certain direction from us. That direction is the angleTarget,
// and the targeted entity must be within tolerance from that target.

Entity* func_123000_8017A994(Entity* self, s16 angleTarget, s16 tolerance) {
    s32 sp10[128];
    Entity* other;

    s16 angleDiff;
    s32 var_a0;
    s32 i;
    s32 entCount;

    s16 xVar;
    s16 yVar;
    s16 angleResult;

    entCount = 0;
    for (other = &g_Entities[64], i = 0; i < 128; i++, other++) {
        sp10[i] = 0;
        if ((!other->entityId) || (other->hitboxState == 0) ||
            (other->flags & FLAG_UNK_00200000)) {
            continue;
        }
        if (other->posX.i.hi < -16) {
            continue;
        }
        if (other->posX.i.hi > 272) {
            continue;
        }
        if (other->posY.i.hi > 240) {
            continue;
        }
        if (other->posY.i.hi < 0) {
            continue;
        }
        if (other->hitPoints >= 0x7000) {
            continue;
        }
        xVar = other->posX.i.hi - self->posX.i.hi;
        yVar = other->posY.i.hi - self->posY.i.hi;
        angleResult = ratan2(-yVar, xVar) & 0xFFF;
        angleDiff = abs(angleTarget - angleResult);
        if (angleDiff < 0x800) {
            if (angleDiff > tolerance) {
                continue;
            }
        } else {
            if ((0x1000 - angleDiff) > tolerance) {
                continue;
            }
        }
        if (other->flags & FLAG_UNK_80000) {
            entCount++;
            sp10[i] = 1;
            continue;
        }
        other->flags |= FLAG_UNK_80000;
        return other;
    }

    if (entCount != 0) {
        var_a0 = D_123000_8017B200 % 128;
        for (i = 0; i < 128; i++) {
            if (sp10[var_a0] != 0) {
                other = &g_Entities[64 + var_a0];
                D_123000_8017B200 = (var_a0 + 1) % 128;
                return other;
            }
            var_a0 = (var_a0 + 1) % 128;
        }
    }
    return NULL;
}

INCLUDE_ASM("weapon/nonmatchings/w_041", EntityWeaponAttack);

INCLUDE_ASM("weapon/nonmatchings/w_041", func_ptr_80170004);

void func_ptr_80170008(Entity* self) {}

void func_ptr_8017000C(Entity* self) {}

void func_ptr_80170010(Entity* self) {}

s32 func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 41; }

void EntityWeaponShieldSpell(Entity* self) {}

void func_ptr_80170024(Entity* self) {}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
