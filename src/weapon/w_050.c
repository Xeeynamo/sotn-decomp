// SPDX-License-Identifier: AGPL-3.0-or-later
// Weapon ID #50. Used by weapons:
// Icebrand, Unknown#181, Unknown#199, Unknown#200, Unknown#201
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_050_1.h"
#include "w_050_2.h"
#define g_Animset w_050_1
#define g_Animset2 w_050_2
#include "sfx.h"

extern WeaponAnimation D_162000_8017AFC0[];
extern SpriteParts D_162000_8017A040[];
extern s32 D_162000_8017CBF8;

void EntityWeaponAttack(Entity* self) {
    s8 animIndex = (self->params & 0x7FFF) >> 8;
    WeaponAnimation* anim = &D_162000_8017AFC0[animIndex];
    s32 hand, temp;

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
        SetSpriteBank1(D_162000_8017A040);
        self->animSet = ANIMSET_OVL(0x10);
        self->palette = 0x110;
        self->unk5A = 0x64;
        if (g_HandId != 0) {
            self->animSet += 2;
            self->palette += 0x18;
            self->unk5A += 2;
        }

        self->palette += anim->palette;
        self->flags = FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;
        self->zPriority = PLAYER.zPriority - 2;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;

        if (animIndex == 1) {
            g_api.PlaySfx(SFX_MAGIC_WEAPON_APPEAR_A);
            g_api.CreateEntFactoryFromEntity(self, WFACTORY(0x3A, 0), 0);
            g_api.CreateEntFactoryFromEntity(self, WFACTORY(0x40, 0), 0);
        }
        SetWeaponProperties(self, 0);
        D_162000_8017CBF8 = 0;
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
    if ((D_162000_8017CBF8 == 0) && (PLAYER.animFrameIdx == 1)) {

        if (animIndex == PLAYER.animFrameIdx) {
            g_api.CreateEntFactoryFromEntity(self, WFACTORY(0x44, 0), 0);
            g_api.PlaySfx(SFX_FM_EXPLODE_B);
            g_api.PlaySfx(SFX_UNK_69D);
        }
        hand = (g_HandId + 1) << 0xC;
        temp = FACTORY(0x61, animIndex);
        g_api.CreateEntFactoryFromEntity(self, hand + temp, 0);
    }
    D_162000_8017CBF8 = PLAYER.animFrameIdx;
    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;
}

extern u8 D_162000_8017B000[6][8];

s32 func_162000_8017B784(Primitive* prim, s16 x, s16 y) {
    s16 size;
    u8* uvPtr;

    // Should be able to do this as an array access but nope
    uvPtr = (u8*)D_162000_8017B000;
    uvPtr += (prim->b0 * 8);

    if (prim->b0 >= 3) {
        size = 4;
    } else {
        size = 6;
    }
    if (prim->b0 == 6) {
        return -1;
    }
    prim->x0 = x - size;
    prim->y0 = y - size;
    prim->x1 = x + size;
    prim->y1 = y - size;
    prim->x2 = x - size;
    prim->y2 = y + size;
    prim->x3 = x + size;
    prim->y3 = y + size;

    prim->u0 = *uvPtr++;
    prim->v0 = *uvPtr++;
    prim->u1 = *uvPtr++;
    prim->v1 = *uvPtr++;
    prim->u2 = *uvPtr++;
    prim->v2 = *uvPtr++;
    prim->u3 = *uvPtr++;
    prim->v3 = *uvPtr;
    prim->b1++;
    if (!(prim->b1 & 1)) {
        prim->b0++;
    }
    return 0;
}

extern s16 D_162000_8017B030[];

void func_162000_8017B87C(Entity* ent, Point16* outPoint, bool arg2) {
    s32 idx;

    idx = PLAYER.ext.player.anim - 0x41;
    if (PLAYER.facingLeft) {
        ent->posX.i.hi = PLAYER.posX.i.hi - D_162000_8017B030[idx * 4 + 0];
        if (arg2) {
            outPoint->x = -(D_162000_8017B030[idx * 4 + 2] * 3 / 4);
        } else {
            outPoint->x = -(D_162000_8017B030[idx * 4 + 2] * 2 / 3);
        }
    } else {
        ent->posX.i.hi = PLAYER.posX.i.hi + D_162000_8017B030[idx * 4 + 0];
        if (arg2) {
            outPoint->x = D_162000_8017B030[idx * 4 + 2] * 3 / 4;
        } else {
            outPoint->x = D_162000_8017B030[idx * 4 + 2] * 2 / 3;
        }
    }
    ent->posY.i.hi = PLAYER.posY.i.hi + D_162000_8017B030[idx * 4 + 1];
    if (arg2) {
        outPoint->y = D_162000_8017B030[idx * 4 + 3] * 3 / 4;
    } else {
        outPoint->y = D_162000_8017B030[idx * 4 + 3] * 2 / 3;
    }
}

void func_162000_8017BA38(Entity* ent, Point16* outPoint, bool arg2) {
    s32 idx;

    idx = PLAYER.ext.player.anim - 0x41;
    if (PLAYER.facingLeft) {
        ent->posX.i.hi = PLAYER.posX.i.hi - D_162000_8017B030[idx * 4 + 0];
        if (arg2) {
            outPoint->x = -(D_162000_8017B030[idx * 4 + 2] * 3 / 4);
        } else {
            outPoint->x = -(D_162000_8017B030[idx * 4 + 2] / 2);
        }
    } else {
        ent->posX.i.hi = PLAYER.posX.i.hi + D_162000_8017B030[idx * 4 + 0];
        if (arg2) {
            outPoint->x = D_162000_8017B030[idx * 4 + 2] * 3 / 4;
        } else {
            outPoint->x = D_162000_8017B030[idx * 4 + 2] / 2;
        }
    }
    ent->posY.i.hi = PLAYER.posY.i.hi + D_162000_8017B030[idx * 4 + 1];
    if (arg2) {
        outPoint->y = D_162000_8017B030[idx * 4 + 3] * 3 / 4;
    } else {
        outPoint->y = D_162000_8017B030[idx * 4 + 3] / 2;
    }
}

extern Point16 D_162000_8017CBFC[];
extern Point16 D_162000_8017CD3E;

s32 func_ptr_80170004(Entity* self) {
    Primitive* prim;
    s32 i;
    s16 prim_x, prim_y;
    s16 x, y;
    s16 angle;
    s32 magnitude;
    s16 xOffset;
    s32 params;

    if (PLAYER.ext.player.anim <= 0x40 || PLAYER.ext.player.anim >= 0x48 ||
        !g_Player.unk46) {
        DestroyEntity(self);
        return;
    }

    params = self->params & 0xFF; // unused, for PSP

    xOffset = 0xC;
    if (PLAYER.facingLeft) {
        xOffset = -xOffset;
    }
    x = PLAYER.posX.i.hi + xOffset;
    y = PLAYER.posY.i.hi - 26;
    if (PLAYER.drawFlags & FLAG_DRAW_ROTY) {
        y -= 5;
    }

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 80);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags = FLAG_HAS_PRIMS | FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 80; i++) {
            prim->clut = 0x1B0;
            prim->tpage = 0x1A;
            prim->b0 = 0;
            prim->b1 = 0;
            prim->g0 = 0;
            prim->g1 = (rand() % 24) + 1;
            prim->g2 = 0;
            prim->priority = PLAYER.zPriority + 4;
            prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_TPAGE2 |
                             DRAW_TPAGE | DRAW_HIDE | DRAW_TRANSP;
            prim = prim->next;
        }
        self->ext.weapon.lifetime = 40;
        self->step++;
        break;
    case 1:
        if (--self->ext.weapon.lifetime == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 80; i++) {
        switch (prim->g0) {
        case 0:
            if (--prim->g1 == 0) {
                angle = rand();
                magnitude = (rand() & 0x1F) + 32;
                D_162000_8017CBFC[i].x =
                    x + (((rcos(angle) >> 4) * magnitude) >> 8);
                D_162000_8017CBFC[i].y =
                    y - (((rsin(angle) >> 4) * magnitude) >> 8);
                prim->g0++;
            }
            break;
        case 1:
            prim_x = D_162000_8017CBFC[i].x -
                     (D_162000_8017CBFC[i].x - x) * prim->g2 / 15;
            // n.b.! this should simplify to something similar to `prim_x`
            // above, and on PSP that simplified version matches, but
            // currently it does not match on PSX.
            prim_y = D_162000_8017CBFC[i].y -
                     (D_162000_8017CBFC[i].y -
                      (D_162000_8017CBFC[i].y -
                       (D_162000_8017CBFC[i].y - y) * prim->g2)) /
                         15;
            prim->g2++;
            if (((s16)func_162000_8017B784(prim, prim_x, prim_y)) < 0) {
                prim->drawMode |= DRAW_HIDE;
                prim->g0++;
            } else {
                prim->drawMode &= ~DRAW_HIDE;
            }
            break;
        }
        prim = prim->next;
    }
}

void func_ptr_80170008(Entity* self) {
    const int PrimCount = 16;
    Primitive* prim;
    s16 angle;
    s32 magnitude;
    s32 i;
    s16 offsetX, offsetY;
    s16 baseX, baseY;
    u8 color;

    if (PLAYER.ext.player.anim <= 0x40 || PLAYER.ext.player.anim >= 0x48 ||
        g_Player.unk46 == 0) {
        DestroyEntity(self);
        return;
    }
    offsetX = 0xC;
    if (PLAYER.facingLeft) {
        offsetX = -0xC;
    }
    self->posX.i.hi = PLAYER.posX.i.hi + offsetX;

    offsetY = PLAYER.posY.i.hi;
    self->posY.i.hi = offsetY - 0x1A;
    if (PLAYER.drawFlags & FLAG_DRAW_ROTY) {
        self->posY.i.hi = offsetY - 0x1F;
    }

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, PrimCount);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags = FLAG_HAS_PRIMS | FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < PrimCount; i++) {
            angle = i << 8;
            prim->u0 = +0x20 + ((rcos(angle) * 2) >> 8);
            prim->v0 = -0x20 - ((rsin(angle) * 2) >> 8);
            angle = (i + 1) << 8;
            prim->u1 = +0x20 + ((rcos(angle) * 2) >> 8);
            prim->v1 = -0x20 - ((rsin(angle) * 2) >> 8);
            if (prim->v0 < 4) {
                prim->v0 = 0xFF;
            }
            if (prim->v1 < 4) {
                prim->v1 = 0xFF;
            }
            prim->u2 = prim->u3 = 0x20;
            prim->v2 = prim->v3 = 0xE0;
            prim->clut = 0x15F;
            prim->tpage = 0x1A;
            prim->r1 = prim->b1 = prim->g1 = 0;
            prim->r0 = prim->b0 = prim->g0 = 0;
            prim->b2 = prim->b3 = prim->g2 = prim->g3 = prim->r2 = prim->r3 =
                0xFF;
            prim->type = PRIM_GT4;
            prim->priority = PLAYER.zPriority + 2;
            prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_TPAGE2 |
                             DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            prim = prim->next;
        }
        self->ext.weapon.lifetime = 4;
        self->ext.weapon.unk7E = 0x28;
        self->ext.weapon.equipId = self->ext.weapon.parent->ext.weapon.equipId;
        SetWeaponProperties(self, 0);
        self->enemyId = self->ext.weapon.parent->enemyId;
        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
        self->step++;
        break;
    case 1:
        if (self->ext.weapon.lifetime < 0x28) {
            self->ext.weapon.lifetime += 6;
        }
        if (--self->ext.weapon.unk7E == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    self->hitboxWidth = self->ext.weapon.lifetime - 4;
    self->hitboxHeight = self->ext.weapon.lifetime - 4;

    color = 0x80;
    if (self->ext.weapon.unk7E < 0x10) {
        color = self->ext.weapon.unk7E * 0x10;
    }

    baseX = self->posX.i.hi;
    baseY = self->posY.i.hi;
    magnitude = self->ext.weapon.lifetime;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < PrimCount; i++) {
        angle = i << 8;
        prim->x3 = baseX;
        prim->x2 = baseX;
        prim->y3 = baseY;
        prim->y2 = baseY;
        prim->r2 = prim->r3 = prim->b2 = prim->b3 = prim->g2 = prim->g3 = color;
        prim->x0 = baseX + (((rcos(angle) >> 4) * magnitude) >> 8);
        prim->y0 = baseY - (((rsin(angle) >> 4) * magnitude) >> 8);
        angle = (i + 1) << 8;
        prim->x1 = baseX + (((rcos(angle) >> 4) * magnitude) >> 8);
        prim->y1 = baseY - (((rsin(angle) >> 4) * magnitude) >> 8);
        prim = prim->next;
    }
}

void func_ptr_8017000C(Entity* self) {
    const int PrimCount = 0x20;
    Primitive* prim;
    Point16 point;
    s16 posX, posY;
    s16 offsetX, offsetY;
    s16 randomX, randomY;
    s32 i;

    func_162000_8017B87C(self, &point, true);
    self->facingLeft = PLAYER.facingLeft;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, PrimCount);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags = FLAG_HAS_PRIMS | FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        offsetX = point.x;
        offsetY = point.y;

        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < PrimCount; i++) {
            prim->r1 = 0x20;
            prim->g1 = 0x20;
            prim->b1 = 0x20;

            prim->r0 = (rand() & 0x1F) - 0x80;
            prim->g0 = (rand() & 0x1F) + 0x60;
            prim->b0 = (rand() & 0x1F) + 0xE0;

            randomY = (rand() % 24) - 12;
            randomX = (rand() % 24) - 12;

            prim->x0 = posX + randomX;
            prim->y0 = posY + randomY;

            prim->x1 = offsetX + prim->x0;
            prim->y1 = offsetY + prim->y0;

            prim->r2 = 0;
            prim->r3 = (rand() % 5) + 1;
            prim->priority = PLAYER.zPriority + 4;
            prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_TPAGE2 |
                             DRAW_TPAGE | DRAW_HIDE | DRAW_COLORS | DRAW_TRANSP;

            prim = prim->next;
        }

        self->ext.weapon.equipId = self->ext.weapon.parent->ext.weapon.equipId;
        SetWeaponProperties(self, 0);
        self->enemyId = self->ext.weapon.parent->enemyId;
        self->hitboxOffX = 0x18;
        self->hitboxWidth = 0x18;
        self->hitboxHeight = 8;
        self->hitboxOffY = 0;
        self->ext.weapon.lifetime = 8;
        self->step++;
        break;
    case 1:
        if (--self->ext.weapon.lifetime == 0) {
            DestroyEntity(self);
            return;
        }
    }

    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < PrimCount; i++) {
        switch (prim->r2) {
        case 0:
            if (--prim->r3 == 0) {
                prim->drawMode &= ~DRAW_HIDE;
                prim->r2++;
            }
            break;
        case 1:
            prim->drawMode |= DRAW_HIDE;
            prim->r2++;
            break;
        }
        prim = prim->next;
    }
}

s32 func_ptr_80170010(Entity* self) {
    const int PrimCount = 8;
    Primitive* prim;
    Point16 point;
    s32 params;
    s32 i;
    s16 x, y;
    s16 baseX, baseY;
    s16 prim_x, prim_y;
    s32 result;

    if (PLAYER.ext.player.anim < 0x41 || PLAYER.ext.player.anim > 0x47 ||
        !g_Player.unk46) {
        DestroyEntity(self);
        return;
    }

    params = (self->params & 0x7F00) >> 8;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, PrimCount);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags = FLAG_HAS_PRIMS | FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;
        if (params == 1) {
            func_162000_8017BA38(self, &point, true);
        } else {
            func_162000_8017BA38(self, &point, false);
        }

        baseX = point.x;
        baseY = point.y;

        if (PLAYER.drawFlags & FLAG_DRAW_ROTY) {
            if ((PLAYER.ext.player.anim - 0x41) == 2 ||
                (PLAYER.ext.player.anim - 0x41) == 3) {
                self->posY.i.hi -= 1;
            } else {
                self->posY.i.hi -= 3;
            }
        }

        x = self->posX.i.hi;
        y = self->posY.i.hi;

        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < PrimCount; i++) {
            prim_x = baseX * i / 8 + x;
            prim_y = baseY * i / 8 + y;

            prim_y += rand() % 10;
            prim_x += rand() % 4;

            D_162000_8017CBFC[i].x = prim_x;
            D_162000_8017CBFC[i].y = prim_y;
            prim->clut = 0x1B0;
            prim->tpage = 0x1A;
            prim->b0 = 0;
            prim->b1 = 0;
            prim->g0 = 0;
            prim->g1 = (i * 2) + 1;
            prim->g2 = 0;
            prim->priority = PLAYER.zPriority;
            prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_TPAGE2 |
                             DRAW_TPAGE | DRAW_HIDE | DRAW_TRANSP;
            if (params == 0) {
                prim->drawMode =
                    DRAW_UNK_200 | DRAW_UNK_100 | DRAW_UNK_40 | DRAW_TPAGE2 |
                    DRAW_TPAGE | DRAW_HIDE | DRAW_TRANSP;
            }
            prim = prim->next;
        }
        self->ext.weapon.lifetime = 0x18;
        self->step++;
        break;

    case 1:
        if (--self->ext.weapon.lifetime == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < PrimCount; i++) {
        switch (prim->g0) {
        case 0:
            if (--prim->g1 == 0) {
                prim->g0++;
            }
            break;
        case 1:
            x = D_162000_8017CBFC[i].x;
            y = D_162000_8017CBFC[i].y;
            result = func_162000_8017B784(prim, x, y);
            D_162000_8017CBFC[i].y--;
            if (result < 0) {
                prim->drawMode |= DRAW_HIDE;
                prim->g0++;
            } else {
                prim->drawMode &= ~DRAW_HIDE;
            }
            break;
        }
        prim = prim->next;
    }
}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 50; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
