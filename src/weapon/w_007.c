// Weapon ID #7. Used by weapons:
// Shield rod, Unknown#173
#define FUNC_04_VOID
#include "weapon_private.h"
#include "w_007_1.h"
#define g_Animset w_007_1
#include "color_tables.h"
#include "animations.h"

static WeaponAnimation D_35000_8017AC28[] = {
    {g_Anim0, g_Hitboxes, 15, SFX_UNK_689, 0x48, 3},
    {g_Anim0, g_Hitboxes, 15, SFX_UNK_689, 0x48, 3}};

// x, y pairs
static s16 D_35000_8017AC48[] = {
    40, -14, 40, -14, 40, 4, 36, 20, 40, -14, 40, -13, 40, 16};

/* duplicated in w_006 */
static u8 D_35000_8017AC64[6][8] = {
    {0x00, 0x50, 0x10, 0x50, 0x00, 0x60, 0x10, 0x60},
    {0x10, 0x50, 0x20, 0x50, 0x10, 0x60, 0x20, 0x60},
    {0x70, 0x40, 0x80, 0x40, 0x70, 0x50, 0x80, 0x50},
    {0x70, 0x30, 0x78, 0x30, 0x70, 0x38, 0x78, 0x38},
    {0x78, 0x30, 0x80, 0x30, 0x78, 0x38, 0x80, 0x38},
    {0x70, 0x38, 0x78, 0x38, 0x77, 0x40, 0x78, 0x40}};

static u16* g_WeaponCluts[] = {g_Clut0, g_Clut0};
static s32 g_HandId = HAND_ID;

#include "shared.h"

static void EntityWeaponAttack(Entity* self) {
    s8 animIndex = (self->params & 0x7FFF) >> 8;
    WeaponAnimation* anim = &D_35000_8017AC28[animIndex];
    s32 hand;
    s32 temp;

    self->posX.val = PLAYER.posX.val;
    self->posY.val = PLAYER.posY.val;
    self->facingLeft = PLAYER.facingLeft;

    if ((PLAYER.ext.player.anim < anim->frameStart) ||
        (PLAYER.ext.player.anim >= anim->frameStart + 7) ||
        g_Player.unk46 == 0) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        SetSpriteBank1(g_Animset);
        self->animSet = ANIMSET_OVL(0x10);
        self->palette = 0x110;
        self->unk5A = 0x64;
        if (g_HandId != 0) {
            self->animSet += 2;
            self->palette += 0x18;
            self->unk5A += 2;
        }

        self->palette += anim->palette;
        self->flags = FLAG_UNK_40000 | FLAG_UNK_20000;
        self->zPriority = PLAYER.zPriority - 2;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        SetWeaponProperties(self, 0);
        self->step++;
    }
    self->ext.weapon.anim = PLAYER.ext.player.anim - anim->frameStart;
    if ((PLAYER.animFrameDuration == 1) &&
        (PLAYER.animFrameIdx == anim->soundFrame)) {
        g_api.PlaySfx(anim->soundId);
    }
    if (g_api.UpdateUnarmedAnim(anim->frameProps, anim->frames) < 0) {
        DestroyEntity(self);
        return;
    }
    if (animIndex && PLAYER.animFrameDuration == 7 &&
        PLAYER.animFrameIdx == 4) {
        hand = (g_HandId + 1) << 0xC;
        temp = (self->ext.weapon.anim << 0x10) + 0x4A;
        g_api.CreateEntFactoryFromEntity(self, hand + temp, 0);
    }
    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;
}

static void func_ptr_80170004(Entity* self) {
    Entity* parent;
    s32 index;
    u16 offsetX, offsetY;

    switch (self->step) {
    case 0:
        parent = self->ext.weapon.parent;
        if (parent->entityId != 0) {
            index = (self->params >> 7);
            self->facingLeft = parent->facingLeft;
            offsetX = D_35000_8017AC48[index];
            offsetY = D_35000_8017AC48[index + 1];
            if (self->facingLeft) {
                offsetX = -offsetX;
            }
            self->posX.i.hi += offsetX;
            self->posY.i.hi += offsetY;

            self->animSet = self->ext.weapon.parent->animSet;
            self->anim = D_35000_8017AB44;
            self->zPriority = 0xA8;
            self->unk5A = self->ext.weapon.parent->unk5A;
            self->palette = self->ext.weapon.parent->palette;

            SetSpeedX(FIX(4.75));
            if ((self->params & 0xFF00) == 0x300 ||
                (self->params & 0xFF00) == 0x600) {
                self->velocityY = FIX(2.75);
                SetSpeedX(FIX(3.75));
            }
            self->drawFlags = FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
            self->rotX = self->rotY = 0x10;
            self->flags = FLAG_UNK_08000000 | FLAG_UNK_100000;
            self->hitboxWidth = self->hitboxHeight = 9;
            self->attack = 1;
            self->attackElement = 0;
            self->hitboxState = 4;
            self->nFramesInvincibility = 4;
            self->stunFrames = 4;
            self->hitEffect = 1;
            self->entityRoomIndex = 0;
            g_api.func_80118894(self);
            g_api.PlaySfx(SFX_UNK_6AD);
            self->step++;
            return;
        }
        DestroyEntity(self);
        return;
    case 1:
        if (self->hitFlags) {
            self->step = 3;
        }
        DecelerateX(FIX(7.0 / 32));
        DecelerateY(FIX(7.0 / 32));
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (self->rotX < 0x100) {
            self->rotX += 0x10;
            self->rotY += 0x10;
        }
        if ((self->velocityX == 0) && (self->rotX >= 0x100)) {
            self->ext.weapon.unk7E = 0x200;
            self->step++;
        }
        break;
    case 3:
        self->rotX -= 0xC;
        self->rotY -= 0xC;
        if (self->rotX < 0x10) {
            DestroyEntity(self);
            return;
        }
        // fallthrough
    case 2:
        self->velocityY = rsin(self->ext.weapon.lifetime);
        self->posY.val += self->velocityY;
        self->ext.weapon.lifetime += 0x20;
        self->posY.val += self->velocityY; // ???
        if (!(self->ext.weapon.unk7E & 7)) {
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xC) | 0x40, 0);
        }
        if (((--self->ext.weapon.unk7E << 0x10) == 0) ||
            (self->hitFlags != 0)) {
            self->step = 3;
        }
        break;
    }
}

static s32 func_35000_8017B604(Primitive* prim, s32 x, s32 y) {
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
