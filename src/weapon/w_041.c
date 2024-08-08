// Weapon ID #41. Used by weapons:
// Monster vial 2
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "w_041_1.h"
#include "w_041_2.h"
#define g_Animset w_041_1
#define g_Animset2 w_041_2
#include "shared.h"
#include "sfx.h"

extern AnimationFrame D_123000_8017A4A4[];
extern FrameProperty D_123000_8017A50C[];
extern s32 D_123000_8017B200;

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

s32 func_ptr_80170004(Entity* self) {
    s16 result;
    s16 angleDiff;
    s16 angle;
    s32 fakeAngle;
    s32 velTemp;

    s32 trigresult;
    s32 trigtemp;

    switch (self->step) {
    case 0:
        self->animSet = self->ext.weapon.parent->animSet;
        self->unk5A = self->ext.weapon.parent->unk5A;
        self->palette = self->ext.weapon.parent->palette;
        self->facingLeft++;
        self->facingLeft &= 1;
        self->flags = FLAG_UNK_08000000;

        self->zPriority = self->ext.weapon.parent->zPriority - 2;
        self->unk4C = D_123000_8017A4A4;
        self->drawFlags |= 3;
        self->rotX = self->rotY = 0;
        self->step++;
        break;
    case 1:
        self->rotX += 4;
        if (self->rotX >= 0x100) {
            self->rotX = 0x100;
            self->ext.weapon.equipId =
                self->ext.weapon.parent->ext.weapon.equipId;
            SetWeaponProperties(self, 0);
            self->ext.weapon.lifetime = 8;
            self->step++;
        }
        self->rotY = self->rotX;
        break;
    case 2:
        if (--self->ext.weapon.lifetime == 0) {
            if (self->facingLeft) {
                self->ext.weapon.unk80 = 0;
                self->ext.weapon.unk7E = 0;
            } else {
                self->ext.weapon.unk80 = 0x800;
                self->ext.weapon.unk7E = 1;
            }
            self->ext.weapon.some_ent =
                func_123000_8017A994(self, self->ext.weapon.unk80, 0x280);
            g_api.PlaySfx(0x69B);
            g_api.PlaySfx(SFX_BAT_SCREECH);
            self->ext.weapon.lifetime = 0x16;
            self->ext.weapon.unk82 = 0x80;
            self->step++;
        }
        break;
    case 3:
        result = g_api.func_80118B18(
            self, self->ext.weapon.some_ent, self->ext.weapon.unk7E);
        if (result >= 0) {
            angle = self->ext.weapon.unk80 & 0xFFF;
            angleDiff = abs(angle - result);
            if (self->ext.weapon.unk82 > angleDiff) {
                self->ext.weapon.unk82 = angleDiff;
            }
            if (angle < result) {
                if (angleDiff < 0x800) {
                    angle += self->ext.weapon.unk82;
                } else {
                    angle -= self->ext.weapon.unk82;
                }
            } else {
                if (angleDiff < 0x800) {
                    angle -= self->ext.weapon.unk82;
                } else {
                    angle += self->ext.weapon.unk82;
                }
            }
            self->ext.weapon.unk80 = angle & 0xFFF;
        }
        trigresult = rcos(self->ext.weapon.unk80);
        trigtemp = trigresult * 16;
        self->velocityX = (trigresult * 32 + trigtemp) << 7 >> 8;

        trigresult = rsin(self->ext.weapon.unk80);
        trigtemp = trigresult * 16;
        self->velocityY = -((trigresult * 32 + trigtemp) << 7) >> 8;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        break;
    case 4:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        break;
    }
    g_api.UpdateAnim(D_123000_8017A50C, NULL);
    func_123000_8017A914();
}

static void func_ptr_80170008(Entity* self) {}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 41; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
