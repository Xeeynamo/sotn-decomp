// SPDX-License-Identifier: AGPL-3.0-or-later
// Weapon ID #41. Used by weapons:
// Monster vial 2
#include "weapon_private.h"
#include "w_041_1.h"
#include "w_041_2.h"
#define g_Animset w_041_1
#define g_Animset2 w_041_2
#include "sfx.h"

static s16 D_123000_8017A284[] = {
    COLOR16(0, 0, 0, 0),    COLOR16(3, 3, 3, 0),    COLOR16(5, 5, 5, 0),
    COLOR16(7, 7, 7, 0),    COLOR16(8, 8, 8, 0),    COLOR16(11, 11, 11, 0),
    COLOR16(14, 14, 14, 0), COLOR16(16, 16, 16, 0), COLOR16(28, 28, 0, 0),
    COLOR16(8, 1, 1, 0),    COLOR16(17, 1, 1, 0),   COLOR16(22, 1, 1, 0),
    COLOR16(29, 1, 1, 0),   COLOR16(13, 9, 6, 0),   COLOR16(16, 14, 11, 0),
    COLOR16(25, 1, 16, 0),  COLOR16(0, 0, 0, 0),    COLOR16(6, 6, 9, 1),
    COLOR16(7, 7, 10, 1),   COLOR16(9, 9, 11, 1),   COLOR16(11, 11, 12, 1),
    COLOR16(13, 13, 13, 1), COLOR16(14, 14, 14, 1), COLOR16(15, 15, 15, 1),
    COLOR16(16, 16, 16, 1), COLOR16(17, 17, 17, 1), COLOR16(18, 18, 18, 1),
    COLOR16(19, 19, 19, 1), COLOR16(20, 20, 20, 1), COLOR16(21, 21, 21, 1),
    COLOR16(22, 22, 22, 1), COLOR16(22, 23, 24, 1), COLOR16(0, 0, 0, 0),
    COLOR16(5, 3, 7, 1),    COLOR16(5, 3, 8, 1),    COLOR16(6, 4, 10, 1),
    COLOR16(7, 5, 12, 1),   COLOR16(8, 6, 13, 1),   COLOR16(9, 7, 15, 1),
    COLOR16(10, 8, 17, 1),  COLOR16(11, 9, 19, 1),  COLOR16(12, 12, 21, 1),
    COLOR16(14, 16, 23, 1), COLOR16(16, 19, 25, 1), COLOR16(17, 23, 27, 1),
    COLOR16(19, 26, 29, 1), COLOR16(21, 30, 31, 1), COLOR16(31, 31, 31, 1),
    COLOR16(0, 0, 0, 0),    COLOR16(25, 25, 24, 0), COLOR16(17, 17, 17, 0),
    COLOR16(9, 9, 9, 0),    COLOR16(13, 13, 12, 0), COLOR16(4, 4, 3, 0),
    COLOR16(3, 3, 3, 0),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(10, 0, 0, 0),   COLOR16(24, 13, 13, 0), COLOR16(20, 0, 0, 0),
    COLOR16(24, 2, 2, 0),   COLOR16(0, 0, 0, 1),    COLOR16(0, 12, 11, 0),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 0),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 0),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 0),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 0),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 0),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 0),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 0),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 0),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 0),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 0),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 0),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 0),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 0),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(1, 0, 0, 0),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 1, 0)};

static AnimationFrame D_123000_8017A4A4[] = {
    {4, FRAME(0x01, 0x02)}, {1, FRAME(0x02, 0x04)},
    {1, FRAME(0x03, 0x06)}, {1, FRAME(0x0A, 0x12)},
    {1, FRAME(0x04, 0x08)}, {1, FRAME(0x05, 0x0A)},
    {4, FRAME(0x06, 0x0C)}, {2, FRAME(0x07, 0x0A)},
    {2, FRAME(0x08, 0x0E)}, {2, FRAME(0x09, 0x10)},
    {1, FRAME(0x0A, 0x12)}, {2, FRAME(0x03, 0x06)},
    {2, FRAME(0x02, 0x04)}, A_LOOP_AT(0)};

static AnimationFrame D_123000_8017A4DC[] = {
    {2, FRAME(0x0C, 0x16)}, {1, FRAME(0x0D, 0x16)},
    {2, FRAME(0x0E, 0x16)}, {1, FRAME(0x0F, 0x16)},
    {1, FRAME(0x10, 0x16)}, {1, FRAME(0x11, 0x16)},
    {1, FRAME(0x12, 0x16)}, {1, FRAME(0x0E, 0x16)},
    {1, FRAME(0x0D, 0x16)}, A_END};

static AnimationFrame D_123000_8017A504[] = {{0x80, 0x000B}, A_END};

static FrameProperty D_123000_8017A50C[] = {
    {0x00, 0x00, 0x00, 0x00}, {0x00, 0xFA, 0x06, 0x0D},
    {0x00, 0xFB, 0x06, 0x0A}, {0x00, 0xFE, 0x06, 0x07},
    {0x00, 0x04, 0x06, 0x08}, {0x00, 0x07, 0x06, 0x0C},
    {0x00, 0x08, 0x06, 0x0E}, {0x00, 0x06, 0x06, 0x0B},
    {0x00, 0x04, 0x06, 0x09}, {0x00, 0x02, 0x06, 0x06},
    {0x00, 0x00, 0x03, 0x03}, {0xC1, 0xC1, 0x00, 0x00}};

static s32 D_123000_8017A53C[] = {
    FIX(0.875),
    FIX(0.375),
    FIX(1.125),
    FIX(0.625),
};

static s32 D_123000_8017A54C[] = {
    FIX(-3.25),
    FIX(-3),
    FIX(-3.5),
};

static u16* g_WeaponCluts[] = {D_123000_8017A284};
static s32 g_HandId = HAND_ID;

#include "shared.h"

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

extern s32 D_123000_8017A53C[];
extern s32 D_123000_8017A54C[];
extern s32 D_123000_8017B204;
extern s32 D_123000_8017B208;

void EntityWeaponAttack(Entity* self) {
    u8 pad[38];
    s32 speedX;

    switch (self->step) {
    case 0:
        SetSpriteBank1(g_Animset);
        self->animSet = ANIMSET_OVL(0x10);
        self->palette = PAL_DRA(0x110);
        self->unk5A = 0x64;
        if (g_HandId != 0) {
            self->palette += 0x18;
            self->unk5A += 2;
            self->animSet += 2;
        }

        self->zPriority = PLAYER.zPriority + 2;
        self->facingLeft = PLAYER.facingLeft;
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_100000;
        self->anim = D_123000_8017A504;
        self->posY.i.hi -= 4;

        speedX = D_123000_8017B204;
        if (D_123000_8017B204 < 0) {
            speedX += 3;
        }

        D_123000_8017B204 -= (speedX >> 2) * 4;

        SetSpeedX(D_123000_8017A53C[D_123000_8017B204]);

        D_123000_8017B204++;
        D_123000_8017B208 = D_123000_8017B204 % 3;
        self->velocityY = D_123000_8017A54C[D_123000_8017B208];
        D_123000_8017B208++;
        self->ext.weapon.lifetime = (rand() & 0xF) + 24;
        g_Player.D_80072F00[10] = 4;
        self->step++;
        break;

    case 1:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->velocityY += FIX(5.0 / 32.0);
        self->ext.weapon.lifetime--;
        if (!self->ext.weapon.lifetime) {
            self->anim = D_123000_8017A4DC;
            self->animFrameDuration = 0;
            self->animFrameIdx = 0;
            self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
            g_api.PlaySfxVolPan(SFX_GLASS_BREAK_A, 0x50, 0);
            g_api.CreateEntFactoryFromEntity(self, WFACTORY(56, 0), 0);
            self->step++;
        }
        break;

    case 2:
        if (self->animFrameDuration < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
}

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
        self->anim = D_123000_8017A4A4;
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
