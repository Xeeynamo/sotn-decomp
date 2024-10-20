// SPDX-License-Identifier: AGPL-3.0-or-later
// Weapon ID #48. Used by weapons:
// Thunderbrand, Unknown#178
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_048_1.h"
#include "w_048_2.h"
#define g_Animset w_048_1
#define g_Animset2 w_048_2

extern WeaponAnimation D_154000_8017AFC0[];
extern SpriteParts D_154000_8017A040[];
extern s32 D_154000_8017C3B4;

/* near-duplicate of EntityWeaponAttack_w_049 */
void EntityWeaponAttack(Entity* self) {
    s8 animIndex = (self->params & 0x7FFF) >> 8;
    WeaponAnimation* anim = &D_154000_8017AFC0[animIndex];
    s32 var_s0;

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
        SetSpriteBank1(D_154000_8017A040);
        self->animSet = ANIMSET_OVL(0x10);
        self->palette = PAL_DRA(0x110);
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

        if (animIndex != 0) {
            g_api.CreateEntFactoryFromEntity(self, WFACTORY(0x38, 0), 0);
            g_api.CreateEntFactoryFromEntity(self, WFACTORY(0x3A, 1), 0);
            g_api.CreateEntFactoryFromEntity(self, WFACTORY(0x3A, 2), 0);
            g_api.CreateEntFactoryFromEntity(self, WFACTORY(0x3A, 3), 0);
            g_api.CreateEntFactoryFromEntity(self, WFACTORY(0x40, 0), 0);
        }
        SetWeaponProperties(self, 0);
        D_154000_8017C3B4 = 0;
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
    if (D_154000_8017C3B4 == 0 && PLAYER.animFrameIdx == 1) {
        inline void create(Entity * self, s32 a, s32 b) {
            g_api.CreateEntFactoryFromEntity(self, a + b, 0);
        }

        var_s0 = 0x10;
        if (animIndex != 0) {
            var_s0 = 0x20;
        }

        create(self, ((g_HandId + 1) << 0xC), FACTORY(0x38, var_s0 + 0));
        create(self, ((g_HandId + 1) << 0xC), FACTORY(0x3A, var_s0 + 1));
        create(self, ((g_HandId + 1) << 0xC), FACTORY(0x3A, var_s0 + 2));
        create(self, ((g_HandId + 1) << 0xC), FACTORY(0x3A, var_s0 + 3));
    }
    D_154000_8017C3B4 = PLAYER.animFrameIdx;
    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;
}

extern s16 D_154000_8017B000[];

void func_154000_8017B810(Entity* ent, Point16* outPoint, bool arg2) {
    s32 idx;

    idx = PLAYER.ext.player.anim - 0x41;
    if (PLAYER.facingLeft) {
        ent->posX.i.hi = PLAYER.posX.i.hi - D_154000_8017B000[idx * 4 + 0];
        if (arg2) {
            outPoint->x = -(D_154000_8017B000[idx * 4 + 2] / 2);
        } else {
            outPoint->x = -(D_154000_8017B000[idx * 4 + 2]);
        }
    } else {
        ent->posX.i.hi = PLAYER.posX.i.hi + D_154000_8017B000[idx * 4 + 0];
        if (arg2) {
            outPoint->x = D_154000_8017B000[idx * 4 + 2] / 2;
        } else {
            outPoint->x = D_154000_8017B000[idx * 4 + 2];
        }
    }
    ent->posY.i.hi = PLAYER.posY.i.hi + D_154000_8017B000[idx * 4 + 1];
    if (arg2) {
        outPoint->y = D_154000_8017B000[idx * 4 + 3] / 2;
    } else {
        outPoint->y = D_154000_8017B000[idx * 4 + 3];
    }
}

extern u16 D_154000_8017AFE0[];

s32 func_ptr_80170004(Entity* self) {
    const int PrimCount = 10;
    Primitive* prim;
    s16 x, y;
    s16 angle;
    s16 newXPos, newYPos;
    s16 xOffset, yOffset;
    s16 scale;
    s32 params;
    Point16 point;
    s32 i;
    s32 red, green, blue;
    s32 colorIndex;

    if (PLAYER.ext.weapon.anim < 65 || PLAYER.ext.weapon.anim >= 72 ||
        !g_Player.unk46) {
        DestroyEntity(self);
        return;
    }

    params = ((self->params >> 8) & 0x7f);

    if (params < 16) {
        xOffset = 12;
        if (PLAYER.facingLeft) {
            xOffset = -xOffset;
        }
        self->posX.i.hi = PLAYER.posX.i.hi + xOffset;
        self->posY.i.hi = PLAYER.posY.i.hi - 26;
        newXPos = self->posX.i.hi;
        newYPos = self->posY.i.hi - 48;
    } else {
        if (params >= 32) {
            func_154000_8017B810(self, &point, false);
        } else {
            func_154000_8017B810(self, &point, true);
        }

        newXPos = self->posX.i.hi + point.x;
        newYPos = self->posY.i.hi + point.y;
    }

    self->facingLeft = PLAYER.facingLeft;

    if (PLAYER.drawFlags & FLAG_DRAW_ROTY) {
        if (params < 16) {
            self->posY.i.hi -= 3;
            newYPos -= 3;
        }
        if ((PLAYER.ext.weapon.anim - 65) == 2 ||
            (PLAYER.ext.weapon.anim - 65) == 3) {
            self->posY.i.hi--;
            newYPos--;
        } else {
            self->posY.i.hi -= 3;
            newYPos -= 3;
        }
    }

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, PrimCount);

        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags = FLAG_HAS_PRIMS | FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;
        colorIndex = (params & 0xF);
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < PrimCount; i++) {
            red = D_154000_8017AFE0[colorIndex * 4];
            blue = D_154000_8017AFE0[colorIndex * 4 + 1];
            green = D_154000_8017AFE0[colorIndex * 4 + 2];

            prim->r0 = (((red & 0xFFFF) * (10 - i)) / 10);
            prim->b0 = (((blue & 0xFFFF) * (10 - i)) / 10);
            prim->g0 = (((green & 0xFFFF) * (10 - i)) / 10);

            prim->r1 = ((red & 0xFFFF) * (9 - i)) / 10;
            prim->b1 = ((blue & 0xFFFF) * (9 - i)) / 10;
            prim->g1 = ((green & 0xFFFF) * (9 - i)) / 10;

#ifdef VERSION_PSP
            prim->x2 = rand() & 0x7FFF;
#else
            prim->x2 = rand();
#endif

            prim->priority = PLAYER.zPriority + 4;
            prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_TPAGE2 |
                             DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            prim = prim->next;
        }

        self->ext.weapon.equipId = self->ext.weapon.parent->ext.weapon.equipId;

        SetWeaponProperties(self, 0);
        self->enemyId = self->ext.weapon.parent->enemyId;

        if (params < 16) {
            self->hitboxOffX = 0;
            self->hitboxOffY = -20;
            self->hitboxWidth = 4;
            self->hitboxHeight = 20;
            self->ext.weapon.lifetime = 40;
        } else {
            if (params >= 32) {
                if (!(params & 0xF)) {
                    self->hitboxOffX = 32;
                    self->hitboxOffY = 0;
                    self->hitboxWidth = 32;
                    self->hitboxHeight = 6;
                } else {
                    self->hitboxState = 0;
                }
            }
            self->ext.weapon.lifetime = 6;
        }
        self->step++;
        break;
    case 1:
        if (--self->ext.weapon.lifetime == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    x = self->posX.i.hi;
    y = self->posY.i.hi;
    xOffset = newXPos - x;
    yOffset = newYPos - y;

    scale = 3;

    prim = &g_PrimBuf[self->primIndex];

    for (i = 0; i < PrimCount; i++) {
        prim->x0 = x;
        prim->y0 = y;
        angle = prim->x2;
        prim->x2 += 768;

        prim->x1 = self->posX.i.hi + xOffset * (i + 1) / 10;
        prim->x1 += (((rcos(angle) >> 4) * scale) >> 8);

        prim->y1 = self->posY.i.hi + yOffset * (i + 1) / 10;
        prim->y1 -= (((rsin(angle) >> 4) * scale) >> 8);

        x = prim->x1;
        y = prim->y1;

        prim = prim->next;
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
    u8 blue;

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

        self->flags = FLAG_HAS_PRIMS | FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;
        prim = &g_PrimBuf[self->primIndex];

        for (i = 0; i < 16; i++) {
            angle = i * 256;
            prim->u0 = ((rcos(angle) * 2) >> 8) + 32;
            prim->v0 = -32 - ((rsin(angle) * 2) >> 8);

            angle = (i + 1) * 256;
            prim->u1 = ((rcos(angle) * 2) >> 8) + 32;
            prim->v1 = -32 - ((rsin(angle) * 2) >> 8);

            if (prim->v0 < 4) {
                prim->v0 = 0xFF;
            }
            if (prim->v1 < 4) {
                prim->v1 = 0xFF;
            }

            prim->u2 = prim->u3 = 0x20;
            prim->v2 = prim->v3 = 0xE0;
            prim->b2 = prim->b3 = 0x80;
            prim->clut = 0x15F;
            prim->tpage = 0x1A;
            prim->r1 = prim->b1 = prim->g1 = 0;
            prim->r0 = prim->b0 = prim->g0 = 0;
            prim->r3 = prim->g3 = 0;
            prim->r2 = prim->g2 = 0;
            prim->type = PRIM_GT4;
            prim->priority = PLAYER.zPriority + 2;
            prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_TPAGE2 |
                             DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            prim = prim->next;
        }
        self->ext.weapon.lifetime = 4;
        self->ext.weapon.unk7E = 0x28;
        g_api.PlaySfx(SFX_THUNDER_B);
        self->step++;
        break;

    case 1:
        if (self->ext.weapon.lifetime < 24) {
            self->ext.weapon.lifetime += 4;
        }
        self->ext.weapon.unk7E--;
        if (!self->ext.weapon.unk7E) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    blue = 0x80;
    if (self->ext.weapon.unk7E < 16) {
        blue = self->ext.weapon.unk7E * 8;
    }
    posX = self->posX.i.hi;
    posY = self->posY.i.hi;
    lifetime = self->ext.weapon.lifetime;
    prim = &g_PrimBuf[self->primIndex];

    for (i = 0; i < 16; i++) {
        prim->x2 = prim->x3 = posX;
        prim->y2 = prim->y3 = posY;

        prim->b3 = blue;
        prim->b2 = blue;

        angle = i * 256;
        prim->x0 = posX + (((rcos(angle) >> 4) * lifetime) >> 8);
        prim->y0 = posY - (((rsin(angle) >> 4) * lifetime) >> 8);

        angle = (i + 1) * 256;
        prim->x1 = posX + (((rcos(angle) >> 4) * lifetime) >> 8);
        prim->y1 = posY - (((rsin(angle) >> 4) * lifetime) >> 8);
        prim = prim->next;
    }
}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 48; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
