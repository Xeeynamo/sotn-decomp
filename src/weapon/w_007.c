// Weapon ID #7. Used by weapons:
// Shield rod, Unknown#173
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_007_1.h"
#include "w_007_2.h"
#define g_Animset w_007_1
#define g_Animset2 w_007_2

INCLUDE_ASM("weapon/nonmatchings/w_007", EntityWeaponAttack);

INCLUDE_ASM("weapon/nonmatchings/w_007", func_ptr_80170004);

extern u8 D_35000_8017AC64[6][8];

s32 func_35000_8017B604(Primitive* prim, s32 x, s32 y) {
    s32 size;
    s32 left;
    s32 right;
    s32 top;
    s32 bottom;
    u8* uvPtr;

    // Should be able to do this as an array access but nope
    uvPtr = &D_35000_8017AC64;
    uvPtr += prim->b0 * 8;

    if (prim->b0 >= 3) {
        size = 2;
    } else {
        size = 3;
    }
    if (prim->b0 == 6) {
        return -1;
    }
    left = x - size;
    top = y - size;
    right = x + size;
    bottom = y + size;

    prim->x0 = left;
    prim->y0 = top;
    prim->x1 = right;
    prim->y1 = top;
    prim->x2 = left;
    prim->y2 = bottom;
    prim->x3 = right;
    prim->y3 = bottom;

    prim->u0 = *uvPtr++;
    prim->v0 = *uvPtr++;
    prim->u1 = *uvPtr++;
    prim->v1 = *uvPtr++;
    prim->u2 = *uvPtr++;
    prim->v2 = *uvPtr++;
    prim->u3 = *uvPtr++;
    prim->v3 = *uvPtr++;
    if (!(++prim->b1 & 1)) {
        prim->b0++;
    }
    return 0;
}

static void func_ptr_80170008(Entity* self) {
    Primitive* prim;
    s32 velocityX;
    s32 range;

    if (self->step == 0) {
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags = FLAG_UNK_08000000 | FLAG_UNK_800000;
        self->velocityY = FIX(3.0 / 4.0);

        range = 16;
        velocityX = (rand() % range) - 8;

        self->posX.i.hi += velocityX;
        self->posY.i.hi += rand() % range;

        prim = &g_PrimBuf[self->primIndex];
        prim->clut = 0x1B0;
        prim->tpage = 0x1A;
        prim->b0 = 0;
        prim->b1 = 0;
        prim->priority = self->zPriority + 4;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;

        func_35000_8017B604(prim, self->posX.i.hi, self->posY.i.hi);
        self->step++;
        return;
    }

    self->posY.val += self->velocityY;

    prim = &g_PrimBuf[self->primIndex];
    if (func_35000_8017B604(prim, self->posX.i.hi, self->posY.i.hi)) {
        DestroyEntity(self);
    }
}
static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 7; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
