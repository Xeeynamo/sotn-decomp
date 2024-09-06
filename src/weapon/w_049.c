// SPDX-License-Identifier: AGPL-3.0-or-later
// Weapon ID #49. Used by weapons:
// Firebrand, Marsil, Unknown#179, Unknown#180
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "w_049_1.h"
#include "w_049_2.h"
#define g_Animset w_049_1
#define g_Animset2 w_049_2
#include "shared.h"
#include "sfx.h"

extern WeaponAnimation D_15B000_8017AFFC[];
extern s16 D_15B000_8017B03C[];
extern AnimationFrame D_15B000_8017B074[];
extern AnimationFrame D_15B000_8017B0D4[];
extern AnimationFrame D_15B000_8017B10C[];
extern s32 D_15B000_8017C8CC;

/* near-duplicate of EntityWeaponAttack_w_048 */
void EntityWeaponAttack(Entity* self) {
    s8 animIndex = (self->params & 0x7FFF) >> 8;
    WeaponAnimation* anim = &D_15B000_8017AFFC[animIndex];

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

        if (animIndex == 1) {
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xC) | 0x5B, 0);
        }
        if (animIndex == 3) {
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xC) | 0x5F, 0);
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xC) + 0x10040, 0);
        }
        SetWeaponProperties(self, 0);
        D_15B000_8017C8CC = 0;
        self->step += 1;
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
    if ((D_15B000_8017C8CC == 0) && (PLAYER.animFrameIdx == 1)) {
        if ((animIndex == PLAYER.animFrameIdx) || (animIndex == 3)) {
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xC) | 0x5D, 0);
            g_api.PlaySfx(SFX_FM_EXPLODE_B);
        }
        if (animIndex == 2) {
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xC) + 0x1005D, 0);
            g_api.PlaySfx(SFX_FM_EXPLODE_B);
        }
    }
    D_15B000_8017C8CC = PLAYER.animFrameIdx;
    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;
}

void func_15B000_8017B88C(Entity* ent, Point16* outPoint, bool arg2) {
    s32 idx;

    idx = PLAYER.ext.player.anim - 0x41;
    if (PLAYER.facingLeft) {
        ent->posX.i.hi = PLAYER.posX.i.hi - D_15B000_8017B03C[idx * 4 + 0];
        if (arg2) {
            outPoint->x = -(D_15B000_8017B03C[idx * 4 + 2] * 3 / 4);
        } else {
            outPoint->x = -(D_15B000_8017B03C[idx * 4 + 2] * 2 / 3);
        }
    } else {
        ent->posX.i.hi = PLAYER.posX.i.hi + D_15B000_8017B03C[idx * 4 + 0];
        if (arg2) {
            outPoint->x = D_15B000_8017B03C[idx * 4 + 2] * 3 / 4;
        } else {
            outPoint->x = D_15B000_8017B03C[idx * 4 + 2] * 2 / 3;
        }
    }
    ent->posY.i.hi = PLAYER.posY.i.hi + D_15B000_8017B03C[idx * 4 + 1];
    if (arg2) {
        outPoint->y = D_15B000_8017B03C[idx * 4 + 3] * 3 / 4;
    } else {
        outPoint->y = D_15B000_8017B03C[idx * 4 + 3] * 2 / 3;
    }
}

s32 func_ptr_80170004(Entity* self) {
    s32 angle;
    s32 magnitude;
    s16 baseX, baseY;
    s16 offsetX;
    bool rotate;
    s16 initialX, initialY;
    u8 params;

    if ((PLAYER.ext.player.anim < 0x41 || PLAYER.ext.player.anim > 0x47) ||
        g_Player.unk46 == 0) {
        DestroyEntity(self);
        return;
    }

    params = self->params;
    offsetX = 0xC;
    if (PLAYER.facingLeft) {
        offsetX = -0xC;
    }

    baseX = offsetX + PLAYER.posX.i.hi;
    baseY = PLAYER.posY.i.hi - 0x1A;
    if (PLAYER.drawFlags & FLAG_DRAW_ROTY) {
        baseY = PLAYER.posY.i.hi - 0x1F;
    }

    switch (self->step) {
    case 0:
        rotate = 0;
        self->animSet = 9;
        self->anim = D_15B000_8017B074;
        self->zPriority = PLAYER.zPriority + 2;
        self->facingLeft = 1;
        self->flags = FLAG_UNK_100000 | FLAG_UNK_40000 | FLAG_UNK_20000;
        self->drawFlags = FLAG_DRAW_ROTZ;
        self->ext.weapon.unk80 = params * 512;
        self->rotZ = self->ext.weapon.unk80 - FIX(1.0 / 64);
        self->attack = self->ext.weapon.parent->attack;
        self->attackElement = self->ext.weapon.parent->attackElement;
        self->hitboxState = self->ext.weapon.parent->hitboxState;
        self->nFramesInvincibility =
            self->ext.weapon.parent->nFramesInvincibility;
        self->stunFrames = self->ext.weapon.parent->stunFrames;
        self->hitEffect = self->ext.weapon.parent->hitEffect;
        self->entityRoomIndex = self->ext.weapon.parent->entityRoomIndex;
        g_api.func_80118894(self);
        self->hitboxWidth = 6;
        self->hitboxHeight = 6;
        self->ext.weapon.unk7E = 0x40;
        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
        self->ext.weapon.lifetime = 0x28;
        self->step++;
        break;
    case 1:
        rotate = 1;
        initialX = self->ext.weapon.unk7E; // ???
        if (self->ext.weapon.unk7E >= 8) {
            self->ext.weapon.unk7E -= 3;
        }
        if (--self->ext.weapon.lifetime == 0x18 && params == 0) {
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xC) | 0x40, 0);
        }
        self->ext.weapon.unk80 = self->ext.weapon.unk80 - 0x20;
        if (self->ext.weapon.lifetime < 0x11) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    angle = self->ext.weapon.unk80;
    initialX = self->posX.i.hi;
    magnitude = self->ext.weapon.unk7E;
    initialY = self->posY.i.hi;
    self->posX.i.hi = baseX + (((rcos(angle) >> 4) * magnitude) >> 8);
    self->posY.i.hi = baseY - (((rsin(angle) >> 4) * magnitude) >> 8);
    if (rotate != 0) {
        self->rotZ = ratan2(-(s16)(self->posY.i.hi - initialY),
                            (s16)(self->posX.i.hi - initialX));
    }
}

void func_ptr_80170008(Entity* self) {
    Primitive* prim;
    s16 primIndex;
    s32 i;
    s16 angle;
    s16 lifetime;
    s32 xOffset;
    u16 posY;
    u16 posX;
    u8 red, green;

    if (!(PLAYER.ext.weapon.anim > 0x40 && PLAYER.ext.weapon.anim < 0x48) ||
        g_Player.unk46 == 0) {
        DestroyEntity(self);
        return;
    }

    xOffset = 12;
    if (PLAYER.facingLeft != 0) {
        xOffset = -12;
    }

    self->posX.i.hi = xOffset + PLAYER.posX.i.hi;
    self->posY.i.hi = PLAYER.posY.i.hi - 26;
    if (PLAYER.drawFlags & FLAG_DRAW_ROTY) {
        self->posY.i.hi -= 5;
    }

    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 16);
        self->primIndex = primIndex;
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags = FLAG_HAS_PRIMS | FLAG_UNK_40000 | FLAG_UNK_20000;
        prim = &g_PrimBuf[self->primIndex];

        for (i = 0; i < 16; i++) {
            angle = i * 256;
            prim->u0 = ((rcos(angle) * 2) >> 8) + 32;
            prim->v0 = -32 - ((rsin(angle) * 2) >> 8);

            angle = (i + 1) * 256;
            prim->u1 = ((rcos((s32)angle) * 2) >> 8) + 32;
            prim->v1 = -32 - ((rsin((s32)angle) * 2) >> 8);

            if (prim->v0 < 4) {
                prim->v0 = 0xFF;
            }
            if (prim->v1 < 4) {
                prim->v1 = 0xFF;
            }

            prim->u2 = prim->u3 = 0x20;
            prim->v2 = prim->v3 = 0xE0;
            prim->g3 = prim->g2 = 0x7F;
            prim->clut = 0x15F;
            prim->tpage = 0x1A;
            prim->r1 = prim->b1 = prim->g1 = 0;
            prim->r0 = prim->b0 = prim->g0 = 0;
            prim->r2 = prim->r3 = 0xFF;
            prim->b2 = prim->b3 = 0;
            prim->type = PRIM_GT4;
            prim->priority = PLAYER.zPriority + 2;
            prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_TPAGE2 |
                             DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            prim = prim->next;
        }
        self->ext.weapon.lifetime = 4;
        self->ext.weapon.unk7E = 0x19;
        if (self->params & 0x7F00) {
            self->ext.weapon.unk7E = 40;
        }
        self->step++;
        break;

    case 1:
        if (self->ext.weapon.lifetime < 40) {
            self->ext.weapon.lifetime += 6;
        }
        self->ext.weapon.unk7E--;
        if (!self->ext.weapon.unk7E) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    red = 0x80;
    if (self->ext.weapon.unk7E < 8) {
        red = (self->ext.weapon.unk7E * 16);
    }
    i = 0; // FAKE? why here?
    green = red >> 1;
    posX = self->posX.i.hi;
    posY = self->posY.i.hi;
    lifetime = self->ext.weapon.lifetime;
    prim = &g_PrimBuf[self->primIndex];

    for (i = 0; i < 16; i++) {
        prim->x2 = prim->x3 = posX;
        prim->y2 = prim->y3 = posY;

        prim->r3 = red;
        prim->r2 = red;

        prim->g3 = green;
        prim->g2 = green;

        angle = i * 256;
        prim->x0 = posX + (((rcos(angle) >> 4) * lifetime) >> 8);
        prim->y0 = posY - (((rsin(angle) >> 4) * lifetime) >> 8);

        angle = (i + 1) * 256;
        prim->x1 = posX + (((rcos(angle) >> 4) * lifetime) >> 8);
        prim->y1 = posY - (((rsin(angle) >> 4) * lifetime) >> 8);
        prim = prim->next;
    }
}

void func_ptr_8017000C(Entity* self) {
    Point16 point;
    s32 palette;
    u32 upperParams;
    s32 lowerParams;
    s16 tempX, tempY;

    if ((PLAYER.ext.player.anim < 0x41 || PLAYER.ext.player.anim > 0x47 ||
         g_Player.unk46 == 0) &&
        (self->step == 0)) {
        DestroyEntity(self);
        return;
    }

    upperParams = (self->params >> 8) & 0x7F;
    lowerParams = (u8)self->params;
    if (self->step == 0) {
        self->facingLeft = PLAYER.facingLeft;
        if (upperParams == 1) {
            func_15B000_8017B88C(self, &point, false);
        } else {
            func_15B000_8017B88C(self, &point, true);
        }

        tempX = point.x;
        tempY = point.y;
        self->posX.i.hi += (tempX * lowerParams / 8);
        self->posY.i.hi += (tempY * lowerParams / 8);
        self->posY.i.hi += rand() % 16;
        self->posX.i.hi += rand() % 4;

        SetSpriteBank2(g_Animset2);
        self->animSet = ANIMSET_OVL(0x11);
        self->unk5A = 0x65;
        palette = rand() & 7;
        self->palette = palette + 0x117;
        if (g_HandId != 0) {
            self->palette = palette + 0x12F;
            self->unk5A += 2;
            self->animSet += 2;
        }
        self->anim = D_15B000_8017B0D4;
        self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
        self->rotX = 0x80;
        self->rotY = 0x80;
        self->rotX = self->rotY = (rand() & 0x3F) | 0x80;
        self->zPriority = PLAYER.zPriority + (rand() & 1) * 4;
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_100000;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        if (rand() % 3) {
            self->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE;
        }

        self->velocityY = -FIX(0.5);
        if (PLAYER.drawFlags & FLAG_DRAW_ROTY) {
            if (PLAYER.ext.player.anim >= 0x43 &&
                PLAYER.ext.player.anim < 0x45) {
                self->posY.i.hi -= 1;
            } else {
                self->posY.i.hi -= 3;
            }
        }
        self->ext.weapon.equipId = self->ext.weapon.parent->ext.weapon.equipId;
        SetWeaponProperties(self, 0);
        self->enemyId = self->ext.weapon.parent->enemyId;
        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
        self->hitboxWidth = 6;
        self->hitboxHeight = 6;
        self->step++;
    } else {
        self->posY.val += self->velocityY;
        if (self->animFrameDuration < 0) {
            DestroyEntity(self);
        }
    }
}

s32 func_ptr_80170010(Entity* self) {
    s32 magnitude;
    s16 baseX, baseY;
    s16 offsetX;
    s16 angle;
    s8 params;

    if ((PLAYER.ext.player.anim < 0x41 || PLAYER.ext.player.anim > 0x47 ||
         g_Player.unk46 == 0) &&
        (self->step == 0 || self->step == 1)) {
        DestroyEntity(self);
        return;
    }

    params = self->params;
    offsetX = 0xC;
    if (PLAYER.facingLeft != 0) {
        offsetX = -0xC;
    }

    baseX = offsetX + PLAYER.posX.i.hi;
    baseY = PLAYER.posY.i.hi - 0x1A;
    if (PLAYER.drawFlags & FLAG_DRAW_ROTY) {
        baseY = PLAYER.posY.i.hi - 0x1F;
    }

    switch (self->step) {
    case 0:
        self->facingLeft = 1;
        self->flags = FLAG_UNK_40000 | FLAG_UNK_20000;
        self->ext.weapon.unk80 = params * 512;
        self->ext.weapon.equipId = self->ext.weapon.parent->ext.weapon.equipId;
        SetWeaponProperties(self, 0);
        self->enemyId = self->ext.weapon.parent->enemyId;
        self->hitboxWidth = 0;
        self->hitboxHeight = 0;
        self->ext.weapon.unk7E = 0xC;
        self->ext.weapon.lifetime = rand() % 5;
        self->step++;
        break;
    case 1:
        self->ext.weapon.unk7E += 4;
        self->ext.weapon.unk80 -= 0x20;
        if (self->ext.weapon.unk7E >= 0x40) {
            self->step += 1;
        }
        break;
    case 2:
        self->ext.weapon.unk7E += 4;
        self->flags = FLAG_UNK_08000000;
        if (self->ext.weapon.unk7E >= 0x70) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    angle = self->ext.weapon.unk80;
    magnitude = self->ext.weapon.unk7E;
    self->ext.weapon.lifetime++;
    self->posX.i.hi = baseX + (((rcos(angle) >> 4) * magnitude) >> 8);
    self->posY.i.hi = baseY - (((rsin(angle) >> 4) * magnitude) >> 8);
    if (self->ext.weapon.lifetime % 7 == 0) {
        g_api.CreateEntFactoryFromEntity(
            self, ((g_HandId + 1) << 0xC) | 0x65, 0);
    }
}

static s32 func_ptr_80170014(Entity* self) {
    switch (self->step) {
    case 0:
        SetSpriteBank2(g_Animset2);
        self->animSet = ANIMSET_OVL(0x11);
        self->unk5A = 101;
        self->palette = 0x117;
        if (g_HandId != 0) {
            self->palette = 0x12F;
            self->unk5A += 2;
            self->animSet += 2;
        }
        self->anim = D_15B000_8017B10C;
        self->zPriority = PLAYER.zPriority + 2;
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_100000;
        self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
        self->rotX = self->rotY = 0x100;
        self->drawMode = DRAW_TPAGE | 0x20;
        self->ext.weapon.equipId = self->ext.weapon.parent->ext.weapon.equipId;
        SetWeaponProperties(self, 0);
        self->enemyId = self->ext.weapon.parent->enemyId;
        self->hitboxHeight = self->hitboxWidth = 12;
        self->hitboxOffY = self->hitboxOffX = 0;
        self->velocityY = FIX(-0.375);
        g_api.PlaySfx(SFX_FM_EXPLODE_B);
        self->step++;
        return;
    case 1:
        self->posY.val += self->velocityY;
        if (self->animFrameDuration < 0) {
            DestroyEntity(self);
        }
    }
}

static int GetWeaponId(void) { return 49; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
