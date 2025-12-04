// SPDX-License-Identifier: AGPL-3.0-or-later
#include "maria.h"

// ** How to calculate self->unk5A
// GFX_ENTRY(Y, X, ...
// where Y and X are variables for the python script below
// def calc_tpage(y, x):
//     return (y // 0x100) * 0x40 + ((y & 0x80) // 0x40) + \
//            ((x & 0x20) // 0x20) + ((x // 0x20) * 2)

static s32 D_pspeu_092E5F18;
static s32 D_pspeu_092E5D18[0x80];
static Point16 D_pspeu_092E5B18[0x80];
static s32 D_pspeu_092E5B10;
static u8 D_pspeu_092E5B08[8];
static s32 D_pspeu_092E5908[0x80];
static s32 D_pspeu_092E5900;

static AnimationFrame anim_doll_prepare[] = {
    POSE(3, 7, 0), POSE(3, 8, 0), POSE_LOOP(0)};
static AnimationFrame anim_doll_attack[] = {
    POSE(2, 1, 0), POSE(2, 2, 0), POSE(2, 3, 0), POSE(1, 4, 0), POSE(1, 5, 0),
    POSE(2, 6, 0), POSE(1, 5, 0), POSE(2, 4, 0), POSE_LOOP(0)};
static AnimationFrame anim_doll_stand[] = {POSE(1, 9, 0), POSE_LOOP(0)};
void EntityMariaDollAttack(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_UNK_100000;
#ifdef VERSION_PSP
        self->unk5A = 0x19;
#else
        self->unk5A = 0x67;
#endif
        self->zPriority = PLAYER.zPriority - 8;
        self->palette = PAL_WPN_DOLL;
        self->animSet = ANIMSET_WPN_DOLL;
        MarSetAnimation(anim_doll_stand);
        self->facingLeft = PLAYER.facingLeft;
        self->velocityX = 0;
        self->posX.i.hi = PLAYER.posX.i.hi + (self->facingLeft ? -24 : 24);
        self->posY.i.hi = PLAYER.posY.i.hi + 0x18;
        self->hitboxWidth = 0;
        self->hitboxHeight = 0;
        self->hitboxOffX = 0;
        self->hitboxOffY = -8;
        self->ext.mariaDoll.unkB0 = 0;
        MarSetWeaponParams(self, 18, ELEMENT_HOLY, 2, 16, 16, 1, 0);
        g_Player.unk5C = 1;
        self->ext.mariaDoll.timer = 0;
        self->step = 1;
        MarCreateEntFactoryFromEntity(self, BP_DOLL_ACTIVATE, 0);
        break;
    case 1:
        if (self->ext.mariaDoll.timer > 10) {
            MarSetAnimation(anim_doll_prepare);
            self->step = 2;
            self->velocityX = FIX(3.25);
            self->ext.mariaDoll.timer = 0;
        }
        self->ext.mariaDoll.timer++;
        break;
    case 2:
        if (self->hitboxOffX < 24) {
            self->hitboxOffX += 2;
        } else {
            self->hitboxOffX = 24;
        }
        if ((self->hitboxWidth) < 24) {
            self->hitboxWidth += 2;
        } else {
            self->hitboxWidth = 24;
        }
        if ((self->hitboxHeight) < 24) {
            self->hitboxHeight += 4;
        } else {
            self->hitboxHeight = 24;
        }
        if (self->ext.mariaDoll.timer < 15) {
            self->posX.val +=
                self->facingLeft ? -self->velocityX : self->velocityX;
        }
        if (self->ext.mariaDoll.timer == 15) {
            self->velocityX = 0;
            MarSetAnimation(anim_doll_attack);
        }
        if ((self->ext.mariaDoll.timer % 6) == 0) {
            g_api.PlaySfx(SFX_WEAPON_SWISH_A);
        }
        self->ext.mariaDoll.timer++;
        if (self->ext.mariaDoll.timer > 75) {
            MarSetAnimation(anim_doll_stand);
            self->ext.mariaDoll.opacity = 128;
            self->ext.mariaDoll.ttl = 15;
            self->step = 3;
            self->hitboxState = 0;
        }
        break;
    case 3:
        if (self->ext.mariaDoll.ttl > 0) {
            self->ext.mariaDoll.ttl--;
        } else {
            self->ext.mariaDoll.opacity -= 8;
        }
        if (self->ext.mariaDoll.opacity <= 0) {
            SetOpacity(self, 0);
            self->step = 4;
            return;
        }
        SetOpacity(self, self->ext.mariaDoll.opacity);
        break;
    case 4:
        g_Player.unk5C = 0;
        DestroyEntity(self);
        break;
    }
}

void EntityMariaDollActivate(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_UNK_100000;
#ifdef VERSION_PSP
        self->unk5A = 0x19;
#else
        self->unk5A = 0x67;
#endif
        self->zPriority = PLAYER.zPriority - 8;
        self->palette = PAL_WPN_DOLL;
        self->animSet = ANIMSET_WPN_DOLL;
        MarSetAnimation(anim_doll_stand);
        self->ext.mariaDoll.timer = 0;
        self->ext.mariaDoll.opacity = 0;
        self->step = 2;
        self->posX.val = self->ext.mariaDoll.parent->posX.val;
        self->posY.val = self->ext.mariaDoll.parent->posY.val;
        self->ext.mariaDoll.opacity = 64;
        self->ext.mariaDoll.scale = 0x100;
        self->scaleX = self->ext.mariaDoll.scale;
        self->scaleY = self->ext.mariaDoll.scale;
        SetOpacity(self, 64);
        self->drawFlags |= FLAG_DRAW_SCALEX | FLAG_DRAW_SCALEY;
        break;
    case 2:
        self->ext.mariaDoll.timer++;
        if (self->ext.mariaDoll.timer > 10) {
            self->ext.mariaDoll.opacity = 128;
            self->step = 4;
            return;
        }
        self->ext.mariaDoll.opacity -= 2;
        self->ext.mariaDoll.scale += 8;
        SetOpacity(self, self->ext.mariaDoll.opacity);
        self->drawFlags |= FLAG_DRAW_SCALEX | FLAG_DRAW_SCALEY;
        // scaleX and scaleY are also used to scale horizontally and vertically
        self->scaleX = self->ext.mariaDoll.scale;
        self->scaleY = self->ext.mariaDoll.scale;
        break;
    case 4:
        DestroyEntity(self);
        break;
    }
}

static int func_pspeu_092A6958(s32 x, s32 y, s32 horizPixelCount) {
    Collider col;

    g_api.CheckCollision(x, y, &col, 0);
    while (col.effects & EFFECT_UNK_0002) {
        if (horizPixelCount-- < 0) {
            return -1;
        }
        y--;
        g_api.CheckCollision(x, y, &col, 0);
    }
    return y;
}

static int CheckFieldCollisionForCat(
    Entity* entity, s32 x, s32 y, Collider* col) {
    s32 sp3C;
    s32 var_s8;
    s32 var_s7;
    s32 var_s6;
    s32 var_s3;
    s32 var_s2;
    s32 var_s1;
    s32 var_s0;

    var_s3 = abs(x) >> 0x10;
    var_s2 = abs(y) >> 0x10;
    if (x < 0) {
        x = -var_s3;
    } else {
        x = var_s3;
    }
    if (y < 0) {
        y = -var_s2;
    } else {
        y = var_s2;
    }
    var_s7 = entity->posX.i.hi;
    sp3C = var_s7;
    var_s6 = entity->posY.i.hi;
    var_s8 = var_s6;
    if (var_s2 < var_s3) {
        if (var_s3 == 0) {
            return 0;
        }
        for (var_s1 = 0; var_s1 <= var_s3; var_s1++) {
            entity->posX.i.hi = sp3C + (x < 0 ? -var_s1 : var_s1);
            entity->posY.i.hi = var_s8 + (y * var_s1) / var_s3;
            g_api.CheckCollision(entity->posX.i.hi, entity->posY.i.hi, col, 0);
            if (col->effects & (EFFECT_SOLID | EFFECT_UNK_0002)) {
                if (var_s2 == 0) {
                    col->effects = EFFECT_SOLID;
                }
                entity->posX.i.hi = var_s7;
                entity->posY.i.hi = var_s6;
                if (var_s1 && y > 0) {
                    g_api.CheckCollision(
                        entity->posX.i.hi, entity->posY.i.hi + 1, col, 0);
                    if (col->effects & (EFFECT_SOLID | EFFECT_UNK_0002)) {
                        col->effects = EFFECT_UNK_0002;
                    } else {
                        col->effects = EFFECT_SOLID;
                    }
                }
                return 1;
            }
            var_s7 = entity->posX.i.hi;
            var_s6 = entity->posY.i.hi;
        }
    } else {
        if (var_s2 == 0) {
            return 0;
        }
        for (var_s0 = 0; var_s0 <= var_s2; var_s0++) {
            entity->posX.i.hi = sp3C + (x * var_s0) / var_s2;
            entity->posY.i.hi = var_s8 + (y < 0 ? -var_s0 : var_s0);
            g_api.CheckCollision(entity->posX.i.hi, entity->posY.i.hi, col, 0);
            if (col->effects & (EFFECT_SOLID | EFFECT_UNK_0002)) {
                if (var_s3 == 0) {
                    col->effects = EFFECT_UNK_0002;
                }
                entity->posX.i.hi = var_s7;
                entity->posY.i.hi = var_s6;
                if (var_s0 && y > 0) {
                    g_api.CheckCollision(
                        entity->posX.i.hi, entity->posY.i.hi + 1, col, 0);
                    if (col->effects & (EFFECT_SOLID | EFFECT_UNK_0002)) {
                        col->effects = EFFECT_UNK_0002;
                    } else {
                        col->effects = EFFECT_SOLID;
                    }
                }
                return 1;
            }
            var_s7 = entity->posX.i.hi;
            var_s6 = entity->posY.i.hi;
        }
    }
    return 0;
}

static AnimationFrame anim_cat[] = {
    POSE(11, 1, 0), POSE(4, 2, 0), POSE(6, 3, 0),
    POSE(4, 4, 0),  POSE(7, 5, 0), POSE_LOOP(0)};
void EntityMariaCatAttack(Entity* self) {
    Collider col;
    s32 newY;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;

    switch (self->step) {
    case 0:
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_UNK_100000;
#ifdef VERSION_PSP
        self->unk5A = 0x14;
#else
        self->unk5A = 0x6E;
#endif
        self->zPriority = PLAYER.zPriority - 8;
        self->palette = PAL_WPN_CAT;
        self->animSet = ANIMSET_WPN_CAT;
        MarSetAnimation(anim_cat);
        self->facingLeft = PLAYER.facingLeft;
        self->velocityX = FIX(3.0);
        self->posX.i.hi = PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi;
        self->hitboxWidth = 18;
        self->hitboxHeight = 30;
        self->hitboxOffX = 0;
        self->hitboxOffY = -8;
        self->ext.mariaCat.unkB0 = 0;
        MarSetWeaponParams(self, 15, ELEMENT_HOLY, 2, 16, 16, 1, 0);
        self->ext.mariaCat.timer = 0;
        g_Player.unk7A = 1;
        self->ext.mariaCat.nBounce = 3;
        self->step = 2;
        self->ext.mariaCat.opacity = 128;
        break;
    case 1:
        self->velocityX += FIX(1.0);
        if (self->velocityX > FIX(3.0)) {
            self->velocityX = FIX(3.0);
        }
        if ((self->ext.mariaCat.timer % 10) == 0) {
            g_api.PlaySfx(SFX_QUIET_STEPS);
        }
        self->ext.mariaCat.timer++;
        CheckFieldCollisionForCat(
            self, self->facingLeft ? -self->velocityX : self->velocityX, 0,
            &col);
        if (col.effects & EFFECT_SOLID || self->hitFlags == 1) {
            self->velocityX = FIX(-3.0);
            self->velocityY = FIX(-8.0);
            if (col.effects & EFFECT_SOLID) {
                self->ext.mariaCat.nBounce = 0;
            }
            if (self->ext.mariaCat.nBounce > 0) {
                self->ext.mariaCat.nBounce--;
                self->step = 3;
            } else {
                self->step = 4;
            }
            self->ext.mariaCat.timer = 0;
        } else {
            g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi + 1, &col, 0);
            if (!(col.effects & EFFECT_UNK_0002)) {
                self->velocityY = FIX(-8.0);
                self->step = 2;
                self->ext.mariaCat.timer = 0;
            }
        }
        break;
    case 2:
    case 3:
        if (self->step == 2) {
            self->velocityX += FIX(1.0);
            if (self->velocityX > FIX(3.0)) {
                self->velocityX = FIX(3.0);
            }
        }
        self->velocityY += FIX(1.0);
        if (self->velocityY > FIX(4.0)) {
            self->velocityY = FIX(4.0);
        }
        CheckFieldCollisionForCat(
            self, self->facingLeft ? -self->velocityX : self->velocityX,
            self->velocityY, &col);
        if (col.effects & EFFECT_UNK_0002) {
            newY = func_pspeu_092A6958(
                self->posX.i.hi, self->posY.i.hi, self->velocityY >> 16);
            if (newY != -1) {
                self->velocityX = FIX(3.0);
                self->posY.i.hi = newY;
                self->posY.i.lo = 0;
                self->step = 1;
                col.effects = EFFECT_NONE;
                self->hitFlags = 0;
            }
        }
        if ((col.effects & EFFECT_SOLID) || self->hitFlags == 1) {
            self->velocityX = FIX(-3.0);
            self->velocityY = FIX(-8.0);
            if (col.effects & EFFECT_SOLID) {
                self->ext.mariaCat.nBounce = 0;
            }
            if (self->ext.mariaCat.nBounce > 0) {
                self->ext.mariaCat.nBounce--;
                self->step = 3;
            } else {
                self->step = 4;
            }
        }
        break;
    case 4:
        self->hitboxState = 0;
        self->velocityY += FIX(1.0);
        if (self->velocityY > FIX(4.0)) {
            self->velocityY = FIX(4.0);
        }
        self->posX.val += self->facingLeft ? -self->velocityX : self->velocityX;
        self->posY.val += self->velocityY;
        self->ext.mariaCat.opacity -= 8;
        if (self->ext.mariaCat.opacity <= 0) {
            SetOpacity(self, 0);
            self->step = 5;
        } else {
            SetOpacity(self, self->ext.mariaCat.opacity);
        }
        break;
    case 5:
        g_Player.unk7A = 0;
        DestroyEntity(self);
        break;
    }
    if (self->step != 5) {
        if (self->posX.i.hi < -8 || self->posX.i.hi > 264 ||
            self->posY.i.hi > 264) {
            self->step = 5;
        }
    }
    self->hitFlags = 0;
}

static AnimationFrame anim_cat_crash_stand[] = {
    POSE(13, 6, 0), POSE(8, 7, 0), POSE(11, 8, 0), POSE(8, 7, 0), POSE_LOOP(0)};
void EntityMariaCatCrash(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_UNK_100000;
#ifdef VERSION_PSP
        self->unk5A = 0x14;
#else
        self->unk5A = 0x6E;
#endif
        self->zPriority = PLAYER.zPriority - 8;
        self->palette = PAL_WPN_CAT_CRASH;
        self->animSet = ANIMSET_WPN_CAT;
        MarSetAnimation(anim_cat_crash_stand);
        self->ext.mariaCat.timer = 0;
        self->ext.mariaCat.opacity = 0;
        self->ext.mariaCat.unk46 = g_Player.unk46;
        self->step = 1;
        SpawnCrashSummon(2);
        SetOpacity(self, 0);
        break;
    case 1:
        if (g_Player.unk5C == 1) {
            g_api.PlaySfx(SFX_VO_MAR_8F1);
            self->step = 3;
        }
        break;
    case 3:
        self->facingLeft = PLAYER.facingLeft;
        self->posX.i.hi = PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi + 24;
        self->ext.mariaCat.opacity += 16;
        if (self->ext.mariaCat.opacity >= 128) {
            SetOpacity(self, 128);
            self->ext.mariaCat.opacity = 0;
            self->step = 2;
        } else {
            SetOpacity(self, self->ext.mariaCat.opacity);
        }
        break;
    case 4:
        self->posX.i.hi += self->facingLeft ? -4 : 4;
        self->ext.mariaCat.opacity -= 16;
        if (self->ext.mariaCat.opacity <= 0) {
            SetOpacity(self, 0);
            self->ext.mariaCat.opacity = 0;
            self->step = self->ext.mariaCat.timer > 300 ? 5 : 3;
        } else {
            SetOpacity(self, self->ext.mariaCat.opacity);
        }
        break;
    case 2:
        if (self->facingLeft != PLAYER.facingLeft) {
            self->ext.mariaCat.opacity = 128;
            self->step = 4;
        } else {
            self->facingLeft = PLAYER.facingLeft;
            self->posX.i.hi = PLAYER.posX.i.hi;
            self->posY.i.hi = PLAYER.posY.i.hi + 24;
            if (self->ext.mariaCat.timer > 300) {
                self->ext.mariaCat.opacity = 128;
                self->step = 4;
            }
        }
        break;
    case 5:
        g_Player.unk5C = 0;
        DestroyEntity(self);
        break;
    }
    self->ext.mariaCat.timer++;
    if (self->step != 5 && g_Player.padTapped & PAD_SQUARE) {
        // while the big cat is on screen, pressing the Attack button will
        // unleash its power
        MarCreateEntFactoryFromEntity(self, BP_CAT_CRASH_ATTACK, 0);
    }
    self->ext.mariaCat.unk46 = g_Player.unk46;
}

static AnimationFrame anim_cat_crash_attack[] = {
    POSE(1, 10, 0), POSE(1, 11, 0), POSE(1, 12, 0),
    POSE(3, 13, 0), POSE(1, 14, 0), POSE(1, 15, 0),
    POSE(1, 16, 0), POSE(25, 9, 0), POSE_END};
void EntityMariaCatCrashAttack(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_UNK_100000 | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_POS_CAMERA_LOCKED;
#ifdef VERSION_PSP
        self->unk5A = 0x14;
#else
        self->unk5A = 0x6E;
#endif
        self->zPriority = PLAYER.zPriority - 8;
        self->palette = PAL_WPN_CAT;
        self->animSet = ANIMSET_WPN_CAT;
        MarSetAnimation(anim_cat_crash_attack);
        self->facingLeft = PLAYER.facingLeft;
        self->velocityX = FIX(4);
        self->posX.i.hi = PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi + 24;
        self->hitboxWidth = 16;
        self->hitboxHeight = 32;
        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
        self->ext.mariaCat.unkB0 = 0;
        MarSetWeaponParams(
            self, 32, ELEMENT_CUT | ELEMENT_HOLY, 2, 16, 16, 1, 0);
        g_api.PlaySfx(SFX_ALUCARD_SWORD_SWISH);
        self->step = 1;
        break;
    case 1:
        self->posX.val += self->facingLeft ? -self->velocityX : self->velocityX;
        if (self->poseTimer < 0) {
            self->step = 2;
        }
        if (self->posX.i.hi < -16 || self->posX.i.hi > 272) {
            self->step = 2;
            return;
        }
        break;
    case 2:
        DestroyEntity(self);
        break;
    }
}

static AnimationFrame anim_maria_dragon[] = {
    POSE(4, 5, 0), POSE(2, 6, 0),  POSE(1, 7, 0),  POSE(1, 8, 0),
    POSE(1, 9, 0), POSE(2, 10, 0), POSE(4, 11, 0), POSE(1, 8, 0),
    POSE(1, 7, 0), POSE(1, 6, 0),  POSE_LOOP(0)};
void EntityMariaDragonAttack(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_UNK_100000 | FLAG_KEEP_ALIVE_OFFCAMERA;
#ifdef VERSION_PSP
        self->unk5A = 0x15;
#else
        self->unk5A = 0x64;
#endif
        self->zPriority = PLAYER.zPriority - 8;
        self->palette = PAL_WPN_DRAGON;
        self->animSet = ANIMSET_WPN_DRAGON;
        MarSetAnimation(anim_maria_dragon);
        self->facingLeft = PLAYER.facingLeft;
        self->velocityX = 0;
        self->posX.i.hi = PLAYER.posX.i.hi + (PLAYER.facingLeft ? 32 : -32);
        self->posY.i.hi = PLAYER.posY.i.hi - 8;
        self->ext.mariaDragon.y = self->posY.i.hi;
        self->hitboxWidth = 24;
        self->hitboxHeight = 32;
        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
        self->ext.mariaDragon.unkB0 = 0;
        MarSetWeaponParams(self, 42, ELEMENT_HOLY, 2, 16, 16, 1, 0);
        g_Player.unk7A = 1;
        self->ext.mariaDragon.timer = 0;
        self->step = 2;
        // fallthrough
    case 2:
        self->ext.mariaDragon.opacity += 16;
        if (self->ext.mariaDragon.opacity >= 128) {
            SetOpacity(self, 128);
            self->step = 1;
            return;
        }
        SetOpacity(self, self->ext.mariaDragon.opacity);
        break;
    case 1:
        self->velocityX += FIX(0.25);
        if (self->velocityX > FIX(3)) {
            self->velocityX = FIX(3);
        }
        self->posX.val += self->facingLeft ? -self->velocityX : self->velocityX;
        self->posY.i.hi =
            self->ext.mariaDragon.y +
            -rsin(self->ext.mariaDragon.timer << 6) * 0x18 / 0x1000;
        if ((self->ext.mariaDragon.timer % 60) == 0) {
            g_api.PlaySfx(SFX_WING_FLAP_B);
        }
        self->ext.mariaDragon.timer++;
        if (self->posX.i.hi < -16 || self->posX.i.hi > 272) {
            self->step = 3;
            return;
        }
        break;
    case 3:
        g_Player.unk7A = 0;
        DestroyEntity(self);
        break;
    }
}

static s32 NormalizeAngle(s32 angle) {
    angle %= 0x1000;
    if (angle < 0) {
        angle += 0x1000;
    }
    return angle;
}

static Entity* FindTarget(Entity* self) {
    Entity* e;
    s32 i;
    s32 var_s2;
    s32 found;

    found = 0;
    e = &g_Entities[STAGE_ENTITY_START];
    for (i = 0; i < LEN(D_pspeu_092E5908); i++, e++) {
        D_pspeu_092E5908[i] = 0;
        if (!e->entityId) {
            continue;
        }
        if (e->hitboxState == 0) {
            continue;
        }
        if (e->flags & FLAG_UNK_00200000) {
            continue;
        }
        if (e->posX.i.hi < -0x10 || e->posX.i.hi > 0x110) {
            continue;
        }
        if (e->posY.i.hi > 0xF0 || e->posY.i.hi < 0) {
            continue;
        }
        if (e->hitboxState & 8) {
            continue;
        }
        if (e->hitPoints >= 0x7000) {
            continue;
        }
        if (e->flags & FLAG_UNK_80000) {
            found++;
            D_pspeu_092E5908[i] = 1;
        } else {
            e->flags |= FLAG_UNK_80000;
            return e;
        }
    }
    if (found) {
        var_s2 = D_pspeu_092E5B10 % LEN(D_pspeu_092E5908);
        for (i = 0; i < LEN(D_pspeu_092E5908); i++) {
            if (D_pspeu_092E5908[var_s2]) {
                e = &g_Entities[var_s2 + 0x40];
                D_pspeu_092E5B10 = (var_s2 + 1) % LEN(D_pspeu_092E5908);
                return e;
            }
            var_s2 = (var_s2 + 1) % LEN(D_pspeu_092E5908);
        }
    }
    return NULL;
}

static int IsTargetValid(Entity* entity) {
    if (entity == NULL) {
        return 0;
    }
    if (entity->hitboxState == 0) {
        return 0;
    }
    if (entity->posX.i.hi < -0x10) {
        return 0;
    }
    if (entity->posX.i.hi > 0x110) {
        return 0;
    }
    if (entity->posY.i.hi > 0xF0) {
        return 0;
    }
    if (entity->posY.i.hi < 0) {
        return 0;
    }
    if (entity->hitPoints >= 0x7000) {
        return 0;
    }
    if (entity->hitPoints <= 0) {
        return 0;
    }
    return 1;
}

static AnimationFrame anim_dragon_crash[] = {POSE(1, 1, 0), POSE_LOOP(0)};
void EntityMariaDragonCrash(Entity* self) {
    s32 x;
    s32 y;
    s32 angle;
    s32 i;

    switch (self->step) {
    case 0:
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_UNK_100000;
#ifdef VERSION_PSP
        self->unk5A = 0x15;
#else
        self->unk5A = 0x64;
#endif
        self->zPriority = 0x1C0;
        self->palette = PAL_WPN_DRAGON_CRASH;
        self->animSet = ANIMSET_WPN_DRAGON;
        MarSetAnimation(anim_dragon_crash);
        self->facingLeft = 0;
        self->velocityX = 0;
        self->posX.i.hi = PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi - 32;
        self->rotate = 0;
        self->ext.mariaDragon.velocity = 1280;
        self->hitboxWidth = 24;
        self->hitboxHeight = 24;
        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
        self->ext.mariaDragon.unkB0 = 0;
        MarSetWeaponParams(
            self, 24, ELEMENT_HOLY | ELEMENT_THUNDER, 2, 40, 16, 1, 0);
        D_pspeu_092E5900 = 0;
        self->ext.mariaDragon.timer = 0;
        self->step = 1;
        SpawnCrashSummon(4);
        self->ext.mariaDragon.opacity = 0;
        SetOpacity(self, 0);
        break;
    case 1:
        if (g_Player.unk5C == 1) {
            MarCreateEntFactoryFromEntity(self, BP_DRAGON_CRASH_BODY_PART, 0);
            self->step = 2;
            g_api.PlaySfx(SFX_VO_MAR_8F1);
        }
        self->drawFlags |= FLAG_DRAW_ROTATE;
        break;
    case 2:
        if (self->ext.mariaDragon.opacity < 128) {
            self->ext.mariaDragon.opacity += 8;
            SetOpacity(self, self->ext.mariaDragon.opacity);
        } else {
            SetOpacity(self, 128);
        }
        self->drawFlags |= FLAG_DRAW_ROTATE;
        {
            MATRIX m;
            VECTOR vTranslate = {0, 0, 0};
            VECTOR vVelocity;
            SVECTOR svVelocity;
            long out;
            if (!IsTargetValid(self->ext.mariaDragon.target)) {
                self->ext.mariaDragon.target = FindTarget(self);
            }
            if (self->ext.mariaDragon.target) {
                x = self->ext.mariaDragon.target->posX.i.hi;
                y = self->ext.mariaDragon.target->posY.i.hi;
            } else {
                x = PLAYER.posX.i.hi;
                y = PLAYER.posY.i.hi;
            }
            self->rotate = NormalizeAngle(self->rotate);
            angle = NormalizeAngle(
                ratan2(y - self->posY.i.hi, x - self->posX.i.hi));
            if (self->rotate < angle) {
                if (angle - self->rotate < 0x800) {
                    self->rotate += 0x40;
                } else {
                    self->rotate -= 0x40;
                }
            } else if (self->rotate - angle < 0x800) {
                self->rotate -= 0x40;
            } else {
                self->rotate += 0x40;
            }
            SetGeomOffset(0, 0);
            func_psp_089285A0(self->rotate, &m);
            TransMatrix(&m, &vTranslate);
            SetRotMatrix(&m);
            SetTransMatrix(&m);
            svVelocity.vx = self->ext.mariaDragon.velocity;
            svVelocity.vy = 0;
            svVelocity.vz = 0;
            RotTrans(&svVelocity, &vVelocity, &out);
            self->velocityX = vVelocity.vx << 8;
            self->velocityY = vVelocity.vy << 8;
            FntPrint("%08x : %08x\n", self->velocityX, self->velocityY);
            self->posX.val += self->velocityX;
            self->posY.val += self->velocityY;
            if ((self->ext.mariaDragon.timer % 120) == 0) {
                g_api.PlaySfx(SFX_HIPPOGRYPH_FIRE_ATTACK);
            }
            self->ext.mariaDragon.timer++;
            if (self->ext.mariaDragon.timer > 300) {
                self->step = 3;
            }
        }
        break;
    case 3:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->ext.mariaDragon.timer++;
        if (self->ext.mariaDragon.timer > 300 &&
            (self->posX.i.hi < -0x100 || self->posX.i.hi > 0x200 ||
             self->posY.i.hi < -0x100 || self->posY.i.hi > 0x200)) {
            self->step = 4;
        }
        break;
    case 4:
        g_Player.unk5C = 0;
        D_pspeu_092E5900 = 0;
        DestroyEntity(self);
        break;
    }
    if (g_Player.unk5C == 1 && self->step != 4) {
        if (D_pspeu_092E5900 == 0x80) {
            for (i = 0; i < 0x40; i++) {
                D_pspeu_092E5B18[i].x = D_pspeu_092E5B18[i + 0x40].x;
                D_pspeu_092E5B18[i].y = D_pspeu_092E5B18[i + 0x40].y;
            }
            D_pspeu_092E5900 -= 0x40;
        }
        if (D_pspeu_092E5900 < 0x80) {
            D_pspeu_092E5B18[D_pspeu_092E5900].x =
                self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            D_pspeu_092E5B18[D_pspeu_092E5900].y =
                self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            D_pspeu_092E5900++;
        }
    }
}

void EntityMariaDragonCrashBodyPart(Entity* self) {
    s32 xStart;
    s32 xEnd;
    s32 yStart;
    s32 yEnd;
    s32 var_s6;
    s32 var_s5;
    s32 u;
    s32 v;
    s32 var_s2;
    s32 i;
    Primitive* prim;

    switch (self->step) {
    case 0:
        self->primIndex =
            g_api.AllocPrimitives(PRIM_GT4, LEN(D_pspeu_092E5B08));
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
#ifdef VERSION_PSP
        self->unk5A = 0x15;
#else
        self->unk5A = 0x64;
#endif
        self->zPriority = 0x1C0;
        self->palette = PAL_WPN_DRAGON_CRASH;
        self->animSet = ANIMSET_WPN_DRAGON;
        MarSetAnimation(anim_dragon_crash);
        self->facingLeft = PLAYER.facingLeft;
        self->velocityX = 0;
        self->posX.i.hi = PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi;
        self->hitboxWidth = 24;
        self->hitboxHeight = 24;
        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
        self->ext.mariaDragon.unkB0 = 0;
        MarSetWeaponParams(
            self, 24, ELEMENT_HOLY | ELEMENT_THUNDER, 2, 40, 16, 1, 0);
        for (i = 0; i < LEN(D_pspeu_092E5B08); i++) {
            D_pspeu_092E5B08[i] = 0;
        }
        self->step = 1;
        // fallthrough
    case 1:
        xStart = 0;
        xEnd = 0;
        yStart = 0;
        yEnd = 0;
        prim = &g_PrimBuf[self->primIndex];
        var_s2 = D_pspeu_092E5900 - 1;
        for (i = 0; i < LEN(D_pspeu_092E5B08); i++) {
#ifdef VERSION_PSP
            prim->tpage = 5;
#else
            prim->tpage = 0x19;
#endif
            prim->clut = self->palette & 0x3FF;
            prim->priority = self->zPriority;
            if (var_s2 >= 7) {
                var_s6 = D_pspeu_092E5B18[var_s2].x - g_Tilemap.scrollX.i.hi;
                var_s5 = D_pspeu_092E5B18[var_s2].y - g_Tilemap.scrollY.i.hi;
                var_s2 -= 7;
                if (var_s2 < 0) {
                    var_s2 = 0;
                }
                {
                    s32 spD4 =
                        D_pspeu_092E5B18[var_s2].x - g_Tilemap.scrollX.i.hi;
                    s32 spD0 =
                        D_pspeu_092E5B18[var_s2].y - g_Tilemap.scrollY.i.hi;
                    MATRIX m;
                    VECTOR spA0 = {0, 0, 0};
                    VECTOR vPosEnd;
                    VECTOR sp80;
                    VECTOR vPosStart;
                    VECTOR sp60;
                    SVECTOR svPosEnd;
                    SVECTOR sp50;
                    SVECTOR svPosStart;
                    SVECTOR sp40;
                    long out;
                    s32 angle;
                    angle =
                        NormalizeAngle(ratan2(spD0 - var_s5, spD4 - var_s6));
                    func_psp_089285A0(angle, &m);
                    SetGeomOffset(var_s6, var_s5);
#ifndef VERSION_PSP
                    // I do not know why this works. The stack might be messed
                    // up and function just so happen to match PSP decomp.
                    spA0.vx = var_s6;
                    spA0.vy = var_s5;
#endif
                    TransMatrix(&m, &spA0);
                    SetRotMatrix(&m);
                    SetTransMatrix(&m);
                    if (i == 0) {
                        sp40.vx = -16;
                        sp40.vy = -16;
                        sp40.vz = 0;
                        svPosStart.vx = 16;
                        svPosStart.vy = -16;
                        svPosStart.vz = 0;
                        sp50.vx = -16;
                        sp50.vy = 16;
                        sp50.vz = 0;
                        svPosEnd.vx = 16;
                        svPosEnd.vy = 16;
                        svPosEnd.vz = 0;
                        RotTrans(&sp40, &sp60, &out);
                        RotTrans(&svPosStart, &vPosStart, &out);
                        RotTrans(&sp50, &sp80, &out);
                        RotTrans(&svPosEnd, &vPosEnd, &out);
                        prim->x0 = sp60.vx;
                        prim->y0 = sp60.vy;
                        prim->x1 = vPosStart.vx;
                        prim->y1 = vPosStart.vy;
                        prim->x2 = sp80.vx;
                        prim->y2 = sp80.vy;
                        prim->x3 = vPosEnd.vx;
                        prim->y3 = vPosEnd.vy;
                    } else {
                        svPosStart.vx = 16;
                        svPosStart.vy = -16;
                        svPosStart.vz = 0;
                        svPosEnd.vx = 16;
                        svPosEnd.vy = 16;
                        svPosEnd.vz = 0;
                        RotTrans(&svPosStart, &vPosStart, &out);
                        RotTrans(&svPosEnd, &vPosEnd, &out);
                        prim->x0 = xStart;
                        prim->y0 = yStart;
                        prim->x1 = vPosStart.vx;
                        prim->y1 = vPosStart.vy;
                        prim->x2 = xEnd;
                        prim->y2 = yEnd;
                        prim->x3 = vPosEnd.vx;
                        prim->y3 = vPosEnd.vy;
                    }
                    xStart = vPosStart.vx;
                    yStart = vPosStart.vy;
                    xEnd = vPosEnd.vx;
                    yEnd = vPosEnd.vy;
                }

                if (i == 7) {
                    u = 0xE0;
                    v = 0x20;
                } else if (i == 6) {
                    u = 0xE0;
                    v = 0;
                } else {
                    u = 0x80;
                    v = 0;
                }
#ifndef VERSION_PSP
                // Dragon GFXs are re-located in the VRAM on other platforms
                u -= 0x80;
#endif
                prim->u1 = u;
                prim->v1 = v + 0x1F;
                prim->u0 = u + 0x1F;
                prim->v0 = v + 0x1F;
                prim->u3 = u;
                prim->v3 = v;
                prim->u2 = u + 0x1F;
                prim->v2 = v;
                prim->drawMode = DRAW_DEFAULT;
                D_pspeu_092E5B08[i] += 0x10;
                if (D_pspeu_092E5B08[i] < 0x80) {
                    prim->drawMode |=
                        DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
                } else {
                    D_pspeu_092E5B08[i] = 0x80;
                }
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = D_pspeu_092E5B08[i];
                prim->g0 = prim->g1 = prim->g2 = prim->g3 = D_pspeu_092E5B08[i];
                prim->b0 = prim->b1 = prim->b2 = prim->b3 = D_pspeu_092E5B08[i];
            } else {
                prim->drawMode = DRAW_HIDE;
            }
            prim = prim->next;
        }
        if (g_Player.unk5C != 0) {
            return;
        }
        self->step = 2;
        break;
    case 2:
        DestroyEntity(self);
        break;
    }
}

static int GetFireWingsPivotY() {
    switch (PLAYER.step) {
    case PL_S_CROUCH:
        return -20;
    default:
        return -36;
    }
}

static AnimationFrame anim_fire_wings[] = {
    POSE(3, 9, 0),  POSE(3, 10, 0), POSE(3, 11, 0), POSE(3, 12, 0),
    POSE(3, 13, 0), POSE(3, 14, 0), POSE(3, 9, 0),  POSE(3, 10, 0),
    POSE(3, 11, 0), POSE(3, 12, 0), POSE_LOOP(0)};
void EntityMariaCardinalAttack(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_UNK_100000 | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_POS_CAMERA_LOCKED;
#ifdef VERSION_PSP
        self->unk5A = 0x11;
#else
        self->unk5A = 0x65;
#endif
        self->drawMode = DRAW_TPAGE | DRAW_TPAGE2;
        self->zPriority = PLAYER.zPriority - 8;
        self->palette = PAL_WPN_CARDINAL;
        self->animSet = ANIMSET_WPN_CARDINAL;
        MarSetAnimation(anim_fire_wings);
        self->facingLeft = 0;
        self->velocityX = 0;
        self->posX.i.hi = PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi + 0x18 + GetFireWingsPivotY();
        self->scaleX = 0;
        self->scaleY = 0;
        self->drawFlags = FLAG_DRAW_SCALEX | FLAG_DRAW_SCALEY;
        self->hitboxWidth = 48;
        self->hitboxHeight = 40;
        self->hitboxOffX = 0;
        self->hitboxOffY = -20;
        self->ext.mariaCardinal.unkB0 = 0;
        MarSetWeaponParams(
            self, 32, ELEMENT_HOLY | ELEMENT_FIRE, 2, 32, 16, 1, 0);
        g_api.PlaySfx(SFX_FIREBALL_SHOT_B);
        g_Player.unk7A = 1;
        self->ext.mariaCardinal.timer = 0;
        self->step++;
        break;
    case 1:
        self->posX.i.hi = PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi + 0x18 + GetFireWingsPivotY();
        self->hitboxOffY = -20;
        self->scaleX += 16;
        self->scaleY += 16;
        if (self->scaleX == 256) {
            self->step++;
        }
        break;
    case 2:
        self->posX.i.hi = PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi + 0x18 + GetFireWingsPivotY();
        self->hitboxOffY = -20;
        self->drawFlags = FLAG_DRAW_DEFAULT;
        self->ext.mariaCardinal.timer++;
        if (self->ext.mariaCardinal.timer >= 60) {
            self->step++;
        }
        break;
    case 3:
        g_Player.unk7A = 0;
        DestroyEntity(self);
        break;
    }
    if (PLAYER.step != PL_S_CARDINAL_ATTACK) {
        self->step = 3;
    }
}

static AnimationFrame anim_cardinal_crash[] = {
    POSE(9, 3, 0), POSE(6, 4, 0), POSE(6, 5, 0), POSE(8, 6, 0),
    POSE(6, 7, 0), POSE(6, 8, 0), POSE_LOOP(0)};
void EntityMariaCardinalCrash(Entity* self) {
    s32 var_s0;

    switch (self->step) {
    case 0:
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_UNK_100000;
#ifdef VERSION_PSP
        self->unk5A = 0x11;
#else
        self->unk5A = 0x65;
#endif
        self->zPriority = 0x1C0;
        self->palette = PAL_WPN_CARDINAL;
        self->animSet = ANIMSET_WPN_CARDINAL;
        MarSetAnimation(anim_cardinal_crash);
        self->facingLeft = PLAYER.facingLeft;
        if (PLAYER.facingLeft) {
            var_s0 = 24;
        } else {
            var_s0 = -24;
        }
        self->posX.i.hi = PLAYER.posX.i.hi + var_s0;
        self->posY.i.hi = PLAYER.posY.i.hi + 24;
#if defined(VERSION_PC)
        g_Player.unk20 = (signed long long)self;
#else
        g_Player.unk20 = (s32)self;
#endif
        self->ext.mariaCardinal.timer = 0;
        self->ext.mariaCardinal.nSpawn = 0;
        self->ext.mariaCardinal.opacity = 0;
        self->step = 1;
        SpawnCrashSummon(1);
        SetOpacity(self, 0);
        break;
    case 1:
        if (g_Player.unk5C == 1) {
            g_api.PlaySfx(SFX_VO_MAR_8F1);
            self->step = 3;
        }
        break;
    case 3:
        self->ext.mariaCardinal.opacity += 16;
        if (self->ext.mariaCardinal.opacity >= 128) {
            SetOpacity(self, 128);
            self->step = 2;
        } else {
            SetOpacity(self, self->ext.mariaCardinal.opacity);
        }
        break;
    case 2:
        if (self->ext.mariaCardinal.timer > 300) {
            self->ext.mariaCardinal.opacity = 128;
            self->step = 4;
        }
        break;
    case 4:
        self->posY.i.hi -= 4;
        self->ext.mariaCardinal.opacity -= 16;
        if (self->ext.mariaCardinal.opacity <= 0) {
            SetOpacity(self, 0);
            self->step = 5;
        } else {
            SetOpacity(self, self->ext.mariaCardinal.opacity);
        }
        break;
    case 5:
        g_Player.unk20 = 0;
        g_Player.unk5C = 0;
        DestroyEntity(self);
        break;
    }
    self->ext.mariaCardinal.timer++;
    if (g_Player.unk5C == 1 && self->step == 2 &&
        self->ext.mariaCardinal.timer < 240 &&
        (self->ext.mariaCardinal.timer % 5) == 0) {
        MarCreateEntFactoryFromEntity(self, BP_CARDINAL_CRASH_FIREBALL, 0);
        self->ext.mariaCardinal.nSpawn++;
    }
}

static s32 NormalizeAngle2(s32 angle) {
    angle %= 0x1000;
    if (angle < 0) {
        angle += 0x1000;
    }
    return angle;
}

static Entity* FindTarget2(Entity* self) {
    Entity* e;
    s32 i;
    s32 var_s2;
    s32 found;

    found = 0;
    e = &g_Entities[STAGE_ENTITY_START];
    for (i = 0; i < LEN(D_pspeu_092E5D18); i++, e++) {
        D_pspeu_092E5D18[i] = 0;
        if (!e->entityId) {
            continue;
        }
        if (e->hitboxState == 0) {
            continue;
        }
        if (e->flags & FLAG_UNK_00200000) {
            continue;
        }
        if (e->posX.i.hi < -0x10 || e->posX.i.hi > 0x110) {
            continue;
        }
        if (e->posY.i.hi > 0xF0 || e->posY.i.hi < 0) {
            continue;
        }
        if (e->hitboxState & 8) {
            continue;
        }
        if (self->facingLeft && self->posX.i.hi < e->posX.i.hi) {
            continue;
        }
        if (!self->facingLeft && self->posX.i.hi > e->posX.i.hi) {
            continue;
        }
        if (e->hitPoints >= 0x7000) {
            continue;
        }
        if (e->flags & FLAG_UNK_80000) {
            found++;
            D_pspeu_092E5D18[i] = 1;
        } else {
            e->flags |= FLAG_UNK_80000;
            return e;
        }
    }
    if (found) {
        var_s2 = D_pspeu_092E5F18 % LEN(D_pspeu_092E5D18);
        for (i = 0; i < LEN(D_pspeu_092E5D18); i++) {
            if (D_pspeu_092E5D18[var_s2]) {
                e = &g_Entities[var_s2 + 0x40];
                D_pspeu_092E5F18 = (var_s2 + 1) % LEN(D_pspeu_092E5D18);
                return e;
            }
            var_s2 = (var_s2 + 1) % LEN(D_pspeu_092E5D18);
        }
    }
    return NULL;
}

static int IsTargetValid2(Entity* entity) {
    if (entity == NULL) {
        return 0;
    }
    if (entity->hitboxState == 0) {
        return 0;
    }
    if (entity->posX.i.hi < -0x10) {
        return 0;
    }
    if (entity->posX.i.hi > 0x110) {
        return 0;
    }
    if (entity->posY.i.hi > 0xF0) {
        return 0;
    }
    if (entity->posY.i.hi < 0) {
        return 0;
    }
    if (entity->hitPoints >= 0x7000) {
        return 0;
    }
    if (entity->hitPoints <= 0) {
        return 0;
    }
    return 1;
}

static void func_pspeu_092A9D48(Entity* entity, s32 x, s32 y) {
    entity->ext.mariaCardinalCrash.pos1.x = x;
    entity->ext.mariaCardinalCrash.pos1.y = y;
    entity->ext.mariaCardinalCrash.pos2.x = x;
    entity->ext.mariaCardinalCrash.pos2.y = y;
    entity->ext.mariaCardinalCrash.pos3.x = x;
    entity->ext.mariaCardinalCrash.pos3.y = y;
    entity->ext.mariaCardinalCrash.pos4.x = x;
    entity->ext.mariaCardinalCrash.pos4.y = y;
}

static void func_pspeu_092A9DE8(Entity* entity, s32 x, s32 y) {
    entity->ext.mariaCardinalCrash.pos4.x =
        entity->ext.mariaCardinalCrash.pos3.x;
    entity->ext.mariaCardinalCrash.pos4.y =
        entity->ext.mariaCardinalCrash.pos3.y;
    entity->ext.mariaCardinalCrash.pos3.x =
        entity->ext.mariaCardinalCrash.pos2.x;
    entity->ext.mariaCardinalCrash.pos3.y =
        entity->ext.mariaCardinalCrash.pos2.y;
    entity->ext.mariaCardinalCrash.pos2.x =
        entity->ext.mariaCardinalCrash.pos1.x;
    entity->ext.mariaCardinalCrash.pos2.y =
        entity->ext.mariaCardinalCrash.pos1.y;
    entity->ext.mariaCardinalCrash.pos1.x = x;
    entity->ext.mariaCardinalCrash.pos1.y = y;
}

static AnimationFrame anim_cardinal_crash_fireball[] = {
    POSE(0, 1, 0), POSE_LOOP(0)};
void EntityMariaCardinalCrashFireball(Entity* self) {
    s32 acceleration;
    s32 initialAcceleration;
    s32 yStart;
    MATRIX sp74;
    VECTOR sp64;
    VECTOR sp54;
    SVECTOR sp4C;
    s32 angle;
    s32 targetX;
    s32 targetY;
    Entity* parent;
    s8 color;
    s32 i;
    s32 x;
    s32 y;
    Primitive* prim;

    acceleration = 64;
    initialAcceleration = 115;
    parent = *(Entity**)&g_Player.unk20;
    switch (self->step) {
    case 0: {
        if (g_Player.unk5C == 0 || parent == NULL) {
            DestroyEntity(self);
            return;
        }
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 4);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags =
            FLAG_HAS_PRIMS | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_POS_CAMERA_LOCKED;
#ifdef VERSION_PSP
        self->unk5A = 0x11;
#else
        self->unk5A = 0x65;
#endif
        self->zPriority = 0x1C0;
        self->palette = PAL_WPN_CARDINAL;
        self->animSet = ANIMSET_WPN_CARDINAL;
        MarSetAnimation(anim_cardinal_crash_fireball);
        self->facingLeft = parent->facingLeft;
        self->posX.i.hi = parent->posX.i.hi + (self->facingLeft ? 37 : -37);
        self->posY.i.hi = parent->posY.i.hi - 52;
        func_pspeu_092A9D48(self, self->posX.i.hi, self->posY.i.hi);
        self->ext.mariaCardinalCrash.defaultTargetX =
            self->posX.i.hi + (self->facingLeft ? -200 : 200);
        self->ext.mariaCardinalCrash.defaultTargetY = self->posY.i.hi;
        if (parent->ext.mariaCardinalCrash.defaultTargetY & 1) {
            self->ext.mariaCardinalCrash.angle = (rand() % 0x400) / 2;
            yStart = -(rand() % 24);
        } else {
            self->ext.mariaCardinalCrash.angle = 0x400 - (rand() % 0x400) / 2;
            yStart = rand() % 24;
        }

        self->posY.i.hi += self->facingLeft ? yStart : -yStart;
        self->ext.mariaCardinalCrash.angle +=
            (self->facingLeft ? 0 : 0x800) - 0x200;
        self->hitboxWidth = 16;
        self->hitboxHeight = 16;
        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
        self->ext.mariaCardinalCrash.unkB0 = 0;
        MarSetWeaponParams(
            self, 32, ELEMENT_HOLY | ELEMENT_FIRE, 2, 28, 16, 1, 0);
        self->ext.mariaCardinalCrash.timer = 0;
        self->ext.mariaCardinalCrash.velocityX = (rand() % 384) + 0x80;
        self->step = 1;
        g_api.PlaySfx(SFX_PSP_MARIA_CARDINAL_CRASH);
    } break;
    case 1: {
        self->ext.mariaCardinalCrash.timer++;
        {
            MATRIX m;
            VECTOR vTransform = {0, 0, 0};
            VECTOR vVelocity;
            SVECTOR svVelocity;
            long sp48;
            if (self->ext.mariaCardinalCrash.timer < 35) {
                if (IsTargetValid2(self->ext.mariaCardinalCrash.target) == 0) {
                    self->ext.mariaCardinalCrash.target = FindTarget2(self);
                }
                if (self->ext.mariaCardinalCrash.target) {
                    targetX = self->ext.mariaCardinalCrash.target->posX.i.hi;
                    targetY = self->ext.mariaCardinalCrash.target->posY.i.hi;
                    if (abs(targetX - self->posX.i.hi) < 16 &&
                        abs(targetY - self->posY.i.hi) < 16) {
                        self->ext.mariaCardinalCrash.timer = 35;
                    }
                } else {
                    targetX = self->ext.mariaCardinalCrash.defaultTargetX;
                    targetY = self->ext.mariaCardinalCrash.defaultTargetY;
                }
                self->ext.mariaCardinalCrash.angle =
                    NormalizeAngle2(self->ext.mariaCardinalCrash.angle);
                angle = NormalizeAngle2(ratan2(
                    targetY - self->posY.i.hi, targetX - self->posX.i.hi));
                if (self->ext.mariaCardinalCrash.angle < angle) {
                    if (angle - self->ext.mariaCardinalCrash.angle < 0x800) {
                        self->ext.mariaCardinalCrash.angle += 0x50;
                    } else {
                        self->ext.mariaCardinalCrash.angle -= 0x50;
                    }
                } else {
                    if (self->ext.mariaCardinalCrash.angle - angle < 0x800) {
                        self->ext.mariaCardinalCrash.angle -= 0x50;
                    } else {
                        self->ext.mariaCardinalCrash.angle += 0x50;
                    }
                }
                self->ext.mariaCardinalCrash.velocityX += acceleration;
                if (self->ext.mariaCardinalCrash.velocityX > 0x400) {
                    self->ext.mariaCardinalCrash.velocityX = 0x400;
                }
            } else {
                self->ext.mariaCardinalCrash.velocityX += initialAcceleration;
            }
            SetGeomOffset(0, 0);
            func_psp_089285A0(self->ext.mariaCardinalCrash.angle, &m);
            TransMatrix(&m, &vTransform);
            SetRotMatrix(&m);
            SetTransMatrix(&m);
            svVelocity.vx = self->ext.mariaCardinalCrash.velocityX;
            svVelocity.vy = 0;
            svVelocity.vz = 0;
            RotTrans(&svVelocity, &vVelocity, &sp48);
            self->velocityX = vVelocity.vx << 8;
            self->velocityY = vVelocity.vy << 8;
            self->posX.val += self->velocityX;
            self->posY.val += self->velocityY;
            if (self->ext.mariaCardinalCrash.timer % 2 == 0) {
                func_pspeu_092A9DE8(self, self->posX.i.hi, self->posY.i.hi);
            } else {
                self->ext.mariaCardinalCrash.pos1.x = self->posX.i.hi;
                self->ext.mariaCardinalCrash.pos1.y = self->posY.i.hi;
            }
            prim = &g_PrimBuf[self->primIndex];
            for (i = 0; i < 4; i++) {
                color = -0x80;
                prim->clut = PAL_WPN_CARDINAL & 0x3FF;
                prim->priority = self->zPriority;
                prim->drawMode = DRAW_DEFAULT;
                switch (i) {
                case 0:
                    x = self->ext.mariaCardinalCrash.pos1.x;
                    y = self->ext.mariaCardinalCrash.pos1.y;
                    break;
                case 1:
                    x = self->ext.mariaCardinalCrash.pos2.x;
                    y = self->ext.mariaCardinalCrash.pos2.y;
                    break;
                case 2:
                    x = self->ext.mariaCardinalCrash.pos3.x;
                    y = self->ext.mariaCardinalCrash.pos3.y;
                    break;
                case 3:
                    x = self->ext.mariaCardinalCrash.pos4.x;
                    y = self->ext.mariaCardinalCrash.pos4.y;
                    break;
                }
                prim->x0 = x - 8;
                prim->y0 = y - 8;
                prim->x1 = x + 8;
                prim->y1 = y - 8;
                prim->x2 = x - 8;
                prim->y2 = y + 8;
                prim->x3 = x + 8;
                prim->y3 = y + 8;
                if (i == 0) {
                    prim->u0 = 0xB8;
                    prim->v0 = 0x68;
                    prim->u1 = 0xCF;
                    prim->v1 = 0x68;
                    prim->u2 = 0xB8;
                    prim->v2 = 0x7F;
                    prim->u3 = 0xCF;
                    prim->v3 = 0x7F;
#ifdef VERSION_PSP
                    prim->tpage = 0x4;
#else
                    prim->tpage = 0x19;
#endif
                } else {
                    prim->u0 = 0x98;
                    prim->v0 = 0x38;
                    prim->u1 = 0xA7;
                    prim->v1 = 0x38;
                    prim->u2 = 0x98;
                    prim->v2 = 0x47;
                    prim->u3 = 0xA7;
                    prim->v3 = 0x47;
#ifdef VERSION_PSP
                    prim->tpage = 0x24;
#else
                    prim->tpage = 0x39;
#endif
                    prim->drawMode |= FLAG_DRAW_SCALEX | FLAG_DRAW_ROTATE;
                    if (i == 1) {
                        color = -0x80;
                    } else if (i == 2) {
                        color = 0x60;
                    } else if (i == 3) {
                        color = 0x40;
                    }
                }
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = color;
                prim->g0 = prim->g1 = prim->g2 = prim->g3 = color;
                prim->b0 = prim->b1 = prim->b2 = prim->b3 = color;
                prim = prim->next;
            }
            if (self->ext.mariaCardinalCrash.timer > 35 &&
                (self->posX.i.hi < -16 || self->posX.i.hi > 272)) {
                self->step = 2;
            }
        }
    } break;
    case 2:
        DestroyEntity(self);
        break;
    }
}

static AnimationFrame anim_turtle[] = {POSE(1, 1, 0), POSE_LOOP(0)};
void EntityMariaTurtleAttack(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_UNK_100000;
#ifdef VERSION_PSP
        self->unk5A = 0x10;
#else
        self->unk5A = 0x6D;
#endif
        self->zPriority = PLAYER.zPriority - 8;
        self->palette = PAL_WPN_TURTLE;
        self->animSet = ANIMSET_WPN_TURTLE;
        MarSetAnimation(anim_turtle);
        self->facingLeft = PLAYER.facingLeft;
        self->velocityX = 0;
        self->ext.mariaTurtleAttack.x = 0;
        self->posX.i.hi = PLAYER.posX.i.hi + self->ext.mariaTurtleAttack.x;
        self->posY.i.hi = PLAYER.posY.i.hi + 24;
        self->hitboxWidth = 24;
        self->hitboxHeight = 48;
        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
        self->attack = 255;
        self->attackElement = ELEMENT_NONE;
        self->hitboxState = 4;
        self->nFramesInvincibility = 6;
        self->stunFrames = 0;
        self->hitEffect = 1;
        self->entityRoomIndex = 1;
        g_Player.unk7A = 1;
        self->ext.mariaTurtleAttack.timer = 0;
        self->step++;
        break;
    case 1:
        self->posX.i.hi = PLAYER.posX.i.hi + self->ext.mariaTurtleAttack.x;
        self->posY.i.hi = PLAYER.posY.i.hi + 24;
        self->ext.mariaTurtleAttack.timer++;
        if (self->ext.mariaTurtleAttack.timer >= 180) {
            self->step++;
        }
        break;
    case 2:
        g_Player.unk7A = 0;
        DestroyEntity(self);
        break;
    }
}

static AnimationFrame anim_turtle_crash_vortex[] = {
    POSE(1, 2, 0), POSE_LOOP(0)};
static AnimationFrame anim_turtle_crash[] = {
    POSE(19, 3, 0), POSE(19, 4, 0), POSE(19, 5, 0), POSE(19, 6, 0),
    POSE_LOOP(0)};
void EntityMariaTurtleCrash(Entity* self) {
    s32 x;

    switch (self->step) {
    case 0:
        self->flags = FLAG_UNK_100000 | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_POS_CAMERA_LOCKED;
#ifdef VERSION_PSP
        self->unk5A = 0x10;
#else
        self->unk5A = 0x6D;
#endif
        self->zPriority = PLAYER.zPriority - 6;
        self->palette = PAL_WPN_TURTLE;
        self->animSet = ANIMSET_WPN_TURTLE;
        MarSetAnimation(anim_turtle_crash);
        self->facingLeft = PLAYER.facingLeft;
        if (PLAYER.facingLeft) {
            x = -74;
        } else {
            x = 74;
        }
        self->posX.i.hi = PLAYER.posX.i.hi + x;
        self->posY.i.hi = PLAYER.posY.i.hi - 16;
        self->scaleX = 0;
        self->scaleY = 0;
        self->drawFlags |= FLAG_DRAW_SCALEX | FLAG_DRAW_SCALEY;
        g_Player.unk28 = NULL;
#if defined(VERSION_PC)
        g_Player.unk20 = (signed long long)self;
#else
        g_Player.unk20 = (s32)self;
#endif
        g_Player.unk24 = 0;
        self->ext.mariaTurtleCrash.timer = 0;
        self->ext.mariaTurtleCrash.timer2 = 0;
        g_Player.unk2C = -1;
        self->step = 1;
        SpawnCrashSummon(3);
        SetOpacity(self, 0);
        return;
    case 1:
        if (g_Player.unk5C == 1) {
            g_api.PlaySfx(SFX_VO_MAR_8F1);
            MarCreateEntFactoryFromEntity(self, BP_TURTLE_CRASH_VORTEX, 0);
            self->step = 3;
        }
        break;
    case 3:
        self->ext.mariaTurtleCrash.timer2 += 16;
        if (self->ext.mariaTurtleCrash.timer2 >= 128) {
            SetOpacity(self, 0x80);
            self->step = 2;
            return;
        }
        SetOpacity(self, self->ext.mariaTurtleCrash.timer2);
        break;
    case 2:
        if (self->scaleX < 256) {
            self->scaleX += 16;
            self->scaleY += 16;
        } else {
            self->drawFlags &= ~(FLAG_DRAW_SCALEX | FLAG_DRAW_SCALEY);
        }
        if ((self->ext.mariaTurtleCrash.timer % 60) == 0) {
            g_api.PlaySfx(SFX_MAGIC_NOISE_SWEEP);
        }
        self->ext.mariaTurtleCrash.timer++;
        if (self->ext.mariaTurtleCrash.timer >= 0xFF) {
            self->step = 5;
        }
        break;
    case 5:
        if (self->scaleX > 0x80) {
            self->drawFlags |=
                FLAG_DRAW_SCALEX | FLAG_DRAW_SCALEY | FLAG_DRAW_ROTATE;
            self->scaleX -= 0x20;
            self->scaleY -= 0x20;
            self->rotate += 0xF78;
            return;
        }
        self->ext.mariaTurtleCrash.timer2 = 0x80;
        self->step = 4;
        break;
    case 4:
        self->ext.mariaTurtleCrash.timer2 -= 0x10;
        if (self->ext.mariaTurtleCrash.timer2 <= 0) {
            SetOpacity(self, 0);
            self->drawFlags |=
                FLAG_DRAW_ROTATE | FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
            self->step = 6;
            func_pspeu_092BFEB0(g_Player.unk20);
            g_Player.unk2C = 0xB4;
            return;
        }
        SetOpacity(self, self->ext.mariaTurtleCrash.timer2);
        self->drawFlags |=
            FLAG_DRAW_SCALEX | FLAG_DRAW_SCALEY | FLAG_DRAW_ROTATE;
        break;
    case 6:
        if (g_Player.unk28 == NULL) {
            self->step = 7;
            self->ext.mariaTurtleCrash.timer3 = 0;
            return;
        }
        if (g_Player.unk2C == 0) {
            g_api.PlaySfx(SFX_HEALTH_PICKUP);
            g_Player.unk56 = 1;
            g_Player.unk58 = g_Player.unk24;
            self->step = 7;
            self->ext.mariaTurtleCrash.timer3 = 0;
            return;
        }
        g_Player.unk2C--;
        break;
    case 7:
        self->ext.mariaTurtleCrash.timer3++;
        if (self->ext.mariaTurtleCrash.timer3 > 60) {
            g_Player.unk28 = NULL;
            g_Player.unk20 = 0;
            g_Player.unk5C = 0;
            DestroyEntity(self);
        }
        break;
    }
}

void EntityMariaTurtleCrashVortex(Entity* self) {
    Entity* entity;
    s32 x;

    entity = *(Entity**)&g_Player.unk20;
    switch (self->step) {
    case 0:
        self->flags = FLAG_UNK_100000 | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_POS_CAMERA_LOCKED;
#ifdef VERSION_PSP
        self->unk5A = 0x10;
#else
        self->unk5A = 0x6D;
#endif
        self->zPriority = PLAYER.zPriority - 7;
        self->palette = PAL_WPN_TURTLE;
        self->animSet = ANIMSET_WPN_TURTLE;
        MarSetAnimation(anim_turtle_crash_vortex);
        self->facingLeft = 0;
        self->velocityX = 0;
        self->ext.mariaTurtleVortex.rotation = 0xF0;
        if (entity == NULL) {
            if (PLAYER.facingLeft) {
                x = -74;
            } else {
                x = 74;
            }
            self->posX.i.hi = PLAYER.posX.i.hi + x;
            self->posY.i.hi = PLAYER.posY.i.hi - 0x10;
        } else {
            self->posX.i.hi = entity->posX.i.hi;
            self->posY.i.hi = entity->posY.i.hi;
        }
        self->scaleX = 0;
        self->scaleY = 0;
        self->drawFlags |= FLAG_DRAW_SCALEX | FLAG_DRAW_SCALEY;
        self->drawMode |= DRAW_TPAGE;
        self->drawFlags |= FLAG_DRAW_ROTATE | FLAG_DRAW_OPACITY;
        self->rotate = 0;
        self->opacity = 0x80;
        self->hitboxWidth = 48;
        self->hitboxHeight = 48;
        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
        self->ext.mariaTurtleVortex.unkB0 = 0;
        MarSetWeaponParams(
            self, 5, ELEMENT_WATER | ELEMENT_HOLY, 2, 32, 0, 2, 0);
        self->ext.mariaTurtleVortex.hitboxState = self->hitboxState;
        self->hitboxState = 0;
        self->ext.mariaTurtleVortex.timer = 0;
        self->step = 1;
        self->rotate +=
            0x1000 - (0x1000 / self->ext.mariaTurtleVortex.rotation);
        return;
    case 1:
        if (self->scaleX < 256) {
            self->scaleX += 16;
            self->scaleY += 16;
        } else {
            self->hitboxState = self->ext.mariaTurtleVortex.hitboxState;
            self->drawFlags &= ~(FLAG_DRAW_SCALEX | FLAG_DRAW_SCALEY);
        }
        self->ext.mariaTurtleVortex.timer++;
        if (self->ext.mariaTurtleVortex.timer >= 240) {
            self->hitboxState = 0;
            self->step = 2;
        }
        if (self->ext.mariaTurtleVortex.timer % 8 == 0) {
            self->ext.mariaTurtleVortex.rotation -= 5;
        }
        self->rotate +=
            0x1000 - (0x1000 / self->ext.mariaTurtleVortex.rotation);
        return;
    case 2:
        if (self->ext.mariaTurtleVortex.rotation >= 65) {
            self->ext.mariaTurtleVortex.rotation -= 5;
        } else {
            self->step = 3;
        }
        self->rotate +=
            0x1000 - (0x1000 / self->ext.mariaTurtleVortex.rotation);
        return;
    case 3:
        if (self->scaleX > 0) {
            self->scaleX -= 8;
            self->scaleY -= 8;
            self->drawFlags |= FLAG_DRAW_SCALEX | FLAG_DRAW_SCALEY;
        } else {
            self->step = 4;
        }
        self->rotate +=
            0x1000 - (0x1000 / self->ext.mariaTurtleVortex.rotation);
        return;
    case 4:
        DestroyEntity(self);
        return;
    }
}
