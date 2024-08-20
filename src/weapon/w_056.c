// Weapon ID #56. Used by weapons:
// Muramasa
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_056_1.h"
#include "w_056_2.h"
#define g_Animset w_056_1
#define g_Animset2 w_056_2

extern WeaponAnimation D_18C000_8017AF64[];
extern u16 D_18C000_8017AF94[];
extern u16 D_18C000_8017AF9C[];

void EntityWeaponAttack(Entity* self) {
    WeaponAnimation* anim;
    s16 animIndex;
    Primitive* prim;
    s32 i;
    s16 x;
    s32 y;
    s32 x2;
    s32 offsetIndex;
    u8 brightness;
    u16* xValues;
    s32 primIndex;

    self->posX.val = PLAYER.posX.val;
    self->posY.val = PLAYER.posY.val;
    self->facingLeft = PLAYER.facingLeft;

    animIndex = (self->params >> 8) & 0x7F;

    if (g_Player.D_80072F00[11] != 0) {
        animIndex = 2;
    }

    anim = &D_18C000_8017AF64[animIndex];

    if (PLAYER.ext.player.anim < anim->frameStart ||
        PLAYER.ext.player.anim >= (anim->frameStart + 7) ||
        g_Player.unk46 == 0) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        SetSpriteBank1(g_Animset);
        self->animSet = ANIMSET_OVL(0x10);
        self->palette = PAL_DRA(0x110);
        self->unk5A = 0x64;
        if (g_HandId != 0) {
            self->animSet = self->animSet + 2;
            self->palette += 0x18;
            self->unk5A += 2;
        }
        self->palette += anim->palette;
        self->flags = FLAG_UNK_40000 | FLAG_UNK_20000;

        primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 0xC);

        self->primIndex = primIndex;
        if (primIndex != -1) {
            self->flags |= FLAG_UNK_800000;
            prim = &g_PrimBuf[self->primIndex];
            for (i = 0; i < 12; i++) {
                if (i <= 3) {
                    prim->r2 = rand() & 3;
                    do {
                        prim->b2 = 1;
                    } while (0);
                }
                if (i >= 7 && (i & 1)) {
                    prim->r2 = rand() & 0xF;
                    prim->b2 = 2;
                } else {
                    prim->r2 = rand() & 7;
                    prim->b2 = 1;
                }
                prim->r3 = i / 6;
                if (i == 11) {
                    prim->r2 = 0x18;
                    prim->r3 = 2;
                    prim->b2 = 3;
                }
                prim->r0 = prim->r1 = 255;
                prim->b0 = prim->b1 = prim->g0 = prim->g1 = rand() & 0x1F;

                prim->priority = PLAYER.zPriority;
                prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_HIDE;
                prim = prim->next;
            }
        }

        self->zPriority = PLAYER.zPriority - 2;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        SetWeaponProperties(self, 0);

        if (self->attack >= 0x1E) {
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xC) + FACTORY(0, 56), 0);
        }
        self->step++;
    }

    self->ext.weapon.anim = PLAYER.ext.player.anim - anim->frameStart;

    if (PLAYER.animFrameDuration == 1 &&
        PLAYER.animFrameIdx == anim->soundFrame) {
        g_api.PlaySfx(anim->soundId);
    }

    if (g_api.UpdateUnarmedAnim(anim->frameProps, anim->frames) < 0) {
        DestroyEntity(self);
        return;
    }

    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;

    if (self->animCurFrame != 0xD && self->animCurFrame != 0x22 &&
        self->animCurFrame != 0x2C && self->animCurFrame != 0x3E) {
        return;
    }

    if (self->primIndex != -1) {
        i = 0;

        xValues = D_18C000_8017AF94;
        self->flags |= FLAG_UNK_800000;
        prim = &g_PrimBuf[self->primIndex];

        for (; i < 12; i++) {
            switch (self->animCurFrame) {
            case 0xD:
                offsetIndex = 0;
                break;
            case 0x22:
                offsetIndex = 1;
                break;
            case 0x2C:
                offsetIndex = 2;
                break;
            case 0x3E:
                offsetIndex = 3;
                break;
            }

            x2 = -1;
            x = xValues[offsetIndex] - i;
            if (self->facingLeft != 0) {
                x = -x;
                x2 = 1;
            }
            prim->x2 = x2 + prim->x2;

            y = D_18C000_8017AF9C[offsetIndex] + (i / 6);

            prim->x0 = x + self->posX.i.hi;
            prim->x1 = prim->x0 + prim->x2;

            prim->y0 = y + self->posY.i.hi;
            prim->y1 = y + self->posY.i.hi + prim->r3;

            if (prim->r2 > prim->r3) {
                prim->r3 += prim->b2;
            }

            prim->drawMode &= ~DRAW_HIDE;
            prim = prim->next;
        }
    }
}

INCLUDE_ASM("weapon/nonmatchings/w_056", func_ptr_80170004);

static void func_ptr_80170008(Entity* self) {}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 56; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
